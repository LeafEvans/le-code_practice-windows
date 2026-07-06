// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';

/**
 * @deprecated LoadBundleEntry and ReloadBundleEntry contain all properties of InitBackgroundRuntimeEntry
 */
export class InitBackgroundRuntimeEntry extends PerformanceEntry {
    public loadCoreStart: number;
    public loadCoreEnd: number;
    constructor(props: Record<string, Object>) {
        super(props);
        this.loadCoreStart = (props['loadCoreStart'] !== undefined && typeof props['loadCoreStart'] === 'number') ? props['loadCoreStart'] : -1.0;
        this.loadCoreEnd = (props['loadCoreEnd'] !== undefined && typeof props['loadCoreEnd'] === 'number') ? props['loadCoreEnd'] : -1.0;
    }
}
