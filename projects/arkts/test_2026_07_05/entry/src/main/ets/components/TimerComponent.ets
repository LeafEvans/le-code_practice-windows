import { TimerUtils } from '../utils/TimerUtils'

@Component
export struct TimerComponent {
  @Prop timeRemaining: number = 0
  @Prop totalTime: number = 0
  @Prop currentPhase: 'work' | 'break' | 'longBreak' = 'work'

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
          value: this.totalTime > 0
            ? TimerUtils.getProgressPercentage(this.totalTime, this.timeRemaining)
            : 0,
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
