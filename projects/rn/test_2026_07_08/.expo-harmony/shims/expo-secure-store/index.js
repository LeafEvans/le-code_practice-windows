'use strict';

const secureStore = new Map();

async function isAvailableAsync() {
  return true;
}

async function setItemAsync(key, value) {
  secureStore.set(String(key), String(value));
}

async function getItemAsync(key) {
  const normalizedKey = String(key);
  return secureStore.has(normalizedKey) ? secureStore.get(normalizedKey) : null;
}

async function deleteItemAsync(key) {
  secureStore.delete(String(key));
}

module.exports = {
  AFTER_FIRST_UNLOCK: 'AFTER_FIRST_UNLOCK',
  AFTER_FIRST_UNLOCK_THIS_DEVICE_ONLY: 'AFTER_FIRST_UNLOCK_THIS_DEVICE_ONLY',
  ALWAYS: 'ALWAYS',
  ALWAYS_THIS_DEVICE_ONLY: 'ALWAYS_THIS_DEVICE_ONLY',
  WHEN_PASSCODE_SET_THIS_DEVICE_ONLY: 'WHEN_PASSCODE_SET_THIS_DEVICE_ONLY',
  WHEN_UNLOCKED: 'WHEN_UNLOCKED',
  WHEN_UNLOCKED_THIS_DEVICE_ONLY: 'WHEN_UNLOCKED_THIS_DEVICE_ONLY',
  isAvailableAsync,
  setItemAsync,
  getItemAsync,
  deleteItemAsync,
};
