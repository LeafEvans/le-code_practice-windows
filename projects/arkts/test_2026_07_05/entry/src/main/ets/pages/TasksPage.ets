import { Task } from '../models/PomodoroData'
import { TaskListComponent } from '../components/TaskListComponent'
import { preferences } from '@kit.ArkData'

@Component
export struct TasksPage {
  @State tasks: Task[] = []
  private preferences: preferences.Preferences | null = null

  aboutToAppear(): void {
    this.loadTasks()
  }

  build() {
    Column() {
      // 标题
      Text('我的任务')
        .fontSize(28)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 20 })

      // 任务列表组件
      TaskListComponent({
        tasks: this.tasks,
        onAddTask: (name: string): void => this.addTask(name),
        onToggleTask: (id: string): void => this.toggleTask(id),
        onDeleteTask: (id: string): void => this.deleteTask(id)
      })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }

  private addTask(name: string): void {
    const newTask: Task = {
      id: `${Date.now()}-${Math.random().toString(36).substr(2, 9)}`,
      name: name,
      completed: false,
      createdAt: Date.now()
    }
    this.tasks.push(newTask)
    this.saveTasks()
  }

  private toggleTask(id: string): void {
    const index = this.tasks.findIndex((task: Task) => task.id === id)
    if (index !== -1) {
      this.tasks[index].completed = !this.tasks[index].completed
      this.saveTasks()
    }
  }

  private deleteTask(id: string): void {
    this.tasks = this.tasks.filter((task: Task) => task.id !== id)
    this.saveTasks()
  }

  private async loadTasks(): Promise<void> {
    try {
      const context = getContext(this)
      this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      try {
        const tasksStr = await this.preferences.get('tasks', JSON.stringify(this.tasks))
        this.tasks = JSON.parse(tasksStr as string)
      } catch (e) {
        console.error('解析任务失败:', e)
      }
    } catch (error) {
      console.error('加载任务失败:', error)
    }
  }

  private async saveTasks(): Promise<void> {
    try {
      if (!this.preferences) {
        const context = getContext(this)
        this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      }
      await this.preferences.put('tasks', JSON.stringify(this.tasks))
      await this.preferences.flush()
    } catch (error) {
      console.error('保存任务失败:', error)
    }
  }
}
