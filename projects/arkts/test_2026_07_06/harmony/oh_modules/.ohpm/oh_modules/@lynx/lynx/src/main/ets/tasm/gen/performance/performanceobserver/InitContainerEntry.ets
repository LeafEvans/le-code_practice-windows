// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';

/**
 * @deprecated LoadBundleEntry and ReloadBundleEntry contain all properties of InitContainerEntry
 */
export class InitContainerEntry extends PerformanceEntry {
    public openTime: number;
    public containerInitStart: number;
    public containerInitEnd: number;
    public prepareTemplateStart: number;
    public prepareTemplateEnd: number;
    public extraTiming: Record<string, number>;
    constructor(props: Record<string, Object>) {
        super(props);
        this.openTime = (props['openTime'] !== undefined && typeof props['openTime'] === 'number') ? props['openTime'] : -1.0;
        this.containerInitStart = (props['containerInitStart'] !== undefined && typeof props['containerInitStart'] === 'number') ? props['containerInitStart'] : -1.0;
        this.containerInitEnd = (props['containerInitEnd'] !== undefined && typeof props['containerInitEnd'] === 'number') ? props['containerInitEnd'] : -1.0;
        this.prepareTemplateStart = (props['prepareTemplateStart'] !== undefined && typeof props['prepareTemplateStart'] === 'number') ? props['prepareTemplateStart'] : -1.0;
        this.prepareTemplateEnd = (props['prepareTemplateEnd'] !== undefined && typeof props['prepareTemplateEnd'] === 'number') ? props['prepareTemplateEnd'] : -1.0;
        this.extraTiming = (props['extraTiming']!== undefined)? props['extraTiming'] as Record<string, number> : {};
    }
}
