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
