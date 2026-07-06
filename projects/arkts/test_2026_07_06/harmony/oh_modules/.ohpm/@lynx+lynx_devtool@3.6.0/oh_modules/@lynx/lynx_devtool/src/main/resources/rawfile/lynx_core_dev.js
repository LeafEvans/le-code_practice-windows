/** build time: Sun, 04 Jan 2026 08:42:35 GMT, commit: f210b95bcb720c63148de6329f31732ffab11f43 */
(() => {
  var __create = Object.create;
  var __defProp = Object.defineProperty;
  var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
  var __getOwnPropNames = Object.getOwnPropertyNames;
  var __getProtoOf = Object.getPrototypeOf;
  var __hasOwnProp = Object.prototype.hasOwnProperty;
  var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, { enumerable: true,
  configurable: true, writable: true, value }) : obj[key] = value;
  var __commonJS = (cb, mod) => function __require() {
    return mod || (0, cb[__getOwnPropNames(cb)[0]])((mod = { exports: {} }).exports,
    mod), mod.exports;
  };
  var __copyProps = (to, from, except, desc) => {
    if (from && typeof from === "object" || typeof from === "function") {
      for (let key of __getOwnPropNames(from))
        if (!__hasOwnProp.call(to, key) && key !== except)
          __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(
          from, key)) || desc.enumerable });
    }
    return to;
  };
  var __toESM = (mod, isNodeMode, target) => (target = mod != null ? __create(__getProtoOf(
  mod)) : {}, __copyProps(
    // If the importer is in node compatibility mode or this is not an ESM
    // file that has been converted to a CommonJS file using a Babel-
    // compatible transform (i.e. "__esModule" has not been set), then set
    // "default" to the CommonJS "module.exports" for node compatibility.
    isNodeMode || !mod || !mod.__esModule ? __defProp(target, "default", { value: mod,
    enumerable: true }) : target,
    mod
  ));
  var __publicField = (obj, key, value) => {
    __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
    return value;
  };

  // ../lynx-promise/src/core.js
  var require_core = __commonJS({
    "../lynx-promise/src/core.js"(exports, module2) {
      "use strict";
      function noop2() {
      }
      var LAST_ERROR = null;
      var IS_ERROR = {};
      function getThen(obj) {
        try {
          return obj.then;
        } catch (ex) {
          LAST_ERROR = ex;
          return IS_ERROR;
        }
      }
      function tryCallOne(fn, a) {
        try {
          return fn(a);
        } catch (ex) {
          LAST_ERROR = ex;
          return IS_ERROR;
        }
      }
      function tryCallTwo(fn, a, b) {
        try {
          fn(a, b);
        } catch (ex) {
          LAST_ERROR = ex;
          return IS_ERROR;
        }
      }
      function trimStack(stack) {
        if (!stack) {
          return "";
        }
        const index = stack.indexOf("\n");
        if (index === -1) {
          return stack;
        }
        return stack.substring(index + 1);
      }
      module2.exports = (opt) => {
        var nextTick = opt.nextTick;
        function Promise2(fn) {
          this.__createStack = trimStack(new Error("Promise creation stack").stack);
          if (typeof this !== "object") {
            throw new TypeError("Promises must be constructed via new");
          }
          if (typeof fn !== "function") {
            throw new TypeError("Promise constructor's argument is not a functio\
n");
          }
          this._deferredState = 0;
          this._state = 0;
          this._value = null;
          this._deferreds = null;
          if (fn === noop2)
            return;
          doResolve(fn, this);
        }
        Promise2._onHandle = null;
        Promise2._onReject = null;
        Promise2._noop = noop2;
        Promise2.prototype.then = function(onFulfilled, onRejected) {
          if (this.constructor !== Promise2) {
            return safeThen(this, onFulfilled, onRejected);
          }
          var res = new Promise2(noop2);
          handle(this, new Handler(onFulfilled, onRejected, res));
          return res;
        };
        function safeThen(self, onFulfilled, onRejected) {
          return new self.constructor(function(resolve2, reject2) {
            var res = new Promise2(noop2);
            res.then(resolve2, reject2);
            handle(self, new Handler(onFulfilled, onRejected, res));
          });
        }
        function handle(self, deferred) {
          while (self._state === 3) {
            self = self._value;
          }
          if (Promise2._onHandle) {
            Promise2._onHandle(self);
          }
          if (self._state === 0) {
            if (self._deferredState === 0) {
              self._deferredState = 1;
              self._deferreds = deferred;
              return;
            }
            if (self._deferredState === 1) {
              self._deferredState = 2;
              self._deferreds = [self._deferreds, deferred];
              return;
            }
            self._deferreds.push(deferred);
            return;
          }
          handleResolved(self, deferred);
        }
        function handleResolved(self, deferred) {
          nextTick(function() {
            var cb = self._state === 1 ? deferred.onFulfilled : deferred.onRejected;
            if (cb === null) {
              if (self._state === 1) {
                resolve(deferred.promise, self._value);
              } else {
                reject(deferred.promise, self._value);
              }
              return;
            }
            var ret = tryCallOne(cb, self._value);
            if (ret === IS_ERROR) {
              reject(deferred.promise, LAST_ERROR);
            } else {
              resolve(deferred.promise, ret);
            }
          });
        }
        function resolve(self, newValue) {
          if (newValue === self) {
            return reject(self, new TypeError("A promise cannot be resolved with\
 itself."));
          }
          if (newValue && (typeof newValue === "object" || typeof newValue === "\
function")) {
            var then = getThen(newValue);
            if (then === IS_ERROR) {
              return reject(self, LAST_ERROR);
            }
            if (then === self.then && newValue instanceof Promise2) {
              self._state = 3;
              self._value = newValue;
              finale(self);
              return;
            } else if (typeof then === "function") {
              doResolve(then.bind(newValue), self);
              return;
            }
          }
          self._state = 1;
          self._value = newValue;
          finale(self);
        }
        function reject(self, newValue) {
          self._state = 2;
          self._value = newValue;
          if (Promise2._onReject) {
            Promise2._onReject(self, newValue);
          }
          finale(self);
        }
        function finale(self) {
          if (self._deferredState === 1) {
            handle(self, self._deferreds);
            self._deferreds = null;
          }
          if (self._deferredState === 2) {
            for (var i = 0; i < self._deferreds.length; i++) {
              handle(self, self._deferreds[i]);
            }
            self._deferreds = null;
          }
        }
        function Handler(onFulfilled, onRejected, promise) {
          this.onFulfilled = typeof onFulfilled === "function" ? onFulfilled : null;
          this.onRejected = typeof onRejected === "function" ? onRejected : null;
          this.promise = promise;
        }
        function doResolve(fn, promise) {
          var done = false;
          var res = tryCallTwo(
            fn,
            function(value) {
              if (done)
                return;
              done = true;
              resolve(promise, value);
            },
            function(reason) {
              if (done)
                return;
              done = true;
              reject(promise, reason);
            }
          );
          if (!done && res === IS_ERROR) {
            done = true;
            reject(promise, LAST_ERROR);
          }
        }
        return Promise2;
      };
    }
  });

  // ../lynx-promise/src/es6-extensions.js
  var require_es6_extensions = __commonJS({
    "../lynx-promise/src/es6-extensions.js"(exports, module2) {
      "use strict";
      module2.exports = (Promise2) => {
        var TRUE = valuePromise(true);
        var FALSE = valuePromise(false);
        var NULL = valuePromise(null);
        var UNDEFINED = valuePromise(void 0);
        var ZERO = valuePromise(0);
        var EMPTYSTRING = valuePromise("");
        function valuePromise(value) {
          var p = new Promise2(Promise2._noop);
          p._state = 1;
          p._value = value;
          return p;
        }
        Promise2.resolve = function(value) {
          if (value instanceof Promise2)
            return value;
          if (value === null)
            return NULL;
          if (value === void 0)
            return UNDEFINED;
          if (value === true)
            return TRUE;
          if (value === false)
            return FALSE;
          if (value === 0)
            return ZERO;
          if (value === "")
            return EMPTYSTRING;
          if (typeof value === "object" || typeof value === "function") {
            try {
              var then = value.then;
              if (typeof then === "function") {
                return new Promise2(then.bind(value));
              }
            } catch (ex) {
              return new Promise2(function(resolve, reject) {
                reject(ex);
              });
            }
          }
          return valuePromise(value);
        };
        var iterableToArray = function(iterable) {
          if (typeof Array.from === "function") {
            iterableToArray = Array.from;
            return Array.from(iterable);
          }
          iterableToArray = function(x) {
            return Array.prototype.slice.call(x);
          };
          return Array.prototype.slice.call(iterable);
        };
        Promise2.all = function(arr) {
          var args = iterableToArray(arr);
          return new Promise2(function(resolve, reject) {
            if (args.length === 0)
              return resolve([]);
            var remaining = args.length;
            function res(i2, val) {
              if (val && (typeof val === "object" || typeof val === "function")) {
                if (val instanceof Promise2 && val.then === Promise2.prototype.then) {
                  while (val._state === 3) {
                    val = val._value;
                  }
                  if (val._state === 1)
                    return res(i2, val._value);
                  if (val._state === 2)
                    reject(val._value);
                  val.then(function(val2) {
                    res(i2, val2);
                  }, reject);
                  return;
                } else {
                  var then = val.then;
                  if (typeof then === "function") {
                    var p = new Promise2(then.bind(val));
                    p.then(function(val2) {
                      res(i2, val2);
                    }, reject);
                    return;
                  }
                }
              }
              args[i2] = val;
              if (--remaining === 0) {
                resolve(args);
              }
            }
            for (var i = 0; i < args.length; i++) {
              res(i, args[i]);
            }
          });
        };
        Promise2.reject = function(value) {
          return new Promise2(function(resolve, reject) {
            reject(value);
          });
        };
        Promise2.race = function(values) {
          return new Promise2(function(resolve, reject) {
            iterableToArray(values).forEach(function(value) {
              Promise2.resolve(value).then(resolve, reject);
            });
          });
        };
        Promise2.prototype["catch"] = function(onRejected) {
          return this.then(null, onRejected);
        };
        Promise2.prototype.done = function(onFulfilled, onRejected) {
          var self = arguments.length ? this.then.apply(this, arguments) : this;
          self.then(null, function(err) {
            setTimeout(function() {
              throw err;
            }, 0);
          });
        };
        Promise2.prototype.finally = function(f) {
          return this.then(
            function(value) {
              return Promise2.resolve(f()).then(function() {
                return value;
              });
            },
            function(err) {
              return Promise2.resolve(f()).then(function() {
                throw err;
              });
            }
          );
        };
        return Promise2;
      };
    }
  });

  // ../lynx-promise/src/rejection-tracking.js
  var require_rejection_tracking = __commonJS({
    "../lynx-promise/src/rejection-tracking.js"(exports, module2) {
      "use strict";
      module2.exports = (Promise2, setTimeout2, clearTimeout) => {
        var DEFAULT_WHITELIST = [ReferenceError, TypeError, RangeError];
        var enabled = false;
        function disable() {
          enabled = false;
          Promise2._onHandle = null;
          Promise2._onReject = null;
        }
        function enable(options) {
          options = options || {};
          if (enabled)
            disable();
          enabled = true;
          var id = 0;
          var displayId = 0;
          var rejections = {};
          Promise2._onHandle = function(promise) {
            if (promise._state === 2 && // IS REJECTED
            rejections[promise._rejectionId]) {
              if (rejections[promise._rejectionId].logged) {
                onHandled(promise._rejectionId);
              } else {
                clearTimeout && clearTimeout(rejections[promise._rejectionId].timeout);
              }
              delete rejections[promise._rejectionId];
            }
          };
          Promise2._onReject = function(promise, err) {
            if (promise._deferredState === 0) {
              promise._rejectionId = id++;
              rejections[promise._rejectionId] = {
                displayId: null,
                error: err,
                timeout: setTimeout2(
                  onUnhandled.bind(null, promise),
                  0
                ),
                logged: false
              };
            }
          };
          function onUnhandled(promise) {
            const id2 = promise._rejectionId;
            if (options.allRejections || matchWhitelist(rejections[id2].error, options.
            whitelist || DEFAULT_WHITELIST)) {
              rejections[id2].displayId = displayId++;
              if (options.onUnhandled) {
                rejections[id2].logged = true;
                if (rejections[id2].error && !(rejections[id2].error instanceof Error)) {
                  const error = new Error(JSON.stringify(rejections[id2].error));
                  error.stack = promise.__createStack;
                  rejections[id2].error = error;
                }
                options.onUnhandled(rejections[id2].displayId, rejections[id2].error);
              } else {
                rejections[id2].logged = true;
                logError(rejections[id2].displayId, rejections[id2].error);
              }
            }
          }
          function onHandled(id2) {
            if (rejections[id2].logged) {
              if (options.onHandled) {
                options.onHandled(rejections[id2].displayId, rejections[id2].error);
              } else if (!rejections[id2].onUnhandled) {
                console.warn("Promise Rejection Handled (id: " + rejections[id2].
                displayId + "):");
                console.warn(
                  '  This means you can ignore any previous messages of the form\
 "Possible Unhandled Promise Rejection" with id ' + rejections[id2].displayId + "\
."
                );
              }
            }
          }
          return Promise2;
        }
        function logError(id, error) {
          console.warn("Possible Unhandled Promise Rejection (id: " + id + "):");
          var errStr = (error && (error.stack || error)) + "";
          errStr.split("\n").forEach(function(line) {
            console.warn("  " + line);
          });
        }
        function matchWhitelist(error, list) {
          return list.some(function(cls) {
            return error instanceof cls;
          });
        }
        return {
          enable,
          disable
        };
      };
    }
  });

  // ../lynx-promise/src/index.js
  var require_src = __commonJS({
    "../lynx-promise/src/index.js"(exports, module2) {
      "use strict";
      var promiseFactor = require_core();
      var es6 = require_es6_extensions();
      var rejectionHandle = require_rejection_tracking();
      var gg = new Function("return this")();
      gg.getPromise = module2.exports.getPromise = (opt) => {
        var setTimeout2 = opt.setTimeout;
        var onUnhandled = opt.onUnhandled;
        var clearTimeout = opt.clearTimeout;
        var nextTick = opt.nextTick || ((fn) => {
          setTimeout2(fn, 0);
        });
        var Promise2 = promiseFactor({ nextTick });
        Promise2 = es6(Promise2);
        Promise2 = rejectionHandle(Promise2, setTimeout2, clearTimeout).enable({
          allRejections: true,
          onUnhandled
        });
        return Promise2;
      };
    }
  });

  // ../../node_modules/.pnpm/regenerator-runtime@0.13.7/node_modules/regenerator-runtime/runtime.js
  var require_runtime = __commonJS({
    "../../node_modules/.pnpm/regenerator-runtime@0.13.7/node_modules/regenerato\
r-runtime/runtime.js"(exports, module2) {
      var runtime = function(exports2) {
        "use strict";
        var Op = Object.prototype;
        var hasOwn = Op.hasOwnProperty;
        var undefined2;
        var $Symbol = typeof Symbol === "function" ? Symbol : {};
        var iteratorSymbol = $Symbol.iterator || "@@iterator";
        var asyncIteratorSymbol = $Symbol.asyncIterator || "@@asyncIterator";
        var toStringTagSymbol = $Symbol.toStringTag || "@@toStringTag";
        function define(obj, key, value) {
          Object.defineProperty(obj, key, {
            value,
            enumerable: true,
            configurable: true,
            writable: true
          });
          return obj[key];
        }
        try {
          define({}, "");
        } catch (err) {
          define = function(obj, key, value) {
            return obj[key] = value;
          };
        }
        function wrap(innerFn, outerFn, self, tryLocsList) {
          var protoGenerator = outerFn && outerFn.prototype instanceof Generator ?
          outerFn : Generator;
          var generator = Object.create(protoGenerator.prototype);
          var context = new Context(tryLocsList || []);
          generator._invoke = makeInvokeMethod(innerFn, self, context);
          return generator;
        }
        exports2.wrap = wrap;
        function tryCatch(fn, obj, arg) {
          try {
            return { type: "normal", arg: fn.call(obj, arg) };
          } catch (err) {
            return { type: "throw", arg: err };
          }
        }
        var GenStateSuspendedStart = "suspendedStart";
        var GenStateSuspendedYield = "suspendedYield";
        var GenStateExecuting = "executing";
        var GenStateCompleted = "completed";
        var ContinueSentinel = {};
        function Generator() {
        }
        function GeneratorFunction() {
        }
        function GeneratorFunctionPrototype() {
        }
        var IteratorPrototype = {};
        IteratorPrototype[iteratorSymbol] = function() {
          return this;
        };
        var getProto = Object.getPrototypeOf;
        var NativeIteratorPrototype = getProto && getProto(getProto(values([])));
        if (NativeIteratorPrototype && NativeIteratorPrototype !== Op && hasOwn.
        call(NativeIteratorPrototype, iteratorSymbol)) {
          IteratorPrototype = NativeIteratorPrototype;
        }
        var Gp = GeneratorFunctionPrototype.prototype = Generator.prototype = Object.
        create(IteratorPrototype);
        GeneratorFunction.prototype = Gp.constructor = GeneratorFunctionPrototype;
        GeneratorFunctionPrototype.constructor = GeneratorFunction;
        GeneratorFunction.displayName = define(
          GeneratorFunctionPrototype,
          toStringTagSymbol,
          "GeneratorFunction"
        );
        function defineIteratorMethods(prototype) {
          ["next", "throw", "return"].forEach(function(method) {
            define(prototype, method, function(arg) {
              return this._invoke(method, arg);
            });
          });
        }
        exports2.isGeneratorFunction = function(genFun) {
          var ctor = typeof genFun === "function" && genFun.constructor;
          return ctor ? ctor === GeneratorFunction || // For the native GeneratorFunction constructor, the best we can
          // do is to check its .name property.
          (ctor.displayName || ctor.name) === "GeneratorFunction" : false;
        };
        exports2.mark = function(genFun) {
          if (Object.setPrototypeOf) {
            Object.setPrototypeOf(genFun, GeneratorFunctionPrototype);
          } else {
            genFun.__proto__ = GeneratorFunctionPrototype;
            define(genFun, toStringTagSymbol, "GeneratorFunction");
          }
          genFun.prototype = Object.create(Gp);
          return genFun;
        };
        exports2.awrap = function(arg) {
          return { __await: arg };
        };
        function AsyncIterator(generator, PromiseImpl) {
          function invoke(method, arg, resolve, reject) {
            var record = tryCatch(generator[method], generator, arg);
            if (record.type === "throw") {
              reject(record.arg);
            } else {
              var result = record.arg;
              var value = result.value;
              if (value && typeof value === "object" && hasOwn.call(value, "__aw\
ait")) {
                return PromiseImpl.resolve(value.__await).then(function(value2) {
                  invoke("next", value2, resolve, reject);
                }, function(err) {
                  invoke("throw", err, resolve, reject);
                });
              }
              return PromiseImpl.resolve(value).then(function(unwrapped) {
                result.value = unwrapped;
                resolve(result);
              }, function(error) {
                return invoke("throw", error, resolve, reject);
              });
            }
          }
          var previousPromise;
          function enqueue(method, arg) {
            function callInvokeWithMethodAndArg() {
              return new PromiseImpl(function(resolve, reject) {
                invoke(method, arg, resolve, reject);
              });
            }
            return previousPromise = // If enqueue has been called before, then we want to wait until
            // all previous Promises have been resolved before calling invoke,
            // so that results are always delivered in the correct order. If
            // enqueue has not been called before, then it is important to
            // call invoke immediately, without waiting on a callback to fire,
            // so that the async generator function has the opportunity to do
            // any necessary setup in a predictable way. This predictability
            // is why the Promise constructor synchronously invokes its
            // executor callback, and why async functions synchronously
            // execute code before the first await. Since we implement simple
            // async functions in terms of async generators, it is especially
            // important to get this right, even though it requires care.
            previousPromise ? previousPromise.then(
              callInvokeWithMethodAndArg,
              // Avoid propagating failures to Promises returned by later
              // invocations of the iterator.
              callInvokeWithMethodAndArg
            ) : callInvokeWithMethodAndArg();
          }
          this._invoke = enqueue;
        }
        defineIteratorMethods(AsyncIterator.prototype);
        AsyncIterator.prototype[asyncIteratorSymbol] = function() {
          return this;
        };
        exports2.AsyncIterator = AsyncIterator;
        exports2.async = function(innerFn, outerFn, self, tryLocsList, PromiseImpl) {
          if (PromiseImpl === void 0)
            PromiseImpl = Promise;
          var iter = new AsyncIterator(
            wrap(innerFn, outerFn, self, tryLocsList),
            PromiseImpl
          );
          return exports2.isGeneratorFunction(outerFn) ? iter : iter.next().then(
          function(result) {
            return result.done ? result.value : iter.next();
          });
        };
        function makeInvokeMethod(innerFn, self, context) {
          var state = GenStateSuspendedStart;
          return function invoke(method, arg) {
            if (state === GenStateExecuting) {
              throw new Error("Generator is already running");
            }
            if (state === GenStateCompleted) {
              if (method === "throw") {
                throw arg;
              }
              return doneResult();
            }
            context.method = method;
            context.arg = arg;
            while (true) {
              var delegate = context.delegate;
              if (delegate) {
                var delegateResult = maybeInvokeDelegate(delegate, context);
                if (delegateResult) {
                  if (delegateResult === ContinueSentinel)
                    continue;
                  return delegateResult;
                }
              }
              if (context.method === "next") {
                context.sent = context._sent = context.arg;
              } else if (context.method === "throw") {
                if (state === GenStateSuspendedStart) {
                  state = GenStateCompleted;
                  throw context.arg;
                }
                context.dispatchException(context.arg);
              } else if (context.method === "return") {
                context.abrupt("return", context.arg);
              }
              state = GenStateExecuting;
              var record = tryCatch(innerFn, self, context);
              if (record.type === "normal") {
                state = context.done ? GenStateCompleted : GenStateSuspendedYield;
                if (record.arg === ContinueSentinel) {
                  continue;
                }
                return {
                  value: record.arg,
                  done: context.done
                };
              } else if (record.type === "throw") {
                state = GenStateCompleted;
                context.method = "throw";
                context.arg = record.arg;
              }
            }
          };
        }
        function maybeInvokeDelegate(delegate, context) {
          var method = delegate.iterator[context.method];
          if (method === undefined2) {
            context.delegate = null;
            if (context.method === "throw") {
              if (delegate.iterator["return"]) {
                context.method = "return";
                context.arg = undefined2;
                maybeInvokeDelegate(delegate, context);
                if (context.method === "throw") {
                  return ContinueSentinel;
                }
              }
              context.method = "throw";
              context.arg = new TypeError(
                "The iterator does not provide a 'throw' method"
              );
            }
            return ContinueSentinel;
          }
          var record = tryCatch(method, delegate.iterator, context.arg);
          if (record.type === "throw") {
            context.method = "throw";
            context.arg = record.arg;
            context.delegate = null;
            return ContinueSentinel;
          }
          var info = record.arg;
          if (!info) {
            context.method = "throw";
            context.arg = new TypeError("iterator result is not an object");
            context.delegate = null;
            return ContinueSentinel;
          }
          if (info.done) {
            context[delegate.resultName] = info.value;
            context.next = delegate.nextLoc;
            if (context.method !== "return") {
              context.method = "next";
              context.arg = undefined2;
            }
          } else {
            return info;
          }
          context.delegate = null;
          return ContinueSentinel;
        }
        defineIteratorMethods(Gp);
        define(Gp, toStringTagSymbol, "Generator");
        Gp[iteratorSymbol] = function() {
          return this;
        };
        Gp.toString = function() {
          return "[object Generator]";
        };
        function pushTryEntry(locs) {
          var entry = { tryLoc: locs[0] };
          if (1 in locs) {
            entry.catchLoc = locs[1];
          }
          if (2 in locs) {
            entry.finallyLoc = locs[2];
            entry.afterLoc = locs[3];
          }
          this.tryEntries.push(entry);
        }
        function resetTryEntry(entry) {
          var record = entry.completion || {};
          record.type = "normal";
          delete record.arg;
          entry.completion = record;
        }
        function Context(tryLocsList) {
          this.tryEntries = [{ tryLoc: "root" }];
          tryLocsList.forEach(pushTryEntry, this);
          this.reset(true);
        }
        exports2.keys = function(object) {
          var keys = [];
          for (var key in object) {
            keys.push(key);
          }
          keys.reverse();
          return function next() {
            while (keys.length) {
              var key2 = keys.pop();
              if (key2 in object) {
                next.value = key2;
                next.done = false;
                return next;
              }
            }
            next.done = true;
            return next;
          };
        };
        function values(iterable) {
          if (iterable) {
            var iteratorMethod = iterable[iteratorSymbol];
            if (iteratorMethod) {
              return iteratorMethod.call(iterable);
            }
            if (typeof iterable.next === "function") {
              return iterable;
            }
            if (!isNaN(iterable.length)) {
              var i = -1, next = function next2() {
                while (++i < iterable.length) {
                  if (hasOwn.call(iterable, i)) {
                    next2.value = iterable[i];
                    next2.done = false;
                    return next2;
                  }
                }
                next2.value = undefined2;
                next2.done = true;
                return next2;
              };
              return next.next = next;
            }
          }
          return { next: doneResult };
        }
        exports2.values = values;
        function doneResult() {
          return { value: undefined2, done: true };
        }
        Context.prototype = {
          constructor: Context,
          reset: function(skipTempReset) {
            this.prev = 0;
            this.next = 0;
            this.sent = this._sent = undefined2;
            this.done = false;
            this.delegate = null;
            this.method = "next";
            this.arg = undefined2;
            this.tryEntries.forEach(resetTryEntry);
            if (!skipTempReset) {
              for (var name in this) {
                if (name.charAt(0) === "t" && hasOwn.call(this, name) && !isNaN(
                +name.slice(1))) {
                  this[name] = undefined2;
                }
              }
            }
          },
          stop: function() {
            this.done = true;
            var rootEntry = this.tryEntries[0];
            var rootRecord = rootEntry.completion;
            if (rootRecord.type === "throw") {
              throw rootRecord.arg;
            }
            return this.rval;
          },
          dispatchException: function(exception) {
            if (this.done) {
              throw exception;
            }
            var context = this;
            function handle(loc, caught) {
              record.type = "throw";
              record.arg = exception;
              context.next = loc;
              if (caught) {
                context.method = "next";
                context.arg = undefined2;
              }
              return !!caught;
            }
            for (var i = this.tryEntries.length - 1; i >= 0; --i) {
              var entry = this.tryEntries[i];
              var record = entry.completion;
              if (entry.tryLoc === "root") {
                return handle("end");
              }
              if (entry.tryLoc <= this.prev) {
                var hasCatch = hasOwn.call(entry, "catchLoc");
                var hasFinally = hasOwn.call(entry, "finallyLoc");
                if (hasCatch && hasFinally) {
                  if (this.prev < entry.catchLoc) {
                    return handle(entry.catchLoc, true);
                  } else if (this.prev < entry.finallyLoc) {
                    return handle(entry.finallyLoc);
                  }
                } else if (hasCatch) {
                  if (this.prev < entry.catchLoc) {
                    return handle(entry.catchLoc, true);
                  }
                } else if (hasFinally) {
                  if (this.prev < entry.finallyLoc) {
                    return handle(entry.finallyLoc);
                  }
                } else {
                  throw new Error("try statement without catch or finally");
                }
              }
            }
          },
          abrupt: function(type, arg) {
            for (var i = this.tryEntries.length - 1; i >= 0; --i) {
              var entry = this.tryEntries[i];
              if (entry.tryLoc <= this.prev && hasOwn.call(entry, "finallyLoc") &&
              this.prev < entry.finallyLoc) {
                var finallyEntry = entry;
                break;
              }
            }
            if (finallyEntry && (type === "break" || type === "continue") && finallyEntry.
            tryLoc <= arg && arg <= finallyEntry.finallyLoc) {
              finallyEntry = null;
            }
            var record = finallyEntry ? finallyEntry.completion : {};
            record.type = type;
            record.arg = arg;
            if (finallyEntry) {
              this.method = "next";
              this.next = finallyEntry.finallyLoc;
              return ContinueSentinel;
            }
            return this.complete(record);
          },
          complete: function(record, afterLoc) {
            if (record.type === "throw") {
              throw record.arg;
            }
            if (record.type === "break" || record.type === "continue") {
              this.next = record.arg;
            } else if (record.type === "return") {
              this.rval = this.arg = record.arg;
              this.method = "return";
              this.next = "end";
            } else if (record.type === "normal" && afterLoc) {
              this.next = afterLoc;
            }
            return ContinueSentinel;
          },
          finish: function(finallyLoc) {
            for (var i = this.tryEntries.length - 1; i >= 0; --i) {
              var entry = this.tryEntries[i];
              if (entry.finallyLoc === finallyLoc) {
                this.complete(entry.completion, entry.afterLoc);
                resetTryEntry(entry);
                return ContinueSentinel;
              }
            }
          },
          "catch": function(tryLoc) {
            for (var i = this.tryEntries.length - 1; i >= 0; --i) {
              var entry = this.tryEntries[i];
              if (entry.tryLoc === tryLoc) {
                var record = entry.completion;
                if (record.type === "throw") {
                  var thrown = record.arg;
                  resetTryEntry(entry);
                }
                return thrown;
              }
            }
            throw new Error("illegal catch attempt");
          },
          delegateYield: function(iterable, resultName, nextLoc) {
            this.delegate = {
              iterator: values(iterable),
              resultName,
              nextLoc
            };
            if (this.method === "next") {
              this.arg = undefined2;
            }
            return ContinueSentinel;
          }
        };
        return exports2;
      }(
        // If this script is executing as a CommonJS module, use module.exports
        // as the regeneratorRuntime namespace. Otherwise create a new empty
        // object. Either way, the resulting object will be used to initialize
        // the regeneratorRuntime variable at the top of this file.
        typeof module2 === "object" ? module2.exports : {}
      );
      try {
        regeneratorRuntime = runtime;
      } catch (accidentalStrictMode) {
        Function("r", "regeneratorRuntime = r")(runtime);
      }
    }
  });

  // kernel-build/android-polyfill.js
  var globalThis2 = new Function("return this;")();
  globalThis2.globalThis = globalThis2;

  // src/index.build.ts
  var import_ios_polyfill_promise = __toESM(require_src(), 1);
  var import_runtime3 = __toESM(require_runtime(), 1);

  // ../lynx-runtime-shared/dist/nativeGlobal.js
  var _global = function() {
    return this || (0, eval)("this");
  }();
  var nativeGlobal_default = _global;

  // ../lynx-runtime-shared/dist/ttConsole.js
  function createSharedConsole(runtimeId) {
    return nativeConsole;
  }
  var _global2 = function() {
    return this || (0, eval)("this");
  }();
  var groupConsole = createSharedConsole(`groupId:${_global2.groupId || "-1"}`);
  var ttConsole_default = true ? groupConsole : nativeConsole;

  // ../lynx-runtime-shared/dist/utils.js
  function getDataType(data) {
    const type = typeof data;
    if (type !== "object")
      return type;
    if (Array.isArray(data))
      return "array";
    if (data == null)
      return "null";
    if (data instanceof Date)
      return "date";
    if (data instanceof RegExp)
      return "regExp";
    return "object";
  }
  function isString(val) {
    return typeof val === "string";
  }
  function isObject(val) {
    return getDataType(val) === "object";
  }
  function isFunction(obj) {
    const dataType = getDataType(obj);
    return dataType === "function";
  }
  function isError(o) {
    switch (Object.prototype.toString.call(o)) {
      case "[object Error]":
        return true;
      case "[object Exception]":
        return true;
      case "[object DOMException]":
        return true;
      default:
        return isInstanceOf(o, Error);
    }
  }
  function isInstanceOf(o, base) {
    try {
      return o instanceof base;
    } catch (_e) {
      return false;
    }
  }
  function noop() {
  }

  // src/common/ttConsole.ts
  var ttConsole_default2 = ttConsole_default;

  // src/modules/report/errors.ts
  var BaseError = class extends Error {
    constructor(message, stack) {
      super(message);
      if (stack) {
        this.stack = stack;
      }
    }
  };
  var InternalError = class extends BaseError {
    constructor() {
      super(...arguments);
      this.kind = "INTERNAL_ERROR";
    }
  };
  var UserError = class extends BaseError {
    constructor() {
      super(...arguments);
      this.kind = "USER_ERROR";
    }
  };
  var UserRuntimeError = class extends UserError {
    constructor() {
      super(...arguments);
      this.name = "USER_RUNTIME_ERROR";
    }
  };
  var InternalRuntimeError = class extends InternalError {
    constructor() {
      super(...arguments);
      this.name = "INTERNAL_RUNTIME_ERROR";
    }
  };
  var InvokeError = class extends InternalError {
    constructor() {
      super(...arguments);
      this.name = "INVOKE_ERROR";
    }
  };

  // src/common/constants.ts
  var DEFAULT_ENTRY = "__Card__";
  var APP_SERVICE_NAME = "app-service.js";
  var SOURCE_MAP_RELEASE_ERROR_NAME = "LynxGetSourceMapReleaseError";
  var LYNX_CORE = {
    filename: "lynx_core",
    slot: "f210b95bcb720c63148de6329f31732ffab11f43",
    release: "3.6.0"
  };

  // src/modules/sharedData/ShareDataSubject.ts
  var ShareDataSubject = class {
    constructor() {
      /**
       * @type {Observer[]} List of subscribers.
       *
       */
      this.observersFunc = [];
    }
    /**
     * The subscription management methods.
     */
    registerObserver(observer) {
      const isExist = this.observersFunc.includes(observer);
      if (isExist) {
        return ttConsole_default2.log("Subject: Observer has been attached alrea\
dy.");
      }
      this.observersFunc.push(observer);
    }
    removeObserver(observer) {
      const observerIndex = this.observersFunc.indexOf(observer);
      if (observerIndex === -1) {
        return ttConsole_default2.log("Subject: Nonexistent observer.");
      }
      this.observersFunc.splice(observerIndex, 1);
    }
    notifyDataChange(value) {
      this.observersFunc.forEach((toObserver) => {
        if (typeof toObserver === "function") {
          try {
            toObserver(value);
          } catch (error) {
            ttConsole_default2.log(
              "SharedData change and notifyDataChange error info:" + error
            );
          }
        }
      });
    }
  };

  // src/common/nativeGlobal.ts
  nativeGlobal_default.multiApps = {};
  nativeGlobal_default.currentAppId = "";
  nativeGlobal_default.globComponentRegistPath = "";
  nativeGlobal_default.sharedData = {};
  nativeGlobal_default.globDynamicComponentEntry = DEFAULT_ENTRY;
  nativeGlobal_default.shareDataSubject = new ShareDataSubject();
  nativeGlobal_default.TaroLynx = {};
  nativeGlobal_default.bundleSupportLoadScript = true;
  var { loadScript } = nativeGlobal_default;
  var nativeGlobal_default2 = nativeGlobal_default;

  // src/common/log.ts
  var isNativeConsoleHasALog;
  function alog(str) {
    if (true) {
      return;
    }
    if (isNativeConsoleHasALog === void 0) {
      isNativeConsoleHasALog = typeof ttConsole_default2.alog === "function";
    }
    if (isNativeConsoleHasALog) {
      ttConsole_default2.alog("[LynxJSSDK]" + str);
    }
  }

  // src/common/version.ts
  var numberRegExp = /\d+/;
  var Version = class _Version {
    // version: major.minor.revision.build
    constructor(version) {
      this.major = 0;
      this.minor = 0;
      this.revision = 0;
      this.build = 0;
      version = String(version);
      [
        this.major = 0,
        this.minor = 0,
        this.revision = 0,
        this.build = 0
      ] = version.split(".").map((v) => {
        const result = numberRegExp.exec(v);
        if (result && result.length > 0) {
          return +result[0];
        }
        return 0;
      });
    }
    /**
     * Greater Than
     * @param version the version to be compared
     * @returns this > version
     */
    gt(version) {
      if (typeof version === "string") {
        version = new _Version(version);
      }
      if (this.major > version.major) {
        return true;
      } else if (this.major < version.major) {
        return false;
      }
      if (this.minor > version.minor) {
        return true;
      } else if (this.minor < version.minor) {
        return false;
      }
      if (this.revision > version.revision) {
        return true;
      } else if (this.revision < version.revision) {
        return false;
      }
      if (this.build > version.build) {
        return true;
      } else if (this.build < version.build) {
        return false;
      }
      return false;
    }
    /**
     * EQual
     * @param version the version to be compared
     * @returns this == version
     */
    eq(version) {
      if (typeof version === "string") {
        version = new _Version(version);
      }
      return this.major === version.major && this.minor === version.minor && this.
      revision === version.revision && this.build === version.build;
    }
    /**
     * Less Than
     * @param version the version to be compared
     * @returns this < version
     */
    lt(version) {
      if (this.eq(version)) {
        return false;
      }
      return !this.gt(version);
    }
    /**
     * Greater Than or Equal
     * @param version the version to be compared
     * @returns this >= version
     */
    gte(version) {
      return this.eq(version) || this.gt(version);
    }
    /**
     * Less Than or Equal
     * @param version the version to be compared
     * @returns this <= version
     */
    lte(version) {
      return this.eq(version) || this.lt(version);
    }
  };
  var version2_4 = new Version("2.4");
  var version2_7 = new Version("2.7");
  var version2_9 = new Version("2.9");
  var version2_12 = new Version("2.12");
  var version2_14 = new Version("2.14");

  // src/common/callbackManager.ts
  var CallbackManager = class {
    constructor() {
      this.id = 1;
      this.callbacks = /* @__PURE__ */ new Map();
      this.taskIdToCallbackIds = /* @__PURE__ */ new Map();
    }
    nextId() {
      if (!this.callbacks) {
        return void 0;
      }
      return this.id++;
    }
    addCallback(callback) {
      if (!this.callbacks) {
        return void 0;
      }
      const id = this.nextId();
      if (id === void 0) {
        return void 0;
      }
      this.callbacks.set(id, callback);
      return id;
    }
    invokeCallback(once, key, ...args) {
      if (!this.callbacks) {
        return;
      }
      const callback = this.callbacks.get(key);
      if (callback) {
        try {
          callback.apply(callback, args);
        } finally {
          if (once) {
            this.removeCallback(key);
          }
        }
      } else {
        console.warn(`callCallback: Callback with ID ${key} not found`);
      }
    }
    removeCallback(key) {
      if (this.callbacks) {
        if (typeof key !== "number") {
          return;
        }
        this.callbacks.delete(key);
      }
    }
    addTaskIdAndCallbackId(taskId, callbackId) {
      if (this.taskIdToCallbackIds) {
        this.taskIdToCallbackIds.set(taskId, callbackId);
      }
    }
    removeCallbackByTaskId(taskId) {
      if (this.taskIdToCallbackIds && this.callbacks) {
        const callbackId = this.taskIdToCallbackIds.get(taskId);
        this.taskIdToCallbackIds.delete(taskId);
        this.removeCallback(callbackId);
      }
    }
    removeTaskId(taskId) {
      if (this.taskIdToCallbackIds && taskId !== void 0) {
        this.taskIdToCallbackIds.delete(taskId);
      }
    }
    destroy() {
      this.callbacks = void 0;
      this.taskIdToCallbackIds = void 0;
    }
  };

  // src/modules/report/report-error.ts
  function reportError(error, nativeApp, options) {
    const { originError, errorCode, errorLevel, runType = LYNX_CORE } = options !=
    null ? options : {};
    ttConsole_default2.error("The following error occurred in the JSRuntime:");
    ttConsole_default2.error(`${error == null ? void 0 : error.message}
${error == null ? void 0 : error.stack}`);
    error.cause = isObject(error.cause) ? JSON.stringify(error.cause) : error.cause;
    try {
      nativeApp.reportException(error, {
        ...runType,
        buildVersion: "3.6.0",
        versionCode: "3.6.0",
        errorCode,
        errorLevel
      });
    } catch (error2) {
      ttConsole_default2.error("reportError err:\n", error2);
    }
  }
  function legacyReportError(error, nativeApp, runType = LYNX_CORE, originError, proxy) {
    return reportError(error, nativeApp, {
      runType,
      originError,
      __sourcemap__release__: proxy.__sourcemap__release__
    });
  }

  // src/modules/report/wrapper.ts
  function wrapUserFunction(desc, instance, callback, runType = LYNX_CORE) {
    if (!isFunction(callback))
      return noop;
    return wrapFunction("USER_ERROR", desc, callback, instance, runType);
  }
  function wrapFunction(errorKind = "INTERNAL_ERROR", desc, callback, instance, runType) {
    return function wrapFunctionInner(...args) {
      try {
        return callback.apply(this, args);
      } catch (error) {
        const message = `${desc} 
${error.message}`;
        if (callback.name !== "onError" && typeof instance.onError === "function") {
          instance.onError(
            `Card ${callback.name} exec error:${message}
${error.stack}`,
            error
          );
        }
        const err = errorKind === "INTERNAL_ERROR" ? new InternalRuntimeError(message,
        error.stack) : new UserRuntimeError(message, error.stack);
        ttConsole_default2.log(`wrapError-${desc}`, err);
        reportError(err, instance._nativeApp, {
          runType,
          __sourcemap__release__: instance.__sourcemap__release__,
          getSourceMapRelease: instance.getSourceMapRelease
        });
      }
    };
  }
  function wrapInnerFunction(desc, instance, callback, runType = LYNX_CORE) {
    if (!isFunction(callback))
      return noop;
    return wrapFunction("INTERNAL_ERROR", desc, callback, instance, runType);
  }

  // src/modules/report/reporter.ts
  var Reporter = class {
    constructor(getApp, getNativeApp) {
      this.getApp = getApp;
      this.getNativeApp = getNativeApp;
      // /**
      //  * key url -> value sourcemap
      //  * support different sourcemap for external js
      //  */
      // sourcemaps: Record<string, string> = {};
      /**
       * Set sourcemap release with a newly thrown error
       * @param {Error} error
       * The error thrown from the file that wants to set sourcemap release.
       * The top frame of `error.stack` **must be** the filename.
       * The `error.name` **must be** `'LynxGetSourceMapReleaseError'`.
       * The `error.message` **must be** the sourcemap release.
       *
       * @example
       * (function () {
       *   try {
       *     throw new Error(sourcemapRelease);
       *   } catch (e) {
       *     e.name = 'LynxGetSourceMapReleaseError';
       *     tt.setSourceMapRelease(e);
       *   }
       * })()
       */
      this.setSourceMapRelease = (error) => {
        if (isError(error) && error.name === BaseApp.kGetSourceMapReleaseErrorName &&
        isString(error.message) && isString(error.stack)) {
          this.getNativeApp().__SetSourceMapRelease({
            name: error.name,
            message: error.message,
            stack: error.stack
          });
          return;
        }
        alog(`setSourceMapRelease failed with error: ${JSON.stringify(error)}`);
      };
      this.getSourceMapRelease = (url) => {
        let ret = this.getNativeApp().__GetSourceMapRelease(url);
        if (!ret) {
          ret = this.getNativeApp().__GetSourceMapRelease(
            BaseApp.kDefaultSourceMapURL
          );
        }
        return ret;
      };
      this.getApp = getApp;
      this.getNativeApp = getNativeApp;
    }
    rebind(getApp) {
      this.getApp = getApp;
    }
  };

  // src/modules/animation/animation.ts
  var _Animation = class _Animation {
    constructor(effect) {
      this.effect = effect;
      this.id = "__lynx-inner-js-animation-" + _Animation.count++;
    }
    cancel() {
      this.effect.target.cancelAnimate(this);
    }
    pause() {
      this.effect.target.pauseAnimate(this);
    }
    play() {
      this.effect.target.playAnimate(this);
    }
  };
  _Animation.count = 0;
  var Animation = _Animation;

  // src/modules/animation/effect.ts
  var KeyframeEffect = class {
    constructor(target, keyframes, options) {
      this.target = target;
      this.keyframes = keyframes;
      this.options = options;
    }
  };
  var KeyframeEffectV2 = class {
    constructor(keyframes, options) {
      this.keyframes = keyframes;
      this.options = options;
    }
  };

  // src/modules/animation/animationV2.ts
  var AnimationV2 = class {
    constructor(id, keyframes, options) {
      this.id = id;
      this.effect = new KeyframeEffectV2(keyframes, options);
    }
  };

  // src/modules/element/element.ts
  var Element = class {
    constructor(root, id, lynxProxy) {
      this._root = root;
      this._idSelector = "#" + id;
      this._lynx = lynxProxy;
      this._element = void 0;
    }
    ensureElement() {
      if (!this._element) {
        this._element = this._lynx.createElement(this._root, this._idSelector);
      }
    }
    // keyframes: see https://developer.mozilla.org/en-US/docs/Web/API/Web_Animations_API/Keyframe_Formats
    //  Either an array of keyframe objects, or a keyframe object whose property are arrays of values to iterate over. See Keyframe Formats for more details.
    //
    // timingOptions: see https://developer.mozilla.org/en-US/docs/Web/API/Element/animate
    //  id Optional: A property unique to animate(): a DOMString with which to reference the animation.
    //  delay Optional: The number of milliseconds to delay the start of the animation. Defaults to 0.
    //  direction Optional: Whether the animation runs forwards (normal), backwards (reverse), switches direction after each iteration (alternate), or runs backwards and switches direction after each iteration (alternate-reverse). Defaults to "normal".
    //  duration Optional: The number of milliseconds each iteration of the animation takes to complete. Defaults to 0. Although this is technically optional, keep in mind that your animation will not run if this value is 0.
    //  easing Optional: The rate of the animation's change over time. Accepts the pre-defined values "linear", "ease", "ease-in", "ease-out", and "ease-in-out", or a custom "cubic-bezier" value like "cubic-bezier(0.42, 0, 0.58, 1)". Defaults to "linear".
    //  endDelay Optional: The number of milliseconds to delay after the end of an animation. This is primarily of use when sequencing animations based on the end time of another animation. Defaults to 0.
    //  fill Optional: Dictates whether the animation's effects should be reflected by the element(s) prior to playing ("backwards"), retained after the animation has completed playing ("forwards"), or both. Defaults to "none".
    //  iterationStart Optional: Describes at what point in the iteration the animation should start. 0.5 would indicate starting halfway through the first iteration for example, and with this value set, an animation with 2 iterations would end halfway through a third iteration. Defaults to 0.0.
    // iterations Optional: The number of times the animation should repeat. Defaults to 1, and can also take a value of Infinity to make it repeat for as long as the element exists.
    animate(keyframes, timingOptions) {
      this.ensureElement();
      let ani = new Animation(new KeyframeEffect(this, keyframes, timingOptions));
      this._element.animate(0, ani.id, keyframes, timingOptions);
      return ani;
    }
    playAnimate(ani) {
      this._element.animate(1, ani.id, void 0, void 0);
    }
    pauseAnimate(ani) {
      this._element.animate(2, ani.id, void 0, void 0);
    }
    cancelAnimate(ani) {
      this._element.animate(3, ani.id, void 0, void 0);
    }
    finishAnimate(ani) {
      this._element.animate(4, ani.id, void 0, void 0);
    }
    setProperty(propsObj, propsVal) {
      this.ensureElement();
      if (typeof propsObj === "string" && typeof propsVal === "string") {
        this._element.setProperty({
          [propsObj]: propsVal
        });
      } else if (typeof propsObj === "object") {
        this._element.setProperty(propsObj);
      } else {
        throw new Error(
          `setProperty's param must be string or object. While current type is ${typeof propsObj}\
 and ${typeof propsVal}.`
        );
      }
    }
  };

  // src/modules/element/index.ts
  var element_default = Element;

  // src/modules/fetch/TextDecoder.ts
  var TextDecoder = class {
    constructor() {
    }
    decode(buffer) {
      if (buffer.byteLength === 0) {
        return "";
      }
      if (buffer instanceof DataView) {
        buffer = buffer.buffer.slice(
          buffer.byteOffset,
          buffer.byteOffset + buffer.byteLength
        );
      } else if (ArrayBuffer.isView(buffer)) {
        buffer = buffer.buffer;
      }
      return globalThis.TextCodecHelper.decode(buffer);
    }
    encodeInto() {
      throw TypeError("TextEncoder().encodeInto not supported");
    }
    get encoding() {
      return "utf-8";
    }
    get fatal() {
      return false;
    }
    get ignoreBOM() {
      return true;
    }
  };

  // src/modules/fetch/TextEncoder.ts
  var TextEncoder = class {
    constructor() {
    }
    encode(str) {
      return new Uint8Array(globalThis.TextCodecHelper.encode(str));
    }
    encodeInto() {
      throw TypeError("TextEncoder().encodeInto not supported");
    }
    get encoding() {
      return "utf-8";
    }
  };

  // src/modules/event/eventEmitter.ts
  var EventEmitter = class {
    constructor(callLynxSetModule) {
      this._internal_callLynxSetModule = callLynxSetModule;
      this._events = /* @__PURE__ */ new Map();
    }
    getEventsSize(eventType) {
      var _a3;
      return (_a3 = this._events.get(eventType)) == null ? void 0 : _a3.length;
    }
    setCallLynxSetModule(callLynxSetModule) {
      this._internal_callLynxSetModule = callLynxSetModule;
    }
    addListener(eventName, listener, context) {
      const event = this._events.get(eventName);
      if (eventName == "keyboardstatuschanged") {
        if (this._internal_callLynxSetModule) {
          this._internal_callLynxSetModule("switchKeyBoardDetect", [true]);
        }
      }
      if (event) {
        event.push({
          listener,
          context
        });
      } else {
        this._events.set(eventName, [
          {
            listener,
            context
          }
        ]);
      }
    }
    removeListener(eventName, listener) {
      if (typeof listener !== "function") {
        throw new Error("removeListener only takes instances of Function");
      }
      const events = this._events.get(eventName);
      let index = 0;
      if (Array.isArray(events)) {
        const flag = events.some((item) => {
          if (listener === item.listener) {
            return true;
          }
          index++;
        });
        flag && events.splice(index, 1);
      }
      if (eventName == "keyboardstatuschanged") {
        if (this._internal_callLynxSetModule) {
          this._internal_callLynxSetModule("switchKeyBoardDetect", [false]);
        }
      }
    }
    emit(eventName, data) {
      const events = this._events.get(eventName);
      if (Array.isArray(events)) {
        events.forEach((item) => {
          const { listener, context } = item;
          if (typeof listener === "function") {
            listener.apply(context || this, data);
          }
        });
      }
    }
    removeAllListeners(eventName) {
      if (typeof eventName === "string") {
        this._events.delete(eventName);
        return;
      }
      this._events = /* @__PURE__ */ new Map();
    }
    trigger(eventName, params2) {
      const events = this._events.get(eventName);
      if (Array.isArray(events)) {
        if (typeof params2 === "string") {
          params2 = JSON.parse(params2);
        }
        events.forEach((item) => {
          const { listener, context } = item;
          if (typeof listener === "function") {
            listener.call(context || this, params2);
          }
        });
      }
    }
    toggle(eventName, ...data) {
      this.emit(eventName, data);
    }
  };
  function createEventEmitter() {
    return new EventEmitter();
  }

  // src/modules/event/aop.ts
  var AopManager = class {
    constructor() {
      this._beforePublishEvent = new BeforePublishEvent();
    }
  };
  var BeforePublishEvent = class extends EventEmitter {
    add(eventName, callback, context) {
      super.addListener(eventName, callback, context);
      return this;
    }
    remove(eventName, callback) {
      super.removeListener(eventName, callback);
      return this;
    }
  };

  // src/modules/event/index.ts
  var event_default = EventEmitter;

  // src/modules/fetch/ReadableStream.ts
  var LynxReadableStream = class {
  };
  function createReadableStreamClass(Promise2) {
    return class ReadableStream extends LynxReadableStream {
      constructor() {
        super();
        this.__dataReceived = [];
        this.__done = false;
        this.__cancelled = false;
        this.__locked = false;
        this.__eventCenter = new event_default();
      }
      onData(data) {
        if (this.__cancelled) {
          return;
        }
        this.__dataReceived.push(data);
        this.__eventCenter.emit("waitSignal", null);
      }
      onEnd() {
        this.__done = true;
        this.__eventCenter.emit("waitSignal", null);
      }
      onError(error) {
        this.__error = new Error(error);
        this.__eventCenter.emit("waitSignal", null);
      }
      processRead(resolve, reject) {
        if (this.__error) {
          return reject(this.__error);
        }
        if (this.__cancelled || this.__done && this.__dataReceived.length == 0) {
          return resolve({ done: true, value: void 0 });
        }
        if (this.__dataReceived.length > 0) {
          const currData = this.__dataReceived.shift();
          return resolve({ done: false, value: currData });
        }
        const waitSignal = () => {
          this.__eventCenter.removeListener("waitSignal", waitSignal);
          this.processRead(resolve, reject);
        };
        this.__eventCenter.addListener("waitSignal", waitSignal, this);
      }
      __read() {
        return new Promise2((resolve, reject) => {
          this.processRead(resolve, reject);
        });
      }
      get locked() {
        return this.__locked;
      }
      cancel(reason) {
        this.__cancelled = true;
        this.__dataReceived = null;
        this.__eventCenter.emit("waitSignal", null);
        return Promise2.resolve(reason);
      }
      getReader() {
        if (this.__locked) {
          return null;
        }
        this.__locked = true;
        return new ReadableStreamDefaultReader(this);
      }
    };
  }
  var ReadableStreamDefaultReader = class {
    constructor(stream) {
      this.__stream = stream;
    }
    cancel(reason) {
      return this.__stream.cancel(reason);
    }
    read() {
      return this.__stream.__read();
    }
  };

  // src/modules/fetch/BodyMixin.ts
  var BodyMixin = class _BodyMixin {
    constructor() {
      this._arrayBuffer = new ArrayBuffer(0);
      this._bodyStream = null;
      this._bodyUsed = false;
    }
    safeUseBody(use) {
      if (this._bodyUsed) {
        return void 0;
      }
      const ret = use(this._arrayBuffer);
      this._bodyUsed = true;
      this._arrayBuffer = null;
      return ret;
    }
    cloneArrayBuffer(src) {
      return src.slice(0);
    }
    setBody(body) {
      if (body instanceof _BodyMixin) {
        if (body._bodyUsed || body._bodyStream) {
          throw new Error("body used, or try to copy body stream");
        }
        this._arrayBuffer = this.cloneArrayBuffer(body._arrayBuffer);
      } else {
        if (body instanceof ArrayBuffer) {
          this._arrayBuffer = this.cloneArrayBuffer(body);
        } else if (body instanceof DataView) {
          this._arrayBuffer = this.cloneArrayBuffer(
            body.buffer.slice(body.byteOffset, body.byteOffset + body.byteLength)
          );
        } else if (ArrayBuffer.isView(body)) {
          this._arrayBuffer = this.cloneArrayBuffer(body.buffer);
        } else if (body) {
          this._arrayBuffer = new TextEncoder().encode(body.toString()).buffer;
        }
        if (body instanceof LynxReadableStream) {
          this._bodyStream = body;
        }
      }
    }
    arrayBuffer() {
      return Promise.resolve(this.safeUseBody((body) => body));
    }
    get body() {
      if (this._bodyUsed) {
        throw new Error("body used");
      }
      this._bodyUsed = true;
      return this._bodyStream;
    }
    text() {
      return Promise.resolve(
        this.safeUseBody((body) => new TextDecoder().decode(body))
      );
    }
    json() {
      return Promise.resolve(
        this.safeUseBody((body) => JSON.parse(new TextDecoder().decode(body)))
      );
    }
    // TODO(huzhanbo.luc): these APIs rely on foundamental types
    // which require extra works to support, we will support these
    // later when we have implemented these types.
    // blob(): Blob;
    // formData(): FormData;
    // cloneStream(): ReadableStream;
    get bodyUsed() {
      return this._bodyUsed;
    }
  };

  // src/modules/fetch/Headers.ts
  var _a;
  var Headers2 = class _Headers {
    constructor(init) {
      this._headers_map = /* @__PURE__ */ new Map();
      this[_a] = "Headers";
      if (init === null || typeof init === "number") {
        throw new TypeError(`Headers init with null/number`);
      }
      if (init instanceof _Headers) {
        for (const [key, value] of init) {
          this.append(key, value);
        }
      } else if (Array.isArray(init)) {
        init.forEach(([name, value]) => {
          this.append(name, Array.isArray(value) ? value.join(" ") : value);
        });
      } else if (init) {
        Object.getOwnPropertyNames(init).forEach((name) => {
          const value = init[name];
          this.append(name, Array.isArray(value) ? value.join(" ") : value);
        });
      }
    }
    [(_a = Symbol.toStringTag, Symbol.iterator)]() {
      return this.entries();
    }
    *keys() {
      for (const [key, value] of this._headers_map) {
        yield key;
      }
    }
    *values() {
      for (const [key, value] of this._headers_map) {
        yield value;
      }
    }
    *entries() {
      for (const entry of this._headers_map) {
        yield entry;
      }
    }
    /**
     * Returns a boolean stating whether a `Headers` object contains a certain header.
     */
    has(name) {
      return this._headers_map.has(name);
    }
    /**
     * Returns a `ByteString` sequence of all the values of a header with a given name.
     */
    get(name) {
      var _a3;
      return (_a3 = this._headers_map.get(name)) != null ? _a3 : null;
    }
    /**
     * Sets a new value for an existing header inside a `Headers` object, or adds the header if it does not already exist.
     */
    set(name, value) {
      this._headers_map.set(name, String(value));
    }
    /**
     * Appends a new value onto an existing header inside a `Headers` object, or adds the header if it does not already exist.
     */
    append(name, value) {
      let resolvedValue = this.has(name) ? `${this.get(name)}, ${value}` : value;
      this.set(name, resolvedValue);
    }
    /**
     * Deletes a header from the `Headers` object.
     */
    delete(name) {
      if (!this.has(name)) {
        return;
      }
      this._headers_map.delete(name);
    }
    /**
     * Traverses the `Headers` object,
     * calling the given callback for each header.
     */
    forEach(callback, thisArg) {
      for (const [name, value] of this.entries()) {
        callback.call(thisArg, value, name, this);
      }
    }
  };

  // src/modules/fetch/AbortController.ts
  var AbortSignal = class _AbortSignal extends event_default {
    get aborted() {
      return this._aborted;
    }
    get reason() {
      return this._reason;
    }
    constructor() {
      super();
      this._aborted = false;
    }
    get [Symbol.toStringTag]() {
      return "[object AbortSignal]";
    }
    dispatchEvent(event) {
      if (event.type === "abort") {
        this._aborted = true;
        this._reason = event.reason;
        if (typeof this.onabort === "function") {
          this.onabort.call(this, event);
        }
      }
      super.emit(event.type, event);
    }
    addEventListener(type, listener) {
      super.addListener(type, listener);
    }
    removeEventListener(type, listener) {
      super.removeListener(type, listener);
    }
    static __create() {
      return new _AbortSignal();
    }
  };
  var AbortController = class {
    get signal() {
      return this._signal;
    }
    constructor() {
      this._signal = AbortSignal.__create();
    }
    abort(reason) {
      let signalReason = reason;
      if (signalReason === void 0) {
        signalReason = new Error("This operation was aborted");
        signalReason.name = "AbortError";
      }
      const event = {
        type: "abort",
        reason: signalReason
      };
      this.signal.dispatchEvent(event);
    }
    get [Symbol.toStringTag]() {
      return "[object AbortController]";
    }
  };

  // src/modules/fetch/Request.ts
  var Request = class _Request extends BodyMixin {
    get url() {
      return this._url;
    }
    get headers() {
      return this._headers;
    }
    get method() {
      return this._method;
    }
    get signal() {
      return this._signal;
    }
    get lynxExtension() {
      return this._lynxExtension;
    }
    constructor(input, options) {
      super();
      options = options || {};
      if (input instanceof _Request) {
        if (input.bodyUsed) {
          throw new TypeError("Already read");
        }
        this._url = input.url;
        if (!options.headers) {
          this._headers = new Headers2(input.headers);
        }
        this._method = input.method;
        this._signal = input.signal;
        this.setBody(input._arrayBuffer);
      } else {
        this._url = String(input);
      }
      if (options.headers || !this.headers) {
        this._headers = new Headers2(options.headers);
      }
      this._method = options.method || this.method || "GET";
      this._method = this._method.toUpperCase();
      if ((this.method === "GET" || this.method === "HEAD") && options.body) {
        throw new TypeError("Body not allowed for GET or HEAD requests");
      }
      if (typeof options.signal !== "undefined") {
        this._signal = options.signal;
      }
      this._signal = this._signal || AbortSignal.__create();
      this._lynxExtension = options.lynxExtension || {};
      if (!this._headers.get("Content-Type")) {
        if (typeof options.body === "string") {
          this._headers.set("Content-Type", "text/plain;charset=UTF-8");
        } else if (globalThis.URLSearchParams && options.body instanceof URLSearchParams) {
          this._headers.set(
            "Content-Type",
            "application/x-www-form-urlencoded;charset=UTF-8"
          );
        } else if (options.body instanceof ArrayBuffer) {
        } else {
          this._headers.set("Content-Type", "text/plain;charset=UTF-8");
        }
      }
      this.setBody(options.body);
    }
    clone() {
      const cloned = new _Request(this, {
        method: this.method
      });
      cloned.setBody(this);
      return cloned;
    }
  };

  // src/modules/fetch/Response.ts
  var Response = class _Response extends BodyMixin {
    get url() {
      return this._url;
    }
    get status() {
      return this._status;
    }
    get statusText() {
      return this._statusText;
    }
    get ok() {
      return this._ok;
    }
    get headers() {
      return this._headers;
    }
    get lynxExtension() {
      return this._lynxExtension;
    }
    constructor(bodyInit, options) {
      super();
      options = options || {};
      this._status = options.status === void 0 ? 200 : options.status;
      if (this._status < 200 || this._status > 599) {
        throw new RangeError(
          "Failed to construct 'Response': The status provided (0) is outside th\
e range [200, 599]."
        );
      }
      this._ok = this._status >= 200 && this._status < 300;
      this._statusText = options.statusText === void 0 ? "" : "" + options.statusText;
      this._headers = new Headers(options.headers);
      this._url = options.url || "";
      this._lynxExtension = options.lynxExtension || {};
      this.setBody(bodyInit);
    }
    clone() {
      const cloned = new _Response(null, {
        status: this._status,
        statusText: this._statusText,
        headers: new Headers(this._headers),
        url: this._url
      });
      cloned.setBody(this);
      return cloned;
    }
  };

  // src/modules/fetch/URL.js
  function validateBaseUrl(url) {
    return /^(?:(?:(?:https?|ftp):)?\/\/)(?:(?:[1-9]\d?|1\d\d|2[01]\d|22[0-3])(?:\.(?:1?\d{1,2}|2[0-4]\d|25[0-5])){2}(?:\.(?:[1-9]\d?|1\d\d|2[0-4]\d|25[0-4]))|(?:(?:[a-z0-9\u00a1-\uffff][a-z0-9\u00a1-\uffff_-]{0,62})?[a-z0-9\u00a1-\uffff]\.)*(?:[a-z\u00a1-\uffff]{2,}\.?))(?::\d{2,5})?(?:[/?#]\S*)?$/.
    test(
      url
    );
  }
  var URL = class {
    constructor(url, base) {
      __publicField(this, "_url");
      __publicField(this, "_searchParamsInstance", null);
      let baseUrl = null;
      if (!base || validateBaseUrl(url)) {
        this._url = url;
        if (!this._url.endsWith("/")) {
          this._url += "/";
        }
      } else {
        if (typeof base === "string") {
          baseUrl = base;
          if (!validateBaseUrl(baseUrl)) {
            throw new TypeError(`Invalid base URL: ${baseUrl}`);
          }
        } else {
          baseUrl = base.toString();
        }
        if (baseUrl.endsWith("/")) {
          baseUrl = baseUrl.slice(0, baseUrl.length - 1);
        }
        if (!url.startsWith("/")) {
          url = `/${url}`;
        }
        if (baseUrl.endsWith(url)) {
          url = "";
        }
        this._url = `${baseUrl}${url}`;
      }
    }
    get href() {
      return this.toString();
    }
    get searchParams() {
      if (this._searchParamsInstance == null) {
        this._searchParamsInstance = new URLSearchParams();
      }
      return this._searchParamsInstance;
    }
    toJSON() {
      return this.toString();
    }
    toString() {
      if (this._searchParamsInstance === null) {
        return this._url;
      }
      const instanceString = this._searchParamsInstance.toString();
      const separator = this._url.indexOf("?") > -1 ? "&" : "?";
      return this._url + separator + instanceString;
    }
  };

  // src/modules/fetch/UrlSearchParamsPolyfill.js
  function URLSearchParamsPolyfill(self) {
    "use strict";
    var _a3;
    const __URLSearchParams__ = "__URLSearchParams__";
    function URLSearchParamsPolyfill2(search) {
      search = search || "";
      if (search instanceof URLSearchParams) {
        search = search.toString();
      }
      this[__URLSearchParams__] = parseToDict(search);
    }
    const prototype = URLSearchParamsPolyfill2.prototype;
    prototype.append = function(name, value) {
      appendTo(this[__URLSearchParams__], name, value);
    };
    prototype["delete"] = function(name) {
      delete this[__URLSearchParams__][name];
    };
    prototype.get = function(name) {
      var dict = this[__URLSearchParams__];
      return this.has(name) ? dict[name][0] : null;
    };
    prototype.getAll = function(name) {
      var dict = this[__URLSearchParams__];
      return this.has(name) ? dict[name].slice(0) : [];
    };
    prototype.has = function(name) {
      return hasOwnProperty(this[__URLSearchParams__], name);
    };
    prototype.set = function set(name, value) {
      this[__URLSearchParams__][name] = ["" + value];
    };
    prototype.toString = function() {
      var dict = this[__URLSearchParams__], query = [], i, key, name, value;
      for (key in dict) {
        name = encode(key);
        for (i = 0, value = dict[key]; i < value.length; i++) {
          query.push(name + "=" + encode(value[i]));
        }
      }
      return query.join("&");
    };
    prototype.polyfill = true;
    prototype[Symbol.toStringTag] = "URLSearchParams";
    prototype.forEach = function(callback, thisArg) {
      var dict = parseToDict(this.toString());
      Object.getOwnPropertyNames(dict).forEach(function(name) {
        dict[name].forEach(function(value) {
          callback.call(thisArg, value, name, this);
        }, this);
      }, this);
    };
    prototype.sort = function() {
      var dict = parseToDict(this.toString()), keys = [], k, i, j;
      for (k in dict) {
        keys.push(k);
      }
      keys.sort();
      for (i = 0; i < keys.length; i++) {
        this["delete"](keys[i]);
      }
      for (i = 0; i < keys.length; i++) {
        var key = keys[i], values = dict[key];
        for (j = 0; j < values.length; j++) {
          this.append(key, values[j]);
        }
      }
    };
    prototype.keys = function() {
      var items = [];
      this.forEach(function(item, name) {
        items.push(name);
      });
      return makeIterator(items);
    };
    prototype.values = function() {
      var items = [];
      this.forEach(function(item) {
        items.push(item);
      });
      return makeIterator(items);
    };
    prototype.entries = function() {
      var items = [];
      this.forEach(function(item, name) {
        items.push([name, item]);
      });
      return makeIterator(items);
    };
    prototype[Symbol.iterator] = prototype.entries;
    Object.defineProperty(prototype, "size", {
      get: function() {
        var dict = parseToDict(this.toString());
        if (prototype === this) {
          throw new TypeError("Illegal invocation at URLSearchParams.invokeGette\
r");
        }
        return Object.keys(dict).reduce(function(prev, cur) {
          return prev + dict[cur].length;
        }, 0);
      }
    });
    function encode(str) {
      var replace = {
        "!": "%21",
        "'": "%27",
        "(": "%28",
        ")": "%29",
        "~": "%7E",
        "%20": "+",
        "%00": "\0"
      };
      return encodeURIComponent(str).replace(/[!'\(\)~]|%20|%00/g, function(match) {
        return replace[match];
      });
    }
    function decode(str) {
      return str.replace(/[ +]/g, "%20").replace(/(%[a-f0-9]{2})+/ig, function(match) {
        return decodeURIComponent(match);
      });
    }
    function makeIterator(arr) {
      var iterator = {
        next: function() {
          var value = arr.shift();
          return { done: value === void 0, value };
        }
      };
      iterator[Symbol.iterator] = function() {
        return iterator;
      };
      return iterator;
    }
    function parseToDict(search) {
      var dict = {};
      if (typeof search === "object") {
        if (isArray(search)) {
          for (var i = 0; i < search.length; i++) {
            var item = search[i];
            if (isArray(item) && item.length === 2) {
              appendTo(dict, item[0], item[1]);
            } else {
              throw new TypeError("Failed to construct 'URLSearchParams': Sequen\
ce initializer must only contain pair elements");
            }
          }
        } else {
          for (var key in search) {
            if (search.hasOwnProperty(key)) {
              appendTo(dict, key, search[key]);
            }
          }
        }
      } else {
        if (search.indexOf("?") === 0) {
          search = search.slice(1);
        }
        var pairs = search.split("&");
        for (var j = 0; j < pairs.length; j++) {
          var value = pairs[j], index = value.indexOf("=");
          if (-1 < index) {
            appendTo(dict, decode(value.slice(0, index)), decode(value.slice(index +
            1)));
          } else {
            if (value) {
              appendTo(dict, decode(value), "");
            }
          }
        }
      }
      return dict;
    }
    function appendTo(dict, name, value) {
      var val = typeof value === "string" ? value : value !== null && value !== void 0 &&
      typeof value.toString === "function" ? value.toString() : JSON.stringify(value);
      if (hasOwnProperty(dict, name)) {
        dict[name].push(val);
      } else {
        dict[name] = [val];
      }
    }
    function isArray(val) {
      return !!val && "[object Array]" === Object.prototype.toString.call(val);
    }
    function hasOwnProperty(obj, prop) {
      return Object.prototype.hasOwnProperty.call(obj, prop);
    }
    self.URLSearchParams = (_a3 = self.URLSearchParams) != null ? _a3 : URLSearchParamsPolyfill2;
  }

  // src/modules/fetch/EventSource.ts
  function createEventSource(fetch) {
    return class EventSource {
      constructor(url, options = {}) {
        this.listeners = {};
        this.url = url;
        this.options = options;
        this._closed = false;
        this._connect();
      }
      close() {
        this._closed = true;
      }
      _dispatchEvent(type, event) {
        const eventToDispatch = {
          type,
          detail: event,
          timestamp: Date.now(),
          target: {},
          currentTarget: {},
          preventDefault: () => {
          },
          stopPropagation: () => {
          }
        };
        if (type === "message" && this.onmessage) {
          this.onmessage(event);
        } else if (type === "error" && this.onerror) {
          this.onerror(eventToDispatch);
        } else if (type === "open" && this.onopen) {
          this.onopen(eventToDispatch);
        }
        const listeners = this.listeners[type] || [];
        listeners.forEach((listener) => listener(event));
      }
      addEventListener(type, listener) {
        this.listeners[type] = this.listeners[type] || [];
        this.listeners[type].push(listener);
      }
      removeEventListener(type, listener) {
        this.listeners[type] = this.listeners[type] || [];
        this.listeners[type] = this.listeners[type].filter((l) => l !== listener);
      }
      async _connect() {
        try {
          const response = await fetch(this.url, {
            ...this.options,
            lynxExtension: {
              useStreaming: true
            }
          });
          this._dispatchEvent("open", { data: "" });
          const reader = response.body.getReader();
          while (true) {
            const { done, value } = await reader.read();
            if (done)
              break;
            const rawEvent = globalThis.TextCodecHelper.decode(value);
            const event = this._parseEvent(rawEvent);
            if (event) {
              this._dispatchEvent(event.event || "message", event);
            }
          }
        } catch (err) {
          this._dispatchEvent("error", { data: "", error: err });
        }
      }
      _parseEvent(raw) {
        const lines = raw.split("\n");
        let event = { data: "" };
        for (const line of lines) {
          if (line.startsWith("data:")) {
            event.data += line.slice(5).trim() + "\n";
          } else if (line.startsWith("event:")) {
            event.event = line.slice(6).trim();
          } else if (line.startsWith("id:")) {
            event.id = line.slice(3).trim();
          }
        }
        if (event.data)
          event.data = event.data.slice(0, -1);
        return event.data ? event : null;
      }
    };
  }

  // src/modules/selectorQuery/SelectorQuery.ts
  var SelectorQuery = class _SelectorQuery {
    constructor(component, taskQueue, proxy) {
      this._component = component;
      this._taskQueue = taskQueue;
      this._native_proxy = proxy;
      this._fire_immediately = false;
      this._root_unique_id = void 0;
    }
    static fromQuery(prevQuery, component) {
      return new _SelectorQuery(
        component != null ? component : prevQuery._component,
        prevQuery._taskQueue.slice(),
        prevQuery._native_proxy
      );
    }
    static newEmptyQuery(proxy, component) {
      return new _SelectorQuery(component != null ? component : "", [], proxy);
    }
    /**
     * According to `this._fire_immediately`,
     * either execute the query immediately or add it to the task queue of the SelectorQuery.
     * In the latter case, a new query is returned, and `this` is not modified.
     * @param task the task to commit
     */
    commitTask(task) {
      let new_query = _SelectorQuery.fromQuery(this, this._component);
      new_query._taskQueue.push(task);
      if (this._fire_immediately) {
        new_query.exec();
        return void 0;
      }
      return new_query;
    }
    in(component) {
      return component.createSelectorQuery(this);
    }
    /**
     * Selects a single node by CSS selector.
     * @param selector CSS selector
     */
    select(selector) {
      return new NodesRef(this, {
        type: 0 /* ID_SELECTOR */,
        identifier: selector,
        component_id: this._component,
        root_unique_id: this._root_unique_id,
        first_only: true
      });
    }
    /**
     * Selects all nodes satisfying CSS selector.
     * @param selector CSS selector
     */
    selectAll(selector) {
      return new NodesRef(this, {
        type: 0 /* ID_SELECTOR */,
        identifier: selector,
        component_id: this._component,
        root_unique_id: this._root_unique_id,
        first_only: false
      });
    }
    /**
     * Selects a single node as React ref.
     * When works as ReactRef, SelectorQuery should act like getNodeRef, which means:
     * 1. cascade query is disabled.
     * 2. tasks are executed immediately without calling exec().
     */
    selectReactRef(ref_string) {
      if (this._taskQueue.length) {
        const errorMessage = "selectReactRef() should be called before any other\
 selector query methods";
        nativeConsole.warn(errorMessage);
        const error = new Error(errorMessage);
        reportError(
          new InvokeError(errorMessage, error.stack),
          this._native_proxy.nativeApp
        );
        return;
      }
      this._fire_immediately = true;
      return new NodesRef(this, {
        type: 1 /* REF_ID */,
        identifier: ref_string,
        component_id: this._component,
        root_unique_id: this._root_unique_id,
        first_only: true
      });
    }
    /**
     * Select root node of the component.
     */
    selectRoot() {
      return this.select("");
    }
    /**
     * Selects a single node by element id.
     * When a touch event is triggered, the element id of the node is passed to the event handler as 'uid',
     * by which can a node be selected in its event handler.
     */
    selectUniqueID(uniqueId) {
      return new NodesRef(this, {
        type: 2 /* UNIQUE_ID */,
        identifier: uniqueId.toString(),
        component_id: this._component,
        root_unique_id: this._root_unique_id,
        first_only: true
      });
    }
    /**
     * Execute all tasks in the task queue.
     * When `this._fire_immediately` is set to true, this method is called automatically.
     */
    exec() {
      for (let i = 0; i < this._taskQueue.length; ++i) {
        this._taskQueue[i](this._native_proxy);
      }
    }
    setRoot(uniqueId) {
      this._root_unique_id = Number(uniqueId);
      return this;
    }
  };
  var NodesRef = class {
    constructor(selectorQuery, nodeSelectToken) {
      this._nodeSelectToken = nodeSelectToken;
      this._selectorQuery = selectorQuery;
    }
    invoke(options) {
      let errorStack;
      if (true) {
        errorStack = new Error("");
      }
      let task = (proxy) => {
        var _a3;
        let callback = (res) => {
          if (res.code === 0 /* SUCCESS */) {
            options.success && options.success(res.data);
          } else {
            if (options.fail) {
              options.fail(res);
            } else {
              if (true) {
                if (!proxy.lynx._switches.disableSelectorQueryWarningWhenFailed) {
                  const errorMessage = `Failed to exec createSelectorQuery().inv\
oke() on NodesRef ${JSON.stringify(
                    this._nodeSelectToken
                  )}. Add a fail callback to suppress this warning. Msg: ${JSON.
                  stringify(
                    res
                  )}`;
                  nativeConsole.warn(errorMessage);
                  reportError(
                    new InvokeError(errorMessage, errorStack.stack),
                    proxy.nativeApp
                  );
                }
              }
            }
          }
        };
        if (!this._nodeSelectToken.first_only) {
          callback({
            code: 5 /* SELECTOR_NOT_SUPPORTED */,
            data: "selectAll not supported for invoke method"
          });
          return;
        }
        proxy.nativeApp.invokeUIMethod(
          this._nodeSelectToken.type,
          this._nodeSelectToken.identifier,
          this._nodeSelectToken.component_id,
          options.method,
          (_a3 = options.params) != null ? _a3 : {},
          callback,
          this._nodeSelectToken.root_unique_id
        );
      };
      return this._selectorQuery.commitTask(task);
    }
    path(cb) {
      let task = (proxy) => {
        let callback = (res) => {
          cb && cb(res.data, res.status);
        };
        proxy.nativeApp.getPathInfo(
          this._nodeSelectToken.type,
          this._nodeSelectToken.identifier,
          this._nodeSelectToken.component_id,
          this._nodeSelectToken.first_only,
          callback,
          this._nodeSelectToken.root_unique_id
        );
      };
      return this._selectorQuery.commitTask(task);
    }
    fields(fields, cb) {
      let task = (proxy) => {
        let callback = (res) => {
          if (fields.query) {
            const addQueryObject = (result) => {
              result.query = SelectorQuery.newEmptyQuery(proxy);
              result.query.setRoot(result.unique_id.toString());
              if (!fields.unique_id) {
                delete result.unique_id;
              }
            };
            if (this._nodeSelectToken.first_only) {
              let result = res.data;
              if (result) {
                addQueryObject(result);
              }
            } else {
              for (let result of res.data) {
                addQueryObject(result);
              }
            }
          }
          cb && cb(res.data, res.status);
        };
        let fields_array = [];
        for (let key in fields) {
          if (key == "query" && fields[key] == true && !fields.unique_id) {
            fields_array.push("unique_id");
            continue;
          }
          if (fields[key]) {
            fields_array.push(key);
          }
        }
        proxy.nativeApp.getFields(
          this._nodeSelectToken.type,
          this._nodeSelectToken.identifier,
          this._nodeSelectToken.component_id,
          this._nodeSelectToken.first_only,
          fields_array,
          callback,
          this._nodeSelectToken.root_unique_id
        );
      };
      return this._selectorQuery.commitTask(task);
    }
    animate(animations) {
      let animationsArray = [];
      if (Array.isArray(animations)) {
        animationsArray = animations;
      } else {
        animationsArray.push(animations);
      }
      let task = (proxy) => {
        animationsArray.forEach((animation) => {
          var _a3, _b2;
          proxy.nativeApp.animate(
            this._nodeSelectToken.type,
            this._nodeSelectToken.identifier,
            this._nodeSelectToken.component_id,
            0 /* START */,
            animation == null ? void 0 : animation.id,
            (_a3 = animation == null ? void 0 : animation.effect) == null ? void 0 :
            _a3.keyframes,
            (_b2 = animation == null ? void 0 : animation.effect) == null ? void 0 :
            _b2.options
          );
        });
      };
      return this._selectorQuery.commitTask(task);
    }
    animationOperate(operation, ids) {
      let idArray = [];
      if (Array.isArray(ids)) {
        idArray = ids;
      } else {
        idArray.push(ids);
      }
      let task = (proxy) => {
        idArray.forEach((id) => {
          proxy.nativeApp.animate(
            this._nodeSelectToken.type,
            this._nodeSelectToken.identifier,
            this._nodeSelectToken.component_id,
            operation,
            id,
            null,
            null
          );
        });
      };
      return this._selectorQuery.commitTask(task);
    }
    playAnimation(ids) {
      return this.animationOperate(1 /* PLAY */, ids);
    }
    pauseAnimation(ids) {
      return this.animationOperate(2 /* PAUSE */, ids);
    }
    cancelAnimation(ids) {
      return this.animationOperate(3 /* CANCEL */, ids);
    }
    finishAnimation(ids) {
      return this.animationOperate(4 /* FINISH */, ids);
    }
    setNativeProps(nativeProps) {
      let task = (proxy) => {
        proxy.nativeApp.setNativeProps(
          this._nodeSelectToken.type,
          this._nodeSelectToken.identifier,
          this._nodeSelectToken.component_id,
          this._nodeSelectToken.first_only,
          nativeProps,
          this._nodeSelectToken.root_unique_id
        );
      };
      return this._selectorQuery.commitTask(task);
    }
  };
  NodesRef.nodePool = {};

  // src/lynx/lynx.ts
  var _a2, _b, _c;
  var _Lynx = class _Lynx {
    constructor(getNativeApp, getApp, Promise2, getNativeLynx) {
      this.getNativeApp = getNativeApp;
      this.getApp = getApp;
      this.Promise = Promise2;
      this.getNativeLynx = getNativeLynx;
      this.setTimeout = this.getApp().wrapReport(
        this.getApp().setTimeout,
        "setTimeout Error"
      );
      this.setInterval = this.getApp().wrapReport(
        this.getApp().setInterval,
        "setInterval Error"
      );
      this.clearInterval = this.getNativeApp().clearInterval;
      this.clearTimeout = this.getNativeApp().clearTimeout;
      this.resumeExposure = this.getApp()._apiList["resumeExposure"];
      this.requireModule = (path2, entryName2, options) => {
        if (this.requireModule.cache[path2]) {
          return this.requireModule.cache[path2];
        }
        const exports = this.getApp().requireModule(path2, entryName2, options);
        this.requireModule.cache[path2] = exports;
        return exports;
      };
      this.requireModuleAsync = (path2, callback) => {
        callback != null ? callback : callback = (error) => {
          if (!error) {
            return;
          }
          this.getApp().handleUserError(error);
        };
        if (this.requireModuleAsync.cache[path2]) {
          callback(null, this.requireModuleAsync.cache[path2]);
          return;
        }
        this.getApp().requireModuleAsync(path2, (error, exports) => {
          if (!error) {
            this.requireModuleAsync.cache[path2] = exports;
          }
          callback(error, exports);
        });
      };
      this.createElement = (rootId, id) => this.getNativeLynx().createElement(rootId,
      id);
      this.getElementById = (id) => {
        return new element_default("", id, this);
      };
      this.reportError = (error, options) => {
        let errorObj;
        if (isError(error)) {
          errorObj = error;
        } else {
          let message;
          if (typeof error !== "string") {
            message = JSON.stringify(error);
          } else {
            message = error;
          }
          errorObj = new Error(message);
        }
        const { level = "error" } = options || {};
        let errorLevel;
        switch (level) {
          case "error":
            errorLevel = 1 /* Error */;
            break;
          case "warning":
            errorLevel = 2 /* Warn */;
            break;
          case "fatal":
            errorLevel = 0 /* Fatal */;
            break;
          default:
            errorLevel = 1 /* Error */;
        }
        this.getApp().handleUserError(errorObj, errorObj.cause, errorLevel);
      };
      this.registerModule = (name, module2) => this.getApp().registerModule(name,
      module2);
      this.getJSModule = (name) => {
        return this.getApp().getJSModule(name);
      };
      this.getTextInfo = this.getApp()._apiList["getTextInfo"];
      this.addFont = (font, callback) => {
        if (!isObject(font)) {
          throw new Error("The first argument must be object type");
        }
        if (!isString(font["font-family"]) || !isString(font["src"])) {
          throw new Error("The font value must have font-family and src");
        }
        if (!isFunction(callback)) {
          throw new Error("The second argument must be function type");
        }
        this.getNativeLynx().addFont(font, callback);
      };
      this.stopExposure = this.getApp()._apiList["stopExposure"];
      this.setObserverFrameRate = this.getApp()._apiList["setObserverFrameRate"];
      this.performance = this.getApp().performance;
      this.beforePublishEvent = this.getApp()._aopManager._beforePublishEvent;
      // sessionStorage Api
      this.setSessionStorageItem = (key, value) => {
        this.dispatchSessionStorageEvent({
          type: "__SetSessionStorageItem" /* EVENT_SET_SESSION_STORAGE */,
          data: {
            key,
            value
          }
        });
      };
      this.getSessionStorageItem = (key, callback) => {
        this.getNativeApp().getSessionStorageItem(key, callback);
      };
      this.subscribeSessionStorage = (key, callback) => {
        let listenerId = _Lynx.__registerSharedDataCounter++;
        this.getNativeApp().subscribeSessionStorage(key, listenerId, callback);
        return listenerId;
      };
      this.unsubscribeSessionStorage = (key, listenerId) => {
        this.dispatchSessionStorageEvent({
          type: "__UnSubscribeSessionStorage" /* EVENT_UNSUBSCRIBE_SESSION_STORAGE */,
          data: {
            key,
            listenerId
          }
        });
      };
      this.getDevtool = this.getNativeLynx().getDevtool;
      this.getCoreContext = this.getNativeLynx().getCoreContext;
      this.getJSContext = this.getNativeLynx().getJSContext;
      this.getUIContext = this.getNativeLynx().getUIContext;
      this.getNative = this.getNativeLynx().getNative;
      this.getEngine = this.getNativeLynx().getEngine;
      this.getCustomSectionSync = this.getNativeLynx().getCustomSectionSync;
      this.accessibilityAnnounce = (_a2 = this.getNativeApp().nativeModuleProxy.
      LynxAccessibilityModule) == null ? void 0 : _a2.accessibilityAnnounce;
      this.requestResourcePrefetch = (_b = this.getNativeApp().nativeModuleProxy.
      LynxResourceModule) == null ? void 0 : _b.requestResourcePrefetch;
      this.cancelResourcePrefetch = (_c = this.getNativeApp().nativeModuleProxy.
      LynxResourceModule) == null ? void 0 : _c.cancelResourcePrefetch;
      this.setSharedData = (dataKey, dataVal) => {
        nativeGlobal_default2.sharedData[dataKey] = dataVal;
        let variable = {};
        variable[dataKey] = dataVal;
        nativeGlobal_default2.shareDataSubject.notifyDataChange(variable);
      };
      this.getSharedData = (dataKey) => {
        var _a3;
        let data = nativeGlobal_default2.sharedData[dataKey];
        if (true) {
          if (data === void 0) {
            data = (_a3 = this.getApp().NativeModules.LynxRecorderReplayDataModule) ==
            null ? void 0 : _a3.getSharedData(
              dataKey
            ).value;
          } else {
            this.getNativeApp().recordSharedData(dataKey, data);
          }
        }
        return data;
      };
      this.registerSharedDataObserver = (callback) => nativeGlobal_default2.shareDataSubject.
      registerObserver(callback);
      this.removeSharedDataObserver = (callback) => nativeGlobal_default2.shareDataSubject.
      removeObserver(callback);
      this.triggerLepusGlobalEvent = (event, params2) => this.getNativeApp().triggerLepusGlobalEvent(
      event, params2);
      // for reload
      this.reload = (value, callback) => {
        this.getNativeLynx().reload(value, callback);
      };
      this.fetchDynamicComponent = (url, options, callback, id) => this.getNativeLynx().
      fetchDynamicComponent(url, options, callback, id);
      // Wrapper QueryComponent to decide if component has loaded.
      this.QueryComponent = (source, callback) => {
        const innerInvokeCallback = () => {
          callback({
            code: 0,
            data: { url: source, sync: true, error_message: "", mode: "cache" },
            detail: { schema: source, cache: false, errMsg: "" }
          });
        };
        if (this.getApp().loadedDynamicComponentsSet.has(source)) {
          innerInvokeCallback();
          return;
        }
        const innerCallback = (result) => {
          if (result.__hasReady === true) {
            nativeGlobal_default2.loadDynamicComponent(this.getApp(), source);
            innerInvokeCallback();
          } else {
            callback(result);
          }
        };
        this.getNativeLynx().QueryComponent(source, innerCallback);
      };
      this.loadDynamicComponent = (idOrUrl, urlOrOptions, options = {}) => {
        return new this.Promise((resolve, reject) => {
          let ids = [];
          let url;
          if (Array.isArray(idOrUrl)) {
            ids = idOrUrl;
            url = urlOrOptions;
          } else if (typeof urlOrOptions === "string") {
            ids = [idOrUrl];
            url = urlOrOptions;
          } else {
            url = idOrUrl;
            options = urlOrOptions;
          }
          if (this.getApp().loadedDynamicComponentsSet.has(url)) {
            resolve({
              code: 0,
              data: { url, sync: false, error_message: "", mode: "normal" },
              detail: { schema: url, cache: false, errMsg: "" }
            });
            return;
          }
          this.getNativeLynx().fetchDynamicComponent(
            url,
            options,
            (res) => {
              if (res && res.code == 0) {
                resolve(res);
              } else {
                reject(res);
              }
            },
            ids
          );
        });
      };
      this.fetch = (input, init) => {
        return new this.Promise((resolve, reject) => {
          const request = new nativeGlobal_default2.Request(input, init);
          const signal = request.signal;
          if (signal.aborted) {
            return reject(signal.reason);
          }
          signal.addEventListener("abort", (event) => {
            reject(signal.reason);
          });
          const fetchArg = {
            method: request.method,
            url: request.url,
            origin: this.getNativeApp().__pageUrl,
            headers: Object.fromEntries(request.headers.entries()),
            body: request._arrayBuffer,
            lynxExtension: request.lynxExtension
          };
          const useStreaming = request.lynxExtension["useStreaming"];
          this.getApp().NativeModules.LynxFetchModule.fetch(
            fetchArg,
            (response) => {
              if (signal.aborted) {
                return;
              }
              try {
                const streamingBodyReceiver = new (this.getApp())._ReadableStreamClass();
                const resp = new nativeGlobal_default2.Response(
                  useStreaming ? streamingBodyReceiver : response.body,
                  response
                );
                if (useStreaming) {
                  const id = resp.lynxExtension["streamingId"];
                  this.getApp().GlobalEventEmitter.addListener(
                    id,
                    (result) => {
                      const event = result.event;
                      if (event === "onData") {
                        streamingBodyReceiver.onData(result.data);
                      } else if (event === "onEnd") {
                        streamingBodyReceiver.onEnd();
                      } else if (event === "onError") {
                        streamingBodyReceiver.onError(result.error);
                      }
                    }
                  );
                }
                resolve(resp);
              } catch (_) {
                reject(new TypeError(response.statusText));
              }
            },
            (error) => {
              if (signal.aborted) {
                return;
              }
              reject(new TypeError(error.message));
            }
          );
        });
      };
      this.EventSource = createEventSource(this.fetch);
      this.createSelectorQuery = (component) => {
        return SelectorQuery.newEmptyQuery(
          {
            nativeApp: this.getNativeApp(),
            lynx: this
          },
          component
        );
      };
      this.requestAnimationFrame = (callback) => this.getNativeApp().requestAnimationFrame(
      callback);
      this.cancelAnimationFrame = (animationId) => this.getNativeApp().cancelAnimationFrame(
      animationId);
      this.loadScript = (url, options) => {
        const { bundleName = DEFAULT_ENTRY } = options;
        const cacheKey = bundleName + ":" + url;
        if (this.loadScript.cache[cacheKey]) {
          return this.loadScript.cache[cacheKey];
        }
        const exports = this.getApp().loadScript(url, options);
        this.loadScript.cache[cacheKey] = exports;
        return exports;
      };
      this.fetchBundle = this.getNativeLynx().fetchBundle;
      this.__addReporterCustomInfo = (info) => {
        this.getNativeApp().__addReporterCustomInfo(info);
      };
      this.getModuleLoader = () => {
        return nativeGlobal_default2["napiLoaderOnRT" + this.getApp().nativeAppId];
      };
      this.createAnimation = (id, keyframes, options) => {
        return new AnimationV2(id, keyframes, options);
      };
      this.init(void 0);
    }
    rebind(getApp) {
      this.init(getApp);
    }
    init(getApp) {
      if (getApp) {
        this.getApp = getApp;
        this.__globalProps = this.getNativeLynx().__globalProps || {};
        this.__presetData = this.getNativeLynx().__presetData || {};
      } else {
        const cache = {};
        this.requireModule.cache = cache;
        this.requireModuleAsync.cache = cache;
        this.loadScript.cache = {};
        this.__globalProps = this.getNativeLynx().__globalProps || {};
        this.__presetData = this.getNativeLynx().__presetData || {};
        this._switches = {};
      }
    }
    dispatchSessionStorageEvent(event) {
      var eventResult = this.getCoreContext().dispatchEvent(event);
      if (eventResult == 0) {
        return;
      }
      this.getJSContext().dispatchEvent(event);
    }
    queueMicrotask(callback) {
      this.getApp().queueMicrotask(callback);
    }
  };
  _Lynx.__registerSharedDataCounter = 0;
  var Lynx = _Lynx;

  // src/modules/nativeModules/textInfo.ts
  var TextInfoManager = class {
    constructor(nativeModules) {
      this._textInfoModule = void 0;
      this.getTextInfo = (param, options) => {
        if (this._textInfoModule === void 0) {
          this._textInfoModule = this._nativeModules.LynxTextInfoModule;
        }
        if (this._textInfoModule && this._textInfoModule.getTextInfo) {
          return this._textInfoModule.getTextInfo(param, options);
        } else {
          return {
            width: param.length
          };
        }
      };
      this._nativeModules = nativeModules;
    }
  };

  // src/modules/nativeModules/exposure.ts
  var ExposureManager = class {
    constructor(nativeModules) {
      this.resumeExposure = () => {
        this._exposureModule.resumeExposure();
      };
      this.stopExposure = (options) => {
        this._exposureModule.stopExposure(options);
      };
      this.setObserverFrameRate = (options) => {
        this._exposureModule.setObserverFrameRate(options);
      };
      this._nativeModules = nativeModules;
      this._exposureModule = this._nativeModules.LynxExposureModule;
    }
  };

  // src/modules/nativeModules/intersectionObserver.ts
  var IntersectionObservationTarget = class {
    constructor(selector, callback) {
      this._selector = selector;
      this._callback = callback;
    }
    invokeCallback(data) {
      this._callback(data);
    }
  };
  var IntersectionObserver = class {
    constructor(id, intersectionObserverModule, manager) {
      this._id = id;
      this._intersectionObserverModule = intersectionObserverModule;
      this._manager = manager;
      this._observationTargets = [];
      this._defaultMargins = {
        left: 0,
        right: 0,
        top: 0,
        bottom: 0
      };
    }
    relativeTo(selector, margins) {
      this._intersectionObserverModule.relativeTo(
        this._id,
        selector,
        margins || this._defaultMargins
      );
      return this;
    }
    relativeToViewport(margins) {
      this._intersectionObserverModule.relativeToViewport(
        this._id,
        margins || this._defaultMargins
      );
      return this;
    }
    relativeToScreen(margins) {
      this._intersectionObserverModule.relativeToScreen(
        this._id,
        margins || this._defaultMargins
      );
      return this;
    }
    observe(selector, callback) {
      this._observationTargets.push(
        new IntersectionObservationTarget(selector, callback)
      );
      this._intersectionObserverModule.observe(
        this._id,
        selector,
        this._observationTargets.length - 1
      );
    }
    disconnect() {
      this._intersectionObserverModule.disconnect(this._id);
      this._manager.removeObserver(this._id);
    }
    invokeCallback(callbackId, data) {
      if (callbackId < this._observationTargets.length) {
        this._observationTargets[callbackId].invokeCallback(data);
      }
    }
  };
  var IntersectionObserverManager = class {
    constructor(nativeModules) {
      this._nativeModules = nativeModules;
      this._observerId = 0;
      this._observers = {};
      this._defaultOptions = {
        thresholds: [0],
        initialRatio: 0,
        observeAll: false
      };
    }
    createIntersectionObserver(componentId, options) {
      let intersectionObserverModule = this._nativeModules["IntersectionObserver\
Module"];
      const observer = new IntersectionObserver(
        this._observerId,
        intersectionObserverModule,
        this
      );
      this._observers[this._observerId] = observer;
      intersectionObserverModule.createIntersectionObserver(
        this._observerId,
        componentId,
        options || this._defaultOptions
      );
      this._observerId++;
      return observer;
    }
    getObserver(observerId) {
      return this._observers[observerId];
    }
    removeObserver(observerId) {
      this._observers[observerId] = null;
    }
  };

  // src/modules/performance/performanceObserver.ts
  var ListenerKeys = {
    onPerformance: "lynx.performance.onPerformanceEvent"
  };
  var PerformanceObserver = class {
    constructor(emitter, callback) {
      this._emitter = emitter;
      this._onPerformance = callback;
      this._observedNames = [];
    }
    observe(names) {
      if (this._observedNames.length > 0) {
        return;
      }
      this._observedNames = names;
      this._emitter.addListener(
        ListenerKeys.onPerformance,
        this.onPerformanceEvent.bind(this)
      );
    }
    disconnect() {
      this._observedNames = [];
      this._emitter.removeListener(
        ListenerKeys.onPerformance,
        this.onPerformanceEvent.bind(this)
      );
    }
    onPerformanceEvent(entry) {
      if (this._observedNames.length === 0) {
        return;
      }
      let entryName2 = entry.entryType + "." + entry.name;
      if (this._observedNames.includes(entryName2) || this._observedNames.includes(
      entry.entryType)) {
        this._onPerformance(entry);
      }
    }
  };

  // src/modules/performance/performance.ts
  var ListenerKeys2 = {
    onSetup: "lynx.performance.timing.onSetup",
    onUpdate: "lynx.performance.timing.onUpdate"
  };
  var Performance = class {
    constructor(emitter, nativeApp) {
      this._emitter = emitter;
      this._generatePipelineOptions = nativeApp.generatePipelineOptions;
      this._onPipelineStart = nativeApp.onPipelineStart;
      this._markTiming = nativeApp.markPipelineTiming;
      this._profileStart = nativeApp.profileStart;
      this._profileEnd = nativeApp.profileEnd;
      this._profileMark = nativeApp.profileMark;
      this._profileFlowId = nativeApp.profileFlowId;
      this._isProfileRecording = nativeApp.isProfileRecording;
      this._bindPipelineIdWithTimingFlag = nativeApp.bindPipelineIdWithTimingFlag;
    }
    profileStart(traceName, option) {
      this._profileStart(traceName, option);
    }
    profileEnd() {
      this._profileEnd();
    }
    profileMark(traceName, option) {
      this._profileMark(traceName, option);
    }
    profileFlowId() {
      return this._profileFlowId();
    }
    createObserver(callback) {
      return new PerformanceObserver(this._emitter, callback);
    }
    isProfileRecording() {
      return this._isProfileRecording();
    }
    addTimingListener(listener) {
      this._emitter.addListener(ListenerKeys2.onSetup, listener.onSetup, listener);
      this._emitter.addListener(
        ListenerKeys2.onUpdate,
        listener.onUpdate,
        listener
      );
    }
    removeTimingListener(listener) {
      this._emitter.removeListener(ListenerKeys2.onSetup, listener.onSetup);
      this._emitter.removeListener(ListenerKeys2.onUpdate, listener.onUpdate);
    }
    removeAllTimingListener() {
      this._emitter.removeAllListeners(ListenerKeys2.onSetup);
      this._emitter.removeAllListeners(ListenerKeys2.onUpdate);
    }
    _initializeAndStartPipeline() {
      const pipelineOptions = this._generatePipelineOptions();
      if (pipelineOptions) {
        this._onPipelineStart(pipelineOptions.pipelineID);
      }
      return pipelineOptions;
    }
    _checkAndBindTimingFlag(pipelineOptions, data) {
      if (!pipelineOptions) {
        return;
      }
      const PerformanceTimingFlag = "__lynx_timing_flag";
      if (data[PerformanceTimingFlag]) {
        this._bindPipelineIdWithTimingFlag(
          pipelineOptions.pipelineID,
          data[PerformanceTimingFlag]
        );
        this._markTiming(pipelineOptions.pipelineID, "update_set_state_trigger");
        pipelineOptions.needTimestamps = true;
      }
    }
  };

  // src/modules/performance/index.ts
  var performance_default = Performance;

  // src/common/jsbi.ts
  var jsbi_default = nativeGlobal_default2.LynxJSBI;

  // src/util/cachedFunctionProxy.ts
  var CachedFunctionProxy = class _CachedFunctionProxy {
    constructor(obj) {
      this._cachedFunctions = {};
      for (const key in obj) {
        Object.defineProperty(this, key, {
          get() {
            if (this._cachedFunctions[key]) {
              return this._cachedFunctions[key];
            }
            const value = obj[key];
            if (typeof value === "function") {
              this._cachedFunctions[key] = value;
            }
            return value;
          }
        });
      }
    }
    static create(obj) {
      return new _CachedFunctionProxy(obj);
    }
  };

  // src/util/setup-promise.ts
  function getPromiseMaybePolyfill(setTimeout2, onUnhandled, clearTimeout, queueMicrotask = void 0, enableMicrotaskPromisePolyfill = false) {
    const { getPromise } = nativeGlobal_default2;
    if (typeof getPromise === "function") {
      const nextTick = enableMicrotaskPromisePolyfill ? queueMicrotask : (fn) => setTimeout2(
      fn, 0);
      return getPromise({ nextTick, setTimeout: setTimeout2, onUnhandled, clearTimeout });
    } else {
      return nativeGlobal_default2.Promise;
    }
  }

  // src/util/TraceEventDef.ts
  var TraceEventDef = class {
  };
  TraceEventDef.EXECUTE_LOADED_SCRIPT = "executeLoadedScript";

  // src/app/app.ts
  var _BaseApp = class _BaseApp {
    constructor(options, baseAppSingleData) {
      this.dataTypeSet = /* @__PURE__ */ new Set([
        "string",
        "number",
        "array",
        "object",
        "boolean",
        "null",
        "function"
      ]);
      this.removeInternalEventListenersCallbacks = [];
      /**
       * Set sourcemap release with a newly thrown error
       * @param {Error} error
       * The error thrown from the file that wants to set sourcemap release.
       * The top frame of `error.stack` **must be** the filename.
       * The `error.name` **must be** `'LynxGetSourceMapReleaseError'`.
       * The `error.message` **must be** the sourcemap release.
       *
       * @example
       * (function () {
       *   try {
       *     throw new Error(sourcemapRelease);
       *   } catch (e) {
       *     e.name = 'LynxGetSourceMapReleaseError';
       *     tt.setSourceMapRelease(e);
       *   }
       * })()
       */
      this.setSourceMapRelease = (error) => {
        this.Reporter.setSourceMapRelease(error);
      };
      this.getSourceMapRelease = (url) => {
        return this.Reporter.getSourceMapRelease(url);
      };
      this.queueMicrotask = (callback) => {
        var _a3, _b2;
        if (!callback) {
          return;
        }
        if (!((_b2 = (_a3 = this.params) == null ? void 0 : _a3.pageConfigSubset) ==
        null ? void 0 : _b2.enableJSCallbackManager)) {
          this.lynx.getNativeLynx().queueMicrotask(callback);
        } else {
          const id = this._callbackManager.addCallback(callback);
          if (id === void 0) {
            return;
          }
          this.lynx.getNativeLynx().queueMicrotask(id);
        }
      };
      this.wrapClearTimerMethod = (nativeMethod) => {
        var _a3, _b2;
        if (!((_b2 = (_a3 = this.params) == null ? void 0 : _a3.pageConfigSubset) ==
        null ? void 0 : _b2.enableJSCallbackManager)) {
          return nativeMethod;
        }
        return (taskId) => {
          nativeMethod.call(void 0, taskId);
          this._callbackManager.removeCallbackByTaskId(taskId);
        };
      };
      this.setupGetTextInfoApi = () => {
        this._apiList["getTextInfo"] = (text, options) => {
          return this._textInfoManager.getTextInfo(text, options);
        };
      };
      this.setupExposureApi = () => {
        this._apiList["resumeExposure"] = () => {
          this._exposureManager.resumeExposure();
        };
        this._apiList["stopExposure"] = (options) => {
          this._exposureManager.stopExposure(
            options ? options : { sendEvent: true }
          );
        };
        this._apiList["setObserverFrameRate"] = (options) => {
          this._exposureManager.setObserverFrameRate(
            options ? options : { forPageRect: 20, forExposureCheck: 20 }
          );
        };
      };
      this.requestAnimationFrame = (callback) => this._nativeApp.requestAnimationFrame(
      callback);
      this.cancelAnimationFrame = (animationId) => this._nativeApp.cancelAnimationFrame(
      animationId);
      this.__removeInternalEventListeners = () => {
        this.removeInternalEventListenersCallbacks.forEach((f) => {
          f();
        });
      };
      this.initBase(options);
      if (baseAppSingleData) {
        baseAppSingleData.transferSingletonData(
          this,
          this.__internal__callLynxSetModule.bind(this)
        );
      } else {
        this.initExtra(options);
      }
      this.addInternalEventListeners();
      nativeGlobal_default2["notifyRuntimeReadyOnRT" + this.nativeAppId] && nativeGlobal_default2["\
notifyRuntimeReadyOnRT" + this.nativeAppId](this.lynx);
    }
    initExtra(options) {
      const { lynx } = options;
      this._callbackManager = new CallbackManager();
      this.setTimeout = this.wrapCallbackMethod(this.nativeApp.setTimeout);
      this.setInterval = this.wrapCallbackMethod(
        this.nativeApp.setInterval,
        false
      );
      this.clearInterval = this.wrapClearTimerMethod(
        this.nativeApp.clearInterval
      );
      this.clearTimeout = this.wrapClearTimerMethod(this.nativeApp.clearTimeout);
      this.modules = {};
      this._lazyCallableModules = /* @__PURE__ */ new Map();
      this._nativeApp = CachedFunctionProxy.create(
        this._nativeApp
      );
      this.sharedConsole = createSharedConsole(`runtimeId:${this.nativeAppId}`);
      this.dynamicComponentExports = {};
      this.loadedDynamicComponentsSet = /* @__PURE__ */ new Set();
      this._lazyCallableModules = /* @__PURE__ */ new Map();
      this.Reporter = new Reporter(
        () => this,
        () => this.nativeApp
      );
      this.GlobalEventEmitter = new event_default(
        this.__internal__callLynxSetModule.bind(this)
      );
      this._intersectionObserverManager = new IntersectionObserverManager(
        this.NativeModules
      );
      this._exposureManager = new ExposureManager(this.NativeModules);
      this.setupExposureApi();
      this._aopManager = new AopManager();
      this.beforePublishEvent = this._aopManager._beforePublishEvent;
      this.performance = new performance_default(this.GlobalEventEmitter, this.nativeApp);
      const promiseCtor = this.setupPromise(
        this.setTimeout,
        this.clearTimeout,
        this.queueMicrotask
      );
      this.lynx = this.createLynx(lynx, promiseCtor);
      this.setupJSModule();
      this.setupIntersectionApi();
      this.setupFetchAPI(promiseCtor);
    }
    initBase(options) {
      const { nativeApp, params: params2 } = options;
      this.nativeAppId = nativeApp.id;
      this._params = params2;
      this._nativeApp = nativeApp;
      this.NativeModules = nativeApp.nativeModuleProxy;
      this.LynxUIMethodModule = nativeApp.nativeModuleProxy.LynxUIMethodModule;
      this.LynxTestModule = nativeApp.nativeModuleProxy.LynxTestModule;
      this.LynxResourceModule = nativeApp.nativeModuleProxy.LynxResourceModule;
      this.LynxAccessibilityModule = nativeApp.nativeModuleProxy.LynxAccessibilityModule;
      this.LynxSetModule = nativeApp.nativeModuleProxy.LynxSetModule;
      this._apiList = {};
      this._textInfoManager = new TextInfoManager(this.NativeModules);
      this.setupGetTextInfoApi();
    }
    /**
     * legacy sourcemap release use url default
     * used for backward compatibility
     *
     * new template should use setSourceMapRelease
     */
    set __sourcemap__release__(release) {
      let error = new Error();
      error.name = "LynxGetSourceMapReleaseError";
      error.message = release;
      error.stack = `at <anonymous> (${_BaseApp.kDefaultSourceMapURL}:1:1)`;
      this.setSourceMapRelease(error);
    }
    /**
     * pass id instead of callback for native.
     * for setTimeout、setInterval、queueMicrotask and other.
     */
    wrapCallbackMethod(nativeMethod, isTimeout = true) {
      var _a3, _b2;
      if (!((_b2 = (_a3 = this.params) == null ? void 0 : _a3.pageConfigSubset) ==
      null ? void 0 : _b2.enableJSCallbackManager)) {
        return nativeMethod;
      }
      const that2 = this;
      return function(callback, delay) {
        if (!callback) {
          return -1;
        }
        const taskInfo = { taskId: void 0 };
        const cb = () => {
          try {
            callback.apply(callback, void 0);
          } finally {
            if (isTimeout) {
              that2._callbackManager.removeTaskId(taskInfo.taskId);
            }
          }
        };
        const id = that2._callbackManager.addCallback(cb);
        if (id === void 0) {
          return -1;
        }
        const taskId = nativeMethod.call(void 0, id, delay);
        if (taskId !== void 0) {
          that2._callbackManager.addTaskIdAndCallbackId(taskId, id);
          taskInfo.taskId = taskId;
        }
        return taskId;
      };
    }
    destroy() {
      this.__removeInternalEventListeners();
      this._callbackManager.destroy();
      this._nativeApp = null;
      this._params = null;
      this._lazyCallableModules = null;
      this.GlobalEventEmitter = null;
    }
    registerModule(name, module2) {
      this._lazyCallableModules[name] = module2;
    }
    getJSModule(name) {
      return this._lazyCallableModules[name];
    }
    setupJSModule() {
      this.registerModule("GlobalEventEmitter", this.GlobalEventEmitter);
      this.registerModule("Reporter", this.Reporter);
    }
    setupFetchAPI(Promise2) {
      this._createReadableStreamClass = createReadableStreamClass;
      this._ReadableStreamClass = createReadableStreamClass(Promise2);
      if (!nativeGlobal_default2.Request) {
        nativeGlobal_default2.Request = Request;
      }
      if (!nativeGlobal_default2.Response) {
        nativeGlobal_default2.Response = Response;
      }
      if (!nativeGlobal_default2.ReadableStream) {
        nativeGlobal_default2.ReadableStream = this._ReadableStreamClass;
      }
    }
    __internal__callLynxSetModule(functionName, payload) {
      const nativeFunction = this.LynxSetModule[functionName];
      if (nativeFunction) {
        Function.prototype.apply.call(nativeFunction, void 0, payload);
      }
    }
    get nativeApp() {
      return this._nativeApp;
    }
    set nativeApp(nativeApp) {
      this._nativeApp = nativeApp;
    }
    get params() {
      return this._params;
    }
    set apiList(api) {
      this._apiList = { ...this._apiList, ...api };
    }
    setupIntersectionApi() {
      let self = this;
      this._apiList["createIntersectionObserver"] = function(component, options) {
        const { componentId = "" } = component;
        return self._intersectionObserverManager.createIntersectionObserver(
          componentId,
          options
        );
      };
      this.lynx["createIntersectionObserver"] = this._apiList["createIntersectio\
nObserver"];
    }
    onIntersectionObserverEvent(observerId, callbackId, data) {
      const observer = this._intersectionObserverManager.getObserver(observerId);
      if (observer) {
        observer.invokeCallback(callbackId, data);
      }
    }
    reportError(error) {
      return this.lynx.reportError(error);
    }
    handleError(error, originError, errorLevel) {
      reportError(error, this.nativeApp, {
        originError,
        getSourceMapRelease: this.getSourceMapRelease,
        errorLevel
      });
    }
    handleUserError(error, cause, errorLevel, prefix) {
      let { message, name, stack } = error || {};
      if (!message) {
        ({ message, name, stack } = new Error(JSON.stringify(error)));
      }
      const userError = new UserRuntimeError(
        prefix ? `${prefix} ${name}: ${message}` : `${name}: ${message}`,
        stack
      );
      userError.cause = cause;
      this.handleError(userError, error, errorLevel);
    }
    /**
     * @internal
     */
    handleInternalError(error, cause) {
      let { message, name, stack } = error || {};
      if (!message) {
        ({ message, name, stack } = new Error(JSON.stringify(error)));
      }
      const internalError = new InternalRuntimeError(
        `${name}: ${message}`,
        stack
      );
      internalError.cause = cause;
      this.handleError(internalError, error);
    }
    /**
     * Get a external env with boolean value.
     * The same as `base::LynxEnv::GetInstance().GetBoolEnv`
     *
     * @param {EnvKey} key The {@link EnvKey}, should be placed in `lynx_env.h`
     */
    getBoolEnv(key) {
      const env = this.nativeApp.getEnv(key);
      return (env == null ? void 0 : env.toLowerCase()) === "true";
    }
    /**
     * @internal
     * Execute the loaded JS module ,  Called by {@link requireModule} & {@link requireModuleAsync}
     * @throws {UserRuntimeError} when loading or evaluating failed
     * @throws {Error} when executing failed
     */
    _$executeInit(exports, {
      path: path2,
      entryName: entryName2,
      shouldCacheFactory = true,
      cacheKey
    }) {
      let factory;
      if (exports && exports.init) {
        factory = exports.init.bind(exports);
      } else if (nativeGlobal_default2.initBundle) {
        factory = nativeGlobal_default2.initBundle.bind(nativeGlobal_default2.initBundle);
        delete nativeGlobal_default2.initBundle;
      } else {
        throw new UserRuntimeError(
          `load failed. path:${path2},entryName:${entryName2}`
        );
      }
      try {
        this.lynx.performance.profileStart(TraceEventDef.EXECUTE_LOADED_SCRIPT, {
          args: { path: path2 }
        });
        const ret = factory({ tt: this });
        if (shouldCacheFactory) {
          _BaseApp._$factoryCache[path2] = factory;
        }
        addLoadScriptCache(cacheKey, exports);
        return ret;
      } finally {
        this.lynx.performance.profileEnd();
      }
    }
    /**
     * @internal
     * Used to load the json module. Called by {@link requireModule} & {@link requireModuleAsync}
     * @param content
     * @param path
     * @private
     */
    _$executeJSON(content, { path: path2 }) {
      const ret = JSON.parse(content);
      const init = () => ret;
      _BaseApp._$factoryCache[path2] = init;
      return ret;
    }
    requireModule(path2, entryName2, options) {
      const init = _BaseApp._$factoryCache[path2];
      if (false) {
        return this._$executeInit({ init }, { path: path2, entryName: entryName2 });
      }
      if (path2.split("?")[0].endsWith(".json")) {
        const content = this.nativeApp.readScript(path2, {
          dynamicComponentEntry: entryName2 != null ? entryName2 : DEFAULT_ENTRY,
          ...options
        });
        return this._$executeJSON(content, { path: path2, entryName: entryName2 });
      }
      const cacheKey = this.getLoadScriptCacheKey(
        path2,
        entryName2,
        this.params.srcName
      );
      const cache = tryGetLoadScriptCache(cacheKey);
      if (cache) {
        return this._$executeInit(cache, {
          path: path2,
          entryName: entryName2
        });
      } else {
        const exports = this.nativeApp.loadScript(path2, entryName2, options);
        return this._$executeInit(exports, { path: path2, entryName: entryName2,
        cacheKey });
      }
    }
    requireModuleAsync(path2, callback) {
      const init = _BaseApp._$factoryCache[path2];
      if (false) {
        callback(null, this._$executeInit({ init }, { path: path2 }));
        return;
      }
      if (path2.split("?")[0].endsWith(".json")) {
        try {
          const content = this.nativeApp.readScript(path2);
          const ret = this._$executeJSON(content, { path: path2 });
          callback(null, ret);
        } catch (e) {
          callback(e);
        }
        return;
      }
      const cacheKey = this.getLoadScriptCacheKey(path2, this.params.srcName);
      const cache = tryGetLoadScriptCache(cacheKey);
      if (cache) {
        try {
          return callback(
            null,
            this._$executeInit(cache, { path: path2 })
          );
        } catch (e) {
          callback(e);
        }
      }
      const error = new Error();
      this.nativeApp.loadScriptAsync(path2, (message, exports) => {
        if (message) {
          error.message = message;
          return callback(error);
        }
        try {
          return callback(null, this._$executeInit(exports, { path: path2, cacheKey }));
        } catch (e) {
          return callback(e);
        }
      });
    }
    require(path, params) {
      const that = this;
      if (typeof path !== "string") {
        throw new Error("require args must be a string");
      }
      const entryName = params && params.dynamicComponentEntry ? params.dynamicComponentEntry :
      DEFAULT_ENTRY;
      if (!that.modules[entryName]) {
        that.modules[entryName] = {};
      }
      let module = that.modules[entryName][path];
      if (!module) {
        try {
          const tt = that;
          const jsContent = that._nativeApp.readScript(path, {
            dynamicComponentEntry: entryName
          });
          eval(jsContent);
          module = that.modules[entryName][path];
        } catch (e) {
          this.handleError(
            new UserRuntimeError(
              `eval user: ${that._nativeApp.id} error: ${e.message}`,
              e.stack
            ),
            e
          );
        }
        if (!that.modules[entryName][path]) {
          throw new Error(
            `module ${path} in ${entryName} is not defined in card: ${that._nativeApp.
            id}`
          );
        }
      }
      if (!module.hasRun) {
        const { factory } = module;
        const _module = {
          exports: {}
        };
        let res;
        module.hasRun = true;
        module.exports = _module.exports;
        if (typeof factory === "function") {
          const inRequireCopy = inRequire.call(that, path);
          const tt2 = that;
          res = factory(
            inRequireCopy,
            _module,
            _module.exports,
            that.Card.bind(tt2),
            that.setTimeout,
            that.setInterval,
            that.clearInterval,
            that.clearTimeout,
            that.NativeModules,
            that._apiList,
            that.sharedConsole,
            that.Component.bind(tt2),
            params == null ? void 0 : params.ReactLynx,
            that.nativeAppId,
            that.Behavior.bind(tt2),
            jsbi_default,
            that.lynx,
            void 0,
            // window
            void 0,
            // document
            void 0,
            // frames
            void 0,
            // self
            void 0,
            // location
            void 0,
            // navigator
            void 0,
            // localStorage
            void 0,
            // history
            void 0,
            // Caches
            void 0,
            // screen
            void 0,
            // alert
            void 0,
            // confirm
            void 0,
            // prompt
            that.lynx.fetch,
            // fetch
            void 0,
            // XMLHttpRequest
            void 0,
            // WebSocket
            void 0,
            // webkit
            void 0,
            // Reporter
            void 0,
            // print
            void 0,
            // global
            that.requestAnimationFrame,
            that.cancelAnimationFrame
          );
          module.exports = _module.exports || res;
        }
      }
      return module.exports;
    }
    define(path2, factory, entryName2) {
      entryName2 = entryName2 ? entryName2 : DEFAULT_ENTRY;
      if (!this.modules[entryName2]) {
        this.modules[entryName2] = {};
      }
      this.modules[entryName2][path2] = {
        hasRun: false,
        factory: factory.bind(this)
      };
    }
    loadScript(url, options) {
      const { bundleName = DEFAULT_ENTRY, useModuleWrapper = false } = options ||
      {};
      const cacheKey = this.getLoadScriptCacheKey(
        url,
        bundleName,
        this.params.srcName,
        true
      );
      let exports = tryGetLoadScriptCache(cacheKey);
      if (true) {
        let maybeExports = this.lynx.getNativeLynx().loadScript(url, options);
        if (maybeExports && typeof maybeExports.init === "function") {
          exports = maybeExports;
        } else if (useModuleWrapper && maybeExports && typeof maybeExports === "\
function") {
          exports = maybeExports;
        } else {
          return maybeExports;
        }
      }
      if (useModuleWrapper) {
        const module2 = { exports: {} };
        let that2 = this;
        const inRequireCopy = inRequire.call(that2, url);
        const args = [
          inRequireCopy,
          module2,
          module2.exports,
          that2.setTimeout,
          that2.setInterval,
          that2.clearInterval,
          that2.clearTimeout,
          that2.NativeModules,
          that2.sharedConsole,
          that2.nativeAppId,
          jsbi_default,
          that2.lynx,
          that2.requestAnimationFrame,
          that2.cancelAnimationFrame,
          that2.lynx.fetch
        ];
        exports.apply(module2.exports, args);
        addLoadScriptCache(cacheKey, exports);
        return module2.exports;
      } else {
        return this._$executeInit(exports, {
          path: url,
          entryName: options == null ? void 0 : options.bundleName,
          shouldCacheFactory: false,
          cacheKey
        });
      }
    }
    /**
     * Call By Native js_app
     * @internal
     * @param module
     * @param method
     * @param args
     */
    callFunction(module2, method, args) {
      try {
        const moduleMethods = this.getJSModule(module2);
        if (typeof moduleMethods[method] === "function") {
          moduleMethods[method].apply(moduleMethods, args);
        }
      } catch (e) {
        this.handleUserError(e, { by: `${module2}.${method}` });
      }
    }
    /**
     * Call By Native js_app
     * @internal
     * @param {never} _ Used for backward compatiblity, DO NOT USE.
     * @param {Error} error the Error object emit by native.
     */
    onAppError(_, error) {
      this.handleInternalError(error);
    }
    saveDynamicComponentExports(componentUrl, moduleExports) {
      this.dynamicComponentExports[componentUrl] = moduleExports;
    }
    getDynamicComponentExports(componentUrl) {
      return this.dynamicComponentExports[componentUrl];
    }
    Component(...args) {
    }
    Card(...args) {
    }
    Behavior(...args) {
    }
    /**
     * @param setTimeout
     */
    wrapReport(setTimeout2, desc) {
      const that2 = this;
      function wrapReport(fn) {
        return function wrapReportInner(...args) {
          try {
            return fn.apply(this, args);
          } catch (e) {
            that2.handleUserError(e, { by: desc });
          }
        };
      }
      return function WrapTimeout(fn, ...args) {
        return Function.prototype.apply.call(setTimeout2, void 0, [
          wrapReport(fn),
          ...args
        ]);
      };
    }
    setupPromise(setTimeout2, clearTimeout, queueMicrotask) {
      var _a3, _b2, _c2;
      const PromiseConstructor = getPromiseMaybePolyfill(
        setTimeout2,
        (id, reason) => {
          try {
            if (reason) {
              if (!reason.stack) {
                reason = new Error(JSON.stringify(reason));
              }
              reason.name = "unhandled rejection";
              this.handleUserError(reason);
            }
          } catch (err) {
          }
        },
        clearTimeout,
        queueMicrotask,
        (_c2 = (_b2 = (_a3 = this._params) == null ? void 0 : _a3.pageConfigSubset) ==
        null ? void 0 : _b2.enableMicrotaskPromisePolyfill) != null ? _c2 : false
      );
      this.resolvedPromise = PromiseConstructor.resolve();
      return PromiseConstructor;
    }
    invokeCallback(once, callbackId, ...args) {
      this._callbackManager.invokeCallback(once, callbackId, ...args);
    }
    addInternalEventListener(contextProxyType, type, listener) {
      this.contextProxyTypeToMethod[contextProxyType]().addEventListener(
        type,
        listener
      );
      this.removeInternalEventListenersCallbacks.push(() => {
        this.contextProxyTypeToMethod[contextProxyType]().removeEventListener(
          type,
          listener
        );
      });
    }
    addInternalEventListeners() {
      if (!this.contextProxyTypeToMethod) {
        this.contextProxyTypeToMethod = {
          [0 /* CoreContext */]: () => this.lynx.getCoreContext(),
          [1 /* DevTool */]: () => this.lynx.getDevtool(),
          [2 /* JSContext */]: () => this.lynx.getJSContext(),
          [3 /* UIContext */]: () => this.lynx.getUIContext(),
          [4 /* Native */]: () => this.lynx.getNative(),
          [5 /* Engine */]: () => this.lynx.getEngine()
        };
      }
      this.addInternalEventListener(
        0 /* CoreContext */,
        "__OnNativeAppReady" /* ON_NATIVE_APP_READY */,
        () => {
          this.onNativeAppReady();
        }
      );
      this.addInternalEventListener(
        0 /* CoreContext */,
        "__NotifyGlobalPropsUpdated" /* NOTIFY_GLOBAL_PROPS_UPDATED */,
        (event) => {
          this.updateGlobalProps(event.data);
        }
      );
      this.addInternalEventListener(
        0 /* CoreContext */,
        "__OnLifecycleEvent" /* ON_LIFECYCLE_EVENT */,
        (event) => {
          this.OnLifecycleEvent(event.data);
        }
      );
      this.addInternalEventListener(
        0 /* CoreContext */,
        "__OnAppFirstScreen" /* ON_APP_FIRST_SCREEN */,
        () => {
          this.onAppFirstScreen();
        }
      );
      this.addInternalEventListener(
        0 /* CoreContext */,
        "__OnDynamicJSSourcePrepared" /* ON_DYNAMIC_JS_SOURCE_PREPARED */,
        (event) => {
          nativeGlobal_default2.loadDynamicComponent(this, event.data);
        }
      );
      this.addInternalEventListener(
        0 /* CoreContext */,
        "__OnAppEnterForeground" /* ON_APP_ENTER_FOREGROUND */,
        () => {
          this.onAppEnterForeground();
        }
      );
      this.addInternalEventListener(
        0 /* CoreContext */,
        "__OnAppEnterBackground" /* ON_APP_ENTER_BACKGROUND */,
        () => {
          this.onAppEnterBackground();
        }
      );
    }
    getLoadScriptCacheKey(path2, entryName2, templateUrl, ignoreConfig = false) {
      if (!templateUrl || true) {
        return void 0;
      }
      let cacheKey = (entryName2 ? entryName2 : DEFAULT_ENTRY) + path2;
      if (path2.startsWith("/") || path2.startsWith("lynx_assets")) {
        cacheKey = templateUrl + cacheKey;
      }
      return cacheKey;
    }
    /**
     *  override by subclass
     * @param newData
     */
    updateGlobalProps(newData) {
    }
    /**
     *  override by subclass
     * @param newData
     */
    OnLifecycleEvent(args) {
    }
    /**
     *  override by subclass
     * @param newData
     */
    onNativeAppReady() {
    }
    /**
     *  override by subclass
     * @param newData
     */
    onAppFirstScreen() {
    }
    /**
     *  override by subclass
     * @param newData
     */
    onAppEnterBackground() {
    }
    /**
     *  override by subclass
     * @param newData
     */
    onAppEnterForeground() {
    }
  };
  _BaseApp.kDefaultSourceMapURL = "default";
  _BaseApp.kGetSourceMapReleaseErrorName = SOURCE_MAP_RELEASE_ERROR_NAME;
  /**
   * @internal
   * @static
   * The LynxGroup level cache for requireModule , {@link registerModule}
   */
  _BaseApp._$factoryCache = {};
  /**
   * @internal
   * @static
   * The LynxGroup level cache for loadScript
   */
  _BaseApp._$loadScriptCache = {};
  var BaseApp = _BaseApp;
  function pathProcess(path2) {
    const match = path2.match(/(.*)\/([^/]+)?$/);
    return (match == null ? void 0 : match[1]) ? match[1] : "./";
  }
  function inRequire(path2) {
    const that2 = this;
    const pwd = pathProcess(path2);
    return function(path3) {
      const t = [];
      const r = `${pwd}/${path3}`.split("/");
      const i = r.length;
      if (typeof path3 !== "string") {
        throw new Error("require args must be a string");
      }
      for (let o = 0; o < i; ++o) {
        const a = r[o];
        if (a !== "" && a !== ".") {
          if (a === "..") {
            if (t.length === 0) {
              throw new Error(
                `can't find module ${path3} in app: ${that2._nativeApp.id}`
              );
            }
            t.pop();
          } else {
            o + 1 < i && r[o + 1] === ".." ? o++ : t.push(a);
          }
        }
      }
      let c = t.join("/");
      return c.endsWith(".js") || (c += ".js"), that2.require(c);
    };
  }
  function tryGetLoadScriptCache(cacheKey) {
    if (!cacheKey) {
      return void 0;
    }
    return BaseApp._$loadScriptCache[cacheKey];
  }
  function addLoadScriptCache(cacheKey, exports) {
    if (!cacheKey || !exports) {
      return;
    }
    BaseApp._$loadScriptCache[cacheKey] = exports;
  }

  // src/react/reactApp.ts
  var ReactApp = class extends BaseApp {
    createLynx(nativeLynx, promiseCtor) {
      const lynx_proxy = CachedFunctionProxy.create(nativeLynx);
      return new Lynx(
        () => this.nativeApp,
        () => this,
        promiseCtor,
        () => lynx_proxy
      );
    }
    callBeforePublishEvent(eventData) {
      if (this._aopManager._beforePublishEvent.getEventsSize(eventData.type) !==
      0) {
        const copyData = { ...eventData };
        try {
          this._aopManager._beforePublishEvent.emit(copyData.type, [copyData]);
        } catch (e) {
          this.handleUserError(e, {
            by: "callBeforePublishEvent",
            type: copyData.type
          });
        }
      }
    }
  };

  // src/standalone/StandaloneApp.ts
  var BaseAppSingletonData = class {
    transferSingletonData(baseApp, callLynxSetModule) {
      baseApp.nativeApp = this.nativeApp;
      baseApp.sharedConsole = this.sharedConsole;
      baseApp.dynamicComponentExports = this.dynamicComponentExports;
      baseApp.loadedDynamicComponentsSet = this.loadedDynamicComponentsSet;
      baseApp._intersectionObserverManager = this.intersectionObserverManager;
      baseApp._exposureManager = this.exposureManager;
      baseApp._textInfoManager = this.textInfoManager;
      this.globalEventEmitter.setCallLynxSetModule(callLynxSetModule);
      baseApp.GlobalEventEmitter = this.globalEventEmitter;
      baseApp._aopManager = this.aopManager;
      baseApp.performance = this.performance;
      baseApp.modules = this.modules;
      baseApp._lazyCallableModules = this.lazyCallableModules;
      baseApp.lynx = this.lynx;
      this.lynx.rebind(() => baseApp);
      baseApp._apiList = this.apiList;
      this.Reporter.rebind(() => baseApp);
      baseApp.Reporter = this.Reporter;
      baseApp._callbackManager = this.callbackManager;
      baseApp.setTimeout = this.setTimeout;
      baseApp.setInterval = this.setInterval;
      baseApp.clearInterval = this.clearInterval;
      baseApp.clearTimeout = this.clearTimeout;
      baseApp.resolvedPromise = this.resolvedPromise;
      baseApp._createReadableStreamClass = this._createReadableStreamClass;
      baseApp._ReadableStreamClass = this._ReadableStreamClass;
    }
  };
  var StandaloneApp = class extends BaseApp {
    constructor(options, params2) {
      super(options, void 0);
      this.fillSingletonData();
      try {
        if (params2.srcName) {
          delete this.lynx.requireModule.cache[params2.srcName];
          delete BaseApp._$factoryCache[params2.srcName];
          this.lynx.requireModule(params2.srcName, DEFAULT_ENTRY);
          this.dataTypeSet.add("undefined");
        }
      } catch (e) {
        this.handleUserError(e);
      }
    }
    createLynx(nativeLynx, promise) {
      const lynx_proxy = CachedFunctionProxy.create(nativeLynx);
      return new Lynx(
        () => this.nativeApp,
        () => this,
        promise,
        () => lynx_proxy
      );
    }
    fillSingletonData() {
      this.singletonData = new BaseAppSingletonData();
      this.singletonData.nativeApp = this._nativeApp;
      this.singletonData.sharedConsole = this.sharedConsole;
      this.singletonData.dynamicComponentExports = this.dynamicComponentExports;
      this.singletonData.loadedDynamicComponentsSet = this.loadedDynamicComponentsSet;
      this.singletonData.intersectionObserverManager = this._intersectionObserverManager;
      this.singletonData.exposureManager = this._exposureManager;
      this.singletonData.textInfoManager = this._textInfoManager;
      this.singletonData.globalEventEmitter = this.GlobalEventEmitter;
      this.singletonData.aopManager = this._aopManager;
      this.singletonData.performance = this.performance;
      this.singletonData.modules = this.modules;
      this.singletonData.lazyCallableModules = this._lazyCallableModules;
      this.singletonData.lynx = this.lynx;
      this.singletonData.apiList = this._apiList;
      this.singletonData.Reporter = this.Reporter;
      this.singletonData.callbackManager = this._callbackManager;
      this.singletonData.setTimeout = this.setTimeout;
      this.singletonData.setInterval = this.setInterval;
      this.singletonData.clearInterval = this.clearInterval;
      this.singletonData.clearTimeout = this.clearTimeout;
      this.singletonData.resolvedPromise = this.resolvedPromise;
      this.singletonData._createReadableStreamClass = this._createReadableStreamClass;
      this.singletonData._ReadableStreamClass = this._ReadableStreamClass;
    }
  };

  // src/appManager.ts
  function loadCard(nativeApp, params2, lynx) {
    const { id } = nativeApp;
    const { cardType } = params2;
    alog(`load card native app id: ${id}`);
    let loadSuccess = true;
    let tt2;
    try {
      if (cardType == "standalone") {
        tt2 = new StandaloneApp({ nativeApp, params: params2, lynx }, params2);
      } else {
        tt2 = new ReactApp({
          nativeApp,
          params: params2,
          lynx
        });
      }
      nativeGlobal_default2.currentAppId = id;
      nativeGlobal_default2.multiApps[id] = tt2;
      if (cardType === "standalone") {
        nativeApp.setCard(tt2);
        return true;
      }
      alog(
        `load card native app load app-service.js params.bundleSupportLoadScript\
 ${params2.bundleSupportLoadScript}`
      );
      loadSuccess = true;
      try {
        delete tt2.lynx.requireModule.cache[APP_SERVICE_NAME];
        delete BaseApp._$factoryCache[APP_SERVICE_NAME];
        tt2.lynx.requireModule(APP_SERVICE_NAME, DEFAULT_ENTRY);
        if (tt2.lynx._switches["allowUndefinedInNativeDataTypeSet"]) {
          tt2.dataTypeSet.add("undefined");
        }
      } catch (e) {
        loadSuccess = false;
        tt2.handleUserError(e, void 0, void 0, "loadCard failed");
      }
      nativeApp.setCard(tt2);
    } catch (e) {
      handleLoadCardError(nativeApp, e);
      loadSuccess = false;
    }
    return loadSuccess;
  }
  function destroyCard(id) {
    alog(`destroy ${id}`);
    const appInstance = nativeGlobal_default2.multiApps[id];
    appInstance.destroy();
    delete nativeGlobal_default2.multiApps[id];
  }
  function callDestroyLifetimeFun(id) {
    alog(`callDestroyLifetimeFun ${id}`);
    const appInstance = nativeGlobal_default2.multiApps[id];
    appInstance.callDestroyLifetimeFun();
  }
  function loadDynamicComponent(tt2, componentUrl) {
    if (tt2.loadedDynamicComponentsSet.has(componentUrl)) {
      return tt2.getDynamicComponentExports(componentUrl);
    }
    const preEntry = nativeGlobal_default2.globDynamicComponentEntry;
    nativeGlobal_default2.globDynamicComponentEntry = componentUrl;
    try {
      delete tt2.lynx.requireModule.cache[APP_SERVICE_NAME];
      delete BaseApp._$factoryCache[APP_SERVICE_NAME];
      const ret = tt2.lynx.requireModule(APP_SERVICE_NAME, componentUrl);
      tt2.saveDynamicComponentExports(componentUrl, ret);
      tt2.loadedDynamicComponentsSet.add(componentUrl);
      return ret;
    } catch (error) {
      tt2.handleUserError(error);
    } finally {
      nativeGlobal_default2.globDynamicComponentEntry = preEntry;
    }
  }
  function handleLoadCardError(nativeApp, error, cause) {
    let { message, name, stack } = error || {};
    if (!message) {
      ({ message, name, stack } = new Error(JSON.stringify(error)));
    }
    const internalError = new InternalRuntimeError(
      `loadCard failed ${name}: ${message}`,
      stack
    );
    internalError.cause = cause;
    reportError(internalError, nativeApp, {
      originError: error,
      getSourceMapRelease: (url) => {
        let ret = nativeApp.__GetSourceMapRelease(url);
        if (!ret) {
          return nativeApp.__GetSourceMapRelease(BaseApp.kDefaultSourceMapURL);
        }
      }
    });
  }
  function __invokeAppMethod(instanceId, methodName, ...args) {
    const appInstance = nativeGlobal_default2.multiApps[instanceId];
    if (!appInstance) {
      console.error(`callCallback: App instance not found for ID ${instanceId}`);
      return;
    }
    if (typeof appInstance[methodName] === "function") {
      appInstance[methodName](...args);
    }
  }

  // src/polyfill/arraybuffer.ts
  var chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  var lookup = new Uint8Array(256);
  for (let i = 0; i < chars.length; i++) {
    lookup[chars.charCodeAt(i)] = i;
  }
  function arrayBufferToBase64(buffer) {
    var bytes = new Uint8Array(buffer);
    var i;
    var len = bytes.length;
    var base64 = "";
    for (i = 0; i < len; i += 3) {
      base64 += chars[bytes[i] >> 2];
      base64 += chars[(bytes[i] & 3) << 4 | bytes[i + 1] >> 4];
      base64 += chars[(bytes[i + 1] & 15) << 2 | bytes[i + 2] >> 6];
      base64 += chars[bytes[i + 2] & 63];
    }
    if (len % 3 === 2) {
      base64 = base64.substring(0, base64.length - 1) + "=";
    } else if (len % 3 === 1) {
      base64 = base64.substring(0, base64.length - 2) + "==";
    }
    return base64;
  }
  function base64ToArrayBuffer(base64) {
    let bufferLength = base64.length * 0.75;
    const len = base64.length;
    let i;
    let p = 0;
    let encoded1;
    let encoded2;
    let encoded3;
    let encoded4;
    if (base64[base64.length - 1] === "=") {
      bufferLength--;
      if (base64[base64.length - 2] === "=") {
        bufferLength--;
      }
    }
    let arraybuffer = new ArrayBuffer(bufferLength);
    let bytes = new Uint8Array(arraybuffer);
    for (i = 0; i < len; i += 4) {
      encoded1 = lookup[base64.charCodeAt(i)];
      encoded2 = lookup[base64.charCodeAt(i + 1)];
      encoded3 = lookup[base64.charCodeAt(i + 2)];
      encoded4 = lookup[base64.charCodeAt(i + 3)];
      bytes[p++] = encoded1 << 2 | encoded2 >> 4;
      bytes[p++] = (encoded2 & 15) << 4 | encoded3 >> 2;
      bytes[p++] = (encoded3 & 3) << 6 | encoded4 & 63;
    }
    return arraybuffer;
  }

  // src/index.card.ts
  nativeGlobal_default2.loadCard = loadCard;
  nativeGlobal_default2.destroyCard = destroyCard;
  nativeGlobal_default2.callDestroyLifetimeFun = callDestroyLifetimeFun;
  nativeGlobal_default2.loadDynamicComponent = loadDynamicComponent;
  nativeGlobal_default2.__createEventEmitter = createEventEmitter;
  nativeGlobal_default2.__lynxArrayBufferToBase64 = arrayBufferToBase64;
  nativeGlobal_default2.__lynxBase64ToArrayBuffer = base64ToArrayBuffer;
  nativeGlobal_default2.LynxSDKCore = {
    report: legacyReportError,
    reportInner: wrapInnerFunction,
    reportUser: wrapUserFunction
  };
  nativeGlobal_default2.Headers = Headers2;
  nativeGlobal_default2.AbortController = AbortController;
  nativeGlobal_default2.AbortSignal = AbortSignal;
  nativeGlobal_default2.URL = URL;
  URLSearchParamsPolyfill(nativeGlobal_default2);
  nativeGlobal_default2.__invokeAppMethod = __invokeAppMethod;
})();
//# sourceMappingURL=data:application/json;base64,ewogICJ2ZXJzaW9uIjogMywKICAic291cmNlcyI6IFsiLi4vLi4vbHlueC1wcm9taXNlL3NyYy9jb3JlLmpzIiwgIi4uLy4uL2x5bngtcHJvbWlzZS9zcmMvZXM2LWV4dGVuc2lvbnMuanMiLCAiLi4vLi4vbHlueC1wcm9taXNlL3NyYy9yZWplY3Rpb24tdHJhY2tpbmcuanMiLCAiLi4vLi4vbHlueC1wcm9taXNlL3NyYy9pbmRleC5qcyIsICIuLi8uLi8uLi9ub2RlX21vZHVsZXMvLnBucG0vcmVnZW5lcmF0b3ItcnVudGltZUAwLjEzLjcvbm9kZV9tb2R1bGVzL3JlZ2VuZXJhdG9yLXJ1bnRpbWUvcnVudGltZS5qcyIsICIuLi9rZXJuZWwtYnVpbGQvYW5kcm9pZC1wb2x5ZmlsbC5qcyIsICIuLi9zcmMvaW5kZXguYnVpbGQudHMiLCAiLi4vLi4vbHlueC1ydW50aW1lLXNoYXJlZC9zcmMvbmF0aXZlR2xvYmFsLnRzIiwgIi4uLy4uL2x5bngtcnVudGltZS1zaGFyZWQvc3JjL3R0Q29uc29sZS50cyIsICIuLi8uLi9seW54LXJ1bnRpbWUtc2hhcmVkL3NyYy91dGlscy50cyIsICIuLi9zcmMvY29tbW9uL3R0Q29uc29sZS50cyIsICIuLi9zcmMvbW9kdWxlcy9yZXBvcnQvZXJyb3JzLnRzIiwgIi4uL3NyYy9jb21tb24vY29uc3RhbnRzLnRzIiwgIi4uL3NyYy9tb2R1bGVzL3NoYXJlZERhdGEvU2hhcmVEYXRhU3ViamVjdC50cyIsICIuLi9zcmMvY29tbW9uL25hdGl2ZUdsb2JhbC50cyIsICIuLi9zcmMvY29tbW9uL2xvZy50cyIsICIuLi9zcmMvY29tbW9uL3ZlcnNpb24udHMiLCAiLi4vc3JjL2NvbW1vbi9jYWxsYmFja01hbmFnZXIudHMiLCAiLi4vc3JjL21vZHVsZXMvcmVwb3J0L3JlcG9ydC1lcnJvci50cyIsICIuLi9zcmMvbW9kdWxlcy9yZXBvcnQvd3JhcHBlci50cyIsICIuLi9zcmMvbW9kdWxlcy9yZXBvcnQvcmVwb3J0ZXIudHMiLCAiLi4vc3JjL21vZHVsZXMvYW5pbWF0aW9uL2FuaW1hdGlvbi50cyIsICIuLi9zcmMvbW9kdWxlcy9hbmltYXRpb24vZWZmZWN0LnRzIiwgIi4uL3NyYy9tb2R1bGVzL2FuaW1hdGlvbi9hbmltYXRpb25WMi50cyIsICIuLi9zcmMvbW9kdWxlcy9lbGVtZW50L2VsZW1lbnQudHMiLCAiLi4vc3JjL21vZHVsZXMvZWxlbWVudC9pbmRleC50cyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9UZXh0RGVjb2Rlci50cyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9UZXh0RW5jb2Rlci50cyIsICIuLi9zcmMvbW9kdWxlcy9ldmVudC9ldmVudEVtaXR0ZXIudHMiLCAiLi4vc3JjL21vZHVsZXMvZXZlbnQvYW9wLnRzIiwgIi4uL3NyYy9tb2R1bGVzL2V2ZW50L2luZGV4LnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL1JlYWRhYmxlU3RyZWFtLnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL0JvZHlNaXhpbi50cyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9IZWFkZXJzLnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL0Fib3J0Q29udHJvbGxlci50cyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9SZXF1ZXN0LnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL1Jlc3BvbnNlLnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL1VSTC5qcyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9VcmxTZWFyY2hQYXJhbXNQb2x5ZmlsbC5qcyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9FdmVudFNvdXJjZS50cyIsICIuLi9zcmMvbW9kdWxlcy9zZWxlY3RvclF1ZXJ5L1NlbGVjdG9yUXVlcnkudHMiLCAiLi4vc3JjL2x5bngvbHlueC50cyIsICIuLi9zcmMvbW9kdWxlcy9uYXRpdmVNb2R1bGVzL3RleHRJbmZvLnRzIiwgIi4uL3NyYy9tb2R1bGVzL25hdGl2ZU1vZHVsZXMvZXhwb3N1cmUudHMiLCAiLi4vc3JjL21vZHVsZXMvbmF0aXZlTW9kdWxlcy9pbnRlcnNlY3Rpb25PYnNlcnZlci50cyIsICIuLi9zcmMvbW9kdWxlcy9wZXJmb3JtYW5jZS9wZXJmb3JtYW5jZU9ic2VydmVyLnRzIiwgIi4uL3NyYy9tb2R1bGVzL3BlcmZvcm1hbmNlL3BlcmZvcm1hbmNlLnRzIiwgIi4uL3NyYy9tb2R1bGVzL3BlcmZvcm1hbmNlL2luZGV4LnRzIiwgIi4uL3NyYy9jb21tb24vanNiaS50cyIsICIuLi9zcmMvdXRpbC9jYWNoZWRGdW5jdGlvblByb3h5LnRzIiwgIi4uL3NyYy91dGlsL3NldHVwLXByb21pc2UudHMiLCAiLi4vc3JjL3V0aWwvVHJhY2VFdmVudERlZi50cyIsICIuLi9zcmMvYXBwL2FwcC50cyIsICIuLi9zcmMvcmVhY3QvcmVhY3RBcHAudHMiLCAiLi4vc3JjL3N0YW5kYWxvbmUvU3RhbmRhbG9uZUFwcC50cyIsICIuLi9zcmMvYXBwTWFuYWdlci50cyIsICIuLi9zcmMvcG9seWZpbGwvYXJyYXlidWZmZXIudHMiLCAiLi4vc3JjL2luZGV4LmNhcmQudHMiXSwKICAic291cmNlc0NvbnRlbnQiOiBbIi8qKlxuICogQGxpY2Vuc2VcbkNvcHlyaWdodCAoYykgMjAxNCBGb3JiZXMgTGluZGVzYXlcblxuUGVybWlzc2lvbiBpcyBoZXJlYnkgZ3JhbnRlZCwgZnJlZSBvZiBjaGFyZ2UsIHRvIGFueSBwZXJzb24gb2J0YWluaW5nIGEgY29weVxub2YgdGhpcyBzb2Z0d2FyZSBhbmQgYXNzb2NpYXRlZCBkb2N1bWVudGF0aW9uIGZpbGVzICh0aGUgXCJTb2Z0d2FyZVwiKSwgdG8gZGVhbFxuaW4gdGhlIFNvZnR3YXJlIHdpdGhvdXQgcmVzdHJpY3Rpb24sIGluY2x1ZGluZyB3aXRob3V0IGxpbWl0YXRpb24gdGhlIHJpZ2h0c1xudG8gdXNlLCBjb3B5LCBtb2RpZnksIG1lcmdlLCBwdWJsaXNoLCBkaXN0cmlidXRlLCBzdWJsaWNlbnNlLCBhbmQvb3Igc2VsbFxuY29waWVzIG9mIHRoZSBTb2Z0d2FyZSwgYW5kIHRvIHBlcm1pdCBwZXJzb25zIHRvIHdob20gdGhlIFNvZnR3YXJlIGlzXG5mdXJuaXNoZWQgdG8gZG8gc28sIHN1YmplY3QgdG8gdGhlIGZvbGxvd2luZyBjb25kaXRpb25zOlxuXG5UaGUgYWJvdmUgY29weXJpZ2h0IG5vdGljZSBhbmQgdGhpcyBwZXJtaXNzaW9uIG5vdGljZSBzaGFsbCBiZSBpbmNsdWRlZCBpblxuYWxsIGNvcGllcyBvciBzdWJzdGFudGlhbCBwb3J0aW9ucyBvZiB0aGUgU29mdHdhcmUuXG5cblRIRSBTT0ZUV0FSRSBJUyBQUk9WSURFRCBcIkFTIElTXCIsIFdJVEhPVVQgV0FSUkFOVFkgT0YgQU5ZIEtJTkQsIEVYUFJFU1MgT1JcbklNUExJRUQsIElOQ0xVRElORyBCVVQgTk9UIExJTUlURUQgVE8gVEhFIFdBUlJBTlRJRVMgT0YgTUVSQ0hBTlRBQklMSVRZLFxuRklUTkVTUyBGT1IgQSBQQVJUSUNVTEFSIFBVUlBPU0UgQU5EIE5PTklORlJJTkdFTUVOVC4gSU4gTk8gRVZFTlQgU0hBTEwgVEhFXG5BVVRIT1JTIE9SIENPUFlSSUdIVCBIT0xERVJTIEJFIExJQUJMRSBGT1IgQU5ZIENMQUlNLCBEQU1BR0VTIE9SIE9USEVSXG5MSUFCSUxJVFksIFdIRVRIRVIgSU4gQU4gQUNUSU9OIE9GIENPTlRSQUNULCBUT1JUIE9SIE9USEVSV0lTRSwgQVJJU0lORyBGUk9NLFxuT1VUIE9GIE9SIElOIENPTk5FQ1RJT04gV0lUSCBUSEUgU09GVFdBUkUgT1IgVEhFIFVTRSBPUiBPVEhFUiBERUFMSU5HUyBJTlxuVEhFIFNPRlRXQVJFLlxuICovXG4ndXNlIHN0cmljdCc7XG5cbmZ1bmN0aW9uIG5vb3AoKSB7fVxuXG4vLyBTdGF0ZXM6XG4vL1xuLy8gMCAtIHBlbmRpbmdcbi8vIDEgLSBmdWxmaWxsZWQgd2l0aCBfdmFsdWVcbi8vIDIgLSByZWplY3RlZCB3aXRoIF92YWx1ZVxuLy8gMyAtIGFkb3B0ZWQgdGhlIHN0YXRlIG9mIGFub3RoZXIgcHJvbWlzZSwgX3ZhbHVlXG4vL1xuLy8gb25jZSB0aGUgc3RhdGUgaXMgbm8gbG9uZ2VyIHBlbmRpbmcgKDApIGl0IGlzIGltbXV0YWJsZVxuXG4vLyBBbGwgYF9gIHByZWZpeGVkIHByb3BlcnRpZXMgd2lsbCBiZSByZWR1Y2VkIHRvIGBfe3JhbmRvbSBudW1iZXJ9YFxuLy8gYXQgYnVpbGQgdGltZSB0byBvYmZ1c2NhdGUgdGhlbSBhbmQgZGlzY291cmFnZSB0aGVpciB1c2UuXG4vLyBXZSBkb24ndCB1c2Ugc3ltYm9scyBvciBPYmplY3QuZGVmaW5lUHJvcGVydHkgdG8gZnVsbHkgaGlkZSB0aGVtXG4vLyBiZWNhdXNlIHRoZSBwZXJmb3JtYW5jZSBpc24ndCBnb29kIGVub3VnaC5cblxuLy8gdG8gYXZvaWQgdXNpbmcgdHJ5L2NhdGNoIGluc2lkZSBjcml0aWNhbCBmdW5jdGlvbnMsIHdlXG4vLyBleHRyYWN0IHRoZW0gdG8gaGVyZS5cbnZhciBMQVNUX0VSUk9SID0gbnVsbDtcbnZhciBJU19FUlJPUiA9IHt9O1xuZnVuY3Rpb24gZ2V0VGhlbihvYmopIHtcbiAgdHJ5IHtcbiAgICByZXR1cm4gb2JqLnRoZW47XG4gIH0gY2F0Y2ggKGV4KSB7XG4gICAgTEFTVF9FUlJPUiA9IGV4O1xuICAgIHJldHVybiBJU19FUlJPUjtcbiAgfVxufVxuXG5mdW5jdGlvbiB0cnlDYWxsT25lKGZuLCBhKSB7XG4gIHRyeSB7XG4gICAgcmV0dXJuIGZuKGEpO1xuICB9IGNhdGNoIChleCkge1xuICAgIExBU1RfRVJST1IgPSBleDtcbiAgICByZXR1cm4gSVNfRVJST1I7XG4gIH1cbn1cbmZ1bmN0aW9uIHRyeUNhbGxUd28oZm4sIGEsIGIpIHtcbiAgdHJ5IHtcbiAgICBmbihhLCBiKTtcbiAgfSBjYXRjaCAoZXgpIHtcbiAgICBMQVNUX0VSUk9SID0gZXg7XG4gICAgcmV0dXJuIElTX0VSUk9SO1xuICB9XG59XG5cbmZ1bmN0aW9uIHRyaW1TdGFjayhzdGFjaykge1xuICAgIGlmICghc3RhY2spIHtcbiAgICAgICAgcmV0dXJuICcnO1xuICAgIH1cbiAgICBjb25zdCBpbmRleCA9IHN0YWNrLmluZGV4T2YoJ1xcbicpO1xuICAgIGlmIChpbmRleCA9PT0gLTEpIHtcbiAgICAgICAgcmV0dXJuIHN0YWNrO1xuICAgIH1cbiAgICAvLyByZW1vdmUgXCJhdCBQcm9taXNlMlwiIHN0YWNrLlxuICAgIHJldHVybiBzdGFjay5zdWJzdHJpbmcoaW5kZXggKyAxKTtcbn1cblxubW9kdWxlLmV4cG9ydHMgPSAob3B0KSA9PiB7XG4gIHZhciBuZXh0VGljayA9IG9wdC5uZXh0VGljaztcbiAgZnVuY3Rpb24gUHJvbWlzZShmbikge1xuICAgICAgdGhpcy5fX2NyZWF0ZVN0YWNrID0gdHJpbVN0YWNrKG5ldyBFcnJvcignUHJvbWlzZSBjcmVhdGlvbiBzdGFjaycpLnN0YWNrKTtcbiAgICBpZiAodHlwZW9mIHRoaXMgIT09ICdvYmplY3QnKSB7XG4gICAgICB0aHJvdyBuZXcgVHlwZUVycm9yKCdQcm9taXNlcyBtdXN0IGJlIGNvbnN0cnVjdGVkIHZpYSBuZXcnKTtcbiAgICB9XG4gICAgaWYgKHR5cGVvZiBmbiAhPT0gJ2Z1bmN0aW9uJykge1xuICAgICAgdGhyb3cgbmV3IFR5cGVFcnJvcihcIlByb21pc2UgY29uc3RydWN0b3IncyBhcmd1bWVudCBpcyBub3QgYSBmdW5jdGlvblwiKTtcbiAgICB9XG4gICAgdGhpcy5fZGVmZXJyZWRTdGF0ZSA9IDA7XG4gICAgdGhpcy5fc3RhdGUgPSAwO1xuICAgIHRoaXMuX3ZhbHVlID0gbnVsbDtcbiAgICB0aGlzLl9kZWZlcnJlZHMgPSBudWxsO1xuICAgIGlmIChmbiA9PT0gbm9vcCkgcmV0dXJuO1xuICAgIGRvUmVzb2x2ZShmbiwgdGhpcyk7XG4gIH1cbiAgUHJvbWlzZS5fb25IYW5kbGUgPSBudWxsO1xuICBQcm9taXNlLl9vblJlamVjdCA9IG51bGw7XG4gIFByb21pc2UuX25vb3AgPSBub29wO1xuXG4gIFByb21pc2UucHJvdG90eXBlLnRoZW4gPSBmdW5jdGlvbihvbkZ1bGZpbGxlZCwgb25SZWplY3RlZCkge1xuICAgIGlmICh0aGlzLmNvbnN0cnVjdG9yICE9PSBQcm9taXNlKSB7XG4gICAgICByZXR1cm4gc2FmZVRoZW4odGhpcywgb25GdWxmaWxsZWQsIG9uUmVqZWN0ZWQpO1xuICAgIH1cbiAgICB2YXIgcmVzID0gbmV3IFByb21pc2Uobm9vcCk7XG4gICAgaGFuZGxlKHRoaXMsIG5ldyBIYW5kbGVyKG9uRnVsZmlsbGVkLCBvblJlamVjdGVkLCByZXMpKTtcbiAgICByZXR1cm4gcmVzO1xuICB9O1xuXG4gIGZ1bmN0aW9uIHNhZmVUaGVuKHNlbGYsIG9uRnVsZmlsbGVkLCBvblJlamVjdGVkKSB7XG4gICAgcmV0dXJuIG5ldyBzZWxmLmNvbnN0cnVjdG9yKGZ1bmN0aW9uKHJlc29sdmUsIHJlamVjdCkge1xuICAgICAgdmFyIHJlcyA9IG5ldyBQcm9taXNlKG5vb3ApO1xuICAgICAgcmVzLnRoZW4ocmVzb2x2ZSwgcmVqZWN0KTtcbiAgICAgIGhhbmRsZShzZWxmLCBuZXcgSGFuZGxlcihvbkZ1bGZpbGxlZCwgb25SZWplY3RlZCwgcmVzKSk7XG4gICAgfSk7XG4gIH1cbiAgZnVuY3Rpb24gaGFuZGxlKHNlbGYsIGRlZmVycmVkKSB7XG4gICAgd2hpbGUgKHNlbGYuX3N0YXRlID09PSAzKSB7XG4gICAgICBzZWxmID0gc2VsZi5fdmFsdWU7XG4gICAgfVxuICAgIGlmIChQcm9taXNlLl9vbkhhbmRsZSkge1xuICAgICAgUHJvbWlzZS5fb25IYW5kbGUoc2VsZik7XG4gICAgfVxuICAgIGlmIChzZWxmLl9zdGF0ZSA9PT0gMCkge1xuICAgICAgaWYgKHNlbGYuX2RlZmVycmVkU3RhdGUgPT09IDApIHtcbiAgICAgICAgc2VsZi5fZGVmZXJyZWRTdGF0ZSA9IDE7XG4gICAgICAgIHNlbGYuX2RlZmVycmVkcyA9IGRlZmVycmVkO1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgICBpZiAoc2VsZi5fZGVmZXJyZWRTdGF0ZSA9PT0gMSkge1xuICAgICAgICBzZWxmLl9kZWZlcnJlZFN0YXRlID0gMjtcbiAgICAgICAgc2VsZi5fZGVmZXJyZWRzID0gW3NlbGYuX2RlZmVycmVkcywgZGVmZXJyZWRdO1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgICBzZWxmLl9kZWZlcnJlZHMucHVzaChkZWZlcnJlZCk7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIGhhbmRsZVJlc29sdmVkKHNlbGYsIGRlZmVycmVkKTtcbiAgfVxuXG4gIGZ1bmN0aW9uIGhhbmRsZVJlc29sdmVkKHNlbGYsIGRlZmVycmVkKSB7XG4gICAgbmV4dFRpY2soZnVuY3Rpb24oKSB7XG4gICAgICB2YXIgY2IgPSBzZWxmLl9zdGF0ZSA9PT0gMSA/IGRlZmVycmVkLm9uRnVsZmlsbGVkIDogZGVmZXJyZWQub25SZWplY3RlZDtcbiAgICAgIGlmIChjYiA9PT0gbnVsbCkge1xuICAgICAgICBpZiAoc2VsZi5fc3RhdGUgPT09IDEpIHtcbiAgICAgICAgICByZXNvbHZlKGRlZmVycmVkLnByb21pc2UsIHNlbGYuX3ZhbHVlKTtcbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICByZWplY3QoZGVmZXJyZWQucHJvbWlzZSwgc2VsZi5fdmFsdWUpO1xuICAgICAgICB9XG4gICAgICAgIHJldHVybjtcbiAgICAgIH1cbiAgICAgIHZhciByZXQgPSB0cnlDYWxsT25lKGNiLCBzZWxmLl92YWx1ZSk7XG4gICAgICBpZiAocmV0ID09PSBJU19FUlJPUikge1xuICAgICAgICByZWplY3QoZGVmZXJyZWQucHJvbWlzZSwgTEFTVF9FUlJPUik7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICByZXNvbHZlKGRlZmVycmVkLnByb21pc2UsIHJldCk7XG4gICAgICB9XG4gICAgfSk7XG4gIH1cbiAgZnVuY3Rpb24gcmVzb2x2ZShzZWxmLCBuZXdWYWx1ZSkge1xuICAgIC8vIFByb21pc2UgUmVzb2x1dGlvbiBQcm9jZWR1cmU6IGh0dHBzOi8vZ2l0aHViLmNvbS9wcm9taXNlcy1hcGx1cy9wcm9taXNlcy1zcGVjI3RoZS1wcm9taXNlLXJlc29sdXRpb24tcHJvY2VkdXJlXG4gICAgaWYgKG5ld1ZhbHVlID09PSBzZWxmKSB7XG4gICAgICByZXR1cm4gcmVqZWN0KHNlbGYsIG5ldyBUeXBlRXJyb3IoJ0EgcHJvbWlzZSBjYW5ub3QgYmUgcmVzb2x2ZWQgd2l0aCBpdHNlbGYuJykpO1xuICAgIH1cbiAgICBpZiAobmV3VmFsdWUgJiYgKHR5cGVvZiBuZXdWYWx1ZSA9PT0gJ29iamVjdCcgfHwgdHlwZW9mIG5ld1ZhbHVlID09PSAnZnVuY3Rpb24nKSkge1xuICAgICAgdmFyIHRoZW4gPSBnZXRUaGVuKG5ld1ZhbHVlKTtcbiAgICAgIGlmICh0aGVuID09PSBJU19FUlJPUikge1xuICAgICAgICByZXR1cm4gcmVqZWN0KHNlbGYsIExBU1RfRVJST1IpO1xuICAgICAgfVxuICAgICAgaWYgKHRoZW4gPT09IHNlbGYudGhlbiAmJiBuZXdWYWx1ZSBpbnN0YW5jZW9mIFByb21pc2UpIHtcbiAgICAgICAgc2VsZi5fc3RhdGUgPSAzO1xuICAgICAgICBzZWxmLl92YWx1ZSA9IG5ld1ZhbHVlO1xuICAgICAgICBmaW5hbGUoc2VsZik7XG4gICAgICAgIHJldHVybjtcbiAgICAgIH0gZWxzZSBpZiAodHlwZW9mIHRoZW4gPT09ICdmdW5jdGlvbicpIHtcbiAgICAgICAgZG9SZXNvbHZlKHRoZW4uYmluZChuZXdWYWx1ZSksIHNlbGYpO1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgfVxuICAgIHNlbGYuX3N0YXRlID0gMTtcbiAgICBzZWxmLl92YWx1ZSA9IG5ld1ZhbHVlO1xuICAgIGZpbmFsZShzZWxmKTtcbiAgfVxuXG4gIGZ1bmN0aW9uIHJlamVjdChzZWxmLCBuZXdWYWx1ZSkge1xuICAgIHNlbGYuX3N0YXRlID0gMjtcbiAgICBzZWxmLl92YWx1ZSA9IG5ld1ZhbHVlO1xuICAgIGlmIChQcm9taXNlLl9vblJlamVjdCkge1xuICAgICAgUHJvbWlzZS5fb25SZWplY3Qoc2VsZiwgbmV3VmFsdWUpO1xuICAgIH1cbiAgICBmaW5hbGUoc2VsZik7XG4gIH1cbiAgZnVuY3Rpb24gZmluYWxlKHNlbGYpIHtcbiAgICBpZiAoc2VsZi5fZGVmZXJyZWRTdGF0ZSA9PT0gMSkge1xuICAgICAgaGFuZGxlKHNlbGYsIHNlbGYuX2RlZmVycmVkcyk7XG4gICAgICBzZWxmLl9kZWZlcnJlZHMgPSBudWxsO1xuICAgIH1cbiAgICBpZiAoc2VsZi5fZGVmZXJyZWRTdGF0ZSA9PT0gMikge1xuICAgICAgZm9yICh2YXIgaSA9IDA7IGkgPCBzZWxmLl9kZWZlcnJlZHMubGVuZ3RoOyBpKyspIHtcbiAgICAgICAgaGFuZGxlKHNlbGYsIHNlbGYuX2RlZmVycmVkc1tpXSk7XG4gICAgICB9XG4gICAgICBzZWxmLl9kZWZlcnJlZHMgPSBudWxsO1xuICAgIH1cbiAgfVxuXG4gIGZ1bmN0aW9uIEhhbmRsZXIob25GdWxmaWxsZWQsIG9uUmVqZWN0ZWQsIHByb21pc2UpIHtcbiAgICB0aGlzLm9uRnVsZmlsbGVkID0gdHlwZW9mIG9uRnVsZmlsbGVkID09PSAnZnVuY3Rpb24nID8gb25GdWxmaWxsZWQgOiBudWxsO1xuICAgIHRoaXMub25SZWplY3RlZCA9IHR5cGVvZiBvblJlamVjdGVkID09PSAnZnVuY3Rpb24nID8gb25SZWplY3RlZCA6IG51bGw7XG4gICAgdGhpcy5wcm9taXNlID0gcHJvbWlzZTtcbiAgfVxuXG4gIC8qKlxuICAgKiBUYWtlIGEgcG90ZW50aWFsbHkgbWlzYmVoYXZpbmcgcmVzb2x2ZXIgZnVuY3Rpb24gYW5kIG1ha2Ugc3VyZVxuICAgKiBvbkZ1bGZpbGxlZCBhbmQgb25SZWplY3RlZCBhcmUgb25seSBjYWxsZWQgb25jZS5cbiAgICpcbiAgICogTWFrZXMgbm8gZ3VhcmFudGVlcyBhYm91dCBhc3luY2hyb255LlxuICAgKi9cbiAgZnVuY3Rpb24gZG9SZXNvbHZlKGZuLCBwcm9taXNlKSB7XG4gICAgdmFyIGRvbmUgPSBmYWxzZTtcbiAgICB2YXIgcmVzID0gdHJ5Q2FsbFR3byhcbiAgICAgIGZuLFxuICAgICAgZnVuY3Rpb24odmFsdWUpIHtcbiAgICAgICAgaWYgKGRvbmUpIHJldHVybjtcbiAgICAgICAgZG9uZSA9IHRydWU7XG4gICAgICAgIHJlc29sdmUocHJvbWlzZSwgdmFsdWUpO1xuICAgICAgfSxcbiAgICAgIGZ1bmN0aW9uKHJlYXNvbikge1xuICAgICAgICBpZiAoZG9uZSkgcmV0dXJuO1xuICAgICAgICBkb25lID0gdHJ1ZTtcbiAgICAgICAgcmVqZWN0KHByb21pc2UsIHJlYXNvbik7XG4gICAgICB9XG4gICAgKTtcbiAgICBpZiAoIWRvbmUgJiYgcmVzID09PSBJU19FUlJPUikge1xuICAgICAgZG9uZSA9IHRydWU7XG4gICAgICByZWplY3QocHJvbWlzZSwgTEFTVF9FUlJPUik7XG4gICAgfVxuICB9XG4gIHJldHVybiBQcm9taXNlO1xufTtcbiIsICIvKipcbiAqIEBsaWNlbnNlXG5Db3B5cmlnaHQgKGMpIDIwMTQgRm9yYmVzIExpbmRlc2F5XG5cblBlcm1pc3Npb24gaXMgaGVyZWJ5IGdyYW50ZWQsIGZyZWUgb2YgY2hhcmdlLCB0byBhbnkgcGVyc29uIG9idGFpbmluZyBhIGNvcHlcbm9mIHRoaXMgc29mdHdhcmUgYW5kIGFzc29jaWF0ZWQgZG9jdW1lbnRhdGlvbiBmaWxlcyAodGhlIFwiU29mdHdhcmVcIiksIHRvIGRlYWxcbmluIHRoZSBTb2Z0d2FyZSB3aXRob3V0IHJlc3RyaWN0aW9uLCBpbmNsdWRpbmcgd2l0aG91dCBsaW1pdGF0aW9uIHRoZSByaWdodHNcbnRvIHVzZSwgY29weSwgbW9kaWZ5LCBtZXJnZSwgcHVibGlzaCwgZGlzdHJpYnV0ZSwgc3VibGljZW5zZSwgYW5kL29yIHNlbGxcbmNvcGllcyBvZiB0aGUgU29mdHdhcmUsIGFuZCB0byBwZXJtaXQgcGVyc29ucyB0byB3aG9tIHRoZSBTb2Z0d2FyZSBpc1xuZnVybmlzaGVkIHRvIGRvIHNvLCBzdWJqZWN0IHRvIHRoZSBmb2xsb3dpbmcgY29uZGl0aW9uczpcblxuVGhlIGFib3ZlIGNvcHlyaWdodCBub3RpY2UgYW5kIHRoaXMgcGVybWlzc2lvbiBub3RpY2Ugc2hhbGwgYmUgaW5jbHVkZWQgaW5cbmFsbCBjb3BpZXMgb3Igc3Vic3RhbnRpYWwgcG9ydGlvbnMgb2YgdGhlIFNvZnR3YXJlLlxuXG5USEUgU09GVFdBUkUgSVMgUFJPVklERUQgXCJBUyBJU1wiLCBXSVRIT1VUIFdBUlJBTlRZIE9GIEFOWSBLSU5ELCBFWFBSRVNTIE9SXG5JTVBMSUVELCBJTkNMVURJTkcgQlVUIE5PVCBMSU1JVEVEIFRPIFRIRSBXQVJSQU5USUVTIE9GIE1FUkNIQU5UQUJJTElUWSxcbkZJVE5FU1MgRk9SIEEgUEFSVElDVUxBUiBQVVJQT1NFIEFORCBOT05JTkZSSU5HRU1FTlQuIElOIE5PIEVWRU5UIFNIQUxMIFRIRVxuQVVUSE9SUyBPUiBDT1BZUklHSFQgSE9MREVSUyBCRSBMSUFCTEUgRk9SIEFOWSBDTEFJTSwgREFNQUdFUyBPUiBPVEhFUlxuTElBQklMSVRZLCBXSEVUSEVSIElOIEFOIEFDVElPTiBPRiBDT05UUkFDVCwgVE9SVCBPUiBPVEhFUldJU0UsIEFSSVNJTkcgRlJPTSxcbk9VVCBPRiBPUiBJTiBDT05ORUNUSU9OIFdJVEggVEhFIFNPRlRXQVJFIE9SIFRIRSBVU0UgT1IgT1RIRVIgREVBTElOR1MgSU5cblRIRSBTT0ZUV0FSRS5cbiAqL1xuJ3VzZSBzdHJpY3QnO1xuXG4vL1RoaXMgZmlsZSBjb250YWlucyB0aGUgRVM2IGV4dGVuc2lvbnMgdG8gdGhlIGNvcmUgUHJvbWlzZXMvQSsgQVBJXG5cbm1vZHVsZS5leHBvcnRzID0gUHJvbWlzZSA9PiB7XG4gIC8qIFN0YXRpYyBGdW5jdGlvbnMgKi9cblxuICB2YXIgVFJVRSA9IHZhbHVlUHJvbWlzZSh0cnVlKTtcbiAgdmFyIEZBTFNFID0gdmFsdWVQcm9taXNlKGZhbHNlKTtcbiAgdmFyIE5VTEwgPSB2YWx1ZVByb21pc2UobnVsbCk7XG4gIHZhciBVTkRFRklORUQgPSB2YWx1ZVByb21pc2UodW5kZWZpbmVkKTtcbiAgdmFyIFpFUk8gPSB2YWx1ZVByb21pc2UoMCk7XG4gIHZhciBFTVBUWVNUUklORyA9IHZhbHVlUHJvbWlzZSgnJyk7XG5cbiAgZnVuY3Rpb24gdmFsdWVQcm9taXNlKHZhbHVlKSB7XG4gICAgdmFyIHAgPSBuZXcgUHJvbWlzZShQcm9taXNlLl9ub29wKTtcbiAgICBwLl9zdGF0ZSA9IDE7XG4gICAgcC5fdmFsdWUgPSB2YWx1ZTtcbiAgICByZXR1cm4gcDtcbiAgfVxuICBQcm9taXNlLnJlc29sdmUgPSBmdW5jdGlvbih2YWx1ZSkge1xuICAgIGlmICh2YWx1ZSBpbnN0YW5jZW9mIFByb21pc2UpIHJldHVybiB2YWx1ZTtcblxuICAgIGlmICh2YWx1ZSA9PT0gbnVsbCkgcmV0dXJuIE5VTEw7XG4gICAgaWYgKHZhbHVlID09PSB1bmRlZmluZWQpIHJldHVybiBVTkRFRklORUQ7XG4gICAgaWYgKHZhbHVlID09PSB0cnVlKSByZXR1cm4gVFJVRTtcbiAgICBpZiAodmFsdWUgPT09IGZhbHNlKSByZXR1cm4gRkFMU0U7XG4gICAgaWYgKHZhbHVlID09PSAwKSByZXR1cm4gWkVSTztcbiAgICBpZiAodmFsdWUgPT09ICcnKSByZXR1cm4gRU1QVFlTVFJJTkc7XG5cbiAgICBpZiAodHlwZW9mIHZhbHVlID09PSAnb2JqZWN0JyB8fCB0eXBlb2YgdmFsdWUgPT09ICdmdW5jdGlvbicpIHtcbiAgICAgIHRyeSB7XG4gICAgICAgIHZhciB0aGVuID0gdmFsdWUudGhlbjtcbiAgICAgICAgaWYgKHR5cGVvZiB0aGVuID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgICAgcmV0dXJuIG5ldyBQcm9taXNlKHRoZW4uYmluZCh2YWx1ZSkpO1xuICAgICAgICB9XG4gICAgICB9IGNhdGNoIChleCkge1xuICAgICAgICByZXR1cm4gbmV3IFByb21pc2UoZnVuY3Rpb24ocmVzb2x2ZSwgcmVqZWN0KSB7XG4gICAgICAgICAgcmVqZWN0KGV4KTtcbiAgICAgICAgfSk7XG4gICAgICB9XG4gICAgfVxuICAgIHJldHVybiB2YWx1ZVByb21pc2UodmFsdWUpO1xuICB9O1xuXG4gIHZhciBpdGVyYWJsZVRvQXJyYXkgPSBmdW5jdGlvbihpdGVyYWJsZSkge1xuICAgIGlmICh0eXBlb2YgQXJyYXkuZnJvbSA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgLy8gRVMyMDE1KywgaXRlcmFibGVzIGV4aXN0XG4gICAgICBpdGVyYWJsZVRvQXJyYXkgPSBBcnJheS5mcm9tO1xuICAgICAgcmV0dXJuIEFycmF5LmZyb20oaXRlcmFibGUpO1xuICAgIH1cblxuICAgIC8vIEVTNSwgb25seSBhcnJheXMgYW5kIGFycmF5LWxpa2VzIGV4aXN0XG4gICAgaXRlcmFibGVUb0FycmF5ID0gZnVuY3Rpb24oeCkge1xuICAgICAgcmV0dXJuIEFycmF5LnByb3RvdHlwZS5zbGljZS5jYWxsKHgpO1xuICAgIH07XG4gICAgcmV0dXJuIEFycmF5LnByb3RvdHlwZS5zbGljZS5jYWxsKGl0ZXJhYmxlKTtcbiAgfTtcblxuICBQcm9taXNlLmFsbCA9IGZ1bmN0aW9uKGFycikge1xuICAgIHZhciBhcmdzID0gaXRlcmFibGVUb0FycmF5KGFycik7XG5cbiAgICByZXR1cm4gbmV3IFByb21pc2UoZnVuY3Rpb24ocmVzb2x2ZSwgcmVqZWN0KSB7XG4gICAgICBpZiAoYXJncy5sZW5ndGggPT09IDApIHJldHVybiByZXNvbHZlKFtdKTtcbiAgICAgIHZhciByZW1haW5pbmcgPSBhcmdzLmxlbmd0aDtcbiAgICAgIGZ1bmN0aW9uIHJlcyhpLCB2YWwpIHtcbiAgICAgICAgaWYgKHZhbCAmJiAodHlwZW9mIHZhbCA9PT0gJ29iamVjdCcgfHwgdHlwZW9mIHZhbCA9PT0gJ2Z1bmN0aW9uJykpIHtcbiAgICAgICAgICBpZiAodmFsIGluc3RhbmNlb2YgUHJvbWlzZSAmJiB2YWwudGhlbiA9PT0gUHJvbWlzZS5wcm90b3R5cGUudGhlbikge1xuICAgICAgICAgICAgd2hpbGUgKHZhbC5fc3RhdGUgPT09IDMpIHtcbiAgICAgICAgICAgICAgdmFsID0gdmFsLl92YWx1ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGlmICh2YWwuX3N0YXRlID09PSAxKSByZXR1cm4gcmVzKGksIHZhbC5fdmFsdWUpO1xuICAgICAgICAgICAgaWYgKHZhbC5fc3RhdGUgPT09IDIpIHJlamVjdCh2YWwuX3ZhbHVlKTtcbiAgICAgICAgICAgIHZhbC50aGVuKGZ1bmN0aW9uKHZhbCkge1xuICAgICAgICAgICAgICByZXMoaSwgdmFsKTtcbiAgICAgICAgICAgIH0sIHJlamVjdCk7XG4gICAgICAgICAgICByZXR1cm47XG4gICAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAgIHZhciB0aGVuID0gdmFsLnRoZW47XG4gICAgICAgICAgICBpZiAodHlwZW9mIHRoZW4gPT09ICdmdW5jdGlvbicpIHtcbiAgICAgICAgICAgICAgdmFyIHAgPSBuZXcgUHJvbWlzZSh0aGVuLmJpbmQodmFsKSk7XG4gICAgICAgICAgICAgIHAudGhlbihmdW5jdGlvbih2YWwpIHtcbiAgICAgICAgICAgICAgICByZXMoaSwgdmFsKTtcbiAgICAgICAgICAgICAgfSwgcmVqZWN0KTtcbiAgICAgICAgICAgICAgcmV0dXJuO1xuICAgICAgICAgICAgfVxuICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICBhcmdzW2ldID0gdmFsO1xuICAgICAgICBpZiAoLS1yZW1haW5pbmcgPT09IDApIHtcbiAgICAgICAgICByZXNvbHZlKGFyZ3MpO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgICBmb3IgKHZhciBpID0gMDsgaSA8IGFyZ3MubGVuZ3RoOyBpKyspIHtcbiAgICAgICAgcmVzKGksIGFyZ3NbaV0pO1xuICAgICAgfVxuICAgIH0pO1xuICB9O1xuXG4gIFByb21pc2UucmVqZWN0ID0gZnVuY3Rpb24odmFsdWUpIHtcbiAgICByZXR1cm4gbmV3IFByb21pc2UoZnVuY3Rpb24ocmVzb2x2ZSwgcmVqZWN0KSB7XG4gICAgICByZWplY3QodmFsdWUpO1xuICAgIH0pO1xuICB9O1xuXG4gIFByb21pc2UucmFjZSA9IGZ1bmN0aW9uKHZhbHVlcykge1xuICAgIHJldHVybiBuZXcgUHJvbWlzZShmdW5jdGlvbihyZXNvbHZlLCByZWplY3QpIHtcbiAgICAgIGl0ZXJhYmxlVG9BcnJheSh2YWx1ZXMpLmZvckVhY2goZnVuY3Rpb24odmFsdWUpIHtcbiAgICAgICAgUHJvbWlzZS5yZXNvbHZlKHZhbHVlKS50aGVuKHJlc29sdmUsIHJlamVjdCk7XG4gICAgICB9KTtcbiAgICB9KTtcbiAgfTtcblxuICAvKiBQcm90b3R5cGUgTWV0aG9kcyAqL1xuXG4gIFByb21pc2UucHJvdG90eXBlWydjYXRjaCddID0gZnVuY3Rpb24ob25SZWplY3RlZCkge1xuICAgIHJldHVybiB0aGlzLnRoZW4obnVsbCwgb25SZWplY3RlZCk7XG4gIH07XG4gIFByb21pc2UucHJvdG90eXBlLmRvbmUgPSBmdW5jdGlvbihvbkZ1bGZpbGxlZCwgb25SZWplY3RlZCkge1xuICAgIHZhciBzZWxmID0gYXJndW1lbnRzLmxlbmd0aCA/IHRoaXMudGhlbi5hcHBseSh0aGlzLCBhcmd1bWVudHMpIDogdGhpcztcbiAgICBzZWxmLnRoZW4obnVsbCwgZnVuY3Rpb24oZXJyKSB7XG4gICAgICBzZXRUaW1lb3V0KGZ1bmN0aW9uKCkge1xuICAgICAgICB0aHJvdyBlcnI7XG4gICAgICB9LCAwKTtcbiAgICB9KTtcbiAgfTtcbiAgUHJvbWlzZS5wcm90b3R5cGUuZmluYWxseSA9IGZ1bmN0aW9uKGYpIHtcbiAgICByZXR1cm4gdGhpcy50aGVuKFxuICAgICAgZnVuY3Rpb24odmFsdWUpIHtcbiAgICAgICAgcmV0dXJuIFByb21pc2UucmVzb2x2ZShmKCkpLnRoZW4oZnVuY3Rpb24oKSB7XG4gICAgICAgICAgcmV0dXJuIHZhbHVlO1xuICAgICAgICB9KTtcbiAgICAgIH0sXG4gICAgICBmdW5jdGlvbihlcnIpIHtcbiAgICAgICAgcmV0dXJuIFByb21pc2UucmVzb2x2ZShmKCkpLnRoZW4oZnVuY3Rpb24oKSB7XG4gICAgICAgICAgdGhyb3cgZXJyO1xuICAgICAgICB9KTtcbiAgICAgIH1cbiAgICApO1xuICB9O1xuICByZXR1cm4gUHJvbWlzZTtcbn07XG4iLCAiLyoqXG4gKiBAbGljZW5zZVxuQ29weXJpZ2h0IChjKSAyMDE0IEZvcmJlcyBMaW5kZXNheVxuXG5QZXJtaXNzaW9uIGlzIGhlcmVieSBncmFudGVkLCBmcmVlIG9mIGNoYXJnZSwgdG8gYW55IHBlcnNvbiBvYnRhaW5pbmcgYSBjb3B5XG5vZiB0aGlzIHNvZnR3YXJlIGFuZCBhc3NvY2lhdGVkIGRvY3VtZW50YXRpb24gZmlsZXMgKHRoZSBcIlNvZnR3YXJlXCIpLCB0byBkZWFsXG5pbiB0aGUgU29mdHdhcmUgd2l0aG91dCByZXN0cmljdGlvbiwgaW5jbHVkaW5nIHdpdGhvdXQgbGltaXRhdGlvbiB0aGUgcmlnaHRzXG50byB1c2UsIGNvcHksIG1vZGlmeSwgbWVyZ2UsIHB1Ymxpc2gsIGRpc3RyaWJ1dGUsIHN1YmxpY2Vuc2UsIGFuZC9vciBzZWxsXG5jb3BpZXMgb2YgdGhlIFNvZnR3YXJlLCBhbmQgdG8gcGVybWl0IHBlcnNvbnMgdG8gd2hvbSB0aGUgU29mdHdhcmUgaXNcbmZ1cm5pc2hlZCB0byBkbyBzbywgc3ViamVjdCB0byB0aGUgZm9sbG93aW5nIGNvbmRpdGlvbnM6XG5cblRoZSBhYm92ZSBjb3B5cmlnaHQgbm90aWNlIGFuZCB0aGlzIHBlcm1pc3Npb24gbm90aWNlIHNoYWxsIGJlIGluY2x1ZGVkIGluXG5hbGwgY29waWVzIG9yIHN1YnN0YW50aWFsIHBvcnRpb25zIG9mIHRoZSBTb2Z0d2FyZS5cblxuVEhFIFNPRlRXQVJFIElTIFBST1ZJREVEIFwiQVMgSVNcIiwgV0lUSE9VVCBXQVJSQU5UWSBPRiBBTlkgS0lORCwgRVhQUkVTUyBPUlxuSU1QTElFRCwgSU5DTFVESU5HIEJVVCBOT1QgTElNSVRFRCBUTyBUSEUgV0FSUkFOVElFUyBPRiBNRVJDSEFOVEFCSUxJVFksXG5GSVRORVNTIEZPUiBBIFBBUlRJQ1VMQVIgUFVSUE9TRSBBTkQgTk9OSU5GUklOR0VNRU5ULiBJTiBOTyBFVkVOVCBTSEFMTCBUSEVcbkFVVEhPUlMgT1IgQ09QWVJJR0hUIEhPTERFUlMgQkUgTElBQkxFIEZPUiBBTlkgQ0xBSU0sIERBTUFHRVMgT1IgT1RIRVJcbkxJQUJJTElUWSwgV0hFVEhFUiBJTiBBTiBBQ1RJT04gT0YgQ09OVFJBQ1QsIFRPUlQgT1IgT1RIRVJXSVNFLCBBUklTSU5HIEZST00sXG5PVVQgT0YgT1IgSU4gQ09OTkVDVElPTiBXSVRIIFRIRSBTT0ZUV0FSRSBPUiBUSEUgVVNFIE9SIE9USEVSIERFQUxJTkdTIElOXG5USEUgU09GVFdBUkUuXG4gKi9cbid1c2Ugc3RyaWN0JztcblxubW9kdWxlLmV4cG9ydHMgPSAoUHJvbWlzZSwgc2V0VGltZW91dCwgY2xlYXJUaW1lb3V0KSA9PiB7XG4gIHZhciBERUZBVUxUX1dISVRFTElTVCA9IFtSZWZlcmVuY2VFcnJvciwgVHlwZUVycm9yLCBSYW5nZUVycm9yXTtcblxuICB2YXIgZW5hYmxlZCA9IGZhbHNlO1xuXG4gIGZ1bmN0aW9uIGRpc2FibGUoKSB7XG4gICAgZW5hYmxlZCA9IGZhbHNlO1xuICAgIFByb21pc2UuX29uSGFuZGxlID0gbnVsbDtcbiAgICBQcm9taXNlLl9vblJlamVjdCA9IG51bGw7XG4gIH1cblxuICBmdW5jdGlvbiBlbmFibGUob3B0aW9ucykge1xuICAgIG9wdGlvbnMgPSBvcHRpb25zIHx8IHt9O1xuICAgIGlmIChlbmFibGVkKSBkaXNhYmxlKCk7XG4gICAgZW5hYmxlZCA9IHRydWU7XG4gICAgdmFyIGlkID0gMDtcbiAgICB2YXIgZGlzcGxheUlkID0gMDtcbiAgICB2YXIgcmVqZWN0aW9ucyA9IHt9O1xuICAgIFByb21pc2UuX29uSGFuZGxlID0gZnVuY3Rpb24ocHJvbWlzZSkge1xuICAgICAgaWYgKFxuICAgICAgICBwcm9taXNlLl9zdGF0ZSA9PT0gMiAmJiAvLyBJUyBSRUpFQ1RFRFxuICAgICAgICByZWplY3Rpb25zW3Byb21pc2UuX3JlamVjdGlvbklkXVxuICAgICAgKSB7XG4gICAgICAgIGlmIChyZWplY3Rpb25zW3Byb21pc2UuX3JlamVjdGlvbklkXS5sb2dnZWQpIHtcbiAgICAgICAgICBvbkhhbmRsZWQocHJvbWlzZS5fcmVqZWN0aW9uSWQpO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIGNsZWFyVGltZW91dCAmJiBjbGVhclRpbWVvdXQocmVqZWN0aW9uc1twcm9taXNlLl9yZWplY3Rpb25JZF0udGltZW91dCk7XG4gICAgICAgIH1cbiAgICAgICAgZGVsZXRlIHJlamVjdGlvbnNbcHJvbWlzZS5fcmVqZWN0aW9uSWRdO1xuICAgICAgfVxuICAgIH07XG4gICAgUHJvbWlzZS5fb25SZWplY3QgPSBmdW5jdGlvbihwcm9taXNlLCBlcnIpIHtcbiAgICAgIGlmIChwcm9taXNlLl9kZWZlcnJlZFN0YXRlID09PSAwKSB7XG4gICAgICAgIC8vIG5vdCB5ZXQgaGFuZGxlZFxuICAgICAgICBwcm9taXNlLl9yZWplY3Rpb25JZCA9IGlkKys7XG4gICAgICAgIHJlamVjdGlvbnNbcHJvbWlzZS5fcmVqZWN0aW9uSWRdID0ge1xuICAgICAgICAgIGRpc3BsYXlJZDogbnVsbCxcbiAgICAgICAgICBlcnJvcjogZXJyLFxuICAgICAgICAgIHRpbWVvdXQ6IHNldFRpbWVvdXQoXG4gICAgICAgICAgICBvblVuaGFuZGxlZC5iaW5kKG51bGwsIHByb21pc2UpLCAwKSxcbiAgICAgICAgICBsb2dnZWQ6IGZhbHNlLFxuICAgICAgICB9O1xuICAgICAgfVxuICAgIH07XG4gICAgZnVuY3Rpb24gb25VbmhhbmRsZWQocHJvbWlzZSkge1xuICAgICAgY29uc3QgaWQgPSBwcm9taXNlLl9yZWplY3Rpb25JZDtcbiAgICAgIGlmIChvcHRpb25zLmFsbFJlamVjdGlvbnMgfHwgbWF0Y2hXaGl0ZWxpc3QocmVqZWN0aW9uc1tpZF0uZXJyb3IsIG9wdGlvbnMud2hpdGVsaXN0IHx8IERFRkFVTFRfV0hJVEVMSVNUKSkge1xuICAgICAgICByZWplY3Rpb25zW2lkXS5kaXNwbGF5SWQgPSBkaXNwbGF5SWQrKztcbiAgICAgICAgaWYgKG9wdGlvbnMub25VbmhhbmRsZWQpIHtcbiAgICAgICAgICByZWplY3Rpb25zW2lkXS5sb2dnZWQgPSB0cnVlO1xuICAgICAgICAgIGlmIChyZWplY3Rpb25zW2lkXS5lcnJvciAmJiAhKHJlamVjdGlvbnNbaWRdLmVycm9yIGluc3RhbmNlb2YgRXJyb3IpKSB7XG4gICAgICAgICAgICBjb25zdCBlcnJvciA9IG5ldyBFcnJvcihKU09OLnN0cmluZ2lmeShyZWplY3Rpb25zW2lkXS5lcnJvcikpO1xuICAgICAgICAgICAgZXJyb3Iuc3RhY2sgPSBwcm9taXNlLl9fY3JlYXRlU3RhY2s7XG4gICAgICAgICAgICByZWplY3Rpb25zW2lkXS5lcnJvciA9IGVycm9yO1xuICAgICAgICAgIH1cbiAgICAgICAgICBvcHRpb25zLm9uVW5oYW5kbGVkKHJlamVjdGlvbnNbaWRdLmRpc3BsYXlJZCwgcmVqZWN0aW9uc1tpZF0uZXJyb3IpO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIHJlamVjdGlvbnNbaWRdLmxvZ2dlZCA9IHRydWU7XG4gICAgICAgICAgbG9nRXJyb3IocmVqZWN0aW9uc1tpZF0uZGlzcGxheUlkLCByZWplY3Rpb25zW2lkXS5lcnJvcik7XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICB9XG4gICAgZnVuY3Rpb24gb25IYW5kbGVkKGlkKSB7XG4gICAgICBpZiAocmVqZWN0aW9uc1tpZF0ubG9nZ2VkKSB7XG4gICAgICAgIGlmIChvcHRpb25zLm9uSGFuZGxlZCkge1xuICAgICAgICAgIG9wdGlvbnMub25IYW5kbGVkKHJlamVjdGlvbnNbaWRdLmRpc3BsYXlJZCwgcmVqZWN0aW9uc1tpZF0uZXJyb3IpO1xuICAgICAgICB9IGVsc2UgaWYgKCFyZWplY3Rpb25zW2lkXS5vblVuaGFuZGxlZCkge1xuICAgICAgICAgIGNvbnNvbGUud2FybignUHJvbWlzZSBSZWplY3Rpb24gSGFuZGxlZCAoaWQ6ICcgKyByZWplY3Rpb25zW2lkXS5kaXNwbGF5SWQgKyAnKTonKTtcbiAgICAgICAgICBjb25zb2xlLndhcm4oXG4gICAgICAgICAgICAnICBUaGlzIG1lYW5zIHlvdSBjYW4gaWdub3JlIGFueSBwcmV2aW91cyBtZXNzYWdlcyBvZiB0aGUgZm9ybSBcIlBvc3NpYmxlIFVuaGFuZGxlZCBQcm9taXNlIFJlamVjdGlvblwiIHdpdGggaWQgJyArXG4gICAgICAgICAgICAgIHJlamVjdGlvbnNbaWRdLmRpc3BsYXlJZCArXG4gICAgICAgICAgICAgICcuJ1xuICAgICAgICAgICk7XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICB9XG4gICAgcmV0dXJuIFByb21pc2U7XG4gIH1cblxuICBmdW5jdGlvbiBsb2dFcnJvcihpZCwgZXJyb3IpIHtcbiAgICBjb25zb2xlLndhcm4oJ1Bvc3NpYmxlIFVuaGFuZGxlZCBQcm9taXNlIFJlamVjdGlvbiAoaWQ6ICcgKyBpZCArICcpOicpO1xuICAgIHZhciBlcnJTdHIgPSAoZXJyb3IgJiYgKGVycm9yLnN0YWNrIHx8IGVycm9yKSkgKyAnJztcbiAgICBlcnJTdHIuc3BsaXQoJ1xcbicpLmZvckVhY2goZnVuY3Rpb24obGluZSkge1xuICAgICAgY29uc29sZS53YXJuKCcgICcgKyBsaW5lKTtcbiAgICB9KTtcbiAgfVxuXG4gIGZ1bmN0aW9uIG1hdGNoV2hpdGVsaXN0KGVycm9yLCBsaXN0KSB7XG4gICAgcmV0dXJuIGxpc3Quc29tZShmdW5jdGlvbihjbHMpIHtcbiAgICAgIHJldHVybiBlcnJvciBpbnN0YW5jZW9mIGNscztcbiAgICB9KTtcbiAgfVxuICByZXR1cm4ge1xuICAgIGVuYWJsZSxcbiAgICBkaXNhYmxlLFxuICB9O1xufTtcbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG52YXIgcHJvbWlzZUZhY3RvciA9IHJlcXVpcmUoJy4vY29yZScpO1xudmFyIGVzNiA9IHJlcXVpcmUoJy4vZXM2LWV4dGVuc2lvbnMnKTtcbnZhciByZWplY3Rpb25IYW5kbGUgPSByZXF1aXJlKCcuL3JlamVjdGlvbi10cmFja2luZycpO1xudmFyIGdnID0gbmV3IEZ1bmN0aW9uKCdyZXR1cm4gdGhpcycpKCk7XG4vLyBlc2xpbnQtZGlzYWJsZS1uZXh0LWxpbmUgbm8tbXVsdGktYXNzaWduXG5nZy5nZXRQcm9taXNlID0gbW9kdWxlLmV4cG9ydHMuZ2V0UHJvbWlzZSA9IChvcHQpID0+IHtcbiAgdmFyIHNldFRpbWVvdXQgPSBvcHQuc2V0VGltZW91dDtcbiAgdmFyIG9uVW5oYW5kbGVkID0gb3B0Lm9uVW5oYW5kbGVkO1xuICB2YXIgY2xlYXJUaW1lb3V0ID0gb3B0LmNsZWFyVGltZW91dDtcbiAgdmFyIG5leHRUaWNrID0gb3B0Lm5leHRUaWNrIHx8IChmbiA9PiB7IHNldFRpbWVvdXQoZm4sIDApOyB9KTtcbiAgdmFyIFByb21pc2UgPSBwcm9taXNlRmFjdG9yKHsgbmV4dFRpY2s6IG5leHRUaWNrIH0pO1xuICBQcm9taXNlID0gZXM2KFByb21pc2UpO1xuICBQcm9taXNlID0gcmVqZWN0aW9uSGFuZGxlKFByb21pc2UsIHNldFRpbWVvdXQsIGNsZWFyVGltZW91dCkuZW5hYmxlKHtcbiAgICBhbGxSZWplY3Rpb25zOiB0cnVlLFxuICAgIG9uVW5oYW5kbGVkLFxuICB9KTtcblxuICByZXR1cm4gUHJvbWlzZTtcbn07XG4iLCAiLyoqXG4gKiBDb3B5cmlnaHQgKGMpIDIwMTQtcHJlc2VudCwgRmFjZWJvb2ssIEluYy5cbiAqXG4gKiBUaGlzIHNvdXJjZSBjb2RlIGlzIGxpY2Vuc2VkIHVuZGVyIHRoZSBNSVQgbGljZW5zZSBmb3VuZCBpbiB0aGVcbiAqIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cbiAqL1xuXG52YXIgcnVudGltZSA9IChmdW5jdGlvbiAoZXhwb3J0cykge1xuICBcInVzZSBzdHJpY3RcIjtcblxuICB2YXIgT3AgPSBPYmplY3QucHJvdG90eXBlO1xuICB2YXIgaGFzT3duID0gT3AuaGFzT3duUHJvcGVydHk7XG4gIHZhciB1bmRlZmluZWQ7IC8vIE1vcmUgY29tcHJlc3NpYmxlIHRoYW4gdm9pZCAwLlxuICB2YXIgJFN5bWJvbCA9IHR5cGVvZiBTeW1ib2wgPT09IFwiZnVuY3Rpb25cIiA/IFN5bWJvbCA6IHt9O1xuICB2YXIgaXRlcmF0b3JTeW1ib2wgPSAkU3ltYm9sLml0ZXJhdG9yIHx8IFwiQEBpdGVyYXRvclwiO1xuICB2YXIgYXN5bmNJdGVyYXRvclN5bWJvbCA9ICRTeW1ib2wuYXN5bmNJdGVyYXRvciB8fCBcIkBAYXN5bmNJdGVyYXRvclwiO1xuICB2YXIgdG9TdHJpbmdUYWdTeW1ib2wgPSAkU3ltYm9sLnRvU3RyaW5nVGFnIHx8IFwiQEB0b1N0cmluZ1RhZ1wiO1xuXG4gIGZ1bmN0aW9uIGRlZmluZShvYmosIGtleSwgdmFsdWUpIHtcbiAgICBPYmplY3QuZGVmaW5lUHJvcGVydHkob2JqLCBrZXksIHtcbiAgICAgIHZhbHVlOiB2YWx1ZSxcbiAgICAgIGVudW1lcmFibGU6IHRydWUsXG4gICAgICBjb25maWd1cmFibGU6IHRydWUsXG4gICAgICB3cml0YWJsZTogdHJ1ZVxuICAgIH0pO1xuICAgIHJldHVybiBvYmpba2V5XTtcbiAgfVxuICB0cnkge1xuICAgIC8vIElFIDggaGFzIGEgYnJva2VuIE9iamVjdC5kZWZpbmVQcm9wZXJ0eSB0aGF0IG9ubHkgd29ya3Mgb24gRE9NIG9iamVjdHMuXG4gICAgZGVmaW5lKHt9LCBcIlwiKTtcbiAgfSBjYXRjaCAoZXJyKSB7XG4gICAgZGVmaW5lID0gZnVuY3Rpb24ob2JqLCBrZXksIHZhbHVlKSB7XG4gICAgICByZXR1cm4gb2JqW2tleV0gPSB2YWx1ZTtcbiAgICB9O1xuICB9XG5cbiAgZnVuY3Rpb24gd3JhcChpbm5lckZuLCBvdXRlckZuLCBzZWxmLCB0cnlMb2NzTGlzdCkge1xuICAgIC8vIElmIG91dGVyRm4gcHJvdmlkZWQgYW5kIG91dGVyRm4ucHJvdG90eXBlIGlzIGEgR2VuZXJhdG9yLCB0aGVuIG91dGVyRm4ucHJvdG90eXBlIGluc3RhbmNlb2YgR2VuZXJhdG9yLlxuICAgIHZhciBwcm90b0dlbmVyYXRvciA9IG91dGVyRm4gJiYgb3V0ZXJGbi5wcm90b3R5cGUgaW5zdGFuY2VvZiBHZW5lcmF0b3IgPyBvdXRlckZuIDogR2VuZXJhdG9yO1xuICAgIHZhciBnZW5lcmF0b3IgPSBPYmplY3QuY3JlYXRlKHByb3RvR2VuZXJhdG9yLnByb3RvdHlwZSk7XG4gICAgdmFyIGNvbnRleHQgPSBuZXcgQ29udGV4dCh0cnlMb2NzTGlzdCB8fCBbXSk7XG5cbiAgICAvLyBUaGUgLl9pbnZva2UgbWV0aG9kIHVuaWZpZXMgdGhlIGltcGxlbWVudGF0aW9ucyBvZiB0aGUgLm5leHQsXG4gICAgLy8gLnRocm93LCBhbmQgLnJldHVybiBtZXRob2RzLlxuICAgIGdlbmVyYXRvci5faW52b2tlID0gbWFrZUludm9rZU1ldGhvZChpbm5lckZuLCBzZWxmLCBjb250ZXh0KTtcblxuICAgIHJldHVybiBnZW5lcmF0b3I7XG4gIH1cbiAgZXhwb3J0cy53cmFwID0gd3JhcDtcblxuICAvLyBUcnkvY2F0Y2ggaGVscGVyIHRvIG1pbmltaXplIGRlb3B0aW1pemF0aW9ucy4gUmV0dXJucyBhIGNvbXBsZXRpb25cbiAgLy8gcmVjb3JkIGxpa2UgY29udGV4dC50cnlFbnRyaWVzW2ldLmNvbXBsZXRpb24uIFRoaXMgaW50ZXJmYWNlIGNvdWxkXG4gIC8vIGhhdmUgYmVlbiAoYW5kIHdhcyBwcmV2aW91c2x5KSBkZXNpZ25lZCB0byB0YWtlIGEgY2xvc3VyZSB0byBiZVxuICAvLyBpbnZva2VkIHdpdGhvdXQgYXJndW1lbnRzLCBidXQgaW4gYWxsIHRoZSBjYXNlcyB3ZSBjYXJlIGFib3V0IHdlXG4gIC8vIGFscmVhZHkgaGF2ZSBhbiBleGlzdGluZyBtZXRob2Qgd2Ugd2FudCB0byBjYWxsLCBzbyB0aGVyZSdzIG5vIG5lZWRcbiAgLy8gdG8gY3JlYXRlIGEgbmV3IGZ1bmN0aW9uIG9iamVjdC4gV2UgY2FuIGV2ZW4gZ2V0IGF3YXkgd2l0aCBhc3N1bWluZ1xuICAvLyB0aGUgbWV0aG9kIHRha2VzIGV4YWN0bHkgb25lIGFyZ3VtZW50LCBzaW5jZSB0aGF0IGhhcHBlbnMgdG8gYmUgdHJ1ZVxuICAvLyBpbiBldmVyeSBjYXNlLCBzbyB3ZSBkb24ndCBoYXZlIHRvIHRvdWNoIHRoZSBhcmd1bWVudHMgb2JqZWN0LiBUaGVcbiAgLy8gb25seSBhZGRpdGlvbmFsIGFsbG9jYXRpb24gcmVxdWlyZWQgaXMgdGhlIGNvbXBsZXRpb24gcmVjb3JkLCB3aGljaFxuICAvLyBoYXMgYSBzdGFibGUgc2hhcGUgYW5kIHNvIGhvcGVmdWxseSBzaG91bGQgYmUgY2hlYXAgdG8gYWxsb2NhdGUuXG4gIGZ1bmN0aW9uIHRyeUNhdGNoKGZuLCBvYmosIGFyZykge1xuICAgIHRyeSB7XG4gICAgICByZXR1cm4geyB0eXBlOiBcIm5vcm1hbFwiLCBhcmc6IGZuLmNhbGwob2JqLCBhcmcpIH07XG4gICAgfSBjYXRjaCAoZXJyKSB7XG4gICAgICByZXR1cm4geyB0eXBlOiBcInRocm93XCIsIGFyZzogZXJyIH07XG4gICAgfVxuICB9XG5cbiAgdmFyIEdlblN0YXRlU3VzcGVuZGVkU3RhcnQgPSBcInN1c3BlbmRlZFN0YXJ0XCI7XG4gIHZhciBHZW5TdGF0ZVN1c3BlbmRlZFlpZWxkID0gXCJzdXNwZW5kZWRZaWVsZFwiO1xuICB2YXIgR2VuU3RhdGVFeGVjdXRpbmcgPSBcImV4ZWN1dGluZ1wiO1xuICB2YXIgR2VuU3RhdGVDb21wbGV0ZWQgPSBcImNvbXBsZXRlZFwiO1xuXG4gIC8vIFJldHVybmluZyB0aGlzIG9iamVjdCBmcm9tIHRoZSBpbm5lckZuIGhhcyB0aGUgc2FtZSBlZmZlY3QgYXNcbiAgLy8gYnJlYWtpbmcgb3V0IG9mIHRoZSBkaXNwYXRjaCBzd2l0Y2ggc3RhdGVtZW50LlxuICB2YXIgQ29udGludWVTZW50aW5lbCA9IHt9O1xuXG4gIC8vIER1bW15IGNvbnN0cnVjdG9yIGZ1bmN0aW9ucyB0aGF0IHdlIHVzZSBhcyB0aGUgLmNvbnN0cnVjdG9yIGFuZFxuICAvLyAuY29uc3RydWN0b3IucHJvdG90eXBlIHByb3BlcnRpZXMgZm9yIGZ1bmN0aW9ucyB0aGF0IHJldHVybiBHZW5lcmF0b3JcbiAgLy8gb2JqZWN0cy4gRm9yIGZ1bGwgc3BlYyBjb21wbGlhbmNlLCB5b3UgbWF5IHdpc2ggdG8gY29uZmlndXJlIHlvdXJcbiAgLy8gbWluaWZpZXIgbm90IHRvIG1hbmdsZSB0aGUgbmFtZXMgb2YgdGhlc2UgdHdvIGZ1bmN0aW9ucy5cbiAgZnVuY3Rpb24gR2VuZXJhdG9yKCkge31cbiAgZnVuY3Rpb24gR2VuZXJhdG9yRnVuY3Rpb24oKSB7fVxuICBmdW5jdGlvbiBHZW5lcmF0b3JGdW5jdGlvblByb3RvdHlwZSgpIHt9XG5cbiAgLy8gVGhpcyBpcyBhIHBvbHlmaWxsIGZvciAlSXRlcmF0b3JQcm90b3R5cGUlIGZvciBlbnZpcm9ubWVudHMgdGhhdFxuICAvLyBkb24ndCBuYXRpdmVseSBzdXBwb3J0IGl0LlxuICB2YXIgSXRlcmF0b3JQcm90b3R5cGUgPSB7fTtcbiAgSXRlcmF0b3JQcm90b3R5cGVbaXRlcmF0b3JTeW1ib2xdID0gZnVuY3Rpb24gKCkge1xuICAgIHJldHVybiB0aGlzO1xuICB9O1xuXG4gIHZhciBnZXRQcm90byA9IE9iamVjdC5nZXRQcm90b3R5cGVPZjtcbiAgdmFyIE5hdGl2ZUl0ZXJhdG9yUHJvdG90eXBlID0gZ2V0UHJvdG8gJiYgZ2V0UHJvdG8oZ2V0UHJvdG8odmFsdWVzKFtdKSkpO1xuICBpZiAoTmF0aXZlSXRlcmF0b3JQcm90b3R5cGUgJiZcbiAgICAgIE5hdGl2ZUl0ZXJhdG9yUHJvdG90eXBlICE9PSBPcCAmJlxuICAgICAgaGFzT3duLmNhbGwoTmF0aXZlSXRlcmF0b3JQcm90b3R5cGUsIGl0ZXJhdG9yU3ltYm9sKSkge1xuICAgIC8vIFRoaXMgZW52aXJvbm1lbnQgaGFzIGEgbmF0aXZlICVJdGVyYXRvclByb3RvdHlwZSU7IHVzZSBpdCBpbnN0ZWFkXG4gICAgLy8gb2YgdGhlIHBvbHlmaWxsLlxuICAgIEl0ZXJhdG9yUHJvdG90eXBlID0gTmF0aXZlSXRlcmF0b3JQcm90b3R5cGU7XG4gIH1cblxuICB2YXIgR3AgPSBHZW5lcmF0b3JGdW5jdGlvblByb3RvdHlwZS5wcm90b3R5cGUgPVxuICAgIEdlbmVyYXRvci5wcm90b3R5cGUgPSBPYmplY3QuY3JlYXRlKEl0ZXJhdG9yUHJvdG90eXBlKTtcbiAgR2VuZXJhdG9yRnVuY3Rpb24ucHJvdG90eXBlID0gR3AuY29uc3RydWN0b3IgPSBHZW5lcmF0b3JGdW5jdGlvblByb3RvdHlwZTtcbiAgR2VuZXJhdG9yRnVuY3Rpb25Qcm90b3R5cGUuY29uc3RydWN0b3IgPSBHZW5lcmF0b3JGdW5jdGlvbjtcbiAgR2VuZXJhdG9yRnVuY3Rpb24uZGlzcGxheU5hbWUgPSBkZWZpbmUoXG4gICAgR2VuZXJhdG9yRnVuY3Rpb25Qcm90b3R5cGUsXG4gICAgdG9TdHJpbmdUYWdTeW1ib2wsXG4gICAgXCJHZW5lcmF0b3JGdW5jdGlvblwiXG4gICk7XG5cbiAgLy8gSGVscGVyIGZvciBkZWZpbmluZyB0aGUgLm5leHQsIC50aHJvdywgYW5kIC5yZXR1cm4gbWV0aG9kcyBvZiB0aGVcbiAgLy8gSXRlcmF0b3IgaW50ZXJmYWNlIGluIHRlcm1zIG9mIGEgc2luZ2xlIC5faW52b2tlIG1ldGhvZC5cbiAgZnVuY3Rpb24gZGVmaW5lSXRlcmF0b3JNZXRob2RzKHByb3RvdHlwZSkge1xuICAgIFtcIm5leHRcIiwgXCJ0aHJvd1wiLCBcInJldHVyblwiXS5mb3JFYWNoKGZ1bmN0aW9uKG1ldGhvZCkge1xuICAgICAgZGVmaW5lKHByb3RvdHlwZSwgbWV0aG9kLCBmdW5jdGlvbihhcmcpIHtcbiAgICAgICAgcmV0dXJuIHRoaXMuX2ludm9rZShtZXRob2QsIGFyZyk7XG4gICAgICB9KTtcbiAgICB9KTtcbiAgfVxuXG4gIGV4cG9ydHMuaXNHZW5lcmF0b3JGdW5jdGlvbiA9IGZ1bmN0aW9uKGdlbkZ1bikge1xuICAgIHZhciBjdG9yID0gdHlwZW9mIGdlbkZ1biA9PT0gXCJmdW5jdGlvblwiICYmIGdlbkZ1bi5jb25zdHJ1Y3RvcjtcbiAgICByZXR1cm4gY3RvclxuICAgICAgPyBjdG9yID09PSBHZW5lcmF0b3JGdW5jdGlvbiB8fFxuICAgICAgICAvLyBGb3IgdGhlIG5hdGl2ZSBHZW5lcmF0b3JGdW5jdGlvbiBjb25zdHJ1Y3RvciwgdGhlIGJlc3Qgd2UgY2FuXG4gICAgICAgIC8vIGRvIGlzIHRvIGNoZWNrIGl0cyAubmFtZSBwcm9wZXJ0eS5cbiAgICAgICAgKGN0b3IuZGlzcGxheU5hbWUgfHwgY3Rvci5uYW1lKSA9PT0gXCJHZW5lcmF0b3JGdW5jdGlvblwiXG4gICAgICA6IGZhbHNlO1xuICB9O1xuXG4gIGV4cG9ydHMubWFyayA9IGZ1bmN0aW9uKGdlbkZ1bikge1xuICAgIGlmIChPYmplY3Quc2V0UHJvdG90eXBlT2YpIHtcbiAgICAgIE9iamVjdC5zZXRQcm90b3R5cGVPZihnZW5GdW4sIEdlbmVyYXRvckZ1bmN0aW9uUHJvdG90eXBlKTtcbiAgICB9IGVsc2Uge1xuICAgICAgZ2VuRnVuLl9fcHJvdG9fXyA9IEdlbmVyYXRvckZ1bmN0aW9uUHJvdG90eXBlO1xuICAgICAgZGVmaW5lKGdlbkZ1biwgdG9TdHJpbmdUYWdTeW1ib2wsIFwiR2VuZXJhdG9yRnVuY3Rpb25cIik7XG4gICAgfVxuICAgIGdlbkZ1bi5wcm90b3R5cGUgPSBPYmplY3QuY3JlYXRlKEdwKTtcbiAgICByZXR1cm4gZ2VuRnVuO1xuICB9O1xuXG4gIC8vIFdpdGhpbiB0aGUgYm9keSBvZiBhbnkgYXN5bmMgZnVuY3Rpb24sIGBhd2FpdCB4YCBpcyB0cmFuc2Zvcm1lZCB0b1xuICAvLyBgeWllbGQgcmVnZW5lcmF0b3JSdW50aW1lLmF3cmFwKHgpYCwgc28gdGhhdCB0aGUgcnVudGltZSBjYW4gdGVzdFxuICAvLyBgaGFzT3duLmNhbGwodmFsdWUsIFwiX19hd2FpdFwiKWAgdG8gZGV0ZXJtaW5lIGlmIHRoZSB5aWVsZGVkIHZhbHVlIGlzXG4gIC8vIG1lYW50IHRvIGJlIGF3YWl0ZWQuXG4gIGV4cG9ydHMuYXdyYXAgPSBmdW5jdGlvbihhcmcpIHtcbiAgICByZXR1cm4geyBfX2F3YWl0OiBhcmcgfTtcbiAgfTtcblxuICBmdW5jdGlvbiBBc3luY0l0ZXJhdG9yKGdlbmVyYXRvciwgUHJvbWlzZUltcGwpIHtcbiAgICBmdW5jdGlvbiBpbnZva2UobWV0aG9kLCBhcmcsIHJlc29sdmUsIHJlamVjdCkge1xuICAgICAgdmFyIHJlY29yZCA9IHRyeUNhdGNoKGdlbmVyYXRvclttZXRob2RdLCBnZW5lcmF0b3IsIGFyZyk7XG4gICAgICBpZiAocmVjb3JkLnR5cGUgPT09IFwidGhyb3dcIikge1xuICAgICAgICByZWplY3QocmVjb3JkLmFyZyk7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICB2YXIgcmVzdWx0ID0gcmVjb3JkLmFyZztcbiAgICAgICAgdmFyIHZhbHVlID0gcmVzdWx0LnZhbHVlO1xuICAgICAgICBpZiAodmFsdWUgJiZcbiAgICAgICAgICAgIHR5cGVvZiB2YWx1ZSA9PT0gXCJvYmplY3RcIiAmJlxuICAgICAgICAgICAgaGFzT3duLmNhbGwodmFsdWUsIFwiX19hd2FpdFwiKSkge1xuICAgICAgICAgIHJldHVybiBQcm9taXNlSW1wbC5yZXNvbHZlKHZhbHVlLl9fYXdhaXQpLnRoZW4oZnVuY3Rpb24odmFsdWUpIHtcbiAgICAgICAgICAgIGludm9rZShcIm5leHRcIiwgdmFsdWUsIHJlc29sdmUsIHJlamVjdCk7XG4gICAgICAgICAgfSwgZnVuY3Rpb24oZXJyKSB7XG4gICAgICAgICAgICBpbnZva2UoXCJ0aHJvd1wiLCBlcnIsIHJlc29sdmUsIHJlamVjdCk7XG4gICAgICAgICAgfSk7XG4gICAgICAgIH1cblxuICAgICAgICByZXR1cm4gUHJvbWlzZUltcGwucmVzb2x2ZSh2YWx1ZSkudGhlbihmdW5jdGlvbih1bndyYXBwZWQpIHtcbiAgICAgICAgICAvLyBXaGVuIGEgeWllbGRlZCBQcm9taXNlIGlzIHJlc29sdmVkLCBpdHMgZmluYWwgdmFsdWUgYmVjb21lc1xuICAgICAgICAgIC8vIHRoZSAudmFsdWUgb2YgdGhlIFByb21pc2U8e3ZhbHVlLGRvbmV9PiByZXN1bHQgZm9yIHRoZVxuICAgICAgICAgIC8vIGN1cnJlbnQgaXRlcmF0aW9uLlxuICAgICAgICAgIHJlc3VsdC52YWx1ZSA9IHVud3JhcHBlZDtcbiAgICAgICAgICByZXNvbHZlKHJlc3VsdCk7XG4gICAgICAgIH0sIGZ1bmN0aW9uKGVycm9yKSB7XG4gICAgICAgICAgLy8gSWYgYSByZWplY3RlZCBQcm9taXNlIHdhcyB5aWVsZGVkLCB0aHJvdyB0aGUgcmVqZWN0aW9uIGJhY2tcbiAgICAgICAgICAvLyBpbnRvIHRoZSBhc3luYyBnZW5lcmF0b3IgZnVuY3Rpb24gc28gaXQgY2FuIGJlIGhhbmRsZWQgdGhlcmUuXG4gICAgICAgICAgcmV0dXJuIGludm9rZShcInRocm93XCIsIGVycm9yLCByZXNvbHZlLCByZWplY3QpO1xuICAgICAgICB9KTtcbiAgICAgIH1cbiAgICB9XG5cbiAgICB2YXIgcHJldmlvdXNQcm9taXNlO1xuXG4gICAgZnVuY3Rpb24gZW5xdWV1ZShtZXRob2QsIGFyZykge1xuICAgICAgZnVuY3Rpb24gY2FsbEludm9rZVdpdGhNZXRob2RBbmRBcmcoKSB7XG4gICAgICAgIHJldHVybiBuZXcgUHJvbWlzZUltcGwoZnVuY3Rpb24ocmVzb2x2ZSwgcmVqZWN0KSB7XG4gICAgICAgICAgaW52b2tlKG1ldGhvZCwgYXJnLCByZXNvbHZlLCByZWplY3QpO1xuICAgICAgICB9KTtcbiAgICAgIH1cblxuICAgICAgcmV0dXJuIHByZXZpb3VzUHJvbWlzZSA9XG4gICAgICAgIC8vIElmIGVucXVldWUgaGFzIGJlZW4gY2FsbGVkIGJlZm9yZSwgdGhlbiB3ZSB3YW50IHRvIHdhaXQgdW50aWxcbiAgICAgICAgLy8gYWxsIHByZXZpb3VzIFByb21pc2VzIGhhdmUgYmVlbiByZXNvbHZlZCBiZWZvcmUgY2FsbGluZyBpbnZva2UsXG4gICAgICAgIC8vIHNvIHRoYXQgcmVzdWx0cyBhcmUgYWx3YXlzIGRlbGl2ZXJlZCBpbiB0aGUgY29ycmVjdCBvcmRlci4gSWZcbiAgICAgICAgLy8gZW5xdWV1ZSBoYXMgbm90IGJlZW4gY2FsbGVkIGJlZm9yZSwgdGhlbiBpdCBpcyBpbXBvcnRhbnQgdG9cbiAgICAgICAgLy8gY2FsbCBpbnZva2UgaW1tZWRpYXRlbHksIHdpdGhvdXQgd2FpdGluZyBvbiBhIGNhbGxiYWNrIHRvIGZpcmUsXG4gICAgICAgIC8vIHNvIHRoYXQgdGhlIGFzeW5jIGdlbmVyYXRvciBmdW5jdGlvbiBoYXMgdGhlIG9wcG9ydHVuaXR5IHRvIGRvXG4gICAgICAgIC8vIGFueSBuZWNlc3Nhcnkgc2V0dXAgaW4gYSBwcmVkaWN0YWJsZSB3YXkuIFRoaXMgcHJlZGljdGFiaWxpdHlcbiAgICAgICAgLy8gaXMgd2h5IHRoZSBQcm9taXNlIGNvbnN0cnVjdG9yIHN5bmNocm9ub3VzbHkgaW52b2tlcyBpdHNcbiAgICAgICAgLy8gZXhlY3V0b3IgY2FsbGJhY2ssIGFuZCB3aHkgYXN5bmMgZnVuY3Rpb25zIHN5bmNocm9ub3VzbHlcbiAgICAgICAgLy8gZXhlY3V0ZSBjb2RlIGJlZm9yZSB0aGUgZmlyc3QgYXdhaXQuIFNpbmNlIHdlIGltcGxlbWVudCBzaW1wbGVcbiAgICAgICAgLy8gYXN5bmMgZnVuY3Rpb25zIGluIHRlcm1zIG9mIGFzeW5jIGdlbmVyYXRvcnMsIGl0IGlzIGVzcGVjaWFsbHlcbiAgICAgICAgLy8gaW1wb3J0YW50IHRvIGdldCB0aGlzIHJpZ2h0LCBldmVuIHRob3VnaCBpdCByZXF1aXJlcyBjYXJlLlxuICAgICAgICBwcmV2aW91c1Byb21pc2UgPyBwcmV2aW91c1Byb21pc2UudGhlbihcbiAgICAgICAgICBjYWxsSW52b2tlV2l0aE1ldGhvZEFuZEFyZyxcbiAgICAgICAgICAvLyBBdm9pZCBwcm9wYWdhdGluZyBmYWlsdXJlcyB0byBQcm9taXNlcyByZXR1cm5lZCBieSBsYXRlclxuICAgICAgICAgIC8vIGludm9jYXRpb25zIG9mIHRoZSBpdGVyYXRvci5cbiAgICAgICAgICBjYWxsSW52b2tlV2l0aE1ldGhvZEFuZEFyZ1xuICAgICAgICApIDogY2FsbEludm9rZVdpdGhNZXRob2RBbmRBcmcoKTtcbiAgICB9XG5cbiAgICAvLyBEZWZpbmUgdGhlIHVuaWZpZWQgaGVscGVyIG1ldGhvZCB0aGF0IGlzIHVzZWQgdG8gaW1wbGVtZW50IC5uZXh0LFxuICAgIC8vIC50aHJvdywgYW5kIC5yZXR1cm4gKHNlZSBkZWZpbmVJdGVyYXRvck1ldGhvZHMpLlxuICAgIHRoaXMuX2ludm9rZSA9IGVucXVldWU7XG4gIH1cblxuICBkZWZpbmVJdGVyYXRvck1ldGhvZHMoQXN5bmNJdGVyYXRvci5wcm90b3R5cGUpO1xuICBBc3luY0l0ZXJhdG9yLnByb3RvdHlwZVthc3luY0l0ZXJhdG9yU3ltYm9sXSA9IGZ1bmN0aW9uICgpIHtcbiAgICByZXR1cm4gdGhpcztcbiAgfTtcbiAgZXhwb3J0cy5Bc3luY0l0ZXJhdG9yID0gQXN5bmNJdGVyYXRvcjtcblxuICAvLyBOb3RlIHRoYXQgc2ltcGxlIGFzeW5jIGZ1bmN0aW9ucyBhcmUgaW1wbGVtZW50ZWQgb24gdG9wIG9mXG4gIC8vIEFzeW5jSXRlcmF0b3Igb2JqZWN0czsgdGhleSBqdXN0IHJldHVybiBhIFByb21pc2UgZm9yIHRoZSB2YWx1ZSBvZlxuICAvLyB0aGUgZmluYWwgcmVzdWx0IHByb2R1Y2VkIGJ5IHRoZSBpdGVyYXRvci5cbiAgZXhwb3J0cy5hc3luYyA9IGZ1bmN0aW9uKGlubmVyRm4sIG91dGVyRm4sIHNlbGYsIHRyeUxvY3NMaXN0LCBQcm9taXNlSW1wbCkge1xuICAgIGlmIChQcm9taXNlSW1wbCA9PT0gdm9pZCAwKSBQcm9taXNlSW1wbCA9IFByb21pc2U7XG5cbiAgICB2YXIgaXRlciA9IG5ldyBBc3luY0l0ZXJhdG9yKFxuICAgICAgd3JhcChpbm5lckZuLCBvdXRlckZuLCBzZWxmLCB0cnlMb2NzTGlzdCksXG4gICAgICBQcm9taXNlSW1wbFxuICAgICk7XG5cbiAgICByZXR1cm4gZXhwb3J0cy5pc0dlbmVyYXRvckZ1bmN0aW9uKG91dGVyRm4pXG4gICAgICA/IGl0ZXIgLy8gSWYgb3V0ZXJGbiBpcyBhIGdlbmVyYXRvciwgcmV0dXJuIHRoZSBmdWxsIGl0ZXJhdG9yLlxuICAgICAgOiBpdGVyLm5leHQoKS50aGVuKGZ1bmN0aW9uKHJlc3VsdCkge1xuICAgICAgICAgIHJldHVybiByZXN1bHQuZG9uZSA/IHJlc3VsdC52YWx1ZSA6IGl0ZXIubmV4dCgpO1xuICAgICAgICB9KTtcbiAgfTtcblxuICBmdW5jdGlvbiBtYWtlSW52b2tlTWV0aG9kKGlubmVyRm4sIHNlbGYsIGNvbnRleHQpIHtcbiAgICB2YXIgc3RhdGUgPSBHZW5TdGF0ZVN1c3BlbmRlZFN0YXJ0O1xuXG4gICAgcmV0dXJuIGZ1bmN0aW9uIGludm9rZShtZXRob2QsIGFyZykge1xuICAgICAgaWYgKHN0YXRlID09PSBHZW5TdGF0ZUV4ZWN1dGluZykge1xuICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJHZW5lcmF0b3IgaXMgYWxyZWFkeSBydW5uaW5nXCIpO1xuICAgICAgfVxuXG4gICAgICBpZiAoc3RhdGUgPT09IEdlblN0YXRlQ29tcGxldGVkKSB7XG4gICAgICAgIGlmIChtZXRob2QgPT09IFwidGhyb3dcIikge1xuICAgICAgICAgIHRocm93IGFyZztcbiAgICAgICAgfVxuXG4gICAgICAgIC8vIEJlIGZvcmdpdmluZywgcGVyIDI1LjMuMy4zLjMgb2YgdGhlIHNwZWM6XG4gICAgICAgIC8vIGh0dHBzOi8vcGVvcGxlLm1vemlsbGEub3JnL35qb3JlbmRvcmZmL2VzNi1kcmFmdC5odG1sI3NlYy1nZW5lcmF0b3JyZXN1bWVcbiAgICAgICAgcmV0dXJuIGRvbmVSZXN1bHQoKTtcbiAgICAgIH1cblxuICAgICAgY29udGV4dC5tZXRob2QgPSBtZXRob2Q7XG4gICAgICBjb250ZXh0LmFyZyA9IGFyZztcblxuICAgICAgd2hpbGUgKHRydWUpIHtcbiAgICAgICAgdmFyIGRlbGVnYXRlID0gY29udGV4dC5kZWxlZ2F0ZTtcbiAgICAgICAgaWYgKGRlbGVnYXRlKSB7XG4gICAgICAgICAgdmFyIGRlbGVnYXRlUmVzdWx0ID0gbWF5YmVJbnZva2VEZWxlZ2F0ZShkZWxlZ2F0ZSwgY29udGV4dCk7XG4gICAgICAgICAgaWYgKGRlbGVnYXRlUmVzdWx0KSB7XG4gICAgICAgICAgICBpZiAoZGVsZWdhdGVSZXN1bHQgPT09IENvbnRpbnVlU2VudGluZWwpIGNvbnRpbnVlO1xuICAgICAgICAgICAgcmV0dXJuIGRlbGVnYXRlUmVzdWx0O1xuICAgICAgICAgIH1cbiAgICAgICAgfVxuXG4gICAgICAgIGlmIChjb250ZXh0Lm1ldGhvZCA9PT0gXCJuZXh0XCIpIHtcbiAgICAgICAgICAvLyBTZXR0aW5nIGNvbnRleHQuX3NlbnQgZm9yIGxlZ2FjeSBzdXBwb3J0IG9mIEJhYmVsJ3NcbiAgICAgICAgICAvLyBmdW5jdGlvbi5zZW50IGltcGxlbWVudGF0aW9uLlxuICAgICAgICAgIGNvbnRleHQuc2VudCA9IGNvbnRleHQuX3NlbnQgPSBjb250ZXh0LmFyZztcblxuICAgICAgICB9IGVsc2UgaWYgKGNvbnRleHQubWV0aG9kID09PSBcInRocm93XCIpIHtcbiAgICAgICAgICBpZiAoc3RhdGUgPT09IEdlblN0YXRlU3VzcGVuZGVkU3RhcnQpIHtcbiAgICAgICAgICAgIHN0YXRlID0gR2VuU3RhdGVDb21wbGV0ZWQ7XG4gICAgICAgICAgICB0aHJvdyBjb250ZXh0LmFyZztcbiAgICAgICAgICB9XG5cbiAgICAgICAgICBjb250ZXh0LmRpc3BhdGNoRXhjZXB0aW9uKGNvbnRleHQuYXJnKTtcblxuICAgICAgICB9IGVsc2UgaWYgKGNvbnRleHQubWV0aG9kID09PSBcInJldHVyblwiKSB7XG4gICAgICAgICAgY29udGV4dC5hYnJ1cHQoXCJyZXR1cm5cIiwgY29udGV4dC5hcmcpO1xuICAgICAgICB9XG5cbiAgICAgICAgc3RhdGUgPSBHZW5TdGF0ZUV4ZWN1dGluZztcblxuICAgICAgICB2YXIgcmVjb3JkID0gdHJ5Q2F0Y2goaW5uZXJGbiwgc2VsZiwgY29udGV4dCk7XG4gICAgICAgIGlmIChyZWNvcmQudHlwZSA9PT0gXCJub3JtYWxcIikge1xuICAgICAgICAgIC8vIElmIGFuIGV4Y2VwdGlvbiBpcyB0aHJvd24gZnJvbSBpbm5lckZuLCB3ZSBsZWF2ZSBzdGF0ZSA9PT1cbiAgICAgICAgICAvLyBHZW5TdGF0ZUV4ZWN1dGluZyBhbmQgbG9vcCBiYWNrIGZvciBhbm90aGVyIGludm9jYXRpb24uXG4gICAgICAgICAgc3RhdGUgPSBjb250ZXh0LmRvbmVcbiAgICAgICAgICAgID8gR2VuU3RhdGVDb21wbGV0ZWRcbiAgICAgICAgICAgIDogR2VuU3RhdGVTdXNwZW5kZWRZaWVsZDtcblxuICAgICAgICAgIGlmIChyZWNvcmQuYXJnID09PSBDb250aW51ZVNlbnRpbmVsKSB7XG4gICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICB9XG5cbiAgICAgICAgICByZXR1cm4ge1xuICAgICAgICAgICAgdmFsdWU6IHJlY29yZC5hcmcsXG4gICAgICAgICAgICBkb25lOiBjb250ZXh0LmRvbmVcbiAgICAgICAgICB9O1xuXG4gICAgICAgIH0gZWxzZSBpZiAocmVjb3JkLnR5cGUgPT09IFwidGhyb3dcIikge1xuICAgICAgICAgIHN0YXRlID0gR2VuU3RhdGVDb21wbGV0ZWQ7XG4gICAgICAgICAgLy8gRGlzcGF0Y2ggdGhlIGV4Y2VwdGlvbiBieSBsb29waW5nIGJhY2sgYXJvdW5kIHRvIHRoZVxuICAgICAgICAgIC8vIGNvbnRleHQuZGlzcGF0Y2hFeGNlcHRpb24oY29udGV4dC5hcmcpIGNhbGwgYWJvdmUuXG4gICAgICAgICAgY29udGV4dC5tZXRob2QgPSBcInRocm93XCI7XG4gICAgICAgICAgY29udGV4dC5hcmcgPSByZWNvcmQuYXJnO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgfTtcbiAgfVxuXG4gIC8vIENhbGwgZGVsZWdhdGUuaXRlcmF0b3JbY29udGV4dC5tZXRob2RdKGNvbnRleHQuYXJnKSBhbmQgaGFuZGxlIHRoZVxuICAvLyByZXN1bHQsIGVpdGhlciBieSByZXR1cm5pbmcgYSB7IHZhbHVlLCBkb25lIH0gcmVzdWx0IGZyb20gdGhlXG4gIC8vIGRlbGVnYXRlIGl0ZXJhdG9yLCBvciBieSBtb2RpZnlpbmcgY29udGV4dC5tZXRob2QgYW5kIGNvbnRleHQuYXJnLFxuICAvLyBzZXR0aW5nIGNvbnRleHQuZGVsZWdhdGUgdG8gbnVsbCwgYW5kIHJldHVybmluZyB0aGUgQ29udGludWVTZW50aW5lbC5cbiAgZnVuY3Rpb24gbWF5YmVJbnZva2VEZWxlZ2F0ZShkZWxlZ2F0ZSwgY29udGV4dCkge1xuICAgIHZhciBtZXRob2QgPSBkZWxlZ2F0ZS5pdGVyYXRvcltjb250ZXh0Lm1ldGhvZF07XG4gICAgaWYgKG1ldGhvZCA9PT0gdW5kZWZpbmVkKSB7XG4gICAgICAvLyBBIC50aHJvdyBvciAucmV0dXJuIHdoZW4gdGhlIGRlbGVnYXRlIGl0ZXJhdG9yIGhhcyBubyAudGhyb3dcbiAgICAgIC8vIG1ldGhvZCBhbHdheXMgdGVybWluYXRlcyB0aGUgeWllbGQqIGxvb3AuXG4gICAgICBjb250ZXh0LmRlbGVnYXRlID0gbnVsbDtcblxuICAgICAgaWYgKGNvbnRleHQubWV0aG9kID09PSBcInRocm93XCIpIHtcbiAgICAgICAgLy8gTm90ZTogW1wicmV0dXJuXCJdIG11c3QgYmUgdXNlZCBmb3IgRVMzIHBhcnNpbmcgY29tcGF0aWJpbGl0eS5cbiAgICAgICAgaWYgKGRlbGVnYXRlLml0ZXJhdG9yW1wicmV0dXJuXCJdKSB7XG4gICAgICAgICAgLy8gSWYgdGhlIGRlbGVnYXRlIGl0ZXJhdG9yIGhhcyBhIHJldHVybiBtZXRob2QsIGdpdmUgaXQgYVxuICAgICAgICAgIC8vIGNoYW5jZSB0byBjbGVhbiB1cC5cbiAgICAgICAgICBjb250ZXh0Lm1ldGhvZCA9IFwicmV0dXJuXCI7XG4gICAgICAgICAgY29udGV4dC5hcmcgPSB1bmRlZmluZWQ7XG4gICAgICAgICAgbWF5YmVJbnZva2VEZWxlZ2F0ZShkZWxlZ2F0ZSwgY29udGV4dCk7XG5cbiAgICAgICAgICBpZiAoY29udGV4dC5tZXRob2QgPT09IFwidGhyb3dcIikge1xuICAgICAgICAgICAgLy8gSWYgbWF5YmVJbnZva2VEZWxlZ2F0ZShjb250ZXh0KSBjaGFuZ2VkIGNvbnRleHQubWV0aG9kIGZyb21cbiAgICAgICAgICAgIC8vIFwicmV0dXJuXCIgdG8gXCJ0aHJvd1wiLCBsZXQgdGhhdCBvdmVycmlkZSB0aGUgVHlwZUVycm9yIGJlbG93LlxuICAgICAgICAgICAgcmV0dXJuIENvbnRpbnVlU2VudGluZWw7XG4gICAgICAgICAgfVxuICAgICAgICB9XG5cbiAgICAgICAgY29udGV4dC5tZXRob2QgPSBcInRocm93XCI7XG4gICAgICAgIGNvbnRleHQuYXJnID0gbmV3IFR5cGVFcnJvcihcbiAgICAgICAgICBcIlRoZSBpdGVyYXRvciBkb2VzIG5vdCBwcm92aWRlIGEgJ3Rocm93JyBtZXRob2RcIik7XG4gICAgICB9XG5cbiAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgIH1cblxuICAgIHZhciByZWNvcmQgPSB0cnlDYXRjaChtZXRob2QsIGRlbGVnYXRlLml0ZXJhdG9yLCBjb250ZXh0LmFyZyk7XG5cbiAgICBpZiAocmVjb3JkLnR5cGUgPT09IFwidGhyb3dcIikge1xuICAgICAgY29udGV4dC5tZXRob2QgPSBcInRocm93XCI7XG4gICAgICBjb250ZXh0LmFyZyA9IHJlY29yZC5hcmc7XG4gICAgICBjb250ZXh0LmRlbGVnYXRlID0gbnVsbDtcbiAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgIH1cblxuICAgIHZhciBpbmZvID0gcmVjb3JkLmFyZztcblxuICAgIGlmICghIGluZm8pIHtcbiAgICAgIGNvbnRleHQubWV0aG9kID0gXCJ0aHJvd1wiO1xuICAgICAgY29udGV4dC5hcmcgPSBuZXcgVHlwZUVycm9yKFwiaXRlcmF0b3IgcmVzdWx0IGlzIG5vdCBhbiBvYmplY3RcIik7XG4gICAgICBjb250ZXh0LmRlbGVnYXRlID0gbnVsbDtcbiAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgIH1cblxuICAgIGlmIChpbmZvLmRvbmUpIHtcbiAgICAgIC8vIEFzc2lnbiB0aGUgcmVzdWx0IG9mIHRoZSBmaW5pc2hlZCBkZWxlZ2F0ZSB0byB0aGUgdGVtcG9yYXJ5XG4gICAgICAvLyB2YXJpYWJsZSBzcGVjaWZpZWQgYnkgZGVsZWdhdGUucmVzdWx0TmFtZSAoc2VlIGRlbGVnYXRlWWllbGQpLlxuICAgICAgY29udGV4dFtkZWxlZ2F0ZS5yZXN1bHROYW1lXSA9IGluZm8udmFsdWU7XG5cbiAgICAgIC8vIFJlc3VtZSBleGVjdXRpb24gYXQgdGhlIGRlc2lyZWQgbG9jYXRpb24gKHNlZSBkZWxlZ2F0ZVlpZWxkKS5cbiAgICAgIGNvbnRleHQubmV4dCA9IGRlbGVnYXRlLm5leHRMb2M7XG5cbiAgICAgIC8vIElmIGNvbnRleHQubWV0aG9kIHdhcyBcInRocm93XCIgYnV0IHRoZSBkZWxlZ2F0ZSBoYW5kbGVkIHRoZVxuICAgICAgLy8gZXhjZXB0aW9uLCBsZXQgdGhlIG91dGVyIGdlbmVyYXRvciBwcm9jZWVkIG5vcm1hbGx5LiBJZlxuICAgICAgLy8gY29udGV4dC5tZXRob2Qgd2FzIFwibmV4dFwiLCBmb3JnZXQgY29udGV4dC5hcmcgc2luY2UgaXQgaGFzIGJlZW5cbiAgICAgIC8vIFwiY29uc3VtZWRcIiBieSB0aGUgZGVsZWdhdGUgaXRlcmF0b3IuIElmIGNvbnRleHQubWV0aG9kIHdhc1xuICAgICAgLy8gXCJyZXR1cm5cIiwgYWxsb3cgdGhlIG9yaWdpbmFsIC5yZXR1cm4gY2FsbCB0byBjb250aW51ZSBpbiB0aGVcbiAgICAgIC8vIG91dGVyIGdlbmVyYXRvci5cbiAgICAgIGlmIChjb250ZXh0Lm1ldGhvZCAhPT0gXCJyZXR1cm5cIikge1xuICAgICAgICBjb250ZXh0Lm1ldGhvZCA9IFwibmV4dFwiO1xuICAgICAgICBjb250ZXh0LmFyZyA9IHVuZGVmaW5lZDtcbiAgICAgIH1cblxuICAgIH0gZWxzZSB7XG4gICAgICAvLyBSZS15aWVsZCB0aGUgcmVzdWx0IHJldHVybmVkIGJ5IHRoZSBkZWxlZ2F0ZSBtZXRob2QuXG4gICAgICByZXR1cm4gaW5mbztcbiAgICB9XG5cbiAgICAvLyBUaGUgZGVsZWdhdGUgaXRlcmF0b3IgaXMgZmluaXNoZWQsIHNvIGZvcmdldCBpdCBhbmQgY29udGludWUgd2l0aFxuICAgIC8vIHRoZSBvdXRlciBnZW5lcmF0b3IuXG4gICAgY29udGV4dC5kZWxlZ2F0ZSA9IG51bGw7XG4gICAgcmV0dXJuIENvbnRpbnVlU2VudGluZWw7XG4gIH1cblxuICAvLyBEZWZpbmUgR2VuZXJhdG9yLnByb3RvdHlwZS57bmV4dCx0aHJvdyxyZXR1cm59IGluIHRlcm1zIG9mIHRoZVxuICAvLyB1bmlmaWVkIC5faW52b2tlIGhlbHBlciBtZXRob2QuXG4gIGRlZmluZUl0ZXJhdG9yTWV0aG9kcyhHcCk7XG5cbiAgZGVmaW5lKEdwLCB0b1N0cmluZ1RhZ1N5bWJvbCwgXCJHZW5lcmF0b3JcIik7XG5cbiAgLy8gQSBHZW5lcmF0b3Igc2hvdWxkIGFsd2F5cyByZXR1cm4gaXRzZWxmIGFzIHRoZSBpdGVyYXRvciBvYmplY3Qgd2hlbiB0aGVcbiAgLy8gQEBpdGVyYXRvciBmdW5jdGlvbiBpcyBjYWxsZWQgb24gaXQuIFNvbWUgYnJvd3NlcnMnIGltcGxlbWVudGF0aW9ucyBvZiB0aGVcbiAgLy8gaXRlcmF0b3IgcHJvdG90eXBlIGNoYWluIGluY29ycmVjdGx5IGltcGxlbWVudCB0aGlzLCBjYXVzaW5nIHRoZSBHZW5lcmF0b3JcbiAgLy8gb2JqZWN0IHRvIG5vdCBiZSByZXR1cm5lZCBmcm9tIHRoaXMgY2FsbC4gVGhpcyBlbnN1cmVzIHRoYXQgZG9lc24ndCBoYXBwZW4uXG4gIC8vIFNlZSBodHRwczovL2dpdGh1Yi5jb20vZmFjZWJvb2svcmVnZW5lcmF0b3IvaXNzdWVzLzI3NCBmb3IgbW9yZSBkZXRhaWxzLlxuICBHcFtpdGVyYXRvclN5bWJvbF0gPSBmdW5jdGlvbigpIHtcbiAgICByZXR1cm4gdGhpcztcbiAgfTtcblxuICBHcC50b1N0cmluZyA9IGZ1bmN0aW9uKCkge1xuICAgIHJldHVybiBcIltvYmplY3QgR2VuZXJhdG9yXVwiO1xuICB9O1xuXG4gIGZ1bmN0aW9uIHB1c2hUcnlFbnRyeShsb2NzKSB7XG4gICAgdmFyIGVudHJ5ID0geyB0cnlMb2M6IGxvY3NbMF0gfTtcblxuICAgIGlmICgxIGluIGxvY3MpIHtcbiAgICAgIGVudHJ5LmNhdGNoTG9jID0gbG9jc1sxXTtcbiAgICB9XG5cbiAgICBpZiAoMiBpbiBsb2NzKSB7XG4gICAgICBlbnRyeS5maW5hbGx5TG9jID0gbG9jc1syXTtcbiAgICAgIGVudHJ5LmFmdGVyTG9jID0gbG9jc1szXTtcbiAgICB9XG5cbiAgICB0aGlzLnRyeUVudHJpZXMucHVzaChlbnRyeSk7XG4gIH1cblxuICBmdW5jdGlvbiByZXNldFRyeUVudHJ5KGVudHJ5KSB7XG4gICAgdmFyIHJlY29yZCA9IGVudHJ5LmNvbXBsZXRpb24gfHwge307XG4gICAgcmVjb3JkLnR5cGUgPSBcIm5vcm1hbFwiO1xuICAgIGRlbGV0ZSByZWNvcmQuYXJnO1xuICAgIGVudHJ5LmNvbXBsZXRpb24gPSByZWNvcmQ7XG4gIH1cblxuICBmdW5jdGlvbiBDb250ZXh0KHRyeUxvY3NMaXN0KSB7XG4gICAgLy8gVGhlIHJvb3QgZW50cnkgb2JqZWN0IChlZmZlY3RpdmVseSBhIHRyeSBzdGF0ZW1lbnQgd2l0aG91dCBhIGNhdGNoXG4gICAgLy8gb3IgYSBmaW5hbGx5IGJsb2NrKSBnaXZlcyB1cyBhIHBsYWNlIHRvIHN0b3JlIHZhbHVlcyB0aHJvd24gZnJvbVxuICAgIC8vIGxvY2F0aW9ucyB3aGVyZSB0aGVyZSBpcyBubyBlbmNsb3NpbmcgdHJ5IHN0YXRlbWVudC5cbiAgICB0aGlzLnRyeUVudHJpZXMgPSBbeyB0cnlMb2M6IFwicm9vdFwiIH1dO1xuICAgIHRyeUxvY3NMaXN0LmZvckVhY2gocHVzaFRyeUVudHJ5LCB0aGlzKTtcbiAgICB0aGlzLnJlc2V0KHRydWUpO1xuICB9XG5cbiAgZXhwb3J0cy5rZXlzID0gZnVuY3Rpb24ob2JqZWN0KSB7XG4gICAgdmFyIGtleXMgPSBbXTtcbiAgICBmb3IgKHZhciBrZXkgaW4gb2JqZWN0KSB7XG4gICAgICBrZXlzLnB1c2goa2V5KTtcbiAgICB9XG4gICAga2V5cy5yZXZlcnNlKCk7XG5cbiAgICAvLyBSYXRoZXIgdGhhbiByZXR1cm5pbmcgYW4gb2JqZWN0IHdpdGggYSBuZXh0IG1ldGhvZCwgd2Uga2VlcFxuICAgIC8vIHRoaW5ncyBzaW1wbGUgYW5kIHJldHVybiB0aGUgbmV4dCBmdW5jdGlvbiBpdHNlbGYuXG4gICAgcmV0dXJuIGZ1bmN0aW9uIG5leHQoKSB7XG4gICAgICB3aGlsZSAoa2V5cy5sZW5ndGgpIHtcbiAgICAgICAgdmFyIGtleSA9IGtleXMucG9wKCk7XG4gICAgICAgIGlmIChrZXkgaW4gb2JqZWN0KSB7XG4gICAgICAgICAgbmV4dC52YWx1ZSA9IGtleTtcbiAgICAgICAgICBuZXh0LmRvbmUgPSBmYWxzZTtcbiAgICAgICAgICByZXR1cm4gbmV4dDtcbiAgICAgICAgfVxuICAgICAgfVxuXG4gICAgICAvLyBUbyBhdm9pZCBjcmVhdGluZyBhbiBhZGRpdGlvbmFsIG9iamVjdCwgd2UganVzdCBoYW5nIHRoZSAudmFsdWVcbiAgICAgIC8vIGFuZCAuZG9uZSBwcm9wZXJ0aWVzIG9mZiB0aGUgbmV4dCBmdW5jdGlvbiBvYmplY3QgaXRzZWxmLiBUaGlzXG4gICAgICAvLyBhbHNvIGVuc3VyZXMgdGhhdCB0aGUgbWluaWZpZXIgd2lsbCBub3QgYW5vbnltaXplIHRoZSBmdW5jdGlvbi5cbiAgICAgIG5leHQuZG9uZSA9IHRydWU7XG4gICAgICByZXR1cm4gbmV4dDtcbiAgICB9O1xuICB9O1xuXG4gIGZ1bmN0aW9uIHZhbHVlcyhpdGVyYWJsZSkge1xuICAgIGlmIChpdGVyYWJsZSkge1xuICAgICAgdmFyIGl0ZXJhdG9yTWV0aG9kID0gaXRlcmFibGVbaXRlcmF0b3JTeW1ib2xdO1xuICAgICAgaWYgKGl0ZXJhdG9yTWV0aG9kKSB7XG4gICAgICAgIHJldHVybiBpdGVyYXRvck1ldGhvZC5jYWxsKGl0ZXJhYmxlKTtcbiAgICAgIH1cblxuICAgICAgaWYgKHR5cGVvZiBpdGVyYWJsZS5uZXh0ID09PSBcImZ1bmN0aW9uXCIpIHtcbiAgICAgICAgcmV0dXJuIGl0ZXJhYmxlO1xuICAgICAgfVxuXG4gICAgICBpZiAoIWlzTmFOKGl0ZXJhYmxlLmxlbmd0aCkpIHtcbiAgICAgICAgdmFyIGkgPSAtMSwgbmV4dCA9IGZ1bmN0aW9uIG5leHQoKSB7XG4gICAgICAgICAgd2hpbGUgKCsraSA8IGl0ZXJhYmxlLmxlbmd0aCkge1xuICAgICAgICAgICAgaWYgKGhhc093bi5jYWxsKGl0ZXJhYmxlLCBpKSkge1xuICAgICAgICAgICAgICBuZXh0LnZhbHVlID0gaXRlcmFibGVbaV07XG4gICAgICAgICAgICAgIG5leHQuZG9uZSA9IGZhbHNlO1xuICAgICAgICAgICAgICByZXR1cm4gbmV4dDtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICB9XG5cbiAgICAgICAgICBuZXh0LnZhbHVlID0gdW5kZWZpbmVkO1xuICAgICAgICAgIG5leHQuZG9uZSA9IHRydWU7XG5cbiAgICAgICAgICByZXR1cm4gbmV4dDtcbiAgICAgICAgfTtcblxuICAgICAgICByZXR1cm4gbmV4dC5uZXh0ID0gbmV4dDtcbiAgICAgIH1cbiAgICB9XG5cbiAgICAvLyBSZXR1cm4gYW4gaXRlcmF0b3Igd2l0aCBubyB2YWx1ZXMuXG4gICAgcmV0dXJuIHsgbmV4dDogZG9uZVJlc3VsdCB9O1xuICB9XG4gIGV4cG9ydHMudmFsdWVzID0gdmFsdWVzO1xuXG4gIGZ1bmN0aW9uIGRvbmVSZXN1bHQoKSB7XG4gICAgcmV0dXJuIHsgdmFsdWU6IHVuZGVmaW5lZCwgZG9uZTogdHJ1ZSB9O1xuICB9XG5cbiAgQ29udGV4dC5wcm90b3R5cGUgPSB7XG4gICAgY29uc3RydWN0b3I6IENvbnRleHQsXG5cbiAgICByZXNldDogZnVuY3Rpb24oc2tpcFRlbXBSZXNldCkge1xuICAgICAgdGhpcy5wcmV2ID0gMDtcbiAgICAgIHRoaXMubmV4dCA9IDA7XG4gICAgICAvLyBSZXNldHRpbmcgY29udGV4dC5fc2VudCBmb3IgbGVnYWN5IHN1cHBvcnQgb2YgQmFiZWwnc1xuICAgICAgLy8gZnVuY3Rpb24uc2VudCBpbXBsZW1lbnRhdGlvbi5cbiAgICAgIHRoaXMuc2VudCA9IHRoaXMuX3NlbnQgPSB1bmRlZmluZWQ7XG4gICAgICB0aGlzLmRvbmUgPSBmYWxzZTtcbiAgICAgIHRoaXMuZGVsZWdhdGUgPSBudWxsO1xuXG4gICAgICB0aGlzLm1ldGhvZCA9IFwibmV4dFwiO1xuICAgICAgdGhpcy5hcmcgPSB1bmRlZmluZWQ7XG5cbiAgICAgIHRoaXMudHJ5RW50cmllcy5mb3JFYWNoKHJlc2V0VHJ5RW50cnkpO1xuXG4gICAgICBpZiAoIXNraXBUZW1wUmVzZXQpIHtcbiAgICAgICAgZm9yICh2YXIgbmFtZSBpbiB0aGlzKSB7XG4gICAgICAgICAgLy8gTm90IHN1cmUgYWJvdXQgdGhlIG9wdGltYWwgb3JkZXIgb2YgdGhlc2UgY29uZGl0aW9uczpcbiAgICAgICAgICBpZiAobmFtZS5jaGFyQXQoMCkgPT09IFwidFwiICYmXG4gICAgICAgICAgICAgIGhhc093bi5jYWxsKHRoaXMsIG5hbWUpICYmXG4gICAgICAgICAgICAgICFpc05hTigrbmFtZS5zbGljZSgxKSkpIHtcbiAgICAgICAgICAgIHRoaXNbbmFtZV0gPSB1bmRlZmluZWQ7XG4gICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICB9XG4gICAgfSxcblxuICAgIHN0b3A6IGZ1bmN0aW9uKCkge1xuICAgICAgdGhpcy5kb25lID0gdHJ1ZTtcblxuICAgICAgdmFyIHJvb3RFbnRyeSA9IHRoaXMudHJ5RW50cmllc1swXTtcbiAgICAgIHZhciByb290UmVjb3JkID0gcm9vdEVudHJ5LmNvbXBsZXRpb247XG4gICAgICBpZiAocm9vdFJlY29yZC50eXBlID09PSBcInRocm93XCIpIHtcbiAgICAgICAgdGhyb3cgcm9vdFJlY29yZC5hcmc7XG4gICAgICB9XG5cbiAgICAgIHJldHVybiB0aGlzLnJ2YWw7XG4gICAgfSxcblxuICAgIGRpc3BhdGNoRXhjZXB0aW9uOiBmdW5jdGlvbihleGNlcHRpb24pIHtcbiAgICAgIGlmICh0aGlzLmRvbmUpIHtcbiAgICAgICAgdGhyb3cgZXhjZXB0aW9uO1xuICAgICAgfVxuXG4gICAgICB2YXIgY29udGV4dCA9IHRoaXM7XG4gICAgICBmdW5jdGlvbiBoYW5kbGUobG9jLCBjYXVnaHQpIHtcbiAgICAgICAgcmVjb3JkLnR5cGUgPSBcInRocm93XCI7XG4gICAgICAgIHJlY29yZC5hcmcgPSBleGNlcHRpb247XG4gICAgICAgIGNvbnRleHQubmV4dCA9IGxvYztcblxuICAgICAgICBpZiAoY2F1Z2h0KSB7XG4gICAgICAgICAgLy8gSWYgdGhlIGRpc3BhdGNoZWQgZXhjZXB0aW9uIHdhcyBjYXVnaHQgYnkgYSBjYXRjaCBibG9jayxcbiAgICAgICAgICAvLyB0aGVuIGxldCB0aGF0IGNhdGNoIGJsb2NrIGhhbmRsZSB0aGUgZXhjZXB0aW9uIG5vcm1hbGx5LlxuICAgICAgICAgIGNvbnRleHQubWV0aG9kID0gXCJuZXh0XCI7XG4gICAgICAgICAgY29udGV4dC5hcmcgPSB1bmRlZmluZWQ7XG4gICAgICAgIH1cblxuICAgICAgICByZXR1cm4gISEgY2F1Z2h0O1xuICAgICAgfVxuXG4gICAgICBmb3IgKHZhciBpID0gdGhpcy50cnlFbnRyaWVzLmxlbmd0aCAtIDE7IGkgPj0gMDsgLS1pKSB7XG4gICAgICAgIHZhciBlbnRyeSA9IHRoaXMudHJ5RW50cmllc1tpXTtcbiAgICAgICAgdmFyIHJlY29yZCA9IGVudHJ5LmNvbXBsZXRpb247XG5cbiAgICAgICAgaWYgKGVudHJ5LnRyeUxvYyA9PT0gXCJyb290XCIpIHtcbiAgICAgICAgICAvLyBFeGNlcHRpb24gdGhyb3duIG91dHNpZGUgb2YgYW55IHRyeSBibG9jayB0aGF0IGNvdWxkIGhhbmRsZVxuICAgICAgICAgIC8vIGl0LCBzbyBzZXQgdGhlIGNvbXBsZXRpb24gdmFsdWUgb2YgdGhlIGVudGlyZSBmdW5jdGlvbiB0b1xuICAgICAgICAgIC8vIHRocm93IHRoZSBleGNlcHRpb24uXG4gICAgICAgICAgcmV0dXJuIGhhbmRsZShcImVuZFwiKTtcbiAgICAgICAgfVxuXG4gICAgICAgIGlmIChlbnRyeS50cnlMb2MgPD0gdGhpcy5wcmV2KSB7XG4gICAgICAgICAgdmFyIGhhc0NhdGNoID0gaGFzT3duLmNhbGwoZW50cnksIFwiY2F0Y2hMb2NcIik7XG4gICAgICAgICAgdmFyIGhhc0ZpbmFsbHkgPSBoYXNPd24uY2FsbChlbnRyeSwgXCJmaW5hbGx5TG9jXCIpO1xuXG4gICAgICAgICAgaWYgKGhhc0NhdGNoICYmIGhhc0ZpbmFsbHkpIHtcbiAgICAgICAgICAgIGlmICh0aGlzLnByZXYgPCBlbnRyeS5jYXRjaExvYykge1xuICAgICAgICAgICAgICByZXR1cm4gaGFuZGxlKGVudHJ5LmNhdGNoTG9jLCB0cnVlKTtcbiAgICAgICAgICAgIH0gZWxzZSBpZiAodGhpcy5wcmV2IDwgZW50cnkuZmluYWxseUxvYykge1xuICAgICAgICAgICAgICByZXR1cm4gaGFuZGxlKGVudHJ5LmZpbmFsbHlMb2MpO1xuICAgICAgICAgICAgfVxuXG4gICAgICAgICAgfSBlbHNlIGlmIChoYXNDYXRjaCkge1xuICAgICAgICAgICAgaWYgKHRoaXMucHJldiA8IGVudHJ5LmNhdGNoTG9jKSB7XG4gICAgICAgICAgICAgIHJldHVybiBoYW5kbGUoZW50cnkuY2F0Y2hMb2MsIHRydWUpO1xuICAgICAgICAgICAgfVxuXG4gICAgICAgICAgfSBlbHNlIGlmIChoYXNGaW5hbGx5KSB7XG4gICAgICAgICAgICBpZiAodGhpcy5wcmV2IDwgZW50cnkuZmluYWxseUxvYykge1xuICAgICAgICAgICAgICByZXR1cm4gaGFuZGxlKGVudHJ5LmZpbmFsbHlMb2MpO1xuICAgICAgICAgICAgfVxuXG4gICAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAgIHRocm93IG5ldyBFcnJvcihcInRyeSBzdGF0ZW1lbnQgd2l0aG91dCBjYXRjaCBvciBmaW5hbGx5XCIpO1xuICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgfVxuICAgIH0sXG5cbiAgICBhYnJ1cHQ6IGZ1bmN0aW9uKHR5cGUsIGFyZykge1xuICAgICAgZm9yICh2YXIgaSA9IHRoaXMudHJ5RW50cmllcy5sZW5ndGggLSAxOyBpID49IDA7IC0taSkge1xuICAgICAgICB2YXIgZW50cnkgPSB0aGlzLnRyeUVudHJpZXNbaV07XG4gICAgICAgIGlmIChlbnRyeS50cnlMb2MgPD0gdGhpcy5wcmV2ICYmXG4gICAgICAgICAgICBoYXNPd24uY2FsbChlbnRyeSwgXCJmaW5hbGx5TG9jXCIpICYmXG4gICAgICAgICAgICB0aGlzLnByZXYgPCBlbnRyeS5maW5hbGx5TG9jKSB7XG4gICAgICAgICAgdmFyIGZpbmFsbHlFbnRyeSA9IGVudHJ5O1xuICAgICAgICAgIGJyZWFrO1xuICAgICAgICB9XG4gICAgICB9XG5cbiAgICAgIGlmIChmaW5hbGx5RW50cnkgJiZcbiAgICAgICAgICAodHlwZSA9PT0gXCJicmVha1wiIHx8XG4gICAgICAgICAgIHR5cGUgPT09IFwiY29udGludWVcIikgJiZcbiAgICAgICAgICBmaW5hbGx5RW50cnkudHJ5TG9jIDw9IGFyZyAmJlxuICAgICAgICAgIGFyZyA8PSBmaW5hbGx5RW50cnkuZmluYWxseUxvYykge1xuICAgICAgICAvLyBJZ25vcmUgdGhlIGZpbmFsbHkgZW50cnkgaWYgY29udHJvbCBpcyBub3QganVtcGluZyB0byBhXG4gICAgICAgIC8vIGxvY2F0aW9uIG91dHNpZGUgdGhlIHRyeS9jYXRjaCBibG9jay5cbiAgICAgICAgZmluYWxseUVudHJ5ID0gbnVsbDtcbiAgICAgIH1cblxuICAgICAgdmFyIHJlY29yZCA9IGZpbmFsbHlFbnRyeSA/IGZpbmFsbHlFbnRyeS5jb21wbGV0aW9uIDoge307XG4gICAgICByZWNvcmQudHlwZSA9IHR5cGU7XG4gICAgICByZWNvcmQuYXJnID0gYXJnO1xuXG4gICAgICBpZiAoZmluYWxseUVudHJ5KSB7XG4gICAgICAgIHRoaXMubWV0aG9kID0gXCJuZXh0XCI7XG4gICAgICAgIHRoaXMubmV4dCA9IGZpbmFsbHlFbnRyeS5maW5hbGx5TG9jO1xuICAgICAgICByZXR1cm4gQ29udGludWVTZW50aW5lbDtcbiAgICAgIH1cblxuICAgICAgcmV0dXJuIHRoaXMuY29tcGxldGUocmVjb3JkKTtcbiAgICB9LFxuXG4gICAgY29tcGxldGU6IGZ1bmN0aW9uKHJlY29yZCwgYWZ0ZXJMb2MpIHtcbiAgICAgIGlmIChyZWNvcmQudHlwZSA9PT0gXCJ0aHJvd1wiKSB7XG4gICAgICAgIHRocm93IHJlY29yZC5hcmc7XG4gICAgICB9XG5cbiAgICAgIGlmIChyZWNvcmQudHlwZSA9PT0gXCJicmVha1wiIHx8XG4gICAgICAgICAgcmVjb3JkLnR5cGUgPT09IFwiY29udGludWVcIikge1xuICAgICAgICB0aGlzLm5leHQgPSByZWNvcmQuYXJnO1xuICAgICAgfSBlbHNlIGlmIChyZWNvcmQudHlwZSA9PT0gXCJyZXR1cm5cIikge1xuICAgICAgICB0aGlzLnJ2YWwgPSB0aGlzLmFyZyA9IHJlY29yZC5hcmc7XG4gICAgICAgIHRoaXMubWV0aG9kID0gXCJyZXR1cm5cIjtcbiAgICAgICAgdGhpcy5uZXh0ID0gXCJlbmRcIjtcbiAgICAgIH0gZWxzZSBpZiAocmVjb3JkLnR5cGUgPT09IFwibm9ybWFsXCIgJiYgYWZ0ZXJMb2MpIHtcbiAgICAgICAgdGhpcy5uZXh0ID0gYWZ0ZXJMb2M7XG4gICAgICB9XG5cbiAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgIH0sXG5cbiAgICBmaW5pc2g6IGZ1bmN0aW9uKGZpbmFsbHlMb2MpIHtcbiAgICAgIGZvciAodmFyIGkgPSB0aGlzLnRyeUVudHJpZXMubGVuZ3RoIC0gMTsgaSA+PSAwOyAtLWkpIHtcbiAgICAgICAgdmFyIGVudHJ5ID0gdGhpcy50cnlFbnRyaWVzW2ldO1xuICAgICAgICBpZiAoZW50cnkuZmluYWxseUxvYyA9PT0gZmluYWxseUxvYykge1xuICAgICAgICAgIHRoaXMuY29tcGxldGUoZW50cnkuY29tcGxldGlvbiwgZW50cnkuYWZ0ZXJMb2MpO1xuICAgICAgICAgIHJlc2V0VHJ5RW50cnkoZW50cnkpO1xuICAgICAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgfSxcblxuICAgIFwiY2F0Y2hcIjogZnVuY3Rpb24odHJ5TG9jKSB7XG4gICAgICBmb3IgKHZhciBpID0gdGhpcy50cnlFbnRyaWVzLmxlbmd0aCAtIDE7IGkgPj0gMDsgLS1pKSB7XG4gICAgICAgIHZhciBlbnRyeSA9IHRoaXMudHJ5RW50cmllc1tpXTtcbiAgICAgICAgaWYgKGVudHJ5LnRyeUxvYyA9PT0gdHJ5TG9jKSB7XG4gICAgICAgICAgdmFyIHJlY29yZCA9IGVudHJ5LmNvbXBsZXRpb247XG4gICAgICAgICAgaWYgKHJlY29yZC50eXBlID09PSBcInRocm93XCIpIHtcbiAgICAgICAgICAgIHZhciB0aHJvd24gPSByZWNvcmQuYXJnO1xuICAgICAgICAgICAgcmVzZXRUcnlFbnRyeShlbnRyeSk7XG4gICAgICAgICAgfVxuICAgICAgICAgIHJldHVybiB0aHJvd247XG4gICAgICAgIH1cbiAgICAgIH1cblxuICAgICAgLy8gVGhlIGNvbnRleHQuY2F0Y2ggbWV0aG9kIG11c3Qgb25seSBiZSBjYWxsZWQgd2l0aCBhIGxvY2F0aW9uXG4gICAgICAvLyBhcmd1bWVudCB0aGF0IGNvcnJlc3BvbmRzIHRvIGEga25vd24gY2F0Y2ggYmxvY2suXG4gICAgICB0aHJvdyBuZXcgRXJyb3IoXCJpbGxlZ2FsIGNhdGNoIGF0dGVtcHRcIik7XG4gICAgfSxcblxuICAgIGRlbGVnYXRlWWllbGQ6IGZ1bmN0aW9uKGl0ZXJhYmxlLCByZXN1bHROYW1lLCBuZXh0TG9jKSB7XG4gICAgICB0aGlzLmRlbGVnYXRlID0ge1xuICAgICAgICBpdGVyYXRvcjogdmFsdWVzKGl0ZXJhYmxlKSxcbiAgICAgICAgcmVzdWx0TmFtZTogcmVzdWx0TmFtZSxcbiAgICAgICAgbmV4dExvYzogbmV4dExvY1xuICAgICAgfTtcblxuICAgICAgaWYgKHRoaXMubWV0aG9kID09PSBcIm5leHRcIikge1xuICAgICAgICAvLyBEZWxpYmVyYXRlbHkgZm9yZ2V0IHRoZSBsYXN0IHNlbnQgdmFsdWUgc28gdGhhdCB3ZSBkb24ndFxuICAgICAgICAvLyBhY2NpZGVudGFsbHkgcGFzcyBpdCBvbiB0byB0aGUgZGVsZWdhdGUuXG4gICAgICAgIHRoaXMuYXJnID0gdW5kZWZpbmVkO1xuICAgICAgfVxuXG4gICAgICByZXR1cm4gQ29udGludWVTZW50aW5lbDtcbiAgICB9XG4gIH07XG5cbiAgLy8gUmVnYXJkbGVzcyBvZiB3aGV0aGVyIHRoaXMgc2NyaXB0IGlzIGV4ZWN1dGluZyBhcyBhIENvbW1vbkpTIG1vZHVsZVxuICAvLyBvciBub3QsIHJldHVybiB0aGUgcnVudGltZSBvYmplY3Qgc28gdGhhdCB3ZSBjYW4gZGVjbGFyZSB0aGUgdmFyaWFibGVcbiAgLy8gcmVnZW5lcmF0b3JSdW50aW1lIGluIHRoZSBvdXRlciBzY29wZSwgd2hpY2ggYWxsb3dzIHRoaXMgbW9kdWxlIHRvIGJlXG4gIC8vIGluamVjdGVkIGVhc2lseSBieSBgYmluL3JlZ2VuZXJhdG9yIC0taW5jbHVkZS1ydW50aW1lIHNjcmlwdC5qc2AuXG4gIHJldHVybiBleHBvcnRzO1xuXG59KFxuICAvLyBJZiB0aGlzIHNjcmlwdCBpcyBleGVjdXRpbmcgYXMgYSBDb21tb25KUyBtb2R1bGUsIHVzZSBtb2R1bGUuZXhwb3J0c1xuICAvLyBhcyB0aGUgcmVnZW5lcmF0b3JSdW50aW1lIG5hbWVzcGFjZS4gT3RoZXJ3aXNlIGNyZWF0ZSBhIG5ldyBlbXB0eVxuICAvLyBvYmplY3QuIEVpdGhlciB3YXksIHRoZSByZXN1bHRpbmcgb2JqZWN0IHdpbGwgYmUgdXNlZCB0byBpbml0aWFsaXplXG4gIC8vIHRoZSByZWdlbmVyYXRvclJ1bnRpbWUgdmFyaWFibGUgYXQgdGhlIHRvcCBvZiB0aGlzIGZpbGUuXG4gIHR5cGVvZiBtb2R1bGUgPT09IFwib2JqZWN0XCIgPyBtb2R1bGUuZXhwb3J0cyA6IHt9XG4pKTtcblxudHJ5IHtcbiAgcmVnZW5lcmF0b3JSdW50aW1lID0gcnVudGltZTtcbn0gY2F0Y2ggKGFjY2lkZW50YWxTdHJpY3RNb2RlKSB7XG4gIC8vIFRoaXMgbW9kdWxlIHNob3VsZCBub3QgYmUgcnVubmluZyBpbiBzdHJpY3QgbW9kZSwgc28gdGhlIGFib3ZlXG4gIC8vIGFzc2lnbm1lbnQgc2hvdWxkIGFsd2F5cyB3b3JrIHVubGVzcyBzb21ldGhpbmcgaXMgbWlzY29uZmlndXJlZC4gSnVzdFxuICAvLyBpbiBjYXNlIHJ1bnRpbWUuanMgYWNjaWRlbnRhbGx5IHJ1bnMgaW4gc3RyaWN0IG1vZGUsIHdlIGNhbiBlc2NhcGVcbiAgLy8gc3RyaWN0IG1vZGUgdXNpbmcgYSBnbG9iYWwgRnVuY3Rpb24gY2FsbC4gVGhpcyBjb3VsZCBjb25jZWl2YWJseSBmYWlsXG4gIC8vIGlmIGEgQ29udGVudCBTZWN1cml0eSBQb2xpY3kgZm9yYmlkcyB1c2luZyBGdW5jdGlvbiwgYnV0IGluIHRoYXQgY2FzZVxuICAvLyB0aGUgcHJvcGVyIHNvbHV0aW9uIGlzIHRvIGZpeCB0aGUgYWNjaWRlbnRhbCBzdHJpY3QgbW9kZSBwcm9ibGVtLiBJZlxuICAvLyB5b3UndmUgbWlzY29uZmlndXJlZCB5b3VyIGJ1bmRsZXIgdG8gZm9yY2Ugc3RyaWN0IG1vZGUgYW5kIGFwcGxpZWQgYVxuICAvLyBDU1AgdG8gZm9yYmlkIEZ1bmN0aW9uLCBhbmQgeW91J3JlIG5vdCB3aWxsaW5nIHRvIGZpeCBlaXRoZXIgb2YgdGhvc2VcbiAgLy8gcHJvYmxlbXMsIHBsZWFzZSBkZXRhaWwgeW91ciB1bmlxdWUgcHJlZGljYW1lbnQgaW4gYSBHaXRIdWIgaXNzdWUuXG4gIEZ1bmN0aW9uKFwiclwiLCBcInJlZ2VuZXJhdG9yUnVudGltZSA9IHJcIikocnVudGltZSk7XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxudmFyIGdsb2JhbFRoaXMgPSAobmV3IEZ1bmN0aW9uKCdyZXR1cm4gdGhpczsnKSkoKTtcbmdsb2JhbFRoaXMuZ2xvYmFsVGhpcyA9IGdsb2JhbFRoaXM7XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cbmltcG9ydCAnQGx5bngtanMvaW9zLXBvbHlmaWxsJztcbmltcG9ydCAnQGx5bngtanMvaW9zLXBvbHlmaWxsLXByb21pc2UnO1xuaW1wb3J0ICdyZWdlbmVyYXRvci1ydW50aW1lL3J1bnRpbWUnO1xuaW1wb3J0ICcuL2luZGV4LmNhcmQnO1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbi8vIEdldCB0aGUgZ2xvYmFsIHZhcmlhYmxlIG9mIHRoZSBjdXJyZW50IEpTIHJ1bnRpbWUuXG5jb25zdCBfZ2xvYmFsID0gKGZ1bmN0aW9uICgpIHtcbiAgLy8gZXNsaW50LWRpc2FibGUtbmV4dC1saW5lIG5vLWV2YWxcbiAgcmV0dXJuIHRoaXMgfHwgKDAsIGV2YWwpKCd0aGlzJyk7XG59KSgpO1xuZXhwb3J0IGRlZmF1bHQgX2dsb2JhbDtcbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBpc0Z1bmN0aW9uIH0gZnJvbSAnLi91dGlscyc7XG5cbmV4cG9ydCB0eXBlIFNoYXJlZENvbnNvbGUgPSB0eXBlb2YgbmF0aXZlQ29uc29sZSAmIHsgcnVudGltZUlkOiBzdHJpbmcgfTtcblxuLyoqXG4gKiBDcmVhdGUgYSBjb25zb2xlIHRoYXQgd3JhcHBlZCB0aGUgbmF0aXZlQ29uc29sZSB0byBsb2cgd2l0aCBydW50aW1lSWQuXG4gKiBAcGFyYW0gcnVudGltZUlkIFRoZSBydW50aW1lSWQgdG8gYmUgbG9nZ2VkXG4gKlxuICogVGhlIHJ1bnRpbWVJZCBjYW4gYmUgY2hhbmdlZCBieSBzZXR0aW5nIGRpcmVjdGx5LlxuICpcbiAqIEBleGFtcGxlXG4gKiBjb25zdCBzaGFyZWRDb25zb2xlID0gY3JlYXRlU2hhcmVkQ29uc29sZShydW50aW1lSWQpO1xuICovXG5leHBvcnQgZnVuY3Rpb24gY3JlYXRlU2hhcmVkQ29uc29sZShydW50aW1lSWQ/OiBzdHJpbmcpOiBTaGFyZWRDb25zb2xlIHtcbiAgLy8gVE9ETyh6aGFuZ3F1bi4yOSk6IERlbGV0ZSBhbGwgcmVmZXJlbmNlcyB0byBydW50aW1lSWRcbiAgcmV0dXJuIG5hdGl2ZUNvbnNvbGUgYXMgU2hhcmVkQ29uc29sZTtcbn1cblxuY29uc3QgX2dsb2JhbCA9IChmdW5jdGlvbiAoKSB7XG4gIC8vIGVzbGludC1kaXNhYmxlLW5leHQtbGluZSBuby1ldmFsXG4gIHJldHVybiB0aGlzIHx8ICgwLCBldmFsKSgndGhpcycpO1xufSkoKTtcblxuLyoqXG4gKiBUaGlzIGlzIGEgd3JhcHBlciB0byBuYXRpdmVDb25zb2xlIHRoYXQgbG9nIHdpdGggZ3JvdXBJZC5cbiAqXG4gKiBUaGUgZ3JvdXBJZCBkZWZhdWx0cyB0byAnLTEnIGFuZCBjYW4gYmUgY2hhbmdlZC5cbiAqL1xuY29uc3QgZ3JvdXBDb25zb2xlID0gY3JlYXRlU2hhcmVkQ29uc29sZShgZ3JvdXBJZDoke19nbG9iYWwuZ3JvdXBJZCB8fCAnLTEnfWApO1xuXG4vKipcbiAqIEFsbCBjb25zb2xlIGluIGx5bngta2VybmVsIHNob3VsZCB1c2UgdGhpcyBjb25zb2xlXG4gKi9cbmV4cG9ydCBkZWZhdWx0IE5PREVfRU5WID09PSAnZGV2ZWxvcG1lbnQnXG4gID8gZ3JvdXBDb25zb2xlXG4gIDogKG5hdGl2ZUNvbnNvbGUgYXMgU2hhcmVkQ29uc29sZSk7XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuZXhwb3J0IGZ1bmN0aW9uIGhhc1Byb3BlcnR5KG9iamVjdCwgcHJvcGVydHkpOiBib29sZWFuIHtcbiAgLy8gcmV0dXJuIE9iamVjdC5wcm90b3R5cGUuaGFzT3duUHJvcGVydHkuY2FsbChPYmplY3QuZ2V0UHJvdG90eXBlT2Yob2JqZWN0KSwgcHJvcGVydHkpXG4gIHJldHVybiBPYmplY3QucHJvdG90eXBlLmhhc093blByb3BlcnR5LmNhbGwob2JqZWN0IHx8IHt9LCBwcm9wZXJ0eSk7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBnZXREYXRhVHlwZShkYXRhOiBhbnkpOiBzdHJpbmcge1xuICBjb25zdCB0eXBlID0gdHlwZW9mIGRhdGE7XG4gIGlmICh0eXBlICE9PSAnb2JqZWN0JykgcmV0dXJuIHR5cGU7XG4gIGlmIChBcnJheS5pc0FycmF5KGRhdGEpKSByZXR1cm4gJ2FycmF5JztcbiAgaWYgKGRhdGEgPT0gbnVsbCkgcmV0dXJuICdudWxsJztcbiAgaWYgKGRhdGEgaW5zdGFuY2VvZiBEYXRlKSByZXR1cm4gJ2RhdGUnO1xuICBpZiAoZGF0YSBpbnN0YW5jZW9mIFJlZ0V4cCkgcmV0dXJuICdyZWdFeHAnO1xuICByZXR1cm4gJ29iamVjdCc7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBpc1N0cmluZyh2YWw6IHVua25vd24pOiB2YWwgaXMgc3RyaW5nIHtcbiAgcmV0dXJuIHR5cGVvZiB2YWwgPT09ICdzdHJpbmcnO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gaXNPYmplY3QodmFsOiB1bmtub3duKTogYm9vbGVhbiB7XG4gIHJldHVybiBnZXREYXRhVHlwZSh2YWwpID09PSAnb2JqZWN0Jztcbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGlzRnVuY3Rpb24ob2JqOiB1bmtub3duKTogb2JqIGlzIEFueUZ1bmN0aW9uIHtcbiAgY29uc3QgZGF0YVR5cGUgPSBnZXREYXRhVHlwZShvYmopO1xuICByZXR1cm4gZGF0YVR5cGUgPT09ICdmdW5jdGlvbic7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBpc0FycmF5KGFycmF5OiB1bmtub3duKTogYXJyYXkgaXMgQXJyYXk8dW5rbm93bj4ge1xuICByZXR1cm4gZ2V0RGF0YVR5cGUoYXJyYXkpID09PSAnYXJyYXknO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gaXNOdWxsKG86IHVua25vd24pOiBvIGlzIG51bGwge1xuICByZXR1cm4gbyA9PT0gbnVsbDtcbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGlzVW5kZWZpbmVkKG86IHVua25vd24pOiBvIGlzIHVuZGVmaW5lZCB7XG4gIHJldHVybiBvID09PSB2b2lkIDA7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBpc051bGxPclVuZGVmKG86IHVua25vd24pOiBvIGlzIG51bGwgfCB1bmRlZmluZWQge1xuICByZXR1cm4gaXNVbmRlZmluZWQobykgfHwgaXNOdWxsKG8pO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gaXNFcnJvcihvOiB1bmtub3duKTogbyBpcyBFcnJvciB7XG4gIHN3aXRjaCAoT2JqZWN0LnByb3RvdHlwZS50b1N0cmluZy5jYWxsKG8pKSB7XG4gICAgY2FzZSAnW29iamVjdCBFcnJvcl0nOlxuICAgICAgcmV0dXJuIHRydWU7XG4gICAgY2FzZSAnW29iamVjdCBFeGNlcHRpb25dJzpcbiAgICAgIHJldHVybiB0cnVlO1xuICAgIGNhc2UgJ1tvYmplY3QgRE9NRXhjZXB0aW9uXSc6XG4gICAgICByZXR1cm4gdHJ1ZTtcbiAgICBkZWZhdWx0OlxuICAgICAgcmV0dXJuIGlzSW5zdGFuY2VPZihvLCBFcnJvcik7XG4gIH1cbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGlzSW5zdGFuY2VPZjxUIGV4dGVuZHMgRnVuY3Rpb24+KG86IHVua25vd24sIGJhc2U6IFQpOiBvIGlzIFQge1xuICB0cnkge1xuICAgIHJldHVybiBvIGluc3RhbmNlb2YgYmFzZTtcbiAgfSBjYXRjaCAoX2UpIHtcbiAgICByZXR1cm4gZmFsc2U7XG4gIH1cbn1cblxuZXhwb3J0IGNsYXNzIFRoaXJkU2NyaXB0RXJyb3IgZXh0ZW5kcyBFcnJvciB7XG4gIHR5cGU6IHN0cmluZztcbiAgY29uc3RydWN0b3IobXNnOiBhbnkpIHtcbiAgICBzdXBlcihgJHttc2d9YCk7XG4gICAgdGhpcy50eXBlID0gJ1RoaXJkU2NyaXB0RXJyb3InO1xuICB9XG59XG5cbmV4cG9ydCBjbGFzcyBBcHBTZXJ2aWNlU2RrS25vd25FcnJvciBleHRlbmRzIEVycm9yIHtcbiAgdHlwZTogc3RyaW5nO1xuICBjb25zdHJ1Y3Rvcihtc2cpIHtcbiAgICBzdXBlcihgQVBQLVNFUlZJQ0UtU0RLOiArICR7bXNnfWApO1xuICAgIHRoaXMudHlwZSA9ICdBcHBTZXJ2aWNlU2RrS25vd25FcnJvcic7XG4gIH1cbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGd1aWQoKTogc3RyaW5nIHtcbiAgcmV0dXJuICd4eHh4eHh4eC14eHh4LTR4eHgteXh4eC14eHh4eHh4eHh4eHgnLnJlcGxhY2UoL1t4eV0vZywgKGNoYXIpID0+IHtcbiAgICBjb25zdCByYW5kID0gKDE2ICogTWF0aC5yYW5kb20oKSkgfCAwO1xuICAgIHJldHVybiAoY2hhciA9PT0gJ3gnID8gcmFuZCA6ICgzICYgcmFuZCkgfCA4KS50b1N0cmluZygxNik7XG4gIH0pO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gbm9vcCgpOiB2b2lkIHt9XG5cbmV4cG9ydCBmdW5jdGlvbiBmb3JFYWNoUmlnaHQ8VD4oYXJyOiBBcnJheTxUPiwgY2I6ICh2YWx1ZTogVCkgPT4gdm9pZCk6IHZvaWQge1xuICBpZiAoQXJyYXkuaXNBcnJheShhcnIpKSB7XG4gICAgbGV0IGxlbiA9IGFyci5sZW5ndGg7XG4gICAgZm9yIChsZXQgaW5kZXggPSBsZW4gLSAxOyBpbmRleCA+PSAwOyBpbmRleC0tKSB7XG4gICAgICBjYihhcnJbaW5kZXhdKTtcbiAgICB9XG4gIH0gZWxzZSB7XG4gICAgdGhyb3cgbmV3IEVycm9yKCdmb3JFYWNoUmlnaHQgRVJST1I6IGZpcnN0IHBhcmFtcyBtdXN0IGJlIGFycmF5LicpO1xuICB9XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBjYWxsYmFja01lcmdlKF9jYnMpOiB2b2lkIHtcbiAgaWYgKEFycmF5LmlzQXJyYXkoX2NicykpIHtcbiAgICBmb3IgKGxldCBpID0gMCwgbGVuID0gX2Nicy5sZW5ndGg7IGkgPCBsZW47ICsraSkge1xuICAgICAgX2Nic1tpXSgpO1xuICAgIH1cbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IHR0Q29uc29sZSB9IGZyb20gJ0BseW54LWpzL3J1bnRpbWUtc2hhcmVkJztcbmV4cG9ydCB7IFNoYXJlZENvbnNvbGUsIGNyZWF0ZVNoYXJlZENvbnNvbGUgfSBmcm9tICdAbHlueC1qcy9ydW50aW1lLXNoYXJlZCc7XG5leHBvcnQgZGVmYXVsdCB0dENvbnNvbGU7XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuZXhwb3J0IHR5cGUgRXJyb3JOYW1lID1cbiAgfCAnSU5URVJOQUxfUEFSU0VfRVJST1InXG4gIHwgJ0lOVEVSTkFMX1JVTlRJTUVfRVJST1InXG4gIHwgJ1VTRVJfVkFMSURBVEVfRVJST1InXG4gIHwgJ1VTRVJfUlVOVElNRV9FUlJPUidcbiAgfCAnREFUQV9DSEFOR0VfSEFORExFX0VSUk9SJ1xuICB8ICdJTlZPS0VfRVJST1InO1xuXG5leHBvcnQgdHlwZSBFcnJvcktpbmQgPSAnSU5URVJOQUxfRVJST1InIHwgJ1VTRVJfRVJST1InO1xuZXhwb3J0IHR5cGUgRXJyb3JFbnYgPSAnU0VSVklDRSc7XG5cbi8qKlxuICogVGhlIGVudW0gdmFsdWVzIHNob3VsZCBiZSBzeW5jIHdpdGggYGx5bnhfZXJyb3IuaGAuXG4gKi9cbmV4cG9ydCBjb25zdCBlbnVtIEx5bnhFcnJvckxldmVsIHtcbiAgRmF0YWwgPSAwLFxuICBFcnJvcixcbiAgV2Fybixcbn1cblxuZXhwb3J0IGFic3RyYWN0IGNsYXNzIEJhc2VFcnJvciBleHRlbmRzIEVycm9yIHtcbiAgYWJzdHJhY3Qga2luZDogRXJyb3JLaW5kO1xuICBhYnN0cmFjdCBuYW1lOiBFcnJvck5hbWU7XG4gIGVudj86IEVycm9yRW52O1xuICBjb25zdHJ1Y3RvcihtZXNzYWdlOiBzdHJpbmcsIHN0YWNrPzogc3RyaW5nKSB7XG4gICAgc3VwZXIobWVzc2FnZSk7XG4gICAgaWYgKHN0YWNrKSB7XG4gICAgICB0aGlzLnN0YWNrID0gc3RhY2s7XG4gICAgfVxuICB9XG59XG5cbmV4cG9ydCBhYnN0cmFjdCBjbGFzcyBJbnRlcm5hbEVycm9yIGV4dGVuZHMgQmFzZUVycm9yIHtcbiAga2luZCA9ICdJTlRFUk5BTF9FUlJPUicgYXMgY29uc3Q7XG59XG5cbmV4cG9ydCBhYnN0cmFjdCBjbGFzcyBVc2VyRXJyb3IgZXh0ZW5kcyBCYXNlRXJyb3Ige1xuICBraW5kID0gJ1VTRVJfRVJST1InIGFzIGNvbnN0O1xufVxuXG5leHBvcnQgY2xhc3MgVXNlclZhbGlkYXRlRXJyb3IgZXh0ZW5kcyBVc2VyRXJyb3Ige1xuICBuYW1lID0gJ1VTRVJfVkFMSURBVEVfRVJST1InIGFzIGNvbnN0O1xufVxuXG4vKiogZXJyb3IgY29tZXMgZm9ybSB1c2UgY29kZSAqL1xuZXhwb3J0IGNsYXNzIFVzZXJSdW50aW1lRXJyb3IgZXh0ZW5kcyBVc2VyRXJyb3Ige1xuICBuYW1lID0gJ1VTRVJfUlVOVElNRV9FUlJPUicgYXMgY29uc3Q7XG59XG5cbi8qKlxuICogZXJyb3IgZnJvbSBpbnRlcm5hbCBmcmFtZXdvcmtcbiAqL1xuZXhwb3J0IGNsYXNzIEludGVybmFsUnVudGltZUVycm9yIGV4dGVuZHMgSW50ZXJuYWxFcnJvciB7XG4gIG5hbWUgPSAnSU5URVJOQUxfUlVOVElNRV9FUlJPUicgYXMgY29uc3Q7XG59XG5cbi8qKlxuICogZXJyb3IgZnJvbSBsZXB1c05HXG4gKi9cbmV4cG9ydCBjbGFzcyBJbnRlcm5hbExlcHVzTmdFcnJvciBleHRlbmRzIEVycm9yIHtcbiAgbmFtZTogc3RyaW5nO1xuICBzdGFjazogc3RyaW5nO1xuICBjb25zdHJ1Y3RvcihtZXNzYWdlOiBzdHJpbmcsIHN0YWNrPzogc3RyaW5nKSB7XG4gICAgc3VwZXIobWVzc2FnZSk7XG4gICAgaWYgKHN0YWNrKSB7XG4gICAgICB0aGlzLnN0YWNrID0gc3RhY2s7XG4gICAgfVxuICB9XG59XG5cbi8qKiBlcnJvciBjb21lcyBmcm9tIGpzYiBpbnZva2UgICovXG5leHBvcnQgY2xhc3MgSW52b2tlRXJyb3IgZXh0ZW5kcyBJbnRlcm5hbEVycm9yIHtcbiAgbmFtZSA9ICdJTlZPS0VfRVJST1InIGFzIGNvbnN0O1xufVxuXG5leHBvcnQgY2xhc3MgQXBwU2VydmljZUVuZ2luZUtub3duRXJyb3IgZXh0ZW5kcyBFcnJvciB7XG4gIHR5cGU6IHN0cmluZztcbiAgY29uc3RydWN0b3IobXNnKSB7XG4gICAgc3VwZXIoYEFQUC1TRVJWSUNFLUVuZ2luZTogJHttc2d9YCk7XG4gICAgdGhpcy50eXBlID0gJ0FwcFNlcnZpY2VFbmdpbmVLbm93bkVycm9yJztcbiAgfVxufVxuXG5leHBvcnQgaW50ZXJmYWNlIHNvdXJjZU1hcFJlbGVhc2VPYmoge1xuICBuYW1lOiBzdHJpbmc7XG4gIHN0YWNrOiBzdHJpbmc7IC8vIGRldGFpbCBzdGFjayBvZiBlcnJvclxuICBtZXNzYWdlOiBzdHJpbmc7IC8vIHRoZSBzb3VyY2VNYXBSZWxlYXNlSWQsIHN1Y2ggYXMgXCJkNzMxNjAxMTllZjdlNzc3NzYyNDZjYWNhMmE3Yjk4ZVwiXG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuZXhwb3J0IGNvbnN0IERFRkFVTFRfRU5UUlkgPSAnX19DYXJkX18nO1xuZXhwb3J0IGNvbnN0IEFQUF9TRVJWSUNFX05BTUUgPSAnYXBwLXNlcnZpY2UuanMnO1xuZXhwb3J0IGNvbnN0IFNPVVJDRV9NQVBfUkVMRUFTRV9FUlJPUl9OQU1FID0gJ0x5bnhHZXRTb3VyY2VNYXBSZWxlYXNlRXJyb3InO1xuZXhwb3J0IGludGVyZmFjZSBSVU5fVFlQRSB7XG4gIGZpbGVuYW1lOiBzdHJpbmc7XG4gIC8qKiBSZXBsYWNlIHRoZSBjb2RlIHdpdGggdGhlIGNvcnJlc3BvbmRpbmcgY29tbWl0SGFzaCBhZnRlciBjb21waWxhdGlvbiAqL1xuICBzbG90OiBzdHJpbmc7XG5cbiAgLyoqIHNvdXJjZW1hcCByZWxlYXNlIGZvciBrZXJuZWwgKi9cbiAgcmVsZWFzZTogc3RyaW5nO1xufVxuXG5leHBvcnQgY29uc3QgTFlOWF9DT1JFOiBSVU5fVFlQRSA9IHtcbiAgZmlsZW5hbWU6ICdseW54X2NvcmUnLFxuICBzbG90OiBfX0NPTU1JVF9IQVNIX18sXG4gIHJlbGVhc2U6IF9fQlVJTERfVkVSU0lPTl9fLFxufTtcbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgbmF0aXZlQ29uc29sZSBmcm9tICcuLi8uLi9jb21tb24vdHRDb25zb2xlJztcbi8qKlxuICogVGhlIFN1YmplY3QgaW50ZXJmYWNlIGRlY2xhcmVzIGEgc2V0IG9mIG1ldGhvZHMgZm9yIG1hbmFnaW5nIHN1YnNjcmliZXJzLlxuICovXG5pbnRlcmZhY2UgU3ViamVjdCB7XG4gIHJlZ2lzdGVyT2JzZXJ2ZXIob2JzZXJ2ZXI6IEZ1bmN0aW9uKTogdm9pZDtcbiAgcmVtb3ZlT2JzZXJ2ZXIob2JzZXJ2ZXI6IEZ1bmN0aW9uKTogdm9pZDtcbiAgbm90aWZ5RGF0YUNoYW5nZSh2YWx1ZTogYW55KTogdm9pZDtcbn1cblxuLyoqXG4gKiBUaGUgU3ViamVjdCBvd25zIHNvbWUgaW1wb3J0YW50IHN0YXRlIGFuZCBub3RpZmllcyBvYnNlcnZlcnMgd2hlbiB0aGUgc3RhdGVcbiAqIGNoYW5nZXMuXG4gKi9cbmNsYXNzIFNoYXJlRGF0YVN1YmplY3QgaW1wbGVtZW50cyBTdWJqZWN0IHtcbiAgLyoqXG4gICAqIEB0eXBlIHtudW1iZXJ9IEZvciB0aGUgc2FrZSBvZiBzaW1wbGljaXR5LCB0aGUgU3ViamVjdCdzIHN0YXRlLCBlc3NlbnRpYWxcbiAgICogdG8gYWxsIHN1YnNjcmliZXJzLCBpcyBzdG9yZWQgaW4gdGhpcyB2YXJpYWJsZS5cbiAgICovXG4gIHB1YmxpYyBzdGF0ZTogbnVtYmVyO1xuXG4gIC8qKlxuICAgKiBAdHlwZSB7T2JzZXJ2ZXJbXX0gTGlzdCBvZiBzdWJzY3JpYmVycy5cbiAgICpcbiAgICovXG4gIHByaXZhdGUgb2JzZXJ2ZXJzRnVuYzogRnVuY3Rpb25bXSA9IFtdO1xuXG4gIC8qKlxuICAgKiBUaGUgc3Vic2NyaXB0aW9uIG1hbmFnZW1lbnQgbWV0aG9kcy5cbiAgICovXG4gIHB1YmxpYyByZWdpc3Rlck9ic2VydmVyKG9ic2VydmVyOiBGdW5jdGlvbik6IHZvaWQge1xuICAgIGNvbnN0IGlzRXhpc3QgPSB0aGlzLm9ic2VydmVyc0Z1bmMuaW5jbHVkZXMob2JzZXJ2ZXIpO1xuICAgIGlmIChpc0V4aXN0KSB7XG4gICAgICByZXR1cm4gbmF0aXZlQ29uc29sZS5sb2coJ1N1YmplY3Q6IE9ic2VydmVyIGhhcyBiZWVuIGF0dGFjaGVkIGFscmVhZHkuJyk7XG4gICAgfVxuICAgIHRoaXMub2JzZXJ2ZXJzRnVuYy5wdXNoKG9ic2VydmVyKTtcbiAgfVxuXG4gIHB1YmxpYyByZW1vdmVPYnNlcnZlcihvYnNlcnZlcjogRnVuY3Rpb24pOiB2b2lkIHtcbiAgICAvLyBuYXRpdmVDb25zb2xlLmxvZygnU3ViamVjdDogTm9uZXhpc3RlbnQgb2JzZXJ2ZXIuJyk7XG4gICAgY29uc3Qgb2JzZXJ2ZXJJbmRleCA9IHRoaXMub2JzZXJ2ZXJzRnVuYy5pbmRleE9mKG9ic2VydmVyKTtcbiAgICBpZiAob2JzZXJ2ZXJJbmRleCA9PT0gLTEpIHtcbiAgICAgIHJldHVybiBuYXRpdmVDb25zb2xlLmxvZygnU3ViamVjdDogTm9uZXhpc3RlbnQgb2JzZXJ2ZXIuJyk7XG4gICAgfVxuXG4gICAgdGhpcy5vYnNlcnZlcnNGdW5jLnNwbGljZShvYnNlcnZlckluZGV4LCAxKTtcbiAgICAvLyAgIG5hdGl2ZUNvbnNvbGUubG9nKCdTdWJqZWN0OiBEZXRhY2hlZCBhbiBvYnNlcnZlci4nKTtcbiAgfVxuXG4gIHB1YmxpYyBub3RpZnlEYXRhQ2hhbmdlKHZhbHVlOiBhbnkpOiB2b2lkIHtcbiAgICB0aGlzLm9ic2VydmVyc0Z1bmMuZm9yRWFjaCgodG9PYnNlcnZlcikgPT4ge1xuICAgICAgaWYgKHR5cGVvZiB0b09ic2VydmVyID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgIHRyeSB7XG4gICAgICAgICAgdG9PYnNlcnZlcih2YWx1ZSk7XG4gICAgICAgIH0gY2F0Y2ggKGVycm9yKSB7XG4gICAgICAgICAgbmF0aXZlQ29uc29sZS5sb2coXG4gICAgICAgICAgICAnU2hhcmVkRGF0YSBjaGFuZ2UgYW5kIG5vdGlmeURhdGFDaGFuZ2UgZXJyb3IgaW5mbzonICsgZXJyb3JcbiAgICAgICAgICApO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgfSk7XG4gIH1cbn1cblxuZXhwb3J0IHsgU2hhcmVEYXRhU3ViamVjdCB9O1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IERFRkFVTFRfRU5UUlkgfSBmcm9tICcuL2NvbnN0YW50cyc7XG5pbXBvcnQgeyBTaGFyZURhdGFTdWJqZWN0IH0gZnJvbSAnLi4vbW9kdWxlcy9zaGFyZWREYXRhL1NoYXJlRGF0YVN1YmplY3QnO1xuaW1wb3J0IHsgbmF0aXZlR2xvYmFsIGFzIF9nbG9iYWwgfSBmcm9tICdAbHlueC1qcy9ydW50aW1lLXNoYXJlZCc7XG5cbi8vIGZvciBjYXJkLlxuX2dsb2JhbC5tdWx0aUFwcHMgPSB7fTtcbl9nbG9iYWwuY3VycmVudEFwcElkID0gJyc7XG5fZ2xvYmFsLmdsb2JDb21wb25lbnRSZWdpc3RQYXRoID0gJyc7XG5fZ2xvYmFsLnNoYXJlZERhdGEgPSB7fTtcbl9nbG9iYWwuZ2xvYkR5bmFtaWNDb21wb25lbnRFbnRyeSA9IERFRkFVTFRfRU5UUlk7XG5cbl9nbG9iYWwuc2hhcmVEYXRhU3ViamVjdCA9IG5ldyBTaGFyZURhdGFTdWJqZWN0KCk7XG5cbl9nbG9iYWwuVGFyb0x5bnggPSB7fTtcbi8vIGJ1bmRsZSBydW4gd2l0aCBubyBldmFsXG5fZ2xvYmFsLmJ1bmRsZVN1cHBvcnRMb2FkU2NyaXB0ID0gdHJ1ZTtcbmV4cG9ydCBjb25zdCB7IGxvYWRTY3JpcHQgfSA9IF9nbG9iYWw7XG5leHBvcnQgZGVmYXVsdCBfZ2xvYmFsO1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCBuYXRpdmVDb25zb2xlIGZyb20gJy4vdHRDb25zb2xlJztcbmxldCBpc05hdGl2ZUNvbnNvbGVIYXNBTG9nOiBib29sZWFuIHwgdW5kZWZpbmVkO1xuXG5leHBvcnQgZnVuY3Rpb24gYWxvZyhzdHI6IHN0cmluZykge1xuICBpZiAoIV9fT1BFTl9JTlRFUk5BTF9MT0dfXykge1xuICAgIHJldHVybjtcbiAgfVxuICBpZiAoaXNOYXRpdmVDb25zb2xlSGFzQUxvZyA9PT0gdW5kZWZpbmVkKSB7XG4gICAgaXNOYXRpdmVDb25zb2xlSGFzQUxvZyA9IHR5cGVvZiBuYXRpdmVDb25zb2xlLmFsb2cgPT09ICdmdW5jdGlvbic7XG4gIH1cbiAgaWYgKGlzTmF0aXZlQ29uc29sZUhhc0FMb2cpIHtcbiAgICBuYXRpdmVDb25zb2xlLmFsb2coJ1tMeW54SlNTREtdJyArIHN0cik7XG4gIH1cbn1cblxubGV0IGlzTmF0aXZlQ29uc29sZUhhc1JlcG9ydDogYm9vbGVhbiB8IHVuZGVmaW5lZDtcblxuZXhwb3J0IGZ1bmN0aW9uIHJlcG9ydChzdHI6IHN0cmluZykge1xuICBpZiAoIV9fT1BFTl9JTlRFUk5BTF9MT0dfXykge1xuICAgIHJldHVybjtcbiAgfVxuICBpZiAoaXNOYXRpdmVDb25zb2xlSGFzUmVwb3J0ID09PSB1bmRlZmluZWQpIHtcbiAgICBpc05hdGl2ZUNvbnNvbGVIYXNSZXBvcnQgPSB0eXBlb2YgbmF0aXZlQ29uc29sZS5yZXBvcnQgPT09ICdmdW5jdGlvbic7XG4gIH1cbiAgaWYgKGlzTmF0aXZlQ29uc29sZUhhc1JlcG9ydCkge1xuICAgIG5hdGl2ZUNvbnNvbGUucmVwb3J0KCdbTHlueEpTU0RLXScgKyBzdHIpO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuY29uc3QgbnVtYmVyUmVnRXhwID0gL1xcZCsvO1xuY2xhc3MgVmVyc2lvbiB7XG4gIG1ham9yOiBudW1iZXIgPSAwO1xuICBtaW5vcjogbnVtYmVyID0gMDtcbiAgcmV2aXNpb246IG51bWJlciA9IDA7XG4gIGJ1aWxkOiBudW1iZXIgPSAwO1xuXG4gIC8vIHZlcnNpb246IG1ham9yLm1pbm9yLnJldmlzaW9uLmJ1aWxkXG4gIGNvbnN0cnVjdG9yKHZlcnNpb246IHN0cmluZykge1xuICAgIHZlcnNpb24gPSBTdHJpbmcodmVyc2lvbik7XG4gICAgW1xuICAgICAgdGhpcy5tYWpvciA9IDAsXG4gICAgICB0aGlzLm1pbm9yID0gMCxcbiAgICAgIHRoaXMucmV2aXNpb24gPSAwLFxuICAgICAgdGhpcy5idWlsZCA9IDAsXG4gICAgXSA9IHZlcnNpb24uc3BsaXQoJy4nKS5tYXAoKHYpID0+IHtcbiAgICAgIGNvbnN0IHJlc3VsdCA9IG51bWJlclJlZ0V4cC5leGVjKHYpO1xuICAgICAgaWYgKHJlc3VsdCAmJiByZXN1bHQubGVuZ3RoID4gMCkge1xuICAgICAgICByZXR1cm4gK3Jlc3VsdFswXTtcbiAgICAgIH1cblxuICAgICAgcmV0dXJuIDA7XG4gICAgfSk7XG4gIH1cblxuICAvKipcbiAgICogR3JlYXRlciBUaGFuXG4gICAqIEBwYXJhbSB2ZXJzaW9uIHRoZSB2ZXJzaW9uIHRvIGJlIGNvbXBhcmVkXG4gICAqIEByZXR1cm5zIHRoaXMgPiB2ZXJzaW9uXG4gICAqL1xuICBndCh2ZXJzaW9uOiBzdHJpbmcgfCBWZXJzaW9uKTogYm9vbGVhbiB7XG4gICAgaWYgKHR5cGVvZiB2ZXJzaW9uID09PSAnc3RyaW5nJykge1xuICAgICAgdmVyc2lvbiA9IG5ldyBWZXJzaW9uKHZlcnNpb24pO1xuICAgIH1cblxuICAgIGlmICh0aGlzLm1ham9yID4gdmVyc2lvbi5tYWpvcikge1xuICAgICAgcmV0dXJuIHRydWU7XG4gICAgfSBlbHNlIGlmICh0aGlzLm1ham9yIDwgdmVyc2lvbi5tYWpvcikge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cblxuICAgIGlmICh0aGlzLm1pbm9yID4gdmVyc2lvbi5taW5vcikge1xuICAgICAgcmV0dXJuIHRydWU7XG4gICAgfSBlbHNlIGlmICh0aGlzLm1pbm9yIDwgdmVyc2lvbi5taW5vcikge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cblxuICAgIGlmICh0aGlzLnJldmlzaW9uID4gdmVyc2lvbi5yZXZpc2lvbikge1xuICAgICAgcmV0dXJuIHRydWU7XG4gICAgfSBlbHNlIGlmICh0aGlzLnJldmlzaW9uIDwgdmVyc2lvbi5yZXZpc2lvbikge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cblxuICAgIGlmICh0aGlzLmJ1aWxkID4gdmVyc2lvbi5idWlsZCkge1xuICAgICAgcmV0dXJuIHRydWU7XG4gICAgfSBlbHNlIGlmICh0aGlzLmJ1aWxkIDwgdmVyc2lvbi5idWlsZCkge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cblxuICAgIC8vIGVxdWFsc1xuICAgIHJldHVybiBmYWxzZTtcbiAgfVxuXG4gIC8qKlxuICAgKiBFUXVhbFxuICAgKiBAcGFyYW0gdmVyc2lvbiB0aGUgdmVyc2lvbiB0byBiZSBjb21wYXJlZFxuICAgKiBAcmV0dXJucyB0aGlzID09IHZlcnNpb25cbiAgICovXG4gIGVxKHZlcnNpb246IHN0cmluZyB8IFZlcnNpb24pOiBib29sZWFuIHtcbiAgICBpZiAodHlwZW9mIHZlcnNpb24gPT09ICdzdHJpbmcnKSB7XG4gICAgICB2ZXJzaW9uID0gbmV3IFZlcnNpb24odmVyc2lvbik7XG4gICAgfVxuXG4gICAgcmV0dXJuIChcbiAgICAgIHRoaXMubWFqb3IgPT09IHZlcnNpb24ubWFqb3IgJiZcbiAgICAgIHRoaXMubWlub3IgPT09IHZlcnNpb24ubWlub3IgJiZcbiAgICAgIHRoaXMucmV2aXNpb24gPT09IHZlcnNpb24ucmV2aXNpb24gJiZcbiAgICAgIHRoaXMuYnVpbGQgPT09IHZlcnNpb24uYnVpbGRcbiAgICApO1xuICB9XG5cbiAgLyoqXG4gICAqIExlc3MgVGhhblxuICAgKiBAcGFyYW0gdmVyc2lvbiB0aGUgdmVyc2lvbiB0byBiZSBjb21wYXJlZFxuICAgKiBAcmV0dXJucyB0aGlzIDwgdmVyc2lvblxuICAgKi9cbiAgbHQodmVyc2lvbjogc3RyaW5nIHwgVmVyc2lvbik6IGJvb2xlYW4ge1xuICAgIGlmICh0aGlzLmVxKHZlcnNpb24pKSB7XG4gICAgICByZXR1cm4gZmFsc2U7XG4gICAgfVxuXG4gICAgcmV0dXJuICF0aGlzLmd0KHZlcnNpb24pO1xuICB9XG5cbiAgLyoqXG4gICAqIEdyZWF0ZXIgVGhhbiBvciBFcXVhbFxuICAgKiBAcGFyYW0gdmVyc2lvbiB0aGUgdmVyc2lvbiB0byBiZSBjb21wYXJlZFxuICAgKiBAcmV0dXJucyB0aGlzID49IHZlcnNpb25cbiAgICovXG4gIGd0ZSh2ZXJzaW9uOiBzdHJpbmcgfCBWZXJzaW9uKTogYm9vbGVhbiB7XG4gICAgcmV0dXJuIHRoaXMuZXEodmVyc2lvbikgfHwgdGhpcy5ndCh2ZXJzaW9uKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBMZXNzIFRoYW4gb3IgRXF1YWxcbiAgICogQHBhcmFtIHZlcnNpb24gdGhlIHZlcnNpb24gdG8gYmUgY29tcGFyZWRcbiAgICogQHJldHVybnMgdGhpcyA8PSB2ZXJzaW9uXG4gICAqL1xuICBsdGUodmVyc2lvbjogc3RyaW5nIHwgVmVyc2lvbik6IGJvb2xlYW4ge1xuICAgIHJldHVybiB0aGlzLmVxKHZlcnNpb24pIHx8IHRoaXMubHQodmVyc2lvbik7XG4gIH1cbn1cblxuZXhwb3J0IGRlZmF1bHQgVmVyc2lvbjtcblxuZXhwb3J0IGNvbnN0IHZlcnNpb24yXzQgPSBuZXcgVmVyc2lvbignMi40Jyk7XG5leHBvcnQgY29uc3QgdmVyc2lvbjJfNyA9IG5ldyBWZXJzaW9uKCcyLjcnKTtcbmV4cG9ydCBjb25zdCB2ZXJzaW9uMl85ID0gbmV3IFZlcnNpb24oJzIuOScpO1xuZXhwb3J0IGNvbnN0IHZlcnNpb24yXzEyID0gbmV3IFZlcnNpb24oJzIuMTInKTtcbmV4cG9ydCBjb25zdCB2ZXJzaW9uMl8xNCA9IG5ldyBWZXJzaW9uKCcyLjE0Jyk7XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjUgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cbmV4cG9ydCBjbGFzcyBDYWxsYmFja01hbmFnZXIge1xuICBwcml2YXRlIGlkOiBudW1iZXIgPSAxO1xuICBwcml2YXRlIGNhbGxiYWNrczogTWFwPG51bWJlciwgRnVuY3Rpb24+O1xuICBwcml2YXRlIHRhc2tJZFRvQ2FsbGJhY2tJZHM6IE1hcDxudW1iZXIsIG51bWJlcj47XG5cbiAgY29uc3RydWN0b3IoKSB7XG4gICAgdGhpcy5jYWxsYmFja3MgPSBuZXcgTWFwKCk7XG4gICAgdGhpcy50YXNrSWRUb0NhbGxiYWNrSWRzID0gbmV3IE1hcCgpO1xuICB9XG5cbiAgcHJpdmF0ZSBuZXh0SWQoKTogbnVtYmVyIHwgdW5kZWZpbmVkIHtcbiAgICBpZiAoIXRoaXMuY2FsbGJhY2tzKSB7XG4gICAgICByZXR1cm4gdW5kZWZpbmVkO1xuICAgIH1cbiAgICByZXR1cm4gdGhpcy5pZCsrO1xuICB9XG5cbiAgYWRkQ2FsbGJhY2soY2FsbGJhY2s6IEZ1bmN0aW9uKTogbnVtYmVyIHwgdW5kZWZpbmVkIHtcbiAgICBpZiAoIXRoaXMuY2FsbGJhY2tzKSB7XG4gICAgICByZXR1cm4gdW5kZWZpbmVkO1xuICAgIH1cbiAgICBjb25zdCBpZCA9IHRoaXMubmV4dElkKCk7XG4gICAgaWYgKGlkID09PSB1bmRlZmluZWQpIHtcbiAgICAgIHJldHVybiB1bmRlZmluZWQ7XG4gICAgfVxuICAgIHRoaXMuY2FsbGJhY2tzLnNldChpZCwgY2FsbGJhY2spO1xuICAgIHJldHVybiBpZDtcbiAgfVxuXG4gIGludm9rZUNhbGxiYWNrKG9uY2U6IGJvb2xlYW4sIGtleTogbnVtYmVyLCAuLi5hcmdzOiB1bmtub3duW10pIHtcbiAgICBpZiAoIXRoaXMuY2FsbGJhY2tzKSB7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIGNvbnN0IGNhbGxiYWNrID0gdGhpcy5jYWxsYmFja3MuZ2V0KGtleSk7XG4gICAgaWYgKGNhbGxiYWNrKSB7XG4gICAgICB0cnkge1xuICAgICAgICBjYWxsYmFjay5hcHBseShjYWxsYmFjaywgYXJncyk7XG4gICAgICB9IGZpbmFsbHkge1xuICAgICAgICBpZiAob25jZSkge1xuICAgICAgICAgIHRoaXMucmVtb3ZlQ2FsbGJhY2soa2V5KTtcbiAgICAgICAgfVxuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICBjb25zb2xlLndhcm4oYGNhbGxDYWxsYmFjazogQ2FsbGJhY2sgd2l0aCBJRCAke2tleX0gbm90IGZvdW5kYCk7XG4gICAgfVxuICB9XG5cbiAgcmVtb3ZlQ2FsbGJhY2soa2V5OiBudW1iZXIpIHtcbiAgICBpZiAodGhpcy5jYWxsYmFja3MpIHtcbiAgICAgIGlmICh0eXBlb2Yga2V5ICE9PSAnbnVtYmVyJykge1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgICB0aGlzLmNhbGxiYWNrcy5kZWxldGUoa2V5KTtcbiAgICB9XG4gIH1cblxuICBhZGRUYXNrSWRBbmRDYWxsYmFja0lkKHRhc2tJZDogbnVtYmVyLCBjYWxsYmFja0lkOiBudW1iZXIpIHtcbiAgICBpZiAodGhpcy50YXNrSWRUb0NhbGxiYWNrSWRzKSB7XG4gICAgICB0aGlzLnRhc2tJZFRvQ2FsbGJhY2tJZHMuc2V0KHRhc2tJZCwgY2FsbGJhY2tJZCk7XG4gICAgfVxuICB9XG5cbiAgcmVtb3ZlQ2FsbGJhY2tCeVRhc2tJZCh0YXNrSWQ6IG51bWJlcikge1xuICAgIGlmICh0aGlzLnRhc2tJZFRvQ2FsbGJhY2tJZHMgJiYgdGhpcy5jYWxsYmFja3MpIHtcbiAgICAgIGNvbnN0IGNhbGxiYWNrSWQgPSB0aGlzLnRhc2tJZFRvQ2FsbGJhY2tJZHMuZ2V0KHRhc2tJZCk7XG4gICAgICB0aGlzLnRhc2tJZFRvQ2FsbGJhY2tJZHMuZGVsZXRlKHRhc2tJZCk7XG4gICAgICB0aGlzLnJlbW92ZUNhbGxiYWNrKGNhbGxiYWNrSWQpO1xuICAgIH1cbiAgfVxuICByZW1vdmVUYXNrSWQodGFza0lkOiBudW1iZXIgfCB1bmRlZmluZWQpIHtcbiAgICBpZiAodGhpcy50YXNrSWRUb0NhbGxiYWNrSWRzICYmIHRhc2tJZCAhPT0gdW5kZWZpbmVkKSB7XG4gICAgICB0aGlzLnRhc2tJZFRvQ2FsbGJhY2tJZHMuZGVsZXRlKHRhc2tJZCk7XG4gICAgfVxuICB9XG5cbiAgZGVzdHJveSgpIHtcbiAgICB0aGlzLmNhbGxiYWNrcyA9IHVuZGVmaW5lZDtcbiAgICB0aGlzLnRhc2tJZFRvQ2FsbGJhY2tJZHMgPSB1bmRlZmluZWQ7XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgbmF0aXZlQ29uc29sZSBmcm9tICcuLi8uLi9jb21tb24vdHRDb25zb2xlJztcbmltcG9ydCB7IExZTlhfQ09SRSwgUlVOX1RZUEUgfSBmcm9tICcuLi8uLi9jb21tb24nO1xuaW1wb3J0IHsgQXBwLCBOYXRpdmVBcHAgfSBmcm9tICcuLi8uLi9hcHAnO1xuaW1wb3J0IHsgaXNPYmplY3QgfSBmcm9tICdAbHlueC1qcy9ydW50aW1lLXNoYXJlZCc7XG5pbXBvcnQgeyBCYXNlRXJyb3IsIEx5bnhFcnJvckxldmVsIH0gZnJvbSAnLi9lcnJvcnMnO1xuXG5leHBvcnQgZnVuY3Rpb24gcmVwb3J0RXJyb3IoXG4gIGVycm9yOiBCYXNlRXJyb3IsXG4gIG5hdGl2ZUFwcDogTmF0aXZlQXBwLFxuICBvcHRpb25zPzoge1xuICAgIHJ1blR5cGU/OiBSVU5fVFlQRTtcbiAgICBvcmlnaW5FcnJvcj86IGFueTtcbiAgICBfX3NvdXJjZW1hcF9fcmVsZWFzZV9fPzogc3RyaW5nO1xuICAgIGdldFNvdXJjZU1hcFJlbGVhc2U/OiAodXJsOiBzdHJpbmcpID0+IHN0cmluZztcbiAgICBlcnJvckNvZGU/OiBudW1iZXI7XG4gICAgZXJyb3JMZXZlbD86IEx5bnhFcnJvckxldmVsO1xuICB9XG4pOiB2b2lkIHtcbiAgY29uc3QgeyBvcmlnaW5FcnJvciwgZXJyb3JDb2RlLCBlcnJvckxldmVsLCBydW5UeXBlID0gTFlOWF9DT1JFIH0gPVxuICAgIG9wdGlvbnMgPz8ge307XG4gIG5hdGl2ZUNvbnNvbGUuZXJyb3IoJ1RoZSBmb2xsb3dpbmcgZXJyb3Igb2NjdXJyZWQgaW4gdGhlIEpTUnVudGltZTonKTtcbiAgbmF0aXZlQ29uc29sZS5lcnJvcihgJHtlcnJvcj8ubWVzc2FnZX1cXG4ke2Vycm9yPy5zdGFja31gKTtcbiAgZXJyb3IuY2F1c2UgPSBpc09iamVjdChlcnJvci5jYXVzZSlcbiAgICA/IEpTT04uc3RyaW5naWZ5KGVycm9yLmNhdXNlKVxuICAgIDogZXJyb3IuY2F1c2U7XG4gIHRyeSB7XG4gICAgbmF0aXZlQXBwLnJlcG9ydEV4Y2VwdGlvbihlcnJvciwge1xuICAgICAgLi4ucnVuVHlwZSxcbiAgICAgIGJ1aWxkVmVyc2lvbjogX19CVUlMRF9WRVJTSU9OX18sXG4gICAgICB2ZXJzaW9uQ29kZTogX19WRVJTSU9OX18sXG4gICAgICBlcnJvckNvZGUsXG4gICAgICBlcnJvckxldmVsLFxuICAgIH0pO1xuICB9IGNhdGNoIChlcnJvcikge1xuICAgIG5hdGl2ZUNvbnNvbGUuZXJyb3IoJ3JlcG9ydEVycm9yIGVycjpcXG4nLCBlcnJvcik7XG4gIH1cbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGxlZ2FjeVJlcG9ydEVycm9yKFxuICBlcnJvcjogQmFzZUVycm9yLFxuICBuYXRpdmVBcHA6IE5hdGl2ZUFwcCxcbiAgcnVuVHlwZSA9IExZTlhfQ09SRSxcbiAgb3JpZ2luRXJyb3I/OiBhbnksXG4gIHByb3h5PzogQXBwXG4pIHtcbiAgcmV0dXJuIHJlcG9ydEVycm9yKGVycm9yLCBuYXRpdmVBcHAsIHtcbiAgICBydW5UeXBlLFxuICAgIG9yaWdpbkVycm9yLFxuICAgIF9fc291cmNlbWFwX19yZWxlYXNlX186IHByb3h5Ll9fc291cmNlbWFwX19yZWxlYXNlX18sXG4gIH0pO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gcmVwb3J0VGhyb3dFcnJvcih7XG4gIGVycm9yLFxuICBuYXRpdmVBcHAsXG4gIHJ1blR5cGUgPSBMWU5YX0NPUkUsXG4gIHJhd0Vycm9yLFxuICBfX3NvdXJjZW1hcF9fcmVsZWFzZV9fLFxuICBnZXRTb3VyY2VNYXBSZWxlYXNlLFxufToge1xuICBlcnJvcjogQmFzZUVycm9yO1xuICBuYXRpdmVBcHA6IE5hdGl2ZUFwcDtcbiAgcnVuVHlwZT86IFJVTl9UWVBFO1xuICByYXdFcnJvcjogb2JqZWN0O1xuICBfX3NvdXJjZW1hcF9fcmVsZWFzZV9fPzogc3RyaW5nO1xuICBnZXRTb3VyY2VNYXBSZWxlYXNlPzogKHVybDogc3RyaW5nKSA9PiBzdHJpbmc7XG59KTogdm9pZCB7XG4gIHJlcG9ydEVycm9yKGVycm9yLCBuYXRpdmVBcHAsIHtcbiAgICBvcmlnaW5FcnJvcjogcmF3RXJyb3IsXG4gICAgcnVuVHlwZSxcbiAgICBfX3NvdXJjZW1hcF9fcmVsZWFzZV9fLFxuICAgIGdldFNvdXJjZU1hcFJlbGVhc2UsXG4gIH0pO1xufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCBuYXRpdmVDb25zb2xlIGZyb20gJy4uLy4uL2NvbW1vbi90dENvbnNvbGUnO1xuaW1wb3J0IHsgaXNGdW5jdGlvbiwgbm9vcCB9IGZyb20gJ0BseW54LWpzL3J1bnRpbWUtc2hhcmVkJztcbmltcG9ydCB7IEVycm9yS2luZCwgVXNlclJ1bnRpbWVFcnJvciwgSW50ZXJuYWxSdW50aW1lRXJyb3IgfSBmcm9tICcuL2Vycm9ycyc7XG5pbXBvcnQgeyByZXBvcnRFcnJvciB9IGZyb20gJy4vcmVwb3J0LWVycm9yJztcbmltcG9ydCB7IFJVTl9UWVBFLCBMWU5YX0NPUkUgfSBmcm9tICcuLi8uLi9jb21tb24nO1xuaW1wb3J0IHsgTmF0aXZlQXBwIH0gZnJvbSAnLi4vLi4vYXBwJztcblxudHlwZSBJbnN0YW5jZSA9IHtcbiAgX25hdGl2ZUFwcDogTmF0aXZlQXBwO1xuICBvbkVycm9yPzogKGVycm9yOiBzdHJpbmcsIGVycm9yT2JqOiBhbnkpID0+IHZvaWQ7XG4gIF9fc291cmNlbWFwX19yZWxlYXNlX18/OiBzdHJpbmc7XG4gIGdldFNvdXJjZU1hcFJlbGVhc2U/OiAodXJsOiBzdHJpbmcpID0+IHN0cmluZztcbn07XG5cbmV4cG9ydCBmdW5jdGlvbiB3cmFwVXNlckZ1bmN0aW9uPFQgZXh0ZW5kcyBBbnlGdW5jdGlvbj4oXG4gIGRlc2M6IHN0cmluZyxcbiAgaW5zdGFuY2U6IEluc3RhbmNlLFxuICBjYWxsYmFjazogVCxcbiAgcnVuVHlwZTogUlVOX1RZUEUgPSBMWU5YX0NPUkVcbik6IFQge1xuICBpZiAoIWlzRnVuY3Rpb24oY2FsbGJhY2spKSByZXR1cm4gbm9vcCBhcyBUO1xuICByZXR1cm4gd3JhcEZ1bmN0aW9uKCdVU0VSX0VSUk9SJywgZGVzYywgY2FsbGJhY2ssIGluc3RhbmNlLCBydW5UeXBlKSBhcyBUO1xufVxuZnVuY3Rpb24gd3JhcEZ1bmN0aW9uKFxuICBlcnJvcktpbmQ6IEVycm9yS2luZCA9ICdJTlRFUk5BTF9FUlJPUicsXG4gIGRlc2M6IHN0cmluZyxcbiAgY2FsbGJhY2s6IEFueUZ1bmN0aW9uLFxuICBpbnN0YW5jZTogSW5zdGFuY2UsXG4gIHJ1blR5cGU6IFJVTl9UWVBFXG4pIHtcbiAgcmV0dXJuIGZ1bmN0aW9uIHdyYXBGdW5jdGlvbklubmVyKC4uLmFyZ3MpIHtcbiAgICB0cnkge1xuICAgICAgcmV0dXJuIGNhbGxiYWNrLmFwcGx5KHRoaXMsIGFyZ3MpO1xuICAgIH0gY2F0Y2ggKGVycm9yKSB7XG4gICAgICBjb25zdCBtZXNzYWdlID0gYCR7ZGVzY30gXFxuJHtlcnJvci5tZXNzYWdlfWA7XG4gICAgICBpZiAoXG4gICAgICAgIGNhbGxiYWNrLm5hbWUgIT09ICdvbkVycm9yJyAmJlxuICAgICAgICB0eXBlb2YgaW5zdGFuY2Uub25FcnJvciA9PT0gJ2Z1bmN0aW9uJ1xuICAgICAgKSB7XG4gICAgICAgIGluc3RhbmNlLm9uRXJyb3IoXG4gICAgICAgICAgYENhcmQgJHtjYWxsYmFjay5uYW1lfSBleGVjIGVycm9yOiR7bWVzc2FnZX1cXG4ke2Vycm9yLnN0YWNrfWAsXG4gICAgICAgICAgZXJyb3JcbiAgICAgICAgKTtcbiAgICAgIH1cbiAgICAgIGNvbnN0IGVyciA9XG4gICAgICAgIGVycm9yS2luZCA9PT0gJ0lOVEVSTkFMX0VSUk9SJ1xuICAgICAgICAgID8gbmV3IEludGVybmFsUnVudGltZUVycm9yKG1lc3NhZ2UsIGVycm9yLnN0YWNrKVxuICAgICAgICAgIDogbmV3IFVzZXJSdW50aW1lRXJyb3IobWVzc2FnZSwgZXJyb3Iuc3RhY2spO1xuICAgICAgbmF0aXZlQ29uc29sZS5sb2coYHdyYXBFcnJvci0ke2Rlc2N9YCwgZXJyKTtcbiAgICAgIHJlcG9ydEVycm9yKGVyciwgaW5zdGFuY2UuX25hdGl2ZUFwcCwge1xuICAgICAgICBydW5UeXBlLFxuICAgICAgICBfX3NvdXJjZW1hcF9fcmVsZWFzZV9fOiBpbnN0YW5jZS5fX3NvdXJjZW1hcF9fcmVsZWFzZV9fLFxuICAgICAgICBnZXRTb3VyY2VNYXBSZWxlYXNlOiBpbnN0YW5jZS5nZXRTb3VyY2VNYXBSZWxlYXNlLFxuICAgICAgfSk7XG4gICAgfVxuICB9O1xufVxuZXhwb3J0IGZ1bmN0aW9uIHdyYXBJbm5lckZ1bmN0aW9uPFQgZXh0ZW5kcyBBbnlGdW5jdGlvbj4oXG4gIGRlc2M6IHN0cmluZyxcbiAgaW5zdGFuY2U6IEluc3RhbmNlLFxuICBjYWxsYmFjazogVCxcbiAgcnVuVHlwZTogUlVOX1RZUEUgPSBMWU5YX0NPUkVcbik6IFQge1xuICBpZiAoIWlzRnVuY3Rpb24oY2FsbGJhY2spKSByZXR1cm4gbm9vcCBhcyBUO1xuICByZXR1cm4gd3JhcEZ1bmN0aW9uKCdJTlRFUk5BTF9FUlJPUicsIGRlc2MsIGNhbGxiYWNrLCBpbnN0YW5jZSwgcnVuVHlwZSkgYXMgVDtcbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBpc0Vycm9yLCBpc1N0cmluZyB9IGZyb20gJ0BseW54LWpzL3J1bnRpbWUtc2hhcmVkJztcbmltcG9ydCB7IEJhc2VBcHAsIE5hdGl2ZUFwcCB9IGZyb20gJy4uLy4uL2FwcCc7XG5pbXBvcnQgeyBhbG9nIH0gZnJvbSAnLi4vLi4vY29tbW9uL2xvZyc7XG5cbmV4cG9ydCBjbGFzcyBSZXBvcnRlciB7XG4gIGNvbnN0cnVjdG9yKFxuICAgIHByaXZhdGUgZ2V0QXBwOiAoKSA9PiBCYXNlQXBwLFxuICAgIHByaXZhdGUgcmVhZG9ubHkgZ2V0TmF0aXZlQXBwOiAoKSA9PiBOYXRpdmVBcHBcbiAgKSB7XG4gICAgdGhpcy5nZXRBcHAgPSBnZXRBcHA7XG4gICAgdGhpcy5nZXROYXRpdmVBcHAgPSBnZXROYXRpdmVBcHA7XG4gIH1cblxuICBwdWJsaWMgcmViaW5kKGdldEFwcDogKCkgPT4gQmFzZUFwcCkge1xuICAgIHRoaXMuZ2V0QXBwID0gZ2V0QXBwO1xuICB9XG5cbiAgLy8gLyoqXG4gIC8vICAqIGtleSB1cmwgLT4gdmFsdWUgc291cmNlbWFwXG4gIC8vICAqIHN1cHBvcnQgZGlmZmVyZW50IHNvdXJjZW1hcCBmb3IgZXh0ZXJuYWwganNcbiAgLy8gICovXG4gIC8vIHNvdXJjZW1hcHM6IFJlY29yZDxzdHJpbmcsIHN0cmluZz4gPSB7fTtcblxuICAvKipcbiAgICogU2V0IHNvdXJjZW1hcCByZWxlYXNlIHdpdGggYSBuZXdseSB0aHJvd24gZXJyb3JcbiAgICogQHBhcmFtIHtFcnJvcn0gZXJyb3JcbiAgICogVGhlIGVycm9yIHRocm93biBmcm9tIHRoZSBmaWxlIHRoYXQgd2FudHMgdG8gc2V0IHNvdXJjZW1hcCByZWxlYXNlLlxuICAgKiBUaGUgdG9wIGZyYW1lIG9mIGBlcnJvci5zdGFja2AgKiptdXN0IGJlKiogdGhlIGZpbGVuYW1lLlxuICAgKiBUaGUgYGVycm9yLm5hbWVgICoqbXVzdCBiZSoqIGAnTHlueEdldFNvdXJjZU1hcFJlbGVhc2VFcnJvcidgLlxuICAgKiBUaGUgYGVycm9yLm1lc3NhZ2VgICoqbXVzdCBiZSoqIHRoZSBzb3VyY2VtYXAgcmVsZWFzZS5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogKGZ1bmN0aW9uICgpIHtcbiAgICogICB0cnkge1xuICAgKiAgICAgdGhyb3cgbmV3IEVycm9yKHNvdXJjZW1hcFJlbGVhc2UpO1xuICAgKiAgIH0gY2F0Y2ggKGUpIHtcbiAgICogICAgIGUubmFtZSA9ICdMeW54R2V0U291cmNlTWFwUmVsZWFzZUVycm9yJztcbiAgICogICAgIHR0LnNldFNvdXJjZU1hcFJlbGVhc2UoZSk7XG4gICAqICAgfVxuICAgKiB9KSgpXG4gICAqL1xuICBzZXRTb3VyY2VNYXBSZWxlYXNlID0gKGVycm9yOiBFcnJvcikgPT4ge1xuICAgIGlmIChcbiAgICAgIGlzRXJyb3IoZXJyb3IpICYmXG4gICAgICBlcnJvci5uYW1lID09PSBCYXNlQXBwLmtHZXRTb3VyY2VNYXBSZWxlYXNlRXJyb3JOYW1lICYmXG4gICAgICBpc1N0cmluZyhlcnJvci5tZXNzYWdlKSAmJlxuICAgICAgaXNTdHJpbmcoZXJyb3Iuc3RhY2spXG4gICAgKSB7XG4gICAgICB0aGlzLmdldE5hdGl2ZUFwcCgpLl9fU2V0U291cmNlTWFwUmVsZWFzZSh7XG4gICAgICAgIG5hbWU6IGVycm9yLm5hbWUsXG4gICAgICAgIG1lc3NhZ2U6IGVycm9yLm1lc3NhZ2UsXG4gICAgICAgIHN0YWNrOiBlcnJvci5zdGFjayxcbiAgICAgIH0pO1xuICAgICAgcmV0dXJuO1xuICAgIH1cbiAgICBhbG9nKGBzZXRTb3VyY2VNYXBSZWxlYXNlIGZhaWxlZCB3aXRoIGVycm9yOiAke0pTT04uc3RyaW5naWZ5KGVycm9yKX1gKTtcbiAgfTtcblxuICBnZXRTb3VyY2VNYXBSZWxlYXNlID0gKHVybDogc3RyaW5nKTogc3RyaW5nID0+IHtcbiAgICBsZXQgcmV0ID0gdGhpcy5nZXROYXRpdmVBcHAoKS5fX0dldFNvdXJjZU1hcFJlbGVhc2UodXJsKTtcbiAgICBpZiAoIXJldCkge1xuICAgICAgcmV0ID0gdGhpcy5nZXROYXRpdmVBcHAoKS5fX0dldFNvdXJjZU1hcFJlbGVhc2UoXG4gICAgICAgIEJhc2VBcHAua0RlZmF1bHRTb3VyY2VNYXBVUkxcbiAgICAgICk7XG4gICAgfVxuICAgIHJldHVybiByZXQ7XG4gIH07XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IHsgQW5pbWF0aW9uIGFzIElBbmltYXRpb24gfSBmcm9tICdAbHlueC1qcy90eXBlcyc7XG5pbXBvcnQgeyBLZXlmcmFtZUVmZmVjdCB9IGZyb20gJy4vZWZmZWN0JztcblxuZXhwb3J0IGNvbnN0IGVudW0gQW5pbWF0aW9uT3BlcmF0aW9uIHtcbiAgU1RBUlQgPSAwLFxuICBQTEFZLFxuICBQQVVTRSxcbiAgQ0FOQ0VMLFxuICBGSU5JU0gsXG59XG5cbmV4cG9ydCBjbGFzcyBBbmltYXRpb24gaW1wbGVtZW50cyBJQW5pbWF0aW9uIHtcbiAgc3RhdGljIGNvdW50OiBudW1iZXIgPSAwO1xuICBwdWJsaWMgcmVhZG9ubHkgZWZmZWN0OiBLZXlmcmFtZUVmZmVjdDtcbiAgcHVibGljIHJlYWRvbmx5IGlkOiBzdHJpbmc7XG5cbiAgY29uc3RydWN0b3IoZWZmZWN0OiBLZXlmcmFtZUVmZmVjdCkge1xuICAgIHRoaXMuZWZmZWN0ID0gZWZmZWN0O1xuICAgIHRoaXMuaWQgPSAnX19seW54LWlubmVyLWpzLWFuaW1hdGlvbi0nICsgQW5pbWF0aW9uLmNvdW50Kys7XG4gIH1cblxuICBjYW5jZWwoKTogdm9pZCB7XG4gICAgdGhpcy5lZmZlY3QudGFyZ2V0LmNhbmNlbEFuaW1hdGUodGhpcyk7XG4gIH1cblxuICBwYXVzZSgpOiB2b2lkIHtcbiAgICB0aGlzLmVmZmVjdC50YXJnZXQucGF1c2VBbmltYXRlKHRoaXMpO1xuICB9XG5cbiAgcGxheSgpOiB2b2lkIHtcbiAgICB0aGlzLmVmZmVjdC50YXJnZXQucGxheUFuaW1hdGUodGhpcyk7XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQge1xuICBLZXlmcmFtZUVmZmVjdCBhcyBJS2V5ZnJhbWVFZmZlY3QsXG4gIEtleWZyYW1lRWZmZWN0VjIgYXMgSUtleWZyYW1lRWZmZWN0VjIsXG59IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCBFbGVtZW50IGZyb20gJy4uL2VsZW1lbnQnO1xuXG5leHBvcnQgY2xhc3MgS2V5ZnJhbWVFZmZlY3QgaW1wbGVtZW50cyBJS2V5ZnJhbWVFZmZlY3Qge1xuICBwdWJsaWMgcmVhZG9ubHkgdGFyZ2V0OiBFbGVtZW50O1xuICBwdWJsaWMgcmVhZG9ubHkga2V5ZnJhbWVzOiBBcnJheTxSZWNvcmQ8c3RyaW5nLCBhbnk+PjtcbiAgcHVibGljIHJlYWRvbmx5IG9wdGlvbnM6IFJlY29yZDxzdHJpbmcsIGFueT47XG5cbiAgY29uc3RydWN0b3IoXG4gICAgdGFyZ2V0OiBFbGVtZW50LFxuICAgIGtleWZyYW1lczogQXJyYXk8UmVjb3JkPHN0cmluZywgYW55Pj4sXG4gICAgb3B0aW9uczogUmVjb3JkPHN0cmluZywgYW55PlxuICApIHtcbiAgICB0aGlzLnRhcmdldCA9IHRhcmdldDtcbiAgICB0aGlzLmtleWZyYW1lcyA9IGtleWZyYW1lcztcbiAgICB0aGlzLm9wdGlvbnMgPSBvcHRpb25zO1xuICB9XG59XG5cbmV4cG9ydCBjbGFzcyBLZXlmcmFtZUVmZmVjdFYyIGltcGxlbWVudHMgSUtleWZyYW1lRWZmZWN0VjIge1xuICBwdWJsaWMgcmVhZG9ubHkgdGFyZ2V0PzogRWxlbWVudDtcbiAgcHVibGljIHJlYWRvbmx5IGtleWZyYW1lczogQXJyYXk8UmVjb3JkPHN0cmluZywgYW55Pj47XG4gIHB1YmxpYyByZWFkb25seSBvcHRpb25zOiBSZWNvcmQ8c3RyaW5nLCBhbnk+O1xuXG4gIGNvbnN0cnVjdG9yKFxuICAgIGtleWZyYW1lczogQXJyYXk8UmVjb3JkPHN0cmluZywgYW55Pj4sXG4gICAgb3B0aW9uczogUmVjb3JkPHN0cmluZywgYW55PlxuICApIHtcbiAgICB0aGlzLmtleWZyYW1lcyA9IGtleWZyYW1lcztcbiAgICB0aGlzLm9wdGlvbnMgPSBvcHRpb25zO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjUgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IHsgQW5pbWF0aW9uVjIgYXMgSUFuaW1hdGlvbiB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCB7IEtleWZyYW1lRWZmZWN0VjIgfSBmcm9tICcuL2VmZmVjdCc7XG5cbmV4cG9ydCBjbGFzcyBBbmltYXRpb25WMiBpbXBsZW1lbnRzIElBbmltYXRpb24ge1xuICBwdWJsaWMgcmVhZG9ubHkgZWZmZWN0OiBLZXlmcmFtZUVmZmVjdFYyO1xuICBwdWJsaWMgcmVhZG9ubHkgaWQ6IHN0cmluZztcblxuICBjb25zdHJ1Y3RvcihcbiAgICBpZDogc3RyaW5nLFxuICAgIGtleWZyYW1lczogQXJyYXk8UmVjb3JkPHN0cmluZywgYW55Pj4sXG4gICAgb3B0aW9uczogUmVjb3JkPHN0cmluZywgYW55PlxuICApIHtcbiAgICB0aGlzLmlkID0gaWQ7XG4gICAgdGhpcy5lZmZlY3QgPSBuZXcgS2V5ZnJhbWVFZmZlY3RWMihrZXlmcmFtZXMsIG9wdGlvbnMpO1xuICB9XG59XG4iLCAiaW1wb3J0IHsgQW5pbWF0aW9uLCBBbmltYXRpb25PcGVyYXRpb24sIEtleWZyYW1lRWZmZWN0IH0gZnJvbSAnLi4vYW5pbWF0aW9uJztcbmltcG9ydCB7IEx5bnggfSBmcm9tICcuLi8uLi9seW54JztcblxuLyoqXG4gKiBOYXRpdmUgRWxlbWVudCwgSGVsZCBieSB7QGxpbmsgRWxlbWVudH0gYW5kIGludGVyYWN0aW5nIHdpdGggbmF0aXZlLlxuICovXG5leHBvcnQgaW50ZXJmYWNlIE5hdGl2ZUVsZW1lbnRQcm94eSB7XG4gIGFuaW1hdGUoXG4gICAgb3BlcmF0aW9uOiBBbmltYXRpb25PcGVyYXRpb24sXG4gICAgaWQ6IHN0cmluZyxcbiAgICBrZXlmcmFtZXM/OiBSZWNvcmQ8c3RyaW5nLCBhbnk+W10sXG4gICAgdGltaW5nT3B0aW9ucz86IFJlY29yZDxzdHJpbmcsIGFueT5cbiAgKTogdm9pZDtcbiAgc2V0UHJvcGVydHkocHJvcHNOYW1lOiBzdHJpbmcsIHByb3BzVmFsdWU6IHN0cmluZyk6IHZvaWQ7XG4gIHNldFByb3BlcnR5KHByb3BzOiBSZWNvcmQ8c3RyaW5nLCBzdHJpbmc+KTogdm9pZDtcbn1cblxuZXhwb3J0IGRlZmF1bHQgY2xhc3MgRWxlbWVudCB7XG4gIHByaXZhdGUgcmVhZG9ubHkgX3Jvb3Q6IHN0cmluZztcbiAgcHJpdmF0ZSByZWFkb25seSBfaWRTZWxlY3Rvcjogc3RyaW5nO1xuICBwcml2YXRlIHJlYWRvbmx5IF9seW54OiBMeW54O1xuICBwcml2YXRlIF9lbGVtZW50OiBOYXRpdmVFbGVtZW50UHJveHk7XG5cbiAgY29uc3RydWN0b3Iocm9vdDogc3RyaW5nLCBpZDogc3RyaW5nLCBseW54UHJveHk6IEx5bngpIHtcbiAgICB0aGlzLl9yb290ID0gcm9vdDtcbiAgICB0aGlzLl9pZFNlbGVjdG9yID0gJyMnICsgaWQ7XG4gICAgdGhpcy5fbHlueCA9IGx5bnhQcm94eTtcbiAgICB0aGlzLl9lbGVtZW50ID0gdW5kZWZpbmVkO1xuICB9XG5cbiAgcHJpdmF0ZSBlbnN1cmVFbGVtZW50KCkge1xuICAgIGlmICghdGhpcy5fZWxlbWVudCkge1xuICAgICAgdGhpcy5fZWxlbWVudCA9IHRoaXMuX2x5bnguY3JlYXRlRWxlbWVudCh0aGlzLl9yb290LCB0aGlzLl9pZFNlbGVjdG9yKTtcbiAgICB9XG4gIH1cblxuICAvLyBrZXlmcmFtZXM6IHNlZSBodHRwczovL2RldmVsb3Blci5tb3ppbGxhLm9yZy9lbi1VUy9kb2NzL1dlYi9BUEkvV2ViX0FuaW1hdGlvbnNfQVBJL0tleWZyYW1lX0Zvcm1hdHNcbiAgLy8gIEVpdGhlciBhbiBhcnJheSBvZiBrZXlmcmFtZSBvYmplY3RzLCBvciBhIGtleWZyYW1lIG9iamVjdCB3aG9zZSBwcm9wZXJ0eSBhcmUgYXJyYXlzIG9mIHZhbHVlcyB0byBpdGVyYXRlIG92ZXIuIFNlZSBLZXlmcmFtZSBGb3JtYXRzIGZvciBtb3JlIGRldGFpbHMuXG4gIC8vXG4gIC8vIHRpbWluZ09wdGlvbnM6IHNlZSBodHRwczovL2RldmVsb3Blci5tb3ppbGxhLm9yZy9lbi1VUy9kb2NzL1dlYi9BUEkvRWxlbWVudC9hbmltYXRlXG4gIC8vICBpZCBPcHRpb25hbDogQSBwcm9wZXJ0eSB1bmlxdWUgdG8gYW5pbWF0ZSgpOiBhIERPTVN0cmluZyB3aXRoIHdoaWNoIHRvIHJlZmVyZW5jZSB0aGUgYW5pbWF0aW9uLlxuICAvLyAgZGVsYXkgT3B0aW9uYWw6IFRoZSBudW1iZXIgb2YgbWlsbGlzZWNvbmRzIHRvIGRlbGF5IHRoZSBzdGFydCBvZiB0aGUgYW5pbWF0aW9uLiBEZWZhdWx0cyB0byAwLlxuICAvLyAgZGlyZWN0aW9uIE9wdGlvbmFsOiBXaGV0aGVyIHRoZSBhbmltYXRpb24gcnVucyBmb3J3YXJkcyAobm9ybWFsKSwgYmFja3dhcmRzIChyZXZlcnNlKSwgc3dpdGNoZXMgZGlyZWN0aW9uIGFmdGVyIGVhY2ggaXRlcmF0aW9uIChhbHRlcm5hdGUpLCBvciBydW5zIGJhY2t3YXJkcyBhbmQgc3dpdGNoZXMgZGlyZWN0aW9uIGFmdGVyIGVhY2ggaXRlcmF0aW9uIChhbHRlcm5hdGUtcmV2ZXJzZSkuIERlZmF1bHRzIHRvIFwibm9ybWFsXCIuXG4gIC8vICBkdXJhdGlvbiBPcHRpb25hbDogVGhlIG51bWJlciBvZiBtaWxsaXNlY29uZHMgZWFjaCBpdGVyYXRpb24gb2YgdGhlIGFuaW1hdGlvbiB0YWtlcyB0byBjb21wbGV0ZS4gRGVmYXVsdHMgdG8gMC4gQWx0aG91Z2ggdGhpcyBpcyB0ZWNobmljYWxseSBvcHRpb25hbCwga2VlcCBpbiBtaW5kIHRoYXQgeW91ciBhbmltYXRpb24gd2lsbCBub3QgcnVuIGlmIHRoaXMgdmFsdWUgaXMgMC5cbiAgLy8gIGVhc2luZyBPcHRpb25hbDogVGhlIHJhdGUgb2YgdGhlIGFuaW1hdGlvbidzIGNoYW5nZSBvdmVyIHRpbWUuIEFjY2VwdHMgdGhlIHByZS1kZWZpbmVkIHZhbHVlcyBcImxpbmVhclwiLCBcImVhc2VcIiwgXCJlYXNlLWluXCIsIFwiZWFzZS1vdXRcIiwgYW5kIFwiZWFzZS1pbi1vdXRcIiwgb3IgYSBjdXN0b20gXCJjdWJpYy1iZXppZXJcIiB2YWx1ZSBsaWtlIFwiY3ViaWMtYmV6aWVyKDAuNDIsIDAsIDAuNTgsIDEpXCIuIERlZmF1bHRzIHRvIFwibGluZWFyXCIuXG4gIC8vICBlbmREZWxheSBPcHRpb25hbDogVGhlIG51bWJlciBvZiBtaWxsaXNlY29uZHMgdG8gZGVsYXkgYWZ0ZXIgdGhlIGVuZCBvZiBhbiBhbmltYXRpb24uIFRoaXMgaXMgcHJpbWFyaWx5IG9mIHVzZSB3aGVuIHNlcXVlbmNpbmcgYW5pbWF0aW9ucyBiYXNlZCBvbiB0aGUgZW5kIHRpbWUgb2YgYW5vdGhlciBhbmltYXRpb24uIERlZmF1bHRzIHRvIDAuXG4gIC8vICBmaWxsIE9wdGlvbmFsOiBEaWN0YXRlcyB3aGV0aGVyIHRoZSBhbmltYXRpb24ncyBlZmZlY3RzIHNob3VsZCBiZSByZWZsZWN0ZWQgYnkgdGhlIGVsZW1lbnQocykgcHJpb3IgdG8gcGxheWluZyAoXCJiYWNrd2FyZHNcIiksIHJldGFpbmVkIGFmdGVyIHRoZSBhbmltYXRpb24gaGFzIGNvbXBsZXRlZCBwbGF5aW5nIChcImZvcndhcmRzXCIpLCBvciBib3RoLiBEZWZhdWx0cyB0byBcIm5vbmVcIi5cbiAgLy8gIGl0ZXJhdGlvblN0YXJ0IE9wdGlvbmFsOiBEZXNjcmliZXMgYXQgd2hhdCBwb2ludCBpbiB0aGUgaXRlcmF0aW9uIHRoZSBhbmltYXRpb24gc2hvdWxkIHN0YXJ0LiAwLjUgd291bGQgaW5kaWNhdGUgc3RhcnRpbmcgaGFsZndheSB0aHJvdWdoIHRoZSBmaXJzdCBpdGVyYXRpb24gZm9yIGV4YW1wbGUsIGFuZCB3aXRoIHRoaXMgdmFsdWUgc2V0LCBhbiBhbmltYXRpb24gd2l0aCAyIGl0ZXJhdGlvbnMgd291bGQgZW5kIGhhbGZ3YXkgdGhyb3VnaCBhIHRoaXJkIGl0ZXJhdGlvbi4gRGVmYXVsdHMgdG8gMC4wLlxuICAvLyBpdGVyYXRpb25zIE9wdGlvbmFsOiBUaGUgbnVtYmVyIG9mIHRpbWVzIHRoZSBhbmltYXRpb24gc2hvdWxkIHJlcGVhdC4gRGVmYXVsdHMgdG8gMSwgYW5kIGNhbiBhbHNvIHRha2UgYSB2YWx1ZSBvZiBJbmZpbml0eSB0byBtYWtlIGl0IHJlcGVhdCBmb3IgYXMgbG9uZyBhcyB0aGUgZWxlbWVudCBleGlzdHMuXG4gIGFuaW1hdGUoXG4gICAga2V5ZnJhbWVzOiBBcnJheTxSZWNvcmQ8c3RyaW5nLCBhbnk+PixcbiAgICB0aW1pbmdPcHRpb25zOiBSZWNvcmQ8c3RyaW5nLCBhbnk+XG4gICk6IEFuaW1hdGlvbiB7XG4gICAgdGhpcy5lbnN1cmVFbGVtZW50KCk7XG4gICAgbGV0IGFuaSA9IG5ldyBBbmltYXRpb24obmV3IEtleWZyYW1lRWZmZWN0KHRoaXMsIGtleWZyYW1lcywgdGltaW5nT3B0aW9ucykpO1xuICAgIHRoaXMuX2VsZW1lbnQuYW5pbWF0ZSgwLCBhbmkuaWQsIGtleWZyYW1lcywgdGltaW5nT3B0aW9ucyk7XG4gICAgcmV0dXJuIGFuaTtcbiAgfVxuXG4gIHBsYXlBbmltYXRlKGFuaTogQW5pbWF0aW9uKTogdm9pZCB7XG4gICAgdGhpcy5fZWxlbWVudC5hbmltYXRlKDEsIGFuaS5pZCwgdW5kZWZpbmVkLCB1bmRlZmluZWQpO1xuICB9XG5cbiAgcGF1c2VBbmltYXRlKGFuaTogQW5pbWF0aW9uKTogdm9pZCB7XG4gICAgdGhpcy5fZWxlbWVudC5hbmltYXRlKDIsIGFuaS5pZCwgdW5kZWZpbmVkLCB1bmRlZmluZWQpO1xuICB9XG5cbiAgY2FuY2VsQW5pbWF0ZShhbmk6IEFuaW1hdGlvbik6IHZvaWQge1xuICAgIHRoaXMuX2VsZW1lbnQuYW5pbWF0ZSgzLCBhbmkuaWQsIHVuZGVmaW5lZCwgdW5kZWZpbmVkKTtcbiAgfVxuXG4gIGZpbmlzaEFuaW1hdGUoYW5pOiBBbmltYXRpb24pOiB2b2lkIHtcbiAgICB0aGlzLl9lbGVtZW50LmFuaW1hdGUoNCwgYW5pLmlkLCB1bmRlZmluZWQsIHVuZGVmaW5lZCk7XG4gIH1cblxuICBzZXRQcm9wZXJ0eShcbiAgICBwcm9wc09iajogc3RyaW5nIHwgUmVjb3JkPHN0cmluZywgc3RyaW5nPixcbiAgICBwcm9wc1ZhbD86IHN0cmluZ1xuICApOiB2b2lkIHtcbiAgICB0aGlzLmVuc3VyZUVsZW1lbnQoKTtcbiAgICBpZiAodHlwZW9mIHByb3BzT2JqID09PSAnc3RyaW5nJyAmJiB0eXBlb2YgcHJvcHNWYWwgPT09ICdzdHJpbmcnKSB7XG4gICAgICB0aGlzLl9lbGVtZW50LnNldFByb3BlcnR5KHtcbiAgICAgICAgW3Byb3BzT2JqXTogcHJvcHNWYWwsXG4gICAgICB9KTtcbiAgICB9IGVsc2UgaWYgKHR5cGVvZiBwcm9wc09iaiA9PT0gJ29iamVjdCcpIHtcbiAgICAgIHRoaXMuX2VsZW1lbnQuc2V0UHJvcGVydHkocHJvcHNPYmopO1xuICAgIH0gZWxzZSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoXG4gICAgICAgIGBzZXRQcm9wZXJ0eSdzIHBhcmFtIG11c3QgYmUgc3RyaW5nIG9yIG9iamVjdC4gV2hpbGUgY3VycmVudCB0eXBlIGlzICR7dHlwZW9mIHByb3BzT2JqfSBhbmQgJHt0eXBlb2YgcHJvcHNWYWx9LmBcbiAgICAgICk7XG4gICAgfVxuICB9XG59XG4iLCAiaW1wb3J0IEVsZW1lbnQgZnJvbSAnLi9lbGVtZW50JztcbmV4cG9ydCBkZWZhdWx0IEVsZW1lbnQ7XG5cbmV4cG9ydCB0eXBlIHsgTmF0aXZlRWxlbWVudFByb3h5IH0gZnJvbSAnLi9lbGVtZW50JztcbiIsICJ0eXBlIFR5cGVkQXJyYXkgPVxuICB8IEludDhBcnJheVxuICB8IFVpbnQ4QXJyYXlcbiAgfCBVaW50OENsYW1wZWRBcnJheVxuICB8IEludDE2QXJyYXlcbiAgfCBVaW50MTZBcnJheVxuICB8IEludDMyQXJyYXlcbiAgfCBVaW50MzJBcnJheVxuICB8IEZsb2F0MzJBcnJheVxuICB8IEZsb2F0NjRBcnJheTtcblxuZXhwb3J0IGNsYXNzIFRleHREZWNvZGVyIHtcbiAgY29uc3RydWN0b3IoKSB7fVxuXG4gIGRlY29kZShidWZmZXI6IEFycmF5QnVmZmVyIHwgVHlwZWRBcnJheSB8IERhdGFWaWV3KTogc3RyaW5nIHtcbiAgICBpZiAoYnVmZmVyLmJ5dGVMZW5ndGggPT09IDApIHtcbiAgICAgIHJldHVybiAnJztcbiAgICB9XG5cbiAgICBpZiAoYnVmZmVyIGluc3RhbmNlb2YgRGF0YVZpZXcpIHtcbiAgICAgIGJ1ZmZlciA9IGJ1ZmZlci5idWZmZXIuc2xpY2UoXG4gICAgICAgIGJ1ZmZlci5ieXRlT2Zmc2V0LFxuICAgICAgICBidWZmZXIuYnl0ZU9mZnNldCArIGJ1ZmZlci5ieXRlTGVuZ3RoXG4gICAgICApO1xuICAgIH0gZWxzZSBpZiAoQXJyYXlCdWZmZXIuaXNWaWV3KGJ1ZmZlcikpIHtcbiAgICAgIGJ1ZmZlciA9IGJ1ZmZlci5idWZmZXI7XG4gICAgfVxuXG4gICAgcmV0dXJuIGdsb2JhbFRoaXMuVGV4dENvZGVjSGVscGVyLmRlY29kZShidWZmZXIpO1xuICB9XG5cbiAgZW5jb2RlSW50bygpIHtcbiAgICB0aHJvdyBUeXBlRXJyb3IoJ1RleHRFbmNvZGVyKCkuZW5jb2RlSW50byBub3Qgc3VwcG9ydGVkJyk7XG4gIH1cblxuICBnZXQgZW5jb2RpbmcoKSB7XG4gICAgcmV0dXJuICd1dGYtOCc7XG4gIH1cblxuICBnZXQgZmF0YWwoKSB7XG4gICAgcmV0dXJuIGZhbHNlO1xuICB9XG5cbiAgZ2V0IGlnbm9yZUJPTSgpIHtcbiAgICByZXR1cm4gdHJ1ZTtcbiAgfVxufVxuIiwgImV4cG9ydCBjbGFzcyBUZXh0RW5jb2RlciB7XG4gIGNvbnN0cnVjdG9yKCkge31cblxuICBlbmNvZGUoc3RyOiBzdHJpbmcpOiBVaW50OEFycmF5IHtcbiAgICByZXR1cm4gbmV3IFVpbnQ4QXJyYXkoZ2xvYmFsVGhpcy5UZXh0Q29kZWNIZWxwZXIuZW5jb2RlKHN0cikpO1xuICB9XG5cbiAgZW5jb2RlSW50bygpIHtcbiAgICB0aHJvdyBUeXBlRXJyb3IoJ1RleHRFbmNvZGVyKCkuZW5jb2RlSW50byBub3Qgc3VwcG9ydGVkJyk7XG4gIH1cblxuICBnZXQgZW5jb2RpbmcoKSB7XG4gICAgcmV0dXJuICd1dGYtOCc7XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBFdmVudEVtaXR0ZXIgYXMgSUV2ZW50RW1pdHRlciB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCB7IENhbGxMeW54U2V0TW9kdWxlIH0gZnJvbSAnLi4vbmF0aXZlTW9kdWxlcyc7XG5cbmV4cG9ydCBkZWZhdWx0IGNsYXNzIEV2ZW50RW1pdHRlciBpbXBsZW1lbnRzIElFdmVudEVtaXR0ZXIge1xuICAvLyBlc2xpbnQtZGlzYWJsZS1uZXh0LWxpbmUgQHR5cGVzY3JpcHQtZXNsaW50L3ByZWZlci1yZWFkb25seVxuICBwcml2YXRlIF9ldmVudHM6IE1hcDxcbiAgICBzdHJpbmcsXG4gICAgeyBsaXN0ZW5lcjogKC4uLmFyZ3M6IHVua25vd25bXSkgPT4gdm9pZDsgY29udGV4dD86IG9iamVjdCB9W11cbiAgPjtcbiAgcHJpdmF0ZSBfaW50ZXJuYWxfY2FsbEx5bnhTZXRNb2R1bGU/OiBDYWxsTHlueFNldE1vZHVsZTtcbiAgY29uc3RydWN0b3IoY2FsbEx5bnhTZXRNb2R1bGU/OiBDYWxsTHlueFNldE1vZHVsZSkge1xuICAgIHRoaXMuX2ludGVybmFsX2NhbGxMeW54U2V0TW9kdWxlID0gY2FsbEx5bnhTZXRNb2R1bGU7XG4gICAgdGhpcy5fZXZlbnRzID0gbmV3IE1hcCgpO1xuICB9XG5cbiAgZ2V0RXZlbnRzU2l6ZShldmVudFR5cGU6IHN0cmluZyk6IG51bWJlciB7XG4gICAgcmV0dXJuIHRoaXMuX2V2ZW50cy5nZXQoZXZlbnRUeXBlKT8ubGVuZ3RoO1xuICB9XG5cbiAgc2V0Q2FsbEx5bnhTZXRNb2R1bGUoY2FsbEx5bnhTZXRNb2R1bGU/OiBDYWxsTHlueFNldE1vZHVsZSkge1xuICAgIHRoaXMuX2ludGVybmFsX2NhbGxMeW54U2V0TW9kdWxlID0gY2FsbEx5bnhTZXRNb2R1bGU7XG4gIH1cblxuICBhZGRMaXN0ZW5lcihcbiAgICBldmVudE5hbWU6IHN0cmluZyxcbiAgICBsaXN0ZW5lcjogKC4uLmFyZ3M6IHVua25vd25bXSkgPT4gdm9pZCxcbiAgICBjb250ZXh0Pzogb2JqZWN0XG4gICk6IHZvaWQge1xuICAgIGNvbnN0IGV2ZW50ID0gdGhpcy5fZXZlbnRzLmdldChldmVudE5hbWUpO1xuICAgIC8vIFRPRE86IHJlbW92ZWQgdGhpcyBhcGkgZGVzaWduIGFmdGVyIHNwcmluZ1xuICAgIGlmIChldmVudE5hbWUgPT0gJ2tleWJvYXJkc3RhdHVzY2hhbmdlZCcpIHtcbiAgICAgIGlmICh0aGlzLl9pbnRlcm5hbF9jYWxsTHlueFNldE1vZHVsZSkge1xuICAgICAgICB0aGlzLl9pbnRlcm5hbF9jYWxsTHlueFNldE1vZHVsZSgnc3dpdGNoS2V5Qm9hcmREZXRlY3QnLCBbdHJ1ZV0pO1xuICAgICAgfVxuICAgIH1cbiAgICBpZiAoZXZlbnQpIHtcbiAgICAgIGV2ZW50LnB1c2goe1xuICAgICAgICBsaXN0ZW5lcixcbiAgICAgICAgY29udGV4dCxcbiAgICAgIH0pO1xuICAgIH0gZWxzZSB7XG4gICAgICB0aGlzLl9ldmVudHMuc2V0KGV2ZW50TmFtZSwgW1xuICAgICAgICB7XG4gICAgICAgICAgbGlzdGVuZXIsXG4gICAgICAgICAgY29udGV4dCxcbiAgICAgICAgfSxcbiAgICAgIF0pO1xuICAgIH1cbiAgfVxuXG4gIHJlbW92ZUxpc3RlbmVyKFxuICAgIGV2ZW50TmFtZTogc3RyaW5nLFxuICAgIGxpc3RlbmVyOiAoLi4uYXJnczogdW5rbm93bltdKSA9PiB2b2lkXG4gICk6IHZvaWQge1xuICAgIGlmICh0eXBlb2YgbGlzdGVuZXIgIT09ICdmdW5jdGlvbicpIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcigncmVtb3ZlTGlzdGVuZXIgb25seSB0YWtlcyBpbnN0YW5jZXMgb2YgRnVuY3Rpb24nKTtcbiAgICB9XG4gICAgY29uc3QgZXZlbnRzID0gdGhpcy5fZXZlbnRzLmdldChldmVudE5hbWUpO1xuICAgIGxldCBpbmRleCA9IDA7XG4gICAgaWYgKEFycmF5LmlzQXJyYXkoZXZlbnRzKSkge1xuICAgICAgY29uc3QgZmxhZyA9IGV2ZW50cy5zb21lKChpdGVtKSA9PiB7XG4gICAgICAgIGlmIChsaXN0ZW5lciA9PT0gaXRlbS5saXN0ZW5lcikge1xuICAgICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgICB9XG4gICAgICAgIGluZGV4Kys7XG4gICAgICB9KTtcbiAgICAgIGZsYWcgJiYgZXZlbnRzLnNwbGljZShpbmRleCwgMSk7XG4gICAgfVxuXG4gICAgLy8gVE9ETzogcmVtb3ZlZCB0aGlzIGFwaSBkZXNpZ24gYWZ0ZXIgc3ByaW5nXG4gICAgaWYgKGV2ZW50TmFtZSA9PSAna2V5Ym9hcmRzdGF0dXNjaGFuZ2VkJykge1xuICAgICAgaWYgKHRoaXMuX2ludGVybmFsX2NhbGxMeW54U2V0TW9kdWxlKSB7XG4gICAgICAgIHRoaXMuX2ludGVybmFsX2NhbGxMeW54U2V0TW9kdWxlKCdzd2l0Y2hLZXlCb2FyZERldGVjdCcsIFtmYWxzZV0pO1xuICAgICAgfVxuICAgIH1cbiAgfVxuXG4gIGVtaXQoZXZlbnROYW1lOiBzdHJpbmcsIGRhdGE6IHVua25vd24pOiB2b2lkIHtcbiAgICBjb25zdCBldmVudHMgPSB0aGlzLl9ldmVudHMuZ2V0KGV2ZW50TmFtZSk7XG4gICAgaWYgKEFycmF5LmlzQXJyYXkoZXZlbnRzKSkge1xuICAgICAgZXZlbnRzLmZvckVhY2goKGl0ZW0pID0+IHtcbiAgICAgICAgY29uc3QgeyBsaXN0ZW5lciwgY29udGV4dCB9ID0gaXRlbTtcbiAgICAgICAgaWYgKHR5cGVvZiBsaXN0ZW5lciA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgICAgIGxpc3RlbmVyLmFwcGx5KGNvbnRleHQgfHwgdGhpcywgZGF0YSk7XG4gICAgICAgIH1cbiAgICAgIH0pO1xuICAgIH1cbiAgfVxuXG4gIHJlbW92ZUFsbExpc3RlbmVycyhldmVudE5hbWU/OiBzdHJpbmcpOiB2b2lkIHtcbiAgICBpZiAodHlwZW9mIGV2ZW50TmFtZSA9PT0gJ3N0cmluZycpIHtcbiAgICAgIHRoaXMuX2V2ZW50cy5kZWxldGUoZXZlbnROYW1lKTtcbiAgICAgIHJldHVybjtcbiAgICB9XG5cbiAgICAvLyBjbGVhciBhbGxcbiAgICB0aGlzLl9ldmVudHMgPSBuZXcgTWFwKCk7XG4gIH1cblxuICB0cmlnZ2VyKGV2ZW50TmFtZTogc3RyaW5nLCBwYXJhbXM6IHN0cmluZyB8IFJlY29yZDxhbnksIGFueT4pOiB2b2lkIHtcbiAgICAvLyBmb3IgYXBpIHVzYWdlO1xuICAgIGNvbnN0IGV2ZW50cyA9IHRoaXMuX2V2ZW50cy5nZXQoZXZlbnROYW1lKTtcbiAgICBpZiAoQXJyYXkuaXNBcnJheShldmVudHMpKSB7XG4gICAgICBpZiAodHlwZW9mIHBhcmFtcyA9PT0gJ3N0cmluZycpIHtcbiAgICAgICAgcGFyYW1zID0gSlNPTi5wYXJzZShwYXJhbXMpO1xuICAgICAgfVxuICAgICAgZXZlbnRzLmZvckVhY2goKGl0ZW0pID0+IHtcbiAgICAgICAgY29uc3QgeyBsaXN0ZW5lciwgY29udGV4dCB9ID0gaXRlbTtcbiAgICAgICAgaWYgKHR5cGVvZiBsaXN0ZW5lciA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgICAgIGxpc3RlbmVyLmNhbGwoY29udGV4dCB8fCB0aGlzLCBwYXJhbXMpO1xuICAgICAgICB9XG4gICAgICB9KTtcbiAgICB9XG4gIH1cblxuICB0b2dnbGUoZXZlbnROYW1lOiBzdHJpbmcsIC4uLmRhdGE6IHVua25vd25bXSk6IHZvaWQge1xuICAgIHRoaXMuZW1pdChldmVudE5hbWUsIGRhdGEpO1xuICB9XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBjcmVhdGVFdmVudEVtaXR0ZXIoKSB7XG4gIHJldHVybiBuZXcgRXZlbnRFbWl0dGVyKCk7XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IHsgQmVmb3JlUHVibGlzaEV2ZW50IGFzIElCZWZvcmVQdWJsaXNoRXZlbnQgfSBmcm9tICdAbHlueC1qcy90eXBlcyc7XG5pbXBvcnQgRXZlbnRFbWl0dGVyIGZyb20gJy4vZXZlbnRFbWl0dGVyJztcblxuZXhwb3J0IGNsYXNzIEFvcE1hbmFnZXIge1xuICBwdWJsaWMgX2JlZm9yZVB1Ymxpc2hFdmVudDogQmVmb3JlUHVibGlzaEV2ZW50O1xuXG4gIGNvbnN0cnVjdG9yKCkge1xuICAgIHRoaXMuX2JlZm9yZVB1Ymxpc2hFdmVudCA9IG5ldyBCZWZvcmVQdWJsaXNoRXZlbnQoKTtcbiAgfVxufVxuXG5leHBvcnQgY2xhc3MgQmVmb3JlUHVibGlzaEV2ZW50XG4gIGV4dGVuZHMgRXZlbnRFbWl0dGVyXG4gIGltcGxlbWVudHMgSUJlZm9yZVB1Ymxpc2hFdmVudCB7XG4gIGFkZChcbiAgICBldmVudE5hbWU6IHN0cmluZyxcbiAgICBjYWxsYmFjazogKC4uLmFyZ3M6IHVua25vd25bXSkgPT4gdm9pZCxcbiAgICBjb250ZXh0Pzogb2JqZWN0XG4gICk6IEJlZm9yZVB1Ymxpc2hFdmVudCB7XG4gICAgc3VwZXIuYWRkTGlzdGVuZXIoZXZlbnROYW1lLCBjYWxsYmFjaywgY29udGV4dCk7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cblxuICByZW1vdmUoXG4gICAgZXZlbnROYW1lOiBzdHJpbmcsXG4gICAgY2FsbGJhY2s6ICguLi5hcmdzOiB1bmtub3duW10pID0+IHZvaWRcbiAgKTogQmVmb3JlUHVibGlzaEV2ZW50IHtcbiAgICBzdXBlci5yZW1vdmVMaXN0ZW5lcihldmVudE5hbWUsIGNhbGxiYWNrKTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCBFdmVudEVtaXR0ZXIgZnJvbSAnLi9ldmVudEVtaXR0ZXInO1xuZXhwb3J0IGRlZmF1bHQgRXZlbnRFbWl0dGVyO1xuZXhwb3J0IHsgY3JlYXRlRXZlbnRFbWl0dGVyIH0gZnJvbSAnLi9ldmVudEVtaXR0ZXInO1xuXG5leHBvcnQgKiBmcm9tICcuL2FvcCc7XG4iLCAiaW1wb3J0IEV2ZW50RW1pdHRlciBmcm9tICcuLi9ldmVudCc7XG5cbmludGVyZmFjZSBTdHJlYW1EZWxlZ2F0ZSB7XG4gIG9uRGF0YShkYXRhOiBBcnJheUJ1ZmZlcik6IHZvaWQ7XG4gIG9uRW5kKCk6IHZvaWQ7XG4gIG9uRXJyb3IoZXJyb3I6IHN0cmluZyk6IHZvaWQ7XG59XG4vKipcbiAqIFNlcnZlcyBhcyBhIHN0YWJsZSB0eXBlIGlkZW50aWZpZXIgYWNyb3NzIGRpZmZlcmVudCBQcm9taXNlIGNvbnN0cnVjdG9yIGVudmlyb25tZW50c1xuICpcbiAqIFRoaXMgY2xhc3MgaXMgdXNlZCB0byBlbnN1cmUgdHlwZSByZWNvZ25pdGlvbiB3b3JrcyB3aGVuIHNhbWUtY2xhc3MgaW5zdGFuY2VzIGNvbWUgZnJvbVxuICogZGlmZmVyZW50IFByb21pc2UgY29uc3RydWN0b3IgZW52aXJvbm1lbnRzIChlLmcuIGRpZmZlcmVudCBseW54IGluc3RhbmNlcylcbiAqL1xuZXhwb3J0IGFic3RyYWN0IGNsYXNzIEx5bnhSZWFkYWJsZVN0cmVhbSB7fVxuXG5leHBvcnQgZnVuY3Rpb24gY3JlYXRlUmVhZGFibGVTdHJlYW1DbGFzcyhQcm9taXNlOiBQcm9taXNlQ29uc3RydWN0b3IpOiBhbnkge1xuICByZXR1cm4gY2xhc3MgUmVhZGFibGVTdHJlYW1cbiAgICBleHRlbmRzIEx5bnhSZWFkYWJsZVN0cmVhbVxuICAgIGltcGxlbWVudHMgU3RyZWFtRGVsZWdhdGUge1xuICAgIHByaXZhdGUgX19ldmVudENlbnRlcjogRXZlbnRFbWl0dGVyO1xuICAgIHByaXZhdGUgX19kYXRhUmVjZWl2ZWQ6IEFycmF5QnVmZmVyW107XG4gICAgcHJpdmF0ZSBfX2RvbmU6IGJvb2xlYW47XG4gICAgcHJpdmF0ZSBfX2NhbmNlbGxlZDogYm9vbGVhbjtcbiAgICBwcml2YXRlIF9fbG9ja2VkOiBib29sZWFuO1xuICAgIHByaXZhdGUgX19lcnJvcjogRXJyb3I7XG4gICAgY29uc3RydWN0b3IoKSB7XG4gICAgICBzdXBlcigpO1xuICAgICAgdGhpcy5fX2RhdGFSZWNlaXZlZCA9IFtdO1xuICAgICAgdGhpcy5fX2RvbmUgPSBmYWxzZTtcbiAgICAgIHRoaXMuX19jYW5jZWxsZWQgPSBmYWxzZTtcbiAgICAgIHRoaXMuX19sb2NrZWQgPSBmYWxzZTtcbiAgICAgIHRoaXMuX19ldmVudENlbnRlciA9IG5ldyBFdmVudEVtaXR0ZXIoKTtcbiAgICB9XG4gICAgb25EYXRhKGRhdGE6IEFycmF5QnVmZmVyKTogdm9pZCB7XG4gICAgICBpZiAodGhpcy5fX2NhbmNlbGxlZCkge1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgICB0aGlzLl9fZGF0YVJlY2VpdmVkLnB1c2goZGF0YSk7XG4gICAgICB0aGlzLl9fZXZlbnRDZW50ZXIuZW1pdCgnd2FpdFNpZ25hbCcsIG51bGwpO1xuICAgIH1cbiAgICBvbkVuZCgpOiB2b2lkIHtcbiAgICAgIHRoaXMuX19kb25lID0gdHJ1ZTtcbiAgICAgIHRoaXMuX19ldmVudENlbnRlci5lbWl0KCd3YWl0U2lnbmFsJywgbnVsbCk7XG4gICAgfVxuICAgIG9uRXJyb3IoZXJyb3I6IHN0cmluZyk6IHZvaWQge1xuICAgICAgdGhpcy5fX2Vycm9yID0gbmV3IEVycm9yKGVycm9yKTtcbiAgICAgIHRoaXMuX19ldmVudENlbnRlci5lbWl0KCd3YWl0U2lnbmFsJywgbnVsbCk7XG4gICAgfVxuICAgIHByaXZhdGUgcHJvY2Vzc1JlYWQocmVzb2x2ZSwgcmVqZWN0KSB7XG4gICAgICBpZiAodGhpcy5fX2Vycm9yKSB7XG4gICAgICAgIHJldHVybiByZWplY3QodGhpcy5fX2Vycm9yKTtcbiAgICAgIH1cbiAgICAgIGlmIChcbiAgICAgICAgdGhpcy5fX2NhbmNlbGxlZCB8fFxuICAgICAgICAodGhpcy5fX2RvbmUgJiYgdGhpcy5fX2RhdGFSZWNlaXZlZC5sZW5ndGggPT0gMClcbiAgICAgICkge1xuICAgICAgICByZXR1cm4gcmVzb2x2ZSh7IGRvbmU6IHRydWUsIHZhbHVlOiB1bmRlZmluZWQgfSk7XG4gICAgICB9XG4gICAgICBpZiAodGhpcy5fX2RhdGFSZWNlaXZlZC5sZW5ndGggPiAwKSB7XG4gICAgICAgIGNvbnN0IGN1cnJEYXRhID0gdGhpcy5fX2RhdGFSZWNlaXZlZC5zaGlmdCgpO1xuICAgICAgICByZXR1cm4gcmVzb2x2ZSh7IGRvbmU6IGZhbHNlLCB2YWx1ZTogY3VyckRhdGEgfSk7XG4gICAgICB9XG4gICAgICAvLyB3YWl0IGZvciBzaWduYWxzXG4gICAgICBjb25zdCB3YWl0U2lnbmFsID0gKCkgPT4ge1xuICAgICAgICB0aGlzLl9fZXZlbnRDZW50ZXIucmVtb3ZlTGlzdGVuZXIoJ3dhaXRTaWduYWwnLCB3YWl0U2lnbmFsKTtcbiAgICAgICAgdGhpcy5wcm9jZXNzUmVhZChyZXNvbHZlLCByZWplY3QpO1xuICAgICAgfTtcblxuICAgICAgdGhpcy5fX2V2ZW50Q2VudGVyLmFkZExpc3RlbmVyKCd3YWl0U2lnbmFsJywgd2FpdFNpZ25hbCwgdGhpcyk7XG4gICAgfVxuICAgIHB1YmxpYyBfX3JlYWQoKSB7XG4gICAgICByZXR1cm4gbmV3IFByb21pc2UoKHJlc29sdmUsIHJlamVjdCkgPT4ge1xuICAgICAgICB0aGlzLnByb2Nlc3NSZWFkKHJlc29sdmUsIHJlamVjdCk7XG4gICAgICB9KTtcbiAgICB9XG4gICAgcHVibGljIGdldCBsb2NrZWQoKSB7XG4gICAgICByZXR1cm4gdGhpcy5fX2xvY2tlZDtcbiAgICB9XG4gICAgcHVibGljIGNhbmNlbChyZWFzb24/OiBhbnkpIHtcbiAgICAgIHRoaXMuX19jYW5jZWxsZWQgPSB0cnVlO1xuICAgICAgdGhpcy5fX2RhdGFSZWNlaXZlZCA9IG51bGw7XG4gICAgICB0aGlzLl9fZXZlbnRDZW50ZXIuZW1pdCgnd2FpdFNpZ25hbCcsIG51bGwpO1xuICAgICAgcmV0dXJuIFByb21pc2UucmVzb2x2ZShyZWFzb24pO1xuICAgIH1cbiAgICBwdWJsaWMgZ2V0UmVhZGVyKCkge1xuICAgICAgaWYgKHRoaXMuX19sb2NrZWQpIHtcbiAgICAgICAgcmV0dXJuIG51bGw7XG4gICAgICB9XG4gICAgICB0aGlzLl9fbG9ja2VkID0gdHJ1ZTtcbiAgICAgIHJldHVybiBuZXcgUmVhZGFibGVTdHJlYW1EZWZhdWx0UmVhZGVyKHRoaXMgYXMgYW55KTtcbiAgICB9XG4gIH07XG59XG5jbGFzcyBSZWFkYWJsZVN0cmVhbURlZmF1bHRSZWFkZXIge1xuICBwcml2YXRlIF9fc3RyZWFtO1xuICBjb25zdHJ1Y3RvcihzdHJlYW06IFJlYWRhYmxlU3RyZWFtKSB7XG4gICAgdGhpcy5fX3N0cmVhbSA9IHN0cmVhbTtcbiAgfVxuICBwdWJsaWMgY2FuY2VsKHJlYXNvbj86IGFueSkge1xuICAgIHJldHVybiB0aGlzLl9fc3RyZWFtLmNhbmNlbChyZWFzb24pO1xuICB9XG4gIHB1YmxpYyByZWFkKCkge1xuICAgIHJldHVybiB0aGlzLl9fc3RyZWFtLl9fcmVhZCgpO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IHsgVGV4dERlY29kZXIgfSBmcm9tICcuL1RleHREZWNvZGVyJztcbmltcG9ydCB7IFRleHRFbmNvZGVyIH0gZnJvbSAnLi9UZXh0RW5jb2Rlcic7XG5pbXBvcnQgeyBMeW54UmVhZGFibGVTdHJlYW0gfSBmcm9tICcuL1JlYWRhYmxlU3RyZWFtJztcbmV4cG9ydCBjbGFzcyBCb2R5TWl4aW4ge1xuICBfYXJyYXlCdWZmZXI6IEFycmF5QnVmZmVyO1xuICBfYm9keVN0cmVhbTogTHlueFJlYWRhYmxlU3RyZWFtO1xuICBfYm9keVVzZWQ6IGJvb2xlYW47XG5cbiAgY29uc3RydWN0b3IoKSB7XG4gICAgdGhpcy5fYXJyYXlCdWZmZXIgPSBuZXcgQXJyYXlCdWZmZXIoMCk7XG4gICAgdGhpcy5fYm9keVN0cmVhbSA9IG51bGw7XG4gICAgdGhpcy5fYm9keVVzZWQgPSBmYWxzZTtcbiAgfVxuXG4gIHByaXZhdGUgc2FmZVVzZUJvZHk8VD4odXNlOiAoYm9keTogQXJyYXlCdWZmZXIpID0+IFQpOiBUIHtcbiAgICBpZiAodGhpcy5fYm9keVVzZWQpIHtcbiAgICAgIC8vIFRPRE8oaHV6aGFuYm8ubHVjKTogdGhyb3cgYSBlcnJvciBpZiB0aGUgYnJlYWsgY2hhbmdlIGlzIG9rLlxuICAgICAgcmV0dXJuIHVuZGVmaW5lZDtcbiAgICB9XG5cbiAgICBjb25zdCByZXQgPSB1c2UodGhpcy5fYXJyYXlCdWZmZXIpO1xuICAgIHRoaXMuX2JvZHlVc2VkID0gdHJ1ZTtcbiAgICB0aGlzLl9hcnJheUJ1ZmZlciA9IG51bGw7XG4gICAgcmV0dXJuIHJldDtcbiAgfVxuXG4gIHByaXZhdGUgY2xvbmVBcnJheUJ1ZmZlcihzcmM6IEFycmF5QnVmZmVyKSB7XG4gICAgcmV0dXJuIHNyYy5zbGljZSgwKTtcbiAgfVxuXG4gIHByb3RlY3RlZCBzZXRCb2R5KGJvZHk/OiBCb2R5SW5pdCB8IEJvZHlNaXhpbiB8IFJlYWRhYmxlU3RyZWFtKSB7XG4gICAgaWYgKGJvZHkgaW5zdGFuY2VvZiBCb2R5TWl4aW4pIHtcbiAgICAgIGlmIChib2R5Ll9ib2R5VXNlZCB8fCBib2R5Ll9ib2R5U3RyZWFtKSB7XG4gICAgICAgIHRocm93IG5ldyBFcnJvcignYm9keSB1c2VkLCBvciB0cnkgdG8gY29weSBib2R5IHN0cmVhbScpO1xuICAgICAgfVxuICAgICAgdGhpcy5fYXJyYXlCdWZmZXIgPSB0aGlzLmNsb25lQXJyYXlCdWZmZXIoYm9keS5fYXJyYXlCdWZmZXIpO1xuICAgIH0gZWxzZSB7XG4gICAgICBpZiAoYm9keSBpbnN0YW5jZW9mIEFycmF5QnVmZmVyKSB7XG4gICAgICAgIHRoaXMuX2FycmF5QnVmZmVyID0gdGhpcy5jbG9uZUFycmF5QnVmZmVyKGJvZHkpO1xuICAgICAgfSBlbHNlIGlmIChib2R5IGluc3RhbmNlb2YgRGF0YVZpZXcpIHtcbiAgICAgICAgdGhpcy5fYXJyYXlCdWZmZXIgPSB0aGlzLmNsb25lQXJyYXlCdWZmZXIoXG4gICAgICAgICAgYm9keS5idWZmZXIuc2xpY2UoYm9keS5ieXRlT2Zmc2V0LCBib2R5LmJ5dGVPZmZzZXQgKyBib2R5LmJ5dGVMZW5ndGgpXG4gICAgICAgICk7XG4gICAgICB9IGVsc2UgaWYgKEFycmF5QnVmZmVyLmlzVmlldyhib2R5KSkge1xuICAgICAgICB0aGlzLl9hcnJheUJ1ZmZlciA9IHRoaXMuY2xvbmVBcnJheUJ1ZmZlcihib2R5LmJ1ZmZlcik7XG4gICAgICB9IGVsc2UgaWYgKGJvZHkpIHtcbiAgICAgICAgdGhpcy5fYXJyYXlCdWZmZXIgPSBuZXcgVGV4dEVuY29kZXIoKS5lbmNvZGUoYm9keS50b1N0cmluZygpKS5idWZmZXI7XG4gICAgICB9XG4gICAgICBpZiAoYm9keSBpbnN0YW5jZW9mIEx5bnhSZWFkYWJsZVN0cmVhbSkge1xuICAgICAgICB0aGlzLl9ib2R5U3RyZWFtID0gYm9keTtcbiAgICAgIH1cbiAgICB9XG4gIH1cblxuICBwdWJsaWMgYXJyYXlCdWZmZXIoKTogUHJvbWlzZTxBcnJheUJ1ZmZlcj4ge1xuICAgIHJldHVybiBQcm9taXNlLnJlc29sdmUodGhpcy5zYWZlVXNlQm9keSgoYm9keSkgPT4gYm9keSkpO1xuICB9XG5cbiAgcHVibGljIGdldCBib2R5KCkge1xuICAgIGlmICh0aGlzLl9ib2R5VXNlZCkge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKCdib2R5IHVzZWQnKTtcbiAgICB9XG4gICAgdGhpcy5fYm9keVVzZWQgPSB0cnVlO1xuICAgIHJldHVybiB0aGlzLl9ib2R5U3RyZWFtO1xuICB9XG5cbiAgcHVibGljIHRleHQoKTogUHJvbWlzZTxzdHJpbmc+IHtcbiAgICByZXR1cm4gUHJvbWlzZS5yZXNvbHZlKFxuICAgICAgdGhpcy5zYWZlVXNlQm9keSgoYm9keSkgPT4gbmV3IFRleHREZWNvZGVyKCkuZGVjb2RlKGJvZHkpKVxuICAgICk7XG4gIH1cblxuICBwdWJsaWMganNvbigpOiBQcm9taXNlPGFueT4ge1xuICAgIHJldHVybiBQcm9taXNlLnJlc29sdmUoXG4gICAgICB0aGlzLnNhZmVVc2VCb2R5KChib2R5KSA9PiBKU09OLnBhcnNlKG5ldyBUZXh0RGVjb2RlcigpLmRlY29kZShib2R5KSkpXG4gICAgKTtcbiAgfVxuXG4gIC8vIFRPRE8oaHV6aGFuYm8ubHVjKTogdGhlc2UgQVBJcyByZWx5IG9uIGZvdW5kYW1lbnRhbCB0eXBlc1xuICAvLyB3aGljaCByZXF1aXJlIGV4dHJhIHdvcmtzIHRvIHN1cHBvcnQsIHdlIHdpbGwgc3VwcG9ydCB0aGVzZVxuICAvLyBsYXRlciB3aGVuIHdlIGhhdmUgaW1wbGVtZW50ZWQgdGhlc2UgdHlwZXMuXG5cbiAgLy8gYmxvYigpOiBCbG9iO1xuICAvLyBmb3JtRGF0YSgpOiBGb3JtRGF0YTtcbiAgLy8gY2xvbmVTdHJlYW0oKTogUmVhZGFibGVTdHJlYW07XG5cbiAgcHVibGljIGdldCBib2R5VXNlZCgpIHtcbiAgICByZXR1cm4gdGhpcy5fYm9keVVzZWQ7XG4gIH1cbn1cbiIsICIvKipcbiAqIEBsaWNlbnNlIE1JVFxuICogaHR0cHM6Ly9naXRodWIuY29tL21zd2pzL2hlYWRlcnMtcG9seWZpbGwvYmxvYi9tYWluL0xJQ0VOU0VcbiAqXG5Db3B5cmlnaHQgKGMpIDIwMjDigJNwcmVzZW50IEFydGVtIFpha2hhcmNoZW5rb1xuXG5QZXJtaXNzaW9uIGlzIGhlcmVieSBncmFudGVkLCBmcmVlIG9mIGNoYXJnZSwgdG8gYW55IHBlcnNvbiBvYnRhaW5pbmcgYSBjb3B5IG9mIHRoaXMgc29mdHdhcmUgYW5kIGFzc29jaWF0ZWQgZG9jdW1lbnRhdGlvbiBmaWxlcyAodGhlIFwiU29mdHdhcmVcIiksIHRvIGRlYWwgaW4gdGhlIFNvZnR3YXJlIHdpdGhvdXQgcmVzdHJpY3Rpb24sIGluY2x1ZGluZyB3aXRob3V0IGxpbWl0YXRpb24gdGhlIHJpZ2h0cyB0byB1c2UsIGNvcHksIG1vZGlmeSwgbWVyZ2UsIHB1Ymxpc2gsIGRpc3RyaWJ1dGUsIHN1YmxpY2Vuc2UsIGFuZC9vciBzZWxsIGNvcGllcyBvZiB0aGUgU29mdHdhcmUsIGFuZCB0byBwZXJtaXQgcGVyc29ucyB0byB3aG9tIHRoZSBTb2Z0d2FyZSBpcyBmdXJuaXNoZWQgdG8gZG8gc28sIHN1YmplY3QgdG8gdGhlIGZvbGxvd2luZyBjb25kaXRpb25zOlxuXG5UaGUgYWJvdmUgY29weXJpZ2h0IG5vdGljZSBhbmQgdGhpcyBwZXJtaXNzaW9uIG5vdGljZSBzaGFsbCBiZSBpbmNsdWRlZCBpbiBhbGwgY29waWVzIG9yIHN1YnN0YW50aWFsIHBvcnRpb25zIG9mIHRoZSBTb2Z0d2FyZS5cblxuVEhFIFNPRlRXQVJFIElTIFBST1ZJREVEIFwiQVMgSVNcIiwgV0lUSE9VVCBXQVJSQU5UWSBPRiBBTlkgS0lORCwgRVhQUkVTUyBPUiBJTVBMSUVELCBJTkNMVURJTkcgQlVUIE5PVCBMSU1JVEVEIFRPIFRIRSBXQVJSQU5USUVTIE9GIE1FUkNIQU5UQUJJTElUWSwgRklUTkVTUyBGT1IgQSBQQVJUSUNVTEFSIFBVUlBPU0UgQU5EIE5PTklORlJJTkdFTUVOVC4gSU4gTk8gRVZFTlQgU0hBTEwgVEhFIEFVVEhPUlMgT1IgQ09QWVJJR0hUIEhPTERFUlMgQkUgTElBQkxFIEZPUiBBTlkgQ0xBSU0sIERBTUFHRVMgT1IgT1RIRVIgTElBQklMSVRZLCBXSEVUSEVSIElOIEFOIEFDVElPTiBPRiBDT05UUkFDVCwgVE9SVCBPUiBPVEhFUldJU0UsIEFSSVNJTkcgRlJPTSwgT1VUIE9GIE9SIElOIENPTk5FQ1RJT04gV0lUSCBUSEUgU09GVFdBUkUgT1IgVEhFIFVTRSBPUiBPVEhFUiBERUFMSU5HUyBJTiBUSEUgU09GVFdBUkUuXG4gKi9cbmV4cG9ydCBjbGFzcyBIZWFkZXJzIHtcbiAgcHJpdmF0ZSBfaGVhZGVyc19tYXA6IE1hcDxzdHJpbmcsIHN0cmluZz4gPSBuZXcgTWFwKCk7XG5cbiAgY29uc3RydWN0b3IoaW5pdD86IEhlYWRlcnNJbml0KSB7XG4gICAgaWYgKGluaXQgPT09IG51bGwgfHwgdHlwZW9mIGluaXQgPT09ICdudW1iZXInKSB7XG4gICAgICB0aHJvdyBuZXcgVHlwZUVycm9yKGBIZWFkZXJzIGluaXQgd2l0aCBudWxsL251bWJlcmApO1xuICAgIH1cbiAgICBpZiAoaW5pdCBpbnN0YW5jZW9mIEhlYWRlcnMpIHtcbiAgICAgIGZvciAoY29uc3QgW2tleSwgdmFsdWVdIG9mIGluaXQpIHtcbiAgICAgICAgdGhpcy5hcHBlbmQoa2V5LCB2YWx1ZSk7XG4gICAgICB9XG4gICAgfSBlbHNlIGlmIChBcnJheS5pc0FycmF5KGluaXQpKSB7XG4gICAgICBpbml0LmZvckVhY2goKFtuYW1lLCB2YWx1ZV0pID0+IHtcbiAgICAgICAgdGhpcy5hcHBlbmQobmFtZSwgQXJyYXkuaXNBcnJheSh2YWx1ZSkgPyB2YWx1ZS5qb2luKCcgJykgOiB2YWx1ZSk7XG4gICAgICB9KTtcbiAgICB9IGVsc2UgaWYgKGluaXQpIHtcbiAgICAgIE9iamVjdC5nZXRPd25Qcm9wZXJ0eU5hbWVzKGluaXQpLmZvckVhY2goKG5hbWUpID0+IHtcbiAgICAgICAgY29uc3QgdmFsdWUgPSBpbml0W25hbWVdO1xuICAgICAgICB0aGlzLmFwcGVuZChuYW1lLCBBcnJheS5pc0FycmF5KHZhbHVlKSA/IHZhbHVlLmpvaW4oJyAnKSA6IHZhbHVlKTtcbiAgICAgIH0pO1xuICAgIH1cbiAgfVxuXG4gIFtTeW1ib2wudG9TdHJpbmdUYWddID0gJ0hlYWRlcnMnO1xuXG4gIFtTeW1ib2wuaXRlcmF0b3JdKCkge1xuICAgIHJldHVybiB0aGlzLmVudHJpZXMoKTtcbiAgfVxuXG4gICprZXlzKCk6IEl0ZXJhYmxlSXRlcmF0b3I8c3RyaW5nPiB7XG4gICAgZm9yIChjb25zdCBba2V5LCB2YWx1ZV0gb2YgdGhpcy5faGVhZGVyc19tYXApIHtcbiAgICAgIHlpZWxkIGtleTtcbiAgICB9XG4gIH1cblxuICAqdmFsdWVzKCk6IEl0ZXJhYmxlSXRlcmF0b3I8c3RyaW5nPiB7XG4gICAgZm9yIChjb25zdCBba2V5LCB2YWx1ZV0gb2YgdGhpcy5faGVhZGVyc19tYXApIHtcbiAgICAgIHlpZWxkIHZhbHVlO1xuICAgIH1cbiAgfVxuXG4gICplbnRyaWVzKCk6IEl0ZXJhYmxlSXRlcmF0b3I8W3N0cmluZywgc3RyaW5nXT4ge1xuICAgIGZvciAoY29uc3QgZW50cnkgb2YgdGhpcy5faGVhZGVyc19tYXApIHtcbiAgICAgIHlpZWxkIGVudHJ5O1xuICAgIH1cbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm5zIGEgYm9vbGVhbiBzdGF0aW5nIHdoZXRoZXIgYSBgSGVhZGVyc2Agb2JqZWN0IGNvbnRhaW5zIGEgY2VydGFpbiBoZWFkZXIuXG4gICAqL1xuICBoYXMobmFtZTogc3RyaW5nKTogYm9vbGVhbiB7XG4gICAgcmV0dXJuIHRoaXMuX2hlYWRlcnNfbWFwLmhhcyhuYW1lKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm5zIGEgYEJ5dGVTdHJpbmdgIHNlcXVlbmNlIG9mIGFsbCB0aGUgdmFsdWVzIG9mIGEgaGVhZGVyIHdpdGggYSBnaXZlbiBuYW1lLlxuICAgKi9cbiAgZ2V0KG5hbWU6IHN0cmluZyk6IHN0cmluZyB8IG51bGwge1xuICAgIHJldHVybiB0aGlzLl9oZWFkZXJzX21hcC5nZXQobmFtZSkgPz8gbnVsbDtcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXRzIGEgbmV3IHZhbHVlIGZvciBhbiBleGlzdGluZyBoZWFkZXIgaW5zaWRlIGEgYEhlYWRlcnNgIG9iamVjdCwgb3IgYWRkcyB0aGUgaGVhZGVyIGlmIGl0IGRvZXMgbm90IGFscmVhZHkgZXhpc3QuXG4gICAqL1xuICBzZXQobmFtZTogc3RyaW5nLCB2YWx1ZTogc3RyaW5nKTogdm9pZCB7XG4gICAgdGhpcy5faGVhZGVyc19tYXAuc2V0KG5hbWUsIFN0cmluZyh2YWx1ZSkpO1xuICB9XG5cbiAgLyoqXG4gICAqIEFwcGVuZHMgYSBuZXcgdmFsdWUgb250byBhbiBleGlzdGluZyBoZWFkZXIgaW5zaWRlIGEgYEhlYWRlcnNgIG9iamVjdCwgb3IgYWRkcyB0aGUgaGVhZGVyIGlmIGl0IGRvZXMgbm90IGFscmVhZHkgZXhpc3QuXG4gICAqL1xuICBhcHBlbmQobmFtZTogc3RyaW5nLCB2YWx1ZTogc3RyaW5nKTogdm9pZCB7XG4gICAgbGV0IHJlc29sdmVkVmFsdWUgPSB0aGlzLmhhcyhuYW1lKSA/IGAke3RoaXMuZ2V0KG5hbWUpfSwgJHt2YWx1ZX1gIDogdmFsdWU7XG5cbiAgICB0aGlzLnNldChuYW1lLCByZXNvbHZlZFZhbHVlKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBEZWxldGVzIGEgaGVhZGVyIGZyb20gdGhlIGBIZWFkZXJzYCBvYmplY3QuXG4gICAqL1xuICBkZWxldGUobmFtZTogc3RyaW5nKTogdm9pZCB7XG4gICAgaWYgKCF0aGlzLmhhcyhuYW1lKSkge1xuICAgICAgcmV0dXJuO1xuICAgIH1cblxuICAgIHRoaXMuX2hlYWRlcnNfbWFwLmRlbGV0ZShuYW1lKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBUcmF2ZXJzZXMgdGhlIGBIZWFkZXJzYCBvYmplY3QsXG4gICAqIGNhbGxpbmcgdGhlIGdpdmVuIGNhbGxiYWNrIGZvciBlYWNoIGhlYWRlci5cbiAgICovXG4gIGZvckVhY2g8VGhpc0FyZyA9IHRoaXM+KFxuICAgIGNhbGxiYWNrOiAoXG4gICAgICB0aGlzOiBUaGlzQXJnLFxuICAgICAgdmFsdWU6IHN0cmluZyxcbiAgICAgIG5hbWU6IHN0cmluZyxcbiAgICAgIHBhcmVudDogdGhpc1xuICAgICkgPT4gdm9pZCxcbiAgICB0aGlzQXJnPzogVGhpc0FyZ1xuICApIHtcbiAgICBmb3IgKGNvbnN0IFtuYW1lLCB2YWx1ZV0gb2YgdGhpcy5lbnRyaWVzKCkpIHtcbiAgICAgIGNhbGxiYWNrLmNhbGwodGhpc0FyZywgdmFsdWUsIG5hbWUsIHRoaXMpO1xuICAgIH1cbiAgfVxufVxuIiwgIi8vIE1JVCBMaWNlbnNlXG5cbi8vIENvcHlyaWdodCAoYykgMjAxNyBtb2xzc29uXG5cbi8vIFBlcm1pc3Npb24gaXMgaGVyZWJ5IGdyYW50ZWQsIGZyZWUgb2YgY2hhcmdlLCB0byBhbnkgcGVyc29uIG9idGFpbmluZyBhIGNvcHlcbi8vIG9mIHRoaXMgc29mdHdhcmUgYW5kIGFzc29jaWF0ZWQgZG9jdW1lbnRhdGlvbiBmaWxlcyAodGhlIFwiU29mdHdhcmVcIiksIHRvIGRlYWxcbi8vIGluIHRoZSBTb2Z0d2FyZSB3aXRob3V0IHJlc3RyaWN0aW9uLCBpbmNsdWRpbmcgd2l0aG91dCBsaW1pdGF0aW9uIHRoZSByaWdodHNcbi8vIHRvIHVzZSwgY29weSwgbW9kaWZ5LCBtZXJnZSwgcHVibGlzaCwgZGlzdHJpYnV0ZSwgc3VibGljZW5zZSwgYW5kL29yIHNlbGxcbi8vIGNvcGllcyBvZiB0aGUgU29mdHdhcmUsIGFuZCB0byBwZXJtaXQgcGVyc29ucyB0byB3aG9tIHRoZSBTb2Z0d2FyZSBpc1xuLy8gZnVybmlzaGVkIHRvIGRvIHNvLCBzdWJqZWN0IHRvIHRoZSBmb2xsb3dpbmcgY29uZGl0aW9uczpcblxuLy8gVGhlIGFib3ZlIGNvcHlyaWdodCBub3RpY2UgYW5kIHRoaXMgcGVybWlzc2lvbiBub3RpY2Ugc2hhbGwgYmUgaW5jbHVkZWQgaW4gYWxsXG4vLyBjb3BpZXMgb3Igc3Vic3RhbnRpYWwgcG9ydGlvbnMgb2YgdGhlIFNvZnR3YXJlLlxuXG4vLyBUSEUgU09GVFdBUkUgSVMgUFJPVklERUQgXCJBUyBJU1wiLCBXSVRIT1VUIFdBUlJBTlRZIE9GIEFOWSBLSU5ELCBFWFBSRVNTIE9SXG4vLyBJTVBMSUVELCBJTkNMVURJTkcgQlVUIE5PVCBMSU1JVEVEIFRPIFRIRSBXQVJSQU5USUVTIE9GIE1FUkNIQU5UQUJJTElUWSxcbi8vIEZJVE5FU1MgRk9SIEEgUEFSVElDVUxBUiBQVVJQT1NFIEFORCBOT05JTkZSSU5HRU1FTlQuIElOIE5PIEVWRU5UIFNIQUxMIFRIRVxuLy8gQVVUSE9SUyBPUiBDT1BZUklHSFQgSE9MREVSUyBCRSBMSUFCTEUgRk9SIEFOWSBDTEFJTSwgREFNQUdFUyBPUiBPVEhFUlxuLy8gTElBQklMSVRZLCBXSEVUSEVSIElOIEFOIEFDVElPTiBPRiBDT05UUkFDVCwgVE9SVCBPUiBPVEhFUldJU0UsIEFSSVNJTkcgRlJPTSxcbi8vIE9VVCBPRiBPUiBJTiBDT05ORUNUSU9OIFdJVEggVEhFIFNPRlRXQVJFIE9SIFRIRSBVU0UgT1IgT1RIRVIgREVBTElOR1MgSU4gVEhFXG4vLyBTT0ZUV0FSRS5cblxuaW1wb3J0IEV2ZW50RW1pdHRlciBmcm9tICcuLi9ldmVudCc7XG5cbmludGVyZmFjZSBBYm9ydEV2ZW50IHtcbiAgdHlwZTogJ2Fib3J0JztcbiAgcmVhc29uPzogYW55O1xufVxuXG5leHBvcnQgY2xhc3MgQWJvcnRTaWduYWwgZXh0ZW5kcyBFdmVudEVtaXR0ZXIge1xuICBwcml2YXRlIF9hYm9ydGVkOiBib29sZWFuO1xuICBwcml2YXRlIF9yZWFzb246IGFueTtcblxuICBwdWJsaWMgb25hYm9ydDogKC4uLmFyZ3M6IHVua25vd25bXSkgPT4gdm9pZDtcblxuICBnZXQgYWJvcnRlZCgpIHtcbiAgICByZXR1cm4gdGhpcy5fYWJvcnRlZDtcbiAgfVxuXG4gIGdldCByZWFzb24oKSB7XG4gICAgcmV0dXJuIHRoaXMuX3JlYXNvbjtcbiAgfVxuXG4gIHByaXZhdGUgY29uc3RydWN0b3IoKSB7XG4gICAgc3VwZXIoKTtcbiAgICB0aGlzLl9hYm9ydGVkID0gZmFsc2U7XG4gIH1cblxuICBnZXQgW1N5bWJvbC50b1N0cmluZ1RhZ10oKSB7XG4gICAgcmV0dXJuICdbb2JqZWN0IEFib3J0U2lnbmFsXSc7XG4gIH1cblxuICBkaXNwYXRjaEV2ZW50KGV2ZW50OiBBYm9ydEV2ZW50KSB7XG4gICAgaWYgKGV2ZW50LnR5cGUgPT09ICdhYm9ydCcpIHtcbiAgICAgIHRoaXMuX2Fib3J0ZWQgPSB0cnVlO1xuICAgICAgdGhpcy5fcmVhc29uID0gZXZlbnQucmVhc29uO1xuICAgICAgaWYgKHR5cGVvZiB0aGlzLm9uYWJvcnQgPT09ICdmdW5jdGlvbicpIHtcbiAgICAgICAgdGhpcy5vbmFib3J0LmNhbGwodGhpcywgZXZlbnQpO1xuICAgICAgfVxuICAgIH1cblxuICAgIHN1cGVyLmVtaXQoZXZlbnQudHlwZSwgZXZlbnQpO1xuICB9XG5cbiAgYWRkRXZlbnRMaXN0ZW5lcih0eXBlOiBzdHJpbmcsIGxpc3RlbmVyOiAoLi4uYXJnczogdW5rbm93bltdKSA9PiB2b2lkKSB7XG4gICAgc3VwZXIuYWRkTGlzdGVuZXIodHlwZSwgbGlzdGVuZXIpO1xuICB9XG5cbiAgcmVtb3ZlRXZlbnRMaXN0ZW5lcih0eXBlOiBzdHJpbmcsIGxpc3RlbmVyOiAoLi4uYXJnczogdW5rbm93bltdKSA9PiB2b2lkKSB7XG4gICAgc3VwZXIucmVtb3ZlTGlzdGVuZXIodHlwZSwgbGlzdGVuZXIpO1xuICB9XG5cbiAgc3RhdGljIF9fY3JlYXRlKCkge1xuICAgIHJldHVybiBuZXcgQWJvcnRTaWduYWwoKTtcbiAgfVxufVxuXG5leHBvcnQgY2xhc3MgQWJvcnRDb250cm9sbGVyIHtcbiAgcHJpdmF0ZSBfc2lnbmFsOiBBYm9ydFNpZ25hbDtcbiAgZ2V0IHNpZ25hbCgpIHtcbiAgICByZXR1cm4gdGhpcy5fc2lnbmFsO1xuICB9XG5cbiAgY29uc3RydWN0b3IoKSB7XG4gICAgdGhpcy5fc2lnbmFsID0gQWJvcnRTaWduYWwuX19jcmVhdGUoKTtcbiAgfVxuXG4gIGFib3J0KHJlYXNvbj86IGFueSkge1xuICAgIGxldCBzaWduYWxSZWFzb24gPSByZWFzb247XG4gICAgaWYgKHNpZ25hbFJlYXNvbiA9PT0gdW5kZWZpbmVkKSB7XG4gICAgICBzaWduYWxSZWFzb24gPSBuZXcgRXJyb3IoJ1RoaXMgb3BlcmF0aW9uIHdhcyBhYm9ydGVkJyk7XG4gICAgICBzaWduYWxSZWFzb24ubmFtZSA9ICdBYm9ydEVycm9yJztcbiAgICB9XG5cbiAgICBjb25zdCBldmVudDogQWJvcnRFdmVudCA9IHtcbiAgICAgIHR5cGU6ICdhYm9ydCcsXG4gICAgICByZWFzb246IHNpZ25hbFJlYXNvbixcbiAgICB9O1xuXG4gICAgdGhpcy5zaWduYWwuZGlzcGF0Y2hFdmVudChldmVudCk7XG4gIH1cblxuICBnZXQgW1N5bWJvbC50b1N0cmluZ1RhZ10oKSB7XG4gICAgcmV0dXJuICdbb2JqZWN0IEFib3J0Q29udHJvbGxlcl0nO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IHsgQm9keU1peGluIH0gZnJvbSAnLi9Cb2R5TWl4aW4nO1xuaW1wb3J0IHsgSGVhZGVycyB9IGZyb20gJy4vSGVhZGVycyc7XG5pbXBvcnQgeyBBYm9ydENvbnRyb2xsZXIsIEFib3J0U2lnbmFsIH0gZnJvbSAnLi9BYm9ydENvbnRyb2xsZXInO1xuXG50eXBlIFJlcXVlc3RMeW54RXh0ZW5zaW9uID0gUmVjb3JkPHN0cmluZywgYW55PjtcblxuaW50ZXJmYWNlIFJlcXVlc3RJbml0SW5uZXIgZXh0ZW5kcyBSZXF1ZXN0SW5pdCB7XG4gIGx5bnhFeHRlbnNpb24/OiBSZXF1ZXN0THlueEV4dGVuc2lvbjtcbn1cblxuZXhwb3J0IGNsYXNzIFJlcXVlc3QgZXh0ZW5kcyBCb2R5TWl4aW4ge1xuICBwcml2YXRlIF91cmw6IHN0cmluZztcbiAgcHJpdmF0ZSBfaGVhZGVyczogSGVhZGVycztcbiAgcHJpdmF0ZSBfbWV0aG9kOiBzdHJpbmc7XG4gIHByaXZhdGUgX3NpZ25hbDogQWJvcnRTaWduYWw7XG4gIHByaXZhdGUgX2x5bnhFeHRlbnNpb246IFJlcXVlc3RMeW54RXh0ZW5zaW9uO1xuXG4gIGdldCB1cmwoKSB7XG4gICAgcmV0dXJuIHRoaXMuX3VybDtcbiAgfVxuXG4gIGdldCBoZWFkZXJzKCkge1xuICAgIHJldHVybiB0aGlzLl9oZWFkZXJzO1xuICB9XG5cbiAgZ2V0IG1ldGhvZCgpIHtcbiAgICByZXR1cm4gdGhpcy5fbWV0aG9kO1xuICB9XG5cbiAgZ2V0IHNpZ25hbCgpIHtcbiAgICByZXR1cm4gdGhpcy5fc2lnbmFsO1xuICB9XG5cbiAgZ2V0IGx5bnhFeHRlbnNpb24oKSB7XG4gICAgcmV0dXJuIHRoaXMuX2x5bnhFeHRlbnNpb247XG4gIH1cblxuICBjb25zdHJ1Y3RvcihpbnB1dDogUmVxdWVzdEluZm8sIG9wdGlvbnM/OiBSZXF1ZXN0SW5pdElubmVyKSB7XG4gICAgc3VwZXIoKTtcbiAgICBvcHRpb25zID0gb3B0aW9ucyB8fCB7fTtcblxuICAgIGlmIChpbnB1dCBpbnN0YW5jZW9mIFJlcXVlc3QpIHtcbiAgICAgIGlmIChpbnB1dC5ib2R5VXNlZCkge1xuICAgICAgICB0aHJvdyBuZXcgVHlwZUVycm9yKCdBbHJlYWR5IHJlYWQnKTtcbiAgICAgIH1cbiAgICAgIHRoaXMuX3VybCA9IGlucHV0LnVybDtcbiAgICAgIGlmICghb3B0aW9ucy5oZWFkZXJzKSB7XG4gICAgICAgIHRoaXMuX2hlYWRlcnMgPSBuZXcgSGVhZGVycyhpbnB1dC5oZWFkZXJzIGFzIGdsb2JhbFRoaXMuSGVhZGVycyk7XG4gICAgICB9XG4gICAgICB0aGlzLl9tZXRob2QgPSBpbnB1dC5tZXRob2Q7XG4gICAgICB0aGlzLl9zaWduYWwgPSAoaW5wdXQuc2lnbmFsIGFzIGFueSkgYXMgQWJvcnRTaWduYWw7XG4gICAgICB0aGlzLnNldEJvZHkoaW5wdXQuX2FycmF5QnVmZmVyKTtcbiAgICB9IGVsc2Uge1xuICAgICAgdGhpcy5fdXJsID0gU3RyaW5nKGlucHV0KTtcbiAgICB9XG5cbiAgICBpZiAob3B0aW9ucy5oZWFkZXJzIHx8ICF0aGlzLmhlYWRlcnMpIHtcbiAgICAgIHRoaXMuX2hlYWRlcnMgPSBuZXcgSGVhZGVycyhvcHRpb25zLmhlYWRlcnMpO1xuICAgIH1cbiAgICB0aGlzLl9tZXRob2QgPSBvcHRpb25zLm1ldGhvZCB8fCB0aGlzLm1ldGhvZCB8fCAnR0VUJztcbiAgICB0aGlzLl9tZXRob2QgPSB0aGlzLl9tZXRob2QudG9VcHBlckNhc2UoKTtcblxuICAgIGlmICgodGhpcy5tZXRob2QgPT09ICdHRVQnIHx8IHRoaXMubWV0aG9kID09PSAnSEVBRCcpICYmIG9wdGlvbnMuYm9keSkge1xuICAgICAgdGhyb3cgbmV3IFR5cGVFcnJvcignQm9keSBub3QgYWxsb3dlZCBmb3IgR0VUIG9yIEhFQUQgcmVxdWVzdHMnKTtcbiAgICB9XG5cbiAgICBpZiAodHlwZW9mIG9wdGlvbnMuc2lnbmFsICE9PSAndW5kZWZpbmVkJykge1xuICAgICAgdGhpcy5fc2lnbmFsID0gKG9wdGlvbnMuc2lnbmFsIGFzIGFueSkgYXMgQWJvcnRTaWduYWw7XG4gICAgfVxuICAgIHRoaXMuX3NpZ25hbCA9IHRoaXMuX3NpZ25hbCB8fCBBYm9ydFNpZ25hbC5fX2NyZWF0ZSgpO1xuXG4gICAgdGhpcy5fbHlueEV4dGVuc2lvbiA9IG9wdGlvbnMubHlueEV4dGVuc2lvbiB8fCB7fTtcblxuICAgIGlmICghdGhpcy5faGVhZGVycy5nZXQoJ0NvbnRlbnQtVHlwZScpKSB7XG4gICAgICBpZiAodHlwZW9mIG9wdGlvbnMuYm9keSA9PT0gJ3N0cmluZycpIHtcbiAgICAgICAgdGhpcy5faGVhZGVycy5zZXQoJ0NvbnRlbnQtVHlwZScsICd0ZXh0L3BsYWluO2NoYXJzZXQ9VVRGLTgnKTtcbiAgICAgIH0gZWxzZSBpZiAoXG4gICAgICAgIGdsb2JhbFRoaXMuVVJMU2VhcmNoUGFyYW1zICYmXG4gICAgICAgIG9wdGlvbnMuYm9keSBpbnN0YW5jZW9mIFVSTFNlYXJjaFBhcmFtc1xuICAgICAgKSB7XG4gICAgICAgIHRoaXMuX2hlYWRlcnMuc2V0KFxuICAgICAgICAgICdDb250ZW50LVR5cGUnLFxuICAgICAgICAgICdhcHBsaWNhdGlvbi94LXd3dy1mb3JtLXVybGVuY29kZWQ7Y2hhcnNldD1VVEYtOCdcbiAgICAgICAgKTtcbiAgICAgIH0gZWxzZSBpZiAob3B0aW9ucy5ib2R5IGluc3RhbmNlb2YgQXJyYXlCdWZmZXIpIHtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHRoaXMuX2hlYWRlcnMuc2V0KCdDb250ZW50LVR5cGUnLCAndGV4dC9wbGFpbjtjaGFyc2V0PVVURi04Jyk7XG4gICAgICB9XG4gICAgfVxuXG4gICAgdGhpcy5zZXRCb2R5KG9wdGlvbnMuYm9keSk7XG4gIH1cblxuICBwdWJsaWMgY2xvbmUoKTogUmVxdWVzdCB7XG4gICAgY29uc3QgY2xvbmVkID0gbmV3IFJlcXVlc3QodGhpcyBhcyBhbnksIHtcbiAgICAgIG1ldGhvZDogdGhpcy5tZXRob2QsXG4gICAgfSk7XG5cbiAgICBjbG9uZWQuc2V0Qm9keSh0aGlzKTtcbiAgICByZXR1cm4gY2xvbmVkO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IHsgQm9keU1peGluIH0gZnJvbSAnLi9Cb2R5TWl4aW4nO1xuXG50eXBlIFJlc3BvbnNlTHlueEV4dGVuc2lvbiA9IFJlY29yZDxzdHJpbmcsIGFueT47XG5cbmludGVyZmFjZSBSZXNwb25zZUluaXRJbm5lciBleHRlbmRzIFJlc3BvbnNlSW5pdCB7XG4gIHVybD86IHN0cmluZztcbiAgbHlueEV4dGVuc2lvbj86IFJlc3BvbnNlTHlueEV4dGVuc2lvbjtcbn1cblxuZXhwb3J0IGNsYXNzIFJlc3BvbnNlIGV4dGVuZHMgQm9keU1peGluIHtcbiAgcHJpdmF0ZSBfdXJsOiBzdHJpbmc7XG4gIHByaXZhdGUgX3N0YXR1czogbnVtYmVyO1xuICBwcml2YXRlIF9zdGF0dXNUZXh0OiBzdHJpbmc7XG4gIHByaXZhdGUgX29rOiBib29sZWFuO1xuICBwcml2YXRlIF9oZWFkZXJzOiBIZWFkZXJzO1xuICBwcml2YXRlIF9seW54RXh0ZW5zaW9uOiBSZXNwb25zZUx5bnhFeHRlbnNpb247XG5cbiAgZ2V0IHVybCgpIHtcbiAgICByZXR1cm4gdGhpcy5fdXJsO1xuICB9XG5cbiAgZ2V0IHN0YXR1cygpIHtcbiAgICByZXR1cm4gdGhpcy5fc3RhdHVzO1xuICB9XG5cbiAgZ2V0IHN0YXR1c1RleHQoKSB7XG4gICAgcmV0dXJuIHRoaXMuX3N0YXR1c1RleHQ7XG4gIH1cblxuICBnZXQgb2soKSB7XG4gICAgcmV0dXJuIHRoaXMuX29rO1xuICB9XG5cbiAgZ2V0IGhlYWRlcnMoKSB7XG4gICAgcmV0dXJuIHRoaXMuX2hlYWRlcnM7XG4gIH1cblxuICBnZXQgbHlueEV4dGVuc2lvbigpIHtcbiAgICByZXR1cm4gdGhpcy5fbHlueEV4dGVuc2lvbjtcbiAgfVxuXG4gIGNvbnN0cnVjdG9yKGJvZHlJbml0PzogQm9keUluaXQsIG9wdGlvbnM/OiBSZXNwb25zZUluaXRJbm5lcikge1xuICAgIHN1cGVyKCk7XG4gICAgb3B0aW9ucyA9IG9wdGlvbnMgfHwge307XG5cbiAgICB0aGlzLl9zdGF0dXMgPSBvcHRpb25zLnN0YXR1cyA9PT0gdW5kZWZpbmVkID8gMjAwIDogb3B0aW9ucy5zdGF0dXM7XG4gICAgaWYgKHRoaXMuX3N0YXR1cyA8IDIwMCB8fCB0aGlzLl9zdGF0dXMgPiA1OTkpIHtcbiAgICAgIHRocm93IG5ldyBSYW5nZUVycm9yKFxuICAgICAgICBcIkZhaWxlZCB0byBjb25zdHJ1Y3QgJ1Jlc3BvbnNlJzogVGhlIHN0YXR1cyBwcm92aWRlZCAoMCkgaXMgb3V0c2lkZSB0aGUgcmFuZ2UgWzIwMCwgNTk5XS5cIlxuICAgICAgKTtcbiAgICB9XG4gICAgdGhpcy5fb2sgPSB0aGlzLl9zdGF0dXMgPj0gMjAwICYmIHRoaXMuX3N0YXR1cyA8IDMwMDtcbiAgICB0aGlzLl9zdGF0dXNUZXh0ID1cbiAgICAgIG9wdGlvbnMuc3RhdHVzVGV4dCA9PT0gdW5kZWZpbmVkID8gJycgOiAnJyArIG9wdGlvbnMuc3RhdHVzVGV4dDtcbiAgICB0aGlzLl9oZWFkZXJzID0gbmV3IEhlYWRlcnMob3B0aW9ucy5oZWFkZXJzKTtcbiAgICB0aGlzLl91cmwgPSBvcHRpb25zLnVybCB8fCAnJztcbiAgICB0aGlzLl9seW54RXh0ZW5zaW9uID0gb3B0aW9ucy5seW54RXh0ZW5zaW9uIHx8IHt9O1xuICAgIHRoaXMuc2V0Qm9keShib2R5SW5pdCk7XG4gIH1cblxuICBwdWJsaWMgY2xvbmUoKTogUmVzcG9uc2Uge1xuICAgIGNvbnN0IGNsb25lZCA9IG5ldyBSZXNwb25zZShudWxsLCB7XG4gICAgICBzdGF0dXM6IHRoaXMuX3N0YXR1cyxcbiAgICAgIHN0YXR1c1RleHQ6IHRoaXMuX3N0YXR1c1RleHQsXG4gICAgICBoZWFkZXJzOiBuZXcgSGVhZGVycyh0aGlzLl9oZWFkZXJzKSxcbiAgICAgIHVybDogdGhpcy5fdXJsLFxuICAgIH0pO1xuXG4gICAgY2xvbmVkLnNldEJvZHkodGhpcyk7XG5cbiAgICByZXR1cm4gY2xvbmVkO1xuICB9XG59XG4iLCAiLyoqXG4gKiBDb3B5cmlnaHQgKGMpIE1ldGEgUGxhdGZvcm1zLCBJbmMuIGFuZCBhZmZpbGlhdGVzLlxuICpcbiAqIFRoaXMgc291cmNlIGNvZGUgaXMgbGljZW5zZWQgdW5kZXIgdGhlIE1JVCBsaWNlbnNlIGZvdW5kIGluIHRoZVxuICogTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuICpcbiAqL1xuXG5mdW5jdGlvbiB2YWxpZGF0ZUJhc2VVcmwodXJsKSB7XG4gICAgLy8gZnJvbSB0aGlzIE1JVC1saWNlbnNlZCBnaXN0OiBodHRwczovL2dpc3QuZ2l0aHViLmNvbS9kcGVyaW5pLzcyOTI5NFxuICAgIHJldHVybiAvXig/Oig/Oig/Omh0dHBzP3xmdHApOik/XFwvXFwvKSg/Oig/OlsxLTldXFxkP3wxXFxkXFxkfDJbMDFdXFxkfDIyWzAtM10pKD86XFwuKD86MT9cXGR7MSwyfXwyWzAtNF1cXGR8MjVbMC01XSkpezJ9KD86XFwuKD86WzEtOV1cXGQ/fDFcXGRcXGR8MlswLTRdXFxkfDI1WzAtNF0pKXwoPzooPzpbYS16MC05XFx1MDBhMS1cXHVmZmZmXVthLXowLTlcXHUwMGExLVxcdWZmZmZfLV17MCw2Mn0pP1thLXowLTlcXHUwMGExLVxcdWZmZmZdXFwuKSooPzpbYS16XFx1MDBhMS1cXHVmZmZmXXsyLH1cXC4/KSkoPzo6XFxkezIsNX0pPyg/OlsvPyNdXFxTKik/JC8udGVzdChcbiAgICAgIHVybCxcbiAgICApO1xuICB9XG4gIFxuZXhwb3J0IGNsYXNzIFVSTCB7XG4gICAgX3VybDtcbiAgICBfc2VhcmNoUGFyYW1zSW5zdGFuY2UgPSBudWxsO1xuICBcbiAgICBjb25zdHJ1Y3Rvcih1cmwsIGJhc2UpIHtcbiAgICAgIGxldCBiYXNlVXJsID0gbnVsbDtcbiAgICAgIGlmICghYmFzZSB8fCB2YWxpZGF0ZUJhc2VVcmwodXJsKSkge1xuICAgICAgICB0aGlzLl91cmwgPSB1cmw7XG4gICAgICAgIGlmICghdGhpcy5fdXJsLmVuZHNXaXRoKCcvJykpIHtcbiAgICAgICAgICB0aGlzLl91cmwgKz0gJy8nO1xuICAgICAgICB9XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBpZiAodHlwZW9mIGJhc2UgPT09ICdzdHJpbmcnKSB7XG4gICAgICAgICAgYmFzZVVybCA9IGJhc2U7XG4gICAgICAgICAgaWYgKCF2YWxpZGF0ZUJhc2VVcmwoYmFzZVVybCkpIHtcbiAgICAgICAgICAgIHRocm93IG5ldyBUeXBlRXJyb3IoYEludmFsaWQgYmFzZSBVUkw6ICR7YmFzZVVybH1gKTtcbiAgICAgICAgICB9XG4gICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgYmFzZVVybCA9IGJhc2UudG9TdHJpbmcoKTtcbiAgICAgICAgfVxuICAgICAgICBpZiAoYmFzZVVybC5lbmRzV2l0aCgnLycpKSB7XG4gICAgICAgICAgYmFzZVVybCA9IGJhc2VVcmwuc2xpY2UoMCwgYmFzZVVybC5sZW5ndGggLSAxKTtcbiAgICAgICAgfVxuICAgICAgICBpZiAoIXVybC5zdGFydHNXaXRoKCcvJykpIHtcbiAgICAgICAgICB1cmwgPSBgLyR7dXJsfWA7XG4gICAgICAgIH1cbiAgICAgICAgaWYgKGJhc2VVcmwuZW5kc1dpdGgodXJsKSkge1xuICAgICAgICAgIHVybCA9ICcnO1xuICAgICAgICB9XG4gICAgICAgIHRoaXMuX3VybCA9IGAke2Jhc2VVcmx9JHt1cmx9YDtcbiAgICAgIH1cbiAgICB9XG5cbiAgICBnZXQgaHJlZigpIHtcbiAgICAgIHJldHVybiB0aGlzLnRvU3RyaW5nKCk7XG4gICAgfVxuICBcbiAgICBnZXQgc2VhcmNoUGFyYW1zKCkge1xuICAgICAgaWYgKHRoaXMuX3NlYXJjaFBhcmFtc0luc3RhbmNlID09IG51bGwpIHtcbiAgICAgICAgdGhpcy5fc2VhcmNoUGFyYW1zSW5zdGFuY2UgPSBuZXcgVVJMU2VhcmNoUGFyYW1zKCk7XG4gICAgICB9XG4gICAgICByZXR1cm4gdGhpcy5fc2VhcmNoUGFyYW1zSW5zdGFuY2U7XG4gICAgfVxuICBcbiAgICB0b0pTT04oKSB7XG4gICAgICByZXR1cm4gdGhpcy50b1N0cmluZygpO1xuICAgIH1cbiAgXG4gICAgdG9TdHJpbmcoKSB7XG4gICAgICBpZiAodGhpcy5fc2VhcmNoUGFyYW1zSW5zdGFuY2UgPT09IG51bGwpIHtcbiAgICAgICAgcmV0dXJuIHRoaXMuX3VybDtcbiAgICAgIH1cbiAgXG4gICAgICBjb25zdCBpbnN0YW5jZVN0cmluZyA9IHRoaXMuX3NlYXJjaFBhcmFtc0luc3RhbmNlLnRvU3RyaW5nKCk7XG4gICAgICBjb25zdCBzZXBhcmF0b3IgPSB0aGlzLl91cmwuaW5kZXhPZignPycpID4gLTEgPyAnJicgOiAnPyc7XG4gICAgICByZXR1cm4gdGhpcy5fdXJsICsgc2VwYXJhdG9yICsgaW5zdGFuY2VTdHJpbmc7XG4gICAgfVxuICB9XG4gICIsICIvLyBNSVQgTGljZW5zZVxuXG4vLyBDb3B5cmlnaHQgKGMpIDIwMTYgSmVycnkgQmVuZHlcblxuLy8gUGVybWlzc2lvbiBpcyBoZXJlYnkgZ3JhbnRlZCwgZnJlZSBvZiBjaGFyZ2UsIHRvIGFueSBwZXJzb24gb2J0YWluaW5nIGEgY29weVxuLy8gb2YgdGhpcyBzb2Z0d2FyZSBhbmQgYXNzb2NpYXRlZCBkb2N1bWVudGF0aW9uIGZpbGVzICh0aGUgXCJTb2Z0d2FyZVwiKSwgdG8gZGVhbFxuLy8gaW4gdGhlIFNvZnR3YXJlIHdpdGhvdXQgcmVzdHJpY3Rpb24sIGluY2x1ZGluZyB3aXRob3V0IGxpbWl0YXRpb24gdGhlIHJpZ2h0c1xuLy8gdG8gdXNlLCBjb3B5LCBtb2RpZnksIG1lcmdlLCBwdWJsaXNoLCBkaXN0cmlidXRlLCBzdWJsaWNlbnNlLCBhbmQvb3Igc2VsbFxuLy8gY29waWVzIG9mIHRoZSBTb2Z0d2FyZSwgYW5kIHRvIHBlcm1pdCBwZXJzb25zIHRvIHdob20gdGhlIFNvZnR3YXJlIGlzXG4vLyBmdXJuaXNoZWQgdG8gZG8gc28sIHN1YmplY3QgdG8gdGhlIGZvbGxvd2luZyBjb25kaXRpb25zOlxuXG4vLyBUaGUgYWJvdmUgY29weXJpZ2h0IG5vdGljZSBhbmQgdGhpcyBwZXJtaXNzaW9uIG5vdGljZSBzaGFsbCBiZSBpbmNsdWRlZCBpbiBhbGxcbi8vIGNvcGllcyBvciBzdWJzdGFudGlhbCBwb3J0aW9ucyBvZiB0aGUgU29mdHdhcmUuXG5cbi8vIFRIRSBTT0ZUV0FSRSBJUyBQUk9WSURFRCBcIkFTIElTXCIsIFdJVEhPVVQgV0FSUkFOVFkgT0YgQU5ZIEtJTkQsIEVYUFJFU1MgT1Jcbi8vIElNUExJRUQsIElOQ0xVRElORyBCVVQgTk9UIExJTUlURUQgVE8gVEhFIFdBUlJBTlRJRVMgT0YgTUVSQ0hBTlRBQklMSVRZLFxuLy8gRklUTkVTUyBGT1IgQSBQQVJUSUNVTEFSIFBVUlBPU0UgQU5EIE5PTklORlJJTkdFTUVOVC4gSU4gTk8gRVZFTlQgU0hBTEwgVEhFXG4vLyBBVVRIT1JTIE9SIENPUFlSSUdIVCBIT0xERVJTIEJFIExJQUJMRSBGT1IgQU5ZIENMQUlNLCBEQU1BR0VTIE9SIE9USEVSXG4vLyBMSUFCSUxJVFksIFdIRVRIRVIgSU4gQU4gQUNUSU9OIE9GIENPTlRSQUNULCBUT1JUIE9SIE9USEVSV0lTRSwgQVJJU0lORyBGUk9NLFxuLy8gT1VUIE9GIE9SIElOIENPTk5FQ1RJT04gV0lUSCBUSEUgU09GVFdBUkUgT1IgVEhFIFVTRSBPUiBPVEhFUiBERUFMSU5HUyBJTiBUSEVcbi8vIFNPRlRXQVJFLlxuXG4vKiohXG4gKiB1cmwtc2VhcmNoLXBhcmFtcy1wb2x5ZmlsbFxuICpcbiAqIEBhdXRob3IgSmVycnkgQmVuZHkgKGh0dHBzOi8vZ2l0aHViLmNvbS9qZXJyeWJlbmR5KVxuICogQGxpY2VuY2UgTUlUXG4gKi9cblxuZXhwb3J0IGZ1bmN0aW9uIFVSTFNlYXJjaFBhcmFtc1BvbHlmaWxsKHNlbGYpIHtcbiAgICAndXNlIHN0cmljdCc7XG4gICAgY29uc3QgX19VUkxTZWFyY2hQYXJhbXNfXyA9IFwiX19VUkxTZWFyY2hQYXJhbXNfX1wiO1xuLyoqXG4gKiBNYWtlIGEgVVJMU2VhcmNoUGFyYW1zIGluc3RhbmNlXG4gKlxuICogQHBhcmFtIHtvYmplY3R8c3RyaW5nfFVSTFNlYXJjaFBhcmFtc30gc2VhcmNoXG4gKiBAY29uc3RydWN0b3JcbiAqL1xuZnVuY3Rpb24gVVJMU2VhcmNoUGFyYW1zUG9seWZpbGwoc2VhcmNoKSB7XG4gICAgc2VhcmNoID0gc2VhcmNoIHx8IFwiXCI7XG5cbiAgICAvLyBzdXBwb3J0IGNvbnN0cnVjdCBvYmplY3Qgd2l0aCBhbm90aGVyIFVSTFNlYXJjaFBhcmFtcyBpbnN0YW5jZVxuICAgIGlmIChzZWFyY2ggaW5zdGFuY2VvZiBVUkxTZWFyY2hQYXJhbXMpIHtcbiAgICAgICAgc2VhcmNoID0gc2VhcmNoLnRvU3RyaW5nKCk7XG4gICAgfVxuICAgIHRoaXMgW19fVVJMU2VhcmNoUGFyYW1zX19dID0gcGFyc2VUb0RpY3Qoc2VhcmNoKTtcbn1cblxuY29uc3QgcHJvdG90eXBlID0gVVJMU2VhcmNoUGFyYW1zUG9seWZpbGwucHJvdG90eXBlO1xuXG4vKipcbiAqIEFwcGVuZHMgYSBzcGVjaWZpZWQga2V5L3ZhbHVlIHBhaXIgYXMgYSBuZXcgc2VhcmNoIHBhcmFtZXRlci5cbiAqXG4gKiBAcGFyYW0ge3N0cmluZ30gbmFtZVxuICogQHBhcmFtIHtzdHJpbmd9IHZhbHVlXG4gKi9cbnByb3RvdHlwZS5hcHBlbmQgPSBmdW5jdGlvbihuYW1lLCB2YWx1ZSkge1xuICAgIGFwcGVuZFRvKHRoaXMgW19fVVJMU2VhcmNoUGFyYW1zX19dLCBuYW1lLCB2YWx1ZSk7XG59O1xuXG4vKipcbiAqIERlbGV0ZXMgdGhlIGdpdmVuIHNlYXJjaCBwYXJhbWV0ZXIsIGFuZCBpdHMgYXNzb2NpYXRlZCB2YWx1ZSxcbiAqIGZyb20gdGhlIGxpc3Qgb2YgYWxsIHNlYXJjaCBwYXJhbWV0ZXJzLlxuICpcbiAqIEBwYXJhbSB7c3RyaW5nfSBuYW1lXG4gKi9cbnByb3RvdHlwZVsnZGVsZXRlJ10gPSBmdW5jdGlvbihuYW1lKSB7XG4gICAgZGVsZXRlIHRoaXMgW19fVVJMU2VhcmNoUGFyYW1zX19dIFtuYW1lXTtcbn07XG5cbi8qKlxuICogUmV0dXJucyB0aGUgZmlyc3QgdmFsdWUgYXNzb2NpYXRlZCB0byB0aGUgZ2l2ZW4gc2VhcmNoIHBhcmFtZXRlci5cbiAqXG4gKiBAcGFyYW0ge3N0cmluZ30gbmFtZVxuICogQHJldHVybnMge3N0cmluZ3xudWxsfVxuICovXG5wcm90b3R5cGUuZ2V0ID0gZnVuY3Rpb24obmFtZSkge1xuICAgIHZhciBkaWN0ID0gdGhpcyBbX19VUkxTZWFyY2hQYXJhbXNfX107XG4gICAgcmV0dXJuIHRoaXMuaGFzKG5hbWUpID8gZGljdFtuYW1lXVswXSA6IG51bGw7XG59O1xuXG4vKipcbiAqIFJldHVybnMgYWxsIHRoZSB2YWx1ZXMgYXNzb2NpYXRpb24gd2l0aCBhIGdpdmVuIHNlYXJjaCBwYXJhbWV0ZXIuXG4gKlxuICogQHBhcmFtIHtzdHJpbmd9IG5hbWVcbiAqIEByZXR1cm5zIHtBcnJheX1cbiAqL1xucHJvdG90eXBlLmdldEFsbCA9IGZ1bmN0aW9uKG5hbWUpIHtcbiAgICB2YXIgZGljdCA9IHRoaXMgW19fVVJMU2VhcmNoUGFyYW1zX19dO1xuICAgIHJldHVybiB0aGlzLmhhcyhuYW1lKSA/IGRpY3QgW25hbWVdLnNsaWNlKDApIDogW107XG59O1xuXG4vKipcbiAqIFJldHVybnMgYSBCb29sZWFuIGluZGljYXRpbmcgaWYgc3VjaCBhIHNlYXJjaCBwYXJhbWV0ZXIgZXhpc3RzLlxuICpcbiAqIEBwYXJhbSB7c3RyaW5nfSBuYW1lXG4gKiBAcmV0dXJucyB7Ym9vbGVhbn1cbiAqL1xucHJvdG90eXBlLmhhcyA9IGZ1bmN0aW9uKG5hbWUpIHtcbiAgICByZXR1cm4gaGFzT3duUHJvcGVydHkodGhpcyBbX19VUkxTZWFyY2hQYXJhbXNfX10sIG5hbWUpO1xufTtcblxuLyoqXG4gKiBTZXRzIHRoZSB2YWx1ZSBhc3NvY2lhdGVkIHRvIGEgZ2l2ZW4gc2VhcmNoIHBhcmFtZXRlciB0b1xuICogdGhlIGdpdmVuIHZhbHVlLiBJZiB0aGVyZSB3ZXJlIHNldmVyYWwgdmFsdWVzLCBkZWxldGUgdGhlXG4gKiBvdGhlcnMuXG4gKlxuICogQHBhcmFtIHtzdHJpbmd9IG5hbWVcbiAqIEBwYXJhbSB7c3RyaW5nfSB2YWx1ZVxuICovXG5wcm90b3R5cGUuc2V0ID0gZnVuY3Rpb24gc2V0KG5hbWUsIHZhbHVlKSB7XG4gICAgdGhpcyBbX19VUkxTZWFyY2hQYXJhbXNfX11bbmFtZV0gPSBbJycgKyB2YWx1ZV07XG59O1xuXG4vKipcbiAqIFJldHVybnMgYSBzdHJpbmcgY29udGFpbmluZyBhIHF1ZXJ5IHN0cmluZyBzdWl0YWJsZSBmb3IgdXNlIGluIGEgVVJMLlxuICpcbiAqIEByZXR1cm5zIHtzdHJpbmd9XG4gKi9cbnByb3RvdHlwZS50b1N0cmluZyA9IGZ1bmN0aW9uKCkge1xuICAgIHZhciBkaWN0ID0gdGhpc1tfX1VSTFNlYXJjaFBhcmFtc19fXSwgcXVlcnkgPSBbXSwgaSwga2V5LCBuYW1lLCB2YWx1ZTtcbiAgICBmb3IgKGtleSBpbiBkaWN0KSB7XG4gICAgICAgIG5hbWUgPSBlbmNvZGUoa2V5KTtcbiAgICAgICAgZm9yIChpID0gMCwgdmFsdWUgPSBkaWN0W2tleV07IGkgPCB2YWx1ZS5sZW5ndGg7IGkrKykge1xuICAgICAgICAgICAgcXVlcnkucHVzaChuYW1lICsgJz0nICsgZW5jb2RlKHZhbHVlW2ldKSk7XG4gICAgICAgIH1cbiAgICB9XG4gICAgcmV0dXJuIHF1ZXJ5LmpvaW4oJyYnKTtcbn07XG5cbnByb3RvdHlwZS5wb2x5ZmlsbCA9IHRydWU7XG5wcm90b3R5cGVbU3ltYm9sLnRvU3RyaW5nVGFnXSA9ICdVUkxTZWFyY2hQYXJhbXMnO1xuXG4vKipcbiAqXG4gKiBAcGFyYW0ge2Z1bmN0aW9ufSBjYWxsYmFja1xuICogQHBhcmFtIHtvYmplY3R9IHRoaXNBcmdcbiAqL1xucHJvdG90eXBlLmZvckVhY2ggPSBmdW5jdGlvbihjYWxsYmFjaywgdGhpc0FyZykge1xuICAgIHZhciBkaWN0ID0gcGFyc2VUb0RpY3QodGhpcy50b1N0cmluZygpKTtcbiAgICBPYmplY3QuZ2V0T3duUHJvcGVydHlOYW1lcyhkaWN0KS5mb3JFYWNoKGZ1bmN0aW9uKG5hbWUpIHtcbiAgICAgICAgZGljdFtuYW1lXS5mb3JFYWNoKGZ1bmN0aW9uKHZhbHVlKSB7XG4gICAgICAgICAgICBjYWxsYmFjay5jYWxsKHRoaXNBcmcsIHZhbHVlLCBuYW1lLCB0aGlzKTtcbiAgICAgICAgfSwgdGhpcyk7XG4gICAgfSwgdGhpcyk7XG59O1xuXG4vKipcbiAqIFNvcnQgYWxsIG5hbWUtdmFsdWUgcGFpcnNcbiAqL1xucHJvdG90eXBlLnNvcnQgPSBmdW5jdGlvbigpIHtcbiAgICB2YXIgZGljdCA9IHBhcnNlVG9EaWN0KHRoaXMudG9TdHJpbmcoKSksIGtleXMgPSBbXSwgaywgaSwgajtcbiAgICBmb3IgKGsgaW4gZGljdCkge1xuICAgICAgICBrZXlzLnB1c2goayk7XG4gICAgfVxuICAgIGtleXMuc29ydCgpO1xuXG4gICAgZm9yIChpID0gMDsgaSA8IGtleXMubGVuZ3RoOyBpKyspIHtcbiAgICAgICAgdGhpc1snZGVsZXRlJ10oa2V5c1tpXSk7XG4gICAgfVxuICAgIGZvciAoaSA9IDA7IGkgPCBrZXlzLmxlbmd0aDsgaSsrKSB7XG4gICAgICAgIHZhciBrZXkgPSBrZXlzW2ldLCB2YWx1ZXMgPSBkaWN0W2tleV07XG4gICAgICAgIGZvciAoaiA9IDA7IGogPCB2YWx1ZXMubGVuZ3RoOyBqKyspIHtcbiAgICAgICAgICAgIHRoaXMuYXBwZW5kKGtleSwgdmFsdWVzW2pdKTtcbiAgICAgICAgfVxuICAgIH1cbn07XG5cbi8qKlxuICogUmV0dXJucyBhbiBpdGVyYXRvciBhbGxvd2luZyB0byBnbyB0aHJvdWdoIGFsbCBrZXlzIG9mXG4gKiB0aGUga2V5L3ZhbHVlIHBhaXJzIGNvbnRhaW5lZCBpbiB0aGlzIG9iamVjdC5cbiAqXG4gKiBAcmV0dXJucyB7ZnVuY3Rpb259XG4gKi9cbnByb3RvdHlwZS5rZXlzID0gZnVuY3Rpb24oKSB7XG4gICAgdmFyIGl0ZW1zID0gW107XG4gICAgdGhpcy5mb3JFYWNoKGZ1bmN0aW9uKGl0ZW0sIG5hbWUpIHtcbiAgICAgICAgaXRlbXMucHVzaChuYW1lKTtcbiAgICB9KTtcbiAgICByZXR1cm4gbWFrZUl0ZXJhdG9yKGl0ZW1zKTtcbn07XG5cbi8qKlxuICogUmV0dXJucyBhbiBpdGVyYXRvciBhbGxvd2luZyB0byBnbyB0aHJvdWdoIGFsbCB2YWx1ZXMgb2ZcbiAqIHRoZSBrZXkvdmFsdWUgcGFpcnMgY29udGFpbmVkIGluIHRoaXMgb2JqZWN0LlxuICpcbiAqIEByZXR1cm5zIHtmdW5jdGlvbn1cbiAqL1xucHJvdG90eXBlLnZhbHVlcyA9IGZ1bmN0aW9uKCkge1xuICAgIHZhciBpdGVtcyA9IFtdO1xuICAgIHRoaXMuZm9yRWFjaChmdW5jdGlvbihpdGVtKSB7XG4gICAgICAgIGl0ZW1zLnB1c2goaXRlbSk7XG4gICAgfSk7XG4gICAgcmV0dXJuIG1ha2VJdGVyYXRvcihpdGVtcyk7XG59O1xuXG4vKipcbiAqIFJldHVybnMgYW4gaXRlcmF0b3IgYWxsb3dpbmcgdG8gZ28gdGhyb3VnaCBhbGwga2V5L3ZhbHVlXG4gKiBwYWlycyBjb250YWluZWQgaW4gdGhpcyBvYmplY3QuXG4gKlxuICogQHJldHVybnMge2Z1bmN0aW9ufVxuICovXG5wcm90b3R5cGUuZW50cmllcyA9IGZ1bmN0aW9uKCkge1xuICAgIHZhciBpdGVtcyA9IFtdO1xuICAgIHRoaXMuZm9yRWFjaChmdW5jdGlvbihpdGVtLCBuYW1lKSB7XG4gICAgICAgIGl0ZW1zLnB1c2goW25hbWUsIGl0ZW1dKTtcbiAgICB9KTtcbiAgICByZXR1cm4gbWFrZUl0ZXJhdG9yKGl0ZW1zKTtcbn07XG5cbnByb3RvdHlwZVtTeW1ib2wuaXRlcmF0b3JdID0gcHJvdG90eXBlLmVudHJpZXM7XG5cbk9iamVjdC5kZWZpbmVQcm9wZXJ0eShwcm90b3R5cGUsICdzaXplJywge1xuICAgIGdldDogZnVuY3Rpb24gKCkge1xuICAgICAgICB2YXIgZGljdCA9IHBhcnNlVG9EaWN0KHRoaXMudG9TdHJpbmcoKSlcbiAgICAgICAgaWYgKHByb3RvdHlwZSA9PT0gdGhpcykge1xuICAgICAgICAgICAgdGhyb3cgbmV3IFR5cGVFcnJvcignSWxsZWdhbCBpbnZvY2F0aW9uIGF0IFVSTFNlYXJjaFBhcmFtcy5pbnZva2VHZXR0ZXInKVxuICAgICAgICB9XG4gICAgICAgIHJldHVybiBPYmplY3Qua2V5cyhkaWN0KS5yZWR1Y2UoZnVuY3Rpb24gKHByZXYsIGN1cikge1xuICAgICAgICAgICAgcmV0dXJuIHByZXYgKyBkaWN0W2N1cl0ubGVuZ3RoO1xuICAgICAgICB9LCAwKTtcbiAgICB9XG59KTtcblxuZnVuY3Rpb24gZW5jb2RlKHN0cikge1xuICAgIHZhciByZXBsYWNlID0ge1xuICAgICAgICAnISc6ICclMjEnLFxuICAgICAgICBcIidcIjogJyUyNycsXG4gICAgICAgICcoJzogJyUyOCcsXG4gICAgICAgICcpJzogJyUyOScsXG4gICAgICAgICd+JzogJyU3RScsXG4gICAgICAgICclMjAnOiAnKycsXG4gICAgICAgICclMDAnOiAnXFx4MDAnXG4gICAgfTtcbiAgICByZXR1cm4gZW5jb2RlVVJJQ29tcG9uZW50KHN0cikucmVwbGFjZSgvWyEnXFwoXFwpfl18JTIwfCUwMC9nLCBmdW5jdGlvbihtYXRjaCkge1xuICAgICAgICByZXR1cm4gcmVwbGFjZVttYXRjaF07XG4gICAgfSk7XG59XG5cbmZ1bmN0aW9uIGRlY29kZShzdHIpIHtcbiAgICByZXR1cm4gc3RyXG4gICAgICAgIC5yZXBsYWNlKC9bICtdL2csICclMjAnKVxuICAgICAgICAucmVwbGFjZSgvKCVbYS1mMC05XXsyfSkrL2lnLCBmdW5jdGlvbihtYXRjaCkge1xuICAgICAgICAgICAgcmV0dXJuIGRlY29kZVVSSUNvbXBvbmVudChtYXRjaCk7XG4gICAgICAgIH0pO1xufVxuXG5mdW5jdGlvbiBtYWtlSXRlcmF0b3IoYXJyKSB7XG4gICAgdmFyIGl0ZXJhdG9yID0ge1xuICAgICAgICBuZXh0OiBmdW5jdGlvbigpIHtcbiAgICAgICAgICAgIHZhciB2YWx1ZSA9IGFyci5zaGlmdCgpO1xuICAgICAgICAgICAgcmV0dXJuIHtkb25lOiB2YWx1ZSA9PT0gdW5kZWZpbmVkLCB2YWx1ZTogdmFsdWV9O1xuICAgICAgICB9XG4gICAgfTtcblxuICAgIGl0ZXJhdG9yW1N5bWJvbC5pdGVyYXRvcl0gPSBmdW5jdGlvbigpIHtcbiAgICAgICAgcmV0dXJuIGl0ZXJhdG9yO1xuICAgIH07XG5cbiAgICByZXR1cm4gaXRlcmF0b3I7XG59XG5cbmZ1bmN0aW9uIHBhcnNlVG9EaWN0KHNlYXJjaCkge1xuICAgIHZhciBkaWN0ID0ge307XG5cbiAgICBpZiAodHlwZW9mIHNlYXJjaCA9PT0gXCJvYmplY3RcIikge1xuICAgICAgICAvLyBpZiBgc2VhcmNoYCBpcyBhbiBhcnJheSwgdHJlYXQgaXQgYXMgYSBzZXF1ZW5jZVxuICAgICAgICBpZiAoaXNBcnJheShzZWFyY2gpKSB7XG4gICAgICAgICAgICBmb3IgKHZhciBpID0gMDsgaSA8IHNlYXJjaC5sZW5ndGg7IGkrKykge1xuICAgICAgICAgICAgICAgIHZhciBpdGVtID0gc2VhcmNoW2ldO1xuICAgICAgICAgICAgICAgIGlmIChpc0FycmF5KGl0ZW0pICYmIGl0ZW0ubGVuZ3RoID09PSAyKSB7XG4gICAgICAgICAgICAgICAgICAgIGFwcGVuZFRvKGRpY3QsIGl0ZW1bMF0sIGl0ZW1bMV0pO1xuICAgICAgICAgICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgICAgICAgICAgIHRocm93IG5ldyBUeXBlRXJyb3IoXCJGYWlsZWQgdG8gY29uc3RydWN0ICdVUkxTZWFyY2hQYXJhbXMnOiBTZXF1ZW5jZSBpbml0aWFsaXplciBtdXN0IG9ubHkgY29udGFpbiBwYWlyIGVsZW1lbnRzXCIpO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cblxuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgICAgZm9yICh2YXIga2V5IGluIHNlYXJjaCkge1xuICAgICAgICAgICAgICAgIGlmIChzZWFyY2guaGFzT3duUHJvcGVydHkoa2V5KSkge1xuICAgICAgICAgICAgICAgICAgICBhcHBlbmRUbyhkaWN0LCBrZXksIHNlYXJjaFtrZXldKTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cblxuICAgIH0gZWxzZSB7XG4gICAgICAgIC8vIHJlbW92ZSBmaXJzdCAnPydcbiAgICAgICAgaWYgKHNlYXJjaC5pbmRleE9mKFwiP1wiKSA9PT0gMCkge1xuICAgICAgICAgICAgc2VhcmNoID0gc2VhcmNoLnNsaWNlKDEpO1xuICAgICAgICB9XG5cbiAgICAgICAgdmFyIHBhaXJzID0gc2VhcmNoLnNwbGl0KFwiJlwiKTtcbiAgICAgICAgZm9yICh2YXIgaiA9IDA7IGogPCBwYWlycy5sZW5ndGg7IGorKykge1xuICAgICAgICAgICAgdmFyIHZhbHVlID0gcGFpcnMgW2pdLFxuICAgICAgICAgICAgICAgIGluZGV4ID0gdmFsdWUuaW5kZXhPZignPScpO1xuXG4gICAgICAgICAgICBpZiAoLTEgPCBpbmRleCkge1xuICAgICAgICAgICAgICAgIGFwcGVuZFRvKGRpY3QsIGRlY29kZSh2YWx1ZS5zbGljZSgwLCBpbmRleCkpLCBkZWNvZGUodmFsdWUuc2xpY2UoaW5kZXggKyAxKSkpO1xuXG4gICAgICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgICAgICAgIGlmICh2YWx1ZSkge1xuICAgICAgICAgICAgICAgICAgICBhcHBlbmRUbyhkaWN0LCBkZWNvZGUodmFsdWUpLCAnJyk7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuICAgICAgICB9XG4gICAgfVxuXG4gICAgcmV0dXJuIGRpY3Q7XG59XG5cbmZ1bmN0aW9uIGFwcGVuZFRvKGRpY3QsIG5hbWUsIHZhbHVlKSB7XG4gICAgdmFyIHZhbCA9IHR5cGVvZiB2YWx1ZSA9PT0gJ3N0cmluZycgPyB2YWx1ZSA6IChcbiAgICAgICAgdmFsdWUgIT09IG51bGwgJiYgdmFsdWUgIT09IHVuZGVmaW5lZCAmJiB0eXBlb2YgdmFsdWUudG9TdHJpbmcgPT09ICdmdW5jdGlvbicgPyB2YWx1ZS50b1N0cmluZygpIDogSlNPTi5zdHJpbmdpZnkodmFsdWUpXG4gICAgKTtcblxuICAgIC8vICM0NyBQcmV2ZW50IHVzaW5nIGBoYXNPd25Qcm9wZXJ0eWAgYXMgYSBwcm9wZXJ0eSBuYW1lXG4gICAgaWYgKGhhc093blByb3BlcnR5KGRpY3QsIG5hbWUpKSB7XG4gICAgICAgIGRpY3RbbmFtZV0ucHVzaCh2YWwpO1xuICAgIH0gZWxzZSB7XG4gICAgICAgIGRpY3RbbmFtZV0gPSBbdmFsXTtcbiAgICB9XG59XG5cbmZ1bmN0aW9uIGlzQXJyYXkodmFsKSB7XG4gICAgcmV0dXJuICEhdmFsICYmICdbb2JqZWN0IEFycmF5XScgPT09IE9iamVjdC5wcm90b3R5cGUudG9TdHJpbmcuY2FsbCh2YWwpO1xufVxuXG5mdW5jdGlvbiBoYXNPd25Qcm9wZXJ0eShvYmosIHByb3ApIHtcbiAgICByZXR1cm4gT2JqZWN0LnByb3RvdHlwZS5oYXNPd25Qcm9wZXJ0eS5jYWxsKG9iaiwgcHJvcCk7XG59XG5cbnNlbGYuVVJMU2VhcmNoUGFyYW1zID0gc2VsZi5VUkxTZWFyY2hQYXJhbXMgPz8gVVJMU2VhcmNoUGFyYW1zUG9seWZpbGw7XG5cbn0iLCAiaW1wb3J0IHsgTHlueCB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCB7IEJhc2VFdmVudE9yaWcsIFRhcmdldCB9IGZyb20gJy4uLy4uLy4uLy4uL3R5cGVzL3R5cGVzL2NvbW1vbi9ldmVudHMnO1xuXG50eXBlIEV2ZW50U291cmNlRXZlbnQgPSB7XG4gIGRhdGE6IHN0cmluZztcbiAgZXZlbnQ/OiBzdHJpbmc7XG4gIGlkPzogc3RyaW5nO1xuICBba2V5OiBzdHJpbmddOiBhbnk7XG59O1xudHlwZSBFdmVudCA9IEJhc2VFdmVudE9yaWc8YW55PjtcblxuaW50ZXJmYWNlIEZldGNoRXZlbnRTb3VyY2VPcHRpb25zIGV4dGVuZHMgUmVxdWVzdEluaXQge31cblxuZXhwb3J0IGZ1bmN0aW9uIGNyZWF0ZUV2ZW50U291cmNlKGZldGNoOiBMeW54WydmZXRjaCddKTogYW55IHtcbiAgcmV0dXJuIGNsYXNzIEV2ZW50U291cmNlIHtcbiAgICBwcml2YXRlIHVybDogc3RyaW5nO1xuICAgIHByaXZhdGUgb3B0aW9uczogRmV0Y2hFdmVudFNvdXJjZU9wdGlvbnM7XG4gICAgcHJpdmF0ZSBsaXN0ZW5lcnM6IFJlY29yZDxzdHJpbmcsIEV2ZW50TGlzdGVuZXJbXT4gPSB7fTtcbiAgICBwcml2YXRlIF9jbG9zZWQ6IGJvb2xlYW47XG4gICAgb25tZXNzYWdlOiAoZXZlbnQ6IEV2ZW50U291cmNlRXZlbnQpID0+IHZvaWQ7XG4gICAgb25lcnJvcjogKGV2ZW50OiBFdmVudCkgPT4gdm9pZDtcbiAgICBvbm9wZW46IChldmVudDogRXZlbnQpID0+IHZvaWQ7XG5cbiAgICBjb25zdHJ1Y3Rvcih1cmw6IHN0cmluZywgb3B0aW9uczogRmV0Y2hFdmVudFNvdXJjZU9wdGlvbnMgPSB7fSkge1xuICAgICAgdGhpcy51cmwgPSB1cmw7XG4gICAgICB0aGlzLm9wdGlvbnMgPSBvcHRpb25zO1xuICAgICAgdGhpcy5fY2xvc2VkID0gZmFsc2U7XG4gICAgICB0aGlzLl9jb25uZWN0KCk7XG4gICAgfVxuXG4gICAgcHVibGljIGNsb3NlKCk6IHZvaWQge1xuICAgICAgdGhpcy5fY2xvc2VkID0gdHJ1ZTtcbiAgICB9XG5cbiAgICBwcml2YXRlIF9kaXNwYXRjaEV2ZW50KHR5cGU6IHN0cmluZywgZXZlbnQ6IEV2ZW50U291cmNlRXZlbnQpOiB2b2lkIHtcbiAgICAgIGNvbnN0IGV2ZW50VG9EaXNwYXRjaDogRXZlbnQgPSB7XG4gICAgICAgIHR5cGU6IHR5cGUsXG4gICAgICAgIGRldGFpbDogZXZlbnQsXG4gICAgICAgIHRpbWVzdGFtcDogRGF0ZS5ub3coKSxcbiAgICAgICAgdGFyZ2V0OiB7fSBhcyBUYXJnZXQsXG4gICAgICAgIGN1cnJlbnRUYXJnZXQ6IHt9IGFzIFRhcmdldCxcbiAgICAgICAgcHJldmVudERlZmF1bHQ6ICgpID0+IHt9LFxuICAgICAgICBzdG9wUHJvcGFnYXRpb246ICgpID0+IHt9LFxuICAgICAgfTtcblxuICAgICAgaWYgKHR5cGUgPT09ICdtZXNzYWdlJyAmJiB0aGlzLm9ubWVzc2FnZSkge1xuICAgICAgICB0aGlzLm9ubWVzc2FnZShldmVudCk7XG4gICAgICB9IGVsc2UgaWYgKHR5cGUgPT09ICdlcnJvcicgJiYgdGhpcy5vbmVycm9yKSB7XG4gICAgICAgIHRoaXMub25lcnJvcihldmVudFRvRGlzcGF0Y2gpO1xuICAgICAgfSBlbHNlIGlmICh0eXBlID09PSAnb3BlbicgJiYgdGhpcy5vbm9wZW4pIHtcbiAgICAgICAgdGhpcy5vbm9wZW4oZXZlbnRUb0Rpc3BhdGNoKTtcbiAgICAgIH1cbiAgICAgIGNvbnN0IGxpc3RlbmVycyA9IHRoaXMubGlzdGVuZXJzW3R5cGVdIHx8IFtdO1xuICAgICAgbGlzdGVuZXJzLmZvckVhY2goKGxpc3RlbmVyKSA9PiBsaXN0ZW5lcihldmVudCBhcyBhbnkpKTtcbiAgICB9XG5cbiAgICBwdWJsaWMgYWRkRXZlbnRMaXN0ZW5lcih0eXBlOiBzdHJpbmcsIGxpc3RlbmVyOiBFdmVudExpc3RlbmVyKTogdm9pZCB7XG4gICAgICB0aGlzLmxpc3RlbmVyc1t0eXBlXSA9IHRoaXMubGlzdGVuZXJzW3R5cGVdIHx8IFtdO1xuICAgICAgdGhpcy5saXN0ZW5lcnNbdHlwZV0ucHVzaChsaXN0ZW5lcik7XG4gICAgfVxuXG4gICAgcHVibGljIHJlbW92ZUV2ZW50TGlzdGVuZXIodHlwZTogc3RyaW5nLCBsaXN0ZW5lcjogRXZlbnRMaXN0ZW5lcik6IHZvaWQge1xuICAgICAgdGhpcy5saXN0ZW5lcnNbdHlwZV0gPSB0aGlzLmxpc3RlbmVyc1t0eXBlXSB8fCBbXTtcbiAgICAgIHRoaXMubGlzdGVuZXJzW3R5cGVdID0gdGhpcy5saXN0ZW5lcnNbdHlwZV0uZmlsdGVyKChsKSA9PiBsICE9PSBsaXN0ZW5lcik7XG4gICAgfVxuXG4gICAgcHJpdmF0ZSBhc3luYyBfY29ubmVjdCgpOiBQcm9taXNlPHZvaWQ+IHtcbiAgICAgIHRyeSB7XG4gICAgICAgIGNvbnN0IHJlc3BvbnNlID0gYXdhaXQgZmV0Y2godGhpcy51cmwsIHtcbiAgICAgICAgICAuLi50aGlzLm9wdGlvbnMsXG4gICAgICAgICAgbHlueEV4dGVuc2lvbjoge1xuICAgICAgICAgICAgdXNlU3RyZWFtaW5nOiB0cnVlLFxuICAgICAgICAgIH0sXG4gICAgICAgIH0pO1xuICAgICAgICB0aGlzLl9kaXNwYXRjaEV2ZW50KCdvcGVuJywgeyBkYXRhOiAnJyB9KTtcbiAgICAgICAgY29uc3QgcmVhZGVyID0gcmVzcG9uc2UuYm9keS5nZXRSZWFkZXIoKTtcbiAgICAgICAgd2hpbGUgKHRydWUpIHtcbiAgICAgICAgICBjb25zdCB7IGRvbmUsIHZhbHVlIH0gPSBhd2FpdCByZWFkZXIucmVhZCgpO1xuICAgICAgICAgIGlmIChkb25lKSBicmVhaztcbiAgICAgICAgICBjb25zdCByYXdFdmVudCA9IGdsb2JhbFRoaXMuVGV4dENvZGVjSGVscGVyLmRlY29kZSh2YWx1ZSk7XG4gICAgICAgICAgY29uc3QgZXZlbnQgPSB0aGlzLl9wYXJzZUV2ZW50KHJhd0V2ZW50KTtcbiAgICAgICAgICBpZiAoZXZlbnQpIHtcbiAgICAgICAgICAgIHRoaXMuX2Rpc3BhdGNoRXZlbnQoZXZlbnQuZXZlbnQgfHwgJ21lc3NhZ2UnLCBldmVudCk7XG4gICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICB9IGNhdGNoIChlcnI6IGFueSkge1xuICAgICAgICB0aGlzLl9kaXNwYXRjaEV2ZW50KCdlcnJvcicsIHsgZGF0YTogJycsIGVycm9yOiBlcnIgfSk7XG4gICAgICB9XG4gICAgfVxuXG4gICAgcHJpdmF0ZSBfcGFyc2VFdmVudChyYXc6IHN0cmluZyk6IEV2ZW50U291cmNlRXZlbnQgfCBudWxsIHtcbiAgICAgIGNvbnN0IGxpbmVzID0gcmF3LnNwbGl0KCdcXG4nKTtcbiAgICAgIGxldCBldmVudDogRXZlbnRTb3VyY2VFdmVudCA9IHsgZGF0YTogJycgfTtcbiAgICAgIGZvciAoY29uc3QgbGluZSBvZiBsaW5lcykge1xuICAgICAgICBpZiAobGluZS5zdGFydHNXaXRoKCdkYXRhOicpKSB7XG4gICAgICAgICAgZXZlbnQuZGF0YSArPSBsaW5lLnNsaWNlKDUpLnRyaW0oKSArICdcXG4nO1xuICAgICAgICB9IGVsc2UgaWYgKGxpbmUuc3RhcnRzV2l0aCgnZXZlbnQ6JykpIHtcbiAgICAgICAgICBldmVudC5ldmVudCA9IGxpbmUuc2xpY2UoNikudHJpbSgpO1xuICAgICAgICB9IGVsc2UgaWYgKGxpbmUuc3RhcnRzV2l0aCgnaWQ6JykpIHtcbiAgICAgICAgICBldmVudC5pZCA9IGxpbmUuc2xpY2UoMykudHJpbSgpO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgICAvLyByZW1vdmUgbGFzdCBuZXdsaW5lXG4gICAgICBpZiAoZXZlbnQuZGF0YSkgZXZlbnQuZGF0YSA9IGV2ZW50LmRhdGEuc2xpY2UoMCwgLTEpO1xuICAgICAgcmV0dXJuIGV2ZW50LmRhdGEgPyBldmVudCA6IG51bGw7XG4gICAgfVxuICB9O1xufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7XG4gIE5vZGVzUmVmIGFzIElOb2Rlc1JlZixcbiAgTXVsdGlOb2Rlc1JlZiBhcyBJTXVsdGlOb2Rlc1JlZixcbiAgU2VsZWN0b3JRdWVyeSBhcyBJU2VsZWN0b3JRdWVyeSxcbiAgdWlGaWVsZHNPcHRpb25zLFxuICB1aU1ldGhvZE9wdGlvbnMsXG59IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCB7XG4gIEVycm9yQ29kZSxcbiAgSWRlbnRpZmllclR5cGUsXG4gIE5vZGVTZWxlY3RUb2tlbixcbiAgU2VsZWN0b3JRdWVyeU5hdGl2ZVByb3h5LFxufSBmcm9tICcuL2ludGVyZmFjZSc7XG5pbXBvcnQgeyBJbnZva2VFcnJvciwgcmVwb3J0RXJyb3IgfSBmcm9tICcuLi9yZXBvcnQnO1xuaW1wb3J0IHsgQW5pbWF0aW9uT3BlcmF0aW9uLCBBbmltYXRpb25WMiB9IGZyb20gJy4uL2FuaW1hdGlvbic7XG5cbi8qKlxuICogU2VsZWN0b3JRdWVyeSBpcyBhIHF1ZXJ5IG9iamVjdCB0aGF0IGNhbiBiZSB1c2VkIHRvIHNlbGVjdCBub2RlcyBpbiB0aGUgVmlydHVhbCBET00gdHJlZS5cbiAqXG4gKiBFeGFtcGxlOlxuICogdGhpcy5jcmVhdGVTZWxlY3RvclF1ZXJ5KClcbiAqICAgLnNlbGVjdCgnI3ZpZGVvJylcbiAqICAgLmludm9rZSh7XG4gKiAgICAgbWV0aG9kOiAnc2Vla1RvJyxcbiAqICAgICBwYXJhbXM6IHtcbiAqICAgICAgIGR1cmF0aW9uOiAxMDAwLFxuICogICAgIH0sXG4gKiAgICAgc3VjY2VzczogZnVuY3Rpb24gKHJlcykge1xuICogICAgICAgY29uc29sZS5sb2cocmVzKTtcbiAqICAgICB9LFxuICogICAgIGZhaWw6IGZ1bmN0aW9uIChyZXMpIHtcbiAqICAgICAgIGNvbnNvbGUubG9nKHJlcy5jb2RlLCByZXMuZGF0YSk7XG4gKiAgICAgfSxcbiAqICAgfSlcbiAqICAgLmV4ZWMoKTtcbiAqL1xuZXhwb3J0IGRlZmF1bHQgY2xhc3MgU2VsZWN0b3JRdWVyeSBpbXBsZW1lbnRzIElTZWxlY3RvclF1ZXJ5IHtcbiAgcHJpdmF0ZSByZWFkb25seSBfY29tcG9uZW50OiBzdHJpbmc7XG4gIHByaXZhdGUgcmVhZG9ubHkgX3Rhc2tRdWV1ZTogRnVuY3Rpb25bXTtcbiAgcHJpdmF0ZSByZWFkb25seSBfbmF0aXZlX3Byb3h5OiBTZWxlY3RvclF1ZXJ5TmF0aXZlUHJveHk7XG4gIHByaXZhdGUgX3Jvb3RfdW5pcXVlX2lkPzogbnVtYmVyO1xuXG4gIC8qKlxuICAgKiBOb3JtYWxseSwgYSBxdWVyeSBpcyBleGVjdXRlZCBhZnRlciBjYWxsaW5nIGV4ZWMoKS5cbiAgICogSG93ZXZlciwgd2hlbiBgX2ZpcmVfaW1tZWRpYXRlbHlgIGlzIHNldCB0byB0cnVlLFxuICAgKiB0aGUgcXVlcnkgd2lsbCBiZSBleGVjdXRlZCBpbW1lZGlhdGVseSBhZnRlciB0YXNrIGNvbW1pdHRlZCAod2hlbiBjYWxsaW5nIGBpbnZva2UoKWAsIGV0Yy4pXG4gICAqIHdpdGhvdXQgdGhlIG5lZWQgb2YgY2FsbGluZyBgZXhlYygpYCBleHBsaWNpdGx5LlxuICAgKlxuICAgKiBUaGlzIGlzIHVzZWQgd2hlbiBTZWxlY3RvclF1ZXJ5IGlzIHVzZWQgYXMgUmVhY3RSZWYuXG4gICAqL1xuICBwcml2YXRlIF9maXJlX2ltbWVkaWF0ZWx5OiBib29sZWFuO1xuXG4gIHByaXZhdGUgY29uc3RydWN0b3IoXG4gICAgY29tcG9uZW50OiBzdHJpbmcsXG4gICAgdGFza1F1ZXVlOiBGdW5jdGlvbltdLFxuICAgIHByb3h5OiBTZWxlY3RvclF1ZXJ5TmF0aXZlUHJveHlcbiAgKSB7XG4gICAgdGhpcy5fY29tcG9uZW50ID0gY29tcG9uZW50O1xuICAgIHRoaXMuX3Rhc2tRdWV1ZSA9IHRhc2tRdWV1ZTtcbiAgICB0aGlzLl9uYXRpdmVfcHJveHkgPSBwcm94eTtcbiAgICB0aGlzLl9maXJlX2ltbWVkaWF0ZWx5ID0gZmFsc2U7XG4gICAgdGhpcy5fcm9vdF91bmlxdWVfaWQgPSB1bmRlZmluZWQ7XG4gIH1cblxuICBzdGF0aWMgZnJvbVF1ZXJ5KFxuICAgIHByZXZRdWVyeTogU2VsZWN0b3JRdWVyeSxcbiAgICBjb21wb25lbnQ/OiBzdHJpbmdcbiAgKTogU2VsZWN0b3JRdWVyeSB7XG4gICAgcmV0dXJuIG5ldyBTZWxlY3RvclF1ZXJ5KFxuICAgICAgY29tcG9uZW50ID8/IHByZXZRdWVyeS5fY29tcG9uZW50LFxuICAgICAgcHJldlF1ZXJ5Ll90YXNrUXVldWUuc2xpY2UoKSxcbiAgICAgIHByZXZRdWVyeS5fbmF0aXZlX3Byb3h5XG4gICAgKTtcbiAgfVxuXG4gIHN0YXRpYyBuZXdFbXB0eVF1ZXJ5KFxuICAgIHByb3h5OiBTZWxlY3RvclF1ZXJ5TmF0aXZlUHJveHksXG4gICAgY29tcG9uZW50Pzogc3RyaW5nXG4gICk6IFNlbGVjdG9yUXVlcnkge1xuICAgIHJldHVybiBuZXcgU2VsZWN0b3JRdWVyeShjb21wb25lbnQgPz8gJycsIFtdLCBwcm94eSk7XG4gIH1cblxuICAvKipcbiAgICogQWNjb3JkaW5nIHRvIGB0aGlzLl9maXJlX2ltbWVkaWF0ZWx5YCxcbiAgICogZWl0aGVyIGV4ZWN1dGUgdGhlIHF1ZXJ5IGltbWVkaWF0ZWx5IG9yIGFkZCBpdCB0byB0aGUgdGFzayBxdWV1ZSBvZiB0aGUgU2VsZWN0b3JRdWVyeS5cbiAgICogSW4gdGhlIGxhdHRlciBjYXNlLCBhIG5ldyBxdWVyeSBpcyByZXR1cm5lZCwgYW5kIGB0aGlzYCBpcyBub3QgbW9kaWZpZWQuXG4gICAqIEBwYXJhbSB0YXNrIHRoZSB0YXNrIHRvIGNvbW1pdFxuICAgKi9cbiAgY29tbWl0VGFzayh0YXNrOiBGdW5jdGlvbik6IElTZWxlY3RvclF1ZXJ5IHtcbiAgICBsZXQgbmV3X3F1ZXJ5ID0gU2VsZWN0b3JRdWVyeS5mcm9tUXVlcnkodGhpcywgdGhpcy5fY29tcG9uZW50KTtcbiAgICBuZXdfcXVlcnkuX3Rhc2tRdWV1ZS5wdXNoKHRhc2spO1xuXG4gICAgaWYgKHRoaXMuX2ZpcmVfaW1tZWRpYXRlbHkpIHtcbiAgICAgIG5ld19xdWVyeS5leGVjKCk7XG4gICAgICByZXR1cm4gdW5kZWZpbmVkO1xuICAgIH1cbiAgICByZXR1cm4gbmV3X3F1ZXJ5O1xuICB9XG5cbiAgaW4oY29tcG9uZW50OiB7IGNyZWF0ZVNlbGVjdG9yUXVlcnk6IEZ1bmN0aW9uIH0pOiBJU2VsZWN0b3JRdWVyeSB7XG4gICAgcmV0dXJuIGNvbXBvbmVudC5jcmVhdGVTZWxlY3RvclF1ZXJ5KHRoaXMpO1xuICB9XG5cbiAgLyoqXG4gICAqIFNlbGVjdHMgYSBzaW5nbGUgbm9kZSBieSBDU1Mgc2VsZWN0b3IuXG4gICAqIEBwYXJhbSBzZWxlY3RvciBDU1Mgc2VsZWN0b3JcbiAgICovXG4gIHNlbGVjdChzZWxlY3Rvcjogc3RyaW5nKTogSU5vZGVzUmVmIHtcbiAgICByZXR1cm4gbmV3IE5vZGVzUmVmKHRoaXMsIHtcbiAgICAgIHR5cGU6IElkZW50aWZpZXJUeXBlLklEX1NFTEVDVE9SLFxuICAgICAgaWRlbnRpZmllcjogc2VsZWN0b3IsXG4gICAgICBjb21wb25lbnRfaWQ6IHRoaXMuX2NvbXBvbmVudCxcbiAgICAgIHJvb3RfdW5pcXVlX2lkOiB0aGlzLl9yb290X3VuaXF1ZV9pZCxcbiAgICAgIGZpcnN0X29ubHk6IHRydWUsXG4gICAgfSk7XG4gIH1cblxuICAvKipcbiAgICogU2VsZWN0cyBhbGwgbm9kZXMgc2F0aXNmeWluZyBDU1Mgc2VsZWN0b3IuXG4gICAqIEBwYXJhbSBzZWxlY3RvciBDU1Mgc2VsZWN0b3JcbiAgICovXG4gIHNlbGVjdEFsbChzZWxlY3Rvcjogc3RyaW5nKTogSU11bHRpTm9kZXNSZWYge1xuICAgIHJldHVybiBuZXcgTm9kZXNSZWYodGhpcywge1xuICAgICAgdHlwZTogSWRlbnRpZmllclR5cGUuSURfU0VMRUNUT1IsXG4gICAgICBpZGVudGlmaWVyOiBzZWxlY3RvcixcbiAgICAgIGNvbXBvbmVudF9pZDogdGhpcy5fY29tcG9uZW50LFxuICAgICAgcm9vdF91bmlxdWVfaWQ6IHRoaXMuX3Jvb3RfdW5pcXVlX2lkLFxuICAgICAgZmlyc3Rfb25seTogZmFsc2UsXG4gICAgfSk7XG4gIH1cblxuICAvKipcbiAgICogU2VsZWN0cyBhIHNpbmdsZSBub2RlIGFzIFJlYWN0IHJlZi5cbiAgICogV2hlbiB3b3JrcyBhcyBSZWFjdFJlZiwgU2VsZWN0b3JRdWVyeSBzaG91bGQgYWN0IGxpa2UgZ2V0Tm9kZVJlZiwgd2hpY2ggbWVhbnM6XG4gICAqIDEuIGNhc2NhZGUgcXVlcnkgaXMgZGlzYWJsZWQuXG4gICAqIDIuIHRhc2tzIGFyZSBleGVjdXRlZCBpbW1lZGlhdGVseSB3aXRob3V0IGNhbGxpbmcgZXhlYygpLlxuICAgKi9cbiAgc2VsZWN0UmVhY3RSZWYocmVmX3N0cmluZzogc3RyaW5nKTogSU5vZGVzUmVmIHtcbiAgICBpZiAodGhpcy5fdGFza1F1ZXVlLmxlbmd0aCkge1xuICAgICAgY29uc3QgZXJyb3JNZXNzYWdlID1cbiAgICAgICAgJ3NlbGVjdFJlYWN0UmVmKCkgc2hvdWxkIGJlIGNhbGxlZCBiZWZvcmUgYW55IG90aGVyIHNlbGVjdG9yIHF1ZXJ5IG1ldGhvZHMnO1xuICAgICAgbmF0aXZlQ29uc29sZS53YXJuKGVycm9yTWVzc2FnZSk7XG4gICAgICBjb25zdCBlcnJvciA9IG5ldyBFcnJvcihlcnJvck1lc3NhZ2UpO1xuICAgICAgcmVwb3J0RXJyb3IoXG4gICAgICAgIG5ldyBJbnZva2VFcnJvcihlcnJvck1lc3NhZ2UsIGVycm9yLnN0YWNrKSxcbiAgICAgICAgdGhpcy5fbmF0aXZlX3Byb3h5Lm5hdGl2ZUFwcFxuICAgICAgKTtcbiAgICAgIHJldHVybjtcbiAgICB9XG5cbiAgICB0aGlzLl9maXJlX2ltbWVkaWF0ZWx5ID0gdHJ1ZTtcbiAgICByZXR1cm4gbmV3IE5vZGVzUmVmKHRoaXMsIHtcbiAgICAgIHR5cGU6IElkZW50aWZpZXJUeXBlLlJFRl9JRCxcbiAgICAgIGlkZW50aWZpZXI6IHJlZl9zdHJpbmcsXG4gICAgICBjb21wb25lbnRfaWQ6IHRoaXMuX2NvbXBvbmVudCxcbiAgICAgIHJvb3RfdW5pcXVlX2lkOiB0aGlzLl9yb290X3VuaXF1ZV9pZCxcbiAgICAgIGZpcnN0X29ubHk6IHRydWUsXG4gICAgfSk7XG4gIH1cblxuICAvKipcbiAgICogU2VsZWN0IHJvb3Qgbm9kZSBvZiB0aGUgY29tcG9uZW50LlxuICAgKi9cbiAgc2VsZWN0Um9vdCgpOiBJTm9kZXNSZWYge1xuICAgIHJldHVybiB0aGlzLnNlbGVjdCgnJyk7XG4gIH1cblxuICAvKipcbiAgICogU2VsZWN0cyBhIHNpbmdsZSBub2RlIGJ5IGVsZW1lbnQgaWQuXG4gICAqIFdoZW4gYSB0b3VjaCBldmVudCBpcyB0cmlnZ2VyZWQsIHRoZSBlbGVtZW50IGlkIG9mIHRoZSBub2RlIGlzIHBhc3NlZCB0byB0aGUgZXZlbnQgaGFuZGxlciBhcyAndWlkJyxcbiAgICogYnkgd2hpY2ggY2FuIGEgbm9kZSBiZSBzZWxlY3RlZCBpbiBpdHMgZXZlbnQgaGFuZGxlci5cbiAgICovXG4gIHNlbGVjdFVuaXF1ZUlEKHVuaXF1ZUlkOiBzdHJpbmcgfCBudW1iZXIpOiBJTm9kZXNSZWYge1xuICAgIHJldHVybiBuZXcgTm9kZXNSZWYodGhpcywge1xuICAgICAgdHlwZTogSWRlbnRpZmllclR5cGUuVU5JUVVFX0lELFxuICAgICAgaWRlbnRpZmllcjogdW5pcXVlSWQudG9TdHJpbmcoKSxcbiAgICAgIGNvbXBvbmVudF9pZDogdGhpcy5fY29tcG9uZW50LFxuICAgICAgcm9vdF91bmlxdWVfaWQ6IHRoaXMuX3Jvb3RfdW5pcXVlX2lkLFxuICAgICAgZmlyc3Rfb25seTogdHJ1ZSxcbiAgICB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBFeGVjdXRlIGFsbCB0YXNrcyBpbiB0aGUgdGFzayBxdWV1ZS5cbiAgICogV2hlbiBgdGhpcy5fZmlyZV9pbW1lZGlhdGVseWAgaXMgc2V0IHRvIHRydWUsIHRoaXMgbWV0aG9kIGlzIGNhbGxlZCBhdXRvbWF0aWNhbGx5LlxuICAgKi9cbiAgZXhlYygpOiB2b2lkIHtcbiAgICBmb3IgKGxldCBpID0gMDsgaSA8IHRoaXMuX3Rhc2tRdWV1ZS5sZW5ndGg7ICsraSkge1xuICAgICAgdGhpcy5fdGFza1F1ZXVlW2ldKHRoaXMuX25hdGl2ZV9wcm94eSk7XG4gICAgfVxuICB9XG5cbiAgc2V0Um9vdCh1bmlxdWVJZDogc3RyaW5nIHwgbnVtYmVyKTogU2VsZWN0b3JRdWVyeSB7XG4gICAgdGhpcy5fcm9vdF91bmlxdWVfaWQgPSBOdW1iZXIodW5pcXVlSWQpO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG59XG5cbmV4cG9ydCBjbGFzcyBOb2Rlc1JlZiBpbXBsZW1lbnRzIElOb2Rlc1JlZiB7XG4gIHByaXZhdGUgc3RhdGljIG5vZGVQb29sID0ge307XG5cbiAgcHJpdmF0ZSByZWFkb25seSBfbm9kZVNlbGVjdFRva2VuOiBOb2RlU2VsZWN0VG9rZW47XG4gIHByaXZhdGUgcmVhZG9ubHkgX3NlbGVjdG9yUXVlcnk6IFNlbGVjdG9yUXVlcnk7XG5cbiAgY29uc3RydWN0b3Ioc2VsZWN0b3JRdWVyeTogU2VsZWN0b3JRdWVyeSwgbm9kZVNlbGVjdFRva2VuOiBOb2RlU2VsZWN0VG9rZW4pIHtcbiAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4gPSBub2RlU2VsZWN0VG9rZW47XG4gICAgdGhpcy5fc2VsZWN0b3JRdWVyeSA9IHNlbGVjdG9yUXVlcnk7XG4gIH1cbiAgaW52b2tlKG9wdGlvbnM6IHVpTWV0aG9kT3B0aW9ucyk6IElTZWxlY3RvclF1ZXJ5IHtcbiAgICBsZXQgZXJyb3JTdGFjaztcbiAgICBpZiAoTk9ERV9FTlYgPT09ICdkZXZlbG9wbWVudCcgfHwgTk9ERV9FTlYgPT09ICd0ZXN0Jykge1xuICAgICAgZXJyb3JTdGFjayA9IG5ldyBFcnJvcignJyk7XG4gICAgfVxuXG4gICAgbGV0IHRhc2sgPSAocHJveHk6IFNlbGVjdG9yUXVlcnlOYXRpdmVQcm94eSkgPT4ge1xuICAgICAgbGV0IGNhbGxiYWNrID0gKHJlcykgPT4ge1xuICAgICAgICBpZiAocmVzLmNvZGUgPT09IEVycm9yQ29kZS5TVUNDRVNTKSB7XG4gICAgICAgICAgb3B0aW9ucy5zdWNjZXNzICYmIG9wdGlvbnMuc3VjY2VzcyhyZXMuZGF0YSk7XG4gICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgaWYgKG9wdGlvbnMuZmFpbCkge1xuICAgICAgICAgICAgb3B0aW9ucy5mYWlsKHJlcyk7XG4gICAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAgIC8vIGVuYWJsZSB3YXJuaW5nIGluIGRldmVsb3BtZW50IGFuZCB0ZXN0XG4gICAgICAgICAgICBpZiAoTk9ERV9FTlYgPT09ICdkZXZlbG9wbWVudCcgfHwgTk9ERV9FTlYgPT09ICd0ZXN0Jykge1xuICAgICAgICAgICAgICBpZiAoIXByb3h5Lmx5bnguX3N3aXRjaGVzLmRpc2FibGVTZWxlY3RvclF1ZXJ5V2FybmluZ1doZW5GYWlsZWQpIHtcbiAgICAgICAgICAgICAgICBjb25zdCBlcnJvck1lc3NhZ2UgPSBgRmFpbGVkIHRvIGV4ZWMgY3JlYXRlU2VsZWN0b3JRdWVyeSgpLmludm9rZSgpIG9uIE5vZGVzUmVmICR7SlNPTi5zdHJpbmdpZnkoXG4gICAgICAgICAgICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW5cbiAgICAgICAgICAgICAgICApfS4gQWRkIGEgZmFpbCBjYWxsYmFjayB0byBzdXBwcmVzcyB0aGlzIHdhcm5pbmcuIE1zZzogJHtKU09OLnN0cmluZ2lmeShcbiAgICAgICAgICAgICAgICAgIHJlc1xuICAgICAgICAgICAgICAgICl9YDtcbiAgICAgICAgICAgICAgICBuYXRpdmVDb25zb2xlLndhcm4oZXJyb3JNZXNzYWdlKTtcbiAgICAgICAgICAgICAgICByZXBvcnRFcnJvcihcbiAgICAgICAgICAgICAgICAgIG5ldyBJbnZva2VFcnJvcihlcnJvck1lc3NhZ2UsIGVycm9yU3RhY2suc3RhY2spLFxuICAgICAgICAgICAgICAgICAgcHJveHkubmF0aXZlQXBwXG4gICAgICAgICAgICAgICAgKTtcbiAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgfTtcbiAgICAgIGlmICghdGhpcy5fbm9kZVNlbGVjdFRva2VuLmZpcnN0X29ubHkpIHtcbiAgICAgICAgY2FsbGJhY2soe1xuICAgICAgICAgIGNvZGU6IEVycm9yQ29kZS5TRUxFQ1RPUl9OT1RfU1VQUE9SVEVELFxuICAgICAgICAgIGRhdGE6ICdzZWxlY3RBbGwgbm90IHN1cHBvcnRlZCBmb3IgaW52b2tlIG1ldGhvZCcsXG4gICAgICAgIH0pO1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgICBwcm94eS5uYXRpdmVBcHAuaW52b2tlVUlNZXRob2QoXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi50eXBlLFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uaWRlbnRpZmllcixcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLmNvbXBvbmVudF9pZCxcbiAgICAgICAgb3B0aW9ucy5tZXRob2QsXG4gICAgICAgIG9wdGlvbnMucGFyYW1zID8/IHt9LFxuICAgICAgICBjYWxsYmFjayxcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLnJvb3RfdW5pcXVlX2lkXG4gICAgICApO1xuICAgIH07XG4gICAgcmV0dXJuIHRoaXMuX3NlbGVjdG9yUXVlcnkuY29tbWl0VGFzayh0YXNrKTtcbiAgfVxuXG4gIHBhdGgoY2I6IEZ1bmN0aW9uKSB7XG4gICAgbGV0IHRhc2sgPSAocHJveHk6IFNlbGVjdG9yUXVlcnlOYXRpdmVQcm94eSkgPT4ge1xuICAgICAgbGV0IGNhbGxiYWNrID0gKHJlcykgPT4ge1xuICAgICAgICBjYiAmJiBjYihyZXMuZGF0YSwgcmVzLnN0YXR1cyk7XG4gICAgICB9O1xuICAgICAgcHJveHkubmF0aXZlQXBwLmdldFBhdGhJbmZvKFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4udHlwZSxcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLmlkZW50aWZpZXIsXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5jb21wb25lbnRfaWQsXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5maXJzdF9vbmx5LFxuICAgICAgICBjYWxsYmFjayxcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLnJvb3RfdW5pcXVlX2lkXG4gICAgICApO1xuICAgIH07XG4gICAgcmV0dXJuIHRoaXMuX3NlbGVjdG9yUXVlcnkuY29tbWl0VGFzayh0YXNrKTtcbiAgfVxuXG4gIGZpZWxkcyhmaWVsZHM6IHVpRmllbGRzT3B0aW9ucywgY2I6IEZ1bmN0aW9uKSB7XG4gICAgbGV0IHRhc2sgPSAocHJveHk6IFNlbGVjdG9yUXVlcnlOYXRpdmVQcm94eSkgPT4ge1xuICAgICAgbGV0IGNhbGxiYWNrID0gKHJlczogeyBkYXRhOiBhbnk7IHN0YXR1czogYW55IH0pID0+IHtcbiAgICAgICAgLy8gd2hlbiAncXVlcnknIGlzIHBhc3NlZCwgJ3VuaXF1ZV9pZCcgaXMgYWN0dWFsbHkgcmV0dXJuZWQuXG4gICAgICAgIC8vIHNob3VsZCBjcmVhdGUgU2VsZWN0b3JRdWVyeSB1c2luZyAndW5pcXVlX2lkJyBhcyByb290IGhlcmUuXG4gICAgICAgIGlmIChmaWVsZHMucXVlcnkpIHtcbiAgICAgICAgICBjb25zdCBhZGRRdWVyeU9iamVjdCA9IChyZXN1bHQpID0+IHtcbiAgICAgICAgICAgIHJlc3VsdC5xdWVyeSA9IFNlbGVjdG9yUXVlcnkubmV3RW1wdHlRdWVyeShwcm94eSk7XG4gICAgICAgICAgICByZXN1bHQucXVlcnkuc2V0Um9vdChyZXN1bHQudW5pcXVlX2lkLnRvU3RyaW5nKCkpO1xuICAgICAgICAgICAgaWYgKCFmaWVsZHMudW5pcXVlX2lkKSB7XG4gICAgICAgICAgICAgIGRlbGV0ZSByZXN1bHQudW5pcXVlX2lkO1xuICAgICAgICAgICAgfVxuICAgICAgICAgIH07XG4gICAgICAgICAgaWYgKHRoaXMuX25vZGVTZWxlY3RUb2tlbi5maXJzdF9vbmx5KSB7XG4gICAgICAgICAgICBsZXQgcmVzdWx0ID0gcmVzLmRhdGE7XG4gICAgICAgICAgICBpZiAocmVzdWx0KSB7XG4gICAgICAgICAgICAgIGFkZFF1ZXJ5T2JqZWN0KHJlc3VsdCk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAgIGZvciAobGV0IHJlc3VsdCBvZiByZXMuZGF0YSkge1xuICAgICAgICAgICAgICBhZGRRdWVyeU9iamVjdChyZXN1bHQpO1xuICAgICAgICAgICAgfVxuICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICBjYiAmJiBjYihyZXMuZGF0YSwgcmVzLnN0YXR1cyk7XG4gICAgICB9O1xuICAgICAgbGV0IGZpZWxkc19hcnJheTogc3RyaW5nW10gPSBbXTtcbiAgICAgIGZvciAobGV0IGtleSBpbiBmaWVsZHMpIHtcbiAgICAgICAgLy8gZmlsdGVyICdxdWVyeScuIHVzZSAndW5pcXVlX2lkJyBpbnN0ZWFkLlxuICAgICAgICBpZiAoa2V5ID09ICdxdWVyeScgJiYgZmllbGRzW2tleV0gPT0gdHJ1ZSAmJiAhZmllbGRzLnVuaXF1ZV9pZCkge1xuICAgICAgICAgIGZpZWxkc19hcnJheS5wdXNoKCd1bmlxdWVfaWQnKTtcbiAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgfVxuICAgICAgICBpZiAoZmllbGRzW2tleV0pIHtcbiAgICAgICAgICBmaWVsZHNfYXJyYXkucHVzaChrZXkpO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgICBwcm94eS5uYXRpdmVBcHAuZ2V0RmllbGRzKFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4udHlwZSxcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLmlkZW50aWZpZXIsXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5jb21wb25lbnRfaWQsXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5maXJzdF9vbmx5LFxuICAgICAgICBmaWVsZHNfYXJyYXksXG4gICAgICAgIGNhbGxiYWNrLFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4ucm9vdF91bmlxdWVfaWRcbiAgICAgICk7XG4gICAgfTtcbiAgICByZXR1cm4gdGhpcy5fc2VsZWN0b3JRdWVyeS5jb21taXRUYXNrKHRhc2spO1xuICB9XG5cbiAgYW5pbWF0ZShhbmltYXRpb25zOiBBbmltYXRpb25WMltdIHwgQW5pbWF0aW9uVjIpOiBJU2VsZWN0b3JRdWVyeSB7XG4gICAgbGV0IGFuaW1hdGlvbnNBcnJheSA9IFtdO1xuICAgIGlmIChBcnJheS5pc0FycmF5KGFuaW1hdGlvbnMpKSB7XG4gICAgICBhbmltYXRpb25zQXJyYXkgPSBhbmltYXRpb25zO1xuICAgIH0gZWxzZSB7XG4gICAgICBhbmltYXRpb25zQXJyYXkucHVzaChhbmltYXRpb25zKTtcbiAgICB9XG4gICAgbGV0IHRhc2sgPSAocHJveHk6IFNlbGVjdG9yUXVlcnlOYXRpdmVQcm94eSkgPT4ge1xuICAgICAgYW5pbWF0aW9uc0FycmF5LmZvckVhY2goKGFuaW1hdGlvbikgPT4ge1xuICAgICAgICBwcm94eS5uYXRpdmVBcHAuYW5pbWF0ZShcbiAgICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4udHlwZSxcbiAgICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uaWRlbnRpZmllcixcbiAgICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uY29tcG9uZW50X2lkLFxuICAgICAgICAgIEFuaW1hdGlvbk9wZXJhdGlvbi5TVEFSVCxcbiAgICAgICAgICBhbmltYXRpb24/LmlkLFxuICAgICAgICAgIGFuaW1hdGlvbj8uZWZmZWN0Py5rZXlmcmFtZXMsXG4gICAgICAgICAgYW5pbWF0aW9uPy5lZmZlY3Q/Lm9wdGlvbnNcbiAgICAgICAgKTtcbiAgICAgIH0pO1xuICAgIH07XG4gICAgcmV0dXJuIHRoaXMuX3NlbGVjdG9yUXVlcnkuY29tbWl0VGFzayh0YXNrKTtcbiAgfVxuXG4gIGFuaW1hdGlvbk9wZXJhdGUoXG4gICAgb3BlcmF0aW9uOiBBbmltYXRpb25PcGVyYXRpb24sXG4gICAgaWRzOiBzdHJpbmdbXSB8IHN0cmluZ1xuICApOiBJU2VsZWN0b3JRdWVyeSB7XG4gICAgbGV0IGlkQXJyYXkgPSBbXTtcbiAgICBpZiAoQXJyYXkuaXNBcnJheShpZHMpKSB7XG4gICAgICBpZEFycmF5ID0gaWRzO1xuICAgIH0gZWxzZSB7XG4gICAgICBpZEFycmF5LnB1c2goaWRzKTtcbiAgICB9XG4gICAgbGV0IHRhc2sgPSAocHJveHk6IFNlbGVjdG9yUXVlcnlOYXRpdmVQcm94eSkgPT4ge1xuICAgICAgaWRBcnJheS5mb3JFYWNoKChpZCkgPT4ge1xuICAgICAgICBwcm94eS5uYXRpdmVBcHAuYW5pbWF0ZShcbiAgICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4udHlwZSxcbiAgICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uaWRlbnRpZmllcixcbiAgICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uY29tcG9uZW50X2lkLFxuICAgICAgICAgIG9wZXJhdGlvbixcbiAgICAgICAgICBpZCxcbiAgICAgICAgICBudWxsLFxuICAgICAgICAgIG51bGxcbiAgICAgICAgKTtcbiAgICAgIH0pO1xuICAgIH07XG4gICAgcmV0dXJuIHRoaXMuX3NlbGVjdG9yUXVlcnkuY29tbWl0VGFzayh0YXNrKTtcbiAgfVxuXG4gIHBsYXlBbmltYXRpb24oaWRzOiBzdHJpbmdbXSB8IHN0cmluZyk6IElTZWxlY3RvclF1ZXJ5IHtcbiAgICByZXR1cm4gdGhpcy5hbmltYXRpb25PcGVyYXRlKEFuaW1hdGlvbk9wZXJhdGlvbi5QTEFZLCBpZHMpO1xuICB9XG5cbiAgcGF1c2VBbmltYXRpb24oaWRzOiBzdHJpbmdbXSk6IElTZWxlY3RvclF1ZXJ5IHtcbiAgICByZXR1cm4gdGhpcy5hbmltYXRpb25PcGVyYXRlKEFuaW1hdGlvbk9wZXJhdGlvbi5QQVVTRSwgaWRzKTtcbiAgfVxuXG4gIGNhbmNlbEFuaW1hdGlvbihpZHM6IHN0cmluZ1tdKTogSVNlbGVjdG9yUXVlcnkge1xuICAgIHJldHVybiB0aGlzLmFuaW1hdGlvbk9wZXJhdGUoQW5pbWF0aW9uT3BlcmF0aW9uLkNBTkNFTCwgaWRzKTtcbiAgfVxuXG4gIGZpbmlzaEFuaW1hdGlvbihpZHM6IHN0cmluZ1tdKTogSVNlbGVjdG9yUXVlcnkge1xuICAgIHJldHVybiB0aGlzLmFuaW1hdGlvbk9wZXJhdGUoQW5pbWF0aW9uT3BlcmF0aW9uLkZJTklTSCwgaWRzKTtcbiAgfVxuXG4gIHNldE5hdGl2ZVByb3BzKG5hdGl2ZVByb3BzOiBSZWNvcmQ8c3RyaW5nLCB1bmtub3duPikge1xuICAgIGxldCB0YXNrID0gKHByb3h5OiBTZWxlY3RvclF1ZXJ5TmF0aXZlUHJveHkpID0+IHtcbiAgICAgIHByb3h5Lm5hdGl2ZUFwcC5zZXROYXRpdmVQcm9wcyhcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLnR5cGUsXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5pZGVudGlmaWVyLFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uY29tcG9uZW50X2lkLFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uZmlyc3Rfb25seSxcbiAgICAgICAgbmF0aXZlUHJvcHMsXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5yb290X3VuaXF1ZV9pZFxuICAgICAgKTtcbiAgICB9O1xuICAgIHJldHVybiB0aGlzLl9zZWxlY3RvclF1ZXJ5LmNvbW1pdFRhc2sodGFzayk7XG4gIH1cbn1cbiIsICJpbXBvcnQge1xuICBpc0Vycm9yLFxuICBpc0Z1bmN0aW9uLFxuICBpc09iamVjdCxcbiAgaXNTdHJpbmcsXG59IGZyb20gJ0BseW54LWpzL3J1bnRpbWUtc2hhcmVkJztcbmltcG9ydCB7XG4gIENyZWF0ZUludGVyc2VjdGlvbk9ic2VydmVyRnVuYyxcbiAgR2xvYmFsUHJvcHMsXG4gIExvYWREeW5hbWljQ29tcG9uZW50RmFpbGVkUmVzdWx0LFxuICBMb2FkRHluYW1pY0NvbXBvbmVudEZ1bmMsXG4gIExvYWREeW5hbWljQ29tcG9uZW50U3VjY2Vzc1Jlc3VsdCxcbiAgTHlueFNldFRpbWVvdXQsXG4gIE1lc3NhZ2VFdmVudCxcbn0gZnJvbSAnQGx5bngtanMvdHlwZXMnO1xuaW1wb3J0IHtcbiAgUmVxdWlyZU1vZHVsZSxcbiAgUmVxdWlyZU1vZHVsZUFzeW5jLFxuICBOYXRpdmVMeW54UHJveHksXG4gIE1lc3NhZ2VFdmVudFR5cGUsXG4gIExvYWRTY3JpcHQsXG59IGZyb20gJy4vaW50ZXJmYWNlJztcbmltcG9ydCB7IEJhc2VBcHAsIE5hdGl2ZUFwcCB9IGZyb20gJy4uL2FwcCc7XG5pbXBvcnQgeyBUZXh0SW5mbywgVGV4dE1ldHJpY3MgfSBmcm9tICcuLi9tb2R1bGVzL25hdGl2ZU1vZHVsZXMnO1xuaW1wb3J0IG5hdGl2ZUdsb2JhbCBmcm9tICcuLi9jb21tb24vbmF0aXZlR2xvYmFsJztcbmltcG9ydCBFbGVtZW50IGZyb20gJy4uL21vZHVsZXMvZWxlbWVudCc7XG5pbXBvcnQgeyBMeW54RXJyb3JMZXZlbCB9IGZyb20gJy4uL21vZHVsZXMvcmVwb3J0JztcbmltcG9ydCB7IGNyZWF0ZUV2ZW50U291cmNlIH0gZnJvbSAnLi4vbW9kdWxlcy9mZXRjaCc7XG5pbXBvcnQgUGVyZm9ybWFuY2UgZnJvbSAnLi4vbW9kdWxlcy9wZXJmb3JtYW5jZSc7XG5pbXBvcnQgU2VsZWN0b3JRdWVyeSBmcm9tICcuLi9tb2R1bGVzL3NlbGVjdG9yUXVlcnkvU2VsZWN0b3JRdWVyeSc7XG5pbXBvcnQgeyBBbmltYXRpb25WMiB9IGZyb20gJy4uL21vZHVsZXMvYW5pbWF0aW9uL2FuaW1hdGlvblYyJztcbmltcG9ydCB7IERFRkFVTFRfRU5UUlkgfSBmcm9tICcuLi9jb21tb24vY29uc3RhbnRzJztcblxuaW50ZXJmYWNlIEx5bnhNb2R1bGVMb2FkZXIge1xuICBsb2FkKG1vZHVsZU5hbWU6IHN0cmluZyk6IGFueTtcbn1cblxuZXhwb3J0IGNsYXNzIEx5bngge1xuICBzdGF0aWMgX19yZWdpc3RlclNoYXJlZERhdGFDb3VudGVyOiBudW1iZXIgPSAwO1xuICBfX2dsb2JhbFByb3BzOiBHbG9iYWxQcm9wcztcbiAgX19wcmVzZXREYXRhOiBSZWNvcmQ8c3RyaW5nLCB1bmtub3duPjtcbiAgX3N3aXRjaGVzOiBSZWNvcmQ8c3RyaW5nLCBib29sZWFuPjtcbiAgdGFyZ2V0U2RrVmVyc2lvbj86IHN0cmluZztcblxuICBjb25zdHJ1Y3RvcihcbiAgICAvLyBzaG91bGQgdXNlIGZ1bmN0aW9uIHRvIGdldCBuYXRpdmUgYXBwIHRvIGF2b2lkIGN5Y2xlXG4gICAgcHVibGljIGdldE5hdGl2ZUFwcDogKCkgPT4gTmF0aXZlQXBwLFxuICAgIHB1YmxpYyBnZXRBcHA6ICgpID0+IEJhc2VBcHAsXG4gICAgcHVibGljIFByb21pc2U6IFByb21pc2VDb25zdHJ1Y3RvcixcbiAgICBwdWJsaWMgZ2V0TmF0aXZlTHlueDogKCkgPT4gTmF0aXZlTHlueFByb3h5XG4gICkge1xuICAgIHRoaXMuaW5pdCh1bmRlZmluZWQpO1xuICB9XG5cbiAgc2V0VGltZW91dDogTHlueFNldFRpbWVvdXQgPSB0aGlzLmdldEFwcCgpLndyYXBSZXBvcnQoXG4gICAgdGhpcy5nZXRBcHAoKS5zZXRUaW1lb3V0LFxuICAgICdzZXRUaW1lb3V0IEVycm9yJ1xuICApO1xuXG4gIHB1YmxpYyByZWJpbmQoZ2V0QXBwOiAoKSA9PiBCYXNlQXBwKSB7XG4gICAgdGhpcy5pbml0KGdldEFwcCk7XG4gIH1cblxuICBwcml2YXRlIGluaXQoZ2V0QXBwPzogKCkgPT4gQmFzZUFwcCkge1xuICAgIGlmIChnZXRBcHApIHtcbiAgICAgIHRoaXMuZ2V0QXBwID0gZ2V0QXBwO1xuICAgICAgLy8gVE9ETyhsaXlhbmJvKTogbWVyZ2Ugb3IgcmVwbGFjZT8gbm93IGlzIHJlcGxhY2UuXG4gICAgICB0aGlzLl9fZ2xvYmFsUHJvcHMgPSB0aGlzLmdldE5hdGl2ZUx5bngoKS5fX2dsb2JhbFByb3BzIHx8IHt9O1xuICAgICAgdGhpcy5fX3ByZXNldERhdGEgPSB0aGlzLmdldE5hdGl2ZUx5bngoKS5fX3ByZXNldERhdGEgfHwge307XG4gICAgfSBlbHNlIHtcbiAgICAgIGNvbnN0IGNhY2hlID0ge307XG4gICAgICB0aGlzLnJlcXVpcmVNb2R1bGUuY2FjaGUgPSBjYWNoZTtcbiAgICAgIHRoaXMucmVxdWlyZU1vZHVsZUFzeW5jLmNhY2hlID0gY2FjaGU7XG4gICAgICB0aGlzLmxvYWRTY3JpcHQuY2FjaGUgPSB7fTtcbiAgICAgIHRoaXMuX19nbG9iYWxQcm9wcyA9IHRoaXMuZ2V0TmF0aXZlTHlueCgpLl9fZ2xvYmFsUHJvcHMgfHwge307XG4gICAgICB0aGlzLl9fcHJlc2V0RGF0YSA9IHRoaXMuZ2V0TmF0aXZlTHlueCgpLl9fcHJlc2V0RGF0YSB8fCB7fTtcbiAgICAgIHRoaXMuX3N3aXRjaGVzID0ge307XG4gICAgfVxuICB9XG5cbiAgc2V0SW50ZXJ2YWw6IEx5bnhTZXRUaW1lb3V0ID0gdGhpcy5nZXRBcHAoKS53cmFwUmVwb3J0KFxuICAgIHRoaXMuZ2V0QXBwKCkuc2V0SW50ZXJ2YWwsXG4gICAgJ3NldEludGVydmFsIEVycm9yJ1xuICApO1xuICBjbGVhckludGVydmFsID0gdGhpcy5nZXROYXRpdmVBcHAoKS5jbGVhckludGVydmFsO1xuICBjbGVhclRpbWVvdXQgPSB0aGlzLmdldE5hdGl2ZUFwcCgpLmNsZWFyVGltZW91dDtcblxuICByZXN1bWVFeHBvc3VyZSA9IHRoaXMuZ2V0QXBwKCkuX2FwaUxpc3RbJ3Jlc3VtZUV4cG9zdXJlJ10gYXMgKCkgPT4gdm9pZDtcblxuICByZXF1aXJlTW9kdWxlID0gPFJlcXVpcmVNb2R1bGU+KDxUPihcbiAgICBwYXRoOiBzdHJpbmcsXG4gICAgZW50cnlOYW1lPzogc3RyaW5nLFxuICAgIG9wdGlvbnM/OiB7IHRpbWVvdXQ6IG51bWJlciB9XG4gICk6IFQgPT4ge1xuICAgIGlmICh0aGlzLnJlcXVpcmVNb2R1bGUuY2FjaGVbcGF0aF0pIHtcbiAgICAgIHJldHVybiB0aGlzLnJlcXVpcmVNb2R1bGUuY2FjaGVbcGF0aF0gYXMgVDtcbiAgICB9XG4gICAgLy8gVE9ETyh3YW5ncWluZ3l1KTogZGVhbCB3aXRoIGN5Y2xpYyByZXF1aXJlTW9kdWxlXG4gICAgY29uc3QgZXhwb3J0cyA9IHRoaXMuZ2V0QXBwKCkucmVxdWlyZU1vZHVsZTxUPihwYXRoLCBlbnRyeU5hbWUsIG9wdGlvbnMpO1xuXG4gICAgLy8gV2hlbiBlcnJvciBoYXBwZW5zIGluIGxvYWRpbmcgb3IgZXhlY3V0aW5nLCBhIEpTIGVycm9yIHdpbGwgYmUgdGhyb3duLlxuICAgIC8vIFNvIHdoZW4gd2UgYXJlIGhlcmUsIHRoZSBtb2R1bGUgaXMgbG9hZGVkIGFuZCBleGVjdXRlZCBzdWNjZXNzZnVsbHkuXG4gICAgdGhpcy5yZXF1aXJlTW9kdWxlLmNhY2hlW3BhdGhdID0gZXhwb3J0cztcbiAgICByZXR1cm4gZXhwb3J0cztcbiAgfSk7XG5cbiAgcmVxdWlyZU1vZHVsZUFzeW5jID0gPFJlcXVpcmVNb2R1bGVBc3luYz4oPFQ+KFxuICAgIHBhdGg6IHN0cmluZyxcbiAgICBjYWxsYmFjaz86IChlcnJvcj86IEVycm9yLCByZXQ/OiBUKSA9PiB2b2lkXG4gICk6IHZvaWQgPT4ge1xuICAgIGNhbGxiYWNrID8/PSAoZXJyb3I/OiBFcnJvcikgPT4ge1xuICAgICAgaWYgKCFlcnJvcikge1xuICAgICAgICAvLyBgdW5kZWZpbmVkIHwgbnVsbGAgbWVhbnMgbm8gZXJyb3Igb2NjdXJyZWRcbiAgICAgICAgcmV0dXJuO1xuICAgICAgfVxuICAgICAgdGhpcy5nZXRBcHAoKS5oYW5kbGVVc2VyRXJyb3IoZXJyb3IpO1xuICAgIH07XG5cbiAgICBpZiAodGhpcy5yZXF1aXJlTW9kdWxlQXN5bmMuY2FjaGVbcGF0aF0pIHtcbiAgICAgIGNhbGxiYWNrKG51bGwsIHRoaXMucmVxdWlyZU1vZHVsZUFzeW5jLmNhY2hlW3BhdGhdIGFzIFQpO1xuICAgICAgcmV0dXJuO1xuICAgIH1cbiAgICAvLyBUT0RPKHdhbmdxaW5neXUpOiBkZWFsIHdpdGggY3ljbGljIHJlcXVpcmVNb2R1bGVcbiAgICB0aGlzLmdldEFwcCgpLnJlcXVpcmVNb2R1bGVBc3luYzxUPihwYXRoLCAoZXJyb3IsIGV4cG9ydHMpID0+IHtcbiAgICAgIGlmICghZXJyb3IpIHtcbiAgICAgICAgLy8gT25seSBjYWNoZSB0aGUgZXhwb3J0cyB3aGVuIG5vIGVycm9yIGhhcHBlbmRzLlxuICAgICAgICB0aGlzLnJlcXVpcmVNb2R1bGVBc3luYy5jYWNoZVtwYXRoXSA9IGV4cG9ydHM7XG4gICAgICB9XG4gICAgICBjYWxsYmFjayhlcnJvciwgZXhwb3J0cyk7XG4gICAgfSk7XG4gIH0pO1xuXG4gIGNyZWF0ZUVsZW1lbnQgPSAocm9vdElkOiBzdHJpbmcsIGlkOiBzdHJpbmcpID0+XG4gICAgdGhpcy5nZXROYXRpdmVMeW54KCkuY3JlYXRlRWxlbWVudChyb290SWQsIGlkKTtcblxuICBnZXRFbGVtZW50QnlJZCA9IChpZDogc3RyaW5nKTogRWxlbWVudCA9PiB7XG4gICAgcmV0dXJuIG5ldyBFbGVtZW50KCcnLCBpZCwgdGhpcyk7XG4gIH07XG5cbiAgcmVwb3J0RXJyb3IgPSAoZXJyb3I6IEVycm9yIHwgc3RyaW5nLCBvcHRpb25zPzogeyBsZXZlbD86IHN0cmluZyB9KTogdm9pZCA9PiB7XG4gICAgbGV0IGVycm9yT2JqOiBFcnJvcjtcbiAgICBpZiAoaXNFcnJvcihlcnJvcikpIHtcbiAgICAgIGVycm9yT2JqID0gZXJyb3I7XG4gICAgfSBlbHNlIHtcbiAgICAgIGxldCBtZXNzYWdlOiBzdHJpbmc7XG4gICAgICBpZiAodHlwZW9mIGVycm9yICE9PSAnc3RyaW5nJykge1xuICAgICAgICBtZXNzYWdlID0gSlNPTi5zdHJpbmdpZnkoZXJyb3IpO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgbWVzc2FnZSA9IGVycm9yO1xuICAgICAgfVxuICAgICAgZXJyb3JPYmogPSBuZXcgRXJyb3IobWVzc2FnZSk7XG4gICAgfVxuICAgIGNvbnN0IHsgbGV2ZWwgPSAnZXJyb3InIH0gPSBvcHRpb25zIHx8IHt9O1xuICAgIGxldCBlcnJvckxldmVsOiBMeW54RXJyb3JMZXZlbDtcbiAgICBzd2l0Y2ggKGxldmVsKSB7XG4gICAgICBjYXNlICdlcnJvcic6XG4gICAgICAgIGVycm9yTGV2ZWwgPSBMeW54RXJyb3JMZXZlbC5FcnJvcjtcbiAgICAgICAgYnJlYWs7XG4gICAgICBjYXNlICd3YXJuaW5nJzpcbiAgICAgICAgZXJyb3JMZXZlbCA9IEx5bnhFcnJvckxldmVsLldhcm47XG4gICAgICAgIGJyZWFrO1xuICAgICAgY2FzZSAnZmF0YWwnOlxuICAgICAgICBlcnJvckxldmVsID0gTHlueEVycm9yTGV2ZWwuRmF0YWw7XG4gICAgICAgIGJyZWFrO1xuICAgICAgZGVmYXVsdDpcbiAgICAgICAgZXJyb3JMZXZlbCA9IEx5bnhFcnJvckxldmVsLkVycm9yO1xuICAgIH1cbiAgICB0aGlzLmdldEFwcCgpLmhhbmRsZVVzZXJFcnJvcihlcnJvck9iaiwgZXJyb3JPYmouY2F1c2UsIGVycm9yTGV2ZWwpO1xuICB9O1xuXG4gIHJlZ2lzdGVyTW9kdWxlID0gPE1vZHVsZSBleHRlbmRzIG9iamVjdD4oXG4gICAgbmFtZTogc3RyaW5nLFxuICAgIG1vZHVsZTogTW9kdWxlXG4gICk6IHZvaWQgPT4gdGhpcy5nZXRBcHAoKS5yZWdpc3Rlck1vZHVsZShuYW1lLCBtb2R1bGUpO1xuXG4gIGdldEpTTW9kdWxlID0gPE1vZHVsZSA9IHVua25vd24+KG5hbWU6IHN0cmluZyk6IE1vZHVsZSA9PiB7XG4gICAgcmV0dXJuIHRoaXMuZ2V0QXBwKCkuZ2V0SlNNb2R1bGU8TW9kdWxlPihuYW1lKTtcbiAgfTtcblxuICBnZXRUZXh0SW5mbyA9IHRoaXMuZ2V0QXBwKCkuX2FwaUxpc3RbJ2dldFRleHRJbmZvJ10gYXMgKFxuICAgIHRleHQ6IHN0cmluZyxcbiAgICBpbmZvOiBUZXh0SW5mb1xuICApID0+IFRleHRNZXRyaWNzO1xuXG4gIGFkZEZvbnQgPSAoXG4gICAgZm9udDogeyBzcmM6IHN0cmluZzsgJ2ZvbnQtZmFtaWx5Jzogc3RyaW5nIH0sXG4gICAgY2FsbGJhY2s6IChlPzogRXJyb3IpID0+IHZvaWRcbiAgKSA9PiB7XG4gICAgaWYgKCFpc09iamVjdChmb250KSkge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKCdUaGUgZmlyc3QgYXJndW1lbnQgbXVzdCBiZSBvYmplY3QgdHlwZScpO1xuICAgIH1cbiAgICBpZiAoIWlzU3RyaW5nKGZvbnRbJ2ZvbnQtZmFtaWx5J10pIHx8ICFpc1N0cmluZyhmb250WydzcmMnXSkpIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcignVGhlIGZvbnQgdmFsdWUgbXVzdCBoYXZlIGZvbnQtZmFtaWx5IGFuZCBzcmMnKTtcbiAgICB9XG4gICAgaWYgKCFpc0Z1bmN0aW9uKGNhbGxiYWNrKSkge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKCdUaGUgc2Vjb25kIGFyZ3VtZW50IG11c3QgYmUgZnVuY3Rpb24gdHlwZScpO1xuICAgIH1cblxuICAgIHRoaXMuZ2V0TmF0aXZlTHlueCgpLmFkZEZvbnQoZm9udCwgY2FsbGJhY2spO1xuICB9O1xuXG4gIHN0b3BFeHBvc3VyZSA9IHRoaXMuZ2V0QXBwKCkuX2FwaUxpc3RbJ3N0b3BFeHBvc3VyZSddIGFzIChvcHRpb25zPzoge1xuICAgIHNlbmRFdmVudDogYm9vbGVhbjtcbiAgfSkgPT4gdm9pZDtcblxuICBzZXRPYnNlcnZlckZyYW1lUmF0ZSA9IHRoaXMuZ2V0QXBwKCkuX2FwaUxpc3RbXG4gICAgJ3NldE9ic2VydmVyRnJhbWVSYXRlJ1xuICBdIGFzIChvcHRpb25zPzogeyBmb3JQYWdlUmVjdD86IG51bWJlcjsgZm9yRXhwb3N1cmVDaGVjaz86IG51bWJlciB9KSA9PiB2b2lkO1xuXG4gIHBlcmZvcm1hbmNlOiBQZXJmb3JtYW5jZSA9IHRoaXMuZ2V0QXBwKCkucGVyZm9ybWFuY2U7XG5cbiAgYmVmb3JlUHVibGlzaEV2ZW50ID0gdGhpcy5nZXRBcHAoKS5fYW9wTWFuYWdlci5fYmVmb3JlUHVibGlzaEV2ZW50O1xuXG4gIGRpc3BhdGNoU2Vzc2lvblN0b3JhZ2VFdmVudChldmVudDogTWVzc2FnZUV2ZW50KTogdm9pZCB7XG4gICAgdmFyIGV2ZW50UmVzdWx0ID0gdGhpcy5nZXRDb3JlQ29udGV4dCgpLmRpc3BhdGNoRXZlbnQoZXZlbnQpO1xuXG4gICAgLy8gSW4gTHlueFZpZXcsIHRoZSBldmVudCBoYXMgYmVlbiBzdWNlc3NmdWxseSBoYW5kbGVkIGJ5IGBDb3JlQ29udGV4dGAuXG4gICAgaWYgKGV2ZW50UmVzdWx0ID09IDApIHtcbiAgICAgIHJldHVybjtcbiAgICB9XG5cbiAgICAvLyBJbiBydW50aW1lIHN0YW5kYWxvbmUgbW9kZSwgcnVudGltZSBjYW5ub3QgZGlzcGF0Y2ggZXZlbnQgdG8gYENvcmVDb250ZXh0YCxcbiAgICAvLyBmYWxsYmFjayB0byBgSlNDb250ZXh0YCBzbyB0aGF0IHJ1bnRpbWUgY2FuIGhhbmRsZSBzZXNzaW9uIHN0b3JhZ2UgZXZlbnRzXG4gICAgLy8gYnkgaXRzZWxmLlxuICAgIHRoaXMuZ2V0SlNDb250ZXh0KCkuZGlzcGF0Y2hFdmVudChldmVudCk7XG4gIH1cblxuICAvLyBzZXNzaW9uU3RvcmFnZSBBcGlcbiAgc2V0U2Vzc2lvblN0b3JhZ2VJdGVtID0gPFQ+KGtleTogc3RyaW5nLCB2YWx1ZTogVCk6IHZvaWQgPT4ge1xuICAgIHRoaXMuZGlzcGF0Y2hTZXNzaW9uU3RvcmFnZUV2ZW50KHtcbiAgICAgIHR5cGU6IE1lc3NhZ2VFdmVudFR5cGUuRVZFTlRfU0VUX1NFU1NJT05fU1RPUkFHRSxcbiAgICAgIGRhdGE6IHtcbiAgICAgICAga2V5LFxuICAgICAgICB2YWx1ZSxcbiAgICAgIH0sXG4gICAgfSk7XG4gIH07XG5cbiAgZ2V0U2Vzc2lvblN0b3JhZ2VJdGVtID0gPFQ+KFxuICAgIGtleTogc3RyaW5nLFxuICAgIGNhbGxiYWNrOiAodmFsdWU6IFQpID0+IHZvaWRcbiAgKTogdm9pZCA9PiB7XG4gICAgLy8gVE9ETyhuaWhhby5yb3lhbCk6IHJlZmFjdG9yIHRvIGRpc3BhdGNoRXZlbnQgYWZ0ZXIgQXBpQ2FsbGJhY2sgc3VwcG9ydGVkLlxuICAgIHRoaXMuZ2V0TmF0aXZlQXBwKCkuZ2V0U2Vzc2lvblN0b3JhZ2VJdGVtKGtleSwgY2FsbGJhY2spO1xuICB9O1xuXG4gIHN1YnNjcmliZVNlc3Npb25TdG9yYWdlID0gPFQ+KFxuICAgIGtleTogc3RyaW5nLFxuICAgIGNhbGxiYWNrOiAodmFsdWU6IFQpID0+IHZvaWRcbiAgKTogbnVtYmVyID0+IHtcbiAgICAvLyBUT0RPKG5paGFvLnJveWFsKTogcmVmYWN0b3IgdG8gZGlzcGF0Y2hFdmVudCBhZnRlciBBcGlDYWxsYmFjayBzdXBwb3J0ZWQuXG4gICAgbGV0IGxpc3RlbmVySWQgPSBMeW54Ll9fcmVnaXN0ZXJTaGFyZWREYXRhQ291bnRlcisrO1xuICAgIHRoaXMuZ2V0TmF0aXZlQXBwKCkuc3Vic2NyaWJlU2Vzc2lvblN0b3JhZ2Uoa2V5LCBsaXN0ZW5lcklkLCBjYWxsYmFjayk7XG4gICAgcmV0dXJuIGxpc3RlbmVySWQ7XG4gIH07XG5cbiAgdW5zdWJzY3JpYmVTZXNzaW9uU3RvcmFnZSA9IChrZXk6IHN0cmluZywgbGlzdGVuZXJJZDogbnVtYmVyKSA9PiB7XG4gICAgdGhpcy5kaXNwYXRjaFNlc3Npb25TdG9yYWdlRXZlbnQoe1xuICAgICAgdHlwZTogTWVzc2FnZUV2ZW50VHlwZS5FVkVOVF9VTlNVQlNDUklCRV9TRVNTSU9OX1NUT1JBR0UsXG4gICAgICBkYXRhOiB7XG4gICAgICAgIGtleSxcbiAgICAgICAgbGlzdGVuZXJJZCxcbiAgICAgIH0sXG4gICAgfSk7XG4gIH07XG5cbiAgZ2V0RGV2dG9vbCA9IHRoaXMuZ2V0TmF0aXZlTHlueCgpLmdldERldnRvb2w7XG4gIGdldENvcmVDb250ZXh0ID0gdGhpcy5nZXROYXRpdmVMeW54KCkuZ2V0Q29yZUNvbnRleHQ7XG4gIGdldEpTQ29udGV4dCA9IHRoaXMuZ2V0TmF0aXZlTHlueCgpLmdldEpTQ29udGV4dDtcbiAgZ2V0VUlDb250ZXh0ID0gdGhpcy5nZXROYXRpdmVMeW54KCkuZ2V0VUlDb250ZXh0O1xuICBnZXROYXRpdmUgPSB0aGlzLmdldE5hdGl2ZUx5bngoKS5nZXROYXRpdmU7XG4gIGdldEVuZ2luZSA9IHRoaXMuZ2V0TmF0aXZlTHlueCgpLmdldEVuZ2luZTtcblxuICBnZXRDdXN0b21TZWN0aW9uU3luYyA9IHRoaXMuZ2V0TmF0aXZlTHlueCgpLmdldEN1c3RvbVNlY3Rpb25TeW5jO1xuXG4gIGFjY2Vzc2liaWxpdHlBbm5vdW5jZSA9IHRoaXMuZ2V0TmF0aXZlQXBwKCkubmF0aXZlTW9kdWxlUHJveHlcbiAgICAuTHlueEFjY2Vzc2liaWxpdHlNb2R1bGU/LmFjY2Vzc2liaWxpdHlBbm5vdW5jZTtcblxuICByZXF1ZXN0UmVzb3VyY2VQcmVmZXRjaCA9IHRoaXMuZ2V0TmF0aXZlQXBwKCkubmF0aXZlTW9kdWxlUHJveHlcbiAgICAuTHlueFJlc291cmNlTW9kdWxlPy5yZXF1ZXN0UmVzb3VyY2VQcmVmZXRjaDtcblxuICBjYW5jZWxSZXNvdXJjZVByZWZldGNoID0gdGhpcy5nZXROYXRpdmVBcHAoKS5uYXRpdmVNb2R1bGVQcm94eVxuICAgIC5MeW54UmVzb3VyY2VNb2R1bGU/LmNhbmNlbFJlc291cmNlUHJlZmV0Y2g7XG5cbiAgc2V0U2hhcmVkRGF0YSA9IChkYXRhS2V5OiBzdHJpbmcsIGRhdGFWYWw6IHVua25vd24pOiB2b2lkID0+IHtcbiAgICBuYXRpdmVHbG9iYWwuc2hhcmVkRGF0YVtkYXRhS2V5XSA9IGRhdGFWYWw7XG4gICAgbGV0IHZhcmlhYmxlID0ge307XG4gICAgdmFyaWFibGVbZGF0YUtleV0gPSBkYXRhVmFsO1xuICAgIG5hdGl2ZUdsb2JhbC5zaGFyZURhdGFTdWJqZWN0Lm5vdGlmeURhdGFDaGFuZ2UodmFyaWFibGUpO1xuICB9O1xuXG4gIGdldFNoYXJlZERhdGEgPSA8VCA9IHVua25vd24+KGRhdGFLZXk6IHN0cmluZyk6IFQgPT4ge1xuICAgIGxldCBkYXRhID0gbmF0aXZlR2xvYmFsLnNoYXJlZERhdGFbZGF0YUtleV07XG4gICAgaWYgKE5PREVfRU5WID09PSAnZGV2ZWxvcG1lbnQnKSB7XG4gICAgICBpZiAoZGF0YSA9PT0gdW5kZWZpbmVkKSB7XG4gICAgICAgIGRhdGEgPSB0aGlzLmdldEFwcCgpLk5hdGl2ZU1vZHVsZXMuTHlueFJlY29yZGVyUmVwbGF5RGF0YU1vZHVsZT8uZ2V0U2hhcmVkRGF0YShcbiAgICAgICAgICBkYXRhS2V5XG4gICAgICAgICkudmFsdWU7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICB0aGlzLmdldE5hdGl2ZUFwcCgpLnJlY29yZFNoYXJlZERhdGEoZGF0YUtleSwgZGF0YSk7XG4gICAgICB9XG4gICAgfVxuICAgIHJldHVybiBkYXRhO1xuICB9O1xuXG4gIHJlZ2lzdGVyU2hhcmVkRGF0YU9ic2VydmVyID0gPFQ+KGNhbGxiYWNrOiAoZGF0YTogVCkgPT4gdm9pZCk6IHZvaWQgPT5cbiAgICBuYXRpdmVHbG9iYWwuc2hhcmVEYXRhU3ViamVjdC5yZWdpc3Rlck9ic2VydmVyKGNhbGxiYWNrKTtcblxuICByZW1vdmVTaGFyZWREYXRhT2JzZXJ2ZXIgPSA8VD4oY2FsbGJhY2s6IChkYXRhOiBUKSA9PiB2b2lkKTogdm9pZCA9PlxuICAgIG5hdGl2ZUdsb2JhbC5zaGFyZURhdGFTdWJqZWN0LnJlbW92ZU9ic2VydmVyKGNhbGxiYWNrKTtcblxuICB0cmlnZ2VyTGVwdXNHbG9iYWxFdmVudCA9IChldmVudDogc3RyaW5nLCBwYXJhbXM6IFJlY29yZDxhbnksIGFueT4pOiB2b2lkID0+XG4gICAgdGhpcy5nZXROYXRpdmVBcHAoKS50cmlnZ2VyTGVwdXNHbG9iYWxFdmVudChldmVudCwgcGFyYW1zKTtcblxuICAvLyBmb3IgcmVsb2FkXG4gIHJlbG9hZCA9ICh2YWx1ZTogb2JqZWN0LCBjYWxsYmFjazogKCkgPT4gdm9pZCkgPT4ge1xuICAgIHRoaXMuZ2V0TmF0aXZlTHlueCgpLnJlbG9hZCh2YWx1ZSwgY2FsbGJhY2spO1xuICB9O1xuXG4gIGNyZWF0ZUludGVyc2VjdGlvbk9ic2VydmVyOiBDcmVhdGVJbnRlcnNlY3Rpb25PYnNlcnZlckZ1bmM7XG5cbiAgZmV0Y2hEeW5hbWljQ29tcG9uZW50ID0gKFxuICAgIHVybDogc3RyaW5nLFxuICAgIG9wdGlvbnM6IFJlY29yZDxzdHJpbmcsIGFueT4sXG4gICAgY2FsbGJhY2s6IChyZXM6IHsgY29kZTogbnVtYmVyIH0pID0+IHZvaWQsXG4gICAgaWQ6IHN0cmluZ1tdXG4gICkgPT4gdGhpcy5nZXROYXRpdmVMeW54KCkuZmV0Y2hEeW5hbWljQ29tcG9uZW50KHVybCwgb3B0aW9ucywgY2FsbGJhY2ssIGlkKTtcblxuICAvLyBXcmFwcGVyIFF1ZXJ5Q29tcG9uZW50IHRvIGRlY2lkZSBpZiBjb21wb25lbnQgaGFzIGxvYWRlZC5cbiAgUXVlcnlDb21wb25lbnQgPSAoc291cmNlOiBzdHJpbmcsIGNhbGxiYWNrOiAocmVzdWx0OiBhbnkpID0+IHZvaWQpID0+IHtcbiAgICBjb25zdCBpbm5lckludm9rZUNhbGxiYWNrID0gKCkgPT4ge1xuICAgICAgY2FsbGJhY2soe1xuICAgICAgICBjb2RlOiAwLFxuICAgICAgICBkYXRhOiB7IHVybDogc291cmNlLCBzeW5jOiB0cnVlLCBlcnJvcl9tZXNzYWdlOiAnJywgbW9kZTogJ2NhY2hlJyB9LFxuICAgICAgICBkZXRhaWw6IHsgc2NoZW1hOiBzb3VyY2UsIGNhY2hlOiBmYWxzZSwgZXJyTXNnOiAnJyB9LFxuICAgICAgfSk7XG4gICAgfTtcbiAgICAvLyBpZiBkeW5hbWljIGNvbXBvbmV0IGhhcyBiZWVuIHJlYWR5IGluIGJhY2tncm91bmQgdGhyZWFkLCBjYWxsYmFjayBkaXJlY3RseVxuICAgIGlmICh0aGlzLmdldEFwcCgpLmxvYWRlZER5bmFtaWNDb21wb25lbnRzU2V0Lmhhcyhzb3VyY2UpKSB7XG4gICAgICBpbm5lckludm9rZUNhbGxiYWNrKCk7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIC8vIGlmIGR5bmFtaWMgY29tcG9uZXQgaGFzIGJlZW4gcmVhZHkgaW4gbWFpbiB0aHJlYWQsIGxvYWREeW5hbWljQ29tcG9uZW50IGFuZCBjYWxsYmFjayBkaXJlY3RseVxuICAgIGNvbnN0IGlubmVyQ2FsbGJhY2sgPSAocmVzdWx0OiBhbnkpID0+IHtcbiAgICAgIGlmIChyZXN1bHQuX19oYXNSZWFkeSA9PT0gdHJ1ZSkge1xuICAgICAgICBuYXRpdmVHbG9iYWwubG9hZER5bmFtaWNDb21wb25lbnQodGhpcy5nZXRBcHAoKSwgc291cmNlKTtcbiAgICAgICAgaW5uZXJJbnZva2VDYWxsYmFjaygpO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgY2FsbGJhY2socmVzdWx0KTtcbiAgICAgIH1cbiAgICB9O1xuICAgIC8vIHF1ZXJ5IGNvbXBvbmV0XG4gICAgdGhpcy5nZXROYXRpdmVMeW54KCkuUXVlcnlDb21wb25lbnQoc291cmNlLCBpbm5lckNhbGxiYWNrKTtcbiAgfTtcblxuICBsb2FkRHluYW1pY0NvbXBvbmVudDogTG9hZER5bmFtaWNDb21wb25lbnRGdW5jID0gKFxuICAgIGlkT3JVcmw6IHN0cmluZyB8IHN0cmluZ1tdLFxuICAgIHVybE9yT3B0aW9ucz86IHN0cmluZyB8IFJlY29yZDxzdHJpbmcsIGFueT4sXG4gICAgb3B0aW9uczogUmVjb3JkPHN0cmluZywgYW55PiA9IHt9XG4gICk6IFByb21pc2U8XG4gICAgTG9hZER5bmFtaWNDb21wb25lbnRTdWNjZXNzUmVzdWx0IHwgTG9hZER5bmFtaWNDb21wb25lbnRGYWlsZWRSZXN1bHRcbiAgPiA9PiB7XG4gICAgcmV0dXJuIG5ldyB0aGlzLlByb21pc2UoKHJlc29sdmUsIHJlamVjdCkgPT4ge1xuICAgICAgLy8gbGVnYWwgcGFyYW0gdHlwZXM6XG4gICAgICAvLyAwLiAodXJsOiBzdHJpbmcsID9vcHRpb25zKVxuICAgICAgLy8gMS4gKGlkOiBzdHJpbmcsIHVybDogc3RyaW5nLCA/b3B0aW9ucylcbiAgICAgIC8vIDIuIChpZHM6IHN0cmluZ1tdLCB1cmw6IHN0cmluZywgP29wdGlvbnMpXG4gICAgICBsZXQgaWRzOiBzdHJpbmdbXSA9IFtdO1xuICAgICAgbGV0IHVybDogc3RyaW5nO1xuICAgICAgaWYgKEFycmF5LmlzQXJyYXkoaWRPclVybCkpIHtcbiAgICAgICAgaWRzID0gaWRPclVybDtcbiAgICAgICAgdXJsID0gdXJsT3JPcHRpb25zIGFzIHN0cmluZztcbiAgICAgIH0gZWxzZSBpZiAodHlwZW9mIHVybE9yT3B0aW9ucyA9PT0gJ3N0cmluZycpIHtcbiAgICAgICAgaWRzID0gW2lkT3JVcmxdO1xuICAgICAgICB1cmwgPSB1cmxPck9wdGlvbnM7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICB1cmwgPSBpZE9yVXJsO1xuICAgICAgICBvcHRpb25zID0gdXJsT3JPcHRpb25zO1xuICAgICAgfVxuICAgICAgaWYgKHRoaXMuZ2V0QXBwKCkubG9hZGVkRHluYW1pY0NvbXBvbmVudHNTZXQuaGFzKHVybCkpIHtcbiAgICAgICAgLy8gaW52b2tlIGRpcmVjdGx5XG4gICAgICAgIHJlc29sdmUoe1xuICAgICAgICAgIGNvZGU6IDAsXG4gICAgICAgICAgZGF0YTogeyB1cmw6IHVybCwgc3luYzogZmFsc2UsIGVycm9yX21lc3NhZ2U6ICcnLCBtb2RlOiAnbm9ybWFsJyB9LFxuICAgICAgICAgIGRldGFpbDogeyBzY2hlbWE6IHVybCwgY2FjaGU6IGZhbHNlLCBlcnJNc2c6ICcnIH0sXG4gICAgICAgIH0gYXMgTG9hZER5bmFtaWNDb21wb25lbnRTdWNjZXNzUmVzdWx0KTtcbiAgICAgICAgcmV0dXJuO1xuICAgICAgfVxuXG4gICAgICB0aGlzLmdldE5hdGl2ZUx5bngoKS5mZXRjaER5bmFtaWNDb21wb25lbnQoXG4gICAgICAgIHVybCxcbiAgICAgICAgb3B0aW9ucyxcbiAgICAgICAgKHJlcykgPT4ge1xuICAgICAgICAgIGlmIChyZXMgJiYgcmVzLmNvZGUgPT0gMCkge1xuICAgICAgICAgICAgcmVzb2x2ZShyZXMgYXMgTG9hZER5bmFtaWNDb21wb25lbnRTdWNjZXNzUmVzdWx0KTtcbiAgICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgICAgcmVqZWN0KHJlcyk7XG4gICAgICAgICAgfVxuICAgICAgICB9LFxuICAgICAgICBpZHNcbiAgICAgICk7XG4gICAgfSk7XG4gIH07XG5cbiAgZmV0Y2ggPSAoaW5wdXQ6IFJlcXVlc3RJbmZvLCBpbml0PzogUmVxdWVzdEluaXQpOiBQcm9taXNlPFJlc3BvbnNlPiA9PiB7XG4gICAgcmV0dXJuIG5ldyB0aGlzLlByb21pc2UoKHJlc29sdmUsIHJlamVjdCkgPT4ge1xuICAgICAgY29uc3QgcmVxdWVzdCA9IG5ldyBuYXRpdmVHbG9iYWwuUmVxdWVzdChpbnB1dCwgaW5pdCk7XG4gICAgICBjb25zdCBzaWduYWwgPSByZXF1ZXN0LnNpZ25hbDtcbiAgICAgIGlmIChzaWduYWwuYWJvcnRlZCkge1xuICAgICAgICByZXR1cm4gcmVqZWN0KHNpZ25hbC5yZWFzb24pO1xuICAgICAgfVxuXG4gICAgICBzaWduYWwuYWRkRXZlbnRMaXN0ZW5lcignYWJvcnQnLCAoZXZlbnQpID0+IHtcbiAgICAgICAgcmVqZWN0KHNpZ25hbC5yZWFzb24pO1xuICAgICAgfSk7XG5cbiAgICAgIGNvbnN0IGZldGNoQXJnID0ge1xuICAgICAgICBtZXRob2Q6IHJlcXVlc3QubWV0aG9kLFxuICAgICAgICB1cmw6IHJlcXVlc3QudXJsLFxuICAgICAgICBvcmlnaW46IHRoaXMuZ2V0TmF0aXZlQXBwKCkuX19wYWdlVXJsLFxuICAgICAgICBoZWFkZXJzOiBPYmplY3QuZnJvbUVudHJpZXMocmVxdWVzdC5oZWFkZXJzLmVudHJpZXMoKSksXG4gICAgICAgIGJvZHk6IHJlcXVlc3QuX2FycmF5QnVmZmVyLFxuICAgICAgICBseW54RXh0ZW5zaW9uOiByZXF1ZXN0Lmx5bnhFeHRlbnNpb24sXG4gICAgICB9O1xuICAgICAgY29uc3QgdXNlU3RyZWFtaW5nID0gcmVxdWVzdC5seW54RXh0ZW5zaW9uWyd1c2VTdHJlYW1pbmcnXTtcbiAgICAgIHRoaXMuZ2V0QXBwKCkuTmF0aXZlTW9kdWxlcy5MeW54RmV0Y2hNb2R1bGUuZmV0Y2goXG4gICAgICAgIGZldGNoQXJnLFxuICAgICAgICAocmVzcG9uc2U6IGFueSkgPT4ge1xuICAgICAgICAgIGlmIChzaWduYWwuYWJvcnRlZCkge1xuICAgICAgICAgICAgcmV0dXJuO1xuICAgICAgICAgIH1cbiAgICAgICAgICB0cnkge1xuICAgICAgICAgICAgY29uc3Qgc3RyZWFtaW5nQm9keVJlY2VpdmVyID0gbmV3ICh0aGlzLmdldEFwcCgpLl9SZWFkYWJsZVN0cmVhbUNsYXNzKSgpO1xuXG4gICAgICAgICAgICBjb25zdCByZXNwID0gbmV3IG5hdGl2ZUdsb2JhbC5SZXNwb25zZShcbiAgICAgICAgICAgICAgdXNlU3RyZWFtaW5nID8gc3RyZWFtaW5nQm9keVJlY2VpdmVyIDogcmVzcG9uc2UuYm9keSxcbiAgICAgICAgICAgICAgcmVzcG9uc2VcbiAgICAgICAgICAgICk7XG5cbiAgICAgICAgICAgIGlmICh1c2VTdHJlYW1pbmcpIHtcbiAgICAgICAgICAgICAgY29uc3QgaWQgPSByZXNwLmx5bnhFeHRlbnNpb25bJ3N0cmVhbWluZ0lkJ107XG4gICAgICAgICAgICAgIHRoaXMuZ2V0QXBwKCkuR2xvYmFsRXZlbnRFbWl0dGVyLmFkZExpc3RlbmVyKFxuICAgICAgICAgICAgICAgIGlkLFxuICAgICAgICAgICAgICAgIChyZXN1bHQ6IGFueSkgPT4ge1xuICAgICAgICAgICAgICAgICAgY29uc3QgZXZlbnQgPSByZXN1bHQuZXZlbnQ7XG4gICAgICAgICAgICAgICAgICBpZiAoZXZlbnQgPT09ICdvbkRhdGEnKSB7XG4gICAgICAgICAgICAgICAgICAgIHN0cmVhbWluZ0JvZHlSZWNlaXZlci5vbkRhdGEocmVzdWx0LmRhdGEpO1xuICAgICAgICAgICAgICAgICAgfSBlbHNlIGlmIChldmVudCA9PT0gJ29uRW5kJykge1xuICAgICAgICAgICAgICAgICAgICBzdHJlYW1pbmdCb2R5UmVjZWl2ZXIub25FbmQoKTtcbiAgICAgICAgICAgICAgICAgIH0gZWxzZSBpZiAoZXZlbnQgPT09ICdvbkVycm9yJykge1xuICAgICAgICAgICAgICAgICAgICBzdHJlYW1pbmdCb2R5UmVjZWl2ZXIub25FcnJvcihyZXN1bHQuZXJyb3IpO1xuICAgICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIHJlc29sdmUocmVzcCk7XG4gICAgICAgICAgfSBjYXRjaCAoXykge1xuICAgICAgICAgICAgLy8gQ2F0Y2hlcyBhbnkgZXhjZXB0aW9uIHRoYXQgbWlnaHQgbGVhZCB0byBhIGZhaWx1cmUgaW5cbiAgICAgICAgICAgIC8vIGNyZWF0aW5nIGEgUmVzcG9uc2UgYW5kIHRocm93cyB0aGUgZXJyb3IgdXNpbmcgYHJlamVjdGAsXG4gICAgICAgICAgICAvLyBlbmFibGluZyB0aGUgZnJvbnRlbmQgdG8gaGFuZGxlIHRoZSBlcnJvci5cbiAgICAgICAgICAgIHJlamVjdChuZXcgVHlwZUVycm9yKHJlc3BvbnNlLnN0YXR1c1RleHQpKTtcbiAgICAgICAgICB9XG4gICAgICAgIH0sXG4gICAgICAgIChlcnJvcjogYW55KSA9PiB7XG4gICAgICAgICAgaWYgKHNpZ25hbC5hYm9ydGVkKSB7XG4gICAgICAgICAgICByZXR1cm47XG4gICAgICAgICAgfVxuICAgICAgICAgIHJlamVjdChuZXcgVHlwZUVycm9yKGVycm9yLm1lc3NhZ2UpKTtcbiAgICAgICAgfVxuICAgICAgKTtcbiAgICB9KTtcbiAgfTtcblxuICBFdmVudFNvdXJjZSA9IGNyZWF0ZUV2ZW50U291cmNlKHRoaXMuZmV0Y2gpO1xuXG4gIGNyZWF0ZVNlbGVjdG9yUXVlcnkgPSAoY29tcG9uZW50Pzogc3RyaW5nKTogU2VsZWN0b3JRdWVyeSA9PiB7XG4gICAgcmV0dXJuIFNlbGVjdG9yUXVlcnkubmV3RW1wdHlRdWVyeShcbiAgICAgIHtcbiAgICAgICAgbmF0aXZlQXBwOiB0aGlzLmdldE5hdGl2ZUFwcCgpLFxuICAgICAgICBseW54OiB0aGlzLFxuICAgICAgfSxcbiAgICAgIGNvbXBvbmVudFxuICAgICk7XG4gIH07XG5cbiAgcmVxdWVzdEFuaW1hdGlvbkZyYW1lID0gKGNhbGxiYWNrOiAoKSA9PiB2b2lkKSA9PlxuICAgIHRoaXMuZ2V0TmF0aXZlQXBwKCkucmVxdWVzdEFuaW1hdGlvbkZyYW1lKGNhbGxiYWNrKTtcblxuICBjYW5jZWxBbmltYXRpb25GcmFtZSA9IChhbmltYXRpb25JZDogbnVtYmVyKSA9PlxuICAgIHRoaXMuZ2V0TmF0aXZlQXBwKCkuY2FuY2VsQW5pbWF0aW9uRnJhbWUoYW5pbWF0aW9uSWQpO1xuXG4gIHF1ZXVlTWljcm90YXNrKGNhbGxiYWNrOiAoKSA9PiB2b2lkKSB7XG4gICAgdGhpcy5nZXRBcHAoKS5xdWV1ZU1pY3JvdGFzayhjYWxsYmFjayk7XG4gIH1cblxuICBsb2FkU2NyaXB0ID0gPExvYWRTY3JpcHQ+KDxUPihcbiAgICB1cmw6IHN0cmluZyxcbiAgICBvcHRpb25zPzogeyBidW5kbGVOYW1lPzogc3RyaW5nOyB1c2VNb2R1bGVXcmFwcGVyPzogYm9vbGVhbiB9XG4gICk6IFQgPT4ge1xuICAgIGNvbnN0IHsgYnVuZGxlTmFtZSA9IERFRkFVTFRfRU5UUlkgfSA9IG9wdGlvbnM7XG4gICAgY29uc3QgY2FjaGVLZXkgPSBidW5kbGVOYW1lICsgJzonICsgdXJsO1xuICAgIGlmICh0aGlzLmxvYWRTY3JpcHQuY2FjaGVbY2FjaGVLZXldKSB7XG4gICAgICByZXR1cm4gdGhpcy5sb2FkU2NyaXB0LmNhY2hlW2NhY2hlS2V5XSBhcyBUO1xuICAgIH1cbiAgICBjb25zdCBleHBvcnRzID0gdGhpcy5nZXRBcHAoKS5sb2FkU2NyaXB0PFQ+KHVybCwgb3B0aW9ucyk7XG4gICAgdGhpcy5sb2FkU2NyaXB0LmNhY2hlW2NhY2hlS2V5XSA9IGV4cG9ydHM7XG4gICAgcmV0dXJuIGV4cG9ydHM7XG4gIH0pO1xuXG4gIGZldGNoQnVuZGxlID0gdGhpcy5nZXROYXRpdmVMeW54KCkuZmV0Y2hCdW5kbGU7XG5cbiAgX19hZGRSZXBvcnRlckN1c3RvbUluZm8gPSAoaW5mbzogUmVjb3JkPHN0cmluZywgc3RyaW5nPik6IHZvaWQgPT4ge1xuICAgIHRoaXMuZ2V0TmF0aXZlQXBwKCkuX19hZGRSZXBvcnRlckN1c3RvbUluZm8oaW5mbyk7XG4gIH07XG5cbiAgZ2V0TW9kdWxlTG9hZGVyID0gKCk6IEx5bnhNb2R1bGVMb2FkZXIgPT4ge1xuICAgIHJldHVybiBuYXRpdmVHbG9iYWxbJ25hcGlMb2FkZXJPblJUJyArIHRoaXMuZ2V0QXBwKCkubmF0aXZlQXBwSWRdO1xuICB9O1xuXG4gIGNyZWF0ZUFuaW1hdGlvbiA9IChcbiAgICBpZDogc3RyaW5nLFxuICAgIGtleWZyYW1lczogQXJyYXk8UmVjb3JkPHN0cmluZywgYW55Pj4sXG4gICAgb3B0aW9uczogUmVjb3JkPHN0cmluZywgYW55PlxuICApID0+IHtcbiAgICByZXR1cm4gbmV3IEFuaW1hdGlvblYyKGlkLCBrZXlmcmFtZXMsIG9wdGlvbnMpO1xuICB9O1xufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmV4cG9ydCBpbnRlcmZhY2UgVGV4dEluZm8ge1xuICBmb250U2l6ZTogc3RyaW5nO1xuICBmb250RmFtaWx5Pzogc3RyaW5nO1xufVxuXG5leHBvcnQgaW50ZXJmYWNlIFRleHRNZXRyaWNzIHtcbiAgd2lkdGg6IG51bWJlcjtcbn1cblxuZXhwb3J0IGNsYXNzIFRleHRJbmZvTWFuYWdlciB7XG4gIHByaXZhdGUgcmVhZG9ubHkgX25hdGl2ZU1vZHVsZXM6IGFueTtcbiAgcHJpdmF0ZSBfdGV4dEluZm9Nb2R1bGU6IGFueSA9IHVuZGVmaW5lZDtcblxuICBjb25zdHJ1Y3RvcihuYXRpdmVNb2R1bGVzOiBvYmplY3QpIHtcbiAgICB0aGlzLl9uYXRpdmVNb2R1bGVzID0gbmF0aXZlTW9kdWxlcztcbiAgfVxuXG4gIGdldFRleHRJbmZvID0gKHBhcmFtOiBhbnksIG9wdGlvbnM/OiBUZXh0SW5mbyk6IFRleHRNZXRyaWNzID0+IHtcbiAgICBpZiAodGhpcy5fdGV4dEluZm9Nb2R1bGUgPT09IHVuZGVmaW5lZCkge1xuICAgICAgdGhpcy5fdGV4dEluZm9Nb2R1bGUgPSB0aGlzLl9uYXRpdmVNb2R1bGVzLkx5bnhUZXh0SW5mb01vZHVsZTtcbiAgICB9XG4gICAgaWYgKHRoaXMuX3RleHRJbmZvTW9kdWxlICYmIHRoaXMuX3RleHRJbmZvTW9kdWxlLmdldFRleHRJbmZvKSB7XG4gICAgICByZXR1cm4gdGhpcy5fdGV4dEluZm9Nb2R1bGUuZ2V0VGV4dEluZm8ocGFyYW0sIG9wdGlvbnMpO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4ge1xuICAgICAgICB3aWR0aDogcGFyYW0ubGVuZ3RoLFxuICAgICAgfTtcbiAgICB9XG4gIH07XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuZXhwb3J0IGNsYXNzIEV4cG9zdXJlTWFuYWdlciB7XG4gIHByaXZhdGUgcmVhZG9ubHkgX25hdGl2ZU1vZHVsZXM6IGFueTtcbiAgcHJpdmF0ZSByZWFkb25seSBfZXhwb3N1cmVNb2R1bGU6IGFueTtcblxuICBjb25zdHJ1Y3RvcihuYXRpdmVNb2R1bGVzOiBvYmplY3QpIHtcbiAgICB0aGlzLl9uYXRpdmVNb2R1bGVzID0gbmF0aXZlTW9kdWxlcztcbiAgICB0aGlzLl9leHBvc3VyZU1vZHVsZSA9IHRoaXMuX25hdGl2ZU1vZHVsZXMuTHlueEV4cG9zdXJlTW9kdWxlO1xuICB9XG5cbiAgcmVzdW1lRXhwb3N1cmUgPSAoKTogdm9pZCA9PiB7XG4gICAgdGhpcy5fZXhwb3N1cmVNb2R1bGUucmVzdW1lRXhwb3N1cmUoKTtcbiAgfTtcblxuICBzdG9wRXhwb3N1cmUgPSAob3B0aW9ucz86IHsgc2VuZEV2ZW50PzogYm9vbGVhbiB9KTogdm9pZCA9PiB7XG4gICAgdGhpcy5fZXhwb3N1cmVNb2R1bGUuc3RvcEV4cG9zdXJlKG9wdGlvbnMpO1xuICB9O1xuXG4gIHNldE9ic2VydmVyRnJhbWVSYXRlID0gKG9wdGlvbnM/OiB7XG4gICAgZm9yUGFnZVJlY3Q/OiBudW1iZXI7XG4gICAgZm9yRXhwb3N1cmVDaGVjaz86IG51bWJlcjtcbiAgfSk6IHZvaWQgPT4ge1xuICAgIHRoaXMuX2V4cG9zdXJlTW9kdWxlLnNldE9ic2VydmVyRnJhbWVSYXRlKG9wdGlvbnMpO1xuICB9O1xufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IEludGVyc2VjdGlvbk9ic2VydmVyIGFzIElJbnRlcnNlY3Rpb25PYnNlcnZlciB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcblxuZXhwb3J0IGludGVyZmFjZSBJbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZSB7XG4gIGNyZWF0ZUludGVyc2VjdGlvbk9ic2VydmVyOiBGdW5jdGlvbjtcbiAgcmVsYXRpdmVUbzogRnVuY3Rpb247XG4gIHJlbGF0aXZlVG9WaWV3cG9ydDogRnVuY3Rpb247XG4gIHJlbGF0aXZlVG9TY3JlZW46IEZ1bmN0aW9uO1xuICBvYnNlcnZlOiBGdW5jdGlvbjtcbiAgZGlzY29ubmVjdDogRnVuY3Rpb247XG59XG5cbmNsYXNzIEludGVyc2VjdGlvbk9ic2VydmF0aW9uVGFyZ2V0IHtcbiAgcHJpdmF0ZSByZWFkb25seSBfc2VsZWN0b3I6IHN0cmluZztcbiAgcHJpdmF0ZSByZWFkb25seSBfY2FsbGJhY2s6IEZ1bmN0aW9uO1xuXG4gIGNvbnN0cnVjdG9yKHNlbGVjdG9yOiBzdHJpbmcsIGNhbGxiYWNrOiBGdW5jdGlvbikge1xuICAgIHRoaXMuX3NlbGVjdG9yID0gc2VsZWN0b3I7XG4gICAgdGhpcy5fY2FsbGJhY2sgPSBjYWxsYmFjaztcbiAgfVxuXG4gIGludm9rZUNhbGxiYWNrKGRhdGE6IG9iamVjdCk6IHZvaWQge1xuICAgIHRoaXMuX2NhbGxiYWNrKGRhdGEpO1xuICB9XG59XG5cbmV4cG9ydCBjbGFzcyBJbnRlcnNlY3Rpb25PYnNlcnZlciBpbXBsZW1lbnRzIElJbnRlcnNlY3Rpb25PYnNlcnZlciB7XG4gIHByaXZhdGUgcmVhZG9ubHkgX2lkOiBudW1iZXI7XG4gIHByaXZhdGUgcmVhZG9ubHkgX2ludGVyc2VjdGlvbk9ic2VydmVyTW9kdWxlOiBJbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZTtcbiAgcHJpdmF0ZSByZWFkb25seSBfbWFuYWdlcjogSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyO1xuICBwcml2YXRlIHJlYWRvbmx5IF9vYnNlcnZhdGlvblRhcmdldHM6IEludGVyc2VjdGlvbk9ic2VydmF0aW9uVGFyZ2V0W107XG4gIHByaXZhdGUgcmVhZG9ubHkgX2RlZmF1bHRNYXJnaW5zOiBvYmplY3Q7XG5cbiAgY29uc3RydWN0b3IoXG4gICAgaWQ6IG51bWJlcixcbiAgICBpbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZTogSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUsXG4gICAgbWFuYWdlcjogSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyXG4gICkge1xuICAgIHRoaXMuX2lkID0gaWQ7XG4gICAgdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUgPSBpbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZTtcbiAgICB0aGlzLl9tYW5hZ2VyID0gbWFuYWdlcjtcbiAgICB0aGlzLl9vYnNlcnZhdGlvblRhcmdldHMgPSBbXTtcbiAgICB0aGlzLl9kZWZhdWx0TWFyZ2lucyA9IHtcbiAgICAgIGxlZnQ6IDAsXG4gICAgICByaWdodDogMCxcbiAgICAgIHRvcDogMCxcbiAgICAgIGJvdHRvbTogMCxcbiAgICB9O1xuICB9XG5cbiAgcmVsYXRpdmVUbyhzZWxlY3Rvcjogc3RyaW5nLCBtYXJnaW5zPzoge30pOiBJbnRlcnNlY3Rpb25PYnNlcnZlciB7XG4gICAgdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUucmVsYXRpdmVUbyhcbiAgICAgIHRoaXMuX2lkLFxuICAgICAgc2VsZWN0b3IsXG4gICAgICBtYXJnaW5zIHx8IHRoaXMuX2RlZmF1bHRNYXJnaW5zXG4gICAgKTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIHJlbGF0aXZlVG9WaWV3cG9ydChtYXJnaW5zPzoge30pOiBJbnRlcnNlY3Rpb25PYnNlcnZlciB7XG4gICAgdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUucmVsYXRpdmVUb1ZpZXdwb3J0KFxuICAgICAgdGhpcy5faWQsXG4gICAgICBtYXJnaW5zIHx8IHRoaXMuX2RlZmF1bHRNYXJnaW5zXG4gICAgKTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIHJlbGF0aXZlVG9TY3JlZW4obWFyZ2lucz86IHt9KTogSW50ZXJzZWN0aW9uT2JzZXJ2ZXIge1xuICAgIHRoaXMuX2ludGVyc2VjdGlvbk9ic2VydmVyTW9kdWxlLnJlbGF0aXZlVG9TY3JlZW4oXG4gICAgICB0aGlzLl9pZCxcbiAgICAgIG1hcmdpbnMgfHwgdGhpcy5fZGVmYXVsdE1hcmdpbnNcbiAgICApO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgb2JzZXJ2ZShzZWxlY3Rvcjogc3RyaW5nLCBjYWxsYmFjazogRnVuY3Rpb24pOiB2b2lkIHtcbiAgICB0aGlzLl9vYnNlcnZhdGlvblRhcmdldHMucHVzaChcbiAgICAgIG5ldyBJbnRlcnNlY3Rpb25PYnNlcnZhdGlvblRhcmdldChzZWxlY3RvciwgY2FsbGJhY2spXG4gICAgKTtcbiAgICB0aGlzLl9pbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZS5vYnNlcnZlKFxuICAgICAgdGhpcy5faWQsXG4gICAgICBzZWxlY3RvcixcbiAgICAgIHRoaXMuX29ic2VydmF0aW9uVGFyZ2V0cy5sZW5ndGggLSAxXG4gICAgKTtcbiAgfVxuXG4gIGRpc2Nvbm5lY3QoKTogdm9pZCB7XG4gICAgdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUuZGlzY29ubmVjdCh0aGlzLl9pZCk7XG4gICAgdGhpcy5fbWFuYWdlci5yZW1vdmVPYnNlcnZlcih0aGlzLl9pZCk7XG4gIH1cblxuICBpbnZva2VDYWxsYmFjayhjYWxsYmFja0lkOiBudW1iZXIsIGRhdGE6IG9iamVjdCk6IHZvaWQge1xuICAgIGlmIChjYWxsYmFja0lkIDwgdGhpcy5fb2JzZXJ2YXRpb25UYXJnZXRzLmxlbmd0aCkge1xuICAgICAgdGhpcy5fb2JzZXJ2YXRpb25UYXJnZXRzW2NhbGxiYWNrSWRdLmludm9rZUNhbGxiYWNrKGRhdGEpO1xuICAgIH1cbiAgfVxufVxuXG5leHBvcnQgY2xhc3MgSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyIHtcbiAgcHJpdmF0ZSByZWFkb25seSBfbmF0aXZlTW9kdWxlczogb2JqZWN0O1xuICBwcml2YXRlIF9vYnNlcnZlcklkOiBudW1iZXI7XG4gIHByaXZhdGUgX29ic2VydmVyczogb2JqZWN0O1xuICBwcml2YXRlIHJlYWRvbmx5IF9kZWZhdWx0T3B0aW9uczogb2JqZWN0O1xuXG4gIGNvbnN0cnVjdG9yKG5hdGl2ZU1vZHVsZXM6IG9iamVjdCkge1xuICAgIHRoaXMuX25hdGl2ZU1vZHVsZXMgPSBuYXRpdmVNb2R1bGVzO1xuICAgIHRoaXMuX29ic2VydmVySWQgPSAwO1xuICAgIHRoaXMuX29ic2VydmVycyA9IHt9O1xuICAgIHRoaXMuX2RlZmF1bHRPcHRpb25zID0ge1xuICAgICAgdGhyZXNob2xkczogWzBdLFxuICAgICAgaW5pdGlhbFJhdGlvOiAwLFxuICAgICAgb2JzZXJ2ZUFsbDogZmFsc2UsXG4gICAgfTtcbiAgfVxuXG4gIGNyZWF0ZUludGVyc2VjdGlvbk9ic2VydmVyKFxuICAgIGNvbXBvbmVudElkOiBzdHJpbmcsXG4gICAgb3B0aW9ucz86IG9iamVjdFxuICApOiBJbnRlcnNlY3Rpb25PYnNlcnZlciB7XG4gICAgbGV0IGludGVyc2VjdGlvbk9ic2VydmVyTW9kdWxlID0gdGhpcy5fbmF0aXZlTW9kdWxlc1tcbiAgICAgICdJbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZSdcbiAgICBdO1xuICAgIGNvbnN0IG9ic2VydmVyID0gbmV3IEludGVyc2VjdGlvbk9ic2VydmVyKFxuICAgICAgdGhpcy5fb2JzZXJ2ZXJJZCxcbiAgICAgIGludGVyc2VjdGlvbk9ic2VydmVyTW9kdWxlLFxuICAgICAgdGhpc1xuICAgICk7XG4gICAgdGhpcy5fb2JzZXJ2ZXJzW3RoaXMuX29ic2VydmVySWRdID0gb2JzZXJ2ZXI7XG4gICAgaW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUuY3JlYXRlSW50ZXJzZWN0aW9uT2JzZXJ2ZXIoXG4gICAgICB0aGlzLl9vYnNlcnZlcklkLFxuICAgICAgY29tcG9uZW50SWQsXG4gICAgICBvcHRpb25zIHx8IHRoaXMuX2RlZmF1bHRPcHRpb25zXG4gICAgKTtcbiAgICB0aGlzLl9vYnNlcnZlcklkKys7XG4gICAgcmV0dXJuIG9ic2VydmVyO1xuICB9XG5cbiAgZ2V0T2JzZXJ2ZXIob2JzZXJ2ZXJJZDogbnVtYmVyKTogSW50ZXJzZWN0aW9uT2JzZXJ2ZXIge1xuICAgIHJldHVybiB0aGlzLl9vYnNlcnZlcnNbb2JzZXJ2ZXJJZF07XG4gIH1cblxuICByZW1vdmVPYnNlcnZlcihvYnNlcnZlcklkOiBudW1iZXIpOiB2b2lkIHtcbiAgICB0aGlzLl9vYnNlcnZlcnNbb2JzZXJ2ZXJJZF0gPSBudWxsO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IEV2ZW50RW1pdHRlciBmcm9tICcuLi9ldmVudCc7XG5pbXBvcnQge1xuICBQZXJmb3JtYW5jZU9ic2VydmVyIGFzIElQZXJmb3JtYW5jZU9ic2VydmVyLFxuICBQZXJmb3JtYW5jZUNhbGxiYWNrLFxuICBQZXJmb3JtYW5jZUVudHJ5LFxufSBmcm9tICdAbHlueC1qcy90eXBlcyc7XG5cbmNvbnN0IExpc3RlbmVyS2V5cyA9IHtcbiAgb25QZXJmb3JtYW5jZTogJ2x5bngucGVyZm9ybWFuY2Uub25QZXJmb3JtYW5jZUV2ZW50Jyxcbn07XG5cbmV4cG9ydCBjbGFzcyBQZXJmb3JtYW5jZU9ic2VydmVyIGltcGxlbWVudHMgSVBlcmZvcm1hbmNlT2JzZXJ2ZXIge1xuICBfZW1pdHRlcjogRXZlbnRFbWl0dGVyO1xuICBfb2JzZXJ2ZWROYW1lczogc3RyaW5nW107XG4gIF9vblBlcmZvcm1hbmNlOiBQZXJmb3JtYW5jZUNhbGxiYWNrO1xuICBjb25zdHJ1Y3RvcihlbWl0dGVyOiBFdmVudEVtaXR0ZXIsIGNhbGxiYWNrOiBQZXJmb3JtYW5jZUNhbGxiYWNrKSB7XG4gICAgdGhpcy5fZW1pdHRlciA9IGVtaXR0ZXI7XG4gICAgdGhpcy5fb25QZXJmb3JtYW5jZSA9IGNhbGxiYWNrO1xuICAgIHRoaXMuX29ic2VydmVkTmFtZXMgPSBbXTtcbiAgfVxuXG4gIG9ic2VydmUobmFtZXM6IHN0cmluZ1tdKTogdm9pZCB7XG4gICAgLy8gVGhlIHByZXZpb3VzIG9ic2VydmUgbXVzdCBiZSBjbG9zZWQgdXNpbmcgdGhlIGRpc2Nvbm5lY3QgbWV0aG9kIGJlZm9yZSByZS1vYnNlcnZpbmcuXG4gICAgaWYgKHRoaXMuX29ic2VydmVkTmFtZXMubGVuZ3RoID4gMCkge1xuICAgICAgcmV0dXJuO1xuICAgIH1cblxuICAgIHRoaXMuX29ic2VydmVkTmFtZXMgPSBuYW1lcztcbiAgICB0aGlzLl9lbWl0dGVyLmFkZExpc3RlbmVyKFxuICAgICAgTGlzdGVuZXJLZXlzLm9uUGVyZm9ybWFuY2UsXG4gICAgICB0aGlzLm9uUGVyZm9ybWFuY2VFdmVudC5iaW5kKHRoaXMpXG4gICAgKTtcbiAgfVxuXG4gIGRpc2Nvbm5lY3QoKTogdm9pZCB7XG4gICAgdGhpcy5fb2JzZXJ2ZWROYW1lcyA9IFtdO1xuICAgIHRoaXMuX2VtaXR0ZXIucmVtb3ZlTGlzdGVuZXIoXG4gICAgICBMaXN0ZW5lcktleXMub25QZXJmb3JtYW5jZSxcbiAgICAgIHRoaXMub25QZXJmb3JtYW5jZUV2ZW50LmJpbmQodGhpcylcbiAgICApO1xuICB9XG5cbiAgb25QZXJmb3JtYW5jZUV2ZW50KGVudHJ5OiBQZXJmb3JtYW5jZUVudHJ5KTogdm9pZCB7XG4gICAgaWYgKHRoaXMuX29ic2VydmVkTmFtZXMubGVuZ3RoID09PSAwKSB7XG4gICAgICByZXR1cm47XG4gICAgfVxuXG4gICAgbGV0IGVudHJ5TmFtZSA9IGVudHJ5LmVudHJ5VHlwZSArICcuJyArIGVudHJ5Lm5hbWU7XG4gICAgaWYgKFxuICAgICAgdGhpcy5fb2JzZXJ2ZWROYW1lcy5pbmNsdWRlcyhlbnRyeU5hbWUpIHx8XG4gICAgICB0aGlzLl9vYnNlcnZlZE5hbWVzLmluY2x1ZGVzKGVudHJ5LmVudHJ5VHlwZSlcbiAgICApIHtcbiAgICAgIHRoaXMuX29uUGVyZm9ybWFuY2UoZW50cnkpO1xuICAgIH1cbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCBFdmVudEVtaXR0ZXIgZnJvbSAnLi4vZXZlbnQnO1xuaW1wb3J0IHtcbiAgUGVyZm9ybWFuY2UgYXMgSVBlcmZvcm1hbmNlLFxuICBUaW1pbmdMaXN0ZW5lcixcbiAgUGVyZm9ybWFuY2VDYWxsYmFjayxcbn0gZnJvbSAnQGx5bngtanMvdHlwZXMnO1xuaW1wb3J0IHsgTmF0aXZlQXBwIH0gZnJvbSAnLi4vLi4vYXBwJztcbmltcG9ydCB7IFRyYWNlT3B0aW9uIH0gZnJvbSAnQGx5bngtanMvdHlwZXMvdHlwZXMvY29tbW9uL3BlcmZvcm1hbmNlJztcbmltcG9ydCB7IFBlcmZvcm1hbmNlT2JzZXJ2ZXIgfSBmcm9tICcuL3BlcmZvcm1hbmNlT2JzZXJ2ZXInO1xuXG5jb25zdCBMaXN0ZW5lcktleXMgPSB7XG4gIG9uU2V0dXA6ICdseW54LnBlcmZvcm1hbmNlLnRpbWluZy5vblNldHVwJyxcbiAgb25VcGRhdGU6ICdseW54LnBlcmZvcm1hbmNlLnRpbWluZy5vblVwZGF0ZScsXG59O1xuXG5leHBvcnQgaW50ZXJmYWNlIFBpcGVsaW5lT3B0aW9ucyB7XG4gIHBpcGVsaW5lSUQ6IHN0cmluZztcbiAgcGlwZWxpbmVPcmlnaW46IHN0cmluZzsgLy8gVGhlIG9yaWdpbiBvZiB0aGUgcGlwZWxpbmVcbiAgbmVlZFRpbWVzdGFtcHM6IGJvb2xlYW47XG4gIGRzbDogc3RyaW5nO1xuICBzdGFnZTogc3RyaW5nO1xufVxuXG5leHBvcnQgZGVmYXVsdCBjbGFzcyBQZXJmb3JtYW5jZSBpbXBsZW1lbnRzIElQZXJmb3JtYW5jZSB7XG4gIF9lbWl0dGVyOiBFdmVudEVtaXR0ZXI7XG4gIF9nZW5lcmF0ZVBpcGVsaW5lT3B0aW9uczogKCkgPT4gUGlwZWxpbmVPcHRpb25zO1xuICBfb25QaXBlbGluZVN0YXJ0OiAoXG4gICAgcGlwZWxpbmVfaWQ6IHN0cmluZyxcbiAgICBwaXBlbGluZV9vcHRpb25zPzogUGlwZWxpbmVPcHRpb25zXG4gICkgPT4gdm9pZDtcbiAgX21hcmtUaW1pbmc6IChwaXBlbGluZV9pZDogc3RyaW5nLCB0aW1pbmdfa2V5OiBzdHJpbmcpID0+IHZvaWQ7XG4gIF9wcm9maWxlU3RhcnQ6ICh0cmFjZU5hbWU6IHN0cmluZywgb3B0aW9uPzogVHJhY2VPcHRpb24pID0+IHZvaWQ7XG4gIF9wcm9maWxlRW5kOiAob3B0aW9uPzogVHJhY2VPcHRpb24pID0+IHZvaWQ7XG4gIF9wcm9maWxlTWFyazogKHRyYWNlTmFtZTogc3RyaW5nLCBvcHRpb24/OiBUcmFjZU9wdGlvbikgPT4gdm9pZDtcbiAgX3Byb2ZpbGVGbG93SWQ6ICgpID0+IG51bWJlcjtcbiAgX2lzUHJvZmlsZVJlY29yZGluZzogKCkgPT4gYm9vbGVhbjtcbiAgX2JpbmRQaXBlbGluZUlkV2l0aFRpbWluZ0ZsYWc6IChcbiAgICBwaXBlbGluZV9pZDogc3RyaW5nLFxuICAgIHRpbWluZ19mbGFnOiBzdHJpbmdcbiAgKSA9PiB2b2lkO1xuICBjb25zdHJ1Y3RvcihlbWl0dGVyOiBFdmVudEVtaXR0ZXIsIG5hdGl2ZUFwcDogTmF0aXZlQXBwKSB7XG4gICAgdGhpcy5fZW1pdHRlciA9IGVtaXR0ZXI7XG4gICAgdGhpcy5fZ2VuZXJhdGVQaXBlbGluZU9wdGlvbnMgPSBuYXRpdmVBcHAuZ2VuZXJhdGVQaXBlbGluZU9wdGlvbnM7XG4gICAgdGhpcy5fb25QaXBlbGluZVN0YXJ0ID0gbmF0aXZlQXBwLm9uUGlwZWxpbmVTdGFydDtcbiAgICB0aGlzLl9tYXJrVGltaW5nID0gbmF0aXZlQXBwLm1hcmtQaXBlbGluZVRpbWluZztcbiAgICB0aGlzLl9wcm9maWxlU3RhcnQgPSBuYXRpdmVBcHAucHJvZmlsZVN0YXJ0O1xuICAgIHRoaXMuX3Byb2ZpbGVFbmQgPSBuYXRpdmVBcHAucHJvZmlsZUVuZDtcbiAgICB0aGlzLl9wcm9maWxlTWFyayA9IG5hdGl2ZUFwcC5wcm9maWxlTWFyaztcbiAgICB0aGlzLl9wcm9maWxlRmxvd0lkID0gbmF0aXZlQXBwLnByb2ZpbGVGbG93SWQ7XG4gICAgdGhpcy5faXNQcm9maWxlUmVjb3JkaW5nID0gbmF0aXZlQXBwLmlzUHJvZmlsZVJlY29yZGluZztcbiAgICB0aGlzLl9iaW5kUGlwZWxpbmVJZFdpdGhUaW1pbmdGbGFnID0gbmF0aXZlQXBwLmJpbmRQaXBlbGluZUlkV2l0aFRpbWluZ0ZsYWc7XG4gIH1cblxuICBwcm9maWxlU3RhcnQodHJhY2VOYW1lOiBzdHJpbmcsIG9wdGlvbj86IFRyYWNlT3B0aW9uKSB7XG4gICAgdGhpcy5fcHJvZmlsZVN0YXJ0KHRyYWNlTmFtZSwgb3B0aW9uKTtcbiAgfVxuXG4gIHByb2ZpbGVFbmQoKSB7XG4gICAgdGhpcy5fcHJvZmlsZUVuZCgpO1xuICB9XG5cbiAgcHJvZmlsZU1hcmsodHJhY2VOYW1lOiBzdHJpbmcsIG9wdGlvbj86IFRyYWNlT3B0aW9uKSB7XG4gICAgdGhpcy5fcHJvZmlsZU1hcmsodHJhY2VOYW1lLCBvcHRpb24pO1xuICB9XG5cbiAgcHJvZmlsZUZsb3dJZCgpIHtcbiAgICByZXR1cm4gdGhpcy5fcHJvZmlsZUZsb3dJZCgpO1xuICB9XG5cbiAgY3JlYXRlT2JzZXJ2ZXIoY2FsbGJhY2s6IFBlcmZvcm1hbmNlQ2FsbGJhY2spOiBQZXJmb3JtYW5jZU9ic2VydmVyIHtcbiAgICByZXR1cm4gbmV3IFBlcmZvcm1hbmNlT2JzZXJ2ZXIodGhpcy5fZW1pdHRlciwgY2FsbGJhY2spO1xuICB9XG5cbiAgaXNQcm9maWxlUmVjb3JkaW5nKCkge1xuICAgIHJldHVybiB0aGlzLl9pc1Byb2ZpbGVSZWNvcmRpbmcoKTtcbiAgfVxuXG4gIGFkZFRpbWluZ0xpc3RlbmVyKGxpc3RlbmVyOiBUaW1pbmdMaXN0ZW5lcik6IHZvaWQge1xuICAgIHRoaXMuX2VtaXR0ZXIuYWRkTGlzdGVuZXIoTGlzdGVuZXJLZXlzLm9uU2V0dXAsIGxpc3RlbmVyLm9uU2V0dXAsIGxpc3RlbmVyKTtcbiAgICB0aGlzLl9lbWl0dGVyLmFkZExpc3RlbmVyKFxuICAgICAgTGlzdGVuZXJLZXlzLm9uVXBkYXRlLFxuICAgICAgbGlzdGVuZXIub25VcGRhdGUsXG4gICAgICBsaXN0ZW5lclxuICAgICk7XG4gIH1cblxuICByZW1vdmVUaW1pbmdMaXN0ZW5lcihsaXN0ZW5lcjogVGltaW5nTGlzdGVuZXIpIHtcbiAgICB0aGlzLl9lbWl0dGVyLnJlbW92ZUxpc3RlbmVyKExpc3RlbmVyS2V5cy5vblNldHVwLCBsaXN0ZW5lci5vblNldHVwKTtcbiAgICB0aGlzLl9lbWl0dGVyLnJlbW92ZUxpc3RlbmVyKExpc3RlbmVyS2V5cy5vblVwZGF0ZSwgbGlzdGVuZXIub25VcGRhdGUpO1xuICB9XG5cbiAgcmVtb3ZlQWxsVGltaW5nTGlzdGVuZXIoKSB7XG4gICAgdGhpcy5fZW1pdHRlci5yZW1vdmVBbGxMaXN0ZW5lcnMoTGlzdGVuZXJLZXlzLm9uU2V0dXApO1xuICAgIHRoaXMuX2VtaXR0ZXIucmVtb3ZlQWxsTGlzdGVuZXJzKExpc3RlbmVyS2V5cy5vblVwZGF0ZSk7XG4gIH1cbiAgX2luaXRpYWxpemVBbmRTdGFydFBpcGVsaW5lKCk6IFBpcGVsaW5lT3B0aW9ucyB7XG4gICAgY29uc3QgcGlwZWxpbmVPcHRpb25zID0gdGhpcy5fZ2VuZXJhdGVQaXBlbGluZU9wdGlvbnMoKTtcbiAgICBpZiAocGlwZWxpbmVPcHRpb25zKSB7XG4gICAgICB0aGlzLl9vblBpcGVsaW5lU3RhcnQocGlwZWxpbmVPcHRpb25zLnBpcGVsaW5lSUQpO1xuICAgIH1cbiAgICByZXR1cm4gcGlwZWxpbmVPcHRpb25zO1xuICB9XG4gIF9jaGVja0FuZEJpbmRUaW1pbmdGbGFnKFxuICAgIHBpcGVsaW5lT3B0aW9uczogUGlwZWxpbmVPcHRpb25zLFxuICAgIGRhdGE6IFJlY29yZDxzdHJpbmcsIHVua25vd24+XG4gICkge1xuICAgIGlmICghcGlwZWxpbmVPcHRpb25zKSB7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIGNvbnN0IFBlcmZvcm1hbmNlVGltaW5nRmxhZyA9ICdfX2x5bnhfdGltaW5nX2ZsYWcnO1xuICAgIGlmIChkYXRhW1BlcmZvcm1hbmNlVGltaW5nRmxhZ10pIHtcbiAgICAgIHRoaXMuX2JpbmRQaXBlbGluZUlkV2l0aFRpbWluZ0ZsYWcoXG4gICAgICAgIHBpcGVsaW5lT3B0aW9ucy5waXBlbGluZUlELFxuICAgICAgICBkYXRhW1BlcmZvcm1hbmNlVGltaW5nRmxhZ10gYXMgc3RyaW5nXG4gICAgICApO1xuICAgICAgdGhpcy5fbWFya1RpbWluZyhwaXBlbGluZU9wdGlvbnMucGlwZWxpbmVJRCwgJ3VwZGF0ZV9zZXRfc3RhdGVfdHJpZ2dlcicpO1xuICAgICAgcGlwZWxpbmVPcHRpb25zLm5lZWRUaW1lc3RhbXBzID0gdHJ1ZTtcbiAgICB9XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgUGVyZm9ybWFuY2UgZnJvbSAnLi9wZXJmb3JtYW5jZSc7XG5leHBvcnQgZGVmYXVsdCBQZXJmb3JtYW5jZTtcbmV4cG9ydCAqIGZyb20gJy4vcGVyZm9ybWFuY2UnO1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCBuYXRpdmVHbG9iYWwgZnJvbSAnLi9uYXRpdmVHbG9iYWwnO1xuZXhwb3J0IGRlZmF1bHQgbmF0aXZlR2xvYmFsLkx5bnhKU0JJO1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbi8vIENhY2hlIGFjY2VzcyB0byBmdW5jdGlvbnMgb2YgdGhlIHRhcmdldCBvYmplY3QuXG4vL1xuLy8gV2hlbiBhIGZ1bmN0aW9uIG9uIHRhcmdldCBvYmogaXMgYWNjZXNzZWQgZm9yIHRoZSBmaXJzdCB0aW1lLFxuLy8gdGhlIHByb3h5IG9idGFpbnMgdGhlIGZ1bmN0aW9uIG9iamVjdCBhbmQgc2F2ZXMgaXQsXG4vLyBhbmQgcmV0dXJucyB0aGUgY2FjaGVkIGZ1bmN0aW9uIG9iamVjdCBkaXJlY3RseSBkdXJpbmcgc3Vic2VxdWVudCBhY2Nlc3Ncbi8vIHdpdGhvdXQgYWNjZXNzaW5nIGFnYWluLlxuZXhwb3J0IGNsYXNzIENhY2hlZEZ1bmN0aW9uUHJveHk8VD4ge1xuICBwcml2YXRlIF9jYWNoZWRGdW5jdGlvbnM6IFJlY29yZDxzdHJpbmcsIEZ1bmN0aW9uPiA9IHt9O1xuXG4gIHN0YXRpYyBjcmVhdGU8VD4ob2JqOiBUKTogVCB7XG4gICAgcmV0dXJuIG5ldyBDYWNoZWRGdW5jdGlvblByb3h5KG9iaikgYXMgYW55O1xuICB9XG5cbiAgY29uc3RydWN0b3Iob2JqOiBUKSB7XG4gICAgZm9yIChjb25zdCBrZXkgaW4gb2JqKSB7XG4gICAgICBPYmplY3QuZGVmaW5lUHJvcGVydHkodGhpcywga2V5LCB7XG4gICAgICAgIGdldCgpIHtcbiAgICAgICAgICBpZiAodGhpcy5fY2FjaGVkRnVuY3Rpb25zW2tleV0pIHtcbiAgICAgICAgICAgIHJldHVybiB0aGlzLl9jYWNoZWRGdW5jdGlvbnNba2V5XTtcbiAgICAgICAgICB9XG4gICAgICAgICAgY29uc3QgdmFsdWUgPSBvYmpba2V5XTtcbiAgICAgICAgICBpZiAodHlwZW9mIHZhbHVlID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgICAgICB0aGlzLl9jYWNoZWRGdW5jdGlvbnNba2V5XSA9IHZhbHVlO1xuICAgICAgICAgIH1cbiAgICAgICAgICByZXR1cm4gdmFsdWU7XG4gICAgICAgIH0sXG4gICAgICB9KTtcbiAgICB9XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBMeW54Q2xlYXJUaW1lb3V0LCBMeW54U2V0VGltZW91dCB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCBuYXRpdmVHbG9iYWwgZnJvbSAnLi4vY29tbW9uL25hdGl2ZUdsb2JhbCc7XG5cbnR5cGUgbmV4dFRpY2sgPSAoY2FsbGJhY2s6ICgpID0+IHZvaWQpID0+IHZvaWQ7XG5leHBvcnQgZnVuY3Rpb24gZ2V0UHJvbWlzZU1heWJlUG9seWZpbGwoXG4gIHNldFRpbWVvdXQ6IEx5bnhTZXRUaW1lb3V0LFxuICBvblVuaGFuZGxlZCxcbiAgY2xlYXJUaW1lb3V0OiBMeW54Q2xlYXJUaW1lb3V0LFxuICBxdWV1ZU1pY3JvdGFzazogbmV4dFRpY2sgPSB1bmRlZmluZWQsXG4gIGVuYWJsZU1pY3JvdGFza1Byb21pc2VQb2x5ZmlsbDogYm9vbGVhbiA9IGZhbHNlXG4pIHtcbiAgY29uc3QgeyBnZXRQcm9taXNlIH0gPSBuYXRpdmVHbG9iYWw7XG4gIGlmICh0eXBlb2YgZ2V0UHJvbWlzZSA9PT0gJ2Z1bmN0aW9uJykge1xuICAgIGNvbnN0IG5leHRUaWNrID0gZW5hYmxlTWljcm90YXNrUHJvbWlzZVBvbHlmaWxsXG4gICAgICA/IHF1ZXVlTWljcm90YXNrXG4gICAgICA6IChmbjogKCkgPT4gdm9pZCkgPT4gc2V0VGltZW91dChmbiwgMCk7XG4gICAgcmV0dXJuIGdldFByb21pc2UoeyBuZXh0VGljaywgc2V0VGltZW91dCwgb25VbmhhbmRsZWQsIGNsZWFyVGltZW91dCB9KTtcbiAgfSBlbHNlIHtcbiAgICAvLyBUT0RPOiBzaG91bGQgcmVwb3J0IGVycm9yO1xuICAgIHJldHVybiBuYXRpdmVHbG9iYWwuUHJvbWlzZTtcbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI1IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmV4cG9ydCBjbGFzcyBUcmFjZUV2ZW50RGVmIHtcbiAgc3RhdGljIHJlYWRvbmx5IEVYRUNVVEVfTE9BREVEX1NDUklQVCA9ICdleGVjdXRlTG9hZGVkU2NyaXB0Jztcbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQge1xuICBBcHBQcm94eVBhcmFtcyxcbiAgQnVuZGxlSW5pdFJldHVybk9iaixcbiAgRW52S2V5LFxuICBMaWZlRXZlbnQsXG4gIGxvYWRDYXJkUGFyYW1zLFxuICBMeW54U2V0VGltZW91dDIsXG4gIE5hdGl2ZUFwcCxcbiAgcmVxdWlyZVBhcmFtT2JqLFxufSBmcm9tICcuL2ludGVyZmFjZSc7XG5pbXBvcnQgeyBBTURGYWN0b3J5LCBBTURNb2R1bGUgfSBmcm9tICcuLi9jb21tb24nO1xuaW1wb3J0IHsgY3JlYXRlU2hhcmVkQ29uc29sZSwgU2hhcmVkQ29uc29sZSB9IGZyb20gJ0BseW54LWpzL3J1bnRpbWUtc2hhcmVkJztcbmltcG9ydCB7XG4gIFJlcG9ydGVyLFxuICBCYXNlRXJyb3IsXG4gIEludGVybmFsUnVudGltZUVycm9yLFxuICBMeW54RXJyb3JMZXZlbCxcbiAgVXNlclJ1bnRpbWVFcnJvcixcbn0gZnJvbSAnLi4vbW9kdWxlcy9yZXBvcnQnO1xuaW1wb3J0IHsgQ29udGV4dFByb3h5VHlwZSwgTHlueCwgTmF0aXZlTHlueFByb3h5IH0gZnJvbSAnLi4vbHlueCc7XG5pbXBvcnQgRXZlbnRFbWl0dGVyLCB7IEFvcE1hbmFnZXIsIEJlZm9yZVB1Ymxpc2hFdmVudCB9IGZyb20gJy4uL21vZHVsZXMvZXZlbnQnO1xuaW1wb3J0IHtcbiAgRXhwb3N1cmVNYW5hZ2VyLFxuICBJbnRlcnNlY3Rpb25PYnNlcnZlck1hbmFnZXIsXG4gIE5hdGl2ZUx5bnhVSU1vZHVsZSxcbiAgTmF0aXZlTW9kdWxlLFxuICBUZXh0SW5mbyxcbiAgVGV4dEluZm9NYW5hZ2VyLFxuICBUZXh0TWV0cmljcyxcbn0gZnJvbSAnLi4vbW9kdWxlcy9uYXRpdmVNb2R1bGVzJztcbmltcG9ydCB7IERFRkFVTFRfRU5UUlksIFNPVVJDRV9NQVBfUkVMRUFTRV9FUlJPUl9OQU1FIH0gZnJvbSAnLi4vY29tbW9uJztcbmltcG9ydCBuYXRpdmVHbG9iYWwgZnJvbSAnLi4vY29tbW9uL25hdGl2ZUdsb2JhbCc7XG5pbXBvcnQge1xuICBDcmVhdGVJbnRlcnNlY3Rpb25PYnNlcnZlckZ1bmMsXG4gIEx5bnhDbGVhclRpbWVvdXQsXG4gIEx5bnhTZXRUaW1lb3V0LFxuICBNZXNzYWdlRXZlbnQsXG59IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCBQZXJmb3JtYW5jZSBmcm9tICcuLi9tb2R1bGVzL3BlcmZvcm1hbmNlJztcbmltcG9ydCB7IHJlcG9ydEVycm9yIH0gZnJvbSAnLi4vbW9kdWxlcy9yZXBvcnQnO1xuaW1wb3J0IEx5bnhKU0JJIGZyb20gJy4uL2NvbW1vbi9qc2JpJztcbmltcG9ydCB7IEJhc2VBcHBTaW5nbGV0b25EYXRhIH0gZnJvbSAnLi4vc3RhbmRhbG9uZS9TdGFuZGFsb25lQXBwJztcbmltcG9ydCB7IENhY2hlZEZ1bmN0aW9uUHJveHkgfSBmcm9tICcuLi91dGlsL2NhY2hlZEZ1bmN0aW9uUHJveHknO1xuaW1wb3J0IHsgZ2V0UHJvbWlzZU1heWJlUG9seWZpbGwgfSBmcm9tICcuLi91dGlsL3NldHVwLXByb21pc2UnO1xuaW1wb3J0IHsgY3JlYXRlUmVhZGFibGVTdHJlYW1DbGFzcywgUmVxdWVzdCwgUmVzcG9uc2UgfSBmcm9tICcuLi9tb2R1bGVzL2ZldGNoJztcbmltcG9ydCB7IE1lc3NhZ2VFdmVudFR5cGUgfSBmcm9tICcuLi9seW54JztcbmltcG9ydCB7IFRyYWNlRXZlbnREZWYgfSBmcm9tICcuLi91dGlsL1RyYWNlRXZlbnREZWYnO1xuaW1wb3J0IHsgQ2FsbGJhY2tNYW5hZ2VyIH0gZnJvbSAnLi4vY29tbW9uL2NhbGxiYWNrTWFuYWdlcic7XG5cbmV4cG9ydCBhYnN0cmFjdCBjbGFzcyBCYXNlQXBwPFxuICBOYXRpdmVBcHBQcm94eSBleHRlbmRzIE5hdGl2ZUFwcCA9IE5hdGl2ZUFwcCxcbiAgTHlueEltcGwgZXh0ZW5kcyBMeW54ID0gTHlueFxuPiB7XG4gIF9uYXRpdmVBcHA6IE5hdGl2ZUFwcFByb3h5O1xuICBuYXRpdmVBcHBJZDogc3RyaW5nO1xuICBfcGFyYW1zOiBsb2FkQ2FyZFBhcmFtcztcbiAgbHlueDogTHlueEltcGw7XG4gIG1vZHVsZXM6IFJlY29yZDxzdHJpbmcsIFJlY29yZDxzdHJpbmcsIEFNRE1vZHVsZT4+O1xuICBzaGFyZWRDb25zb2xlOiBTaGFyZWRDb25zb2xlO1xuICBkeW5hbWljQ29tcG9uZW50RXhwb3J0czogb2JqZWN0O1xuICBsb2FkZWREeW5hbWljQ29tcG9uZW50c1NldDogU2V0PHN0cmluZz47XG4gIHJlc29sdmVkUHJvbWlzZTogUHJvbWlzZTx2b2lkPjtcblxuICBSZXBvcnRlcjogUmVwb3J0ZXI7XG4gIF9sYXp5Q2FsbGFibGVNb2R1bGVzOiBNYXA8c3RyaW5nLCB1bmtub3duPjtcbiAgR2xvYmFsRXZlbnRFbWl0dGVyOiBFdmVudEVtaXR0ZXI7XG4gIE5hdGl2ZU1vZHVsZXM6IE5hdGl2ZU1vZHVsZTtcbiAgTHlueFVJTWV0aG9kTW9kdWxlOiBOYXRpdmVMeW54VUlNb2R1bGU7XG4gIEx5bnhUZXN0TW9kdWxlOiBvYmplY3Q7XG4gIEx5bnhSZXNvdXJjZU1vZHVsZTogb2JqZWN0O1xuICBMeW54QWNjZXNzaWJpbGl0eU1vZHVsZTogb2JqZWN0O1xuICBMeW54U2V0TW9kdWxlOiBvYmplY3Q7XG5cbiAgX2FwaUxpc3Q6IFJlY29yZDxzdHJpbmcsIHVua25vd24+O1xuICBfaW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyOiBJbnRlcnNlY3Rpb25PYnNlcnZlck1hbmFnZXI7XG4gIF9leHBvc3VyZU1hbmFnZXI6IEV4cG9zdXJlTWFuYWdlcjtcbiAgX3RleHRJbmZvTWFuYWdlcjogVGV4dEluZm9NYW5hZ2VyO1xuICBfYW9wTWFuYWdlcjogQW9wTWFuYWdlcjtcbiAgYmVmb3JlUHVibGlzaEV2ZW50OiBCZWZvcmVQdWJsaXNoRXZlbnQ7XG5cbiAgcGVyZm9ybWFuY2U6IFBlcmZvcm1hbmNlO1xuXG4gIHNldFRpbWVvdXQ6IEx5bnhTZXRUaW1lb3V0O1xuICBzZXRJbnRlcnZhbDogTHlueFNldFRpbWVvdXQ7XG4gIGNsZWFySW50ZXJ2YWw6IEx5bnhDbGVhclRpbWVvdXQ7XG4gIGNsZWFyVGltZW91dDogTHlueENsZWFyVGltZW91dDtcblxuICBfY3JlYXRlUmVhZGFibGVTdHJlYW1DbGFzczogKFxuICAgIFByb21pc2U6IFByb21pc2VDb25zdHJ1Y3RvclxuICApID0+IFJldHVyblR5cGU8dHlwZW9mIGNyZWF0ZVJlYWRhYmxlU3RyZWFtQ2xhc3M+O1xuICBfUmVhZGFibGVTdHJlYW1DbGFzczogUmV0dXJuVHlwZTx0eXBlb2YgY3JlYXRlUmVhZGFibGVTdHJlYW1DbGFzcz47XG5cbiAgZGF0YVR5cGVTZXQgPSBuZXcgU2V0KFtcbiAgICAnc3RyaW5nJyxcbiAgICAnbnVtYmVyJyxcbiAgICAnYXJyYXknLFxuICAgICdvYmplY3QnLFxuICAgICdib29sZWFuJyxcbiAgICAnbnVsbCcsXG4gICAgJ2Z1bmN0aW9uJyxcbiAgXSk7XG5cbiAgLyoqXG4gICAqIEludGVybmFsIEV2ZW50IExpc3RlbmVyXG4gICAqIEBwcml2YXRlXG4gICAqL1xuICBwcml2YXRlIGNvbnRleHRQcm94eVR5cGVUb01ldGhvZDoge307XG4gIHByaXZhdGUgcmVtb3ZlSW50ZXJuYWxFdmVudExpc3RlbmVyc0NhbGxiYWNrczogKCgpID0+IHZvaWQpW10gPSBbXTtcblxuICBfY2FsbGJhY2tNYW5hZ2VyOiBDYWxsYmFja01hbmFnZXI7XG5cbiAgY29uc3RydWN0b3IoXG4gICAgb3B0aW9uczogQXBwUHJveHlQYXJhbXM8TmF0aXZlQXBwUHJveHk+LFxuICAgIGJhc2VBcHBTaW5nbGVEYXRhPzogQmFzZUFwcFNpbmdsZXRvbkRhdGE8TmF0aXZlQXBwUHJveHksIEx5bnhJbXBsPlxuICApIHtcbiAgICB0aGlzLmluaXRCYXNlKG9wdGlvbnMpO1xuICAgIGlmIChiYXNlQXBwU2luZ2xlRGF0YSkge1xuICAgICAgYmFzZUFwcFNpbmdsZURhdGEudHJhbnNmZXJTaW5nbGV0b25EYXRhKFxuICAgICAgICB0aGlzLFxuICAgICAgICB0aGlzLl9faW50ZXJuYWxfX2NhbGxMeW54U2V0TW9kdWxlLmJpbmQodGhpcylcbiAgICAgICk7XG4gICAgfSBlbHNlIHtcbiAgICAgIHRoaXMuaW5pdEV4dHJhKG9wdGlvbnMpO1xuICAgIH1cblxuICAgIHRoaXMuYWRkSW50ZXJuYWxFdmVudExpc3RlbmVycygpO1xuXG4gICAgbmF0aXZlR2xvYmFsWydub3RpZnlSdW50aW1lUmVhZHlPblJUJyArIHRoaXMubmF0aXZlQXBwSWRdICYmXG4gICAgICBuYXRpdmVHbG9iYWxbJ25vdGlmeVJ1bnRpbWVSZWFkeU9uUlQnICsgdGhpcy5uYXRpdmVBcHBJZF0odGhpcy5seW54KTtcbiAgfVxuXG4gIHByb3RlY3RlZCBpbml0RXh0cmEob3B0aW9uczogQXBwUHJveHlQYXJhbXM8TmF0aXZlQXBwUHJveHk+KSB7XG4gICAgY29uc3QgeyBseW54IH0gPSBvcHRpb25zO1xuXG4gICAgdGhpcy5fY2FsbGJhY2tNYW5hZ2VyID0gbmV3IENhbGxiYWNrTWFuYWdlcigpO1xuICAgIHRoaXMuc2V0VGltZW91dCA9IHRoaXMud3JhcENhbGxiYWNrTWV0aG9kKHRoaXMubmF0aXZlQXBwLnNldFRpbWVvdXQpO1xuICAgIHRoaXMuc2V0SW50ZXJ2YWwgPSB0aGlzLndyYXBDYWxsYmFja01ldGhvZChcbiAgICAgIHRoaXMubmF0aXZlQXBwLnNldEludGVydmFsLFxuICAgICAgZmFsc2VcbiAgICApO1xuICAgIHRoaXMuY2xlYXJJbnRlcnZhbCA9IHRoaXMud3JhcENsZWFyVGltZXJNZXRob2QoXG4gICAgICB0aGlzLm5hdGl2ZUFwcC5jbGVhckludGVydmFsXG4gICAgKTtcbiAgICB0aGlzLmNsZWFyVGltZW91dCA9IHRoaXMud3JhcENsZWFyVGltZXJNZXRob2QodGhpcy5uYXRpdmVBcHAuY2xlYXJUaW1lb3V0KTtcblxuICAgIHRoaXMubW9kdWxlcyA9IHt9O1xuICAgIHRoaXMuX2xhenlDYWxsYWJsZU1vZHVsZXMgPSBuZXcgTWFwKCk7XG4gICAgdGhpcy5fbmF0aXZlQXBwID0gQ2FjaGVkRnVuY3Rpb25Qcm94eS5jcmVhdGU8TmF0aXZlQXBwUHJveHk+KFxuICAgICAgdGhpcy5fbmF0aXZlQXBwXG4gICAgKTtcbiAgICB0aGlzLnNoYXJlZENvbnNvbGUgPSBjcmVhdGVTaGFyZWRDb25zb2xlKGBydW50aW1lSWQ6JHt0aGlzLm5hdGl2ZUFwcElkfWApO1xuICAgIHRoaXMuZHluYW1pY0NvbXBvbmVudEV4cG9ydHMgPSB7fTtcbiAgICB0aGlzLmxvYWRlZER5bmFtaWNDb21wb25lbnRzU2V0ID0gbmV3IFNldCgpO1xuICAgIHRoaXMuX2xhenlDYWxsYWJsZU1vZHVsZXMgPSBuZXcgTWFwKCk7XG5cbiAgICB0aGlzLlJlcG9ydGVyID0gbmV3IFJlcG9ydGVyKFxuICAgICAgKCkgPT4gdGhpcyxcbiAgICAgICgpID0+IHRoaXMubmF0aXZlQXBwXG4gICAgKTtcblxuICAgIC8vIGluaXQgZXZlbnRFbWl0dGVyXG4gICAgdGhpcy5HbG9iYWxFdmVudEVtaXR0ZXIgPSBuZXcgRXZlbnRFbWl0dGVyKFxuICAgICAgdGhpcy5fX2ludGVybmFsX19jYWxsTHlueFNldE1vZHVsZS5iaW5kKHRoaXMpXG4gICAgKTtcbiAgICB0aGlzLl9pbnRlcnNlY3Rpb25PYnNlcnZlck1hbmFnZXIgPSBuZXcgSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyKFxuICAgICAgdGhpcy5OYXRpdmVNb2R1bGVzXG4gICAgKTtcblxuICAgIHRoaXMuX2V4cG9zdXJlTWFuYWdlciA9IG5ldyBFeHBvc3VyZU1hbmFnZXIodGhpcy5OYXRpdmVNb2R1bGVzKTtcbiAgICB0aGlzLnNldHVwRXhwb3N1cmVBcGkoKTtcbiAgICB0aGlzLl9hb3BNYW5hZ2VyID0gbmV3IEFvcE1hbmFnZXIoKTtcbiAgICB0aGlzLmJlZm9yZVB1Ymxpc2hFdmVudCA9IHRoaXMuX2FvcE1hbmFnZXIuX2JlZm9yZVB1Ymxpc2hFdmVudDtcblxuICAgIHRoaXMucGVyZm9ybWFuY2UgPSBuZXcgUGVyZm9ybWFuY2UodGhpcy5HbG9iYWxFdmVudEVtaXR0ZXIsIHRoaXMubmF0aXZlQXBwKTtcblxuICAgIGNvbnN0IHByb21pc2VDdG9yID0gdGhpcy5zZXR1cFByb21pc2UoXG4gICAgICB0aGlzLnNldFRpbWVvdXQsXG4gICAgICB0aGlzLmNsZWFyVGltZW91dCxcbiAgICAgIHRoaXMucXVldWVNaWNyb3Rhc2tcbiAgICApO1xuXG4gICAgdGhpcy5seW54ID0gdGhpcy5jcmVhdGVMeW54KGx5bngsIHByb21pc2VDdG9yKTtcbiAgICB0aGlzLnNldHVwSlNNb2R1bGUoKTtcbiAgICB0aGlzLnNldHVwSW50ZXJzZWN0aW9uQXBpKCk7XG4gICAgdGhpcy5zZXR1cEZldGNoQVBJKHByb21pc2VDdG9yKTtcbiAgfVxuXG4gIHByb3RlY3RlZCBpbml0QmFzZShvcHRpb25zOiBBcHBQcm94eVBhcmFtczxOYXRpdmVBcHBQcm94eT4pIHtcbiAgICBjb25zdCB7IG5hdGl2ZUFwcCwgcGFyYW1zIH0gPSBvcHRpb25zO1xuXG4gICAgLy8gaW5pdCBpZCAmIGxvYWRDYXJkUGFyYW1cbiAgICB0aGlzLm5hdGl2ZUFwcElkID0gbmF0aXZlQXBwLmlkO1xuICAgIHRoaXMuX3BhcmFtcyA9IHBhcmFtcztcbiAgICB0aGlzLl9uYXRpdmVBcHAgPSBuYXRpdmVBcHA7XG5cbiAgICAvLyBpbml0IG5hdGl2ZSBOYXRpdmVNb2R1bGVzXG4gICAgdGhpcy5OYXRpdmVNb2R1bGVzID0gbmF0aXZlQXBwLm5hdGl2ZU1vZHVsZVByb3h5O1xuICAgIHRoaXMuTHlueFVJTWV0aG9kTW9kdWxlID0gbmF0aXZlQXBwLm5hdGl2ZU1vZHVsZVByb3h5Lkx5bnhVSU1ldGhvZE1vZHVsZTtcbiAgICB0aGlzLkx5bnhUZXN0TW9kdWxlID0gbmF0aXZlQXBwLm5hdGl2ZU1vZHVsZVByb3h5Lkx5bnhUZXN0TW9kdWxlO1xuICAgIHRoaXMuTHlueFJlc291cmNlTW9kdWxlID0gbmF0aXZlQXBwLm5hdGl2ZU1vZHVsZVByb3h5Lkx5bnhSZXNvdXJjZU1vZHVsZTtcbiAgICB0aGlzLkx5bnhBY2Nlc3NpYmlsaXR5TW9kdWxlID1cbiAgICAgIG5hdGl2ZUFwcC5uYXRpdmVNb2R1bGVQcm94eS5MeW54QWNjZXNzaWJpbGl0eU1vZHVsZTtcbiAgICB0aGlzLkx5bnhTZXRNb2R1bGUgPSBuYXRpdmVBcHAubmF0aXZlTW9kdWxlUHJveHkuTHlueFNldE1vZHVsZTtcblxuICAgIC8vaW5pdCBhcHBMaXN0XG4gICAgdGhpcy5fYXBpTGlzdCA9IHt9O1xuICAgIHRoaXMuX3RleHRJbmZvTWFuYWdlciA9IG5ldyBUZXh0SW5mb01hbmFnZXIodGhpcy5OYXRpdmVNb2R1bGVzKTtcbiAgICB0aGlzLnNldHVwR2V0VGV4dEluZm9BcGkoKTtcbiAgfVxuXG4gIHN0YXRpYyBrRGVmYXVsdFNvdXJjZU1hcFVSTCA9ICdkZWZhdWx0JztcbiAgc3RhdGljIGtHZXRTb3VyY2VNYXBSZWxlYXNlRXJyb3JOYW1lID0gU09VUkNFX01BUF9SRUxFQVNFX0VSUk9SX05BTUU7XG4gIC8qKlxuICAgKiBsZWdhY3kgc291cmNlbWFwIHJlbGVhc2UgdXNlIHVybCBkZWZhdWx0XG4gICAqIHVzZWQgZm9yIGJhY2t3YXJkIGNvbXBhdGliaWxpdHlcbiAgICpcbiAgICogbmV3IHRlbXBsYXRlIHNob3VsZCB1c2Ugc2V0U291cmNlTWFwUmVsZWFzZVxuICAgKi9cbiAgc2V0IF9fc291cmNlbWFwX19yZWxlYXNlX18ocmVsZWFzZTogc3RyaW5nKSB7XG4gICAgbGV0IGVycm9yID0gbmV3IEVycm9yKCk7XG4gICAgZXJyb3IubmFtZSA9ICdMeW54R2V0U291cmNlTWFwUmVsZWFzZUVycm9yJztcbiAgICBlcnJvci5tZXNzYWdlID0gcmVsZWFzZTtcbiAgICBlcnJvci5zdGFjayA9IGBhdCA8YW5vbnltb3VzPiAoJHtCYXNlQXBwLmtEZWZhdWx0U291cmNlTWFwVVJMfToxOjEpYDtcbiAgICB0aGlzLnNldFNvdXJjZU1hcFJlbGVhc2UoZXJyb3IpO1xuICB9XG5cbiAgLyoqXG4gICAqIFNldCBzb3VyY2VtYXAgcmVsZWFzZSB3aXRoIGEgbmV3bHkgdGhyb3duIGVycm9yXG4gICAqIEBwYXJhbSB7RXJyb3J9IGVycm9yXG4gICAqIFRoZSBlcnJvciB0aHJvd24gZnJvbSB0aGUgZmlsZSB0aGF0IHdhbnRzIHRvIHNldCBzb3VyY2VtYXAgcmVsZWFzZS5cbiAgICogVGhlIHRvcCBmcmFtZSBvZiBgZXJyb3Iuc3RhY2tgICoqbXVzdCBiZSoqIHRoZSBmaWxlbmFtZS5cbiAgICogVGhlIGBlcnJvci5uYW1lYCAqKm11c3QgYmUqKiBgJ0x5bnhHZXRTb3VyY2VNYXBSZWxlYXNlRXJyb3InYC5cbiAgICogVGhlIGBlcnJvci5tZXNzYWdlYCAqKm11c3QgYmUqKiB0aGUgc291cmNlbWFwIHJlbGVhc2UuXG4gICAqXG4gICAqIEBleGFtcGxlXG4gICAqIChmdW5jdGlvbiAoKSB7XG4gICAqICAgdHJ5IHtcbiAgICogICAgIHRocm93IG5ldyBFcnJvcihzb3VyY2VtYXBSZWxlYXNlKTtcbiAgICogICB9IGNhdGNoIChlKSB7XG4gICAqICAgICBlLm5hbWUgPSAnTHlueEdldFNvdXJjZU1hcFJlbGVhc2VFcnJvcic7XG4gICAqICAgICB0dC5zZXRTb3VyY2VNYXBSZWxlYXNlKGUpO1xuICAgKiAgIH1cbiAgICogfSkoKVxuICAgKi9cbiAgc2V0U291cmNlTWFwUmVsZWFzZSA9IChlcnJvcjogRXJyb3IpID0+IHtcbiAgICB0aGlzLlJlcG9ydGVyLnNldFNvdXJjZU1hcFJlbGVhc2UoZXJyb3IpO1xuICB9O1xuXG4gIGdldFNvdXJjZU1hcFJlbGVhc2UgPSAodXJsOiBzdHJpbmcpOiBzdHJpbmcgPT4ge1xuICAgIHJldHVybiB0aGlzLlJlcG9ydGVyLmdldFNvdXJjZU1hcFJlbGVhc2UodXJsKTtcbiAgfTtcblxuICBxdWV1ZU1pY3JvdGFzayA9IChjYWxsYmFjazogKCkgPT4gdm9pZCk6IHZvaWQgPT4ge1xuICAgIGlmICghY2FsbGJhY2spIHtcbiAgICAgIHJldHVybjtcbiAgICB9XG4gICAgaWYgKCF0aGlzLnBhcmFtcz8ucGFnZUNvbmZpZ1N1YnNldD8uZW5hYmxlSlNDYWxsYmFja01hbmFnZXIpIHtcbiAgICAgIHRoaXMubHlueC5nZXROYXRpdmVMeW54KCkucXVldWVNaWNyb3Rhc2soY2FsbGJhY2spO1xuICAgIH0gZWxzZSB7XG4gICAgICBjb25zdCBpZCA9IHRoaXMuX2NhbGxiYWNrTWFuYWdlci5hZGRDYWxsYmFjayhjYWxsYmFjayk7XG4gICAgICBpZiAoaWQgPT09IHVuZGVmaW5lZCkge1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgICB0aGlzLmx5bnguZ2V0TmF0aXZlTHlueCgpLnF1ZXVlTWljcm90YXNrKGlkKTtcbiAgICB9XG4gIH07XG5cbiAgLyoqXG4gICAqIHBhc3MgaWQgaW5zdGVhZCBvZiBjYWxsYmFjayBmb3IgbmF0aXZlLlxuICAgKiBmb3Igc2V0VGltZW91dOOAgXNldEludGVydmFs44CBcXVldWVNaWNyb3Rhc2sgYW5kIG90aGVyLlxuICAgKi9cbiAgcHJpdmF0ZSB3cmFwQ2FsbGJhY2tNZXRob2QoXG4gICAgbmF0aXZlTWV0aG9kOiBMeW54U2V0VGltZW91dDIsXG4gICAgaXNUaW1lb3V0OiBib29sZWFuID0gdHJ1ZVxuICApOiAoY2FsbGJhY2s6ICguLi5hcmdzOiB1bmtub3duW10pID0+IHVua25vd24sIGRlbGF5OiBudW1iZXIpID0+IG51bWJlciB7XG4gICAgaWYgKCF0aGlzLnBhcmFtcz8ucGFnZUNvbmZpZ1N1YnNldD8uZW5hYmxlSlNDYWxsYmFja01hbmFnZXIpIHtcbiAgICAgIHJldHVybiBuYXRpdmVNZXRob2Q7XG4gICAgfVxuICAgIGNvbnN0IHRoYXQgPSB0aGlzO1xuICAgIHJldHVybiBmdW5jdGlvbiAoXG4gICAgICBjYWxsYmFjazogKC4uLmFyZ3M6IHVua25vd25bXSkgPT4gdW5rbm93bixcbiAgICAgIGRlbGF5OiBudW1iZXJcbiAgICApOiBudW1iZXIge1xuICAgICAgaWYgKCFjYWxsYmFjaykge1xuICAgICAgICByZXR1cm4gLTE7XG4gICAgICB9XG4gICAgICBjb25zdCB0YXNrSW5mbyA9IHsgdGFza0lkOiB1bmRlZmluZWQgfTtcbiAgICAgIGNvbnN0IGNiID0gKCkgPT4ge1xuICAgICAgICB0cnkge1xuICAgICAgICAgIGNhbGxiYWNrLmFwcGx5KGNhbGxiYWNrLCB1bmRlZmluZWQpO1xuICAgICAgICB9IGZpbmFsbHkge1xuICAgICAgICAgIGlmIChpc1RpbWVvdXQpIHtcbiAgICAgICAgICAgIHRoYXQuX2NhbGxiYWNrTWFuYWdlci5yZW1vdmVUYXNrSWQodGFza0luZm8udGFza0lkKTtcbiAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgIH07XG4gICAgICBjb25zdCBpZCA9IHRoYXQuX2NhbGxiYWNrTWFuYWdlci5hZGRDYWxsYmFjayhjYik7XG4gICAgICBpZiAoaWQgPT09IHVuZGVmaW5lZCkge1xuICAgICAgICByZXR1cm4gLTE7XG4gICAgICB9XG4gICAgICBjb25zdCB0YXNrSWQgPSBuYXRpdmVNZXRob2QuY2FsbCh1bmRlZmluZWQsIGlkLCBkZWxheSk7XG4gICAgICBpZiAodGFza0lkICE9PSB1bmRlZmluZWQpIHtcbiAgICAgICAgdGhhdC5fY2FsbGJhY2tNYW5hZ2VyLmFkZFRhc2tJZEFuZENhbGxiYWNrSWQodGFza0lkLCBpZCk7XG4gICAgICAgIHRhc2tJbmZvLnRhc2tJZCA9IHRhc2tJZDtcbiAgICAgIH1cbiAgICAgIHJldHVybiB0YXNrSWQ7XG4gICAgfTtcbiAgfVxuXG4gIHByaXZhdGUgd3JhcENsZWFyVGltZXJNZXRob2QgPSAoXG4gICAgbmF0aXZlTWV0aG9kOiBMeW54Q2xlYXJUaW1lb3V0XG4gICk6IEx5bnhDbGVhclRpbWVvdXQgPT4ge1xuICAgIGlmICghdGhpcy5wYXJhbXM/LnBhZ2VDb25maWdTdWJzZXQ/LmVuYWJsZUpTQ2FsbGJhY2tNYW5hZ2VyKSB7XG4gICAgICByZXR1cm4gbmF0aXZlTWV0aG9kO1xuICAgIH1cbiAgICByZXR1cm4gKHRhc2tJZDogbnVtYmVyKSA9PiB7XG4gICAgICBuYXRpdmVNZXRob2QuY2FsbCh1bmRlZmluZWQsIHRhc2tJZCk7XG4gICAgICB0aGlzLl9jYWxsYmFja01hbmFnZXIucmVtb3ZlQ2FsbGJhY2tCeVRhc2tJZCh0YXNrSWQpO1xuICAgIH07XG4gIH07XG5cbiAgZGVzdHJveSgpIHtcbiAgICB0aGlzLl9fcmVtb3ZlSW50ZXJuYWxFdmVudExpc3RlbmVycygpO1xuICAgIHRoaXMuX2NhbGxiYWNrTWFuYWdlci5kZXN0cm95KCk7XG4gICAgdGhpcy5fbmF0aXZlQXBwID0gbnVsbDtcbiAgICB0aGlzLl9wYXJhbXMgPSBudWxsO1xuICAgIHRoaXMuX2xhenlDYWxsYWJsZU1vZHVsZXMgPSBudWxsO1xuICAgIHRoaXMuR2xvYmFsRXZlbnRFbWl0dGVyID0gbnVsbDtcbiAgfVxuXG4gIHJlZ2lzdGVyTW9kdWxlKG5hbWU6IHN0cmluZywgbW9kdWxlOiBvYmplY3QpOiB2b2lkIHtcbiAgICB0aGlzLl9sYXp5Q2FsbGFibGVNb2R1bGVzW25hbWVdID0gbW9kdWxlO1xuICB9XG5cbiAgZ2V0SlNNb2R1bGU8TW9kdWxlID0gdW5rbm93bj4obmFtZTogc3RyaW5nKTogTW9kdWxlIHtcbiAgICByZXR1cm4gdGhpcy5fbGF6eUNhbGxhYmxlTW9kdWxlc1tuYW1lXTtcbiAgfVxuXG4gIHNldHVwSlNNb2R1bGUoKSB7XG4gICAgdGhpcy5yZWdpc3Rlck1vZHVsZSgnR2xvYmFsRXZlbnRFbWl0dGVyJywgdGhpcy5HbG9iYWxFdmVudEVtaXR0ZXIpO1xuICAgIHRoaXMucmVnaXN0ZXJNb2R1bGUoJ1JlcG9ydGVyJywgdGhpcy5SZXBvcnRlcik7XG4gIH1cblxuICBzZXR1cEZldGNoQVBJKFByb21pc2U6IFByb21pc2VDb25zdHJ1Y3Rvcikge1xuICAgIHRoaXMuX2NyZWF0ZVJlYWRhYmxlU3RyZWFtQ2xhc3MgPSBjcmVhdGVSZWFkYWJsZVN0cmVhbUNsYXNzO1xuICAgIHRoaXMuX1JlYWRhYmxlU3RyZWFtQ2xhc3MgPSBjcmVhdGVSZWFkYWJsZVN0cmVhbUNsYXNzKFByb21pc2UpO1xuICAgIGlmICghbmF0aXZlR2xvYmFsLlJlcXVlc3QpIHtcbiAgICAgIG5hdGl2ZUdsb2JhbC5SZXF1ZXN0ID0gUmVxdWVzdDtcbiAgICB9XG4gICAgaWYgKCFuYXRpdmVHbG9iYWwuUmVzcG9uc2UpIHtcbiAgICAgIG5hdGl2ZUdsb2JhbC5SZXNwb25zZSA9IFJlc3BvbnNlO1xuICAgIH1cbiAgICBpZiAoIW5hdGl2ZUdsb2JhbC5SZWFkYWJsZVN0cmVhbSkge1xuICAgICAgbmF0aXZlR2xvYmFsLlJlYWRhYmxlU3RyZWFtID0gdGhpcy5fUmVhZGFibGVTdHJlYW1DbGFzcztcbiAgICB9XG4gIH1cblxuICBwcml2YXRlIF9faW50ZXJuYWxfX2NhbGxMeW54U2V0TW9kdWxlKGZ1bmN0aW9uTmFtZTogc3RyaW5nLCBwYXlsb2FkOiBhbnlbXSkge1xuICAgIGNvbnN0IG5hdGl2ZUZ1bmN0aW9uID0gdGhpcy5MeW54U2V0TW9kdWxlW2Z1bmN0aW9uTmFtZV07XG4gICAgaWYgKG5hdGl2ZUZ1bmN0aW9uKSB7XG4gICAgICBGdW5jdGlvbi5wcm90b3R5cGUuYXBwbHkuY2FsbChuYXRpdmVGdW5jdGlvbiwgdW5kZWZpbmVkLCBwYXlsb2FkKTtcbiAgICB9XG4gIH1cblxuICBnZXQgbmF0aXZlQXBwKCk6IE5hdGl2ZUFwcFByb3h5IHtcbiAgICByZXR1cm4gdGhpcy5fbmF0aXZlQXBwO1xuICB9XG5cbiAgc2V0IG5hdGl2ZUFwcChuYXRpdmVBcHA6IE5hdGl2ZUFwcFByb3h5KSB7XG4gICAgdGhpcy5fbmF0aXZlQXBwID0gbmF0aXZlQXBwO1xuICB9XG5cbiAgZ2V0IHBhcmFtcygpOiBsb2FkQ2FyZFBhcmFtcyB7XG4gICAgcmV0dXJuIHRoaXMuX3BhcmFtcztcbiAgfVxuXG4gIHNldCBhcGlMaXN0KGFwaTogb2JqZWN0KSB7XG4gICAgdGhpcy5fYXBpTGlzdCA9IHsgLi4udGhpcy5fYXBpTGlzdCwgLi4uYXBpIH07XG4gIH1cblxuICBzZXR1cEludGVyc2VjdGlvbkFwaSgpIHtcbiAgICBsZXQgc2VsZiA9IHRoaXM7XG4gICAgdGhpcy5fYXBpTGlzdFsnY3JlYXRlSW50ZXJzZWN0aW9uT2JzZXJ2ZXInXSA9IGZ1bmN0aW9uIChcbiAgICAgIGNvbXBvbmVudDogeyBjb21wb25lbnRJZDogc3RyaW5nIH0gJiB7IFtrZXk6IHN0cmluZ106IGFueSB9LFxuICAgICAgb3B0aW9ucz86IHtcbiAgICAgICAgdGhyZXNob2xkcz86IFtdO1xuICAgICAgICBpbml0aWFsUmF0aW8/OiBudW1iZXI7XG4gICAgICAgIG9ic2VydmVBbGw/OiBib29sZWFuO1xuICAgICAgfVxuICAgICkge1xuICAgICAgY29uc3QgeyBjb21wb25lbnRJZCA9ICcnIH0gPSBjb21wb25lbnQ7XG4gICAgICByZXR1cm4gc2VsZi5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyLmNyZWF0ZUludGVyc2VjdGlvbk9ic2VydmVyKFxuICAgICAgICBjb21wb25lbnRJZCxcbiAgICAgICAgb3B0aW9uc1xuICAgICAgKTtcbiAgICB9O1xuICAgIHRoaXMubHlueFsnY3JlYXRlSW50ZXJzZWN0aW9uT2JzZXJ2ZXInXSA9IHRoaXMuX2FwaUxpc3RbXG4gICAgICAnY3JlYXRlSW50ZXJzZWN0aW9uT2JzZXJ2ZXInXG4gICAgXSBhcyBDcmVhdGVJbnRlcnNlY3Rpb25PYnNlcnZlckZ1bmM7XG4gIH1cblxuICBvbkludGVyc2VjdGlvbk9ic2VydmVyRXZlbnQoXG4gICAgb2JzZXJ2ZXJJZDogbnVtYmVyLFxuICAgIGNhbGxiYWNrSWQ6IG51bWJlcixcbiAgICBkYXRhOiBSZWNvcmQ8YW55LCBhbnk+XG4gICk6IHZvaWQge1xuICAgIGNvbnN0IG9ic2VydmVyID0gdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyLmdldE9ic2VydmVyKG9ic2VydmVySWQpO1xuICAgIGlmIChvYnNlcnZlcikge1xuICAgICAgb2JzZXJ2ZXIuaW52b2tlQ2FsbGJhY2soY2FsbGJhY2tJZCwgZGF0YSk7XG4gICAgfVxuICB9XG5cbiAgc2V0dXBHZXRUZXh0SW5mb0FwaSA9ICgpOiB2b2lkID0+IHtcbiAgICB0aGlzLl9hcGlMaXN0WydnZXRUZXh0SW5mbyddID0gKFxuICAgICAgdGV4dDogU3RyaW5nLFxuICAgICAgb3B0aW9ucz86IFRleHRJbmZvXG4gICAgKTogVGV4dE1ldHJpY3MgPT4ge1xuICAgICAgcmV0dXJuIHRoaXMuX3RleHRJbmZvTWFuYWdlci5nZXRUZXh0SW5mbyh0ZXh0LCBvcHRpb25zKTtcbiAgICB9O1xuICB9O1xuXG4gIHNldHVwRXhwb3N1cmVBcGkgPSAoKTogdm9pZCA9PiB7XG4gICAgdGhpcy5fYXBpTGlzdFsncmVzdW1lRXhwb3N1cmUnXSA9ICgpOiB2b2lkID0+IHtcbiAgICAgIHRoaXMuX2V4cG9zdXJlTWFuYWdlci5yZXN1bWVFeHBvc3VyZSgpO1xuICAgIH07XG4gICAgdGhpcy5fYXBpTGlzdFsnc3RvcEV4cG9zdXJlJ10gPSAob3B0aW9ucz86IHtcbiAgICAgIHNlbmRFdmVudD86IGJvb2xlYW47XG4gICAgfSk6IHZvaWQgPT4ge1xuICAgICAgdGhpcy5fZXhwb3N1cmVNYW5hZ2VyLnN0b3BFeHBvc3VyZShcbiAgICAgICAgb3B0aW9ucyA/IG9wdGlvbnMgOiB7IHNlbmRFdmVudDogdHJ1ZSB9XG4gICAgICApO1xuICAgIH07XG4gICAgdGhpcy5fYXBpTGlzdFsnc2V0T2JzZXJ2ZXJGcmFtZVJhdGUnXSA9IChvcHRpb25zPzoge1xuICAgICAgZm9yUGFnZVJlY3Q/OiBudW1iZXI7XG4gICAgICBmb3JFeHBvc3VyZUNoZWNrPzogbnVtYmVyO1xuICAgIH0pOiB2b2lkID0+IHtcbiAgICAgIHRoaXMuX2V4cG9zdXJlTWFuYWdlci5zZXRPYnNlcnZlckZyYW1lUmF0ZShcbiAgICAgICAgb3B0aW9ucyA/IG9wdGlvbnMgOiB7IGZvclBhZ2VSZWN0OiAyMCwgZm9yRXhwb3N1cmVDaGVjazogMjAgfVxuICAgICAgKTtcbiAgICB9O1xuICB9O1xuXG4gIHJlcG9ydEVycm9yKGVycm9yOiBFcnJvcikge1xuICAgIHJldHVybiB0aGlzLmx5bngucmVwb3J0RXJyb3IoZXJyb3IpO1xuICB9XG5cbiAgaGFuZGxlRXJyb3IoXG4gICAgZXJyb3I6IEJhc2VFcnJvcixcbiAgICBvcmlnaW5FcnJvcj86IEVycm9yLFxuICAgIGVycm9yTGV2ZWw/OiBMeW54RXJyb3JMZXZlbFxuICApIHtcbiAgICByZXBvcnRFcnJvcihlcnJvciwgdGhpcy5uYXRpdmVBcHAsIHtcbiAgICAgIG9yaWdpbkVycm9yLFxuICAgICAgZ2V0U291cmNlTWFwUmVsZWFzZTogdGhpcy5nZXRTb3VyY2VNYXBSZWxlYXNlLFxuICAgICAgZXJyb3JMZXZlbDogZXJyb3JMZXZlbCxcbiAgICB9KTtcbiAgfVxuXG4gIGhhbmRsZVVzZXJFcnJvcihcbiAgICBlcnJvcj86IEVycm9yLFxuICAgIGNhdXNlPzogdW5rbm93bixcbiAgICBlcnJvckxldmVsPzogTHlueEVycm9yTGV2ZWwsXG4gICAgcHJlZml4Pzogc3RyaW5nXG4gICk6IHZvaWQge1xuICAgIGxldCB7IG1lc3NhZ2UsIG5hbWUsIHN0YWNrIH0gPSBlcnJvciB8fCB7fTtcbiAgICBpZiAoIW1lc3NhZ2UpIHtcbiAgICAgIC8vIElmIHRoZXJlIGlzIG5vIGVycm9yIG1lc3NhZ2UgaW4gZXJyb3IsIG1lYW5zIHRoYXQgaXQgaXMgbm90IGFuIGVycm9yLWxpa2Ugb2JqZWN0LlxuICAgICAgLy8gV2UgY29uc3RydWN0IGEgbmV3IEVycm9yIHVzaW5nIEpTT04uc3RyaW5naWZ5XG4gICAgICAoeyBtZXNzYWdlLCBuYW1lLCBzdGFjayB9ID0gbmV3IEVycm9yKEpTT04uc3RyaW5naWZ5KGVycm9yKSkpO1xuICAgIH1cbiAgICBjb25zdCB1c2VyRXJyb3IgPSBuZXcgVXNlclJ1bnRpbWVFcnJvcihcbiAgICAgIHByZWZpeCA/IGAke3ByZWZpeH0gJHtuYW1lfTogJHttZXNzYWdlfWAgOiBgJHtuYW1lfTogJHttZXNzYWdlfWAsXG4gICAgICBzdGFja1xuICAgICk7XG4gICAgdXNlckVycm9yLmNhdXNlID0gY2F1c2U7XG4gICAgdGhpcy5oYW5kbGVFcnJvcih1c2VyRXJyb3IsIGVycm9yLCBlcnJvckxldmVsKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBAaW50ZXJuYWxcbiAgICovXG4gIGhhbmRsZUludGVybmFsRXJyb3IoZXJyb3I/OiBFcnJvciwgY2F1c2U/OiB1bmtub3duKTogdm9pZCB7XG4gICAgbGV0IHsgbWVzc2FnZSwgbmFtZSwgc3RhY2sgfSA9IGVycm9yIHx8IHt9O1xuICAgIGlmICghbWVzc2FnZSkge1xuICAgICAgLy8gSWYgdGhlcmUgaXMgbm8gZXJyb3IgbWVzc2FnZSBpbiBlcnJvciwgbWVhbnMgdGhhdCBpdCBpcyBub3QgYW4gZXJyb3ItbGlrZSBvYmplY3QuXG4gICAgICAvLyBXZSBjb25zdHJ1Y3QgYSBuZXcgRXJyb3IgdXNpbmcgSlNPTi5zdHJpbmdpZnlcbiAgICAgICh7IG1lc3NhZ2UsIG5hbWUsIHN0YWNrIH0gPSBuZXcgRXJyb3IoSlNPTi5zdHJpbmdpZnkoZXJyb3IpKSk7XG4gICAgfVxuICAgIGNvbnN0IGludGVybmFsRXJyb3IgPSBuZXcgSW50ZXJuYWxSdW50aW1lRXJyb3IoXG4gICAgICBgJHtuYW1lfTogJHttZXNzYWdlfWAsXG4gICAgICBzdGFja1xuICAgICk7XG4gICAgaW50ZXJuYWxFcnJvci5jYXVzZSA9IGNhdXNlO1xuICAgIHRoaXMuaGFuZGxlRXJyb3IoaW50ZXJuYWxFcnJvciwgZXJyb3IpO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCBhIGV4dGVybmFsIGVudiB3aXRoIGJvb2xlYW4gdmFsdWUuXG4gICAqIFRoZSBzYW1lIGFzIGBiYXNlOjpMeW54RW52OjpHZXRJbnN0YW5jZSgpLkdldEJvb2xFbnZgXG4gICAqXG4gICAqIEBwYXJhbSB7RW52S2V5fSBrZXkgVGhlIHtAbGluayBFbnZLZXl9LCBzaG91bGQgYmUgcGxhY2VkIGluIGBseW54X2Vudi5oYFxuICAgKi9cbiAgZ2V0Qm9vbEVudihrZXk6IEVudktleSk6IGJvb2xlYW4ge1xuICAgIGNvbnN0IGVudiA9IHRoaXMubmF0aXZlQXBwLmdldEVudihrZXkpO1xuICAgIHJldHVybiBlbnY/LnRvTG93ZXJDYXNlKCkgPT09ICd0cnVlJztcbiAgfVxuXG4gIC8qKlxuICAgKiBAaW50ZXJuYWxcbiAgICogQHN0YXRpY1xuICAgKiBUaGUgTHlueEdyb3VwIGxldmVsIGNhY2hlIGZvciByZXF1aXJlTW9kdWxlICwge0BsaW5rIHJlZ2lzdGVyTW9kdWxlfVxuICAgKi9cbiAgc3RhdGljIF8kZmFjdG9yeUNhY2hlOiBSZWNvcmQ8XG4gICAgc3RyaW5nLFxuICAgIDxUPihpbmplY3RlZDogeyB0dDogQmFzZUFwcCB9KSA9PiBUXG4gID4gPSB7fTtcblxuICAvKipcbiAgICogQGludGVybmFsXG4gICAqIEBzdGF0aWNcbiAgICogVGhlIEx5bnhHcm91cCBsZXZlbCBjYWNoZSBmb3IgbG9hZFNjcmlwdFxuICAgKi9cbiAgc3RhdGljIF8kbG9hZFNjcmlwdENhY2hlOiBSZWNvcmQ8c3RyaW5nLCBCdW5kbGVJbml0UmV0dXJuT2JqIHwgRnVuY3Rpb24+ID0ge307XG5cbiAgLyoqXG4gICAqIEBpbnRlcm5hbFxuICAgKiBFeGVjdXRlIHRoZSBsb2FkZWQgSlMgbW9kdWxlICwgIENhbGxlZCBieSB7QGxpbmsgcmVxdWlyZU1vZHVsZX0gJiB7QGxpbmsgcmVxdWlyZU1vZHVsZUFzeW5jfVxuICAgKiBAdGhyb3dzIHtVc2VyUnVudGltZUVycm9yfSB3aGVuIGxvYWRpbmcgb3IgZXZhbHVhdGluZyBmYWlsZWRcbiAgICogQHRocm93cyB7RXJyb3J9IHdoZW4gZXhlY3V0aW5nIGZhaWxlZFxuICAgKi9cbiAgcHJpdmF0ZSBfJGV4ZWN1dGVJbml0PFQ+KFxuICAgIGV4cG9ydHM6IFJldHVyblR5cGU8TmF0aXZlQXBwWydsb2FkU2NyaXB0J10+LFxuICAgIHtcbiAgICAgIHBhdGgsXG4gICAgICBlbnRyeU5hbWUsXG4gICAgICBzaG91bGRDYWNoZUZhY3RvcnkgPSB0cnVlLFxuICAgICAgY2FjaGVLZXksXG4gICAgfToge1xuICAgICAgcGF0aDogc3RyaW5nO1xuICAgICAgZW50cnlOYW1lPzogc3RyaW5nO1xuICAgICAgc2hvdWxkQ2FjaGVGYWN0b3J5PzogYm9vbGVhbjtcbiAgICAgIGNhY2hlS2V5Pzogc3RyaW5nO1xuICAgIH1cbiAgKTogVCB7XG4gICAgbGV0IGZhY3Rvcnk6IDxUPihpbmplY3RlZDogeyB0dDogQmFzZUFwcCB9KSA9PiBUO1xuICAgIGlmIChleHBvcnRzICYmIGV4cG9ydHMuaW5pdCkge1xuICAgICAgLy8gYXBwLXNlcnZpY2UuanMgYW5kIGNvbW1vbi1jaHVuay5qcyB3aXRoIG5ldyBmb3JtYXQgd2lsbCBoYXZlIGluaXQgZnVuY3Rpb25cbiAgICAgIGZhY3RvcnkgPSBleHBvcnRzLmluaXQuYmluZChleHBvcnRzKTtcbiAgICB9IGVsc2UgaWYgKG5hdGl2ZUdsb2JhbC5pbml0QnVuZGxlKSB7XG4gICAgICAvLyBjb21tb24tY2h1bmsuanMgd2l0aCBvbGQgZm9ybWF0IHdpbGwgc2V0IGdsb2JhbC5pbml0QnVuZGxlIGR1cmluZyBsb2FkU2NyaXB0XG4gICAgICBmYWN0b3J5ID0gbmF0aXZlR2xvYmFsLmluaXRCdW5kbGUuYmluZChuYXRpdmVHbG9iYWwuaW5pdEJ1bmRsZSk7XG4gICAgICBkZWxldGUgbmF0aXZlR2xvYmFsLmluaXRCdW5kbGU7IC8vIHNob3VsZCBkZWxldGUgaW5pdEJ1bmRsZSBhZnRlciB1c2VkXG4gICAgfSBlbHNlIHtcbiAgICAgIC8vIG5vIGZhY3RvcnkgZnVuY3Rpb24gZm91bmQsIHByb2JhYmx5IGxvYWRTY3JpcHQgZmFpbGVkLlxuICAgICAgLy8gVE9ETyh3YW5ncWluZ3l1KTogZG8gbm90IHRocm93IHRoaXMgd2hlbiBgbmF0aXZlQXBwLmxvYWRTY3JpcHRgIHN1cHBvcnQgZXhjZXB0aW9uc1xuICAgICAgdGhyb3cgbmV3IFVzZXJSdW50aW1lRXJyb3IoXG4gICAgICAgIGBsb2FkIGZhaWxlZC4gcGF0aDoke3BhdGh9LGVudHJ5TmFtZToke2VudHJ5TmFtZX1gXG4gICAgICApO1xuICAgIH1cbiAgICB0cnkge1xuICAgICAgdGhpcy5seW54LnBlcmZvcm1hbmNlLnByb2ZpbGVTdGFydChUcmFjZUV2ZW50RGVmLkVYRUNVVEVfTE9BREVEX1NDUklQVCwge1xuICAgICAgICBhcmdzOiB7IHBhdGggfSxcbiAgICAgIH0pO1xuICAgICAgY29uc3QgcmV0ID0gZmFjdG9yeTxUPih7IHR0OiB0aGlzIH0pO1xuXG4gICAgICAvLyBIZXJlIG1lYW5zIHRoYXQgbm8gZXJyb3Igb2NjdXJyZWQgd2hlbiBleGVjdXRpbmcuXG4gICAgICAvLyBPbmx5IHRoZW4gd2UgY2FjaGUgdGhlIGZhY3RvcnkuXG4gICAgICBpZiAoc2hvdWxkQ2FjaGVGYWN0b3J5KSB7XG4gICAgICAgIEJhc2VBcHAuXyRmYWN0b3J5Q2FjaGVbcGF0aF0gPSBmYWN0b3J5O1xuICAgICAgfVxuICAgICAgYWRkTG9hZFNjcmlwdENhY2hlKGNhY2hlS2V5LCBleHBvcnRzKTtcblxuICAgICAgcmV0dXJuIHJldDtcbiAgICB9IGZpbmFsbHkge1xuICAgICAgdGhpcy5seW54LnBlcmZvcm1hbmNlLnByb2ZpbGVFbmQoKTtcbiAgICB9XG4gIH1cblxuICAvKipcbiAgICogQGludGVybmFsXG4gICAqIFVzZWQgdG8gbG9hZCB0aGUganNvbiBtb2R1bGUuIENhbGxlZCBieSB7QGxpbmsgcmVxdWlyZU1vZHVsZX0gJiB7QGxpbmsgcmVxdWlyZU1vZHVsZUFzeW5jfVxuICAgKiBAcGFyYW0gY29udGVudFxuICAgKiBAcGFyYW0gcGF0aFxuICAgKiBAcHJpdmF0ZVxuICAgKi9cbiAgcHJpdmF0ZSBfJGV4ZWN1dGVKU09OPFQ+KFxuICAgIGNvbnRlbnQ6IFJldHVyblR5cGU8TmF0aXZlQXBwWydyZWFkU2NyaXB0J10+LFxuICAgIHsgcGF0aCB9OiB7IHBhdGg6IHN0cmluZzsgZW50cnlOYW1lPzogc3RyaW5nIH1cbiAgKTogVCB7XG4gICAgY29uc3QgcmV0ID0gSlNPTi5wYXJzZShjb250ZW50KTtcbiAgICBjb25zdCBpbml0ID0gKCkgPT4gcmV0O1xuICAgIEJhc2VBcHAuXyRmYWN0b3J5Q2FjaGVbcGF0aF0gPSBpbml0O1xuICAgIHJldHVybiByZXQ7XG4gIH1cblxuICByZXF1aXJlTW9kdWxlPFQ+KFxuICAgIHBhdGg6IHN0cmluZyxcbiAgICBlbnRyeU5hbWU/OiBzdHJpbmcsXG4gICAgb3B0aW9ucz86IHsgdGltZW91dDogbnVtYmVyIH1cbiAgKTogVCB7XG4gICAgY29uc3QgaW5pdCA9IEJhc2VBcHAuXyRmYWN0b3J5Q2FjaGVbcGF0aF07XG4gICAgaWYgKE5PREVfRU5WICE9PSAnZGV2ZWxvcG1lbnQnICYmIGluaXQpIHtcbiAgICAgIC8vIGNhY2hlIGhpdFxuICAgICAgcmV0dXJuIHRoaXMuXyRleGVjdXRlSW5pdDxUPih7IGluaXQgfSwgeyBwYXRoLCBlbnRyeU5hbWUgfSk7XG4gICAgfVxuXG4gICAgLy8gY2FjaGUgbWlzc1xuICAgIGlmIChwYXRoLnNwbGl0KCc/JylbMF0uZW5kc1dpdGgoJy5qc29uJykpIHtcbiAgICAgIGNvbnN0IGNvbnRlbnQgPSB0aGlzLm5hdGl2ZUFwcC5yZWFkU2NyaXB0KHBhdGgsIHtcbiAgICAgICAgZHluYW1pY0NvbXBvbmVudEVudHJ5OiBlbnRyeU5hbWUgPz8gREVGQVVMVF9FTlRSWSxcbiAgICAgICAgLi4ub3B0aW9ucyxcbiAgICAgIH0pO1xuICAgICAgcmV0dXJuIHRoaXMuXyRleGVjdXRlSlNPTihjb250ZW50LCB7IHBhdGgsIGVudHJ5TmFtZSB9KTtcbiAgICB9XG4gICAgY29uc3QgY2FjaGVLZXkgPSB0aGlzLmdldExvYWRTY3JpcHRDYWNoZUtleShcbiAgICAgIHBhdGgsXG4gICAgICBlbnRyeU5hbWUsXG4gICAgICB0aGlzLnBhcmFtcy5zcmNOYW1lXG4gICAgKTtcbiAgICBjb25zdCBjYWNoZSA9IHRyeUdldExvYWRTY3JpcHRDYWNoZShjYWNoZUtleSk7XG4gICAgaWYgKGNhY2hlKSB7XG4gICAgICAvLyBjYWNoZSBoaXRcbiAgICAgIHJldHVybiB0aGlzLl8kZXhlY3V0ZUluaXQ8VD4oY2FjaGUgYXMgQnVuZGxlSW5pdFJldHVybk9iaiwge1xuICAgICAgICBwYXRoLFxuICAgICAgICBlbnRyeU5hbWUsXG4gICAgICB9KTtcbiAgICB9IGVsc2Uge1xuICAgICAgY29uc3QgZXhwb3J0cyA9IHRoaXMubmF0aXZlQXBwLmxvYWRTY3JpcHQocGF0aCwgZW50cnlOYW1lLCBvcHRpb25zKTtcbiAgICAgIHJldHVybiB0aGlzLl8kZXhlY3V0ZUluaXQ8VD4oZXhwb3J0cywgeyBwYXRoLCBlbnRyeU5hbWUsIGNhY2hlS2V5IH0pO1xuICAgIH1cbiAgfVxuXG4gIHJlcXVpcmVNb2R1bGVBc3luYzxUPihcbiAgICBwYXRoOiBzdHJpbmcsXG4gICAgY2FsbGJhY2s6IChlcnJvcj86IEVycm9yLCBleHBvcnRzPzogVCkgPT4gdm9pZFxuICApOiB2b2lkIHtcbiAgICBjb25zdCBpbml0ID0gQmFzZUFwcC5fJGZhY3RvcnlDYWNoZVtwYXRoXTtcbiAgICBpZiAoTk9ERV9FTlYgIT09ICdkZXZlbG9wbWVudCcgJiYgaW5pdCkge1xuICAgICAgLy8gY2FjaGUgaGl0XG4gICAgICBjYWxsYmFjayhudWxsLCB0aGlzLl8kZXhlY3V0ZUluaXQ8VD4oeyBpbml0IH0sIHsgcGF0aCB9KSk7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIC8vIGNhY2hlIG1pc3NcbiAgICBpZiAocGF0aC5zcGxpdCgnPycpWzBdLmVuZHNXaXRoKCcuanNvbicpKSB7XG4gICAgICB0cnkge1xuICAgICAgICBjb25zdCBjb250ZW50ID0gdGhpcy5uYXRpdmVBcHAucmVhZFNjcmlwdChwYXRoKTtcbiAgICAgICAgY29uc3QgcmV0ID0gdGhpcy5fJGV4ZWN1dGVKU09OPFQ+KGNvbnRlbnQsIHsgcGF0aCB9KTtcbiAgICAgICAgY2FsbGJhY2sobnVsbCwgcmV0KTtcbiAgICAgIH0gY2F0Y2ggKGUpIHtcbiAgICAgICAgY2FsbGJhY2soZSk7XG4gICAgICB9XG4gICAgICByZXR1cm47XG4gICAgfVxuXG4gICAgLy8gZ2V0IGNhY2hlIGZpcnN0XG4gICAgY29uc3QgY2FjaGVLZXkgPSB0aGlzLmdldExvYWRTY3JpcHRDYWNoZUtleShwYXRoLCB0aGlzLnBhcmFtcy5zcmNOYW1lKTtcbiAgICBjb25zdCBjYWNoZSA9IHRyeUdldExvYWRTY3JpcHRDYWNoZShjYWNoZUtleSk7XG4gICAgaWYgKGNhY2hlKSB7XG4gICAgICAvLyBjYWNoZSBoaXRcbiAgICAgIHRyeSB7XG4gICAgICAgIHJldHVybiBjYWxsYmFjayhcbiAgICAgICAgICBudWxsLFxuICAgICAgICAgIHRoaXMuXyRleGVjdXRlSW5pdChjYWNoZSBhcyBCdW5kbGVJbml0UmV0dXJuT2JqLCB7IHBhdGggfSlcbiAgICAgICAgKTtcbiAgICAgIH0gY2F0Y2ggKGUpIHtcbiAgICAgICAgY2FsbGJhY2soZSk7XG4gICAgICB9XG4gICAgfVxuICAgIC8vIENyZWF0ZSBhbiBlcnJvciBoZXJlIHRvIG1ha2Ugc3VyZSB0aGUgc3RhY2sgY29udGFpbnNcbiAgICAvLyBseW54LnJlcXVpcmVNb2R1bGVBc3luYyBhbmQgaXQncyBjYWxsZXIuXG4gICAgY29uc3QgZXJyb3IgPSBuZXcgRXJyb3IoKTtcbiAgICB0aGlzLm5hdGl2ZUFwcC5sb2FkU2NyaXB0QXN5bmMocGF0aCwgKG1lc3NhZ2UsIGV4cG9ydHMpOiB2b2lkID0+IHtcbiAgICAgIGlmIChtZXNzYWdlKSB7XG4gICAgICAgIGVycm9yLm1lc3NhZ2UgPSBtZXNzYWdlO1xuICAgICAgICAvLyBPbmx5IG92ZXJyaWRlIGVycm9yLm1lc3NhZ2Ugc28gdGhhdCB3ZSBjb3VsZCBwcml2aWRlIHN0YWNrIHdpdGhcbiAgICAgICAgLy8gbHlueC5yZXF1aXJlTW9kdWxlQXN5bmMgYW5kIGl0J3MgY2FsbGVyLlxuICAgICAgICByZXR1cm4gY2FsbGJhY2soZXJyb3IpO1xuICAgICAgfVxuXG4gICAgICB0cnkge1xuICAgICAgICByZXR1cm4gY2FsbGJhY2sobnVsbCwgdGhpcy5fJGV4ZWN1dGVJbml0KGV4cG9ydHMsIHsgcGF0aCwgY2FjaGVLZXkgfSkpO1xuICAgICAgfSBjYXRjaCAoZSkge1xuICAgICAgICByZXR1cm4gY2FsbGJhY2soZSk7XG4gICAgICB9XG4gICAgfSk7XG4gIH1cblxuICByZXF1aXJlKHBhdGg6IHN0cmluZywgcGFyYW1zPzogcmVxdWlyZVBhcmFtT2JqKSB7XG4gICAgY29uc3QgdGhhdCA9IHRoaXM7XG4gICAgaWYgKHR5cGVvZiBwYXRoICE9PSAnc3RyaW5nJykge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKCdyZXF1aXJlIGFyZ3MgbXVzdCBiZSBhIHN0cmluZycpO1xuICAgIH1cbiAgICBjb25zdCBlbnRyeU5hbWUgPVxuICAgICAgcGFyYW1zICYmIHBhcmFtcy5keW5hbWljQ29tcG9uZW50RW50cnlcbiAgICAgICAgPyBwYXJhbXMuZHluYW1pY0NvbXBvbmVudEVudHJ5XG4gICAgICAgIDogREVGQVVMVF9FTlRSWTtcbiAgICBpZiAoIXRoYXQubW9kdWxlc1tlbnRyeU5hbWVdKSB7XG4gICAgICB0aGF0Lm1vZHVsZXNbZW50cnlOYW1lXSA9IHt9O1xuICAgIH1cbiAgICBsZXQgbW9kdWxlID0gdGhhdC5tb2R1bGVzW2VudHJ5TmFtZV1bcGF0aF07XG4gICAgaWYgKCFtb2R1bGUpIHtcbiAgICAgIHRyeSB7XG4gICAgICAgIC8vIGVzbGludC1kaXNhYmxlLW5leHQtbGluZSBAdHlwZXNjcmlwdC1lc2xpbnQvbm8tdW51c2VkLXZhcnNcbiAgICAgICAgY29uc3QgdHQgPSB0aGF0O1xuICAgICAgICBjb25zdCBqc0NvbnRlbnQgPSB0aGF0Ll9uYXRpdmVBcHAucmVhZFNjcmlwdChwYXRoLCB7XG4gICAgICAgICAgZHluYW1pY0NvbXBvbmVudEVudHJ5OiBlbnRyeU5hbWUsXG4gICAgICAgIH0pO1xuICAgICAgICAvLyBlc2xpbnQtZGlzYWJsZS1uZXh0LWxpbmUgbm8tZXZhbFxuICAgICAgICBldmFsKGpzQ29udGVudCk7XG4gICAgICAgIG1vZHVsZSA9IHRoYXQubW9kdWxlc1tlbnRyeU5hbWVdW3BhdGhdO1xuICAgICAgfSBjYXRjaCAoZSkge1xuICAgICAgICB0aGlzLmhhbmRsZUVycm9yKFxuICAgICAgICAgIG5ldyBVc2VyUnVudGltZUVycm9yKFxuICAgICAgICAgICAgYGV2YWwgdXNlcjogJHt0aGF0Ll9uYXRpdmVBcHAuaWR9IGVycm9yOiAke2UubWVzc2FnZX1gLFxuICAgICAgICAgICAgZS5zdGFja1xuICAgICAgICAgICksXG4gICAgICAgICAgZVxuICAgICAgICApO1xuICAgICAgfVxuXG4gICAgICBpZiAoIXRoYXQubW9kdWxlc1tlbnRyeU5hbWVdW3BhdGhdKSB7XG4gICAgICAgIHRocm93IG5ldyBFcnJvcihcbiAgICAgICAgICBgbW9kdWxlICR7cGF0aH0gaW4gJHtlbnRyeU5hbWV9IGlzIG5vdCBkZWZpbmVkIGluIGNhcmQ6ICR7dGhhdC5fbmF0aXZlQXBwLmlkfWBcbiAgICAgICAgKTtcbiAgICAgIH1cbiAgICB9XG5cbiAgICBpZiAoIW1vZHVsZS5oYXNSdW4pIHtcbiAgICAgIGNvbnN0IHsgZmFjdG9yeSB9ID0gbW9kdWxlO1xuICAgICAgY29uc3QgX21vZHVsZSA9IHtcbiAgICAgICAgZXhwb3J0czoge30sXG4gICAgICB9O1xuICAgICAgbGV0IHJlcztcblxuICAgICAgbW9kdWxlLmhhc1J1biA9IHRydWU7XG4gICAgICBtb2R1bGUuZXhwb3J0cyA9IF9tb2R1bGUuZXhwb3J0cztcbiAgICAgIGlmICh0eXBlb2YgZmFjdG9yeSA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgICBjb25zdCBpblJlcXVpcmVDb3B5ID0gaW5SZXF1aXJlLmNhbGwodGhhdCwgcGF0aCk7XG4gICAgICAgIGNvbnN0IHR0ID0gdGhhdDtcbiAgICAgICAgcmVzID0gZmFjdG9yeShcbiAgICAgICAgICBpblJlcXVpcmVDb3B5LFxuICAgICAgICAgIF9tb2R1bGUsXG4gICAgICAgICAgX21vZHVsZS5leHBvcnRzLFxuICAgICAgICAgIHRoYXQuQ2FyZC5iaW5kKHR0KSxcbiAgICAgICAgICB0aGF0LnNldFRpbWVvdXQsXG4gICAgICAgICAgdGhhdC5zZXRJbnRlcnZhbCxcbiAgICAgICAgICB0aGF0LmNsZWFySW50ZXJ2YWwsXG4gICAgICAgICAgdGhhdC5jbGVhclRpbWVvdXQsXG4gICAgICAgICAgdGhhdC5OYXRpdmVNb2R1bGVzLFxuICAgICAgICAgIHRoYXQuX2FwaUxpc3QsXG4gICAgICAgICAgdGhhdC5zaGFyZWRDb25zb2xlLFxuICAgICAgICAgIHRoYXQuQ29tcG9uZW50LmJpbmQodHQpLFxuICAgICAgICAgIHBhcmFtcz8uUmVhY3RMeW54LFxuICAgICAgICAgIHRoYXQubmF0aXZlQXBwSWQsXG4gICAgICAgICAgdGhhdC5CZWhhdmlvci5iaW5kKHR0KSxcbiAgICAgICAgICBMeW54SlNCSSxcbiAgICAgICAgICB0aGF0Lmx5bngsXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyB3aW5kb3dcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIGRvY3VtZW50XG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBmcmFtZXNcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIHNlbGZcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIGxvY2F0aW9uXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBuYXZpZ2F0b3JcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIGxvY2FsU3RvcmFnZVxuICAgICAgICAgIHVuZGVmaW5lZCwgLy8gaGlzdG9yeVxuICAgICAgICAgIHVuZGVmaW5lZCwgLy8gQ2FjaGVzXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBzY3JlZW5cbiAgICAgICAgICB1bmRlZmluZWQsIC8vIGFsZXJ0XG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBjb25maXJtXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBwcm9tcHRcbiAgICAgICAgICB0aGF0Lmx5bnguZmV0Y2gsIC8vIGZldGNoXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBYTUxIdHRwUmVxdWVzdFxuICAgICAgICAgIHVuZGVmaW5lZCwgLy8gV2ViU29ja2V0XG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyB3ZWJraXRcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIFJlcG9ydGVyXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBwcmludFxuICAgICAgICAgIHVuZGVmaW5lZCwgLy8gZ2xvYmFsXG4gICAgICAgICAgdGhhdC5yZXF1ZXN0QW5pbWF0aW9uRnJhbWUsXG4gICAgICAgICAgdGhhdC5jYW5jZWxBbmltYXRpb25GcmFtZVxuICAgICAgICApO1xuICAgICAgICBtb2R1bGUuZXhwb3J0cyA9IF9tb2R1bGUuZXhwb3J0cyB8fCByZXM7XG4gICAgICB9XG4gICAgfVxuICAgIHJldHVybiBtb2R1bGUuZXhwb3J0cztcbiAgfVxuXG4gIGRlZmluZShwYXRoOiBzdHJpbmcsIGZhY3Rvcnk6IEFNREZhY3RvcnksIGVudHJ5TmFtZT86IHN0cmluZykge1xuICAgIGVudHJ5TmFtZSA9IGVudHJ5TmFtZSA/IGVudHJ5TmFtZSA6IERFRkFVTFRfRU5UUlk7XG4gICAgaWYgKCF0aGlzLm1vZHVsZXNbZW50cnlOYW1lXSkge1xuICAgICAgdGhpcy5tb2R1bGVzW2VudHJ5TmFtZV0gPSB7fTtcbiAgICB9XG4gICAgdGhpcy5tb2R1bGVzW2VudHJ5TmFtZV1bcGF0aF0gPSB7XG4gICAgICBoYXNSdW46IGZhbHNlLFxuICAgICAgZmFjdG9yeTogZmFjdG9yeS5iaW5kKHRoaXMpLFxuICAgIH07XG4gIH1cblxuICBsb2FkU2NyaXB0PFQ+KFxuICAgIHVybDogc3RyaW5nLFxuICAgIG9wdGlvbnM/OiB7IGJ1bmRsZU5hbWU/OiBzdHJpbmc7IHVzZU1vZHVsZVdyYXBwZXI/OiBib29sZWFuIH1cbiAgKTogVCB7XG4gICAgY29uc3QgeyBidW5kbGVOYW1lID0gREVGQVVMVF9FTlRSWSwgdXNlTW9kdWxlV3JhcHBlciA9IGZhbHNlIH0gPVxuICAgICAgb3B0aW9ucyB8fCB7fTtcbiAgICBjb25zdCBjYWNoZUtleSA9IHRoaXMuZ2V0TG9hZFNjcmlwdENhY2hlS2V5KFxuICAgICAgdXJsLFxuICAgICAgYnVuZGxlTmFtZSxcbiAgICAgIHRoaXMucGFyYW1zLnNyY05hbWUsXG4gICAgICB0cnVlXG4gICAgKTtcbiAgICBsZXQgZXhwb3J0czogQnVuZGxlSW5pdFJldHVybk9iaiB8IG9iamVjdCA9IHRyeUdldExvYWRTY3JpcHRDYWNoZShjYWNoZUtleSk7XG4gICAgaWYgKE5PREVfRU5WID09PSAnZGV2ZWxvcG1lbnQnIHx8ICFleHBvcnRzKSB7XG4gICAgICBsZXQgbWF5YmVFeHBvcnRzID0gdGhpcy5seW54LmdldE5hdGl2ZUx5bngoKS5sb2FkU2NyaXB0KHVybCwgb3B0aW9ucyk7XG4gICAgICBpZiAobWF5YmVFeHBvcnRzICYmIHR5cGVvZiAobWF5YmVFeHBvcnRzIGFzIGFueSkuaW5pdCA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgICBleHBvcnRzID0gbWF5YmVFeHBvcnRzIGFzIEJ1bmRsZUluaXRSZXR1cm5PYmo7XG4gICAgICB9IGVsc2UgaWYgKFxuICAgICAgICB1c2VNb2R1bGVXcmFwcGVyICYmXG4gICAgICAgIG1heWJlRXhwb3J0cyAmJlxuICAgICAgICB0eXBlb2YgbWF5YmVFeHBvcnRzID09PSAnZnVuY3Rpb24nXG4gICAgICApIHtcbiAgICAgICAgZXhwb3J0cyA9IG1heWJlRXhwb3J0cztcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHJldHVybiBtYXliZUV4cG9ydHMgYXMgVDtcbiAgICAgIH1cbiAgICB9XG5cbiAgICBpZiAodXNlTW9kdWxlV3JhcHBlcikge1xuICAgICAgY29uc3QgbW9kdWxlID0geyBleHBvcnRzOiB7fSB9O1xuICAgICAgbGV0IHRoYXQgPSB0aGlzO1xuICAgICAgY29uc3QgaW5SZXF1aXJlQ29weSA9IGluUmVxdWlyZS5jYWxsKHRoYXQsIHVybCk7XG4gICAgICBjb25zdCBhcmdzID0gW1xuICAgICAgICBpblJlcXVpcmVDb3B5LFxuICAgICAgICBtb2R1bGUsXG4gICAgICAgIG1vZHVsZS5leHBvcnRzLFxuICAgICAgICB0aGF0LnNldFRpbWVvdXQsXG4gICAgICAgIHRoYXQuc2V0SW50ZXJ2YWwsXG4gICAgICAgIHRoYXQuY2xlYXJJbnRlcnZhbCxcbiAgICAgICAgdGhhdC5jbGVhclRpbWVvdXQsXG4gICAgICAgIHRoYXQuTmF0aXZlTW9kdWxlcyxcbiAgICAgICAgdGhhdC5zaGFyZWRDb25zb2xlLFxuICAgICAgICB0aGF0Lm5hdGl2ZUFwcElkLFxuICAgICAgICBMeW54SlNCSSxcbiAgICAgICAgdGhhdC5seW54LFxuICAgICAgICB0aGF0LnJlcXVlc3RBbmltYXRpb25GcmFtZSxcbiAgICAgICAgdGhhdC5jYW5jZWxBbmltYXRpb25GcmFtZSxcbiAgICAgICAgdGhhdC5seW54LmZldGNoLFxuICAgICAgXTtcbiAgICAgIChleHBvcnRzIGFzIEZ1bmN0aW9uKS5hcHBseShtb2R1bGUuZXhwb3J0cywgYXJncyk7XG4gICAgICBhZGRMb2FkU2NyaXB0Q2FjaGUoY2FjaGVLZXksIGV4cG9ydHMgYXMgRnVuY3Rpb24pO1xuICAgICAgcmV0dXJuIG1vZHVsZS5leHBvcnRzIGFzIFQ7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiB0aGlzLl8kZXhlY3V0ZUluaXQ8VD4oZXhwb3J0cyBhcyBCdW5kbGVJbml0UmV0dXJuT2JqLCB7XG4gICAgICAgIHBhdGg6IHVybCxcbiAgICAgICAgZW50cnlOYW1lOiBvcHRpb25zPy5idW5kbGVOYW1lLFxuICAgICAgICBzaG91bGRDYWNoZUZhY3Rvcnk6IGZhbHNlLFxuICAgICAgICBjYWNoZUtleTogY2FjaGVLZXksXG4gICAgICB9KTtcbiAgICB9XG4gIH1cblxuICAvKipcbiAgICogQ2FsbCBCeSBOYXRpdmUganNfYXBwXG4gICAqIEBpbnRlcm5hbFxuICAgKiBAcGFyYW0gbW9kdWxlXG4gICAqIEBwYXJhbSBtZXRob2RcbiAgICogQHBhcmFtIGFyZ3NcbiAgICovXG4gIGNhbGxGdW5jdGlvbihtb2R1bGU6IHN0cmluZywgbWV0aG9kOiBzdHJpbmcsIGFyZ3M/OiB1bmtub3duW10pOiB2b2lkIHtcbiAgICB0cnkge1xuICAgICAgY29uc3QgbW9kdWxlTWV0aG9kcyA9IHRoaXMuZ2V0SlNNb2R1bGUobW9kdWxlKTtcbiAgICAgIGlmICh0eXBlb2YgbW9kdWxlTWV0aG9kc1ttZXRob2RdID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgIG1vZHVsZU1ldGhvZHNbbWV0aG9kXS5hcHBseShtb2R1bGVNZXRob2RzLCBhcmdzKTtcbiAgICAgIH1cbiAgICB9IGNhdGNoIChlKSB7XG4gICAgICB0aGlzLmhhbmRsZVVzZXJFcnJvcihlLCB7IGJ5OiBgJHttb2R1bGV9LiR7bWV0aG9kfWAgfSk7XG4gICAgfVxuICB9XG5cbiAgLyoqXG4gICAqIENhbGwgQnkgTmF0aXZlIGpzX2FwcFxuICAgKiBAaW50ZXJuYWxcbiAgICogQHBhcmFtIHtuZXZlcn0gXyBVc2VkIGZvciBiYWNrd2FyZCBjb21wYXRpYmxpdHksIERPIE5PVCBVU0UuXG4gICAqIEBwYXJhbSB7RXJyb3J9IGVycm9yIHRoZSBFcnJvciBvYmplY3QgZW1pdCBieSBuYXRpdmUuXG4gICAqL1xuICBvbkFwcEVycm9yKF86IG5ldmVyLCBlcnJvcjogRXJyb3IpOiB2b2lkIHtcbiAgICB0aGlzLmhhbmRsZUludGVybmFsRXJyb3IoZXJyb3IpO1xuICB9XG5cbiAgc2F2ZUR5bmFtaWNDb21wb25lbnRFeHBvcnRzKGNvbXBvbmVudFVybCwgbW9kdWxlRXhwb3J0cykge1xuICAgIHRoaXMuZHluYW1pY0NvbXBvbmVudEV4cG9ydHNbY29tcG9uZW50VXJsXSA9IG1vZHVsZUV4cG9ydHM7XG4gIH1cblxuICBnZXREeW5hbWljQ29tcG9uZW50RXhwb3J0cyhjb21wb25lbnRVcmwpIHtcbiAgICByZXR1cm4gdGhpcy5keW5hbWljQ29tcG9uZW50RXhwb3J0c1tjb21wb25lbnRVcmxdO1xuICB9XG5cbiAgQ29tcG9uZW50KC4uLmFyZ3M6IHVua25vd25bXSk6IHZvaWQge31cblxuICBDYXJkKC4uLmFyZ3M6IHVua25vd25bXSk6IHZvaWQge31cblxuICBCZWhhdmlvcj8oLi4uYXJnczogdW5rbm93bltdKTogdm9pZCB7fVxuXG4gIC8qKlxuICAgKiBAcGFyYW0gc2V0VGltZW91dFxuICAgKi9cbiAgd3JhcFJlcG9ydChzZXRUaW1lb3V0OiBGdW5jdGlvbiwgZGVzYzogc3RyaW5nKSB7XG4gICAgY29uc3QgdGhhdCA9IHRoaXM7XG5cbiAgICBmdW5jdGlvbiB3cmFwUmVwb3J0KGZuOiBGdW5jdGlvbikge1xuICAgICAgcmV0dXJuIGZ1bmN0aW9uIHdyYXBSZXBvcnRJbm5lciguLi5hcmdzOiBhbnlbXSkge1xuICAgICAgICB0cnkge1xuICAgICAgICAgIHJldHVybiBmbi5hcHBseSh0aGlzLCBhcmdzKTtcbiAgICAgICAgfSBjYXRjaCAoZSkge1xuICAgICAgICAgIHRoYXQuaGFuZGxlVXNlckVycm9yKGUsIHsgYnk6IGRlc2MgfSk7XG4gICAgICAgIH1cbiAgICAgIH07XG4gICAgfVxuXG4gICAgcmV0dXJuIGZ1bmN0aW9uIFdyYXBUaW1lb3V0KGZuOiBGdW5jdGlvbiwgLi4uYXJnczogYW55W10pIHtcbiAgICAgIHJldHVybiBGdW5jdGlvbi5wcm90b3R5cGUuYXBwbHkuY2FsbChzZXRUaW1lb3V0LCB1bmRlZmluZWQsIFtcbiAgICAgICAgd3JhcFJlcG9ydChmbiksXG4gICAgICAgIC4uLmFyZ3MsXG4gICAgICBdKTtcbiAgICB9O1xuICB9XG5cbiAgc2V0dXBQcm9taXNlKFxuICAgIHNldFRpbWVvdXQ6IEx5bnhTZXRUaW1lb3V0LFxuICAgIGNsZWFyVGltZW91dDogTHlueENsZWFyVGltZW91dCxcbiAgICBxdWV1ZU1pY3JvdGFzazogKGNhbGxiYWNrOiAoKSA9PiB2b2lkKSA9PiB2b2lkXG4gICkge1xuICAgIGNvbnN0IFByb21pc2VDb25zdHJ1Y3RvciA9IGdldFByb21pc2VNYXliZVBvbHlmaWxsKFxuICAgICAgc2V0VGltZW91dCxcbiAgICAgIChpZCwgcmVhc29uOiBFcnJvcikgPT4ge1xuICAgICAgICB0cnkge1xuICAgICAgICAgIGlmIChyZWFzb24pIHtcbiAgICAgICAgICAgIGlmICghcmVhc29uLnN0YWNrKSB7XG4gICAgICAgICAgICAgIHJlYXNvbiA9IG5ldyBFcnJvcihKU09OLnN0cmluZ2lmeShyZWFzb24pKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIHJlYXNvbi5uYW1lID0gJ3VuaGFuZGxlZCByZWplY3Rpb24nO1xuICAgICAgICAgICAgdGhpcy5oYW5kbGVVc2VyRXJyb3IocmVhc29uKTtcbiAgICAgICAgICB9XG4gICAgICAgIH0gY2F0Y2ggKGVycikge1xuICAgICAgICAgIC8vIGp1c3QgaWdub3JlXG4gICAgICAgIH1cbiAgICAgIH0sXG4gICAgICBjbGVhclRpbWVvdXQsXG4gICAgICBxdWV1ZU1pY3JvdGFzayxcbiAgICAgIHRoaXMuX3BhcmFtcz8ucGFnZUNvbmZpZ1N1YnNldD8uZW5hYmxlTWljcm90YXNrUHJvbWlzZVBvbHlmaWxsID8/IGZhbHNlXG4gICAgKTtcbiAgICB0aGlzLnJlc29sdmVkUHJvbWlzZSA9IFByb21pc2VDb25zdHJ1Y3Rvci5yZXNvbHZlKCk7XG4gICAgcmV0dXJuIFByb21pc2VDb25zdHJ1Y3RvcjtcbiAgfVxuXG4gIHJlcXVlc3RBbmltYXRpb25GcmFtZSA9IChjYWxsYmFjazogKCkgPT4gdm9pZCkgPT5cbiAgICB0aGlzLl9uYXRpdmVBcHAucmVxdWVzdEFuaW1hdGlvbkZyYW1lKGNhbGxiYWNrKTtcblxuICBjYW5jZWxBbmltYXRpb25GcmFtZSA9IChhbmltYXRpb25JZDogbnVtYmVyKSA9PlxuICAgIHRoaXMuX25hdGl2ZUFwcC5jYW5jZWxBbmltYXRpb25GcmFtZShhbmltYXRpb25JZCk7XG5cbiAgaW52b2tlQ2FsbGJhY2sob25jZTogYm9vbGVhbiwgY2FsbGJhY2tJZDogbnVtYmVyLCAuLi5hcmdzOiB1bmtub3duW10pOiB2b2lkIHtcbiAgICB0aGlzLl9jYWxsYmFja01hbmFnZXIuaW52b2tlQ2FsbGJhY2sob25jZSwgY2FsbGJhY2tJZCwgLi4uYXJncyk7XG4gIH1cblxuICBwcm90ZWN0ZWQgYWRkSW50ZXJuYWxFdmVudExpc3RlbmVyKFxuICAgIGNvbnRleHRQcm94eVR5cGU6IENvbnRleHRQcm94eVR5cGUsXG4gICAgdHlwZTogc3RyaW5nLFxuICAgIGxpc3RlbmVyOiAoZXZlbnQ6IE1lc3NhZ2VFdmVudCkgPT4gdm9pZFxuICApIHtcbiAgICB0aGlzLmNvbnRleHRQcm94eVR5cGVUb01ldGhvZFtjb250ZXh0UHJveHlUeXBlXSgpLmFkZEV2ZW50TGlzdGVuZXIoXG4gICAgICB0eXBlLFxuICAgICAgbGlzdGVuZXJcbiAgICApO1xuICAgIHRoaXMucmVtb3ZlSW50ZXJuYWxFdmVudExpc3RlbmVyc0NhbGxiYWNrcy5wdXNoKCgpID0+IHtcbiAgICAgIHRoaXMuY29udGV4dFByb3h5VHlwZVRvTWV0aG9kW2NvbnRleHRQcm94eVR5cGVdKCkucmVtb3ZlRXZlbnRMaXN0ZW5lcihcbiAgICAgICAgdHlwZSxcbiAgICAgICAgbGlzdGVuZXJcbiAgICAgICk7XG4gICAgfSk7XG4gIH1cblxuICBwcm90ZWN0ZWQgYWRkSW50ZXJuYWxFdmVudExpc3RlbmVycygpIHtcbiAgICBpZiAoIXRoaXMuY29udGV4dFByb3h5VHlwZVRvTWV0aG9kKSB7XG4gICAgICB0aGlzLmNvbnRleHRQcm94eVR5cGVUb01ldGhvZCA9IHtcbiAgICAgICAgW0NvbnRleHRQcm94eVR5cGUuQ29yZUNvbnRleHRdOiAoKSA9PiB0aGlzLmx5bnguZ2V0Q29yZUNvbnRleHQoKSxcbiAgICAgICAgW0NvbnRleHRQcm94eVR5cGUuRGV2VG9vbF06ICgpID0+IHRoaXMubHlueC5nZXREZXZ0b29sKCksXG4gICAgICAgIFtDb250ZXh0UHJveHlUeXBlLkpTQ29udGV4dF06ICgpID0+IHRoaXMubHlueC5nZXRKU0NvbnRleHQoKSxcbiAgICAgICAgW0NvbnRleHRQcm94eVR5cGUuVUlDb250ZXh0XTogKCkgPT4gdGhpcy5seW54LmdldFVJQ29udGV4dCgpLFxuICAgICAgICBbQ29udGV4dFByb3h5VHlwZS5OYXRpdmVdOiAoKSA9PiB0aGlzLmx5bnguZ2V0TmF0aXZlKCksXG4gICAgICAgIFtDb250ZXh0UHJveHlUeXBlLkVuZ2luZV06ICgpID0+IHRoaXMubHlueC5nZXRFbmdpbmUoKSxcbiAgICAgIH07XG4gICAgfVxuXG4gICAgdGhpcy5hZGRJbnRlcm5hbEV2ZW50TGlzdGVuZXIoXG4gICAgICBDb250ZXh0UHJveHlUeXBlLkNvcmVDb250ZXh0LFxuICAgICAgTWVzc2FnZUV2ZW50VHlwZS5PTl9OQVRJVkVfQVBQX1JFQURZLFxuICAgICAgKCkgPT4ge1xuICAgICAgICB0aGlzLm9uTmF0aXZlQXBwUmVhZHkoKTtcbiAgICAgIH1cbiAgICApO1xuICAgIHRoaXMuYWRkSW50ZXJuYWxFdmVudExpc3RlbmVyKFxuICAgICAgQ29udGV4dFByb3h5VHlwZS5Db3JlQ29udGV4dCxcbiAgICAgIE1lc3NhZ2VFdmVudFR5cGUuTk9USUZZX0dMT0JBTF9QUk9QU19VUERBVEVELFxuICAgICAgKGV2ZW50OiBNZXNzYWdlRXZlbnQpID0+IHtcbiAgICAgICAgdGhpcy51cGRhdGVHbG9iYWxQcm9wcyhldmVudC5kYXRhKTtcbiAgICAgIH1cbiAgICApO1xuICAgIHRoaXMuYWRkSW50ZXJuYWxFdmVudExpc3RlbmVyKFxuICAgICAgQ29udGV4dFByb3h5VHlwZS5Db3JlQ29udGV4dCxcbiAgICAgIE1lc3NhZ2VFdmVudFR5cGUuT05fTElGRUNZQ0xFX0VWRU5ULFxuICAgICAgKGV2ZW50OiBNZXNzYWdlRXZlbnQpID0+IHtcbiAgICAgICAgdGhpcy5PbkxpZmVjeWNsZUV2ZW50KGV2ZW50LmRhdGEpO1xuICAgICAgfVxuICAgICk7XG4gICAgdGhpcy5hZGRJbnRlcm5hbEV2ZW50TGlzdGVuZXIoXG4gICAgICBDb250ZXh0UHJveHlUeXBlLkNvcmVDb250ZXh0LFxuICAgICAgTWVzc2FnZUV2ZW50VHlwZS5PTl9BUFBfRklSU1RfU0NSRUVOLFxuICAgICAgKCkgPT4ge1xuICAgICAgICB0aGlzLm9uQXBwRmlyc3RTY3JlZW4oKTtcbiAgICAgIH1cbiAgICApO1xuICAgIHRoaXMuYWRkSW50ZXJuYWxFdmVudExpc3RlbmVyKFxuICAgICAgQ29udGV4dFByb3h5VHlwZS5Db3JlQ29udGV4dCxcbiAgICAgIE1lc3NhZ2VFdmVudFR5cGUuT05fRFlOQU1JQ19KU19TT1VSQ0VfUFJFUEFSRUQsXG4gICAgICAoZXZlbnQ6IE1lc3NhZ2VFdmVudCkgPT4ge1xuICAgICAgICBuYXRpdmVHbG9iYWwubG9hZER5bmFtaWNDb21wb25lbnQodGhpcywgZXZlbnQuZGF0YSk7XG4gICAgICB9XG4gICAgKTtcbiAgICB0aGlzLmFkZEludGVybmFsRXZlbnRMaXN0ZW5lcihcbiAgICAgIENvbnRleHRQcm94eVR5cGUuQ29yZUNvbnRleHQsXG4gICAgICBNZXNzYWdlRXZlbnRUeXBlLk9OX0FQUF9FTlRFUl9GT1JFR1JPVU5ELFxuICAgICAgKCkgPT4ge1xuICAgICAgICB0aGlzLm9uQXBwRW50ZXJGb3JlZ3JvdW5kKCk7XG4gICAgICB9XG4gICAgKTtcbiAgICB0aGlzLmFkZEludGVybmFsRXZlbnRMaXN0ZW5lcihcbiAgICAgIENvbnRleHRQcm94eVR5cGUuQ29yZUNvbnRleHQsXG4gICAgICBNZXNzYWdlRXZlbnRUeXBlLk9OX0FQUF9FTlRFUl9CQUNLR1JPVU5ELFxuICAgICAgKCkgPT4ge1xuICAgICAgICB0aGlzLm9uQXBwRW50ZXJCYWNrZ3JvdW5kKCk7XG4gICAgICB9XG4gICAgKTtcbiAgfVxuXG4gIHByaXZhdGUgX19yZW1vdmVJbnRlcm5hbEV2ZW50TGlzdGVuZXJzID0gKCkgPT4ge1xuICAgIHRoaXMucmVtb3ZlSW50ZXJuYWxFdmVudExpc3RlbmVyc0NhbGxiYWNrcy5mb3JFYWNoKChmKSA9PiB7XG4gICAgICBmKCk7XG4gICAgfSk7XG4gIH07XG5cbiAgcHJpdmF0ZSBnZXRMb2FkU2NyaXB0Q2FjaGVLZXkoXG4gICAgcGF0aDogc3RyaW5nLFxuICAgIGVudHJ5TmFtZT86IHN0cmluZyxcbiAgICB0ZW1wbGF0ZVVybD86IHN0cmluZyxcbiAgICBpZ25vcmVDb25maWc6IGJvb2xlYW4gPSBmYWxzZVxuICApOiBzdHJpbmcgfCB1bmRlZmluZWQge1xuICAgIGlmIChcbiAgICAgICF0ZW1wbGF0ZVVybCB8fFxuICAgICAgTk9ERV9FTlYgPT09ICdkZXZlbG9wbWVudCcgfHxcbiAgICAgICghdGhpcy5wYXJhbXM/LnBhZ2VDb25maWdTdWJzZXQ/LmVuYWJsZVJldXNlTG9hZFNjcmlwdEV4cG9ydHMgJiZcbiAgICAgICAgIWlnbm9yZUNvbmZpZylcbiAgICApIHtcbiAgICAgIHJldHVybiB1bmRlZmluZWQ7XG4gICAgfVxuICAgIGxldCBjYWNoZUtleSA9IChlbnRyeU5hbWUgPyBlbnRyeU5hbWUgOiBERUZBVUxUX0VOVFJZKSArIHBhdGg7XG4gICAgaWYgKHBhdGguc3RhcnRzV2l0aCgnLycpIHx8IHBhdGguc3RhcnRzV2l0aCgnbHlueF9hc3NldHMnKSkge1xuICAgICAgY2FjaGVLZXkgPSB0ZW1wbGF0ZVVybCArIGNhY2hlS2V5O1xuICAgIH1cbiAgICByZXR1cm4gY2FjaGVLZXk7XG4gIH1cblxuICAvKipcbiAgICogIG92ZXJyaWRlIGJ5IHN1YmNsYXNzXG4gICAqIEBwYXJhbSBuZXdEYXRhXG4gICAqL1xuICB1cGRhdGVHbG9iYWxQcm9wcyhuZXdEYXRhOiBvYmplY3QpOiB2b2lkIHt9XG5cbiAgLyoqXG4gICAqICBvdmVycmlkZSBieSBzdWJjbGFzc1xuICAgKiBAcGFyYW0gbmV3RGF0YVxuICAgKi9cbiAgT25MaWZlY3ljbGVFdmVudChcbiAgICBhcmdzOiBbXG4gICAgICBzdHJpbmcsXG4gICAgICBMaWZlRXZlbnQgfCBMaWZlRXZlbnRbXSxcbiAgICAgIHtcbiAgICAgICAgcHJvcHM/OiBSZWNvcmQ8c3RyaW5nLCB1bmtub3duPjtcbiAgICAgICAgaW5pdERhdGE/OiBSZWNvcmQ8c3RyaW5nLCB1bmtub3duPjtcbiAgICAgICAgZGF0YXNldD86IFJlY29yZDxzdHJpbmcsIHN0cmluZz47XG4gICAgICAgIGlkPzogc3RyaW5nO1xuICAgICAgICBjbGFzc05hbWU/OiBzdHJpbmc7XG4gICAgICAgIHBhcmVudElkPzogc3RyaW5nO1xuICAgICAgICBwYXRoPzogc3RyaW5nO1xuICAgICAgICBlbnRyeU5hbWU/OiBzdHJpbmc7XG4gICAgICAgIC8qKlxuICAgICAgICAgKiBhZGRpdGlvbmFsIGFyZ3VtZW50cyBsaWtlIGZvcmNlRmx1c2ggZm9yIFNTUiBjYW4gYmUgcHV0IGhlcmVcbiAgICAgICAgICovXG4gICAgICAgIFtrZXk6IHN0cmluZ106IHVua25vd247XG4gICAgICB9XG4gICAgXVxuICApOiB2b2lkIHt9XG5cbiAgLyoqXG4gICAqICBvdmVycmlkZSBieSBzdWJjbGFzc1xuICAgKiBAcGFyYW0gbmV3RGF0YVxuICAgKi9cbiAgb25OYXRpdmVBcHBSZWFkeSgpOiB2b2lkIHt9XG5cbiAgLyoqXG4gICAqICBvdmVycmlkZSBieSBzdWJjbGFzc1xuICAgKiBAcGFyYW0gbmV3RGF0YVxuICAgKi9cbiAgb25BcHBGaXJzdFNjcmVlbigpOiB2b2lkIHt9XG5cbiAgLyoqXG4gICAqICBvdmVycmlkZSBieSBzdWJjbGFzc1xuICAgKiBAcGFyYW0gbmV3RGF0YVxuICAgKi9cbiAgb25BcHBFbnRlckJhY2tncm91bmQoKTogdm9pZCB7fVxuXG4gIC8qKlxuICAgKiAgb3ZlcnJpZGUgYnkgc3ViY2xhc3NcbiAgICogQHBhcmFtIG5ld0RhdGFcbiAgICovXG4gIG9uQXBwRW50ZXJGb3JlZ3JvdW5kKCk6IHZvaWQge31cblxuICBhYnN0cmFjdCBjcmVhdGVMeW54KFxuICAgIG5hdGl2ZUx5bng6IE5hdGl2ZUx5bnhQcm94eSxcbiAgICBwcm9taXNlQ3RvcjogUHJvbWlzZUNvbnN0cnVjdG9yXG4gICk6IEx5bnhJbXBsO1xufVxuXG5mdW5jdGlvbiBwYXRoUHJvY2VzcyhwYXRoOiBzdHJpbmcpOiBzdHJpbmcge1xuICBjb25zdCBtYXRjaCA9IHBhdGgubWF0Y2goLyguKilcXC8oW14vXSspPyQvKTtcbiAgcmV0dXJuIG1hdGNoPy5bMV0gPyBtYXRjaFsxXSA6ICcuLyc7XG59XG5cbmZ1bmN0aW9uIGluUmVxdWlyZShwYXRoOiBzdHJpbmcpOiBGdW5jdGlvbiB7XG4gIGNvbnN0IHRoYXQgPSB0aGlzO1xuICBjb25zdCBwd2QgPSBwYXRoUHJvY2VzcyhwYXRoKTtcblxuICByZXR1cm4gZnVuY3Rpb24gKHBhdGgpIHtcbiAgICBjb25zdCB0ID0gW107XG4gICAgY29uc3QgciA9IGAke3B3ZH0vJHtwYXRofWAuc3BsaXQoJy8nKTtcbiAgICBjb25zdCBpID0gci5sZW5ndGg7XG5cbiAgICBpZiAodHlwZW9mIHBhdGggIT09ICdzdHJpbmcnKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoJ3JlcXVpcmUgYXJncyBtdXN0IGJlIGEgc3RyaW5nJyk7XG4gICAgfVxuICAgIGZvciAobGV0IG8gPSAwOyBvIDwgaTsgKytvKSB7XG4gICAgICBjb25zdCBhID0gcltvXTtcbiAgICAgIGlmIChhICE9PSAnJyAmJiBhICE9PSAnLicpIHtcbiAgICAgICAgaWYgKGEgPT09ICcuLicpIHtcbiAgICAgICAgICBpZiAodC5sZW5ndGggPT09IDApIHtcbiAgICAgICAgICAgIHRocm93IG5ldyBFcnJvcihcbiAgICAgICAgICAgICAgYGNhbid0IGZpbmQgbW9kdWxlICR7cGF0aH0gaW4gYXBwOiAke3RoYXQuX25hdGl2ZUFwcC5pZH1gXG4gICAgICAgICAgICApO1xuICAgICAgICAgIH1cbiAgICAgICAgICB0LnBvcCgpO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIG8gKyAxIDwgaSAmJiByW28gKyAxXSA9PT0gJy4uJyA/IG8rKyA6IHQucHVzaChhKTtcbiAgICAgICAgfVxuICAgICAgfVxuICAgIH1cbiAgICBsZXQgYyA9IHQuam9pbignLycpO1xuICAgIC8qIGVzbGludC1kaXNhYmxlIG5vLXJldHVybi1hc3NpZ24gKi9cbiAgICAvKiBlc2xpbnQtZGlzYWJsZSBuby1zZXF1ZW5jZXMgKi9cbiAgICByZXR1cm4gYy5lbmRzV2l0aCgnLmpzJykgfHwgKGMgKz0gJy5qcycpLCB0aGF0LnJlcXVpcmUoYyk7XG4gIH07XG59XG5cbmZ1bmN0aW9uIHRyeUdldExvYWRTY3JpcHRDYWNoZShcbiAgY2FjaGVLZXk6IHN0cmluZyB8IHVuZGVmaW5lZFxuKTogQnVuZGxlSW5pdFJldHVybk9iaiB8IHVuZGVmaW5lZCB8IEZ1bmN0aW9uIHtcbiAgaWYgKCFjYWNoZUtleSkge1xuICAgIHJldHVybiB1bmRlZmluZWQ7XG4gIH1cbiAgcmV0dXJuIEJhc2VBcHAuXyRsb2FkU2NyaXB0Q2FjaGVbY2FjaGVLZXldO1xufVxuXG5mdW5jdGlvbiBhZGRMb2FkU2NyaXB0Q2FjaGUoXG4gIGNhY2hlS2V5OiBzdHJpbmcgfCB1bmRlZmluZWQsXG4gIGV4cG9ydHM6IEJ1bmRsZUluaXRSZXR1cm5PYmogfCB1bmRlZmluZWQgfCBGdW5jdGlvblxuKSB7XG4gIGlmICghY2FjaGVLZXkgfHwgIWV4cG9ydHMpIHtcbiAgICByZXR1cm47XG4gIH1cbiAgQmFzZUFwcC5fJGxvYWRTY3JpcHRDYWNoZVtjYWNoZUtleV0gPSBleHBvcnRzO1xufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IEJhc2VBcHAgfSBmcm9tICcuLi9hcHAnO1xuaW1wb3J0IHsgTHlueCwgTmF0aXZlTHlueFByb3h5IH0gZnJvbSAnLi4vbHlueCc7XG5pbXBvcnQgeyBDYWNoZWRGdW5jdGlvblByb3h5IH0gZnJvbSAnLi4vdXRpbCc7XG5cbmV4cG9ydCBjbGFzcyBSZWFjdEFwcCBleHRlbmRzIEJhc2VBcHAge1xuICBjcmVhdGVMeW54KFxuICAgIG5hdGl2ZUx5bng6IE5hdGl2ZUx5bnhQcm94eSxcbiAgICBwcm9taXNlQ3RvcjogUHJvbWlzZUNvbnN0cnVjdG9yXG4gICk6IEx5bngge1xuICAgIGNvbnN0IGx5bnhfcHJveHkgPSBDYWNoZWRGdW5jdGlvblByb3h5LmNyZWF0ZShuYXRpdmVMeW54KTtcbiAgICByZXR1cm4gbmV3IEx5bngoXG4gICAgICAoKSA9PiB0aGlzLm5hdGl2ZUFwcCxcbiAgICAgICgpID0+IHRoaXMsXG4gICAgICBwcm9taXNlQ3RvcixcbiAgICAgICgpID0+IGx5bnhfcHJveHlcbiAgICApO1xuICB9XG5cbiAgY2FsbEJlZm9yZVB1Ymxpc2hFdmVudChldmVudERhdGE/OiBhbnkpOiB2b2lkIHtcbiAgICBpZiAoXG4gICAgICB0aGlzLl9hb3BNYW5hZ2VyLl9iZWZvcmVQdWJsaXNoRXZlbnQuZ2V0RXZlbnRzU2l6ZShldmVudERhdGEudHlwZSkgIT09IDBcbiAgICApIHtcbiAgICAgIGNvbnN0IGNvcHlEYXRhID0geyAuLi5ldmVudERhdGEgfTtcbiAgICAgIHRyeSB7XG4gICAgICAgIHRoaXMuX2FvcE1hbmFnZXIuX2JlZm9yZVB1Ymxpc2hFdmVudC5lbWl0KGNvcHlEYXRhLnR5cGUsIFtjb3B5RGF0YV0pO1xuICAgICAgfSBjYXRjaCAoZSkge1xuICAgICAgICB0aGlzLmhhbmRsZVVzZXJFcnJvcihlLCB7XG4gICAgICAgICAgYnk6ICdjYWxsQmVmb3JlUHVibGlzaEV2ZW50JyxcbiAgICAgICAgICB0eXBlOiAoY29weURhdGEgYXMgYW55KS50eXBlLFxuICAgICAgICB9KTtcbiAgICAgIH1cbiAgICB9XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBERUZBVUxUX0VOVFJZIH0gZnJvbSAnLi4vY29tbW9uJztcbmltcG9ydCB7IFNoYXJlZENvbnNvbGUgfSBmcm9tICdAbHlueC1qcy9ydW50aW1lLXNoYXJlZCc7XG5pbXBvcnQgeyBBcHBQcm94eVBhcmFtcywgQmFzZUFwcCwgbG9hZENhcmRQYXJhbXMsIE5hdGl2ZUFwcCB9IGZyb20gJy4uL2FwcCc7XG5pbXBvcnQgeyBMeW54LCBOYXRpdmVMeW54UHJveHkgfSBmcm9tICcuLi9seW54JztcbmltcG9ydCB7XG4gIENhbGxMeW54U2V0TW9kdWxlLFxuICBFeHBvc3VyZU1hbmFnZXIsXG4gIEludGVyc2VjdGlvbk9ic2VydmVyTWFuYWdlcixcbiAgVGV4dEluZm9NYW5hZ2VyLFxufSBmcm9tICcuLi9tb2R1bGVzL25hdGl2ZU1vZHVsZXMnO1xuaW1wb3J0IHsgQW9wTWFuYWdlciB9IGZyb20gJy4uL21vZHVsZXMnO1xuaW1wb3J0IEV2ZW50RW1pdHRlciBmcm9tICcuLi9tb2R1bGVzL2V2ZW50JztcbmltcG9ydCB7IFJlcG9ydGVyIH0gZnJvbSAnLi4vbW9kdWxlcyc7XG5pbXBvcnQgUGVyZm9ybWFuY2UgZnJvbSAnLi4vbW9kdWxlcy9wZXJmb3JtYW5jZSc7XG5pbXBvcnQgeyBDYWNoZWRGdW5jdGlvblByb3h5IH0gZnJvbSAnLi4vdXRpbCc7XG5pbXBvcnQgeyBBTURNb2R1bGUgfSBmcm9tICcuLi9jb21tb24vYW1kJztcbmltcG9ydCB7IGNyZWF0ZVJlYWRhYmxlU3RyZWFtQ2xhc3MgfSBmcm9tICcuLi9tb2R1bGVzL2ZldGNoJztcbmltcG9ydCB7IENhbGxiYWNrTWFuYWdlciB9IGZyb20gJ3NyYy9jb21tb24vY2FsbGJhY2tNYW5hZ2VyJztcbmltcG9ydCB7IEx5bnhDbGVhclRpbWVvdXQsIEx5bnhTZXRUaW1lb3V0IH0gZnJvbSAnQGx5bngtanMvdHlwZXMnO1xuXG5leHBvcnQgY2xhc3MgQmFzZUFwcFNpbmdsZXRvbkRhdGE8XG4gIE5hdGl2ZUFwcFByb3h5IGV4dGVuZHMgTmF0aXZlQXBwID0gTmF0aXZlQXBwLFxuICBMeW54SW1wbCBleHRlbmRzIEx5bnggPSBMeW54XG4+IHtcbiAgbmF0aXZlQXBwOiBOYXRpdmVBcHBQcm94eTtcbiAgc2hhcmVkQ29uc29sZTogU2hhcmVkQ29uc29sZTtcbiAgZHluYW1pY0NvbXBvbmVudEV4cG9ydHM6IG9iamVjdDtcbiAgbG9hZGVkRHluYW1pY0NvbXBvbmVudHNTZXQ6IFNldDxzdHJpbmc+O1xuICBpbnRlcnNlY3Rpb25PYnNlcnZlck1hbmFnZXI6IEludGVyc2VjdGlvbk9ic2VydmVyTWFuYWdlcjtcbiAgZXhwb3N1cmVNYW5hZ2VyOiBFeHBvc3VyZU1hbmFnZXI7XG4gIHRleHRJbmZvTWFuYWdlcjogVGV4dEluZm9NYW5hZ2VyO1xuICBnbG9iYWxFdmVudEVtaXR0ZXI6IEV2ZW50RW1pdHRlcjtcbiAgYW9wTWFuYWdlcjogQW9wTWFuYWdlcjtcbiAgcGVyZm9ybWFuY2U6IFBlcmZvcm1hbmNlO1xuICBtb2R1bGVzOiBSZWNvcmQ8c3RyaW5nLCBSZWNvcmQ8c3RyaW5nLCBBTURNb2R1bGU+PjtcbiAgbGF6eUNhbGxhYmxlTW9kdWxlczogTWFwPHN0cmluZywgdW5rbm93bj47XG4gIGx5bng6IEx5bnhJbXBsO1xuICBhcGlMaXN0OiBSZWNvcmQ8c3RyaW5nLCB1bmtub3duPjtcbiAgUmVwb3J0ZXI6IFJlcG9ydGVyO1xuICBjYWxsYmFja01hbmFnZXI6IENhbGxiYWNrTWFuYWdlcjtcbiAgc2V0VGltZW91dDogTHlueFNldFRpbWVvdXQ7XG4gIHNldEludGVydmFsOiBMeW54U2V0VGltZW91dDtcbiAgY2xlYXJJbnRlcnZhbDogTHlueENsZWFyVGltZW91dDtcbiAgY2xlYXJUaW1lb3V0OiBMeW54Q2xlYXJUaW1lb3V0O1xuICByZXNvbHZlZFByb21pc2U6IFByb21pc2U8dm9pZD47XG4gIF9jcmVhdGVSZWFkYWJsZVN0cmVhbUNsYXNzOiAoXG4gICAgUHJvbWlzZTogUHJvbWlzZUNvbnN0cnVjdG9yXG4gICkgPT4gUmV0dXJuVHlwZTx0eXBlb2YgY3JlYXRlUmVhZGFibGVTdHJlYW1DbGFzcz47XG4gIF9SZWFkYWJsZVN0cmVhbUNsYXNzOiBSZXR1cm5UeXBlPHR5cGVvZiBjcmVhdGVSZWFkYWJsZVN0cmVhbUNsYXNzPjtcblxuICBwdWJsaWMgdHJhbnNmZXJTaW5nbGV0b25EYXRhKFxuICAgIGJhc2VBcHA6IEJhc2VBcHAsXG4gICAgY2FsbEx5bnhTZXRNb2R1bGU/OiBDYWxsTHlueFNldE1vZHVsZVxuICApIHtcbiAgICBiYXNlQXBwLm5hdGl2ZUFwcCA9IHRoaXMubmF0aXZlQXBwO1xuICAgIGJhc2VBcHAuc2hhcmVkQ29uc29sZSA9IHRoaXMuc2hhcmVkQ29uc29sZTtcbiAgICBiYXNlQXBwLmR5bmFtaWNDb21wb25lbnRFeHBvcnRzID0gdGhpcy5keW5hbWljQ29tcG9uZW50RXhwb3J0cztcbiAgICBiYXNlQXBwLmxvYWRlZER5bmFtaWNDb21wb25lbnRzU2V0ID0gdGhpcy5sb2FkZWREeW5hbWljQ29tcG9uZW50c1NldDtcbiAgICBiYXNlQXBwLl9pbnRlcnNlY3Rpb25PYnNlcnZlck1hbmFnZXIgPSB0aGlzLmludGVyc2VjdGlvbk9ic2VydmVyTWFuYWdlcjtcbiAgICBiYXNlQXBwLl9leHBvc3VyZU1hbmFnZXIgPSB0aGlzLmV4cG9zdXJlTWFuYWdlcjtcbiAgICBiYXNlQXBwLl90ZXh0SW5mb01hbmFnZXIgPSB0aGlzLnRleHRJbmZvTWFuYWdlcjtcbiAgICB0aGlzLmdsb2JhbEV2ZW50RW1pdHRlci5zZXRDYWxsTHlueFNldE1vZHVsZShjYWxsTHlueFNldE1vZHVsZSk7XG4gICAgYmFzZUFwcC5HbG9iYWxFdmVudEVtaXR0ZXIgPSB0aGlzLmdsb2JhbEV2ZW50RW1pdHRlcjtcbiAgICBiYXNlQXBwLl9hb3BNYW5hZ2VyID0gdGhpcy5hb3BNYW5hZ2VyO1xuICAgIGJhc2VBcHAucGVyZm9ybWFuY2UgPSB0aGlzLnBlcmZvcm1hbmNlO1xuICAgIGJhc2VBcHAubW9kdWxlcyA9IHRoaXMubW9kdWxlcztcbiAgICBiYXNlQXBwLl9sYXp5Q2FsbGFibGVNb2R1bGVzID0gdGhpcy5sYXp5Q2FsbGFibGVNb2R1bGVzO1xuICAgIGJhc2VBcHAubHlueCA9IHRoaXMubHlueDtcbiAgICB0aGlzLmx5bngucmViaW5kKCgpID0+IGJhc2VBcHApO1xuICAgIGJhc2VBcHAuX2FwaUxpc3QgPSB0aGlzLmFwaUxpc3Q7XG4gICAgdGhpcy5SZXBvcnRlci5yZWJpbmQoKCkgPT4gYmFzZUFwcCk7XG4gICAgYmFzZUFwcC5SZXBvcnRlciA9IHRoaXMuUmVwb3J0ZXI7XG4gICAgYmFzZUFwcC5fY2FsbGJhY2tNYW5hZ2VyID0gdGhpcy5jYWxsYmFja01hbmFnZXI7XG4gICAgYmFzZUFwcC5zZXRUaW1lb3V0ID0gdGhpcy5zZXRUaW1lb3V0O1xuICAgIGJhc2VBcHAuc2V0SW50ZXJ2YWwgPSB0aGlzLnNldEludGVydmFsO1xuICAgIGJhc2VBcHAuY2xlYXJJbnRlcnZhbCA9IHRoaXMuY2xlYXJJbnRlcnZhbDtcbiAgICBiYXNlQXBwLmNsZWFyVGltZW91dCA9IHRoaXMuY2xlYXJUaW1lb3V0O1xuICAgIGJhc2VBcHAucmVzb2x2ZWRQcm9taXNlID0gdGhpcy5yZXNvbHZlZFByb21pc2U7XG4gICAgLy8gZmV0Y2ggYXBpIHJlbGF0ZWRcbiAgICBiYXNlQXBwLl9jcmVhdGVSZWFkYWJsZVN0cmVhbUNsYXNzID0gdGhpcy5fY3JlYXRlUmVhZGFibGVTdHJlYW1DbGFzcztcbiAgICBiYXNlQXBwLl9SZWFkYWJsZVN0cmVhbUNsYXNzID0gdGhpcy5fUmVhZGFibGVTdHJlYW1DbGFzcztcbiAgfVxufVxuXG5leHBvcnQgZGVmYXVsdCBjbGFzcyBTdGFuZGFsb25lQXBwIGV4dGVuZHMgQmFzZUFwcCB7XG4gIHB1YmxpYyBzaW5nbGV0b25EYXRhOiBCYXNlQXBwU2luZ2xldG9uRGF0YTtcblxuICBjb25zdHJ1Y3RvcihvcHRpb25zOiBBcHBQcm94eVBhcmFtczxOYXRpdmVBcHA+LCBwYXJhbXM6IGxvYWRDYXJkUGFyYW1zKSB7XG4gICAgc3VwZXIob3B0aW9ucywgdW5kZWZpbmVkKTtcbiAgICB0aGlzLmZpbGxTaW5nbGV0b25EYXRhKCk7XG4gICAgdHJ5IHtcbiAgICAgIGlmIChwYXJhbXMuc3JjTmFtZSkge1xuICAgICAgICBkZWxldGUgdGhpcy5seW54LnJlcXVpcmVNb2R1bGUuY2FjaGVbcGFyYW1zLnNyY05hbWVdO1xuICAgICAgICBkZWxldGUgQmFzZUFwcC5fJGZhY3RvcnlDYWNoZVtwYXJhbXMuc3JjTmFtZV07XG4gICAgICAgIHRoaXMubHlueC5yZXF1aXJlTW9kdWxlKHBhcmFtcy5zcmNOYW1lLCBERUZBVUxUX0VOVFJZKTtcbiAgICAgICAgdGhpcy5kYXRhVHlwZVNldC5hZGQoJ3VuZGVmaW5lZCcpO1xuICAgICAgfVxuICAgIH0gY2F0Y2ggKGUpIHtcbiAgICAgIHRoaXMuaGFuZGxlVXNlckVycm9yKGUpO1xuICAgIH1cbiAgfVxuXG4gIGNyZWF0ZUx5bngobmF0aXZlTHlueDogTmF0aXZlTHlueFByb3h5LCBwcm9taXNlOiBQcm9taXNlQ29uc3RydWN0b3IpOiBMeW54IHtcbiAgICBjb25zdCBseW54X3Byb3h5ID0gQ2FjaGVkRnVuY3Rpb25Qcm94eS5jcmVhdGUobmF0aXZlTHlueCk7XG4gICAgcmV0dXJuIG5ldyBMeW54KFxuICAgICAgKCkgPT4gdGhpcy5uYXRpdmVBcHAsXG4gICAgICAoKSA9PiB0aGlzLFxuICAgICAgcHJvbWlzZSxcbiAgICAgICgpID0+IGx5bnhfcHJveHlcbiAgICApO1xuICB9XG5cbiAgcHJpdmF0ZSBmaWxsU2luZ2xldG9uRGF0YSgpIHtcbiAgICB0aGlzLnNpbmdsZXRvbkRhdGEgPSBuZXcgQmFzZUFwcFNpbmdsZXRvbkRhdGEoKTtcbiAgICB0aGlzLnNpbmdsZXRvbkRhdGEubmF0aXZlQXBwID0gdGhpcy5fbmF0aXZlQXBwO1xuICAgIHRoaXMuc2luZ2xldG9uRGF0YS5zaGFyZWRDb25zb2xlID0gdGhpcy5zaGFyZWRDb25zb2xlO1xuICAgIHRoaXMuc2luZ2xldG9uRGF0YS5keW5hbWljQ29tcG9uZW50RXhwb3J0cyA9IHRoaXMuZHluYW1pY0NvbXBvbmVudEV4cG9ydHM7XG4gICAgdGhpcy5zaW5nbGV0b25EYXRhLmxvYWRlZER5bmFtaWNDb21wb25lbnRzU2V0ID0gdGhpcy5sb2FkZWREeW5hbWljQ29tcG9uZW50c1NldDtcbiAgICB0aGlzLnNpbmdsZXRvbkRhdGEuaW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyID0gdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyO1xuICAgIHRoaXMuc2luZ2xldG9uRGF0YS5leHBvc3VyZU1hbmFnZXIgPSB0aGlzLl9leHBvc3VyZU1hbmFnZXI7XG4gICAgdGhpcy5zaW5nbGV0b25EYXRhLnRleHRJbmZvTWFuYWdlciA9IHRoaXMuX3RleHRJbmZvTWFuYWdlcjtcbiAgICB0aGlzLnNpbmdsZXRvbkRhdGEuZ2xvYmFsRXZlbnRFbWl0dGVyID0gdGhpcy5HbG9iYWxFdmVudEVtaXR0ZXI7XG4gICAgdGhpcy5zaW5nbGV0b25EYXRhLmFvcE1hbmFnZXIgPSB0aGlzLl9hb3BNYW5hZ2VyO1xuICAgIHRoaXMuc2luZ2xldG9uRGF0YS5wZXJmb3JtYW5jZSA9IHRoaXMucGVyZm9ybWFuY2U7XG4gICAgdGhpcy5zaW5nbGV0b25EYXRhLm1vZHVsZXMgPSB0aGlzLm1vZHVsZXM7XG4gICAgdGhpcy5zaW5nbGV0b25EYXRhLmxhenlDYWxsYWJsZU1vZHVsZXMgPSB0aGlzLl9sYXp5Q2FsbGFibGVNb2R1bGVzO1xuICAgIHRoaXMuc2luZ2xldG9uRGF0YS5seW54ID0gdGhpcy5seW54O1xuICAgIHRoaXMuc2luZ2xldG9uRGF0YS5hcGlMaXN0ID0gdGhpcy5fYXBpTGlzdDtcbiAgICB0aGlzLnNpbmdsZXRvbkRhdGEuUmVwb3J0ZXIgPSB0aGlzLlJlcG9ydGVyO1xuICAgIHRoaXMuc2luZ2xldG9uRGF0YS5jYWxsYmFja01hbmFnZXIgPSB0aGlzLl9jYWxsYmFja01hbmFnZXI7XG4gICAgdGhpcy5zaW5nbGV0b25EYXRhLnNldFRpbWVvdXQgPSB0aGlzLnNldFRpbWVvdXQ7XG4gICAgdGhpcy5zaW5nbGV0b25EYXRhLnNldEludGVydmFsID0gdGhpcy5zZXRJbnRlcnZhbDtcbiAgICB0aGlzLnNpbmdsZXRvbkRhdGEuY2xlYXJJbnRlcnZhbCA9IHRoaXMuY2xlYXJJbnRlcnZhbDtcbiAgICB0aGlzLnNpbmdsZXRvbkRhdGEuY2xlYXJUaW1lb3V0ID0gdGhpcy5jbGVhclRpbWVvdXQ7XG4gICAgdGhpcy5zaW5nbGV0b25EYXRhLnJlc29sdmVkUHJvbWlzZSA9IHRoaXMucmVzb2x2ZWRQcm9taXNlO1xuICAgIC8vIGZldGNoIGFwaSByZWxhdGVkXG4gICAgdGhpcy5zaW5nbGV0b25EYXRhLl9jcmVhdGVSZWFkYWJsZVN0cmVhbUNsYXNzID0gdGhpcy5fY3JlYXRlUmVhZGFibGVTdHJlYW1DbGFzcztcbiAgICB0aGlzLnNpbmdsZXRvbkRhdGEuX1JlYWRhYmxlU3RyZWFtQ2xhc3MgPSB0aGlzLl9SZWFkYWJsZVN0cmVhbUNsYXNzO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuLy8gc3RhcnQganMgYXBwLCBuYXRpdmUgaGFzIGRlY29kZSBqcyBjb2RlO1xuLy8gcmV0dXJuIG1lYW5zIGxvYWRDYXJkIHN1Y2Nlc3Mgb3IgZmFpbGVkLlxuaW1wb3J0IHsgQmFzZUFwcCwgbG9hZENhcmRQYXJhbXMsIE5hdGl2ZUFwcCB9IGZyb20gJy4vYXBwJztcbmltcG9ydCB7IEx5bngsIE5hdGl2ZUx5bnhQcm94eSB9IGZyb20gJy4vbHlueCc7XG5pbXBvcnQgeyBhbG9nIH0gZnJvbSAnLi9jb21tb24vbG9nJztcbmltcG9ydCBuYXRpdmVHbG9iYWwgZnJvbSAnLi9jb21tb24vbmF0aXZlR2xvYmFsJztcbmltcG9ydCB7IEFQUF9TRVJWSUNFX05BTUUsIERFRkFVTFRfRU5UUlksIEx5bnhGZWF0dXJlIH0gZnJvbSAnLi9jb21tb24nO1xuaW1wb3J0IHsgUmVhY3RBcHAgfSBmcm9tICcuL3JlYWN0L3JlYWN0QXBwJztcbmltcG9ydCB7IEludGVybmFsUnVudGltZUVycm9yLCByZXBvcnRFcnJvciB9IGZyb20gJy4vbW9kdWxlcy9yZXBvcnQnO1xuaW1wb3J0IFN0YW5kYWxvbmVBcHAgZnJvbSAnLi9zdGFuZGFsb25lL1N0YW5kYWxvbmVBcHAnO1xuXG5leHBvcnQgZnVuY3Rpb24gbG9hZENhcmQoXG4gIG5hdGl2ZUFwcDogTmF0aXZlQXBwLFxuICBwYXJhbXM6IGxvYWRDYXJkUGFyYW1zLFxuICBseW54PzogTmF0aXZlTHlueFByb3h5XG4pOiBib29sZWFuIHtcbiAgY29uc3QgeyBpZCB9ID0gbmF0aXZlQXBwO1xuICBjb25zdCB7IGNhcmRUeXBlIH0gPSBwYXJhbXM7XG4gIGFsb2coYGxvYWQgY2FyZCBuYXRpdmUgYXBwIGlkOiAke2lkfWApO1xuICBsZXQgbG9hZFN1Y2Nlc3M6IGJvb2xlYW4gPSB0cnVlO1xuICBsZXQgdHQ6IFJlYWN0QXBwIHwgU3RhbmRhbG9uZUFwcDtcbiAgdHJ5IHtcbiAgICBpZiAoY2FyZFR5cGUgPT0gJ3N0YW5kYWxvbmUnKSB7XG4gICAgICB0dCA9IG5ldyBTdGFuZGFsb25lQXBwKHsgbmF0aXZlQXBwLCBwYXJhbXMsIGx5bnggfSwgcGFyYW1zKTtcbiAgICB9IGVsc2Uge1xuICAgICAgdHQgPSBuZXcgUmVhY3RBcHAoe1xuICAgICAgICBuYXRpdmVBcHAsXG4gICAgICAgIHBhcmFtcyxcbiAgICAgICAgbHlueCxcbiAgICAgIH0pO1xuICAgIH1cbiAgICBuYXRpdmVHbG9iYWwuY3VycmVudEFwcElkID0gaWQ7XG4gICAgbmF0aXZlR2xvYmFsLm11bHRpQXBwc1tpZF0gPSB0dDtcblxuICAgIGlmIChjYXJkVHlwZSA9PT0gJ3N0YW5kYWxvbmUnKSB7XG4gICAgICBuYXRpdmVBcHAuc2V0Q2FyZCh0dCk7XG4gICAgICByZXR1cm4gdHJ1ZTtcbiAgICB9XG5cbiAgICBhbG9nKFxuICAgICAgYGxvYWQgY2FyZCBuYXRpdmUgYXBwIGxvYWQgYXBwLXNlcnZpY2UuanMgcGFyYW1zLmJ1bmRsZVN1cHBvcnRMb2FkU2NyaXB0ICR7cGFyYW1zLmJ1bmRsZVN1cHBvcnRMb2FkU2NyaXB0fWBcbiAgICApO1xuICAgIGxvYWRTdWNjZXNzID0gdHJ1ZTtcbiAgICB0cnkge1xuICAgICAgZGVsZXRlIHR0Lmx5bngucmVxdWlyZU1vZHVsZS5jYWNoZVtBUFBfU0VSVklDRV9OQU1FXTtcbiAgICAgIGRlbGV0ZSBCYXNlQXBwLl8kZmFjdG9yeUNhY2hlW0FQUF9TRVJWSUNFX05BTUVdO1xuICAgICAgdHQubHlueC5yZXF1aXJlTW9kdWxlKEFQUF9TRVJWSUNFX05BTUUsIERFRkFVTFRfRU5UUlkpO1xuICAgICAgaWYgKHR0Lmx5bnguX3N3aXRjaGVzWydhbGxvd1VuZGVmaW5lZEluTmF0aXZlRGF0YVR5cGVTZXQnXSkge1xuICAgICAgICB0dC5kYXRhVHlwZVNldC5hZGQoJ3VuZGVmaW5lZCcpO1xuICAgICAgfVxuICAgIH0gY2F0Y2ggKGUpIHtcbiAgICAgIGxvYWRTdWNjZXNzID0gZmFsc2U7XG4gICAgICB0dC5oYW5kbGVVc2VyRXJyb3IoZSwgdW5kZWZpbmVkLCB1bmRlZmluZWQsICdsb2FkQ2FyZCBmYWlsZWQnKTtcbiAgICB9XG4gICAgbmF0aXZlQXBwLnNldENhcmQodHQpO1xuICB9IGNhdGNoIChlKSB7XG4gICAgaGFuZGxlTG9hZENhcmRFcnJvcihuYXRpdmVBcHAsIGUpO1xuICAgIGxvYWRTdWNjZXNzID0gZmFsc2U7XG4gIH1cbiAgcmV0dXJuIGxvYWRTdWNjZXNzO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gZGVzdHJveUNhcmQoaWQ6IHN0cmluZyk6IHZvaWQge1xuICBhbG9nKGBkZXN0cm95ICR7aWR9YCk7XG4gIGNvbnN0IGFwcEluc3RhbmNlID0gbmF0aXZlR2xvYmFsLm11bHRpQXBwc1tpZF07XG4gIGFwcEluc3RhbmNlLmRlc3Ryb3koKTtcbiAgLy8gZXNsaW50LWRpc2FibGUtbmV4dC1saW5lIEB0eXBlc2NyaXB0LWVzbGludC9uby1keW5hbWljLWRlbGV0ZVxuICBkZWxldGUgbmF0aXZlR2xvYmFsLm11bHRpQXBwc1tpZF07XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBjYWxsRGVzdHJveUxpZmV0aW1lRnVuKGlkOiBzdHJpbmcpOiB2b2lkIHtcbiAgYWxvZyhgY2FsbERlc3Ryb3lMaWZldGltZUZ1biAke2lkfWApO1xuICBjb25zdCBhcHBJbnN0YW5jZSA9IG5hdGl2ZUdsb2JhbC5tdWx0aUFwcHNbaWRdO1xuICBhcHBJbnN0YW5jZS5jYWxsRGVzdHJveUxpZmV0aW1lRnVuKCk7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBsb2FkRHluYW1pY0NvbXBvbmVudDxUPih0dDogQmFzZUFwcCwgY29tcG9uZW50VXJsOiBzdHJpbmcpOiBUIHtcbiAgaWYgKHR0LmxvYWRlZER5bmFtaWNDb21wb25lbnRzU2V0Lmhhcyhjb21wb25lbnRVcmwpKSB7XG4gICAgcmV0dXJuIHR0LmdldER5bmFtaWNDb21wb25lbnRFeHBvcnRzKGNvbXBvbmVudFVybCk7XG4gIH1cblxuICBjb25zdCBwcmVFbnRyeSA9IG5hdGl2ZUdsb2JhbC5nbG9iRHluYW1pY0NvbXBvbmVudEVudHJ5O1xuICBuYXRpdmVHbG9iYWwuZ2xvYkR5bmFtaWNDb21wb25lbnRFbnRyeSA9IGNvbXBvbmVudFVybDtcblxuICB0cnkge1xuICAgIGRlbGV0ZSB0dC5seW54LnJlcXVpcmVNb2R1bGUuY2FjaGVbQVBQX1NFUlZJQ0VfTkFNRV07XG4gICAgZGVsZXRlIEJhc2VBcHAuXyRmYWN0b3J5Q2FjaGVbQVBQX1NFUlZJQ0VfTkFNRV07XG4gICAgY29uc3QgcmV0ID0gdHQubHlueC5yZXF1aXJlTW9kdWxlPFQ+KEFQUF9TRVJWSUNFX05BTUUsIGNvbXBvbmVudFVybCk7XG4gICAgdHQuc2F2ZUR5bmFtaWNDb21wb25lbnRFeHBvcnRzKGNvbXBvbmVudFVybCwgcmV0KTtcbiAgICB0dC5sb2FkZWREeW5hbWljQ29tcG9uZW50c1NldC5hZGQoY29tcG9uZW50VXJsKTtcbiAgICByZXR1cm4gcmV0O1xuICB9IGNhdGNoIChlcnJvcikge1xuICAgIHR0LmhhbmRsZVVzZXJFcnJvcihlcnJvcik7XG4gIH0gZmluYWxseSB7XG4gICAgLy8gSGVyZSByZXNldCBnbG9iRHluYW1pY0NvbXBvbmVudEVudHJ5IHRvIGF2b2lkIGFmZmVjdCBvdGhlciBMeW54VmlldyBpbiB0aGUgc2FtZSBMeW54R3JvdXBcbiAgICAvLyBkZXRhaWwgc2VlOiAjODcyMFxuICAgIG5hdGl2ZUdsb2JhbC5nbG9iRHluYW1pY0NvbXBvbmVudEVudHJ5ID0gcHJlRW50cnk7XG4gIH1cbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGhhbmRsZUxvYWRDYXJkRXJyb3IoXG4gIG5hdGl2ZUFwcDogTmF0aXZlQXBwLFxuICBlcnJvcj86IEVycm9yLFxuICBjYXVzZT86IHVua25vd25cbikge1xuICBsZXQgeyBtZXNzYWdlLCBuYW1lLCBzdGFjayB9ID0gZXJyb3IgfHwge307XG4gIGlmICghbWVzc2FnZSkge1xuICAgIC8vIElmIHRoZXJlIGlzIG5vIGVycm9yIG1lc3NhZ2UgaW4gZXJyb3IsIG1lYW5zIHRoYXQgaXQgaXMgbm90IGFuIGVycm9yLWxpa2Ugb2JqZWN0LlxuICAgIC8vIFdlIGNvbnN0cnVjdCBhIG5ldyBFcnJvciB1c2luZyBKU09OLnN0cmluZ2lmeVxuICAgICh7IG1lc3NhZ2UsIG5hbWUsIHN0YWNrIH0gPSBuZXcgRXJyb3IoSlNPTi5zdHJpbmdpZnkoZXJyb3IpKSk7XG4gIH1cbiAgY29uc3QgaW50ZXJuYWxFcnJvciA9IG5ldyBJbnRlcm5hbFJ1bnRpbWVFcnJvcihcbiAgICBgbG9hZENhcmQgZmFpbGVkICR7bmFtZX06ICR7bWVzc2FnZX1gLFxuICAgIHN0YWNrXG4gICk7XG4gIGludGVybmFsRXJyb3IuY2F1c2UgPSBjYXVzZTtcbiAgcmVwb3J0RXJyb3IoaW50ZXJuYWxFcnJvciwgbmF0aXZlQXBwLCB7XG4gICAgb3JpZ2luRXJyb3I6IGVycm9yLFxuICAgIGdldFNvdXJjZU1hcFJlbGVhc2U6ICh1cmw6IHN0cmluZyk6IHN0cmluZyA9PiB7XG4gICAgICBsZXQgcmV0ID0gbmF0aXZlQXBwLl9fR2V0U291cmNlTWFwUmVsZWFzZSh1cmwpO1xuICAgICAgaWYgKCFyZXQpIHtcbiAgICAgICAgcmV0dXJuIG5hdGl2ZUFwcC5fX0dldFNvdXJjZU1hcFJlbGVhc2UoQmFzZUFwcC5rRGVmYXVsdFNvdXJjZU1hcFVSTCk7XG4gICAgICB9XG4gICAgfSxcbiAgfSk7XG59XG5cbi8qKlxuICogQ2FsbHMgYSBjYWxsYmFjayBmdW5jdGlvbiBvZiB0aGUgc3BlY2lmaWVkIGFwcGxpY2F0aW9uIGluc3RhbmNlXG4gKiBAcGFyYW0gaW5zdGFuY2VJZCBBcHBsaWNhdGlvbiBpbnN0YW5jZSBJRFxuICogQHBhcmFtIG1ldGhvZE5hbWUgZnVuY3Rpb24gbmFtZVxuICogQHBhcmFtIGFyZ3MgQXJndW1lbnRzIHRvIHBhc3MgdG8gdGhlIGNhbGxiYWNrIGZ1bmN0aW9uIChvcHRpb25hbClcbiAqL1xuZXhwb3J0IGZ1bmN0aW9uIF9faW52b2tlQXBwTWV0aG9kKFxuICBpbnN0YW5jZUlkOiBzdHJpbmcsXG4gIG1ldGhvZE5hbWU6IHN0cmluZyxcbiAgLi4uYXJnczogdW5rbm93bltdXG4pOiB2b2lkIHtcbiAgY29uc3QgYXBwSW5zdGFuY2UgPSBuYXRpdmVHbG9iYWwubXVsdGlBcHBzW2luc3RhbmNlSWRdO1xuICBpZiAoIWFwcEluc3RhbmNlKSB7XG4gICAgY29uc29sZS5lcnJvcihgY2FsbENhbGxiYWNrOiBBcHAgaW5zdGFuY2Ugbm90IGZvdW5kIGZvciBJRCAke2luc3RhbmNlSWR9YCk7XG4gICAgcmV0dXJuO1xuICB9XG4gIGlmICh0eXBlb2YgYXBwSW5zdGFuY2VbbWV0aG9kTmFtZV0gPT09ICdmdW5jdGlvbicpIHtcbiAgICBhcHBJbnN0YW5jZVttZXRob2ROYW1lXSguLi5hcmdzKTtcbiAgfVxufVxuIiwgIi8qKlxuICogQHNlZTogaHR0cHM6Ly9kZXZlbG9wZXIuYXBwbGUuY29tL2RvY3VtZW50YXRpb24vamF2YXNjcmlwdGNvcmUvMTY0NDU5OC1qc29iamVjdG1ha2V0eXBlZGFycmF5d2l0aGFycmF5YlxuICogQGRlc2NyaXB0aW9uOiBKYXZhU2NyaXB0IENvcmUgcHJvdmlkZSBBcnJheUJ1ZmZlciBBUEkgSW4gSlNSdW50aW1lLiBCdXQgZGlkIG5vdCBleHBvcnQgc29tZSBjLWFwaSBvbiBpT1M5LlxuICovXG5cbi8vIGJhc2U2NCBjaGFyYWN0ZXIgc2V0LCBwbHVzIHBhZGRpbmcgY2hhcmFjdGVyICg9KVxuY29uc3QgY2hhcnMgPVxuICAnQUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ejAxMjM0NTY3ODkrLyc7XG4vLyBSZWd1bGFyIGV4cHJlc3Npb24gdG8gY2hlY2sgZm9ybWFsIGNvcnJlY3RuZXNzIG9mIGJhc2U2NCBlbmNvZGVkIHN0cmluZ3NcbmNvbnN0IGxvb2t1cCA9IG5ldyBVaW50OEFycmF5KDI1Nik7XG5mb3IgKGxldCBpID0gMDsgaSA8IGNoYXJzLmxlbmd0aDsgaSsrKSB7XG4gIGxvb2t1cFtjaGFycy5jaGFyQ29kZUF0KGkpXSA9IGk7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBhcnJheUJ1ZmZlclRvQmFzZTY0KGJ1ZmZlcjogQXJyYXlCdWZmZXIpOiBzdHJpbmcge1xuICB2YXIgYnl0ZXMgPSBuZXcgVWludDhBcnJheShidWZmZXIpO1xuICB2YXIgaTogbnVtYmVyO1xuICB2YXIgbGVuOiBudW1iZXIgPSBieXRlcy5sZW5ndGg7XG4gIHZhciBiYXNlNjQgPSAnJztcblxuICBmb3IgKGkgPSAwOyBpIDwgbGVuOyBpICs9IDMpIHtcbiAgICBiYXNlNjQgKz0gY2hhcnNbYnl0ZXNbaV0gPj4gMl07XG4gICAgYmFzZTY0ICs9IGNoYXJzWygoYnl0ZXNbaV0gJiAzKSA8PCA0KSB8IChieXRlc1tpICsgMV0gPj4gNCldO1xuICAgIGJhc2U2NCArPSBjaGFyc1soKGJ5dGVzW2kgKyAxXSAmIDE1KSA8PCAyKSB8IChieXRlc1tpICsgMl0gPj4gNildO1xuICAgIGJhc2U2NCArPSBjaGFyc1tieXRlc1tpICsgMl0gJiA2M107XG4gIH1cblxuICBpZiAobGVuICUgMyA9PT0gMikge1xuICAgIGJhc2U2NCA9IGJhc2U2NC5zdWJzdHJpbmcoMCwgYmFzZTY0Lmxlbmd0aCAtIDEpICsgJz0nO1xuICB9IGVsc2UgaWYgKGxlbiAlIDMgPT09IDEpIHtcbiAgICBiYXNlNjQgPSBiYXNlNjQuc3Vic3RyaW5nKDAsIGJhc2U2NC5sZW5ndGggLSAyKSArICc9PSc7XG4gIH1cblxuICByZXR1cm4gYmFzZTY0O1xufVxuXG5leHBvcnQgZnVuY3Rpb24gYmFzZTY0VG9BcnJheUJ1ZmZlcihiYXNlNjQ6IHN0cmluZyk6IEFycmF5QnVmZmVyIHtcbiAgbGV0IGJ1ZmZlckxlbmd0aDogbnVtYmVyID0gYmFzZTY0Lmxlbmd0aCAqIDAuNzU7XG4gIGNvbnN0IGxlbjogbnVtYmVyID0gYmFzZTY0Lmxlbmd0aDtcbiAgbGV0IGk7XG4gIGxldCBwID0gMDtcbiAgbGV0IGVuY29kZWQxO1xuICBsZXQgZW5jb2RlZDI7XG4gIGxldCBlbmNvZGVkMztcbiAgbGV0IGVuY29kZWQ0O1xuXG4gIGlmIChiYXNlNjRbYmFzZTY0Lmxlbmd0aCAtIDFdID09PSAnPScpIHtcbiAgICBidWZmZXJMZW5ndGgtLTtcbiAgICBpZiAoYmFzZTY0W2Jhc2U2NC5sZW5ndGggLSAyXSA9PT0gJz0nKSB7XG4gICAgICBidWZmZXJMZW5ndGgtLTtcbiAgICB9XG4gIH1cblxuICBsZXQgYXJyYXlidWZmZXIgPSBuZXcgQXJyYXlCdWZmZXIoYnVmZmVyTGVuZ3RoKTtcbiAgbGV0IGJ5dGVzID0gbmV3IFVpbnQ4QXJyYXkoYXJyYXlidWZmZXIpO1xuXG4gIGZvciAoaSA9IDA7IGkgPCBsZW47IGkgKz0gNCkge1xuICAgIGVuY29kZWQxID0gbG9va3VwW2Jhc2U2NC5jaGFyQ29kZUF0KGkpXTtcbiAgICBlbmNvZGVkMiA9IGxvb2t1cFtiYXNlNjQuY2hhckNvZGVBdChpICsgMSldO1xuICAgIGVuY29kZWQzID0gbG9va3VwW2Jhc2U2NC5jaGFyQ29kZUF0KGkgKyAyKV07XG4gICAgZW5jb2RlZDQgPSBsb29rdXBbYmFzZTY0LmNoYXJDb2RlQXQoaSArIDMpXTtcblxuICAgIGJ5dGVzW3ArK10gPSAoZW5jb2RlZDEgPDwgMikgfCAoZW5jb2RlZDIgPj4gNCk7XG4gICAgYnl0ZXNbcCsrXSA9ICgoZW5jb2RlZDIgJiAxNSkgPDwgNCkgfCAoZW5jb2RlZDMgPj4gMik7XG4gICAgYnl0ZXNbcCsrXSA9ICgoZW5jb2RlZDMgJiAzKSA8PCA2KSB8IChlbmNvZGVkNCAmIDYzKTtcbiAgfVxuXG4gIHJldHVybiBhcnJheWJ1ZmZlcjtcbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuaW1wb3J0IHtcbiAgbG9hZENhcmQsXG4gIGRlc3Ryb3lDYXJkLFxuICBjYWxsRGVzdHJveUxpZmV0aW1lRnVuLFxuICBsb2FkRHluYW1pY0NvbXBvbmVudCxcbiAgX19pbnZva2VBcHBNZXRob2QsXG59IGZyb20gJy4vYXBwTWFuYWdlcic7XG5pbXBvcnQgeyBhcnJheUJ1ZmZlclRvQmFzZTY0LCBiYXNlNjRUb0FycmF5QnVmZmVyIH0gZnJvbSAnLi9wb2x5ZmlsbCc7XG5pbXBvcnQgbmF0aXZlR2xvYmFsIGZyb20gJy4vY29tbW9uL25hdGl2ZUdsb2JhbCc7XG5pbXBvcnQge1xuICBjcmVhdGVFdmVudEVtaXR0ZXIsXG4gIGxlZ2FjeVJlcG9ydEVycm9yLFxuICB3cmFwSW5uZXJGdW5jdGlvbixcbiAgd3JhcFVzZXJGdW5jdGlvbixcbn0gZnJvbSAnLi9tb2R1bGVzJztcbmltcG9ydCB7XG4gIEhlYWRlcnMsXG4gIFVSTCxcbiAgVVJMU2VhcmNoUGFyYW1zUG9seWZpbGwsXG4gIEFib3J0Q29udHJvbGxlcixcbiAgQWJvcnRTaWduYWwsXG4gIFRleHRFbmNvZGVyLFxuICBUZXh0RGVjb2Rlcixcbn0gZnJvbSAnLi9tb2R1bGVzL2ZldGNoJztcblxuZXhwb3J0IHsgbG9hZENhcmQsIGRlc3Ryb3lDYXJkLCBjYWxsRGVzdHJveUxpZmV0aW1lRnVuLCBsb2FkRHluYW1pY0NvbXBvbmVudCB9O1xuXG5uYXRpdmVHbG9iYWwubG9hZENhcmQgPSBsb2FkQ2FyZDtcbm5hdGl2ZUdsb2JhbC5kZXN0cm95Q2FyZCA9IGRlc3Ryb3lDYXJkO1xubmF0aXZlR2xvYmFsLmNhbGxEZXN0cm95TGlmZXRpbWVGdW4gPSBjYWxsRGVzdHJveUxpZmV0aW1lRnVuO1xubmF0aXZlR2xvYmFsLmxvYWREeW5hbWljQ29tcG9uZW50ID0gbG9hZER5bmFtaWNDb21wb25lbnQ7XG4vKipcbiAqIG9ubHkgZm9yIGx5bnggbmF0aXZlIHJ1bnRpbWVcbiAqL1xubmF0aXZlR2xvYmFsLl9fY3JlYXRlRXZlbnRFbWl0dGVyID0gY3JlYXRlRXZlbnRFbWl0dGVyO1xubmF0aXZlR2xvYmFsLl9fbHlueEFycmF5QnVmZmVyVG9CYXNlNjQgPSBhcnJheUJ1ZmZlclRvQmFzZTY0O1xubmF0aXZlR2xvYmFsLl9fbHlueEJhc2U2NFRvQXJyYXlCdWZmZXIgPSBiYXNlNjRUb0FycmF5QnVmZmVyO1xubmF0aXZlR2xvYmFsLkx5bnhTREtDb3JlID0ge1xuICByZXBvcnQ6IGxlZ2FjeVJlcG9ydEVycm9yLFxuICByZXBvcnRJbm5lcjogd3JhcElubmVyRnVuY3Rpb24sXG4gIHJlcG9ydFVzZXI6IHdyYXBVc2VyRnVuY3Rpb24sXG59O1xuXG5uYXRpdmVHbG9iYWwuSGVhZGVycyA9IEhlYWRlcnM7XG5uYXRpdmVHbG9iYWwuQWJvcnRDb250cm9sbGVyID0gQWJvcnRDb250cm9sbGVyO1xubmF0aXZlR2xvYmFsLkFib3J0U2lnbmFsID0gQWJvcnRTaWduYWw7XG5uYXRpdmVHbG9iYWwuVVJMID0gVVJMO1xuVVJMU2VhcmNoUGFyYW1zUG9seWZpbGwobmF0aXZlR2xvYmFsKTtcbm5hdGl2ZUdsb2JhbC5fX2ludm9rZUFwcE1ldGhvZCA9IF9faW52b2tlQXBwTWV0aG9kO1xuIl0sCiAgIm1hcHBpbmdzIjogIjs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7O0FBQUE7QUFBQSwyQ0FBQUEsU0FBQTtBQUFBO0FBd0JBLGVBQVNDLFFBQU87QUFBQSxNQUFDO0FBa0JqQixVQUFJLGFBQWE7QUFDakIsVUFBSSxXQUFXLENBQUM7QUFDaEIsZUFBUyxRQUFRLEtBQUs7QUFDcEIsWUFBSTtBQUNGLGlCQUFPLElBQUk7QUFBQSxRQUNiLFNBQVMsSUFBSTtBQUNYLHVCQUFhO0FBQ2IsaUJBQU87QUFBQSxRQUNUO0FBQUEsTUFDRjtBQUVBLGVBQVMsV0FBVyxJQUFJLEdBQUc7QUFDekIsWUFBSTtBQUNGLGlCQUFPLEdBQUcsQ0FBQztBQUFBLFFBQ2IsU0FBUyxJQUFJO0FBQ1gsdUJBQWE7QUFDYixpQkFBTztBQUFBLFFBQ1Q7QUFBQSxNQUNGO0FBQ0EsZUFBUyxXQUFXLElBQUksR0FBRyxHQUFHO0FBQzVCLFlBQUk7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R0FBRyxJQUFLLFlBQVksSUFBTSxZQUFZO0FBQzVDLFlBQU0sR0FBRyxLQUFNLFdBQVcsT0FBTyxJQUFNLFlBQVk7QUFDbkQsWUFBTSxHQUFHLEtBQU0sV0FBVyxNQUFNLElBQU0sV0FBVztBQUFBLElBQ25EO0FBRUEsV0FBTztBQUFBLEVBQ1Q7OztBQ3RDQSxFQUFBQyxzQkFBYSxXQUFXO0FBQ3hCLEVBQUFBLHNCQUFhLGNBQWM7QUFDM0IsRUFBQUEsc0JBQWEseUJBQXlCO0FBQ3RDLEVBQUFBLHNCQUFhLHVCQUF1QjtBQUlwQyxFQUFBQSxzQkFBYSx1QkFBdUI7QUFDcEMsRUFBQUEsc0JBQWEsNEJBQTRCO0FBQ3pDLEVBQUFBLHNCQUFhLDRCQUE0QjtBQUN6QyxFQUFBQSxzQkFBYSxjQUFjO0FBQUEsSUFDekIsUUFBUTtBQUFBLElBQ1IsYUFBYTtBQUFBLElBQ2IsWUFBWTtBQUFBLEVBQ2Q7QUFFQSxFQUFBQSxzQkFBYSxVQUFVQztBQUN2QixFQUFBRCxzQkFBYSxrQkFBa0I7QUFDL0IsRUFBQUEsc0JBQWEsY0FBYztBQUMzQixFQUFBQSxzQkFBYSxNQUFNO0FBQ25CLDBCQUF3QkEscUJBQVk7QUFDcEMsRUFBQUEsc0JBQWEsb0JBQW9COyIsCiAgIm5hbWVzIjogWyJtb2R1bGUiLCAibm9vcCIsICJQcm9taXNlIiwgInJlc29sdmUiLCAicmVqZWN0IiwgIm1vZHVsZSIsICJQcm9taXNlIiwgImkiLCAidmFsIiwgIm1vZHVsZSIsICJQcm9taXNlIiwgInNldFRpbWVvdXQiLCAiaWQiLCAibW9kdWxlIiwgInNldFRpbWVvdXQiLCAiUHJvbWlzZSIsICJtb2R1bGUiLCAiZXhwb3J0cyIsICJ1bmRlZmluZWQiLCAidmFsdWUiLCAia2V5IiwgIm5leHQiLCAiZ2xvYmFsVGhpcyIsICJpbXBvcnRfcnVudGltZSIsICJfZ2xvYmFsIiwgInR0Q29uc29sZV9kZWZhdWx0IiwgInR0Q29uc29sZV9kZWZhdWx0IiwgIm5hdGl2ZUdsb2JhbF9kZWZhdWx0IiwgInR0Q29uc29sZV9kZWZhdWx0IiwgInR0Q29uc29sZV9kZWZhdWx0IiwgImVycm9yIiwgInR0Q29uc29sZV9kZWZhdWx0IiwgIl9hIiwgInBhcmFtcyIsICJQcm9taXNlIiwgIkhlYWRlcnMiLCAiX2EiLCAiSGVhZGVycyIsICJfYSIsICJVUkxTZWFyY2hQYXJhbXNQb2x5ZmlsbCIsICJfYSIsICJfYiIsICJfYSIsICJQcm9taXNlIiwgInBhdGgiLCAiZW50cnlOYW1lIiwgIm1vZHVsZSIsICJuYXRpdmVHbG9iYWxfZGVmYXVsdCIsICJwYXJhbXMiLCAiZW50cnlOYW1lIiwgIkxpc3RlbmVyS2V5cyIsICJuYXRpdmVHbG9iYWxfZGVmYXVsdCIsICJzZXRUaW1lb3V0IiwgIm5hdGl2ZUdsb2JhbF9kZWZhdWx0IiwgIl9hIiwgIl9iIiwgIm5hdGl2ZUdsb2JhbF9kZWZhdWx0IiwgInBhcmFtcyIsICJ0aGF0IiwgIm1vZHVsZSIsICJQcm9taXNlIiwgInBhdGgiLCAiZW50cnlOYW1lIiwgInR0IiwgInNldFRpbWVvdXQiLCAiX2MiLCAicGFyYW1zIiwgInBhcmFtcyIsICJ0dCIsICJuYXRpdmVHbG9iYWxfZGVmYXVsdCIsICJuYXRpdmVHbG9iYWxfZGVmYXVsdCIsICJIZWFkZXJzIl0KfQo=
