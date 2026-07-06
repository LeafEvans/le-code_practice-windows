// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
import { PerformanceEntry } from './PerformanceEntry';
import { PerformanceMetric } from './PerformanceMetric';

export class MetricFspEntry extends PerformanceEntry {
    public fsp: PerformanceMetric;
    public lynxFsp: PerformanceMetric;
    public totalFsp: PerformanceMetric;
    public fspStatus: string;
    public contentFillPercentageX: number;
    public contentFillPercentageY: number;
    public contentFillPercentageTotalArea: number;
    public containerFillPercentageContainerArea: number;
    constructor(props: Record<string, Object>) {
        super(props);
        this.fsp = (props['fsp'] !== undefined) ? new PerformanceMetric(props['fsp'] as Record<string, Object>) : new PerformanceMetric({});
        this.lynxFsp = (props['lynxFsp'] !== undefined) ? new PerformanceMetric(props['lynxFsp'] as Record<string, Object>) : new PerformanceMetric({});
        this.totalFsp = (props['totalFsp'] !== undefined) ? new PerformanceMetric(props['totalFsp'] as Record<string, Object>) : new PerformanceMetric({});
        this.fspStatus = (props['fspStatus'] !== undefined && typeof props['fspStatus'] === 'string') ? props['fspStatus'] : '';
        this.contentFillPercentageX = (props['contentFillPercentageX'] !== undefined && typeof props['contentFillPercentageX'] === 'number') ? props['contentFillPercentageX'] : -1.0;
        this.contentFillPercentageY = (props['contentFillPercentageY'] !== undefined && typeof props['contentFillPercentageY'] === 'number') ? props['contentFillPercentageY'] : -1.0;
        this.contentFillPercentageTotalArea = (props['contentFillPercentageTotalArea'] !== undefined && typeof props['contentFillPercentageTotalArea'] === 'number') ? props['contentFillPercentageTotalArea'] : -1.0;
        this.containerFillPercentageContainerArea = (props['containerFillPercentageContainerArea'] !== undefined && typeof props['containerFillPercentageContainerArea'] === 'number') ? props['containerFillPercentageContainerArea'] : -1.0;
    }
}
