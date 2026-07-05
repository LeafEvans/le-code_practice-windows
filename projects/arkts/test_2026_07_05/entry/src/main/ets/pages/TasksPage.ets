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
    Scroll() {
      Column() {
        // 标题区
        Row() {
          Column() {
            Text('我的任务')
              .fontSize(28)
              .fontWeight(FontWeight.Bold)
              .fontColor('#1A1A1A')

            Text(`${this.tasks.filter((t: Task) => !t.completed).length}项未完成`)
              .fontSize(14)
              .fontColor('#999999')
              .margin({ top: 4 })
          }
          .alignItems(HorizontalAlign.Start)
        }
        .width('100%')
        .padding({ top: 20 })

        // 任务数量统计
        Row() {
          // 全部
          Column() {
            Text(this.tasks.length.toString())
              .fontSize(24)
              .fontWeight(FontWeight.Bold)
              .fontColor('#FF6B6B')
            Text('全部')
              .fontSize(12)
              .fontColor('#999999')
              .margin({ top: 2 })
          }
          .layoutWeight(1)
          .alignItems(HorizontalAlign.Center)

          // 已完成
          Column() {
            Text(this.tasks.filter((t: Task) => t.completed).length.toString())
              .fontSize(24)
              .fontWeight(FontWeight.Bold)
              .fontColor('#4ECDC4')
            Text('已完成')
              .fontSize(12)
              .fontColor('#999999')
              .margin({ top: 2 })
          }
          .layoutWeight(1)
          .alignItems(HorizontalAlign.Center)

          // 未完成
          Column() {
            Text(this.tasks.filter((t: Task) => !t.completed).length.toString())
              .fontSize(24)
              .fontWeight(FontWeight.Bold)
              .fontColor('#FFA726')
            Text('未完成')
              .fontSize(12)
              .fontColor('#999999')
              .margin({ top: 2 })
          }
          .layoutWeight(1)
          .alignItems(HorizontalAlign.Center)
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#FFFFFF')
        .borderRadius(20)
        .shadow({
          radius: 20,
          color: 'rgba(0, 0, 0, 0.06)',
          offsetX: 0,
          offsetY: 4
        })
        .margin({ top: 16 })

        // 任务列表卡片
        Column() {
          TaskListComponent({
            tasks: this.tasks,
            onAddTask: (name: string): void => this.addTask(name),
            onToggleTask: (id: string): void => this.toggleTask(id),
            onDeleteTask: (id: string): void => this.deleteTask(id)
          })
        }
        .width('100%')
        .backgroundColor('#FFFFFF')
        .borderRadius(20)
        .shadow({
          radius: 20,
          color: 'rgba(0, 0, 0, 0.06)',
          offsetX: 0,
          offsetY: 4
        })
        .margin({ top: 16 })

        if (this.tasks.length === 0) {
          // 空态占位
          Column() {
            Text('还没有任务')
              .fontSize(16)
              .fontColor('#CCCCCC')
            Text('在上方输入框中添加你的第一个番茄任务')
              .fontSize(14)
              .fontColor('#DDDDDD')
              .margin({ top: 8 })
          }
          .width('100%')
          .height(120)
          .justifyContent(FlexAlign.Center)
          .alignItems(HorizontalAlign.Center)
          .margin({ top: 40 })
        }
      }
      .width('100%')
      .padding({ left: 16, right: 16, bottom: 96 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
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
