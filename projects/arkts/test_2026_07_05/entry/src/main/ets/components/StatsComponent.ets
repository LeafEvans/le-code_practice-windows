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

      // 统计内容
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
            .margin({ top: 4 })
        }
        .layoutWeight(1)
        .alignItems(HorizontalAlign.Center)

        // 分割线
        Divider()
          .width(1)
          .height(40)
          .color('#E8E8E8')

        // 总工作时间
        Column() {
          Text(`${this.stats.totalWorkTime}分钟`)
            .fontSize(36)
            .fontWeight(FontWeight.Bold)
            .fontColor('#4ECDC4')
          Text('工作时间')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ top: 4 })
        }
        .layoutWeight(1)
        .alignItems(HorizontalAlign.Center)
      }
      .width('100%')
      .height(80)
      .margin({ top: 16 })
    }
    .width('100%')
  }
}
