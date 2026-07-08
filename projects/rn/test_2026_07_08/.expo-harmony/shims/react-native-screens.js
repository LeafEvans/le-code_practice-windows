// Minimal shim for react-native-screens on HarmonyOS
// Provides enough surface for expo-router to bundle without errors

const noop = () => undefined;

export const Screen = null;
export const ScreenStack = null;
export const ScreenStackHeaderConfig = null;
export const ScreenStackHeaderBackButtonImage = null;
export const ScreenStackHeaderRightView = null;
export const ScreenStackHeaderLeftView = null;
export const ScreenStackHeaderCenterView = null;
export const ScreenStackHeaderSearchBarView = null;
export const SearchBar = null;

export const enableScreens = noop;
export const screensEnabled = () => false;
export const NativeScreen = null;
export const NativeScreenContainer = null;
export const NativeScreenNavigationContainer = null;

export default {
  enableScreens,
  screensEnabled,
  Screen,
  ScreenStack,
  ScreenStackHeaderConfig,
  SearchBar,
};
