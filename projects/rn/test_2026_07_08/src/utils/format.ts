export function formatCurrency(amount: number): string {
  return `¥${amount.toFixed(2)}`;
}

export function formatDate(dateStr: string): string {
  const d = new Date(dateStr);
  return `${d.getMonth() + 1}月${d.getDate()}日`;
}

export function getMonthKey(dateStr: string): string {
  return dateStr.slice(0, 7);
}

export function getCurrentMonth(): string {
  return new Date().toISOString().slice(0, 7);
}

export function getToday(): string {
  return new Date().toISOString().slice(0, 10);
}
