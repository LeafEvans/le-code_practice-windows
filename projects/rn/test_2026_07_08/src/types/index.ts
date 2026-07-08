export interface ExpenseRecord {
  id: string;
  type: 'income' | 'expense';
  amount: number;
  category: string;
  date: string; // YYYY-MM-DD
  note: string;
}

export interface Category {
  key: string;
  label: string;
  icon: string;
}
