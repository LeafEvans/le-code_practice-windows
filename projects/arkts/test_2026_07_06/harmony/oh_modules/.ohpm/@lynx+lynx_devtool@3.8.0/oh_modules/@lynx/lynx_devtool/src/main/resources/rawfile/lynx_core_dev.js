/** build time: Tue, 26 May 2026 10:26:03 GMT, commit: bd80d7adbe313d489f742d4503f39bb5460cc413 */
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
    slot: "bd80d7adbe313d489f742d4503f39bb5460cc413",
    release: "3.8.0"
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
  nativeGlobal_default.getNapiLoader = () => {
    return nativeGlobal_default.__lynxNapiLoader;
  };
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
        buildVersion: "3.8.0",
        versionCode: "3.8.0",
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
      this._enableFetchAPIStandardStreaming = false;
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
    setBody(body, enableFetchAPIStandardStreaming) {
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
          this._enableFetchAPIStandardStreaming = enableFetchAPIStandardStreaming;
        }
      }
    }
    async arrayBuffer() {
      if (this._enableFetchAPIStandardStreaming && this._bodyStream != null) {
        const buffer = await this.consumeStream();
        if (buffer === null) {
          return new ArrayBuffer(0);
        }
        return buffer;
      } else {
        return Promise.resolve(this.safeUseBody((body) => body));
      }
    }
    get body() {
      if (this._bodyUsed) {
        throw new Error("body used");
      }
      this._bodyUsed = true;
      return this._bodyStream;
    }
    async text() {
      if (this._enableFetchAPIStandardStreaming && this._bodyStream != null) {
        const buffer = await this.consumeStream();
        if (buffer === null) {
          return "";
        }
        return new TextDecoder().decode(buffer);
      } else {
        const result = await this.safeUseBody(
          (body) => new TextDecoder().decode(body)
        );
        return result;
      }
    }
    async json() {
      if (this._enableFetchAPIStandardStreaming && this._bodyStream != null) {
        const buffer = await this.consumeStream();
        if (buffer === null) {
          return null;
        }
        const text = new TextDecoder().decode(buffer);
        return JSON.parse(text);
      } else {
        const result = this.safeUseBody((body) => new TextDecoder().decode(body));
        return Promise.resolve(result).then((text) => JSON.parse(text));
      }
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
    async getArrayBufferOfStreaming() {
      const chunks = [];
      let totalLength = 0;
      const reader = this._bodyStream.getReader();
      {
        while (true) {
          const { done, value } = await reader.read();
          if (done) {
            break;
          }
          chunks.push(new Uint8Array(value));
          totalLength += value.byteLength;
        }
        const finalBuffer = new Uint8Array(totalLength);
        let offset = 0;
        for (const chunk of chunks) {
          finalBuffer.set(chunk, offset);
          offset += chunk.byteLength;
        }
        return finalBuffer.buffer;
      }
    }
    async consumeStream() {
      if (this._bodyUsed) {
        return null;
      }
      this._bodyUsed = true;
      return await this.getArrayBufferOfStreaming();
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
    constructor(bodyInit, options, enableFetchAPIStandardStreaming) {
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
      this.setBody(bodyInit, enableFetchAPIStandardStreaming);
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
        this.getNativeApp().setTimeout,
        "setTimeout Error"
      );
      this.setInterval = this.getApp().wrapReport(
        this.getNativeApp().setInterval,
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
          var _a3, _b2;
          const request = new nativeGlobal_default2.Request(input, init);
          const signal = request.signal;
          if (signal.aborted) {
            return reject(signal.reason);
          }
          signal.addEventListener("abort", (event) => {
            reject(signal.reason);
          });
          const enableFetchAPIStandardStreaming = (_b2 = (_a3 = this.getApp().params) ==
          null ? void 0 : _a3.pageConfigSubset) == null ? void 0 : _b2.enableFetchAPIStandardStreaming;
          request.lynxExtension["enableFetchAPIStandardStreaming"] = enableFetchAPIStandardStreaming;
          const fetchArg = {
            method: request.method,
            url: request.url,
            origin: this.getNativeApp().__pageUrl,
            headers: Object.fromEntries(request.headers.entries()),
            body: request._arrayBuffer,
            lynxExtension: request.lynxExtension
          };
          const useStreaming = request.lynxExtension["useStreaming"] || enableFetchAPIStandardStreaming;
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
                  response,
                  enableFetchAPIStandardStreaming
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
      this.getNativeLynx().queueMicrotask(callback);
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
    constructor(options, otherApp) {
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
      this.initWithReusedApp(options, otherApp);
      this.addInternalEventListeners();
      nativeGlobal_default2["notifyRuntimeReadyOnRT" + this.nativeAppId] && nativeGlobal_default2["\
notifyRuntimeReadyOnRT" + this.nativeAppId](this.lynx);
    }
    initWithReusedApp(options, otherApp) {
      if (otherApp) {
        this._nativeApp = otherApp.nativeApp;
        this.sharedConsole = otherApp.sharedConsole;
        this.dynamicComponentExports = otherApp.dynamicComponentExports;
        this.loadedDynamicComponentsSet = otherApp.loadedDynamicComponentsSet;
        this._apiList = otherApp._apiList;
        this._intersectionObserverManager = otherApp._intersectionObserverManager;
        this._exposureManager = otherApp._exposureManager;
        this._textInfoManager = otherApp._textInfoManager;
        otherApp.GlobalEventEmitter.setCallLynxSetModule(
          this.__internal__callLynxSetModule.bind(this)
        );
        this.GlobalEventEmitter = otherApp.GlobalEventEmitter;
        this._aopManager = otherApp._aopManager;
        this.performance = otherApp.performance;
        this.modules = otherApp.modules;
        this._lazyCallableModules = otherApp._lazyCallableModules;
        otherApp.lynx.rebind(() => this);
        this.lynx = otherApp.lynx;
        otherApp.Reporter.rebind(() => this);
        this.Reporter = otherApp.Reporter;
        this.setTimeout = otherApp.setTimeout;
        this.setInterval = otherApp.setInterval;
        this.clearInterval = otherApp.clearInterval;
        this.clearTimeout = otherApp.clearTimeout;
        this.resolvedPromise = otherApp.resolvedPromise;
        this._createReadableStreamClass = otherApp._createReadableStreamClass;
        this._ReadableStreamClass = otherApp._ReadableStreamClass;
      } else {
        const { lynx } = options;
        this.setTimeout = this.nativeApp.setTimeout;
        this.setInterval = this.nativeApp.setInterval;
        this.clearInterval = this.nativeApp.clearInterval;
        this.clearTimeout = this.nativeApp.clearTimeout;
        this.modules = {};
        this._apiList = {};
        this._textInfoManager = new TextInfoManager(this.NativeModules);
        this.setupGetTextInfoApi();
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
        this.performance = new performance_default(
          this.GlobalEventEmitter,
          this.nativeApp
        );
        const promiseCtor = this.setupPromise(
          this.nativeApp.setTimeout,
          this.nativeApp.clearTimeout,
          lynx
        );
        this.lynx = this.createLynx(lynx, promiseCtor);
        this.setupJSModule();
        this.setupIntersectionApi();
        this.setupFetchAPI(promiseCtor);
      }
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
    destroy() {
      this.__removeInternalEventListeners();
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
    handleUserError(error, outerCause, errorLevel, prefix) {
      let { message, name, stack, cause } = error || {};
      if (!message) {
        ({ message, name, stack } = new Error(JSON.stringify(error)));
      }
      cause = cause != null ? cause : outerCause;
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
    setupPromise(setTimeout2, clearTimeout, lynx) {
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
        lynx.queueMicrotask,
        (_c2 = (_b2 = (_a3 = this._params) == null ? void 0 : _a3.pageConfigSubset) ==
        null ? void 0 : _b2.enableMicrotaskPromisePolyfill) != null ? _c2 : false
      );
      this.resolvedPromise = PromiseConstructor.resolve();
      return PromiseConstructor;
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
  var StandaloneApp = class extends BaseApp {
    constructor(options, params2) {
      super(options, void 0);
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
  };

  // src/appManager.ts
  function loadCard(nativeApp, params2, lynx) {
    var _a3;
    const { id } = nativeApp;
    const { cardType } = params2;
    alog(`load card native app id: ${id}`);
    let loadSuccess = true;
    let tt2;
    try {
      if (cardType == "standalone") {
        tt2 = new StandaloneApp({ nativeApp, params: params2, lynx }, params2);
      } else {
        tt2 = new ReactApp(
          {
            nativeApp,
            params: params2,
            lynx
          },
          (_a3 = nativeGlobal_default2) == null ? void 0 : _a3.multiApps[id]
        );
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
})();
//# sourceMappingURL=data:application/json;base64,ewogICJ2ZXJzaW9uIjogMywKICAic291cmNlcyI6IFsiLi4vLi4vbHlueC1wcm9taXNlL3NyYy9jb3JlLmpzIiwgIi4uLy4uL2x5bngtcHJvbWlzZS9zcmMvZXM2LWV4dGVuc2lvbnMuanMiLCAiLi4vLi4vbHlueC1wcm9taXNlL3NyYy9yZWplY3Rpb24tdHJhY2tpbmcuanMiLCAiLi4vLi4vbHlueC1wcm9taXNlL3NyYy9pbmRleC5qcyIsICIuLi8uLi8uLi9ub2RlX21vZHVsZXMvLnBucG0vcmVnZW5lcmF0b3ItcnVudGltZUAwLjEzLjcvbm9kZV9tb2R1bGVzL3JlZ2VuZXJhdG9yLXJ1bnRpbWUvcnVudGltZS5qcyIsICIuLi9rZXJuZWwtYnVpbGQvYW5kcm9pZC1wb2x5ZmlsbC5qcyIsICIuLi9zcmMvaW5kZXguYnVpbGQudHMiLCAiLi4vLi4vbHlueC1ydW50aW1lLXNoYXJlZC9zcmMvbmF0aXZlR2xvYmFsLnRzIiwgIi4uLy4uL2x5bngtcnVudGltZS1zaGFyZWQvc3JjL3R0Q29uc29sZS50cyIsICIuLi8uLi9seW54LXJ1bnRpbWUtc2hhcmVkL3NyYy91dGlscy50cyIsICIuLi9zcmMvY29tbW9uL3R0Q29uc29sZS50cyIsICIuLi9zcmMvbW9kdWxlcy9yZXBvcnQvZXJyb3JzLnRzIiwgIi4uL3NyYy9jb21tb24vY29uc3RhbnRzLnRzIiwgIi4uL3NyYy9tb2R1bGVzL3NoYXJlZERhdGEvU2hhcmVEYXRhU3ViamVjdC50cyIsICIuLi9zcmMvY29tbW9uL25hdGl2ZUdsb2JhbC50cyIsICIuLi9zcmMvY29tbW9uL2xvZy50cyIsICIuLi9zcmMvY29tbW9uL3ZlcnNpb24udHMiLCAiLi4vc3JjL21vZHVsZXMvcmVwb3J0L3JlcG9ydC1lcnJvci50cyIsICIuLi9zcmMvbW9kdWxlcy9yZXBvcnQvd3JhcHBlci50cyIsICIuLi9zcmMvbW9kdWxlcy9yZXBvcnQvcmVwb3J0ZXIudHMiLCAiLi4vc3JjL21vZHVsZXMvYW5pbWF0aW9uL2FuaW1hdGlvbi50cyIsICIuLi9zcmMvbW9kdWxlcy9hbmltYXRpb24vZWZmZWN0LnRzIiwgIi4uL3NyYy9tb2R1bGVzL2FuaW1hdGlvbi9hbmltYXRpb25WMi50cyIsICIuLi9zcmMvbW9kdWxlcy9lbGVtZW50L2VsZW1lbnQudHMiLCAiLi4vc3JjL21vZHVsZXMvZWxlbWVudC9pbmRleC50cyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9UZXh0RGVjb2Rlci50cyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9UZXh0RW5jb2Rlci50cyIsICIuLi9zcmMvbW9kdWxlcy9ldmVudC9ldmVudEVtaXR0ZXIudHMiLCAiLi4vc3JjL21vZHVsZXMvZXZlbnQvYW9wLnRzIiwgIi4uL3NyYy9tb2R1bGVzL2V2ZW50L2luZGV4LnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL1JlYWRhYmxlU3RyZWFtLnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL0JvZHlNaXhpbi50cyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9IZWFkZXJzLnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL0Fib3J0Q29udHJvbGxlci50cyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9SZXF1ZXN0LnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL1Jlc3BvbnNlLnRzIiwgIi4uL3NyYy9tb2R1bGVzL2ZldGNoL1VSTC5qcyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9VcmxTZWFyY2hQYXJhbXNQb2x5ZmlsbC5qcyIsICIuLi9zcmMvbW9kdWxlcy9mZXRjaC9FdmVudFNvdXJjZS50cyIsICIuLi9zcmMvbW9kdWxlcy9zZWxlY3RvclF1ZXJ5L1NlbGVjdG9yUXVlcnkudHMiLCAiLi4vc3JjL2x5bngvbHlueC50cyIsICIuLi9zcmMvbW9kdWxlcy9uYXRpdmVNb2R1bGVzL3RleHRJbmZvLnRzIiwgIi4uL3NyYy9tb2R1bGVzL25hdGl2ZU1vZHVsZXMvZXhwb3N1cmUudHMiLCAiLi4vc3JjL21vZHVsZXMvbmF0aXZlTW9kdWxlcy9pbnRlcnNlY3Rpb25PYnNlcnZlci50cyIsICIuLi9zcmMvbW9kdWxlcy9wZXJmb3JtYW5jZS9wZXJmb3JtYW5jZU9ic2VydmVyLnRzIiwgIi4uL3NyYy9tb2R1bGVzL3BlcmZvcm1hbmNlL3BlcmZvcm1hbmNlLnRzIiwgIi4uL3NyYy9tb2R1bGVzL3BlcmZvcm1hbmNlL2luZGV4LnRzIiwgIi4uL3NyYy9jb21tb24vanNiaS50cyIsICIuLi9zcmMvdXRpbC9jYWNoZWRGdW5jdGlvblByb3h5LnRzIiwgIi4uL3NyYy91dGlsL3NldHVwLXByb21pc2UudHMiLCAiLi4vc3JjL3V0aWwvVHJhY2VFdmVudERlZi50cyIsICIuLi9zcmMvYXBwL2FwcC50cyIsICIuLi9zcmMvcmVhY3QvcmVhY3RBcHAudHMiLCAiLi4vc3JjL3N0YW5kYWxvbmUvU3RhbmRhbG9uZUFwcC50cyIsICIuLi9zcmMvYXBwTWFuYWdlci50cyIsICIuLi9zcmMvcG9seWZpbGwvYXJyYXlidWZmZXIudHMiLCAiLi4vc3JjL2luZGV4LmNhcmQudHMiXSwKICAic291cmNlc0NvbnRlbnQiOiBbIi8qKlxuICogQGxpY2Vuc2VcbkNvcHlyaWdodCAoYykgMjAxNCBGb3JiZXMgTGluZGVzYXlcblxuUGVybWlzc2lvbiBpcyBoZXJlYnkgZ3JhbnRlZCwgZnJlZSBvZiBjaGFyZ2UsIHRvIGFueSBwZXJzb24gb2J0YWluaW5nIGEgY29weVxub2YgdGhpcyBzb2Z0d2FyZSBhbmQgYXNzb2NpYXRlZCBkb2N1bWVudGF0aW9uIGZpbGVzICh0aGUgXCJTb2Z0d2FyZVwiKSwgdG8gZGVhbFxuaW4gdGhlIFNvZnR3YXJlIHdpdGhvdXQgcmVzdHJpY3Rpb24sIGluY2x1ZGluZyB3aXRob3V0IGxpbWl0YXRpb24gdGhlIHJpZ2h0c1xudG8gdXNlLCBjb3B5LCBtb2RpZnksIG1lcmdlLCBwdWJsaXNoLCBkaXN0cmlidXRlLCBzdWJsaWNlbnNlLCBhbmQvb3Igc2VsbFxuY29waWVzIG9mIHRoZSBTb2Z0d2FyZSwgYW5kIHRvIHBlcm1pdCBwZXJzb25zIHRvIHdob20gdGhlIFNvZnR3YXJlIGlzXG5mdXJuaXNoZWQgdG8gZG8gc28sIHN1YmplY3QgdG8gdGhlIGZvbGxvd2luZyBjb25kaXRpb25zOlxuXG5UaGUgYWJvdmUgY29weXJpZ2h0IG5vdGljZSBhbmQgdGhpcyBwZXJtaXNzaW9uIG5vdGljZSBzaGFsbCBiZSBpbmNsdWRlZCBpblxuYWxsIGNvcGllcyBvciBzdWJzdGFudGlhbCBwb3J0aW9ucyBvZiB0aGUgU29mdHdhcmUuXG5cblRIRSBTT0ZUV0FSRSBJUyBQUk9WSURFRCBcIkFTIElTXCIsIFdJVEhPVVQgV0FSUkFOVFkgT0YgQU5ZIEtJTkQsIEVYUFJFU1MgT1JcbklNUExJRUQsIElOQ0xVRElORyBCVVQgTk9UIExJTUlURUQgVE8gVEhFIFdBUlJBTlRJRVMgT0YgTUVSQ0hBTlRBQklMSVRZLFxuRklUTkVTUyBGT1IgQSBQQVJUSUNVTEFSIFBVUlBPU0UgQU5EIE5PTklORlJJTkdFTUVOVC4gSU4gTk8gRVZFTlQgU0hBTEwgVEhFXG5BVVRIT1JTIE9SIENPUFlSSUdIVCBIT0xERVJTIEJFIExJQUJMRSBGT1IgQU5ZIENMQUlNLCBEQU1BR0VTIE9SIE9USEVSXG5MSUFCSUxJVFksIFdIRVRIRVIgSU4gQU4gQUNUSU9OIE9GIENPTlRSQUNULCBUT1JUIE9SIE9USEVSV0lTRSwgQVJJU0lORyBGUk9NLFxuT1VUIE9GIE9SIElOIENPTk5FQ1RJT04gV0lUSCBUSEUgU09GVFdBUkUgT1IgVEhFIFVTRSBPUiBPVEhFUiBERUFMSU5HUyBJTlxuVEhFIFNPRlRXQVJFLlxuICovXG4ndXNlIHN0cmljdCc7XG5cbmZ1bmN0aW9uIG5vb3AoKSB7fVxuXG4vLyBTdGF0ZXM6XG4vL1xuLy8gMCAtIHBlbmRpbmdcbi8vIDEgLSBmdWxmaWxsZWQgd2l0aCBfdmFsdWVcbi8vIDIgLSByZWplY3RlZCB3aXRoIF92YWx1ZVxuLy8gMyAtIGFkb3B0ZWQgdGhlIHN0YXRlIG9mIGFub3RoZXIgcHJvbWlzZSwgX3ZhbHVlXG4vL1xuLy8gb25jZSB0aGUgc3RhdGUgaXMgbm8gbG9uZ2VyIHBlbmRpbmcgKDApIGl0IGlzIGltbXV0YWJsZVxuXG4vLyBBbGwgYF9gIHByZWZpeGVkIHByb3BlcnRpZXMgd2lsbCBiZSByZWR1Y2VkIHRvIGBfe3JhbmRvbSBudW1iZXJ9YFxuLy8gYXQgYnVpbGQgdGltZSB0byBvYmZ1c2NhdGUgdGhlbSBhbmQgZGlzY291cmFnZSB0aGVpciB1c2UuXG4vLyBXZSBkb24ndCB1c2Ugc3ltYm9scyBvciBPYmplY3QuZGVmaW5lUHJvcGVydHkgdG8gZnVsbHkgaGlkZSB0aGVtXG4vLyBiZWNhdXNlIHRoZSBwZXJmb3JtYW5jZSBpc24ndCBnb29kIGVub3VnaC5cblxuLy8gdG8gYXZvaWQgdXNpbmcgdHJ5L2NhdGNoIGluc2lkZSBjcml0aWNhbCBmdW5jdGlvbnMsIHdlXG4vLyBleHRyYWN0IHRoZW0gdG8gaGVyZS5cbnZhciBMQVNUX0VSUk9SID0gbnVsbDtcbnZhciBJU19FUlJPUiA9IHt9O1xuZnVuY3Rpb24gZ2V0VGhlbihvYmopIHtcbiAgdHJ5IHtcbiAgICByZXR1cm4gb2JqLnRoZW47XG4gIH0gY2F0Y2ggKGV4KSB7XG4gICAgTEFTVF9FUlJPUiA9IGV4O1xuICAgIHJldHVybiBJU19FUlJPUjtcbiAgfVxufVxuXG5mdW5jdGlvbiB0cnlDYWxsT25lKGZuLCBhKSB7XG4gIHRyeSB7XG4gICAgcmV0dXJuIGZuKGEpO1xuICB9IGNhdGNoIChleCkge1xuICAgIExBU1RfRVJST1IgPSBleDtcbiAgICByZXR1cm4gSVNfRVJST1I7XG4gIH1cbn1cbmZ1bmN0aW9uIHRyeUNhbGxUd28oZm4sIGEsIGIpIHtcbiAgdHJ5IHtcbiAgICBmbihhLCBiKTtcbiAgfSBjYXRjaCAoZXgpIHtcbiAgICBMQVNUX0VSUk9SID0gZXg7XG4gICAgcmV0dXJuIElTX0VSUk9SO1xuICB9XG59XG5cbmZ1bmN0aW9uIHRyaW1TdGFjayhzdGFjaykge1xuICAgIGlmICghc3RhY2spIHtcbiAgICAgICAgcmV0dXJuICcnO1xuICAgIH1cbiAgICBjb25zdCBpbmRleCA9IHN0YWNrLmluZGV4T2YoJ1xcbicpO1xuICAgIGlmIChpbmRleCA9PT0gLTEpIHtcbiAgICAgICAgcmV0dXJuIHN0YWNrO1xuICAgIH1cbiAgICAvLyByZW1vdmUgXCJhdCBQcm9taXNlMlwiIHN0YWNrLlxuICAgIHJldHVybiBzdGFjay5zdWJzdHJpbmcoaW5kZXggKyAxKTtcbn1cblxubW9kdWxlLmV4cG9ydHMgPSAob3B0KSA9PiB7XG4gIHZhciBuZXh0VGljayA9IG9wdC5uZXh0VGljaztcbiAgZnVuY3Rpb24gUHJvbWlzZShmbikge1xuICAgICAgdGhpcy5fX2NyZWF0ZVN0YWNrID0gdHJpbVN0YWNrKG5ldyBFcnJvcignUHJvbWlzZSBjcmVhdGlvbiBzdGFjaycpLnN0YWNrKTtcbiAgICBpZiAodHlwZW9mIHRoaXMgIT09ICdvYmplY3QnKSB7XG4gICAgICB0aHJvdyBuZXcgVHlwZUVycm9yKCdQcm9taXNlcyBtdXN0IGJlIGNvbnN0cnVjdGVkIHZpYSBuZXcnKTtcbiAgICB9XG4gICAgaWYgKHR5cGVvZiBmbiAhPT0gJ2Z1bmN0aW9uJykge1xuICAgICAgdGhyb3cgbmV3IFR5cGVFcnJvcihcIlByb21pc2UgY29uc3RydWN0b3IncyBhcmd1bWVudCBpcyBub3QgYSBmdW5jdGlvblwiKTtcbiAgICB9XG4gICAgdGhpcy5fZGVmZXJyZWRTdGF0ZSA9IDA7XG4gICAgdGhpcy5fc3RhdGUgPSAwO1xuICAgIHRoaXMuX3ZhbHVlID0gbnVsbDtcbiAgICB0aGlzLl9kZWZlcnJlZHMgPSBudWxsO1xuICAgIGlmIChmbiA9PT0gbm9vcCkgcmV0dXJuO1xuICAgIGRvUmVzb2x2ZShmbiwgdGhpcyk7XG4gIH1cbiAgUHJvbWlzZS5fb25IYW5kbGUgPSBudWxsO1xuICBQcm9taXNlLl9vblJlamVjdCA9IG51bGw7XG4gIFByb21pc2UuX25vb3AgPSBub29wO1xuXG4gIFByb21pc2UucHJvdG90eXBlLnRoZW4gPSBmdW5jdGlvbihvbkZ1bGZpbGxlZCwgb25SZWplY3RlZCkge1xuICAgIGlmICh0aGlzLmNvbnN0cnVjdG9yICE9PSBQcm9taXNlKSB7XG4gICAgICByZXR1cm4gc2FmZVRoZW4odGhpcywgb25GdWxmaWxsZWQsIG9uUmVqZWN0ZWQpO1xuICAgIH1cbiAgICB2YXIgcmVzID0gbmV3IFByb21pc2Uobm9vcCk7XG4gICAgaGFuZGxlKHRoaXMsIG5ldyBIYW5kbGVyKG9uRnVsZmlsbGVkLCBvblJlamVjdGVkLCByZXMpKTtcbiAgICByZXR1cm4gcmVzO1xuICB9O1xuXG4gIGZ1bmN0aW9uIHNhZmVUaGVuKHNlbGYsIG9uRnVsZmlsbGVkLCBvblJlamVjdGVkKSB7XG4gICAgcmV0dXJuIG5ldyBzZWxmLmNvbnN0cnVjdG9yKGZ1bmN0aW9uKHJlc29sdmUsIHJlamVjdCkge1xuICAgICAgdmFyIHJlcyA9IG5ldyBQcm9taXNlKG5vb3ApO1xuICAgICAgcmVzLnRoZW4ocmVzb2x2ZSwgcmVqZWN0KTtcbiAgICAgIGhhbmRsZShzZWxmLCBuZXcgSGFuZGxlcihvbkZ1bGZpbGxlZCwgb25SZWplY3RlZCwgcmVzKSk7XG4gICAgfSk7XG4gIH1cbiAgZnVuY3Rpb24gaGFuZGxlKHNlbGYsIGRlZmVycmVkKSB7XG4gICAgd2hpbGUgKHNlbGYuX3N0YXRlID09PSAzKSB7XG4gICAgICBzZWxmID0gc2VsZi5fdmFsdWU7XG4gICAgfVxuICAgIGlmIChQcm9taXNlLl9vbkhhbmRsZSkge1xuICAgICAgUHJvbWlzZS5fb25IYW5kbGUoc2VsZik7XG4gICAgfVxuICAgIGlmIChzZWxmLl9zdGF0ZSA9PT0gMCkge1xuICAgICAgaWYgKHNlbGYuX2RlZmVycmVkU3RhdGUgPT09IDApIHtcbiAgICAgICAgc2VsZi5fZGVmZXJyZWRTdGF0ZSA9IDE7XG4gICAgICAgIHNlbGYuX2RlZmVycmVkcyA9IGRlZmVycmVkO1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgICBpZiAoc2VsZi5fZGVmZXJyZWRTdGF0ZSA9PT0gMSkge1xuICAgICAgICBzZWxmLl9kZWZlcnJlZFN0YXRlID0gMjtcbiAgICAgICAgc2VsZi5fZGVmZXJyZWRzID0gW3NlbGYuX2RlZmVycmVkcywgZGVmZXJyZWRdO1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgICBzZWxmLl9kZWZlcnJlZHMucHVzaChkZWZlcnJlZCk7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIGhhbmRsZVJlc29sdmVkKHNlbGYsIGRlZmVycmVkKTtcbiAgfVxuXG4gIGZ1bmN0aW9uIGhhbmRsZVJlc29sdmVkKHNlbGYsIGRlZmVycmVkKSB7XG4gICAgbmV4dFRpY2soZnVuY3Rpb24oKSB7XG4gICAgICB2YXIgY2IgPSBzZWxmLl9zdGF0ZSA9PT0gMSA/IGRlZmVycmVkLm9uRnVsZmlsbGVkIDogZGVmZXJyZWQub25SZWplY3RlZDtcbiAgICAgIGlmIChjYiA9PT0gbnVsbCkge1xuICAgICAgICBpZiAoc2VsZi5fc3RhdGUgPT09IDEpIHtcbiAgICAgICAgICByZXNvbHZlKGRlZmVycmVkLnByb21pc2UsIHNlbGYuX3ZhbHVlKTtcbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICByZWplY3QoZGVmZXJyZWQucHJvbWlzZSwgc2VsZi5fdmFsdWUpO1xuICAgICAgICB9XG4gICAgICAgIHJldHVybjtcbiAgICAgIH1cbiAgICAgIHZhciByZXQgPSB0cnlDYWxsT25lKGNiLCBzZWxmLl92YWx1ZSk7XG4gICAgICBpZiAocmV0ID09PSBJU19FUlJPUikge1xuICAgICAgICByZWplY3QoZGVmZXJyZWQucHJvbWlzZSwgTEFTVF9FUlJPUik7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICByZXNvbHZlKGRlZmVycmVkLnByb21pc2UsIHJldCk7XG4gICAgICB9XG4gICAgfSk7XG4gIH1cbiAgZnVuY3Rpb24gcmVzb2x2ZShzZWxmLCBuZXdWYWx1ZSkge1xuICAgIC8vIFByb21pc2UgUmVzb2x1dGlvbiBQcm9jZWR1cmU6IGh0dHBzOi8vZ2l0aHViLmNvbS9wcm9taXNlcy1hcGx1cy9wcm9taXNlcy1zcGVjI3RoZS1wcm9taXNlLXJlc29sdXRpb24tcHJvY2VkdXJlXG4gICAgaWYgKG5ld1ZhbHVlID09PSBzZWxmKSB7XG4gICAgICByZXR1cm4gcmVqZWN0KHNlbGYsIG5ldyBUeXBlRXJyb3IoJ0EgcHJvbWlzZSBjYW5ub3QgYmUgcmVzb2x2ZWQgd2l0aCBpdHNlbGYuJykpO1xuICAgIH1cbiAgICBpZiAobmV3VmFsdWUgJiYgKHR5cGVvZiBuZXdWYWx1ZSA9PT0gJ29iamVjdCcgfHwgdHlwZW9mIG5ld1ZhbHVlID09PSAnZnVuY3Rpb24nKSkge1xuICAgICAgdmFyIHRoZW4gPSBnZXRUaGVuKG5ld1ZhbHVlKTtcbiAgICAgIGlmICh0aGVuID09PSBJU19FUlJPUikge1xuICAgICAgICByZXR1cm4gcmVqZWN0KHNlbGYsIExBU1RfRVJST1IpO1xuICAgICAgfVxuICAgICAgaWYgKHRoZW4gPT09IHNlbGYudGhlbiAmJiBuZXdWYWx1ZSBpbnN0YW5jZW9mIFByb21pc2UpIHtcbiAgICAgICAgc2VsZi5fc3RhdGUgPSAzO1xuICAgICAgICBzZWxmLl92YWx1ZSA9IG5ld1ZhbHVlO1xuICAgICAgICBmaW5hbGUoc2VsZik7XG4gICAgICAgIHJldHVybjtcbiAgICAgIH0gZWxzZSBpZiAodHlwZW9mIHRoZW4gPT09ICdmdW5jdGlvbicpIHtcbiAgICAgICAgZG9SZXNvbHZlKHRoZW4uYmluZChuZXdWYWx1ZSksIHNlbGYpO1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgfVxuICAgIHNlbGYuX3N0YXRlID0gMTtcbiAgICBzZWxmLl92YWx1ZSA9IG5ld1ZhbHVlO1xuICAgIGZpbmFsZShzZWxmKTtcbiAgfVxuXG4gIGZ1bmN0aW9uIHJlamVjdChzZWxmLCBuZXdWYWx1ZSkge1xuICAgIHNlbGYuX3N0YXRlID0gMjtcbiAgICBzZWxmLl92YWx1ZSA9IG5ld1ZhbHVlO1xuICAgIGlmIChQcm9taXNlLl9vblJlamVjdCkge1xuICAgICAgUHJvbWlzZS5fb25SZWplY3Qoc2VsZiwgbmV3VmFsdWUpO1xuICAgIH1cbiAgICBmaW5hbGUoc2VsZik7XG4gIH1cbiAgZnVuY3Rpb24gZmluYWxlKHNlbGYpIHtcbiAgICBpZiAoc2VsZi5fZGVmZXJyZWRTdGF0ZSA9PT0gMSkge1xuICAgICAgaGFuZGxlKHNlbGYsIHNlbGYuX2RlZmVycmVkcyk7XG4gICAgICBzZWxmLl9kZWZlcnJlZHMgPSBudWxsO1xuICAgIH1cbiAgICBpZiAoc2VsZi5fZGVmZXJyZWRTdGF0ZSA9PT0gMikge1xuICAgICAgZm9yICh2YXIgaSA9IDA7IGkgPCBzZWxmLl9kZWZlcnJlZHMubGVuZ3RoOyBpKyspIHtcbiAgICAgICAgaGFuZGxlKHNlbGYsIHNlbGYuX2RlZmVycmVkc1tpXSk7XG4gICAgICB9XG4gICAgICBzZWxmLl9kZWZlcnJlZHMgPSBudWxsO1xuICAgIH1cbiAgfVxuXG4gIGZ1bmN0aW9uIEhhbmRsZXIob25GdWxmaWxsZWQsIG9uUmVqZWN0ZWQsIHByb21pc2UpIHtcbiAgICB0aGlzLm9uRnVsZmlsbGVkID0gdHlwZW9mIG9uRnVsZmlsbGVkID09PSAnZnVuY3Rpb24nID8gb25GdWxmaWxsZWQgOiBudWxsO1xuICAgIHRoaXMub25SZWplY3RlZCA9IHR5cGVvZiBvblJlamVjdGVkID09PSAnZnVuY3Rpb24nID8gb25SZWplY3RlZCA6IG51bGw7XG4gICAgdGhpcy5wcm9taXNlID0gcHJvbWlzZTtcbiAgfVxuXG4gIC8qKlxuICAgKiBUYWtlIGEgcG90ZW50aWFsbHkgbWlzYmVoYXZpbmcgcmVzb2x2ZXIgZnVuY3Rpb24gYW5kIG1ha2Ugc3VyZVxuICAgKiBvbkZ1bGZpbGxlZCBhbmQgb25SZWplY3RlZCBhcmUgb25seSBjYWxsZWQgb25jZS5cbiAgICpcbiAgICogTWFrZXMgbm8gZ3VhcmFudGVlcyBhYm91dCBhc3luY2hyb255LlxuICAgKi9cbiAgZnVuY3Rpb24gZG9SZXNvbHZlKGZuLCBwcm9taXNlKSB7XG4gICAgdmFyIGRvbmUgPSBmYWxzZTtcbiAgICB2YXIgcmVzID0gdHJ5Q2FsbFR3byhcbiAgICAgIGZuLFxuICAgICAgZnVuY3Rpb24odmFsdWUpIHtcbiAgICAgICAgaWYgKGRvbmUpIHJldHVybjtcbiAgICAgICAgZG9uZSA9IHRydWU7XG4gICAgICAgIHJlc29sdmUocHJvbWlzZSwgdmFsdWUpO1xuICAgICAgfSxcbiAgICAgIGZ1bmN0aW9uKHJlYXNvbikge1xuICAgICAgICBpZiAoZG9uZSkgcmV0dXJuO1xuICAgICAgICBkb25lID0gdHJ1ZTtcbiAgICAgICAgcmVqZWN0KHByb21pc2UsIHJlYXNvbik7XG4gICAgICB9XG4gICAgKTtcbiAgICBpZiAoIWRvbmUgJiYgcmVzID09PSBJU19FUlJPUikge1xuICAgICAgZG9uZSA9IHRydWU7XG4gICAgICByZWplY3QocHJvbWlzZSwgTEFTVF9FUlJPUik7XG4gICAgfVxuICB9XG4gIHJldHVybiBQcm9taXNlO1xufTtcbiIsICIvKipcbiAqIEBsaWNlbnNlXG5Db3B5cmlnaHQgKGMpIDIwMTQgRm9yYmVzIExpbmRlc2F5XG5cblBlcm1pc3Npb24gaXMgaGVyZWJ5IGdyYW50ZWQsIGZyZWUgb2YgY2hhcmdlLCB0byBhbnkgcGVyc29uIG9idGFpbmluZyBhIGNvcHlcbm9mIHRoaXMgc29mdHdhcmUgYW5kIGFzc29jaWF0ZWQgZG9jdW1lbnRhdGlvbiBmaWxlcyAodGhlIFwiU29mdHdhcmVcIiksIHRvIGRlYWxcbmluIHRoZSBTb2Z0d2FyZSB3aXRob3V0IHJlc3RyaWN0aW9uLCBpbmNsdWRpbmcgd2l0aG91dCBsaW1pdGF0aW9uIHRoZSByaWdodHNcbnRvIHVzZSwgY29weSwgbW9kaWZ5LCBtZXJnZSwgcHVibGlzaCwgZGlzdHJpYnV0ZSwgc3VibGljZW5zZSwgYW5kL29yIHNlbGxcbmNvcGllcyBvZiB0aGUgU29mdHdhcmUsIGFuZCB0byBwZXJtaXQgcGVyc29ucyB0byB3aG9tIHRoZSBTb2Z0d2FyZSBpc1xuZnVybmlzaGVkIHRvIGRvIHNvLCBzdWJqZWN0IHRvIHRoZSBmb2xsb3dpbmcgY29uZGl0aW9uczpcblxuVGhlIGFib3ZlIGNvcHlyaWdodCBub3RpY2UgYW5kIHRoaXMgcGVybWlzc2lvbiBub3RpY2Ugc2hhbGwgYmUgaW5jbHVkZWQgaW5cbmFsbCBjb3BpZXMgb3Igc3Vic3RhbnRpYWwgcG9ydGlvbnMgb2YgdGhlIFNvZnR3YXJlLlxuXG5USEUgU09GVFdBUkUgSVMgUFJPVklERUQgXCJBUyBJU1wiLCBXSVRIT1VUIFdBUlJBTlRZIE9GIEFOWSBLSU5ELCBFWFBSRVNTIE9SXG5JTVBMSUVELCBJTkNMVURJTkcgQlVUIE5PVCBMSU1JVEVEIFRPIFRIRSBXQVJSQU5USUVTIE9GIE1FUkNIQU5UQUJJTElUWSxcbkZJVE5FU1MgRk9SIEEgUEFSVElDVUxBUiBQVVJQT1NFIEFORCBOT05JTkZSSU5HRU1FTlQuIElOIE5PIEVWRU5UIFNIQUxMIFRIRVxuQVVUSE9SUyBPUiBDT1BZUklHSFQgSE9MREVSUyBCRSBMSUFCTEUgRk9SIEFOWSBDTEFJTSwgREFNQUdFUyBPUiBPVEhFUlxuTElBQklMSVRZLCBXSEVUSEVSIElOIEFOIEFDVElPTiBPRiBDT05UUkFDVCwgVE9SVCBPUiBPVEhFUldJU0UsIEFSSVNJTkcgRlJPTSxcbk9VVCBPRiBPUiBJTiBDT05ORUNUSU9OIFdJVEggVEhFIFNPRlRXQVJFIE9SIFRIRSBVU0UgT1IgT1RIRVIgREVBTElOR1MgSU5cblRIRSBTT0ZUV0FSRS5cbiAqL1xuJ3VzZSBzdHJpY3QnO1xuXG4vL1RoaXMgZmlsZSBjb250YWlucyB0aGUgRVM2IGV4dGVuc2lvbnMgdG8gdGhlIGNvcmUgUHJvbWlzZXMvQSsgQVBJXG5cbm1vZHVsZS5leHBvcnRzID0gUHJvbWlzZSA9PiB7XG4gIC8qIFN0YXRpYyBGdW5jdGlvbnMgKi9cblxuICB2YXIgVFJVRSA9IHZhbHVlUHJvbWlzZSh0cnVlKTtcbiAgdmFyIEZBTFNFID0gdmFsdWVQcm9taXNlKGZhbHNlKTtcbiAgdmFyIE5VTEwgPSB2YWx1ZVByb21pc2UobnVsbCk7XG4gIHZhciBVTkRFRklORUQgPSB2YWx1ZVByb21pc2UodW5kZWZpbmVkKTtcbiAgdmFyIFpFUk8gPSB2YWx1ZVByb21pc2UoMCk7XG4gIHZhciBFTVBUWVNUUklORyA9IHZhbHVlUHJvbWlzZSgnJyk7XG5cbiAgZnVuY3Rpb24gdmFsdWVQcm9taXNlKHZhbHVlKSB7XG4gICAgdmFyIHAgPSBuZXcgUHJvbWlzZShQcm9taXNlLl9ub29wKTtcbiAgICBwLl9zdGF0ZSA9IDE7XG4gICAgcC5fdmFsdWUgPSB2YWx1ZTtcbiAgICByZXR1cm4gcDtcbiAgfVxuICBQcm9taXNlLnJlc29sdmUgPSBmdW5jdGlvbih2YWx1ZSkge1xuICAgIGlmICh2YWx1ZSBpbnN0YW5jZW9mIFByb21pc2UpIHJldHVybiB2YWx1ZTtcblxuICAgIGlmICh2YWx1ZSA9PT0gbnVsbCkgcmV0dXJuIE5VTEw7XG4gICAgaWYgKHZhbHVlID09PSB1bmRlZmluZWQpIHJldHVybiBVTkRFRklORUQ7XG4gICAgaWYgKHZhbHVlID09PSB0cnVlKSByZXR1cm4gVFJVRTtcbiAgICBpZiAodmFsdWUgPT09IGZhbHNlKSByZXR1cm4gRkFMU0U7XG4gICAgaWYgKHZhbHVlID09PSAwKSByZXR1cm4gWkVSTztcbiAgICBpZiAodmFsdWUgPT09ICcnKSByZXR1cm4gRU1QVFlTVFJJTkc7XG5cbiAgICBpZiAodHlwZW9mIHZhbHVlID09PSAnb2JqZWN0JyB8fCB0eXBlb2YgdmFsdWUgPT09ICdmdW5jdGlvbicpIHtcbiAgICAgIHRyeSB7XG4gICAgICAgIHZhciB0aGVuID0gdmFsdWUudGhlbjtcbiAgICAgICAgaWYgKHR5cGVvZiB0aGVuID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgICAgcmV0dXJuIG5ldyBQcm9taXNlKHRoZW4uYmluZCh2YWx1ZSkpO1xuICAgICAgICB9XG4gICAgICB9IGNhdGNoIChleCkge1xuICAgICAgICByZXR1cm4gbmV3IFByb21pc2UoZnVuY3Rpb24ocmVzb2x2ZSwgcmVqZWN0KSB7XG4gICAgICAgICAgcmVqZWN0KGV4KTtcbiAgICAgICAgfSk7XG4gICAgICB9XG4gICAgfVxuICAgIHJldHVybiB2YWx1ZVByb21pc2UodmFsdWUpO1xuICB9O1xuXG4gIHZhciBpdGVyYWJsZVRvQXJyYXkgPSBmdW5jdGlvbihpdGVyYWJsZSkge1xuICAgIGlmICh0eXBlb2YgQXJyYXkuZnJvbSA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgLy8gRVMyMDE1KywgaXRlcmFibGVzIGV4aXN0XG4gICAgICBpdGVyYWJsZVRvQXJyYXkgPSBBcnJheS5mcm9tO1xuICAgICAgcmV0dXJuIEFycmF5LmZyb20oaXRlcmFibGUpO1xuICAgIH1cblxuICAgIC8vIEVTNSwgb25seSBhcnJheXMgYW5kIGFycmF5LWxpa2VzIGV4aXN0XG4gICAgaXRlcmFibGVUb0FycmF5ID0gZnVuY3Rpb24oeCkge1xuICAgICAgcmV0dXJuIEFycmF5LnByb3RvdHlwZS5zbGljZS5jYWxsKHgpO1xuICAgIH07XG4gICAgcmV0dXJuIEFycmF5LnByb3RvdHlwZS5zbGljZS5jYWxsKGl0ZXJhYmxlKTtcbiAgfTtcblxuICBQcm9taXNlLmFsbCA9IGZ1bmN0aW9uKGFycikge1xuICAgIHZhciBhcmdzID0gaXRlcmFibGVUb0FycmF5KGFycik7XG5cbiAgICByZXR1cm4gbmV3IFByb21pc2UoZnVuY3Rpb24ocmVzb2x2ZSwgcmVqZWN0KSB7XG4gICAgICBpZiAoYXJncy5sZW5ndGggPT09IDApIHJldHVybiByZXNvbHZlKFtdKTtcbiAgICAgIHZhciByZW1haW5pbmcgPSBhcmdzLmxlbmd0aDtcbiAgICAgIGZ1bmN0aW9uIHJlcyhpLCB2YWwpIHtcbiAgICAgICAgaWYgKHZhbCAmJiAodHlwZW9mIHZhbCA9PT0gJ29iamVjdCcgfHwgdHlwZW9mIHZhbCA9PT0gJ2Z1bmN0aW9uJykpIHtcbiAgICAgICAgICBpZiAodmFsIGluc3RhbmNlb2YgUHJvbWlzZSAmJiB2YWwudGhlbiA9PT0gUHJvbWlzZS5wcm90b3R5cGUudGhlbikge1xuICAgICAgICAgICAgd2hpbGUgKHZhbC5fc3RhdGUgPT09IDMpIHtcbiAgICAgICAgICAgICAgdmFsID0gdmFsLl92YWx1ZTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIGlmICh2YWwuX3N0YXRlID09PSAxKSByZXR1cm4gcmVzKGksIHZhbC5fdmFsdWUpO1xuICAgICAgICAgICAgaWYgKHZhbC5fc3RhdGUgPT09IDIpIHJlamVjdCh2YWwuX3ZhbHVlKTtcbiAgICAgICAgICAgIHZhbC50aGVuKGZ1bmN0aW9uKHZhbCkge1xuICAgICAgICAgICAgICByZXMoaSwgdmFsKTtcbiAgICAgICAgICAgIH0sIHJlamVjdCk7XG4gICAgICAgICAgICByZXR1cm47XG4gICAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAgIHZhciB0aGVuID0gdmFsLnRoZW47XG4gICAgICAgICAgICBpZiAodHlwZW9mIHRoZW4gPT09ICdmdW5jdGlvbicpIHtcbiAgICAgICAgICAgICAgdmFyIHAgPSBuZXcgUHJvbWlzZSh0aGVuLmJpbmQodmFsKSk7XG4gICAgICAgICAgICAgIHAudGhlbihmdW5jdGlvbih2YWwpIHtcbiAgICAgICAgICAgICAgICByZXMoaSwgdmFsKTtcbiAgICAgICAgICAgICAgfSwgcmVqZWN0KTtcbiAgICAgICAgICAgICAgcmV0dXJuO1xuICAgICAgICAgICAgfVxuICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgICBhcmdzW2ldID0gdmFsO1xuICAgICAgICBpZiAoLS1yZW1haW5pbmcgPT09IDApIHtcbiAgICAgICAgICByZXNvbHZlKGFyZ3MpO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgICBmb3IgKHZhciBpID0gMDsgaSA8IGFyZ3MubGVuZ3RoOyBpKyspIHtcbiAgICAgICAgcmVzKGksIGFyZ3NbaV0pO1xuICAgICAgfVxuICAgIH0pO1xuICB9O1xuXG4gIFByb21pc2UucmVqZWN0ID0gZnVuY3Rpb24odmFsdWUpIHtcbiAgICByZXR1cm4gbmV3IFByb21pc2UoZnVuY3Rpb24ocmVzb2x2ZSwgcmVqZWN0KSB7XG4gICAgICByZWplY3QodmFsdWUpO1xuICAgIH0pO1xuICB9O1xuXG4gIFByb21pc2UucmFjZSA9IGZ1bmN0aW9uKHZhbHVlcykge1xuICAgIHJldHVybiBuZXcgUHJvbWlzZShmdW5jdGlvbihyZXNvbHZlLCByZWplY3QpIHtcbiAgICAgIGl0ZXJhYmxlVG9BcnJheSh2YWx1ZXMpLmZvckVhY2goZnVuY3Rpb24odmFsdWUpIHtcbiAgICAgICAgUHJvbWlzZS5yZXNvbHZlKHZhbHVlKS50aGVuKHJlc29sdmUsIHJlamVjdCk7XG4gICAgICB9KTtcbiAgICB9KTtcbiAgfTtcblxuICAvKiBQcm90b3R5cGUgTWV0aG9kcyAqL1xuXG4gIFByb21pc2UucHJvdG90eXBlWydjYXRjaCddID0gZnVuY3Rpb24ob25SZWplY3RlZCkge1xuICAgIHJldHVybiB0aGlzLnRoZW4obnVsbCwgb25SZWplY3RlZCk7XG4gIH07XG4gIFByb21pc2UucHJvdG90eXBlLmRvbmUgPSBmdW5jdGlvbihvbkZ1bGZpbGxlZCwgb25SZWplY3RlZCkge1xuICAgIHZhciBzZWxmID0gYXJndW1lbnRzLmxlbmd0aCA/IHRoaXMudGhlbi5hcHBseSh0aGlzLCBhcmd1bWVudHMpIDogdGhpcztcbiAgICBzZWxmLnRoZW4obnVsbCwgZnVuY3Rpb24oZXJyKSB7XG4gICAgICBzZXRUaW1lb3V0KGZ1bmN0aW9uKCkge1xuICAgICAgICB0aHJvdyBlcnI7XG4gICAgICB9LCAwKTtcbiAgICB9KTtcbiAgfTtcbiAgUHJvbWlzZS5wcm90b3R5cGUuZmluYWxseSA9IGZ1bmN0aW9uKGYpIHtcbiAgICByZXR1cm4gdGhpcy50aGVuKFxuICAgICAgZnVuY3Rpb24odmFsdWUpIHtcbiAgICAgICAgcmV0dXJuIFByb21pc2UucmVzb2x2ZShmKCkpLnRoZW4oZnVuY3Rpb24oKSB7XG4gICAgICAgICAgcmV0dXJuIHZhbHVlO1xuICAgICAgICB9KTtcbiAgICAgIH0sXG4gICAgICBmdW5jdGlvbihlcnIpIHtcbiAgICAgICAgcmV0dXJuIFByb21pc2UucmVzb2x2ZShmKCkpLnRoZW4oZnVuY3Rpb24oKSB7XG4gICAgICAgICAgdGhyb3cgZXJyO1xuICAgICAgICB9KTtcbiAgICAgIH1cbiAgICApO1xuICB9O1xuICByZXR1cm4gUHJvbWlzZTtcbn07XG4iLCAiLyoqXG4gKiBAbGljZW5zZVxuQ29weXJpZ2h0IChjKSAyMDE0IEZvcmJlcyBMaW5kZXNheVxuXG5QZXJtaXNzaW9uIGlzIGhlcmVieSBncmFudGVkLCBmcmVlIG9mIGNoYXJnZSwgdG8gYW55IHBlcnNvbiBvYnRhaW5pbmcgYSBjb3B5XG5vZiB0aGlzIHNvZnR3YXJlIGFuZCBhc3NvY2lhdGVkIGRvY3VtZW50YXRpb24gZmlsZXMgKHRoZSBcIlNvZnR3YXJlXCIpLCB0byBkZWFsXG5pbiB0aGUgU29mdHdhcmUgd2l0aG91dCByZXN0cmljdGlvbiwgaW5jbHVkaW5nIHdpdGhvdXQgbGltaXRhdGlvbiB0aGUgcmlnaHRzXG50byB1c2UsIGNvcHksIG1vZGlmeSwgbWVyZ2UsIHB1Ymxpc2gsIGRpc3RyaWJ1dGUsIHN1YmxpY2Vuc2UsIGFuZC9vciBzZWxsXG5jb3BpZXMgb2YgdGhlIFNvZnR3YXJlLCBhbmQgdG8gcGVybWl0IHBlcnNvbnMgdG8gd2hvbSB0aGUgU29mdHdhcmUgaXNcbmZ1cm5pc2hlZCB0byBkbyBzbywgc3ViamVjdCB0byB0aGUgZm9sbG93aW5nIGNvbmRpdGlvbnM6XG5cblRoZSBhYm92ZSBjb3B5cmlnaHQgbm90aWNlIGFuZCB0aGlzIHBlcm1pc3Npb24gbm90aWNlIHNoYWxsIGJlIGluY2x1ZGVkIGluXG5hbGwgY29waWVzIG9yIHN1YnN0YW50aWFsIHBvcnRpb25zIG9mIHRoZSBTb2Z0d2FyZS5cblxuVEhFIFNPRlRXQVJFIElTIFBST1ZJREVEIFwiQVMgSVNcIiwgV0lUSE9VVCBXQVJSQU5UWSBPRiBBTlkgS0lORCwgRVhQUkVTUyBPUlxuSU1QTElFRCwgSU5DTFVESU5HIEJVVCBOT1QgTElNSVRFRCBUTyBUSEUgV0FSUkFOVElFUyBPRiBNRVJDSEFOVEFCSUxJVFksXG5GSVRORVNTIEZPUiBBIFBBUlRJQ1VMQVIgUFVSUE9TRSBBTkQgTk9OSU5GUklOR0VNRU5ULiBJTiBOTyBFVkVOVCBTSEFMTCBUSEVcbkFVVEhPUlMgT1IgQ09QWVJJR0hUIEhPTERFUlMgQkUgTElBQkxFIEZPUiBBTlkgQ0xBSU0sIERBTUFHRVMgT1IgT1RIRVJcbkxJQUJJTElUWSwgV0hFVEhFUiBJTiBBTiBBQ1RJT04gT0YgQ09OVFJBQ1QsIFRPUlQgT1IgT1RIRVJXSVNFLCBBUklTSU5HIEZST00sXG5PVVQgT0YgT1IgSU4gQ09OTkVDVElPTiBXSVRIIFRIRSBTT0ZUV0FSRSBPUiBUSEUgVVNFIE9SIE9USEVSIERFQUxJTkdTIElOXG5USEUgU09GVFdBUkUuXG4gKi9cbid1c2Ugc3RyaWN0JztcblxubW9kdWxlLmV4cG9ydHMgPSAoUHJvbWlzZSwgc2V0VGltZW91dCwgY2xlYXJUaW1lb3V0KSA9PiB7XG4gIHZhciBERUZBVUxUX1dISVRFTElTVCA9IFtSZWZlcmVuY2VFcnJvciwgVHlwZUVycm9yLCBSYW5nZUVycm9yXTtcblxuICB2YXIgZW5hYmxlZCA9IGZhbHNlO1xuXG4gIGZ1bmN0aW9uIGRpc2FibGUoKSB7XG4gICAgZW5hYmxlZCA9IGZhbHNlO1xuICAgIFByb21pc2UuX29uSGFuZGxlID0gbnVsbDtcbiAgICBQcm9taXNlLl9vblJlamVjdCA9IG51bGw7XG4gIH1cblxuICBmdW5jdGlvbiBlbmFibGUob3B0aW9ucykge1xuICAgIG9wdGlvbnMgPSBvcHRpb25zIHx8IHt9O1xuICAgIGlmIChlbmFibGVkKSBkaXNhYmxlKCk7XG4gICAgZW5hYmxlZCA9IHRydWU7XG4gICAgdmFyIGlkID0gMDtcbiAgICB2YXIgZGlzcGxheUlkID0gMDtcbiAgICB2YXIgcmVqZWN0aW9ucyA9IHt9O1xuICAgIFByb21pc2UuX29uSGFuZGxlID0gZnVuY3Rpb24ocHJvbWlzZSkge1xuICAgICAgaWYgKFxuICAgICAgICBwcm9taXNlLl9zdGF0ZSA9PT0gMiAmJiAvLyBJUyBSRUpFQ1RFRFxuICAgICAgICByZWplY3Rpb25zW3Byb21pc2UuX3JlamVjdGlvbklkXVxuICAgICAgKSB7XG4gICAgICAgIGlmIChyZWplY3Rpb25zW3Byb21pc2UuX3JlamVjdGlvbklkXS5sb2dnZWQpIHtcbiAgICAgICAgICBvbkhhbmRsZWQocHJvbWlzZS5fcmVqZWN0aW9uSWQpO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIGNsZWFyVGltZW91dCAmJiBjbGVhclRpbWVvdXQocmVqZWN0aW9uc1twcm9taXNlLl9yZWplY3Rpb25JZF0udGltZW91dCk7XG4gICAgICAgIH1cbiAgICAgICAgZGVsZXRlIHJlamVjdGlvbnNbcHJvbWlzZS5fcmVqZWN0aW9uSWRdO1xuICAgICAgfVxuICAgIH07XG4gICAgUHJvbWlzZS5fb25SZWplY3QgPSBmdW5jdGlvbihwcm9taXNlLCBlcnIpIHtcbiAgICAgIGlmIChwcm9taXNlLl9kZWZlcnJlZFN0YXRlID09PSAwKSB7XG4gICAgICAgIC8vIG5vdCB5ZXQgaGFuZGxlZFxuICAgICAgICBwcm9taXNlLl9yZWplY3Rpb25JZCA9IGlkKys7XG4gICAgICAgIHJlamVjdGlvbnNbcHJvbWlzZS5fcmVqZWN0aW9uSWRdID0ge1xuICAgICAgICAgIGRpc3BsYXlJZDogbnVsbCxcbiAgICAgICAgICBlcnJvcjogZXJyLFxuICAgICAgICAgIHRpbWVvdXQ6IHNldFRpbWVvdXQoXG4gICAgICAgICAgICBvblVuaGFuZGxlZC5iaW5kKG51bGwsIHByb21pc2UpLCAwKSxcbiAgICAgICAgICBsb2dnZWQ6IGZhbHNlLFxuICAgICAgICB9O1xuICAgICAgfVxuICAgIH07XG4gICAgZnVuY3Rpb24gb25VbmhhbmRsZWQocHJvbWlzZSkge1xuICAgICAgY29uc3QgaWQgPSBwcm9taXNlLl9yZWplY3Rpb25JZDtcbiAgICAgIGlmIChvcHRpb25zLmFsbFJlamVjdGlvbnMgfHwgbWF0Y2hXaGl0ZWxpc3QocmVqZWN0aW9uc1tpZF0uZXJyb3IsIG9wdGlvbnMud2hpdGVsaXN0IHx8IERFRkFVTFRfV0hJVEVMSVNUKSkge1xuICAgICAgICByZWplY3Rpb25zW2lkXS5kaXNwbGF5SWQgPSBkaXNwbGF5SWQrKztcbiAgICAgICAgaWYgKG9wdGlvbnMub25VbmhhbmRsZWQpIHtcbiAgICAgICAgICByZWplY3Rpb25zW2lkXS5sb2dnZWQgPSB0cnVlO1xuICAgICAgICAgIGlmIChyZWplY3Rpb25zW2lkXS5lcnJvciAmJiAhKHJlamVjdGlvbnNbaWRdLmVycm9yIGluc3RhbmNlb2YgRXJyb3IpKSB7XG4gICAgICAgICAgICBjb25zdCBlcnJvciA9IG5ldyBFcnJvcihKU09OLnN0cmluZ2lmeShyZWplY3Rpb25zW2lkXS5lcnJvcikpO1xuICAgICAgICAgICAgZXJyb3Iuc3RhY2sgPSBwcm9taXNlLl9fY3JlYXRlU3RhY2s7XG4gICAgICAgICAgICByZWplY3Rpb25zW2lkXS5lcnJvciA9IGVycm9yO1xuICAgICAgICAgIH1cbiAgICAgICAgICBvcHRpb25zLm9uVW5oYW5kbGVkKHJlamVjdGlvbnNbaWRdLmRpc3BsYXlJZCwgcmVqZWN0aW9uc1tpZF0uZXJyb3IpO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIHJlamVjdGlvbnNbaWRdLmxvZ2dlZCA9IHRydWU7XG4gICAgICAgICAgbG9nRXJyb3IocmVqZWN0aW9uc1tpZF0uZGlzcGxheUlkLCByZWplY3Rpb25zW2lkXS5lcnJvcik7XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICB9XG4gICAgZnVuY3Rpb24gb25IYW5kbGVkKGlkKSB7XG4gICAgICBpZiAocmVqZWN0aW9uc1tpZF0ubG9nZ2VkKSB7XG4gICAgICAgIGlmIChvcHRpb25zLm9uSGFuZGxlZCkge1xuICAgICAgICAgIG9wdGlvbnMub25IYW5kbGVkKHJlamVjdGlvbnNbaWRdLmRpc3BsYXlJZCwgcmVqZWN0aW9uc1tpZF0uZXJyb3IpO1xuICAgICAgICB9IGVsc2UgaWYgKCFyZWplY3Rpb25zW2lkXS5vblVuaGFuZGxlZCkge1xuICAgICAgICAgIGNvbnNvbGUud2FybignUHJvbWlzZSBSZWplY3Rpb24gSGFuZGxlZCAoaWQ6ICcgKyByZWplY3Rpb25zW2lkXS5kaXNwbGF5SWQgKyAnKTonKTtcbiAgICAgICAgICBjb25zb2xlLndhcm4oXG4gICAgICAgICAgICAnICBUaGlzIG1lYW5zIHlvdSBjYW4gaWdub3JlIGFueSBwcmV2aW91cyBtZXNzYWdlcyBvZiB0aGUgZm9ybSBcIlBvc3NpYmxlIFVuaGFuZGxlZCBQcm9taXNlIFJlamVjdGlvblwiIHdpdGggaWQgJyArXG4gICAgICAgICAgICAgIHJlamVjdGlvbnNbaWRdLmRpc3BsYXlJZCArXG4gICAgICAgICAgICAgICcuJ1xuICAgICAgICAgICk7XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICB9XG4gICAgcmV0dXJuIFByb21pc2U7XG4gIH1cblxuICBmdW5jdGlvbiBsb2dFcnJvcihpZCwgZXJyb3IpIHtcbiAgICBjb25zb2xlLndhcm4oJ1Bvc3NpYmxlIFVuaGFuZGxlZCBQcm9taXNlIFJlamVjdGlvbiAoaWQ6ICcgKyBpZCArICcpOicpO1xuICAgIHZhciBlcnJTdHIgPSAoZXJyb3IgJiYgKGVycm9yLnN0YWNrIHx8IGVycm9yKSkgKyAnJztcbiAgICBlcnJTdHIuc3BsaXQoJ1xcbicpLmZvckVhY2goZnVuY3Rpb24obGluZSkge1xuICAgICAgY29uc29sZS53YXJuKCcgICcgKyBsaW5lKTtcbiAgICB9KTtcbiAgfVxuXG4gIGZ1bmN0aW9uIG1hdGNoV2hpdGVsaXN0KGVycm9yLCBsaXN0KSB7XG4gICAgcmV0dXJuIGxpc3Quc29tZShmdW5jdGlvbihjbHMpIHtcbiAgICAgIHJldHVybiBlcnJvciBpbnN0YW5jZW9mIGNscztcbiAgICB9KTtcbiAgfVxuICByZXR1cm4ge1xuICAgIGVuYWJsZSxcbiAgICBkaXNhYmxlLFxuICB9O1xufTtcbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG52YXIgcHJvbWlzZUZhY3RvciA9IHJlcXVpcmUoJy4vY29yZScpO1xudmFyIGVzNiA9IHJlcXVpcmUoJy4vZXM2LWV4dGVuc2lvbnMnKTtcbnZhciByZWplY3Rpb25IYW5kbGUgPSByZXF1aXJlKCcuL3JlamVjdGlvbi10cmFja2luZycpO1xudmFyIGdnID0gbmV3IEZ1bmN0aW9uKCdyZXR1cm4gdGhpcycpKCk7XG4vLyBlc2xpbnQtZGlzYWJsZS1uZXh0LWxpbmUgbm8tbXVsdGktYXNzaWduXG5nZy5nZXRQcm9taXNlID0gbW9kdWxlLmV4cG9ydHMuZ2V0UHJvbWlzZSA9IChvcHQpID0+IHtcbiAgdmFyIHNldFRpbWVvdXQgPSBvcHQuc2V0VGltZW91dDtcbiAgdmFyIG9uVW5oYW5kbGVkID0gb3B0Lm9uVW5oYW5kbGVkO1xuICB2YXIgY2xlYXJUaW1lb3V0ID0gb3B0LmNsZWFyVGltZW91dDtcbiAgdmFyIG5leHRUaWNrID0gb3B0Lm5leHRUaWNrIHx8IChmbiA9PiB7IHNldFRpbWVvdXQoZm4sIDApOyB9KTtcbiAgdmFyIFByb21pc2UgPSBwcm9taXNlRmFjdG9yKHsgbmV4dFRpY2s6IG5leHRUaWNrIH0pO1xuICBQcm9taXNlID0gZXM2KFByb21pc2UpO1xuICBQcm9taXNlID0gcmVqZWN0aW9uSGFuZGxlKFByb21pc2UsIHNldFRpbWVvdXQsIGNsZWFyVGltZW91dCkuZW5hYmxlKHtcbiAgICBhbGxSZWplY3Rpb25zOiB0cnVlLFxuICAgIG9uVW5oYW5kbGVkLFxuICB9KTtcblxuICByZXR1cm4gUHJvbWlzZTtcbn07XG4iLCAiLyoqXG4gKiBDb3B5cmlnaHQgKGMpIDIwMTQtcHJlc2VudCwgRmFjZWJvb2ssIEluYy5cbiAqXG4gKiBUaGlzIHNvdXJjZSBjb2RlIGlzIGxpY2Vuc2VkIHVuZGVyIHRoZSBNSVQgbGljZW5zZSBmb3VuZCBpbiB0aGVcbiAqIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cbiAqL1xuXG52YXIgcnVudGltZSA9IChmdW5jdGlvbiAoZXhwb3J0cykge1xuICBcInVzZSBzdHJpY3RcIjtcblxuICB2YXIgT3AgPSBPYmplY3QucHJvdG90eXBlO1xuICB2YXIgaGFzT3duID0gT3AuaGFzT3duUHJvcGVydHk7XG4gIHZhciB1bmRlZmluZWQ7IC8vIE1vcmUgY29tcHJlc3NpYmxlIHRoYW4gdm9pZCAwLlxuICB2YXIgJFN5bWJvbCA9IHR5cGVvZiBTeW1ib2wgPT09IFwiZnVuY3Rpb25cIiA/IFN5bWJvbCA6IHt9O1xuICB2YXIgaXRlcmF0b3JTeW1ib2wgPSAkU3ltYm9sLml0ZXJhdG9yIHx8IFwiQEBpdGVyYXRvclwiO1xuICB2YXIgYXN5bmNJdGVyYXRvclN5bWJvbCA9ICRTeW1ib2wuYXN5bmNJdGVyYXRvciB8fCBcIkBAYXN5bmNJdGVyYXRvclwiO1xuICB2YXIgdG9TdHJpbmdUYWdTeW1ib2wgPSAkU3ltYm9sLnRvU3RyaW5nVGFnIHx8IFwiQEB0b1N0cmluZ1RhZ1wiO1xuXG4gIGZ1bmN0aW9uIGRlZmluZShvYmosIGtleSwgdmFsdWUpIHtcbiAgICBPYmplY3QuZGVmaW5lUHJvcGVydHkob2JqLCBrZXksIHtcbiAgICAgIHZhbHVlOiB2YWx1ZSxcbiAgICAgIGVudW1lcmFibGU6IHRydWUsXG4gICAgICBjb25maWd1cmFibGU6IHRydWUsXG4gICAgICB3cml0YWJsZTogdHJ1ZVxuICAgIH0pO1xuICAgIHJldHVybiBvYmpba2V5XTtcbiAgfVxuICB0cnkge1xuICAgIC8vIElFIDggaGFzIGEgYnJva2VuIE9iamVjdC5kZWZpbmVQcm9wZXJ0eSB0aGF0IG9ubHkgd29ya3Mgb24gRE9NIG9iamVjdHMuXG4gICAgZGVmaW5lKHt9LCBcIlwiKTtcbiAgfSBjYXRjaCAoZXJyKSB7XG4gICAgZGVmaW5lID0gZnVuY3Rpb24ob2JqLCBrZXksIHZhbHVlKSB7XG4gICAgICByZXR1cm4gb2JqW2tleV0gPSB2YWx1ZTtcbiAgICB9O1xuICB9XG5cbiAgZnVuY3Rpb24gd3JhcChpbm5lckZuLCBvdXRlckZuLCBzZWxmLCB0cnlMb2NzTGlzdCkge1xuICAgIC8vIElmIG91dGVyRm4gcHJvdmlkZWQgYW5kIG91dGVyRm4ucHJvdG90eXBlIGlzIGEgR2VuZXJhdG9yLCB0aGVuIG91dGVyRm4ucHJvdG90eXBlIGluc3RhbmNlb2YgR2VuZXJhdG9yLlxuICAgIHZhciBwcm90b0dlbmVyYXRvciA9IG91dGVyRm4gJiYgb3V0ZXJGbi5wcm90b3R5cGUgaW5zdGFuY2VvZiBHZW5lcmF0b3IgPyBvdXRlckZuIDogR2VuZXJhdG9yO1xuICAgIHZhciBnZW5lcmF0b3IgPSBPYmplY3QuY3JlYXRlKHByb3RvR2VuZXJhdG9yLnByb3RvdHlwZSk7XG4gICAgdmFyIGNvbnRleHQgPSBuZXcgQ29udGV4dCh0cnlMb2NzTGlzdCB8fCBbXSk7XG5cbiAgICAvLyBUaGUgLl9pbnZva2UgbWV0aG9kIHVuaWZpZXMgdGhlIGltcGxlbWVudGF0aW9ucyBvZiB0aGUgLm5leHQsXG4gICAgLy8gLnRocm93LCBhbmQgLnJldHVybiBtZXRob2RzLlxuICAgIGdlbmVyYXRvci5faW52b2tlID0gbWFrZUludm9rZU1ldGhvZChpbm5lckZuLCBzZWxmLCBjb250ZXh0KTtcblxuICAgIHJldHVybiBnZW5lcmF0b3I7XG4gIH1cbiAgZXhwb3J0cy53cmFwID0gd3JhcDtcblxuICAvLyBUcnkvY2F0Y2ggaGVscGVyIHRvIG1pbmltaXplIGRlb3B0aW1pemF0aW9ucy4gUmV0dXJucyBhIGNvbXBsZXRpb25cbiAgLy8gcmVjb3JkIGxpa2UgY29udGV4dC50cnlFbnRyaWVzW2ldLmNvbXBsZXRpb24uIFRoaXMgaW50ZXJmYWNlIGNvdWxkXG4gIC8vIGhhdmUgYmVlbiAoYW5kIHdhcyBwcmV2aW91c2x5KSBkZXNpZ25lZCB0byB0YWtlIGEgY2xvc3VyZSB0byBiZVxuICAvLyBpbnZva2VkIHdpdGhvdXQgYXJndW1lbnRzLCBidXQgaW4gYWxsIHRoZSBjYXNlcyB3ZSBjYXJlIGFib3V0IHdlXG4gIC8vIGFscmVhZHkgaGF2ZSBhbiBleGlzdGluZyBtZXRob2Qgd2Ugd2FudCB0byBjYWxsLCBzbyB0aGVyZSdzIG5vIG5lZWRcbiAgLy8gdG8gY3JlYXRlIGEgbmV3IGZ1bmN0aW9uIG9iamVjdC4gV2UgY2FuIGV2ZW4gZ2V0IGF3YXkgd2l0aCBhc3N1bWluZ1xuICAvLyB0aGUgbWV0aG9kIHRha2VzIGV4YWN0bHkgb25lIGFyZ3VtZW50LCBzaW5jZSB0aGF0IGhhcHBlbnMgdG8gYmUgdHJ1ZVxuICAvLyBpbiBldmVyeSBjYXNlLCBzbyB3ZSBkb24ndCBoYXZlIHRvIHRvdWNoIHRoZSBhcmd1bWVudHMgb2JqZWN0LiBUaGVcbiAgLy8gb25seSBhZGRpdGlvbmFsIGFsbG9jYXRpb24gcmVxdWlyZWQgaXMgdGhlIGNvbXBsZXRpb24gcmVjb3JkLCB3aGljaFxuICAvLyBoYXMgYSBzdGFibGUgc2hhcGUgYW5kIHNvIGhvcGVmdWxseSBzaG91bGQgYmUgY2hlYXAgdG8gYWxsb2NhdGUuXG4gIGZ1bmN0aW9uIHRyeUNhdGNoKGZuLCBvYmosIGFyZykge1xuICAgIHRyeSB7XG4gICAgICByZXR1cm4geyB0eXBlOiBcIm5vcm1hbFwiLCBhcmc6IGZuLmNhbGwob2JqLCBhcmcpIH07XG4gICAgfSBjYXRjaCAoZXJyKSB7XG4gICAgICByZXR1cm4geyB0eXBlOiBcInRocm93XCIsIGFyZzogZXJyIH07XG4gICAgfVxuICB9XG5cbiAgdmFyIEdlblN0YXRlU3VzcGVuZGVkU3RhcnQgPSBcInN1c3BlbmRlZFN0YXJ0XCI7XG4gIHZhciBHZW5TdGF0ZVN1c3BlbmRlZFlpZWxkID0gXCJzdXNwZW5kZWRZaWVsZFwiO1xuICB2YXIgR2VuU3RhdGVFeGVjdXRpbmcgPSBcImV4ZWN1dGluZ1wiO1xuICB2YXIgR2VuU3RhdGVDb21wbGV0ZWQgPSBcImNvbXBsZXRlZFwiO1xuXG4gIC8vIFJldHVybmluZyB0aGlzIG9iamVjdCBmcm9tIHRoZSBpbm5lckZuIGhhcyB0aGUgc2FtZSBlZmZlY3QgYXNcbiAgLy8gYnJlYWtpbmcgb3V0IG9mIHRoZSBkaXNwYXRjaCBzd2l0Y2ggc3RhdGVtZW50LlxuICB2YXIgQ29udGludWVTZW50aW5lbCA9IHt9O1xuXG4gIC8vIER1bW15IGNvbnN0cnVjdG9yIGZ1bmN0aW9ucyB0aGF0IHdlIHVzZSBhcyB0aGUgLmNvbnN0cnVjdG9yIGFuZFxuICAvLyAuY29uc3RydWN0b3IucHJvdG90eXBlIHByb3BlcnRpZXMgZm9yIGZ1bmN0aW9ucyB0aGF0IHJldHVybiBHZW5lcmF0b3JcbiAgLy8gb2JqZWN0cy4gRm9yIGZ1bGwgc3BlYyBjb21wbGlhbmNlLCB5b3UgbWF5IHdpc2ggdG8gY29uZmlndXJlIHlvdXJcbiAgLy8gbWluaWZpZXIgbm90IHRvIG1hbmdsZSB0aGUgbmFtZXMgb2YgdGhlc2UgdHdvIGZ1bmN0aW9ucy5cbiAgZnVuY3Rpb24gR2VuZXJhdG9yKCkge31cbiAgZnVuY3Rpb24gR2VuZXJhdG9yRnVuY3Rpb24oKSB7fVxuICBmdW5jdGlvbiBHZW5lcmF0b3JGdW5jdGlvblByb3RvdHlwZSgpIHt9XG5cbiAgLy8gVGhpcyBpcyBhIHBvbHlmaWxsIGZvciAlSXRlcmF0b3JQcm90b3R5cGUlIGZvciBlbnZpcm9ubWVudHMgdGhhdFxuICAvLyBkb24ndCBuYXRpdmVseSBzdXBwb3J0IGl0LlxuICB2YXIgSXRlcmF0b3JQcm90b3R5cGUgPSB7fTtcbiAgSXRlcmF0b3JQcm90b3R5cGVbaXRlcmF0b3JTeW1ib2xdID0gZnVuY3Rpb24gKCkge1xuICAgIHJldHVybiB0aGlzO1xuICB9O1xuXG4gIHZhciBnZXRQcm90byA9IE9iamVjdC5nZXRQcm90b3R5cGVPZjtcbiAgdmFyIE5hdGl2ZUl0ZXJhdG9yUHJvdG90eXBlID0gZ2V0UHJvdG8gJiYgZ2V0UHJvdG8oZ2V0UHJvdG8odmFsdWVzKFtdKSkpO1xuICBpZiAoTmF0aXZlSXRlcmF0b3JQcm90b3R5cGUgJiZcbiAgICAgIE5hdGl2ZUl0ZXJhdG9yUHJvdG90eXBlICE9PSBPcCAmJlxuICAgICAgaGFzT3duLmNhbGwoTmF0aXZlSXRlcmF0b3JQcm90b3R5cGUsIGl0ZXJhdG9yU3ltYm9sKSkge1xuICAgIC8vIFRoaXMgZW52aXJvbm1lbnQgaGFzIGEgbmF0aXZlICVJdGVyYXRvclByb3RvdHlwZSU7IHVzZSBpdCBpbnN0ZWFkXG4gICAgLy8gb2YgdGhlIHBvbHlmaWxsLlxuICAgIEl0ZXJhdG9yUHJvdG90eXBlID0gTmF0aXZlSXRlcmF0b3JQcm90b3R5cGU7XG4gIH1cblxuICB2YXIgR3AgPSBHZW5lcmF0b3JGdW5jdGlvblByb3RvdHlwZS5wcm90b3R5cGUgPVxuICAgIEdlbmVyYXRvci5wcm90b3R5cGUgPSBPYmplY3QuY3JlYXRlKEl0ZXJhdG9yUHJvdG90eXBlKTtcbiAgR2VuZXJhdG9yRnVuY3Rpb24ucHJvdG90eXBlID0gR3AuY29uc3RydWN0b3IgPSBHZW5lcmF0b3JGdW5jdGlvblByb3RvdHlwZTtcbiAgR2VuZXJhdG9yRnVuY3Rpb25Qcm90b3R5cGUuY29uc3RydWN0b3IgPSBHZW5lcmF0b3JGdW5jdGlvbjtcbiAgR2VuZXJhdG9yRnVuY3Rpb24uZGlzcGxheU5hbWUgPSBkZWZpbmUoXG4gICAgR2VuZXJhdG9yRnVuY3Rpb25Qcm90b3R5cGUsXG4gICAgdG9TdHJpbmdUYWdTeW1ib2wsXG4gICAgXCJHZW5lcmF0b3JGdW5jdGlvblwiXG4gICk7XG5cbiAgLy8gSGVscGVyIGZvciBkZWZpbmluZyB0aGUgLm5leHQsIC50aHJvdywgYW5kIC5yZXR1cm4gbWV0aG9kcyBvZiB0aGVcbiAgLy8gSXRlcmF0b3IgaW50ZXJmYWNlIGluIHRlcm1zIG9mIGEgc2luZ2xlIC5faW52b2tlIG1ldGhvZC5cbiAgZnVuY3Rpb24gZGVmaW5lSXRlcmF0b3JNZXRob2RzKHByb3RvdHlwZSkge1xuICAgIFtcIm5leHRcIiwgXCJ0aHJvd1wiLCBcInJldHVyblwiXS5mb3JFYWNoKGZ1bmN0aW9uKG1ldGhvZCkge1xuICAgICAgZGVmaW5lKHByb3RvdHlwZSwgbWV0aG9kLCBmdW5jdGlvbihhcmcpIHtcbiAgICAgICAgcmV0dXJuIHRoaXMuX2ludm9rZShtZXRob2QsIGFyZyk7XG4gICAgICB9KTtcbiAgICB9KTtcbiAgfVxuXG4gIGV4cG9ydHMuaXNHZW5lcmF0b3JGdW5jdGlvbiA9IGZ1bmN0aW9uKGdlbkZ1bikge1xuICAgIHZhciBjdG9yID0gdHlwZW9mIGdlbkZ1biA9PT0gXCJmdW5jdGlvblwiICYmIGdlbkZ1bi5jb25zdHJ1Y3RvcjtcbiAgICByZXR1cm4gY3RvclxuICAgICAgPyBjdG9yID09PSBHZW5lcmF0b3JGdW5jdGlvbiB8fFxuICAgICAgICAvLyBGb3IgdGhlIG5hdGl2ZSBHZW5lcmF0b3JGdW5jdGlvbiBjb25zdHJ1Y3RvciwgdGhlIGJlc3Qgd2UgY2FuXG4gICAgICAgIC8vIGRvIGlzIHRvIGNoZWNrIGl0cyAubmFtZSBwcm9wZXJ0eS5cbiAgICAgICAgKGN0b3IuZGlzcGxheU5hbWUgfHwgY3Rvci5uYW1lKSA9PT0gXCJHZW5lcmF0b3JGdW5jdGlvblwiXG4gICAgICA6IGZhbHNlO1xuICB9O1xuXG4gIGV4cG9ydHMubWFyayA9IGZ1bmN0aW9uKGdlbkZ1bikge1xuICAgIGlmIChPYmplY3Quc2V0UHJvdG90eXBlT2YpIHtcbiAgICAgIE9iamVjdC5zZXRQcm90b3R5cGVPZihnZW5GdW4sIEdlbmVyYXRvckZ1bmN0aW9uUHJvdG90eXBlKTtcbiAgICB9IGVsc2Uge1xuICAgICAgZ2VuRnVuLl9fcHJvdG9fXyA9IEdlbmVyYXRvckZ1bmN0aW9uUHJvdG90eXBlO1xuICAgICAgZGVmaW5lKGdlbkZ1biwgdG9TdHJpbmdUYWdTeW1ib2wsIFwiR2VuZXJhdG9yRnVuY3Rpb25cIik7XG4gICAgfVxuICAgIGdlbkZ1bi5wcm90b3R5cGUgPSBPYmplY3QuY3JlYXRlKEdwKTtcbiAgICByZXR1cm4gZ2VuRnVuO1xuICB9O1xuXG4gIC8vIFdpdGhpbiB0aGUgYm9keSBvZiBhbnkgYXN5bmMgZnVuY3Rpb24sIGBhd2FpdCB4YCBpcyB0cmFuc2Zvcm1lZCB0b1xuICAvLyBgeWllbGQgcmVnZW5lcmF0b3JSdW50aW1lLmF3cmFwKHgpYCwgc28gdGhhdCB0aGUgcnVudGltZSBjYW4gdGVzdFxuICAvLyBgaGFzT3duLmNhbGwodmFsdWUsIFwiX19hd2FpdFwiKWAgdG8gZGV0ZXJtaW5lIGlmIHRoZSB5aWVsZGVkIHZhbHVlIGlzXG4gIC8vIG1lYW50IHRvIGJlIGF3YWl0ZWQuXG4gIGV4cG9ydHMuYXdyYXAgPSBmdW5jdGlvbihhcmcpIHtcbiAgICByZXR1cm4geyBfX2F3YWl0OiBhcmcgfTtcbiAgfTtcblxuICBmdW5jdGlvbiBBc3luY0l0ZXJhdG9yKGdlbmVyYXRvciwgUHJvbWlzZUltcGwpIHtcbiAgICBmdW5jdGlvbiBpbnZva2UobWV0aG9kLCBhcmcsIHJlc29sdmUsIHJlamVjdCkge1xuICAgICAgdmFyIHJlY29yZCA9IHRyeUNhdGNoKGdlbmVyYXRvclttZXRob2RdLCBnZW5lcmF0b3IsIGFyZyk7XG4gICAgICBpZiAocmVjb3JkLnR5cGUgPT09IFwidGhyb3dcIikge1xuICAgICAgICByZWplY3QocmVjb3JkLmFyZyk7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICB2YXIgcmVzdWx0ID0gcmVjb3JkLmFyZztcbiAgICAgICAgdmFyIHZhbHVlID0gcmVzdWx0LnZhbHVlO1xuICAgICAgICBpZiAodmFsdWUgJiZcbiAgICAgICAgICAgIHR5cGVvZiB2YWx1ZSA9PT0gXCJvYmplY3RcIiAmJlxuICAgICAgICAgICAgaGFzT3duLmNhbGwodmFsdWUsIFwiX19hd2FpdFwiKSkge1xuICAgICAgICAgIHJldHVybiBQcm9taXNlSW1wbC5yZXNvbHZlKHZhbHVlLl9fYXdhaXQpLnRoZW4oZnVuY3Rpb24odmFsdWUpIHtcbiAgICAgICAgICAgIGludm9rZShcIm5leHRcIiwgdmFsdWUsIHJlc29sdmUsIHJlamVjdCk7XG4gICAgICAgICAgfSwgZnVuY3Rpb24oZXJyKSB7XG4gICAgICAgICAgICBpbnZva2UoXCJ0aHJvd1wiLCBlcnIsIHJlc29sdmUsIHJlamVjdCk7XG4gICAgICAgICAgfSk7XG4gICAgICAgIH1cblxuICAgICAgICByZXR1cm4gUHJvbWlzZUltcGwucmVzb2x2ZSh2YWx1ZSkudGhlbihmdW5jdGlvbih1bndyYXBwZWQpIHtcbiAgICAgICAgICAvLyBXaGVuIGEgeWllbGRlZCBQcm9taXNlIGlzIHJlc29sdmVkLCBpdHMgZmluYWwgdmFsdWUgYmVjb21lc1xuICAgICAgICAgIC8vIHRoZSAudmFsdWUgb2YgdGhlIFByb21pc2U8e3ZhbHVlLGRvbmV9PiByZXN1bHQgZm9yIHRoZVxuICAgICAgICAgIC8vIGN1cnJlbnQgaXRlcmF0aW9uLlxuICAgICAgICAgIHJlc3VsdC52YWx1ZSA9IHVud3JhcHBlZDtcbiAgICAgICAgICByZXNvbHZlKHJlc3VsdCk7XG4gICAgICAgIH0sIGZ1bmN0aW9uKGVycm9yKSB7XG4gICAgICAgICAgLy8gSWYgYSByZWplY3RlZCBQcm9taXNlIHdhcyB5aWVsZGVkLCB0aHJvdyB0aGUgcmVqZWN0aW9uIGJhY2tcbiAgICAgICAgICAvLyBpbnRvIHRoZSBhc3luYyBnZW5lcmF0b3IgZnVuY3Rpb24gc28gaXQgY2FuIGJlIGhhbmRsZWQgdGhlcmUuXG4gICAgICAgICAgcmV0dXJuIGludm9rZShcInRocm93XCIsIGVycm9yLCByZXNvbHZlLCByZWplY3QpO1xuICAgICAgICB9KTtcbiAgICAgIH1cbiAgICB9XG5cbiAgICB2YXIgcHJldmlvdXNQcm9taXNlO1xuXG4gICAgZnVuY3Rpb24gZW5xdWV1ZShtZXRob2QsIGFyZykge1xuICAgICAgZnVuY3Rpb24gY2FsbEludm9rZVdpdGhNZXRob2RBbmRBcmcoKSB7XG4gICAgICAgIHJldHVybiBuZXcgUHJvbWlzZUltcGwoZnVuY3Rpb24ocmVzb2x2ZSwgcmVqZWN0KSB7XG4gICAgICAgICAgaW52b2tlKG1ldGhvZCwgYXJnLCByZXNvbHZlLCByZWplY3QpO1xuICAgICAgICB9KTtcbiAgICAgIH1cblxuICAgICAgcmV0dXJuIHByZXZpb3VzUHJvbWlzZSA9XG4gICAgICAgIC8vIElmIGVucXVldWUgaGFzIGJlZW4gY2FsbGVkIGJlZm9yZSwgdGhlbiB3ZSB3YW50IHRvIHdhaXQgdW50aWxcbiAgICAgICAgLy8gYWxsIHByZXZpb3VzIFByb21pc2VzIGhhdmUgYmVlbiByZXNvbHZlZCBiZWZvcmUgY2FsbGluZyBpbnZva2UsXG4gICAgICAgIC8vIHNvIHRoYXQgcmVzdWx0cyBhcmUgYWx3YXlzIGRlbGl2ZXJlZCBpbiB0aGUgY29ycmVjdCBvcmRlci4gSWZcbiAgICAgICAgLy8gZW5xdWV1ZSBoYXMgbm90IGJlZW4gY2FsbGVkIGJlZm9yZSwgdGhlbiBpdCBpcyBpbXBvcnRhbnQgdG9cbiAgICAgICAgLy8gY2FsbCBpbnZva2UgaW1tZWRpYXRlbHksIHdpdGhvdXQgd2FpdGluZyBvbiBhIGNhbGxiYWNrIHRvIGZpcmUsXG4gICAgICAgIC8vIHNvIHRoYXQgdGhlIGFzeW5jIGdlbmVyYXRvciBmdW5jdGlvbiBoYXMgdGhlIG9wcG9ydHVuaXR5IHRvIGRvXG4gICAgICAgIC8vIGFueSBuZWNlc3Nhcnkgc2V0dXAgaW4gYSBwcmVkaWN0YWJsZSB3YXkuIFRoaXMgcHJlZGljdGFiaWxpdHlcbiAgICAgICAgLy8gaXMgd2h5IHRoZSBQcm9taXNlIGNvbnN0cnVjdG9yIHN5bmNocm9ub3VzbHkgaW52b2tlcyBpdHNcbiAgICAgICAgLy8gZXhlY3V0b3IgY2FsbGJhY2ssIGFuZCB3aHkgYXN5bmMgZnVuY3Rpb25zIHN5bmNocm9ub3VzbHlcbiAgICAgICAgLy8gZXhlY3V0ZSBjb2RlIGJlZm9yZSB0aGUgZmlyc3QgYXdhaXQuIFNpbmNlIHdlIGltcGxlbWVudCBzaW1wbGVcbiAgICAgICAgLy8gYXN5bmMgZnVuY3Rpb25zIGluIHRlcm1zIG9mIGFzeW5jIGdlbmVyYXRvcnMsIGl0IGlzIGVzcGVjaWFsbHlcbiAgICAgICAgLy8gaW1wb3J0YW50IHRvIGdldCB0aGlzIHJpZ2h0LCBldmVuIHRob3VnaCBpdCByZXF1aXJlcyBjYXJlLlxuICAgICAgICBwcmV2aW91c1Byb21pc2UgPyBwcmV2aW91c1Byb21pc2UudGhlbihcbiAgICAgICAgICBjYWxsSW52b2tlV2l0aE1ldGhvZEFuZEFyZyxcbiAgICAgICAgICAvLyBBdm9pZCBwcm9wYWdhdGluZyBmYWlsdXJlcyB0byBQcm9taXNlcyByZXR1cm5lZCBieSBsYXRlclxuICAgICAgICAgIC8vIGludm9jYXRpb25zIG9mIHRoZSBpdGVyYXRvci5cbiAgICAgICAgICBjYWxsSW52b2tlV2l0aE1ldGhvZEFuZEFyZ1xuICAgICAgICApIDogY2FsbEludm9rZVdpdGhNZXRob2RBbmRBcmcoKTtcbiAgICB9XG5cbiAgICAvLyBEZWZpbmUgdGhlIHVuaWZpZWQgaGVscGVyIG1ldGhvZCB0aGF0IGlzIHVzZWQgdG8gaW1wbGVtZW50IC5uZXh0LFxuICAgIC8vIC50aHJvdywgYW5kIC5yZXR1cm4gKHNlZSBkZWZpbmVJdGVyYXRvck1ldGhvZHMpLlxuICAgIHRoaXMuX2ludm9rZSA9IGVucXVldWU7XG4gIH1cblxuICBkZWZpbmVJdGVyYXRvck1ldGhvZHMoQXN5bmNJdGVyYXRvci5wcm90b3R5cGUpO1xuICBBc3luY0l0ZXJhdG9yLnByb3RvdHlwZVthc3luY0l0ZXJhdG9yU3ltYm9sXSA9IGZ1bmN0aW9uICgpIHtcbiAgICByZXR1cm4gdGhpcztcbiAgfTtcbiAgZXhwb3J0cy5Bc3luY0l0ZXJhdG9yID0gQXN5bmNJdGVyYXRvcjtcblxuICAvLyBOb3RlIHRoYXQgc2ltcGxlIGFzeW5jIGZ1bmN0aW9ucyBhcmUgaW1wbGVtZW50ZWQgb24gdG9wIG9mXG4gIC8vIEFzeW5jSXRlcmF0b3Igb2JqZWN0czsgdGhleSBqdXN0IHJldHVybiBhIFByb21pc2UgZm9yIHRoZSB2YWx1ZSBvZlxuICAvLyB0aGUgZmluYWwgcmVzdWx0IHByb2R1Y2VkIGJ5IHRoZSBpdGVyYXRvci5cbiAgZXhwb3J0cy5hc3luYyA9IGZ1bmN0aW9uKGlubmVyRm4sIG91dGVyRm4sIHNlbGYsIHRyeUxvY3NMaXN0LCBQcm9taXNlSW1wbCkge1xuICAgIGlmIChQcm9taXNlSW1wbCA9PT0gdm9pZCAwKSBQcm9taXNlSW1wbCA9IFByb21pc2U7XG5cbiAgICB2YXIgaXRlciA9IG5ldyBBc3luY0l0ZXJhdG9yKFxuICAgICAgd3JhcChpbm5lckZuLCBvdXRlckZuLCBzZWxmLCB0cnlMb2NzTGlzdCksXG4gICAgICBQcm9taXNlSW1wbFxuICAgICk7XG5cbiAgICByZXR1cm4gZXhwb3J0cy5pc0dlbmVyYXRvckZ1bmN0aW9uKG91dGVyRm4pXG4gICAgICA/IGl0ZXIgLy8gSWYgb3V0ZXJGbiBpcyBhIGdlbmVyYXRvciwgcmV0dXJuIHRoZSBmdWxsIGl0ZXJhdG9yLlxuICAgICAgOiBpdGVyLm5leHQoKS50aGVuKGZ1bmN0aW9uKHJlc3VsdCkge1xuICAgICAgICAgIHJldHVybiByZXN1bHQuZG9uZSA/IHJlc3VsdC52YWx1ZSA6IGl0ZXIubmV4dCgpO1xuICAgICAgICB9KTtcbiAgfTtcblxuICBmdW5jdGlvbiBtYWtlSW52b2tlTWV0aG9kKGlubmVyRm4sIHNlbGYsIGNvbnRleHQpIHtcbiAgICB2YXIgc3RhdGUgPSBHZW5TdGF0ZVN1c3BlbmRlZFN0YXJ0O1xuXG4gICAgcmV0dXJuIGZ1bmN0aW9uIGludm9rZShtZXRob2QsIGFyZykge1xuICAgICAgaWYgKHN0YXRlID09PSBHZW5TdGF0ZUV4ZWN1dGluZykge1xuICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXCJHZW5lcmF0b3IgaXMgYWxyZWFkeSBydW5uaW5nXCIpO1xuICAgICAgfVxuXG4gICAgICBpZiAoc3RhdGUgPT09IEdlblN0YXRlQ29tcGxldGVkKSB7XG4gICAgICAgIGlmIChtZXRob2QgPT09IFwidGhyb3dcIikge1xuICAgICAgICAgIHRocm93IGFyZztcbiAgICAgICAgfVxuXG4gICAgICAgIC8vIEJlIGZvcmdpdmluZywgcGVyIDI1LjMuMy4zLjMgb2YgdGhlIHNwZWM6XG4gICAgICAgIC8vIGh0dHBzOi8vcGVvcGxlLm1vemlsbGEub3JnL35qb3JlbmRvcmZmL2VzNi1kcmFmdC5odG1sI3NlYy1nZW5lcmF0b3JyZXN1bWVcbiAgICAgICAgcmV0dXJuIGRvbmVSZXN1bHQoKTtcbiAgICAgIH1cblxuICAgICAgY29udGV4dC5tZXRob2QgPSBtZXRob2Q7XG4gICAgICBjb250ZXh0LmFyZyA9IGFyZztcblxuICAgICAgd2hpbGUgKHRydWUpIHtcbiAgICAgICAgdmFyIGRlbGVnYXRlID0gY29udGV4dC5kZWxlZ2F0ZTtcbiAgICAgICAgaWYgKGRlbGVnYXRlKSB7XG4gICAgICAgICAgdmFyIGRlbGVnYXRlUmVzdWx0ID0gbWF5YmVJbnZva2VEZWxlZ2F0ZShkZWxlZ2F0ZSwgY29udGV4dCk7XG4gICAgICAgICAgaWYgKGRlbGVnYXRlUmVzdWx0KSB7XG4gICAgICAgICAgICBpZiAoZGVsZWdhdGVSZXN1bHQgPT09IENvbnRpbnVlU2VudGluZWwpIGNvbnRpbnVlO1xuICAgICAgICAgICAgcmV0dXJuIGRlbGVnYXRlUmVzdWx0O1xuICAgICAgICAgIH1cbiAgICAgICAgfVxuXG4gICAgICAgIGlmIChjb250ZXh0Lm1ldGhvZCA9PT0gXCJuZXh0XCIpIHtcbiAgICAgICAgICAvLyBTZXR0aW5nIGNvbnRleHQuX3NlbnQgZm9yIGxlZ2FjeSBzdXBwb3J0IG9mIEJhYmVsJ3NcbiAgICAgICAgICAvLyBmdW5jdGlvbi5zZW50IGltcGxlbWVudGF0aW9uLlxuICAgICAgICAgIGNvbnRleHQuc2VudCA9IGNvbnRleHQuX3NlbnQgPSBjb250ZXh0LmFyZztcblxuICAgICAgICB9IGVsc2UgaWYgKGNvbnRleHQubWV0aG9kID09PSBcInRocm93XCIpIHtcbiAgICAgICAgICBpZiAoc3RhdGUgPT09IEdlblN0YXRlU3VzcGVuZGVkU3RhcnQpIHtcbiAgICAgICAgICAgIHN0YXRlID0gR2VuU3RhdGVDb21wbGV0ZWQ7XG4gICAgICAgICAgICB0aHJvdyBjb250ZXh0LmFyZztcbiAgICAgICAgICB9XG5cbiAgICAgICAgICBjb250ZXh0LmRpc3BhdGNoRXhjZXB0aW9uKGNvbnRleHQuYXJnKTtcblxuICAgICAgICB9IGVsc2UgaWYgKGNvbnRleHQubWV0aG9kID09PSBcInJldHVyblwiKSB7XG4gICAgICAgICAgY29udGV4dC5hYnJ1cHQoXCJyZXR1cm5cIiwgY29udGV4dC5hcmcpO1xuICAgICAgICB9XG5cbiAgICAgICAgc3RhdGUgPSBHZW5TdGF0ZUV4ZWN1dGluZztcblxuICAgICAgICB2YXIgcmVjb3JkID0gdHJ5Q2F0Y2goaW5uZXJGbiwgc2VsZiwgY29udGV4dCk7XG4gICAgICAgIGlmIChyZWNvcmQudHlwZSA9PT0gXCJub3JtYWxcIikge1xuICAgICAgICAgIC8vIElmIGFuIGV4Y2VwdGlvbiBpcyB0aHJvd24gZnJvbSBpbm5lckZuLCB3ZSBsZWF2ZSBzdGF0ZSA9PT1cbiAgICAgICAgICAvLyBHZW5TdGF0ZUV4ZWN1dGluZyBhbmQgbG9vcCBiYWNrIGZvciBhbm90aGVyIGludm9jYXRpb24uXG4gICAgICAgICAgc3RhdGUgPSBjb250ZXh0LmRvbmVcbiAgICAgICAgICAgID8gR2VuU3RhdGVDb21wbGV0ZWRcbiAgICAgICAgICAgIDogR2VuU3RhdGVTdXNwZW5kZWRZaWVsZDtcblxuICAgICAgICAgIGlmIChyZWNvcmQuYXJnID09PSBDb250aW51ZVNlbnRpbmVsKSB7XG4gICAgICAgICAgICBjb250aW51ZTtcbiAgICAgICAgICB9XG5cbiAgICAgICAgICByZXR1cm4ge1xuICAgICAgICAgICAgdmFsdWU6IHJlY29yZC5hcmcsXG4gICAgICAgICAgICBkb25lOiBjb250ZXh0LmRvbmVcbiAgICAgICAgICB9O1xuXG4gICAgICAgIH0gZWxzZSBpZiAocmVjb3JkLnR5cGUgPT09IFwidGhyb3dcIikge1xuICAgICAgICAgIHN0YXRlID0gR2VuU3RhdGVDb21wbGV0ZWQ7XG4gICAgICAgICAgLy8gRGlzcGF0Y2ggdGhlIGV4Y2VwdGlvbiBieSBsb29waW5nIGJhY2sgYXJvdW5kIHRvIHRoZVxuICAgICAgICAgIC8vIGNvbnRleHQuZGlzcGF0Y2hFeGNlcHRpb24oY29udGV4dC5hcmcpIGNhbGwgYWJvdmUuXG4gICAgICAgICAgY29udGV4dC5tZXRob2QgPSBcInRocm93XCI7XG4gICAgICAgICAgY29udGV4dC5hcmcgPSByZWNvcmQuYXJnO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgfTtcbiAgfVxuXG4gIC8vIENhbGwgZGVsZWdhdGUuaXRlcmF0b3JbY29udGV4dC5tZXRob2RdKGNvbnRleHQuYXJnKSBhbmQgaGFuZGxlIHRoZVxuICAvLyByZXN1bHQsIGVpdGhlciBieSByZXR1cm5pbmcgYSB7IHZhbHVlLCBkb25lIH0gcmVzdWx0IGZyb20gdGhlXG4gIC8vIGRlbGVnYXRlIGl0ZXJhdG9yLCBvciBieSBtb2RpZnlpbmcgY29udGV4dC5tZXRob2QgYW5kIGNvbnRleHQuYXJnLFxuICAvLyBzZXR0aW5nIGNvbnRleHQuZGVsZWdhdGUgdG8gbnVsbCwgYW5kIHJldHVybmluZyB0aGUgQ29udGludWVTZW50aW5lbC5cbiAgZnVuY3Rpb24gbWF5YmVJbnZva2VEZWxlZ2F0ZShkZWxlZ2F0ZSwgY29udGV4dCkge1xuICAgIHZhciBtZXRob2QgPSBkZWxlZ2F0ZS5pdGVyYXRvcltjb250ZXh0Lm1ldGhvZF07XG4gICAgaWYgKG1ldGhvZCA9PT0gdW5kZWZpbmVkKSB7XG4gICAgICAvLyBBIC50aHJvdyBvciAucmV0dXJuIHdoZW4gdGhlIGRlbGVnYXRlIGl0ZXJhdG9yIGhhcyBubyAudGhyb3dcbiAgICAgIC8vIG1ldGhvZCBhbHdheXMgdGVybWluYXRlcyB0aGUgeWllbGQqIGxvb3AuXG4gICAgICBjb250ZXh0LmRlbGVnYXRlID0gbnVsbDtcblxuICAgICAgaWYgKGNvbnRleHQubWV0aG9kID09PSBcInRocm93XCIpIHtcbiAgICAgICAgLy8gTm90ZTogW1wicmV0dXJuXCJdIG11c3QgYmUgdXNlZCBmb3IgRVMzIHBhcnNpbmcgY29tcGF0aWJpbGl0eS5cbiAgICAgICAgaWYgKGRlbGVnYXRlLml0ZXJhdG9yW1wicmV0dXJuXCJdKSB7XG4gICAgICAgICAgLy8gSWYgdGhlIGRlbGVnYXRlIGl0ZXJhdG9yIGhhcyBhIHJldHVybiBtZXRob2QsIGdpdmUgaXQgYVxuICAgICAgICAgIC8vIGNoYW5jZSB0byBjbGVhbiB1cC5cbiAgICAgICAgICBjb250ZXh0Lm1ldGhvZCA9IFwicmV0dXJuXCI7XG4gICAgICAgICAgY29udGV4dC5hcmcgPSB1bmRlZmluZWQ7XG4gICAgICAgICAgbWF5YmVJbnZva2VEZWxlZ2F0ZShkZWxlZ2F0ZSwgY29udGV4dCk7XG5cbiAgICAgICAgICBpZiAoY29udGV4dC5tZXRob2QgPT09IFwidGhyb3dcIikge1xuICAgICAgICAgICAgLy8gSWYgbWF5YmVJbnZva2VEZWxlZ2F0ZShjb250ZXh0KSBjaGFuZ2VkIGNvbnRleHQubWV0aG9kIGZyb21cbiAgICAgICAgICAgIC8vIFwicmV0dXJuXCIgdG8gXCJ0aHJvd1wiLCBsZXQgdGhhdCBvdmVycmlkZSB0aGUgVHlwZUVycm9yIGJlbG93LlxuICAgICAgICAgICAgcmV0dXJuIENvbnRpbnVlU2VudGluZWw7XG4gICAgICAgICAgfVxuICAgICAgICB9XG5cbiAgICAgICAgY29udGV4dC5tZXRob2QgPSBcInRocm93XCI7XG4gICAgICAgIGNvbnRleHQuYXJnID0gbmV3IFR5cGVFcnJvcihcbiAgICAgICAgICBcIlRoZSBpdGVyYXRvciBkb2VzIG5vdCBwcm92aWRlIGEgJ3Rocm93JyBtZXRob2RcIik7XG4gICAgICB9XG5cbiAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgIH1cblxuICAgIHZhciByZWNvcmQgPSB0cnlDYXRjaChtZXRob2QsIGRlbGVnYXRlLml0ZXJhdG9yLCBjb250ZXh0LmFyZyk7XG5cbiAgICBpZiAocmVjb3JkLnR5cGUgPT09IFwidGhyb3dcIikge1xuICAgICAgY29udGV4dC5tZXRob2QgPSBcInRocm93XCI7XG4gICAgICBjb250ZXh0LmFyZyA9IHJlY29yZC5hcmc7XG4gICAgICBjb250ZXh0LmRlbGVnYXRlID0gbnVsbDtcbiAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgIH1cblxuICAgIHZhciBpbmZvID0gcmVjb3JkLmFyZztcblxuICAgIGlmICghIGluZm8pIHtcbiAgICAgIGNvbnRleHQubWV0aG9kID0gXCJ0aHJvd1wiO1xuICAgICAgY29udGV4dC5hcmcgPSBuZXcgVHlwZUVycm9yKFwiaXRlcmF0b3IgcmVzdWx0IGlzIG5vdCBhbiBvYmplY3RcIik7XG4gICAgICBjb250ZXh0LmRlbGVnYXRlID0gbnVsbDtcbiAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgIH1cblxuICAgIGlmIChpbmZvLmRvbmUpIHtcbiAgICAgIC8vIEFzc2lnbiB0aGUgcmVzdWx0IG9mIHRoZSBmaW5pc2hlZCBkZWxlZ2F0ZSB0byB0aGUgdGVtcG9yYXJ5XG4gICAgICAvLyB2YXJpYWJsZSBzcGVjaWZpZWQgYnkgZGVsZWdhdGUucmVzdWx0TmFtZSAoc2VlIGRlbGVnYXRlWWllbGQpLlxuICAgICAgY29udGV4dFtkZWxlZ2F0ZS5yZXN1bHROYW1lXSA9IGluZm8udmFsdWU7XG5cbiAgICAgIC8vIFJlc3VtZSBleGVjdXRpb24gYXQgdGhlIGRlc2lyZWQgbG9jYXRpb24gKHNlZSBkZWxlZ2F0ZVlpZWxkKS5cbiAgICAgIGNvbnRleHQubmV4dCA9IGRlbGVnYXRlLm5leHRMb2M7XG5cbiAgICAgIC8vIElmIGNvbnRleHQubWV0aG9kIHdhcyBcInRocm93XCIgYnV0IHRoZSBkZWxlZ2F0ZSBoYW5kbGVkIHRoZVxuICAgICAgLy8gZXhjZXB0aW9uLCBsZXQgdGhlIG91dGVyIGdlbmVyYXRvciBwcm9jZWVkIG5vcm1hbGx5LiBJZlxuICAgICAgLy8gY29udGV4dC5tZXRob2Qgd2FzIFwibmV4dFwiLCBmb3JnZXQgY29udGV4dC5hcmcgc2luY2UgaXQgaGFzIGJlZW5cbiAgICAgIC8vIFwiY29uc3VtZWRcIiBieSB0aGUgZGVsZWdhdGUgaXRlcmF0b3IuIElmIGNvbnRleHQubWV0aG9kIHdhc1xuICAgICAgLy8gXCJyZXR1cm5cIiwgYWxsb3cgdGhlIG9yaWdpbmFsIC5yZXR1cm4gY2FsbCB0byBjb250aW51ZSBpbiB0aGVcbiAgICAgIC8vIG91dGVyIGdlbmVyYXRvci5cbiAgICAgIGlmIChjb250ZXh0Lm1ldGhvZCAhPT0gXCJyZXR1cm5cIikge1xuICAgICAgICBjb250ZXh0Lm1ldGhvZCA9IFwibmV4dFwiO1xuICAgICAgICBjb250ZXh0LmFyZyA9IHVuZGVmaW5lZDtcbiAgICAgIH1cblxuICAgIH0gZWxzZSB7XG4gICAgICAvLyBSZS15aWVsZCB0aGUgcmVzdWx0IHJldHVybmVkIGJ5IHRoZSBkZWxlZ2F0ZSBtZXRob2QuXG4gICAgICByZXR1cm4gaW5mbztcbiAgICB9XG5cbiAgICAvLyBUaGUgZGVsZWdhdGUgaXRlcmF0b3IgaXMgZmluaXNoZWQsIHNvIGZvcmdldCBpdCBhbmQgY29udGludWUgd2l0aFxuICAgIC8vIHRoZSBvdXRlciBnZW5lcmF0b3IuXG4gICAgY29udGV4dC5kZWxlZ2F0ZSA9IG51bGw7XG4gICAgcmV0dXJuIENvbnRpbnVlU2VudGluZWw7XG4gIH1cblxuICAvLyBEZWZpbmUgR2VuZXJhdG9yLnByb3RvdHlwZS57bmV4dCx0aHJvdyxyZXR1cm59IGluIHRlcm1zIG9mIHRoZVxuICAvLyB1bmlmaWVkIC5faW52b2tlIGhlbHBlciBtZXRob2QuXG4gIGRlZmluZUl0ZXJhdG9yTWV0aG9kcyhHcCk7XG5cbiAgZGVmaW5lKEdwLCB0b1N0cmluZ1RhZ1N5bWJvbCwgXCJHZW5lcmF0b3JcIik7XG5cbiAgLy8gQSBHZW5lcmF0b3Igc2hvdWxkIGFsd2F5cyByZXR1cm4gaXRzZWxmIGFzIHRoZSBpdGVyYXRvciBvYmplY3Qgd2hlbiB0aGVcbiAgLy8gQEBpdGVyYXRvciBmdW5jdGlvbiBpcyBjYWxsZWQgb24gaXQuIFNvbWUgYnJvd3NlcnMnIGltcGxlbWVudGF0aW9ucyBvZiB0aGVcbiAgLy8gaXRlcmF0b3IgcHJvdG90eXBlIGNoYWluIGluY29ycmVjdGx5IGltcGxlbWVudCB0aGlzLCBjYXVzaW5nIHRoZSBHZW5lcmF0b3JcbiAgLy8gb2JqZWN0IHRvIG5vdCBiZSByZXR1cm5lZCBmcm9tIHRoaXMgY2FsbC4gVGhpcyBlbnN1cmVzIHRoYXQgZG9lc24ndCBoYXBwZW4uXG4gIC8vIFNlZSBodHRwczovL2dpdGh1Yi5jb20vZmFjZWJvb2svcmVnZW5lcmF0b3IvaXNzdWVzLzI3NCBmb3IgbW9yZSBkZXRhaWxzLlxuICBHcFtpdGVyYXRvclN5bWJvbF0gPSBmdW5jdGlvbigpIHtcbiAgICByZXR1cm4gdGhpcztcbiAgfTtcblxuICBHcC50b1N0cmluZyA9IGZ1bmN0aW9uKCkge1xuICAgIHJldHVybiBcIltvYmplY3QgR2VuZXJhdG9yXVwiO1xuICB9O1xuXG4gIGZ1bmN0aW9uIHB1c2hUcnlFbnRyeShsb2NzKSB7XG4gICAgdmFyIGVudHJ5ID0geyB0cnlMb2M6IGxvY3NbMF0gfTtcblxuICAgIGlmICgxIGluIGxvY3MpIHtcbiAgICAgIGVudHJ5LmNhdGNoTG9jID0gbG9jc1sxXTtcbiAgICB9XG5cbiAgICBpZiAoMiBpbiBsb2NzKSB7XG4gICAgICBlbnRyeS5maW5hbGx5TG9jID0gbG9jc1syXTtcbiAgICAgIGVudHJ5LmFmdGVyTG9jID0gbG9jc1szXTtcbiAgICB9XG5cbiAgICB0aGlzLnRyeUVudHJpZXMucHVzaChlbnRyeSk7XG4gIH1cblxuICBmdW5jdGlvbiByZXNldFRyeUVudHJ5KGVudHJ5KSB7XG4gICAgdmFyIHJlY29yZCA9IGVudHJ5LmNvbXBsZXRpb24gfHwge307XG4gICAgcmVjb3JkLnR5cGUgPSBcIm5vcm1hbFwiO1xuICAgIGRlbGV0ZSByZWNvcmQuYXJnO1xuICAgIGVudHJ5LmNvbXBsZXRpb24gPSByZWNvcmQ7XG4gIH1cblxuICBmdW5jdGlvbiBDb250ZXh0KHRyeUxvY3NMaXN0KSB7XG4gICAgLy8gVGhlIHJvb3QgZW50cnkgb2JqZWN0IChlZmZlY3RpdmVseSBhIHRyeSBzdGF0ZW1lbnQgd2l0aG91dCBhIGNhdGNoXG4gICAgLy8gb3IgYSBmaW5hbGx5IGJsb2NrKSBnaXZlcyB1cyBhIHBsYWNlIHRvIHN0b3JlIHZhbHVlcyB0aHJvd24gZnJvbVxuICAgIC8vIGxvY2F0aW9ucyB3aGVyZSB0aGVyZSBpcyBubyBlbmNsb3NpbmcgdHJ5IHN0YXRlbWVudC5cbiAgICB0aGlzLnRyeUVudHJpZXMgPSBbeyB0cnlMb2M6IFwicm9vdFwiIH1dO1xuICAgIHRyeUxvY3NMaXN0LmZvckVhY2gocHVzaFRyeUVudHJ5LCB0aGlzKTtcbiAgICB0aGlzLnJlc2V0KHRydWUpO1xuICB9XG5cbiAgZXhwb3J0cy5rZXlzID0gZnVuY3Rpb24ob2JqZWN0KSB7XG4gICAgdmFyIGtleXMgPSBbXTtcbiAgICBmb3IgKHZhciBrZXkgaW4gb2JqZWN0KSB7XG4gICAgICBrZXlzLnB1c2goa2V5KTtcbiAgICB9XG4gICAga2V5cy5yZXZlcnNlKCk7XG5cbiAgICAvLyBSYXRoZXIgdGhhbiByZXR1cm5pbmcgYW4gb2JqZWN0IHdpdGggYSBuZXh0IG1ldGhvZCwgd2Uga2VlcFxuICAgIC8vIHRoaW5ncyBzaW1wbGUgYW5kIHJldHVybiB0aGUgbmV4dCBmdW5jdGlvbiBpdHNlbGYuXG4gICAgcmV0dXJuIGZ1bmN0aW9uIG5leHQoKSB7XG4gICAgICB3aGlsZSAoa2V5cy5sZW5ndGgpIHtcbiAgICAgICAgdmFyIGtleSA9IGtleXMucG9wKCk7XG4gICAgICAgIGlmIChrZXkgaW4gb2JqZWN0KSB7XG4gICAgICAgICAgbmV4dC52YWx1ZSA9IGtleTtcbiAgICAgICAgICBuZXh0LmRvbmUgPSBmYWxzZTtcbiAgICAgICAgICByZXR1cm4gbmV4dDtcbiAgICAgICAgfVxuICAgICAgfVxuXG4gICAgICAvLyBUbyBhdm9pZCBjcmVhdGluZyBhbiBhZGRpdGlvbmFsIG9iamVjdCwgd2UganVzdCBoYW5nIHRoZSAudmFsdWVcbiAgICAgIC8vIGFuZCAuZG9uZSBwcm9wZXJ0aWVzIG9mZiB0aGUgbmV4dCBmdW5jdGlvbiBvYmplY3QgaXRzZWxmLiBUaGlzXG4gICAgICAvLyBhbHNvIGVuc3VyZXMgdGhhdCB0aGUgbWluaWZpZXIgd2lsbCBub3QgYW5vbnltaXplIHRoZSBmdW5jdGlvbi5cbiAgICAgIG5leHQuZG9uZSA9IHRydWU7XG4gICAgICByZXR1cm4gbmV4dDtcbiAgICB9O1xuICB9O1xuXG4gIGZ1bmN0aW9uIHZhbHVlcyhpdGVyYWJsZSkge1xuICAgIGlmIChpdGVyYWJsZSkge1xuICAgICAgdmFyIGl0ZXJhdG9yTWV0aG9kID0gaXRlcmFibGVbaXRlcmF0b3JTeW1ib2xdO1xuICAgICAgaWYgKGl0ZXJhdG9yTWV0aG9kKSB7XG4gICAgICAgIHJldHVybiBpdGVyYXRvck1ldGhvZC5jYWxsKGl0ZXJhYmxlKTtcbiAgICAgIH1cblxuICAgICAgaWYgKHR5cGVvZiBpdGVyYWJsZS5uZXh0ID09PSBcImZ1bmN0aW9uXCIpIHtcbiAgICAgICAgcmV0dXJuIGl0ZXJhYmxlO1xuICAgICAgfVxuXG4gICAgICBpZiAoIWlzTmFOKGl0ZXJhYmxlLmxlbmd0aCkpIHtcbiAgICAgICAgdmFyIGkgPSAtMSwgbmV4dCA9IGZ1bmN0aW9uIG5leHQoKSB7XG4gICAgICAgICAgd2hpbGUgKCsraSA8IGl0ZXJhYmxlLmxlbmd0aCkge1xuICAgICAgICAgICAgaWYgKGhhc093bi5jYWxsKGl0ZXJhYmxlLCBpKSkge1xuICAgICAgICAgICAgICBuZXh0LnZhbHVlID0gaXRlcmFibGVbaV07XG4gICAgICAgICAgICAgIG5leHQuZG9uZSA9IGZhbHNlO1xuICAgICAgICAgICAgICByZXR1cm4gbmV4dDtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICB9XG5cbiAgICAgICAgICBuZXh0LnZhbHVlID0gdW5kZWZpbmVkO1xuICAgICAgICAgIG5leHQuZG9uZSA9IHRydWU7XG5cbiAgICAgICAgICByZXR1cm4gbmV4dDtcbiAgICAgICAgfTtcblxuICAgICAgICByZXR1cm4gbmV4dC5uZXh0ID0gbmV4dDtcbiAgICAgIH1cbiAgICB9XG5cbiAgICAvLyBSZXR1cm4gYW4gaXRlcmF0b3Igd2l0aCBubyB2YWx1ZXMuXG4gICAgcmV0dXJuIHsgbmV4dDogZG9uZVJlc3VsdCB9O1xuICB9XG4gIGV4cG9ydHMudmFsdWVzID0gdmFsdWVzO1xuXG4gIGZ1bmN0aW9uIGRvbmVSZXN1bHQoKSB7XG4gICAgcmV0dXJuIHsgdmFsdWU6IHVuZGVmaW5lZCwgZG9uZTogdHJ1ZSB9O1xuICB9XG5cbiAgQ29udGV4dC5wcm90b3R5cGUgPSB7XG4gICAgY29uc3RydWN0b3I6IENvbnRleHQsXG5cbiAgICByZXNldDogZnVuY3Rpb24oc2tpcFRlbXBSZXNldCkge1xuICAgICAgdGhpcy5wcmV2ID0gMDtcbiAgICAgIHRoaXMubmV4dCA9IDA7XG4gICAgICAvLyBSZXNldHRpbmcgY29udGV4dC5fc2VudCBmb3IgbGVnYWN5IHN1cHBvcnQgb2YgQmFiZWwnc1xuICAgICAgLy8gZnVuY3Rpb24uc2VudCBpbXBsZW1lbnRhdGlvbi5cbiAgICAgIHRoaXMuc2VudCA9IHRoaXMuX3NlbnQgPSB1bmRlZmluZWQ7XG4gICAgICB0aGlzLmRvbmUgPSBmYWxzZTtcbiAgICAgIHRoaXMuZGVsZWdhdGUgPSBudWxsO1xuXG4gICAgICB0aGlzLm1ldGhvZCA9IFwibmV4dFwiO1xuICAgICAgdGhpcy5hcmcgPSB1bmRlZmluZWQ7XG5cbiAgICAgIHRoaXMudHJ5RW50cmllcy5mb3JFYWNoKHJlc2V0VHJ5RW50cnkpO1xuXG4gICAgICBpZiAoIXNraXBUZW1wUmVzZXQpIHtcbiAgICAgICAgZm9yICh2YXIgbmFtZSBpbiB0aGlzKSB7XG4gICAgICAgICAgLy8gTm90IHN1cmUgYWJvdXQgdGhlIG9wdGltYWwgb3JkZXIgb2YgdGhlc2UgY29uZGl0aW9uczpcbiAgICAgICAgICBpZiAobmFtZS5jaGFyQXQoMCkgPT09IFwidFwiICYmXG4gICAgICAgICAgICAgIGhhc093bi5jYWxsKHRoaXMsIG5hbWUpICYmXG4gICAgICAgICAgICAgICFpc05hTigrbmFtZS5zbGljZSgxKSkpIHtcbiAgICAgICAgICAgIHRoaXNbbmFtZV0gPSB1bmRlZmluZWQ7XG4gICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICB9XG4gICAgfSxcblxuICAgIHN0b3A6IGZ1bmN0aW9uKCkge1xuICAgICAgdGhpcy5kb25lID0gdHJ1ZTtcblxuICAgICAgdmFyIHJvb3RFbnRyeSA9IHRoaXMudHJ5RW50cmllc1swXTtcbiAgICAgIHZhciByb290UmVjb3JkID0gcm9vdEVudHJ5LmNvbXBsZXRpb247XG4gICAgICBpZiAocm9vdFJlY29yZC50eXBlID09PSBcInRocm93XCIpIHtcbiAgICAgICAgdGhyb3cgcm9vdFJlY29yZC5hcmc7XG4gICAgICB9XG5cbiAgICAgIHJldHVybiB0aGlzLnJ2YWw7XG4gICAgfSxcblxuICAgIGRpc3BhdGNoRXhjZXB0aW9uOiBmdW5jdGlvbihleGNlcHRpb24pIHtcbiAgICAgIGlmICh0aGlzLmRvbmUpIHtcbiAgICAgICAgdGhyb3cgZXhjZXB0aW9uO1xuICAgICAgfVxuXG4gICAgICB2YXIgY29udGV4dCA9IHRoaXM7XG4gICAgICBmdW5jdGlvbiBoYW5kbGUobG9jLCBjYXVnaHQpIHtcbiAgICAgICAgcmVjb3JkLnR5cGUgPSBcInRocm93XCI7XG4gICAgICAgIHJlY29yZC5hcmcgPSBleGNlcHRpb247XG4gICAgICAgIGNvbnRleHQubmV4dCA9IGxvYztcblxuICAgICAgICBpZiAoY2F1Z2h0KSB7XG4gICAgICAgICAgLy8gSWYgdGhlIGRpc3BhdGNoZWQgZXhjZXB0aW9uIHdhcyBjYXVnaHQgYnkgYSBjYXRjaCBibG9jayxcbiAgICAgICAgICAvLyB0aGVuIGxldCB0aGF0IGNhdGNoIGJsb2NrIGhhbmRsZSB0aGUgZXhjZXB0aW9uIG5vcm1hbGx5LlxuICAgICAgICAgIGNvbnRleHQubWV0aG9kID0gXCJuZXh0XCI7XG4gICAgICAgICAgY29udGV4dC5hcmcgPSB1bmRlZmluZWQ7XG4gICAgICAgIH1cblxuICAgICAgICByZXR1cm4gISEgY2F1Z2h0O1xuICAgICAgfVxuXG4gICAgICBmb3IgKHZhciBpID0gdGhpcy50cnlFbnRyaWVzLmxlbmd0aCAtIDE7IGkgPj0gMDsgLS1pKSB7XG4gICAgICAgIHZhciBlbnRyeSA9IHRoaXMudHJ5RW50cmllc1tpXTtcbiAgICAgICAgdmFyIHJlY29yZCA9IGVudHJ5LmNvbXBsZXRpb247XG5cbiAgICAgICAgaWYgKGVudHJ5LnRyeUxvYyA9PT0gXCJyb290XCIpIHtcbiAgICAgICAgICAvLyBFeGNlcHRpb24gdGhyb3duIG91dHNpZGUgb2YgYW55IHRyeSBibG9jayB0aGF0IGNvdWxkIGhhbmRsZVxuICAgICAgICAgIC8vIGl0LCBzbyBzZXQgdGhlIGNvbXBsZXRpb24gdmFsdWUgb2YgdGhlIGVudGlyZSBmdW5jdGlvbiB0b1xuICAgICAgICAgIC8vIHRocm93IHRoZSBleGNlcHRpb24uXG4gICAgICAgICAgcmV0dXJuIGhhbmRsZShcImVuZFwiKTtcbiAgICAgICAgfVxuXG4gICAgICAgIGlmIChlbnRyeS50cnlMb2MgPD0gdGhpcy5wcmV2KSB7XG4gICAgICAgICAgdmFyIGhhc0NhdGNoID0gaGFzT3duLmNhbGwoZW50cnksIFwiY2F0Y2hMb2NcIik7XG4gICAgICAgICAgdmFyIGhhc0ZpbmFsbHkgPSBoYXNPd24uY2FsbChlbnRyeSwgXCJmaW5hbGx5TG9jXCIpO1xuXG4gICAgICAgICAgaWYgKGhhc0NhdGNoICYmIGhhc0ZpbmFsbHkpIHtcbiAgICAgICAgICAgIGlmICh0aGlzLnByZXYgPCBlbnRyeS5jYXRjaExvYykge1xuICAgICAgICAgICAgICByZXR1cm4gaGFuZGxlKGVudHJ5LmNhdGNoTG9jLCB0cnVlKTtcbiAgICAgICAgICAgIH0gZWxzZSBpZiAodGhpcy5wcmV2IDwgZW50cnkuZmluYWxseUxvYykge1xuICAgICAgICAgICAgICByZXR1cm4gaGFuZGxlKGVudHJ5LmZpbmFsbHlMb2MpO1xuICAgICAgICAgICAgfVxuXG4gICAgICAgICAgfSBlbHNlIGlmIChoYXNDYXRjaCkge1xuICAgICAgICAgICAgaWYgKHRoaXMucHJldiA8IGVudHJ5LmNhdGNoTG9jKSB7XG4gICAgICAgICAgICAgIHJldHVybiBoYW5kbGUoZW50cnkuY2F0Y2hMb2MsIHRydWUpO1xuICAgICAgICAgICAgfVxuXG4gICAgICAgICAgfSBlbHNlIGlmIChoYXNGaW5hbGx5KSB7XG4gICAgICAgICAgICBpZiAodGhpcy5wcmV2IDwgZW50cnkuZmluYWxseUxvYykge1xuICAgICAgICAgICAgICByZXR1cm4gaGFuZGxlKGVudHJ5LmZpbmFsbHlMb2MpO1xuICAgICAgICAgICAgfVxuXG4gICAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAgIHRocm93IG5ldyBFcnJvcihcInRyeSBzdGF0ZW1lbnQgd2l0aG91dCBjYXRjaCBvciBmaW5hbGx5XCIpO1xuICAgICAgICAgIH1cbiAgICAgICAgfVxuICAgICAgfVxuICAgIH0sXG5cbiAgICBhYnJ1cHQ6IGZ1bmN0aW9uKHR5cGUsIGFyZykge1xuICAgICAgZm9yICh2YXIgaSA9IHRoaXMudHJ5RW50cmllcy5sZW5ndGggLSAxOyBpID49IDA7IC0taSkge1xuICAgICAgICB2YXIgZW50cnkgPSB0aGlzLnRyeUVudHJpZXNbaV07XG4gICAgICAgIGlmIChlbnRyeS50cnlMb2MgPD0gdGhpcy5wcmV2ICYmXG4gICAgICAgICAgICBoYXNPd24uY2FsbChlbnRyeSwgXCJmaW5hbGx5TG9jXCIpICYmXG4gICAgICAgICAgICB0aGlzLnByZXYgPCBlbnRyeS5maW5hbGx5TG9jKSB7XG4gICAgICAgICAgdmFyIGZpbmFsbHlFbnRyeSA9IGVudHJ5O1xuICAgICAgICAgIGJyZWFrO1xuICAgICAgICB9XG4gICAgICB9XG5cbiAgICAgIGlmIChmaW5hbGx5RW50cnkgJiZcbiAgICAgICAgICAodHlwZSA9PT0gXCJicmVha1wiIHx8XG4gICAgICAgICAgIHR5cGUgPT09IFwiY29udGludWVcIikgJiZcbiAgICAgICAgICBmaW5hbGx5RW50cnkudHJ5TG9jIDw9IGFyZyAmJlxuICAgICAgICAgIGFyZyA8PSBmaW5hbGx5RW50cnkuZmluYWxseUxvYykge1xuICAgICAgICAvLyBJZ25vcmUgdGhlIGZpbmFsbHkgZW50cnkgaWYgY29udHJvbCBpcyBub3QganVtcGluZyB0byBhXG4gICAgICAgIC8vIGxvY2F0aW9uIG91dHNpZGUgdGhlIHRyeS9jYXRjaCBibG9jay5cbiAgICAgICAgZmluYWxseUVudHJ5ID0gbnVsbDtcbiAgICAgIH1cblxuICAgICAgdmFyIHJlY29yZCA9IGZpbmFsbHlFbnRyeSA/IGZpbmFsbHlFbnRyeS5jb21wbGV0aW9uIDoge307XG4gICAgICByZWNvcmQudHlwZSA9IHR5cGU7XG4gICAgICByZWNvcmQuYXJnID0gYXJnO1xuXG4gICAgICBpZiAoZmluYWxseUVudHJ5KSB7XG4gICAgICAgIHRoaXMubWV0aG9kID0gXCJuZXh0XCI7XG4gICAgICAgIHRoaXMubmV4dCA9IGZpbmFsbHlFbnRyeS5maW5hbGx5TG9jO1xuICAgICAgICByZXR1cm4gQ29udGludWVTZW50aW5lbDtcbiAgICAgIH1cblxuICAgICAgcmV0dXJuIHRoaXMuY29tcGxldGUocmVjb3JkKTtcbiAgICB9LFxuXG4gICAgY29tcGxldGU6IGZ1bmN0aW9uKHJlY29yZCwgYWZ0ZXJMb2MpIHtcbiAgICAgIGlmIChyZWNvcmQudHlwZSA9PT0gXCJ0aHJvd1wiKSB7XG4gICAgICAgIHRocm93IHJlY29yZC5hcmc7XG4gICAgICB9XG5cbiAgICAgIGlmIChyZWNvcmQudHlwZSA9PT0gXCJicmVha1wiIHx8XG4gICAgICAgICAgcmVjb3JkLnR5cGUgPT09IFwiY29udGludWVcIikge1xuICAgICAgICB0aGlzLm5leHQgPSByZWNvcmQuYXJnO1xuICAgICAgfSBlbHNlIGlmIChyZWNvcmQudHlwZSA9PT0gXCJyZXR1cm5cIikge1xuICAgICAgICB0aGlzLnJ2YWwgPSB0aGlzLmFyZyA9IHJlY29yZC5hcmc7XG4gICAgICAgIHRoaXMubWV0aG9kID0gXCJyZXR1cm5cIjtcbiAgICAgICAgdGhpcy5uZXh0ID0gXCJlbmRcIjtcbiAgICAgIH0gZWxzZSBpZiAocmVjb3JkLnR5cGUgPT09IFwibm9ybWFsXCIgJiYgYWZ0ZXJMb2MpIHtcbiAgICAgICAgdGhpcy5uZXh0ID0gYWZ0ZXJMb2M7XG4gICAgICB9XG5cbiAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgIH0sXG5cbiAgICBmaW5pc2g6IGZ1bmN0aW9uKGZpbmFsbHlMb2MpIHtcbiAgICAgIGZvciAodmFyIGkgPSB0aGlzLnRyeUVudHJpZXMubGVuZ3RoIC0gMTsgaSA+PSAwOyAtLWkpIHtcbiAgICAgICAgdmFyIGVudHJ5ID0gdGhpcy50cnlFbnRyaWVzW2ldO1xuICAgICAgICBpZiAoZW50cnkuZmluYWxseUxvYyA9PT0gZmluYWxseUxvYykge1xuICAgICAgICAgIHRoaXMuY29tcGxldGUoZW50cnkuY29tcGxldGlvbiwgZW50cnkuYWZ0ZXJMb2MpO1xuICAgICAgICAgIHJlc2V0VHJ5RW50cnkoZW50cnkpO1xuICAgICAgICAgIHJldHVybiBDb250aW51ZVNlbnRpbmVsO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgfSxcblxuICAgIFwiY2F0Y2hcIjogZnVuY3Rpb24odHJ5TG9jKSB7XG4gICAgICBmb3IgKHZhciBpID0gdGhpcy50cnlFbnRyaWVzLmxlbmd0aCAtIDE7IGkgPj0gMDsgLS1pKSB7XG4gICAgICAgIHZhciBlbnRyeSA9IHRoaXMudHJ5RW50cmllc1tpXTtcbiAgICAgICAgaWYgKGVudHJ5LnRyeUxvYyA9PT0gdHJ5TG9jKSB7XG4gICAgICAgICAgdmFyIHJlY29yZCA9IGVudHJ5LmNvbXBsZXRpb247XG4gICAgICAgICAgaWYgKHJlY29yZC50eXBlID09PSBcInRocm93XCIpIHtcbiAgICAgICAgICAgIHZhciB0aHJvd24gPSByZWNvcmQuYXJnO1xuICAgICAgICAgICAgcmVzZXRUcnlFbnRyeShlbnRyeSk7XG4gICAgICAgICAgfVxuICAgICAgICAgIHJldHVybiB0aHJvd247XG4gICAgICAgIH1cbiAgICAgIH1cblxuICAgICAgLy8gVGhlIGNvbnRleHQuY2F0Y2ggbWV0aG9kIG11c3Qgb25seSBiZSBjYWxsZWQgd2l0aCBhIGxvY2F0aW9uXG4gICAgICAvLyBhcmd1bWVudCB0aGF0IGNvcnJlc3BvbmRzIHRvIGEga25vd24gY2F0Y2ggYmxvY2suXG4gICAgICB0aHJvdyBuZXcgRXJyb3IoXCJpbGxlZ2FsIGNhdGNoIGF0dGVtcHRcIik7XG4gICAgfSxcblxuICAgIGRlbGVnYXRlWWllbGQ6IGZ1bmN0aW9uKGl0ZXJhYmxlLCByZXN1bHROYW1lLCBuZXh0TG9jKSB7XG4gICAgICB0aGlzLmRlbGVnYXRlID0ge1xuICAgICAgICBpdGVyYXRvcjogdmFsdWVzKGl0ZXJhYmxlKSxcbiAgICAgICAgcmVzdWx0TmFtZTogcmVzdWx0TmFtZSxcbiAgICAgICAgbmV4dExvYzogbmV4dExvY1xuICAgICAgfTtcblxuICAgICAgaWYgKHRoaXMubWV0aG9kID09PSBcIm5leHRcIikge1xuICAgICAgICAvLyBEZWxpYmVyYXRlbHkgZm9yZ2V0IHRoZSBsYXN0IHNlbnQgdmFsdWUgc28gdGhhdCB3ZSBkb24ndFxuICAgICAgICAvLyBhY2NpZGVudGFsbHkgcGFzcyBpdCBvbiB0byB0aGUgZGVsZWdhdGUuXG4gICAgICAgIHRoaXMuYXJnID0gdW5kZWZpbmVkO1xuICAgICAgfVxuXG4gICAgICByZXR1cm4gQ29udGludWVTZW50aW5lbDtcbiAgICB9XG4gIH07XG5cbiAgLy8gUmVnYXJkbGVzcyBvZiB3aGV0aGVyIHRoaXMgc2NyaXB0IGlzIGV4ZWN1dGluZyBhcyBhIENvbW1vbkpTIG1vZHVsZVxuICAvLyBvciBub3QsIHJldHVybiB0aGUgcnVudGltZSBvYmplY3Qgc28gdGhhdCB3ZSBjYW4gZGVjbGFyZSB0aGUgdmFyaWFibGVcbiAgLy8gcmVnZW5lcmF0b3JSdW50aW1lIGluIHRoZSBvdXRlciBzY29wZSwgd2hpY2ggYWxsb3dzIHRoaXMgbW9kdWxlIHRvIGJlXG4gIC8vIGluamVjdGVkIGVhc2lseSBieSBgYmluL3JlZ2VuZXJhdG9yIC0taW5jbHVkZS1ydW50aW1lIHNjcmlwdC5qc2AuXG4gIHJldHVybiBleHBvcnRzO1xuXG59KFxuICAvLyBJZiB0aGlzIHNjcmlwdCBpcyBleGVjdXRpbmcgYXMgYSBDb21tb25KUyBtb2R1bGUsIHVzZSBtb2R1bGUuZXhwb3J0c1xuICAvLyBhcyB0aGUgcmVnZW5lcmF0b3JSdW50aW1lIG5hbWVzcGFjZS4gT3RoZXJ3aXNlIGNyZWF0ZSBhIG5ldyBlbXB0eVxuICAvLyBvYmplY3QuIEVpdGhlciB3YXksIHRoZSByZXN1bHRpbmcgb2JqZWN0IHdpbGwgYmUgdXNlZCB0byBpbml0aWFsaXplXG4gIC8vIHRoZSByZWdlbmVyYXRvclJ1bnRpbWUgdmFyaWFibGUgYXQgdGhlIHRvcCBvZiB0aGlzIGZpbGUuXG4gIHR5cGVvZiBtb2R1bGUgPT09IFwib2JqZWN0XCIgPyBtb2R1bGUuZXhwb3J0cyA6IHt9XG4pKTtcblxudHJ5IHtcbiAgcmVnZW5lcmF0b3JSdW50aW1lID0gcnVudGltZTtcbn0gY2F0Y2ggKGFjY2lkZW50YWxTdHJpY3RNb2RlKSB7XG4gIC8vIFRoaXMgbW9kdWxlIHNob3VsZCBub3QgYmUgcnVubmluZyBpbiBzdHJpY3QgbW9kZSwgc28gdGhlIGFib3ZlXG4gIC8vIGFzc2lnbm1lbnQgc2hvdWxkIGFsd2F5cyB3b3JrIHVubGVzcyBzb21ldGhpbmcgaXMgbWlzY29uZmlndXJlZC4gSnVzdFxuICAvLyBpbiBjYXNlIHJ1bnRpbWUuanMgYWNjaWRlbnRhbGx5IHJ1bnMgaW4gc3RyaWN0IG1vZGUsIHdlIGNhbiBlc2NhcGVcbiAgLy8gc3RyaWN0IG1vZGUgdXNpbmcgYSBnbG9iYWwgRnVuY3Rpb24gY2FsbC4gVGhpcyBjb3VsZCBjb25jZWl2YWJseSBmYWlsXG4gIC8vIGlmIGEgQ29udGVudCBTZWN1cml0eSBQb2xpY3kgZm9yYmlkcyB1c2luZyBGdW5jdGlvbiwgYnV0IGluIHRoYXQgY2FzZVxuICAvLyB0aGUgcHJvcGVyIHNvbHV0aW9uIGlzIHRvIGZpeCB0aGUgYWNjaWRlbnRhbCBzdHJpY3QgbW9kZSBwcm9ibGVtLiBJZlxuICAvLyB5b3UndmUgbWlzY29uZmlndXJlZCB5b3VyIGJ1bmRsZXIgdG8gZm9yY2Ugc3RyaWN0IG1vZGUgYW5kIGFwcGxpZWQgYVxuICAvLyBDU1AgdG8gZm9yYmlkIEZ1bmN0aW9uLCBhbmQgeW91J3JlIG5vdCB3aWxsaW5nIHRvIGZpeCBlaXRoZXIgb2YgdGhvc2VcbiAgLy8gcHJvYmxlbXMsIHBsZWFzZSBkZXRhaWwgeW91ciB1bmlxdWUgcHJlZGljYW1lbnQgaW4gYSBHaXRIdWIgaXNzdWUuXG4gIEZ1bmN0aW9uKFwiclwiLCBcInJlZ2VuZXJhdG9yUnVudGltZSA9IHJcIikocnVudGltZSk7XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxudmFyIGdsb2JhbFRoaXMgPSAobmV3IEZ1bmN0aW9uKCdyZXR1cm4gdGhpczsnKSkoKTtcbmdsb2JhbFRoaXMuZ2xvYmFsVGhpcyA9IGdsb2JhbFRoaXM7XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cbmltcG9ydCAnQGx5bngtanMvaW9zLXBvbHlmaWxsJztcbmltcG9ydCAnQGx5bngtanMvaW9zLXBvbHlmaWxsLXByb21pc2UnO1xuaW1wb3J0ICdyZWdlbmVyYXRvci1ydW50aW1lL3J1bnRpbWUnO1xuaW1wb3J0ICcuL2luZGV4LmNhcmQnO1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbi8vIEdldCB0aGUgZ2xvYmFsIHZhcmlhYmxlIG9mIHRoZSBjdXJyZW50IEpTIHJ1bnRpbWUuXG5jb25zdCBfZ2xvYmFsID0gKGZ1bmN0aW9uICgpIHtcbiAgLy8gZXNsaW50LWRpc2FibGUtbmV4dC1saW5lIG5vLWV2YWxcbiAgcmV0dXJuIHRoaXMgfHwgKDAsIGV2YWwpKCd0aGlzJyk7XG59KSgpO1xuZXhwb3J0IGRlZmF1bHQgX2dsb2JhbDtcbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBpc0Z1bmN0aW9uIH0gZnJvbSAnLi91dGlscyc7XG5cbmV4cG9ydCB0eXBlIFNoYXJlZENvbnNvbGUgPSB0eXBlb2YgbmF0aXZlQ29uc29sZSAmIHsgcnVudGltZUlkOiBzdHJpbmcgfTtcblxuLyoqXG4gKiBDcmVhdGUgYSBjb25zb2xlIHRoYXQgd3JhcHBlZCB0aGUgbmF0aXZlQ29uc29sZSB0byBsb2cgd2l0aCBydW50aW1lSWQuXG4gKiBAcGFyYW0gcnVudGltZUlkIFRoZSBydW50aW1lSWQgdG8gYmUgbG9nZ2VkXG4gKlxuICogVGhlIHJ1bnRpbWVJZCBjYW4gYmUgY2hhbmdlZCBieSBzZXR0aW5nIGRpcmVjdGx5LlxuICpcbiAqIEBleGFtcGxlXG4gKiBjb25zdCBzaGFyZWRDb25zb2xlID0gY3JlYXRlU2hhcmVkQ29uc29sZShydW50aW1lSWQpO1xuICovXG5leHBvcnQgZnVuY3Rpb24gY3JlYXRlU2hhcmVkQ29uc29sZShydW50aW1lSWQ/OiBzdHJpbmcpOiBTaGFyZWRDb25zb2xlIHtcbiAgLy8gVE9ETyh6aGFuZ3F1bi4yOSk6IERlbGV0ZSBhbGwgcmVmZXJlbmNlcyB0byBydW50aW1lSWRcbiAgcmV0dXJuIG5hdGl2ZUNvbnNvbGUgYXMgU2hhcmVkQ29uc29sZTtcbn1cblxuY29uc3QgX2dsb2JhbCA9IChmdW5jdGlvbiAoKSB7XG4gIC8vIGVzbGludC1kaXNhYmxlLW5leHQtbGluZSBuby1ldmFsXG4gIHJldHVybiB0aGlzIHx8ICgwLCBldmFsKSgndGhpcycpO1xufSkoKTtcblxuLyoqXG4gKiBUaGlzIGlzIGEgd3JhcHBlciB0byBuYXRpdmVDb25zb2xlIHRoYXQgbG9nIHdpdGggZ3JvdXBJZC5cbiAqXG4gKiBUaGUgZ3JvdXBJZCBkZWZhdWx0cyB0byAnLTEnIGFuZCBjYW4gYmUgY2hhbmdlZC5cbiAqL1xuY29uc3QgZ3JvdXBDb25zb2xlID0gY3JlYXRlU2hhcmVkQ29uc29sZShgZ3JvdXBJZDoke19nbG9iYWwuZ3JvdXBJZCB8fCAnLTEnfWApO1xuXG4vKipcbiAqIEFsbCBjb25zb2xlIGluIGx5bngta2VybmVsIHNob3VsZCB1c2UgdGhpcyBjb25zb2xlXG4gKi9cbmV4cG9ydCBkZWZhdWx0IE5PREVfRU5WID09PSAnZGV2ZWxvcG1lbnQnXG4gID8gZ3JvdXBDb25zb2xlXG4gIDogKG5hdGl2ZUNvbnNvbGUgYXMgU2hhcmVkQ29uc29sZSk7XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuZXhwb3J0IGZ1bmN0aW9uIGhhc1Byb3BlcnR5KG9iamVjdCwgcHJvcGVydHkpOiBib29sZWFuIHtcbiAgLy8gcmV0dXJuIE9iamVjdC5wcm90b3R5cGUuaGFzT3duUHJvcGVydHkuY2FsbChPYmplY3QuZ2V0UHJvdG90eXBlT2Yob2JqZWN0KSwgcHJvcGVydHkpXG4gIHJldHVybiBPYmplY3QucHJvdG90eXBlLmhhc093blByb3BlcnR5LmNhbGwob2JqZWN0IHx8IHt9LCBwcm9wZXJ0eSk7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBnZXREYXRhVHlwZShkYXRhOiBhbnkpOiBzdHJpbmcge1xuICBjb25zdCB0eXBlID0gdHlwZW9mIGRhdGE7XG4gIGlmICh0eXBlICE9PSAnb2JqZWN0JykgcmV0dXJuIHR5cGU7XG4gIGlmIChBcnJheS5pc0FycmF5KGRhdGEpKSByZXR1cm4gJ2FycmF5JztcbiAgaWYgKGRhdGEgPT0gbnVsbCkgcmV0dXJuICdudWxsJztcbiAgaWYgKGRhdGEgaW5zdGFuY2VvZiBEYXRlKSByZXR1cm4gJ2RhdGUnO1xuICBpZiAoZGF0YSBpbnN0YW5jZW9mIFJlZ0V4cCkgcmV0dXJuICdyZWdFeHAnO1xuICByZXR1cm4gJ29iamVjdCc7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBpc1N0cmluZyh2YWw6IHVua25vd24pOiB2YWwgaXMgc3RyaW5nIHtcbiAgcmV0dXJuIHR5cGVvZiB2YWwgPT09ICdzdHJpbmcnO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gaXNPYmplY3QodmFsOiB1bmtub3duKTogYm9vbGVhbiB7XG4gIHJldHVybiBnZXREYXRhVHlwZSh2YWwpID09PSAnb2JqZWN0Jztcbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGlzRnVuY3Rpb24ob2JqOiB1bmtub3duKTogb2JqIGlzIEFueUZ1bmN0aW9uIHtcbiAgY29uc3QgZGF0YVR5cGUgPSBnZXREYXRhVHlwZShvYmopO1xuICByZXR1cm4gZGF0YVR5cGUgPT09ICdmdW5jdGlvbic7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBpc0FycmF5KGFycmF5OiB1bmtub3duKTogYXJyYXkgaXMgQXJyYXk8dW5rbm93bj4ge1xuICByZXR1cm4gZ2V0RGF0YVR5cGUoYXJyYXkpID09PSAnYXJyYXknO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gaXNOdWxsKG86IHVua25vd24pOiBvIGlzIG51bGwge1xuICByZXR1cm4gbyA9PT0gbnVsbDtcbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGlzVW5kZWZpbmVkKG86IHVua25vd24pOiBvIGlzIHVuZGVmaW5lZCB7XG4gIHJldHVybiBvID09PSB2b2lkIDA7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBpc051bGxPclVuZGVmKG86IHVua25vd24pOiBvIGlzIG51bGwgfCB1bmRlZmluZWQge1xuICByZXR1cm4gaXNVbmRlZmluZWQobykgfHwgaXNOdWxsKG8pO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gaXNFcnJvcihvOiB1bmtub3duKTogbyBpcyBFcnJvciB7XG4gIHN3aXRjaCAoT2JqZWN0LnByb3RvdHlwZS50b1N0cmluZy5jYWxsKG8pKSB7XG4gICAgY2FzZSAnW29iamVjdCBFcnJvcl0nOlxuICAgICAgcmV0dXJuIHRydWU7XG4gICAgY2FzZSAnW29iamVjdCBFeGNlcHRpb25dJzpcbiAgICAgIHJldHVybiB0cnVlO1xuICAgIGNhc2UgJ1tvYmplY3QgRE9NRXhjZXB0aW9uXSc6XG4gICAgICByZXR1cm4gdHJ1ZTtcbiAgICBkZWZhdWx0OlxuICAgICAgcmV0dXJuIGlzSW5zdGFuY2VPZihvLCBFcnJvcik7XG4gIH1cbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGlzSW5zdGFuY2VPZjxUIGV4dGVuZHMgRnVuY3Rpb24+KG86IHVua25vd24sIGJhc2U6IFQpOiBvIGlzIFQge1xuICB0cnkge1xuICAgIHJldHVybiBvIGluc3RhbmNlb2YgYmFzZTtcbiAgfSBjYXRjaCAoX2UpIHtcbiAgICByZXR1cm4gZmFsc2U7XG4gIH1cbn1cblxuZXhwb3J0IGNsYXNzIFRoaXJkU2NyaXB0RXJyb3IgZXh0ZW5kcyBFcnJvciB7XG4gIHR5cGU6IHN0cmluZztcbiAgY29uc3RydWN0b3IobXNnOiBhbnkpIHtcbiAgICBzdXBlcihgJHttc2d9YCk7XG4gICAgdGhpcy50eXBlID0gJ1RoaXJkU2NyaXB0RXJyb3InO1xuICB9XG59XG5cbmV4cG9ydCBjbGFzcyBBcHBTZXJ2aWNlU2RrS25vd25FcnJvciBleHRlbmRzIEVycm9yIHtcbiAgdHlwZTogc3RyaW5nO1xuICBjb25zdHJ1Y3Rvcihtc2cpIHtcbiAgICBzdXBlcihgQVBQLVNFUlZJQ0UtU0RLOiArICR7bXNnfWApO1xuICAgIHRoaXMudHlwZSA9ICdBcHBTZXJ2aWNlU2RrS25vd25FcnJvcic7XG4gIH1cbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGd1aWQoKTogc3RyaW5nIHtcbiAgcmV0dXJuICd4eHh4eHh4eC14eHh4LTR4eHgteXh4eC14eHh4eHh4eHh4eHgnLnJlcGxhY2UoL1t4eV0vZywgKGNoYXIpID0+IHtcbiAgICBjb25zdCByYW5kID0gKDE2ICogTWF0aC5yYW5kb20oKSkgfCAwO1xuICAgIHJldHVybiAoY2hhciA9PT0gJ3gnID8gcmFuZCA6ICgzICYgcmFuZCkgfCA4KS50b1N0cmluZygxNik7XG4gIH0pO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gbm9vcCgpOiB2b2lkIHt9XG5cbmV4cG9ydCBmdW5jdGlvbiBmb3JFYWNoUmlnaHQ8VD4oYXJyOiBBcnJheTxUPiwgY2I6ICh2YWx1ZTogVCkgPT4gdm9pZCk6IHZvaWQge1xuICBpZiAoQXJyYXkuaXNBcnJheShhcnIpKSB7XG4gICAgbGV0IGxlbiA9IGFyci5sZW5ndGg7XG4gICAgZm9yIChsZXQgaW5kZXggPSBsZW4gLSAxOyBpbmRleCA+PSAwOyBpbmRleC0tKSB7XG4gICAgICBjYihhcnJbaW5kZXhdKTtcbiAgICB9XG4gIH0gZWxzZSB7XG4gICAgdGhyb3cgbmV3IEVycm9yKCdmb3JFYWNoUmlnaHQgRVJST1I6IGZpcnN0IHBhcmFtcyBtdXN0IGJlIGFycmF5LicpO1xuICB9XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBjYWxsYmFja01lcmdlKF9jYnMpOiB2b2lkIHtcbiAgaWYgKEFycmF5LmlzQXJyYXkoX2NicykpIHtcbiAgICBmb3IgKGxldCBpID0gMCwgbGVuID0gX2Nicy5sZW5ndGg7IGkgPCBsZW47ICsraSkge1xuICAgICAgX2Nic1tpXSgpO1xuICAgIH1cbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IHR0Q29uc29sZSB9IGZyb20gJ0BseW54LWpzL3J1bnRpbWUtc2hhcmVkJztcbmV4cG9ydCB7IFNoYXJlZENvbnNvbGUsIGNyZWF0ZVNoYXJlZENvbnNvbGUgfSBmcm9tICdAbHlueC1qcy9ydW50aW1lLXNoYXJlZCc7XG5leHBvcnQgZGVmYXVsdCB0dENvbnNvbGU7XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuZXhwb3J0IHR5cGUgRXJyb3JOYW1lID1cbiAgfCAnSU5URVJOQUxfUEFSU0VfRVJST1InXG4gIHwgJ0lOVEVSTkFMX1JVTlRJTUVfRVJST1InXG4gIHwgJ1VTRVJfVkFMSURBVEVfRVJST1InXG4gIHwgJ1VTRVJfUlVOVElNRV9FUlJPUidcbiAgfCAnREFUQV9DSEFOR0VfSEFORExFX0VSUk9SJ1xuICB8ICdJTlZPS0VfRVJST1InO1xuXG5leHBvcnQgdHlwZSBFcnJvcktpbmQgPSAnSU5URVJOQUxfRVJST1InIHwgJ1VTRVJfRVJST1InO1xuZXhwb3J0IHR5cGUgRXJyb3JFbnYgPSAnU0VSVklDRSc7XG5cbi8qKlxuICogVGhlIGVudW0gdmFsdWVzIHNob3VsZCBiZSBzeW5jIHdpdGggYGx5bnhfZXJyb3IuaGAuXG4gKi9cbmV4cG9ydCBjb25zdCBlbnVtIEx5bnhFcnJvckxldmVsIHtcbiAgRmF0YWwgPSAwLFxuICBFcnJvcixcbiAgV2Fybixcbn1cblxuZXhwb3J0IGFic3RyYWN0IGNsYXNzIEJhc2VFcnJvciBleHRlbmRzIEVycm9yIHtcbiAgYWJzdHJhY3Qga2luZDogRXJyb3JLaW5kO1xuICBhYnN0cmFjdCBuYW1lOiBFcnJvck5hbWU7XG4gIGVudj86IEVycm9yRW52O1xuICBjb25zdHJ1Y3RvcihtZXNzYWdlOiBzdHJpbmcsIHN0YWNrPzogc3RyaW5nKSB7XG4gICAgc3VwZXIobWVzc2FnZSk7XG4gICAgaWYgKHN0YWNrKSB7XG4gICAgICB0aGlzLnN0YWNrID0gc3RhY2s7XG4gICAgfVxuICB9XG59XG5cbmV4cG9ydCBhYnN0cmFjdCBjbGFzcyBJbnRlcm5hbEVycm9yIGV4dGVuZHMgQmFzZUVycm9yIHtcbiAga2luZCA9ICdJTlRFUk5BTF9FUlJPUicgYXMgY29uc3Q7XG59XG5cbmV4cG9ydCBhYnN0cmFjdCBjbGFzcyBVc2VyRXJyb3IgZXh0ZW5kcyBCYXNlRXJyb3Ige1xuICBraW5kID0gJ1VTRVJfRVJST1InIGFzIGNvbnN0O1xufVxuXG5leHBvcnQgY2xhc3MgVXNlclZhbGlkYXRlRXJyb3IgZXh0ZW5kcyBVc2VyRXJyb3Ige1xuICBuYW1lID0gJ1VTRVJfVkFMSURBVEVfRVJST1InIGFzIGNvbnN0O1xufVxuXG4vKiogZXJyb3IgY29tZXMgZm9ybSB1c2UgY29kZSAqL1xuZXhwb3J0IGNsYXNzIFVzZXJSdW50aW1lRXJyb3IgZXh0ZW5kcyBVc2VyRXJyb3Ige1xuICBuYW1lID0gJ1VTRVJfUlVOVElNRV9FUlJPUicgYXMgY29uc3Q7XG59XG5cbi8qKlxuICogZXJyb3IgZnJvbSBpbnRlcm5hbCBmcmFtZXdvcmtcbiAqL1xuZXhwb3J0IGNsYXNzIEludGVybmFsUnVudGltZUVycm9yIGV4dGVuZHMgSW50ZXJuYWxFcnJvciB7XG4gIG5hbWUgPSAnSU5URVJOQUxfUlVOVElNRV9FUlJPUicgYXMgY29uc3Q7XG59XG5cbi8qKlxuICogZXJyb3IgZnJvbSBsZXB1c05HXG4gKi9cbmV4cG9ydCBjbGFzcyBJbnRlcm5hbExlcHVzTmdFcnJvciBleHRlbmRzIEVycm9yIHtcbiAgbmFtZTogc3RyaW5nO1xuICBzdGFjazogc3RyaW5nO1xuICBjb25zdHJ1Y3RvcihtZXNzYWdlOiBzdHJpbmcsIHN0YWNrPzogc3RyaW5nKSB7XG4gICAgc3VwZXIobWVzc2FnZSk7XG4gICAgaWYgKHN0YWNrKSB7XG4gICAgICB0aGlzLnN0YWNrID0gc3RhY2s7XG4gICAgfVxuICB9XG59XG5cbi8qKiBlcnJvciBjb21lcyBmcm9tIGpzYiBpbnZva2UgICovXG5leHBvcnQgY2xhc3MgSW52b2tlRXJyb3IgZXh0ZW5kcyBJbnRlcm5hbEVycm9yIHtcbiAgbmFtZSA9ICdJTlZPS0VfRVJST1InIGFzIGNvbnN0O1xufVxuXG5leHBvcnQgY2xhc3MgQXBwU2VydmljZUVuZ2luZUtub3duRXJyb3IgZXh0ZW5kcyBFcnJvciB7XG4gIHR5cGU6IHN0cmluZztcbiAgY29uc3RydWN0b3IobXNnKSB7XG4gICAgc3VwZXIoYEFQUC1TRVJWSUNFLUVuZ2luZTogJHttc2d9YCk7XG4gICAgdGhpcy50eXBlID0gJ0FwcFNlcnZpY2VFbmdpbmVLbm93bkVycm9yJztcbiAgfVxufVxuXG5leHBvcnQgaW50ZXJmYWNlIHNvdXJjZU1hcFJlbGVhc2VPYmoge1xuICBuYW1lOiBzdHJpbmc7XG4gIHN0YWNrOiBzdHJpbmc7IC8vIGRldGFpbCBzdGFjayBvZiBlcnJvclxuICBtZXNzYWdlOiBzdHJpbmc7IC8vIHRoZSBzb3VyY2VNYXBSZWxlYXNlSWQsIHN1Y2ggYXMgXCJkNzMxNjAxMTllZjdlNzc3NzYyNDZjYWNhMmE3Yjk4ZVwiXG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuZXhwb3J0IGNvbnN0IERFRkFVTFRfRU5UUlkgPSAnX19DYXJkX18nO1xuZXhwb3J0IGNvbnN0IEFQUF9TRVJWSUNFX05BTUUgPSAnYXBwLXNlcnZpY2UuanMnO1xuZXhwb3J0IGNvbnN0IFNPVVJDRV9NQVBfUkVMRUFTRV9FUlJPUl9OQU1FID0gJ0x5bnhHZXRTb3VyY2VNYXBSZWxlYXNlRXJyb3InO1xuZXhwb3J0IGludGVyZmFjZSBSVU5fVFlQRSB7XG4gIGZpbGVuYW1lOiBzdHJpbmc7XG4gIC8qKiBSZXBsYWNlIHRoZSBjb2RlIHdpdGggdGhlIGNvcnJlc3BvbmRpbmcgY29tbWl0SGFzaCBhZnRlciBjb21waWxhdGlvbiAqL1xuICBzbG90OiBzdHJpbmc7XG5cbiAgLyoqIHNvdXJjZW1hcCByZWxlYXNlIGZvciBrZXJuZWwgKi9cbiAgcmVsZWFzZTogc3RyaW5nO1xufVxuXG5leHBvcnQgY29uc3QgTFlOWF9DT1JFOiBSVU5fVFlQRSA9IHtcbiAgZmlsZW5hbWU6ICdseW54X2NvcmUnLFxuICBzbG90OiBfX0NPTU1JVF9IQVNIX18sXG4gIHJlbGVhc2U6IF9fQlVJTERfVkVSU0lPTl9fLFxufTtcbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgbmF0aXZlQ29uc29sZSBmcm9tICcuLi8uLi9jb21tb24vdHRDb25zb2xlJztcbi8qKlxuICogVGhlIFN1YmplY3QgaW50ZXJmYWNlIGRlY2xhcmVzIGEgc2V0IG9mIG1ldGhvZHMgZm9yIG1hbmFnaW5nIHN1YnNjcmliZXJzLlxuICovXG5pbnRlcmZhY2UgU3ViamVjdCB7XG4gIHJlZ2lzdGVyT2JzZXJ2ZXIob2JzZXJ2ZXI6IEZ1bmN0aW9uKTogdm9pZDtcbiAgcmVtb3ZlT2JzZXJ2ZXIob2JzZXJ2ZXI6IEZ1bmN0aW9uKTogdm9pZDtcbiAgbm90aWZ5RGF0YUNoYW5nZSh2YWx1ZTogYW55KTogdm9pZDtcbn1cblxuLyoqXG4gKiBUaGUgU3ViamVjdCBvd25zIHNvbWUgaW1wb3J0YW50IHN0YXRlIGFuZCBub3RpZmllcyBvYnNlcnZlcnMgd2hlbiB0aGUgc3RhdGVcbiAqIGNoYW5nZXMuXG4gKi9cbmNsYXNzIFNoYXJlRGF0YVN1YmplY3QgaW1wbGVtZW50cyBTdWJqZWN0IHtcbiAgLyoqXG4gICAqIEB0eXBlIHtudW1iZXJ9IEZvciB0aGUgc2FrZSBvZiBzaW1wbGljaXR5LCB0aGUgU3ViamVjdCdzIHN0YXRlLCBlc3NlbnRpYWxcbiAgICogdG8gYWxsIHN1YnNjcmliZXJzLCBpcyBzdG9yZWQgaW4gdGhpcyB2YXJpYWJsZS5cbiAgICovXG4gIHB1YmxpYyBzdGF0ZTogbnVtYmVyO1xuXG4gIC8qKlxuICAgKiBAdHlwZSB7T2JzZXJ2ZXJbXX0gTGlzdCBvZiBzdWJzY3JpYmVycy5cbiAgICpcbiAgICovXG4gIHByaXZhdGUgb2JzZXJ2ZXJzRnVuYzogRnVuY3Rpb25bXSA9IFtdO1xuXG4gIC8qKlxuICAgKiBUaGUgc3Vic2NyaXB0aW9uIG1hbmFnZW1lbnQgbWV0aG9kcy5cbiAgICovXG4gIHB1YmxpYyByZWdpc3Rlck9ic2VydmVyKG9ic2VydmVyOiBGdW5jdGlvbik6IHZvaWQge1xuICAgIGNvbnN0IGlzRXhpc3QgPSB0aGlzLm9ic2VydmVyc0Z1bmMuaW5jbHVkZXMob2JzZXJ2ZXIpO1xuICAgIGlmIChpc0V4aXN0KSB7XG4gICAgICByZXR1cm4gbmF0aXZlQ29uc29sZS5sb2coJ1N1YmplY3Q6IE9ic2VydmVyIGhhcyBiZWVuIGF0dGFjaGVkIGFscmVhZHkuJyk7XG4gICAgfVxuICAgIHRoaXMub2JzZXJ2ZXJzRnVuYy5wdXNoKG9ic2VydmVyKTtcbiAgfVxuXG4gIHB1YmxpYyByZW1vdmVPYnNlcnZlcihvYnNlcnZlcjogRnVuY3Rpb24pOiB2b2lkIHtcbiAgICAvLyBuYXRpdmVDb25zb2xlLmxvZygnU3ViamVjdDogTm9uZXhpc3RlbnQgb2JzZXJ2ZXIuJyk7XG4gICAgY29uc3Qgb2JzZXJ2ZXJJbmRleCA9IHRoaXMub2JzZXJ2ZXJzRnVuYy5pbmRleE9mKG9ic2VydmVyKTtcbiAgICBpZiAob2JzZXJ2ZXJJbmRleCA9PT0gLTEpIHtcbiAgICAgIHJldHVybiBuYXRpdmVDb25zb2xlLmxvZygnU3ViamVjdDogTm9uZXhpc3RlbnQgb2JzZXJ2ZXIuJyk7XG4gICAgfVxuXG4gICAgdGhpcy5vYnNlcnZlcnNGdW5jLnNwbGljZShvYnNlcnZlckluZGV4LCAxKTtcbiAgICAvLyAgIG5hdGl2ZUNvbnNvbGUubG9nKCdTdWJqZWN0OiBEZXRhY2hlZCBhbiBvYnNlcnZlci4nKTtcbiAgfVxuXG4gIHB1YmxpYyBub3RpZnlEYXRhQ2hhbmdlKHZhbHVlOiBhbnkpOiB2b2lkIHtcbiAgICB0aGlzLm9ic2VydmVyc0Z1bmMuZm9yRWFjaCgodG9PYnNlcnZlcikgPT4ge1xuICAgICAgaWYgKHR5cGVvZiB0b09ic2VydmVyID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgIHRyeSB7XG4gICAgICAgICAgdG9PYnNlcnZlcih2YWx1ZSk7XG4gICAgICAgIH0gY2F0Y2ggKGVycm9yKSB7XG4gICAgICAgICAgbmF0aXZlQ29uc29sZS5sb2coXG4gICAgICAgICAgICAnU2hhcmVkRGF0YSBjaGFuZ2UgYW5kIG5vdGlmeURhdGFDaGFuZ2UgZXJyb3IgaW5mbzonICsgZXJyb3JcbiAgICAgICAgICApO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgfSk7XG4gIH1cbn1cblxuZXhwb3J0IHsgU2hhcmVEYXRhU3ViamVjdCB9O1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IERFRkFVTFRfRU5UUlkgfSBmcm9tICcuL2NvbnN0YW50cyc7XG5pbXBvcnQgeyBTaGFyZURhdGFTdWJqZWN0IH0gZnJvbSAnLi4vbW9kdWxlcy9zaGFyZWREYXRhL1NoYXJlRGF0YVN1YmplY3QnO1xuaW1wb3J0IHsgbmF0aXZlR2xvYmFsIGFzIF9nbG9iYWwgfSBmcm9tICdAbHlueC1qcy9ydW50aW1lLXNoYXJlZCc7XG5pbXBvcnQgeyBMeW54TmFwaUxvYWRlciB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcblxuLy8gZm9yIGNhcmQuXG5fZ2xvYmFsLm11bHRpQXBwcyA9IHt9O1xuX2dsb2JhbC5jdXJyZW50QXBwSWQgPSAnJztcbl9nbG9iYWwuZ2xvYkNvbXBvbmVudFJlZ2lzdFBhdGggPSAnJztcbl9nbG9iYWwuc2hhcmVkRGF0YSA9IHt9O1xuX2dsb2JhbC5nbG9iRHluYW1pY0NvbXBvbmVudEVudHJ5ID0gREVGQVVMVF9FTlRSWTtcblxuX2dsb2JhbC5zaGFyZURhdGFTdWJqZWN0ID0gbmV3IFNoYXJlRGF0YVN1YmplY3QoKTtcblxuX2dsb2JhbC5UYXJvTHlueCA9IHt9O1xuLy8gYnVuZGxlIHJ1biB3aXRoIG5vIGV2YWxcbl9nbG9iYWwuYnVuZGxlU3VwcG9ydExvYWRTY3JpcHQgPSB0cnVlO1xuLy8gZm9yIG5hcGlcbl9nbG9iYWwuZ2V0TmFwaUxvYWRlciA9ICgpOiBMeW54TmFwaUxvYWRlciB8IHVuZGVmaW5lZCA9PiB7XG4gIHJldHVybiBfZ2xvYmFsLl9fbHlueE5hcGlMb2FkZXI7XG59O1xuXG5leHBvcnQgY29uc3QgeyBsb2FkU2NyaXB0IH0gPSBfZ2xvYmFsO1xuZXhwb3J0IGRlZmF1bHQgX2dsb2JhbDtcbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgbmF0aXZlQ29uc29sZSBmcm9tICcuL3R0Q29uc29sZSc7XG5sZXQgaXNOYXRpdmVDb25zb2xlSGFzQUxvZzogYm9vbGVhbiB8IHVuZGVmaW5lZDtcblxuZXhwb3J0IGZ1bmN0aW9uIGFsb2coc3RyOiBzdHJpbmcpIHtcbiAgaWYgKCFfX09QRU5fSU5URVJOQUxfTE9HX18pIHtcbiAgICByZXR1cm47XG4gIH1cbiAgaWYgKGlzTmF0aXZlQ29uc29sZUhhc0FMb2cgPT09IHVuZGVmaW5lZCkge1xuICAgIGlzTmF0aXZlQ29uc29sZUhhc0FMb2cgPSB0eXBlb2YgbmF0aXZlQ29uc29sZS5hbG9nID09PSAnZnVuY3Rpb24nO1xuICB9XG4gIGlmIChpc05hdGl2ZUNvbnNvbGVIYXNBTG9nKSB7XG4gICAgbmF0aXZlQ29uc29sZS5hbG9nKCdbTHlueEpTU0RLXScgKyBzdHIpO1xuICB9XG59XG5cbmxldCBpc05hdGl2ZUNvbnNvbGVIYXNSZXBvcnQ6IGJvb2xlYW4gfCB1bmRlZmluZWQ7XG5cbmV4cG9ydCBmdW5jdGlvbiByZXBvcnQoc3RyOiBzdHJpbmcpIHtcbiAgaWYgKCFfX09QRU5fSU5URVJOQUxfTE9HX18pIHtcbiAgICByZXR1cm47XG4gIH1cbiAgaWYgKGlzTmF0aXZlQ29uc29sZUhhc1JlcG9ydCA9PT0gdW5kZWZpbmVkKSB7XG4gICAgaXNOYXRpdmVDb25zb2xlSGFzUmVwb3J0ID0gdHlwZW9mIG5hdGl2ZUNvbnNvbGUucmVwb3J0ID09PSAnZnVuY3Rpb24nO1xuICB9XG4gIGlmIChpc05hdGl2ZUNvbnNvbGVIYXNSZXBvcnQpIHtcbiAgICBuYXRpdmVDb25zb2xlLnJlcG9ydCgnW0x5bnhKU1NES10nICsgc3RyKTtcbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmNvbnN0IG51bWJlclJlZ0V4cCA9IC9cXGQrLztcbmNsYXNzIFZlcnNpb24ge1xuICBtYWpvcjogbnVtYmVyID0gMDtcbiAgbWlub3I6IG51bWJlciA9IDA7XG4gIHJldmlzaW9uOiBudW1iZXIgPSAwO1xuICBidWlsZDogbnVtYmVyID0gMDtcblxuICAvLyB2ZXJzaW9uOiBtYWpvci5taW5vci5yZXZpc2lvbi5idWlsZFxuICBjb25zdHJ1Y3Rvcih2ZXJzaW9uOiBzdHJpbmcpIHtcbiAgICB2ZXJzaW9uID0gU3RyaW5nKHZlcnNpb24pO1xuICAgIFtcbiAgICAgIHRoaXMubWFqb3IgPSAwLFxuICAgICAgdGhpcy5taW5vciA9IDAsXG4gICAgICB0aGlzLnJldmlzaW9uID0gMCxcbiAgICAgIHRoaXMuYnVpbGQgPSAwLFxuICAgIF0gPSB2ZXJzaW9uLnNwbGl0KCcuJykubWFwKCh2KSA9PiB7XG4gICAgICBjb25zdCByZXN1bHQgPSBudW1iZXJSZWdFeHAuZXhlYyh2KTtcbiAgICAgIGlmIChyZXN1bHQgJiYgcmVzdWx0Lmxlbmd0aCA+IDApIHtcbiAgICAgICAgcmV0dXJuICtyZXN1bHRbMF07XG4gICAgICB9XG5cbiAgICAgIHJldHVybiAwO1xuICAgIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIEdyZWF0ZXIgVGhhblxuICAgKiBAcGFyYW0gdmVyc2lvbiB0aGUgdmVyc2lvbiB0byBiZSBjb21wYXJlZFxuICAgKiBAcmV0dXJucyB0aGlzID4gdmVyc2lvblxuICAgKi9cbiAgZ3QodmVyc2lvbjogc3RyaW5nIHwgVmVyc2lvbik6IGJvb2xlYW4ge1xuICAgIGlmICh0eXBlb2YgdmVyc2lvbiA9PT0gJ3N0cmluZycpIHtcbiAgICAgIHZlcnNpb24gPSBuZXcgVmVyc2lvbih2ZXJzaW9uKTtcbiAgICB9XG5cbiAgICBpZiAodGhpcy5tYWpvciA+IHZlcnNpb24ubWFqb3IpIHtcbiAgICAgIHJldHVybiB0cnVlO1xuICAgIH0gZWxzZSBpZiAodGhpcy5tYWpvciA8IHZlcnNpb24ubWFqb3IpIHtcbiAgICAgIHJldHVybiBmYWxzZTtcbiAgICB9XG5cbiAgICBpZiAodGhpcy5taW5vciA+IHZlcnNpb24ubWlub3IpIHtcbiAgICAgIHJldHVybiB0cnVlO1xuICAgIH0gZWxzZSBpZiAodGhpcy5taW5vciA8IHZlcnNpb24ubWlub3IpIHtcbiAgICAgIHJldHVybiBmYWxzZTtcbiAgICB9XG5cbiAgICBpZiAodGhpcy5yZXZpc2lvbiA+IHZlcnNpb24ucmV2aXNpb24pIHtcbiAgICAgIHJldHVybiB0cnVlO1xuICAgIH0gZWxzZSBpZiAodGhpcy5yZXZpc2lvbiA8IHZlcnNpb24ucmV2aXNpb24pIHtcbiAgICAgIHJldHVybiBmYWxzZTtcbiAgICB9XG5cbiAgICBpZiAodGhpcy5idWlsZCA+IHZlcnNpb24uYnVpbGQpIHtcbiAgICAgIHJldHVybiB0cnVlO1xuICAgIH0gZWxzZSBpZiAodGhpcy5idWlsZCA8IHZlcnNpb24uYnVpbGQpIHtcbiAgICAgIHJldHVybiBmYWxzZTtcbiAgICB9XG5cbiAgICAvLyBlcXVhbHNcbiAgICByZXR1cm4gZmFsc2U7XG4gIH1cblxuICAvKipcbiAgICogRVF1YWxcbiAgICogQHBhcmFtIHZlcnNpb24gdGhlIHZlcnNpb24gdG8gYmUgY29tcGFyZWRcbiAgICogQHJldHVybnMgdGhpcyA9PSB2ZXJzaW9uXG4gICAqL1xuICBlcSh2ZXJzaW9uOiBzdHJpbmcgfCBWZXJzaW9uKTogYm9vbGVhbiB7XG4gICAgaWYgKHR5cGVvZiB2ZXJzaW9uID09PSAnc3RyaW5nJykge1xuICAgICAgdmVyc2lvbiA9IG5ldyBWZXJzaW9uKHZlcnNpb24pO1xuICAgIH1cblxuICAgIHJldHVybiAoXG4gICAgICB0aGlzLm1ham9yID09PSB2ZXJzaW9uLm1ham9yICYmXG4gICAgICB0aGlzLm1pbm9yID09PSB2ZXJzaW9uLm1pbm9yICYmXG4gICAgICB0aGlzLnJldmlzaW9uID09PSB2ZXJzaW9uLnJldmlzaW9uICYmXG4gICAgICB0aGlzLmJ1aWxkID09PSB2ZXJzaW9uLmJ1aWxkXG4gICAgKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBMZXNzIFRoYW5cbiAgICogQHBhcmFtIHZlcnNpb24gdGhlIHZlcnNpb24gdG8gYmUgY29tcGFyZWRcbiAgICogQHJldHVybnMgdGhpcyA8IHZlcnNpb25cbiAgICovXG4gIGx0KHZlcnNpb246IHN0cmluZyB8IFZlcnNpb24pOiBib29sZWFuIHtcbiAgICBpZiAodGhpcy5lcSh2ZXJzaW9uKSkge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cblxuICAgIHJldHVybiAhdGhpcy5ndCh2ZXJzaW9uKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBHcmVhdGVyIFRoYW4gb3IgRXF1YWxcbiAgICogQHBhcmFtIHZlcnNpb24gdGhlIHZlcnNpb24gdG8gYmUgY29tcGFyZWRcbiAgICogQHJldHVybnMgdGhpcyA+PSB2ZXJzaW9uXG4gICAqL1xuICBndGUodmVyc2lvbjogc3RyaW5nIHwgVmVyc2lvbik6IGJvb2xlYW4ge1xuICAgIHJldHVybiB0aGlzLmVxKHZlcnNpb24pIHx8IHRoaXMuZ3QodmVyc2lvbik7XG4gIH1cblxuICAvKipcbiAgICogTGVzcyBUaGFuIG9yIEVxdWFsXG4gICAqIEBwYXJhbSB2ZXJzaW9uIHRoZSB2ZXJzaW9uIHRvIGJlIGNvbXBhcmVkXG4gICAqIEByZXR1cm5zIHRoaXMgPD0gdmVyc2lvblxuICAgKi9cbiAgbHRlKHZlcnNpb246IHN0cmluZyB8IFZlcnNpb24pOiBib29sZWFuIHtcbiAgICByZXR1cm4gdGhpcy5lcSh2ZXJzaW9uKSB8fCB0aGlzLmx0KHZlcnNpb24pO1xuICB9XG59XG5cbmV4cG9ydCBkZWZhdWx0IFZlcnNpb247XG5cbmV4cG9ydCBjb25zdCB2ZXJzaW9uMl80ID0gbmV3IFZlcnNpb24oJzIuNCcpO1xuZXhwb3J0IGNvbnN0IHZlcnNpb24yXzcgPSBuZXcgVmVyc2lvbignMi43Jyk7XG5leHBvcnQgY29uc3QgdmVyc2lvbjJfOSA9IG5ldyBWZXJzaW9uKCcyLjknKTtcbmV4cG9ydCBjb25zdCB2ZXJzaW9uMl8xMiA9IG5ldyBWZXJzaW9uKCcyLjEyJyk7XG5leHBvcnQgY29uc3QgdmVyc2lvbjJfMTQgPSBuZXcgVmVyc2lvbignMi4xNCcpO1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCBuYXRpdmVDb25zb2xlIGZyb20gJy4uLy4uL2NvbW1vbi90dENvbnNvbGUnO1xuaW1wb3J0IHsgTFlOWF9DT1JFLCBSVU5fVFlQRSB9IGZyb20gJy4uLy4uL2NvbW1vbic7XG5pbXBvcnQgeyBBcHAsIE5hdGl2ZUFwcCB9IGZyb20gJy4uLy4uL2FwcCc7XG5pbXBvcnQgeyBpc09iamVjdCB9IGZyb20gJ0BseW54LWpzL3J1bnRpbWUtc2hhcmVkJztcbmltcG9ydCB7IEJhc2VFcnJvciwgTHlueEVycm9yTGV2ZWwgfSBmcm9tICcuL2Vycm9ycyc7XG5cbmV4cG9ydCBmdW5jdGlvbiByZXBvcnRFcnJvcihcbiAgZXJyb3I6IEJhc2VFcnJvcixcbiAgbmF0aXZlQXBwOiBOYXRpdmVBcHAsXG4gIG9wdGlvbnM/OiB7XG4gICAgcnVuVHlwZT86IFJVTl9UWVBFO1xuICAgIG9yaWdpbkVycm9yPzogYW55O1xuICAgIF9fc291cmNlbWFwX19yZWxlYXNlX18/OiBzdHJpbmc7XG4gICAgZ2V0U291cmNlTWFwUmVsZWFzZT86ICh1cmw6IHN0cmluZykgPT4gc3RyaW5nO1xuICAgIGVycm9yQ29kZT86IG51bWJlcjtcbiAgICBlcnJvckxldmVsPzogTHlueEVycm9yTGV2ZWw7XG4gIH1cbik6IHZvaWQge1xuICBjb25zdCB7IG9yaWdpbkVycm9yLCBlcnJvckNvZGUsIGVycm9yTGV2ZWwsIHJ1blR5cGUgPSBMWU5YX0NPUkUgfSA9XG4gICAgb3B0aW9ucyA/PyB7fTtcbiAgbmF0aXZlQ29uc29sZS5lcnJvcignVGhlIGZvbGxvd2luZyBlcnJvciBvY2N1cnJlZCBpbiB0aGUgSlNSdW50aW1lOicpO1xuICBuYXRpdmVDb25zb2xlLmVycm9yKGAke2Vycm9yPy5tZXNzYWdlfVxcbiR7ZXJyb3I/LnN0YWNrfWApO1xuICBlcnJvci5jYXVzZSA9IGlzT2JqZWN0KGVycm9yLmNhdXNlKVxuICAgID8gSlNPTi5zdHJpbmdpZnkoZXJyb3IuY2F1c2UpXG4gICAgOiBlcnJvci5jYXVzZTtcbiAgdHJ5IHtcbiAgICBuYXRpdmVBcHAucmVwb3J0RXhjZXB0aW9uKGVycm9yLCB7XG4gICAgICAuLi5ydW5UeXBlLFxuICAgICAgYnVpbGRWZXJzaW9uOiBfX0JVSUxEX1ZFUlNJT05fXyxcbiAgICAgIHZlcnNpb25Db2RlOiBfX1ZFUlNJT05fXyxcbiAgICAgIGVycm9yQ29kZSxcbiAgICAgIGVycm9yTGV2ZWwsXG4gICAgfSk7XG4gIH0gY2F0Y2ggKGVycm9yKSB7XG4gICAgbmF0aXZlQ29uc29sZS5lcnJvcigncmVwb3J0RXJyb3IgZXJyOlxcbicsIGVycm9yKTtcbiAgfVxufVxuXG5leHBvcnQgZnVuY3Rpb24gbGVnYWN5UmVwb3J0RXJyb3IoXG4gIGVycm9yOiBCYXNlRXJyb3IsXG4gIG5hdGl2ZUFwcDogTmF0aXZlQXBwLFxuICBydW5UeXBlID0gTFlOWF9DT1JFLFxuICBvcmlnaW5FcnJvcj86IGFueSxcbiAgcHJveHk/OiBBcHBcbikge1xuICByZXR1cm4gcmVwb3J0RXJyb3IoZXJyb3IsIG5hdGl2ZUFwcCwge1xuICAgIHJ1blR5cGUsXG4gICAgb3JpZ2luRXJyb3IsXG4gICAgX19zb3VyY2VtYXBfX3JlbGVhc2VfXzogcHJveHkuX19zb3VyY2VtYXBfX3JlbGVhc2VfXyxcbiAgfSk7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiByZXBvcnRUaHJvd0Vycm9yKHtcbiAgZXJyb3IsXG4gIG5hdGl2ZUFwcCxcbiAgcnVuVHlwZSA9IExZTlhfQ09SRSxcbiAgcmF3RXJyb3IsXG4gIF9fc291cmNlbWFwX19yZWxlYXNlX18sXG4gIGdldFNvdXJjZU1hcFJlbGVhc2UsXG59OiB7XG4gIGVycm9yOiBCYXNlRXJyb3I7XG4gIG5hdGl2ZUFwcDogTmF0aXZlQXBwO1xuICBydW5UeXBlPzogUlVOX1RZUEU7XG4gIHJhd0Vycm9yOiBvYmplY3Q7XG4gIF9fc291cmNlbWFwX19yZWxlYXNlX18/OiBzdHJpbmc7XG4gIGdldFNvdXJjZU1hcFJlbGVhc2U/OiAodXJsOiBzdHJpbmcpID0+IHN0cmluZztcbn0pOiB2b2lkIHtcbiAgcmVwb3J0RXJyb3IoZXJyb3IsIG5hdGl2ZUFwcCwge1xuICAgIG9yaWdpbkVycm9yOiByYXdFcnJvcixcbiAgICBydW5UeXBlLFxuICAgIF9fc291cmNlbWFwX19yZWxlYXNlX18sXG4gICAgZ2V0U291cmNlTWFwUmVsZWFzZSxcbiAgfSk7XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IG5hdGl2ZUNvbnNvbGUgZnJvbSAnLi4vLi4vY29tbW9uL3R0Q29uc29sZSc7XG5pbXBvcnQgeyBpc0Z1bmN0aW9uLCBub29wIH0gZnJvbSAnQGx5bngtanMvcnVudGltZS1zaGFyZWQnO1xuaW1wb3J0IHsgRXJyb3JLaW5kLCBVc2VyUnVudGltZUVycm9yLCBJbnRlcm5hbFJ1bnRpbWVFcnJvciB9IGZyb20gJy4vZXJyb3JzJztcbmltcG9ydCB7IHJlcG9ydEVycm9yIH0gZnJvbSAnLi9yZXBvcnQtZXJyb3InO1xuaW1wb3J0IHsgUlVOX1RZUEUsIExZTlhfQ09SRSB9IGZyb20gJy4uLy4uL2NvbW1vbic7XG5pbXBvcnQgeyBOYXRpdmVBcHAgfSBmcm9tICcuLi8uLi9hcHAnO1xuXG50eXBlIEluc3RhbmNlID0ge1xuICBfbmF0aXZlQXBwOiBOYXRpdmVBcHA7XG4gIG9uRXJyb3I/OiAoZXJyb3I6IHN0cmluZywgZXJyb3JPYmo6IGFueSkgPT4gdm9pZDtcbiAgX19zb3VyY2VtYXBfX3JlbGVhc2VfXz86IHN0cmluZztcbiAgZ2V0U291cmNlTWFwUmVsZWFzZT86ICh1cmw6IHN0cmluZykgPT4gc3RyaW5nO1xufTtcblxuZXhwb3J0IGZ1bmN0aW9uIHdyYXBVc2VyRnVuY3Rpb248VCBleHRlbmRzIEFueUZ1bmN0aW9uPihcbiAgZGVzYzogc3RyaW5nLFxuICBpbnN0YW5jZTogSW5zdGFuY2UsXG4gIGNhbGxiYWNrOiBULFxuICBydW5UeXBlOiBSVU5fVFlQRSA9IExZTlhfQ09SRVxuKTogVCB7XG4gIGlmICghaXNGdW5jdGlvbihjYWxsYmFjaykpIHJldHVybiBub29wIGFzIFQ7XG4gIHJldHVybiB3cmFwRnVuY3Rpb24oJ1VTRVJfRVJST1InLCBkZXNjLCBjYWxsYmFjaywgaW5zdGFuY2UsIHJ1blR5cGUpIGFzIFQ7XG59XG5mdW5jdGlvbiB3cmFwRnVuY3Rpb24oXG4gIGVycm9yS2luZDogRXJyb3JLaW5kID0gJ0lOVEVSTkFMX0VSUk9SJyxcbiAgZGVzYzogc3RyaW5nLFxuICBjYWxsYmFjazogQW55RnVuY3Rpb24sXG4gIGluc3RhbmNlOiBJbnN0YW5jZSxcbiAgcnVuVHlwZTogUlVOX1RZUEVcbikge1xuICByZXR1cm4gZnVuY3Rpb24gd3JhcEZ1bmN0aW9uSW5uZXIoLi4uYXJncykge1xuICAgIHRyeSB7XG4gICAgICByZXR1cm4gY2FsbGJhY2suYXBwbHkodGhpcywgYXJncyk7XG4gICAgfSBjYXRjaCAoZXJyb3IpIHtcbiAgICAgIGNvbnN0IG1lc3NhZ2UgPSBgJHtkZXNjfSBcXG4ke2Vycm9yLm1lc3NhZ2V9YDtcbiAgICAgIGlmIChcbiAgICAgICAgY2FsbGJhY2submFtZSAhPT0gJ29uRXJyb3InICYmXG4gICAgICAgIHR5cGVvZiBpbnN0YW5jZS5vbkVycm9yID09PSAnZnVuY3Rpb24nXG4gICAgICApIHtcbiAgICAgICAgaW5zdGFuY2Uub25FcnJvcihcbiAgICAgICAgICBgQ2FyZCAke2NhbGxiYWNrLm5hbWV9IGV4ZWMgZXJyb3I6JHttZXNzYWdlfVxcbiR7ZXJyb3Iuc3RhY2t9YCxcbiAgICAgICAgICBlcnJvclxuICAgICAgICApO1xuICAgICAgfVxuICAgICAgY29uc3QgZXJyID1cbiAgICAgICAgZXJyb3JLaW5kID09PSAnSU5URVJOQUxfRVJST1InXG4gICAgICAgICAgPyBuZXcgSW50ZXJuYWxSdW50aW1lRXJyb3IobWVzc2FnZSwgZXJyb3Iuc3RhY2spXG4gICAgICAgICAgOiBuZXcgVXNlclJ1bnRpbWVFcnJvcihtZXNzYWdlLCBlcnJvci5zdGFjayk7XG4gICAgICBuYXRpdmVDb25zb2xlLmxvZyhgd3JhcEVycm9yLSR7ZGVzY31gLCBlcnIpO1xuICAgICAgcmVwb3J0RXJyb3IoZXJyLCBpbnN0YW5jZS5fbmF0aXZlQXBwLCB7XG4gICAgICAgIHJ1blR5cGUsXG4gICAgICAgIF9fc291cmNlbWFwX19yZWxlYXNlX186IGluc3RhbmNlLl9fc291cmNlbWFwX19yZWxlYXNlX18sXG4gICAgICAgIGdldFNvdXJjZU1hcFJlbGVhc2U6IGluc3RhbmNlLmdldFNvdXJjZU1hcFJlbGVhc2UsXG4gICAgICB9KTtcbiAgICB9XG4gIH07XG59XG5leHBvcnQgZnVuY3Rpb24gd3JhcElubmVyRnVuY3Rpb248VCBleHRlbmRzIEFueUZ1bmN0aW9uPihcbiAgZGVzYzogc3RyaW5nLFxuICBpbnN0YW5jZTogSW5zdGFuY2UsXG4gIGNhbGxiYWNrOiBULFxuICBydW5UeXBlOiBSVU5fVFlQRSA9IExZTlhfQ09SRVxuKTogVCB7XG4gIGlmICghaXNGdW5jdGlvbihjYWxsYmFjaykpIHJldHVybiBub29wIGFzIFQ7XG4gIHJldHVybiB3cmFwRnVuY3Rpb24oJ0lOVEVSTkFMX0VSUk9SJywgZGVzYywgY2FsbGJhY2ssIGluc3RhbmNlLCBydW5UeXBlKSBhcyBUO1xufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IGlzRXJyb3IsIGlzU3RyaW5nIH0gZnJvbSAnQGx5bngtanMvcnVudGltZS1zaGFyZWQnO1xuaW1wb3J0IHsgQmFzZUFwcCwgTmF0aXZlQXBwIH0gZnJvbSAnLi4vLi4vYXBwJztcbmltcG9ydCB7IGFsb2cgfSBmcm9tICcuLi8uLi9jb21tb24vbG9nJztcblxuZXhwb3J0IGNsYXNzIFJlcG9ydGVyIHtcbiAgY29uc3RydWN0b3IoXG4gICAgcHJpdmF0ZSBnZXRBcHA6ICgpID0+IEJhc2VBcHAsXG4gICAgcHJpdmF0ZSByZWFkb25seSBnZXROYXRpdmVBcHA6ICgpID0+IE5hdGl2ZUFwcFxuICApIHtcbiAgICB0aGlzLmdldEFwcCA9IGdldEFwcDtcbiAgICB0aGlzLmdldE5hdGl2ZUFwcCA9IGdldE5hdGl2ZUFwcDtcbiAgfVxuXG4gIHB1YmxpYyByZWJpbmQoZ2V0QXBwOiAoKSA9PiBCYXNlQXBwKSB7XG4gICAgdGhpcy5nZXRBcHAgPSBnZXRBcHA7XG4gIH1cblxuICAvLyAvKipcbiAgLy8gICoga2V5IHVybCAtPiB2YWx1ZSBzb3VyY2VtYXBcbiAgLy8gICogc3VwcG9ydCBkaWZmZXJlbnQgc291cmNlbWFwIGZvciBleHRlcm5hbCBqc1xuICAvLyAgKi9cbiAgLy8gc291cmNlbWFwczogUmVjb3JkPHN0cmluZywgc3RyaW5nPiA9IHt9O1xuXG4gIC8qKlxuICAgKiBTZXQgc291cmNlbWFwIHJlbGVhc2Ugd2l0aCBhIG5ld2x5IHRocm93biBlcnJvclxuICAgKiBAcGFyYW0ge0Vycm9yfSBlcnJvclxuICAgKiBUaGUgZXJyb3IgdGhyb3duIGZyb20gdGhlIGZpbGUgdGhhdCB3YW50cyB0byBzZXQgc291cmNlbWFwIHJlbGVhc2UuXG4gICAqIFRoZSB0b3AgZnJhbWUgb2YgYGVycm9yLnN0YWNrYCAqKm11c3QgYmUqKiB0aGUgZmlsZW5hbWUuXG4gICAqIFRoZSBgZXJyb3IubmFtZWAgKiptdXN0IGJlKiogYCdMeW54R2V0U291cmNlTWFwUmVsZWFzZUVycm9yJ2AuXG4gICAqIFRoZSBgZXJyb3IubWVzc2FnZWAgKiptdXN0IGJlKiogdGhlIHNvdXJjZW1hcCByZWxlYXNlLlxuICAgKlxuICAgKiBAZXhhbXBsZVxuICAgKiAoZnVuY3Rpb24gKCkge1xuICAgKiAgIHRyeSB7XG4gICAqICAgICB0aHJvdyBuZXcgRXJyb3Ioc291cmNlbWFwUmVsZWFzZSk7XG4gICAqICAgfSBjYXRjaCAoZSkge1xuICAgKiAgICAgZS5uYW1lID0gJ0x5bnhHZXRTb3VyY2VNYXBSZWxlYXNlRXJyb3InO1xuICAgKiAgICAgdHQuc2V0U291cmNlTWFwUmVsZWFzZShlKTtcbiAgICogICB9XG4gICAqIH0pKClcbiAgICovXG4gIHNldFNvdXJjZU1hcFJlbGVhc2UgPSAoZXJyb3I6IEVycm9yKSA9PiB7XG4gICAgaWYgKFxuICAgICAgaXNFcnJvcihlcnJvcikgJiZcbiAgICAgIGVycm9yLm5hbWUgPT09IEJhc2VBcHAua0dldFNvdXJjZU1hcFJlbGVhc2VFcnJvck5hbWUgJiZcbiAgICAgIGlzU3RyaW5nKGVycm9yLm1lc3NhZ2UpICYmXG4gICAgICBpc1N0cmluZyhlcnJvci5zdGFjaylcbiAgICApIHtcbiAgICAgIHRoaXMuZ2V0TmF0aXZlQXBwKCkuX19TZXRTb3VyY2VNYXBSZWxlYXNlKHtcbiAgICAgICAgbmFtZTogZXJyb3IubmFtZSxcbiAgICAgICAgbWVzc2FnZTogZXJyb3IubWVzc2FnZSxcbiAgICAgICAgc3RhY2s6IGVycm9yLnN0YWNrLFxuICAgICAgfSk7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIGFsb2coYHNldFNvdXJjZU1hcFJlbGVhc2UgZmFpbGVkIHdpdGggZXJyb3I6ICR7SlNPTi5zdHJpbmdpZnkoZXJyb3IpfWApO1xuICB9O1xuXG4gIGdldFNvdXJjZU1hcFJlbGVhc2UgPSAodXJsOiBzdHJpbmcpOiBzdHJpbmcgPT4ge1xuICAgIGxldCByZXQgPSB0aGlzLmdldE5hdGl2ZUFwcCgpLl9fR2V0U291cmNlTWFwUmVsZWFzZSh1cmwpO1xuICAgIGlmICghcmV0KSB7XG4gICAgICByZXQgPSB0aGlzLmdldE5hdGl2ZUFwcCgpLl9fR2V0U291cmNlTWFwUmVsZWFzZShcbiAgICAgICAgQmFzZUFwcC5rRGVmYXVsdFNvdXJjZU1hcFVSTFxuICAgICAgKTtcbiAgICB9XG4gICAgcmV0dXJuIHJldDtcbiAgfTtcbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBBbmltYXRpb24gYXMgSUFuaW1hdGlvbiB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCB7IEtleWZyYW1lRWZmZWN0IH0gZnJvbSAnLi9lZmZlY3QnO1xuXG5leHBvcnQgY29uc3QgZW51bSBBbmltYXRpb25PcGVyYXRpb24ge1xuICBTVEFSVCA9IDAsXG4gIFBMQVksXG4gIFBBVVNFLFxuICBDQU5DRUwsXG4gIEZJTklTSCxcbn1cblxuZXhwb3J0IGNsYXNzIEFuaW1hdGlvbiBpbXBsZW1lbnRzIElBbmltYXRpb24ge1xuICBzdGF0aWMgY291bnQ6IG51bWJlciA9IDA7XG4gIHB1YmxpYyByZWFkb25seSBlZmZlY3Q6IEtleWZyYW1lRWZmZWN0O1xuICBwdWJsaWMgcmVhZG9ubHkgaWQ6IHN0cmluZztcblxuICBjb25zdHJ1Y3RvcihlZmZlY3Q6IEtleWZyYW1lRWZmZWN0KSB7XG4gICAgdGhpcy5lZmZlY3QgPSBlZmZlY3Q7XG4gICAgdGhpcy5pZCA9ICdfX2x5bngtaW5uZXItanMtYW5pbWF0aW9uLScgKyBBbmltYXRpb24uY291bnQrKztcbiAgfVxuXG4gIGNhbmNlbCgpOiB2b2lkIHtcbiAgICB0aGlzLmVmZmVjdC50YXJnZXQuY2FuY2VsQW5pbWF0ZSh0aGlzKTtcbiAgfVxuXG4gIHBhdXNlKCk6IHZvaWQge1xuICAgIHRoaXMuZWZmZWN0LnRhcmdldC5wYXVzZUFuaW1hdGUodGhpcyk7XG4gIH1cblxuICBwbGF5KCk6IHZvaWQge1xuICAgIHRoaXMuZWZmZWN0LnRhcmdldC5wbGF5QW5pbWF0ZSh0aGlzKTtcbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7XG4gIEtleWZyYW1lRWZmZWN0IGFzIElLZXlmcmFtZUVmZmVjdCxcbiAgS2V5ZnJhbWVFZmZlY3RWMiBhcyBJS2V5ZnJhbWVFZmZlY3RWMixcbn0gZnJvbSAnQGx5bngtanMvdHlwZXMnO1xuaW1wb3J0IEVsZW1lbnQgZnJvbSAnLi4vZWxlbWVudCc7XG5cbmV4cG9ydCBjbGFzcyBLZXlmcmFtZUVmZmVjdCBpbXBsZW1lbnRzIElLZXlmcmFtZUVmZmVjdCB7XG4gIHB1YmxpYyByZWFkb25seSB0YXJnZXQ6IEVsZW1lbnQ7XG4gIHB1YmxpYyByZWFkb25seSBrZXlmcmFtZXM6IEFycmF5PFJlY29yZDxzdHJpbmcsIGFueT4+O1xuICBwdWJsaWMgcmVhZG9ubHkgb3B0aW9uczogUmVjb3JkPHN0cmluZywgYW55PjtcblxuICBjb25zdHJ1Y3RvcihcbiAgICB0YXJnZXQ6IEVsZW1lbnQsXG4gICAga2V5ZnJhbWVzOiBBcnJheTxSZWNvcmQ8c3RyaW5nLCBhbnk+PixcbiAgICBvcHRpb25zOiBSZWNvcmQ8c3RyaW5nLCBhbnk+XG4gICkge1xuICAgIHRoaXMudGFyZ2V0ID0gdGFyZ2V0O1xuICAgIHRoaXMua2V5ZnJhbWVzID0ga2V5ZnJhbWVzO1xuICAgIHRoaXMub3B0aW9ucyA9IG9wdGlvbnM7XG4gIH1cbn1cblxuZXhwb3J0IGNsYXNzIEtleWZyYW1lRWZmZWN0VjIgaW1wbGVtZW50cyBJS2V5ZnJhbWVFZmZlY3RWMiB7XG4gIHB1YmxpYyByZWFkb25seSB0YXJnZXQ/OiBFbGVtZW50O1xuICBwdWJsaWMgcmVhZG9ubHkga2V5ZnJhbWVzOiBBcnJheTxSZWNvcmQ8c3RyaW5nLCBhbnk+PjtcbiAgcHVibGljIHJlYWRvbmx5IG9wdGlvbnM6IFJlY29yZDxzdHJpbmcsIGFueT47XG5cbiAgY29uc3RydWN0b3IoXG4gICAga2V5ZnJhbWVzOiBBcnJheTxSZWNvcmQ8c3RyaW5nLCBhbnk+PixcbiAgICBvcHRpb25zOiBSZWNvcmQ8c3RyaW5nLCBhbnk+XG4gICkge1xuICAgIHRoaXMua2V5ZnJhbWVzID0ga2V5ZnJhbWVzO1xuICAgIHRoaXMub3B0aW9ucyA9IG9wdGlvbnM7XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNSBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBBbmltYXRpb25WMiBhcyBJQW5pbWF0aW9uIH0gZnJvbSAnQGx5bngtanMvdHlwZXMnO1xuaW1wb3J0IHsgS2V5ZnJhbWVFZmZlY3RWMiB9IGZyb20gJy4vZWZmZWN0JztcblxuZXhwb3J0IGNsYXNzIEFuaW1hdGlvblYyIGltcGxlbWVudHMgSUFuaW1hdGlvbiB7XG4gIHB1YmxpYyByZWFkb25seSBlZmZlY3Q6IEtleWZyYW1lRWZmZWN0VjI7XG4gIHB1YmxpYyByZWFkb25seSBpZDogc3RyaW5nO1xuXG4gIGNvbnN0cnVjdG9yKFxuICAgIGlkOiBzdHJpbmcsXG4gICAga2V5ZnJhbWVzOiBBcnJheTxSZWNvcmQ8c3RyaW5nLCBhbnk+PixcbiAgICBvcHRpb25zOiBSZWNvcmQ8c3RyaW5nLCBhbnk+XG4gICkge1xuICAgIHRoaXMuaWQgPSBpZDtcbiAgICB0aGlzLmVmZmVjdCA9IG5ldyBLZXlmcmFtZUVmZmVjdFYyKGtleWZyYW1lcywgb3B0aW9ucyk7XG4gIH1cbn1cbiIsICJpbXBvcnQgeyBBbmltYXRpb24sIEFuaW1hdGlvbk9wZXJhdGlvbiwgS2V5ZnJhbWVFZmZlY3QgfSBmcm9tICcuLi9hbmltYXRpb24nO1xuaW1wb3J0IHsgTHlueCB9IGZyb20gJy4uLy4uL2x5bngnO1xuXG4vKipcbiAqIE5hdGl2ZSBFbGVtZW50LCBIZWxkIGJ5IHtAbGluayBFbGVtZW50fSBhbmQgaW50ZXJhY3Rpbmcgd2l0aCBuYXRpdmUuXG4gKi9cbmV4cG9ydCBpbnRlcmZhY2UgTmF0aXZlRWxlbWVudFByb3h5IHtcbiAgYW5pbWF0ZShcbiAgICBvcGVyYXRpb246IEFuaW1hdGlvbk9wZXJhdGlvbixcbiAgICBpZDogc3RyaW5nLFxuICAgIGtleWZyYW1lcz86IFJlY29yZDxzdHJpbmcsIGFueT5bXSxcbiAgICB0aW1pbmdPcHRpb25zPzogUmVjb3JkPHN0cmluZywgYW55PlxuICApOiB2b2lkO1xuICBzZXRQcm9wZXJ0eShwcm9wc05hbWU6IHN0cmluZywgcHJvcHNWYWx1ZTogc3RyaW5nKTogdm9pZDtcbiAgc2V0UHJvcGVydHkocHJvcHM6IFJlY29yZDxzdHJpbmcsIHN0cmluZz4pOiB2b2lkO1xufVxuXG5leHBvcnQgZGVmYXVsdCBjbGFzcyBFbGVtZW50IHtcbiAgcHJpdmF0ZSByZWFkb25seSBfcm9vdDogc3RyaW5nO1xuICBwcml2YXRlIHJlYWRvbmx5IF9pZFNlbGVjdG9yOiBzdHJpbmc7XG4gIHByaXZhdGUgcmVhZG9ubHkgX2x5bng6IEx5bng7XG4gIHByaXZhdGUgX2VsZW1lbnQ6IE5hdGl2ZUVsZW1lbnRQcm94eTtcblxuICBjb25zdHJ1Y3Rvcihyb290OiBzdHJpbmcsIGlkOiBzdHJpbmcsIGx5bnhQcm94eTogTHlueCkge1xuICAgIHRoaXMuX3Jvb3QgPSByb290O1xuICAgIHRoaXMuX2lkU2VsZWN0b3IgPSAnIycgKyBpZDtcbiAgICB0aGlzLl9seW54ID0gbHlueFByb3h5O1xuICAgIHRoaXMuX2VsZW1lbnQgPSB1bmRlZmluZWQ7XG4gIH1cblxuICBwcml2YXRlIGVuc3VyZUVsZW1lbnQoKSB7XG4gICAgaWYgKCF0aGlzLl9lbGVtZW50KSB7XG4gICAgICB0aGlzLl9lbGVtZW50ID0gdGhpcy5fbHlueC5jcmVhdGVFbGVtZW50KHRoaXMuX3Jvb3QsIHRoaXMuX2lkU2VsZWN0b3IpO1xuICAgIH1cbiAgfVxuXG4gIC8vIGtleWZyYW1lczogc2VlIGh0dHBzOi8vZGV2ZWxvcGVyLm1vemlsbGEub3JnL2VuLVVTL2RvY3MvV2ViL0FQSS9XZWJfQW5pbWF0aW9uc19BUEkvS2V5ZnJhbWVfRm9ybWF0c1xuICAvLyAgRWl0aGVyIGFuIGFycmF5IG9mIGtleWZyYW1lIG9iamVjdHMsIG9yIGEga2V5ZnJhbWUgb2JqZWN0IHdob3NlIHByb3BlcnR5IGFyZSBhcnJheXMgb2YgdmFsdWVzIHRvIGl0ZXJhdGUgb3Zlci4gU2VlIEtleWZyYW1lIEZvcm1hdHMgZm9yIG1vcmUgZGV0YWlscy5cbiAgLy9cbiAgLy8gdGltaW5nT3B0aW9uczogc2VlIGh0dHBzOi8vZGV2ZWxvcGVyLm1vemlsbGEub3JnL2VuLVVTL2RvY3MvV2ViL0FQSS9FbGVtZW50L2FuaW1hdGVcbiAgLy8gIGlkIE9wdGlvbmFsOiBBIHByb3BlcnR5IHVuaXF1ZSB0byBhbmltYXRlKCk6IGEgRE9NU3RyaW5nIHdpdGggd2hpY2ggdG8gcmVmZXJlbmNlIHRoZSBhbmltYXRpb24uXG4gIC8vICBkZWxheSBPcHRpb25hbDogVGhlIG51bWJlciBvZiBtaWxsaXNlY29uZHMgdG8gZGVsYXkgdGhlIHN0YXJ0IG9mIHRoZSBhbmltYXRpb24uIERlZmF1bHRzIHRvIDAuXG4gIC8vICBkaXJlY3Rpb24gT3B0aW9uYWw6IFdoZXRoZXIgdGhlIGFuaW1hdGlvbiBydW5zIGZvcndhcmRzIChub3JtYWwpLCBiYWNrd2FyZHMgKHJldmVyc2UpLCBzd2l0Y2hlcyBkaXJlY3Rpb24gYWZ0ZXIgZWFjaCBpdGVyYXRpb24gKGFsdGVybmF0ZSksIG9yIHJ1bnMgYmFja3dhcmRzIGFuZCBzd2l0Y2hlcyBkaXJlY3Rpb24gYWZ0ZXIgZWFjaCBpdGVyYXRpb24gKGFsdGVybmF0ZS1yZXZlcnNlKS4gRGVmYXVsdHMgdG8gXCJub3JtYWxcIi5cbiAgLy8gIGR1cmF0aW9uIE9wdGlvbmFsOiBUaGUgbnVtYmVyIG9mIG1pbGxpc2Vjb25kcyBlYWNoIGl0ZXJhdGlvbiBvZiB0aGUgYW5pbWF0aW9uIHRha2VzIHRvIGNvbXBsZXRlLiBEZWZhdWx0cyB0byAwLiBBbHRob3VnaCB0aGlzIGlzIHRlY2huaWNhbGx5IG9wdGlvbmFsLCBrZWVwIGluIG1pbmQgdGhhdCB5b3VyIGFuaW1hdGlvbiB3aWxsIG5vdCBydW4gaWYgdGhpcyB2YWx1ZSBpcyAwLlxuICAvLyAgZWFzaW5nIE9wdGlvbmFsOiBUaGUgcmF0ZSBvZiB0aGUgYW5pbWF0aW9uJ3MgY2hhbmdlIG92ZXIgdGltZS4gQWNjZXB0cyB0aGUgcHJlLWRlZmluZWQgdmFsdWVzIFwibGluZWFyXCIsIFwiZWFzZVwiLCBcImVhc2UtaW5cIiwgXCJlYXNlLW91dFwiLCBhbmQgXCJlYXNlLWluLW91dFwiLCBvciBhIGN1c3RvbSBcImN1YmljLWJlemllclwiIHZhbHVlIGxpa2UgXCJjdWJpYy1iZXppZXIoMC40MiwgMCwgMC41OCwgMSlcIi4gRGVmYXVsdHMgdG8gXCJsaW5lYXJcIi5cbiAgLy8gIGVuZERlbGF5IE9wdGlvbmFsOiBUaGUgbnVtYmVyIG9mIG1pbGxpc2Vjb25kcyB0byBkZWxheSBhZnRlciB0aGUgZW5kIG9mIGFuIGFuaW1hdGlvbi4gVGhpcyBpcyBwcmltYXJpbHkgb2YgdXNlIHdoZW4gc2VxdWVuY2luZyBhbmltYXRpb25zIGJhc2VkIG9uIHRoZSBlbmQgdGltZSBvZiBhbm90aGVyIGFuaW1hdGlvbi4gRGVmYXVsdHMgdG8gMC5cbiAgLy8gIGZpbGwgT3B0aW9uYWw6IERpY3RhdGVzIHdoZXRoZXIgdGhlIGFuaW1hdGlvbidzIGVmZmVjdHMgc2hvdWxkIGJlIHJlZmxlY3RlZCBieSB0aGUgZWxlbWVudChzKSBwcmlvciB0byBwbGF5aW5nIChcImJhY2t3YXJkc1wiKSwgcmV0YWluZWQgYWZ0ZXIgdGhlIGFuaW1hdGlvbiBoYXMgY29tcGxldGVkIHBsYXlpbmcgKFwiZm9yd2FyZHNcIiksIG9yIGJvdGguIERlZmF1bHRzIHRvIFwibm9uZVwiLlxuICAvLyAgaXRlcmF0aW9uU3RhcnQgT3B0aW9uYWw6IERlc2NyaWJlcyBhdCB3aGF0IHBvaW50IGluIHRoZSBpdGVyYXRpb24gdGhlIGFuaW1hdGlvbiBzaG91bGQgc3RhcnQuIDAuNSB3b3VsZCBpbmRpY2F0ZSBzdGFydGluZyBoYWxmd2F5IHRocm91Z2ggdGhlIGZpcnN0IGl0ZXJhdGlvbiBmb3IgZXhhbXBsZSwgYW5kIHdpdGggdGhpcyB2YWx1ZSBzZXQsIGFuIGFuaW1hdGlvbiB3aXRoIDIgaXRlcmF0aW9ucyB3b3VsZCBlbmQgaGFsZndheSB0aHJvdWdoIGEgdGhpcmQgaXRlcmF0aW9uLiBEZWZhdWx0cyB0byAwLjAuXG4gIC8vIGl0ZXJhdGlvbnMgT3B0aW9uYWw6IFRoZSBudW1iZXIgb2YgdGltZXMgdGhlIGFuaW1hdGlvbiBzaG91bGQgcmVwZWF0LiBEZWZhdWx0cyB0byAxLCBhbmQgY2FuIGFsc28gdGFrZSBhIHZhbHVlIG9mIEluZmluaXR5IHRvIG1ha2UgaXQgcmVwZWF0IGZvciBhcyBsb25nIGFzIHRoZSBlbGVtZW50IGV4aXN0cy5cbiAgYW5pbWF0ZShcbiAgICBrZXlmcmFtZXM6IEFycmF5PFJlY29yZDxzdHJpbmcsIGFueT4+LFxuICAgIHRpbWluZ09wdGlvbnM6IFJlY29yZDxzdHJpbmcsIGFueT5cbiAgKTogQW5pbWF0aW9uIHtcbiAgICB0aGlzLmVuc3VyZUVsZW1lbnQoKTtcbiAgICBsZXQgYW5pID0gbmV3IEFuaW1hdGlvbihuZXcgS2V5ZnJhbWVFZmZlY3QodGhpcywga2V5ZnJhbWVzLCB0aW1pbmdPcHRpb25zKSk7XG4gICAgdGhpcy5fZWxlbWVudC5hbmltYXRlKDAsIGFuaS5pZCwga2V5ZnJhbWVzLCB0aW1pbmdPcHRpb25zKTtcbiAgICByZXR1cm4gYW5pO1xuICB9XG5cbiAgcGxheUFuaW1hdGUoYW5pOiBBbmltYXRpb24pOiB2b2lkIHtcbiAgICB0aGlzLl9lbGVtZW50LmFuaW1hdGUoMSwgYW5pLmlkLCB1bmRlZmluZWQsIHVuZGVmaW5lZCk7XG4gIH1cblxuICBwYXVzZUFuaW1hdGUoYW5pOiBBbmltYXRpb24pOiB2b2lkIHtcbiAgICB0aGlzLl9lbGVtZW50LmFuaW1hdGUoMiwgYW5pLmlkLCB1bmRlZmluZWQsIHVuZGVmaW5lZCk7XG4gIH1cblxuICBjYW5jZWxBbmltYXRlKGFuaTogQW5pbWF0aW9uKTogdm9pZCB7XG4gICAgdGhpcy5fZWxlbWVudC5hbmltYXRlKDMsIGFuaS5pZCwgdW5kZWZpbmVkLCB1bmRlZmluZWQpO1xuICB9XG5cbiAgZmluaXNoQW5pbWF0ZShhbmk6IEFuaW1hdGlvbik6IHZvaWQge1xuICAgIHRoaXMuX2VsZW1lbnQuYW5pbWF0ZSg0LCBhbmkuaWQsIHVuZGVmaW5lZCwgdW5kZWZpbmVkKTtcbiAgfVxuXG4gIHNldFByb3BlcnR5KFxuICAgIHByb3BzT2JqOiBzdHJpbmcgfCBSZWNvcmQ8c3RyaW5nLCBzdHJpbmc+LFxuICAgIHByb3BzVmFsPzogc3RyaW5nXG4gICk6IHZvaWQge1xuICAgIHRoaXMuZW5zdXJlRWxlbWVudCgpO1xuICAgIGlmICh0eXBlb2YgcHJvcHNPYmogPT09ICdzdHJpbmcnICYmIHR5cGVvZiBwcm9wc1ZhbCA9PT0gJ3N0cmluZycpIHtcbiAgICAgIHRoaXMuX2VsZW1lbnQuc2V0UHJvcGVydHkoe1xuICAgICAgICBbcHJvcHNPYmpdOiBwcm9wc1ZhbCxcbiAgICAgIH0pO1xuICAgIH0gZWxzZSBpZiAodHlwZW9mIHByb3BzT2JqID09PSAnb2JqZWN0Jykge1xuICAgICAgdGhpcy5fZWxlbWVudC5zZXRQcm9wZXJ0eShwcm9wc09iaik7XG4gICAgfSBlbHNlIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcihcbiAgICAgICAgYHNldFByb3BlcnR5J3MgcGFyYW0gbXVzdCBiZSBzdHJpbmcgb3Igb2JqZWN0LiBXaGlsZSBjdXJyZW50IHR5cGUgaXMgJHt0eXBlb2YgcHJvcHNPYmp9IGFuZCAke3R5cGVvZiBwcm9wc1ZhbH0uYFxuICAgICAgKTtcbiAgICB9XG4gIH1cbn1cbiIsICJpbXBvcnQgRWxlbWVudCBmcm9tICcuL2VsZW1lbnQnO1xuZXhwb3J0IGRlZmF1bHQgRWxlbWVudDtcblxuZXhwb3J0IHR5cGUgeyBOYXRpdmVFbGVtZW50UHJveHkgfSBmcm9tICcuL2VsZW1lbnQnO1xuIiwgInR5cGUgVHlwZWRBcnJheSA9XG4gIHwgSW50OEFycmF5XG4gIHwgVWludDhBcnJheVxuICB8IFVpbnQ4Q2xhbXBlZEFycmF5XG4gIHwgSW50MTZBcnJheVxuICB8IFVpbnQxNkFycmF5XG4gIHwgSW50MzJBcnJheVxuICB8IFVpbnQzMkFycmF5XG4gIHwgRmxvYXQzMkFycmF5XG4gIHwgRmxvYXQ2NEFycmF5O1xuXG5leHBvcnQgY2xhc3MgVGV4dERlY29kZXIge1xuICBjb25zdHJ1Y3RvcigpIHt9XG5cbiAgZGVjb2RlKGJ1ZmZlcjogQXJyYXlCdWZmZXIgfCBUeXBlZEFycmF5IHwgRGF0YVZpZXcpOiBzdHJpbmcge1xuICAgIGlmIChidWZmZXIuYnl0ZUxlbmd0aCA9PT0gMCkge1xuICAgICAgcmV0dXJuICcnO1xuICAgIH1cblxuICAgIGlmIChidWZmZXIgaW5zdGFuY2VvZiBEYXRhVmlldykge1xuICAgICAgYnVmZmVyID0gYnVmZmVyLmJ1ZmZlci5zbGljZShcbiAgICAgICAgYnVmZmVyLmJ5dGVPZmZzZXQsXG4gICAgICAgIGJ1ZmZlci5ieXRlT2Zmc2V0ICsgYnVmZmVyLmJ5dGVMZW5ndGhcbiAgICAgICk7XG4gICAgfSBlbHNlIGlmIChBcnJheUJ1ZmZlci5pc1ZpZXcoYnVmZmVyKSkge1xuICAgICAgYnVmZmVyID0gYnVmZmVyLmJ1ZmZlcjtcbiAgICB9XG5cbiAgICByZXR1cm4gZ2xvYmFsVGhpcy5UZXh0Q29kZWNIZWxwZXIuZGVjb2RlKGJ1ZmZlcik7XG4gIH1cblxuICBlbmNvZGVJbnRvKCkge1xuICAgIHRocm93IFR5cGVFcnJvcignVGV4dEVuY29kZXIoKS5lbmNvZGVJbnRvIG5vdCBzdXBwb3J0ZWQnKTtcbiAgfVxuXG4gIGdldCBlbmNvZGluZygpIHtcbiAgICByZXR1cm4gJ3V0Zi04JztcbiAgfVxuXG4gIGdldCBmYXRhbCgpIHtcbiAgICByZXR1cm4gZmFsc2U7XG4gIH1cblxuICBnZXQgaWdub3JlQk9NKCkge1xuICAgIHJldHVybiB0cnVlO1xuICB9XG59XG4iLCAiZXhwb3J0IGNsYXNzIFRleHRFbmNvZGVyIHtcbiAgY29uc3RydWN0b3IoKSB7fVxuXG4gIGVuY29kZShzdHI6IHN0cmluZyk6IFVpbnQ4QXJyYXkge1xuICAgIHJldHVybiBuZXcgVWludDhBcnJheShnbG9iYWxUaGlzLlRleHRDb2RlY0hlbHBlci5lbmNvZGUoc3RyKSk7XG4gIH1cblxuICBlbmNvZGVJbnRvKCkge1xuICAgIHRocm93IFR5cGVFcnJvcignVGV4dEVuY29kZXIoKS5lbmNvZGVJbnRvIG5vdCBzdXBwb3J0ZWQnKTtcbiAgfVxuXG4gIGdldCBlbmNvZGluZygpIHtcbiAgICByZXR1cm4gJ3V0Zi04JztcbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IEV2ZW50RW1pdHRlciBhcyBJRXZlbnRFbWl0dGVyIH0gZnJvbSAnQGx5bngtanMvdHlwZXMnO1xuaW1wb3J0IHsgQ2FsbEx5bnhTZXRNb2R1bGUgfSBmcm9tICcuLi9uYXRpdmVNb2R1bGVzJztcblxuZXhwb3J0IGRlZmF1bHQgY2xhc3MgRXZlbnRFbWl0dGVyIGltcGxlbWVudHMgSUV2ZW50RW1pdHRlciB7XG4gIC8vIGVzbGludC1kaXNhYmxlLW5leHQtbGluZSBAdHlwZXNjcmlwdC1lc2xpbnQvcHJlZmVyLXJlYWRvbmx5XG4gIHByaXZhdGUgX2V2ZW50czogTWFwPFxuICAgIHN0cmluZyxcbiAgICB7IGxpc3RlbmVyOiAoLi4uYXJnczogdW5rbm93bltdKSA9PiB2b2lkOyBjb250ZXh0Pzogb2JqZWN0IH1bXVxuICA+O1xuICBwcml2YXRlIF9pbnRlcm5hbF9jYWxsTHlueFNldE1vZHVsZT86IENhbGxMeW54U2V0TW9kdWxlO1xuICBjb25zdHJ1Y3RvcihjYWxsTHlueFNldE1vZHVsZT86IENhbGxMeW54U2V0TW9kdWxlKSB7XG4gICAgdGhpcy5faW50ZXJuYWxfY2FsbEx5bnhTZXRNb2R1bGUgPSBjYWxsTHlueFNldE1vZHVsZTtcbiAgICB0aGlzLl9ldmVudHMgPSBuZXcgTWFwKCk7XG4gIH1cblxuICBnZXRFdmVudHNTaXplKGV2ZW50VHlwZTogc3RyaW5nKTogbnVtYmVyIHtcbiAgICByZXR1cm4gdGhpcy5fZXZlbnRzLmdldChldmVudFR5cGUpPy5sZW5ndGg7XG4gIH1cblxuICBzZXRDYWxsTHlueFNldE1vZHVsZShjYWxsTHlueFNldE1vZHVsZT86IENhbGxMeW54U2V0TW9kdWxlKSB7XG4gICAgdGhpcy5faW50ZXJuYWxfY2FsbEx5bnhTZXRNb2R1bGUgPSBjYWxsTHlueFNldE1vZHVsZTtcbiAgfVxuXG4gIGFkZExpc3RlbmVyKFxuICAgIGV2ZW50TmFtZTogc3RyaW5nLFxuICAgIGxpc3RlbmVyOiAoLi4uYXJnczogdW5rbm93bltdKSA9PiB2b2lkLFxuICAgIGNvbnRleHQ/OiBvYmplY3RcbiAgKTogdm9pZCB7XG4gICAgY29uc3QgZXZlbnQgPSB0aGlzLl9ldmVudHMuZ2V0KGV2ZW50TmFtZSk7XG4gICAgLy8gVE9ETzogcmVtb3ZlZCB0aGlzIGFwaSBkZXNpZ24gYWZ0ZXIgc3ByaW5nXG4gICAgaWYgKGV2ZW50TmFtZSA9PSAna2V5Ym9hcmRzdGF0dXNjaGFuZ2VkJykge1xuICAgICAgaWYgKHRoaXMuX2ludGVybmFsX2NhbGxMeW54U2V0TW9kdWxlKSB7XG4gICAgICAgIHRoaXMuX2ludGVybmFsX2NhbGxMeW54U2V0TW9kdWxlKCdzd2l0Y2hLZXlCb2FyZERldGVjdCcsIFt0cnVlXSk7XG4gICAgICB9XG4gICAgfVxuICAgIGlmIChldmVudCkge1xuICAgICAgZXZlbnQucHVzaCh7XG4gICAgICAgIGxpc3RlbmVyLFxuICAgICAgICBjb250ZXh0LFxuICAgICAgfSk7XG4gICAgfSBlbHNlIHtcbiAgICAgIHRoaXMuX2V2ZW50cy5zZXQoZXZlbnROYW1lLCBbXG4gICAgICAgIHtcbiAgICAgICAgICBsaXN0ZW5lcixcbiAgICAgICAgICBjb250ZXh0LFxuICAgICAgICB9LFxuICAgICAgXSk7XG4gICAgfVxuICB9XG5cbiAgcmVtb3ZlTGlzdGVuZXIoXG4gICAgZXZlbnROYW1lOiBzdHJpbmcsXG4gICAgbGlzdGVuZXI6ICguLi5hcmdzOiB1bmtub3duW10pID0+IHZvaWRcbiAgKTogdm9pZCB7XG4gICAgaWYgKHR5cGVvZiBsaXN0ZW5lciAhPT0gJ2Z1bmN0aW9uJykge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKCdyZW1vdmVMaXN0ZW5lciBvbmx5IHRha2VzIGluc3RhbmNlcyBvZiBGdW5jdGlvbicpO1xuICAgIH1cbiAgICBjb25zdCBldmVudHMgPSB0aGlzLl9ldmVudHMuZ2V0KGV2ZW50TmFtZSk7XG4gICAgbGV0IGluZGV4ID0gMDtcbiAgICBpZiAoQXJyYXkuaXNBcnJheShldmVudHMpKSB7XG4gICAgICBjb25zdCBmbGFnID0gZXZlbnRzLnNvbWUoKGl0ZW0pID0+IHtcbiAgICAgICAgaWYgKGxpc3RlbmVyID09PSBpdGVtLmxpc3RlbmVyKSB7XG4gICAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICAgIH1cbiAgICAgICAgaW5kZXgrKztcbiAgICAgIH0pO1xuICAgICAgZmxhZyAmJiBldmVudHMuc3BsaWNlKGluZGV4LCAxKTtcbiAgICB9XG5cbiAgICAvLyBUT0RPOiByZW1vdmVkIHRoaXMgYXBpIGRlc2lnbiBhZnRlciBzcHJpbmdcbiAgICBpZiAoZXZlbnROYW1lID09ICdrZXlib2FyZHN0YXR1c2NoYW5nZWQnKSB7XG4gICAgICBpZiAodGhpcy5faW50ZXJuYWxfY2FsbEx5bnhTZXRNb2R1bGUpIHtcbiAgICAgICAgdGhpcy5faW50ZXJuYWxfY2FsbEx5bnhTZXRNb2R1bGUoJ3N3aXRjaEtleUJvYXJkRGV0ZWN0JywgW2ZhbHNlXSk7XG4gICAgICB9XG4gICAgfVxuICB9XG5cbiAgZW1pdChldmVudE5hbWU6IHN0cmluZywgZGF0YTogdW5rbm93bik6IHZvaWQge1xuICAgIGNvbnN0IGV2ZW50cyA9IHRoaXMuX2V2ZW50cy5nZXQoZXZlbnROYW1lKTtcbiAgICBpZiAoQXJyYXkuaXNBcnJheShldmVudHMpKSB7XG4gICAgICBldmVudHMuZm9yRWFjaCgoaXRlbSkgPT4ge1xuICAgICAgICBjb25zdCB7IGxpc3RlbmVyLCBjb250ZXh0IH0gPSBpdGVtO1xuICAgICAgICBpZiAodHlwZW9mIGxpc3RlbmVyID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgICAgbGlzdGVuZXIuYXBwbHkoY29udGV4dCB8fCB0aGlzLCBkYXRhKTtcbiAgICAgICAgfVxuICAgICAgfSk7XG4gICAgfVxuICB9XG5cbiAgcmVtb3ZlQWxsTGlzdGVuZXJzKGV2ZW50TmFtZT86IHN0cmluZyk6IHZvaWQge1xuICAgIGlmICh0eXBlb2YgZXZlbnROYW1lID09PSAnc3RyaW5nJykge1xuICAgICAgdGhpcy5fZXZlbnRzLmRlbGV0ZShldmVudE5hbWUpO1xuICAgICAgcmV0dXJuO1xuICAgIH1cblxuICAgIC8vIGNsZWFyIGFsbFxuICAgIHRoaXMuX2V2ZW50cyA9IG5ldyBNYXAoKTtcbiAgfVxuXG4gIHRyaWdnZXIoZXZlbnROYW1lOiBzdHJpbmcsIHBhcmFtczogc3RyaW5nIHwgUmVjb3JkPGFueSwgYW55Pik6IHZvaWQge1xuICAgIC8vIGZvciBhcGkgdXNhZ2U7XG4gICAgY29uc3QgZXZlbnRzID0gdGhpcy5fZXZlbnRzLmdldChldmVudE5hbWUpO1xuICAgIGlmIChBcnJheS5pc0FycmF5KGV2ZW50cykpIHtcbiAgICAgIGlmICh0eXBlb2YgcGFyYW1zID09PSAnc3RyaW5nJykge1xuICAgICAgICBwYXJhbXMgPSBKU09OLnBhcnNlKHBhcmFtcyk7XG4gICAgICB9XG4gICAgICBldmVudHMuZm9yRWFjaCgoaXRlbSkgPT4ge1xuICAgICAgICBjb25zdCB7IGxpc3RlbmVyLCBjb250ZXh0IH0gPSBpdGVtO1xuICAgICAgICBpZiAodHlwZW9mIGxpc3RlbmVyID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgICAgbGlzdGVuZXIuY2FsbChjb250ZXh0IHx8IHRoaXMsIHBhcmFtcyk7XG4gICAgICAgIH1cbiAgICAgIH0pO1xuICAgIH1cbiAgfVxuXG4gIHRvZ2dsZShldmVudE5hbWU6IHN0cmluZywgLi4uZGF0YTogdW5rbm93bltdKTogdm9pZCB7XG4gICAgdGhpcy5lbWl0KGV2ZW50TmFtZSwgZGF0YSk7XG4gIH1cbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGNyZWF0ZUV2ZW50RW1pdHRlcigpIHtcbiAgcmV0dXJuIG5ldyBFdmVudEVtaXR0ZXIoKTtcbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBCZWZvcmVQdWJsaXNoRXZlbnQgYXMgSUJlZm9yZVB1Ymxpc2hFdmVudCB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCBFdmVudEVtaXR0ZXIgZnJvbSAnLi9ldmVudEVtaXR0ZXInO1xuXG5leHBvcnQgY2xhc3MgQW9wTWFuYWdlciB7XG4gIHB1YmxpYyBfYmVmb3JlUHVibGlzaEV2ZW50OiBCZWZvcmVQdWJsaXNoRXZlbnQ7XG5cbiAgY29uc3RydWN0b3IoKSB7XG4gICAgdGhpcy5fYmVmb3JlUHVibGlzaEV2ZW50ID0gbmV3IEJlZm9yZVB1Ymxpc2hFdmVudCgpO1xuICB9XG59XG5cbmV4cG9ydCBjbGFzcyBCZWZvcmVQdWJsaXNoRXZlbnRcbiAgZXh0ZW5kcyBFdmVudEVtaXR0ZXJcbiAgaW1wbGVtZW50cyBJQmVmb3JlUHVibGlzaEV2ZW50IHtcbiAgYWRkKFxuICAgIGV2ZW50TmFtZTogc3RyaW5nLFxuICAgIGNhbGxiYWNrOiAoLi4uYXJnczogdW5rbm93bltdKSA9PiB2b2lkLFxuICAgIGNvbnRleHQ/OiBvYmplY3RcbiAgKTogQmVmb3JlUHVibGlzaEV2ZW50IHtcbiAgICBzdXBlci5hZGRMaXN0ZW5lcihldmVudE5hbWUsIGNhbGxiYWNrLCBjb250ZXh0KTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIHJlbW92ZShcbiAgICBldmVudE5hbWU6IHN0cmluZyxcbiAgICBjYWxsYmFjazogKC4uLmFyZ3M6IHVua25vd25bXSkgPT4gdm9pZFxuICApOiBCZWZvcmVQdWJsaXNoRXZlbnQge1xuICAgIHN1cGVyLnJlbW92ZUxpc3RlbmVyKGV2ZW50TmFtZSwgY2FsbGJhY2spO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IEV2ZW50RW1pdHRlciBmcm9tICcuL2V2ZW50RW1pdHRlcic7XG5leHBvcnQgZGVmYXVsdCBFdmVudEVtaXR0ZXI7XG5leHBvcnQgeyBjcmVhdGVFdmVudEVtaXR0ZXIgfSBmcm9tICcuL2V2ZW50RW1pdHRlcic7XG5cbmV4cG9ydCAqIGZyb20gJy4vYW9wJztcbiIsICJpbXBvcnQgRXZlbnRFbWl0dGVyIGZyb20gJy4uL2V2ZW50JztcblxuaW50ZXJmYWNlIFN0cmVhbURlbGVnYXRlIHtcbiAgb25EYXRhKGRhdGE6IEFycmF5QnVmZmVyKTogdm9pZDtcbiAgb25FbmQoKTogdm9pZDtcbiAgb25FcnJvcihlcnJvcjogc3RyaW5nKTogdm9pZDtcbn1cbi8qKlxuICogU2VydmVzIGFzIGEgc3RhYmxlIHR5cGUgaWRlbnRpZmllciBhY3Jvc3MgZGlmZmVyZW50IFByb21pc2UgY29uc3RydWN0b3IgZW52aXJvbm1lbnRzXG4gKlxuICogVGhpcyBjbGFzcyBpcyB1c2VkIHRvIGVuc3VyZSB0eXBlIHJlY29nbml0aW9uIHdvcmtzIHdoZW4gc2FtZS1jbGFzcyBpbnN0YW5jZXMgY29tZSBmcm9tXG4gKiBkaWZmZXJlbnQgUHJvbWlzZSBjb25zdHJ1Y3RvciBlbnZpcm9ubWVudHMgKGUuZy4gZGlmZmVyZW50IGx5bnggaW5zdGFuY2VzKVxuICovXG5leHBvcnQgYWJzdHJhY3QgY2xhc3MgTHlueFJlYWRhYmxlU3RyZWFtIHt9XG5cbmV4cG9ydCBmdW5jdGlvbiBjcmVhdGVSZWFkYWJsZVN0cmVhbUNsYXNzKFByb21pc2U6IFByb21pc2VDb25zdHJ1Y3Rvcik6IGFueSB7XG4gIHJldHVybiBjbGFzcyBSZWFkYWJsZVN0cmVhbVxuICAgIGV4dGVuZHMgTHlueFJlYWRhYmxlU3RyZWFtXG4gICAgaW1wbGVtZW50cyBTdHJlYW1EZWxlZ2F0ZSB7XG4gICAgcHJpdmF0ZSBfX2V2ZW50Q2VudGVyOiBFdmVudEVtaXR0ZXI7XG4gICAgcHJpdmF0ZSBfX2RhdGFSZWNlaXZlZDogQXJyYXlCdWZmZXJbXTtcbiAgICBwcml2YXRlIF9fZG9uZTogYm9vbGVhbjtcbiAgICBwcml2YXRlIF9fY2FuY2VsbGVkOiBib29sZWFuO1xuICAgIHByaXZhdGUgX19sb2NrZWQ6IGJvb2xlYW47XG4gICAgcHJpdmF0ZSBfX2Vycm9yOiBFcnJvcjtcbiAgICBjb25zdHJ1Y3RvcigpIHtcbiAgICAgIHN1cGVyKCk7XG4gICAgICB0aGlzLl9fZGF0YVJlY2VpdmVkID0gW107XG4gICAgICB0aGlzLl9fZG9uZSA9IGZhbHNlO1xuICAgICAgdGhpcy5fX2NhbmNlbGxlZCA9IGZhbHNlO1xuICAgICAgdGhpcy5fX2xvY2tlZCA9IGZhbHNlO1xuICAgICAgdGhpcy5fX2V2ZW50Q2VudGVyID0gbmV3IEV2ZW50RW1pdHRlcigpO1xuICAgIH1cbiAgICBvbkRhdGEoZGF0YTogQXJyYXlCdWZmZXIpOiB2b2lkIHtcbiAgICAgIGlmICh0aGlzLl9fY2FuY2VsbGVkKSB7XG4gICAgICAgIHJldHVybjtcbiAgICAgIH1cbiAgICAgIHRoaXMuX19kYXRhUmVjZWl2ZWQucHVzaChkYXRhKTtcbiAgICAgIHRoaXMuX19ldmVudENlbnRlci5lbWl0KCd3YWl0U2lnbmFsJywgbnVsbCk7XG4gICAgfVxuICAgIG9uRW5kKCk6IHZvaWQge1xuICAgICAgdGhpcy5fX2RvbmUgPSB0cnVlO1xuICAgICAgdGhpcy5fX2V2ZW50Q2VudGVyLmVtaXQoJ3dhaXRTaWduYWwnLCBudWxsKTtcbiAgICB9XG4gICAgb25FcnJvcihlcnJvcjogc3RyaW5nKTogdm9pZCB7XG4gICAgICB0aGlzLl9fZXJyb3IgPSBuZXcgRXJyb3IoZXJyb3IpO1xuICAgICAgdGhpcy5fX2V2ZW50Q2VudGVyLmVtaXQoJ3dhaXRTaWduYWwnLCBudWxsKTtcbiAgICB9XG4gICAgcHJpdmF0ZSBwcm9jZXNzUmVhZChyZXNvbHZlLCByZWplY3QpIHtcbiAgICAgIGlmICh0aGlzLl9fZXJyb3IpIHtcbiAgICAgICAgcmV0dXJuIHJlamVjdCh0aGlzLl9fZXJyb3IpO1xuICAgICAgfVxuICAgICAgaWYgKFxuICAgICAgICB0aGlzLl9fY2FuY2VsbGVkIHx8XG4gICAgICAgICh0aGlzLl9fZG9uZSAmJiB0aGlzLl9fZGF0YVJlY2VpdmVkLmxlbmd0aCA9PSAwKVxuICAgICAgKSB7XG4gICAgICAgIHJldHVybiByZXNvbHZlKHsgZG9uZTogdHJ1ZSwgdmFsdWU6IHVuZGVmaW5lZCB9KTtcbiAgICAgIH1cbiAgICAgIGlmICh0aGlzLl9fZGF0YVJlY2VpdmVkLmxlbmd0aCA+IDApIHtcbiAgICAgICAgY29uc3QgY3VyckRhdGEgPSB0aGlzLl9fZGF0YVJlY2VpdmVkLnNoaWZ0KCk7XG4gICAgICAgIHJldHVybiByZXNvbHZlKHsgZG9uZTogZmFsc2UsIHZhbHVlOiBjdXJyRGF0YSB9KTtcbiAgICAgIH1cbiAgICAgIC8vIHdhaXQgZm9yIHNpZ25hbHNcbiAgICAgIGNvbnN0IHdhaXRTaWduYWwgPSAoKSA9PiB7XG4gICAgICAgIHRoaXMuX19ldmVudENlbnRlci5yZW1vdmVMaXN0ZW5lcignd2FpdFNpZ25hbCcsIHdhaXRTaWduYWwpO1xuICAgICAgICB0aGlzLnByb2Nlc3NSZWFkKHJlc29sdmUsIHJlamVjdCk7XG4gICAgICB9O1xuXG4gICAgICB0aGlzLl9fZXZlbnRDZW50ZXIuYWRkTGlzdGVuZXIoJ3dhaXRTaWduYWwnLCB3YWl0U2lnbmFsLCB0aGlzKTtcbiAgICB9XG4gICAgcHVibGljIF9fcmVhZCgpIHtcbiAgICAgIHJldHVybiBuZXcgUHJvbWlzZSgocmVzb2x2ZSwgcmVqZWN0KSA9PiB7XG4gICAgICAgIHRoaXMucHJvY2Vzc1JlYWQocmVzb2x2ZSwgcmVqZWN0KTtcbiAgICAgIH0pO1xuICAgIH1cbiAgICBwdWJsaWMgZ2V0IGxvY2tlZCgpIHtcbiAgICAgIHJldHVybiB0aGlzLl9fbG9ja2VkO1xuICAgIH1cbiAgICBwdWJsaWMgY2FuY2VsKHJlYXNvbj86IGFueSkge1xuICAgICAgdGhpcy5fX2NhbmNlbGxlZCA9IHRydWU7XG4gICAgICB0aGlzLl9fZGF0YVJlY2VpdmVkID0gbnVsbDtcbiAgICAgIHRoaXMuX19ldmVudENlbnRlci5lbWl0KCd3YWl0U2lnbmFsJywgbnVsbCk7XG4gICAgICByZXR1cm4gUHJvbWlzZS5yZXNvbHZlKHJlYXNvbik7XG4gICAgfVxuICAgIHB1YmxpYyBnZXRSZWFkZXIoKSB7XG4gICAgICBpZiAodGhpcy5fX2xvY2tlZCkge1xuICAgICAgICByZXR1cm4gbnVsbDtcbiAgICAgIH1cbiAgICAgIHRoaXMuX19sb2NrZWQgPSB0cnVlO1xuICAgICAgcmV0dXJuIG5ldyBSZWFkYWJsZVN0cmVhbURlZmF1bHRSZWFkZXIodGhpcyBhcyBhbnkpO1xuICAgIH1cbiAgfTtcbn1cbmNsYXNzIFJlYWRhYmxlU3RyZWFtRGVmYXVsdFJlYWRlciB7XG4gIHByaXZhdGUgX19zdHJlYW07XG4gIGNvbnN0cnVjdG9yKHN0cmVhbTogUmVhZGFibGVTdHJlYW0pIHtcbiAgICB0aGlzLl9fc3RyZWFtID0gc3RyZWFtO1xuICB9XG4gIHB1YmxpYyBjYW5jZWwocmVhc29uPzogYW55KSB7XG4gICAgcmV0dXJuIHRoaXMuX19zdHJlYW0uY2FuY2VsKHJlYXNvbik7XG4gIH1cbiAgcHVibGljIHJlYWQoKSB7XG4gICAgcmV0dXJuIHRoaXMuX19zdHJlYW0uX19yZWFkKCk7XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBUZXh0RGVjb2RlciB9IGZyb20gJy4vVGV4dERlY29kZXInO1xuaW1wb3J0IHsgVGV4dEVuY29kZXIgfSBmcm9tICcuL1RleHRFbmNvZGVyJztcbmltcG9ydCB7IEx5bnhSZWFkYWJsZVN0cmVhbSB9IGZyb20gJy4vUmVhZGFibGVTdHJlYW0nO1xuZXhwb3J0IGNsYXNzIEJvZHlNaXhpbiB7XG4gIF9hcnJheUJ1ZmZlcjogQXJyYXlCdWZmZXI7XG4gIF9ib2R5U3RyZWFtOiBMeW54UmVhZGFibGVTdHJlYW07XG4gIF9ib2R5VXNlZDogYm9vbGVhbjtcbiAgX2VuYWJsZUZldGNoQVBJU3RhbmRhcmRTdHJlYW1pbmc6IGJvb2xlYW47XG5cbiAgY29uc3RydWN0b3IoKSB7XG4gICAgdGhpcy5fYXJyYXlCdWZmZXIgPSBuZXcgQXJyYXlCdWZmZXIoMCk7XG4gICAgdGhpcy5fYm9keVN0cmVhbSA9IG51bGw7XG4gICAgdGhpcy5fYm9keVVzZWQgPSBmYWxzZTtcbiAgICB0aGlzLl9lbmFibGVGZXRjaEFQSVN0YW5kYXJkU3RyZWFtaW5nID0gZmFsc2U7XG4gIH1cblxuICBwcml2YXRlIHNhZmVVc2VCb2R5PFQ+KHVzZTogKGJvZHk6IEFycmF5QnVmZmVyKSA9PiBUKTogVCB7XG4gICAgaWYgKHRoaXMuX2JvZHlVc2VkKSB7XG4gICAgICAvLyBUT0RPKGh1emhhbmJvLmx1Yyk6IHRocm93IGEgZXJyb3IgaWYgdGhlIGJyZWFrIGNoYW5nZSBpcyBvay5cbiAgICAgIHJldHVybiB1bmRlZmluZWQ7XG4gICAgfVxuXG4gICAgY29uc3QgcmV0ID0gdXNlKHRoaXMuX2FycmF5QnVmZmVyKTtcbiAgICB0aGlzLl9ib2R5VXNlZCA9IHRydWU7XG4gICAgdGhpcy5fYXJyYXlCdWZmZXIgPSBudWxsO1xuICAgIHJldHVybiByZXQ7XG4gIH1cblxuICBwcml2YXRlIGNsb25lQXJyYXlCdWZmZXIoc3JjOiBBcnJheUJ1ZmZlcikge1xuICAgIHJldHVybiBzcmMuc2xpY2UoMCk7XG4gIH1cblxuICBwcm90ZWN0ZWQgc2V0Qm9keShcbiAgICBib2R5PzogQm9keUluaXQgfCBCb2R5TWl4aW4gfCBSZWFkYWJsZVN0cmVhbSxcbiAgICBlbmFibGVGZXRjaEFQSVN0YW5kYXJkU3RyZWFtaW5nPzogYm9vbGVhblxuICApIHtcbiAgICBpZiAoYm9keSBpbnN0YW5jZW9mIEJvZHlNaXhpbikge1xuICAgICAgaWYgKGJvZHkuX2JvZHlVc2VkIHx8IGJvZHkuX2JvZHlTdHJlYW0pIHtcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKCdib2R5IHVzZWQsIG9yIHRyeSB0byBjb3B5IGJvZHkgc3RyZWFtJyk7XG4gICAgICB9XG4gICAgICB0aGlzLl9hcnJheUJ1ZmZlciA9IHRoaXMuY2xvbmVBcnJheUJ1ZmZlcihib2R5Ll9hcnJheUJ1ZmZlcik7XG4gICAgfSBlbHNlIHtcbiAgICAgIGlmIChib2R5IGluc3RhbmNlb2YgQXJyYXlCdWZmZXIpIHtcbiAgICAgICAgdGhpcy5fYXJyYXlCdWZmZXIgPSB0aGlzLmNsb25lQXJyYXlCdWZmZXIoYm9keSk7XG4gICAgICB9IGVsc2UgaWYgKGJvZHkgaW5zdGFuY2VvZiBEYXRhVmlldykge1xuICAgICAgICB0aGlzLl9hcnJheUJ1ZmZlciA9IHRoaXMuY2xvbmVBcnJheUJ1ZmZlcihcbiAgICAgICAgICBib2R5LmJ1ZmZlci5zbGljZShib2R5LmJ5dGVPZmZzZXQsIGJvZHkuYnl0ZU9mZnNldCArIGJvZHkuYnl0ZUxlbmd0aClcbiAgICAgICAgKTtcbiAgICAgIH0gZWxzZSBpZiAoQXJyYXlCdWZmZXIuaXNWaWV3KGJvZHkpKSB7XG4gICAgICAgIHRoaXMuX2FycmF5QnVmZmVyID0gdGhpcy5jbG9uZUFycmF5QnVmZmVyKGJvZHkuYnVmZmVyKTtcbiAgICAgIH0gZWxzZSBpZiAoYm9keSkge1xuICAgICAgICB0aGlzLl9hcnJheUJ1ZmZlciA9IG5ldyBUZXh0RW5jb2RlcigpLmVuY29kZShib2R5LnRvU3RyaW5nKCkpLmJ1ZmZlcjtcbiAgICAgIH1cbiAgICAgIGlmIChib2R5IGluc3RhbmNlb2YgTHlueFJlYWRhYmxlU3RyZWFtKSB7XG4gICAgICAgIHRoaXMuX2JvZHlTdHJlYW0gPSBib2R5O1xuICAgICAgICB0aGlzLl9lbmFibGVGZXRjaEFQSVN0YW5kYXJkU3RyZWFtaW5nID0gZW5hYmxlRmV0Y2hBUElTdGFuZGFyZFN0cmVhbWluZztcbiAgICAgIH1cbiAgICB9XG4gIH1cblxuICBwdWJsaWMgYXN5bmMgYXJyYXlCdWZmZXIoKTogUHJvbWlzZTxBcnJheUJ1ZmZlcj4ge1xuICAgIGlmICh0aGlzLl9lbmFibGVGZXRjaEFQSVN0YW5kYXJkU3RyZWFtaW5nICYmIHRoaXMuX2JvZHlTdHJlYW0gIT0gbnVsbCkge1xuICAgICAgY29uc3QgYnVmZmVyID0gYXdhaXQgdGhpcy5jb25zdW1lU3RyZWFtKCk7XG4gICAgICBpZiAoYnVmZmVyID09PSBudWxsKSB7XG4gICAgICAgIHJldHVybiBuZXcgQXJyYXlCdWZmZXIoMCk7XG4gICAgICB9XG4gICAgICByZXR1cm4gYnVmZmVyO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gUHJvbWlzZS5yZXNvbHZlKHRoaXMuc2FmZVVzZUJvZHkoKGJvZHkpID0+IGJvZHkpKTtcbiAgICB9XG4gIH1cblxuICBwdWJsaWMgZ2V0IGJvZHkoKSB7XG4gICAgaWYgKHRoaXMuX2JvZHlVc2VkKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoJ2JvZHkgdXNlZCcpO1xuICAgIH1cbiAgICB0aGlzLl9ib2R5VXNlZCA9IHRydWU7XG4gICAgcmV0dXJuIHRoaXMuX2JvZHlTdHJlYW07XG4gIH1cblxuICBwdWJsaWMgYXN5bmMgdGV4dCgpOiBQcm9taXNlPHN0cmluZz4ge1xuICAgIGlmICh0aGlzLl9lbmFibGVGZXRjaEFQSVN0YW5kYXJkU3RyZWFtaW5nICYmIHRoaXMuX2JvZHlTdHJlYW0gIT0gbnVsbCkge1xuICAgICAgY29uc3QgYnVmZmVyID0gYXdhaXQgdGhpcy5jb25zdW1lU3RyZWFtKCk7XG4gICAgICBpZiAoYnVmZmVyID09PSBudWxsKSB7XG4gICAgICAgIHJldHVybiAnJztcbiAgICAgIH1cbiAgICAgIHJldHVybiBuZXcgVGV4dERlY29kZXIoKS5kZWNvZGUoYnVmZmVyKTtcbiAgICB9IGVsc2Uge1xuICAgICAgY29uc3QgcmVzdWx0ID0gYXdhaXQgdGhpcy5zYWZlVXNlQm9keSgoYm9keSkgPT5cbiAgICAgICAgbmV3IFRleHREZWNvZGVyKCkuZGVjb2RlKGJvZHkpXG4gICAgICApO1xuICAgICAgcmV0dXJuIHJlc3VsdDtcbiAgICB9XG4gIH1cblxuICBwdWJsaWMgYXN5bmMganNvbigpOiBQcm9taXNlPGFueT4ge1xuICAgIGlmICh0aGlzLl9lbmFibGVGZXRjaEFQSVN0YW5kYXJkU3RyZWFtaW5nICYmIHRoaXMuX2JvZHlTdHJlYW0gIT0gbnVsbCkge1xuICAgICAgY29uc3QgYnVmZmVyID0gYXdhaXQgdGhpcy5jb25zdW1lU3RyZWFtKCk7XG4gICAgICBpZiAoYnVmZmVyID09PSBudWxsKSB7XG4gICAgICAgIHJldHVybiBudWxsO1xuICAgICAgfVxuICAgICAgY29uc3QgdGV4dCA9IG5ldyBUZXh0RGVjb2RlcigpLmRlY29kZShidWZmZXIpO1xuICAgICAgcmV0dXJuIEpTT04ucGFyc2UodGV4dCk7XG4gICAgfSBlbHNlIHtcbiAgICAgIGNvbnN0IHJlc3VsdCA9IHRoaXMuc2FmZVVzZUJvZHkoKGJvZHkpID0+IG5ldyBUZXh0RGVjb2RlcigpLmRlY29kZShib2R5KSk7XG4gICAgICByZXR1cm4gUHJvbWlzZS5yZXNvbHZlKHJlc3VsdCkudGhlbigodGV4dCkgPT4gSlNPTi5wYXJzZSh0ZXh0KSk7XG4gICAgfVxuICB9XG5cbiAgLy8gVE9ETyhodXpoYW5iby5sdWMpOiB0aGVzZSBBUElzIHJlbHkgb24gZm91bmRhbWVudGFsIHR5cGVzXG4gIC8vIHdoaWNoIHJlcXVpcmUgZXh0cmEgd29ya3MgdG8gc3VwcG9ydCwgd2Ugd2lsbCBzdXBwb3J0IHRoZXNlXG4gIC8vIGxhdGVyIHdoZW4gd2UgaGF2ZSBpbXBsZW1lbnRlZCB0aGVzZSB0eXBlcy5cblxuICAvLyBibG9iKCk6IEJsb2I7XG4gIC8vIGZvcm1EYXRhKCk6IEZvcm1EYXRhO1xuICAvLyBjbG9uZVN0cmVhbSgpOiBSZWFkYWJsZVN0cmVhbTtcblxuICBwdWJsaWMgZ2V0IGJvZHlVc2VkKCkge1xuICAgIHJldHVybiB0aGlzLl9ib2R5VXNlZDtcbiAgfVxuXG4gIHByaXZhdGUgYXN5bmMgZ2V0QXJyYXlCdWZmZXJPZlN0cmVhbWluZygpOiBQcm9taXNlPEFycmF5QnVmZmVyPiB7XG4gICAgY29uc3QgY2h1bmtzOiBVaW50OEFycmF5W10gPSBbXTtcbiAgICBsZXQgdG90YWxMZW5ndGggPSAwO1xuICAgIGNvbnN0IHJlYWRlciA9ICgodGhpc1xuICAgICAgLl9ib2R5U3RyZWFtIGFzIHVua25vd24pIGFzIFJlYWRhYmxlU3RyZWFtKS5nZXRSZWFkZXIoKTtcbiAgICB7XG4gICAgICAvLyAxLiByZWFkIGFsbCBkYXRhIGNodW5rc1xuICAgICAgd2hpbGUgKHRydWUpIHtcbiAgICAgICAgY29uc3QgeyBkb25lLCB2YWx1ZSB9ID0gYXdhaXQgcmVhZGVyLnJlYWQoKTtcbiAgICAgICAgaWYgKGRvbmUpIHtcbiAgICAgICAgICBicmVhaztcbiAgICAgICAgfVxuICAgICAgICBjaHVua3MucHVzaChuZXcgVWludDhBcnJheSh2YWx1ZSkpO1xuICAgICAgICB0b3RhbExlbmd0aCArPSB2YWx1ZS5ieXRlTGVuZ3RoO1xuICAgICAgfVxuICAgICAgLy8gMi4gY3JlYXRlIGZpbmFsQnVmZmVyIGFuZCBtZXJnZSBkYXRhc1xuICAgICAgY29uc3QgZmluYWxCdWZmZXIgPSBuZXcgVWludDhBcnJheSh0b3RhbExlbmd0aCk7XG4gICAgICBsZXQgb2Zmc2V0ID0gMDtcbiAgICAgIGZvciAoY29uc3QgY2h1bmsgb2YgY2h1bmtzKSB7XG4gICAgICAgIGZpbmFsQnVmZmVyLnNldChjaHVuaywgb2Zmc2V0KTtcbiAgICAgICAgb2Zmc2V0ICs9IGNodW5rLmJ5dGVMZW5ndGg7XG4gICAgICB9XG4gICAgICByZXR1cm4gZmluYWxCdWZmZXIuYnVmZmVyO1xuICAgIH1cbiAgfVxuXG4gIHByaXZhdGUgYXN5bmMgY29uc3VtZVN0cmVhbSgpOiBQcm9taXNlPEFycmF5QnVmZmVyIHwgbnVsbD4ge1xuICAgIGlmICh0aGlzLl9ib2R5VXNlZCkge1xuICAgICAgcmV0dXJuIG51bGw7XG4gICAgfVxuXG4gICAgdGhpcy5fYm9keVVzZWQgPSB0cnVlO1xuICAgIHJldHVybiBhd2FpdCB0aGlzLmdldEFycmF5QnVmZmVyT2ZTdHJlYW1pbmcoKTtcbiAgfVxufVxuIiwgIi8qKlxuICogQGxpY2Vuc2UgTUlUXG4gKiBodHRwczovL2dpdGh1Yi5jb20vbXN3anMvaGVhZGVycy1wb2x5ZmlsbC9ibG9iL21haW4vTElDRU5TRVxuICpcbkNvcHlyaWdodCAoYykgMjAyMOKAk3ByZXNlbnQgQXJ0ZW0gWmFraGFyY2hlbmtvXG5cblBlcm1pc3Npb24gaXMgaGVyZWJ5IGdyYW50ZWQsIGZyZWUgb2YgY2hhcmdlLCB0byBhbnkgcGVyc29uIG9idGFpbmluZyBhIGNvcHkgb2YgdGhpcyBzb2Z0d2FyZSBhbmQgYXNzb2NpYXRlZCBkb2N1bWVudGF0aW9uIGZpbGVzICh0aGUgXCJTb2Z0d2FyZVwiKSwgdG8gZGVhbCBpbiB0aGUgU29mdHdhcmUgd2l0aG91dCByZXN0cmljdGlvbiwgaW5jbHVkaW5nIHdpdGhvdXQgbGltaXRhdGlvbiB0aGUgcmlnaHRzIHRvIHVzZSwgY29weSwgbW9kaWZ5LCBtZXJnZSwgcHVibGlzaCwgZGlzdHJpYnV0ZSwgc3VibGljZW5zZSwgYW5kL29yIHNlbGwgY29waWVzIG9mIHRoZSBTb2Z0d2FyZSwgYW5kIHRvIHBlcm1pdCBwZXJzb25zIHRvIHdob20gdGhlIFNvZnR3YXJlIGlzIGZ1cm5pc2hlZCB0byBkbyBzbywgc3ViamVjdCB0byB0aGUgZm9sbG93aW5nIGNvbmRpdGlvbnM6XG5cblRoZSBhYm92ZSBjb3B5cmlnaHQgbm90aWNlIGFuZCB0aGlzIHBlcm1pc3Npb24gbm90aWNlIHNoYWxsIGJlIGluY2x1ZGVkIGluIGFsbCBjb3BpZXMgb3Igc3Vic3RhbnRpYWwgcG9ydGlvbnMgb2YgdGhlIFNvZnR3YXJlLlxuXG5USEUgU09GVFdBUkUgSVMgUFJPVklERUQgXCJBUyBJU1wiLCBXSVRIT1VUIFdBUlJBTlRZIE9GIEFOWSBLSU5ELCBFWFBSRVNTIE9SIElNUExJRUQsIElOQ0xVRElORyBCVVQgTk9UIExJTUlURUQgVE8gVEhFIFdBUlJBTlRJRVMgT0YgTUVSQ0hBTlRBQklMSVRZLCBGSVRORVNTIEZPUiBBIFBBUlRJQ1VMQVIgUFVSUE9TRSBBTkQgTk9OSU5GUklOR0VNRU5ULiBJTiBOTyBFVkVOVCBTSEFMTCBUSEUgQVVUSE9SUyBPUiBDT1BZUklHSFQgSE9MREVSUyBCRSBMSUFCTEUgRk9SIEFOWSBDTEFJTSwgREFNQUdFUyBPUiBPVEhFUiBMSUFCSUxJVFksIFdIRVRIRVIgSU4gQU4gQUNUSU9OIE9GIENPTlRSQUNULCBUT1JUIE9SIE9USEVSV0lTRSwgQVJJU0lORyBGUk9NLCBPVVQgT0YgT1IgSU4gQ09OTkVDVElPTiBXSVRIIFRIRSBTT0ZUV0FSRSBPUiBUSEUgVVNFIE9SIE9USEVSIERFQUxJTkdTIElOIFRIRSBTT0ZUV0FSRS5cbiAqL1xuZXhwb3J0IGNsYXNzIEhlYWRlcnMge1xuICBwcml2YXRlIF9oZWFkZXJzX21hcDogTWFwPHN0cmluZywgc3RyaW5nPiA9IG5ldyBNYXAoKTtcblxuICBjb25zdHJ1Y3Rvcihpbml0PzogSGVhZGVyc0luaXQpIHtcbiAgICBpZiAoaW5pdCA9PT0gbnVsbCB8fCB0eXBlb2YgaW5pdCA9PT0gJ251bWJlcicpIHtcbiAgICAgIHRocm93IG5ldyBUeXBlRXJyb3IoYEhlYWRlcnMgaW5pdCB3aXRoIG51bGwvbnVtYmVyYCk7XG4gICAgfVxuICAgIGlmIChpbml0IGluc3RhbmNlb2YgSGVhZGVycykge1xuICAgICAgZm9yIChjb25zdCBba2V5LCB2YWx1ZV0gb2YgaW5pdCkge1xuICAgICAgICB0aGlzLmFwcGVuZChrZXksIHZhbHVlKTtcbiAgICAgIH1cbiAgICB9IGVsc2UgaWYgKEFycmF5LmlzQXJyYXkoaW5pdCkpIHtcbiAgICAgIGluaXQuZm9yRWFjaCgoW25hbWUsIHZhbHVlXSkgPT4ge1xuICAgICAgICB0aGlzLmFwcGVuZChuYW1lLCBBcnJheS5pc0FycmF5KHZhbHVlKSA/IHZhbHVlLmpvaW4oJyAnKSA6IHZhbHVlKTtcbiAgICAgIH0pO1xuICAgIH0gZWxzZSBpZiAoaW5pdCkge1xuICAgICAgT2JqZWN0LmdldE93blByb3BlcnR5TmFtZXMoaW5pdCkuZm9yRWFjaCgobmFtZSkgPT4ge1xuICAgICAgICBjb25zdCB2YWx1ZSA9IGluaXRbbmFtZV07XG4gICAgICAgIHRoaXMuYXBwZW5kKG5hbWUsIEFycmF5LmlzQXJyYXkodmFsdWUpID8gdmFsdWUuam9pbignICcpIDogdmFsdWUpO1xuICAgICAgfSk7XG4gICAgfVxuICB9XG5cbiAgW1N5bWJvbC50b1N0cmluZ1RhZ10gPSAnSGVhZGVycyc7XG5cbiAgW1N5bWJvbC5pdGVyYXRvcl0oKSB7XG4gICAgcmV0dXJuIHRoaXMuZW50cmllcygpO1xuICB9XG5cbiAgKmtleXMoKTogSXRlcmFibGVJdGVyYXRvcjxzdHJpbmc+IHtcbiAgICBmb3IgKGNvbnN0IFtrZXksIHZhbHVlXSBvZiB0aGlzLl9oZWFkZXJzX21hcCkge1xuICAgICAgeWllbGQga2V5O1xuICAgIH1cbiAgfVxuXG4gICp2YWx1ZXMoKTogSXRlcmFibGVJdGVyYXRvcjxzdHJpbmc+IHtcbiAgICBmb3IgKGNvbnN0IFtrZXksIHZhbHVlXSBvZiB0aGlzLl9oZWFkZXJzX21hcCkge1xuICAgICAgeWllbGQgdmFsdWU7XG4gICAgfVxuICB9XG5cbiAgKmVudHJpZXMoKTogSXRlcmFibGVJdGVyYXRvcjxbc3RyaW5nLCBzdHJpbmddPiB7XG4gICAgZm9yIChjb25zdCBlbnRyeSBvZiB0aGlzLl9oZWFkZXJzX21hcCkge1xuICAgICAgeWllbGQgZW50cnk7XG4gICAgfVxuICB9XG5cbiAgLyoqXG4gICAqIFJldHVybnMgYSBib29sZWFuIHN0YXRpbmcgd2hldGhlciBhIGBIZWFkZXJzYCBvYmplY3QgY29udGFpbnMgYSBjZXJ0YWluIGhlYWRlci5cbiAgICovXG4gIGhhcyhuYW1lOiBzdHJpbmcpOiBib29sZWFuIHtcbiAgICByZXR1cm4gdGhpcy5faGVhZGVyc19tYXAuaGFzKG5hbWUpO1xuICB9XG5cbiAgLyoqXG4gICAqIFJldHVybnMgYSBgQnl0ZVN0cmluZ2Agc2VxdWVuY2Ugb2YgYWxsIHRoZSB2YWx1ZXMgb2YgYSBoZWFkZXIgd2l0aCBhIGdpdmVuIG5hbWUuXG4gICAqL1xuICBnZXQobmFtZTogc3RyaW5nKTogc3RyaW5nIHwgbnVsbCB7XG4gICAgcmV0dXJuIHRoaXMuX2hlYWRlcnNfbWFwLmdldChuYW1lKSA/PyBudWxsO1xuICB9XG5cbiAgLyoqXG4gICAqIFNldHMgYSBuZXcgdmFsdWUgZm9yIGFuIGV4aXN0aW5nIGhlYWRlciBpbnNpZGUgYSBgSGVhZGVyc2Agb2JqZWN0LCBvciBhZGRzIHRoZSBoZWFkZXIgaWYgaXQgZG9lcyBub3QgYWxyZWFkeSBleGlzdC5cbiAgICovXG4gIHNldChuYW1lOiBzdHJpbmcsIHZhbHVlOiBzdHJpbmcpOiB2b2lkIHtcbiAgICB0aGlzLl9oZWFkZXJzX21hcC5zZXQobmFtZSwgU3RyaW5nKHZhbHVlKSk7XG4gIH1cblxuICAvKipcbiAgICogQXBwZW5kcyBhIG5ldyB2YWx1ZSBvbnRvIGFuIGV4aXN0aW5nIGhlYWRlciBpbnNpZGUgYSBgSGVhZGVyc2Agb2JqZWN0LCBvciBhZGRzIHRoZSBoZWFkZXIgaWYgaXQgZG9lcyBub3QgYWxyZWFkeSBleGlzdC5cbiAgICovXG4gIGFwcGVuZChuYW1lOiBzdHJpbmcsIHZhbHVlOiBzdHJpbmcpOiB2b2lkIHtcbiAgICBsZXQgcmVzb2x2ZWRWYWx1ZSA9IHRoaXMuaGFzKG5hbWUpID8gYCR7dGhpcy5nZXQobmFtZSl9LCAke3ZhbHVlfWAgOiB2YWx1ZTtcblxuICAgIHRoaXMuc2V0KG5hbWUsIHJlc29sdmVkVmFsdWUpO1xuICB9XG5cbiAgLyoqXG4gICAqIERlbGV0ZXMgYSBoZWFkZXIgZnJvbSB0aGUgYEhlYWRlcnNgIG9iamVjdC5cbiAgICovXG4gIGRlbGV0ZShuYW1lOiBzdHJpbmcpOiB2b2lkIHtcbiAgICBpZiAoIXRoaXMuaGFzKG5hbWUpKSB7XG4gICAgICByZXR1cm47XG4gICAgfVxuXG4gICAgdGhpcy5faGVhZGVyc19tYXAuZGVsZXRlKG5hbWUpO1xuICB9XG5cbiAgLyoqXG4gICAqIFRyYXZlcnNlcyB0aGUgYEhlYWRlcnNgIG9iamVjdCxcbiAgICogY2FsbGluZyB0aGUgZ2l2ZW4gY2FsbGJhY2sgZm9yIGVhY2ggaGVhZGVyLlxuICAgKi9cbiAgZm9yRWFjaDxUaGlzQXJnID0gdGhpcz4oXG4gICAgY2FsbGJhY2s6IChcbiAgICAgIHRoaXM6IFRoaXNBcmcsXG4gICAgICB2YWx1ZTogc3RyaW5nLFxuICAgICAgbmFtZTogc3RyaW5nLFxuICAgICAgcGFyZW50OiB0aGlzXG4gICAgKSA9PiB2b2lkLFxuICAgIHRoaXNBcmc/OiBUaGlzQXJnXG4gICkge1xuICAgIGZvciAoY29uc3QgW25hbWUsIHZhbHVlXSBvZiB0aGlzLmVudHJpZXMoKSkge1xuICAgICAgY2FsbGJhY2suY2FsbCh0aGlzQXJnLCB2YWx1ZSwgbmFtZSwgdGhpcyk7XG4gICAgfVxuICB9XG59XG4iLCAiLy8gTUlUIExpY2Vuc2VcblxuLy8gQ29weXJpZ2h0IChjKSAyMDE3IG1vbHNzb25cblxuLy8gUGVybWlzc2lvbiBpcyBoZXJlYnkgZ3JhbnRlZCwgZnJlZSBvZiBjaGFyZ2UsIHRvIGFueSBwZXJzb24gb2J0YWluaW5nIGEgY29weVxuLy8gb2YgdGhpcyBzb2Z0d2FyZSBhbmQgYXNzb2NpYXRlZCBkb2N1bWVudGF0aW9uIGZpbGVzICh0aGUgXCJTb2Z0d2FyZVwiKSwgdG8gZGVhbFxuLy8gaW4gdGhlIFNvZnR3YXJlIHdpdGhvdXQgcmVzdHJpY3Rpb24sIGluY2x1ZGluZyB3aXRob3V0IGxpbWl0YXRpb24gdGhlIHJpZ2h0c1xuLy8gdG8gdXNlLCBjb3B5LCBtb2RpZnksIG1lcmdlLCBwdWJsaXNoLCBkaXN0cmlidXRlLCBzdWJsaWNlbnNlLCBhbmQvb3Igc2VsbFxuLy8gY29waWVzIG9mIHRoZSBTb2Z0d2FyZSwgYW5kIHRvIHBlcm1pdCBwZXJzb25zIHRvIHdob20gdGhlIFNvZnR3YXJlIGlzXG4vLyBmdXJuaXNoZWQgdG8gZG8gc28sIHN1YmplY3QgdG8gdGhlIGZvbGxvd2luZyBjb25kaXRpb25zOlxuXG4vLyBUaGUgYWJvdmUgY29weXJpZ2h0IG5vdGljZSBhbmQgdGhpcyBwZXJtaXNzaW9uIG5vdGljZSBzaGFsbCBiZSBpbmNsdWRlZCBpbiBhbGxcbi8vIGNvcGllcyBvciBzdWJzdGFudGlhbCBwb3J0aW9ucyBvZiB0aGUgU29mdHdhcmUuXG5cbi8vIFRIRSBTT0ZUV0FSRSBJUyBQUk9WSURFRCBcIkFTIElTXCIsIFdJVEhPVVQgV0FSUkFOVFkgT0YgQU5ZIEtJTkQsIEVYUFJFU1MgT1Jcbi8vIElNUExJRUQsIElOQ0xVRElORyBCVVQgTk9UIExJTUlURUQgVE8gVEhFIFdBUlJBTlRJRVMgT0YgTUVSQ0hBTlRBQklMSVRZLFxuLy8gRklUTkVTUyBGT1IgQSBQQVJUSUNVTEFSIFBVUlBPU0UgQU5EIE5PTklORlJJTkdFTUVOVC4gSU4gTk8gRVZFTlQgU0hBTEwgVEhFXG4vLyBBVVRIT1JTIE9SIENPUFlSSUdIVCBIT0xERVJTIEJFIExJQUJMRSBGT1IgQU5ZIENMQUlNLCBEQU1BR0VTIE9SIE9USEVSXG4vLyBMSUFCSUxJVFksIFdIRVRIRVIgSU4gQU4gQUNUSU9OIE9GIENPTlRSQUNULCBUT1JUIE9SIE9USEVSV0lTRSwgQVJJU0lORyBGUk9NLFxuLy8gT1VUIE9GIE9SIElOIENPTk5FQ1RJT04gV0lUSCBUSEUgU09GVFdBUkUgT1IgVEhFIFVTRSBPUiBPVEhFUiBERUFMSU5HUyBJTiBUSEVcbi8vIFNPRlRXQVJFLlxuXG5pbXBvcnQgRXZlbnRFbWl0dGVyIGZyb20gJy4uL2V2ZW50JztcblxuaW50ZXJmYWNlIEFib3J0RXZlbnQge1xuICB0eXBlOiAnYWJvcnQnO1xuICByZWFzb24/OiBhbnk7XG59XG5cbmV4cG9ydCBjbGFzcyBBYm9ydFNpZ25hbCBleHRlbmRzIEV2ZW50RW1pdHRlciB7XG4gIHByaXZhdGUgX2Fib3J0ZWQ6IGJvb2xlYW47XG4gIHByaXZhdGUgX3JlYXNvbjogYW55O1xuXG4gIHB1YmxpYyBvbmFib3J0OiAoLi4uYXJnczogdW5rbm93bltdKSA9PiB2b2lkO1xuXG4gIGdldCBhYm9ydGVkKCkge1xuICAgIHJldHVybiB0aGlzLl9hYm9ydGVkO1xuICB9XG5cbiAgZ2V0IHJlYXNvbigpIHtcbiAgICByZXR1cm4gdGhpcy5fcmVhc29uO1xuICB9XG5cbiAgcHJpdmF0ZSBjb25zdHJ1Y3RvcigpIHtcbiAgICBzdXBlcigpO1xuICAgIHRoaXMuX2Fib3J0ZWQgPSBmYWxzZTtcbiAgfVxuXG4gIGdldCBbU3ltYm9sLnRvU3RyaW5nVGFnXSgpIHtcbiAgICByZXR1cm4gJ1tvYmplY3QgQWJvcnRTaWduYWxdJztcbiAgfVxuXG4gIGRpc3BhdGNoRXZlbnQoZXZlbnQ6IEFib3J0RXZlbnQpIHtcbiAgICBpZiAoZXZlbnQudHlwZSA9PT0gJ2Fib3J0Jykge1xuICAgICAgdGhpcy5fYWJvcnRlZCA9IHRydWU7XG4gICAgICB0aGlzLl9yZWFzb24gPSBldmVudC5yZWFzb247XG4gICAgICBpZiAodHlwZW9mIHRoaXMub25hYm9ydCA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgICB0aGlzLm9uYWJvcnQuY2FsbCh0aGlzLCBldmVudCk7XG4gICAgICB9XG4gICAgfVxuXG4gICAgc3VwZXIuZW1pdChldmVudC50eXBlLCBldmVudCk7XG4gIH1cblxuICBhZGRFdmVudExpc3RlbmVyKHR5cGU6IHN0cmluZywgbGlzdGVuZXI6ICguLi5hcmdzOiB1bmtub3duW10pID0+IHZvaWQpIHtcbiAgICBzdXBlci5hZGRMaXN0ZW5lcih0eXBlLCBsaXN0ZW5lcik7XG4gIH1cblxuICByZW1vdmVFdmVudExpc3RlbmVyKHR5cGU6IHN0cmluZywgbGlzdGVuZXI6ICguLi5hcmdzOiB1bmtub3duW10pID0+IHZvaWQpIHtcbiAgICBzdXBlci5yZW1vdmVMaXN0ZW5lcih0eXBlLCBsaXN0ZW5lcik7XG4gIH1cblxuICBzdGF0aWMgX19jcmVhdGUoKSB7XG4gICAgcmV0dXJuIG5ldyBBYm9ydFNpZ25hbCgpO1xuICB9XG59XG5cbmV4cG9ydCBjbGFzcyBBYm9ydENvbnRyb2xsZXIge1xuICBwcml2YXRlIF9zaWduYWw6IEFib3J0U2lnbmFsO1xuICBnZXQgc2lnbmFsKCkge1xuICAgIHJldHVybiB0aGlzLl9zaWduYWw7XG4gIH1cblxuICBjb25zdHJ1Y3RvcigpIHtcbiAgICB0aGlzLl9zaWduYWwgPSBBYm9ydFNpZ25hbC5fX2NyZWF0ZSgpO1xuICB9XG5cbiAgYWJvcnQocmVhc29uPzogYW55KSB7XG4gICAgbGV0IHNpZ25hbFJlYXNvbiA9IHJlYXNvbjtcbiAgICBpZiAoc2lnbmFsUmVhc29uID09PSB1bmRlZmluZWQpIHtcbiAgICAgIHNpZ25hbFJlYXNvbiA9IG5ldyBFcnJvcignVGhpcyBvcGVyYXRpb24gd2FzIGFib3J0ZWQnKTtcbiAgICAgIHNpZ25hbFJlYXNvbi5uYW1lID0gJ0Fib3J0RXJyb3InO1xuICAgIH1cblxuICAgIGNvbnN0IGV2ZW50OiBBYm9ydEV2ZW50ID0ge1xuICAgICAgdHlwZTogJ2Fib3J0JyxcbiAgICAgIHJlYXNvbjogc2lnbmFsUmVhc29uLFxuICAgIH07XG5cbiAgICB0aGlzLnNpZ25hbC5kaXNwYXRjaEV2ZW50KGV2ZW50KTtcbiAgfVxuXG4gIGdldCBbU3ltYm9sLnRvU3RyaW5nVGFnXSgpIHtcbiAgICByZXR1cm4gJ1tvYmplY3QgQWJvcnRDb250cm9sbGVyXSc7XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBCb2R5TWl4aW4gfSBmcm9tICcuL0JvZHlNaXhpbic7XG5pbXBvcnQgeyBIZWFkZXJzIH0gZnJvbSAnLi9IZWFkZXJzJztcbmltcG9ydCB7IEFib3J0Q29udHJvbGxlciwgQWJvcnRTaWduYWwgfSBmcm9tICcuL0Fib3J0Q29udHJvbGxlcic7XG5cbnR5cGUgUmVxdWVzdEx5bnhFeHRlbnNpb24gPSBSZWNvcmQ8c3RyaW5nLCBhbnk+O1xuXG5pbnRlcmZhY2UgUmVxdWVzdEluaXRJbm5lciBleHRlbmRzIFJlcXVlc3RJbml0IHtcbiAgbHlueEV4dGVuc2lvbj86IFJlcXVlc3RMeW54RXh0ZW5zaW9uO1xufVxuXG5leHBvcnQgY2xhc3MgUmVxdWVzdCBleHRlbmRzIEJvZHlNaXhpbiB7XG4gIHByaXZhdGUgX3VybDogc3RyaW5nO1xuICBwcml2YXRlIF9oZWFkZXJzOiBIZWFkZXJzO1xuICBwcml2YXRlIF9tZXRob2Q6IHN0cmluZztcbiAgcHJpdmF0ZSBfc2lnbmFsOiBBYm9ydFNpZ25hbDtcbiAgcHJpdmF0ZSBfbHlueEV4dGVuc2lvbjogUmVxdWVzdEx5bnhFeHRlbnNpb247XG5cbiAgZ2V0IHVybCgpIHtcbiAgICByZXR1cm4gdGhpcy5fdXJsO1xuICB9XG5cbiAgZ2V0IGhlYWRlcnMoKSB7XG4gICAgcmV0dXJuIHRoaXMuX2hlYWRlcnM7XG4gIH1cblxuICBnZXQgbWV0aG9kKCkge1xuICAgIHJldHVybiB0aGlzLl9tZXRob2Q7XG4gIH1cblxuICBnZXQgc2lnbmFsKCkge1xuICAgIHJldHVybiB0aGlzLl9zaWduYWw7XG4gIH1cblxuICBnZXQgbHlueEV4dGVuc2lvbigpIHtcbiAgICByZXR1cm4gdGhpcy5fbHlueEV4dGVuc2lvbjtcbiAgfVxuXG4gIGNvbnN0cnVjdG9yKGlucHV0OiBSZXF1ZXN0SW5mbywgb3B0aW9ucz86IFJlcXVlc3RJbml0SW5uZXIpIHtcbiAgICBzdXBlcigpO1xuICAgIG9wdGlvbnMgPSBvcHRpb25zIHx8IHt9O1xuXG4gICAgaWYgKGlucHV0IGluc3RhbmNlb2YgUmVxdWVzdCkge1xuICAgICAgaWYgKGlucHV0LmJvZHlVc2VkKSB7XG4gICAgICAgIHRocm93IG5ldyBUeXBlRXJyb3IoJ0FscmVhZHkgcmVhZCcpO1xuICAgICAgfVxuICAgICAgdGhpcy5fdXJsID0gaW5wdXQudXJsO1xuICAgICAgaWYgKCFvcHRpb25zLmhlYWRlcnMpIHtcbiAgICAgICAgdGhpcy5faGVhZGVycyA9IG5ldyBIZWFkZXJzKGlucHV0LmhlYWRlcnMgYXMgZ2xvYmFsVGhpcy5IZWFkZXJzKTtcbiAgICAgIH1cbiAgICAgIHRoaXMuX21ldGhvZCA9IGlucHV0Lm1ldGhvZDtcbiAgICAgIHRoaXMuX3NpZ25hbCA9IChpbnB1dC5zaWduYWwgYXMgYW55KSBhcyBBYm9ydFNpZ25hbDtcbiAgICAgIHRoaXMuc2V0Qm9keShpbnB1dC5fYXJyYXlCdWZmZXIpO1xuICAgIH0gZWxzZSB7XG4gICAgICB0aGlzLl91cmwgPSBTdHJpbmcoaW5wdXQpO1xuICAgIH1cblxuICAgIGlmIChvcHRpb25zLmhlYWRlcnMgfHwgIXRoaXMuaGVhZGVycykge1xuICAgICAgdGhpcy5faGVhZGVycyA9IG5ldyBIZWFkZXJzKG9wdGlvbnMuaGVhZGVycyk7XG4gICAgfVxuICAgIHRoaXMuX21ldGhvZCA9IG9wdGlvbnMubWV0aG9kIHx8IHRoaXMubWV0aG9kIHx8ICdHRVQnO1xuICAgIHRoaXMuX21ldGhvZCA9IHRoaXMuX21ldGhvZC50b1VwcGVyQ2FzZSgpO1xuXG4gICAgaWYgKCh0aGlzLm1ldGhvZCA9PT0gJ0dFVCcgfHwgdGhpcy5tZXRob2QgPT09ICdIRUFEJykgJiYgb3B0aW9ucy5ib2R5KSB7XG4gICAgICB0aHJvdyBuZXcgVHlwZUVycm9yKCdCb2R5IG5vdCBhbGxvd2VkIGZvciBHRVQgb3IgSEVBRCByZXF1ZXN0cycpO1xuICAgIH1cblxuICAgIGlmICh0eXBlb2Ygb3B0aW9ucy5zaWduYWwgIT09ICd1bmRlZmluZWQnKSB7XG4gICAgICB0aGlzLl9zaWduYWwgPSAob3B0aW9ucy5zaWduYWwgYXMgYW55KSBhcyBBYm9ydFNpZ25hbDtcbiAgICB9XG4gICAgdGhpcy5fc2lnbmFsID0gdGhpcy5fc2lnbmFsIHx8IEFib3J0U2lnbmFsLl9fY3JlYXRlKCk7XG5cbiAgICB0aGlzLl9seW54RXh0ZW5zaW9uID0gb3B0aW9ucy5seW54RXh0ZW5zaW9uIHx8IHt9O1xuXG4gICAgaWYgKCF0aGlzLl9oZWFkZXJzLmdldCgnQ29udGVudC1UeXBlJykpIHtcbiAgICAgIGlmICh0eXBlb2Ygb3B0aW9ucy5ib2R5ID09PSAnc3RyaW5nJykge1xuICAgICAgICB0aGlzLl9oZWFkZXJzLnNldCgnQ29udGVudC1UeXBlJywgJ3RleHQvcGxhaW47Y2hhcnNldD1VVEYtOCcpO1xuICAgICAgfSBlbHNlIGlmIChcbiAgICAgICAgZ2xvYmFsVGhpcy5VUkxTZWFyY2hQYXJhbXMgJiZcbiAgICAgICAgb3B0aW9ucy5ib2R5IGluc3RhbmNlb2YgVVJMU2VhcmNoUGFyYW1zXG4gICAgICApIHtcbiAgICAgICAgdGhpcy5faGVhZGVycy5zZXQoXG4gICAgICAgICAgJ0NvbnRlbnQtVHlwZScsXG4gICAgICAgICAgJ2FwcGxpY2F0aW9uL3gtd3d3LWZvcm0tdXJsZW5jb2RlZDtjaGFyc2V0PVVURi04J1xuICAgICAgICApO1xuICAgICAgfSBlbHNlIGlmIChvcHRpb25zLmJvZHkgaW5zdGFuY2VvZiBBcnJheUJ1ZmZlcikge1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgdGhpcy5faGVhZGVycy5zZXQoJ0NvbnRlbnQtVHlwZScsICd0ZXh0L3BsYWluO2NoYXJzZXQ9VVRGLTgnKTtcbiAgICAgIH1cbiAgICB9XG5cbiAgICB0aGlzLnNldEJvZHkob3B0aW9ucy5ib2R5KTtcbiAgfVxuXG4gIHB1YmxpYyBjbG9uZSgpOiBSZXF1ZXN0IHtcbiAgICBjb25zdCBjbG9uZWQgPSBuZXcgUmVxdWVzdCh0aGlzIGFzIGFueSwge1xuICAgICAgbWV0aG9kOiB0aGlzLm1ldGhvZCxcbiAgICB9KTtcblxuICAgIGNsb25lZC5zZXRCb2R5KHRoaXMpO1xuICAgIHJldHVybiBjbG9uZWQ7XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBCb2R5TWl4aW4gfSBmcm9tICcuL0JvZHlNaXhpbic7XG5cbnR5cGUgUmVzcG9uc2VMeW54RXh0ZW5zaW9uID0gUmVjb3JkPHN0cmluZywgYW55PjtcblxuaW50ZXJmYWNlIFJlc3BvbnNlSW5pdElubmVyIGV4dGVuZHMgUmVzcG9uc2VJbml0IHtcbiAgdXJsPzogc3RyaW5nO1xuICBseW54RXh0ZW5zaW9uPzogUmVzcG9uc2VMeW54RXh0ZW5zaW9uO1xufVxuXG5leHBvcnQgY2xhc3MgUmVzcG9uc2UgZXh0ZW5kcyBCb2R5TWl4aW4ge1xuICBwcml2YXRlIF91cmw6IHN0cmluZztcbiAgcHJpdmF0ZSBfc3RhdHVzOiBudW1iZXI7XG4gIHByaXZhdGUgX3N0YXR1c1RleHQ6IHN0cmluZztcbiAgcHJpdmF0ZSBfb2s6IGJvb2xlYW47XG4gIHByaXZhdGUgX2hlYWRlcnM6IEhlYWRlcnM7XG4gIHByaXZhdGUgX2x5bnhFeHRlbnNpb246IFJlc3BvbnNlTHlueEV4dGVuc2lvbjtcblxuICBnZXQgdXJsKCkge1xuICAgIHJldHVybiB0aGlzLl91cmw7XG4gIH1cblxuICBnZXQgc3RhdHVzKCkge1xuICAgIHJldHVybiB0aGlzLl9zdGF0dXM7XG4gIH1cblxuICBnZXQgc3RhdHVzVGV4dCgpIHtcbiAgICByZXR1cm4gdGhpcy5fc3RhdHVzVGV4dDtcbiAgfVxuXG4gIGdldCBvaygpIHtcbiAgICByZXR1cm4gdGhpcy5fb2s7XG4gIH1cblxuICBnZXQgaGVhZGVycygpIHtcbiAgICByZXR1cm4gdGhpcy5faGVhZGVycztcbiAgfVxuXG4gIGdldCBseW54RXh0ZW5zaW9uKCkge1xuICAgIHJldHVybiB0aGlzLl9seW54RXh0ZW5zaW9uO1xuICB9XG5cbiAgY29uc3RydWN0b3IoXG4gICAgYm9keUluaXQ/OiBCb2R5SW5pdCxcbiAgICBvcHRpb25zPzogUmVzcG9uc2VJbml0SW5uZXIsXG4gICAgZW5hYmxlRmV0Y2hBUElTdGFuZGFyZFN0cmVhbWluZz86IGJvb2xlYW5cbiAgKSB7XG4gICAgc3VwZXIoKTtcbiAgICBvcHRpb25zID0gb3B0aW9ucyB8fCB7fTtcblxuICAgIHRoaXMuX3N0YXR1cyA9IG9wdGlvbnMuc3RhdHVzID09PSB1bmRlZmluZWQgPyAyMDAgOiBvcHRpb25zLnN0YXR1cztcbiAgICBpZiAodGhpcy5fc3RhdHVzIDwgMjAwIHx8IHRoaXMuX3N0YXR1cyA+IDU5OSkge1xuICAgICAgdGhyb3cgbmV3IFJhbmdlRXJyb3IoXG4gICAgICAgIFwiRmFpbGVkIHRvIGNvbnN0cnVjdCAnUmVzcG9uc2UnOiBUaGUgc3RhdHVzIHByb3ZpZGVkICgwKSBpcyBvdXRzaWRlIHRoZSByYW5nZSBbMjAwLCA1OTldLlwiXG4gICAgICApO1xuICAgIH1cbiAgICB0aGlzLl9vayA9IHRoaXMuX3N0YXR1cyA+PSAyMDAgJiYgdGhpcy5fc3RhdHVzIDwgMzAwO1xuICAgIHRoaXMuX3N0YXR1c1RleHQgPVxuICAgICAgb3B0aW9ucy5zdGF0dXNUZXh0ID09PSB1bmRlZmluZWQgPyAnJyA6ICcnICsgb3B0aW9ucy5zdGF0dXNUZXh0O1xuICAgIHRoaXMuX2hlYWRlcnMgPSBuZXcgSGVhZGVycyhvcHRpb25zLmhlYWRlcnMpO1xuICAgIHRoaXMuX3VybCA9IG9wdGlvbnMudXJsIHx8ICcnO1xuICAgIHRoaXMuX2x5bnhFeHRlbnNpb24gPSBvcHRpb25zLmx5bnhFeHRlbnNpb24gfHwge307XG4gICAgdGhpcy5zZXRCb2R5KGJvZHlJbml0LCBlbmFibGVGZXRjaEFQSVN0YW5kYXJkU3RyZWFtaW5nKTtcbiAgfVxuXG4gIHB1YmxpYyBjbG9uZSgpOiBSZXNwb25zZSB7XG4gICAgY29uc3QgY2xvbmVkID0gbmV3IFJlc3BvbnNlKG51bGwsIHtcbiAgICAgIHN0YXR1czogdGhpcy5fc3RhdHVzLFxuICAgICAgc3RhdHVzVGV4dDogdGhpcy5fc3RhdHVzVGV4dCxcbiAgICAgIGhlYWRlcnM6IG5ldyBIZWFkZXJzKHRoaXMuX2hlYWRlcnMpLFxuICAgICAgdXJsOiB0aGlzLl91cmwsXG4gICAgfSk7XG5cbiAgICBjbG9uZWQuc2V0Qm9keSh0aGlzKTtcblxuICAgIHJldHVybiBjbG9uZWQ7XG4gIH1cbn1cbiIsICIvKipcbiAqIENvcHlyaWdodCAoYykgTWV0YSBQbGF0Zm9ybXMsIEluYy4gYW5kIGFmZmlsaWF0ZXMuXG4gKlxuICogVGhpcyBzb3VyY2UgY29kZSBpcyBsaWNlbnNlZCB1bmRlciB0aGUgTUlUIGxpY2Vuc2UgZm91bmQgaW4gdGhlXG4gKiBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG4gKlxuICovXG5cbmZ1bmN0aW9uIHZhbGlkYXRlQmFzZVVybCh1cmwpIHtcbiAgICAvLyBmcm9tIHRoaXMgTUlULWxpY2Vuc2VkIGdpc3Q6IGh0dHBzOi8vZ2lzdC5naXRodWIuY29tL2RwZXJpbmkvNzI5Mjk0XG4gICAgcmV0dXJuIC9eKD86KD86KD86aHR0cHM/fGZ0cCk6KT9cXC9cXC8pKD86KD86WzEtOV1cXGQ/fDFcXGRcXGR8MlswMV1cXGR8MjJbMC0zXSkoPzpcXC4oPzoxP1xcZHsxLDJ9fDJbMC00XVxcZHwyNVswLTVdKSl7Mn0oPzpcXC4oPzpbMS05XVxcZD98MVxcZFxcZHwyWzAtNF1cXGR8MjVbMC00XSkpfCg/Oig/OlthLXowLTlcXHUwMGExLVxcdWZmZmZdW2EtejAtOVxcdTAwYTEtXFx1ZmZmZl8tXXswLDYyfSk/W2EtejAtOVxcdTAwYTEtXFx1ZmZmZl1cXC4pKig/OlthLXpcXHUwMGExLVxcdWZmZmZdezIsfVxcLj8pKSg/OjpcXGR7Miw1fSk/KD86Wy8/I11cXFMqKT8kLy50ZXN0KFxuICAgICAgdXJsLFxuICAgICk7XG4gIH1cbiAgXG5leHBvcnQgY2xhc3MgVVJMIHtcbiAgICBfdXJsO1xuICAgIF9zZWFyY2hQYXJhbXNJbnN0YW5jZSA9IG51bGw7XG4gIFxuICAgIGNvbnN0cnVjdG9yKHVybCwgYmFzZSkge1xuICAgICAgbGV0IGJhc2VVcmwgPSBudWxsO1xuICAgICAgaWYgKCFiYXNlIHx8IHZhbGlkYXRlQmFzZVVybCh1cmwpKSB7XG4gICAgICAgIHRoaXMuX3VybCA9IHVybDtcbiAgICAgICAgaWYgKCF0aGlzLl91cmwuZW5kc1dpdGgoJy8nKSkge1xuICAgICAgICAgIHRoaXMuX3VybCArPSAnLyc7XG4gICAgICAgIH1cbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIGlmICh0eXBlb2YgYmFzZSA9PT0gJ3N0cmluZycpIHtcbiAgICAgICAgICBiYXNlVXJsID0gYmFzZTtcbiAgICAgICAgICBpZiAoIXZhbGlkYXRlQmFzZVVybChiYXNlVXJsKSkge1xuICAgICAgICAgICAgdGhyb3cgbmV3IFR5cGVFcnJvcihgSW52YWxpZCBiYXNlIFVSTDogJHtiYXNlVXJsfWApO1xuICAgICAgICAgIH1cbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICBiYXNlVXJsID0gYmFzZS50b1N0cmluZygpO1xuICAgICAgICB9XG4gICAgICAgIGlmIChiYXNlVXJsLmVuZHNXaXRoKCcvJykpIHtcbiAgICAgICAgICBiYXNlVXJsID0gYmFzZVVybC5zbGljZSgwLCBiYXNlVXJsLmxlbmd0aCAtIDEpO1xuICAgICAgICB9XG4gICAgICAgIGlmICghdXJsLnN0YXJ0c1dpdGgoJy8nKSkge1xuICAgICAgICAgIHVybCA9IGAvJHt1cmx9YDtcbiAgICAgICAgfVxuICAgICAgICBpZiAoYmFzZVVybC5lbmRzV2l0aCh1cmwpKSB7XG4gICAgICAgICAgdXJsID0gJyc7XG4gICAgICAgIH1cbiAgICAgICAgdGhpcy5fdXJsID0gYCR7YmFzZVVybH0ke3VybH1gO1xuICAgICAgfVxuICAgIH1cblxuICAgIGdldCBocmVmKCkge1xuICAgICAgcmV0dXJuIHRoaXMudG9TdHJpbmcoKTtcbiAgICB9XG4gIFxuICAgIGdldCBzZWFyY2hQYXJhbXMoKSB7XG4gICAgICBpZiAodGhpcy5fc2VhcmNoUGFyYW1zSW5zdGFuY2UgPT0gbnVsbCkge1xuICAgICAgICB0aGlzLl9zZWFyY2hQYXJhbXNJbnN0YW5jZSA9IG5ldyBVUkxTZWFyY2hQYXJhbXMoKTtcbiAgICAgIH1cbiAgICAgIHJldHVybiB0aGlzLl9zZWFyY2hQYXJhbXNJbnN0YW5jZTtcbiAgICB9XG4gIFxuICAgIHRvSlNPTigpIHtcbiAgICAgIHJldHVybiB0aGlzLnRvU3RyaW5nKCk7XG4gICAgfVxuICBcbiAgICB0b1N0cmluZygpIHtcbiAgICAgIGlmICh0aGlzLl9zZWFyY2hQYXJhbXNJbnN0YW5jZSA9PT0gbnVsbCkge1xuICAgICAgICByZXR1cm4gdGhpcy5fdXJsO1xuICAgICAgfVxuICBcbiAgICAgIGNvbnN0IGluc3RhbmNlU3RyaW5nID0gdGhpcy5fc2VhcmNoUGFyYW1zSW5zdGFuY2UudG9TdHJpbmcoKTtcbiAgICAgIGNvbnN0IHNlcGFyYXRvciA9IHRoaXMuX3VybC5pbmRleE9mKCc/JykgPiAtMSA/ICcmJyA6ICc/JztcbiAgICAgIHJldHVybiB0aGlzLl91cmwgKyBzZXBhcmF0b3IgKyBpbnN0YW5jZVN0cmluZztcbiAgICB9XG4gIH1cbiAgIiwgIi8vIE1JVCBMaWNlbnNlXG5cbi8vIENvcHlyaWdodCAoYykgMjAxNiBKZXJyeSBCZW5keVxuXG4vLyBQZXJtaXNzaW9uIGlzIGhlcmVieSBncmFudGVkLCBmcmVlIG9mIGNoYXJnZSwgdG8gYW55IHBlcnNvbiBvYnRhaW5pbmcgYSBjb3B5XG4vLyBvZiB0aGlzIHNvZnR3YXJlIGFuZCBhc3NvY2lhdGVkIGRvY3VtZW50YXRpb24gZmlsZXMgKHRoZSBcIlNvZnR3YXJlXCIpLCB0byBkZWFsXG4vLyBpbiB0aGUgU29mdHdhcmUgd2l0aG91dCByZXN0cmljdGlvbiwgaW5jbHVkaW5nIHdpdGhvdXQgbGltaXRhdGlvbiB0aGUgcmlnaHRzXG4vLyB0byB1c2UsIGNvcHksIG1vZGlmeSwgbWVyZ2UsIHB1Ymxpc2gsIGRpc3RyaWJ1dGUsIHN1YmxpY2Vuc2UsIGFuZC9vciBzZWxsXG4vLyBjb3BpZXMgb2YgdGhlIFNvZnR3YXJlLCBhbmQgdG8gcGVybWl0IHBlcnNvbnMgdG8gd2hvbSB0aGUgU29mdHdhcmUgaXNcbi8vIGZ1cm5pc2hlZCB0byBkbyBzbywgc3ViamVjdCB0byB0aGUgZm9sbG93aW5nIGNvbmRpdGlvbnM6XG5cbi8vIFRoZSBhYm92ZSBjb3B5cmlnaHQgbm90aWNlIGFuZCB0aGlzIHBlcm1pc3Npb24gbm90aWNlIHNoYWxsIGJlIGluY2x1ZGVkIGluIGFsbFxuLy8gY29waWVzIG9yIHN1YnN0YW50aWFsIHBvcnRpb25zIG9mIHRoZSBTb2Z0d2FyZS5cblxuLy8gVEhFIFNPRlRXQVJFIElTIFBST1ZJREVEIFwiQVMgSVNcIiwgV0lUSE9VVCBXQVJSQU5UWSBPRiBBTlkgS0lORCwgRVhQUkVTUyBPUlxuLy8gSU1QTElFRCwgSU5DTFVESU5HIEJVVCBOT1QgTElNSVRFRCBUTyBUSEUgV0FSUkFOVElFUyBPRiBNRVJDSEFOVEFCSUxJVFksXG4vLyBGSVRORVNTIEZPUiBBIFBBUlRJQ1VMQVIgUFVSUE9TRSBBTkQgTk9OSU5GUklOR0VNRU5ULiBJTiBOTyBFVkVOVCBTSEFMTCBUSEVcbi8vIEFVVEhPUlMgT1IgQ09QWVJJR0hUIEhPTERFUlMgQkUgTElBQkxFIEZPUiBBTlkgQ0xBSU0sIERBTUFHRVMgT1IgT1RIRVJcbi8vIExJQUJJTElUWSwgV0hFVEhFUiBJTiBBTiBBQ1RJT04gT0YgQ09OVFJBQ1QsIFRPUlQgT1IgT1RIRVJXSVNFLCBBUklTSU5HIEZST00sXG4vLyBPVVQgT0YgT1IgSU4gQ09OTkVDVElPTiBXSVRIIFRIRSBTT0ZUV0FSRSBPUiBUSEUgVVNFIE9SIE9USEVSIERFQUxJTkdTIElOIFRIRVxuLy8gU09GVFdBUkUuXG5cbi8qKiFcbiAqIHVybC1zZWFyY2gtcGFyYW1zLXBvbHlmaWxsXG4gKlxuICogQGF1dGhvciBKZXJyeSBCZW5keSAoaHR0cHM6Ly9naXRodWIuY29tL2plcnJ5YmVuZHkpXG4gKiBAbGljZW5jZSBNSVRcbiAqL1xuXG5leHBvcnQgZnVuY3Rpb24gVVJMU2VhcmNoUGFyYW1zUG9seWZpbGwoc2VsZikge1xuICAgICd1c2Ugc3RyaWN0JztcbiAgICBjb25zdCBfX1VSTFNlYXJjaFBhcmFtc19fID0gXCJfX1VSTFNlYXJjaFBhcmFtc19fXCI7XG4vKipcbiAqIE1ha2UgYSBVUkxTZWFyY2hQYXJhbXMgaW5zdGFuY2VcbiAqXG4gKiBAcGFyYW0ge29iamVjdHxzdHJpbmd8VVJMU2VhcmNoUGFyYW1zfSBzZWFyY2hcbiAqIEBjb25zdHJ1Y3RvclxuICovXG5mdW5jdGlvbiBVUkxTZWFyY2hQYXJhbXNQb2x5ZmlsbChzZWFyY2gpIHtcbiAgICBzZWFyY2ggPSBzZWFyY2ggfHwgXCJcIjtcblxuICAgIC8vIHN1cHBvcnQgY29uc3RydWN0IG9iamVjdCB3aXRoIGFub3RoZXIgVVJMU2VhcmNoUGFyYW1zIGluc3RhbmNlXG4gICAgaWYgKHNlYXJjaCBpbnN0YW5jZW9mIFVSTFNlYXJjaFBhcmFtcykge1xuICAgICAgICBzZWFyY2ggPSBzZWFyY2gudG9TdHJpbmcoKTtcbiAgICB9XG4gICAgdGhpcyBbX19VUkxTZWFyY2hQYXJhbXNfX10gPSBwYXJzZVRvRGljdChzZWFyY2gpO1xufVxuXG5jb25zdCBwcm90b3R5cGUgPSBVUkxTZWFyY2hQYXJhbXNQb2x5ZmlsbC5wcm90b3R5cGU7XG5cbi8qKlxuICogQXBwZW5kcyBhIHNwZWNpZmllZCBrZXkvdmFsdWUgcGFpciBhcyBhIG5ldyBzZWFyY2ggcGFyYW1ldGVyLlxuICpcbiAqIEBwYXJhbSB7c3RyaW5nfSBuYW1lXG4gKiBAcGFyYW0ge3N0cmluZ30gdmFsdWVcbiAqL1xucHJvdG90eXBlLmFwcGVuZCA9IGZ1bmN0aW9uKG5hbWUsIHZhbHVlKSB7XG4gICAgYXBwZW5kVG8odGhpcyBbX19VUkxTZWFyY2hQYXJhbXNfX10sIG5hbWUsIHZhbHVlKTtcbn07XG5cbi8qKlxuICogRGVsZXRlcyB0aGUgZ2l2ZW4gc2VhcmNoIHBhcmFtZXRlciwgYW5kIGl0cyBhc3NvY2lhdGVkIHZhbHVlLFxuICogZnJvbSB0aGUgbGlzdCBvZiBhbGwgc2VhcmNoIHBhcmFtZXRlcnMuXG4gKlxuICogQHBhcmFtIHtzdHJpbmd9IG5hbWVcbiAqL1xucHJvdG90eXBlWydkZWxldGUnXSA9IGZ1bmN0aW9uKG5hbWUpIHtcbiAgICBkZWxldGUgdGhpcyBbX19VUkxTZWFyY2hQYXJhbXNfX10gW25hbWVdO1xufTtcblxuLyoqXG4gKiBSZXR1cm5zIHRoZSBmaXJzdCB2YWx1ZSBhc3NvY2lhdGVkIHRvIHRoZSBnaXZlbiBzZWFyY2ggcGFyYW1ldGVyLlxuICpcbiAqIEBwYXJhbSB7c3RyaW5nfSBuYW1lXG4gKiBAcmV0dXJucyB7c3RyaW5nfG51bGx9XG4gKi9cbnByb3RvdHlwZS5nZXQgPSBmdW5jdGlvbihuYW1lKSB7XG4gICAgdmFyIGRpY3QgPSB0aGlzIFtfX1VSTFNlYXJjaFBhcmFtc19fXTtcbiAgICByZXR1cm4gdGhpcy5oYXMobmFtZSkgPyBkaWN0W25hbWVdWzBdIDogbnVsbDtcbn07XG5cbi8qKlxuICogUmV0dXJucyBhbGwgdGhlIHZhbHVlcyBhc3NvY2lhdGlvbiB3aXRoIGEgZ2l2ZW4gc2VhcmNoIHBhcmFtZXRlci5cbiAqXG4gKiBAcGFyYW0ge3N0cmluZ30gbmFtZVxuICogQHJldHVybnMge0FycmF5fVxuICovXG5wcm90b3R5cGUuZ2V0QWxsID0gZnVuY3Rpb24obmFtZSkge1xuICAgIHZhciBkaWN0ID0gdGhpcyBbX19VUkxTZWFyY2hQYXJhbXNfX107XG4gICAgcmV0dXJuIHRoaXMuaGFzKG5hbWUpID8gZGljdCBbbmFtZV0uc2xpY2UoMCkgOiBbXTtcbn07XG5cbi8qKlxuICogUmV0dXJucyBhIEJvb2xlYW4gaW5kaWNhdGluZyBpZiBzdWNoIGEgc2VhcmNoIHBhcmFtZXRlciBleGlzdHMuXG4gKlxuICogQHBhcmFtIHtzdHJpbmd9IG5hbWVcbiAqIEByZXR1cm5zIHtib29sZWFufVxuICovXG5wcm90b3R5cGUuaGFzID0gZnVuY3Rpb24obmFtZSkge1xuICAgIHJldHVybiBoYXNPd25Qcm9wZXJ0eSh0aGlzIFtfX1VSTFNlYXJjaFBhcmFtc19fXSwgbmFtZSk7XG59O1xuXG4vKipcbiAqIFNldHMgdGhlIHZhbHVlIGFzc29jaWF0ZWQgdG8gYSBnaXZlbiBzZWFyY2ggcGFyYW1ldGVyIHRvXG4gKiB0aGUgZ2l2ZW4gdmFsdWUuIElmIHRoZXJlIHdlcmUgc2V2ZXJhbCB2YWx1ZXMsIGRlbGV0ZSB0aGVcbiAqIG90aGVycy5cbiAqXG4gKiBAcGFyYW0ge3N0cmluZ30gbmFtZVxuICogQHBhcmFtIHtzdHJpbmd9IHZhbHVlXG4gKi9cbnByb3RvdHlwZS5zZXQgPSBmdW5jdGlvbiBzZXQobmFtZSwgdmFsdWUpIHtcbiAgICB0aGlzIFtfX1VSTFNlYXJjaFBhcmFtc19fXVtuYW1lXSA9IFsnJyArIHZhbHVlXTtcbn07XG5cbi8qKlxuICogUmV0dXJucyBhIHN0cmluZyBjb250YWluaW5nIGEgcXVlcnkgc3RyaW5nIHN1aXRhYmxlIGZvciB1c2UgaW4gYSBVUkwuXG4gKlxuICogQHJldHVybnMge3N0cmluZ31cbiAqL1xucHJvdG90eXBlLnRvU3RyaW5nID0gZnVuY3Rpb24oKSB7XG4gICAgdmFyIGRpY3QgPSB0aGlzW19fVVJMU2VhcmNoUGFyYW1zX19dLCBxdWVyeSA9IFtdLCBpLCBrZXksIG5hbWUsIHZhbHVlO1xuICAgIGZvciAoa2V5IGluIGRpY3QpIHtcbiAgICAgICAgbmFtZSA9IGVuY29kZShrZXkpO1xuICAgICAgICBmb3IgKGkgPSAwLCB2YWx1ZSA9IGRpY3Rba2V5XTsgaSA8IHZhbHVlLmxlbmd0aDsgaSsrKSB7XG4gICAgICAgICAgICBxdWVyeS5wdXNoKG5hbWUgKyAnPScgKyBlbmNvZGUodmFsdWVbaV0pKTtcbiAgICAgICAgfVxuICAgIH1cbiAgICByZXR1cm4gcXVlcnkuam9pbignJicpO1xufTtcblxucHJvdG90eXBlLnBvbHlmaWxsID0gdHJ1ZTtcbnByb3RvdHlwZVtTeW1ib2wudG9TdHJpbmdUYWddID0gJ1VSTFNlYXJjaFBhcmFtcyc7XG5cbi8qKlxuICpcbiAqIEBwYXJhbSB7ZnVuY3Rpb259IGNhbGxiYWNrXG4gKiBAcGFyYW0ge29iamVjdH0gdGhpc0FyZ1xuICovXG5wcm90b3R5cGUuZm9yRWFjaCA9IGZ1bmN0aW9uKGNhbGxiYWNrLCB0aGlzQXJnKSB7XG4gICAgdmFyIGRpY3QgPSBwYXJzZVRvRGljdCh0aGlzLnRvU3RyaW5nKCkpO1xuICAgIE9iamVjdC5nZXRPd25Qcm9wZXJ0eU5hbWVzKGRpY3QpLmZvckVhY2goZnVuY3Rpb24obmFtZSkge1xuICAgICAgICBkaWN0W25hbWVdLmZvckVhY2goZnVuY3Rpb24odmFsdWUpIHtcbiAgICAgICAgICAgIGNhbGxiYWNrLmNhbGwodGhpc0FyZywgdmFsdWUsIG5hbWUsIHRoaXMpO1xuICAgICAgICB9LCB0aGlzKTtcbiAgICB9LCB0aGlzKTtcbn07XG5cbi8qKlxuICogU29ydCBhbGwgbmFtZS12YWx1ZSBwYWlyc1xuICovXG5wcm90b3R5cGUuc29ydCA9IGZ1bmN0aW9uKCkge1xuICAgIHZhciBkaWN0ID0gcGFyc2VUb0RpY3QodGhpcy50b1N0cmluZygpKSwga2V5cyA9IFtdLCBrLCBpLCBqO1xuICAgIGZvciAoayBpbiBkaWN0KSB7XG4gICAgICAgIGtleXMucHVzaChrKTtcbiAgICB9XG4gICAga2V5cy5zb3J0KCk7XG5cbiAgICBmb3IgKGkgPSAwOyBpIDwga2V5cy5sZW5ndGg7IGkrKykge1xuICAgICAgICB0aGlzWydkZWxldGUnXShrZXlzW2ldKTtcbiAgICB9XG4gICAgZm9yIChpID0gMDsgaSA8IGtleXMubGVuZ3RoOyBpKyspIHtcbiAgICAgICAgdmFyIGtleSA9IGtleXNbaV0sIHZhbHVlcyA9IGRpY3Rba2V5XTtcbiAgICAgICAgZm9yIChqID0gMDsgaiA8IHZhbHVlcy5sZW5ndGg7IGorKykge1xuICAgICAgICAgICAgdGhpcy5hcHBlbmQoa2V5LCB2YWx1ZXNbal0pO1xuICAgICAgICB9XG4gICAgfVxufTtcblxuLyoqXG4gKiBSZXR1cm5zIGFuIGl0ZXJhdG9yIGFsbG93aW5nIHRvIGdvIHRocm91Z2ggYWxsIGtleXMgb2ZcbiAqIHRoZSBrZXkvdmFsdWUgcGFpcnMgY29udGFpbmVkIGluIHRoaXMgb2JqZWN0LlxuICpcbiAqIEByZXR1cm5zIHtmdW5jdGlvbn1cbiAqL1xucHJvdG90eXBlLmtleXMgPSBmdW5jdGlvbigpIHtcbiAgICB2YXIgaXRlbXMgPSBbXTtcbiAgICB0aGlzLmZvckVhY2goZnVuY3Rpb24oaXRlbSwgbmFtZSkge1xuICAgICAgICBpdGVtcy5wdXNoKG5hbWUpO1xuICAgIH0pO1xuICAgIHJldHVybiBtYWtlSXRlcmF0b3IoaXRlbXMpO1xufTtcblxuLyoqXG4gKiBSZXR1cm5zIGFuIGl0ZXJhdG9yIGFsbG93aW5nIHRvIGdvIHRocm91Z2ggYWxsIHZhbHVlcyBvZlxuICogdGhlIGtleS92YWx1ZSBwYWlycyBjb250YWluZWQgaW4gdGhpcyBvYmplY3QuXG4gKlxuICogQHJldHVybnMge2Z1bmN0aW9ufVxuICovXG5wcm90b3R5cGUudmFsdWVzID0gZnVuY3Rpb24oKSB7XG4gICAgdmFyIGl0ZW1zID0gW107XG4gICAgdGhpcy5mb3JFYWNoKGZ1bmN0aW9uKGl0ZW0pIHtcbiAgICAgICAgaXRlbXMucHVzaChpdGVtKTtcbiAgICB9KTtcbiAgICByZXR1cm4gbWFrZUl0ZXJhdG9yKGl0ZW1zKTtcbn07XG5cbi8qKlxuICogUmV0dXJucyBhbiBpdGVyYXRvciBhbGxvd2luZyB0byBnbyB0aHJvdWdoIGFsbCBrZXkvdmFsdWVcbiAqIHBhaXJzIGNvbnRhaW5lZCBpbiB0aGlzIG9iamVjdC5cbiAqXG4gKiBAcmV0dXJucyB7ZnVuY3Rpb259XG4gKi9cbnByb3RvdHlwZS5lbnRyaWVzID0gZnVuY3Rpb24oKSB7XG4gICAgdmFyIGl0ZW1zID0gW107XG4gICAgdGhpcy5mb3JFYWNoKGZ1bmN0aW9uKGl0ZW0sIG5hbWUpIHtcbiAgICAgICAgaXRlbXMucHVzaChbbmFtZSwgaXRlbV0pO1xuICAgIH0pO1xuICAgIHJldHVybiBtYWtlSXRlcmF0b3IoaXRlbXMpO1xufTtcblxucHJvdG90eXBlW1N5bWJvbC5pdGVyYXRvcl0gPSBwcm90b3R5cGUuZW50cmllcztcblxuT2JqZWN0LmRlZmluZVByb3BlcnR5KHByb3RvdHlwZSwgJ3NpemUnLCB7XG4gICAgZ2V0OiBmdW5jdGlvbiAoKSB7XG4gICAgICAgIHZhciBkaWN0ID0gcGFyc2VUb0RpY3QodGhpcy50b1N0cmluZygpKVxuICAgICAgICBpZiAocHJvdG90eXBlID09PSB0aGlzKSB7XG4gICAgICAgICAgICB0aHJvdyBuZXcgVHlwZUVycm9yKCdJbGxlZ2FsIGludm9jYXRpb24gYXQgVVJMU2VhcmNoUGFyYW1zLmludm9rZUdldHRlcicpXG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIE9iamVjdC5rZXlzKGRpY3QpLnJlZHVjZShmdW5jdGlvbiAocHJldiwgY3VyKSB7XG4gICAgICAgICAgICByZXR1cm4gcHJldiArIGRpY3RbY3VyXS5sZW5ndGg7XG4gICAgICAgIH0sIDApO1xuICAgIH1cbn0pO1xuXG5mdW5jdGlvbiBlbmNvZGUoc3RyKSB7XG4gICAgdmFyIHJlcGxhY2UgPSB7XG4gICAgICAgICchJzogJyUyMScsXG4gICAgICAgIFwiJ1wiOiAnJTI3JyxcbiAgICAgICAgJygnOiAnJTI4JyxcbiAgICAgICAgJyknOiAnJTI5JyxcbiAgICAgICAgJ34nOiAnJTdFJyxcbiAgICAgICAgJyUyMCc6ICcrJyxcbiAgICAgICAgJyUwMCc6ICdcXHgwMCdcbiAgICB9O1xuICAgIHJldHVybiBlbmNvZGVVUklDb21wb25lbnQoc3RyKS5yZXBsYWNlKC9bISdcXChcXCl+XXwlMjB8JTAwL2csIGZ1bmN0aW9uKG1hdGNoKSB7XG4gICAgICAgIHJldHVybiByZXBsYWNlW21hdGNoXTtcbiAgICB9KTtcbn1cblxuZnVuY3Rpb24gZGVjb2RlKHN0cikge1xuICAgIHJldHVybiBzdHJcbiAgICAgICAgLnJlcGxhY2UoL1sgK10vZywgJyUyMCcpXG4gICAgICAgIC5yZXBsYWNlKC8oJVthLWYwLTldezJ9KSsvaWcsIGZ1bmN0aW9uKG1hdGNoKSB7XG4gICAgICAgICAgICByZXR1cm4gZGVjb2RlVVJJQ29tcG9uZW50KG1hdGNoKTtcbiAgICAgICAgfSk7XG59XG5cbmZ1bmN0aW9uIG1ha2VJdGVyYXRvcihhcnIpIHtcbiAgICB2YXIgaXRlcmF0b3IgPSB7XG4gICAgICAgIG5leHQ6IGZ1bmN0aW9uKCkge1xuICAgICAgICAgICAgdmFyIHZhbHVlID0gYXJyLnNoaWZ0KCk7XG4gICAgICAgICAgICByZXR1cm4ge2RvbmU6IHZhbHVlID09PSB1bmRlZmluZWQsIHZhbHVlOiB2YWx1ZX07XG4gICAgICAgIH1cbiAgICB9O1xuXG4gICAgaXRlcmF0b3JbU3ltYm9sLml0ZXJhdG9yXSA9IGZ1bmN0aW9uKCkge1xuICAgICAgICByZXR1cm4gaXRlcmF0b3I7XG4gICAgfTtcblxuICAgIHJldHVybiBpdGVyYXRvcjtcbn1cblxuZnVuY3Rpb24gcGFyc2VUb0RpY3Qoc2VhcmNoKSB7XG4gICAgdmFyIGRpY3QgPSB7fTtcblxuICAgIGlmICh0eXBlb2Ygc2VhcmNoID09PSBcIm9iamVjdFwiKSB7XG4gICAgICAgIC8vIGlmIGBzZWFyY2hgIGlzIGFuIGFycmF5LCB0cmVhdCBpdCBhcyBhIHNlcXVlbmNlXG4gICAgICAgIGlmIChpc0FycmF5KHNlYXJjaCkpIHtcbiAgICAgICAgICAgIGZvciAodmFyIGkgPSAwOyBpIDwgc2VhcmNoLmxlbmd0aDsgaSsrKSB7XG4gICAgICAgICAgICAgICAgdmFyIGl0ZW0gPSBzZWFyY2hbaV07XG4gICAgICAgICAgICAgICAgaWYgKGlzQXJyYXkoaXRlbSkgJiYgaXRlbS5sZW5ndGggPT09IDIpIHtcbiAgICAgICAgICAgICAgICAgICAgYXBwZW5kVG8oZGljdCwgaXRlbVswXSwgaXRlbVsxXSk7XG4gICAgICAgICAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICAgICAgICAgICAgdGhyb3cgbmV3IFR5cGVFcnJvcihcIkZhaWxlZCB0byBjb25zdHJ1Y3QgJ1VSTFNlYXJjaFBhcmFtcyc6IFNlcXVlbmNlIGluaXRpYWxpemVyIG11c3Qgb25seSBjb250YWluIHBhaXIgZWxlbWVudHNcIik7XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgfVxuXG4gICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgICBmb3IgKHZhciBrZXkgaW4gc2VhcmNoKSB7XG4gICAgICAgICAgICAgICAgaWYgKHNlYXJjaC5oYXNPd25Qcm9wZXJ0eShrZXkpKSB7XG4gICAgICAgICAgICAgICAgICAgIGFwcGVuZFRvKGRpY3QsIGtleSwgc2VhcmNoW2tleV0pO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuXG4gICAgfSBlbHNlIHtcbiAgICAgICAgLy8gcmVtb3ZlIGZpcnN0ICc/J1xuICAgICAgICBpZiAoc2VhcmNoLmluZGV4T2YoXCI/XCIpID09PSAwKSB7XG4gICAgICAgICAgICBzZWFyY2ggPSBzZWFyY2guc2xpY2UoMSk7XG4gICAgICAgIH1cblxuICAgICAgICB2YXIgcGFpcnMgPSBzZWFyY2guc3BsaXQoXCImXCIpO1xuICAgICAgICBmb3IgKHZhciBqID0gMDsgaiA8IHBhaXJzLmxlbmd0aDsgaisrKSB7XG4gICAgICAgICAgICB2YXIgdmFsdWUgPSBwYWlycyBbal0sXG4gICAgICAgICAgICAgICAgaW5kZXggPSB2YWx1ZS5pbmRleE9mKCc9Jyk7XG5cbiAgICAgICAgICAgIGlmICgtMSA8IGluZGV4KSB7XG4gICAgICAgICAgICAgICAgYXBwZW5kVG8oZGljdCwgZGVjb2RlKHZhbHVlLnNsaWNlKDAsIGluZGV4KSksIGRlY29kZSh2YWx1ZS5zbGljZShpbmRleCArIDEpKSk7XG5cbiAgICAgICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgICAgICAgaWYgKHZhbHVlKSB7XG4gICAgICAgICAgICAgICAgICAgIGFwcGVuZFRvKGRpY3QsIGRlY29kZSh2YWx1ZSksICcnKTtcbiAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICB9XG5cbiAgICByZXR1cm4gZGljdDtcbn1cblxuZnVuY3Rpb24gYXBwZW5kVG8oZGljdCwgbmFtZSwgdmFsdWUpIHtcbiAgICB2YXIgdmFsID0gdHlwZW9mIHZhbHVlID09PSAnc3RyaW5nJyA/IHZhbHVlIDogKFxuICAgICAgICB2YWx1ZSAhPT0gbnVsbCAmJiB2YWx1ZSAhPT0gdW5kZWZpbmVkICYmIHR5cGVvZiB2YWx1ZS50b1N0cmluZyA9PT0gJ2Z1bmN0aW9uJyA/IHZhbHVlLnRvU3RyaW5nKCkgOiBKU09OLnN0cmluZ2lmeSh2YWx1ZSlcbiAgICApO1xuXG4gICAgLy8gIzQ3IFByZXZlbnQgdXNpbmcgYGhhc093blByb3BlcnR5YCBhcyBhIHByb3BlcnR5IG5hbWVcbiAgICBpZiAoaGFzT3duUHJvcGVydHkoZGljdCwgbmFtZSkpIHtcbiAgICAgICAgZGljdFtuYW1lXS5wdXNoKHZhbCk7XG4gICAgfSBlbHNlIHtcbiAgICAgICAgZGljdFtuYW1lXSA9IFt2YWxdO1xuICAgIH1cbn1cblxuZnVuY3Rpb24gaXNBcnJheSh2YWwpIHtcbiAgICByZXR1cm4gISF2YWwgJiYgJ1tvYmplY3QgQXJyYXldJyA9PT0gT2JqZWN0LnByb3RvdHlwZS50b1N0cmluZy5jYWxsKHZhbCk7XG59XG5cbmZ1bmN0aW9uIGhhc093blByb3BlcnR5KG9iaiwgcHJvcCkge1xuICAgIHJldHVybiBPYmplY3QucHJvdG90eXBlLmhhc093blByb3BlcnR5LmNhbGwob2JqLCBwcm9wKTtcbn1cblxuc2VsZi5VUkxTZWFyY2hQYXJhbXMgPSBzZWxmLlVSTFNlYXJjaFBhcmFtcyA/PyBVUkxTZWFyY2hQYXJhbXNQb2x5ZmlsbDtcblxufSIsICJpbXBvcnQgeyBMeW54IH0gZnJvbSAnQGx5bngtanMvdHlwZXMnO1xuaW1wb3J0IHsgQmFzZUV2ZW50T3JpZywgVGFyZ2V0IH0gZnJvbSAnLi4vLi4vLi4vLi4vdHlwZXMvdHlwZXMvY29tbW9uL2V2ZW50cyc7XG5cbnR5cGUgRXZlbnRTb3VyY2VFdmVudCA9IHtcbiAgZGF0YTogc3RyaW5nO1xuICBldmVudD86IHN0cmluZztcbiAgaWQ/OiBzdHJpbmc7XG4gIFtrZXk6IHN0cmluZ106IGFueTtcbn07XG50eXBlIEV2ZW50ID0gQmFzZUV2ZW50T3JpZzxhbnk+O1xuXG5pbnRlcmZhY2UgRmV0Y2hFdmVudFNvdXJjZU9wdGlvbnMgZXh0ZW5kcyBSZXF1ZXN0SW5pdCB7fVxuXG5leHBvcnQgZnVuY3Rpb24gY3JlYXRlRXZlbnRTb3VyY2UoZmV0Y2g6IEx5bnhbJ2ZldGNoJ10pOiBhbnkge1xuICByZXR1cm4gY2xhc3MgRXZlbnRTb3VyY2Uge1xuICAgIHByaXZhdGUgdXJsOiBzdHJpbmc7XG4gICAgcHJpdmF0ZSBvcHRpb25zOiBGZXRjaEV2ZW50U291cmNlT3B0aW9ucztcbiAgICBwcml2YXRlIGxpc3RlbmVyczogUmVjb3JkPHN0cmluZywgRXZlbnRMaXN0ZW5lcltdPiA9IHt9O1xuICAgIHByaXZhdGUgX2Nsb3NlZDogYm9vbGVhbjtcbiAgICBvbm1lc3NhZ2U6IChldmVudDogRXZlbnRTb3VyY2VFdmVudCkgPT4gdm9pZDtcbiAgICBvbmVycm9yOiAoZXZlbnQ6IEV2ZW50KSA9PiB2b2lkO1xuICAgIG9ub3BlbjogKGV2ZW50OiBFdmVudCkgPT4gdm9pZDtcblxuICAgIGNvbnN0cnVjdG9yKHVybDogc3RyaW5nLCBvcHRpb25zOiBGZXRjaEV2ZW50U291cmNlT3B0aW9ucyA9IHt9KSB7XG4gICAgICB0aGlzLnVybCA9IHVybDtcbiAgICAgIHRoaXMub3B0aW9ucyA9IG9wdGlvbnM7XG4gICAgICB0aGlzLl9jbG9zZWQgPSBmYWxzZTtcbiAgICAgIHRoaXMuX2Nvbm5lY3QoKTtcbiAgICB9XG5cbiAgICBwdWJsaWMgY2xvc2UoKTogdm9pZCB7XG4gICAgICB0aGlzLl9jbG9zZWQgPSB0cnVlO1xuICAgIH1cblxuICAgIHByaXZhdGUgX2Rpc3BhdGNoRXZlbnQodHlwZTogc3RyaW5nLCBldmVudDogRXZlbnRTb3VyY2VFdmVudCk6IHZvaWQge1xuICAgICAgY29uc3QgZXZlbnRUb0Rpc3BhdGNoOiBFdmVudCA9IHtcbiAgICAgICAgdHlwZTogdHlwZSxcbiAgICAgICAgZGV0YWlsOiBldmVudCxcbiAgICAgICAgdGltZXN0YW1wOiBEYXRlLm5vdygpLFxuICAgICAgICB0YXJnZXQ6IHt9IGFzIFRhcmdldCxcbiAgICAgICAgY3VycmVudFRhcmdldDoge30gYXMgVGFyZ2V0LFxuICAgICAgICBwcmV2ZW50RGVmYXVsdDogKCkgPT4ge30sXG4gICAgICAgIHN0b3BQcm9wYWdhdGlvbjogKCkgPT4ge30sXG4gICAgICB9O1xuXG4gICAgICBpZiAodHlwZSA9PT0gJ21lc3NhZ2UnICYmIHRoaXMub25tZXNzYWdlKSB7XG4gICAgICAgIHRoaXMub25tZXNzYWdlKGV2ZW50KTtcbiAgICAgIH0gZWxzZSBpZiAodHlwZSA9PT0gJ2Vycm9yJyAmJiB0aGlzLm9uZXJyb3IpIHtcbiAgICAgICAgdGhpcy5vbmVycm9yKGV2ZW50VG9EaXNwYXRjaCk7XG4gICAgICB9IGVsc2UgaWYgKHR5cGUgPT09ICdvcGVuJyAmJiB0aGlzLm9ub3Blbikge1xuICAgICAgICB0aGlzLm9ub3BlbihldmVudFRvRGlzcGF0Y2gpO1xuICAgICAgfVxuICAgICAgY29uc3QgbGlzdGVuZXJzID0gdGhpcy5saXN0ZW5lcnNbdHlwZV0gfHwgW107XG4gICAgICBsaXN0ZW5lcnMuZm9yRWFjaCgobGlzdGVuZXIpID0+IGxpc3RlbmVyKGV2ZW50IGFzIGFueSkpO1xuICAgIH1cblxuICAgIHB1YmxpYyBhZGRFdmVudExpc3RlbmVyKHR5cGU6IHN0cmluZywgbGlzdGVuZXI6IEV2ZW50TGlzdGVuZXIpOiB2b2lkIHtcbiAgICAgIHRoaXMubGlzdGVuZXJzW3R5cGVdID0gdGhpcy5saXN0ZW5lcnNbdHlwZV0gfHwgW107XG4gICAgICB0aGlzLmxpc3RlbmVyc1t0eXBlXS5wdXNoKGxpc3RlbmVyKTtcbiAgICB9XG5cbiAgICBwdWJsaWMgcmVtb3ZlRXZlbnRMaXN0ZW5lcih0eXBlOiBzdHJpbmcsIGxpc3RlbmVyOiBFdmVudExpc3RlbmVyKTogdm9pZCB7XG4gICAgICB0aGlzLmxpc3RlbmVyc1t0eXBlXSA9IHRoaXMubGlzdGVuZXJzW3R5cGVdIHx8IFtdO1xuICAgICAgdGhpcy5saXN0ZW5lcnNbdHlwZV0gPSB0aGlzLmxpc3RlbmVyc1t0eXBlXS5maWx0ZXIoKGwpID0+IGwgIT09IGxpc3RlbmVyKTtcbiAgICB9XG5cbiAgICBwcml2YXRlIGFzeW5jIF9jb25uZWN0KCk6IFByb21pc2U8dm9pZD4ge1xuICAgICAgdHJ5IHtcbiAgICAgICAgY29uc3QgcmVzcG9uc2UgPSBhd2FpdCBmZXRjaCh0aGlzLnVybCwge1xuICAgICAgICAgIC4uLnRoaXMub3B0aW9ucyxcbiAgICAgICAgICBseW54RXh0ZW5zaW9uOiB7XG4gICAgICAgICAgICB1c2VTdHJlYW1pbmc6IHRydWUsXG4gICAgICAgICAgfSxcbiAgICAgICAgfSk7XG4gICAgICAgIHRoaXMuX2Rpc3BhdGNoRXZlbnQoJ29wZW4nLCB7IGRhdGE6ICcnIH0pO1xuICAgICAgICBjb25zdCByZWFkZXIgPSByZXNwb25zZS5ib2R5LmdldFJlYWRlcigpO1xuICAgICAgICB3aGlsZSAodHJ1ZSkge1xuICAgICAgICAgIGNvbnN0IHsgZG9uZSwgdmFsdWUgfSA9IGF3YWl0IHJlYWRlci5yZWFkKCk7XG4gICAgICAgICAgaWYgKGRvbmUpIGJyZWFrO1xuICAgICAgICAgIGNvbnN0IHJhd0V2ZW50ID0gZ2xvYmFsVGhpcy5UZXh0Q29kZWNIZWxwZXIuZGVjb2RlKHZhbHVlKTtcbiAgICAgICAgICBjb25zdCBldmVudCA9IHRoaXMuX3BhcnNlRXZlbnQocmF3RXZlbnQpO1xuICAgICAgICAgIGlmIChldmVudCkge1xuICAgICAgICAgICAgdGhpcy5fZGlzcGF0Y2hFdmVudChldmVudC5ldmVudCB8fCAnbWVzc2FnZScsIGV2ZW50KTtcbiAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgIH0gY2F0Y2ggKGVycjogYW55KSB7XG4gICAgICAgIHRoaXMuX2Rpc3BhdGNoRXZlbnQoJ2Vycm9yJywgeyBkYXRhOiAnJywgZXJyb3I6IGVyciB9KTtcbiAgICAgIH1cbiAgICB9XG5cbiAgICBwcml2YXRlIF9wYXJzZUV2ZW50KHJhdzogc3RyaW5nKTogRXZlbnRTb3VyY2VFdmVudCB8IG51bGwge1xuICAgICAgY29uc3QgbGluZXMgPSByYXcuc3BsaXQoJ1xcbicpO1xuICAgICAgbGV0IGV2ZW50OiBFdmVudFNvdXJjZUV2ZW50ID0geyBkYXRhOiAnJyB9O1xuICAgICAgZm9yIChjb25zdCBsaW5lIG9mIGxpbmVzKSB7XG4gICAgICAgIGlmIChsaW5lLnN0YXJ0c1dpdGgoJ2RhdGE6JykpIHtcbiAgICAgICAgICBldmVudC5kYXRhICs9IGxpbmUuc2xpY2UoNSkudHJpbSgpICsgJ1xcbic7XG4gICAgICAgIH0gZWxzZSBpZiAobGluZS5zdGFydHNXaXRoKCdldmVudDonKSkge1xuICAgICAgICAgIGV2ZW50LmV2ZW50ID0gbGluZS5zbGljZSg2KS50cmltKCk7XG4gICAgICAgIH0gZWxzZSBpZiAobGluZS5zdGFydHNXaXRoKCdpZDonKSkge1xuICAgICAgICAgIGV2ZW50LmlkID0gbGluZS5zbGljZSgzKS50cmltKCk7XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICAgIC8vIHJlbW92ZSBsYXN0IG5ld2xpbmVcbiAgICAgIGlmIChldmVudC5kYXRhKSBldmVudC5kYXRhID0gZXZlbnQuZGF0YS5zbGljZSgwLCAtMSk7XG4gICAgICByZXR1cm4gZXZlbnQuZGF0YSA/IGV2ZW50IDogbnVsbDtcbiAgICB9XG4gIH07XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IHtcbiAgTm9kZXNSZWYgYXMgSU5vZGVzUmVmLFxuICBNdWx0aU5vZGVzUmVmIGFzIElNdWx0aU5vZGVzUmVmLFxuICBTZWxlY3RvclF1ZXJ5IGFzIElTZWxlY3RvclF1ZXJ5LFxuICB1aUZpZWxkc09wdGlvbnMsXG4gIHVpTWV0aG9kT3B0aW9ucyxcbn0gZnJvbSAnQGx5bngtanMvdHlwZXMnO1xuaW1wb3J0IHtcbiAgRXJyb3JDb2RlLFxuICBJZGVudGlmaWVyVHlwZSxcbiAgTm9kZVNlbGVjdFRva2VuLFxuICBTZWxlY3RvclF1ZXJ5TmF0aXZlUHJveHksXG59IGZyb20gJy4vaW50ZXJmYWNlJztcbmltcG9ydCB7IEludm9rZUVycm9yLCByZXBvcnRFcnJvciB9IGZyb20gJy4uL3JlcG9ydCc7XG5pbXBvcnQgeyBBbmltYXRpb25PcGVyYXRpb24sIEFuaW1hdGlvblYyIH0gZnJvbSAnLi4vYW5pbWF0aW9uJztcblxuLyoqXG4gKiBTZWxlY3RvclF1ZXJ5IGlzIGEgcXVlcnkgb2JqZWN0IHRoYXQgY2FuIGJlIHVzZWQgdG8gc2VsZWN0IG5vZGVzIGluIHRoZSBWaXJ0dWFsIERPTSB0cmVlLlxuICpcbiAqIEV4YW1wbGU6XG4gKiB0aGlzLmNyZWF0ZVNlbGVjdG9yUXVlcnkoKVxuICogICAuc2VsZWN0KCcjdmlkZW8nKVxuICogICAuaW52b2tlKHtcbiAqICAgICBtZXRob2Q6ICdzZWVrVG8nLFxuICogICAgIHBhcmFtczoge1xuICogICAgICAgZHVyYXRpb246IDEwMDAsXG4gKiAgICAgfSxcbiAqICAgICBzdWNjZXNzOiBmdW5jdGlvbiAocmVzKSB7XG4gKiAgICAgICBjb25zb2xlLmxvZyhyZXMpO1xuICogICAgIH0sXG4gKiAgICAgZmFpbDogZnVuY3Rpb24gKHJlcykge1xuICogICAgICAgY29uc29sZS5sb2cocmVzLmNvZGUsIHJlcy5kYXRhKTtcbiAqICAgICB9LFxuICogICB9KVxuICogICAuZXhlYygpO1xuICovXG5leHBvcnQgZGVmYXVsdCBjbGFzcyBTZWxlY3RvclF1ZXJ5IGltcGxlbWVudHMgSVNlbGVjdG9yUXVlcnkge1xuICBwcml2YXRlIHJlYWRvbmx5IF9jb21wb25lbnQ6IHN0cmluZztcbiAgcHJpdmF0ZSByZWFkb25seSBfdGFza1F1ZXVlOiBGdW5jdGlvbltdO1xuICBwcml2YXRlIHJlYWRvbmx5IF9uYXRpdmVfcHJveHk6IFNlbGVjdG9yUXVlcnlOYXRpdmVQcm94eTtcbiAgcHJpdmF0ZSBfcm9vdF91bmlxdWVfaWQ/OiBudW1iZXI7XG5cbiAgLyoqXG4gICAqIE5vcm1hbGx5LCBhIHF1ZXJ5IGlzIGV4ZWN1dGVkIGFmdGVyIGNhbGxpbmcgZXhlYygpLlxuICAgKiBIb3dldmVyLCB3aGVuIGBfZmlyZV9pbW1lZGlhdGVseWAgaXMgc2V0IHRvIHRydWUsXG4gICAqIHRoZSBxdWVyeSB3aWxsIGJlIGV4ZWN1dGVkIGltbWVkaWF0ZWx5IGFmdGVyIHRhc2sgY29tbWl0dGVkICh3aGVuIGNhbGxpbmcgYGludm9rZSgpYCwgZXRjLilcbiAgICogd2l0aG91dCB0aGUgbmVlZCBvZiBjYWxsaW5nIGBleGVjKClgIGV4cGxpY2l0bHkuXG4gICAqXG4gICAqIFRoaXMgaXMgdXNlZCB3aGVuIFNlbGVjdG9yUXVlcnkgaXMgdXNlZCBhcyBSZWFjdFJlZi5cbiAgICovXG4gIHByaXZhdGUgX2ZpcmVfaW1tZWRpYXRlbHk6IGJvb2xlYW47XG5cbiAgcHJpdmF0ZSBjb25zdHJ1Y3RvcihcbiAgICBjb21wb25lbnQ6IHN0cmluZyxcbiAgICB0YXNrUXVldWU6IEZ1bmN0aW9uW10sXG4gICAgcHJveHk6IFNlbGVjdG9yUXVlcnlOYXRpdmVQcm94eVxuICApIHtcbiAgICB0aGlzLl9jb21wb25lbnQgPSBjb21wb25lbnQ7XG4gICAgdGhpcy5fdGFza1F1ZXVlID0gdGFza1F1ZXVlO1xuICAgIHRoaXMuX25hdGl2ZV9wcm94eSA9IHByb3h5O1xuICAgIHRoaXMuX2ZpcmVfaW1tZWRpYXRlbHkgPSBmYWxzZTtcbiAgICB0aGlzLl9yb290X3VuaXF1ZV9pZCA9IHVuZGVmaW5lZDtcbiAgfVxuXG4gIHN0YXRpYyBmcm9tUXVlcnkoXG4gICAgcHJldlF1ZXJ5OiBTZWxlY3RvclF1ZXJ5LFxuICAgIGNvbXBvbmVudD86IHN0cmluZ1xuICApOiBTZWxlY3RvclF1ZXJ5IHtcbiAgICByZXR1cm4gbmV3IFNlbGVjdG9yUXVlcnkoXG4gICAgICBjb21wb25lbnQgPz8gcHJldlF1ZXJ5Ll9jb21wb25lbnQsXG4gICAgICBwcmV2UXVlcnkuX3Rhc2tRdWV1ZS5zbGljZSgpLFxuICAgICAgcHJldlF1ZXJ5Ll9uYXRpdmVfcHJveHlcbiAgICApO1xuICB9XG5cbiAgc3RhdGljIG5ld0VtcHR5UXVlcnkoXG4gICAgcHJveHk6IFNlbGVjdG9yUXVlcnlOYXRpdmVQcm94eSxcbiAgICBjb21wb25lbnQ/OiBzdHJpbmdcbiAgKTogU2VsZWN0b3JRdWVyeSB7XG4gICAgcmV0dXJuIG5ldyBTZWxlY3RvclF1ZXJ5KGNvbXBvbmVudCA/PyAnJywgW10sIHByb3h5KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBBY2NvcmRpbmcgdG8gYHRoaXMuX2ZpcmVfaW1tZWRpYXRlbHlgLFxuICAgKiBlaXRoZXIgZXhlY3V0ZSB0aGUgcXVlcnkgaW1tZWRpYXRlbHkgb3IgYWRkIGl0IHRvIHRoZSB0YXNrIHF1ZXVlIG9mIHRoZSBTZWxlY3RvclF1ZXJ5LlxuICAgKiBJbiB0aGUgbGF0dGVyIGNhc2UsIGEgbmV3IHF1ZXJ5IGlzIHJldHVybmVkLCBhbmQgYHRoaXNgIGlzIG5vdCBtb2RpZmllZC5cbiAgICogQHBhcmFtIHRhc2sgdGhlIHRhc2sgdG8gY29tbWl0XG4gICAqL1xuICBjb21taXRUYXNrKHRhc2s6IEZ1bmN0aW9uKTogSVNlbGVjdG9yUXVlcnkge1xuICAgIGxldCBuZXdfcXVlcnkgPSBTZWxlY3RvclF1ZXJ5LmZyb21RdWVyeSh0aGlzLCB0aGlzLl9jb21wb25lbnQpO1xuICAgIG5ld19xdWVyeS5fdGFza1F1ZXVlLnB1c2godGFzayk7XG5cbiAgICBpZiAodGhpcy5fZmlyZV9pbW1lZGlhdGVseSkge1xuICAgICAgbmV3X3F1ZXJ5LmV4ZWMoKTtcbiAgICAgIHJldHVybiB1bmRlZmluZWQ7XG4gICAgfVxuICAgIHJldHVybiBuZXdfcXVlcnk7XG4gIH1cblxuICBpbihjb21wb25lbnQ6IHsgY3JlYXRlU2VsZWN0b3JRdWVyeTogRnVuY3Rpb24gfSk6IElTZWxlY3RvclF1ZXJ5IHtcbiAgICByZXR1cm4gY29tcG9uZW50LmNyZWF0ZVNlbGVjdG9yUXVlcnkodGhpcyk7XG4gIH1cblxuICAvKipcbiAgICogU2VsZWN0cyBhIHNpbmdsZSBub2RlIGJ5IENTUyBzZWxlY3Rvci5cbiAgICogQHBhcmFtIHNlbGVjdG9yIENTUyBzZWxlY3RvclxuICAgKi9cbiAgc2VsZWN0KHNlbGVjdG9yOiBzdHJpbmcpOiBJTm9kZXNSZWYge1xuICAgIHJldHVybiBuZXcgTm9kZXNSZWYodGhpcywge1xuICAgICAgdHlwZTogSWRlbnRpZmllclR5cGUuSURfU0VMRUNUT1IsXG4gICAgICBpZGVudGlmaWVyOiBzZWxlY3RvcixcbiAgICAgIGNvbXBvbmVudF9pZDogdGhpcy5fY29tcG9uZW50LFxuICAgICAgcm9vdF91bmlxdWVfaWQ6IHRoaXMuX3Jvb3RfdW5pcXVlX2lkLFxuICAgICAgZmlyc3Rfb25seTogdHJ1ZSxcbiAgICB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBTZWxlY3RzIGFsbCBub2RlcyBzYXRpc2Z5aW5nIENTUyBzZWxlY3Rvci5cbiAgICogQHBhcmFtIHNlbGVjdG9yIENTUyBzZWxlY3RvclxuICAgKi9cbiAgc2VsZWN0QWxsKHNlbGVjdG9yOiBzdHJpbmcpOiBJTXVsdGlOb2Rlc1JlZiB7XG4gICAgcmV0dXJuIG5ldyBOb2Rlc1JlZih0aGlzLCB7XG4gICAgICB0eXBlOiBJZGVudGlmaWVyVHlwZS5JRF9TRUxFQ1RPUixcbiAgICAgIGlkZW50aWZpZXI6IHNlbGVjdG9yLFxuICAgICAgY29tcG9uZW50X2lkOiB0aGlzLl9jb21wb25lbnQsXG4gICAgICByb290X3VuaXF1ZV9pZDogdGhpcy5fcm9vdF91bmlxdWVfaWQsXG4gICAgICBmaXJzdF9vbmx5OiBmYWxzZSxcbiAgICB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBTZWxlY3RzIGEgc2luZ2xlIG5vZGUgYXMgUmVhY3QgcmVmLlxuICAgKiBXaGVuIHdvcmtzIGFzIFJlYWN0UmVmLCBTZWxlY3RvclF1ZXJ5IHNob3VsZCBhY3QgbGlrZSBnZXROb2RlUmVmLCB3aGljaCBtZWFuczpcbiAgICogMS4gY2FzY2FkZSBxdWVyeSBpcyBkaXNhYmxlZC5cbiAgICogMi4gdGFza3MgYXJlIGV4ZWN1dGVkIGltbWVkaWF0ZWx5IHdpdGhvdXQgY2FsbGluZyBleGVjKCkuXG4gICAqL1xuICBzZWxlY3RSZWFjdFJlZihyZWZfc3RyaW5nOiBzdHJpbmcpOiBJTm9kZXNSZWYge1xuICAgIGlmICh0aGlzLl90YXNrUXVldWUubGVuZ3RoKSB7XG4gICAgICBjb25zdCBlcnJvck1lc3NhZ2UgPVxuICAgICAgICAnc2VsZWN0UmVhY3RSZWYoKSBzaG91bGQgYmUgY2FsbGVkIGJlZm9yZSBhbnkgb3RoZXIgc2VsZWN0b3IgcXVlcnkgbWV0aG9kcyc7XG4gICAgICBuYXRpdmVDb25zb2xlLndhcm4oZXJyb3JNZXNzYWdlKTtcbiAgICAgIGNvbnN0IGVycm9yID0gbmV3IEVycm9yKGVycm9yTWVzc2FnZSk7XG4gICAgICByZXBvcnRFcnJvcihcbiAgICAgICAgbmV3IEludm9rZUVycm9yKGVycm9yTWVzc2FnZSwgZXJyb3Iuc3RhY2spLFxuICAgICAgICB0aGlzLl9uYXRpdmVfcHJveHkubmF0aXZlQXBwXG4gICAgICApO1xuICAgICAgcmV0dXJuO1xuICAgIH1cblxuICAgIHRoaXMuX2ZpcmVfaW1tZWRpYXRlbHkgPSB0cnVlO1xuICAgIHJldHVybiBuZXcgTm9kZXNSZWYodGhpcywge1xuICAgICAgdHlwZTogSWRlbnRpZmllclR5cGUuUkVGX0lELFxuICAgICAgaWRlbnRpZmllcjogcmVmX3N0cmluZyxcbiAgICAgIGNvbXBvbmVudF9pZDogdGhpcy5fY29tcG9uZW50LFxuICAgICAgcm9vdF91bmlxdWVfaWQ6IHRoaXMuX3Jvb3RfdW5pcXVlX2lkLFxuICAgICAgZmlyc3Rfb25seTogdHJ1ZSxcbiAgICB9KTtcbiAgfVxuXG4gIC8qKlxuICAgKiBTZWxlY3Qgcm9vdCBub2RlIG9mIHRoZSBjb21wb25lbnQuXG4gICAqL1xuICBzZWxlY3RSb290KCk6IElOb2Rlc1JlZiB7XG4gICAgcmV0dXJuIHRoaXMuc2VsZWN0KCcnKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBTZWxlY3RzIGEgc2luZ2xlIG5vZGUgYnkgZWxlbWVudCBpZC5cbiAgICogV2hlbiBhIHRvdWNoIGV2ZW50IGlzIHRyaWdnZXJlZCwgdGhlIGVsZW1lbnQgaWQgb2YgdGhlIG5vZGUgaXMgcGFzc2VkIHRvIHRoZSBldmVudCBoYW5kbGVyIGFzICd1aWQnLFxuICAgKiBieSB3aGljaCBjYW4gYSBub2RlIGJlIHNlbGVjdGVkIGluIGl0cyBldmVudCBoYW5kbGVyLlxuICAgKi9cbiAgc2VsZWN0VW5pcXVlSUQodW5pcXVlSWQ6IHN0cmluZyB8IG51bWJlcik6IElOb2Rlc1JlZiB7XG4gICAgcmV0dXJuIG5ldyBOb2Rlc1JlZih0aGlzLCB7XG4gICAgICB0eXBlOiBJZGVudGlmaWVyVHlwZS5VTklRVUVfSUQsXG4gICAgICBpZGVudGlmaWVyOiB1bmlxdWVJZC50b1N0cmluZygpLFxuICAgICAgY29tcG9uZW50X2lkOiB0aGlzLl9jb21wb25lbnQsXG4gICAgICByb290X3VuaXF1ZV9pZDogdGhpcy5fcm9vdF91bmlxdWVfaWQsXG4gICAgICBmaXJzdF9vbmx5OiB0cnVlLFxuICAgIH0pO1xuICB9XG5cbiAgLyoqXG4gICAqIEV4ZWN1dGUgYWxsIHRhc2tzIGluIHRoZSB0YXNrIHF1ZXVlLlxuICAgKiBXaGVuIGB0aGlzLl9maXJlX2ltbWVkaWF0ZWx5YCBpcyBzZXQgdG8gdHJ1ZSwgdGhpcyBtZXRob2QgaXMgY2FsbGVkIGF1dG9tYXRpY2FsbHkuXG4gICAqL1xuICBleGVjKCk6IHZvaWQge1xuICAgIGZvciAobGV0IGkgPSAwOyBpIDwgdGhpcy5fdGFza1F1ZXVlLmxlbmd0aDsgKytpKSB7XG4gICAgICB0aGlzLl90YXNrUXVldWVbaV0odGhpcy5fbmF0aXZlX3Byb3h5KTtcbiAgICB9XG4gIH1cblxuICBzZXRSb290KHVuaXF1ZUlkOiBzdHJpbmcgfCBudW1iZXIpOiBTZWxlY3RvclF1ZXJ5IHtcbiAgICB0aGlzLl9yb290X3VuaXF1ZV9pZCA9IE51bWJlcih1bmlxdWVJZCk7XG4gICAgcmV0dXJuIHRoaXM7XG4gIH1cbn1cblxuZXhwb3J0IGNsYXNzIE5vZGVzUmVmIGltcGxlbWVudHMgSU5vZGVzUmVmIHtcbiAgcHJpdmF0ZSBzdGF0aWMgbm9kZVBvb2wgPSB7fTtcblxuICBwcml2YXRlIHJlYWRvbmx5IF9ub2RlU2VsZWN0VG9rZW46IE5vZGVTZWxlY3RUb2tlbjtcbiAgcHJpdmF0ZSByZWFkb25seSBfc2VsZWN0b3JRdWVyeTogU2VsZWN0b3JRdWVyeTtcblxuICBjb25zdHJ1Y3RvcihzZWxlY3RvclF1ZXJ5OiBTZWxlY3RvclF1ZXJ5LCBub2RlU2VsZWN0VG9rZW46IE5vZGVTZWxlY3RUb2tlbikge1xuICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbiA9IG5vZGVTZWxlY3RUb2tlbjtcbiAgICB0aGlzLl9zZWxlY3RvclF1ZXJ5ID0gc2VsZWN0b3JRdWVyeTtcbiAgfVxuICBpbnZva2Uob3B0aW9uczogdWlNZXRob2RPcHRpb25zKTogSVNlbGVjdG9yUXVlcnkge1xuICAgIGxldCBlcnJvclN0YWNrO1xuICAgIGlmIChOT0RFX0VOViA9PT0gJ2RldmVsb3BtZW50JyB8fCBOT0RFX0VOViA9PT0gJ3Rlc3QnKSB7XG4gICAgICBlcnJvclN0YWNrID0gbmV3IEVycm9yKCcnKTtcbiAgICB9XG5cbiAgICBsZXQgdGFzayA9IChwcm94eTogU2VsZWN0b3JRdWVyeU5hdGl2ZVByb3h5KSA9PiB7XG4gICAgICBsZXQgY2FsbGJhY2sgPSAocmVzKSA9PiB7XG4gICAgICAgIGlmIChyZXMuY29kZSA9PT0gRXJyb3JDb2RlLlNVQ0NFU1MpIHtcbiAgICAgICAgICBvcHRpb25zLnN1Y2Nlc3MgJiYgb3B0aW9ucy5zdWNjZXNzKHJlcy5kYXRhKTtcbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICBpZiAob3B0aW9ucy5mYWlsKSB7XG4gICAgICAgICAgICBvcHRpb25zLmZhaWwocmVzKTtcbiAgICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgICAgLy8gZW5hYmxlIHdhcm5pbmcgaW4gZGV2ZWxvcG1lbnQgYW5kIHRlc3RcbiAgICAgICAgICAgIGlmIChOT0RFX0VOViA9PT0gJ2RldmVsb3BtZW50JyB8fCBOT0RFX0VOViA9PT0gJ3Rlc3QnKSB7XG4gICAgICAgICAgICAgIGlmICghcHJveHkubHlueC5fc3dpdGNoZXMuZGlzYWJsZVNlbGVjdG9yUXVlcnlXYXJuaW5nV2hlbkZhaWxlZCkge1xuICAgICAgICAgICAgICAgIGNvbnN0IGVycm9yTWVzc2FnZSA9IGBGYWlsZWQgdG8gZXhlYyBjcmVhdGVTZWxlY3RvclF1ZXJ5KCkuaW52b2tlKCkgb24gTm9kZXNSZWYgJHtKU09OLnN0cmluZ2lmeShcbiAgICAgICAgICAgICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlblxuICAgICAgICAgICAgICAgICl9LiBBZGQgYSBmYWlsIGNhbGxiYWNrIHRvIHN1cHByZXNzIHRoaXMgd2FybmluZy4gTXNnOiAke0pTT04uc3RyaW5naWZ5KFxuICAgICAgICAgICAgICAgICAgcmVzXG4gICAgICAgICAgICAgICAgKX1gO1xuICAgICAgICAgICAgICAgIG5hdGl2ZUNvbnNvbGUud2FybihlcnJvck1lc3NhZ2UpO1xuICAgICAgICAgICAgICAgIHJlcG9ydEVycm9yKFxuICAgICAgICAgICAgICAgICAgbmV3IEludm9rZUVycm9yKGVycm9yTWVzc2FnZSwgZXJyb3JTdGFjay5zdGFjayksXG4gICAgICAgICAgICAgICAgICBwcm94eS5uYXRpdmVBcHBcbiAgICAgICAgICAgICAgICApO1xuICAgICAgICAgICAgICB9XG4gICAgICAgICAgICB9XG4gICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICB9O1xuICAgICAgaWYgKCF0aGlzLl9ub2RlU2VsZWN0VG9rZW4uZmlyc3Rfb25seSkge1xuICAgICAgICBjYWxsYmFjayh7XG4gICAgICAgICAgY29kZTogRXJyb3JDb2RlLlNFTEVDVE9SX05PVF9TVVBQT1JURUQsXG4gICAgICAgICAgZGF0YTogJ3NlbGVjdEFsbCBub3Qgc3VwcG9ydGVkIGZvciBpbnZva2UgbWV0aG9kJyxcbiAgICAgICAgfSk7XG4gICAgICAgIHJldHVybjtcbiAgICAgIH1cbiAgICAgIHByb3h5Lm5hdGl2ZUFwcC5pbnZva2VVSU1ldGhvZChcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLnR5cGUsXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5pZGVudGlmaWVyLFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uY29tcG9uZW50X2lkLFxuICAgICAgICBvcHRpb25zLm1ldGhvZCxcbiAgICAgICAgb3B0aW9ucy5wYXJhbXMgPz8ge30sXG4gICAgICAgIGNhbGxiYWNrLFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4ucm9vdF91bmlxdWVfaWRcbiAgICAgICk7XG4gICAgfTtcbiAgICByZXR1cm4gdGhpcy5fc2VsZWN0b3JRdWVyeS5jb21taXRUYXNrKHRhc2spO1xuICB9XG5cbiAgcGF0aChjYjogRnVuY3Rpb24pIHtcbiAgICBsZXQgdGFzayA9IChwcm94eTogU2VsZWN0b3JRdWVyeU5hdGl2ZVByb3h5KSA9PiB7XG4gICAgICBsZXQgY2FsbGJhY2sgPSAocmVzKSA9PiB7XG4gICAgICAgIGNiICYmIGNiKHJlcy5kYXRhLCByZXMuc3RhdHVzKTtcbiAgICAgIH07XG4gICAgICBwcm94eS5uYXRpdmVBcHAuZ2V0UGF0aEluZm8oXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi50eXBlLFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uaWRlbnRpZmllcixcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLmNvbXBvbmVudF9pZCxcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLmZpcnN0X29ubHksXG4gICAgICAgIGNhbGxiYWNrLFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4ucm9vdF91bmlxdWVfaWRcbiAgICAgICk7XG4gICAgfTtcbiAgICByZXR1cm4gdGhpcy5fc2VsZWN0b3JRdWVyeS5jb21taXRUYXNrKHRhc2spO1xuICB9XG5cbiAgZmllbGRzKGZpZWxkczogdWlGaWVsZHNPcHRpb25zLCBjYjogRnVuY3Rpb24pIHtcbiAgICBsZXQgdGFzayA9IChwcm94eTogU2VsZWN0b3JRdWVyeU5hdGl2ZVByb3h5KSA9PiB7XG4gICAgICBsZXQgY2FsbGJhY2sgPSAocmVzOiB7IGRhdGE6IGFueTsgc3RhdHVzOiBhbnkgfSkgPT4ge1xuICAgICAgICAvLyB3aGVuICdxdWVyeScgaXMgcGFzc2VkLCAndW5pcXVlX2lkJyBpcyBhY3R1YWxseSByZXR1cm5lZC5cbiAgICAgICAgLy8gc2hvdWxkIGNyZWF0ZSBTZWxlY3RvclF1ZXJ5IHVzaW5nICd1bmlxdWVfaWQnIGFzIHJvb3QgaGVyZS5cbiAgICAgICAgaWYgKGZpZWxkcy5xdWVyeSkge1xuICAgICAgICAgIGNvbnN0IGFkZFF1ZXJ5T2JqZWN0ID0gKHJlc3VsdCkgPT4ge1xuICAgICAgICAgICAgcmVzdWx0LnF1ZXJ5ID0gU2VsZWN0b3JRdWVyeS5uZXdFbXB0eVF1ZXJ5KHByb3h5KTtcbiAgICAgICAgICAgIHJlc3VsdC5xdWVyeS5zZXRSb290KHJlc3VsdC51bmlxdWVfaWQudG9TdHJpbmcoKSk7XG4gICAgICAgICAgICBpZiAoIWZpZWxkcy51bmlxdWVfaWQpIHtcbiAgICAgICAgICAgICAgZGVsZXRlIHJlc3VsdC51bmlxdWVfaWQ7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgfTtcbiAgICAgICAgICBpZiAodGhpcy5fbm9kZVNlbGVjdFRva2VuLmZpcnN0X29ubHkpIHtcbiAgICAgICAgICAgIGxldCByZXN1bHQgPSByZXMuZGF0YTtcbiAgICAgICAgICAgIGlmIChyZXN1bHQpIHtcbiAgICAgICAgICAgICAgYWRkUXVlcnlPYmplY3QocmVzdWx0KTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgICAgZm9yIChsZXQgcmVzdWx0IG9mIHJlcy5kYXRhKSB7XG4gICAgICAgICAgICAgIGFkZFF1ZXJ5T2JqZWN0KHJlc3VsdCk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIGNiICYmIGNiKHJlcy5kYXRhLCByZXMuc3RhdHVzKTtcbiAgICAgIH07XG4gICAgICBsZXQgZmllbGRzX2FycmF5OiBzdHJpbmdbXSA9IFtdO1xuICAgICAgZm9yIChsZXQga2V5IGluIGZpZWxkcykge1xuICAgICAgICAvLyBmaWx0ZXIgJ3F1ZXJ5Jy4gdXNlICd1bmlxdWVfaWQnIGluc3RlYWQuXG4gICAgICAgIGlmIChrZXkgPT0gJ3F1ZXJ5JyAmJiBmaWVsZHNba2V5XSA9PSB0cnVlICYmICFmaWVsZHMudW5pcXVlX2lkKSB7XG4gICAgICAgICAgZmllbGRzX2FycmF5LnB1c2goJ3VuaXF1ZV9pZCcpO1xuICAgICAgICAgIGNvbnRpbnVlO1xuICAgICAgICB9XG4gICAgICAgIGlmIChmaWVsZHNba2V5XSkge1xuICAgICAgICAgIGZpZWxkc19hcnJheS5wdXNoKGtleSk7XG4gICAgICAgIH1cbiAgICAgIH1cbiAgICAgIHByb3h5Lm5hdGl2ZUFwcC5nZXRGaWVsZHMoXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi50eXBlLFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4uaWRlbnRpZmllcixcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLmNvbXBvbmVudF9pZCxcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLmZpcnN0X29ubHksXG4gICAgICAgIGZpZWxkc19hcnJheSxcbiAgICAgICAgY2FsbGJhY2ssXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5yb290X3VuaXF1ZV9pZFxuICAgICAgKTtcbiAgICB9O1xuICAgIHJldHVybiB0aGlzLl9zZWxlY3RvclF1ZXJ5LmNvbW1pdFRhc2sodGFzayk7XG4gIH1cblxuICBhbmltYXRlKGFuaW1hdGlvbnM6IEFuaW1hdGlvblYyW10gfCBBbmltYXRpb25WMik6IElTZWxlY3RvclF1ZXJ5IHtcbiAgICBsZXQgYW5pbWF0aW9uc0FycmF5ID0gW107XG4gICAgaWYgKEFycmF5LmlzQXJyYXkoYW5pbWF0aW9ucykpIHtcbiAgICAgIGFuaW1hdGlvbnNBcnJheSA9IGFuaW1hdGlvbnM7XG4gICAgfSBlbHNlIHtcbiAgICAgIGFuaW1hdGlvbnNBcnJheS5wdXNoKGFuaW1hdGlvbnMpO1xuICAgIH1cbiAgICBsZXQgdGFzayA9IChwcm94eTogU2VsZWN0b3JRdWVyeU5hdGl2ZVByb3h5KSA9PiB7XG4gICAgICBhbmltYXRpb25zQXJyYXkuZm9yRWFjaCgoYW5pbWF0aW9uKSA9PiB7XG4gICAgICAgIHByb3h5Lm5hdGl2ZUFwcC5hbmltYXRlKFxuICAgICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi50eXBlLFxuICAgICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5pZGVudGlmaWVyLFxuICAgICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5jb21wb25lbnRfaWQsXG4gICAgICAgICAgQW5pbWF0aW9uT3BlcmF0aW9uLlNUQVJULFxuICAgICAgICAgIGFuaW1hdGlvbj8uaWQsXG4gICAgICAgICAgYW5pbWF0aW9uPy5lZmZlY3Q/LmtleWZyYW1lcyxcbiAgICAgICAgICBhbmltYXRpb24/LmVmZmVjdD8ub3B0aW9uc1xuICAgICAgICApO1xuICAgICAgfSk7XG4gICAgfTtcbiAgICByZXR1cm4gdGhpcy5fc2VsZWN0b3JRdWVyeS5jb21taXRUYXNrKHRhc2spO1xuICB9XG5cbiAgYW5pbWF0aW9uT3BlcmF0ZShcbiAgICBvcGVyYXRpb246IEFuaW1hdGlvbk9wZXJhdGlvbixcbiAgICBpZHM6IHN0cmluZ1tdIHwgc3RyaW5nXG4gICk6IElTZWxlY3RvclF1ZXJ5IHtcbiAgICBsZXQgaWRBcnJheSA9IFtdO1xuICAgIGlmIChBcnJheS5pc0FycmF5KGlkcykpIHtcbiAgICAgIGlkQXJyYXkgPSBpZHM7XG4gICAgfSBlbHNlIHtcbiAgICAgIGlkQXJyYXkucHVzaChpZHMpO1xuICAgIH1cbiAgICBsZXQgdGFzayA9IChwcm94eTogU2VsZWN0b3JRdWVyeU5hdGl2ZVByb3h5KSA9PiB7XG4gICAgICBpZEFycmF5LmZvckVhY2goKGlkKSA9PiB7XG4gICAgICAgIHByb3h5Lm5hdGl2ZUFwcC5hbmltYXRlKFxuICAgICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi50eXBlLFxuICAgICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5pZGVudGlmaWVyLFxuICAgICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5jb21wb25lbnRfaWQsXG4gICAgICAgICAgb3BlcmF0aW9uLFxuICAgICAgICAgIGlkLFxuICAgICAgICAgIG51bGwsXG4gICAgICAgICAgbnVsbFxuICAgICAgICApO1xuICAgICAgfSk7XG4gICAgfTtcbiAgICByZXR1cm4gdGhpcy5fc2VsZWN0b3JRdWVyeS5jb21taXRUYXNrKHRhc2spO1xuICB9XG5cbiAgcGxheUFuaW1hdGlvbihpZHM6IHN0cmluZ1tdIHwgc3RyaW5nKTogSVNlbGVjdG9yUXVlcnkge1xuICAgIHJldHVybiB0aGlzLmFuaW1hdGlvbk9wZXJhdGUoQW5pbWF0aW9uT3BlcmF0aW9uLlBMQVksIGlkcyk7XG4gIH1cblxuICBwYXVzZUFuaW1hdGlvbihpZHM6IHN0cmluZ1tdKTogSVNlbGVjdG9yUXVlcnkge1xuICAgIHJldHVybiB0aGlzLmFuaW1hdGlvbk9wZXJhdGUoQW5pbWF0aW9uT3BlcmF0aW9uLlBBVVNFLCBpZHMpO1xuICB9XG5cbiAgY2FuY2VsQW5pbWF0aW9uKGlkczogc3RyaW5nW10pOiBJU2VsZWN0b3JRdWVyeSB7XG4gICAgcmV0dXJuIHRoaXMuYW5pbWF0aW9uT3BlcmF0ZShBbmltYXRpb25PcGVyYXRpb24uQ0FOQ0VMLCBpZHMpO1xuICB9XG5cbiAgZmluaXNoQW5pbWF0aW9uKGlkczogc3RyaW5nW10pOiBJU2VsZWN0b3JRdWVyeSB7XG4gICAgcmV0dXJuIHRoaXMuYW5pbWF0aW9uT3BlcmF0ZShBbmltYXRpb25PcGVyYXRpb24uRklOSVNILCBpZHMpO1xuICB9XG5cbiAgc2V0TmF0aXZlUHJvcHMobmF0aXZlUHJvcHM6IFJlY29yZDxzdHJpbmcsIHVua25vd24+KSB7XG4gICAgbGV0IHRhc2sgPSAocHJveHk6IFNlbGVjdG9yUXVlcnlOYXRpdmVQcm94eSkgPT4ge1xuICAgICAgcHJveHkubmF0aXZlQXBwLnNldE5hdGl2ZVByb3BzKFxuICAgICAgICB0aGlzLl9ub2RlU2VsZWN0VG9rZW4udHlwZSxcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLmlkZW50aWZpZXIsXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5jb21wb25lbnRfaWQsXG4gICAgICAgIHRoaXMuX25vZGVTZWxlY3RUb2tlbi5maXJzdF9vbmx5LFxuICAgICAgICBuYXRpdmVQcm9wcyxcbiAgICAgICAgdGhpcy5fbm9kZVNlbGVjdFRva2VuLnJvb3RfdW5pcXVlX2lkXG4gICAgICApO1xuICAgIH07XG4gICAgcmV0dXJuIHRoaXMuX3NlbGVjdG9yUXVlcnkuY29tbWl0VGFzayh0YXNrKTtcbiAgfVxufVxuIiwgImltcG9ydCB7XG4gIGlzRXJyb3IsXG4gIGlzRnVuY3Rpb24sXG4gIGlzT2JqZWN0LFxuICBpc1N0cmluZyxcbn0gZnJvbSAnQGx5bngtanMvcnVudGltZS1zaGFyZWQnO1xuaW1wb3J0IHtcbiAgQ3JlYXRlSW50ZXJzZWN0aW9uT2JzZXJ2ZXJGdW5jLFxuICBHbG9iYWxQcm9wcyxcbiAgTG9hZER5bmFtaWNDb21wb25lbnRGYWlsZWRSZXN1bHQsXG4gIExvYWREeW5hbWljQ29tcG9uZW50RnVuYyxcbiAgTG9hZER5bmFtaWNDb21wb25lbnRTdWNjZXNzUmVzdWx0LFxuICBMeW54U2V0VGltZW91dCxcbiAgTWVzc2FnZUV2ZW50LFxufSBmcm9tICdAbHlueC1qcy90eXBlcyc7XG5pbXBvcnQge1xuICBSZXF1aXJlTW9kdWxlLFxuICBSZXF1aXJlTW9kdWxlQXN5bmMsXG4gIE5hdGl2ZUx5bnhQcm94eSxcbiAgTWVzc2FnZUV2ZW50VHlwZSxcbiAgTG9hZFNjcmlwdCxcbn0gZnJvbSAnLi9pbnRlcmZhY2UnO1xuaW1wb3J0IHsgQmFzZUFwcCwgTmF0aXZlQXBwIH0gZnJvbSAnLi4vYXBwJztcbmltcG9ydCB7IFRleHRJbmZvLCBUZXh0TWV0cmljcyB9IGZyb20gJy4uL21vZHVsZXMvbmF0aXZlTW9kdWxlcyc7XG5pbXBvcnQgbmF0aXZlR2xvYmFsIGZyb20gJy4uL2NvbW1vbi9uYXRpdmVHbG9iYWwnO1xuaW1wb3J0IEVsZW1lbnQgZnJvbSAnLi4vbW9kdWxlcy9lbGVtZW50JztcbmltcG9ydCB7IEx5bnhFcnJvckxldmVsIH0gZnJvbSAnLi4vbW9kdWxlcy9yZXBvcnQnO1xuaW1wb3J0IHsgY3JlYXRlRXZlbnRTb3VyY2UgfSBmcm9tICcuLi9tb2R1bGVzL2ZldGNoJztcbmltcG9ydCBQZXJmb3JtYW5jZSBmcm9tICcuLi9tb2R1bGVzL3BlcmZvcm1hbmNlJztcbmltcG9ydCBTZWxlY3RvclF1ZXJ5IGZyb20gJy4uL21vZHVsZXMvc2VsZWN0b3JRdWVyeS9TZWxlY3RvclF1ZXJ5JztcbmltcG9ydCB7IEFuaW1hdGlvblYyIH0gZnJvbSAnLi4vbW9kdWxlcy9hbmltYXRpb24vYW5pbWF0aW9uVjInO1xuaW1wb3J0IHsgREVGQVVMVF9FTlRSWSB9IGZyb20gJy4uL2NvbW1vbi9jb25zdGFudHMnO1xuXG5pbnRlcmZhY2UgTHlueE1vZHVsZUxvYWRlciB7XG4gIGxvYWQobW9kdWxlTmFtZTogc3RyaW5nKTogYW55O1xufVxuXG5leHBvcnQgY2xhc3MgTHlueCB7XG4gIHN0YXRpYyBfX3JlZ2lzdGVyU2hhcmVkRGF0YUNvdW50ZXI6IG51bWJlciA9IDA7XG4gIF9fZ2xvYmFsUHJvcHM6IEdsb2JhbFByb3BzO1xuICBfX3ByZXNldERhdGE6IFJlY29yZDxzdHJpbmcsIHVua25vd24+O1xuICBfc3dpdGNoZXM6IFJlY29yZDxzdHJpbmcsIGJvb2xlYW4+O1xuICB0YXJnZXRTZGtWZXJzaW9uPzogc3RyaW5nO1xuXG4gIGNvbnN0cnVjdG9yKFxuICAgIC8vIHNob3VsZCB1c2UgZnVuY3Rpb24gdG8gZ2V0IG5hdGl2ZSBhcHAgdG8gYXZvaWQgY3ljbGVcbiAgICBwdWJsaWMgZ2V0TmF0aXZlQXBwOiAoKSA9PiBOYXRpdmVBcHAsXG4gICAgcHVibGljIGdldEFwcDogKCkgPT4gQmFzZUFwcCxcbiAgICBwdWJsaWMgUHJvbWlzZTogUHJvbWlzZUNvbnN0cnVjdG9yLFxuICAgIHB1YmxpYyBnZXROYXRpdmVMeW54OiAoKSA9PiBOYXRpdmVMeW54UHJveHlcbiAgKSB7XG4gICAgdGhpcy5pbml0KHVuZGVmaW5lZCk7XG4gIH1cblxuICBzZXRUaW1lb3V0OiBMeW54U2V0VGltZW91dCA9IHRoaXMuZ2V0QXBwKCkud3JhcFJlcG9ydChcbiAgICB0aGlzLmdldE5hdGl2ZUFwcCgpLnNldFRpbWVvdXQsXG4gICAgJ3NldFRpbWVvdXQgRXJyb3InXG4gICk7XG5cbiAgcHVibGljIHJlYmluZChnZXRBcHA6ICgpID0+IEJhc2VBcHApIHtcbiAgICB0aGlzLmluaXQoZ2V0QXBwKTtcbiAgfVxuXG4gIHByaXZhdGUgaW5pdChnZXRBcHA/OiAoKSA9PiBCYXNlQXBwKSB7XG4gICAgaWYgKGdldEFwcCkge1xuICAgICAgdGhpcy5nZXRBcHAgPSBnZXRBcHA7XG4gICAgICAvLyBUT0RPKGxpeWFuYm8pOiBtZXJnZSBvciByZXBsYWNlPyBub3cgaXMgcmVwbGFjZS5cbiAgICAgIHRoaXMuX19nbG9iYWxQcm9wcyA9IHRoaXMuZ2V0TmF0aXZlTHlueCgpLl9fZ2xvYmFsUHJvcHMgfHwge307XG4gICAgICB0aGlzLl9fcHJlc2V0RGF0YSA9IHRoaXMuZ2V0TmF0aXZlTHlueCgpLl9fcHJlc2V0RGF0YSB8fCB7fTtcbiAgICB9IGVsc2Uge1xuICAgICAgY29uc3QgY2FjaGUgPSB7fTtcbiAgICAgIHRoaXMucmVxdWlyZU1vZHVsZS5jYWNoZSA9IGNhY2hlO1xuICAgICAgdGhpcy5yZXF1aXJlTW9kdWxlQXN5bmMuY2FjaGUgPSBjYWNoZTtcbiAgICAgIHRoaXMubG9hZFNjcmlwdC5jYWNoZSA9IHt9O1xuICAgICAgdGhpcy5fX2dsb2JhbFByb3BzID0gdGhpcy5nZXROYXRpdmVMeW54KCkuX19nbG9iYWxQcm9wcyB8fCB7fTtcbiAgICAgIHRoaXMuX19wcmVzZXREYXRhID0gdGhpcy5nZXROYXRpdmVMeW54KCkuX19wcmVzZXREYXRhIHx8IHt9O1xuICAgICAgdGhpcy5fc3dpdGNoZXMgPSB7fTtcbiAgICB9XG4gIH1cblxuICBzZXRJbnRlcnZhbDogTHlueFNldFRpbWVvdXQgPSB0aGlzLmdldEFwcCgpLndyYXBSZXBvcnQoXG4gICAgdGhpcy5nZXROYXRpdmVBcHAoKS5zZXRJbnRlcnZhbCxcbiAgICAnc2V0SW50ZXJ2YWwgRXJyb3InXG4gICk7XG4gIGNsZWFySW50ZXJ2YWwgPSB0aGlzLmdldE5hdGl2ZUFwcCgpLmNsZWFySW50ZXJ2YWw7XG4gIGNsZWFyVGltZW91dCA9IHRoaXMuZ2V0TmF0aXZlQXBwKCkuY2xlYXJUaW1lb3V0O1xuXG4gIHJlc3VtZUV4cG9zdXJlID0gdGhpcy5nZXRBcHAoKS5fYXBpTGlzdFsncmVzdW1lRXhwb3N1cmUnXSBhcyAoKSA9PiB2b2lkO1xuXG4gIHJlcXVpcmVNb2R1bGUgPSA8UmVxdWlyZU1vZHVsZT4oPFQ+KFxuICAgIHBhdGg6IHN0cmluZyxcbiAgICBlbnRyeU5hbWU/OiBzdHJpbmcsXG4gICAgb3B0aW9ucz86IHsgdGltZW91dDogbnVtYmVyIH1cbiAgKTogVCA9PiB7XG4gICAgaWYgKHRoaXMucmVxdWlyZU1vZHVsZS5jYWNoZVtwYXRoXSkge1xuICAgICAgcmV0dXJuIHRoaXMucmVxdWlyZU1vZHVsZS5jYWNoZVtwYXRoXSBhcyBUO1xuICAgIH1cbiAgICAvLyBUT0RPKHdhbmdxaW5neXUpOiBkZWFsIHdpdGggY3ljbGljIHJlcXVpcmVNb2R1bGVcbiAgICBjb25zdCBleHBvcnRzID0gdGhpcy5nZXRBcHAoKS5yZXF1aXJlTW9kdWxlPFQ+KHBhdGgsIGVudHJ5TmFtZSwgb3B0aW9ucyk7XG5cbiAgICAvLyBXaGVuIGVycm9yIGhhcHBlbnMgaW4gbG9hZGluZyBvciBleGVjdXRpbmcsIGEgSlMgZXJyb3Igd2lsbCBiZSB0aHJvd24uXG4gICAgLy8gU28gd2hlbiB3ZSBhcmUgaGVyZSwgdGhlIG1vZHVsZSBpcyBsb2FkZWQgYW5kIGV4ZWN1dGVkIHN1Y2Nlc3NmdWxseS5cbiAgICB0aGlzLnJlcXVpcmVNb2R1bGUuY2FjaGVbcGF0aF0gPSBleHBvcnRzO1xuICAgIHJldHVybiBleHBvcnRzO1xuICB9KTtcblxuICByZXF1aXJlTW9kdWxlQXN5bmMgPSA8UmVxdWlyZU1vZHVsZUFzeW5jPig8VD4oXG4gICAgcGF0aDogc3RyaW5nLFxuICAgIGNhbGxiYWNrPzogKGVycm9yPzogRXJyb3IsIHJldD86IFQpID0+IHZvaWRcbiAgKTogdm9pZCA9PiB7XG4gICAgY2FsbGJhY2sgPz89IChlcnJvcj86IEVycm9yKSA9PiB7XG4gICAgICBpZiAoIWVycm9yKSB7XG4gICAgICAgIC8vIGB1bmRlZmluZWQgfCBudWxsYCBtZWFucyBubyBlcnJvciBvY2N1cnJlZFxuICAgICAgICByZXR1cm47XG4gICAgICB9XG4gICAgICB0aGlzLmdldEFwcCgpLmhhbmRsZVVzZXJFcnJvcihlcnJvcik7XG4gICAgfTtcblxuICAgIGlmICh0aGlzLnJlcXVpcmVNb2R1bGVBc3luYy5jYWNoZVtwYXRoXSkge1xuICAgICAgY2FsbGJhY2sobnVsbCwgdGhpcy5yZXF1aXJlTW9kdWxlQXN5bmMuY2FjaGVbcGF0aF0gYXMgVCk7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIC8vIFRPRE8od2FuZ3Fpbmd5dSk6IGRlYWwgd2l0aCBjeWNsaWMgcmVxdWlyZU1vZHVsZVxuICAgIHRoaXMuZ2V0QXBwKCkucmVxdWlyZU1vZHVsZUFzeW5jPFQ+KHBhdGgsIChlcnJvciwgZXhwb3J0cykgPT4ge1xuICAgICAgaWYgKCFlcnJvcikge1xuICAgICAgICAvLyBPbmx5IGNhY2hlIHRoZSBleHBvcnRzIHdoZW4gbm8gZXJyb3IgaGFwcGVuZHMuXG4gICAgICAgIHRoaXMucmVxdWlyZU1vZHVsZUFzeW5jLmNhY2hlW3BhdGhdID0gZXhwb3J0cztcbiAgICAgIH1cbiAgICAgIGNhbGxiYWNrKGVycm9yLCBleHBvcnRzKTtcbiAgICB9KTtcbiAgfSk7XG5cbiAgY3JlYXRlRWxlbWVudCA9IChyb290SWQ6IHN0cmluZywgaWQ6IHN0cmluZykgPT5cbiAgICB0aGlzLmdldE5hdGl2ZUx5bngoKS5jcmVhdGVFbGVtZW50KHJvb3RJZCwgaWQpO1xuXG4gIGdldEVsZW1lbnRCeUlkID0gKGlkOiBzdHJpbmcpOiBFbGVtZW50ID0+IHtcbiAgICByZXR1cm4gbmV3IEVsZW1lbnQoJycsIGlkLCB0aGlzKTtcbiAgfTtcblxuICByZXBvcnRFcnJvciA9IChlcnJvcjogRXJyb3IgfCBzdHJpbmcsIG9wdGlvbnM/OiB7IGxldmVsPzogc3RyaW5nIH0pOiB2b2lkID0+IHtcbiAgICBsZXQgZXJyb3JPYmo6IEVycm9yO1xuICAgIGlmIChpc0Vycm9yKGVycm9yKSkge1xuICAgICAgZXJyb3JPYmogPSBlcnJvcjtcbiAgICB9IGVsc2Uge1xuICAgICAgbGV0IG1lc3NhZ2U6IHN0cmluZztcbiAgICAgIGlmICh0eXBlb2YgZXJyb3IgIT09ICdzdHJpbmcnKSB7XG4gICAgICAgIG1lc3NhZ2UgPSBKU09OLnN0cmluZ2lmeShlcnJvcik7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBtZXNzYWdlID0gZXJyb3I7XG4gICAgICB9XG4gICAgICBlcnJvck9iaiA9IG5ldyBFcnJvcihtZXNzYWdlKTtcbiAgICB9XG4gICAgY29uc3QgeyBsZXZlbCA9ICdlcnJvcicgfSA9IG9wdGlvbnMgfHwge307XG4gICAgbGV0IGVycm9yTGV2ZWw6IEx5bnhFcnJvckxldmVsO1xuICAgIHN3aXRjaCAobGV2ZWwpIHtcbiAgICAgIGNhc2UgJ2Vycm9yJzpcbiAgICAgICAgZXJyb3JMZXZlbCA9IEx5bnhFcnJvckxldmVsLkVycm9yO1xuICAgICAgICBicmVhaztcbiAgICAgIGNhc2UgJ3dhcm5pbmcnOlxuICAgICAgICBlcnJvckxldmVsID0gTHlueEVycm9yTGV2ZWwuV2FybjtcbiAgICAgICAgYnJlYWs7XG4gICAgICBjYXNlICdmYXRhbCc6XG4gICAgICAgIGVycm9yTGV2ZWwgPSBMeW54RXJyb3JMZXZlbC5GYXRhbDtcbiAgICAgICAgYnJlYWs7XG4gICAgICBkZWZhdWx0OlxuICAgICAgICBlcnJvckxldmVsID0gTHlueEVycm9yTGV2ZWwuRXJyb3I7XG4gICAgfVxuICAgIHRoaXMuZ2V0QXBwKCkuaGFuZGxlVXNlckVycm9yKGVycm9yT2JqLCBlcnJvck9iai5jYXVzZSwgZXJyb3JMZXZlbCk7XG4gIH07XG5cbiAgcmVnaXN0ZXJNb2R1bGUgPSA8TW9kdWxlIGV4dGVuZHMgb2JqZWN0PihcbiAgICBuYW1lOiBzdHJpbmcsXG4gICAgbW9kdWxlOiBNb2R1bGVcbiAgKTogdm9pZCA9PiB0aGlzLmdldEFwcCgpLnJlZ2lzdGVyTW9kdWxlKG5hbWUsIG1vZHVsZSk7XG5cbiAgZ2V0SlNNb2R1bGUgPSA8TW9kdWxlID0gdW5rbm93bj4obmFtZTogc3RyaW5nKTogTW9kdWxlID0+IHtcbiAgICByZXR1cm4gdGhpcy5nZXRBcHAoKS5nZXRKU01vZHVsZTxNb2R1bGU+KG5hbWUpO1xuICB9O1xuXG4gIGdldFRleHRJbmZvID0gdGhpcy5nZXRBcHAoKS5fYXBpTGlzdFsnZ2V0VGV4dEluZm8nXSBhcyAoXG4gICAgdGV4dDogc3RyaW5nLFxuICAgIGluZm86IFRleHRJbmZvXG4gICkgPT4gVGV4dE1ldHJpY3M7XG5cbiAgYWRkRm9udCA9IChcbiAgICBmb250OiB7IHNyYzogc3RyaW5nOyAnZm9udC1mYW1pbHknOiBzdHJpbmcgfSxcbiAgICBjYWxsYmFjazogKGU/OiBFcnJvcikgPT4gdm9pZFxuICApID0+IHtcbiAgICBpZiAoIWlzT2JqZWN0KGZvbnQpKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoJ1RoZSBmaXJzdCBhcmd1bWVudCBtdXN0IGJlIG9iamVjdCB0eXBlJyk7XG4gICAgfVxuICAgIGlmICghaXNTdHJpbmcoZm9udFsnZm9udC1mYW1pbHknXSkgfHwgIWlzU3RyaW5nKGZvbnRbJ3NyYyddKSkge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKCdUaGUgZm9udCB2YWx1ZSBtdXN0IGhhdmUgZm9udC1mYW1pbHkgYW5kIHNyYycpO1xuICAgIH1cbiAgICBpZiAoIWlzRnVuY3Rpb24oY2FsbGJhY2spKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoJ1RoZSBzZWNvbmQgYXJndW1lbnQgbXVzdCBiZSBmdW5jdGlvbiB0eXBlJyk7XG4gICAgfVxuXG4gICAgdGhpcy5nZXROYXRpdmVMeW54KCkuYWRkRm9udChmb250LCBjYWxsYmFjayk7XG4gIH07XG5cbiAgc3RvcEV4cG9zdXJlID0gdGhpcy5nZXRBcHAoKS5fYXBpTGlzdFsnc3RvcEV4cG9zdXJlJ10gYXMgKG9wdGlvbnM/OiB7XG4gICAgc2VuZEV2ZW50OiBib29sZWFuO1xuICB9KSA9PiB2b2lkO1xuXG4gIHNldE9ic2VydmVyRnJhbWVSYXRlID0gdGhpcy5nZXRBcHAoKS5fYXBpTGlzdFtcbiAgICAnc2V0T2JzZXJ2ZXJGcmFtZVJhdGUnXG4gIF0gYXMgKG9wdGlvbnM/OiB7IGZvclBhZ2VSZWN0PzogbnVtYmVyOyBmb3JFeHBvc3VyZUNoZWNrPzogbnVtYmVyIH0pID0+IHZvaWQ7XG5cbiAgcGVyZm9ybWFuY2U6IFBlcmZvcm1hbmNlID0gdGhpcy5nZXRBcHAoKS5wZXJmb3JtYW5jZTtcblxuICBiZWZvcmVQdWJsaXNoRXZlbnQgPSB0aGlzLmdldEFwcCgpLl9hb3BNYW5hZ2VyLl9iZWZvcmVQdWJsaXNoRXZlbnQ7XG5cbiAgZGlzcGF0Y2hTZXNzaW9uU3RvcmFnZUV2ZW50KGV2ZW50OiBNZXNzYWdlRXZlbnQpOiB2b2lkIHtcbiAgICB2YXIgZXZlbnRSZXN1bHQgPSB0aGlzLmdldENvcmVDb250ZXh0KCkuZGlzcGF0Y2hFdmVudChldmVudCk7XG5cbiAgICAvLyBJbiBMeW54VmlldywgdGhlIGV2ZW50IGhhcyBiZWVuIHN1Y2Vzc2Z1bGx5IGhhbmRsZWQgYnkgYENvcmVDb250ZXh0YC5cbiAgICBpZiAoZXZlbnRSZXN1bHQgPT0gMCkge1xuICAgICAgcmV0dXJuO1xuICAgIH1cblxuICAgIC8vIEluIHJ1bnRpbWUgc3RhbmRhbG9uZSBtb2RlLCBydW50aW1lIGNhbm5vdCBkaXNwYXRjaCBldmVudCB0byBgQ29yZUNvbnRleHRgLFxuICAgIC8vIGZhbGxiYWNrIHRvIGBKU0NvbnRleHRgIHNvIHRoYXQgcnVudGltZSBjYW4gaGFuZGxlIHNlc3Npb24gc3RvcmFnZSBldmVudHNcbiAgICAvLyBieSBpdHNlbGYuXG4gICAgdGhpcy5nZXRKU0NvbnRleHQoKS5kaXNwYXRjaEV2ZW50KGV2ZW50KTtcbiAgfVxuXG4gIC8vIHNlc3Npb25TdG9yYWdlIEFwaVxuICBzZXRTZXNzaW9uU3RvcmFnZUl0ZW0gPSA8VD4oa2V5OiBzdHJpbmcsIHZhbHVlOiBUKTogdm9pZCA9PiB7XG4gICAgdGhpcy5kaXNwYXRjaFNlc3Npb25TdG9yYWdlRXZlbnQoe1xuICAgICAgdHlwZTogTWVzc2FnZUV2ZW50VHlwZS5FVkVOVF9TRVRfU0VTU0lPTl9TVE9SQUdFLFxuICAgICAgZGF0YToge1xuICAgICAgICBrZXksXG4gICAgICAgIHZhbHVlLFxuICAgICAgfSxcbiAgICB9KTtcbiAgfTtcblxuICBnZXRTZXNzaW9uU3RvcmFnZUl0ZW0gPSA8VD4oXG4gICAga2V5OiBzdHJpbmcsXG4gICAgY2FsbGJhY2s6ICh2YWx1ZTogVCkgPT4gdm9pZFxuICApOiB2b2lkID0+IHtcbiAgICAvLyBUT0RPKG5paGFvLnJveWFsKTogcmVmYWN0b3IgdG8gZGlzcGF0Y2hFdmVudCBhZnRlciBBcGlDYWxsYmFjayBzdXBwb3J0ZWQuXG4gICAgdGhpcy5nZXROYXRpdmVBcHAoKS5nZXRTZXNzaW9uU3RvcmFnZUl0ZW0oa2V5LCBjYWxsYmFjayk7XG4gIH07XG5cbiAgc3Vic2NyaWJlU2Vzc2lvblN0b3JhZ2UgPSA8VD4oXG4gICAga2V5OiBzdHJpbmcsXG4gICAgY2FsbGJhY2s6ICh2YWx1ZTogVCkgPT4gdm9pZFxuICApOiBudW1iZXIgPT4ge1xuICAgIC8vIFRPRE8obmloYW8ucm95YWwpOiByZWZhY3RvciB0byBkaXNwYXRjaEV2ZW50IGFmdGVyIEFwaUNhbGxiYWNrIHN1cHBvcnRlZC5cbiAgICBsZXQgbGlzdGVuZXJJZCA9IEx5bnguX19yZWdpc3RlclNoYXJlZERhdGFDb3VudGVyKys7XG4gICAgdGhpcy5nZXROYXRpdmVBcHAoKS5zdWJzY3JpYmVTZXNzaW9uU3RvcmFnZShrZXksIGxpc3RlbmVySWQsIGNhbGxiYWNrKTtcbiAgICByZXR1cm4gbGlzdGVuZXJJZDtcbiAgfTtcblxuICB1bnN1YnNjcmliZVNlc3Npb25TdG9yYWdlID0gKGtleTogc3RyaW5nLCBsaXN0ZW5lcklkOiBudW1iZXIpID0+IHtcbiAgICB0aGlzLmRpc3BhdGNoU2Vzc2lvblN0b3JhZ2VFdmVudCh7XG4gICAgICB0eXBlOiBNZXNzYWdlRXZlbnRUeXBlLkVWRU5UX1VOU1VCU0NSSUJFX1NFU1NJT05fU1RPUkFHRSxcbiAgICAgIGRhdGE6IHtcbiAgICAgICAga2V5LFxuICAgICAgICBsaXN0ZW5lcklkLFxuICAgICAgfSxcbiAgICB9KTtcbiAgfTtcblxuICBnZXREZXZ0b29sID0gdGhpcy5nZXROYXRpdmVMeW54KCkuZ2V0RGV2dG9vbDtcbiAgZ2V0Q29yZUNvbnRleHQgPSB0aGlzLmdldE5hdGl2ZUx5bngoKS5nZXRDb3JlQ29udGV4dDtcbiAgZ2V0SlNDb250ZXh0ID0gdGhpcy5nZXROYXRpdmVMeW54KCkuZ2V0SlNDb250ZXh0O1xuICBnZXRVSUNvbnRleHQgPSB0aGlzLmdldE5hdGl2ZUx5bngoKS5nZXRVSUNvbnRleHQ7XG4gIGdldE5hdGl2ZSA9IHRoaXMuZ2V0TmF0aXZlTHlueCgpLmdldE5hdGl2ZTtcbiAgZ2V0RW5naW5lID0gdGhpcy5nZXROYXRpdmVMeW54KCkuZ2V0RW5naW5lO1xuXG4gIGdldEN1c3RvbVNlY3Rpb25TeW5jID0gdGhpcy5nZXROYXRpdmVMeW54KCkuZ2V0Q3VzdG9tU2VjdGlvblN5bmM7XG5cbiAgYWNjZXNzaWJpbGl0eUFubm91bmNlID0gdGhpcy5nZXROYXRpdmVBcHAoKS5uYXRpdmVNb2R1bGVQcm94eVxuICAgIC5MeW54QWNjZXNzaWJpbGl0eU1vZHVsZT8uYWNjZXNzaWJpbGl0eUFubm91bmNlO1xuXG4gIHJlcXVlc3RSZXNvdXJjZVByZWZldGNoID0gdGhpcy5nZXROYXRpdmVBcHAoKS5uYXRpdmVNb2R1bGVQcm94eVxuICAgIC5MeW54UmVzb3VyY2VNb2R1bGU/LnJlcXVlc3RSZXNvdXJjZVByZWZldGNoO1xuXG4gIGNhbmNlbFJlc291cmNlUHJlZmV0Y2ggPSB0aGlzLmdldE5hdGl2ZUFwcCgpLm5hdGl2ZU1vZHVsZVByb3h5XG4gICAgLkx5bnhSZXNvdXJjZU1vZHVsZT8uY2FuY2VsUmVzb3VyY2VQcmVmZXRjaDtcblxuICBzZXRTaGFyZWREYXRhID0gKGRhdGFLZXk6IHN0cmluZywgZGF0YVZhbDogdW5rbm93bik6IHZvaWQgPT4ge1xuICAgIG5hdGl2ZUdsb2JhbC5zaGFyZWREYXRhW2RhdGFLZXldID0gZGF0YVZhbDtcbiAgICBsZXQgdmFyaWFibGUgPSB7fTtcbiAgICB2YXJpYWJsZVtkYXRhS2V5XSA9IGRhdGFWYWw7XG4gICAgbmF0aXZlR2xvYmFsLnNoYXJlRGF0YVN1YmplY3Qubm90aWZ5RGF0YUNoYW5nZSh2YXJpYWJsZSk7XG4gIH07XG5cbiAgZ2V0U2hhcmVkRGF0YSA9IDxUID0gdW5rbm93bj4oZGF0YUtleTogc3RyaW5nKTogVCA9PiB7XG4gICAgbGV0IGRhdGEgPSBuYXRpdmVHbG9iYWwuc2hhcmVkRGF0YVtkYXRhS2V5XTtcbiAgICBpZiAoTk9ERV9FTlYgPT09ICdkZXZlbG9wbWVudCcpIHtcbiAgICAgIGlmIChkYXRhID09PSB1bmRlZmluZWQpIHtcbiAgICAgICAgZGF0YSA9IHRoaXMuZ2V0QXBwKCkuTmF0aXZlTW9kdWxlcy5MeW54UmVjb3JkZXJSZXBsYXlEYXRhTW9kdWxlPy5nZXRTaGFyZWREYXRhKFxuICAgICAgICAgIGRhdGFLZXlcbiAgICAgICAgKS52YWx1ZTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHRoaXMuZ2V0TmF0aXZlQXBwKCkucmVjb3JkU2hhcmVkRGF0YShkYXRhS2V5LCBkYXRhKTtcbiAgICAgIH1cbiAgICB9XG4gICAgcmV0dXJuIGRhdGE7XG4gIH07XG5cbiAgcmVnaXN0ZXJTaGFyZWREYXRhT2JzZXJ2ZXIgPSA8VD4oY2FsbGJhY2s6IChkYXRhOiBUKSA9PiB2b2lkKTogdm9pZCA9PlxuICAgIG5hdGl2ZUdsb2JhbC5zaGFyZURhdGFTdWJqZWN0LnJlZ2lzdGVyT2JzZXJ2ZXIoY2FsbGJhY2spO1xuXG4gIHJlbW92ZVNoYXJlZERhdGFPYnNlcnZlciA9IDxUPihjYWxsYmFjazogKGRhdGE6IFQpID0+IHZvaWQpOiB2b2lkID0+XG4gICAgbmF0aXZlR2xvYmFsLnNoYXJlRGF0YVN1YmplY3QucmVtb3ZlT2JzZXJ2ZXIoY2FsbGJhY2spO1xuXG4gIHRyaWdnZXJMZXB1c0dsb2JhbEV2ZW50ID0gKGV2ZW50OiBzdHJpbmcsIHBhcmFtczogUmVjb3JkPGFueSwgYW55Pik6IHZvaWQgPT5cbiAgICB0aGlzLmdldE5hdGl2ZUFwcCgpLnRyaWdnZXJMZXB1c0dsb2JhbEV2ZW50KGV2ZW50LCBwYXJhbXMpO1xuXG4gIC8vIGZvciByZWxvYWRcbiAgcmVsb2FkID0gKHZhbHVlOiBvYmplY3QsIGNhbGxiYWNrOiAoKSA9PiB2b2lkKSA9PiB7XG4gICAgdGhpcy5nZXROYXRpdmVMeW54KCkucmVsb2FkKHZhbHVlLCBjYWxsYmFjayk7XG4gIH07XG5cbiAgY3JlYXRlSW50ZXJzZWN0aW9uT2JzZXJ2ZXI6IENyZWF0ZUludGVyc2VjdGlvbk9ic2VydmVyRnVuYztcblxuICBmZXRjaER5bmFtaWNDb21wb25lbnQgPSAoXG4gICAgdXJsOiBzdHJpbmcsXG4gICAgb3B0aW9uczogUmVjb3JkPHN0cmluZywgYW55PixcbiAgICBjYWxsYmFjazogKHJlczogeyBjb2RlOiBudW1iZXIgfSkgPT4gdm9pZCxcbiAgICBpZDogc3RyaW5nW11cbiAgKSA9PiB0aGlzLmdldE5hdGl2ZUx5bngoKS5mZXRjaER5bmFtaWNDb21wb25lbnQodXJsLCBvcHRpb25zLCBjYWxsYmFjaywgaWQpO1xuXG4gIC8vIFdyYXBwZXIgUXVlcnlDb21wb25lbnQgdG8gZGVjaWRlIGlmIGNvbXBvbmVudCBoYXMgbG9hZGVkLlxuICBRdWVyeUNvbXBvbmVudCA9IChzb3VyY2U6IHN0cmluZywgY2FsbGJhY2s6IChyZXN1bHQ6IGFueSkgPT4gdm9pZCkgPT4ge1xuICAgIGNvbnN0IGlubmVySW52b2tlQ2FsbGJhY2sgPSAoKSA9PiB7XG4gICAgICBjYWxsYmFjayh7XG4gICAgICAgIGNvZGU6IDAsXG4gICAgICAgIGRhdGE6IHsgdXJsOiBzb3VyY2UsIHN5bmM6IHRydWUsIGVycm9yX21lc3NhZ2U6ICcnLCBtb2RlOiAnY2FjaGUnIH0sXG4gICAgICAgIGRldGFpbDogeyBzY2hlbWE6IHNvdXJjZSwgY2FjaGU6IGZhbHNlLCBlcnJNc2c6ICcnIH0sXG4gICAgICB9KTtcbiAgICB9O1xuICAgIC8vIGlmIGR5bmFtaWMgY29tcG9uZXQgaGFzIGJlZW4gcmVhZHkgaW4gYmFja2dyb3VuZCB0aHJlYWQsIGNhbGxiYWNrIGRpcmVjdGx5XG4gICAgaWYgKHRoaXMuZ2V0QXBwKCkubG9hZGVkRHluYW1pY0NvbXBvbmVudHNTZXQuaGFzKHNvdXJjZSkpIHtcbiAgICAgIGlubmVySW52b2tlQ2FsbGJhY2soKTtcbiAgICAgIHJldHVybjtcbiAgICB9XG4gICAgLy8gaWYgZHluYW1pYyBjb21wb25ldCBoYXMgYmVlbiByZWFkeSBpbiBtYWluIHRocmVhZCwgbG9hZER5bmFtaWNDb21wb25lbnQgYW5kIGNhbGxiYWNrIGRpcmVjdGx5XG4gICAgY29uc3QgaW5uZXJDYWxsYmFjayA9IChyZXN1bHQ6IGFueSkgPT4ge1xuICAgICAgaWYgKHJlc3VsdC5fX2hhc1JlYWR5ID09PSB0cnVlKSB7XG4gICAgICAgIG5hdGl2ZUdsb2JhbC5sb2FkRHluYW1pY0NvbXBvbmVudCh0aGlzLmdldEFwcCgpLCBzb3VyY2UpO1xuICAgICAgICBpbm5lckludm9rZUNhbGxiYWNrKCk7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBjYWxsYmFjayhyZXN1bHQpO1xuICAgICAgfVxuICAgIH07XG4gICAgLy8gcXVlcnkgY29tcG9uZXRcbiAgICB0aGlzLmdldE5hdGl2ZUx5bngoKS5RdWVyeUNvbXBvbmVudChzb3VyY2UsIGlubmVyQ2FsbGJhY2spO1xuICB9O1xuXG4gIGxvYWREeW5hbWljQ29tcG9uZW50OiBMb2FkRHluYW1pY0NvbXBvbmVudEZ1bmMgPSAoXG4gICAgaWRPclVybDogc3RyaW5nIHwgc3RyaW5nW10sXG4gICAgdXJsT3JPcHRpb25zPzogc3RyaW5nIHwgUmVjb3JkPHN0cmluZywgYW55PixcbiAgICBvcHRpb25zOiBSZWNvcmQ8c3RyaW5nLCBhbnk+ID0ge31cbiAgKTogUHJvbWlzZTxcbiAgICBMb2FkRHluYW1pY0NvbXBvbmVudFN1Y2Nlc3NSZXN1bHQgfCBMb2FkRHluYW1pY0NvbXBvbmVudEZhaWxlZFJlc3VsdFxuICA+ID0+IHtcbiAgICByZXR1cm4gbmV3IHRoaXMuUHJvbWlzZSgocmVzb2x2ZSwgcmVqZWN0KSA9PiB7XG4gICAgICAvLyBsZWdhbCBwYXJhbSB0eXBlczpcbiAgICAgIC8vIDAuICh1cmw6IHN0cmluZywgP29wdGlvbnMpXG4gICAgICAvLyAxLiAoaWQ6IHN0cmluZywgdXJsOiBzdHJpbmcsID9vcHRpb25zKVxuICAgICAgLy8gMi4gKGlkczogc3RyaW5nW10sIHVybDogc3RyaW5nLCA/b3B0aW9ucylcbiAgICAgIGxldCBpZHM6IHN0cmluZ1tdID0gW107XG4gICAgICBsZXQgdXJsOiBzdHJpbmc7XG4gICAgICBpZiAoQXJyYXkuaXNBcnJheShpZE9yVXJsKSkge1xuICAgICAgICBpZHMgPSBpZE9yVXJsO1xuICAgICAgICB1cmwgPSB1cmxPck9wdGlvbnMgYXMgc3RyaW5nO1xuICAgICAgfSBlbHNlIGlmICh0eXBlb2YgdXJsT3JPcHRpb25zID09PSAnc3RyaW5nJykge1xuICAgICAgICBpZHMgPSBbaWRPclVybF07XG4gICAgICAgIHVybCA9IHVybE9yT3B0aW9ucztcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHVybCA9IGlkT3JVcmw7XG4gICAgICAgIG9wdGlvbnMgPSB1cmxPck9wdGlvbnM7XG4gICAgICB9XG4gICAgICBpZiAodGhpcy5nZXRBcHAoKS5sb2FkZWREeW5hbWljQ29tcG9uZW50c1NldC5oYXModXJsKSkge1xuICAgICAgICAvLyBpbnZva2UgZGlyZWN0bHlcbiAgICAgICAgcmVzb2x2ZSh7XG4gICAgICAgICAgY29kZTogMCxcbiAgICAgICAgICBkYXRhOiB7IHVybDogdXJsLCBzeW5jOiBmYWxzZSwgZXJyb3JfbWVzc2FnZTogJycsIG1vZGU6ICdub3JtYWwnIH0sXG4gICAgICAgICAgZGV0YWlsOiB7IHNjaGVtYTogdXJsLCBjYWNoZTogZmFsc2UsIGVyck1zZzogJycgfSxcbiAgICAgICAgfSBhcyBMb2FkRHluYW1pY0NvbXBvbmVudFN1Y2Nlc3NSZXN1bHQpO1xuICAgICAgICByZXR1cm47XG4gICAgICB9XG5cbiAgICAgIHRoaXMuZ2V0TmF0aXZlTHlueCgpLmZldGNoRHluYW1pY0NvbXBvbmVudChcbiAgICAgICAgdXJsLFxuICAgICAgICBvcHRpb25zLFxuICAgICAgICAocmVzKSA9PiB7XG4gICAgICAgICAgaWYgKHJlcyAmJiByZXMuY29kZSA9PSAwKSB7XG4gICAgICAgICAgICByZXNvbHZlKHJlcyBhcyBMb2FkRHluYW1pY0NvbXBvbmVudFN1Y2Nlc3NSZXN1bHQpO1xuICAgICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgICByZWplY3QocmVzKTtcbiAgICAgICAgICB9XG4gICAgICAgIH0sXG4gICAgICAgIGlkc1xuICAgICAgKTtcbiAgICB9KTtcbiAgfTtcblxuICBmZXRjaCA9IChpbnB1dDogUmVxdWVzdEluZm8sIGluaXQ/OiBSZXF1ZXN0SW5pdCk6IFByb21pc2U8UmVzcG9uc2U+ID0+IHtcbiAgICByZXR1cm4gbmV3IHRoaXMuUHJvbWlzZSgocmVzb2x2ZSwgcmVqZWN0KSA9PiB7XG4gICAgICBjb25zdCByZXF1ZXN0ID0gbmV3IG5hdGl2ZUdsb2JhbC5SZXF1ZXN0KGlucHV0LCBpbml0KTtcbiAgICAgIGNvbnN0IHNpZ25hbCA9IHJlcXVlc3Quc2lnbmFsO1xuICAgICAgaWYgKHNpZ25hbC5hYm9ydGVkKSB7XG4gICAgICAgIHJldHVybiByZWplY3Qoc2lnbmFsLnJlYXNvbik7XG4gICAgICB9XG5cbiAgICAgIHNpZ25hbC5hZGRFdmVudExpc3RlbmVyKCdhYm9ydCcsIChldmVudCkgPT4ge1xuICAgICAgICByZWplY3Qoc2lnbmFsLnJlYXNvbik7XG4gICAgICB9KTtcblxuICAgICAgY29uc3QgZW5hYmxlRmV0Y2hBUElTdGFuZGFyZFN0cmVhbWluZyA9IHRoaXMuZ2V0QXBwKCkucGFyYW1zXG4gICAgICAgID8ucGFnZUNvbmZpZ1N1YnNldD8uZW5hYmxlRmV0Y2hBUElTdGFuZGFyZFN0cmVhbWluZztcbiAgICAgIHJlcXVlc3QubHlueEV4dGVuc2lvbltcbiAgICAgICAgJ2VuYWJsZUZldGNoQVBJU3RhbmRhcmRTdHJlYW1pbmcnXG4gICAgICBdID0gZW5hYmxlRmV0Y2hBUElTdGFuZGFyZFN0cmVhbWluZztcbiAgICAgIGNvbnN0IGZldGNoQXJnID0ge1xuICAgICAgICBtZXRob2Q6IHJlcXVlc3QubWV0aG9kLFxuICAgICAgICB1cmw6IHJlcXVlc3QudXJsLFxuICAgICAgICBvcmlnaW46IHRoaXMuZ2V0TmF0aXZlQXBwKCkuX19wYWdlVXJsLFxuICAgICAgICBoZWFkZXJzOiBPYmplY3QuZnJvbUVudHJpZXMocmVxdWVzdC5oZWFkZXJzLmVudHJpZXMoKSksXG4gICAgICAgIGJvZHk6IHJlcXVlc3QuX2FycmF5QnVmZmVyLFxuICAgICAgICBseW54RXh0ZW5zaW9uOiByZXF1ZXN0Lmx5bnhFeHRlbnNpb24sXG4gICAgICB9O1xuICAgICAgY29uc3QgdXNlU3RyZWFtaW5nID1cbiAgICAgICAgcmVxdWVzdC5seW54RXh0ZW5zaW9uWyd1c2VTdHJlYW1pbmcnXSB8fFxuICAgICAgICBlbmFibGVGZXRjaEFQSVN0YW5kYXJkU3RyZWFtaW5nO1xuICAgICAgdGhpcy5nZXRBcHAoKS5OYXRpdmVNb2R1bGVzLkx5bnhGZXRjaE1vZHVsZS5mZXRjaChcbiAgICAgICAgZmV0Y2hBcmcsXG4gICAgICAgIChyZXNwb25zZTogYW55KSA9PiB7XG4gICAgICAgICAgaWYgKHNpZ25hbC5hYm9ydGVkKSB7XG4gICAgICAgICAgICByZXR1cm47XG4gICAgICAgICAgfVxuICAgICAgICAgIHRyeSB7XG4gICAgICAgICAgICBjb25zdCBzdHJlYW1pbmdCb2R5UmVjZWl2ZXIgPSBuZXcgKHRoaXMuZ2V0QXBwKCkuX1JlYWRhYmxlU3RyZWFtQ2xhc3MpKCk7XG5cbiAgICAgICAgICAgIGNvbnN0IHJlc3AgPSBuZXcgbmF0aXZlR2xvYmFsLlJlc3BvbnNlKFxuICAgICAgICAgICAgICB1c2VTdHJlYW1pbmcgPyBzdHJlYW1pbmdCb2R5UmVjZWl2ZXIgOiByZXNwb25zZS5ib2R5LFxuICAgICAgICAgICAgICByZXNwb25zZSxcbiAgICAgICAgICAgICAgZW5hYmxlRmV0Y2hBUElTdGFuZGFyZFN0cmVhbWluZ1xuICAgICAgICAgICAgKTtcblxuICAgICAgICAgICAgaWYgKHVzZVN0cmVhbWluZykge1xuICAgICAgICAgICAgICBjb25zdCBpZCA9IHJlc3AubHlueEV4dGVuc2lvblsnc3RyZWFtaW5nSWQnXTtcbiAgICAgICAgICAgICAgdGhpcy5nZXRBcHAoKS5HbG9iYWxFdmVudEVtaXR0ZXIuYWRkTGlzdGVuZXIoXG4gICAgICAgICAgICAgICAgaWQsXG4gICAgICAgICAgICAgICAgKHJlc3VsdDogYW55KSA9PiB7XG4gICAgICAgICAgICAgICAgICBjb25zdCBldmVudCA9IHJlc3VsdC5ldmVudDtcbiAgICAgICAgICAgICAgICAgIGlmIChldmVudCA9PT0gJ29uRGF0YScpIHtcbiAgICAgICAgICAgICAgICAgICAgc3RyZWFtaW5nQm9keVJlY2VpdmVyLm9uRGF0YShyZXN1bHQuZGF0YSk7XG4gICAgICAgICAgICAgICAgICB9IGVsc2UgaWYgKGV2ZW50ID09PSAnb25FbmQnKSB7XG4gICAgICAgICAgICAgICAgICAgIHN0cmVhbWluZ0JvZHlSZWNlaXZlci5vbkVuZCgpO1xuICAgICAgICAgICAgICAgICAgfSBlbHNlIGlmIChldmVudCA9PT0gJ29uRXJyb3InKSB7XG4gICAgICAgICAgICAgICAgICAgIHN0cmVhbWluZ0JvZHlSZWNlaXZlci5vbkVycm9yKHJlc3VsdC5lcnJvcik7XG4gICAgICAgICAgICAgICAgICB9XG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICApO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgcmVzb2x2ZShyZXNwKTtcbiAgICAgICAgICB9IGNhdGNoIChfKSB7XG4gICAgICAgICAgICAvLyBDYXRjaGVzIGFueSBleGNlcHRpb24gdGhhdCBtaWdodCBsZWFkIHRvIGEgZmFpbHVyZSBpblxuICAgICAgICAgICAgLy8gY3JlYXRpbmcgYSBSZXNwb25zZSBhbmQgdGhyb3dzIHRoZSBlcnJvciB1c2luZyBgcmVqZWN0YCxcbiAgICAgICAgICAgIC8vIGVuYWJsaW5nIHRoZSBmcm9udGVuZCB0byBoYW5kbGUgdGhlIGVycm9yLlxuICAgICAgICAgICAgcmVqZWN0KG5ldyBUeXBlRXJyb3IocmVzcG9uc2Uuc3RhdHVzVGV4dCkpO1xuICAgICAgICAgIH1cbiAgICAgICAgfSxcbiAgICAgICAgKGVycm9yOiBhbnkpID0+IHtcbiAgICAgICAgICBpZiAoc2lnbmFsLmFib3J0ZWQpIHtcbiAgICAgICAgICAgIHJldHVybjtcbiAgICAgICAgICB9XG4gICAgICAgICAgcmVqZWN0KG5ldyBUeXBlRXJyb3IoZXJyb3IubWVzc2FnZSkpO1xuICAgICAgICB9XG4gICAgICApO1xuICAgIH0pO1xuICB9O1xuXG4gIEV2ZW50U291cmNlID0gY3JlYXRlRXZlbnRTb3VyY2UodGhpcy5mZXRjaCk7XG5cbiAgY3JlYXRlU2VsZWN0b3JRdWVyeSA9IChjb21wb25lbnQ/OiBzdHJpbmcpOiBTZWxlY3RvclF1ZXJ5ID0+IHtcbiAgICByZXR1cm4gU2VsZWN0b3JRdWVyeS5uZXdFbXB0eVF1ZXJ5KFxuICAgICAge1xuICAgICAgICBuYXRpdmVBcHA6IHRoaXMuZ2V0TmF0aXZlQXBwKCksXG4gICAgICAgIGx5bng6IHRoaXMsXG4gICAgICB9LFxuICAgICAgY29tcG9uZW50XG4gICAgKTtcbiAgfTtcblxuICByZXF1ZXN0QW5pbWF0aW9uRnJhbWUgPSAoY2FsbGJhY2s6ICgpID0+IHZvaWQpID0+XG4gICAgdGhpcy5nZXROYXRpdmVBcHAoKS5yZXF1ZXN0QW5pbWF0aW9uRnJhbWUoY2FsbGJhY2spO1xuXG4gIGNhbmNlbEFuaW1hdGlvbkZyYW1lID0gKGFuaW1hdGlvbklkOiBudW1iZXIpID0+XG4gICAgdGhpcy5nZXROYXRpdmVBcHAoKS5jYW5jZWxBbmltYXRpb25GcmFtZShhbmltYXRpb25JZCk7XG5cbiAgcXVldWVNaWNyb3Rhc2soY2FsbGJhY2s6ICgpID0+IHZvaWQpOiB2b2lkIHtcbiAgICB0aGlzLmdldE5hdGl2ZUx5bngoKS5xdWV1ZU1pY3JvdGFzayhjYWxsYmFjayk7XG4gIH1cblxuICBsb2FkU2NyaXB0ID0gPExvYWRTY3JpcHQ+KDxUPihcbiAgICB1cmw6IHN0cmluZyxcbiAgICBvcHRpb25zPzogeyBidW5kbGVOYW1lPzogc3RyaW5nOyB1c2VNb2R1bGVXcmFwcGVyPzogYm9vbGVhbiB9XG4gICk6IFQgPT4ge1xuICAgIGNvbnN0IHsgYnVuZGxlTmFtZSA9IERFRkFVTFRfRU5UUlkgfSA9IG9wdGlvbnM7XG4gICAgY29uc3QgY2FjaGVLZXkgPSBidW5kbGVOYW1lICsgJzonICsgdXJsO1xuICAgIGlmICh0aGlzLmxvYWRTY3JpcHQuY2FjaGVbY2FjaGVLZXldKSB7XG4gICAgICByZXR1cm4gdGhpcy5sb2FkU2NyaXB0LmNhY2hlW2NhY2hlS2V5XSBhcyBUO1xuICAgIH1cbiAgICBjb25zdCBleHBvcnRzID0gdGhpcy5nZXRBcHAoKS5sb2FkU2NyaXB0PFQ+KHVybCwgb3B0aW9ucyk7XG4gICAgdGhpcy5sb2FkU2NyaXB0LmNhY2hlW2NhY2hlS2V5XSA9IGV4cG9ydHM7XG4gICAgcmV0dXJuIGV4cG9ydHM7XG4gIH0pO1xuXG4gIGZldGNoQnVuZGxlID0gdGhpcy5nZXROYXRpdmVMeW54KCkuZmV0Y2hCdW5kbGU7XG5cbiAgX19hZGRSZXBvcnRlckN1c3RvbUluZm8gPSAoaW5mbzogUmVjb3JkPHN0cmluZywgc3RyaW5nPik6IHZvaWQgPT4ge1xuICAgIHRoaXMuZ2V0TmF0aXZlQXBwKCkuX19hZGRSZXBvcnRlckN1c3RvbUluZm8oaW5mbyk7XG4gIH07XG5cbiAgZ2V0TW9kdWxlTG9hZGVyID0gKCk6IEx5bnhNb2R1bGVMb2FkZXIgPT4ge1xuICAgIHJldHVybiBuYXRpdmVHbG9iYWxbJ25hcGlMb2FkZXJPblJUJyArIHRoaXMuZ2V0QXBwKCkubmF0aXZlQXBwSWRdO1xuICB9O1xuXG4gIGNyZWF0ZUFuaW1hdGlvbiA9IChcbiAgICBpZDogc3RyaW5nLFxuICAgIGtleWZyYW1lczogQXJyYXk8UmVjb3JkPHN0cmluZywgYW55Pj4sXG4gICAgb3B0aW9uczogUmVjb3JkPHN0cmluZywgYW55PlxuICApID0+IHtcbiAgICByZXR1cm4gbmV3IEFuaW1hdGlvblYyKGlkLCBrZXlmcmFtZXMsIG9wdGlvbnMpO1xuICB9O1xufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmV4cG9ydCBpbnRlcmZhY2UgVGV4dEluZm8ge1xuICBmb250U2l6ZTogc3RyaW5nO1xuICBmb250RmFtaWx5Pzogc3RyaW5nO1xufVxuXG5leHBvcnQgaW50ZXJmYWNlIFRleHRNZXRyaWNzIHtcbiAgd2lkdGg6IG51bWJlcjtcbn1cblxuZXhwb3J0IGNsYXNzIFRleHRJbmZvTWFuYWdlciB7XG4gIHByaXZhdGUgcmVhZG9ubHkgX25hdGl2ZU1vZHVsZXM6IGFueTtcbiAgcHJpdmF0ZSBfdGV4dEluZm9Nb2R1bGU6IGFueSA9IHVuZGVmaW5lZDtcblxuICBjb25zdHJ1Y3RvcihuYXRpdmVNb2R1bGVzOiBvYmplY3QpIHtcbiAgICB0aGlzLl9uYXRpdmVNb2R1bGVzID0gbmF0aXZlTW9kdWxlcztcbiAgfVxuXG4gIGdldFRleHRJbmZvID0gKHBhcmFtOiBhbnksIG9wdGlvbnM/OiBUZXh0SW5mbyk6IFRleHRNZXRyaWNzID0+IHtcbiAgICBpZiAodGhpcy5fdGV4dEluZm9Nb2R1bGUgPT09IHVuZGVmaW5lZCkge1xuICAgICAgdGhpcy5fdGV4dEluZm9Nb2R1bGUgPSB0aGlzLl9uYXRpdmVNb2R1bGVzLkx5bnhUZXh0SW5mb01vZHVsZTtcbiAgICB9XG4gICAgaWYgKHRoaXMuX3RleHRJbmZvTW9kdWxlICYmIHRoaXMuX3RleHRJbmZvTW9kdWxlLmdldFRleHRJbmZvKSB7XG4gICAgICByZXR1cm4gdGhpcy5fdGV4dEluZm9Nb2R1bGUuZ2V0VGV4dEluZm8ocGFyYW0sIG9wdGlvbnMpO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4ge1xuICAgICAgICB3aWR0aDogcGFyYW0ubGVuZ3RoLFxuICAgICAgfTtcbiAgICB9XG4gIH07XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuZXhwb3J0IGNsYXNzIEV4cG9zdXJlTWFuYWdlciB7XG4gIHByaXZhdGUgcmVhZG9ubHkgX25hdGl2ZU1vZHVsZXM6IGFueTtcbiAgcHJpdmF0ZSByZWFkb25seSBfZXhwb3N1cmVNb2R1bGU6IGFueTtcblxuICBjb25zdHJ1Y3RvcihuYXRpdmVNb2R1bGVzOiBvYmplY3QpIHtcbiAgICB0aGlzLl9uYXRpdmVNb2R1bGVzID0gbmF0aXZlTW9kdWxlcztcbiAgICB0aGlzLl9leHBvc3VyZU1vZHVsZSA9IHRoaXMuX25hdGl2ZU1vZHVsZXMuTHlueEV4cG9zdXJlTW9kdWxlO1xuICB9XG5cbiAgcmVzdW1lRXhwb3N1cmUgPSAoKTogdm9pZCA9PiB7XG4gICAgdGhpcy5fZXhwb3N1cmVNb2R1bGUucmVzdW1lRXhwb3N1cmUoKTtcbiAgfTtcblxuICBzdG9wRXhwb3N1cmUgPSAob3B0aW9ucz86IHsgc2VuZEV2ZW50PzogYm9vbGVhbiB9KTogdm9pZCA9PiB7XG4gICAgdGhpcy5fZXhwb3N1cmVNb2R1bGUuc3RvcEV4cG9zdXJlKG9wdGlvbnMpO1xuICB9O1xuXG4gIHNldE9ic2VydmVyRnJhbWVSYXRlID0gKG9wdGlvbnM/OiB7XG4gICAgZm9yUGFnZVJlY3Q/OiBudW1iZXI7XG4gICAgZm9yRXhwb3N1cmVDaGVjaz86IG51bWJlcjtcbiAgfSk6IHZvaWQgPT4ge1xuICAgIHRoaXMuX2V4cG9zdXJlTW9kdWxlLnNldE9ic2VydmVyRnJhbWVSYXRlKG9wdGlvbnMpO1xuICB9O1xufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IEludGVyc2VjdGlvbk9ic2VydmVyIGFzIElJbnRlcnNlY3Rpb25PYnNlcnZlciB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcblxuZXhwb3J0IGludGVyZmFjZSBJbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZSB7XG4gIGNyZWF0ZUludGVyc2VjdGlvbk9ic2VydmVyOiBGdW5jdGlvbjtcbiAgcmVsYXRpdmVUbzogRnVuY3Rpb247XG4gIHJlbGF0aXZlVG9WaWV3cG9ydDogRnVuY3Rpb247XG4gIHJlbGF0aXZlVG9TY3JlZW46IEZ1bmN0aW9uO1xuICBvYnNlcnZlOiBGdW5jdGlvbjtcbiAgZGlzY29ubmVjdDogRnVuY3Rpb247XG59XG5cbmNsYXNzIEludGVyc2VjdGlvbk9ic2VydmF0aW9uVGFyZ2V0IHtcbiAgcHJpdmF0ZSByZWFkb25seSBfc2VsZWN0b3I6IHN0cmluZztcbiAgcHJpdmF0ZSByZWFkb25seSBfY2FsbGJhY2s6IEZ1bmN0aW9uO1xuXG4gIGNvbnN0cnVjdG9yKHNlbGVjdG9yOiBzdHJpbmcsIGNhbGxiYWNrOiBGdW5jdGlvbikge1xuICAgIHRoaXMuX3NlbGVjdG9yID0gc2VsZWN0b3I7XG4gICAgdGhpcy5fY2FsbGJhY2sgPSBjYWxsYmFjaztcbiAgfVxuXG4gIGludm9rZUNhbGxiYWNrKGRhdGE6IG9iamVjdCk6IHZvaWQge1xuICAgIHRoaXMuX2NhbGxiYWNrKGRhdGEpO1xuICB9XG59XG5cbmV4cG9ydCBjbGFzcyBJbnRlcnNlY3Rpb25PYnNlcnZlciBpbXBsZW1lbnRzIElJbnRlcnNlY3Rpb25PYnNlcnZlciB7XG4gIHByaXZhdGUgcmVhZG9ubHkgX2lkOiBudW1iZXI7XG4gIHByaXZhdGUgcmVhZG9ubHkgX2ludGVyc2VjdGlvbk9ic2VydmVyTW9kdWxlOiBJbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZTtcbiAgcHJpdmF0ZSByZWFkb25seSBfbWFuYWdlcjogSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyO1xuICBwcml2YXRlIHJlYWRvbmx5IF9vYnNlcnZhdGlvblRhcmdldHM6IEludGVyc2VjdGlvbk9ic2VydmF0aW9uVGFyZ2V0W107XG4gIHByaXZhdGUgcmVhZG9ubHkgX2RlZmF1bHRNYXJnaW5zOiBvYmplY3Q7XG5cbiAgY29uc3RydWN0b3IoXG4gICAgaWQ6IG51bWJlcixcbiAgICBpbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZTogSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUsXG4gICAgbWFuYWdlcjogSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyXG4gICkge1xuICAgIHRoaXMuX2lkID0gaWQ7XG4gICAgdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUgPSBpbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZTtcbiAgICB0aGlzLl9tYW5hZ2VyID0gbWFuYWdlcjtcbiAgICB0aGlzLl9vYnNlcnZhdGlvblRhcmdldHMgPSBbXTtcbiAgICB0aGlzLl9kZWZhdWx0TWFyZ2lucyA9IHtcbiAgICAgIGxlZnQ6IDAsXG4gICAgICByaWdodDogMCxcbiAgICAgIHRvcDogMCxcbiAgICAgIGJvdHRvbTogMCxcbiAgICB9O1xuICB9XG5cbiAgcmVsYXRpdmVUbyhzZWxlY3Rvcjogc3RyaW5nLCBtYXJnaW5zPzoge30pOiBJbnRlcnNlY3Rpb25PYnNlcnZlciB7XG4gICAgdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUucmVsYXRpdmVUbyhcbiAgICAgIHRoaXMuX2lkLFxuICAgICAgc2VsZWN0b3IsXG4gICAgICBtYXJnaW5zIHx8IHRoaXMuX2RlZmF1bHRNYXJnaW5zXG4gICAgKTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIHJlbGF0aXZlVG9WaWV3cG9ydChtYXJnaW5zPzoge30pOiBJbnRlcnNlY3Rpb25PYnNlcnZlciB7XG4gICAgdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUucmVsYXRpdmVUb1ZpZXdwb3J0KFxuICAgICAgdGhpcy5faWQsXG4gICAgICBtYXJnaW5zIHx8IHRoaXMuX2RlZmF1bHRNYXJnaW5zXG4gICAgKTtcbiAgICByZXR1cm4gdGhpcztcbiAgfVxuXG4gIHJlbGF0aXZlVG9TY3JlZW4obWFyZ2lucz86IHt9KTogSW50ZXJzZWN0aW9uT2JzZXJ2ZXIge1xuICAgIHRoaXMuX2ludGVyc2VjdGlvbk9ic2VydmVyTW9kdWxlLnJlbGF0aXZlVG9TY3JlZW4oXG4gICAgICB0aGlzLl9pZCxcbiAgICAgIG1hcmdpbnMgfHwgdGhpcy5fZGVmYXVsdE1hcmdpbnNcbiAgICApO1xuICAgIHJldHVybiB0aGlzO1xuICB9XG5cbiAgb2JzZXJ2ZShzZWxlY3Rvcjogc3RyaW5nLCBjYWxsYmFjazogRnVuY3Rpb24pOiB2b2lkIHtcbiAgICB0aGlzLl9vYnNlcnZhdGlvblRhcmdldHMucHVzaChcbiAgICAgIG5ldyBJbnRlcnNlY3Rpb25PYnNlcnZhdGlvblRhcmdldChzZWxlY3RvciwgY2FsbGJhY2spXG4gICAgKTtcbiAgICB0aGlzLl9pbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZS5vYnNlcnZlKFxuICAgICAgdGhpcy5faWQsXG4gICAgICBzZWxlY3RvcixcbiAgICAgIHRoaXMuX29ic2VydmF0aW9uVGFyZ2V0cy5sZW5ndGggLSAxXG4gICAgKTtcbiAgfVxuXG4gIGRpc2Nvbm5lY3QoKTogdm9pZCB7XG4gICAgdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUuZGlzY29ubmVjdCh0aGlzLl9pZCk7XG4gICAgdGhpcy5fbWFuYWdlci5yZW1vdmVPYnNlcnZlcih0aGlzLl9pZCk7XG4gIH1cblxuICBpbnZva2VDYWxsYmFjayhjYWxsYmFja0lkOiBudW1iZXIsIGRhdGE6IG9iamVjdCk6IHZvaWQge1xuICAgIGlmIChjYWxsYmFja0lkIDwgdGhpcy5fb2JzZXJ2YXRpb25UYXJnZXRzLmxlbmd0aCkge1xuICAgICAgdGhpcy5fb2JzZXJ2YXRpb25UYXJnZXRzW2NhbGxiYWNrSWRdLmludm9rZUNhbGxiYWNrKGRhdGEpO1xuICAgIH1cbiAgfVxufVxuXG5leHBvcnQgY2xhc3MgSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyIHtcbiAgcHJpdmF0ZSByZWFkb25seSBfbmF0aXZlTW9kdWxlczogb2JqZWN0O1xuICBwcml2YXRlIF9vYnNlcnZlcklkOiBudW1iZXI7XG4gIHByaXZhdGUgX29ic2VydmVyczogb2JqZWN0O1xuICBwcml2YXRlIHJlYWRvbmx5IF9kZWZhdWx0T3B0aW9uczogb2JqZWN0O1xuXG4gIGNvbnN0cnVjdG9yKG5hdGl2ZU1vZHVsZXM6IG9iamVjdCkge1xuICAgIHRoaXMuX25hdGl2ZU1vZHVsZXMgPSBuYXRpdmVNb2R1bGVzO1xuICAgIHRoaXMuX29ic2VydmVySWQgPSAwO1xuICAgIHRoaXMuX29ic2VydmVycyA9IHt9O1xuICAgIHRoaXMuX2RlZmF1bHRPcHRpb25zID0ge1xuICAgICAgdGhyZXNob2xkczogWzBdLFxuICAgICAgaW5pdGlhbFJhdGlvOiAwLFxuICAgICAgb2JzZXJ2ZUFsbDogZmFsc2UsXG4gICAgfTtcbiAgfVxuXG4gIGNyZWF0ZUludGVyc2VjdGlvbk9ic2VydmVyKFxuICAgIGNvbXBvbmVudElkOiBzdHJpbmcsXG4gICAgb3B0aW9ucz86IG9iamVjdFxuICApOiBJbnRlcnNlY3Rpb25PYnNlcnZlciB7XG4gICAgbGV0IGludGVyc2VjdGlvbk9ic2VydmVyTW9kdWxlID0gdGhpcy5fbmF0aXZlTW9kdWxlc1tcbiAgICAgICdJbnRlcnNlY3Rpb25PYnNlcnZlck1vZHVsZSdcbiAgICBdO1xuICAgIGNvbnN0IG9ic2VydmVyID0gbmV3IEludGVyc2VjdGlvbk9ic2VydmVyKFxuICAgICAgdGhpcy5fb2JzZXJ2ZXJJZCxcbiAgICAgIGludGVyc2VjdGlvbk9ic2VydmVyTW9kdWxlLFxuICAgICAgdGhpc1xuICAgICk7XG4gICAgdGhpcy5fb2JzZXJ2ZXJzW3RoaXMuX29ic2VydmVySWRdID0gb2JzZXJ2ZXI7XG4gICAgaW50ZXJzZWN0aW9uT2JzZXJ2ZXJNb2R1bGUuY3JlYXRlSW50ZXJzZWN0aW9uT2JzZXJ2ZXIoXG4gICAgICB0aGlzLl9vYnNlcnZlcklkLFxuICAgICAgY29tcG9uZW50SWQsXG4gICAgICBvcHRpb25zIHx8IHRoaXMuX2RlZmF1bHRPcHRpb25zXG4gICAgKTtcbiAgICB0aGlzLl9vYnNlcnZlcklkKys7XG4gICAgcmV0dXJuIG9ic2VydmVyO1xuICB9XG5cbiAgZ2V0T2JzZXJ2ZXIob2JzZXJ2ZXJJZDogbnVtYmVyKTogSW50ZXJzZWN0aW9uT2JzZXJ2ZXIge1xuICAgIHJldHVybiB0aGlzLl9vYnNlcnZlcnNbb2JzZXJ2ZXJJZF07XG4gIH1cblxuICByZW1vdmVPYnNlcnZlcihvYnNlcnZlcklkOiBudW1iZXIpOiB2b2lkIHtcbiAgICB0aGlzLl9vYnNlcnZlcnNbb2JzZXJ2ZXJJZF0gPSBudWxsO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IEV2ZW50RW1pdHRlciBmcm9tICcuLi9ldmVudCc7XG5pbXBvcnQge1xuICBQZXJmb3JtYW5jZU9ic2VydmVyIGFzIElQZXJmb3JtYW5jZU9ic2VydmVyLFxuICBQZXJmb3JtYW5jZUNhbGxiYWNrLFxuICBQZXJmb3JtYW5jZUVudHJ5LFxufSBmcm9tICdAbHlueC1qcy90eXBlcyc7XG5cbmNvbnN0IExpc3RlbmVyS2V5cyA9IHtcbiAgb25QZXJmb3JtYW5jZTogJ2x5bngucGVyZm9ybWFuY2Uub25QZXJmb3JtYW5jZUV2ZW50Jyxcbn07XG5cbmV4cG9ydCBjbGFzcyBQZXJmb3JtYW5jZU9ic2VydmVyIGltcGxlbWVudHMgSVBlcmZvcm1hbmNlT2JzZXJ2ZXIge1xuICBfZW1pdHRlcjogRXZlbnRFbWl0dGVyO1xuICBfb2JzZXJ2ZWROYW1lczogc3RyaW5nW107XG4gIF9vblBlcmZvcm1hbmNlOiBQZXJmb3JtYW5jZUNhbGxiYWNrO1xuICBjb25zdHJ1Y3RvcihlbWl0dGVyOiBFdmVudEVtaXR0ZXIsIGNhbGxiYWNrOiBQZXJmb3JtYW5jZUNhbGxiYWNrKSB7XG4gICAgdGhpcy5fZW1pdHRlciA9IGVtaXR0ZXI7XG4gICAgdGhpcy5fb25QZXJmb3JtYW5jZSA9IGNhbGxiYWNrO1xuICAgIHRoaXMuX29ic2VydmVkTmFtZXMgPSBbXTtcbiAgfVxuXG4gIG9ic2VydmUobmFtZXM6IHN0cmluZ1tdKTogdm9pZCB7XG4gICAgLy8gVGhlIHByZXZpb3VzIG9ic2VydmUgbXVzdCBiZSBjbG9zZWQgdXNpbmcgdGhlIGRpc2Nvbm5lY3QgbWV0aG9kIGJlZm9yZSByZS1vYnNlcnZpbmcuXG4gICAgaWYgKHRoaXMuX29ic2VydmVkTmFtZXMubGVuZ3RoID4gMCkge1xuICAgICAgcmV0dXJuO1xuICAgIH1cblxuICAgIHRoaXMuX29ic2VydmVkTmFtZXMgPSBuYW1lcztcbiAgICB0aGlzLl9lbWl0dGVyLmFkZExpc3RlbmVyKFxuICAgICAgTGlzdGVuZXJLZXlzLm9uUGVyZm9ybWFuY2UsXG4gICAgICB0aGlzLm9uUGVyZm9ybWFuY2VFdmVudC5iaW5kKHRoaXMpXG4gICAgKTtcbiAgfVxuXG4gIGRpc2Nvbm5lY3QoKTogdm9pZCB7XG4gICAgdGhpcy5fb2JzZXJ2ZWROYW1lcyA9IFtdO1xuICAgIHRoaXMuX2VtaXR0ZXIucmVtb3ZlTGlzdGVuZXIoXG4gICAgICBMaXN0ZW5lcktleXMub25QZXJmb3JtYW5jZSxcbiAgICAgIHRoaXMub25QZXJmb3JtYW5jZUV2ZW50LmJpbmQodGhpcylcbiAgICApO1xuICB9XG5cbiAgb25QZXJmb3JtYW5jZUV2ZW50KGVudHJ5OiBQZXJmb3JtYW5jZUVudHJ5KTogdm9pZCB7XG4gICAgaWYgKHRoaXMuX29ic2VydmVkTmFtZXMubGVuZ3RoID09PSAwKSB7XG4gICAgICByZXR1cm47XG4gICAgfVxuXG4gICAgbGV0IGVudHJ5TmFtZSA9IGVudHJ5LmVudHJ5VHlwZSArICcuJyArIGVudHJ5Lm5hbWU7XG4gICAgaWYgKFxuICAgICAgdGhpcy5fb2JzZXJ2ZWROYW1lcy5pbmNsdWRlcyhlbnRyeU5hbWUpIHx8XG4gICAgICB0aGlzLl9vYnNlcnZlZE5hbWVzLmluY2x1ZGVzKGVudHJ5LmVudHJ5VHlwZSlcbiAgICApIHtcbiAgICAgIHRoaXMuX29uUGVyZm9ybWFuY2UoZW50cnkpO1xuICAgIH1cbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCBFdmVudEVtaXR0ZXIgZnJvbSAnLi4vZXZlbnQnO1xuaW1wb3J0IHtcbiAgUGVyZm9ybWFuY2UgYXMgSVBlcmZvcm1hbmNlLFxuICBUaW1pbmdMaXN0ZW5lcixcbiAgUGVyZm9ybWFuY2VDYWxsYmFjayxcbn0gZnJvbSAnQGx5bngtanMvdHlwZXMnO1xuaW1wb3J0IHsgTmF0aXZlQXBwIH0gZnJvbSAnLi4vLi4vYXBwJztcbmltcG9ydCB7IFRyYWNlT3B0aW9uIH0gZnJvbSAnQGx5bngtanMvdHlwZXMvdHlwZXMvY29tbW9uL3BlcmZvcm1hbmNlJztcbmltcG9ydCB7IFBlcmZvcm1hbmNlT2JzZXJ2ZXIgfSBmcm9tICcuL3BlcmZvcm1hbmNlT2JzZXJ2ZXInO1xuXG5jb25zdCBMaXN0ZW5lcktleXMgPSB7XG4gIG9uU2V0dXA6ICdseW54LnBlcmZvcm1hbmNlLnRpbWluZy5vblNldHVwJyxcbiAgb25VcGRhdGU6ICdseW54LnBlcmZvcm1hbmNlLnRpbWluZy5vblVwZGF0ZScsXG59O1xuXG5leHBvcnQgaW50ZXJmYWNlIFBpcGVsaW5lT3B0aW9ucyB7XG4gIHBpcGVsaW5lSUQ6IHN0cmluZztcbiAgcGlwZWxpbmVPcmlnaW46IHN0cmluZzsgLy8gVGhlIG9yaWdpbiBvZiB0aGUgcGlwZWxpbmVcbiAgbmVlZFRpbWVzdGFtcHM6IGJvb2xlYW47XG4gIGRzbDogc3RyaW5nO1xuICBzdGFnZTogc3RyaW5nO1xufVxuXG5leHBvcnQgZGVmYXVsdCBjbGFzcyBQZXJmb3JtYW5jZSBpbXBsZW1lbnRzIElQZXJmb3JtYW5jZSB7XG4gIF9lbWl0dGVyOiBFdmVudEVtaXR0ZXI7XG4gIF9nZW5lcmF0ZVBpcGVsaW5lT3B0aW9uczogKCkgPT4gUGlwZWxpbmVPcHRpb25zO1xuICBfb25QaXBlbGluZVN0YXJ0OiAoXG4gICAgcGlwZWxpbmVfaWQ6IHN0cmluZyxcbiAgICBwaXBlbGluZV9vcHRpb25zPzogUGlwZWxpbmVPcHRpb25zXG4gICkgPT4gdm9pZDtcbiAgX21hcmtUaW1pbmc6IChwaXBlbGluZV9pZDogc3RyaW5nLCB0aW1pbmdfa2V5OiBzdHJpbmcpID0+IHZvaWQ7XG4gIF9wcm9maWxlU3RhcnQ6ICh0cmFjZU5hbWU6IHN0cmluZywgb3B0aW9uPzogVHJhY2VPcHRpb24pID0+IHZvaWQ7XG4gIF9wcm9maWxlRW5kOiAob3B0aW9uPzogVHJhY2VPcHRpb24pID0+IHZvaWQ7XG4gIF9wcm9maWxlTWFyazogKHRyYWNlTmFtZTogc3RyaW5nLCBvcHRpb24/OiBUcmFjZU9wdGlvbikgPT4gdm9pZDtcbiAgX3Byb2ZpbGVGbG93SWQ6ICgpID0+IG51bWJlcjtcbiAgX2lzUHJvZmlsZVJlY29yZGluZzogKCkgPT4gYm9vbGVhbjtcbiAgX2JpbmRQaXBlbGluZUlkV2l0aFRpbWluZ0ZsYWc6IChcbiAgICBwaXBlbGluZV9pZDogc3RyaW5nLFxuICAgIHRpbWluZ19mbGFnOiBzdHJpbmdcbiAgKSA9PiB2b2lkO1xuICBjb25zdHJ1Y3RvcihlbWl0dGVyOiBFdmVudEVtaXR0ZXIsIG5hdGl2ZUFwcDogTmF0aXZlQXBwKSB7XG4gICAgdGhpcy5fZW1pdHRlciA9IGVtaXR0ZXI7XG4gICAgdGhpcy5fZ2VuZXJhdGVQaXBlbGluZU9wdGlvbnMgPSBuYXRpdmVBcHAuZ2VuZXJhdGVQaXBlbGluZU9wdGlvbnM7XG4gICAgdGhpcy5fb25QaXBlbGluZVN0YXJ0ID0gbmF0aXZlQXBwLm9uUGlwZWxpbmVTdGFydDtcbiAgICB0aGlzLl9tYXJrVGltaW5nID0gbmF0aXZlQXBwLm1hcmtQaXBlbGluZVRpbWluZztcbiAgICB0aGlzLl9wcm9maWxlU3RhcnQgPSBuYXRpdmVBcHAucHJvZmlsZVN0YXJ0O1xuICAgIHRoaXMuX3Byb2ZpbGVFbmQgPSBuYXRpdmVBcHAucHJvZmlsZUVuZDtcbiAgICB0aGlzLl9wcm9maWxlTWFyayA9IG5hdGl2ZUFwcC5wcm9maWxlTWFyaztcbiAgICB0aGlzLl9wcm9maWxlRmxvd0lkID0gbmF0aXZlQXBwLnByb2ZpbGVGbG93SWQ7XG4gICAgdGhpcy5faXNQcm9maWxlUmVjb3JkaW5nID0gbmF0aXZlQXBwLmlzUHJvZmlsZVJlY29yZGluZztcbiAgICB0aGlzLl9iaW5kUGlwZWxpbmVJZFdpdGhUaW1pbmdGbGFnID0gbmF0aXZlQXBwLmJpbmRQaXBlbGluZUlkV2l0aFRpbWluZ0ZsYWc7XG4gIH1cblxuICBwcm9maWxlU3RhcnQodHJhY2VOYW1lOiBzdHJpbmcsIG9wdGlvbj86IFRyYWNlT3B0aW9uKSB7XG4gICAgdGhpcy5fcHJvZmlsZVN0YXJ0KHRyYWNlTmFtZSwgb3B0aW9uKTtcbiAgfVxuXG4gIHByb2ZpbGVFbmQoKSB7XG4gICAgdGhpcy5fcHJvZmlsZUVuZCgpO1xuICB9XG5cbiAgcHJvZmlsZU1hcmsodHJhY2VOYW1lOiBzdHJpbmcsIG9wdGlvbj86IFRyYWNlT3B0aW9uKSB7XG4gICAgdGhpcy5fcHJvZmlsZU1hcmsodHJhY2VOYW1lLCBvcHRpb24pO1xuICB9XG5cbiAgcHJvZmlsZUZsb3dJZCgpIHtcbiAgICByZXR1cm4gdGhpcy5fcHJvZmlsZUZsb3dJZCgpO1xuICB9XG5cbiAgY3JlYXRlT2JzZXJ2ZXIoY2FsbGJhY2s6IFBlcmZvcm1hbmNlQ2FsbGJhY2spOiBQZXJmb3JtYW5jZU9ic2VydmVyIHtcbiAgICByZXR1cm4gbmV3IFBlcmZvcm1hbmNlT2JzZXJ2ZXIodGhpcy5fZW1pdHRlciwgY2FsbGJhY2spO1xuICB9XG5cbiAgaXNQcm9maWxlUmVjb3JkaW5nKCkge1xuICAgIHJldHVybiB0aGlzLl9pc1Byb2ZpbGVSZWNvcmRpbmcoKTtcbiAgfVxuXG4gIGFkZFRpbWluZ0xpc3RlbmVyKGxpc3RlbmVyOiBUaW1pbmdMaXN0ZW5lcik6IHZvaWQge1xuICAgIHRoaXMuX2VtaXR0ZXIuYWRkTGlzdGVuZXIoTGlzdGVuZXJLZXlzLm9uU2V0dXAsIGxpc3RlbmVyLm9uU2V0dXAsIGxpc3RlbmVyKTtcbiAgICB0aGlzLl9lbWl0dGVyLmFkZExpc3RlbmVyKFxuICAgICAgTGlzdGVuZXJLZXlzLm9uVXBkYXRlLFxuICAgICAgbGlzdGVuZXIub25VcGRhdGUsXG4gICAgICBsaXN0ZW5lclxuICAgICk7XG4gIH1cblxuICByZW1vdmVUaW1pbmdMaXN0ZW5lcihsaXN0ZW5lcjogVGltaW5nTGlzdGVuZXIpIHtcbiAgICB0aGlzLl9lbWl0dGVyLnJlbW92ZUxpc3RlbmVyKExpc3RlbmVyS2V5cy5vblNldHVwLCBsaXN0ZW5lci5vblNldHVwKTtcbiAgICB0aGlzLl9lbWl0dGVyLnJlbW92ZUxpc3RlbmVyKExpc3RlbmVyS2V5cy5vblVwZGF0ZSwgbGlzdGVuZXIub25VcGRhdGUpO1xuICB9XG5cbiAgcmVtb3ZlQWxsVGltaW5nTGlzdGVuZXIoKSB7XG4gICAgdGhpcy5fZW1pdHRlci5yZW1vdmVBbGxMaXN0ZW5lcnMoTGlzdGVuZXJLZXlzLm9uU2V0dXApO1xuICAgIHRoaXMuX2VtaXR0ZXIucmVtb3ZlQWxsTGlzdGVuZXJzKExpc3RlbmVyS2V5cy5vblVwZGF0ZSk7XG4gIH1cbiAgX2luaXRpYWxpemVBbmRTdGFydFBpcGVsaW5lKCk6IFBpcGVsaW5lT3B0aW9ucyB7XG4gICAgY29uc3QgcGlwZWxpbmVPcHRpb25zID0gdGhpcy5fZ2VuZXJhdGVQaXBlbGluZU9wdGlvbnMoKTtcbiAgICBpZiAocGlwZWxpbmVPcHRpb25zKSB7XG4gICAgICB0aGlzLl9vblBpcGVsaW5lU3RhcnQocGlwZWxpbmVPcHRpb25zLnBpcGVsaW5lSUQpO1xuICAgIH1cbiAgICByZXR1cm4gcGlwZWxpbmVPcHRpb25zO1xuICB9XG4gIF9jaGVja0FuZEJpbmRUaW1pbmdGbGFnKFxuICAgIHBpcGVsaW5lT3B0aW9uczogUGlwZWxpbmVPcHRpb25zLFxuICAgIGRhdGE6IFJlY29yZDxzdHJpbmcsIHVua25vd24+XG4gICkge1xuICAgIGlmICghcGlwZWxpbmVPcHRpb25zKSB7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIGNvbnN0IFBlcmZvcm1hbmNlVGltaW5nRmxhZyA9ICdfX2x5bnhfdGltaW5nX2ZsYWcnO1xuICAgIGlmIChkYXRhW1BlcmZvcm1hbmNlVGltaW5nRmxhZ10pIHtcbiAgICAgIHRoaXMuX2JpbmRQaXBlbGluZUlkV2l0aFRpbWluZ0ZsYWcoXG4gICAgICAgIHBpcGVsaW5lT3B0aW9ucy5waXBlbGluZUlELFxuICAgICAgICBkYXRhW1BlcmZvcm1hbmNlVGltaW5nRmxhZ10gYXMgc3RyaW5nXG4gICAgICApO1xuICAgICAgdGhpcy5fbWFya1RpbWluZyhwaXBlbGluZU9wdGlvbnMucGlwZWxpbmVJRCwgJ3VwZGF0ZV9zZXRfc3RhdGVfdHJpZ2dlcicpO1xuICAgICAgcGlwZWxpbmVPcHRpb25zLm5lZWRUaW1lc3RhbXBzID0gdHJ1ZTtcbiAgICB9XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgUGVyZm9ybWFuY2UgZnJvbSAnLi9wZXJmb3JtYW5jZSc7XG5leHBvcnQgZGVmYXVsdCBQZXJmb3JtYW5jZTtcbmV4cG9ydCAqIGZyb20gJy4vcGVyZm9ybWFuY2UnO1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCBuYXRpdmVHbG9iYWwgZnJvbSAnLi9uYXRpdmVHbG9iYWwnO1xuZXhwb3J0IGRlZmF1bHQgbmF0aXZlR2xvYmFsLkx5bnhKU0JJO1xuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbi8vIENhY2hlIGFjY2VzcyB0byBmdW5jdGlvbnMgb2YgdGhlIHRhcmdldCBvYmplY3QuXG4vL1xuLy8gV2hlbiBhIGZ1bmN0aW9uIG9uIHRhcmdldCBvYmogaXMgYWNjZXNzZWQgZm9yIHRoZSBmaXJzdCB0aW1lLFxuLy8gdGhlIHByb3h5IG9idGFpbnMgdGhlIGZ1bmN0aW9uIG9iamVjdCBhbmQgc2F2ZXMgaXQsXG4vLyBhbmQgcmV0dXJucyB0aGUgY2FjaGVkIGZ1bmN0aW9uIG9iamVjdCBkaXJlY3RseSBkdXJpbmcgc3Vic2VxdWVudCBhY2Nlc3Ncbi8vIHdpdGhvdXQgYWNjZXNzaW5nIGFnYWluLlxuZXhwb3J0IGNsYXNzIENhY2hlZEZ1bmN0aW9uUHJveHk8VD4ge1xuICBwcml2YXRlIF9jYWNoZWRGdW5jdGlvbnM6IFJlY29yZDxzdHJpbmcsIEZ1bmN0aW9uPiA9IHt9O1xuXG4gIHN0YXRpYyBjcmVhdGU8VD4ob2JqOiBUKTogVCB7XG4gICAgcmV0dXJuIG5ldyBDYWNoZWRGdW5jdGlvblByb3h5KG9iaikgYXMgYW55O1xuICB9XG5cbiAgY29uc3RydWN0b3Iob2JqOiBUKSB7XG4gICAgZm9yIChjb25zdCBrZXkgaW4gb2JqKSB7XG4gICAgICBPYmplY3QuZGVmaW5lUHJvcGVydHkodGhpcywga2V5LCB7XG4gICAgICAgIGdldCgpIHtcbiAgICAgICAgICBpZiAodGhpcy5fY2FjaGVkRnVuY3Rpb25zW2tleV0pIHtcbiAgICAgICAgICAgIHJldHVybiB0aGlzLl9jYWNoZWRGdW5jdGlvbnNba2V5XTtcbiAgICAgICAgICB9XG4gICAgICAgICAgY29uc3QgdmFsdWUgPSBvYmpba2V5XTtcbiAgICAgICAgICBpZiAodHlwZW9mIHZhbHVlID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgICAgICB0aGlzLl9jYWNoZWRGdW5jdGlvbnNba2V5XSA9IHZhbHVlO1xuICAgICAgICAgIH1cbiAgICAgICAgICByZXR1cm4gdmFsdWU7XG4gICAgICAgIH0sXG4gICAgICB9KTtcbiAgICB9XG4gIH1cbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQgeyBMeW54Q2xlYXJUaW1lb3V0LCBMeW54U2V0VGltZW91dCB9IGZyb20gJ0BseW54LWpzL3R5cGVzJztcbmltcG9ydCBuYXRpdmVHbG9iYWwgZnJvbSAnLi4vY29tbW9uL25hdGl2ZUdsb2JhbCc7XG5cbnR5cGUgbmV4dFRpY2sgPSAoY2FsbGJhY2s6ICgpID0+IHZvaWQpID0+IHZvaWQ7XG5leHBvcnQgZnVuY3Rpb24gZ2V0UHJvbWlzZU1heWJlUG9seWZpbGwoXG4gIHNldFRpbWVvdXQ6IEx5bnhTZXRUaW1lb3V0LFxuICBvblVuaGFuZGxlZCxcbiAgY2xlYXJUaW1lb3V0OiBMeW54Q2xlYXJUaW1lb3V0LFxuICBxdWV1ZU1pY3JvdGFzazogbmV4dFRpY2sgPSB1bmRlZmluZWQsXG4gIGVuYWJsZU1pY3JvdGFza1Byb21pc2VQb2x5ZmlsbDogYm9vbGVhbiA9IGZhbHNlXG4pIHtcbiAgY29uc3QgeyBnZXRQcm9taXNlIH0gPSBuYXRpdmVHbG9iYWw7XG4gIGlmICh0eXBlb2YgZ2V0UHJvbWlzZSA9PT0gJ2Z1bmN0aW9uJykge1xuICAgIGNvbnN0IG5leHRUaWNrID0gZW5hYmxlTWljcm90YXNrUHJvbWlzZVBvbHlmaWxsXG4gICAgICA/IHF1ZXVlTWljcm90YXNrXG4gICAgICA6IChmbjogKCkgPT4gdm9pZCkgPT4gc2V0VGltZW91dChmbiwgMCk7XG4gICAgcmV0dXJuIGdldFByb21pc2UoeyBuZXh0VGljaywgc2V0VGltZW91dCwgb25VbmhhbmRsZWQsIGNsZWFyVGltZW91dCB9KTtcbiAgfSBlbHNlIHtcbiAgICAvLyBUT0RPOiBzaG91bGQgcmVwb3J0IGVycm9yO1xuICAgIHJldHVybiBuYXRpdmVHbG9iYWwuUHJvbWlzZTtcbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI1IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmV4cG9ydCBjbGFzcyBUcmFjZUV2ZW50RGVmIHtcbiAgc3RhdGljIHJlYWRvbmx5IEVYRUNVVEVfTE9BREVEX1NDUklQVCA9ICdleGVjdXRlTG9hZGVkU2NyaXB0Jztcbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuXG5pbXBvcnQge1xuICBBcHBQcm94eVBhcmFtcyxcbiAgQnVuZGxlSW5pdFJldHVybk9iaixcbiAgRW52S2V5LFxuICBMaWZlRXZlbnQsXG4gIGxvYWRDYXJkUGFyYW1zLFxuICBOYXRpdmVBcHAsXG4gIHJlcXVpcmVQYXJhbU9iaixcbn0gZnJvbSAnLi9pbnRlcmZhY2UnO1xuaW1wb3J0IHsgQU1ERmFjdG9yeSwgQU1ETW9kdWxlIH0gZnJvbSAnLi4vY29tbW9uJztcbmltcG9ydCB7IGNyZWF0ZVNoYXJlZENvbnNvbGUsIFNoYXJlZENvbnNvbGUgfSBmcm9tICdAbHlueC1qcy9ydW50aW1lLXNoYXJlZCc7XG5pbXBvcnQge1xuICBSZXBvcnRlcixcbiAgQmFzZUVycm9yLFxuICBJbnRlcm5hbFJ1bnRpbWVFcnJvcixcbiAgTHlueEVycm9yTGV2ZWwsXG4gIFVzZXJSdW50aW1lRXJyb3IsXG59IGZyb20gJy4uL21vZHVsZXMvcmVwb3J0JztcbmltcG9ydCB7IENvbnRleHRQcm94eVR5cGUsIEx5bngsIE5hdGl2ZUx5bnhQcm94eSB9IGZyb20gJy4uL2x5bngnO1xuaW1wb3J0IEV2ZW50RW1pdHRlciwgeyBBb3BNYW5hZ2VyLCBCZWZvcmVQdWJsaXNoRXZlbnQgfSBmcm9tICcuLi9tb2R1bGVzL2V2ZW50JztcbmltcG9ydCB7XG4gIEV4cG9zdXJlTWFuYWdlcixcbiAgSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyLFxuICBOYXRpdmVMeW54VUlNb2R1bGUsXG4gIE5hdGl2ZU1vZHVsZSxcbiAgVGV4dEluZm8sXG4gIFRleHRJbmZvTWFuYWdlcixcbiAgVGV4dE1ldHJpY3MsXG59IGZyb20gJy4uL21vZHVsZXMvbmF0aXZlTW9kdWxlcyc7XG5pbXBvcnQgeyBERUZBVUxUX0VOVFJZLCBTT1VSQ0VfTUFQX1JFTEVBU0VfRVJST1JfTkFNRSB9IGZyb20gJy4uL2NvbW1vbic7XG5pbXBvcnQgbmF0aXZlR2xvYmFsIGZyb20gJy4uL2NvbW1vbi9uYXRpdmVHbG9iYWwnO1xuaW1wb3J0IHtcbiAgQ3JlYXRlSW50ZXJzZWN0aW9uT2JzZXJ2ZXJGdW5jLFxuICBMeW54Q2xlYXJUaW1lb3V0LFxuICBMeW54U2V0VGltZW91dCxcbiAgTWVzc2FnZUV2ZW50LFxufSBmcm9tICdAbHlueC1qcy90eXBlcyc7XG5pbXBvcnQgUGVyZm9ybWFuY2UgZnJvbSAnLi4vbW9kdWxlcy9wZXJmb3JtYW5jZSc7XG5pbXBvcnQgeyByZXBvcnRFcnJvciB9IGZyb20gJy4uL21vZHVsZXMvcmVwb3J0JztcbmltcG9ydCBMeW54SlNCSSBmcm9tICcuLi9jb21tb24vanNiaSc7XG5pbXBvcnQgeyBDYWNoZWRGdW5jdGlvblByb3h5IH0gZnJvbSAnLi4vdXRpbC9jYWNoZWRGdW5jdGlvblByb3h5JztcbmltcG9ydCB7IGdldFByb21pc2VNYXliZVBvbHlmaWxsIH0gZnJvbSAnLi4vdXRpbC9zZXR1cC1wcm9taXNlJztcbmltcG9ydCB7IGNyZWF0ZVJlYWRhYmxlU3RyZWFtQ2xhc3MsIFJlcXVlc3QsIFJlc3BvbnNlIH0gZnJvbSAnLi4vbW9kdWxlcy9mZXRjaCc7XG5pbXBvcnQgeyBNZXNzYWdlRXZlbnRUeXBlIH0gZnJvbSAnLi4vbHlueCc7XG5pbXBvcnQgeyBUcmFjZUV2ZW50RGVmIH0gZnJvbSAnLi4vdXRpbC9UcmFjZUV2ZW50RGVmJztcblxuZXhwb3J0IGFic3RyYWN0IGNsYXNzIEJhc2VBcHA8XG4gIE5hdGl2ZUFwcFByb3h5IGV4dGVuZHMgTmF0aXZlQXBwID0gTmF0aXZlQXBwLFxuICBMeW54SW1wbCBleHRlbmRzIEx5bnggPSBMeW54XG4+IHtcbiAgX25hdGl2ZUFwcDogTmF0aXZlQXBwUHJveHk7XG4gIG5hdGl2ZUFwcElkOiBzdHJpbmc7XG4gIF9wYXJhbXM6IGxvYWRDYXJkUGFyYW1zO1xuICBseW54OiBMeW54SW1wbDtcbiAgbW9kdWxlczogUmVjb3JkPHN0cmluZywgUmVjb3JkPHN0cmluZywgQU1ETW9kdWxlPj47XG4gIHNoYXJlZENvbnNvbGU6IFNoYXJlZENvbnNvbGU7XG4gIGR5bmFtaWNDb21wb25lbnRFeHBvcnRzOiBvYmplY3Q7XG4gIGxvYWRlZER5bmFtaWNDb21wb25lbnRzU2V0OiBTZXQ8c3RyaW5nPjtcbiAgcmVzb2x2ZWRQcm9taXNlOiBQcm9taXNlPHZvaWQ+O1xuXG4gIFJlcG9ydGVyOiBSZXBvcnRlcjtcbiAgX2xhenlDYWxsYWJsZU1vZHVsZXM6IE1hcDxzdHJpbmcsIHVua25vd24+O1xuICBHbG9iYWxFdmVudEVtaXR0ZXI6IEV2ZW50RW1pdHRlcjtcbiAgTmF0aXZlTW9kdWxlczogTmF0aXZlTW9kdWxlO1xuICBMeW54VUlNZXRob2RNb2R1bGU6IE5hdGl2ZUx5bnhVSU1vZHVsZTtcbiAgTHlueFRlc3RNb2R1bGU6IG9iamVjdDtcbiAgTHlueFJlc291cmNlTW9kdWxlOiBvYmplY3Q7XG4gIEx5bnhBY2Nlc3NpYmlsaXR5TW9kdWxlOiBvYmplY3Q7XG4gIEx5bnhTZXRNb2R1bGU6IG9iamVjdDtcblxuICBfYXBpTGlzdDogUmVjb3JkPHN0cmluZywgdW5rbm93bj47XG4gIF9pbnRlcnNlY3Rpb25PYnNlcnZlck1hbmFnZXI6IEludGVyc2VjdGlvbk9ic2VydmVyTWFuYWdlcjtcbiAgX2V4cG9zdXJlTWFuYWdlcjogRXhwb3N1cmVNYW5hZ2VyO1xuICBfdGV4dEluZm9NYW5hZ2VyOiBUZXh0SW5mb01hbmFnZXI7XG4gIF9hb3BNYW5hZ2VyOiBBb3BNYW5hZ2VyO1xuICBiZWZvcmVQdWJsaXNoRXZlbnQ6IEJlZm9yZVB1Ymxpc2hFdmVudDtcblxuICBwZXJmb3JtYW5jZTogUGVyZm9ybWFuY2U7XG5cbiAgc2V0VGltZW91dDogTHlueFNldFRpbWVvdXQ7XG4gIHNldEludGVydmFsOiBMeW54U2V0VGltZW91dDtcbiAgY2xlYXJJbnRlcnZhbDogKGludGVydmFsSWQ6IG51bWJlcikgPT4gdm9pZDtcbiAgY2xlYXJUaW1lb3V0OiAodGltZW91dElkOiBudW1iZXIpID0+IHZvaWQ7XG5cbiAgX2NyZWF0ZVJlYWRhYmxlU3RyZWFtQ2xhc3M6IChcbiAgICBQcm9taXNlOiBQcm9taXNlQ29uc3RydWN0b3JcbiAgKSA9PiBSZXR1cm5UeXBlPHR5cGVvZiBjcmVhdGVSZWFkYWJsZVN0cmVhbUNsYXNzPjtcbiAgX1JlYWRhYmxlU3RyZWFtQ2xhc3M6IFJldHVyblR5cGU8dHlwZW9mIGNyZWF0ZVJlYWRhYmxlU3RyZWFtQ2xhc3M+O1xuXG4gIGRhdGFUeXBlU2V0ID0gbmV3IFNldChbXG4gICAgJ3N0cmluZycsXG4gICAgJ251bWJlcicsXG4gICAgJ2FycmF5JyxcbiAgICAnb2JqZWN0JyxcbiAgICAnYm9vbGVhbicsXG4gICAgJ251bGwnLFxuICAgICdmdW5jdGlvbicsXG4gIF0pO1xuXG4gIC8qKlxuICAgKiBJbnRlcm5hbCBFdmVudCBMaXN0ZW5lclxuICAgKiBAcHJpdmF0ZVxuICAgKi9cbiAgcHJpdmF0ZSBjb250ZXh0UHJveHlUeXBlVG9NZXRob2Q6IHt9O1xuICBwcml2YXRlIHJlbW92ZUludGVybmFsRXZlbnRMaXN0ZW5lcnNDYWxsYmFja3M6ICgoKSA9PiB2b2lkKVtdID0gW107XG5cbiAgY29uc3RydWN0b3IoXG4gICAgb3B0aW9uczogQXBwUHJveHlQYXJhbXM8TmF0aXZlQXBwUHJveHk+LFxuICAgIG90aGVyQXBwPzogQmFzZUFwcCAvKiogU3RhbmRhbG9uZUFwcCAqKi9cbiAgKSB7XG4gICAgdGhpcy5pbml0QmFzZShvcHRpb25zKTtcbiAgICB0aGlzLmluaXRXaXRoUmV1c2VkQXBwKG9wdGlvbnMsIG90aGVyQXBwKTtcbiAgICB0aGlzLmFkZEludGVybmFsRXZlbnRMaXN0ZW5lcnMoKTtcblxuICAgIG5hdGl2ZUdsb2JhbFsnbm90aWZ5UnVudGltZVJlYWR5T25SVCcgKyB0aGlzLm5hdGl2ZUFwcElkXSAmJlxuICAgICAgbmF0aXZlR2xvYmFsWydub3RpZnlSdW50aW1lUmVhZHlPblJUJyArIHRoaXMubmF0aXZlQXBwSWRdKHRoaXMubHlueCk7XG4gIH1cblxuICBwcml2YXRlIGluaXRXaXRoUmV1c2VkQXBwKFxuICAgIG9wdGlvbnM6IEFwcFByb3h5UGFyYW1zPE5hdGl2ZUFwcFByb3h5PixcbiAgICBvdGhlckFwcD86IEJhc2VBcHBcbiAgKSB7XG4gICAgaWYgKG90aGVyQXBwKSB7XG4gICAgICB0aGlzLl9uYXRpdmVBcHAgPSBvdGhlckFwcC5uYXRpdmVBcHAgYXMgTmF0aXZlQXBwUHJveHk7XG4gICAgICB0aGlzLnNoYXJlZENvbnNvbGUgPSBvdGhlckFwcC5zaGFyZWRDb25zb2xlO1xuICAgICAgdGhpcy5keW5hbWljQ29tcG9uZW50RXhwb3J0cyA9IG90aGVyQXBwLmR5bmFtaWNDb21wb25lbnRFeHBvcnRzO1xuICAgICAgdGhpcy5sb2FkZWREeW5hbWljQ29tcG9uZW50c1NldCA9IG90aGVyQXBwLmxvYWRlZER5bmFtaWNDb21wb25lbnRzU2V0O1xuICAgICAgdGhpcy5fYXBpTGlzdCA9IG90aGVyQXBwLl9hcGlMaXN0O1xuICAgICAgdGhpcy5faW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyID0gb3RoZXJBcHAuX2ludGVyc2VjdGlvbk9ic2VydmVyTWFuYWdlcjtcbiAgICAgIHRoaXMuX2V4cG9zdXJlTWFuYWdlciA9IG90aGVyQXBwLl9leHBvc3VyZU1hbmFnZXI7XG4gICAgICB0aGlzLl90ZXh0SW5mb01hbmFnZXIgPSBvdGhlckFwcC5fdGV4dEluZm9NYW5hZ2VyO1xuICAgICAgb3RoZXJBcHAuR2xvYmFsRXZlbnRFbWl0dGVyLnNldENhbGxMeW54U2V0TW9kdWxlKFxuICAgICAgICB0aGlzLl9faW50ZXJuYWxfX2NhbGxMeW54U2V0TW9kdWxlLmJpbmQodGhpcylcbiAgICAgICk7XG4gICAgICB0aGlzLkdsb2JhbEV2ZW50RW1pdHRlciA9IG90aGVyQXBwLkdsb2JhbEV2ZW50RW1pdHRlcjtcbiAgICAgIHRoaXMuX2FvcE1hbmFnZXIgPSBvdGhlckFwcC5fYW9wTWFuYWdlcjtcbiAgICAgIHRoaXMucGVyZm9ybWFuY2UgPSBvdGhlckFwcC5wZXJmb3JtYW5jZTtcbiAgICAgIHRoaXMubW9kdWxlcyA9IG90aGVyQXBwLm1vZHVsZXM7XG4gICAgICB0aGlzLl9sYXp5Q2FsbGFibGVNb2R1bGVzID0gb3RoZXJBcHAuX2xhenlDYWxsYWJsZU1vZHVsZXM7XG4gICAgICBvdGhlckFwcC5seW54LnJlYmluZCgoKSA9PiB0aGlzKTtcbiAgICAgIHRoaXMubHlueCA9IG90aGVyQXBwLmx5bnggYXMgTHlueEltcGw7XG4gICAgICBvdGhlckFwcC5SZXBvcnRlci5yZWJpbmQoKCkgPT4gdGhpcyk7XG4gICAgICB0aGlzLlJlcG9ydGVyID0gb3RoZXJBcHAuUmVwb3J0ZXI7XG4gICAgICB0aGlzLnNldFRpbWVvdXQgPSBvdGhlckFwcC5zZXRUaW1lb3V0O1xuICAgICAgdGhpcy5zZXRJbnRlcnZhbCA9IG90aGVyQXBwLnNldEludGVydmFsO1xuICAgICAgdGhpcy5jbGVhckludGVydmFsID0gb3RoZXJBcHAuY2xlYXJJbnRlcnZhbDtcbiAgICAgIHRoaXMuY2xlYXJUaW1lb3V0ID0gb3RoZXJBcHAuY2xlYXJUaW1lb3V0O1xuICAgICAgdGhpcy5yZXNvbHZlZFByb21pc2UgPSBvdGhlckFwcC5yZXNvbHZlZFByb21pc2U7XG4gICAgICAvLyBmZXRjaCBhcGkgcmVsYXRlZFxuICAgICAgdGhpcy5fY3JlYXRlUmVhZGFibGVTdHJlYW1DbGFzcyA9IG90aGVyQXBwLl9jcmVhdGVSZWFkYWJsZVN0cmVhbUNsYXNzO1xuICAgICAgdGhpcy5fUmVhZGFibGVTdHJlYW1DbGFzcyA9IG90aGVyQXBwLl9SZWFkYWJsZVN0cmVhbUNsYXNzO1xuICAgIH0gZWxzZSB7XG4gICAgICBjb25zdCB7IGx5bnggfSA9IG9wdGlvbnM7XG5cbiAgICAgIHRoaXMuc2V0VGltZW91dCA9IHRoaXMubmF0aXZlQXBwLnNldFRpbWVvdXQ7XG4gICAgICB0aGlzLnNldEludGVydmFsID0gdGhpcy5uYXRpdmVBcHAuc2V0SW50ZXJ2YWw7XG4gICAgICB0aGlzLmNsZWFySW50ZXJ2YWwgPSB0aGlzLm5hdGl2ZUFwcC5jbGVhckludGVydmFsO1xuICAgICAgdGhpcy5jbGVhclRpbWVvdXQgPSB0aGlzLm5hdGl2ZUFwcC5jbGVhclRpbWVvdXQ7XG5cbiAgICAgIHRoaXMubW9kdWxlcyA9IHt9O1xuICAgICAgdGhpcy5fYXBpTGlzdCA9IHt9O1xuICAgICAgdGhpcy5fdGV4dEluZm9NYW5hZ2VyID0gbmV3IFRleHRJbmZvTWFuYWdlcih0aGlzLk5hdGl2ZU1vZHVsZXMpO1xuICAgICAgdGhpcy5zZXR1cEdldFRleHRJbmZvQXBpKCk7XG4gICAgICB0aGlzLl9sYXp5Q2FsbGFibGVNb2R1bGVzID0gbmV3IE1hcCgpO1xuICAgICAgdGhpcy5fbmF0aXZlQXBwID0gQ2FjaGVkRnVuY3Rpb25Qcm94eS5jcmVhdGU8TmF0aXZlQXBwUHJveHk+KFxuICAgICAgICB0aGlzLl9uYXRpdmVBcHBcbiAgICAgICk7XG4gICAgICB0aGlzLnNoYXJlZENvbnNvbGUgPSBjcmVhdGVTaGFyZWRDb25zb2xlKGBydW50aW1lSWQ6JHt0aGlzLm5hdGl2ZUFwcElkfWApO1xuICAgICAgdGhpcy5keW5hbWljQ29tcG9uZW50RXhwb3J0cyA9IHt9O1xuICAgICAgdGhpcy5sb2FkZWREeW5hbWljQ29tcG9uZW50c1NldCA9IG5ldyBTZXQoKTtcbiAgICAgIHRoaXMuX2xhenlDYWxsYWJsZU1vZHVsZXMgPSBuZXcgTWFwKCk7XG5cbiAgICAgIHRoaXMuUmVwb3J0ZXIgPSBuZXcgUmVwb3J0ZXIoXG4gICAgICAgICgpID0+IHRoaXMsXG4gICAgICAgICgpID0+IHRoaXMubmF0aXZlQXBwXG4gICAgICApO1xuXG4gICAgICAvLyBpbml0IGV2ZW50RW1pdHRlclxuICAgICAgdGhpcy5HbG9iYWxFdmVudEVtaXR0ZXIgPSBuZXcgRXZlbnRFbWl0dGVyKFxuICAgICAgICB0aGlzLl9faW50ZXJuYWxfX2NhbGxMeW54U2V0TW9kdWxlLmJpbmQodGhpcylcbiAgICAgICk7XG4gICAgICB0aGlzLl9pbnRlcnNlY3Rpb25PYnNlcnZlck1hbmFnZXIgPSBuZXcgSW50ZXJzZWN0aW9uT2JzZXJ2ZXJNYW5hZ2VyKFxuICAgICAgICB0aGlzLk5hdGl2ZU1vZHVsZXNcbiAgICAgICk7XG5cbiAgICAgIHRoaXMuX2V4cG9zdXJlTWFuYWdlciA9IG5ldyBFeHBvc3VyZU1hbmFnZXIodGhpcy5OYXRpdmVNb2R1bGVzKTtcbiAgICAgIHRoaXMuc2V0dXBFeHBvc3VyZUFwaSgpO1xuICAgICAgdGhpcy5fYW9wTWFuYWdlciA9IG5ldyBBb3BNYW5hZ2VyKCk7XG4gICAgICB0aGlzLmJlZm9yZVB1Ymxpc2hFdmVudCA9IHRoaXMuX2FvcE1hbmFnZXIuX2JlZm9yZVB1Ymxpc2hFdmVudDtcblxuICAgICAgdGhpcy5wZXJmb3JtYW5jZSA9IG5ldyBQZXJmb3JtYW5jZShcbiAgICAgICAgdGhpcy5HbG9iYWxFdmVudEVtaXR0ZXIsXG4gICAgICAgIHRoaXMubmF0aXZlQXBwXG4gICAgICApO1xuXG4gICAgICBjb25zdCBwcm9taXNlQ3RvciA9IHRoaXMuc2V0dXBQcm9taXNlKFxuICAgICAgICB0aGlzLm5hdGl2ZUFwcC5zZXRUaW1lb3V0LFxuICAgICAgICB0aGlzLm5hdGl2ZUFwcC5jbGVhclRpbWVvdXQsXG4gICAgICAgIGx5bnhcbiAgICAgICk7XG5cbiAgICAgIHRoaXMubHlueCA9IHRoaXMuY3JlYXRlTHlueChseW54LCBwcm9taXNlQ3Rvcik7XG4gICAgICB0aGlzLnNldHVwSlNNb2R1bGUoKTtcbiAgICAgIHRoaXMuc2V0dXBJbnRlcnNlY3Rpb25BcGkoKTtcbiAgICAgIHRoaXMuc2V0dXBGZXRjaEFQSShwcm9taXNlQ3Rvcik7XG4gICAgfVxuICB9XG5cbiAgcHJvdGVjdGVkIGluaXRCYXNlKG9wdGlvbnM6IEFwcFByb3h5UGFyYW1zPE5hdGl2ZUFwcFByb3h5Pikge1xuICAgIGNvbnN0IHsgbmF0aXZlQXBwLCBwYXJhbXMgfSA9IG9wdGlvbnM7XG5cbiAgICAvLyBpbml0IGlkICYgbG9hZENhcmRQYXJhbVxuICAgIHRoaXMubmF0aXZlQXBwSWQgPSBuYXRpdmVBcHAuaWQ7XG4gICAgdGhpcy5fcGFyYW1zID0gcGFyYW1zO1xuICAgIHRoaXMuX25hdGl2ZUFwcCA9IG5hdGl2ZUFwcDtcblxuICAgIC8vIGluaXQgbmF0aXZlIE5hdGl2ZU1vZHVsZXNcbiAgICB0aGlzLk5hdGl2ZU1vZHVsZXMgPSBuYXRpdmVBcHAubmF0aXZlTW9kdWxlUHJveHk7XG4gICAgdGhpcy5MeW54VUlNZXRob2RNb2R1bGUgPSBuYXRpdmVBcHAubmF0aXZlTW9kdWxlUHJveHkuTHlueFVJTWV0aG9kTW9kdWxlO1xuICAgIHRoaXMuTHlueFRlc3RNb2R1bGUgPSBuYXRpdmVBcHAubmF0aXZlTW9kdWxlUHJveHkuTHlueFRlc3RNb2R1bGU7XG4gICAgdGhpcy5MeW54UmVzb3VyY2VNb2R1bGUgPSBuYXRpdmVBcHAubmF0aXZlTW9kdWxlUHJveHkuTHlueFJlc291cmNlTW9kdWxlO1xuICAgIHRoaXMuTHlueEFjY2Vzc2liaWxpdHlNb2R1bGUgPVxuICAgICAgbmF0aXZlQXBwLm5hdGl2ZU1vZHVsZVByb3h5Lkx5bnhBY2Nlc3NpYmlsaXR5TW9kdWxlO1xuICAgIHRoaXMuTHlueFNldE1vZHVsZSA9IG5hdGl2ZUFwcC5uYXRpdmVNb2R1bGVQcm94eS5MeW54U2V0TW9kdWxlO1xuICB9XG5cbiAgc3RhdGljIGtEZWZhdWx0U291cmNlTWFwVVJMID0gJ2RlZmF1bHQnO1xuICBzdGF0aWMga0dldFNvdXJjZU1hcFJlbGVhc2VFcnJvck5hbWUgPSBTT1VSQ0VfTUFQX1JFTEVBU0VfRVJST1JfTkFNRTtcbiAgLyoqXG4gICAqIGxlZ2FjeSBzb3VyY2VtYXAgcmVsZWFzZSB1c2UgdXJsIGRlZmF1bHRcbiAgICogdXNlZCBmb3IgYmFja3dhcmQgY29tcGF0aWJpbGl0eVxuICAgKlxuICAgKiBuZXcgdGVtcGxhdGUgc2hvdWxkIHVzZSBzZXRTb3VyY2VNYXBSZWxlYXNlXG4gICAqL1xuICBzZXQgX19zb3VyY2VtYXBfX3JlbGVhc2VfXyhyZWxlYXNlOiBzdHJpbmcpIHtcbiAgICBsZXQgZXJyb3IgPSBuZXcgRXJyb3IoKTtcbiAgICBlcnJvci5uYW1lID0gJ0x5bnhHZXRTb3VyY2VNYXBSZWxlYXNlRXJyb3InO1xuICAgIGVycm9yLm1lc3NhZ2UgPSByZWxlYXNlO1xuICAgIGVycm9yLnN0YWNrID0gYGF0IDxhbm9ueW1vdXM+ICgke0Jhc2VBcHAua0RlZmF1bHRTb3VyY2VNYXBVUkx9OjE6MSlgO1xuICAgIHRoaXMuc2V0U291cmNlTWFwUmVsZWFzZShlcnJvcik7XG4gIH1cblxuICAvKipcbiAgICogU2V0IHNvdXJjZW1hcCByZWxlYXNlIHdpdGggYSBuZXdseSB0aHJvd24gZXJyb3JcbiAgICogQHBhcmFtIHtFcnJvcn0gZXJyb3JcbiAgICogVGhlIGVycm9yIHRocm93biBmcm9tIHRoZSBmaWxlIHRoYXQgd2FudHMgdG8gc2V0IHNvdXJjZW1hcCByZWxlYXNlLlxuICAgKiBUaGUgdG9wIGZyYW1lIG9mIGBlcnJvci5zdGFja2AgKiptdXN0IGJlKiogdGhlIGZpbGVuYW1lLlxuICAgKiBUaGUgYGVycm9yLm5hbWVgICoqbXVzdCBiZSoqIGAnTHlueEdldFNvdXJjZU1hcFJlbGVhc2VFcnJvcidgLlxuICAgKiBUaGUgYGVycm9yLm1lc3NhZ2VgICoqbXVzdCBiZSoqIHRoZSBzb3VyY2VtYXAgcmVsZWFzZS5cbiAgICpcbiAgICogQGV4YW1wbGVcbiAgICogKGZ1bmN0aW9uICgpIHtcbiAgICogICB0cnkge1xuICAgKiAgICAgdGhyb3cgbmV3IEVycm9yKHNvdXJjZW1hcFJlbGVhc2UpO1xuICAgKiAgIH0gY2F0Y2ggKGUpIHtcbiAgICogICAgIGUubmFtZSA9ICdMeW54R2V0U291cmNlTWFwUmVsZWFzZUVycm9yJztcbiAgICogICAgIHR0LnNldFNvdXJjZU1hcFJlbGVhc2UoZSk7XG4gICAqICAgfVxuICAgKiB9KSgpXG4gICAqL1xuICBzZXRTb3VyY2VNYXBSZWxlYXNlID0gKGVycm9yOiBFcnJvcikgPT4ge1xuICAgIHRoaXMuUmVwb3J0ZXIuc2V0U291cmNlTWFwUmVsZWFzZShlcnJvcik7XG4gIH07XG5cbiAgZ2V0U291cmNlTWFwUmVsZWFzZSA9ICh1cmw6IHN0cmluZyk6IHN0cmluZyA9PiB7XG4gICAgcmV0dXJuIHRoaXMuUmVwb3J0ZXIuZ2V0U291cmNlTWFwUmVsZWFzZSh1cmwpO1xuICB9O1xuXG4gIGRlc3Ryb3koKSB7XG4gICAgdGhpcy5fX3JlbW92ZUludGVybmFsRXZlbnRMaXN0ZW5lcnMoKTtcbiAgICB0aGlzLl9uYXRpdmVBcHAgPSBudWxsO1xuICAgIHRoaXMuX3BhcmFtcyA9IG51bGw7XG4gICAgdGhpcy5fbGF6eUNhbGxhYmxlTW9kdWxlcyA9IG51bGw7XG4gICAgdGhpcy5HbG9iYWxFdmVudEVtaXR0ZXIgPSBudWxsO1xuICB9XG5cbiAgcmVnaXN0ZXJNb2R1bGUobmFtZTogc3RyaW5nLCBtb2R1bGU6IG9iamVjdCk6IHZvaWQge1xuICAgIHRoaXMuX2xhenlDYWxsYWJsZU1vZHVsZXNbbmFtZV0gPSBtb2R1bGU7XG4gIH1cblxuICBnZXRKU01vZHVsZTxNb2R1bGUgPSB1bmtub3duPihuYW1lOiBzdHJpbmcpOiBNb2R1bGUge1xuICAgIHJldHVybiB0aGlzLl9sYXp5Q2FsbGFibGVNb2R1bGVzW25hbWVdO1xuICB9XG5cbiAgc2V0dXBKU01vZHVsZSgpIHtcbiAgICB0aGlzLnJlZ2lzdGVyTW9kdWxlKCdHbG9iYWxFdmVudEVtaXR0ZXInLCB0aGlzLkdsb2JhbEV2ZW50RW1pdHRlcik7XG4gICAgdGhpcy5yZWdpc3Rlck1vZHVsZSgnUmVwb3J0ZXInLCB0aGlzLlJlcG9ydGVyKTtcbiAgfVxuXG4gIHNldHVwRmV0Y2hBUEkoUHJvbWlzZTogUHJvbWlzZUNvbnN0cnVjdG9yKSB7XG4gICAgdGhpcy5fY3JlYXRlUmVhZGFibGVTdHJlYW1DbGFzcyA9IGNyZWF0ZVJlYWRhYmxlU3RyZWFtQ2xhc3M7XG4gICAgdGhpcy5fUmVhZGFibGVTdHJlYW1DbGFzcyA9IGNyZWF0ZVJlYWRhYmxlU3RyZWFtQ2xhc3MoUHJvbWlzZSk7XG4gICAgaWYgKCFuYXRpdmVHbG9iYWwuUmVxdWVzdCkge1xuICAgICAgbmF0aXZlR2xvYmFsLlJlcXVlc3QgPSBSZXF1ZXN0O1xuICAgIH1cbiAgICBpZiAoIW5hdGl2ZUdsb2JhbC5SZXNwb25zZSkge1xuICAgICAgbmF0aXZlR2xvYmFsLlJlc3BvbnNlID0gUmVzcG9uc2U7XG4gICAgfVxuICAgIGlmICghbmF0aXZlR2xvYmFsLlJlYWRhYmxlU3RyZWFtKSB7XG4gICAgICBuYXRpdmVHbG9iYWwuUmVhZGFibGVTdHJlYW0gPSB0aGlzLl9SZWFkYWJsZVN0cmVhbUNsYXNzO1xuICAgIH1cbiAgfVxuXG4gIHByaXZhdGUgX19pbnRlcm5hbF9fY2FsbEx5bnhTZXRNb2R1bGUoZnVuY3Rpb25OYW1lOiBzdHJpbmcsIHBheWxvYWQ6IGFueVtdKSB7XG4gICAgY29uc3QgbmF0aXZlRnVuY3Rpb24gPSB0aGlzLkx5bnhTZXRNb2R1bGVbZnVuY3Rpb25OYW1lXTtcbiAgICBpZiAobmF0aXZlRnVuY3Rpb24pIHtcbiAgICAgIEZ1bmN0aW9uLnByb3RvdHlwZS5hcHBseS5jYWxsKG5hdGl2ZUZ1bmN0aW9uLCB1bmRlZmluZWQsIHBheWxvYWQpO1xuICAgIH1cbiAgfVxuXG4gIGdldCBuYXRpdmVBcHAoKTogTmF0aXZlQXBwUHJveHkge1xuICAgIHJldHVybiB0aGlzLl9uYXRpdmVBcHA7XG4gIH1cblxuICBzZXQgbmF0aXZlQXBwKG5hdGl2ZUFwcDogTmF0aXZlQXBwUHJveHkpIHtcbiAgICB0aGlzLl9uYXRpdmVBcHAgPSBuYXRpdmVBcHA7XG4gIH1cblxuICBnZXQgcGFyYW1zKCk6IGxvYWRDYXJkUGFyYW1zIHtcbiAgICByZXR1cm4gdGhpcy5fcGFyYW1zO1xuICB9XG5cbiAgc2V0IGFwaUxpc3QoYXBpOiBvYmplY3QpIHtcbiAgICB0aGlzLl9hcGlMaXN0ID0geyAuLi50aGlzLl9hcGlMaXN0LCAuLi5hcGkgfTtcbiAgfVxuXG4gIHNldHVwSW50ZXJzZWN0aW9uQXBpKCkge1xuICAgIGxldCBzZWxmID0gdGhpcztcbiAgICB0aGlzLl9hcGlMaXN0WydjcmVhdGVJbnRlcnNlY3Rpb25PYnNlcnZlciddID0gZnVuY3Rpb24gKFxuICAgICAgY29tcG9uZW50OiB7IGNvbXBvbmVudElkOiBzdHJpbmcgfSAmIHsgW2tleTogc3RyaW5nXTogYW55IH0sXG4gICAgICBvcHRpb25zPzoge1xuICAgICAgICB0aHJlc2hvbGRzPzogW107XG4gICAgICAgIGluaXRpYWxSYXRpbz86IG51bWJlcjtcbiAgICAgICAgb2JzZXJ2ZUFsbD86IGJvb2xlYW47XG4gICAgICB9XG4gICAgKSB7XG4gICAgICBjb25zdCB7IGNvbXBvbmVudElkID0gJycgfSA9IGNvbXBvbmVudDtcbiAgICAgIHJldHVybiBzZWxmLl9pbnRlcnNlY3Rpb25PYnNlcnZlck1hbmFnZXIuY3JlYXRlSW50ZXJzZWN0aW9uT2JzZXJ2ZXIoXG4gICAgICAgIGNvbXBvbmVudElkLFxuICAgICAgICBvcHRpb25zXG4gICAgICApO1xuICAgIH07XG4gICAgdGhpcy5seW54WydjcmVhdGVJbnRlcnNlY3Rpb25PYnNlcnZlciddID0gdGhpcy5fYXBpTGlzdFtcbiAgICAgICdjcmVhdGVJbnRlcnNlY3Rpb25PYnNlcnZlcidcbiAgICBdIGFzIENyZWF0ZUludGVyc2VjdGlvbk9ic2VydmVyRnVuYztcbiAgfVxuXG4gIG9uSW50ZXJzZWN0aW9uT2JzZXJ2ZXJFdmVudChcbiAgICBvYnNlcnZlcklkOiBudW1iZXIsXG4gICAgY2FsbGJhY2tJZDogbnVtYmVyLFxuICAgIGRhdGE6IFJlY29yZDxhbnksIGFueT5cbiAgKTogdm9pZCB7XG4gICAgY29uc3Qgb2JzZXJ2ZXIgPSB0aGlzLl9pbnRlcnNlY3Rpb25PYnNlcnZlck1hbmFnZXIuZ2V0T2JzZXJ2ZXIob2JzZXJ2ZXJJZCk7XG4gICAgaWYgKG9ic2VydmVyKSB7XG4gICAgICBvYnNlcnZlci5pbnZva2VDYWxsYmFjayhjYWxsYmFja0lkLCBkYXRhKTtcbiAgICB9XG4gIH1cblxuICBzZXR1cEdldFRleHRJbmZvQXBpID0gKCk6IHZvaWQgPT4ge1xuICAgIHRoaXMuX2FwaUxpc3RbJ2dldFRleHRJbmZvJ10gPSAoXG4gICAgICB0ZXh0OiBTdHJpbmcsXG4gICAgICBvcHRpb25zPzogVGV4dEluZm9cbiAgICApOiBUZXh0TWV0cmljcyA9PiB7XG4gICAgICByZXR1cm4gdGhpcy5fdGV4dEluZm9NYW5hZ2VyLmdldFRleHRJbmZvKHRleHQsIG9wdGlvbnMpO1xuICAgIH07XG4gIH07XG5cbiAgc2V0dXBFeHBvc3VyZUFwaSA9ICgpOiB2b2lkID0+IHtcbiAgICB0aGlzLl9hcGlMaXN0WydyZXN1bWVFeHBvc3VyZSddID0gKCk6IHZvaWQgPT4ge1xuICAgICAgdGhpcy5fZXhwb3N1cmVNYW5hZ2VyLnJlc3VtZUV4cG9zdXJlKCk7XG4gICAgfTtcbiAgICB0aGlzLl9hcGlMaXN0WydzdG9wRXhwb3N1cmUnXSA9IChvcHRpb25zPzoge1xuICAgICAgc2VuZEV2ZW50PzogYm9vbGVhbjtcbiAgICB9KTogdm9pZCA9PiB7XG4gICAgICB0aGlzLl9leHBvc3VyZU1hbmFnZXIuc3RvcEV4cG9zdXJlKFxuICAgICAgICBvcHRpb25zID8gb3B0aW9ucyA6IHsgc2VuZEV2ZW50OiB0cnVlIH1cbiAgICAgICk7XG4gICAgfTtcbiAgICB0aGlzLl9hcGlMaXN0WydzZXRPYnNlcnZlckZyYW1lUmF0ZSddID0gKG9wdGlvbnM/OiB7XG4gICAgICBmb3JQYWdlUmVjdD86IG51bWJlcjtcbiAgICAgIGZvckV4cG9zdXJlQ2hlY2s/OiBudW1iZXI7XG4gICAgfSk6IHZvaWQgPT4ge1xuICAgICAgdGhpcy5fZXhwb3N1cmVNYW5hZ2VyLnNldE9ic2VydmVyRnJhbWVSYXRlKFxuICAgICAgICBvcHRpb25zID8gb3B0aW9ucyA6IHsgZm9yUGFnZVJlY3Q6IDIwLCBmb3JFeHBvc3VyZUNoZWNrOiAyMCB9XG4gICAgICApO1xuICAgIH07XG4gIH07XG5cbiAgcmVwb3J0RXJyb3IoZXJyb3I6IEVycm9yKSB7XG4gICAgcmV0dXJuIHRoaXMubHlueC5yZXBvcnRFcnJvcihlcnJvcik7XG4gIH1cblxuICBoYW5kbGVFcnJvcihcbiAgICBlcnJvcjogQmFzZUVycm9yLFxuICAgIG9yaWdpbkVycm9yPzogRXJyb3IsXG4gICAgZXJyb3JMZXZlbD86IEx5bnhFcnJvckxldmVsXG4gICkge1xuICAgIHJlcG9ydEVycm9yKGVycm9yLCB0aGlzLm5hdGl2ZUFwcCwge1xuICAgICAgb3JpZ2luRXJyb3IsXG4gICAgICBnZXRTb3VyY2VNYXBSZWxlYXNlOiB0aGlzLmdldFNvdXJjZU1hcFJlbGVhc2UsXG4gICAgICBlcnJvckxldmVsOiBlcnJvckxldmVsLFxuICAgIH0pO1xuICB9XG5cbiAgaGFuZGxlVXNlckVycm9yKFxuICAgIGVycm9yPzogRXJyb3IsXG4gICAgb3V0ZXJDYXVzZT86IHVua25vd24sXG4gICAgZXJyb3JMZXZlbD86IEx5bnhFcnJvckxldmVsLFxuICAgIHByZWZpeD86IHN0cmluZ1xuICApOiB2b2lkIHtcbiAgICBsZXQgeyBtZXNzYWdlLCBuYW1lLCBzdGFjaywgY2F1c2UgfSA9IGVycm9yIHx8IHt9O1xuICAgIGlmICghbWVzc2FnZSkge1xuICAgICAgLy8gSWYgdGhlcmUgaXMgbm8gZXJyb3IgbWVzc2FnZSBpbiBlcnJvciwgbWVhbnMgdGhhdCBpdCBpcyBub3QgYW4gZXJyb3ItbGlrZSBvYmplY3QuXG4gICAgICAvLyBXZSBjb25zdHJ1Y3QgYSBuZXcgRXJyb3IgdXNpbmcgSlNPTi5zdHJpbmdpZnlcbiAgICAgICh7IG1lc3NhZ2UsIG5hbWUsIHN0YWNrIH0gPSBuZXcgRXJyb3IoSlNPTi5zdHJpbmdpZnkoZXJyb3IpKSk7XG4gICAgfVxuICAgIGNhdXNlID0gY2F1c2UgPz8gb3V0ZXJDYXVzZTtcbiAgICBjb25zdCB1c2VyRXJyb3IgPSBuZXcgVXNlclJ1bnRpbWVFcnJvcihcbiAgICAgIHByZWZpeCA/IGAke3ByZWZpeH0gJHtuYW1lfTogJHttZXNzYWdlfWAgOiBgJHtuYW1lfTogJHttZXNzYWdlfWAsXG4gICAgICBzdGFja1xuICAgICk7XG4gICAgdXNlckVycm9yLmNhdXNlID0gY2F1c2U7XG4gICAgdGhpcy5oYW5kbGVFcnJvcih1c2VyRXJyb3IsIGVycm9yLCBlcnJvckxldmVsKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBAaW50ZXJuYWxcbiAgICovXG4gIGhhbmRsZUludGVybmFsRXJyb3IoZXJyb3I/OiBFcnJvciwgY2F1c2U/OiB1bmtub3duKTogdm9pZCB7XG4gICAgbGV0IHsgbWVzc2FnZSwgbmFtZSwgc3RhY2sgfSA9IGVycm9yIHx8IHt9O1xuICAgIGlmICghbWVzc2FnZSkge1xuICAgICAgLy8gSWYgdGhlcmUgaXMgbm8gZXJyb3IgbWVzc2FnZSBpbiBlcnJvciwgbWVhbnMgdGhhdCBpdCBpcyBub3QgYW4gZXJyb3ItbGlrZSBvYmplY3QuXG4gICAgICAvLyBXZSBjb25zdHJ1Y3QgYSBuZXcgRXJyb3IgdXNpbmcgSlNPTi5zdHJpbmdpZnlcbiAgICAgICh7IG1lc3NhZ2UsIG5hbWUsIHN0YWNrIH0gPSBuZXcgRXJyb3IoSlNPTi5zdHJpbmdpZnkoZXJyb3IpKSk7XG4gICAgfVxuICAgIGNvbnN0IGludGVybmFsRXJyb3IgPSBuZXcgSW50ZXJuYWxSdW50aW1lRXJyb3IoXG4gICAgICBgJHtuYW1lfTogJHttZXNzYWdlfWAsXG4gICAgICBzdGFja1xuICAgICk7XG4gICAgaW50ZXJuYWxFcnJvci5jYXVzZSA9IGNhdXNlO1xuICAgIHRoaXMuaGFuZGxlRXJyb3IoaW50ZXJuYWxFcnJvciwgZXJyb3IpO1xuICB9XG5cbiAgLyoqXG4gICAqIEdldCBhIGV4dGVybmFsIGVudiB3aXRoIGJvb2xlYW4gdmFsdWUuXG4gICAqIFRoZSBzYW1lIGFzIGBiYXNlOjpMeW54RW52OjpHZXRJbnN0YW5jZSgpLkdldEJvb2xFbnZgXG4gICAqXG4gICAqIEBwYXJhbSB7RW52S2V5fSBrZXkgVGhlIHtAbGluayBFbnZLZXl9LCBzaG91bGQgYmUgcGxhY2VkIGluIGBseW54X2Vudi5oYFxuICAgKi9cbiAgZ2V0Qm9vbEVudihrZXk6IEVudktleSk6IGJvb2xlYW4ge1xuICAgIGNvbnN0IGVudiA9IHRoaXMubmF0aXZlQXBwLmdldEVudihrZXkpO1xuICAgIHJldHVybiBlbnY/LnRvTG93ZXJDYXNlKCkgPT09ICd0cnVlJztcbiAgfVxuXG4gIC8qKlxuICAgKiBAaW50ZXJuYWxcbiAgICogQHN0YXRpY1xuICAgKiBUaGUgTHlueEdyb3VwIGxldmVsIGNhY2hlIGZvciByZXF1aXJlTW9kdWxlICwge0BsaW5rIHJlZ2lzdGVyTW9kdWxlfVxuICAgKi9cbiAgc3RhdGljIF8kZmFjdG9yeUNhY2hlOiBSZWNvcmQ8XG4gICAgc3RyaW5nLFxuICAgIDxUPihpbmplY3RlZDogeyB0dDogQmFzZUFwcCB9KSA9PiBUXG4gID4gPSB7fTtcblxuICAvKipcbiAgICogQGludGVybmFsXG4gICAqIEBzdGF0aWNcbiAgICogVGhlIEx5bnhHcm91cCBsZXZlbCBjYWNoZSBmb3IgbG9hZFNjcmlwdFxuICAgKi9cbiAgc3RhdGljIF8kbG9hZFNjcmlwdENhY2hlOiBSZWNvcmQ8c3RyaW5nLCBCdW5kbGVJbml0UmV0dXJuT2JqIHwgRnVuY3Rpb24+ID0ge307XG5cbiAgLyoqXG4gICAqIEBpbnRlcm5hbFxuICAgKiBFeGVjdXRlIHRoZSBsb2FkZWQgSlMgbW9kdWxlICwgIENhbGxlZCBieSB7QGxpbmsgcmVxdWlyZU1vZHVsZX0gJiB7QGxpbmsgcmVxdWlyZU1vZHVsZUFzeW5jfVxuICAgKiBAdGhyb3dzIHtVc2VyUnVudGltZUVycm9yfSB3aGVuIGxvYWRpbmcgb3IgZXZhbHVhdGluZyBmYWlsZWRcbiAgICogQHRocm93cyB7RXJyb3J9IHdoZW4gZXhlY3V0aW5nIGZhaWxlZFxuICAgKi9cbiAgcHJpdmF0ZSBfJGV4ZWN1dGVJbml0PFQ+KFxuICAgIGV4cG9ydHM6IFJldHVyblR5cGU8TmF0aXZlQXBwWydsb2FkU2NyaXB0J10+LFxuICAgIHtcbiAgICAgIHBhdGgsXG4gICAgICBlbnRyeU5hbWUsXG4gICAgICBzaG91bGRDYWNoZUZhY3RvcnkgPSB0cnVlLFxuICAgICAgY2FjaGVLZXksXG4gICAgfToge1xuICAgICAgcGF0aDogc3RyaW5nO1xuICAgICAgZW50cnlOYW1lPzogc3RyaW5nO1xuICAgICAgc2hvdWxkQ2FjaGVGYWN0b3J5PzogYm9vbGVhbjtcbiAgICAgIGNhY2hlS2V5Pzogc3RyaW5nO1xuICAgIH1cbiAgKTogVCB7XG4gICAgbGV0IGZhY3Rvcnk6IDxUPihpbmplY3RlZDogeyB0dDogQmFzZUFwcCB9KSA9PiBUO1xuICAgIGlmIChleHBvcnRzICYmIGV4cG9ydHMuaW5pdCkge1xuICAgICAgLy8gYXBwLXNlcnZpY2UuanMgYW5kIGNvbW1vbi1jaHVuay5qcyB3aXRoIG5ldyBmb3JtYXQgd2lsbCBoYXZlIGluaXQgZnVuY3Rpb25cbiAgICAgIGZhY3RvcnkgPSBleHBvcnRzLmluaXQuYmluZChleHBvcnRzKTtcbiAgICB9IGVsc2UgaWYgKG5hdGl2ZUdsb2JhbC5pbml0QnVuZGxlKSB7XG4gICAgICAvLyBjb21tb24tY2h1bmsuanMgd2l0aCBvbGQgZm9ybWF0IHdpbGwgc2V0IGdsb2JhbC5pbml0QnVuZGxlIGR1cmluZyBsb2FkU2NyaXB0XG4gICAgICBmYWN0b3J5ID0gbmF0aXZlR2xvYmFsLmluaXRCdW5kbGUuYmluZChuYXRpdmVHbG9iYWwuaW5pdEJ1bmRsZSk7XG4gICAgICBkZWxldGUgbmF0aXZlR2xvYmFsLmluaXRCdW5kbGU7IC8vIHNob3VsZCBkZWxldGUgaW5pdEJ1bmRsZSBhZnRlciB1c2VkXG4gICAgfSBlbHNlIHtcbiAgICAgIC8vIG5vIGZhY3RvcnkgZnVuY3Rpb24gZm91bmQsIHByb2JhYmx5IGxvYWRTY3JpcHQgZmFpbGVkLlxuICAgICAgLy8gVE9ETyh3YW5ncWluZ3l1KTogZG8gbm90IHRocm93IHRoaXMgd2hlbiBgbmF0aXZlQXBwLmxvYWRTY3JpcHRgIHN1cHBvcnQgZXhjZXB0aW9uc1xuICAgICAgdGhyb3cgbmV3IFVzZXJSdW50aW1lRXJyb3IoXG4gICAgICAgIGBsb2FkIGZhaWxlZC4gcGF0aDoke3BhdGh9LGVudHJ5TmFtZToke2VudHJ5TmFtZX1gXG4gICAgICApO1xuICAgIH1cbiAgICB0cnkge1xuICAgICAgdGhpcy5seW54LnBlcmZvcm1hbmNlLnByb2ZpbGVTdGFydChUcmFjZUV2ZW50RGVmLkVYRUNVVEVfTE9BREVEX1NDUklQVCwge1xuICAgICAgICBhcmdzOiB7IHBhdGggfSxcbiAgICAgIH0pO1xuICAgICAgY29uc3QgcmV0ID0gZmFjdG9yeTxUPih7IHR0OiB0aGlzIH0pO1xuXG4gICAgICAvLyBIZXJlIG1lYW5zIHRoYXQgbm8gZXJyb3Igb2NjdXJyZWQgd2hlbiBleGVjdXRpbmcuXG4gICAgICAvLyBPbmx5IHRoZW4gd2UgY2FjaGUgdGhlIGZhY3RvcnkuXG4gICAgICBpZiAoc2hvdWxkQ2FjaGVGYWN0b3J5KSB7XG4gICAgICAgIEJhc2VBcHAuXyRmYWN0b3J5Q2FjaGVbcGF0aF0gPSBmYWN0b3J5O1xuICAgICAgfVxuICAgICAgYWRkTG9hZFNjcmlwdENhY2hlKGNhY2hlS2V5LCBleHBvcnRzKTtcblxuICAgICAgcmV0dXJuIHJldDtcbiAgICB9IGZpbmFsbHkge1xuICAgICAgdGhpcy5seW54LnBlcmZvcm1hbmNlLnByb2ZpbGVFbmQoKTtcbiAgICB9XG4gIH1cblxuICAvKipcbiAgICogQGludGVybmFsXG4gICAqIFVzZWQgdG8gbG9hZCB0aGUganNvbiBtb2R1bGUuIENhbGxlZCBieSB7QGxpbmsgcmVxdWlyZU1vZHVsZX0gJiB7QGxpbmsgcmVxdWlyZU1vZHVsZUFzeW5jfVxuICAgKiBAcGFyYW0gY29udGVudFxuICAgKiBAcGFyYW0gcGF0aFxuICAgKiBAcHJpdmF0ZVxuICAgKi9cbiAgcHJpdmF0ZSBfJGV4ZWN1dGVKU09OPFQ+KFxuICAgIGNvbnRlbnQ6IFJldHVyblR5cGU8TmF0aXZlQXBwWydyZWFkU2NyaXB0J10+LFxuICAgIHsgcGF0aCB9OiB7IHBhdGg6IHN0cmluZzsgZW50cnlOYW1lPzogc3RyaW5nIH1cbiAgKTogVCB7XG4gICAgY29uc3QgcmV0ID0gSlNPTi5wYXJzZShjb250ZW50KTtcbiAgICBjb25zdCBpbml0ID0gKCkgPT4gcmV0O1xuICAgIEJhc2VBcHAuXyRmYWN0b3J5Q2FjaGVbcGF0aF0gPSBpbml0O1xuICAgIHJldHVybiByZXQ7XG4gIH1cblxuICByZXF1aXJlTW9kdWxlPFQ+KFxuICAgIHBhdGg6IHN0cmluZyxcbiAgICBlbnRyeU5hbWU/OiBzdHJpbmcsXG4gICAgb3B0aW9ucz86IHsgdGltZW91dDogbnVtYmVyIH1cbiAgKTogVCB7XG4gICAgY29uc3QgaW5pdCA9IEJhc2VBcHAuXyRmYWN0b3J5Q2FjaGVbcGF0aF07XG4gICAgaWYgKE5PREVfRU5WICE9PSAnZGV2ZWxvcG1lbnQnICYmIGluaXQpIHtcbiAgICAgIC8vIGNhY2hlIGhpdFxuICAgICAgcmV0dXJuIHRoaXMuXyRleGVjdXRlSW5pdDxUPih7IGluaXQgfSwgeyBwYXRoLCBlbnRyeU5hbWUgfSk7XG4gICAgfVxuXG4gICAgLy8gY2FjaGUgbWlzc1xuICAgIGlmIChwYXRoLnNwbGl0KCc/JylbMF0uZW5kc1dpdGgoJy5qc29uJykpIHtcbiAgICAgIGNvbnN0IGNvbnRlbnQgPSB0aGlzLm5hdGl2ZUFwcC5yZWFkU2NyaXB0KHBhdGgsIHtcbiAgICAgICAgZHluYW1pY0NvbXBvbmVudEVudHJ5OiBlbnRyeU5hbWUgPz8gREVGQVVMVF9FTlRSWSxcbiAgICAgICAgLi4ub3B0aW9ucyxcbiAgICAgIH0pO1xuICAgICAgcmV0dXJuIHRoaXMuXyRleGVjdXRlSlNPTihjb250ZW50LCB7IHBhdGgsIGVudHJ5TmFtZSB9KTtcbiAgICB9XG4gICAgY29uc3QgY2FjaGVLZXkgPSB0aGlzLmdldExvYWRTY3JpcHRDYWNoZUtleShcbiAgICAgIHBhdGgsXG4gICAgICBlbnRyeU5hbWUsXG4gICAgICB0aGlzLnBhcmFtcy5zcmNOYW1lXG4gICAgKTtcbiAgICBjb25zdCBjYWNoZSA9IHRyeUdldExvYWRTY3JpcHRDYWNoZShjYWNoZUtleSk7XG4gICAgaWYgKGNhY2hlKSB7XG4gICAgICAvLyBjYWNoZSBoaXRcbiAgICAgIHJldHVybiB0aGlzLl8kZXhlY3V0ZUluaXQ8VD4oY2FjaGUgYXMgQnVuZGxlSW5pdFJldHVybk9iaiwge1xuICAgICAgICBwYXRoLFxuICAgICAgICBlbnRyeU5hbWUsXG4gICAgICB9KTtcbiAgICB9IGVsc2Uge1xuICAgICAgY29uc3QgZXhwb3J0cyA9IHRoaXMubmF0aXZlQXBwLmxvYWRTY3JpcHQocGF0aCwgZW50cnlOYW1lLCBvcHRpb25zKTtcbiAgICAgIHJldHVybiB0aGlzLl8kZXhlY3V0ZUluaXQ8VD4oZXhwb3J0cywgeyBwYXRoLCBlbnRyeU5hbWUsIGNhY2hlS2V5IH0pO1xuICAgIH1cbiAgfVxuXG4gIHJlcXVpcmVNb2R1bGVBc3luYzxUPihcbiAgICBwYXRoOiBzdHJpbmcsXG4gICAgY2FsbGJhY2s6IChlcnJvcj86IEVycm9yLCBleHBvcnRzPzogVCkgPT4gdm9pZFxuICApOiB2b2lkIHtcbiAgICBjb25zdCBpbml0ID0gQmFzZUFwcC5fJGZhY3RvcnlDYWNoZVtwYXRoXTtcbiAgICBpZiAoTk9ERV9FTlYgIT09ICdkZXZlbG9wbWVudCcgJiYgaW5pdCkge1xuICAgICAgLy8gY2FjaGUgaGl0XG4gICAgICBjYWxsYmFjayhudWxsLCB0aGlzLl8kZXhlY3V0ZUluaXQ8VD4oeyBpbml0IH0sIHsgcGF0aCB9KSk7XG4gICAgICByZXR1cm47XG4gICAgfVxuICAgIC8vIGNhY2hlIG1pc3NcbiAgICBpZiAocGF0aC5zcGxpdCgnPycpWzBdLmVuZHNXaXRoKCcuanNvbicpKSB7XG4gICAgICB0cnkge1xuICAgICAgICBjb25zdCBjb250ZW50ID0gdGhpcy5uYXRpdmVBcHAucmVhZFNjcmlwdChwYXRoKTtcbiAgICAgICAgY29uc3QgcmV0ID0gdGhpcy5fJGV4ZWN1dGVKU09OPFQ+KGNvbnRlbnQsIHsgcGF0aCB9KTtcbiAgICAgICAgY2FsbGJhY2sobnVsbCwgcmV0KTtcbiAgICAgIH0gY2F0Y2ggKGUpIHtcbiAgICAgICAgY2FsbGJhY2soZSk7XG4gICAgICB9XG4gICAgICByZXR1cm47XG4gICAgfVxuXG4gICAgLy8gZ2V0IGNhY2hlIGZpcnN0XG4gICAgY29uc3QgY2FjaGVLZXkgPSB0aGlzLmdldExvYWRTY3JpcHRDYWNoZUtleShwYXRoLCB0aGlzLnBhcmFtcy5zcmNOYW1lKTtcbiAgICBjb25zdCBjYWNoZSA9IHRyeUdldExvYWRTY3JpcHRDYWNoZShjYWNoZUtleSk7XG4gICAgaWYgKGNhY2hlKSB7XG4gICAgICAvLyBjYWNoZSBoaXRcbiAgICAgIHRyeSB7XG4gICAgICAgIHJldHVybiBjYWxsYmFjayhcbiAgICAgICAgICBudWxsLFxuICAgICAgICAgIHRoaXMuXyRleGVjdXRlSW5pdChjYWNoZSBhcyBCdW5kbGVJbml0UmV0dXJuT2JqLCB7IHBhdGggfSlcbiAgICAgICAgKTtcbiAgICAgIH0gY2F0Y2ggKGUpIHtcbiAgICAgICAgY2FsbGJhY2soZSk7XG4gICAgICB9XG4gICAgfVxuICAgIC8vIENyZWF0ZSBhbiBlcnJvciBoZXJlIHRvIG1ha2Ugc3VyZSB0aGUgc3RhY2sgY29udGFpbnNcbiAgICAvLyBseW54LnJlcXVpcmVNb2R1bGVBc3luYyBhbmQgaXQncyBjYWxsZXIuXG4gICAgY29uc3QgZXJyb3IgPSBuZXcgRXJyb3IoKTtcbiAgICB0aGlzLm5hdGl2ZUFwcC5sb2FkU2NyaXB0QXN5bmMocGF0aCwgKG1lc3NhZ2UsIGV4cG9ydHMpOiB2b2lkID0+IHtcbiAgICAgIGlmIChtZXNzYWdlKSB7XG4gICAgICAgIGVycm9yLm1lc3NhZ2UgPSBtZXNzYWdlO1xuICAgICAgICAvLyBPbmx5IG92ZXJyaWRlIGVycm9yLm1lc3NhZ2Ugc28gdGhhdCB3ZSBjb3VsZCBwcml2aWRlIHN0YWNrIHdpdGhcbiAgICAgICAgLy8gbHlueC5yZXF1aXJlTW9kdWxlQXN5bmMgYW5kIGl0J3MgY2FsbGVyLlxuICAgICAgICByZXR1cm4gY2FsbGJhY2soZXJyb3IpO1xuICAgICAgfVxuXG4gICAgICB0cnkge1xuICAgICAgICByZXR1cm4gY2FsbGJhY2sobnVsbCwgdGhpcy5fJGV4ZWN1dGVJbml0KGV4cG9ydHMsIHsgcGF0aCwgY2FjaGVLZXkgfSkpO1xuICAgICAgfSBjYXRjaCAoZSkge1xuICAgICAgICByZXR1cm4gY2FsbGJhY2soZSk7XG4gICAgICB9XG4gICAgfSk7XG4gIH1cblxuICByZXF1aXJlKHBhdGg6IHN0cmluZywgcGFyYW1zPzogcmVxdWlyZVBhcmFtT2JqKSB7XG4gICAgY29uc3QgdGhhdCA9IHRoaXM7XG4gICAgaWYgKHR5cGVvZiBwYXRoICE9PSAnc3RyaW5nJykge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKCdyZXF1aXJlIGFyZ3MgbXVzdCBiZSBhIHN0cmluZycpO1xuICAgIH1cbiAgICBjb25zdCBlbnRyeU5hbWUgPVxuICAgICAgcGFyYW1zICYmIHBhcmFtcy5keW5hbWljQ29tcG9uZW50RW50cnlcbiAgICAgICAgPyBwYXJhbXMuZHluYW1pY0NvbXBvbmVudEVudHJ5XG4gICAgICAgIDogREVGQVVMVF9FTlRSWTtcbiAgICBpZiAoIXRoYXQubW9kdWxlc1tlbnRyeU5hbWVdKSB7XG4gICAgICB0aGF0Lm1vZHVsZXNbZW50cnlOYW1lXSA9IHt9O1xuICAgIH1cbiAgICBsZXQgbW9kdWxlID0gdGhhdC5tb2R1bGVzW2VudHJ5TmFtZV1bcGF0aF07XG4gICAgaWYgKCFtb2R1bGUpIHtcbiAgICAgIHRyeSB7XG4gICAgICAgIC8vIGVzbGludC1kaXNhYmxlLW5leHQtbGluZSBAdHlwZXNjcmlwdC1lc2xpbnQvbm8tdW51c2VkLXZhcnNcbiAgICAgICAgY29uc3QgdHQgPSB0aGF0O1xuICAgICAgICBjb25zdCBqc0NvbnRlbnQgPSB0aGF0Ll9uYXRpdmVBcHAucmVhZFNjcmlwdChwYXRoLCB7XG4gICAgICAgICAgZHluYW1pY0NvbXBvbmVudEVudHJ5OiBlbnRyeU5hbWUsXG4gICAgICAgIH0pO1xuICAgICAgICAvLyBlc2xpbnQtZGlzYWJsZS1uZXh0LWxpbmUgbm8tZXZhbFxuICAgICAgICBldmFsKGpzQ29udGVudCk7XG4gICAgICAgIG1vZHVsZSA9IHRoYXQubW9kdWxlc1tlbnRyeU5hbWVdW3BhdGhdO1xuICAgICAgfSBjYXRjaCAoZSkge1xuICAgICAgICB0aGlzLmhhbmRsZUVycm9yKFxuICAgICAgICAgIG5ldyBVc2VyUnVudGltZUVycm9yKFxuICAgICAgICAgICAgYGV2YWwgdXNlcjogJHt0aGF0Ll9uYXRpdmVBcHAuaWR9IGVycm9yOiAke2UubWVzc2FnZX1gLFxuICAgICAgICAgICAgZS5zdGFja1xuICAgICAgICAgICksXG4gICAgICAgICAgZVxuICAgICAgICApO1xuICAgICAgfVxuXG4gICAgICBpZiAoIXRoYXQubW9kdWxlc1tlbnRyeU5hbWVdW3BhdGhdKSB7XG4gICAgICAgIHRocm93IG5ldyBFcnJvcihcbiAgICAgICAgICBgbW9kdWxlICR7cGF0aH0gaW4gJHtlbnRyeU5hbWV9IGlzIG5vdCBkZWZpbmVkIGluIGNhcmQ6ICR7dGhhdC5fbmF0aXZlQXBwLmlkfWBcbiAgICAgICAgKTtcbiAgICAgIH1cbiAgICB9XG5cbiAgICBpZiAoIW1vZHVsZS5oYXNSdW4pIHtcbiAgICAgIGNvbnN0IHsgZmFjdG9yeSB9ID0gbW9kdWxlO1xuICAgICAgY29uc3QgX21vZHVsZSA9IHtcbiAgICAgICAgZXhwb3J0czoge30sXG4gICAgICB9O1xuICAgICAgbGV0IHJlcztcblxuICAgICAgbW9kdWxlLmhhc1J1biA9IHRydWU7XG4gICAgICBtb2R1bGUuZXhwb3J0cyA9IF9tb2R1bGUuZXhwb3J0cztcbiAgICAgIGlmICh0eXBlb2YgZmFjdG9yeSA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgICBjb25zdCBpblJlcXVpcmVDb3B5ID0gaW5SZXF1aXJlLmNhbGwodGhhdCwgcGF0aCk7XG4gICAgICAgIGNvbnN0IHR0ID0gdGhhdDtcbiAgICAgICAgcmVzID0gZmFjdG9yeShcbiAgICAgICAgICBpblJlcXVpcmVDb3B5LFxuICAgICAgICAgIF9tb2R1bGUsXG4gICAgICAgICAgX21vZHVsZS5leHBvcnRzLFxuICAgICAgICAgIHRoYXQuQ2FyZC5iaW5kKHR0KSxcbiAgICAgICAgICB0aGF0LnNldFRpbWVvdXQsXG4gICAgICAgICAgdGhhdC5zZXRJbnRlcnZhbCxcbiAgICAgICAgICB0aGF0LmNsZWFySW50ZXJ2YWwsXG4gICAgICAgICAgdGhhdC5jbGVhclRpbWVvdXQsXG4gICAgICAgICAgdGhhdC5OYXRpdmVNb2R1bGVzLFxuICAgICAgICAgIHRoYXQuX2FwaUxpc3QsXG4gICAgICAgICAgdGhhdC5zaGFyZWRDb25zb2xlLFxuICAgICAgICAgIHRoYXQuQ29tcG9uZW50LmJpbmQodHQpLFxuICAgICAgICAgIHBhcmFtcz8uUmVhY3RMeW54LFxuICAgICAgICAgIHRoYXQubmF0aXZlQXBwSWQsXG4gICAgICAgICAgdGhhdC5CZWhhdmlvci5iaW5kKHR0KSxcbiAgICAgICAgICBMeW54SlNCSSxcbiAgICAgICAgICB0aGF0Lmx5bngsXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyB3aW5kb3dcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIGRvY3VtZW50XG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBmcmFtZXNcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIHNlbGZcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIGxvY2F0aW9uXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBuYXZpZ2F0b3JcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIGxvY2FsU3RvcmFnZVxuICAgICAgICAgIHVuZGVmaW5lZCwgLy8gaGlzdG9yeVxuICAgICAgICAgIHVuZGVmaW5lZCwgLy8gQ2FjaGVzXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBzY3JlZW5cbiAgICAgICAgICB1bmRlZmluZWQsIC8vIGFsZXJ0XG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBjb25maXJtXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBwcm9tcHRcbiAgICAgICAgICB0aGF0Lmx5bnguZmV0Y2gsIC8vIGZldGNoXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBYTUxIdHRwUmVxdWVzdFxuICAgICAgICAgIHVuZGVmaW5lZCwgLy8gV2ViU29ja2V0XG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyB3ZWJraXRcbiAgICAgICAgICB1bmRlZmluZWQsIC8vIFJlcG9ydGVyXG4gICAgICAgICAgdW5kZWZpbmVkLCAvLyBwcmludFxuICAgICAgICAgIHVuZGVmaW5lZCwgLy8gZ2xvYmFsXG4gICAgICAgICAgdGhhdC5yZXF1ZXN0QW5pbWF0aW9uRnJhbWUsXG4gICAgICAgICAgdGhhdC5jYW5jZWxBbmltYXRpb25GcmFtZVxuICAgICAgICApO1xuICAgICAgICBtb2R1bGUuZXhwb3J0cyA9IF9tb2R1bGUuZXhwb3J0cyB8fCByZXM7XG4gICAgICB9XG4gICAgfVxuICAgIHJldHVybiBtb2R1bGUuZXhwb3J0cztcbiAgfVxuXG4gIGRlZmluZShwYXRoOiBzdHJpbmcsIGZhY3Rvcnk6IEFNREZhY3RvcnksIGVudHJ5TmFtZT86IHN0cmluZykge1xuICAgIGVudHJ5TmFtZSA9IGVudHJ5TmFtZSA/IGVudHJ5TmFtZSA6IERFRkFVTFRfRU5UUlk7XG4gICAgaWYgKCF0aGlzLm1vZHVsZXNbZW50cnlOYW1lXSkge1xuICAgICAgdGhpcy5tb2R1bGVzW2VudHJ5TmFtZV0gPSB7fTtcbiAgICB9XG4gICAgdGhpcy5tb2R1bGVzW2VudHJ5TmFtZV1bcGF0aF0gPSB7XG4gICAgICBoYXNSdW46IGZhbHNlLFxuICAgICAgZmFjdG9yeTogZmFjdG9yeS5iaW5kKHRoaXMpLFxuICAgIH07XG4gIH1cblxuICBsb2FkU2NyaXB0PFQ+KFxuICAgIHVybDogc3RyaW5nLFxuICAgIG9wdGlvbnM/OiB7IGJ1bmRsZU5hbWU/OiBzdHJpbmc7IHVzZU1vZHVsZVdyYXBwZXI/OiBib29sZWFuIH1cbiAgKTogVCB7XG4gICAgY29uc3QgeyBidW5kbGVOYW1lID0gREVGQVVMVF9FTlRSWSwgdXNlTW9kdWxlV3JhcHBlciA9IGZhbHNlIH0gPVxuICAgICAgb3B0aW9ucyB8fCB7fTtcbiAgICBjb25zdCBjYWNoZUtleSA9IHRoaXMuZ2V0TG9hZFNjcmlwdENhY2hlS2V5KFxuICAgICAgdXJsLFxuICAgICAgYnVuZGxlTmFtZSxcbiAgICAgIHRoaXMucGFyYW1zLnNyY05hbWUsXG4gICAgICB0cnVlXG4gICAgKTtcbiAgICBsZXQgZXhwb3J0czogQnVuZGxlSW5pdFJldHVybk9iaiB8IG9iamVjdCA9IHRyeUdldExvYWRTY3JpcHRDYWNoZShjYWNoZUtleSk7XG4gICAgaWYgKE5PREVfRU5WID09PSAnZGV2ZWxvcG1lbnQnIHx8ICFleHBvcnRzKSB7XG4gICAgICBsZXQgbWF5YmVFeHBvcnRzID0gdGhpcy5seW54LmdldE5hdGl2ZUx5bngoKS5sb2FkU2NyaXB0KHVybCwgb3B0aW9ucyk7XG4gICAgICBpZiAobWF5YmVFeHBvcnRzICYmIHR5cGVvZiAobWF5YmVFeHBvcnRzIGFzIGFueSkuaW5pdCA9PT0gJ2Z1bmN0aW9uJykge1xuICAgICAgICBleHBvcnRzID0gbWF5YmVFeHBvcnRzIGFzIEJ1bmRsZUluaXRSZXR1cm5PYmo7XG4gICAgICB9IGVsc2UgaWYgKFxuICAgICAgICB1c2VNb2R1bGVXcmFwcGVyICYmXG4gICAgICAgIG1heWJlRXhwb3J0cyAmJlxuICAgICAgICB0eXBlb2YgbWF5YmVFeHBvcnRzID09PSAnZnVuY3Rpb24nXG4gICAgICApIHtcbiAgICAgICAgZXhwb3J0cyA9IG1heWJlRXhwb3J0cztcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHJldHVybiBtYXliZUV4cG9ydHMgYXMgVDtcbiAgICAgIH1cbiAgICB9XG5cbiAgICBpZiAodXNlTW9kdWxlV3JhcHBlcikge1xuICAgICAgY29uc3QgbW9kdWxlID0geyBleHBvcnRzOiB7fSB9O1xuICAgICAgbGV0IHRoYXQgPSB0aGlzO1xuICAgICAgY29uc3QgaW5SZXF1aXJlQ29weSA9IGluUmVxdWlyZS5jYWxsKHRoYXQsIHVybCk7XG4gICAgICBjb25zdCBhcmdzID0gW1xuICAgICAgICBpblJlcXVpcmVDb3B5LFxuICAgICAgICBtb2R1bGUsXG4gICAgICAgIG1vZHVsZS5leHBvcnRzLFxuICAgICAgICB0aGF0LnNldFRpbWVvdXQsXG4gICAgICAgIHRoYXQuc2V0SW50ZXJ2YWwsXG4gICAgICAgIHRoYXQuY2xlYXJJbnRlcnZhbCxcbiAgICAgICAgdGhhdC5jbGVhclRpbWVvdXQsXG4gICAgICAgIHRoYXQuTmF0aXZlTW9kdWxlcyxcbiAgICAgICAgdGhhdC5zaGFyZWRDb25zb2xlLFxuICAgICAgICB0aGF0Lm5hdGl2ZUFwcElkLFxuICAgICAgICBMeW54SlNCSSxcbiAgICAgICAgdGhhdC5seW54LFxuICAgICAgICB0aGF0LnJlcXVlc3RBbmltYXRpb25GcmFtZSxcbiAgICAgICAgdGhhdC5jYW5jZWxBbmltYXRpb25GcmFtZSxcbiAgICAgICAgdGhhdC5seW54LmZldGNoLFxuICAgICAgXTtcbiAgICAgIChleHBvcnRzIGFzIEZ1bmN0aW9uKS5hcHBseShtb2R1bGUuZXhwb3J0cywgYXJncyk7XG4gICAgICBhZGRMb2FkU2NyaXB0Q2FjaGUoY2FjaGVLZXksIGV4cG9ydHMgYXMgRnVuY3Rpb24pO1xuICAgICAgcmV0dXJuIG1vZHVsZS5leHBvcnRzIGFzIFQ7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiB0aGlzLl8kZXhlY3V0ZUluaXQ8VD4oZXhwb3J0cyBhcyBCdW5kbGVJbml0UmV0dXJuT2JqLCB7XG4gICAgICAgIHBhdGg6IHVybCxcbiAgICAgICAgZW50cnlOYW1lOiBvcHRpb25zPy5idW5kbGVOYW1lLFxuICAgICAgICBzaG91bGRDYWNoZUZhY3Rvcnk6IGZhbHNlLFxuICAgICAgICBjYWNoZUtleTogY2FjaGVLZXksXG4gICAgICB9KTtcbiAgICB9XG4gIH1cblxuICAvKipcbiAgICogQ2FsbCBCeSBOYXRpdmUganNfYXBwXG4gICAqIEBpbnRlcm5hbFxuICAgKiBAcGFyYW0gbW9kdWxlXG4gICAqIEBwYXJhbSBtZXRob2RcbiAgICogQHBhcmFtIGFyZ3NcbiAgICovXG4gIGNhbGxGdW5jdGlvbihtb2R1bGU6IHN0cmluZywgbWV0aG9kOiBzdHJpbmcsIGFyZ3M/OiB1bmtub3duW10pOiB2b2lkIHtcbiAgICB0cnkge1xuICAgICAgY29uc3QgbW9kdWxlTWV0aG9kcyA9IHRoaXMuZ2V0SlNNb2R1bGUobW9kdWxlKTtcbiAgICAgIGlmICh0eXBlb2YgbW9kdWxlTWV0aG9kc1ttZXRob2RdID09PSAnZnVuY3Rpb24nKSB7XG4gICAgICAgIG1vZHVsZU1ldGhvZHNbbWV0aG9kXS5hcHBseShtb2R1bGVNZXRob2RzLCBhcmdzKTtcbiAgICAgIH1cbiAgICB9IGNhdGNoIChlKSB7XG4gICAgICB0aGlzLmhhbmRsZVVzZXJFcnJvcihlLCB7IGJ5OiBgJHttb2R1bGV9LiR7bWV0aG9kfWAgfSk7XG4gICAgfVxuICB9XG5cbiAgLyoqXG4gICAqIENhbGwgQnkgTmF0aXZlIGpzX2FwcFxuICAgKiBAaW50ZXJuYWxcbiAgICogQHBhcmFtIHtuZXZlcn0gXyBVc2VkIGZvciBiYWNrd2FyZCBjb21wYXRpYmxpdHksIERPIE5PVCBVU0UuXG4gICAqIEBwYXJhbSB7RXJyb3J9IGVycm9yIHRoZSBFcnJvciBvYmplY3QgZW1pdCBieSBuYXRpdmUuXG4gICAqL1xuICBvbkFwcEVycm9yKF86IG5ldmVyLCBlcnJvcjogRXJyb3IpOiB2b2lkIHtcbiAgICB0aGlzLmhhbmRsZUludGVybmFsRXJyb3IoZXJyb3IpO1xuICB9XG5cbiAgc2F2ZUR5bmFtaWNDb21wb25lbnRFeHBvcnRzKGNvbXBvbmVudFVybCwgbW9kdWxlRXhwb3J0cykge1xuICAgIHRoaXMuZHluYW1pY0NvbXBvbmVudEV4cG9ydHNbY29tcG9uZW50VXJsXSA9IG1vZHVsZUV4cG9ydHM7XG4gIH1cblxuICBnZXREeW5hbWljQ29tcG9uZW50RXhwb3J0cyhjb21wb25lbnRVcmwpIHtcbiAgICByZXR1cm4gdGhpcy5keW5hbWljQ29tcG9uZW50RXhwb3J0c1tjb21wb25lbnRVcmxdO1xuICB9XG5cbiAgQ29tcG9uZW50KC4uLmFyZ3M6IHVua25vd25bXSk6IHZvaWQge31cblxuICBDYXJkKC4uLmFyZ3M6IHVua25vd25bXSk6IHZvaWQge31cblxuICBCZWhhdmlvcj8oLi4uYXJnczogdW5rbm93bltdKTogdm9pZCB7fVxuXG4gIC8qKlxuICAgKiBAcGFyYW0gc2V0VGltZW91dFxuICAgKi9cbiAgd3JhcFJlcG9ydChzZXRUaW1lb3V0OiBGdW5jdGlvbiwgZGVzYzogc3RyaW5nKSB7XG4gICAgY29uc3QgdGhhdCA9IHRoaXM7XG5cbiAgICBmdW5jdGlvbiB3cmFwUmVwb3J0KGZuOiBGdW5jdGlvbikge1xuICAgICAgcmV0dXJuIGZ1bmN0aW9uIHdyYXBSZXBvcnRJbm5lciguLi5hcmdzOiBhbnlbXSkge1xuICAgICAgICB0cnkge1xuICAgICAgICAgIHJldHVybiBmbi5hcHBseSh0aGlzLCBhcmdzKTtcbiAgICAgICAgfSBjYXRjaCAoZSkge1xuICAgICAgICAgIHRoYXQuaGFuZGxlVXNlckVycm9yKGUsIHsgYnk6IGRlc2MgfSk7XG4gICAgICAgIH1cbiAgICAgIH07XG4gICAgfVxuXG4gICAgcmV0dXJuIGZ1bmN0aW9uIFdyYXBUaW1lb3V0KGZuOiBGdW5jdGlvbiwgLi4uYXJnczogYW55W10pIHtcbiAgICAgIHJldHVybiBGdW5jdGlvbi5wcm90b3R5cGUuYXBwbHkuY2FsbChzZXRUaW1lb3V0LCB1bmRlZmluZWQsIFtcbiAgICAgICAgd3JhcFJlcG9ydChmbiksXG4gICAgICAgIC4uLmFyZ3MsXG4gICAgICBdKTtcbiAgICB9O1xuICB9XG5cbiAgc2V0dXBQcm9taXNlKFxuICAgIHNldFRpbWVvdXQ6IEx5bnhTZXRUaW1lb3V0LFxuICAgIGNsZWFyVGltZW91dDogTHlueENsZWFyVGltZW91dCxcbiAgICBseW54OiBOYXRpdmVMeW54UHJveHlcbiAgKSB7XG4gICAgY29uc3QgUHJvbWlzZUNvbnN0cnVjdG9yID0gZ2V0UHJvbWlzZU1heWJlUG9seWZpbGwoXG4gICAgICBzZXRUaW1lb3V0LFxuICAgICAgKGlkLCByZWFzb246IEVycm9yKSA9PiB7XG4gICAgICAgIHRyeSB7XG4gICAgICAgICAgaWYgKHJlYXNvbikge1xuICAgICAgICAgICAgaWYgKCFyZWFzb24uc3RhY2spIHtcbiAgICAgICAgICAgICAgcmVhc29uID0gbmV3IEVycm9yKEpTT04uc3RyaW5naWZ5KHJlYXNvbikpO1xuICAgICAgICAgICAgfVxuICAgICAgICAgICAgcmVhc29uLm5hbWUgPSAndW5oYW5kbGVkIHJlamVjdGlvbic7XG4gICAgICAgICAgICB0aGlzLmhhbmRsZVVzZXJFcnJvcihyZWFzb24pO1xuICAgICAgICAgIH1cbiAgICAgICAgfSBjYXRjaCAoZXJyKSB7XG4gICAgICAgICAgLy8ganVzdCBpZ25vcmVcbiAgICAgICAgfVxuICAgICAgfSxcbiAgICAgIGNsZWFyVGltZW91dCxcbiAgICAgIGx5bngucXVldWVNaWNyb3Rhc2ssXG4gICAgICB0aGlzLl9wYXJhbXM/LnBhZ2VDb25maWdTdWJzZXQ/LmVuYWJsZU1pY3JvdGFza1Byb21pc2VQb2x5ZmlsbCA/PyBmYWxzZVxuICAgICk7XG4gICAgdGhpcy5yZXNvbHZlZFByb21pc2UgPSBQcm9taXNlQ29uc3RydWN0b3IucmVzb2x2ZSgpO1xuICAgIHJldHVybiBQcm9taXNlQ29uc3RydWN0b3I7XG4gIH1cblxuICByZXF1ZXN0QW5pbWF0aW9uRnJhbWUgPSAoY2FsbGJhY2s6ICgpID0+IHZvaWQpID0+XG4gICAgdGhpcy5fbmF0aXZlQXBwLnJlcXVlc3RBbmltYXRpb25GcmFtZShjYWxsYmFjayk7XG5cbiAgY2FuY2VsQW5pbWF0aW9uRnJhbWUgPSAoYW5pbWF0aW9uSWQ6IG51bWJlcikgPT5cbiAgICB0aGlzLl9uYXRpdmVBcHAuY2FuY2VsQW5pbWF0aW9uRnJhbWUoYW5pbWF0aW9uSWQpO1xuXG4gIHByb3RlY3RlZCBhZGRJbnRlcm5hbEV2ZW50TGlzdGVuZXIoXG4gICAgY29udGV4dFByb3h5VHlwZTogQ29udGV4dFByb3h5VHlwZSxcbiAgICB0eXBlOiBzdHJpbmcsXG4gICAgbGlzdGVuZXI6IChldmVudDogTWVzc2FnZUV2ZW50KSA9PiB2b2lkXG4gICkge1xuICAgIHRoaXMuY29udGV4dFByb3h5VHlwZVRvTWV0aG9kW2NvbnRleHRQcm94eVR5cGVdKCkuYWRkRXZlbnRMaXN0ZW5lcihcbiAgICAgIHR5cGUsXG4gICAgICBsaXN0ZW5lclxuICAgICk7XG4gICAgdGhpcy5yZW1vdmVJbnRlcm5hbEV2ZW50TGlzdGVuZXJzQ2FsbGJhY2tzLnB1c2goKCkgPT4ge1xuICAgICAgdGhpcy5jb250ZXh0UHJveHlUeXBlVG9NZXRob2RbY29udGV4dFByb3h5VHlwZV0oKS5yZW1vdmVFdmVudExpc3RlbmVyKFxuICAgICAgICB0eXBlLFxuICAgICAgICBsaXN0ZW5lclxuICAgICAgKTtcbiAgICB9KTtcbiAgfVxuXG4gIHByb3RlY3RlZCBhZGRJbnRlcm5hbEV2ZW50TGlzdGVuZXJzKCkge1xuICAgIGlmICghdGhpcy5jb250ZXh0UHJveHlUeXBlVG9NZXRob2QpIHtcbiAgICAgIHRoaXMuY29udGV4dFByb3h5VHlwZVRvTWV0aG9kID0ge1xuICAgICAgICBbQ29udGV4dFByb3h5VHlwZS5Db3JlQ29udGV4dF06ICgpID0+IHRoaXMubHlueC5nZXRDb3JlQ29udGV4dCgpLFxuICAgICAgICBbQ29udGV4dFByb3h5VHlwZS5EZXZUb29sXTogKCkgPT4gdGhpcy5seW54LmdldERldnRvb2woKSxcbiAgICAgICAgW0NvbnRleHRQcm94eVR5cGUuSlNDb250ZXh0XTogKCkgPT4gdGhpcy5seW54LmdldEpTQ29udGV4dCgpLFxuICAgICAgICBbQ29udGV4dFByb3h5VHlwZS5VSUNvbnRleHRdOiAoKSA9PiB0aGlzLmx5bnguZ2V0VUlDb250ZXh0KCksXG4gICAgICAgIFtDb250ZXh0UHJveHlUeXBlLk5hdGl2ZV06ICgpID0+IHRoaXMubHlueC5nZXROYXRpdmUoKSxcbiAgICAgICAgW0NvbnRleHRQcm94eVR5cGUuRW5naW5lXTogKCkgPT4gdGhpcy5seW54LmdldEVuZ2luZSgpLFxuICAgICAgfTtcbiAgICB9XG5cbiAgICB0aGlzLmFkZEludGVybmFsRXZlbnRMaXN0ZW5lcihcbiAgICAgIENvbnRleHRQcm94eVR5cGUuQ29yZUNvbnRleHQsXG4gICAgICBNZXNzYWdlRXZlbnRUeXBlLk9OX05BVElWRV9BUFBfUkVBRFksXG4gICAgICAoKSA9PiB7XG4gICAgICAgIHRoaXMub25OYXRpdmVBcHBSZWFkeSgpO1xuICAgICAgfVxuICAgICk7XG4gICAgdGhpcy5hZGRJbnRlcm5hbEV2ZW50TGlzdGVuZXIoXG4gICAgICBDb250ZXh0UHJveHlUeXBlLkNvcmVDb250ZXh0LFxuICAgICAgTWVzc2FnZUV2ZW50VHlwZS5OT1RJRllfR0xPQkFMX1BST1BTX1VQREFURUQsXG4gICAgICAoZXZlbnQ6IE1lc3NhZ2VFdmVudCkgPT4ge1xuICAgICAgICB0aGlzLnVwZGF0ZUdsb2JhbFByb3BzKGV2ZW50LmRhdGEpO1xuICAgICAgfVxuICAgICk7XG4gICAgdGhpcy5hZGRJbnRlcm5hbEV2ZW50TGlzdGVuZXIoXG4gICAgICBDb250ZXh0UHJveHlUeXBlLkNvcmVDb250ZXh0LFxuICAgICAgTWVzc2FnZUV2ZW50VHlwZS5PTl9MSUZFQ1lDTEVfRVZFTlQsXG4gICAgICAoZXZlbnQ6IE1lc3NhZ2VFdmVudCkgPT4ge1xuICAgICAgICB0aGlzLk9uTGlmZWN5Y2xlRXZlbnQoZXZlbnQuZGF0YSk7XG4gICAgICB9XG4gICAgKTtcbiAgICB0aGlzLmFkZEludGVybmFsRXZlbnRMaXN0ZW5lcihcbiAgICAgIENvbnRleHRQcm94eVR5cGUuQ29yZUNvbnRleHQsXG4gICAgICBNZXNzYWdlRXZlbnRUeXBlLk9OX0FQUF9GSVJTVF9TQ1JFRU4sXG4gICAgICAoKSA9PiB7XG4gICAgICAgIHRoaXMub25BcHBGaXJzdFNjcmVlbigpO1xuICAgICAgfVxuICAgICk7XG4gICAgdGhpcy5hZGRJbnRlcm5hbEV2ZW50TGlzdGVuZXIoXG4gICAgICBDb250ZXh0UHJveHlUeXBlLkNvcmVDb250ZXh0LFxuICAgICAgTWVzc2FnZUV2ZW50VHlwZS5PTl9EWU5BTUlDX0pTX1NPVVJDRV9QUkVQQVJFRCxcbiAgICAgIChldmVudDogTWVzc2FnZUV2ZW50KSA9PiB7XG4gICAgICAgIG5hdGl2ZUdsb2JhbC5sb2FkRHluYW1pY0NvbXBvbmVudCh0aGlzLCBldmVudC5kYXRhKTtcbiAgICAgIH1cbiAgICApO1xuICAgIHRoaXMuYWRkSW50ZXJuYWxFdmVudExpc3RlbmVyKFxuICAgICAgQ29udGV4dFByb3h5VHlwZS5Db3JlQ29udGV4dCxcbiAgICAgIE1lc3NhZ2VFdmVudFR5cGUuT05fQVBQX0VOVEVSX0ZPUkVHUk9VTkQsXG4gICAgICAoKSA9PiB7XG4gICAgICAgIHRoaXMub25BcHBFbnRlckZvcmVncm91bmQoKTtcbiAgICAgIH1cbiAgICApO1xuICAgIHRoaXMuYWRkSW50ZXJuYWxFdmVudExpc3RlbmVyKFxuICAgICAgQ29udGV4dFByb3h5VHlwZS5Db3JlQ29udGV4dCxcbiAgICAgIE1lc3NhZ2VFdmVudFR5cGUuT05fQVBQX0VOVEVSX0JBQ0tHUk9VTkQsXG4gICAgICAoKSA9PiB7XG4gICAgICAgIHRoaXMub25BcHBFbnRlckJhY2tncm91bmQoKTtcbiAgICAgIH1cbiAgICApO1xuICB9XG5cbiAgcHJpdmF0ZSBfX3JlbW92ZUludGVybmFsRXZlbnRMaXN0ZW5lcnMgPSAoKSA9PiB7XG4gICAgdGhpcy5yZW1vdmVJbnRlcm5hbEV2ZW50TGlzdGVuZXJzQ2FsbGJhY2tzLmZvckVhY2goKGYpID0+IHtcbiAgICAgIGYoKTtcbiAgICB9KTtcbiAgfTtcblxuICBwcml2YXRlIGdldExvYWRTY3JpcHRDYWNoZUtleShcbiAgICBwYXRoOiBzdHJpbmcsXG4gICAgZW50cnlOYW1lPzogc3RyaW5nLFxuICAgIHRlbXBsYXRlVXJsPzogc3RyaW5nLFxuICAgIGlnbm9yZUNvbmZpZzogYm9vbGVhbiA9IGZhbHNlXG4gICk6IHN0cmluZyB8IHVuZGVmaW5lZCB7XG4gICAgaWYgKFxuICAgICAgIXRlbXBsYXRlVXJsIHx8XG4gICAgICBOT0RFX0VOViA9PT0gJ2RldmVsb3BtZW50JyB8fFxuICAgICAgKCF0aGlzLnBhcmFtcz8ucGFnZUNvbmZpZ1N1YnNldD8uZW5hYmxlUmV1c2VMb2FkU2NyaXB0RXhwb3J0cyAmJlxuICAgICAgICAhaWdub3JlQ29uZmlnKVxuICAgICkge1xuICAgICAgcmV0dXJuIHVuZGVmaW5lZDtcbiAgICB9XG4gICAgbGV0IGNhY2hlS2V5ID0gKGVudHJ5TmFtZSA/IGVudHJ5TmFtZSA6IERFRkFVTFRfRU5UUlkpICsgcGF0aDtcbiAgICBpZiAocGF0aC5zdGFydHNXaXRoKCcvJykgfHwgcGF0aC5zdGFydHNXaXRoKCdseW54X2Fzc2V0cycpKSB7XG4gICAgICBjYWNoZUtleSA9IHRlbXBsYXRlVXJsICsgY2FjaGVLZXk7XG4gICAgfVxuICAgIHJldHVybiBjYWNoZUtleTtcbiAgfVxuXG4gIC8qKlxuICAgKiAgb3ZlcnJpZGUgYnkgc3ViY2xhc3NcbiAgICogQHBhcmFtIG5ld0RhdGFcbiAgICovXG4gIHVwZGF0ZUdsb2JhbFByb3BzKG5ld0RhdGE6IG9iamVjdCk6IHZvaWQge31cblxuICAvKipcbiAgICogIG92ZXJyaWRlIGJ5IHN1YmNsYXNzXG4gICAqIEBwYXJhbSBuZXdEYXRhXG4gICAqL1xuICBPbkxpZmVjeWNsZUV2ZW50KFxuICAgIGFyZ3M6IFtcbiAgICAgIHN0cmluZyxcbiAgICAgIExpZmVFdmVudCB8IExpZmVFdmVudFtdLFxuICAgICAge1xuICAgICAgICBwcm9wcz86IFJlY29yZDxzdHJpbmcsIHVua25vd24+O1xuICAgICAgICBpbml0RGF0YT86IFJlY29yZDxzdHJpbmcsIHVua25vd24+O1xuICAgICAgICBkYXRhc2V0PzogUmVjb3JkPHN0cmluZywgc3RyaW5nPjtcbiAgICAgICAgaWQ/OiBzdHJpbmc7XG4gICAgICAgIGNsYXNzTmFtZT86IHN0cmluZztcbiAgICAgICAgcGFyZW50SWQ/OiBzdHJpbmc7XG4gICAgICAgIHBhdGg/OiBzdHJpbmc7XG4gICAgICAgIGVudHJ5TmFtZT86IHN0cmluZztcbiAgICAgICAgLyoqXG4gICAgICAgICAqIGFkZGl0aW9uYWwgYXJndW1lbnRzIGxpa2UgZm9yY2VGbHVzaCBmb3IgU1NSIGNhbiBiZSBwdXQgaGVyZVxuICAgICAgICAgKi9cbiAgICAgICAgW2tleTogc3RyaW5nXTogdW5rbm93bjtcbiAgICAgIH1cbiAgICBdXG4gICk6IHZvaWQge31cblxuICAvKipcbiAgICogIG92ZXJyaWRlIGJ5IHN1YmNsYXNzXG4gICAqIEBwYXJhbSBuZXdEYXRhXG4gICAqL1xuICBvbk5hdGl2ZUFwcFJlYWR5KCk6IHZvaWQge31cblxuICAvKipcbiAgICogIG92ZXJyaWRlIGJ5IHN1YmNsYXNzXG4gICAqIEBwYXJhbSBuZXdEYXRhXG4gICAqL1xuICBvbkFwcEZpcnN0U2NyZWVuKCk6IHZvaWQge31cblxuICAvKipcbiAgICogIG92ZXJyaWRlIGJ5IHN1YmNsYXNzXG4gICAqIEBwYXJhbSBuZXdEYXRhXG4gICAqL1xuICBvbkFwcEVudGVyQmFja2dyb3VuZCgpOiB2b2lkIHt9XG5cbiAgLyoqXG4gICAqICBvdmVycmlkZSBieSBzdWJjbGFzc1xuICAgKiBAcGFyYW0gbmV3RGF0YVxuICAgKi9cbiAgb25BcHBFbnRlckZvcmVncm91bmQoKTogdm9pZCB7fVxuXG4gIGFic3RyYWN0IGNyZWF0ZUx5bngoXG4gICAgbmF0aXZlTHlueDogTmF0aXZlTHlueFByb3h5LFxuICAgIHByb21pc2VDdG9yOiBQcm9taXNlQ29uc3RydWN0b3JcbiAgKTogTHlueEltcGw7XG59XG5cbmZ1bmN0aW9uIHBhdGhQcm9jZXNzKHBhdGg6IHN0cmluZyk6IHN0cmluZyB7XG4gIGNvbnN0IG1hdGNoID0gcGF0aC5tYXRjaCgvKC4qKVxcLyhbXi9dKyk/JC8pO1xuICByZXR1cm4gbWF0Y2g/LlsxXSA/IG1hdGNoWzFdIDogJy4vJztcbn1cblxuZnVuY3Rpb24gaW5SZXF1aXJlKHBhdGg6IHN0cmluZyk6IEZ1bmN0aW9uIHtcbiAgY29uc3QgdGhhdCA9IHRoaXM7XG4gIGNvbnN0IHB3ZCA9IHBhdGhQcm9jZXNzKHBhdGgpO1xuXG4gIHJldHVybiBmdW5jdGlvbiAocGF0aCkge1xuICAgIGNvbnN0IHQgPSBbXTtcbiAgICBjb25zdCByID0gYCR7cHdkfS8ke3BhdGh9YC5zcGxpdCgnLycpO1xuICAgIGNvbnN0IGkgPSByLmxlbmd0aDtcblxuICAgIGlmICh0eXBlb2YgcGF0aCAhPT0gJ3N0cmluZycpIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcigncmVxdWlyZSBhcmdzIG11c3QgYmUgYSBzdHJpbmcnKTtcbiAgICB9XG4gICAgZm9yIChsZXQgbyA9IDA7IG8gPCBpOyArK28pIHtcbiAgICAgIGNvbnN0IGEgPSByW29dO1xuICAgICAgaWYgKGEgIT09ICcnICYmIGEgIT09ICcuJykge1xuICAgICAgICBpZiAoYSA9PT0gJy4uJykge1xuICAgICAgICAgIGlmICh0Lmxlbmd0aCA9PT0gMCkge1xuICAgICAgICAgICAgdGhyb3cgbmV3IEVycm9yKFxuICAgICAgICAgICAgICBgY2FuJ3QgZmluZCBtb2R1bGUgJHtwYXRofSBpbiBhcHA6ICR7dGhhdC5fbmF0aXZlQXBwLmlkfWBcbiAgICAgICAgICAgICk7XG4gICAgICAgICAgfVxuICAgICAgICAgIHQucG9wKCk7XG4gICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgbyArIDEgPCBpICYmIHJbbyArIDFdID09PSAnLi4nID8gbysrIDogdC5wdXNoKGEpO1xuICAgICAgICB9XG4gICAgICB9XG4gICAgfVxuICAgIGxldCBjID0gdC5qb2luKCcvJyk7XG4gICAgLyogZXNsaW50LWRpc2FibGUgbm8tcmV0dXJuLWFzc2lnbiAqL1xuICAgIC8qIGVzbGludC1kaXNhYmxlIG5vLXNlcXVlbmNlcyAqL1xuICAgIHJldHVybiBjLmVuZHNXaXRoKCcuanMnKSB8fCAoYyArPSAnLmpzJyksIHRoYXQucmVxdWlyZShjKTtcbiAgfTtcbn1cblxuZnVuY3Rpb24gdHJ5R2V0TG9hZFNjcmlwdENhY2hlKFxuICBjYWNoZUtleTogc3RyaW5nIHwgdW5kZWZpbmVkXG4pOiBCdW5kbGVJbml0UmV0dXJuT2JqIHwgdW5kZWZpbmVkIHwgRnVuY3Rpb24ge1xuICBpZiAoIWNhY2hlS2V5KSB7XG4gICAgcmV0dXJuIHVuZGVmaW5lZDtcbiAgfVxuICByZXR1cm4gQmFzZUFwcC5fJGxvYWRTY3JpcHRDYWNoZVtjYWNoZUtleV07XG59XG5cbmZ1bmN0aW9uIGFkZExvYWRTY3JpcHRDYWNoZShcbiAgY2FjaGVLZXk6IHN0cmluZyB8IHVuZGVmaW5lZCxcbiAgZXhwb3J0czogQnVuZGxlSW5pdFJldHVybk9iaiB8IHVuZGVmaW5lZCB8IEZ1bmN0aW9uXG4pIHtcbiAgaWYgKCFjYWNoZUtleSB8fCAhZXhwb3J0cykge1xuICAgIHJldHVybjtcbiAgfVxuICBCYXNlQXBwLl8kbG9hZFNjcmlwdENhY2hlW2NhY2hlS2V5XSA9IGV4cG9ydHM7XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuaW1wb3J0IHsgQmFzZUFwcCB9IGZyb20gJy4uL2FwcCc7XG5pbXBvcnQgeyBMeW54LCBOYXRpdmVMeW54UHJveHkgfSBmcm9tICcuLi9seW54JztcbmltcG9ydCB7IENhY2hlZEZ1bmN0aW9uUHJveHkgfSBmcm9tICcuLi91dGlsJztcblxuZXhwb3J0IGNsYXNzIFJlYWN0QXBwIGV4dGVuZHMgQmFzZUFwcCB7XG4gIGNyZWF0ZUx5bngoXG4gICAgbmF0aXZlTHlueDogTmF0aXZlTHlueFByb3h5LFxuICAgIHByb21pc2VDdG9yOiBQcm9taXNlQ29uc3RydWN0b3JcbiAgKTogTHlueCB7XG4gICAgY29uc3QgbHlueF9wcm94eSA9IENhY2hlZEZ1bmN0aW9uUHJveHkuY3JlYXRlKG5hdGl2ZUx5bngpO1xuICAgIHJldHVybiBuZXcgTHlueChcbiAgICAgICgpID0+IHRoaXMubmF0aXZlQXBwLFxuICAgICAgKCkgPT4gdGhpcyxcbiAgICAgIHByb21pc2VDdG9yLFxuICAgICAgKCkgPT4gbHlueF9wcm94eVxuICAgICk7XG4gIH1cblxuICBjYWxsQmVmb3JlUHVibGlzaEV2ZW50KGV2ZW50RGF0YT86IGFueSk6IHZvaWQge1xuICAgIGlmIChcbiAgICAgIHRoaXMuX2FvcE1hbmFnZXIuX2JlZm9yZVB1Ymxpc2hFdmVudC5nZXRFdmVudHNTaXplKGV2ZW50RGF0YS50eXBlKSAhPT0gMFxuICAgICkge1xuICAgICAgY29uc3QgY29weURhdGEgPSB7IC4uLmV2ZW50RGF0YSB9O1xuICAgICAgdHJ5IHtcbiAgICAgICAgdGhpcy5fYW9wTWFuYWdlci5fYmVmb3JlUHVibGlzaEV2ZW50LmVtaXQoY29weURhdGEudHlwZSwgW2NvcHlEYXRhXSk7XG4gICAgICB9IGNhdGNoIChlKSB7XG4gICAgICAgIHRoaXMuaGFuZGxlVXNlckVycm9yKGUsIHtcbiAgICAgICAgICBieTogJ2NhbGxCZWZvcmVQdWJsaXNoRXZlbnQnLFxuICAgICAgICAgIHR5cGU6IChjb3B5RGF0YSBhcyBhbnkpLnR5cGUsXG4gICAgICAgIH0pO1xuICAgICAgfVxuICAgIH1cbiAgfVxufVxuIiwgIi8vIENvcHlyaWdodCAyMDI0IFRoZSBMeW54IEF1dGhvcnMuIEFsbCByaWdodHMgcmVzZXJ2ZWQuXG4vLyBMaWNlbnNlZCB1bmRlciB0aGUgQXBhY2hlIExpY2Vuc2UgVmVyc2lvbiAyLjAgdGhhdCBjYW4gYmUgZm91bmQgaW4gdGhlXG4vLyBMSUNFTlNFIGZpbGUgaW4gdGhlIHJvb3QgZGlyZWN0b3J5IG9mIHRoaXMgc291cmNlIHRyZWUuXG5cbmltcG9ydCB7IERFRkFVTFRfRU5UUlkgfSBmcm9tICcuLi9jb21tb24nO1xuaW1wb3J0IHsgQXBwUHJveHlQYXJhbXMsIEJhc2VBcHAsIGxvYWRDYXJkUGFyYW1zLCBOYXRpdmVBcHAgfSBmcm9tICcuLi9hcHAnO1xuaW1wb3J0IHsgTHlueCwgTmF0aXZlTHlueFByb3h5IH0gZnJvbSAnLi4vbHlueCc7XG5pbXBvcnQgeyBDYWNoZWRGdW5jdGlvblByb3h5IH0gZnJvbSAnLi4vdXRpbCc7XG5cbmV4cG9ydCBkZWZhdWx0IGNsYXNzIFN0YW5kYWxvbmVBcHAgZXh0ZW5kcyBCYXNlQXBwIHtcbiAgY29uc3RydWN0b3Iob3B0aW9uczogQXBwUHJveHlQYXJhbXM8TmF0aXZlQXBwPiwgcGFyYW1zOiBsb2FkQ2FyZFBhcmFtcykge1xuICAgIHN1cGVyKG9wdGlvbnMsIHVuZGVmaW5lZCk7XG4gICAgdHJ5IHtcbiAgICAgIGlmIChwYXJhbXMuc3JjTmFtZSkge1xuICAgICAgICBkZWxldGUgdGhpcy5seW54LnJlcXVpcmVNb2R1bGUuY2FjaGVbcGFyYW1zLnNyY05hbWVdO1xuICAgICAgICBkZWxldGUgQmFzZUFwcC5fJGZhY3RvcnlDYWNoZVtwYXJhbXMuc3JjTmFtZV07XG4gICAgICAgIHRoaXMubHlueC5yZXF1aXJlTW9kdWxlKHBhcmFtcy5zcmNOYW1lLCBERUZBVUxUX0VOVFJZKTtcbiAgICAgICAgdGhpcy5kYXRhVHlwZVNldC5hZGQoJ3VuZGVmaW5lZCcpO1xuICAgICAgfVxuICAgIH0gY2F0Y2ggKGUpIHtcbiAgICAgIHRoaXMuaGFuZGxlVXNlckVycm9yKGUpO1xuICAgIH1cbiAgfVxuXG4gIGNyZWF0ZUx5bngobmF0aXZlTHlueDogTmF0aXZlTHlueFByb3h5LCBwcm9taXNlOiBQcm9taXNlQ29uc3RydWN0b3IpOiBMeW54IHtcbiAgICBjb25zdCBseW54X3Byb3h5ID0gQ2FjaGVkRnVuY3Rpb25Qcm94eS5jcmVhdGUobmF0aXZlTHlueCk7XG4gICAgcmV0dXJuIG5ldyBMeW54KFxuICAgICAgKCkgPT4gdGhpcy5uYXRpdmVBcHAsXG4gICAgICAoKSA9PiB0aGlzLFxuICAgICAgcHJvbWlzZSxcbiAgICAgICgpID0+IGx5bnhfcHJveHlcbiAgICApO1xuICB9XG59XG4iLCAiLy8gQ29weXJpZ2h0IDIwMjQgVGhlIEx5bnggQXV0aG9ycy4gQWxsIHJpZ2h0cyByZXNlcnZlZC5cbi8vIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSBWZXJzaW9uIDIuMCB0aGF0IGNhbiBiZSBmb3VuZCBpbiB0aGVcbi8vIExJQ0VOU0UgZmlsZSBpbiB0aGUgcm9vdCBkaXJlY3Rvcnkgb2YgdGhpcyBzb3VyY2UgdHJlZS5cblxuLy8gc3RhcnQganMgYXBwLCBuYXRpdmUgaGFzIGRlY29kZSBqcyBjb2RlO1xuLy8gcmV0dXJuIG1lYW5zIGxvYWRDYXJkIHN1Y2Nlc3Mgb3IgZmFpbGVkLlxuaW1wb3J0IHsgQmFzZUFwcCwgbG9hZENhcmRQYXJhbXMsIE5hdGl2ZUFwcCB9IGZyb20gJy4vYXBwJztcbmltcG9ydCB7IEx5bngsIE5hdGl2ZUx5bnhQcm94eSB9IGZyb20gJy4vbHlueCc7XG5pbXBvcnQgeyBhbG9nIH0gZnJvbSAnLi9jb21tb24vbG9nJztcbmltcG9ydCBuYXRpdmVHbG9iYWwgZnJvbSAnLi9jb21tb24vbmF0aXZlR2xvYmFsJztcbmltcG9ydCB7IEFQUF9TRVJWSUNFX05BTUUsIERFRkFVTFRfRU5UUlksIEx5bnhGZWF0dXJlIH0gZnJvbSAnLi9jb21tb24nO1xuaW1wb3J0IHsgUmVhY3RBcHAgfSBmcm9tICcuL3JlYWN0L3JlYWN0QXBwJztcbmltcG9ydCB7IEludGVybmFsUnVudGltZUVycm9yLCByZXBvcnRFcnJvciB9IGZyb20gJy4vbW9kdWxlcy9yZXBvcnQnO1xuaW1wb3J0IFN0YW5kYWxvbmVBcHAgZnJvbSAnLi9zdGFuZGFsb25lL1N0YW5kYWxvbmVBcHAnO1xuXG5leHBvcnQgZnVuY3Rpb24gbG9hZENhcmQoXG4gIG5hdGl2ZUFwcDogTmF0aXZlQXBwLFxuICBwYXJhbXM6IGxvYWRDYXJkUGFyYW1zLFxuICBseW54PzogTmF0aXZlTHlueFByb3h5XG4pOiBib29sZWFuIHtcbiAgY29uc3QgeyBpZCB9ID0gbmF0aXZlQXBwO1xuICBjb25zdCB7IGNhcmRUeXBlIH0gPSBwYXJhbXM7XG4gIGFsb2coYGxvYWQgY2FyZCBuYXRpdmUgYXBwIGlkOiAke2lkfWApO1xuICBsZXQgbG9hZFN1Y2Nlc3M6IGJvb2xlYW4gPSB0cnVlO1xuICBsZXQgdHQ6IFJlYWN0QXBwIHwgU3RhbmRhbG9uZUFwcDtcbiAgdHJ5IHtcbiAgICBpZiAoY2FyZFR5cGUgPT0gJ3N0YW5kYWxvbmUnKSB7XG4gICAgICB0dCA9IG5ldyBTdGFuZGFsb25lQXBwKHsgbmF0aXZlQXBwLCBwYXJhbXMsIGx5bnggfSwgcGFyYW1zKTtcbiAgICB9IGVsc2Uge1xuICAgICAgdHQgPSBuZXcgUmVhY3RBcHAoXG4gICAgICAgIHtcbiAgICAgICAgICBuYXRpdmVBcHAsXG4gICAgICAgICAgcGFyYW1zLFxuICAgICAgICAgIGx5bngsXG4gICAgICAgIH0sXG4gICAgICAgIG5hdGl2ZUdsb2JhbD8ubXVsdGlBcHBzW2lkXVxuICAgICAgKTtcbiAgICB9XG4gICAgbmF0aXZlR2xvYmFsLmN1cnJlbnRBcHBJZCA9IGlkO1xuICAgIG5hdGl2ZUdsb2JhbC5tdWx0aUFwcHNbaWRdID0gdHQ7XG5cbiAgICBpZiAoY2FyZFR5cGUgPT09ICdzdGFuZGFsb25lJykge1xuICAgICAgbmF0aXZlQXBwLnNldENhcmQodHQpO1xuICAgICAgcmV0dXJuIHRydWU7XG4gICAgfVxuXG4gICAgYWxvZyhcbiAgICAgIGBsb2FkIGNhcmQgbmF0aXZlIGFwcCBsb2FkIGFwcC1zZXJ2aWNlLmpzIHBhcmFtcy5idW5kbGVTdXBwb3J0TG9hZFNjcmlwdCAke3BhcmFtcy5idW5kbGVTdXBwb3J0TG9hZFNjcmlwdH1gXG4gICAgKTtcbiAgICBsb2FkU3VjY2VzcyA9IHRydWU7XG4gICAgdHJ5IHtcbiAgICAgIGRlbGV0ZSB0dC5seW54LnJlcXVpcmVNb2R1bGUuY2FjaGVbQVBQX1NFUlZJQ0VfTkFNRV07XG4gICAgICBkZWxldGUgQmFzZUFwcC5fJGZhY3RvcnlDYWNoZVtBUFBfU0VSVklDRV9OQU1FXTtcbiAgICAgIHR0Lmx5bngucmVxdWlyZU1vZHVsZShBUFBfU0VSVklDRV9OQU1FLCBERUZBVUxUX0VOVFJZKTtcbiAgICAgIGlmICh0dC5seW54Ll9zd2l0Y2hlc1snYWxsb3dVbmRlZmluZWRJbk5hdGl2ZURhdGFUeXBlU2V0J10pIHtcbiAgICAgICAgdHQuZGF0YVR5cGVTZXQuYWRkKCd1bmRlZmluZWQnKTtcbiAgICAgIH1cbiAgICB9IGNhdGNoIChlKSB7XG4gICAgICBsb2FkU3VjY2VzcyA9IGZhbHNlO1xuICAgICAgdHQuaGFuZGxlVXNlckVycm9yKGUsIHVuZGVmaW5lZCwgdW5kZWZpbmVkLCAnbG9hZENhcmQgZmFpbGVkJyk7XG4gICAgfVxuICAgIG5hdGl2ZUFwcC5zZXRDYXJkKHR0KTtcbiAgfSBjYXRjaCAoZSkge1xuICAgIGhhbmRsZUxvYWRDYXJkRXJyb3IobmF0aXZlQXBwLCBlKTtcbiAgICBsb2FkU3VjY2VzcyA9IGZhbHNlO1xuICB9XG4gIHJldHVybiBsb2FkU3VjY2Vzcztcbn1cblxuZXhwb3J0IGZ1bmN0aW9uIGRlc3Ryb3lDYXJkKGlkOiBzdHJpbmcpOiB2b2lkIHtcbiAgYWxvZyhgZGVzdHJveSAke2lkfWApO1xuICBjb25zdCBhcHBJbnN0YW5jZSA9IG5hdGl2ZUdsb2JhbC5tdWx0aUFwcHNbaWRdO1xuICBhcHBJbnN0YW5jZS5kZXN0cm95KCk7XG4gIC8vIGVzbGludC1kaXNhYmxlLW5leHQtbGluZSBAdHlwZXNjcmlwdC1lc2xpbnQvbm8tZHluYW1pYy1kZWxldGVcbiAgZGVsZXRlIG5hdGl2ZUdsb2JhbC5tdWx0aUFwcHNbaWRdO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gY2FsbERlc3Ryb3lMaWZldGltZUZ1bihpZDogc3RyaW5nKTogdm9pZCB7XG4gIGFsb2coYGNhbGxEZXN0cm95TGlmZXRpbWVGdW4gJHtpZH1gKTtcbiAgY29uc3QgYXBwSW5zdGFuY2UgPSBuYXRpdmVHbG9iYWwubXVsdGlBcHBzW2lkXTtcbiAgYXBwSW5zdGFuY2UuY2FsbERlc3Ryb3lMaWZldGltZUZ1bigpO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gbG9hZER5bmFtaWNDb21wb25lbnQ8VD4odHQ6IEJhc2VBcHAsIGNvbXBvbmVudFVybDogc3RyaW5nKTogVCB7XG4gIGlmICh0dC5sb2FkZWREeW5hbWljQ29tcG9uZW50c1NldC5oYXMoY29tcG9uZW50VXJsKSkge1xuICAgIHJldHVybiB0dC5nZXREeW5hbWljQ29tcG9uZW50RXhwb3J0cyhjb21wb25lbnRVcmwpO1xuICB9XG5cbiAgY29uc3QgcHJlRW50cnkgPSBuYXRpdmVHbG9iYWwuZ2xvYkR5bmFtaWNDb21wb25lbnRFbnRyeTtcbiAgbmF0aXZlR2xvYmFsLmdsb2JEeW5hbWljQ29tcG9uZW50RW50cnkgPSBjb21wb25lbnRVcmw7XG5cbiAgdHJ5IHtcbiAgICBkZWxldGUgdHQubHlueC5yZXF1aXJlTW9kdWxlLmNhY2hlW0FQUF9TRVJWSUNFX05BTUVdO1xuICAgIGRlbGV0ZSBCYXNlQXBwLl8kZmFjdG9yeUNhY2hlW0FQUF9TRVJWSUNFX05BTUVdO1xuICAgIGNvbnN0IHJldCA9IHR0Lmx5bngucmVxdWlyZU1vZHVsZTxUPihBUFBfU0VSVklDRV9OQU1FLCBjb21wb25lbnRVcmwpO1xuICAgIHR0LnNhdmVEeW5hbWljQ29tcG9uZW50RXhwb3J0cyhjb21wb25lbnRVcmwsIHJldCk7XG4gICAgdHQubG9hZGVkRHluYW1pY0NvbXBvbmVudHNTZXQuYWRkKGNvbXBvbmVudFVybCk7XG4gICAgcmV0dXJuIHJldDtcbiAgfSBjYXRjaCAoZXJyb3IpIHtcbiAgICB0dC5oYW5kbGVVc2VyRXJyb3IoZXJyb3IpO1xuICB9IGZpbmFsbHkge1xuICAgIC8vIEhlcmUgcmVzZXQgZ2xvYkR5bmFtaWNDb21wb25lbnRFbnRyeSB0byBhdm9pZCBhZmZlY3Qgb3RoZXIgTHlueFZpZXcgaW4gdGhlIHNhbWUgTHlueEdyb3VwXG4gICAgLy8gZGV0YWlsIHNlZTogIzg3MjBcbiAgICBuYXRpdmVHbG9iYWwuZ2xvYkR5bmFtaWNDb21wb25lbnRFbnRyeSA9IHByZUVudHJ5O1xuICB9XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBoYW5kbGVMb2FkQ2FyZEVycm9yKFxuICBuYXRpdmVBcHA6IE5hdGl2ZUFwcCxcbiAgZXJyb3I/OiBFcnJvcixcbiAgY2F1c2U/OiB1bmtub3duXG4pIHtcbiAgbGV0IHsgbWVzc2FnZSwgbmFtZSwgc3RhY2sgfSA9IGVycm9yIHx8IHt9O1xuICBpZiAoIW1lc3NhZ2UpIHtcbiAgICAvLyBJZiB0aGVyZSBpcyBubyBlcnJvciBtZXNzYWdlIGluIGVycm9yLCBtZWFucyB0aGF0IGl0IGlzIG5vdCBhbiBlcnJvci1saWtlIG9iamVjdC5cbiAgICAvLyBXZSBjb25zdHJ1Y3QgYSBuZXcgRXJyb3IgdXNpbmcgSlNPTi5zdHJpbmdpZnlcbiAgICAoeyBtZXNzYWdlLCBuYW1lLCBzdGFjayB9ID0gbmV3IEVycm9yKEpTT04uc3RyaW5naWZ5KGVycm9yKSkpO1xuICB9XG4gIGNvbnN0IGludGVybmFsRXJyb3IgPSBuZXcgSW50ZXJuYWxSdW50aW1lRXJyb3IoXG4gICAgYGxvYWRDYXJkIGZhaWxlZCAke25hbWV9OiAke21lc3NhZ2V9YCxcbiAgICBzdGFja1xuICApO1xuICBpbnRlcm5hbEVycm9yLmNhdXNlID0gY2F1c2U7XG4gIHJlcG9ydEVycm9yKGludGVybmFsRXJyb3IsIG5hdGl2ZUFwcCwge1xuICAgIG9yaWdpbkVycm9yOiBlcnJvcixcbiAgICBnZXRTb3VyY2VNYXBSZWxlYXNlOiAodXJsOiBzdHJpbmcpOiBzdHJpbmcgPT4ge1xuICAgICAgbGV0IHJldCA9IG5hdGl2ZUFwcC5fX0dldFNvdXJjZU1hcFJlbGVhc2UodXJsKTtcbiAgICAgIGlmICghcmV0KSB7XG4gICAgICAgIHJldHVybiBuYXRpdmVBcHAuX19HZXRTb3VyY2VNYXBSZWxlYXNlKEJhc2VBcHAua0RlZmF1bHRTb3VyY2VNYXBVUkwpO1xuICAgICAgfVxuICAgIH0sXG4gIH0pO1xufVxuIiwgIi8qKlxuICogQHNlZTogaHR0cHM6Ly9kZXZlbG9wZXIuYXBwbGUuY29tL2RvY3VtZW50YXRpb24vamF2YXNjcmlwdGNvcmUvMTY0NDU5OC1qc29iamVjdG1ha2V0eXBlZGFycmF5d2l0aGFycmF5YlxuICogQGRlc2NyaXB0aW9uOiBKYXZhU2NyaXB0IENvcmUgcHJvdmlkZSBBcnJheUJ1ZmZlciBBUEkgSW4gSlNSdW50aW1lLiBCdXQgZGlkIG5vdCBleHBvcnQgc29tZSBjLWFwaSBvbiBpT1M5LlxuICovXG5cbi8vIGJhc2U2NCBjaGFyYWN0ZXIgc2V0LCBwbHVzIHBhZGRpbmcgY2hhcmFjdGVyICg9KVxuY29uc3QgY2hhcnMgPVxuICAnQUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ejAxMjM0NTY3ODkrLyc7XG4vLyBSZWd1bGFyIGV4cHJlc3Npb24gdG8gY2hlY2sgZm9ybWFsIGNvcnJlY3RuZXNzIG9mIGJhc2U2NCBlbmNvZGVkIHN0cmluZ3NcbmNvbnN0IGxvb2t1cCA9IG5ldyBVaW50OEFycmF5KDI1Nik7XG5mb3IgKGxldCBpID0gMDsgaSA8IGNoYXJzLmxlbmd0aDsgaSsrKSB7XG4gIGxvb2t1cFtjaGFycy5jaGFyQ29kZUF0KGkpXSA9IGk7XG59XG5cbmV4cG9ydCBmdW5jdGlvbiBhcnJheUJ1ZmZlclRvQmFzZTY0KGJ1ZmZlcjogQXJyYXlCdWZmZXIpOiBzdHJpbmcge1xuICB2YXIgYnl0ZXMgPSBuZXcgVWludDhBcnJheShidWZmZXIpO1xuICB2YXIgaTogbnVtYmVyO1xuICB2YXIgbGVuOiBudW1iZXIgPSBieXRlcy5sZW5ndGg7XG4gIHZhciBiYXNlNjQgPSAnJztcblxuICBmb3IgKGkgPSAwOyBpIDwgbGVuOyBpICs9IDMpIHtcbiAgICBiYXNlNjQgKz0gY2hhcnNbYnl0ZXNbaV0gPj4gMl07XG4gICAgYmFzZTY0ICs9IGNoYXJzWygoYnl0ZXNbaV0gJiAzKSA8PCA0KSB8IChieXRlc1tpICsgMV0gPj4gNCldO1xuICAgIGJhc2U2NCArPSBjaGFyc1soKGJ5dGVzW2kgKyAxXSAmIDE1KSA8PCAyKSB8IChieXRlc1tpICsgMl0gPj4gNildO1xuICAgIGJhc2U2NCArPSBjaGFyc1tieXRlc1tpICsgMl0gJiA2M107XG4gIH1cblxuICBpZiAobGVuICUgMyA9PT0gMikge1xuICAgIGJhc2U2NCA9IGJhc2U2NC5zdWJzdHJpbmcoMCwgYmFzZTY0Lmxlbmd0aCAtIDEpICsgJz0nO1xuICB9IGVsc2UgaWYgKGxlbiAlIDMgPT09IDEpIHtcbiAgICBiYXNlNjQgPSBiYXNlNjQuc3Vic3RyaW5nKDAsIGJhc2U2NC5sZW5ndGggLSAyKSArICc9PSc7XG4gIH1cblxuICByZXR1cm4gYmFzZTY0O1xufVxuXG5leHBvcnQgZnVuY3Rpb24gYmFzZTY0VG9BcnJheUJ1ZmZlcihiYXNlNjQ6IHN0cmluZyk6IEFycmF5QnVmZmVyIHtcbiAgbGV0IGJ1ZmZlckxlbmd0aDogbnVtYmVyID0gYmFzZTY0Lmxlbmd0aCAqIDAuNzU7XG4gIGNvbnN0IGxlbjogbnVtYmVyID0gYmFzZTY0Lmxlbmd0aDtcbiAgbGV0IGk7XG4gIGxldCBwID0gMDtcbiAgbGV0IGVuY29kZWQxO1xuICBsZXQgZW5jb2RlZDI7XG4gIGxldCBlbmNvZGVkMztcbiAgbGV0IGVuY29kZWQ0O1xuXG4gIGlmIChiYXNlNjRbYmFzZTY0Lmxlbmd0aCAtIDFdID09PSAnPScpIHtcbiAgICBidWZmZXJMZW5ndGgtLTtcbiAgICBpZiAoYmFzZTY0W2Jhc2U2NC5sZW5ndGggLSAyXSA9PT0gJz0nKSB7XG4gICAgICBidWZmZXJMZW5ndGgtLTtcbiAgICB9XG4gIH1cblxuICBsZXQgYXJyYXlidWZmZXIgPSBuZXcgQXJyYXlCdWZmZXIoYnVmZmVyTGVuZ3RoKTtcbiAgbGV0IGJ5dGVzID0gbmV3IFVpbnQ4QXJyYXkoYXJyYXlidWZmZXIpO1xuXG4gIGZvciAoaSA9IDA7IGkgPCBsZW47IGkgKz0gNCkge1xuICAgIGVuY29kZWQxID0gbG9va3VwW2Jhc2U2NC5jaGFyQ29kZUF0KGkpXTtcbiAgICBlbmNvZGVkMiA9IGxvb2t1cFtiYXNlNjQuY2hhckNvZGVBdChpICsgMSldO1xuICAgIGVuY29kZWQzID0gbG9va3VwW2Jhc2U2NC5jaGFyQ29kZUF0KGkgKyAyKV07XG4gICAgZW5jb2RlZDQgPSBsb29rdXBbYmFzZTY0LmNoYXJDb2RlQXQoaSArIDMpXTtcblxuICAgIGJ5dGVzW3ArK10gPSAoZW5jb2RlZDEgPDwgMikgfCAoZW5jb2RlZDIgPj4gNCk7XG4gICAgYnl0ZXNbcCsrXSA9ICgoZW5jb2RlZDIgJiAxNSkgPDwgNCkgfCAoZW5jb2RlZDMgPj4gMik7XG4gICAgYnl0ZXNbcCsrXSA9ICgoZW5jb2RlZDMgJiAzKSA8PCA2KSB8IChlbmNvZGVkNCAmIDYzKTtcbiAgfVxuXG4gIHJldHVybiBhcnJheWJ1ZmZlcjtcbn1cbiIsICIvLyBDb3B5cmlnaHQgMjAyNCBUaGUgTHlueCBBdXRob3JzLiBBbGwgcmlnaHRzIHJlc2VydmVkLlxuLy8gTGljZW5zZWQgdW5kZXIgdGhlIEFwYWNoZSBMaWNlbnNlIFZlcnNpb24gMi4wIHRoYXQgY2FuIGJlIGZvdW5kIGluIHRoZVxuLy8gTElDRU5TRSBmaWxlIGluIHRoZSByb290IGRpcmVjdG9yeSBvZiB0aGlzIHNvdXJjZSB0cmVlLlxuaW1wb3J0IHtcbiAgbG9hZENhcmQsXG4gIGRlc3Ryb3lDYXJkLFxuICBjYWxsRGVzdHJveUxpZmV0aW1lRnVuLFxuICBsb2FkRHluYW1pY0NvbXBvbmVudCxcbn0gZnJvbSAnLi9hcHBNYW5hZ2VyJztcbmltcG9ydCB7IGFycmF5QnVmZmVyVG9CYXNlNjQsIGJhc2U2NFRvQXJyYXlCdWZmZXIgfSBmcm9tICcuL3BvbHlmaWxsJztcbmltcG9ydCBuYXRpdmVHbG9iYWwgZnJvbSAnLi9jb21tb24vbmF0aXZlR2xvYmFsJztcbmltcG9ydCB7XG4gIGNyZWF0ZUV2ZW50RW1pdHRlcixcbiAgbGVnYWN5UmVwb3J0RXJyb3IsXG4gIHdyYXBJbm5lckZ1bmN0aW9uLFxuICB3cmFwVXNlckZ1bmN0aW9uLFxufSBmcm9tICcuL21vZHVsZXMnO1xuaW1wb3J0IHtcbiAgSGVhZGVycyxcbiAgVVJMLFxuICBVUkxTZWFyY2hQYXJhbXNQb2x5ZmlsbCxcbiAgQWJvcnRDb250cm9sbGVyLFxuICBBYm9ydFNpZ25hbCxcbiAgVGV4dEVuY29kZXIsXG4gIFRleHREZWNvZGVyLFxufSBmcm9tICcuL21vZHVsZXMvZmV0Y2gnO1xuXG5leHBvcnQgeyBsb2FkQ2FyZCwgZGVzdHJveUNhcmQsIGNhbGxEZXN0cm95TGlmZXRpbWVGdW4sIGxvYWREeW5hbWljQ29tcG9uZW50IH07XG5cbm5hdGl2ZUdsb2JhbC5sb2FkQ2FyZCA9IGxvYWRDYXJkO1xubmF0aXZlR2xvYmFsLmRlc3Ryb3lDYXJkID0gZGVzdHJveUNhcmQ7XG5uYXRpdmVHbG9iYWwuY2FsbERlc3Ryb3lMaWZldGltZUZ1biA9IGNhbGxEZXN0cm95TGlmZXRpbWVGdW47XG5uYXRpdmVHbG9iYWwubG9hZER5bmFtaWNDb21wb25lbnQgPSBsb2FkRHluYW1pY0NvbXBvbmVudDtcbi8qKlxuICogb25seSBmb3IgbHlueCBuYXRpdmUgcnVudGltZVxuICovXG5uYXRpdmVHbG9iYWwuX19jcmVhdGVFdmVudEVtaXR0ZXIgPSBjcmVhdGVFdmVudEVtaXR0ZXI7XG5uYXRpdmVHbG9iYWwuX19seW54QXJyYXlCdWZmZXJUb0Jhc2U2NCA9IGFycmF5QnVmZmVyVG9CYXNlNjQ7XG5uYXRpdmVHbG9iYWwuX19seW54QmFzZTY0VG9BcnJheUJ1ZmZlciA9IGJhc2U2NFRvQXJyYXlCdWZmZXI7XG5uYXRpdmVHbG9iYWwuTHlueFNES0NvcmUgPSB7XG4gIHJlcG9ydDogbGVnYWN5UmVwb3J0RXJyb3IsXG4gIHJlcG9ydElubmVyOiB3cmFwSW5uZXJGdW5jdGlvbixcbiAgcmVwb3J0VXNlcjogd3JhcFVzZXJGdW5jdGlvbixcbn07XG5cbm5hdGl2ZUdsb2JhbC5IZWFkZXJzID0gSGVhZGVycztcbm5hdGl2ZUdsb2JhbC5BYm9ydENvbnRyb2xsZXIgPSBBYm9ydENvbnRyb2xsZXI7XG5uYXRpdmVHbG9iYWwuQWJvcnRTaWduYWwgPSBBYm9ydFNpZ25hbDtcbm5hdGl2ZUdsb2JhbC5VUkwgPSBVUkw7XG5VUkxTZWFyY2hQYXJhbXNQb2x5ZmlsbChuYXRpdmVHbG9iYWwpO1xuIl0sCiAgIm1hcHBpbmdzIjogIjs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7O0FBQUE7QUFBQSwyQ0FBQUEsU0FBQTtBQUFBO0FBd0JBLGVBQVNDLFFBQU87QUFBQSxNQUFDO0FBa0JqQixVQUFJLGFBQWE7QUFDakIsVUFBSSxXQUFXLENBQUM7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QUFBLHNCQUFhLDRCQUE0QjtBQUN6QyxFQUFBQSxzQkFBYSw0QkFBNEI7QUFDekMsRUFBQUEsc0JBQWEsY0FBYztBQUFBLElBQ3pCLFFBQVE7QUFBQSxJQUNSLGFBQWE7QUFBQSxJQUNiLFlBQVk7QUFBQSxFQUNkO0FBRUEsRUFBQUEsc0JBQWEsVUFBVUM7QUFDdkIsRUFBQUQsc0JBQWEsa0JBQWtCO0FBQy9CLEVBQUFBLHNCQUFhLGNBQWM7QUFDM0IsRUFBQUEsc0JBQWEsTUFBTTtBQUNuQiwwQkFBd0JBLHFCQUFZOyIsCiAgIm5hbWVzIjogWyJtb2R1bGUiLCAibm9vcCIsICJQcm9taXNlIiwgInJlc29sdmUiLCAicmVqZWN0IiwgIm1vZHVsZSIsICJQcm9taXNlIiwgImkiLCAidmFsIiwgIm1vZHVsZSIsICJQcm9taXNlIiwgInNldFRpbWVvdXQiLCAiaWQiLCAibW9kdWxlIiwgInNldFRpbWVvdXQiLCAiUHJvbWlzZSIsICJtb2R1bGUiLCAiZXhwb3J0cyIsICJ1bmRlZmluZWQiLCAidmFsdWUiLCAia2V5IiwgIm5leHQiLCAiZ2xvYmFsVGhpcyIsICJpbXBvcnRfcnVudGltZSIsICJfZ2xvYmFsIiwgInR0Q29uc29sZV9kZWZhdWx0IiwgInR0Q29uc29sZV9kZWZhdWx0IiwgIm5hdGl2ZUdsb2JhbF9kZWZhdWx0IiwgInR0Q29uc29sZV9kZWZhdWx0IiwgInR0Q29uc29sZV9kZWZhdWx0IiwgImVycm9yIiwgInR0Q29uc29sZV9kZWZhdWx0IiwgIl9hIiwgInBhcmFtcyIsICJQcm9taXNlIiwgIkhlYWRlcnMiLCAiX2EiLCAiSGVhZGVycyIsICJfYSIsICJVUkxTZWFyY2hQYXJhbXNQb2x5ZmlsbCIsICJfYSIsICJfYiIsICJfYSIsICJQcm9taXNlIiwgInBhdGgiLCAiZW50cnlOYW1lIiwgIm1vZHVsZSIsICJuYXRpdmVHbG9iYWxfZGVmYXVsdCIsICJwYXJhbXMiLCAiX2IiLCAiZW50cnlOYW1lIiwgIkxpc3RlbmVyS2V5cyIsICJuYXRpdmVHbG9iYWxfZGVmYXVsdCIsICJzZXRUaW1lb3V0IiwgIm5hdGl2ZUdsb2JhbF9kZWZhdWx0IiwgIm5hdGl2ZUdsb2JhbF9kZWZhdWx0IiwgInBhcmFtcyIsICJtb2R1bGUiLCAiUHJvbWlzZSIsICJwYXRoIiwgImVudHJ5TmFtZSIsICJ0dCIsICJ0aGF0IiwgInNldFRpbWVvdXQiLCAiX2EiLCAiX2IiLCAiX2MiLCAicGFyYW1zIiwgInBhcmFtcyIsICJfYSIsICJ0dCIsICJuYXRpdmVHbG9iYWxfZGVmYXVsdCIsICJuYXRpdmVHbG9iYWxfZGVmYXVsdCIsICJIZWFkZXJzIl0KfQo=
