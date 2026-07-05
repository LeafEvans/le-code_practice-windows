import { TimerPage } from './TimerPage'
import { TasksPage } from './TasksPage'
import { SettingsPage } from './SettingsPage'
import { window } from '@kit.ArkUI'

@Entry
@Component
struct Index {
  @State currentIndex: number = 0
  @State bottomInset: number = 0

  aboutToAppear(): void {
    // 获取底部安全区高度（手势导航条区域）
    const context = getContext(this) as UIAbilityContext
    if (context && context.windowStage) {
      context.windowStage.getMainWindow().then((win: window.Window) => {
        const avoidArea = win.getWindowAvoidArea(window.AvoidAreaType.TYPE_SYSTEM_GESTURE)
        this.bottomInset = avoidArea.bottomRect.height
      })
    }
  }

  build() {
    Tabs({ barPosition: BarPosition.End, index: this.currentIndex }) {
      TabContent() {
        TimerPage()
      }
      .tabBar(this.buildTabBar('计时器', $r('sys.symbol.clock'), 0))

      TabContent() {
        TasksPage()
      }
      .tabBar(this.buildTabBar('任务', $r('sys.symbol.checkmark'), 1))

      TabContent() {
        SettingsPage()
      }
      .tabBar(this.buildTabBar('设置', $r('sys.symbol.gearshape'), 2))
    }
    .barWidth('100%')
    .barHeight(64)
    .barOverlap(true)
    .barBackgroundColor('#E8FFFFFF')
    .barBackgroundBlurStyle(BlurStyle.REGULAR)
    .padding({ bottom: this.bottomInset })
    .onChange((index: number) => {
      this.currentIndex = index
    })
    .expandSafeArea([SafeAreaType.SYSTEM, SafeAreaType.INSET], [SafeAreaEdge.BOTTOM])
  }

  @Builder
  buildTabBar(title: string, icon: Resource, index: number) {
    Column() {
      // 选中指示器
      if (this.currentIndex === index) {
        Column()
          .width(40)
          .height(3)
          .borderRadius(2)
          .backgroundColor('#FF6B6B')
          .margin({ bottom: 6 })
      } else {
        Column()
          .width(40)
          .height(3)
          .margin({ bottom: 6 })
      }

      SymbolGlyph(icon)
        .fontSize(24)
        .fontColor([this.currentIndex === index ? '#FF6B6B' : '#999999'])

      Text(title)
        .fontSize(12)
        .fontColor(this.currentIndex === index ? '#FF6B6B' : '#999999')
        .margin({ top: 4 })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}
