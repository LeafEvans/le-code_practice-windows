// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
export class MemoryUsageItem {
    public category: string;
    public detail: Record<string, string>;
    constructor(props: Record<string, Object>) {
        this.category = (props['category'] !== undefined && typeof props['category'] === 'string') ? props['category'] : '';
        this.detail = (props['detail']!== undefined)? props['detail'] as Record<string, string> : {};
    }
}
