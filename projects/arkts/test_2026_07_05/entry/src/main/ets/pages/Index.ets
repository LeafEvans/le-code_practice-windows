import { TimerPage } from './TimerPage'
import { TasksPage } from './TasksPage'
import { SettingsPage } from './SettingsPage'

@Entry
@Component
struct Index {
  @State currentIndex: number = 0

  build() {
    Tabs({ barPosition: BarPosition.End, index: this.currentIndex }) {
      // 计时器页面
      TabContent() {
        TimerPage()
      }
      .tabBar(this.buildTabBar('计时器', $r('sys.symbol.timer'), 0))

      // 任务列表页面
      TabContent() {
        TasksPage()
      }
      .tabBar(this.buildTabBar('任务', $r('sys.symbol.checklist'), 1))

      // 设置页面
      TabContent() {
        SettingsPage()
      }
      .tabBar(this.buildTabBar('设置', $r('sys.symbol.gearshape'), 2))
    }
    .barWidth('100%')
    .barHeight(56)
    .onChange((index: number) => {
      this.currentIndex = index
    })
  }

  @Builder
  buildTabBar(title: string, icon: Resource, index: number) {
    Column() {
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
