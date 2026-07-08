'use strict';

const React = require('react');
const { Dimensions, View } = require('react-native');

function getWindowMetrics() {
  const metrics = Dimensions.get('window') ?? { width: 0, height: 0 };

  return {
    frame: {
      x: 0,
      y: 0,
      width: typeof metrics.width === 'number' ? metrics.width : 0,
      height: typeof metrics.height === 'number' ? metrics.height : 0,
    },
    insets: {
      top: 0,
      right: 0,
      bottom: 0,
      left: 0,
    },
  };
}

const initialWindowMetrics = getWindowMetrics();
const initialWindowSafeAreaInsets = initialWindowMetrics.insets;
const SafeAreaInsetsContext = React.createContext(initialWindowMetrics.insets);
const SafeAreaFrameContext = React.createContext(initialWindowMetrics.frame);

function SafeAreaProvider({ children, initialMetrics = initialWindowMetrics, style }) {
  const metrics = initialMetrics ?? initialWindowMetrics;

  return React.createElement(
    SafeAreaFrameContext.Provider,
    { value: metrics.frame },
    React.createElement(
      SafeAreaInsetsContext.Provider,
      { value: metrics.insets },
      React.createElement(View, { style: [{ flex: 1 }, style] }, children),
    ),
  );
}

function NativeSafeAreaProvider(props) {
  return React.createElement(SafeAreaProvider, props);
}

function SafeAreaView({ children, style, ...rest }) {
  return React.createElement(View, { ...rest, style }, children);
}

function SafeAreaListener({ children }) {
  return typeof children === 'function' ? children(initialWindowMetrics) : null;
}

function useSafeAreaInsets() {
  return React.useContext(SafeAreaInsetsContext);
}

function useSafeAreaFrame() {
  return React.useContext(SafeAreaFrameContext);
}

function useSafeArea() {
  return useSafeAreaInsets();
}

function withSafeAreaInsets(Component) {
  return React.forwardRef((props, ref) =>
    React.createElement(Component, {
      ...props,
      ref,
      insets: useSafeAreaInsets(),
    }),
  );
}

module.exports = {
  EdgeInsets: undefined,
  initialWindowMetrics,
  initialWindowSafeAreaInsets,
  NativeSafeAreaProvider,
  SafeAreaConsumer: SafeAreaInsetsContext.Consumer,
  SafeAreaFrameContext,
  SafeAreaInsetsContext,
  SafeAreaListener,
  SafeAreaProvider,
  SafeAreaView,
  useSafeArea,
  useSafeAreaFrame,
  useSafeAreaInsets,
  withSafeAreaInsets,
};
