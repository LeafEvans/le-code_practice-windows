// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';
import { PerformanceMetric } from './PerformanceMetric';

export class MetricActualFmpEntry extends PerformanceEntry {
    public actualFmp: PerformanceMetric;
    public lynxActualFmp: PerformanceMetric;
    public totalActualFmp: PerformanceMetric;
    constructor(props: Record<string, Object>) {
        super(props);
        this.actualFmp = (props['actualFmp'] !== undefined) ? new PerformanceMetric(props['actualFmp'] as Record<string, Object>) : new PerformanceMetric({});
        this.lynxActualFmp = (props['lynxActualFmp'] !== undefined) ? new PerformanceMetric(props['lynxActualFmp'] as Record<string, Object>) : new PerformanceMetric({});
        this.totalActualFmp = (props['totalActualFmp'] !== undefined) ? new PerformanceMetric(props['totalActualFmp'] as Record<string, Object>) : new PerformanceMetric({});
    }
}
