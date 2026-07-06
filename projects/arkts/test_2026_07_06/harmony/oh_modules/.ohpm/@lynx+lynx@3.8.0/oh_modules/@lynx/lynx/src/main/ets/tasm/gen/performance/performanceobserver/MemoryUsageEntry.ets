// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';
import { MemoryUsageItem } from './MemoryUsageItem';

export class MemoryUsageEntry extends PerformanceEntry {
    public detail: Record<string, MemoryUsageItem>;
    constructor(props: Record<string, Object>) {
        super(props);
        this.detail = {};
        let originRecord: Record<string, Object> = (props['detail']!== undefined)? props['detail'] as Record<string, Object> : {};
        Object.entries(originRecord).forEach((entry) => {
            this.detail[entry[0]] = new MemoryUsageItem(entry[1] as Record<string, Object>);
        });
    }
}
