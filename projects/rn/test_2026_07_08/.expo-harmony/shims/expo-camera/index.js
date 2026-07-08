'use strict';

const React = require('react');
const { TurboModuleRegistry, requireNativeComponent } = require('react-native');
const { CodedError } = require('expo-modules-core');

const NATIVE_MODULE_NAME = 'ExpoHarmonyCamera';
const NATIVE_MODULE = TurboModuleRegistry.get(NATIVE_MODULE_NAME);
const NativeCameraView = requireNativeComponent('ExpoHarmonyCameraView');
const DEFAULT_PERMISSION_RESPONSE = {
  status: 'undetermined',
  granted: false,
  canAskAgain: true,
  expires: 'never',
};
let nextCameraViewId = 1;

function createError(code, message) {
  return new CodedError(code, message);
}

function createUnsupportedError(operationName) {
  return createError(
    'ERR_EXPO_HARMONY_UNSUPPORTED',
    'expo-camera does not implement ' + operationName + ' on HarmonyOS yet.',
  );
}

function requireNativeModule(operationName) {
  if (NATIVE_MODULE) {
    return NATIVE_MODULE;
  }

  throw createError(
    'ERR_EXPO_HARMONY_NATIVE_MODULE_MISSING',
    'expo-camera expected the ' +
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

async function invokeNative(methodName, operationName, ...args) {
  try {
    return await requireNativeModule(operationName)[methodName](...args);
  } catch (error) {
    throw normalizeNativeError(error);
  }
}

function normalizePermissionResponse(permissionResponse) {
  return {
    status: permissionResponse?.status ?? DEFAULT_PERMISSION_RESPONSE.status,
    granted: permissionResponse?.granted === true,
    canAskAgain: permissionResponse?.canAskAgain !== false,
    expires: permissionResponse?.expires ?? DEFAULT_PERMISSION_RESPONSE.expires,
  };
}

function normalizeCameraFacing(facing) {
  return facing === 'front' ? 'front' : 'back';
}

const CameraView = React.forwardRef(function ExpoHarmonyCameraView(props, ref) {
  const viewIdRef = React.useRef(null);

  if (!viewIdRef.current) {
    viewIdRef.current = 'expo-harmony-camera-view-' + String(nextCameraViewId++);
  }

  const viewId = viewIdRef.current;

  React.useEffect(() => {
    void invokeNative('createPreview', 'CameraView.mount', {
      viewId,
      facing: normalizeCameraFacing(props.facing),
      mode: props.mode ?? 'picture',
    }).catch(() => {});

    return () => {
      void invokeNative('disposePreview', 'CameraView.unmount', {
        viewId,
      }).catch(() => {});
    };
  }, [props.facing, props.mode, viewId]);

  React.useImperativeHandle(
    ref,
    () => ({
      async takePictureAsync(options) {
        return invokeNative('takePicture', 'CameraView.takePictureAsync', {
          viewId,
          cameraType: normalizeCameraFacing(props.facing),
          ...options,
        });
      },
      async pausePreview() {
        return invokeNative('pausePreview', 'CameraView.pausePreview', {
          viewId,
        });
      },
      async resumePreview() {
        return invokeNative('resumePreview', 'CameraView.resumePreview', {
          viewId,
        });
      },
      async getAvailablePictureSizesAsync() {
        throw createUnsupportedError('CameraView.getAvailablePictureSizesAsync');
      },
      async getAvailableLensesAsync() {
        throw createUnsupportedError('CameraView.getAvailableLensesAsync');
      },
      async recordAsync(options) {
        return invokeNative('startRecording', 'CameraView.recordAsync', {
          viewId,
          cameraType: normalizeCameraFacing(props.facing),
          ...options,
        });
      },
      async stopRecording() {
        return invokeNative('stopRecording', 'CameraView.stopRecording', {
          viewId,
        });
      },
      async toggleRecordingAsync(options) {
        return invokeNative('toggleRecording', 'CameraView.toggleRecordingAsync', {
          viewId,
          cameraType: normalizeCameraFacing(props.facing),
          ...options,
        });
      },
    }),
    [props.facing, viewId],
  );

  return React.createElement(NativeCameraView, {
    ...props,
    viewId,
    facing: normalizeCameraFacing(props.facing),
    accessibilityLabel: props.accessibilityLabel ?? 'Expo Harmony embedded camera preview',
    style: [
      {
        minHeight: 220,
        overflow: 'hidden',
        backgroundColor: '#111827',
      },
      props.style,
    ],
  });
});

CameraView.displayName = 'ExpoHarmonyCameraView';

async function getCameraPermissionsAsync() {
  return normalizePermissionResponse(
    await invokeNative('getCameraPermissionStatus', 'getCameraPermissionsAsync'),
  );
}

async function requestCameraPermissionsAsync() {
  return normalizePermissionResponse(
    await invokeNative('requestCameraPermission', 'requestCameraPermissionsAsync'),
  );
}

async function getMicrophonePermissionsAsync() {
  return normalizePermissionResponse(
    await invokeNative('getMicrophonePermissionStatus', 'getMicrophonePermissionsAsync'),
  );
}

async function requestMicrophonePermissionsAsync() {
  return normalizePermissionResponse(
    await invokeNative('requestMicrophonePermission', 'requestMicrophonePermissionsAsync'),
  );
}

module.exports = {
  CameraType: {
    front: 'front',
    back: 'back',
  },
  FlashMode: {
    off: 'off',
    on: 'on',
    auto: 'auto',
    torch: 'torch',
  },
  CameraView,
  Camera: {
    CameraType: {
      front: 'front',
      back: 'back',
    },
    Constants: {
      Type: {
        front: 'front',
        back: 'back',
      },
      FlashMode: {
        off: 'off',
        on: 'on',
        auto: 'auto',
        torch: 'torch',
      },
    },
    getCameraPermissionsAsync,
    requestCameraPermissionsAsync,
    getMicrophonePermissionsAsync,
    requestMicrophonePermissionsAsync,
  },
  getCameraPermissionsAsync,
  requestCameraPermissionsAsync,
  getMicrophonePermissionsAsync,
  requestMicrophonePermissionsAsync,
  async scanFromURLAsync() {
    throw createUnsupportedError('scanFromURLAsync');
  },
};
