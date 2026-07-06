// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PipelineEntry } from './PipelineEntry';

export class ReloadBundleEntry extends PipelineEntry {
    public reloadBundleStart: number;
    public reloadBundleEnd: number;
    public reloadBackgroundStart: number;
    public reloadBackgroundEnd: number;
    public ffiStart: number;
    public ffiEnd: number;
    constructor(props: Record<string, Object>) {
        super(props);
        this.reloadBundleStart = (props['reloadBundleStart'] !== undefined && typeof props['reloadBundleStart'] === 'number') ? props['reloadBundleStart'] : -1.0;
        this.reloadBundleEnd = (props['reloadBundleEnd'] !== undefined && typeof props['reloadBundleEnd'] === 'number') ? props['reloadBundleEnd'] : -1.0;
        this.reloadBackgroundStart = (props['reloadBackgroundStart'] !== undefined && typeof props['reloadBackgroundStart'] === 'number') ? props['reloadBackgroundStart'] : -1.0;
        this.reloadBackgroundEnd = (props['reloadBackgroundEnd'] !== undefined && typeof props['reloadBackgroundEnd'] === 'number') ? props['reloadBackgroundEnd'] : -1.0;
        this.ffiStart = (props['ffiStart'] !== undefined && typeof props['ffiStart'] === 'number') ? props['ffiStart'] : -1.0;
        this.ffiEnd = (props['ffiEnd'] !== undefined && typeof props['ffiEnd'] === 'number') ? props['ffiEnd'] : -1.0;
    }
}
