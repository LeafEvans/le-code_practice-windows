import { media } from '@kit.MediaKit'
import { vibrator } from '@kit.SensorKit'

export class SoundUtils {
  private static player: media.AVPlayer | null = null

  static async playNotificationSound(): Promise<void> {
    try {
      // 使用振动作为通知反馈
      await vibrator.startVibration({
        type: 'time',
        duration: 500
      })
      console.log('振动提示已触发')
    } catch (error) {
      console.error('播放声音失败，尝试备用方案:', error)
      // 备用方案：短振动
      try {
        await vibrator.startVibration({
          type: 'time',
          duration: 200
        })
      } catch (e) {
        console.error('振动也失败:', e)
      }
    }
  }

  static async release(): Promise<void> {
    if (this.player) {
      await this.player.release()
      this.player = null
    }
  }
}
