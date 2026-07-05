import { PomodoroSettings } from '../models/PomodoroData'
import { preferences } from '@kit.ArkData'

@Component
export struct SettingsPage {
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
    Scroll() {
      Column() {
        // 标题区
        Row() {
          Column() {
            Text('设置')
              .fontSize(28)
              .fontWeight(FontWeight.Bold)
              .fontColor('#1A1A1A')

            Text('自定义你的番茄钟参数')
              .fontSize(14)
              .fontColor('#999999')
              .margin({ top: 4 })
          }
          .alignItems(HorizontalAlign.Start)
        }
        .width('100%')
        .padding({ top: 20 })

        // 时间设置区
        Column() {
          Text('时间设置')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .fontColor('#333333')
            .margin({ bottom: 16 })

          this.buildSettingItem(
            '工作时长',
            `${this.settings.workDuration}`,
            '分钟',
            (): void => {
              this.settings.workDuration = Math.max(1, Math.min(60, this.settings.workDuration - 5))
              this.saveSettings()
            },
            (): void => {
              this.settings.workDuration = Math.max(1, Math.min(60, this.settings.workDuration + 5))
              this.saveSettings()
            }
          )

          this.buildSettingItem(
            '短休息时长',
            `${this.settings.breakDuration}`,
            '分钟',
            (): void => {
              this.settings.breakDuration = Math.max(1, Math.min(30, this.settings.breakDuration - 1))
              this.saveSettings()
            },
            (): void => {
              this.settings.breakDuration = Math.max(1, Math.min(30, this.settings.breakDuration + 1))
              this.saveSettings()
            }
          )

          this.buildSettingItem(
            '长休息时长',
            `${this.settings.longBreakDuration}`,
            '分钟',
            (): void => {
              this.settings.longBreakDuration = Math.max(1, Math.min(60, this.settings.longBreakDuration - 5))
              this.saveSettings()
            },
            (): void => {
              this.settings.longBreakDuration = Math.max(1, Math.min(60, this.settings.longBreakDuration + 5))
              this.saveSettings()
            }
          )

          this.buildSettingItem(
            '长休息间隔',
            `${this.settings.longBreakInterval}`,
            '个番茄',
            (): void => {
              this.settings.longBreakInterval = Math.max(1, Math.min(10, this.settings.longBreakInterval - 1))
              this.saveSettings()
            },
            (): void => {
              this.settings.longBreakInterval = Math.max(1, Math.min(10, this.settings.longBreakInterval + 1))
              this.saveSettings()
            }
          )
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

        // 关于
        Column() {
          Text('关于')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .fontColor('#333333')
            .margin({ bottom: 16 })

          Row() {
            Text('版本')
              .fontSize(16)
              .fontColor('#666666')
            Text('1.0.0')
              .fontSize(16)
              .fontColor('#999999')
              .margin({ left: 'auto' })
          }
          .width('100%')
          .padding({ top: 8, bottom: 8 })

          Row() {
            Text('开发平台')
              .fontSize(16)
              .fontColor('#666666')
            Text('HarmonyOS')
              .fontSize(16)
              .fontColor('#999999')
              .margin({ left: 'auto' })
          }
          .width('100%')
          .padding({ top: 8, bottom: 8 })
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
      }
      .width('100%')
      .padding({ left: 16, right: 16, bottom: 96 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  @Builder
  buildSettingItem(title: string, value: string, unit: string, onDecrease: () => void, onIncrease: () => void) {
    Column() {
      Row() {
        Text(title)
          .fontSize(16)
          .fontColor('#333333')

        Text(`${value} ${unit}`)
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .fontColor('#FF6B6B')
          .margin({ left: 'auto' })
      }
      .width('100%')

      Row() {
        Button('-')
          .type(ButtonType.Circle)
          .backgroundColor('#F5F5F5')
          .fontColor('#666666')
          .width(36)
          .height(36)
          .fontSize(18)
          .onClick(onDecrease)

        // 进度条指示器
        Column() {
          Column()
            .width(this.getProgressWidth(title, value))
            .height(6)
            .backgroundColor('#FF6B6B')
            .borderRadius(3)
        }
        .width('100%')
        .height(6)
        .backgroundColor('#F5F5F5')
        .borderRadius(3)
        .margin({ left: 12, right: 12 })
        .layoutWeight(1)

        Button('+')
          .type(ButtonType.Circle)
          .backgroundColor('#F5F5F5')
          .fontColor('#666666')
          .width(36)
          .height(36)
          .fontSize(18)
          .onClick(onIncrease)
      }
      .width('100%')
      .margin({ top: 12 })
    }
    .width('100%')
    .padding({ top: 12, bottom: 12 })
    .borderBottom({
      width: 1,
      color: '#F0F0F0'
    })
  }

  private getProgressWidth(title: string, value: string): string {
    const num = parseInt(value)
    switch (title) {
      case '工作时长': return `${(num / 60) * 100}%`
      case '短休息时长': return `${(num / 30) * 100}%`
      case '长休息时长': return `${(num / 60) * 100}%`
      case '长休息间隔': return `${(num / 10) * 100}%`
      default: return '50%'
    }
  }

  private async loadSettings(): Promise<void> {
    try {
      const context = getContext(this)
      this.preferences = await preferences.getPreferences(context, 'pomodoro_data')
      try {
        const settingsStr = await this.preferences.get('settings', JSON.stringify(this.settings))
        this.settings = JSON.parse(settingsStr as string)
      } catch (e) {
        console.error('解析设置失败:', e)
      }
    } catch (error) {
      console.error('加载设置失败:', error)
    }
  }

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
