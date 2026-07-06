// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
export class PerformanceEntry {
    public name: string;
    public entryType: string;
    public typeResolved: boolean;
    public rawRecord: Record<string, Object>;
    constructor(props: Record<string, Object>) {
        this.name = (props['name'] !== undefined && typeof props['name'] === 'string') ? props['name'] : '';
        this.entryType = (props['entryType'] !== undefined && typeof props['entryType'] === 'string') ? props['entryType'] : '';
        this.typeResolved = (props['typeResolved'] !== undefined && typeof props['typeResolved'] === 'boolean') ? props['typeResolved'] : true;
        this.rawRecord = props;
    }
    public toRecord(): Record<string, Object> {
        return this.rawRecord;
    }
}
