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
