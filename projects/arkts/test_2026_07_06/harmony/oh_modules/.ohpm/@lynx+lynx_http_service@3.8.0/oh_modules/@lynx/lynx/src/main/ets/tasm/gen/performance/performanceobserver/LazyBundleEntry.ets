// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';

export class LazyBundleEntry extends PerformanceEntry {
    public componentUrl: string;
    public mode: string;
    public size: number;
    public sync: boolean;
    public loadSuccess: boolean;
    public requireStart: number;
    public requireEnd: number;
    public decodeStart: number;
    public decodeEnd: number;
    constructor(props: Record<string, Object>) {
        super(props);
        this.componentUrl = (props['componentUrl'] !== undefined && typeof props['componentUrl'] === 'string') ? props['componentUrl'] : '';
        this.mode = (props['mode'] !== undefined && typeof props['mode'] === 'string') ? props['mode'] : '';
        this.size = (props['size'] !== undefined && typeof props['size'] === 'number') ? props['size'] : -1.0;
        this.sync = (props['sync'] !== undefined && typeof props['sync'] === 'boolean') ? props['sync'] : false;
        this.loadSuccess = (props['loadSuccess'] !== undefined && typeof props['loadSuccess'] === 'boolean') ? props['loadSuccess'] : false;
        this.requireStart = (props['requireStart'] !== undefined && typeof props['requireStart'] === 'number') ? props['requireStart'] : -1.0;
        this.requireEnd = (props['requireEnd'] !== undefined && typeof props['requireEnd'] === 'number') ? props['requireEnd'] : -1.0;
        this.decodeStart = (props['decodeStart'] !== undefined && typeof props['decodeStart'] === 'number') ? props['decodeStart'] : -1.0;
        this.decodeEnd = (props['decodeEnd'] !== undefined && typeof props['decodeEnd'] === 'number') ? props['decodeEnd'] : -1.0;
    }
}
