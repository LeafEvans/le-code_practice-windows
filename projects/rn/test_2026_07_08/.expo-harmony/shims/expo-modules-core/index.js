'use strict';

const { Linking, Platform } = require('react-native');

const embeddedExpoConfig = {
  "name": "记账 · Expense Tracker",
  "slug": "expense-tracker",
  "version": "1.0.0",
  "orientation": "portrait",
  "icon": "./assets/icon.png",
  "userInterfaceStyle": "light",
  "scheme": "expense-tracker",
  "ios": {
    "supportsTablet": true,
    "bundleIdentifier": "com.example.expensetracker"
  },
  "android": {
    "package": "com.example.expensetracker",
    "adaptiveIcon": {
      "backgroundColor": "#E6F4FE",
      "foregroundImage": "./assets/android-icon-foreground.png",
      "backgroundImage": "./assets/android-icon-background.png",
      "monochromeImage": "./assets/android-icon-monochrome.png"
    },
    "predictiveBackGestureEnabled": false
  },
  "web": {
    "favicon": "./assets/favicon.png"
  },
  "plugins": [
    "expo-router"
  ],
  "sdkVersion": "55.0.0",
  "platforms": [
    "ios",
    "android",
    "web"
  ],
  "extra": {
    "router": {}
  }
};
const nativeModules = Object.create(null);

class EventSubscription {
  constructor(remove) {
    this._remove = remove;
  }

  remove() {
    if (!this._remove) {
      return;
    }

    const remove = this._remove;
    this._remove = null;
    remove();
  }
}

class EventEmitter {
  constructor() {
    this._listeners = new Map();
  }

  addListener(eventName, listener) {
    const listeners = this._listeners.get(eventName) ?? new Set();
    listeners.add(listener);
    this._listeners.set(eventName, listeners);

    return new EventSubscription(() => {
      listeners.delete(listener);

      if (listeners.size === 0) {
        this._listeners.delete(eventName);
      }
    });
  }

  removeAllListeners(eventName) {
    if (typeof eventName === 'string') {
      this._listeners.delete(eventName);
      return;
    }

    this._listeners.clear();
  }

  emit(eventName, payload) {
    const listeners = this._listeners.get(eventName);

    if (!listeners) {
      return;
    }

    for (const listener of listeners) {
      listener(payload);
    }
  }
}

class LegacyEventEmitter extends EventEmitter {}

class NativeModule extends EventEmitter {}

class SharedObject {}

class SharedRef extends SharedObject {}

class CodedError extends Error {
  constructor(code, message) {
    super(message);
    this.code = code;
    this.name = 'CodedError';
  }
}

class UnavailabilityError extends CodedError {
  constructor(moduleName, propertyName) {
    super(
      'ERR_UNAVAILABLE',
      propertyName
        ? moduleName + '.' + propertyName + ' is not available on Harmony.'
        : moduleName + ' is not available on Harmony.',
    );
    this.name = 'UnavailabilityError';
  }
}

class ExpoLinkingModule extends NativeModule {
  constructor(initialUrl) {
    super();
    this._currentUrl = initialUrl;
  }

  getLinkingURL() {
    return this._currentUrl;
  }

  _setCurrentUrl(url) {
    this._currentUrl = url;
    this.emit('onURLReceived', {
      url,
    });
  }
}

const expoLinkingModule = new ExpoLinkingModule("expense-tracker://");

if (Linking?.addEventListener) {
  Linking.addEventListener('url', (event) => {
    expoLinkingModule._setCurrentUrl(event?.url ?? null);
  });
}

nativeModules.ExpoLinking = expoLinkingModule;
nativeModules.ExponentConstants = {
  manifest: embeddedExpoConfig,
  appOwnership: null,
  executionEnvironment: 'standalone',
  experienceUrl: "expense-tracker://",
  linkingUri: "expense-tracker://",
  statusBarHeight: 0,
  systemVersion: 'HarmonyOS',
  platform: {
    android: embeddedExpoConfig.android ?? null,
    ios: embeddedExpoConfig.ios ?? null,
    web: null,
  },
};
nativeModules.ExpoAsset = {
  async downloadAsync(url) {
    return url;
  },
};
nativeModules.ExpoFetchModule = {
  NativeRequest: class NativeRequest {
    constructor(_response) {
      this._response = _response;
    }

    async start() {
      throw new UnavailabilityError('ExpoFetchModule', 'NativeRequest.start');
    }

    cancel() {}
  },
};

function requireOptionalNativeModule(name) {
  return nativeModules[name] ?? null;
}

function requireNativeModule(name) {
  const nativeModule = requireOptionalNativeModule(name);

  if (nativeModule) {
    return nativeModule;
  }

  throw new UnavailabilityError(name);
}

function requireNativeViewManager(name) {
  throw new UnavailabilityError(name, 'viewManager');
}

function registerWebModule() {}

async function reloadAppAsync() {}

function installOnUIRuntime() {}

globalThis.expo = {
  ...(globalThis.expo ?? {}),
  EventEmitter,
  LegacyEventEmitter,
  NativeModule,
  SharedObject,
  SharedRef,
  modules: {
    ...(globalThis.expo?.modules ?? {}),
    ...nativeModules,
  },
};

module.exports = {
  Platform,
  CodedError,
  UnavailabilityError,
  EventEmitter,
  LegacyEventEmitter,
  NativeModule,
  SharedObject,
  SharedRef,
  requireNativeModule,
  requireOptionalNativeModule,
  requireNativeViewManager,
  registerWebModule,
  reloadAppAsync,
  installOnUIRuntime,
};
