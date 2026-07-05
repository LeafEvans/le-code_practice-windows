import { media } from '@kit.MediaKit'

export class SoundUtils {
  private static player: media.AVPlayer | null = null

  static async playNotificationSound(): Promise<void> {
    try {
      // 使用系统提示音
      // 实际实现需要添加音频资源文件
      console.log('播放提示音')
    } catch (error) {
      console.error('播放声音失败:', error)
    }
  }

  static async release(): Promise<void> {
    if (this.player) {
      await this.player.release()
      this.player = null
    }
  }
}
