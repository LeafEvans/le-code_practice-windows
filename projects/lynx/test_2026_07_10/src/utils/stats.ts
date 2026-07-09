// src/utils/stats.ts
import type { Category, Record } from '../store/types.js';

export interface MonthlyStats {
  totalIncome: number; // in cents
  totalExpense: number; // in cents
  balance: number; // in cents
  expenseByCategory: Map<string, number>; // categoryId -> total cents
}

/** Compute monthly statistics from records filtered to a given month. */
export function computeMonthlyStats(records: Record[]): MonthlyStats {
  let totalIncome = 0;
  let totalExpense = 0;
  const expenseByCategory = new Map<string, number>();

  for (const record of records) {
    if (record.type === 'income') {
      totalIncome += record.amount;
    } else {
      totalExpense += record.amount;
      const current = expenseByCategory.get(record.categoryId) ?? 0;
      expenseByCategory.set(record.categoryId, current + record.amount);
    }
  }

  return {
    totalIncome,
    totalExpense,
    balance: totalIncome - totalExpense,
    expenseByCategory,
  };
}

/** Filter records by year and month (1-indexed). */
export function filterRecordsByMonth(
  records: Record[],
  year: number,
  month: number,
): Record[] {
  const prefix = `${year}-${String(month).padStart(2, '0')}-`;
  return records.filter((r) => r.date.startsWith(prefix));
}

/** Get year and month from a Date. */
export function getYearMonth(date: Date): { year: number; month: number } {
  return { year: date.getFullYear(), month: date.getMonth() + 1 };
}

/** Move month forward/backward by delta. Returns new year/month. */
export function shiftMonth(
  year: number,
  month: number,
  delta: number,
): { year: number; month: number } {
  const totalMonths = year * 12 + (month - 1) + delta;
  return {
    year: Math.floor(totalMonths / 12),
    month: (totalMonths % 12) + 1,
  };
}

/** Look up category by ID, returns undefined if not found. */
export function findCategory(
  categories: Category[],
  id: string,
): Category | undefined {
  return categories.find((c) => c.id === id);
}
