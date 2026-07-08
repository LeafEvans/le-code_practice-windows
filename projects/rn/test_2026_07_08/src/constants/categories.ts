import { Category } from "../types";

export const EXPENSE_CATEGORIES: Category[] = [
  { key: "food", label: "餐饮", icon: "🍔" },
  { key: "transport", label: "交通", icon: "🚗" },
  { key: "shopping", label: "购物", icon: "🛒" },
  { key: "housing", label: "住房", icon: "🏠" },
  { key: "entertainment", label: "娱乐", icon: "🎮" },
  { key: "medical", label: "医疗", icon: "🏥" },
  { key: "education", label: "教育", icon: "📚" },
  { key: "other", label: "其他", icon: "💡" },
];

export const INCOME_CATEGORIES: Category[] = [
  { key: "salary", label: "工资", icon: "💰" },
  { key: "freelance", label: "兼职", icon: "🔧" },
  { key: "investment", label: "理财", icon: "📈" },
  { key: "redpacket", label: "红包", icon: "🎁" },
  { key: "other", label: "其他", icon: "💡" },
];

export function getCategoryLabel(
  type: "income" | "expense",
  key: string,
): string {
  const cats = type === "income" ? INCOME_CATEGORIES : EXPENSE_CATEGORIES;
  return cats.find((c) => c.key === key)?.label ?? key;
}

export function getCategoryIcon(
  type: "income" | "expense",
  key: string,
): string {
  const cats = type === "income" ? INCOME_CATEGORIES : EXPENSE_CATEGORIES;
  return cats.find((c) => c.key === key)?.icon ?? "💡";
}
