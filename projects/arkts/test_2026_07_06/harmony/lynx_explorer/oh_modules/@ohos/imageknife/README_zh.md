# ImageKnife

**专门为OpenHarmony打造的一款图像加载缓存库，致力于更高效、更轻便、更简单。**

## 简介

本项目参考开源库 [Glide](https://github.com/bumptech/glide) 进行OpenHarmony的自研版本：

- 支持自定义内存缓存策略，支持设置内存缓存的大小(默认LRU策略)。
- 支持磁盘二级缓存，对于下载图片会保存一份至磁盘当中。
- 支持自定义实现图片获取/网络下载
- 支持监听网络下载回调进度
- 继承Image的能力，支持option传入border，设置边框，圆角
- 继承Image的能力，支持option传入objectFit设置图片缩放，包括objectFit为auto时根据图片自适应高度
- 支持通过设置transform缩放图片
- 并发请求数量，支持请求排队队列的优先级
- 支持生命周期已销毁的图片，不再发起请求
- 自定义缓存key
- 自定义http网络请求头
- 支持writeCacheStrategy控制缓存的存入策略(只存入内存或文件缓存)
- 支持preLoadCache预加载图片
- 支持onlyRetrieveFromCache仅用缓存加载
- 支持使用一个或多个图片变换，如模糊，高亮等

待实现特性

- 内存降采样优化，节约内存的占用
- 支持自定义图片解码

注意：3.x版本相对2.x版本做了重大的重构，主要体现在：

- 使用Image组件代替Canvas组件渲染
- 重构Dispatch分发逻辑，支持控制并发请求数，支持请求排队队列的优先级
- 支持通过initMemoryCache自定义策略内存缓存策略和大小
- 支持option自定义实现图片获取/网络下载

因此API及能力上，目前有部分差异，主要体现在：

- 不支持drawLifeCycle接口，通过canvas自会图片
- mainScaleType，border等参数，新版本与系统Image保持一致
- gif/webp动图播放与控制(ImageAnimator实现)
- 抗锯齿相关参数

## 下载安装

```
ohpm install @ohos/imageknife

// 如果需要用文件缓存，需要提前初始化文件缓存
await ImageKnife.getInstance().initFileCache(context, 256, 256 * 1024 * 1024)
```

## 使用说明

#### 1.显示本地资源图片

```
ImageKnifeComponent({
  imageKnifeOption: {
    loadSrc: $r("app.media.app_icon"),
    placeholderSrc: $r("app.media.loading"),
    errorholderSrc: $r("app.media.app_icon"),
    objectFit: ImageFit.Auto
  }
}).width(100).height(100)
```

#### 2.显示本地context files下文件

```
ImageKnifeComponent({
  imageKnifeOption: {
    loadSrc: this.localFile,
    placeholderSrc: $r("app.media.loading"),
    errorholderSrc: $r("app.media.app_icon"),
    objectFit: ImageFit.Auto
  }
}).width(100).height(100)
```

#### 3.显示网络图片

```
ImageKnifeComponent({
  imageKnifeOption: {
    loadSrc:"https://www.openharmony.cn/_nuxt/img/logo.dcf95b3.png",
    placeholderSrc: $r("app.media.loading"),
    errorholderSrc: $r("app.media.app_icon"),
    objectFit: ImageFit.Auto
  }
}).width(100).height(100)
```

#### 4.自定义下载图片

```
ImageKnifeComponent({
  imageKnifeOption: {
    loadSrc: "https://file.atomgit.com/uploads/user/1704857786989_8994.jpeg",
    placeholderSrc: $r("app.media.loading"),
    errorholderSrc: $r("app.media.app_icon"),
    objectFit: ImageFit.Auto,
    customGetImage: custom
 }
}).width(100).height(100)

// 自定义实现图片获取方法，如自定义网络下载
@Concurrent
async function custom(context: Context, src: string | PixelMap | Resource): Promise<ArrayBuffer | undefined> {
  console.info("ImageKnife::  custom download：" + src)
  // 举例写死从本地文件读取，也可以自己请求网络图片
  return context.resourceManager.getMediaContentSync($r("app.media.bb").id).buffer as ArrayBuffer
}
```

#### 5.监听网络下载进度

```
ImageKnifeComponent({
  imageKnifeOption: {
    loadSrc:"https://www.openharmony.cn/_nuxt/img/logo.dcf95b3.png",
    progressListener:(progress:number)=>{console.info("ImageKinfe:: call back progress = " + progress)}
  }
}).width(100).height(100)
```

#### 6.支持option传入border，设置边框，圆角

```
ImageKnifeComponent({ imageKnifeOption: 
{
   loadSrc: $r("app.media.rabbit"),
   border: {radius:50}
  }
}).width(100).height(100)
```

#### 7.支持option图片变换

```
ImageKnifeComponent({ imageKnifeOption: 
{
   loadSrc: $r("app.media.rabbit"),
   border: {radius:50},
   transformation: new BlurTransformation(3)
  }
}).width(100).height(100)
```
多种组合变换用法

```
let transformations: collections.Array<PixelMapTransformation> = new collections.Array<PixelMapTransformation>();
transformations.push(new BlurTransformation(5));
transformations.push(new BrightnessTransformation(0.2));
ImageKnifeComponent({
  imageKnifeOption: {
  loadSrc: $r('app.media.pngSample'),
  placeholderSrc: $r("app.media.loading"),
  errorholderSrc: $r("app.media.app_icon"),
  objectFit: ImageFit.Contain,
  border: { radius: { topLeft: 50, bottomRight: 50 } }, // 圆角设置
  transformation: transformations.length > 0 ? new MultiTransTransformation(transformations) : undefined // 图形变换组
}
}).width(300)
  .height(300)
  .rotate({ angle: 90 }) // 旋转90度
  .contrast(12) // 对比度滤波器
```
其它变换相关属性，可叠加实现组合变换效果

圆形裁剪变换示例

```
ImageKnifeComponent({ imageKnifeOption: 
  {
  loadSrc: $r('app.media.pngSample'),
  objectFit: ImageFit.Cover,
  border: { radius: 150 }
}
}).width(300)
  .height(300)
```

圆形裁剪带边框变换示例

```
ImageKnifeComponent({ imageKnifeOption: 
  {
  loadSrc: $r('app.media.pngSample'),
  objectFit: ImageFit.Cover,
  border: { radius: 150, color: Color.Red, width: 5 }
}
}).width(300)
  .height(300)
```

对比度滤波变换示例

```
ImageKnifeComponent({
  imageKnifeOption: {
    loadSrc: $r('app.media.pngSample')
  }
}).width(300)
  .height(300)
  .contrast(12)
```

旋转变换示例

```
ImageKnifeComponent({
  imageKnifeOption:  {
    loadSrc: $r('app.media.pngSample')
  }
}).width(300)
  .height(300)
  .rotate({angle:90})
  .backgroundColor(Color.Pink)
```

#### 8.监听图片加载成功与失败

```
ImageKnifeComponent({ imageKnifeOption: 
{
   loadSrc: $r("app.media.rabbit"),
   onLoadListener:{
    onLoadStart:()=>{
     this.starTime = new Date().getTime()
     console.info("Load start: ");
    },
    onLoadFailed: (err) => {
     console.error("Load Failed Reason: " + err + "  cost " + (new Date().getTime() - this.starTime) + " milliseconds");
    },
    onLoadSuccess: (data, imageData) => {
     console.info("Load Successful: cost " + (new Date().getTime() - this.starTime) + " milliseconds");
     return data;
    },
    onLoadCancel(err){
      console.info(err)
    }
   }
 }
}).width(100).height(100)
```
#### 9.ImageKnifeComponent - syncLoad
设置是否同步加载图片，默认是异步加载。建议加载尺寸较小的Resource图片时将syncLoad设为true，因为耗时较短，在主线程上执行即可
```
ImageKnifeComponent({
        imageKnifeOption:{
          loadSrc:$r("app.media.pngSample"),
          placeholderSrc:$r("app.media.loading")
        },syncLoad:true
      })
```
#### 10.ImageKnifeAnimatorComponent 示例
```
ImageKnifeAnimatorComponent({
        imageKnifeOption: {
          loadSrc:"https://gd-hbimg.huaban.com/e0a25a7cab0d7c2431978726971d61720732728a315ae-57EskW_fw658",
          placeholderSrc:$r('app.media.loading'),
          errorholderSrc:$r('app.media.failed')
        },animatorOption:this.animatorOption
      }).width(300).height(300).backgroundColor(Color.Orange).margin({top:30})
```

#### 11.加载图片回调信息数据 示例
```
ImageKnifeComponent({ imageKnifeOption:  {
                loadSrc: $r('app.media.pngSample'),
                objectFit: ImageFit.Contain,
                onLoadListener: {
                  onLoadStart: (req) => {
                    let startCallBackData = JSON.stringify(req?.imageKnifeData);
                  },
                  onLoadFailed: (res, req) => {
                    let failedBackData = res + ";" + JSON.stringify(req?.imageKnifeData);
                  },
                  onLoadSuccess: (data, imageData, req) => {
                    let successBackData = JSON.stringify(req?.imageKnifeData);
                  },
                  onLoadCancel: (res, req) => {
                    let cancelBackData = res + ";" + JSON.stringify(req?.imageKnifeData);
                  }
                },
                border: { radius: 50 },
                onComplete: (event) => {
                  if (event && event.loadingStatus == 0) {
                    let render_success = JSON.stringify(Date.now())
                  }
                }
              }
}).width(100).height(100)
```
#### 12.图片降采样 示例
```
ImageKnifeComponent({
        imageKnifeOption:{
          loadSrc:$r("app.media.pngSample"),
          placeholderSrc:$r('app.media.loading'),
          errorholderSrc:$r('app.media.failed'),
          downsampleOf: DownsampleStrategy.NONE
        }
      }).width(300).height(300)
```
#### 13.rcp自定义网络请求
```
ImageKnifeComponent({
    imageKnifeOption:{
        loadSrc:"http//xx.xx",
        customGetImage:custom
     }
})
// 自定义下载方法
@Concurrent
async function custom(context: Context, src: string | PixelMap | Resource,headers?: Record<string,Object>): Promise<ArrayBuffer | undefined> {
  return new Promise((resolve,reject)=>{
    if (typeof src == "string") {
      let session = GetSession.session
      let req = new rcp.Request(src,"GET");
      session.fetch(req).then((response)=>{
        if(response.statusCode == 200) {
          let buffer = response.body
          resolve(buffer)
        } else {
          reject("rcp code:"+response.statusCode)
        }
      }).catch((err:BusinessError)=>{
        reject("error rcp src:"+src+",err:"+JSON.stringify(err))
      })
    }
  })
}
```

#### 复用场景
在aboutToRecycle生命周期清空组件内容；通过watch监听触发图片的加载。
## 接口说明
### ImageKnife组件
| 组件名称                        | 入参内容                            | 功能简介   |
|-----------------------------|---------------------------------|--------|
| ImageKnifeComponent         | ImageKnifeOption                | 图片显示组件 |
| ImageKnifeAnimatorComponent | ImageKnifeOption、AnimatorOption | 动图控制组件 |

### AnimatorOption参数列表
| 参数名称       | 入参内容            | 功能简介     |
|------------|-----------------|----------|
| state      | AnimationStatus | 播放状态（可选） |
| iterations | number          | 播放次数（可选） |
| reverse    | boolean         | 播放顺序（可选） |
| onStart    | ()=>void        | 动画开始播放时触发（可选） |
| onFinish    | ()=>void          | 动画播放完成时或者停止播放时触发（可选） |
| onPause    | ()=>void         | 动画暂停播放时触发（可选） |
| onCancel   | ()=>void          | 动画返回最初状态时触发（可选） |
| onRepeat    | ()=>void         | 动画重复播放时触发（可选） |

### ImageKnifeOption参数列表

| 参数名称                  | 入参内容                                                                                                                                                                                                                                                                                            | 功能简介            |
|-----------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------|
| loadSrc               | string、PixelMap、Resource                                                                                                                                                                                                                                                                        | 主图展示            |
| placeholderSrc        | PixelMap、Resource                                                                                                                                                                                                                                                                               | 占位图图展示（可选）      |
| errorholderSrc        | PixelMap、Resource                                                                                                                                                                                                                                                                               | 错误图展示（可选）       |
| objectFit             | ImageFit                                                                                                                                                                                                                                                                                        | 主图填充效果（可选）      |
| placeholderObjectFit  | ImageFit                                                                                                                                                                                                                                                                                        | 占位图填充效果（可选）     |
| errorholderObjectFit  | ImageFit                                                                                                                                                                                                                                                                                        | 错误图填充效果（可选）     |
| writeCacheStrategy    | CacheStrategyType                                                                                                                                                                                                                                                                               | 写入缓存策略(可选)      |
| onlyRetrieveFromCache | boolean                                                                                                                                                                                                                                                                                         | 是否跳过网络和本地请求（可选） |
| customGetImage        | customGetImage?:(context: Context, src: string、PixelMap、Resource ,headers?: Record<string, Object>) => Promise<ArrayBuffer、undefined>                                                                                                                                                           | 自定义下载图片（可选）     |                                                                                                                                                                              | Resource                                      | 错误占位图数据源                    |
| border                | BorderOptions                                                                                                                                                                                                                                                                                   | 边框圆角（可选）        |
| priority              | taskpool.Priority                                                                                                                                                                                                                                                                               | 加载优先级（可选）       | 
| context               | common.UIAbilityContext                                                                                                                                                                                                                                                                         | 上下文（可选）         |
| progressListener      | (progress: number)=>void                                                                                                                                                                                                                                                                        | 进度（可选）          |
| signature             | String                                                                                                                                                                                                                                                                                          | 自定义缓存关键字（可选）    | 
| headerOption          | Array<HeaderOptions>                                                                                                                                                                                                                                                                            | 设置请求头（可选）       |
| transformation        | PixelMapTransformation                                                                                                                                                                                                                                                                          | 图片变换（可选）        |
| drawingColorFilter    | ColorFilter、drawing.ColorFilter                                                                                                                                                                                                                                                                 | 颜色滤镜效果（可选）      |
| onComplete            | (event:EventImage、undefined) => void                                                                                                                                                                                                                                                            | 图片成功回调事件(可选)    |
| onLoadListener        | onLoadStart?: (req?: ImageKnifeRequest) => void,onLoadSuccess?: (data: string \| PixelMap \| undefined, imageData: ImageKnifeData, req?: ImageKnifeRequest) => void,onLoadFailed?: (err: string, req?: ImageKnifeRequest) => void,onLoadCancel?: (res: string, req?: ImageKnifeRequest) => void | 监听图片加载成功与失败     |
| downsampleOf          | DownsampleStrategy                                                                                                                                                                                                                                                                              | 降采样（可选）         |
| httpOption             | HttpRequestOption                                                                                                                                                                                                                                                                               | 网络请求配置（可选）      | 

### 降采样类型
| 类型                     | 相关描述              |
|------------------------|-------------------|
| NONE                   | 不进行降采样            |
| AT_MOST                | 请求尺寸大于实际尺寸不进行放大   |
| FIT_CENTER_MEMORY      | 两边自适应内存优先             |
| FIT_CENTER_QUALITY     | 两边自适应质量优先             |
| CENTER_INSIDE_MEMORY   | 宽高缩放比最大的比例，进行缩放适配内存优先 |
| CENTER_INSIDE_QUALITY | 宽高缩放比最大的比例，进行缩放适配质量优先 |
| AT_LEAST               | 根据宽高的最小的比例，进行适配   |

### ImageKnife接口

| 参数名称              | 入参内容                                                                                                                                  | 功能简介             |
|-------------------|---------------------------------------------------------------------------------------------------------------------------------------|------------------|
| initMemoryCache   | newMemoryCache: IMemoryCache                                                                                                          | 自定义内存缓存策略        |
| initFileCache     | context: Context, size: number, memory: number                                                                                        | 初始化文件缓存数量和大小     |
| reload            | request: ImageKnifeRequest                                                                                                            | 图片重新加载           |
| preLoad           | loadSrc: string I ImageKnifeOption                                                                                                    | 预加载返回图片请求request |
| cancel            | request: ImageKnifeRequest                                                                                                            | 取消图片请求           |
| preLoadCache      | loadSrc: string I ImageKnifeOption                                                                                                    | 预加载并返回文件缓存路径     |
| getCacheImage     | loadSrc: string, cacheType: CacheStrategy = CacheStrategy.Default, signature?: string)                                                | 从内存或文件缓存中获取资源    |
| addHeader         | key: string, value: Object                                                                                                            | 全局添加http请求头      |
| setHeaderOptions  | Array<HeaderOptions>                                                                                                                  | 全局设置http请求头      |
| deleteHeader      | key: string                                                                                                                           | 全局删除http请求头      |
| setCustomGetImage | customGetImage?: (context: Context, src: string、PixelMap、Resource ,headers?: Record<string, Object>) => Promise<ArrayBuffer、undefined>| 全局设置自定义下载 |
| setEngineKeyImpl  | IEngineKey                                                                                                                            | 全局配置缓存key生成策略    |
| putCacheImage     | url: string, pixelMap: PixelMap, cacheType: CacheStrategy = CacheStrategy.Default, signature?: string                                 | 写入内存磁盘缓存         |
| removeMemoryCache | url: string、ImageKnifeOption                                                                                                          | 清理指定内存缓存      |
| removeFileCache   | url: string、ImageKnifeOption                                                                                                          | 清理指定磁盘缓存      |
| getCacheLimitSize  | cacheType?: CacheStrategy                                                                                                             | 获取指定缓存的上限大小      |
| getCurrentCacheNum  | cacheType?: CacheStrategy                                                                                                             | 获取指定缓存的当前缓存图片个数  |
| getCurrentCacheSize  | cacheType?: CacheStrategy                                                                                                             | 获取指定缓存的当前大小      |
| getCurrentCacheSize  | cacheType?: CacheStrategy                                                                                                             | 获取指定缓存的当前大小      |

### 回调接口说明
| 回调接口        | 回调字段                                                                                | 回调描述                                                                                                                                                                  |
|----------------|-------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| onLoadStart    | req: ImageKnifeRequest                                                              | req返回字段中包含了图片请求的信息，如图片的url及其组件的宽高，同时ImageKnifeRequest包含了ImageKnifeData，其中包含此次请求的开始及其检查内存缓存的时间点                                                                        |
| onLoadSuccess  | data: string、PixelMap、undefined, imageData: ImageKnifeData, req?: ImageKnifeRequest | data:加载成功的结果数据；imageData：图片的存入缓存中的信息 ，req：图片请求的信息，同时其中的ImageKnifeData，包含此次请求中图片的原始大小、图片的解码大小、格式、图片帧、请求结束时间、磁盘检查时间、网络请求开始结束、图片解码开始结束等时间点                               |
| onLoadFailed   | err: string, req?: ImageKnifeRequest                                                | err:错误信息描述；req：图片请求的信息，同时其中的ImageKnifeData，包含此次请求错误信息（ErrorInfo，TimeInfo），ErrorInfo其中包含了，错误阶段、错误码及其网络请求的错误码；TimeInfo中包含请求结束时间、磁盘检查时间、网络请求开始结束、图片解码开始结束等时间点            |
| onLoadCancel   | reason: string, req?: ImageKnifeRequest                                             | reason:取消回调原因；req：图片请求的信息，同时其中的ImageKnifeData，包含此次请求错误信息（ErrorInfo，TimeInfo），ErrorInfo其中包含了，错误阶段、错误码及其网络请求的错误码；TimeInfo中包含请求结束时间、磁盘检查时间、网络请求开始结束、图片解码开始结束及其请求取消等时间点   |

### 图形变换类型（需要为GPUImage添加依赖项）

| 类型                               | 相关描述                      |
| ---------------------------------- | ----------------------------- |
| BlurTransformation                 | 模糊处理                      |
| BrightnessTransformation           | 亮度滤波器                    |
| CropSquareTransformation           | 正方形剪裁                    |
| CropTransformation                 | 自定义矩形剪裁                |
| GrayScaleTransformation            | 灰度级滤波器                  |
| InvertTransformation               | 反转滤波器                    |
| KuwaharaTransformation             | 桑原滤波器（使用GPUIImage）   |
| MaskTransformation                 | 遮罩                          |
| PixelationTransformation           | 像素化滤波器（使用GPUIImage） |
| SepiaTransformation                | 乌墨色滤波器（使用GPUIImage） |
| SketchTransformation               | 素描滤波器（使用GPUIImage）   |
| SwirlTransformation                | 扭曲滤波器（使用GPUIImage）   |
| ToonTransformation                 | 动画滤波器（使用GPUIImage）   |
| VignetterTransformation            | 装饰滤波器（使用GPUIImage）   |

## 下载安装GPUImage依赖
方法一：在Terminal窗口中，执行如下命令安装三方包，DevEco Studio会自动在工程的oh-package.json5中自动添加三方包依赖。
```
    ohpm install @ohos/gpu_transform
```
方法二： 在工程的oh-package.json5中设置三方包依赖，配置示例如下：
```
    "dependencies": {
      "@ohos/gpu_transform": "^1.0.2"
    }
```
## 约束与限制

在下述版本验证通过：  
DevEco Studio: NEXT Beta1-5.0.3.806, SDK: API12 Release(5.0.0.66)

## 关于混淆
- 代码混淆，请查看[代码混淆简介](https://docs.openharmony.cn/pages/v5.0/zh-cn/application-dev/arkts-utils/source-obfuscation.md)
- 如果希望imageknife库在代码混淆过程中不会被混淆，需要在混淆规则配置文件obfuscation-rules.txt中添加相应的排除规则：

```
-keep
./oh_modules/@ohos/imageknife
```
## 贡献代码

使用过程中发现任何问题都可以提 [issue](https://gitcode.com/openharmony-tpc/ImageKnife/issues)
，当然，也非常欢迎发 [PR](https://gitcode.com/openharmony-tpc/ImageKnife/pulls) 共建。

## 开源协议

本项目基于 [Apache License 2.0](https://gitcode.com/openharmony-tpc/ImageKnife/blob/master/LICENSE) ，请自由的享受和参与开源。

## 遗留问题

- ImageKnifeAnimator组件无法设置ImageFit属性