import { PomodoroSettings } from '../models/PomodoroData'
import { preferences } from '@kit.ArkData'
import { router } from '@kit.ArkUI'

@Entry
@Component
struct Settings {
  @State settings: PomodoroSettings = {
    workDuration: 25,
    breakDuration: 5,
    longBreakDuration: 15,
    longBreakInterval: 4
  }

  private preferences: preferences.Preferences | null = null

  aboutToAppear(): void {
    this.loadSettings()
  }

  build() {
    Column() {
      // 标题
      Text('设置')
        .fontSize(28)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 30 })

      // 工作时长设置
      this.buildSettingItem(
        '工作时长',
        `${this.settings.workDuration}分钟`,
        (): void => {
          this.settings.workDuration = Math.max(1, Math.min(60, this.settings.workDuration - 5))
          this.saveSettings()
        },
        (): void => {
          this.settings.workDuration = Math.max(1, Math.min(60, this.settings.workDuration + 5))
          this.saveSettings()
        }
      )

      // 短休息时长设置
      this.buildSettingItem(
        '短休息时长',
        `${this.settings.breakDuration}分钟`,
        (): void => {
          this.settings.breakDuration = Math.max(1, Math.min(30, this.settings.breakDuration - 1))
          this.saveSettings()
        },
        (): void => {
          this.settings.breakDuration = Math.max(1, Math.min(30, this.settings.breakDuration + 1))
          this.saveSettings()
        }
      )

      // 长休息时长设置
      this.buildSettingItem(
        '长休息时长',
        `${this.settings.longBreakDuration}分钟`,
        (): void => {
          this.settings.longBreakDuration = Math.max(1, Math.min(60, this.settings.longBreakDuration - 5))
          this.saveSettings()
        },
        (): void => {
          this.settings.longBreakDuration = Math.max(1, Math.min(60, this.settings.longBreakDuration + 5))
          this.saveSettings()
        }
      )

      // 长休息间隔设置
      this.buildSettingItem(
        '长休息间隔',
        `每${this.settings.longBreakInterval}个番茄`,
        (): void => {
          this.settings.longBreakInterval = Math.max(1, Math.min(10, this.settings.longBreakInterval - 1))
          this.saveSettings()
        },
        (): void => {
          this.settings.longBreakInterval = Math.max(1, Math.min(10, this.settings.longBreakInterval + 1))
          this.saveSettings()
        }
      )

      // 返回按钮
      Button('返回')
        .type(ButtonType.Normal)
        .borderRadius(8)
        .backgroundColor('#FF6B6B')
        .fontColor('#FFFFFF')
        .width(120)
        .height(40)
        .margin({ top: 40 })
        .onClick((): void => {
          router.back()
        })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }

  // 构建设置项
  @Builder
  buildSettingItem(title: string, value: string, onDecrease: () => void, onIncrease: () => void) {
    Column() {
      Text(title)
        .fontSize(18)
        .fontColor('#333333')
        .margin({ bottom: 8 })

      Row() {
        Button('-')
          .type(ButtonType.Normal)
          .borderRadius(4)
          .backgroundColor('#E0E0E0')
          .fontColor('#666666')
          .width(40)
          .height(40)
          .onClick(onDecrease)

        Text(value)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ left: 20, right: 20 })
          .width(100)
          .textAlign(TextAlign.Center)

        Button('+')
          .type(ButtonType.Normal)
          .borderRadius(4)
          .backgroundColor('#E0E0E0')
          .fontColor('#666666')
          .width(40)
          .height(40)
          .onClick(onIncrease)
      }
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(16)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .margin({ bottom: 16 })
  }

  // 加载设置
  private async loadSettings(): Promise<void> {
    try {
      const context = getContext(this)
      this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      const settingsStr = await this.preferences.get('settings', JSON.stringify(this.settings))
      this.settings = JSON.parse(settingsStr as string)
    } catch (error) {
      console.error('加载设置失败:', error)
    }
  }

  // 保存设置
  private async saveSettings(): Promise<void> {
    try {
      if (!this.preferences) {
        const context = getContext(this)
        this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      }
      await this.preferences.put('settings', JSON.stringify(this.settings))
      await this.preferences.flush()
    } catch (error) {
      console.error('保存设置失败:', error)
    }
  }
}
