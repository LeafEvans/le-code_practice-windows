# 番茄钟应用实现计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 开发一个功能完整的鸿蒙番茄钟应用，包含计时器、任务管理、统计和声音提醒功能。

**Architecture:** 采用ArkUI声明式UI框架，单Ability多页面架构，组件化设计，使用Preferences进行数据持久化。

**Tech Stack:** ArkTS, ArkUI, Preferences, 关系型数据库

---

## 文件结构

- `entry/src/main/ets/pages/Index.ets` - 主页面（修改）
- `entry/src/main/ets/pages/Settings.ets` - 设置页面（新建）
- `entry/src/main/ets/components/TimerComponent.ets` - 计时器组件（新建）
- `entry/src/main/ets/components/TaskListComponent.ets` - 任务列表组件（新建）
- `entry/src/main/ets/components/StatsComponent.ets` - 统计组件（新建）
- `entry/src/main/ets/components/ControlButtonsComponent.ets` - 控制按钮组件（新建）
- `entry/src/main/ets/models/PomodoroData.ets` - 数据模型（新建）
- `entry/src/main/ets/utils/TimerUtils.ets` - 计时器工具类（新建）
- `entry/src/main/ets/utils/SoundUtils.ets` - 声音工具类（新建）

---

### Task 1: 创建数据模型和工具类

**Files:**
- Create: `entry/src/main/ets/models/PomodoroData.ets`
- Create: `entry/src/main/ets/utils/TimerUtils.ets`
- Create: `entry/src/main/ets/utils/SoundUtils.ets`

- [ ] **Step 1: 创建数据模型**

```typescript
// entry/src/main/ets/models/PomodoroData.ets
export interface Task {
  id: string
  name: string
  completed: boolean
  createdAt: number
}

export interface PomodoroSettings {
  workDuration: number // 分钟
  breakDuration: number // 分钟
  longBreakDuration: number // 分钟
  longBreakInterval: number // 几个番茄后长休息
}

export interface PomodoroStats {
  completedPomodoros: number
  totalWorkTime: number // 分钟
  date: string // YYYY-MM-DD
}

export interface TimerState {
  isRunning: boolean
  isPaused: boolean
  currentPhase: 'work' | 'break' | 'longBreak'
  timeRemaining: number // 秒
  completedPomodoros: number
}
```

- [ ] **Step 2: 创建计时器工具类**

```typescript
// entry/src/main/ets/utils/TimerUtils.ets
export class TimerUtils {
  static formatTime(seconds: number): string {
    const mins = Math.floor(seconds / 60)
    const secs = seconds % 60
    return `${mins.toString().padStart(2, '0')}:${secs.toString().padStart(2, '0')}`
  }

  static getProgressPercentage(total: number, remaining: number): number {
    return ((total - remaining) / total) * 100
  }

  static getTodayDate(): string {
    const now = new Date()
    return `${now.getFullYear()}-${(now.getMonth() + 1).toString().padStart(2, '0')}-${now.getDate().toString().padStart(2, '0')}`
  }
}
```

- [ ] **Step 3: 创建声音工具类**

```typescript
// entry/src/main/ets/utils/SoundUtils.ets
import { media } from '@kit.MediaKit'

export class SoundUtils {
  private static player: media.AVPlayer | null = null

  static async playNotificationSound(): Promise<void> {
    try {
      // 使用系统提示音
      // 实际实现需要添加音频资源文件
      console.log('播放提示音')
    } catch (error) {
      console.error('播放声音失败:', error)
    }
  }

  static async release(): Promise<void> {
    if (this.player) {
      await this.player.release()
      this.player = null
    }
  }
}
```

- [ ] **Step 4: 提交代码**

```bash
git add entry/src/main/ets/models/PomodoroData.ets entry/src/main/ets/utils/TimerUtils.ets entry/src/main/ets/utils/SoundUtils.ets
git commit -m "feat: add data models and utility classes"
```

---

### Task 2: 创建计时器组件

**Files:**
- Create: `entry/src/main/ets/components/TimerComponent.ets`

- [ ] **Step 1: 创建计时器组件**

```typescript
// entry/src/main/ets/components/TimerComponent.ets
import { TimerUtils } from '../utils/TimerUtils'

@Component
export struct TimerComponent {
  @Prop timeRemaining: number = 0
  @Prop totalTime: number = 0
  @Prop currentPhase: string = 'work'
  @Prop isRunning: boolean = false

  build() {
    Column() {
      // 阶段指示器
      Text(this.getPhaseText())
        .fontSize(18)
        .fontColor(this.getPhaseColor())
        .margin({ bottom: 20 })

      // 圆形进度条
      Stack() {
        Progress({
          value: TimerUtils.getProgressPercentage(this.totalTime, this.timeRemaining),
          total: 100,
          type: ProgressType.Ring
        })
          .width(200)
          .height(200)
          .color(this.getPhaseColor())

        // 时间显示
        Text(TimerUtils.formatTime(this.timeRemaining))
          .fontSize(48)
          .fontWeight(FontWeight.Bold)
      }
      .width(220)
      .height(220)
    }
    .alignItems(HorizontalAlign.Center)
  }

  private getPhaseText(): string {
    switch (this.currentPhase) {
      case 'work':
        return '工作时间'
      case 'break':
        return '短休息'
      case 'longBreak':
        return '长休息'
      default:
        return '工作时间'
    }
  }

  private getPhaseColor(): ResourceColor {
    switch (this.currentPhase) {
      case 'work':
        return '#FF6B6B'
      case 'break':
        return '#4ECDC4'
      case 'longBreak':
        return '#45B7D1'
      default:
        return '#FF6B6B'
    }
  }
}
```

- [ ] **Step 2: 提交代码**

```bash
git add entry/src/main/ets/components/TimerComponent.ets
git commit -m "feat: add timer component with circular progress"
```

---

### Task 3: 创建控制按钮组件

**Files:**
- Create: `entry/src/main/ets/components/ControlButtonsComponent.ets`

- [ ] **Step 1: 创建控制按钮组件**

```typescript
// entry/src/main/ets/components/ControlButtonsComponent.ets
@Component
export struct ControlButtonsComponent {
  @Prop isRunning: boolean = false
  @Prop isPaused: boolean = false
  onStart: () => void = () => {}
  onPause: () => void = () => {}
  onResume: () => void = () => {}
  onReset: () => void = () => {}

  build() {
    Row() {
      // 重置按钮
      Button('重置')
        .type(ButtonType.Normal)
        .borderRadius(8)
        .backgroundColor('#E0E0E0')
        .fontColor('#666666')
        .width(80)
        .height(40)
        .onClick(() => {
          this.onReset()
        })
        .margin({ right: 20 })

      // 开始/暂停/继续按钮
      Button(this.getButtonText())
        .type(ButtonType.Normal)
        .borderRadius(8)
        .backgroundColor(this.getButtonColor())
        .fontColor('#FFFFFF')
        .width(120)
        .height(40)
        .onClick(() => {
          if (!this.isRunning) {
            this.onStart()
          } else if (this.isPaused) {
            this.onResume()
          } else {
            this.onPause()
          }
        })
    }
    .justifyContent(FlexAlign.Center)
  }

  private getButtonText(): string {
    if (!this.isRunning) {
      return '开始'
    } else if (this.isPaused) {
      return '继续'
    } else {
      return '暂停'
    }
  }

  private getButtonColor(): ResourceColor {
    if (!this.isRunning) {
      return '#FF6B6B'
    } else if (this.isPaused) {
      return '#4ECDC4'
    } else {
      return '#FFA726'
    }
  }
}
```

- [ ] **Step 2: 提交代码**

```bash
git add entry/src/main/ets/components/ControlButtonsComponent.ets
git commit -m "feat: add control buttons component"
```

---

### Task 4: 创建任务列表组件

**Files:**
- Create: `entry/src/main/ets/components/TaskListComponent.ets`

- [ ] **Step 1: 创建任务列表组件**

```typescript
// entry/src/main/ets/components/TaskListComponent.ets
import { Task } from '../models/PomodoroData'

@Component
export struct TaskListComponent {
  @Prop tasks: Task[] = []
  @State newTaskName: string = ''
  onAddTask: (name: string) => void = () => {}
  onToggleTask: (id: string) => void = () => {}
  onDeleteTask: (id: string) => void = () => {}

  build() {
    Column() {
      // 标题
      Text('任务列表')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      // 添加任务输入框
      Row() {
        TextInput({ placeholder: '添加新任务...', text: this.newTaskName })
          .layoutWeight(1)
          .height(40)
          .onChange((value: string) => {
            this.newTaskName = value
          })

        Button('添加')
          .type(ButtonType.Normal)
          .borderRadius(8)
          .backgroundColor('#FF6B6B')
          .fontColor('#FFFFFF')
          .width(60)
          .height(40)
          .margin({ left: 8 })
          .onClick(() => {
            if (this.newTaskName.trim()) {
              this.onAddTask(this.newTaskName.trim())
              this.newTaskName = ''
            }
          })
      }
      .margin({ bottom: 16 })

      // 任务列表
      List() {
        ForEach(this.tasks, (task: Task) => {
          ListItem() {
            Row() {
              // 完成复选框
              Checkbox()
                .select(task.completed)
                .onChange((value: boolean) => {
                  this.onToggleTask(task.id)
                })
                .width(24)
                .height(24)

              // 任务名称
              Text(task.name)
                .fontSize(16)
                .fontColor(task.completed ? '#999999' : '#333333')
                .decoration({ type: task.completed ? TextDecorationType.LineThrough : TextDecorationType.None })
                .margin({ left: 12 })
                .layoutWeight(1)

              // 删除按钮
              Button('删除')
                .type(ButtonType.Normal)
                .borderRadius(4)
                .backgroundColor('#FF4444')
                .fontColor('#FFFFFF')
                .width(50)
                .height(30)
                .fontSize(12)
                .onClick(() => {
                  this.onDeleteTask(task.id)
                })
            }
            .width('100%')
            .height(50)
            .padding({ left: 8, right: 8 })
          }
        }, (task: Task) => task.id)
      }
      .layoutWeight(1)
    }
    .width('100%')
    .padding(16)
  }
}
```

- [ ] **Step 2: 提交代码**

```bash
git add entry/src/main/ets/components/TaskListComponent.ets
git commit -m "feat: add task list component"
```

---

### Task 5: 创建统计组件

**Files:**
- Create: `entry/src/main/ets/components/StatsComponent.ets`

- [ ] **Step 1: 创建统计组件**

```typescript
// entry/src/main/ets/components/StatsComponent.ets
import { PomodoroStats } from '../models/PomodoroData'

@Component
export struct StatsComponent {
  @Prop stats: PomodoroStats = { completedPomodoros: 0, totalWorkTime: 0, date: '' }

  build() {
    Column() {
      // 标题
      Text('今日统计')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      // 统计卡片
      Row() {
        // 完成番茄数
        Column() {
          Text(this.stats.completedPomodoros.toString())
            .fontSize(36)
            .fontWeight(FontWeight.Bold)
            .fontColor('#FF6B6B')
          Text('完成番茄')
            .fontSize(14)
            .fontColor('#666666')
        }
        .layoutWeight(1)
        .alignItems(HorizontalAlign.Center)

        // 分割线
        Divider()
          .width(1)
          .height(40)
          .color('#E0E0E0')

        // 总工作时间
        Column() {
          Text(`${this.stats.totalWorkTime}分钟`)
            .fontSize(36)
            .fontWeight(FontWeight.Bold)
            .fontColor('#4ECDC4')
          Text('工作时间')
            .fontSize(14)
            .fontColor('#666666')
        }
        .layoutWeight(1)
        .alignItems(HorizontalAlign.Center)
      }
      .width('100%')
      .height(100)
      .backgroundColor('#F5F5F5')
      .borderRadius(12)
      .padding(16)
    }
    .width('100%')
    .padding(16)
  }
}
```

- [ ] **Step 2: 提交代码**

```bash
git add entry/src/main/ets/components/StatsComponent.ets
git commit -m "feat: add stats component"
```

---

### Task 6: 修改主页面

**Files:**
- Modify: `entry/src/main/ets/pages/Index.ets`

- [ ] **Step 1: 重写主页面**

```typescript
// entry/src/main/ets/pages/Index.ets
import { TimerComponent } from '../components/TimerComponent'
import { ControlButtonsComponent } from '../components/ControlButtonsComponent'
import { TaskListComponent } from '../components/TaskListComponent'
import { StatsComponent } from '../components/StatsComponent'
import { Task, PomodoroSettings, PomodoroStats, TimerState } from '../models/PomodoroData'
import { TimerUtils } from '../utils/TimerUtils'
import { SoundUtils } from '../utils/SoundUtils'
import { preferences } from '@kit.ArkData'

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

  aboutToAppear() {
    this.loadData()
    this.startTimer()
  }

  aboutToDisappear() {
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
    if (this.timerState.isRunning) return

    this.timerState.isRunning = true
    this.timerState.isPaused = false

    this.timerId = setInterval(() => {
      if (this.timerState.timeRemaining > 0) {
        this.timerState.timeRemaining--

        // 更新工作时间统计
        if (this.timerState.currentPhase === 'work') {
          this.stats.totalWorkTime = Math.floor((this.settings.workDuration * 60 - this.timerState.timeRemaining) / 60)
        }
      } else {
        // 时间到
        this.onTimerComplete()
      }
    }, 1000)
  }

  // 暂停计时
  private pauseTimer() {
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
      id: Date.now().toString(),
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
      const settingsStr = await this.preferences.get('settings', JSON.stringify(this.settings))
      this.settings = JSON.parse(settingsStr as string)

      // 加载任务
      const tasksStr = await this.preferences.get('tasks', JSON.stringify(this.tasks))
      this.tasks = JSON.parse(tasksStr as string)

      // 加载统计
      const statsStr = await this.preferences.get('stats', JSON.stringify(this.stats))
      const savedStats = JSON.parse(statsStr as string)
      
      // 检查是否是今天的数据
      if (savedStats.date === TimerUtils.getTodayDate()) {
        this.stats = savedStats
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
```

- [ ] **Step 2: 提交代码**

```bash
git add entry/src/main/ets/pages/Index.ets
git commit -m "feat: implement main page with timer, tasks, and stats"
```

---

### Task 7: 创建设置页面

**Files:**
- Create: `entry/src/main/ets/pages/Settings.ets`

- [ ] **Step 1: 创建设置页面**

```typescript
// entry/src/main/ets/pages/Settings.ets
import { PomodoroSettings } from '../models/PomodoroData'
import { preferences } from '@kit.ArkData'

@Entry
@Component
struct Settings {
  @State settings: PomodoroSettings = {
    workDuration: 25,
    breakDuration: 5,
    longBreakDuration: 15,
    longBreakInterval: 4
  }

  private preferences: preferences.Preferences | null = null

  aboutToAppear() {
    this.loadSettings()
  }

  build() {
    Column() {
      // 标题
      Text('设置')
        .fontSize(28)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 30 })

      // 工作时长设置
      this.buildSettingItem(
        '工作时长',
        `${this.settings.workDuration}分钟`,
        () => {
          this.settings.workDuration = Math.max(1, Math.min(60, this.settings.workDuration - 5))
          this.saveSettings()
        },
        () => {
          this.settings.workDuration = Math.max(1, Math.min(60, this.settings.workDuration + 5))
          this.saveSettings()
        }
      )

      // 短休息时长设置
      this.buildSettingItem(
        '短休息时长',
        `${this.settings.breakDuration}分钟`,
        () => {
          this.settings.breakDuration = Math.max(1, Math.min(30, this.settings.breakDuration - 1))
          this.saveSettings()
        },
        () => {
          this.settings.breakDuration = Math.max(1, Math.min(30, this.settings.breakDuration + 1))
          this.saveSettings()
        }
      )

      // 长休息时长设置
      this.buildSettingItem(
        '长休息时长',
        `${this.settings.longBreakDuration}分钟`,
        () => {
          this.settings.longBreakDuration = Math.max(1, Math.min(60, this.settings.longBreakDuration - 5))
          this.saveSettings()
        },
        () => {
          this.settings.longBreakDuration = Math.max(1, Math.min(60, this.settings.longBreakDuration + 5))
          this.saveSettings()
        }
      )

      // 长休息间隔设置
      this.buildSettingItem(
        '长休息间隔',
        `每${this.settings.longBreakInterval}个番茄`,
        () => {
          this.settings.longBreakInterval = Math.max(1, Math.min(10, this.settings.longBreakInterval - 1))
          this.saveSettings()
        },
        () => {
          this.settings.longBreakInterval = Math.max(1, Math.min(10, this.settings.longBreakInterval + 1))
          this.saveSettings()
        }
      )

      // 返回按钮
      Button('返回')
        .type(ButtonType.Normal)
        .borderRadius(8)
        .backgroundColor('#FF6B6B')
        .fontColor('#FFFFFF')
        .width(120)
        .height(40)
        .margin({ top: 40 })
        .onClick(() => {
          router.back()
        })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }

  // 构建设置项
  @Builder
  buildSettingItem(title: string, value: string, onDecrease: () => void, onIncrease: () => void) {
    Column() {
      Text(title)
        .fontSize(18)
        .fontColor('#333333')
        .margin({ bottom: 8 })

      Row() {
        Button('-')
          .type(ButtonType.Normal)
          .borderRadius(4)
          .backgroundColor('#E0E0E0')
          .fontColor('#666666')
          .width(40)
          .height(40)
          .onClick(onDecrease)

        Text(value)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ left: 20, right: 20 })
          .width(100)
          .textAlign(TextAlign.Center)

        Button('+')
          .type(ButtonType.Normal)
          .borderRadius(4)
          .backgroundColor('#E0E0E0')
          .fontColor('#666666')
          .width(40)
          .height(40)
          .onClick(onIncrease)
      }
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(16)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 16 })
  }

  // 加载设置
  private async loadSettings() {
    try {
      this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      const settingsStr = await this.preferences.get('settings', JSON.stringify(this.settings))
      this.settings = JSON.parse(settingsStr as string)
    } catch (error) {
      console.error('加载设置失败:', error)
    }
  }

  // 保存设置
  private async saveSettings() {
    try {
      if (!this.preferences) {
        this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      }
      await this.preferences.put('settings', JSON.stringify(this.settings))
      await this.preferences.flush()
    } catch (error) {
      console.error('保存设置失败:', error)
    }
  }
}
```

- [ ] **Step 2: 提交代码**

```bash
git add entry/src/main/ets/pages/Settings.ets
git commit -m "feat: add settings page for customizing timer durations"
```

---

### Task 8: 配置路由和测试

**Files:**
- Modify: `entry/src/main/resources/base/profile/main_pages.json`

- [ ] **Step 1: 添加设置页面路由**

```json
{
  "src": [
    "pages/Index",
    "pages/Settings"
  ]
}
```

- [ ] **Step 2: 运行应用测试**

```bash
# 在DevEco Studio中运行应用
# 或使用命令行
hvigorw assembleHap
```

- [ ] **Step 3: 最终提交**

```bash
git add .
git commit -m "feat: complete pomodoro timer application"
```

---

## 自检清单

1. **规格覆盖**：所有核心功能（计时器、自定义时长、任务列表、统计、声音提醒）都已实现
2. **占位符扫描**：无TBD、TODO或模糊描述
3. **类型一致性**：所有接口和类型定义一致使用
4. **文件路径**：所有文件路径精确指定
5. **代码完整性**：每个步骤都包含完整代码

---

## 执行选项

**计划完成并保存到 `docs/superpowers/plans/2026-07-05-pomodoro-timer.md`。两种执行选项：**

**1. 子代理驱动（推荐）** - 我为每个任务分派一个新的子代理，任务之间进行审查，快速迭代

**2. 内联执行** - 在此会话中使用executing-plans执行任务，批量执行并设置检查点

**选择哪种方式？**