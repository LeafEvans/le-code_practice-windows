export type RecordType = 'income' | 'expense'

export interface BookRecord {
  id: string
  type: RecordType
  amount: number
  category: string
  note: string
  date: string // YYYY-MM-DD
}

export type TabKey = 'records' | 'add' | 'stats'

export const EXPENSE_CATEGORIES = [
  '餐饮', '交通', '购物', '娱乐',
  '生活', '医疗', '教育', '其他',
]

export const INCOME_CATEGORIES = [
  '工资', '兼职', '投资收益', '红包', '其他',
]
