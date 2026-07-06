// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PipelineEntry } from './PipelineEntry';
import { PerformanceMetric } from './PerformanceMetric';

export class ReloadBundleEntry extends PipelineEntry {
    public reloadBundleStart: number;
    public reloadBundleEnd: number;
    public reloadBackgroundStart: number;
    public reloadBackgroundEnd: number;
    public ffiStart: number;
    public ffiEnd: number;
    public createLynxStart: number;
    public createLynxEnd: number;
    public loadCoreStart: number;
    public loadCoreEnd: number;
    public openTime: number;
    public containerInitStart: number;
    public containerInitEnd: number;
    public prepareTemplateStart: number;
    public prepareTemplateEnd: number;
    public fcp?: PerformanceMetric;
    public lynxFcp: PerformanceMetric;
    public totalFcp?: PerformanceMetric;
    constructor(props: Record<string, Object>) {
        super(props);
        this.reloadBundleStart = (props['reloadBundleStart'] !== undefined && typeof props['reloadBundleStart'] === 'number') ? props['reloadBundleStart'] : -1.0;
        this.reloadBundleEnd = (props['reloadBundleEnd'] !== undefined && typeof props['reloadBundleEnd'] === 'number') ? props['reloadBundleEnd'] : -1.0;
        this.reloadBackgroundStart = (props['reloadBackgroundStart'] !== undefined && typeof props['reloadBackgroundStart'] === 'number') ? props['reloadBackgroundStart'] : -1.0;
        this.reloadBackgroundEnd = (props['reloadBackgroundEnd'] !== undefined && typeof props['reloadBackgroundEnd'] === 'number') ? props['reloadBackgroundEnd'] : -1.0;
        this.ffiStart = (props['ffiStart'] !== undefined && typeof props['ffiStart'] === 'number') ? props['ffiStart'] : -1.0;
        this.ffiEnd = (props['ffiEnd'] !== undefined && typeof props['ffiEnd'] === 'number') ? props['ffiEnd'] : -1.0;
        this.createLynxStart = (props['createLynxStart'] !== undefined && typeof props['createLynxStart'] === 'number') ? props['createLynxStart'] : -1.0;
        this.createLynxEnd = (props['createLynxEnd'] !== undefined && typeof props['createLynxEnd'] === 'number') ? props['createLynxEnd'] : -1.0;
        this.loadCoreStart = (props['loadCoreStart'] !== undefined && typeof props['loadCoreStart'] === 'number') ? props['loadCoreStart'] : -1.0;
        this.loadCoreEnd = (props['loadCoreEnd'] !== undefined && typeof props['loadCoreEnd'] === 'number') ? props['loadCoreEnd'] : -1.0;
        this.openTime = (props['openTime'] !== undefined && typeof props['openTime'] === 'number') ? props['openTime'] : -1.0;
        this.containerInitStart = (props['containerInitStart'] !== undefined && typeof props['containerInitStart'] === 'number') ? props['containerInitStart'] : -1.0;
        this.containerInitEnd = (props['containerInitEnd'] !== undefined && typeof props['containerInitEnd'] === 'number') ? props['containerInitEnd'] : -1.0;
        this.prepareTemplateStart = (props['prepareTemplateStart'] !== undefined && typeof props['prepareTemplateStart'] === 'number') ? props['prepareTemplateStart'] : -1.0;
        this.prepareTemplateEnd = (props['prepareTemplateEnd'] !== undefined && typeof props['prepareTemplateEnd'] === 'number') ? props['prepareTemplateEnd'] : -1.0;
        this.fcp = (props['fcp'] !== undefined) ? new PerformanceMetric(props['fcp'] as Record<string, Object>) : undefined;
        this.lynxFcp = (props['lynxFcp'] !== undefined) ? new PerformanceMetric(props['lynxFcp'] as Record<string, Object>) : new PerformanceMetric({});
        this.totalFcp = (props['totalFcp'] !== undefined) ? new PerformanceMetric(props['totalFcp'] as Record<string, Object>) : undefined;
    }
}
