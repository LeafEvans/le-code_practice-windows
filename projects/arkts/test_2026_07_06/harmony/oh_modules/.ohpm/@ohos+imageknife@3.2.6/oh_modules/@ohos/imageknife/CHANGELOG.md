## 3.2.6
- Add and adapt ImageKnifeComponentV2
- Add and adapt ImageKnifeAnimatorComponentV2
- Fix string type placeholder not displaying
- Fix string type errorholder not displaying
- Only the main image enters the queue for processing

## 3.2.6-rc.0
- ImageKnife Option does not initiate a request when the attribute content remains unchanged during loading
- Fix custom network causing local images to fail to load

## 3.2.5
- Fix image retry function failure

## 3.2.4
- Repeated requests to destroy other components with different IDs or versions in the state of proxies are issued

## 3.2.4-rc.1
- Use system components to load placeholders instead
- Duplicate Request Merge: Merge all duplicate requests into one request

## 3.2.4-rc.0
- Fix preloadCache interface setting ImageKnife Option callback failure
- The images that failed during the decoding phase were fixed and stored in the file cache
- Add hiTrace to each loading step
- Type does not support adding request header information to error logs

## 3.2.3
- File cache storage failed, recreate cache directory

## 3.2.3-rc.0
- Fix the placeholder map error and set ImageFit Auto is invalid
- Add global setting network timeout duration interface
- Fix file cache quantity exceeding lru quantity

## 3.2.2
- Cancel threads when destroying components
- Modify the error callback component ID and version log
- Request for main image not entering queue without value transmission

## 3.2.2-rc.2
- Requests that do not display a placeholder map in the queue, the placeholder map issues a request to read memory
- Release showPixelMap callback when destroying ImageKnife Component
- Fix memory leaks caused by arrayBuffer
## 3.2.2-rc.1
- Support EXIF metadata carried by images as display orientation

## 3.2.2-rc.0
- Add ImageKnifeComponent to destroy network request interruption
- Code refactoring during the download of image resources stage

## 3.2.1
- Release official version

## 3.2.1-rc.0
- Fix bug: CropTransformation is used to crop the original image
- Fix bug: After calling the clear all file cache interfaces, the file cache becomes invalid 
- Optimize the efficiency of file cache initialization.
- Add protection at the location where loadSrc is passed in the pixelmap type

## 3.2.0
- When successfully requesting the network, return the httpcode as well
- Fix bug: Network error code httpCode returns no data
- Modify implementation of ImageFit.Auto: do not modify image height
- Modify memory cache limit and file cache limit
- Fix record decodeEndTime in imageKinfaData
- Add image buffersize in memory cache
- Optimize the magic number of heif format image files
- Fix bug: The width and height of the downsampling component are inconsistent with the image resolution unit

## 3.2.0-rc.6
- Support LogUtil to turn off log
- Support set network request readTimeout and connectTimeout through ImageKnifeOption

## 3.2.0-rc.5
- Enhance: ImageFit.Auto support adaptive height after component width change
- Fix bug: call onLoadStart 2 times(import from 3.2.0-rc.0)
- Change the initial value of the PixelMap component of ImageKnife to ImageContent EMPTY
- Clear memory cache, cancel pixel map release
- Loading process log modification
- Change the network request readTimeout to 30s

## 3.2.0-rc.4
- Support ICO format images
- Fix bug: call reload problem in onLoadFailed
- Provide default downsampling strategy to prevent slow loading for large images

## 3.2.0-rc.3
- Fix bug: PixelMap size exceeds the maximum value of memory cache and is not cached
- Dealing with exception scenarios where imageSource.getImageInfo return undefined
- Fix inability to parse Resource format images of other modules
- Improve the error logs
- Fix callback onLoadFailed when taskpool exception occurs
- ImageKnife AnimatorComponent component adds rounded corner function

## 3.2.0-rc.2
- Added callback information for image loading
- Added the interface for obtaining the upper limit and size of the current cache and the number of images corresponding to the current cache
- HTTPS custom certificate verification
- Add downsampling function to reduces memory cache consumption

## 3.2.0-rc.1
- Change the queue from Stack to Queue
- ShowPixelMap callback PixelMap assigns value to Image component to synchronize

## 3.2.0-rc.0
- Rollback the old version V1 decorator. V2 decorator will be provided in version 4.x
- The sub-thread network request is changed to asynchronous, thereby increasing the number of concurrent sub-thread network requests
- Set the concurrency through the setMaxRequests interface under the ImageKnife class
- aboutToRecycle life cycle clear image content
- Fixed bug for receive only the first onLoadStart for concurrent identical requests
- Modify the condition for determining whether to queue to be greater than or equal to maxRequests

## 3.1.1-rc.1
- Photo reduction sampling

## 3.1.1-rc.0
- 重构代码：抽取ImageKnifeDispatcher子线程requestJob相关代码到ImageKnifeLoader中，降低函数复杂度

## 3.1.0
- 部分静态webp图片有delay属性导致识别成动图,改用getFrameCount识别
- 修复加载错误图后未去请求排队队列中的请求
- 子线程本地Resource参数类型转换成number
- 修改使用hilog记录日志，默认打开debug级别的日志
- file格式图片，fd同步close
- 解码pixelMap默认不可编辑，图形变化可编辑
- 修改网络请求超时设置

## 3.1.0-rc.2
- 修复宽高不等svg图片显示有毛边

## 3.1.0-rc.1
- ImageKnifeAnimatorComponent新增开始、结束、暂停的回调事件
- 文件缓存数量负数和超过INT最大值时默认为INT最大值

## 3.1.0-rc.0
- ComponentV2装饰器适配
- imageKnifeOption={...}用法改为new ImageKnifeOption({...})
- animatorOption={...}用法改为new AnimatorOption({...})

## 3.0.3
- Released version 3.0.3

## 3.0.3-rc.0
- Custom network method to add request header parameters

## 3.0.2
- Added new image reloading interface reload
- Added return request preload interface preload
- Added cancel request interface cancel

## 3.0.2-rc.2
- ImageKnifeAnimatorComponent新增开始、结束、暂停的回调事件
- 文件缓存数量负数和超过INT最大值时默认为INT最大值
- 修复宽高不等svg图片显示有毛边
- 部分静态webp图片有delay属性导致识别成动图,改用getFrameCount识别
- 修复加载错误图后未去请求排队队列中的请求
- 子线程本地Resource参数类型转换成number
- 修改使用hilog记录日志，默认打开debug级别的日志
- 解码pixelMap默认不可编辑，图形变化可编辑
- 修改网络请求超时设置
- 重构代码：抽取ImageKnifeDispatcher子线程requestJob相关代码到ImageKnifeLoader中，降低函数复杂度

## 3.0.2-rc.1
- release打包关闭混淆

## 3.0.2-rc.0
- FileUtil.readFile接口和file格式图片同步关闭fd

## 3.0.1
- 修复animatorOption属性设置初始化值失效
- 网络请求code为206、204时返回arraybuffer
- ImageKnifeComponent显示非必要文件缓存初始化
- 修复webp静态图无法设置图形变换

## 3.0.1-rc.2
- 修复自定义下载失败无失败回调
- 增加全局配置自定义下载接口
- 修复主图相同，错误图不同导致只显示一个错误图
- heic格式图片文件魔数从第五位开始匹配

## 3.0.1-rc.1
- 新增ImageKnifeAnimatorComponent控制动图组件
- 修复部分heif图无法解码

## 3.0.1-rc.0
- 文件缓存设置最大缓存数量改为无限制

## 3.0.0
- 修复图形变换的闪退问题
- 自定义下载customGetImage改为仅主图支持
- 修改网络请求requestInStream配置优先返回arraybuffer
- 新增ColorFilter属性

## 3.0.0-rc.9
- 修复Resource类型$r(变量无法)加载
- 成功回调增加图片格式
- Image组件增加onComplete回调
- 修复404链接无返回错误信息
- onLoadListener增加请求取消回调

## 3.0.0-rc.8
- svg解码单位改为px
- 修复预加载接口preLoadCache传ImageKnifeOption失效
- 文件缓存初始化接口新增目录参数
- 占位图从内存获取提前到判断队列前面
- 图片改为不可拖拽
- 修复getCacheImage默认内存获取后不返回数据
- 成功回调返回GIF图宽高

## 3.0.0-rc.7
- 修复成功回调获取不到宽高
- 新增svg图片解码
- 新增媒体图片file://格式
- 修复头像超过设备高度图片闪动问题-消息列表底部头像闪动问题

## 3.0.0-rc.6
- 支持多种组合变换
- 支持全局配置是否在子线程请求加载图片，默认在子线程
- 文件缓存初始化增加默认值
- 预加载接口新增返回加载错误信息
- 加载队列改为使用堆Stack
- fileType图片格式新增heic格式

## 3.0.0-rc.5
- 图片加载事件增加请求开始的回调,以及修复有缓存时，没有回调的bug
- 修复对已销毁组件不再下发请求的逻辑
- 加载图片流程添加日志
- 子线程写入文件缓存获取buffer优化
- 成功回调增加返回图片分辨率宽高
- 内存缓存时将pixelMap进行release释放
- 提供清理缓存能力

## 3.0.0-rc.4
- 支持hsp多包图片资源
- 新增putCache写入缓存接口
- 修复入参为pixelMap图片不显示问题
- 网络请求减少拼接操作，修复网络加载速度慢
- 提供图片加载成功/失败的事件

## 3.0.0-rc.3
- 将请求默认并行从64调整到8，减少对taskpool execute内存消耗
- 补充option参数：placeholderObjectFit，errorholderObjectFit分别支持占位图填充效果和错误图填充效果

## 3.0.0-rc.2
- 新增支持使用一个或多个图片变换，如模糊，高亮等

## 3.0.0-rc.1
- 新增从内存或文件缓存获取图片数据接口getCacheImage
- 新增图片预加载preLoadCache并返回文件缓存路径
- ImageKnifeOption新增writeCacheStrategy存入策略(只存入内存或文件缓存)
- ImageKnifeOption新增onlyRetrieveFromCache仅用缓存加载
- 新增单个和全局请求头
- 补齐自定key特性
- 获取组件宽高改用onSizeChange （需要API12）

## 3.0.0-rc.0
- 使用Image组件替换Canvas组件渲染，并重构大部分的实现逻辑，提升渲染性能

较2.x版本增强点：
- 使用Image组件代替Canvas组件渲染
- 重构Dispatch分发逻辑，支持控制并发请求数，支持请求排队队列的优先级
- 支持通过initMemoryCache自定义策略内存缓存策略和大小。
- 支持option自定义实现图片获取/网络下载
- 继承Image的能力，支持option传入border，设置边框，圆角
- 继承Image的能力，支持option传入objectFit设置图片缩放
- 修复发送消息时最近的两条消息头像闪动的问题

缺失特性
- 不支持drawLifeCycle接口，通过canvas自会图片
- mainScaleType，border等参数，新版本与系统Image保持一致
- gif/webp动图播放与控制
- signature自定义key的实现
- 支持进行图片变换: 支持图像像素源图片变换效果。
- 抗锯齿相关参数

## 2.2.0-rc.2
- ImageKnife支持heic图片修改demo，按钮控制组件是否展示
- ImageKnife控制可视化区域图片

## 2.2.0-rc.1
- 修改ImageKnife跳过网络,点击默认,图片没有传入宽高,无显示bug
- ImageKnife支持根据自定义key获取已缓存的图片
- ImageKnife加载图片支持自定义网络栈和图片加载组件
- 适配复用场景触发懒加载onDataReloaded
- ImageKnife控制重要图片请求加载优先级

## 2.2.0-rc.0
- 修复自定义DataFetch接口实现不生效问题
- 修改磁盘缓存到子线程
- 更新SDK到API12
- 适配Sendable内存共享优化
- 修改全局请求头覆盖request请求头
- imageKnife支持heic测试demo独立页面展示
- drawLifeCycle支持gif图

## 2.1.2
- 修改ImageKnife跳过网络，从内存中获取图片 cacheType参数未使用bug
- 新增WEBP图片解析能力。
- 新增gif图片支持暂停播放功能

## 2.1.2-rc.12
- 新增gif播放次数功能
- 新增磁盘预加载返回文件路径接口prefetchToDiskCache
- 新增跳过网络判断缓存或者磁盘中是否存在图片接口isUrlExist
- 删除多余操作磁盘记录读写
- 清除定时器改为Gif图时清除
- uuid改为util.generateRandomUUID()

## 2.1.2-rc.11
- 修复设置磁盘容量最大值出现闪退
- 修复概率出现jscrash问题
- 修复进度条问题
- 修复单帧gif图片加载失败
- removeRunning删除running队列log设置开关
- ImageKnife新增图片宽高自适应功能
- 修复onlyRetrieveFromCache属性(仅磁盘和内存获取资源)失效
- 修改拼写错误
- 新增多线程优先级
- 修复复用场景下图片闪动以及概率错位
- 获取组件宽高改为使用CanvasRenderingContext2D对象获取宽高，并修复改变字体大小导致部分图片消失
- 修复获取不到磁盘缓存文件问题
- 修复获取不到网络请求错误回调问题

## 2.1.2-rc.10
- 修复部分gif图片识别成静态图
- 修复同一张图片发送多次请求
- 复用场景缓存到树aboutToRecycle清理定时器

## 2.1.2-rc.9
- 使用taskpool实现多线程加载图片资源
- 修复部分gif图片识别成静态图
- 修复同一张图片发送多次请求
- disAppear生命周期清空定时器只在gif图片时执行

## 2.1.2-rc.8
- onAreaChange绘制图片改为component Util绘制

## 2.1.2-rc.7
- 修复图片圆角图形变换导致抗锯齿、ScaleType失效
- 修复使用模糊化出现图片变模糊和变形

## 2.1.2-rc.6
- 修复手机调节显示大小时图片消失
- imageKnife防盗链，header请求头属性设置
- pngWorker线程改为taskpool
- 修复正方形裁剪有些图片裁剪创建pixelMap失败

## 2.1.2-rc.5
- moduleContext新增缓存策略，缓存上限5，缓存策略Lru
- 适配DevEco Studio 4.1（4.1.3.415）--SDK:API11（ 4.1.0.56）


## 2.1.2-rc.4
- canvas新增抗锯齿
- 修复图片缩放时出现重影

## 2.1.2-rc.3
- svg图片解码改为imageSource解码


## 2.1.2-rc.2
- HSP兼容性优化
- 暴露DetachFromLayout接口
- 修复无法识别部分svg图片的类型

## 2.1.2-rc.1
- 修复断网状态下错误占位图不显示
- 适配IDE4.1(4.1.3.322)和SDK API11(4.1.0.36)

## 2.1.2-rc.0
- 开放.jpg .png .gif的taskpool解码能力


## 2.1.1
- 屏蔽了taskpool解码能力
- 2.1.1正式版本发布

## 2.1.1-rc.5
- .jpg .png .gif解码功能使用taskpool实现
- 修复了内存缓存张数设置为1时gif图片消失的问题
- 新增内存缓存策略，新增缓存张数，缓存大小设置接口
- 磁盘存缓存setAsync改成同步
- 部分release释放放在异步
- requestInStream的回调改成异步
- 修复tasktool出现crash问题
- imageKnife依赖更名为library
- 解决外部定时器失效的问题


## 2.1.1-rc.4

- 删除pako源码依赖,使用ohpm依赖
- 删除gif软解码相关依赖库,包括gifuct-js和jsBinarySchemaParser
- 新增ImageKnife在HSP场景中的使用案例展示
- 更改ImageKnifeOption：
  新增可选参数context,HSP场景中在shard library中使用必须要传递当前library的context对象 （例如:getContext(this).createModuleContext('library') as common.UIAbilityContext）才能保证后续程序正常获取shared library中的Resource资源
- 更改RequestOption:
  新增接口setModuleContext(moduleCtx:common.UIAbilityContext)在HSP场景中必须调用该接口传入正确的context对象,保证HSP场景下正确访问资源
  新增接口getModuleContext():common.UIAbilityContext | undefined

## 2.1.1-rc.3

- 门面类ImageKnife新增pauseRequests接口,全局暂停请求
- 门面类ImageKnife新增resumeRequests接口,全局恢复暂停

## 2.1.1-rc.2

- gif解码改为imageSource解码,不在对worker强依赖
- 下载接口修改为http.requestInStream

## 2.1.1-rc.1

- 新增自定义key参数配置
- 新增MemoryLruCache主动调用PixelMap的release方法,释放native的PixelMap内存
- 新增ImageSource主动调用release方法释放native持有的ImageSource内存

## 2.1.1-rc.0

- 修复不兼容API9的问题

## 2.1.0

- ArkTs语法适配:

  globalThis.ImageKnife方式已经不可使用

  提供了ImageKnifeGlobal对象单例全局可访问

  访问ImageKnife对象需要使用ImageKnifeGlobal.getInstance().getImageKnife()

- 裁剪组件暴露PixelMapCrop组件和配置类Options, 配置类Options不再需要声明PixelMapCrop.Options中的PixelMapCrop命名空间

- 适配DevEco Studio 版本：4.0(4.0.3.512), SDK: API10 (4.0.10.9)

## 2.0.5-rc.0

- 修复若干问题：

​      优化了内存缓存策略，修复了内存缓存策略给布尔值不生效的问题

## 2.0.4

- 修复若干问题：

​      修复了pngj测试页面，快速点击导致应用闪退的问题


## 2.0.3

- 修复若干问题：

​      修复了部分url测试，多次点击加载gif动画重影的问题

​      优化了gif测试中的测试图片，加强了测试的直观性

​      解决gif图片只有1帧时因帧时间延时时间为NaN时导致图片帧不显示的问题


## 2.0.2

- 修复若干问题：

​      修复ImageKnife绘制部分复杂gif图片，gif图片闪屏显示的问题

​      适配DevEco Studio 版本：4.0 Canary2(4.0.3.312), SDK: API10 (4.0.9.3)



## 2.0.1

- 修复若干问题：

​      修复ImageKnifeDrawFactory中的setOval和setRect的中心点取值错误，导致部分圆角绘制失效的问题。

​      修复因重复下载导致的漏加载的问题。

- 新增用例看护已修复的问题

## 2.0.0

- 包管理工具由npm切换为ohpm。
- 适配DevEco Studio: 3.1Beta2(3.1.0.400)。
- 适配SDK: API9 Release(3.2.11.9)。
- 新增开发者可对图片缓存进行全局配置能力。
- 新增对OpenHarmony图库的Uri数据加载的能力（需要申请图库访问权限和文件读取权限，动态申请图库访问权限）。
- 修复若干问题：

​      ImageKnifeOption的loadSrc为undefined，导致的crash问题。

​      ImageKnifeComponent直接绘制GIF图片格式第几帧的时候，无法绘制问题。

## 1.0.6

- 适配DevEco Studio 3.1Beta1及以上版本。

- 适配OpenHarmony SDK API version 9及以上版本。

- 以下变换支持通过GPU进行图片变换，默认未开启，开启需要自行调用接口.enableGPU()。

  ​	支持模糊图片变换

  ​	支持亮度滤波器

  ​	支持颜色反转滤波器

  ​	支持对比度滤波器

  ​	支持灰色滤波器

  ​	支持桑原滤波器

  ​	支持马赛克滤波器

  ​	支持乌墨色滤波器

  ​	支持素描滤波器

  ​	支持扭曲滤波器

  ​	支持动画滤波器

  ​	支持装饰滤波器
## 1.0.5
- 自定义组件已支持通用属性和通用事件绑定,因此ImageKnifeComponent将删除相关内容,相关内容由用户自定义实现，提高扩展能力。

- ImageKnifeOption 支持列表绑定。

- ImageKnifeOption 。

  新增

  -  1.onClick事件属性

  删除

  - 1.size(设置大小)
  - 2.sizeAnimated 显式动画
  - 3.backgroundColor背景色
  - 4.margin 组件外间距 等属性,删除的属性将由通用属性提供支持,可支持在ImageKnifeComponent自定义组件上链式调用
## 1.0.4

- 渲染显示部分使用Canvas组件替代Image组件。

- 重构渲染封装层ImageKnifeComponent自定义组件。

- 新增GIF图片解析能力。

- 新增SVG图片解析能力。

- RequestOption删除addRetryListener接口,重试图层监听请使用retryholder接口。

## 1.0.3

- 适配OpenHarmony API9 Stage模型。
## 1.0.2
- 支持用户自定义扩展变换接口。

## 1.0.1
- 由gradle工程整改为hvigor工程。

## 1.0.0
专门为OpenHarmony打造的一款图像加载缓存库，致力于更高效、更轻便、更简单：
- 支持内存缓存，使用LRUCache算法，对图片数据进行内存缓存。
- 支持磁盘缓存，对于下载图片会保存一份至磁盘当中。
- 支持进行图片变换。
- 支持用户配置参数使用:(例如：配置是否开启一级内存缓存，配置磁盘缓存策略，配置仅使用缓存加载数据，配置图片变换效果，配置占位图，配置加载失败占位图等)。
- 推荐使用ImageKnifeComponent组件配合ImageKnifeOption参数来实现功能。
- 支持用户自定义配置实现能力参考ImageKnifeComponent组件中对于入参ImageKnifeOption的处理。

