require('./.expo-harmony/shims/runtime-prelude.js');

const React = require('react');
const { AppRegistry } = require('react-native');
const { registerRootComponent } = require('expo');
const { ExpoRoot } = require('expo-router');

const context = require.context('./app', true, /\.[jt]sx?$/);

function App() {
  return React.createElement(ExpoRoot, {
    context,
  });
}

registerRootComponent(App);
AppRegistry.registerComponent("expense-tracker", () => App);
