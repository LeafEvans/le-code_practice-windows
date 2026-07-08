'use strict';

let clipboardString = '';
let clipboardUrl = null;
let clipboardImage = null;

async function setStringAsync(value) {
  clipboardString = String(value);
  clipboardUrl = null;
  return true;
}

async function getStringAsync() {
  return clipboardString;
}

async function hasStringAsync() {
  return clipboardString.length > 0;
}

async function setUrlAsync(value) {
  clipboardUrl = String(value);
  clipboardString = clipboardUrl;
}

async function getUrlAsync() {
  return clipboardUrl;
}

async function setImageAsync(value) {
  clipboardImage = String(value);
}

async function getImageAsync() {
  return clipboardImage;
}

module.exports = {
  setStringAsync,
  getStringAsync,
  hasStringAsync,
  setUrlAsync,
  getUrlAsync,
  setImageAsync,
  getImageAsync,
};
