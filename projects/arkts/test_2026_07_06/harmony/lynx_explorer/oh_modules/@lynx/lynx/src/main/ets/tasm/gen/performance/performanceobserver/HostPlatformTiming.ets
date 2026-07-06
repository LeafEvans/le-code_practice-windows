// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
export class HostPlatformTiming {
    public hostPlatformType: string;
    constructor(props: Record<string, Object>) {
        this.hostPlatformType = (props['hostPlatformType'] !== undefined && typeof props['hostPlatformType'] === 'string') ? props['hostPlatformType'] : '';
    }
}
