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
      // 添加任务输入框
      Row() {
        TextInput({ placeholder: '添加新任务...', text: this.newTaskName })
          .layoutWeight(1)
          .height(44)
          .backgroundColor('#F5F5F5')
          .borderRadius(10)
          .padding({ left: 12 })
          .onChange((value: string) => {
            this.newTaskName = value
          })

        Button('添加')
          .type(ButtonType.Normal)
          .borderRadius(10)
          .backgroundColor('#FF6B6B')
          .fontColor('#FFFFFF')
          .width(64)
          .height(44)
          .margin({ left: 8 })
          .onClick(() => {
            if (this.newTaskName.trim()) {
              this.onAddTask(this.newTaskName.trim())
              this.newTaskName = ''
            }
          })
      }
      .margin({ bottom: 12 })

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
                .width(22)
                .height(22)

              // 任务名称
              Text(task.name)
                .fontSize(16)
                .fontColor(task.completed ? '#BBBBBB' : '#333333')
                .decoration({ type: task.completed ? TextDecorationType.LineThrough : TextDecorationType.None })
                .margin({ left: 12 })
                .layoutWeight(1)

              // 删除按钮
              Button() {
                SymbolGlyph($r('sys.symbol.trash'))
                  .fontSize(16)
                  .fontColor(['#CCCCCC'])
              }
                .type(ButtonType.Normal)
                .backgroundColor(Color.Transparent)
                .width(36)
                .height(36)
                .onClick(() => {
                  this.onDeleteTask(task.id)
                })
            }
            .width('100%')
            .height(52)
            .padding({ left: 4, right: 4 })
          }
        }, (task: Task) => task.id)
      }
      .layoutWeight(1)
    }
    .width('100%')
  }
}
