# ImageKnife

ImageKnife is a specially crafted image loading and caching library for OpenHarmony, optimized for efficiency, lightness, and simplicity.

## Introduction

This project is a self-developed version for OpenHarmony, inspired by the open-source [Glide](https://github.com/bumptech/glide) library. It sports the following features:

- Customizable memory cache strategy with adjustable cache size (default LRU)
- Disk L2 cache for downloaded images
- Custom implementation for image acquisition and network downloading
- Listening for progress of network downloads through callbacks
- Image options for borders and rounded corners
- Image scaling with **objectFit**, including auto-adapting height
- Image scaling through transformation
- Concurrent request management with priority queuing
- No requests made for images whose lifecycle has been destroyed
- Custom cache keys
- Custom HTTP request headers
- **writeCacheStrategy** for controlling cache storage (memory or file)
- Preloading images with **preLoadCache**
- Loading images exclusively from cache with **onlyRetrieveFromCache**
- Support for image transformations such as blurring and highlighting

Planned features:

- Memory downsampling optimization to save memory usage
- Support for custom image decoding

Note: The 3.x version has been significantly restructured from the 2.x version, mainly in the following aspects:

- Use of the **Image** component instead of the **Canvas** component for rendering
- Refactored dispatch logic to control the number of concurrent requests and support priority in request queuing
- Support for custom memory cache strategies and sizes through **initMemoryCache**
- Support for custom implementation of image acquisition/network downloading through options

Therefore, there are some differences in APIs and capabilities, which mainly include the following:

- The **drawLifeCycle** API is not supported; images are drawn manually through the canvas.
- In the new version, parameters such as **mainScaleType** and **border** are consistent with the system **Image** component.
- GIF/WebP animation playback and control (implemented by **ImageAnimator**).
- Anti-aliasing related parameters.

## How to Install

```
ohpm install @ohos/imageknife

// If file caching is required, initialize the file cache in advance.
await ImageKnife.getInstance().initFileCache(context, 256, 256 * 1024 * 1024)
```

## How to Use

#### 1. Displaying a Local Resource Image

```
ImageKnifeComponent({
  imageKnifeOption:{
    loadSrc: $r("app.media.app_icon"),
    placeholderSrc: $r("app.media.loading"),
    errorholderSrc: $r("app.media.app_icon"),
    objectFit: ImageFit.Auto
  }
}).width(100).height(100)
```

#### 2. Displaying a File from Local Context Files

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

#### 3. Displaying a Network Image

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

#### 4. Downloading an Image with Custom Options

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

// Custom implementation of the image acquisition method, such as custom network download。
@Concurrent
async function custom(context: Context, src: string | PixelMap | Resource): Promise<ArrayBuffer | undefined> {
  console.info("ImageKnife:: custom download: " + src)
  // Example of hardcoding to read from a local file. You can also request a network image.
  return context.resourceManager.getMediaContentSync($r("app.media.bb").id).buffer as ArrayBuffer
}
```

#### 5. Listening for Network Download Progress

```
ImageKnifeComponent({
  imageKnifeOption: {
    loadSrc:"https://www.openharmony.cn/_nuxt/img/logo.dcf95b3.png",
    progressListener:(progress:number)=>{console.info("ImageKinfe:: call back progress = " + progress)}
  }
}).width(100).height(100)
```

#### 6. Setting Border Options

```
ImageKnifeComponent({ imageKnifeOption: 
{
   loadSrc: $r("app.media.rabbit"),
   border: {radius:50}
  }
}).width(100).height(100)
```

#### 7. Setting Image Transformation Options

```
ImageKnifeComponent({ imageKnifeOption: 
{
   loadSrc: $r("app.media.rabbit"),
   border: {radius:50},
   transformation: new BlurTransformation(3)
  }
}).width(100).height(100)
```
Multiple combined transformation usages:

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
  border: { radius: { topLeft: 50, bottomRight: 50 } }, // Rounded corner settings
  transformation: transformations.length > 0 ? new MultiTransTransformation(transformations) : undefined // Graphic transformation group
}
}).width(300)
  .height(300)
  .rotate ({angle: 90}) // Rotate by 90 degrees.
  .contrast(12) // Contrast filter
```
Other transformation-related properties can be stacked to achieve combined transformation effects.

Example of circular cropping transformation:

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

Example of Circular cropping with border transformation:

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

Example of contrast filtering transformation:

```
ImageKnifeComponent({
  imageKnifeOption: {
    loadSrc: $r('app.media.pngSample')
  }
}).width(300)
  .height(300)
  .contrast(12)
```

Example of rotation transformation:

```
ImageKnifeComponent({
  imageKnifeOption:({
    loadSrc: $r('app.media.pngSample')
  }
}).width(300)
  .height(300)
  .rotate({angle:90})
  .backgroundColor(Color.Pink)
```

#### 8. Listening for Image Loading Success and Failure

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
#### 9. Use of syncLoad
**syncLoad** sets whether to load the image synchronously. By default, the image is loaded asynchronously. When loading a small image, you are advised to set **syncLoad** to **true** so that the image loading can be quickly completed on the main thread.
```
ImageKnifeComponent({
        imageKnifeOption:{
          loadSrc:$r("app.media.pngSample"),
          placeholderSrc:$r("app.media.loading")
        },syncLoad:true
      })
```
#### 10. Use of ImageKnifeAnimatorComponent
```
ImageKnifeAnimatorComponent({
        imageKnifeOption:{
          loadSrc:"https://gd-hbimg.huaban.com/e0a25a7cab0d7c2431978726971d61720732728a315ae-57EskW_fw658",
          placeholderSrc:$r('app.media.loading'),
          errorholderSrc:$r('app.media.failed')
        },animatorOption:this.animatorOption
      }).width(300).height(300).backgroundColor(Color.Orange).margin({top:30})
```
#### Reuse Scenario
Clear the component content in the **aboutToRecycle** lifecycle and trigger image loading through watch observeration.
## Available APIs
### ImageKnife
| Component                   | Parameter                        | Description    |
| --------------------------- | -------------------------------- | ------------ |
| ImageKnifeComponent         | ImageKnifeOption                 | Image display component.|
| ImageKnifeAnimatorComponent | ImageKnifeOption, AnimatorOption| Animated image control component.|

### AnimatorOption
| Parameter  | Type       | Description                                |
| ---------- | --------------- | ---------------------------------------- |
| state      | AnimationStatus | Playback status. Optional.                        |
| iterations | number          | Number of playback times. Optional.                        |
| reverse    | boolean         | Playback order. Optional.                        |
| onStart    | ()=>void        | Triggered when the animation starts. Optional.              |
| onFinish   | ()=>void        | Triggered when the animation finishes or stops. Optional.|
| onPause    | ()=>void        | Triggered when the animation pauses. Optional.              |
| onCancel   | ()=>void        | Triggered when the animation is canceled, that is, when it is reset to its initial state. Optional.          |
| onRepeat   | ()=>void        | Triggered when the animation repeats. Optional.              |

### ImageKnifeOption

| Parameter             | Type                                             | Description                      |
| --------------------- | ----------------------------------------------------- | ------------------------------ |
| loadSrc               | string, PixelMap, Resource                           | Main image.                      |
| placeholderSrc        | PixelMap, Resource                                   | Placeholder image. Optional.          |
| errorholderSrc        | PixelMap, Resource                                   | Error image. Optional.            |
| objectFit             | ImageFit                                              | How the main image is resized to fit its container. Optional.          |
| placeholderObjectFit  | ImageFit                                              | How the placeholder image is resized to fit its container. Optional.        |
| errorholderObjectFit  | ImageFit                                              | How the error image is resized to fit its container. Optional.        |
| writeCacheStrategy    | CacheStrategyType                                     | Cache writing strategy. Optional.            |
| onlyRetrieveFromCache | boolean                                               | Whether to skip network and local requests. Optional.|
| customGetImage        | (context: Context, src: string                        | Custom image download. Optional.        |
| border                | BorderOptions                                         | Border corner. Optional.              |
| priority              | taskpool.Priority                                     | Load priority. Optional.            |
| context               | common.UIAbilityContext                               | Context. Optional.                |
| progressListener      | (progress: number)=>void                              | Progress. Optional.                  |
| signature             | String                                                | Custom cache signature. Optional.      |
| headerOption          | Array\<HeaderOptions>                                 | Request headers. Optional.            |
| transformation        | PixelMapTransformation                                | Image transformation. Optional.              |
| drawingColorFilter    | ColorFilter                                           | Drawing color filter. Optional.            |
| onComplete            | (event:EventImage \| undefined)=>void              | Callback for image loading completion. Optional. |
| onLoadListener        | onLoadStart:()=>void,onLoadSuccess:(data:string\|Pixelmap)=>void                       | Callback for image loading events. Optional. |

### ImageKnife

| Parameter         | Type                                                    | Description                  |
| ----------------- | ------------------------------------------------------------ | -------------------------- |
| initMemoryCache   | newMemoryCache: IMemoryCache                                 | Initializes a custom memory cache strategy.        |
| initFileCache     | context: Context, size: number, memory: number               | Initializes the file cache size and quantity  |
| preLoadCache      | loadSrc: string I ImageKnifeOption                           | Preloads and returns the file cache path.  |
| getCacheImage     | loadSrc: string, cacheType: CacheStrategy = CacheStrategy.Default, signature?: string) | Obtains resources from memory or file cache.|
| addHeader         | key: string, value: Object                                   | Adds a global HTTP request header.        |
| setHeaderOptions  | Array<HeaderOptions>                                         | Sets global HTTP request headers.        |
| deleteHeader      | key: string                                                  | Deletes a global HTTP request header.        |
| setCustomGetImage | customGetImage?: (context: Context, src: string              | PixelMap                   |
| setEngineKeyImpl  | IEngineKey                                                   | Sets a global cache key generation strategy.   |
| putCacheImage     | url: string, pixelMap: PixelMap, cacheType: CacheStrategy = CacheStrategy.Default, signature?: string | Writes to the memory disk cache.          |
| removeMemoryCache | url: string                                                  | Removes an entry from the memory cache.          |
| removeFileCache   | url: string                                                  | Removes an entry from the file cache.          |
### Graphics tRansformation Types (GPUImage Dependency Required)

| Type                    | Description                     |
| ------------------------ | ----------------------------- |
| BlurTransformation       | Blurs the image.                     |
| BrightnessTransformation | Applies a brightness filter.                   |
| CropSquareTransformation | Crops the image to a square.                   |
| CropTransformation       | Crops the image to a custom rectangle.               |
| GrayScaleTransformation  | Applies a grayscale filter.                 |
| InvertTransformation     | Applies an inversion filter.                   |
| KuwaharaTransformation   | Applies a Kuwahara filter (requires **GPUImage**).  |
| MaskTransformation       | Applies a mask.                         |
| PixelationTransformation | Applies a pixelation filter (requires **GPUImage**).|
| SepiaTransformation      | Applies a sepia filter (requires **GPUImage**).|
| SketchTransformation     | Applies a sketch filter (requires **GPUIImage**).  |
| SwirlTransformation      | Applies a swirl filter (requires **GPUImage**).  |
| ToonTransformation       | Applies a cartoon filter (requires **GPUImage**).  |
| VignetterTransformation  | Applies a vignette filter (requires **GPUImage**).  |

## Downloading and Installing the GPUImage Dependency
Method 1: In the **Terminal** window, run the following command to install the third-party HAR. DevEco Studio will automatically add the HAR as a dependency to the **oh-package.json5** file of the project.
```
    ohpm install @ohos/gpu_transform
```
Method 2: Set the third-party HAR as a dependency in the **oh-package.json5** file of the project. The following is a configuration example:
```
    "dependencies": {
      "@ohos/gpu_transform": "^1.0.2"
    }
```
## Constraints

This project has been verified in the following version:

DevEco Studio: NEXT Beta1-5.0.3.806, SDK: API12 Release(5.0.0.66)

## About obfuscation
- Code obfuscation, please see[Code Obfuscation](https://docs.openharmony.cn/pages/v5.0/zh-cn/application-dev/arkts-utils/source-obfuscation.md)
- If you want the imageknife library not to be obfuscated during code obfuscation, you need to add corresponding exclusion rules in the obfuscation rule configuration file obfuscation-rules.txt：
```
-keep
./oh_modules/@ohos/imageknife
```

## How to Contribute

If you find any problem during the use, submit an [Issue](https://gitcode.com/openharmony-tpc/ImageKnife/issues) or a [PR](https://gitcode.com/openharmony-tpc/ImageKnife/issues) to us.

## License

This project is licensed under [Apache License 2.0](https://gitcode.com/openharmony-tpc/ImageKnife/blob/master/LICENSE).

## Known Issues

- The **ImageFit** attribute cannot be set for the **ImageKnifeAnimator** component.
- The **border** attribute of the **ImageKnifeAnimator** component cannot make the image rounded corners.