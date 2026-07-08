'use strict';

const { TurboModuleRegistry } = require('react-native');
const { CodedError } = require('expo-modules-core');

const NATIVE_MODULE_NAME = 'ExpoHarmonyImagePicker';
const NATIVE_MODULE = TurboModuleRegistry.get(NATIVE_MODULE_NAME);

function createError(code, message) {
  return new CodedError(code, message);
}

function requireNativeModule(operationName) {
  if (NATIVE_MODULE) {
    return NATIVE_MODULE;
  }

  throw createError(
    'ERR_EXPO_HARMONY_NATIVE_MODULE_MISSING',
    'expo-image-picker expected the ' +
      NATIVE_MODULE_NAME +
      ' TurboModule to be registered, but it was missing while running ' +
      operationName +
      '.',
  );
}

function normalizeNativeError(error) {
  if (error instanceof Error) {
    return error;
  }

  if (error && typeof error === 'object') {
    const code =
      typeof error.code === 'number' || typeof error.code === 'string'
        ? String(error.code)
        : null;
    const message =
      typeof error.message === 'string' && error.message.length > 0
        ? error.message
        : typeof error.name === 'string' && error.name.length > 0
          ? error.name
          : JSON.stringify(error);

    return new Error(code ? '[native:' + code + '] ' + message : message);
  }

  return new Error(String(error));
}

function normalizePickerResult(result) {
  if (!result || result.canceled === true || !Array.isArray(result.assets) || result.assets.length === 0) {
    return {
      canceled: true,
      assets: null,
    };
  }

  return {
    canceled: false,
    assets: result.assets.map((asset) => ({
      uri: String(asset.uri),
      assetId: asset.assetId ?? null,
      width: Number(asset.width ?? 0),
      height: Number(asset.height ?? 0),
      type: asset.type ?? null,
      fileName: asset.fileName ?? null,
      fileSize:
        typeof asset.fileSize === 'number' && Number.isFinite(asset.fileSize)
          ? asset.fileSize
          : null,
      mimeType: asset.mimeType ?? null,
      duration:
        typeof asset.duration === 'number' && Number.isFinite(asset.duration)
          ? asset.duration
          : null,
      exif: asset.exif ?? null,
      base64: asset.base64 ?? null,
    })),
  };
}

async function invokeNative(methodName, operationName, ...args) {
  try {
    return await requireNativeModule(operationName)[methodName](...args);
  } catch (error) {
    throw normalizeNativeError(error);
  }
}

module.exports = {
  MediaTypeOptions: {
    All: 'All',
    Images: 'Images',
    Videos: 'Videos',
  },
  CameraType: {
    front: 'front',
    back: 'back',
  },
  UIImagePickerPresentationStyle: {
    AUTOMATIC: 'automatic',
    FULL_SCREEN: 'fullScreen',
    PAGE_SHEET: 'pageSheet',
    FORM_SHEET: 'formSheet',
    CURRENT_CONTEXT: 'currentContext',
    OVER_FULL_SCREEN: 'overFullScreen',
  },
  async requestCameraPermissionsAsync() {
    return invokeNative(
      'requestCameraPermission',
      'requestCameraPermissionsAsync',
    );
  },
  async requestMediaLibraryPermissionsAsync(writeOnly) {
    return invokeNative(
      'requestMediaLibraryPermission',
      'requestMediaLibraryPermissionsAsync',
      writeOnly === true,
    );
  },
  async getCameraPermissionsAsync() {
    return invokeNative('getCameraPermissionStatus', 'getCameraPermissionsAsync');
  },
  async getMediaLibraryPermissionsAsync(writeOnly) {
    return invokeNative(
      'getMediaLibraryPermissionStatus',
      'getMediaLibraryPermissionsAsync',
      writeOnly === true,
    );
  },
  async launchCameraAsync(options) {
    return normalizePickerResult(
      await invokeNative('launchCamera', 'launchCameraAsync', options ?? {}),
    );
  },
  async launchImageLibraryAsync(options) {
    return normalizePickerResult(
      await invokeNative('launchImageLibrary', 'launchImageLibraryAsync', options ?? {}),
    );
  },
  async getPendingResultAsync() {
    const result = await invokeNative('getPendingResult', 'getPendingResultAsync');
    return result ? normalizePickerResult(result) : null;
  },
};
