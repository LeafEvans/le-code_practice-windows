## 3.6.0

- [Infra] Simplify Harmony CI tasks preparation ([6b793a2](https://github.com/lynx-family/lynx/commit/6b793a2b3b6519042e05850b5ed951d7647c28e2))

- [BugFix][Harmony] Fix DevTool Debug unavailability caused by timing issue in dynamic DevTool import ([86a5a33](https://github.com/lynx-family/lynx/commit/86a5a33d8925a13900d4af3ee5bd64f2832acf9f))

- [Optimize][Harmony] Fix crash caused by asynchronous release of PerformanceControllerHarmonyJSWrapper. ([c79e681](https://github.com/lynx-family/lynx/commit/c79e681287ee08820615f6f351a7fa36c0d12468))

- [Infra] Support harmony release ([5794f64](https://github.com/lynx-family/lynx/commit/5794f64789e38d9aed49b7139b646963eb53d20b))

- [BugFix][Harmony] Fix the issue where the image's `border-radius` and `background-color` do not take effect. ([9148064](https://github.com/lynx-family/lynx/commit/9148064c6949d3c0d7ac61591dabc848beba7e65))

- [Infra] Harmony explorer build cache ([f700e1b](https://github.com/lynx-family/lynx/commit/f700e1bb0a660651499a7ab4940ff8a8c134a741))

- [Optimize][Harmony] Disable byteCodeHar in build profiles ([d5d8e15](https://github.com/lynx-family/lynx/commit/d5d8e15b1b05f368ce584ba066bcc20b3d78f00a))

- [Optimize][Harmony] Simplify napi_env handling in LynxContext ([41a23b5](https://github.com/lynx-family/lynx/commit/41a23b50c47d38209adc0775f86b6f3625bbaad4))

- [Reland][BugFix][Harmony]  Fix the issue that the clip rect did not take effect after the node frame was changed. ([cc5a0a9](https://github.com/lynx-family/lynx/commit/cc5a0a914ae9f0ff3bb361ada6f69c6e92eae549))

- [Infra] temporarily disable harmony tasks ([b426b72](https://github.com/lynx-family/lynx/commit/b426b727f2fd29ce1555fd2709cd2ef635fe0d33))

- [BugFix][Harmony] Fixed Lynx Context.Reload exception return issue. ([b696f12](https://github.com/lynx-family/lynx/commit/b696f12343f3cc2cb2d3ab88eb6c38d45292dc3d))

- [Optimize] Harmony JSVM loaded dynamicly ([1e38d63](https://github.com/lynx-family/lynx/commit/1e38d63ec1ecc9a13019744122a4611f5c0e2614))

- [Optimize][Harmony] Update PATH environment variable in README ([2ae8532](https://github.com/lynx-family/lynx/commit/2ae85328fb584d558cec36bedb603ff54d73017d))

- [BugFix][Harmony] Add fitContentWidth prop to LynxView with corresponding layout logic ([bc8e60d](https://github.com/lynx-family/lynx/commit/bc8e60d314bf0919c369f8b898eede611c4bbd13))

- [BugFix][Harmony] Parsing issues with JSValue and LepusValue ([c986034](https://github.com/lynx-family/lynx/commit/c986034eedd93d2d5497969de1561e4482a29da0))

- [BugFix][Harmony] Fixed Builtin Native Module not being registered ([b9c342a](https://github.com/lynx-family/lynx/commit/b9c342a598961d25ed3cec552b8ced2c3b410f29))

- [Infra] Resume the HarmonyOS CI task ([b4f02d3](https://github.com/lynx-family/lynx/commit/b4f02d3987c147771366ac384ee0742807cc7dda))

- [BugFix][DevTool] Fix missing prompt when enable_devtool is off during HDT debugging of HarmonyOS cards ([7fced04](https://github.com/lynx-family/lynx/commit/7fced041005dd2fb8d8a044a29dcf6d50758e460))

- [BugFix][Harmony][Text] Fix the issue of missing characters during decoding. ([eaa9b9a](https://github.com/lynx-family/lynx/commit/eaa9b9a562a0567abb16ae2e001054f5551348af))

- [Optimize][Harmony] Image supports local resources of the `Resource` type. ([62cfd6f](https://github.com/lynx-family/lynx/commit/62cfd6fe77717bcda52ac08eca3a284788dd0039))

- [Infra] Resume the HarmonyOS publish  CI task ([8724777](https://github.com/lynx-family/lynx/commit/872477725b765a9b5e1e80799c7704e0d66b2159))

- [BugFix][Event] Fix abnormal exposure issue. ([a5ab69d](https://github.com/lynx-family/lynx/commit/a5ab69d5be3740c8e19dbf31c363c786f7e6d389))

- [BugFix][Harmony] Fix the crash caused by the pointer not being set to null after PerformanceController is released. ([b6fefd3](https://github.com/lynx-family/lynx/commit/b6fefd3e3e8cf4417e01e9dfbcf4e8da1df66942))

- [BugFix] Add a check in Mediator to see if LynxActor<PerformanceController> is empty. ([6ea4935](https://github.com/lynx-family/lynx/commit/6ea49353f0427ba0ef320a68da7e7bd572f9c19f))

- [BugFix][Harmony] Add enableAirStrictMode guard for extension modules ([db7219a](https://github.com/lynx-family/lynx/commit/db7219ac0d7f3207bb07e5ae560d5988566aa6ec))

- [Feature][Harmony] Implement ResourcePrefetch for Harmony ([dbaf3fc](https://github.com/lynx-family/lynx/commit/dbaf3fce19c7c69d0eba02ea62a107eda396ede2))

- [Feature][Harmony] Implement LynxAccessibilityModule for Harmony ([393b3a6](https://github.com/lynx-family/lynx/commit/393b3a63adf15013eb6a326fdd5a77964c39443d))

- [Feature][Harmony][LynxRecorder] Harmony supports LynxRecorder ([32a23eb](https://github.com/lynx-family/lynx/commit/32a23eb5e190b80be995269eaf239abb8a0be59f))

- [Optimize][Harmony] Add dev mode support for harmony platform ([8c19d8e](https://github.com/lynx-family/lynx/commit/8c19d8ef1337ee587b9dc007e06de76d09c4a26d))

- [Infra] Support publish dev version for harmony ([6dcc50d](https://github.com/lynx-family/lynx/commit/6dcc50d4b6e841db59588c6f345f58f5128e7ee9))

- [Feature] add LynxContext as params of LynxResourceRequest. ([cd9aa4b](https://github.com/lynx-family/lynx/commit/cd9aa4b3eba75043e23a055c19376a37c1f9c56e))

- [BugFix][Harmony] Lazy bundle should use template fetcher ([ef0ffcf](https://github.com/lynx-family/lynx/commit/ef0ffcf805b3c657e33eac17c8465e674b87264c))

- [BugFix][LynxRecorder][Harmony] Fix the playback failure issue in Harmony caused by missing ignore info ([8c1997e](https://github.com/lynx-family/lynx/commit/8c1997e9111095b0dd8ced8207d7ff687605336d))

- [BugFix][Harmony] Fix `MergeGlobalProps` method by adding early return for invalid input ([5bdfe02](https://github.com/lynx-family/lynx/commit/5bdfe024b8a559c334d93df49b288e432c5a5d06))

- [BugFix][Harmony] Fix sticky info update not responded to scroll-view ([89756a7](https://github.com/lynx-family/lynx/commit/89756a7f5fea54feafbc8b1458c7181873ac5721))

- [BugFix][Harmony] fix the gesture problem of scroll container ([06dff39](https://github.com/lynx-family/lynx/commit/06dff39cc36cf68bd745921c4a79fbe9e8301ee4))

- [BugFix][Harmony] Fix background layer drawing logic to properly handle border radius rendering ([42cafcf](https://github.com/lynx-family/lynx/commit/42cafcf66eb83e1162e23cc3b0a0eec58734a52d))

- [BugFix][Harmony] fix crash when text process truncation ([67631ea](https://github.com/lynx-family/lynx/commit/67631eabd64394b36e1b9d587fa2faaf561fa98d))

- [Feature] LynxBase standalone -- Set up build project for the LynxBase module On Harmony ([cd960ab](https://github.com/lynx-family/lynx/commit/cd960ab007c9d3787402bfebd1f4fd1e0c90776d))

- [BugFix][DevTool] Fix missing devtool resources in HarmonyOS lynx_devtool HAR ([dc29fb6](https://github.com/lynx-family/lynx/commit/dc29fb68412319310c9bc9a3c8be46b17dd1a0dc))

- [BugFix][Harmony] LynxEnv: fix getTracingDirPath ([a6c6d0e](https://github.com/lynx-family/lynx/commit/a6c6d0e900d45869755a0f72005cf2ed1d684e0f))

- [BugFix][Harmony][LynxRecorder] add default value for JsbIgnoredInfo to avoid crash ([ef9b923](https://github.com/lynx-family/lynx/commit/ef9b923ebd478741c5f16c9b5b2bf81dbc3ec76e))

- [Optimize] Add local URL scheme support for cross-platform resource redirection ([c3f8c58](https://github.com/lynx-family/lynx/commit/c3f8c58ce12d29e339fd91cfce508b1076ec2ae1))

- [Optimize][Harmony] Support image decoding of Harmony loacl image resources ([6e7b31c](https://github.com/lynx-family/lynx/commit/6e7b31c30d3677adbaf83b035b1fb7bc46318925))

- [Feature] LynxBase standalone -- Add service registration and environment initialization ([627772e](https://github.com/lynx-family/lynx/commit/627772ed2d53d627f1f4a6377d497a3d015939d3))

- [BugFix][harmony] Fix the issue of the missing Harmony log initialization process. ([618603c](https://github.com/lynx-family/lynx/commit/618603c76239f52ac1aff88cef4bf7114d3cd0dc))

- [Optimize][Harmony] Improve display info management ([f4076cb](https://github.com/lynx-family/lynx/commit/f4076cb5e91bfcec310be9af612a4b98a1689e84))

- [Optimize][Harmony] Support enable jsvm from LynxView ([795e2a2](https://github.com/lynx-family/lynx/commit/795e2a25c7d8c402fc8eccdb3d35c61ff049840e))

- [Feature] LynxBase standalone -- Migrate Lynx Log implementation to the Lynx Base library ([1a9894b](https://github.com/lynx-family/lynx/commit/1a9894b57cf3b1ec17c8652ae965214f724ef709))

- [Optimize][Harmony][ScrollView]BaseScrollView-part3: Implement base scroll view with nested and directional support ([f182c2d](https://github.com/lynx-family/lynx/commit/f182c2df644972994336148b00036cf84e732ccf))

- [BugFix][Harmony] Handle numeric values directly in UpdateCapInsetScale ([5a292c5](https://github.com/lynx-family/lynx/commit/5a292c5f2a1c290fd159e7ddde1e90e96c321969))

- [Feature] LynxBase standalone -- Migrate Lynx Log implementation to the Lynx Base library ([7ae8baa](https://github.com/lynx-family/lynx/commit/7ae8baa7b76463d4137cc0d68520fc13a68010e9))

- [Optimize][Harmony][ScrollView]BaseScrollView-part6: Implement scroll view component with nested scroll support ([a02d3c6](https://github.com/lynx-family/lynx/commit/a02d3c6f77aad15d027c82c09bc9bd3833cbe0a5))

- [Optimize][Harmony][Event] Support for the event-through-active-regions property. ([f48ee20](https://github.com/lynx-family/lynx/commit/f48ee20e3ab74e4879d421ea7e3fb534c9962116))

- [Feature][Harmony] Verify template when lazy bundle loading ([3f4930c](https://github.com/lynx-family/lynx/commit/3f4930c8f99482bb5fedb78b8afbc72f6b22996d))

- [Optimize][Harmony][Event] Support the pointer-events CSS property. ([ad64305](https://github.com/lynx-family/lynx/commit/ad64305b34eb11a76254e808c20c5b4fb7eddd4e))

- [BugFix][Harmony][Image] Fix the issue of base64 image type ([fdd3d83](https://github.com/lynx-family/lynx/commit/fdd3d83605ae767a415df4740d54270f1601f92c))

- [BugFix][DevTool] Fix DevTool QuickJS Toggle Unavailable on HarmonyOS ([0b74163](https://github.com/lynx-family/lynx/commit/0b74163e3b7dcb51a8789c7a72aa0896808adc09))

- [Feature] LynxBase standalone -- Integrate all modules with the standalone LynxBase library ([fdf6ebc](https://github.com/lynx-family/lynx/commit/fdf6ebc36fe225da1b8308c60d9246ede94a136c))

- [BugFix][List][Harmony] Clamp offset to scroll range when calculating item snap's position. ([3581b16](https://github.com/lynx-family/lynx/commit/3581b1687895a4e5482b6cd2785fb9e1e07b8426))

- [Feature][Harmony] support list callbacks in PubLynxContextDelegate ([15c23ad](https://github.com/lynx-family/lynx/commit/15c23ad0d593e702d357eae266adc62cb810391f))

- [Feature][DevTool][Harmony] Provide interfaces to access BTS console messages. ([a8d72d8](https://github.com/lynx-family/lynx/commit/a8d72d803158d2d900f2566d6a8b72ec224ff32f))

- [Feature] LynxBase standalone -- Integrate all modules with the standalone LynxBase library ([e362bc2](https://github.com/lynx-family/lynx/commit/e362bc22ad5bad6331c9511d5307a901fe5474fa))

- [Feature] Support DevTool Module for Harmony ([326f51a](https://github.com/lynx-family/lynx/commit/326f51a67f8f179204fab7204f29b746ecf2076f))

- [Optimize] update latest version for harmony ([e3496ad](https://github.com/lynx-family/lynx/commit/e3496ad7966f2d9c059db2e576ac371986bc995e))

- [Feature] Support headless mode in HarmonyOS. ([c18b45a](https://github.com/lynx-family/lynx/commit/c18b45abc18ba7063fd18f10378409fe5190b490))

- [Optimize] RTS Animation implement part3：Enhance the ability to drive rts animations ([120f30d](https://github.com/lynx-family/lynx/commit/120f30d6dee8ecec32345519b958d4a827a54985))

- [BugFix][Harmony] Fix velocity gesture intercept when enable new gesture ([e86dd0b](https://github.com/lynx-family/lynx/commit/e86dd0be1c2369c3a3f95fe493d92b00550352ea))

- [Optimize][Harmony] Refactor template loading logic for optional params ([bd80b02](https://github.com/lynx-family/lynx/commit/bd80b02ba78350306d40b7e86a4ef45c1ca46a3f))

- [BugFix][Event] Fix the issue where NewGesture failed. ([0c29c21](https://github.com/lynx-family/lynx/commit/0c29c21852eaec6d89afd36f9c50897a79de2836))

- [BugFix][Harmony] Refactor global event handling and add runtime proxy null checks ([21d7879](https://github.com/lynx-family/lynx/commit/21d78790f1327a8a6764d6ab8bc2d532f003a15f))

- [BugFix][List] Fix list pagination scrolling behavior error ([a4656c5](https://github.com/lynx-family/lynx/commit/a4656c536d73cb476594f5a8e6053e7a4681fd7a))

- [BugFix][Gesture][Harmony] Fix defaultGesture scroll conflict and add gesture extra bundle ([ae14bd1](https://github.com/lynx-family/lynx/commit/ae14bd13051ecc2517ac167c5366bdeab66b78eb))

- [BugFix][Harmony] Fix the lynxbase loading failure issue. ([0942367](https://github.com/lynx-family/lynx/commit/0942367f8fc6f7113bcf98e88add734614a23eed))

- [BugFix][Harmony] LynxView: fix templateBundle render error issue ([b8b744d](https://github.com/lynx-family/lynx/commit/b8b744d03fdc02622c1a2ae885c5af57a5b694d1))

- [BugFix][Harmony] clear pending exception after JSVM call failed ([3895b19](https://github.com/lynx-family/lynx/commit/3895b19b5d4f993e1c23b220fa6c482aba197e18))

- [BugFix][Harmony] Refactor overflow clipping implementation in UIBase for Harmony platform ([12b61c1](https://github.com/lynx-family/lynx/commit/12b61c1eeaeeb0df15a6dc8686addf5a552a2cb6))

- [BugFix][Harmony] Fix vertical position error of inline view when setting vertical-align as middle. ([aed49cd](https://github.com/lynx-family/lynx/commit/aed49cd16902cd7039a708219185949692cc4c0e))

- [BugFix][Gesture][Harmony] Fix gesture stop fling will trigger bindtap in harmony ([9f26a05](https://github.com/lynx-family/lynx/commit/9f26a05d8fa8be53b2ae16db779425c5b30e608b))

- [BugFix][Harmony] Self-Adaptation text height when line-height is the default value. ([6b3ac8c](https://github.com/lynx-family/lynx/commit/6b3ac8c5427daabafabab0c09c867728f23f8aea))

- [BugFix][List] Fix list item-snap not work on Harmony platform. ([ee6b7da](https://github.com/lynx-family/lynx/commit/ee6b7da62ff4ac48a651c00ac8b9e35f21042940))

- [BugFix][Harmony] Use weak_ptr for Delegate in NativeModuleHarmony ([7296cdc](https://github.com/lynx-family/lynx/commit/7296cdc76fc73c238c4fa1a011e85781d1cb7806))

- [BugFix][Harmony] Fix shadow node UAF in FontFaceManager ([63c52a0](https://github.com/lynx-family/lynx/commit/63c52a01fb216912f70bdd32416f227ef737b0a1))

- [BugFix][Clay][Headless] Pick historical fixes in headless mode. ([fb11a74](https://github.com/lynx-family/lynx/commit/fb11a744898bbf01d3bc3aeb5c8a0eb6a9201a3a))

- [BugFix][DevTool] Fix the function name’s initial capitalization error in HarmonySessionHandler ([e266108](https://github.com/lynx-family/lynx/commit/e266108276e9e58d0c526c022f610c40e9f20165))

- [BugFix][DevTool] Fix HarmonyOS logbox failing to display error in some scenarios ([f22d026](https://github.com/lynx-family/lynx/commit/f22d026e88e320b5120db27639ca6b545ddf205f))

- [BugFix][FoldView][Test] Fix foldview hitTest not consider overflow and header/slot level ([0c7fe5d](https://github.com/lynx-family/lynx/commit/0c7fe5d0863c088b217eb3059175bcfc5c1dc616))

- [Optimize][Harmony] Optimize image load failure logging ([b43a7ad](https://github.com/lynx-family/lynx/commit/b43a7ad41b4febe37a6bb498907c9ef93dce4ea0))

- [BugFix][Harmony] Remove spread limit for outset shadow to enable complete display ([8215c28](https://github.com/lynx-family/lynx/commit/8215c287f3577596842adf90efdc390742a4c3ff))

- [Feature]optimize pipelineEnd marking logic and extend timing interface for ClayHostPlatformTiming ([e83bccd](https://github.com/lynx-family/lynx/commit/e83bccd1d2875d8800894a174dde1efe44c081ab))

- [Feature][Harmony] Support BackgroundRuntime standalone ([2778388](https://github.com/lynx-family/lynx/commit/2778388224fa3a8d734caba4f91cfc928829f9e2))

- [Feature]optimize pipelineEnd marking logic and extend timing interface for ClayHostPlatformTiming ([beb84d8](https://github.com/lynx-family/lynx/commit/beb84d8c1909c74464dbfd124c6f2ce19d84df5e))

- [BugFix][Harmony] Use postTask instead of postSyncTask to avoid stuck. ([7ba9c46](https://github.com/lynx-family/lynx/commit/7ba9c460f33879731bcc149dc675e541238883dc))

- [Feature][Harmony] TemplateBundle support async decoding ([85d2e85](https://github.com/lynx-family/lynx/commit/85d2e85760cd0fc40510c79b95e08b0f0614e798))

- [Optimize][Harmony] Support multi-ABI builds for Harmony ([6bb17fb](https://github.com/lynx-family/lynx/commit/6bb17fbf5a494a7343037ddf9e4628ede67eb412))

- [BugFix][Harmony] Fix the crash caused by multi-threaded reading and writing of font face. ([15bc314](https://github.com/lynx-family/lynx/commit/15bc314f8c6c2443127654a2a362c1c4ef592d53))

- [BugFix][DevTool] Fix HarmonyOS DevTools reload issue. ([a9d06a6](https://github.com/lynx-family/lynx/commit/a9d06a6188b9db073ad9395868e4458452381ded))

- [Feature][Harmony] Add addLifecycleClient and removeLifecycleClient for LynxBackgroundRuntime ([949fac9](https://github.com/lynx-family/lynx/commit/949fac90f3df4c58a77990bf88c1588904a214bb))

- [Optimize][Harmony]Clear keyboardHeightChangeCallback when unmounting ([fed917a](https://github.com/lynx-family/lynx/commit/fed917a0c8917c1540fe5786daaeb9424ac87a4d))

- [Optimize][Part1] Filter ability Enhance Part1: Support filter: brightness ([af5782c](https://github.com/lynx-family/lynx/commit/af5782c26f9d303b593ebb5f53dc3cecc3cde5de))

- [BugFix][Harmony] Propagate detailed error messages for lazy bundle fetch/verify failures ([c806969](https://github.com/lynx-family/lynx/commit/c806969ddd670d9572167590f5b6dc3462cc4be1))

- [BugFix][Harmony] Fix overlay not hide when remove from parent ([9897675](https://github.com/lynx-family/lynx/commit/9897675655f3785f9dbfcbab0c029a4575ec774b))

- [Optimize][Harmony] Add windowStage storage link and update window handling ([d85da00](https://github.com/lynx-family/lynx/commit/d85da009d9df65836dab148c1f173bee36443df9))

- [BugFix][Harmony][Font] Fix null pointer crash when calling GetTextInfo. ([1aa368b](https://github.com/lynx-family/lynx/commit/1aa368b49ea9ad494103bc93d59a4730c48cdfb6))

- [Infra] Support publish dev version of lynx_base for harmony ([2b69def](https://github.com/lynx-family/lynx/commit/2b69def5134d2f9fbc754413aabc3c37831b7de6))

- [BugFix] Fixes a logic flaw in `LynxEventReporter.ets` on the Harmony platform. ([a9dd105](https://github.com/lynx-family/lynx/commit/a9dd105fe8d7a68ab395ce32b35034a56bb237b2))

- [Infra][Harmony] upgrade harmony sdk to 6.0.0.868 ([de8f3ed](https://github.com/lynx-family/lynx/commit/de8f3ed2542b1cc88eb3a50f55b233dddc0a092d))

- [Optimize] Optimize for shorthand style on android && harmony. ([121be02](https://github.com/lynx-family/lynx/commit/121be021c883ccff0eafce41e62355b61338b3d7))

- [BugFix][Harmony] Correct LynxView first-screen initialization timing ([bdde705](https://github.com/lynx-family/lynx/commit/bdde7056074a4ea217aef9cd4d085078aa15d40d))

- [Feature][Harmony] Add conic (sweep) gradient background support ([b2cb167](https://github.com/lynx-family/lynx/commit/b2cb167dd25ff405648decb1c2503ec75c957d8b))

- [Optimize][Overlay] Harmony Overlay refactoring based on OverlayManager ([652b621](https://github.com/lynx-family/lynx/commit/652b62183b9538a504bf9264748949a728b1b237))

- [Optimize][Types] Add ScrollView.getScrollInfo UI method with typed callback ([b246d00](https://github.com/lynx-family/lynx/commit/b246d00aaa18f84e5271c061debde45b785d3814))

- [Infra][Harmony] support multiple sdk version ([29d4a36](https://github.com/lynx-family/lynx/commit/29d4a36ca18e06e4690539f40d3265ca517a513d))

- [Optimize][Harmony] Support delegate gesture ([ebdbb65](https://github.com/lynx-family/lynx/commit/ebdbb65e5eaa74237c6f1329ee4f509e5971f16e))

- [Refactor][Layout] Unify layout scheduling and introduce LynxLayoutProxy across platforms ([6cad114](https://github.com/lynx-family/lynx/commit/6cad114b6485bfe3d4863dda0be2c0e4ae004ed2))

- [BugFix] harmony longpress not initial with bindLongPress Event fail ([71a06a3](https://github.com/lynx-family/lynx/commit/71a06a3dba4958c51f1c6d43414e84e3c53045e7))

- [BugFix][Harmony] Add NapiHandleScope to ensure valid N-API handle lifetimes ([705fedc](https://github.com/lynx-family/lynx/commit/705fedc10b153d7b124257b0081d2b1524aa1593))

- [BugFix][Harmony][Overlay] Stabilize overlay show/dismiss lifecycle and gesture target restoration ([55a1e84](https://github.com/lynx-family/lynx/commit/55a1e84de08a04b67ed0331de2d6c9ddced55423))

- [BugFix][Harmony] include lynx_actor_specialization.h where lynx_actor.h is dependent. ([c3cbbd7](https://github.com/lynx-family/lynx/commit/c3cbbd73f51455dada9f8bbf3caebc75ee66c5dd))

- [Optimize] Use RunNowOrPostTask to ensure UI thread execution for callbacks ([4b9bdab](https://github.com/lynx-family/lynx/commit/4b9bdabd9072efdd3090bb6c143807007c7f7b69))

- [Optimize][Config] Switch to pathlib, validate version fields, and improve config/type/doc generation ([1b94fdf](https://github.com/lynx-family/lynx/commit/1b94fdf9c85097ee1fe07ce563fd8fe56a3a6be2))

- [Optimize][Harmony] Add custom "tag" property to ArkUI nodes in UIBase ([80cf3d2](https://github.com/lynx-family/lynx/commit/80cf3d2d42b2ff89446571b915f93cbba3c56d36))

- [BugFix][Harmony] Make LynxView, renderer, and owners optional and guard null accesses ([c7a15a5](https://github.com/lynx-family/lynx/commit/c7a15a5b4d3acaf7997ce0beb34491a6d670b255))

- [Infra] Check jq command exist before harmony release ([f210b95](https://github.com/lynx-family/lynx/commit/f210b95bcb720c63148de6329f31732ffab11f43))
