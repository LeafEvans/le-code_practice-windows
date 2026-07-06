// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
export class PerformanceMetric {
    public name: string;
    public duration: number;
    public startTimestampName: string;
    public startTimestamp: number;
    public endTimestampName: string;
    public endTimestamp: number;
    constructor(props: Record<string, Object>) {
        this.name = (props['name'] !== undefined && typeof props['name'] === 'string') ? props['name'] : '';
        this.duration = (props['duration'] !== undefined && typeof props['duration'] === 'number') ? props['duration'] : -1.0;
        this.startTimestampName = (props['startTimestampName'] !== undefined && typeof props['startTimestampName'] === 'string') ? props['startTimestampName'] : '';
        this.startTimestamp = (props['startTimestamp'] !== undefined && typeof props['startTimestamp'] === 'number') ? props['startTimestamp'] : -1.0;
        this.endTimestampName = (props['endTimestampName'] !== undefined && typeof props['endTimestampName'] === 'string') ? props['endTimestampName'] : '';
        this.endTimestamp = (props['endTimestamp'] !== undefined && typeof props['endTimestamp'] === 'number') ? props['endTimestamp'] : -1.0;
    }
}
