'use strict';

const { CodedError } = require('expo-modules-core');

function createPreviewError() {
  return new CodedError(
    'ERR_EXPO_HARMONY_PREVIEW',
    'expo-media-library is classified as experimental for Harmony, but no managed runtime shim has been wired yet.',
  );
}

function unavailable() {
  throw createPreviewError();
}

module.exports = new Proxy(
  {},
  {
    get(_target, propertyName) {
      if (propertyName === '__esModule') {
        return true;
      }

      return unavailable;
    },
  },
);
