'use strict';

const { TurboModuleRegistry } = require('react-native');
const { CodedError } = require('expo-modules-core');

const NATIVE_MODULE_NAME = 'ExpoHarmonyLocation';
const NATIVE_MODULE = TurboModuleRegistry.get(NATIVE_MODULE_NAME);

function createError(code, message) {
  return new CodedError(code, message);
}

function createUnsupportedError(operationName) {
  return createError(
    'ERR_EXPO_HARMONY_UNSUPPORTED',
    'expo-location does not implement ' + operationName + ' on HarmonyOS yet.',
  );
}

function requireNativeModule(operationName) {
  if (NATIVE_MODULE) {
    return NATIVE_MODULE;
  }

  throw createError(
    'ERR_EXPO_HARMONY_NATIVE_MODULE_MISSING',
    'expo-location expected the ' +
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
    status: permissionResponse?.status ?? 'undetermined',
    granted: permissionResponse?.granted === true,
    canAskAgain: permissionResponse?.canAskAgain !== false,
    expires: permissionResponse?.expires ?? 'never',
    android: permissionResponse?.android ?? { accuracy: 'none' },
    ios: permissionResponse?.ios ?? null,
  };
}

function normalizeLocationObject(location) {
  return {
    coords: {
      latitude: Number(location?.coords?.latitude ?? 0),
      longitude: Number(location?.coords?.longitude ?? 0),
      altitude:
        typeof location?.coords?.altitude === 'number' ? location.coords.altitude : null,
      accuracy:
        typeof location?.coords?.accuracy === 'number' ? location.coords.accuracy : null,
      altitudeAccuracy:
        typeof location?.coords?.altitudeAccuracy === 'number'
          ? location.coords.altitudeAccuracy
          : null,
      heading: typeof location?.coords?.heading === 'number' ? location.coords.heading : null,
      speed: typeof location?.coords?.speed === 'number' ? location.coords.speed : null,
    },
    timestamp: Number(location?.timestamp ?? Date.now()),
    mocked: location?.mocked === true,
  };
}

function normalizeProviderStatus(providerStatus) {
  return {
    locationServicesEnabled: providerStatus?.locationServicesEnabled === true,
    backgroundModeEnabled: providerStatus?.backgroundModeEnabled === true,
    gpsAvailable: providerStatus?.gpsAvailable === true,
    networkAvailable: providerStatus?.networkAvailable === true,
    passiveAvailable: providerStatus?.passiveAvailable === true,
  };
}

function normalizeReverseGeocodeResult(address) {
  return {
    city: address?.city ?? null,
    district: address?.district ?? null,
    streetNumber: address?.streetNumber ?? null,
    street: address?.street ?? null,
    region: address?.region ?? null,
    subregion: address?.subregion ?? null,
    country: address?.country ?? null,
    postalCode: address?.postalCode ?? null,
    name: address?.name ?? null,
    isoCountryCode: address?.isoCountryCode ?? null,
    timezone: address?.timezone ?? null,
    formattedAddress: address?.formattedAddress ?? null,
  };
}

function normalizeGeocodeInput(address) {
  if (typeof address === 'string') {
    return address.trim();
  }

  if (!address || typeof address !== 'object') {
    return '';
  }

  const parts = [
    address.name,
    address.streetNumber,
    address.street,
    address.district,
    address.city,
    address.region,
    address.postalCode,
    address.country,
  ]
    .filter((part) => typeof part === 'string' && part.trim().length > 0)
    .map((part) => part.trim());

  return parts.join(', ');
}

function normalizeGeocodeResults(results) {
  if (!Array.isArray(results)) {
    return [];
  }

  return results.map((result) => ({
    latitude: Number(result?.latitude ?? 0),
    longitude: Number(result?.longitude ?? 0),
    altitude: typeof result?.altitude === 'number' ? result.altitude : null,
    accuracy: typeof result?.accuracy === 'number' ? result.accuracy : null,
  }));
}

function normalizeHeadingObject(heading) {
  return {
    magHeading: Number(heading?.magHeading ?? 0),
    trueHeading:
      typeof heading?.trueHeading === 'number' && Number.isFinite(heading.trueHeading)
        ? heading.trueHeading
        : null,
    accuracy:
      typeof heading?.accuracy === 'number' && Number.isFinite(heading.accuracy)
        ? heading.accuracy
        : 0,
  };
}

function createSubscription(remove) {
  let active = true;

  return {
    remove() {
      if (!active) {
        return;
      }

      active = false;
      remove();
    },
  };
}

module.exports = {
  Accuracy: {
    Lowest: 1,
    Low: 2,
    Balanced: 3,
    High: 4,
    Highest: 5,
    BestForNavigation: 6,
  },
  PermissionStatus: {
    DENIED: 'denied',
    GRANTED: 'granted',
    UNDETERMINED: 'undetermined',
  },
  async getForegroundPermissionsAsync() {
    return normalizePermissionResponse(
      await invokeNative(
        'getForegroundPermissionStatus',
        'getForegroundPermissionsAsync',
      ),
    );
  },
  async requestForegroundPermissionsAsync() {
    return normalizePermissionResponse(
      await invokeNative(
        'requestForegroundPermission',
        'requestForegroundPermissionsAsync',
      ),
    );
  },
  async getBackgroundPermissionsAsync() {
    return normalizePermissionResponse(
      await invokeNative(
        'getBackgroundPermissionStatus',
        'getBackgroundPermissionsAsync',
      ),
    );
  },
  async requestBackgroundPermissionsAsync() {
    return normalizePermissionResponse(
      await invokeNative(
        'requestBackgroundPermission',
        'requestBackgroundPermissionsAsync',
      ),
    );
  },
  async hasServicesEnabledAsync() {
    return await invokeNative('hasServicesEnabled', 'hasServicesEnabledAsync');
  },
  async getProviderStatusAsync() {
    return normalizeProviderStatus(
      await invokeNative('getProviderStatus', 'getProviderStatusAsync'),
    );
  },
  async getCurrentPositionAsync(options) {
    return normalizeLocationObject(
      await invokeNative('getCurrentPosition', 'getCurrentPositionAsync', options ?? {}),
    );
  },
  async getLastKnownPositionAsync(options) {
    const location = await invokeNative(
      'getLastKnownPosition',
      'getLastKnownPositionAsync',
      options ?? {},
    );
    return location ? normalizeLocationObject(location) : null;
  },
  async geocodeAsync(address) {
    return normalizeGeocodeResults(
      await invokeNative(
        'geocode',
        'geocodeAsync',
        normalizeGeocodeInput(address),
      ),
    );
  },
  async reverseGeocodeAsync(location) {
    const results = await invokeNative(
      'reverseGeocode',
      'reverseGeocodeAsync',
      {
        latitude: Number(location?.latitude ?? 0),
        longitude: Number(location?.longitude ?? 0),
      },
    );

    if (!Array.isArray(results)) {
      return [];
    }

    return results.map(normalizeReverseGeocodeResult);
  },
  async watchPositionAsync(options, callback, errorHandler) {
    if (typeof callback !== 'function') {
      throw createError(
        'ERR_EXPO_HARMONY_INVALID_LISTENER',
        'expo-location expected watchPositionAsync to receive a callback.',
      );
    }

    try {
      const watchResult = await invokeNative(
        'startWatchPosition',
        'watchPositionAsync',
        options ?? {},
        null,
      );
      const watchId =
        typeof watchResult?.watchId === 'number' ? watchResult.watchId : Number(Date.now());

      if (watchResult?.initialLocation) {
        callback(normalizeLocationObject(watchResult.initialLocation));
      }

      return createSubscription(() => {
        void invokeNative(
          'stopWatchPosition',
          'Location.watchPositionAsync.remove',
          watchId,
        ).catch(() => {});
      });
    } catch (error) {
      if (typeof errorHandler === 'function') {
        errorHandler(error);
      }

      throw error;
    }
  },
  async watchHeadingAsync(callback) {
    if (typeof callback !== 'function') {
      throw createError(
        'ERR_EXPO_HARMONY_INVALID_LISTENER',
        'expo-location expected watchHeadingAsync to receive a callback.',
      );
    }

    const watchResult = await invokeNative(
      'startWatchHeading',
      'watchHeadingAsync',
      null,
    );
    const watchId =
      typeof watchResult?.watchId === 'number' ? watchResult.watchId : Number(Date.now());

    if (watchResult?.initialHeading) {
      callback(normalizeHeadingObject(watchResult.initialHeading));
    }

    return createSubscription(() => {
      void invokeNative(
        'stopWatchHeading',
        'Location.watchHeadingAsync.remove',
        watchId,
      ).catch(() => {});
    });
  },
  async getHeadingAsync() {
    return normalizeHeadingObject(
      await invokeNative('getHeading', 'getHeadingAsync'),
    );
  },
};
