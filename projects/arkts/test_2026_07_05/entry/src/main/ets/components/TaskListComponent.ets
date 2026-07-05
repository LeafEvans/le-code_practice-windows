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
