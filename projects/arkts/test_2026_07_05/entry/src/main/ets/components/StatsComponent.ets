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
