// src/utils/format.ts

/** Convert cents to yuan string with 2 decimal places. */
export function formatAmount(cents: number): string {
  const yuan = cents / 100;
  return yuan.toFixed(2);
}

/** Format amount with sign prefix: +3500.00 or -12.50 */
export function formatSignedAmount(
  cents: number,
  type: 'income' | 'expense',
): string {
  const sign = type === 'income' ? '+' : '-';
  return `${sign}${formatAmount(Math.abs(cents))}`;
}

/** Parse a date string 'YYYY-MM-DD' to a Date. */
export function parseDate(dateStr: string): Date {
  const parts = dateStr.split('-');
  const year = Number(parts[0]);
  const month = Number(parts[1]);
  const day = Number(parts[2]);
  return new Date(year, month - 1, day);
}

/** Format a Date to 'YYYY-MM-DD'. */
export function formatDate(date: Date): string {
  const y = date.getFullYear();
  const m = String(date.getMonth() + 1).padStart(2, '0');
  const d = String(date.getDate()).padStart(2, '0');
  return `${y}-${m}-${d}`;
}

/** Get today as 'YYYY-MM-DD'. */
export function todayStr(): string {
  return formatDate(new Date());
}

/** Generate a simple UUID v4. */
export function generateId(): string {
  return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, (c) => {
    const r = (Math.random() * 16) | 0;
    const v = c === 'x' ? r : (r & 0x3) | 0x8;
    return v.toString(16);
  });
}
