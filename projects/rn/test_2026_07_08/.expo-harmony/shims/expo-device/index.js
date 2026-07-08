'use strict';

const DeviceType = {
  UNKNOWN: 0,
  PHONE: 1,
  TABLET: 2,
  DESKTOP: 3,
  TV: 4,
};

async function getDeviceTypeAsync() {
  return DeviceType.UNKNOWN;
}

module.exports = {
  DeviceType,
  brand: 'OpenHarmony',
  manufacturer: 'OpenHarmony',
  modelName: 'Harmony preview device',
  modelId: null,
  designName: null,
  productName: 'expo-harmony-preview',
  deviceYearClass: null,
  totalMemory: null,
  supportedCpuArchitectures: [],
  osName: 'HarmonyOS',
  osVersion: 'preview',
  osBuildId: null,
  osInternalBuildId: null,
  osBuildFingerprint: null,
  platformApiLevel: null,
  deviceName: 'Harmony preview device',
  isDevice: true,
  getDeviceTypeAsync,
};
