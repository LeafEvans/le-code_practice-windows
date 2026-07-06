// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';
import { PipelineEntry } from './PipelineEntry';
import { LoadBundleEntry } from './LoadBundleEntry';
import { InitContainerEntry } from './InitContainerEntry';
import { InitLynxviewEntry } from './InitLynxviewEntry';
import { InitBackgroundRuntimeEntry } from './InitBackgroundRuntimeEntry';
import { MetricFcpEntry } from './MetricFcpEntry';
import { MetricFspEntry } from './MetricFspEntry';
import { MetricActualFmpEntry } from './MetricActualFmpEntry';
import { ReloadBundleEntry } from './ReloadBundleEntry';
import { MemoryUsageEntry } from './MemoryUsageEntry';
import { LazyBundleEntry } from './LazyBundleEntry';
import { JSBlockingEntry } from './JSBlockingEntry';

export class PerformanceEntryConverter {
  static makePerformanceEntry(record: Record<string, Object>): PerformanceEntry {
    const name = record['name']?.toString() ?? '';
    const type = record['entryType']?.toString() ?? '';
    let entry: PerformanceEntry;
    if (type === 'pipeline' && name === 'updateTriggeredByBts') {
      entry = new PipelineEntry(record);
    }
    else if (type === 'pipeline' && name === 'updateTriggeredByNative') {
      entry = new PipelineEntry(record);
    }
    else if (type === 'pipeline' && name === 'reactLynxHydrate') {
      entry = new PipelineEntry(record);
    }
    else if (type === 'pipeline' && name === 'setNativeProps') {
      entry = new PipelineEntry(record);
    }
    else if (type === 'pipeline' && name === 'updateGlobalProps') {
      entry = new PipelineEntry(record);
    }
    else if (type === 'pipeline' && name === 'loadBundle') {
      entry = new LoadBundleEntry(record);
    }
    else if (type === 'init' && name === 'container') {
      entry = new InitContainerEntry(record);
    }
    else if (type === 'init' && name === 'lynxview') {
      entry = new InitLynxviewEntry(record);
    }
    else if (type === 'init' && name === 'backgroundRuntime') {
      entry = new InitBackgroundRuntimeEntry(record);
    }
    else if (type === 'metric' && name === 'fcp') {
      entry = new MetricFcpEntry(record);
    }
    else if (type === 'metric' && name === 'fsp') {
      entry = new MetricFspEntry(record);
    }
    else if (type === 'metric' && name === 'actualFmp') {
      entry = new MetricActualFmpEntry(record);
    }
    else if (type === 'pipeline' && name === 'reloadBundleFromNative') {
      entry = new ReloadBundleEntry(record);
    }
    else if (type === 'pipeline' && name === 'reloadBundleFromBts') {
      entry = new ReloadBundleEntry(record);
    }
    else if (type === 'memory' && name === 'memory') {
      entry = new MemoryUsageEntry(record);
    }
    else if (type === 'resource' && name === 'lazyBundle') {
      entry = new LazyBundleEntry(record);
    }
    else if (type === 'jsBlocking' && name === 'jsBlocking') {
      entry = new JSBlockingEntry(record);
    }
    else {
      entry = new PerformanceEntry(record);
    }
    return entry;
  }
}
