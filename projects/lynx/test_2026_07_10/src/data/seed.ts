// src/data/seed.ts
import type { Record } from '../store/types.js';
import { generateId } from '../utils/format.js';

export const seedRecords: Record[] = [
  {
    id: generateId(),
    type: 'expense',
    amount: 3500, // ¥35.00
    categoryId: 'cat-food',
    date: '2026-07-10',
    note: '午餐',
    createdAt: Date.now() - 1000,
  },
  {
    id: generateId(),
    type: 'expense',
    amount: 1250, // ¥12.50
    categoryId: 'cat-transport',
    date: '2026-07-10',
    note: '地铁通勤',
    createdAt: Date.now() - 2000,
  },
  {
    id: generateId(),
    type: 'income',
    amount: 350000, // ¥3,500.00
    categoryId: 'cat-salary',
    date: '2026-07-01',
    note: '7月工资',
    createdAt: Date.now() - 3000,
  },
  {
    id: generateId(),
    type: 'expense',
    amount: 12800, // ¥128.00
    categoryId: 'cat-shopping',
    date: '2026-07-05',
    note: '超市采购',
    createdAt: Date.now() - 4000,
  },
];
