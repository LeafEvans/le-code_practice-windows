import { TimerComponent } from '../components/TimerComponent'
import { ControlButtonsComponent } from '../components/ControlButtonsComponent'
import { TaskListComponent } from '../components/TaskListComponent'
import { StatsComponent } from '../components/StatsComponent'
import { Task, PomodoroSettings, PomodoroStats, TimerState } from '../models/PomodoroData'
import { TimerUtils } from '../utils/TimerUtils'
import { SoundUtils } from '../utils/SoundUtils'
import { preferences } from '@kit.ArkData'
import { router } from '@kit.ArkUI'

@Entry
@Component
struct Index {
  // 设置
  @State settings: PomodoroSettings = {
    workDuration: 25,
    breakDuration: 5,
    longBreakDuration: 15,
    longBreakInterval: 4
  }

  // 计时器状态
  @State timerState: TimerState = {
    isRunning: false,
    isPaused: false,
    currentPhase: 'work',
    timeRemaining: 25 * 60,
    completedPomodoros: 0
  }

  // 任务列表
  @State tasks: Task[] = []

  // 统计数据
  @State stats: PomodoroStats = {
    completedPomodoros: 0,
    totalWorkTime: 0,
    date: TimerUtils.getTodayDate()
  }

  // 定时器ID
  private timerId: number = -1

  // 首选项实例
  private preferences: preferences.Preferences | null = null

  async aboutToAppear() {
    await this.loadData()
    this.startTimer()
  }

  aboutToDisappear() {
    this.stopTimer()
    this.saveData()
  }

  build() {
    Column() {
      // 标题栏
      Row() {
        Text('番茄钟')
          .fontSize(28)
          .fontWeight(FontWeight.Bold)

        Button('设置')
          .fontSize(14)
          .height(32)
          .margin({ left: 'auto' })
          .onClick(() => {
            router.pushUrl({ url: 'pages/Settings' })
          })
      }
      .width('100%')
      .padding({ left: 16, right: 16 })
      .margin({ top: 20, bottom: 20 })

      // 计时器组件
      TimerComponent({
        timeRemaining: this.timerState.timeRemaining,
        totalTime: this.getCurrentPhaseTotalTime(),
        currentPhase: this.timerState.currentPhase,
        isRunning: this.timerState.isRunning
      })

      // 控制按钮
      ControlButtonsComponent({
        isRunning: this.timerState.isRunning,
        isPaused: this.timerState.isPaused,
        onStart: () => this.startTimer(),
        onPause: () => this.pauseTimer(),
        onResume: () => this.resumeTimer(),
        onReset: () => this.resetTimer()
      })
        .margin({ top: 20 })

      // 统计组件
      StatsComponent({ stats: this.stats })
        .margin({ top: 20 })

      // 任务列表
      TaskListComponent({
        tasks: this.tasks,
        onAddTask: (name: string) => this.addTask(name),
        onToggleTask: (id: string) => this.toggleTask(id),
        onDeleteTask: (id: string) => this.deleteTask(id)
      })
        .margin({ top: 20 })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }

  // 开始计时
  private startTimer() {
    // 防止重复启动：如果正在运行且未暂停，直接返回
    if (this.timerState.isRunning && !this.timerState.isPaused) return

    // 确保清除已有的定时器，防止重复间隔
    this.stopTimer()

    this.timerState.isRunning = true
    this.timerState.isPaused = false

    this.timerId = setInterval(() => {
      if (this.timerState.timeRemaining > 0) {
        this.timerState.timeRemaining--
      } else {
        // 时间到
        this.onTimerComplete()
      }
    }, 1000)
  }

  // 暂停计时
  private pauseTimer() {
    this.timerState.isRunning = false
    this.timerState.isPaused = true
    clearInterval(this.timerId)
  }

  // 继续计时
  private resumeTimer() {
    this.timerState.isPaused = false
    this.startTimer()
  }

  // 重置计时
  private resetTimer() {
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
  private stopTimer() {
    if (this.timerId !== -1) {
      clearInterval(this.timerId)
      this.timerId = -1
    }
  }

  // 计时完成处理
  private async onTimerComplete() {
    this.stopTimer()

    // 播放提示音
    await SoundUtils.playNotificationSound()

    if (this.timerState.currentPhase === 'work') {
      // 工作阶段完成
      this.timerState.completedPomodoros++
      this.stats.completedPomodoros++
      this.stats.totalWorkTime += this.settings.workDuration

      // 判断是否需要长休息
      if (this.timerState.completedPomodoros % this.settings.longBreakInterval === 0) {
        this.timerState.currentPhase = 'longBreak'
        this.timerState.timeRemaining = this.settings.longBreakDuration * 60
      } else {
        this.timerState.currentPhase = 'break'
        this.timerState.timeRemaining = this.settings.breakDuration * 60
      }
    } else {
      // 休息阶段完成
      this.timerState.currentPhase = 'work'
      this.timerState.timeRemaining = this.settings.workDuration * 60
    }

    this.timerState.isRunning = false
    this.saveData()
  }

  // 获取当前阶段总时间
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

  // 添加任务
  private addTask(name: string) {
    const newTask: Task = {
      id: `${Date.now()}-${Math.random().toString(36).substr(2, 9)}`,
      name: name,
      completed: false,
      createdAt: Date.now()
    }
    this.tasks.push(newTask)
    this.saveData()
  }

  // 切换任务状态
  private toggleTask(id: string) {
    const index = this.tasks.findIndex((task: Task) => task.id === id)
    if (index !== -1) {
      this.tasks[index].completed = !this.tasks[index].completed
      this.saveData()
    }
  }

  // 删除任务
  private deleteTask(id: string) {
    this.tasks = this.tasks.filter((task: Task) => task.id !== id)
    this.saveData()
  }

  // 加载数据
  private async loadData() {
    try {
      this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      
      // 加载设置
      try {
        const settingsStr = await this.preferences.get('settings', JSON.stringify(this.settings))
        this.settings = JSON.parse(settingsStr as string)
      } catch (e) {
        console.error('解析设置数据失败，使用默认值:', e)
      }

      // 加载任务
      try {
        const tasksStr = await this.preferences.get('tasks', JSON.stringify(this.tasks))
        this.tasks = JSON.parse(tasksStr as string)
      } catch (e) {
        console.error('解析任务数据失败，使用空列表:', e)
      }

      // 加载统计
      try {
        const statsStr = await this.preferences.get('stats', JSON.stringify(this.stats))
        const savedStats = JSON.parse(statsStr as string)
        
        // 检查是否是今天的数据
        if (savedStats.date === TimerUtils.getTodayDate()) {
          this.stats = savedStats
        }
      } catch (e) {
        console.error('解析统计数据失败，使用默认值:', e)
      }

      // 重置计时器状态
      this.timerState.timeRemaining = this.settings.workDuration * 60
    } catch (error) {
      console.error('加载数据失败:', error)
    }
  }

  // 保存数据
  private async saveData() {
    try {
      if (!this.preferences) {
        this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      }

      await this.preferences.put('settings', JSON.stringify(this.settings))
      await this.preferences.put('tasks', JSON.stringify(this.tasks))
      await this.preferences.put('stats', JSON.stringify(this.stats))
      await this.preferences.flush()
    } catch (error) {
      console.error('保存数据失败:', error)
    }
  }
}
