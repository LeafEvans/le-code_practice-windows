'use strict';

const { TurboModuleRegistry } = require('react-native');
const { CodedError } = require('expo-modules-core');

const FILE_SCHEME = 'file://';
const NATIVE_MODULE_NAME = 'ExpoHarmonyFileSystem';
const NATIVE_MODULE = TurboModuleRegistry.get(NATIVE_MODULE_NAME);
const NATIVE_CONSTANTS = NATIVE_MODULE?.getConstants ? NATIVE_MODULE.getConstants() : {};

function createError(code, message) {
  return new CodedError(code, message);
}

function requireNativeModule(operationName) {
  if (NATIVE_MODULE) {
    return NATIVE_MODULE;
  }

  throw createError(
    'ERR_EXPO_HARMONY_NATIVE_MODULE_MISSING',
    'expo-file-system expected the ' +
      NATIVE_MODULE_NAME +
      ' TurboModule to be registered, but it was missing while running ' +
      operationName +
      '.',
  );
}

function createUnsupportedError(operationName) {
  return createError(
    'ERR_EXPO_HARMONY_UNSUPPORTED',
    'expo-file-system currently supports UTF-8 sandbox file operations only. Unsupported operation: ' +
      operationName +
      '.',
  );
}

function toFileUri(pathValue, ensureTrailingSlash) {
  if (typeof pathValue !== 'string' || pathValue.length === 0) {
    return null;
  }

  const normalizedPath = pathValue.startsWith(FILE_SCHEME)
    ? pathValue.slice(FILE_SCHEME.length)
    : pathValue;
  const withScheme = FILE_SCHEME + normalizedPath;

  if (!ensureTrailingSlash) {
    return withScheme;
  }

  let normalizedSchemePath = withScheme;

  while (normalizedSchemePath.endsWith('/')) {
    normalizedSchemePath = normalizedSchemePath.slice(0, -1);
  }

  return normalizedSchemePath + '/';
}

function normalizeInputPath(inputPath) {
  if (typeof inputPath !== 'string' || inputPath.length === 0) {
    throw createError(
      'ERR_EXPO_HARMONY_INVALID_URI',
      'expo-file-system expected a non-empty file URI.',
    );
  }

  const normalizedPath = inputPath.startsWith(FILE_SCHEME)
    ? inputPath.slice(FILE_SCHEME.length)
    : inputPath;

  if (!normalizedPath.startsWith('/')) {
    throw createError(
      'ERR_EXPO_HARMONY_INVALID_URI',
      'expo-file-system supports only absolute file:// URIs inside the app sandbox.',
    );
  }

  if (
    normalizedPath.includes('/../') ||
    normalizedPath.endsWith('/..') ||
    normalizedPath.includes('/./')
  ) {
    throw createError(
      'ERR_EXPO_HARMONY_INVALID_URI',
      'expo-file-system does not accept relative path segments.',
    );
  }

  return normalizedPath;
}

function normalizeStringEncoding(rawEncoding) {
  if (rawEncoding == null || rawEncoding === 'utf8') {
    return 'utf8';
  }

  if (rawEncoding === 'base64') {
    return 'base64';
  }

  throw createUnsupportedError('encoding=' + String(rawEncoding));
}

function normalizeFileDownloadResult(result, requestedUri) {
  return {
    uri: result?.uri ?? String(requestedUri),
    status:
      typeof result?.status === 'number' && Number.isFinite(result.status)
        ? result.status
        : 200,
    headers: result?.headers && typeof result.headers === 'object' ? result.headers : {},
    md5: typeof result?.md5 === 'string' ? result.md5 : undefined,
  };
}

function normalizeFileInfoResult(requestedUri, nativeResult) {
  if (!nativeResult || nativeResult.exists !== true) {
    return {
      exists: false,
      isDirectory: false,
      uri: String(requestedUri),
    };
  }

  const normalizedResult = {
    exists: true,
    uri: toFileUri(nativeResult.path, false) ?? String(requestedUri),
    size: Number(nativeResult.size ?? 0),
    isDirectory: nativeResult.isDirectory === true,
    modificationTime: Number(nativeResult.modificationTime ?? 0),
  };

  if (typeof nativeResult.md5 === 'string' && nativeResult.md5.length > 0) {
    normalizedResult.md5 = nativeResult.md5;
  }

  return normalizedResult;
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

module.exports = {
  documentDirectory: toFileUri(NATIVE_CONSTANTS.documentDirectoryPath, true),
  cacheDirectory: toFileUri(NATIVE_CONSTANTS.cacheDirectoryPath, true),
  bundleDirectory: toFileUri(NATIVE_CONSTANTS.bundleDirectoryPath, true),
  EncodingType: {
    UTF8: 'utf8',
    Base64: 'base64',
  },
  FileSystemSessionType: {
    BACKGROUND: 0,
    FOREGROUND: 1,
  },
  async getInfoAsync(fileUri, options) {
    const normalizedPath = normalizeInputPath(fileUri);
    try {
      const result = await requireNativeModule('getInfoAsync').getInfo(normalizedPath, {
        md5: options?.md5 === true,
      });
      return normalizeFileInfoResult(fileUri, result);
    } catch (error) {
      throw normalizeNativeError(error);
    }
  },
  async readAsStringAsync(fileUri, options) {
    const normalizedPath = normalizeInputPath(fileUri);
    try {
      return await requireNativeModule('readAsStringAsync').readAsString(normalizedPath, {
        encoding: normalizeStringEncoding(options?.encoding),
        position: options?.position,
        length: options?.length,
      });
    } catch (error) {
      throw normalizeNativeError(error);
    }
  },
  async writeAsStringAsync(fileUri, contents, options) {
    const normalizedPath = normalizeInputPath(fileUri);
    try {
      await requireNativeModule('writeAsStringAsync').writeAsString(
        normalizedPath,
        String(contents),
        {
          encoding: normalizeStringEncoding(options?.encoding),
          append: options?.append === true,
        },
      );
    } catch (error) {
      throw normalizeNativeError(error);
    }
  },
  async deleteAsync(fileUri, options) {
    const normalizedPath = normalizeInputPath(fileUri);
    try {
      await requireNativeModule('deleteAsync').deletePath(normalizedPath, {
        idempotent: options?.idempotent === true,
      });
    } catch (error) {
      throw normalizeNativeError(error);
    }
  },
  async makeDirectoryAsync(fileUri, options) {
    const normalizedPath = normalizeInputPath(fileUri);
    try {
      await requireNativeModule('makeDirectoryAsync').makeDirectory(normalizedPath, {
        intermediates: options?.intermediates === true,
      });
    } catch (error) {
      throw normalizeNativeError(error);
    }
  },
  async readDirectoryAsync(fileUri) {
    const normalizedPath = normalizeInputPath(fileUri);
    try {
      return await requireNativeModule('readDirectoryAsync').readDirectory(normalizedPath);
    } catch (error) {
      throw normalizeNativeError(error);
    }
  },
  async copyAsync(options) {
    const fromPath = normalizeInputPath(options?.from);
    const toPath = normalizeInputPath(options?.to);
    try {
      await requireNativeModule('copyAsync').copy(fromPath, toPath);
    } catch (error) {
      throw normalizeNativeError(error);
    }
  },
  async moveAsync(options) {
    const fromPath = normalizeInputPath(options?.from);
    const toPath = normalizeInputPath(options?.to);
    try {
      await requireNativeModule('moveAsync').move(fromPath, toPath);
    } catch (error) {
      throw normalizeNativeError(error);
    }
  },
  async downloadAsync(url, fileUri, options) {
    const normalizedPath = normalizeInputPath(fileUri);
    try {
      return normalizeFileDownloadResult(
        await requireNativeModule('downloadAsync').download(
          String(url),
          normalizedPath,
          {
            headers: options?.headers ?? {},
            md5: options?.md5 === true,
          },
        ),
        fileUri,
      );
    } catch (error) {
      throw normalizeNativeError(error);
    }
  },
};
