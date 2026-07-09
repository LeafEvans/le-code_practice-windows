// src/__tests__/utils.test.ts
import { describe, expect, test } from 'vitest'
import { formatAmount, formatSignedAmount, formatDate, generateId } from '../utils/format'
import { computeMonthlyStats, filterRecordsByMonth, shiftMonth, findCategory } from '../utils/stats'
import type { Record, Category } from '../store/types'

describe('formatAmount', () => {
  test('converts cents to yuan string', () => {
    expect(formatAmount(3500)).toBe('35.00')
    expect(formatAmount(1250)).toBe('12.50')
    expect(formatAmount(0)).toBe('0.00')
    expect(formatAmount(100000)).toBe('1000.00')
  })
})

describe('formatSignedAmount', () => {
  test('adds + for income and - for expense', () => {
    expect(formatSignedAmount(3500, 'income')).toBe('+35.00')
    expect(formatSignedAmount(1250, 'expense')).toBe('-12.50')
  })
})

describe('formatDate', () => {
  test('formats date to YYYY-MM-DD', () => {
    expect(formatDate(new Date(2026, 6, 10))).toBe('2026-07-10')
  })
})

describe('generateId', () => {
  test('generates a UUID-like string', () => {
    const id = generateId()
    expect(id).toMatch(/^[0-9a-f-]{36}$/)
  })

  test('generates unique IDs', () => {
    const ids = new Set(Array.from({ length: 100 }, () => generateId()))
    expect(ids.size).toBe(100)
  })
})

describe('computeMonthlyStats', () => {
  test('computes income, expense, and balance', () => {
    const records: Record[] = [
      { id: '1', type: 'income', amount: 100000, categoryId: 'cat-salary', date: '2026-07-01', createdAt: 1 },
      { id: '2', type: 'expense', amount: 3500, categoryId: 'cat-food', date: '2026-07-10', createdAt: 2 },
      { id: '3', type: 'expense', amount: 1250, categoryId: 'cat-transport', date: '2026-07-10', createdAt: 3 },
    ]

    const stats = computeMonthlyStats(records)
    expect(stats.totalIncome).toBe(100000)
    expect(stats.totalExpense).toBe(4750)
    expect(stats.balance).toBe(95250)
    expect(stats.expenseByCategory.get('cat-food')).toBe(3500)
    expect(stats.expenseByCategory.get('cat-transport')).toBe(1250)
  })
})

describe('filterRecordsByMonth', () => {
  test('filters records by year and month', () => {
    const records: Record[] = [
      { id: '1', type: 'expense', amount: 100, categoryId: 'cat-food', date: '2026-07-10', createdAt: 1 },
      { id: '2', type: 'expense', amount: 200, categoryId: 'cat-food', date: '2026-06-10', createdAt: 2 },
      { id: '3', type: 'expense', amount: 300, categoryId: 'cat-food', date: '2026-07-15', createdAt: 3 },
    ]

    expect(filterRecordsByMonth(records, 2026, 7)).toHaveLength(2)
    expect(filterRecordsByMonth(records, 2026, 6)).toHaveLength(1)
    expect(filterRecordsByMonth(records, 2026, 5)).toHaveLength(0)
  })
})

describe('shiftMonth', () => {
  test('shifts month forward and backward', () => {
    expect(shiftMonth(2026, 7, -1)).toEqual({ year: 2026, month: 6 })
    expect(shiftMonth(2026, 7, 1)).toEqual({ year: 2026, month: 8 })
    expect(shiftMonth(2026, 1, -1)).toEqual({ year: 2025, month: 12 })
    expect(shiftMonth(2026, 12, 1)).toEqual({ year: 2027, month: 1 })
  })
})

describe('findCategory', () => {
  test('finds category by ID', () => {
    const categories: Category[] = [
      { id: 'cat-1', name: 'Food', type: 'expense', icon: 'utensils', color: '#FF6B6B', isDefault: true },
    ]
    expect(findCategory(categories, 'cat-1')?.name).toBe('Food')
    expect(findCategory(categories, 'cat-2')).toBeUndefined()
  })
})
