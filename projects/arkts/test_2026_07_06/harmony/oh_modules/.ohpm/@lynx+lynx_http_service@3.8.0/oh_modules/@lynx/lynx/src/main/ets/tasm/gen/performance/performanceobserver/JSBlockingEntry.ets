// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';

export class JSBlockingEntry extends PerformanceEntry {
    public stage: string;
    public total_blocking_time: number;
    public total_blocking_count: number;
    public total_duration: number;
    public blocking_ratio: number;
    public avg_blocking_time: number;
    public time_after_fcp: number;
    constructor(props: Record<string, Object>) {
        super(props);
        this.stage = (props['stage'] !== undefined && typeof props['stage'] === 'string') ? props['stage'] : '';
        this.total_blocking_time = (props['total_blocking_time'] !== undefined && typeof props['total_blocking_time'] === 'number') ? props['total_blocking_time'] : -1.0;
        this.total_blocking_count = (props['total_blocking_count'] !== undefined && typeof props['total_blocking_count'] === 'number') ? props['total_blocking_count'] : -1.0;
        this.total_duration = (props['total_duration'] !== undefined && typeof props['total_duration'] === 'number') ? props['total_duration'] : -1.0;
        this.blocking_ratio = (props['blocking_ratio'] !== undefined && typeof props['blocking_ratio'] === 'number') ? props['blocking_ratio'] : -1.0;
        this.avg_blocking_time = (props['avg_blocking_time'] !== undefined && typeof props['avg_blocking_time'] === 'number') ? props['avg_blocking_time'] : -1.0;
        this.time_after_fcp = (props['time_after_fcp'] !== undefined && typeof props['time_after_fcp'] === 'number') ? props['time_after_fcp'] : -1.0;
    }
}
