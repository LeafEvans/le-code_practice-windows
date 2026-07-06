// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';
import { PerformanceMetric } from './PerformanceMetric';

/**
 * @deprecated LoadBundleEntry and ReloadBundleEntry contain all properties of MetricFcpEntry
 */
export class MetricFcpEntry extends PerformanceEntry {
    public fcp: PerformanceMetric;
    public lynxFcp: PerformanceMetric;
    public totalFcp: PerformanceMetric;
    constructor(props: Record<string, Object>) {
        super(props);
        this.fcp = (props['fcp'] !== undefined) ? new PerformanceMetric(props['fcp'] as Record<string, Object>) : new PerformanceMetric({});
        this.lynxFcp = (props['lynxFcp'] !== undefined) ? new PerformanceMetric(props['lynxFcp'] as Record<string, Object>) : new PerformanceMetric({});
        this.totalFcp = (props['totalFcp'] !== undefined) ? new PerformanceMetric(props['totalFcp'] as Record<string, Object>) : new PerformanceMetric({});
    }
}
