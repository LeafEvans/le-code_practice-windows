import { TimerComponent } from '../components/TimerComponent'
import { ControlButtonsComponent } from '../components/ControlButtonsComponent'
import { StatsComponent } from '../components/StatsComponent'
import { Task, PomodoroSettings, PomodoroStats, TimerState } from '../models/PomodoroData'
import { TimerUtils } from '../utils/TimerUtils'
import { SoundUtils } from '../utils/SoundUtils'
import { preferences } from '@kit.ArkData'

@Component
export struct TimerPage {
  @State settings: PomodoroSettings = {
    workDuration: 25,
    breakDuration: 5,
    longBreakDuration: 15,
    longBreakInterval: 4
  }

  @State timerState: TimerState = {
    isRunning: false,
    isPaused: false,
    currentPhase: 'work',
    timeRemaining: 25 * 60,
    completedPomodoros: 0
  }

  @State stats: PomodoroStats = {
    completedPomodoros: 0,
    totalWorkTime: 0,
    date: TimerUtils.getTodayDate()
  }

  private timerId: number = -1
  private preferences: preferences.Preferences | null = null

  async aboutToAppear(): Promise<void> {
    await this.loadData()
  }

  aboutToDisappear(): void {
    this.stopTimer()
    this.saveData()
  }

  build() {
    Column() {
      // 标题
      Text('番茄钟')
        .fontSize(28)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 20 })

      // 计时器组件
      TimerComponent({
        timeRemaining: this.timerState.timeRemaining,
        totalTime: this.getCurrentPhaseTotalTime(),
        currentPhase: this.timerState.currentPhase
      })

      // 控制按钮
      ControlButtonsComponent({
        isRunning: this.timerState.isRunning,
        isPaused: this.timerState.isPaused,
        onStart: (): void => this.startTimer(),
        onPause: (): void => this.pauseTimer(),
        onResume: (): void => this.resumeTimer(),
        onReset: (): void => this.resetTimer()
      })
        .margin({ top: 20 })

      // 统计组件
      StatsComponent({ stats: this.stats })
        .margin({ top: 20 })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }

  // 开始计时
  private startTimer(): void {
    if (this.timerState.isRunning && !this.timerState.isPaused) return
    this.stopTimer()
    this.timerState.isRunning = true
    this.timerState.isPaused = false

    this.timerId = setInterval((): void => {
      if (this.timerState.timeRemaining > 0) {
        this.timerState.timeRemaining--
      } else {
        this.onTimerComplete()
      }
    }, 1000)
  }

  // 暂停计时
  private pauseTimer(): void {
    this.timerState.isRunning = false
    this.timerState.isPaused = true
    clearInterval(this.timerId)
  }

  // 继续计时
  private resumeTimer(): void {
    this.timerState.isPaused = false
    this.startTimer()
  }

  // 重置计时
  private resetTimer(): void {
    this.stopTimer()
    this.timerState = {
      isRunning: false,
      isPaused: false,
      currentPhase: 'work',
      timeRemaining: this.settings.workDuration * 60,
      completedPomodoros: 0
    }
  }

  // 停止定时器
  private stopTimer(): void {
    if (this.timerId !== -1) {
      clearInterval(this.timerId)
      this.timerId = -1
    }
  }

  // 计时完成处理
  private async onTimerComplete(): Promise<void> {
    this.stopTimer()
    await SoundUtils.playNotificationSound()

    if (this.timerState.currentPhase === 'work') {
      this.timerState.completedPomodoros++
      this.stats.completedPomodoros++
      this.stats.totalWorkTime += this.settings.workDuration

      if (this.timerState.completedPomodoros % this.settings.longBreakInterval === 0) {
        this.timerState.currentPhase = 'longBreak'
        this.timerState.timeRemaining = this.settings.longBreakDuration * 60
      } else {
        this.timerState.currentPhase = 'break'
        this.timerState.timeRemaining = this.settings.breakDuration * 60
      }
    } else {
      this.timerState.currentPhase = 'work'
      this.timerState.timeRemaining = this.settings.workDuration * 60
    }

    this.timerState.isRunning = false
    this.saveData()
  }

  private getCurrentPhaseTotalTime(): number {
    switch (this.timerState.currentPhase) {
      case 'work':
        return this.settings.workDuration * 60
      case 'break':
        return this.settings.breakDuration * 60
      case 'longBreak':
        return this.settings.longBreakDuration * 60
      default:
        return this.settings.workDuration * 60
    }
  }

  private async loadData(): Promise<void> {
    try {
      const context = getContext(this)
      this.preferences = await preferences.getPreferences(context, 'pomodoro_data')

      try {
        const settingsStr = await this.preferences.get('settings', JSON.stringify(this.settings))
        this.settings = JSON.parse(settingsStr as string)
      } catch (e) {
        console.error('解析设置失败:', e)
      }

      try {
        const statsStr = await this.preferences.get('stats', JSON.stringify(this.stats))
        const savedStats: PomodoroStats = JSON.parse(statsStr as string) as PomodoroStats
        if (savedStats.date === TimerUtils.getTodayDate()) {
          this.stats = savedStats
        }
      } catch (e) {
        console.error('解析统计失败:', e)
      }

      this.timerState.timeRemaining = this.settings.workDuration * 60
    } catch (error) {
      console.error('加载数据失败:', error)
    }
  }

  private async saveData(): Promise<void> {
    try {
      if (!this.preferences) {
        const context = getContext(this)
        this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      }
      await this.preferences.put('settings', JSON.stringify(this.settings))
      await this.preferences.put('stats', JSON.stringify(this.stats))
      await this.preferences.flush()
    } catch (error) {
      console.error('保存数据失败:', error)
    }
  }
}
