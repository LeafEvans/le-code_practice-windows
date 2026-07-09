# Changelog

This file documents all notable changes to the ohos_react_native project.

This changelog follows the [Keep a Changelog](https://keepachangelog.com/en/1.1.0/) specification, and the project version follows [Semantic Versioning 2.0.0](https://semver.org/).

## [0.82.30] - 2026-05-07

### Fixed
- **RefreshControl**: Fixed refreshing behavior when disabled to align with RN, [9be0277a3](https://gitcode.com/openharmony-RN/ohos_react_native/commit/9be0277a34ba9df9602617ab7ac3fc3d05f0f648)
- **RNInstance**: Fixed crash in uv send, [05660611d](https://gitcode.com/openharmony-RN/ohos_react_native/commit/05660611d7ce6c56d99ec1b63f5d07b05e61443c)
- **RefreshControl**: Fixed transparent tintColor and titleColor not taking effect, [38deaf174](https://gitcode.com/openharmony-RN/ohos_react_native/commit/38deaf1743b3b2ee95eed95491bbb9d53256a991)

## [0.82.29] - 2026-04-24

### Added
- **CrashReport**: Added JS stack trace capability for app crashes to help quickly identify crash causes, [55f415f1e](https://gitcode.com/openharmony-RN/ohos_react_native/commit/55f415f1ef1d98d96fc61c0e345703e231500fe8)
- **ScrollView**: Added HarmonyOS-specific flingSpeedLimit property for customizing scroll speed limit, [e25d91800](https://gitcode.com/openharmony-RN/ohos_react_native/commit/e25d91800240de217a1ed36b9a047668f195440e)
- **Build**: Added release mode symbol preservation to separate files for production debugging, [5f825f8a2](https://gitcode.com/openharmony-RN/ohos_react_native/commit/5f825f8a25ead496e931291e7503d3dcc0fa9b35)

### Changed
- **Image**: Changed default resizeMethod to 'auto' to align with RN Android behavior, [ab5cbe78f](https://gitcode.com/openharmony-RN/ohos_react_native/commit/ab5cbe78f12036b9eb319c62cd5638b283ebb552)

### Fixed
- **Modal**: Fixed zoom being re-enabled by default after closing popup, [70545fe58](https://gitcode.com/openharmony-RN/ohos_react_native/commit/70545fe587773a09a2dfda348adeef44bff9af94)
- **RNInstance**: Added NPE protection for m_reactInstance to fix crash, [a79fe8f3e](https://gitcode.com/openharmony-RN/ohos_react_native/commit/a79fe8f3e29d1c9833561a460cf6f027c0e45f48)
- **View**: Fixed performance degradation with 1500+ View components, [35ecfec11](https://gitcode.com/openharmony-RN/ohos_react_native/commit/35ecfec11a9338b44bf8937b42587d23551351c6)
- **Modal**: Fixed crash when sliding in third-party Modal, [907994349](https://gitcode.com/openharmony-RN/ohos_react_native/commit/907994349e5eadbf71e59a8e235f35c3a7971518)
- **API**: Fixed crash on lower API levels caused by unisolated API versions, [4ca9cb95d](https://gitcode.com/openharmony-RN/ohos_react_native/commit/4ca9cb95de642359b1e9c5c98772ed159620cc58)
- **ScrollView**: Fixed scrollable sub-components not responding to click events, [04bdca0a2](https://gitcode.com/openharmony-RN/ohos_react_native/commit/04bdca0a292d39f1ba652eadc384d515d04cdc68)
- **ScrollView**: Fixed horizontal prop being unintentionally reused when not explicitly provided, [077a3d7bb](https://gitcode.com/openharmony-RN/ohos_react_native/commit/077a3d7bb6693c9a0f25639f5cd34ad042523b5a)

### Documentation
- **Docs**: Added community development specification, [270b7249d](https://gitcode.com/openharmony-RN/ohos_react_native/commit/270b7249d9235d8a0e1e3f77195c8b846713a022)
- **Docs**: Adjusted community specification documents and provided template files, [071d05308](https://gitcode.com/openharmony-RN/ohos_react_native/commit/071d05308a9b4763496f7df82a3809b4fb6993d3)

## [0.82.23] - 2026-04-08

### Fixed
- **TextInput**: Fixed the issue where the selection attribute was invalid and selected state refreshed twice, [073955c41](https://gitcode.com/openharmony-RN/ohos_react_native/commit/073955c41bd3634c195847e30e8cef849aa5eb69)
- **ScrollView**: Fixed the issue where button clicks did not respond after disabling scrolling in the settings, [b78d58247](https://gitcode.com/openharmony-RN/ohos_react_native/commit/b78d582477ce72d2e6fbd1b3914970994ff7e37c)
- **AutolinkingSample**: Fixed the issue where the selected state was automatically cleared when switching from multi-select to single-select mode, [3d72c069d](https://gitcode.com/openharmony-RN/ohos_react_native/commit/3d72c069d741eddaf69efa95ba349aa1a71db30f)

### Added
- **Attachment**: Added isClipped field for adapting attachments, [347563229](https://gitcode.com/openharmony-RN/ohos_react_native/commit/347563229ae7fb2aba42680ac7eea801b575f443)

## [0.82.21] - 2026-03-26

### Fixed
- **ScrollView**: Fixed the scrolling capability issue after switching between horizontal and vertical screens, [f3d4e06df](https://gitcode.com/openharmony-sig/ohos_react_native/commit/f3d4e06dfe1536439b96e18b1c279edd9cc21ba6)
- **Image**: Fixed the format issue of image onError callback, [630c16883](https://gitcode.com/openharmony-sig/ohos_react_native/commit/630c168835662bf069ea3e25c68576314e08349d)
- **ScrollView**: Fixed the issue where alwaysBounceHorizontal/alwaysBounceVertical properties could not bounce back when content exceeded the container, [2d2051689](https://gitcode.com/openharmony-sig/ohos_react_native/commit/2d2051689b603c975509ab5ac44210dc320fc220)
- **ScrollNode**: Fixed crash on API level < 18, [5ca932044](https://gitcode.com/openharmony-sig/ohos_react_native/commit/5ca932044269efc1d6524aa81e635cf4f8da9c6b)
- **JSVM**: Fixed multi-threading crash issue caused by markDirty, [a84d36359](https://gitcode.com/openharmony-sig/ohos_react_native/commit/a84d36359ade20e09b2c82eafa800073617197c6)
- **TextInput**: Provided the original TextInput component onChange interface, [4416fc9ab](https://gitcode.com/openharmony-sig/ohos_react_native/commit/4416fc9ab6724fe4327014d0a5cdfbc68ca8960b)
- **Autolinking**: Fixed dependency management and path calculation issues, [d032efead](https://gitcode.com/openharmony-sig/ohos_react_native/commit/d032efead1b5ff827591ab2d2bf74c6bc6aa5ca2)
- **HostObjectProxy**: Fixed potential crash in Getter, [461030d6e](https://gitcode.com/openharmony-sig/ohos_react_native/commit/461030d6e4d7075bc548c081983971e3cc65ca7c)
- **JSVM**: Fixed use-after-free issue when calling OH_JSVM_DestroyVM, [f3ce6cab5](https://gitcode.com/openharmony-sig/ohos_react_native/commit/f3ce6cab56f1cfea7a9a5aa6895ce7ad20c11dc6)

### Added
- **Build**: Added support for preserving symlinks when compiling in release mode, [f3b2ee0ce](https://gitcode.com/openharmony-sig/ohos_react_native/commit/f3b2ee0ceadf07557265a98f38d2c8422cf93352)
- **ScrollView**: Optimized fling deceleration mapping and set default speed limit to 6000, [2b7dabe74](https://gitcode.com/openharmony-sig/ohos_react_native/commit/2b7dabe74606bcc3c9769e265518984b824cc267)
- **JSVM**: Added support for TRIM_MEMORY_RUNNING_CRITICAL in memory pressure handling, [eb502fad9](https://gitcode.com/openharmony-sig/ohos_react_native/commit/eb502fad9f29a667cd199e69be8cbce9d92cae36)
- **Memory**: Added event to get the Level value on onMemoryLevel, [4be2679db](https://gitcode.com/openharmony-sig/ohos_react_native/commit/4be2679dbdc7fd3cb77e284c8b032a169cc8e08a)
- **Autolinking**: Added support for remote dependencies, [4a66ba085](https://gitcode.com/openharmony-sig/ohos_react_native/commit/4a66ba0853715bc151f900da2611be9dc32df5b2)
- **Autolinking**: Added support for custom HA package scan paths and multi-HAR package configuration, [e9dd259fa](https://gitcode.com/openharmony-sig/ohos_react_native/commit/e9dd259fa61ee4d9a1d57d16e69f19bc3b34c8bc)

## [0.82.18] - 2026-03-10

### Fixed
- **Text**: Fixed text maxWidth issue, [bf669b3c4](https://gitcode.com/openharmony-sig/ohos_react_native/commit/bf669b3c453077e626c7169cf71c11df88eb5412)
- **ShadowView**: Fixed potential dangling pointer issue when passing componentName to ShadowView, [ab62e9d2f](https://gitcode.com/openharmony-sig/ohos_react_native/commit/ab62e9d2fcb6f4843c9ca3ffd671d2d07b617d75)
- **TextAreaNode**: Fixed the issue where preview text event was not unregistered, [f10423875](https://gitcode.com/openharmony-sig/ohos_react_native/commit/f104238759085b0db61f09154959005db963e45a)
- **ArkTS Component**: Fixed the issue where child component Tags could not be retrieved in ArkTS Component, [eff6a6c34](https://gitcode.com/openharmony-sig/ohos_react_native/commit/eff6a6c346156791a4d159447aec5fa5f376aba5)
- **Fabric**: Fixed unsafe reordering of Fabric Create mutations, [fdfa1c7e3](https://gitcode.com/openharmony-sig/ohos_react_native/commit/fdfa1c7e35a9abb16f6079734275c1d8c93645f5)

## [0.82.17] - 2026-03-03

### Fixed
- **JSVM**: Fixed libjsvm.so mapping error, [431297d2e](https://gitcode.com/openharmony-sig/ohos_react_native/commit/431297d2e8a4d56cdd4e33b7a482c80e9300a2cc)
- **ScrollView**: Fixed sliding crash issue, [13806f11a](https://gitcode.com/openharmony-sig/ohos_react_native/commit/13806f11ab3b57b4fcfafb6b3eb541b67792f230)
- **JSVM**: Fixed the issue where JS ERROR filename could not be displayed, [74a344a84](https://gitcode.com/openharmony-sig/ohos_react_native/commit/74a344a8480a27d7a51f265639280b1713fc5688)
- **Page**: Fixed the issue of page jitter caused by loop calls, [e36e110e1](https://gitcode.com/openharmony-sig/ohos_react_native/commit/e36e110e128ab7ca989e46acf99b49aa91b9bf7a)
- **HostObjectProxy**: Fixed Enumerator crash, [b5e91d3ee](https://gitcode.com/openharmony-sig/ohos_react_native/commit/b5e91d3eec946fc77e7be61141593e4ea239457e)
- **Obfuscation**: Fixed crash caused by obfuscation making method names unrecognizable, [267143411](https://gitcode.com/openharmony-sig/ohos_react_native/commit/2671434116bd5b60adf5719a3304012341a789a4)
- **JSVMPointerValue**: Fixed crash issue, [7029f4747](https://gitcode.com/openharmony-sig/ohos_react_native/commit/7029f47479d2a476a29c28e90a8dc18cb29ae1f0)
- **Modal**: Fixed inconsistent slide animation due to incorrect modal height, [6c6732ec1](https://gitcode.com/openharmony-sig/ohos_react_native/commit/6c6732ec1eb38126c313d9b8da3bbfb0f17b4a75)
- **ArkTS Component**: Fixed click unresponsiveness in custom ArkTS components after keyboard popup, [50e7c2502](https://gitcode.com/openharmony-sig/ohos_react_native/commit/50e7c25028c131f6fb1471c8e271b15792355464)
- **Performance**: Fixed stuttering caused by join suspension waiting, [d73c7ad99](https://gitcode.com/openharmony-sig/ohos_react_native/commit/d73c7ad99e82f290d909c0b0c73901d94d83be2e)
- **ShadowTreeRegistry**: Fixed re-entrant lock issue during reportMount, [ab0d11db7](https://gitcode.com/openharmony-sig/ohos_react_native/commit/ab0d11db7249f65647d89775feb448a240afa64e)
- **HttpClient**: Fixed the issue where httpClient could not use custom protocol, [32db52367](https://gitcode.com/openharmony-sig/ohos_react_native/commit/32db52367c9f6ab4bf5831d2b3549d054bbb798d)
- **Modal**: Fixed modal pop-up properties restoration logic, [32850c50e](https://gitcode.com/openharmony-sig/ohos_react_native/commit/32850c50e3240a681125b9bc859ca764c8af8786)
- **Dimensions**: Fixed the issue where system modification did not trigger the change event of JS-side Dimensions for display size, [80e4c5e8f](https://gitcode.com/openharmony-sig/ohos_react_native/commit/80e4c5e8f72dbb1734c8fd7fdaa033f9ca4034c7)

### Added
- **Autolinking**: Added support for preserving comments in oh-package.json5 during autolinking, [a8bdd40e1](https://gitcode.com/openharmony-sig/ohos_react_native/commit/a8bdd40e1cc2ce5f03cc8700f12682f5c42e90d3)

### Changed
- **Image**: Enabled Orientation.AUTO by default for RNOH Image component, [133cde9d3](https://gitcode.com/openharmony-sig/ohos_react_native/commit/133cde9d349bf9490115f923601468bc02ae6260)

### Documentation
- **FAQ**: Updated specification FAQ document, [aeea0defd](https://gitcode.com/openharmony-sig/ohos_react_native/commit/aeea0defd8cc56cf6ab441c1d77b3ed2477c7f2c)

## [0.82.8] - 2026-01-27

### Fixed
- **Share**: Fixed the issue where share.js did not support title, [78f198d1d](https://gitcode.com/openharmony-sig/ohos_react_native/commit/78f198d1d83a82bee71ca42bb40d7b9bd004979a)
- **Text**: Fixed the issue where text enlarged when scaled below minimumFontScale, [3383cb2f3](https://gitcode.com/openharmony-sig/ohos_react_native/commit/3383cb2f36c66c9f5a98705214358f44f2fd6c14)
- **TextInput**: Reverted cursor jumping issue fix, [ac13b0971](https://gitcode.com/openharmony-sig/ohos_react_native/commit/ac13b09712e38de4e6fa7dcf139191e2e9cc94d9)
- **TextInput**: Reverted the fix for the issue where modified text in onKeyPress function only displayed the last character, [4e5104c90](https://gitcode.com/openharmony-sig/ohos_react_native/commit/4e5104c90ac2367ce254ff85a20aab1e715c49a7)
- **Text**: Fixed the issue where allowFontScaling did not update font in real-time when system font size was adjusted, [ce362d8c1](https://gitcode.com/openharmony-sig/ohos_react_native/commit/ce362d8c1b9e55a8c7ac58c47d96ebbad45b8ccc)
- **Modal**: Fixed modal scaling detection logic, [de584c48e](https://gitcode.com/openharmony-sig/ohos_react_native/commit/de584c48e6d343ef7da6bece22b0d40728602e73)
- **RefreshControl**: Fixed the issue of disabling refreshing before onRefresh callback, [73109c5b1](https://gitcode.com/openharmony-sig/ohos_react_native/commit/73109c5b1c7819638738da31996ff11797ec457f)
- **Image**: Fixed the issue where base64 image returned remote source type, [fe217807b](https://gitcode.com/openharmony-sig/ohos_react_native/commit/fe217807b54e880333f65817e10bf01ad4631ed0)

### Documentation
- **StatusBar**: Supplemented status bar usage instructions, [7cf93756b](https://gitcode.com/openharmony-sig/ohos_react_native/commit/7cf93756ba99517974cc0599fd8cc8910c21c877)

## [0.82.5] - 2026-01-09

### Fixed
- **View**: Deleted invalid View.js property, [64976f1e6](https://gitcode.com/openharmony-sig/ohos_react_native/commit/64976f1e6bc733f9bc99acd266faaaf46466920b)
- **Font**: Fixed font scaling limit issue, [319ba2281](https://gitcode.com/openharmony-sig/ohos_react_native/commit/319ba228183cd7e779df4928a07742291723a917)
- **TextInput**: Fixed the issue where modified text in onKeyPress function only displayed the last character, [84df7b715](https://gitcode.com/openharmony-sig/ohos_react_native/commit/84df7b715e737ec503ede72a58d2c92320f8ed56)
- **Version**: Fixed version in release note and node version, [f3a6dec7d](https://gitcode.com/openharmony-sig/ohos_react_native/commit/f3a6dec7d4b41836e5ae30528275452bf9fe6e19)
- **SDK**: Improved SDK version configuration guide, [6a6d0eeff](https://gitcode.com/openharmony-sig/ohos_react_native/commit/6a6d0eeffeeae56c0f7a62edc82b9378a8675c3b)
- **TextInput**: Fixed the issue where content in search input box refreshed again, [b13f9808d](https://gitcode.com/openharmony-sig/ohos_react_native/commit/b13f9808da86c2b65f23b92888a9a11441647c78)
- **SafeAreaView**: Reverted bottom inset calculation fix for layout jitter, [68cac5386](https://gitcode.com/openharmony-sig/ohos_react_native/commit/68cac53862e319a11f68c83744eeb251386602e1)
- **View**: Fixed setting transparent borderColor, [32370a052](https://gitcode.com/openharmony-sig/ohos_react_native/commit/32370a052db5b995a760b948bf3b8b9efc26ee85)
- **Docs**: Fixed documentation links and abbreviations, [9a923c26e](https://gitcode.com/openharmony-sig/ohos_react_native/commit/9a923c26e716aee82a4ce8adb9fd5d963417ea80)
- **TextInput**: Fixed the cursor jumping issue, [6333e6323](https://gitcode.com/openharmony-sig/ohos_react_native/commit/6333e63238adc88fadd045d3484d59d653d6f084)
- **NodeAPI**: Fixed crash when nodeApi is nullptr, [754a2da27](https://gitcode.com/openharmony-sig/ohos_react_native/commit/754a2da27b5f8c0c8d8f532fb32a5b47587be997)
- **Socket**: Fixed crash when socket set to undefined before close, [fae39e8e0](https://gitcode.com/openharmony-sig/ohos_react_native/commit/fae39e8e03d603c15c47accbd611f78cf14b5b39)
- **Text/TextInput**: Fixed wrong layout measurements, [9529568c3](https://gitcode.com/openharmony-sig/ohos_react_native/commit/9529568c350855093fa445f363b4531ae730c402)
- **ScrollView**: Fixed the issue where layoutMeasurement field was undefined, [62a502d10](https://gitcode.com/openharmony-sig/ohos_react_native/commit/62a502d1045f993bfc3133bfe7db25609ed1766d)
- **Surface**: Fixed using_surface sample not using navdestination, [ff14bec1a](https://gitcode.com/openharmony-sig/ohos_react_native/commit/ff14bec1a8762bbf4c2c93f4a7f2119fe19cad95)
- **SafeAreaView**: Optimized SafeAreaView by caching insets to reduce TurboModule sync calls, [9e2ef73c1](https://gitcode.com/openharmony-sig/ohos_react_native/commit/9e2ef73c1eb5c921b8a34a12bc3a584f51aeaf64)
- **TextInput**: Fixed the issue that TextInput of numeric keyboardType could not display non-numeric symbols, [b36c304e1](https://gitcode.com/openharmony-sig/ohos_react_native/commit/b36c304e1a1af923dac6ca73ae0ddf05f44698fd)
- **WindowDecor**: Adjusted timing of getWindowDecorVisible call to prevent exceptions, [38e3b1f6f](https://gitcode.com/openharmony-sig/ohos_react_native/commit/38e3b1f6f93ba94d36dc957cbe53463b1ccc3ae3)
- **SafeAreaView**: Fixed layout jitter by refining bottom inset calculation, [8c7e7a014](https://gitcode.com/openharmony-sig/ohos_react_native/commit/8c7e7a014bc130f23ec9ef01ddb8fc00c0edca76)
- **Trace**: Unified trace tag value, [d7e4e0174](https://gitcode.com/openharmony-sig/ohos_react_native/commit/d7e4e01744c0cbdb4f8e5ab95a901e84d9825e24)
- **Dev Menu**: Fixed the issue where Dev Menu could not be used without RNAbility, [7d794458a](https://gitcode.com/openharmony-sig/ohos_react_native/commit/7d794458aec6aa1ff6f4f22402ffae382aad031f)
- **Platform**: Added isvision property of Platform and returned false, [9129103b5](https://gitcode.com/openharmony-sig/ohos_react_native/commit/9129103b5914ff692f22549a0f94c3512cc5de23)
- **ReactNativeVersion**: Fixed export ReactNativeVersion for test, [79ed89abc](https://gitcode.com/openharmony-sig/ohos_react_native/commit/79ed89abcfd07afcb5b5497badc5b00301fab30e)

### Added
- **DPI**: Added page level DPI control interface, [533a26a82](https://gitcode.com/openharmony-sig/ohos_react_native/commit/533a26a8211d94c78640631ed0508df2edb52a99)
- **ScrollView**: Added support for fadingEdgeLength, [18b45e7b4](https://gitcode.com/openharmony-sig/ohos_react_native/commit/18b45e7b4c0c91ff39ddda0a923181241eb76421)

### Documentation
- **Docs**: Supplemented document description, [65b434a7d](https://gitcode.com/openharmony-sig/ohos_react_native/commit/65b434a7d71cb6a730c3098217c9991b9fd263d1)

### Changed
- **Platform**: Updated platform differences, [203ed27e9](https://gitcode.com/openharmony-sig/ohos_react_native/commit/203ed27e998dcb4e04146bfd83eb801ac2e8c6db)

## [0.82.3] - 2026-01-08

### Fixed
- **Surface**: Fixed crash when surface using destroyed animationDriver, [3477a6516](https://gitcode.com/openharmony-sig/ohos_react_native/commit/3477a651643df920d7651699b7a213ad2da45e71)
- **Image**: Captured image URI by value to avoid crash when JS callback runs after instance destruction, [409e3d355](https://gitcode.com/openharmony-sig/ohos_react_native/commit/409e3d355406c54c30d2bf19d706b15f2dc8e2df)
- **TurboModule**: Fixed memory leak in TurboModule, [c56478622](https://gitcode.com/openharmony-sig/ohos_react_native/commit/c56478622aee23466d20fcc72fee4ea876cf2d64)
- **AnimatedTM**: Fixed crash when AnimatedTM destroyed, [966d5fb27](https://gitcode.com/openharmony-sig/ohos_react_native/commit/966d5fb27a221769f3b71d86b31608479106e8a6)
- **Threading**: Fixed deadlock caused by inconsistent lock acquisition order, [c2815a9a7](https://gitcode.com/openharmony-sig/ohos_react_native/commit/c2815a9a7e5f85a836afe19567b197d0783742aa)
- **Version**: Updated version upgrade document and added known community incompatible changes, [caa7611f9](https://gitcode.com/openharmony-sig/ohos_react_native/commit/caa7611f90f3b31e6d8ec2b793fbef1c24a1e6fb)

### Added
- **Migration**: Migrated modifications from version 0.77 to 0.82, [58f13aeaf](https://gitcode.com/openharmony-sig/ohos_react_native/commit/58f13aeaf49ebcb9efd808e8dcd117660a03723d)

### Documentation
- **Performance**: Added performance optimization guide, [84e1a2d56](https://gitcode.com/openharmony-sig/ohos_react_native/commit/84e1a2d56b23fbb633fca20bc6b53e65990e9465)

[0.82.30]: https://gitcode.com/openharmony-RN/ohos_react_native/compare/v0.82.29...v0.82.30
[0.82.29]: https://gitcode.com/openharmony-RN/ohos_react_native/compare/v0.82.23...v0.82.29