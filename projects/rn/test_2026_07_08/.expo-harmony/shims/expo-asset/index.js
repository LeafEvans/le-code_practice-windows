'use strict';

class Asset {
  constructor(input) {
    this.name = input.name ?? null;
    this.type = input.type ?? null;
    this.hash = input.hash ?? null;
    this.uri = input.uri;
    this.localUri = input.localUri ?? input.uri;
    this.width = input.width ?? null;
    this.height = input.height ?? null;
    this.downloaded = Boolean(input.downloaded);
  }

  static fromURI(uri) {
    return new Asset({
      name: String(uri).split('/').pop() || 'remote-asset',
      uri: String(uri),
      downloaded: true,
    });
  }

  static fromModule(moduleId) {
    if (typeof moduleId === 'string') {
      return Asset.fromURI(moduleId);
    }

    return new Asset({
      name: 'expo-harmony-module-asset',
      uri: 'asset://' + String(moduleId),
      localUri: 'asset://' + String(moduleId),
    });
  }

  static async loadAsync(moduleIds) {
    return loadAsync(moduleIds);
  }

  async downloadAsync() {
    this.downloaded = true;
    this.localUri = this.localUri ?? this.uri;
    return this;
  }
}

async function loadAsync(moduleIds) {
  const input = Array.isArray(moduleIds) ? moduleIds : [moduleIds];
  return Promise.all(input.map((moduleId) => Asset.fromModule(moduleId).downloadAsync()));
}

function useAssets() {
  return [null, null];
}

module.exports = {
  Asset,
  loadAsync,
  useAssets,
};
