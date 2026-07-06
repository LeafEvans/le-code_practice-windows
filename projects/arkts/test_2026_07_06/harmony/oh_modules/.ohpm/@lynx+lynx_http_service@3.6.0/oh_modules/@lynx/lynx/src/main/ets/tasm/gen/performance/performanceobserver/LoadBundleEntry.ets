// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PipelineEntry } from './PipelineEntry';

export class LoadBundleEntry extends PipelineEntry {
    public loadBundleStart: number;
    public loadBundleEnd: number;
    public parseStart: number;
    public parseEnd: number;
    public loadBackgroundStart: number;
    public loadBackgroundEnd: number;
    public verifyTasmStart: number;
    public verifyTasmEnd: number;
    public ffiStart: number;
    public ffiEnd: number;
    constructor(props: Record<string, Object>) {
        super(props);
        this.loadBundleStart = (props['loadBundleStart'] !== undefined && typeof props['loadBundleStart'] === 'number') ? props['loadBundleStart'] : -1.0;
        this.loadBundleEnd = (props['loadBundleEnd'] !== undefined && typeof props['loadBundleEnd'] === 'number') ? props['loadBundleEnd'] : -1.0;
        this.parseStart = (props['parseStart'] !== undefined && typeof props['parseStart'] === 'number') ? props['parseStart'] : -1.0;
        this.parseEnd = (props['parseEnd'] !== undefined && typeof props['parseEnd'] === 'number') ? props['parseEnd'] : -1.0;
        this.loadBackgroundStart = (props['loadBackgroundStart'] !== undefined && typeof props['loadBackgroundStart'] === 'number') ? props['loadBackgroundStart'] : -1.0;
        this.loadBackgroundEnd = (props['loadBackgroundEnd'] !== undefined && typeof props['loadBackgroundEnd'] === 'number') ? props['loadBackgroundEnd'] : -1.0;
        this.verifyTasmStart = (props['verifyTasmStart'] !== undefined && typeof props['verifyTasmStart'] === 'number') ? props['verifyTasmStart'] : -1.0;
        this.verifyTasmEnd = (props['verifyTasmEnd'] !== undefined && typeof props['verifyTasmEnd'] === 'number') ? props['verifyTasmEnd'] : -1.0;
        this.ffiStart = (props['ffiStart'] !== undefined && typeof props['ffiStart'] === 'number') ? props['ffiStart'] : -1.0;
        this.ffiEnd = (props['ffiEnd'] !== undefined && typeof props['ffiEnd'] === 'number') ? props['ffiEnd'] : -1.0;
    }
}
