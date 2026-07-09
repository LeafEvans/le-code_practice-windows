// src/data/icons.ts

export interface IconDef {
  viewBox: string
  paths: string[]
}

export const ICONS: Record<string, IconDef> = {
  // --- Category: Expense ---
  utensils: {
    viewBox: '0 0 24 24',
    paths: [
      'M7 2v20',
      'M17 2v11a4 4 0 0 1-4 4h0a4 4 0 0 1-4-4V2',
    ],
  },
  bus: {
    viewBox: '0 0 24 24',
    paths: [
      'M8 6v6M16 6v6M2 12h20',
      'M6 18h.01M18 18h.01',
      'M4 2h16a2 2 0 0 1 2 2v12a2 2 0 0 1-2 2H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2z',
      'M7 2h10l3 4H4l3-4z',
    ],
  },
  'shopping-bag': {
    viewBox: '0 0 24 24',
    paths: [
      'M6 2L3 6v14a2 2 0 0 0 2 2h14a2 2 0 0 0 2-2V6l-3-4z',
      'M3 6h18',
      'M16 10a4 4 0 0 1-8 0',
    ],
  },
  'gamepad-2': {
    viewBox: '0 0 24 24',
    paths: [
      'M6 11h4M8 9v4',
      'M15 12h.01M18 10h.01',
      'M17.32 5H6.68a4 4 0 0 0-3.978 3.59C2.695 8.642 2 13.682 2 16a3 3 0 0 0 3 3c1 0 1.5-.5 2-1l1.414-1.414A2 2 0 0 1 9.828 16h4.344a2 2 0 0 1 1.414.586L17 18c.5.5 1 1 2 1a3 3 0 0 0 3-3c0-2.318-.695-7.358-.702-7.408A4 4 0 0 0 17.32 5z',
    ],
  },
  home: {
    viewBox: '0 0 24 24',
    paths: [
      'M3 9l9-7 9 7v11a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z',
      'M9 22V12h6v10',
    ],
  },
  smartphone: {
    viewBox: '0 0 24 24',
    paths: [
      'M17 2H7a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h10a2 2 0 0 0 2-2V4a2 2 0 0 0-2-2z',
      'M12 18h.01',
    ],
  },
  pill: {
    viewBox: '0 0 24 24',
    paths: [
      'M10.5 20.5L3.5 13.5a4.95 4.95 0 1 1 7-7l7 7a4.95 4.95 0 1 1-7 7z',
      'M8.5 8.5l7 7',
    ],
  },
  'spray-can': {
    viewBox: '0 0 24 24',
    paths: [
      'M3 3h.01M7 5h.01M11 3h.01M3 7h.01M7 9h.01',
      'M9 3v12a2 2 0 0 0 2 2h2a2 2 0 0 0 2-2V3',
      'M14 2v1',
    ],
  },

  // --- Category: Income ---
  banknote: {
    viewBox: '0 0 24 24',
    paths: [
      'M6 12h12',
      'M2 6v12a2 2 0 0 0 2 2h16a2 2 0 0 0 2-2V6a2 2 0 0 0-2-2H4a2 2 0 0 0-2 2z',
      'M18 8h.01',
    ],
  },
  briefcase: {
    viewBox: '0 0 24 24',
    paths: [
      'M16 20V4a2 2 0 0 0-2-2h-4a2 2 0 0 0-2 2v16',
      'M2 14h20',
      'M2 10a2 2 0 0 0-2 2v8a2 2 0 0 0 2 2h20a2 2 0 0 0 2-2v-8a2 2 0 0 0-2-2',
    ],
  },
  gift: {
    viewBox: '0 0 24 24',
    paths: [
      'M20 12v10H4V12',
      'M2 7h20v5H2z',
      'M12 22V7',
      'M12 7H7.5a2.5 2.5 0 0 1 0-5C11 2 12 7 12 7z',
      'M12 7h4.5a2.5 2.5 0 0 0 0-5C13 2 12 7 12 7z',
    ],
  },
  'trending-up': {
    viewBox: '0 0 24 24',
    paths: [
      'M22 7l-8.5 8.5-5-5L2 17',
      'M16 7h6v6',
    ],
  },

  // --- UI Chrome ---
  'plus-circle': {
    viewBox: '0 0 24 24',
    paths: [
      'M12 22c5.523 0 10-4.477 10-10S17.523 2 12 2 2 6.477 2 12s4.477 10 10 10z',
      'M12 8v8M8 12h8',
    ],
  },
  'chevron-left': {
    viewBox: '0 0 24 24',
    paths: ['M15 18l-6-6 6-6'],
  },
  'chevron-right': {
    viewBox: '0 0 24 24',
    paths: ['M9 18l6-6-6-6'],
  },
  x: {
    viewBox: '0 0 24 24',
    paths: ['M18 6L6 18M6 6l12 12'],
  },
  'trash-2': {
    viewBox: '0 0 24 24',
    paths: [
      'M3 6h18',
      'M8 6V4a2 2 0 0 1 2-2h4a2 2 0 0 1 2 2v2',
      'M19 6v14a2 2 0 0 1-2 2H7a2 2 0 0 1-2-2V6h14',
      'M10 11v6M14 11v6',
    ],
  },
  check: {
    viewBox: '0 0 24 24',
    paths: ['M20 6L9 17l-5-5'],
  },
}

export type IconName = keyof typeof ICONS
