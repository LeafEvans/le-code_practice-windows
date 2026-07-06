// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';

/**
 * @deprecated LoadBundleEntry and ReloadBundleEntry contain all properties of InitLynxviewEntry
 */
export class InitLynxviewEntry extends PerformanceEntry {
    public createLynxStart: number;
    public createLynxEnd: number;
    constructor(props: Record<string, Object>) {
        super(props);
        this.createLynxStart = (props['createLynxStart'] !== undefined && typeof props['createLynxStart'] === 'number') ? props['createLynxStart'] : -1.0;
        this.createLynxEnd = (props['createLynxEnd'] !== undefined && typeof props['createLynxEnd'] === 'number') ? props['createLynxEnd'] : -1.0;
    }
}
