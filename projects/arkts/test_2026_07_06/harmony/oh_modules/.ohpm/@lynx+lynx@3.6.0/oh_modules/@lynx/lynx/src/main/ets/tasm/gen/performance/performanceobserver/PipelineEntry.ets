// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';
import { HostPlatformTiming } from './HostPlatformTiming';

export class PipelineEntry extends PerformanceEntry {
    public identifier: string;
    public pipelineStart: number;
    public pipelineEnd: number;
    public mtsRenderStart: number;
    public mtsRenderEnd: number;
    public resolveStart: number;
    public resolveEnd: number;
    public layoutStart: number;
    public layoutEnd: number;
    public paintingUiOperationExecuteStart: number;
    public paintingUiOperationExecuteEnd: number;
    public layoutUiOperationExecuteStart: number;
    public layoutUiOperationExecuteEnd: number;
    public paintEnd: number;
    public frameworkRenderingTiming: Record<string, Object>;
    public hostPlatformTiming: HostPlatformTiming;
    constructor(props: Record<string, Object>) {
        super(props);
        this.identifier = (props['identifier'] !== undefined && typeof props['identifier'] === 'string') ? props['identifier'] : '';
        this.pipelineStart = (props['pipelineStart'] !== undefined && typeof props['pipelineStart'] === 'number') ? props['pipelineStart'] : -1.0;
        this.pipelineEnd = (props['pipelineEnd'] !== undefined && typeof props['pipelineEnd'] === 'number') ? props['pipelineEnd'] : -1.0;
        this.mtsRenderStart = (props['mtsRenderStart'] !== undefined && typeof props['mtsRenderStart'] === 'number') ? props['mtsRenderStart'] : -1.0;
        this.mtsRenderEnd = (props['mtsRenderEnd'] !== undefined && typeof props['mtsRenderEnd'] === 'number') ? props['mtsRenderEnd'] : -1.0;
        this.resolveStart = (props['resolveStart'] !== undefined && typeof props['resolveStart'] === 'number') ? props['resolveStart'] : -1.0;
        this.resolveEnd = (props['resolveEnd'] !== undefined && typeof props['resolveEnd'] === 'number') ? props['resolveEnd'] : -1.0;
        this.layoutStart = (props['layoutStart'] !== undefined && typeof props['layoutStart'] === 'number') ? props['layoutStart'] : -1.0;
        this.layoutEnd = (props['layoutEnd'] !== undefined && typeof props['layoutEnd'] === 'number') ? props['layoutEnd'] : -1.0;
        this.paintingUiOperationExecuteStart = (props['paintingUiOperationExecuteStart'] !== undefined && typeof props['paintingUiOperationExecuteStart'] === 'number') ? props['paintingUiOperationExecuteStart'] : -1.0;
        this.paintingUiOperationExecuteEnd = (props['paintingUiOperationExecuteEnd'] !== undefined && typeof props['paintingUiOperationExecuteEnd'] === 'number') ? props['paintingUiOperationExecuteEnd'] : -1.0;
        this.layoutUiOperationExecuteStart = (props['layoutUiOperationExecuteStart'] !== undefined && typeof props['layoutUiOperationExecuteStart'] === 'number') ? props['layoutUiOperationExecuteStart'] : -1.0;
        this.layoutUiOperationExecuteEnd = (props['layoutUiOperationExecuteEnd'] !== undefined && typeof props['layoutUiOperationExecuteEnd'] === 'number') ? props['layoutUiOperationExecuteEnd'] : -1.0;
        this.paintEnd = (props['paintEnd'] !== undefined && typeof props['paintEnd'] === 'number') ? props['paintEnd'] : -1.0;
        this.frameworkRenderingTiming = (props['frameworkRenderingTiming']!== undefined)? props['frameworkRenderingTiming'] as Record<string, Object> : {};
        this.hostPlatformTiming = (props['hostPlatformTiming'] !== undefined) ? new HostPlatformTiming(props['hostPlatformTiming'] as Record<string, Object>) : new HostPlatformTiming({});
    }
}
