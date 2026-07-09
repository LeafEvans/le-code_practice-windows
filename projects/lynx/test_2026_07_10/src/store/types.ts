// src/store/types.ts

export interface Record {
  id: string;
  type: "income" | "expense";
  amount: number; // in cents
  categoryId: string;
  date: string; // 'YYYY-MM-DD'
  note?: string;
  createdAt: number; // timestamp
}

export interface Category {
  id: string;
  name: string;
  type: "income" | "expense";
  icon: string; // key into ICONS map
  color: string;
  isDefault: boolean;
}

export interface AppState {
  records: Record[];
  categories: Category[];
}

export type Action =
  | { type: "ADD_RECORD"; payload: Record }
  | { type: "DELETE_RECORD"; payload: string }
  | { type: "UPDATE_RECORD"; payload: Record }
  | { type: "ADD_CATEGORY"; payload: Category }
  | { type: "DELETE_CATEGORY"; payload: string }
  | { type: "LOAD_DATA"; payload: AppState };
