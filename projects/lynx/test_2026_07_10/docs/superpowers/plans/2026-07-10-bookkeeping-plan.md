# Bookkeeping App — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a personal bookkeeping app with income/expense recording, category management, and monthly statistics on ReactLynx.

**Architecture:** 3-tab app (Records, Stats, Settings) using React Context + useReducer for state, Lynx native `<svg>` for Lucide icons, `<overlay>` for modals, `<input>` for text entry. Data layer abstracted behind `data/storage.ts`.

**Tech Stack:** ReactLynx (`@lynx-js/react`), TypeScript, Rspeedy, Vitest + `@lynx-js/react/testing-library`

---

## File Map

| File | Role |
|------|------|
| `src/store/types.ts` | All TypeScript type definitions |
| `src/data/icons.ts` | SVG path data for ~18 Lucide icons |
| `src/utils/format.ts` | Amount/date formatting helpers |
| `src/utils/stats.ts` | Statistics computation (monthly totals, category breakdowns) |
| `src/data/storage.ts` | In-memory storage abstraction (module-level state) |
| `src/data/categories.ts` | Default category definitions |
| `src/data/seed.ts` | Demo records for first-time experience |
| `src/store/AppContext.tsx` | Context Provider + useReducer + persistence |
| `src/components/Icon.tsx` | Generic Lynx `<svg>` icon wrapper |
| `src/components/CategoryIcon.tsx` | Category icon with color mapping |
| `src/components/RecordItem.tsx` | Single record row component |
| `src/components/MonthBar.tsx` | Monthly percentage bar chart |
| `src/components/AddRecordModal.tsx` | Overlay modal for adding records |
| `src/pages/RecordsPage.tsx` | Tab 1 — record list + month nav |
| `src/pages/StatsPage.tsx` | Tab 2 — monthly statistics |
| `src/pages/SettingsPage.tsx` | Tab 3 — category management |
| `src/App.tsx` | Tab container (rewrite) |
| `src/App.css` | App styles (rewrite) |
| `src/index.tsx` | Mount point (minor update) |

---

### Task 1: Core Types & Icon Data

**Files:**
- Create: `src/store/types.ts`
- Create: `src/data/icons.ts`

- [ ] **Step 1: Write types.ts**

```typescript
// src/store/types.ts

export interface Record {
  id: string
  type: 'income' | 'expense'
  amount: number // in cents
  categoryId: string
  date: string // 'YYYY-MM-DD'
  note?: string
  createdAt: number // timestamp
}

export interface Category {
  id: string
  name: string
  type: 'income' | 'expense'
  icon: string // key into ICONS map
  color: string
  isDefault: boolean
}

export interface AppState {
  records: Record[]
  categories: Category[]
}

export type Action =
  | { type: 'ADD_RECORD'; payload: Record }
  | { type: 'DELETE_RECORD'; payload: string }
  | { type: 'UPDATE_RECORD'; payload: Record }
  | { type: 'ADD_CATEGORY'; payload: Category }
  | { type: 'DELETE_CATEGORY'; payload: string }
  | { type: 'LOAD_DATA'; payload: AppState }
```

- [ ] **Step 2: Write icons.ts**

```typescript
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
```

- [ ] **Step 3: Commit**

```bash
git add src/store/types.ts src/data/icons.ts
git commit -m "feat: add core types and icon SVG data"
```

---

### Task 2: Utility Functions

**Files:**
- Create: `src/utils/format.ts`
- Create: `src/utils/stats.ts`

- [ ] **Step 1: Write format.ts**

```typescript
// src/utils/format.ts

/** Convert cents to yuan string with 2 decimal places. */
export function formatAmount(cents: number): string {
  const yuan = cents / 100
  return yuan.toFixed(2)
}

/** Format amount with sign prefix: +3500.00 or -12.50 */
export function formatSignedAmount(cents: number, type: 'income' | 'expense'): string {
  const sign = type === 'income' ? '+' : '-'
  return `${sign}${formatAmount(Math.abs(cents))}`
}

/** Parse a date string 'YYYY-MM-DD' to a Date. */
export function parseDate(dateStr: string): Date {
  const [year, month, day] = dateStr.split('-').map(Number)
  return new Date(year!, month! - 1, day!)
}

/** Format a Date to 'YYYY-MM-DD'. */
export function formatDate(date: Date): string {
  const y = date.getFullYear()
  const m = String(date.getMonth() + 1).padStart(2, '0')
  const d = String(date.getDate()).padStart(2, '0')
  return `${y}-${m}-${d}`
}

/** Get today as 'YYYY-MM-DD'. */
export function todayStr(): string {
  return formatDate(new Date())
}

/** Generate a simple UUID v4. */
export function generateId(): string {
  return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, (c) => {
    const r = (Math.random() * 16) | 0
    const v = c === 'x' ? r : (r & 0x3) | 0x8
    return v.toString(16)
  })
}
```

- [ ] **Step 2: Write stats.ts**

```typescript
// src/utils/stats.ts
import type { Record, Category } from '../store/types.js'

export interface MonthlyStats {
  totalIncome: number // in cents
  totalExpense: number // in cents
  balance: number // in cents
  expenseByCategory: Map<string, number> // categoryId -> total cents
}

/** Compute monthly statistics from records filtered to a given month. */
export function computeMonthlyStats(
  records: Record[],
): MonthlyStats {
  let totalIncome = 0
  let totalExpense = 0
  const expenseByCategory = new Map<string, number>()

  for (const record of records) {
    if (record.type === 'income') {
      totalIncome += record.amount
    } else {
      totalExpense += record.amount
      const current = expenseByCategory.get(record.categoryId) ?? 0
      expenseByCategory.set(record.categoryId, current + record.amount)
    }
  }

  return {
    totalIncome,
    totalExpense,
    balance: totalIncome - totalExpense,
    expenseByCategory,
  }
}

/** Filter records by year and month (1-indexed). */
export function filterRecordsByMonth(
  records: Record[],
  year: number,
  month: number,
): Record[] {
  const prefix = `${year}-${String(month).padStart(2, '0')}-`
  return records.filter((r) => r.date.startsWith(prefix))
}

/** Get year and month from a Date. */
export function getYearMonth(date: Date): { year: number; month: number } {
  return { year: date.getFullYear(), month: date.getMonth() + 1 }
}

/** Move month forward/backward by delta. Returns new year/month. */
export function shiftMonth(year: number, month: number, delta: number): { year: number; month: number } {
  const totalMonths = year * 12 + (month - 1) + delta
  return {
    year: Math.floor(totalMonths / 12),
    month: (totalMonths % 12) + 1,
  }
}

/** Look up category by ID, returns undefined if not found. */
export function findCategory(categories: Category[], id: string): Category | undefined {
  return categories.find((c) => c.id === id)
}
```

- [ ] **Step 3: Commit**

```bash
git add src/utils/format.ts src/utils/stats.ts
git commit -m "feat: add format and stats utility functions"
```

---

### Task 3: Data Layer (Storage, Categories, Seed)

**Files:**
- Create: `src/data/storage.ts`
- Create: `src/data/categories.ts`
- Create: `src/data/seed.ts`

- [ ] **Step 1: Write storage.ts**

```typescript
// src/data/storage.ts
import type { AppState } from '../store/types.js'
import { defaultCategories } from './categories.js'
import { seedRecords } from './seed.js'

let appState: AppState | null = null

/** Load state. Returns defaults + seed if never saved. */
export function loadState(): AppState {
  if (appState) return appState

  // First run: seed with defaults
  appState = {
    records: seedRecords,
    categories: [...defaultCategories],
  }
  return appState
}

/** Save state to memory. */
export function saveState(state: AppState): void {
  appState = state
}

/** Reset to empty state (for testing or data clear). */
export function clearState(): void {
  appState = null
}
```

- [ ] **Step 2: Write categories.ts**

```typescript
// src/data/categories.ts
import type { Category } from '../store/types.js'

export const defaultCategories: Category[] = [
  // Expense
  { id: 'cat-food', name: '餐饮', type: 'expense', icon: 'utensils', color: '#FF6B6B', isDefault: true },
  { id: 'cat-transport', name: '交通', type: 'expense', icon: 'bus', color: '#4ECDC4', isDefault: true },
  { id: 'cat-shopping', name: '购物', type: 'expense', icon: 'shopping-bag', color: '#FFD93D', isDefault: true },
  { id: 'cat-entertainment', name: '娱乐', type: 'expense', icon: 'gamepad-2', color: '#6C5CE7', isDefault: true },
  { id: 'cat-housing', name: '居住', type: 'expense', icon: 'home', color: '#A29BFE', isDefault: true },
  { id: 'cat-communication', name: '通讯', type: 'expense', icon: 'smartphone', color: '#FD79A8', isDefault: true },
  { id: 'cat-medical', name: '医疗', type: 'expense', icon: 'pill', color: '#00B894', isDefault: true },
  { id: 'cat-daily', name: '日用', type: 'expense', icon: 'spray-can', color: '#E17055', isDefault: true },
  // Income
  { id: 'cat-salary', name: '工资', type: 'income', icon: 'banknote', color: '#00B894', isDefault: true },
  { id: 'cat-parttime', name: '兼职', type: 'income', icon: 'briefcase', color: '#0984E3', isDefault: true },
  { id: 'cat-redpacket', name: '红包', type: 'income', icon: 'gift', color: '#E84393', isDefault: true },
  { id: 'cat-investment', name: '理财', type: 'income', icon: 'trending-up', color: '#FDCB6E', isDefault: true },
]
```

- [ ] **Step 3: Write seed.ts**

```typescript
// src/data/seed.ts
import type { Record } from '../store/types.js'
import { generateId } from '../utils/format.js'

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
]
```

- [ ] **Step 4: Commit**

```bash
git add src/data/storage.ts src/data/categories.ts src/data/seed.ts
git commit -m "feat: add data layer (storage, categories, seed)"
```

---

### Task 4: AppContext State Management

**Files:**
- Create: `src/store/AppContext.tsx`

- [ ] **Step 1: Write AppContext.tsx**

```typescript
// src/store/AppContext.tsx
import {
  createContext,
  useCallback,
  useContext,
  useEffect,
  useReducer,
  type Dispatch,
} from '@lynx-js/react'
import type { Action, AppState, Record } from './types.js'
import { loadState, saveState } from '../data/storage.js'
import { generateId } from '../utils/format.js'

function reducer(state: AppState, action: Action): AppState {
  switch (action.type) {
    case 'LOAD_DATA':
      return action.payload

    case 'ADD_RECORD':
      return {
        ...state,
        records: [action.payload, ...state.records],
      }

    case 'DELETE_RECORD':
      return {
        ...state,
        records: state.records.filter((r) => r.id !== action.payload),
      }

    case 'UPDATE_RECORD':
      return {
        ...state,
        records: state.records.map((r) =>
          r.id === action.payload.id ? action.payload : r,
        ),
      }

    case 'ADD_CATEGORY':
      return {
        ...state,
        categories: [...state.categories, action.payload],
      }

    case 'DELETE_CATEGORY': {
      const categoryId = action.payload
      return {
        ...state,
        categories: state.categories.filter((c) => c.id !== categoryId),
        records: state.records.filter((r) => r.categoryId !== categoryId),
      }
    }

    default:
      return state
  }
}

interface AppContextValue {
  state: AppState
  dispatch: Dispatch<Action>
  addRecord: (record: Omit<Record, 'id' | 'createdAt'>) => void
}

const AppContext = createContext<AppContextValue | null>(null)

export function AppProvider({ children }: { children: React.ReactNode }) {
  const [state, dispatch] = useReducer(reducer, null, () => loadState())

  // Auto-persist on state change
  useEffect(() => {
    saveState(state)
  }, [state])

  const addRecord = useCallback(
    (data: Omit<Record, 'id' | 'createdAt'>) => {
      'background only'
      const record: Record = {
        ...data,
        id: generateId(),
        createdAt: Date.now(),
      }
      dispatch({ type: 'ADD_RECORD', payload: record })
    },
    [dispatch],
  )

  return (
    <AppContext.Provider value={{ state, dispatch, addRecord }}>
      {children}
    </AppContext.Provider>
  )
}

export function useAppContext(): AppContextValue {
  const ctx = useContext(AppContext)
  if (!ctx) throw new Error('useAppContext must be used within AppProvider')
  return ctx
}
```

- [ ] **Step 2: Commit**

```bash
git add src/store/AppContext.tsx
git commit -m "feat: add AppContext with reducer and persistence"
```

---

### Task 5: Icon & CategoryIcon Components

**Files:**
- Create: `src/components/Icon.tsx`
- Create: `src/components/CategoryIcon.tsx`

- [ ] **Step 1: Write Icon.tsx**

```typescript
// src/components/Icon.tsx
import { ICONS, type IconName } from '../data/icons.js'

interface IconProps {
  name: IconName
  size?: number
  color?: string
}

export function Icon({ name, size = 24, color = 'currentColor' }: IconProps) {
  const def = ICONS[name]
  if (!def) return null

  const paths = def.paths
    .map((d) => `<path d="${d}" fill="none" stroke="${color}" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>`)
    .join('')

  const svgContent = `<svg viewBox="${def.viewBox}" xmlns="http://www.w3.org/2000/svg">${paths}</svg>`

  return (
    <svg
      content={svgContent}
      style={{ width: `${size}px`, height: `${size}px` }}
    />
  )
}
```

- [ ] **Step 2: Write CategoryIcon.tsx**

```typescript
// src/components/CategoryIcon.tsx
import { Icon, type IconName } from './Icon.js'
import type { Category } from '../store/types.js'

interface CategoryIconProps {
  category: Category
  size?: number
}

const BG_COLORS: Record<string, string> = {
  '#FF6B6B': '#FF6B6B20',
  '#4ECDC4': '#4ECDC420',
  '#FFD93D': '#FFD93D20',
  '#6C5CE7': '#6C5CE720',
  '#A29BFE': '#A29BFE20',
  '#FD79A8': '#FD79A820',
  '#00B894': '#00B89420',
  '#E17055': '#E1705520',
  '#0984E3': '#0984E320',
  '#E84393': '#E8439320',
  '#FDCB6E': '#FDCB6E20',
}

export function CategoryIcon({ category, size = 20 }: CategoryIconProps) {
  const bgColor = BG_COLORS[category.color] ?? `${category.color}20`

  return (
    <view
      style={{
        width: `${size + 12}px`,
        height: `${size + 12}px`,
        borderRadius: `${(size + 12) / 2}px`,
        backgroundColor: bgColor,
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
      }}
    >
      <Icon name={category.icon as IconName} size={size} color={category.color} />
    </view>
  )
}
```

- [ ] **Step 3: Commit**

```bash
git add src/components/Icon.tsx src/components/CategoryIcon.tsx
git commit -m "feat: add Icon and CategoryIcon components"
```

---

### Task 6: RecordItem Component

**Files:**
- Create: `src/components/RecordItem.tsx`

- [ ] **Step 1: Write RecordItem.tsx**

```typescript
// src/components/RecordItem.tsx
import { useCallback } from '@lynx-js/react'
import type { Record, Category } from '../store/types.js'
import { CategoryIcon } from './CategoryIcon.js'
import { formatAmount, formatSignedAmount } from '../utils/format.js'
import { useAppContext } from '../store/AppContext.js'

interface RecordItemProps {
  record: Record
  category: Category | undefined
}

export function RecordItem({ record, category }: RecordItemProps) {
  const { dispatch } = useAppContext()

  const onDelete = useCallback(() => {
    'background only'
    dispatch({ type: 'DELETE_RECORD', payload: record.id })
  }, [dispatch, record.id])

  const isExpense = record.type === 'expense'

  return (
    <view
      style={{
        display: 'flex',
        flexDirection: 'row',
        alignItems: 'center',
        padding: '12px 16px',
        borderBottom: '1px solid #f0f0f0',
      }}
    >
      {category && <CategoryIcon category={category} size={18} />}

      <view style={{ flex: 1, marginLeft: '12px' }}>
        <text style={{ fontSize: '16px', fontWeight: '500', color: '#1a1a1a' }}>
          {category?.name ?? '未知'}
        </text>
        {record.note ? (
          <text style={{ fontSize: '12px', color: '#999', marginTop: '2px' }}>
            {record.note}
          </text>
        ) : null}
      </view>

      <text
        style={{
          fontSize: '18px',
          fontWeight: '600',
          color: isExpense ? '#1a1a1a' : '#00B894',
        }}
      >
        {formatSignedAmount(record.amount, record.type)}
      </text>

      <view
        bindtap={onDelete}
        style={{
          marginLeft: '8px',
          padding: '4px',
          width: '28px',
          height: '28px',
          display: 'flex',
          justifyContent: 'center',
          alignItems: 'center',
        }}
      >
        <text style={{ fontSize: '16px', color: '#ccc' }}>✕</text>
      </view>
    </view>
  )
}
```

- [ ] **Step 2: Commit**

```bash
git add src/components/RecordItem.tsx
git commit -m "feat: add RecordItem component"
```

---

### Task 7: MonthBar Component

**Files:**
- Create: `src/components/MonthBar.tsx`

- [ ] **Step 1: Write MonthBar.tsx**

```typescript
// src/components/MonthBar.tsx
import type { Category } from '../store/types.js'
import { CategoryIcon } from './CategoryIcon.js'
import { formatAmount } from '../utils/format.js'
import { findCategory } from '../utils/stats.js'

interface BarItem {
  categoryId: string
  amount: number // cents
  percentage: number // 0-100
}

interface MonthBarProps {
  items: BarItem[]
  total: number // cents
  categories: Category[]
}

export function MonthBar({ items, total, categories }: MonthBarProps) {
  if (items.length === 0) {
    return (
      <view
        style={{
          display: 'flex',
          justifyContent: 'center',
          alignItems: 'center',
          padding: '40px 0',
        }}
      >
        <text style={{ fontSize: '14px', color: '#999' }}>暂无支出数据</text>
      </view>
    )
  }

  // Sort by amount descending
  const sorted = [...items].sort((a, b) => b.amount - a.amount)

  return (
    <view style={{ padding: '0 16px' }}>
      {sorted.slice(0, 8).map((item) => {
        const category = findCategory(categories, item.categoryId)
        if (!category) return null

        return (
          <view
            key={item.categoryId}
            style={{
              display: 'flex',
              flexDirection: 'row',
              alignItems: 'center',
              marginBottom: '10px',
            }}
          >
            <CategoryIcon category={category} size={14} />

            <text style={{ fontSize: '14px', color: '#666', marginLeft: '8px', width: '40px' }}>
              {category.name}
            </text>

            {/* Percentage bar */}
            <view style={{ flex: 1, marginLeft: '8px', marginRight: '8px' }}>
              <view
                style={{
                  height: '8px',
                  borderRadius: '4px',
                  backgroundColor: '#f0f0f0',
                  position: 'relative',
                }}
              >
                <view
                  style={{
                    height: '8px',
                    borderRadius: '4px',
                    backgroundColor: category.color,
                    width: `${Math.max(item.percentage, 2)}%`,
                  }}
                />
              </view>
            </view>

            <text style={{ fontSize: '12px', color: '#999', width: '50px', textAlign: 'right' }}>
              {item.percentage.toFixed(0)}%
            </text>
            <text style={{ fontSize: '12px', color: '#999', width: '60px' }}>
              ¥{formatAmount(item.amount)}
            </text>
          </view>
        )
      })}
    </view>
  )
}
```

- [ ] **Step 2: Commit**

```bash
git add src/components/MonthBar.tsx
git commit -m "feat: add MonthBar component"
```

---

### Task 8: AddRecordModal Component

**Files:**
- Create: `src/components/AddRecordModal.tsx`

- [ ] **Step 1: Write AddRecordModal.tsx**

```typescript
// src/components/AddRecordModal.tsx
import { useCallback, useState } from '@lynx-js/react'
import { useAppContext } from '../store/AppContext.js'
import { CategoryIcon } from './CategoryIcon.js'
import { todayStr } from '../utils/format.js'
import type { Category } from '../store/types.js'

interface AddRecordModalProps {
  visible: boolean
  onClose: () => void
}

export function AddRecordModal({ visible, onClose }: AddRecordModalProps) {
  const { state, addRecord } = useAppContext()
  const [recordType, setRecordType] = useState<'expense' | 'income'>('expense')
  const [amountText, setAmountText] = useState('')
  const [selectedCategoryId, setSelectedCategoryId] = useState<string | null>(null)
  const [note, setNote] = useState('')

  const filteredCategories = state.categories.filter((c) => c.type === recordType)

  const onSave = useCallback(() => {
    'background only'
    const amountYuan = parseFloat(amountText)
    if (isNaN(amountYuan) || amountYuan <= 0 || !selectedCategoryId) return

    addRecord({
      type: recordType,
      amount: Math.round(amountYuan * 100),
      categoryId: selectedCategoryId,
      date: todayStr(),
      note: note || undefined,
    })

    // Reset form
    setAmountText('')
    setSelectedCategoryId(null)
    setNote('')
    onClose()
  }, [amountText, selectedCategoryId, note, recordType, addRecord, onClose])

  const canSave = amountText !== '' && parseFloat(amountText) > 0 && selectedCategoryId !== null

  if (!visible) return null

  return (
    <overlay visible={visible} style={{ position: 'fixed' }}>
      <view
        style={{
          width: '100%',
          height: '100%',
          backgroundColor: 'rgba(0, 0, 0, 0.4)',
          display: 'flex',
          justifyContent: 'flex-end',
        }}
        bindtap={onClose}
      >
        <view
          catchtap={() => {}}
          style={{
            width: '100%',
            backgroundColor: '#fff',
            borderTopLeftRadius: '20px',
            borderTopRightRadius: '20px',
            padding: '20px 16px',
            paddingBottom: '40px',
          }}
        >
          {/* Type toggle */}
          <view
            style={{
              display: 'flex',
              flexDirection: 'row',
              marginBottom: '20px',
            }}
          >
            <view
              bindtap={() => { setRecordType('expense') }}
              style={{
                flex: 1,
                padding: '10px',
                borderRadius: '10px',
                backgroundColor: recordType === 'expense' ? '#FF6B6B' : '#f0f0f0',
                marginRight: '8px',
                display: 'flex',
                justifyContent: 'center',
              }}
            >
              <text style={{ color: recordType === 'expense' ? '#fff' : '#666', fontWeight: '600' }}>
                支出
              </text>
            </view>
            <view
              bindtap={() => { setRecordType('income') }}
              style={{
                flex: 1,
                padding: '10px',
                borderRadius: '10px',
                backgroundColor: recordType === 'income' ? '#00B894' : '#f0f0f0',
                display: 'flex',
                justifyContent: 'center',
              }}
            >
              <text style={{ color: recordType === 'income' ? '#fff' : '#666', fontWeight: '600' }}>
                收入
              </text>
            </view>
          </view>

          {/* Amount input */}
          <view
            style={{
              display: 'flex',
              flexDirection: 'row',
              alignItems: 'center',
              marginBottom: '16px',
              border: '1px solid #e0e0e0',
              borderRadius: '12px',
              padding: '8px 12px',
            }}
          >
            <text style={{ fontSize: '20px', color: recordType === 'expense' ? '#FF6B6B' : '#00B894', marginRight: '4px' }}>
              {recordType === 'expense' ? '-' : '+'}¥
            </text>
            <input
              type="digit"
              placeholder="0.00"
              style={{ flex: 1, fontSize: '20px', color: '#1a1a1a' }}
              value={amountText}
              bindinput={(e: any) => setAmountText(e.detail.value)}
            />
          </view>

          {/* Category picker */}
          <view style={{ marginBottom: '16px' }}>
            <text style={{ fontSize: '14px', color: '#999', marginBottom: '8px' }}>分类</text>
            <scroll-view
              scroll-x={true}
              style={{ height: '60px' }}
            >
              <view style={{ display: 'flex', flexDirection: 'row', padding: '4px 0' }}>
                {filteredCategories.map((cat) => (
                  <view
                    key={cat.id}
                    bindtap={() => { setSelectedCategoryId(cat.id) }}
                    style={{
                      marginRight: '12px',
                      display: 'flex',
                      flexDirection: 'column',
                      alignItems: 'center',
                      opacity: selectedCategoryId === cat.id ? 1 : 0.5,
                    }}
                  >
                    <CategoryIcon category={cat} size={22} />
                    <text style={{ fontSize: '11px', color: '#666', marginTop: '4px' }}>
                      {cat.name}
                    </text>
                  </view>
                ))}
              </view>
            </scroll-view>
          </view>

          {/* Note input */}
          <view style={{ marginBottom: '20px' }}>
            <input
              type="text"
              placeholder="添加备注（选填）"
              style={{
                width: '100%',
                fontSize: '14px',
                color: '#1a1a1a',
                border: '1px solid #e0e0e0',
                borderRadius: '12px',
                padding: '10px 12px',
              }}
              value={note}
              bindinput={(e: any) => setNote(e.detail.value)}
            />
          </view>

          {/* Save button */}
          <view
            bindtap={canSave ? onSave : undefined}
            style={{
              backgroundColor: canSave ? (recordType === 'expense' ? '#FF6B6B' : '#00B894') : '#e0e0e0',
              borderRadius: '12px',
              padding: '14px',
              display: 'flex',
              justifyContent: 'center',
            }}
          >
            <text style={{ color: '#fff', fontSize: '16px', fontWeight: '600' }}>保存</text>
          </view>
        </view>
      </view>
    </overlay>
  )
}
```

- [ ] **Step 2: Commit**

```bash
git add src/components/AddRecordModal.tsx
git commit -m "feat: add AddRecordModal component"
```

---

### Task 9: RecordsPage

**Files:**
- Create: `src/pages/RecordsPage.tsx`

- [ ] **Step 1: Write RecordsPage.tsx**

```typescript
// src/pages/RecordsPage.tsx
import { useCallback, useMemo, useState } from '@lynx-js/react'
import { useAppContext } from '../store/AppContext.js'
import { RecordItem } from '../components/RecordItem.js'
import { AddRecordModal } from '../components/AddRecordModal.js'
import { formatAmount } from '../utils/format.js'
import { filterRecordsByMonth, getYearMonth, shiftMonth, findCategory } from '../utils/stats.js'
import { Icon } from '../components/Icon.js'

export function RecordsPage() {
  const { state } = useAppContext()
  const [date, setDate] = useState(() => new Date())
  const [modalVisible, setModalVisible] = useState(false)

  const { year, month } = getYearMonth(date)

  const monthlyRecords = useMemo(
    () => filterRecordsByMonth(state.records, year, month),
    [state.records, year, month],
  )

  const summary = useMemo(() => {
    let income = 0
    let expense = 0
    for (const r of monthlyRecords) {
      if (r.type === 'income') income += r.amount
      else expense += r.amount
    }
    return { income, expense }
  }, [monthlyRecords])

  const onPrevMonth = useCallback(() => {
    'background only'
    const shifted = shiftMonth(year, month, -1)
    setDate(new Date(shifted.year, shifted.month - 1))
  }, [year, month])

  const onNextMonth = useCallback(() => {
    'background only'
    const shifted = shiftMonth(year, month, 1)
    setDate(new Date(shifted.year, shifted.month - 1))
  }, [year, month])

  // Group by date
  const grouped = useMemo(() => {
    const map = new Map<string, typeof monthlyRecords>()
    for (const r of monthlyRecords) {
      const list = map.get(r.date) ?? []
      list.push(r)
      map.set(r.date, list)
    }
    // Sort dates descending
    return [...map.entries()].sort((a, b) => b[0].localeCompare(a[0]))
  }, [monthlyRecords])

  return (
    <view style={{ flex: 1, backgroundColor: '#fafafa' }}>
      {/* Month header */}
      <view
        style={{
          display: 'flex',
          flexDirection: 'row',
          justifyContent: 'space-between',
          alignItems: 'center',
          padding: '16px',
          backgroundColor: '#fff',
        }}
      >
        <view bindtap={onPrevMonth} style={{ padding: '4px' }}>
          <Icon name="chevron-left" size={20} color="#666" />
        </view>
        <text style={{ fontSize: '18px', fontWeight: '700', color: '#1a1a1a' }}>
          {year}年{month}月
        </text>
        <view bindtap={onNextMonth} style={{ padding: '4px' }}>
          <Icon name="chevron-right" size={20} color="#666" />
        </view>
      </view>

      {/* Summary bar */}
      <view
        style={{
          display: 'flex',
          flexDirection: 'row',
          padding: '12px 16px',
          backgroundColor: '#fff',
          borderBottom: '1px solid #f0f0f0',
        }}
      >
        <view style={{ flex: 1 }}>
          <text style={{ fontSize: '12px', color: '#999' }}>收入</text>
          <text style={{ fontSize: '16px', color: '#00B894', fontWeight: '600' }}>
            ¥{formatAmount(summary.income)}
          </text>
        </view>
        <view style={{ flex: 1 }}>
          <text style={{ fontSize: '12px', color: '#999' }}>支出</text>
          <text style={{ fontSize: '16px', color: '#FF6B6B', fontWeight: '600' }}>
            ¥{formatAmount(summary.expense)}
          </text>
        </view>
      </view>

      {/* Record list */}
      <scroll-view
        scroll-y={true}
        style={{ flex: 1 }}
      >
        {grouped.length === 0 ? (
          <view
            style={{
              display: 'flex',
              justifyContent: 'center',
              alignItems: 'center',
              padding: '60px 0',
            }}
          >
            <text style={{ fontSize: '14px', color: '#ccc' }}>暂无记录</text>
          </view>
        ) : (
          grouped.map(([dateStr, records]) => (
            <view key={dateStr}>
              {/* Date divider */}
              <view
                style={{
                  padding: '10px 16px',
                  backgroundColor: '#fafafa',
                }}
              >
                <text style={{ fontSize: '13px', color: '#999', fontWeight: '500' }}>
                  {dateStr.slice(5)} {getDayLabel(dateStr)}
                </text>
              </view>
              {/* Records */}
              <view style={{ backgroundColor: '#fff' }}>
                {records.map((record) => (
                  <RecordItem
                    key={record.id}
                    record={record}
                    category={findCategory(state.categories, record.categoryId)}
                  />
                ))}
              </view>
            </view>
          ))
        )}
        <view style={{ height: '80px' }} />
      </scroll-view>

      {/* FAB */}
      <view
        bindtap={() => { setModalVisible(true) }}
        style={{
          position: 'fixed',
          bottom: '24px',
          right: '24px',
          width: '56px',
          height: '56px',
          borderRadius: '28px',
          backgroundColor: '#FF6B6B',
          display: 'flex',
          justifyContent: 'center',
          alignItems: 'center',
          boxShadow: '0 4px 12px rgba(255, 107, 107, 0.4)',
        }}
      >
        <Icon name="plus-circle" size={28} color="#fff" />
      </view>

      <AddRecordModal
        visible={modalVisible}
        onClose={() => { setModalVisible(false) }}
      />
    </view>
  )
}

function getDayLabel(dateStr: string): string {
  const days = ['日', '一', '二', '三', '四', '五', '六']
  const d = new Date(dateStr)
  return `周${days[d.getDay()]!}`
}
```

- [ ] **Step 2: Commit**

```bash
git add src/pages/RecordsPage.tsx
git commit -m "feat: add RecordsPage"
```

---

### Task 10: StatsPage

**Files:**
- Create: `src/pages/StatsPage.tsx`

- [ ] **Step 1: Write StatsPage.tsx**

```typescript
// src/pages/StatsPage.tsx
import { useCallback, useMemo, useState } from '@lynx-js/react'
import { useAppContext } from '../store/AppContext.js'
import { MonthBar } from '../components/MonthBar.js'
import { Icon } from '../components/Icon.js'
import { computeMonthlyStats, filterRecordsByMonth, getYearMonth, shiftMonth } from '../utils/stats.js'
import { formatAmount } from '../utils/format.js'

export function StatsPage() {
  const { state } = useAppContext()
  const [date, setDate] = useState(() => new Date())

  const { year, month } = getYearMonth(date)

  const onPrevMonth = useCallback(() => {
    'background only'
    const shifted = shiftMonth(year, month, -1)
    setDate(new Date(shifted.year, shifted.month - 1))
  }, [year, month])

  const onNextMonth = useCallback(() => {
    'background only'
    const shifted = shiftMonth(year, month, 1)
    setDate(new Date(shifted.year, shifted.month - 1))
  }, [year, month])

  const monthlyRecords = useMemo(
    () => filterRecordsByMonth(state.records, year, month),
    [state.records, year, month],
  )

  const stats = useMemo(() => computeMonthlyStats(monthlyRecords), [monthlyRecords])

  const barItems = useMemo(() => {
    const total = stats.totalExpense
    if (total === 0) return []

    return [...stats.expenseByCategory.entries()].map(([categoryId, amount]) => ({
      categoryId,
      amount,
      percentage: (amount / total) * 100,
    }))
  }, [stats])

  return (
    <view style={{ flex: 1, backgroundColor: '#fafafa' }}>
      {/* Month header */}
      <view
        style={{
          display: 'flex',
          flexDirection: 'row',
          justifyContent: 'space-between',
          alignItems: 'center',
          padding: '16px',
          backgroundColor: '#fff',
        }}
      >
        <view bindtap={onPrevMonth} style={{ padding: '4px' }}>
          <Icon name="chevron-left" size={20} color="#666" />
        </view>
        <text style={{ fontSize: '18px', fontWeight: '700', color: '#1a1a1a' }}>
          {month}月统计
        </text>
        <view bindtap={onNextMonth} style={{ padding: '4px' }}>
          <Icon name="chevron-right" size={20} color="#666" />
        </view>
      </view>

      {/* Summary cards */}
      <view
        style={{
          display: 'flex',
          flexDirection: 'row',
          padding: '16px',
          backgroundColor: '#fff',
        }}
      >
        <view
          style={{
            flex: 1,
            marginRight: '8px',
            padding: '16px',
            borderRadius: '12px',
            backgroundColor: '#f0fdf4',
          }}
        >
          <text style={{ fontSize: '12px', color: '#00B894' }}>总收入</text>
          <text style={{ fontSize: '20px', fontWeight: '700', color: '#00B894' }}>
            ¥{formatAmount(stats.totalIncome)}
          </text>
        </view>
        <view
          style={{
            flex: 1,
            marginLeft: '8px',
            marginRight: '8px',
            padding: '16px',
            borderRadius: '12px',
            backgroundColor: '#fff5f5',
          }}
        >
          <text style={{ fontSize: '12px', color: '#FF6B6B' }}>总支出</text>
          <text style={{ fontSize: '20px', fontWeight: '700', color: '#FF6B6B' }}>
            ¥{formatAmount(stats.totalExpense)}
          </text>
        </view>
        <view
          style={{
            flex: 1,
            marginLeft: '8px',
            padding: '16px',
            borderRadius: '12px',
            backgroundColor: '#f0f9ff',
          }}
        >
          <text style={{ fontSize: '12px', color: '#0984E3' }}>结余</text>
          <text
            style={{
              fontSize: '20px',
              fontWeight: '700',
              color: stats.balance >= 0 ? '#0984E3' : '#FF6B6B',
            }}
          >
            ¥{formatAmount(Math.abs(stats.balance))}
          </text>
        </view>
      </view>

      {/* Expense breakdown */}
      <view style={{ padding: '16px', backgroundColor: '#fff', marginTop: '8px' }}>
        <text style={{ fontSize: '16px', fontWeight: '600', color: '#1a1a1a', marginBottom: '16px' }}>
          支出分类
        </text>
        <MonthBar items={barItems} total={stats.totalExpense} categories={state.categories} />
      </view>
    </view>
  )
}
```

- [ ] **Step 2: Commit**

```bash
git add src/pages/StatsPage.tsx
git commit -m "feat: add StatsPage"
```

---

### Task 11: SettingsPage

**Files:**
- Create: `src/pages/SettingsPage.tsx`

- [ ] **Step 1: Write SettingsPage.tsx**

```typescript
// src/pages/SettingsPage.tsx
import { useCallback } from '@lynx-js/react'
import { useAppContext } from '../store/AppContext.js'
import { CategoryIcon } from '../components/CategoryIcon.js'
import type { Category } from '../store/types.js'

export function SettingsPage() {
  const { state, dispatch } = useAppContext()

  const expenseCategories = state.categories.filter((c) => c.type === 'expense')
  const incomeCategories = state.categories.filter((c) => c.type === 'income')

  const onDeleteCategory = useCallback(
    (id: string) => {
      'background only'
      dispatch({ type: 'DELETE_CATEGORY', payload: id })
    },
    [dispatch],
  )

  return (
    <scroll-view scroll-y={true} style={{ flex: 1, backgroundColor: '#fafafa' }}>
      {/* Expense categories */}
      <view style={{ backgroundColor: '#fff', marginTop: '8px' }}>
        <text
          style={{
            fontSize: '14px',
            fontWeight: '600',
            color: '#666',
            padding: '16px 16px 8px',
          }}
        >
          支出分类
        </text>
        {expenseCategories.map((cat) => (
          <CategoryRow
            key={cat.id}
            category={cat}
            onDelete={cat.isDefault ? undefined : () => onDeleteCategory(cat.id)}
          />
        ))}
      </view>

      {/* Income categories */}
      <view style={{ backgroundColor: '#fff', marginTop: '8px' }}>
        <text
          style={{
            fontSize: '14px',
            fontWeight: '600',
            color: '#666',
            padding: '16px 16px 8px',
          }}
        >
          收入分类
        </text>
        {incomeCategories.map((cat) => (
          <CategoryRow
            key={cat.id}
            category={cat}
            onDelete={cat.isDefault ? undefined : () => onDeleteCategory(cat.id)}
          />
        ))}
      </view>

      {/* Footer */}
      <view
        style={{
          padding: '24px 16px',
          display: 'flex',
          justifyContent: 'center',
        }}
      >
        <text style={{ fontSize: '12px', color: '#ccc' }}>Bookkeeping v1.0</text>
      </view>
    </scroll-view>
  )
}

function CategoryRow({
  category,
  onDelete,
}: {
  category: Category
  onDelete?: () => void
}) {
  return (
    <view
      style={{
        display: 'flex',
        flexDirection: 'row',
        alignItems: 'center',
        padding: '12px 16px',
        borderBottom: '1px solid #f5f5f5',
      }}
    >
      <CategoryIcon category={category} size={18} />
      <text style={{ fontSize: '16px', color: '#1a1a1a', marginLeft: '12px', flex: 1 }}>
        {category.name}
      </text>
      {onDelete ? (
        <view
          bindtap={onDelete}
          style={{
            padding: '6px 12px',
            borderRadius: '6px',
            backgroundColor: '#fff5f5',
          }}
        >
          <text style={{ fontSize: '13px', color: '#FF6B6B' }}>删除</text>
        </view>
      ) : (
        <text style={{ fontSize: '12px', color: '#ccc' }}>默认</text>
      )}
    </view>
  )
}
```

- [ ] **Step 2: Commit**

```bash
git add src/pages/SettingsPage.tsx
git commit -m "feat: add SettingsPage"
```

---

### Task 12: App Shell (App.tsx + App.css)

**Files:**
- Replace: `src/App.tsx`
- Replace: `src/App.css`

- [ ] **Step 1: Write App.tsx**

```typescript
// src/App.tsx
import { useState } from '@lynx-js/react'
import './App.css'
import { AppProvider } from './store/AppContext.js'
import { RecordsPage } from './pages/RecordsPage.js'
import { StatsPage } from './pages/StatsPage.js'
import { SettingsPage } from './pages/SettingsPage.js'

type Tab = 'records' | 'stats' | 'settings'

const TABS: { key: Tab; label: string }[] = [
  { key: 'records', label: '流水' },
  { key: 'stats', label: '统计' },
  { key: 'settings', label: '设置' },
]

export function App() {
  const [activeTab, setActiveTab] = useState<Tab>('records')

  return (
    <AppProvider>
      <view className="AppContainer">
        {/* Page content */}
        <view style={{ flex: 1 }}>
          {activeTab === 'records' && <RecordsPage />}
          {activeTab === 'stats' && <StatsPage />}
          {activeTab === 'settings' && <SettingsPage />}
        </view>

        {/* Bottom tab bar */}
        <view className="TabBar">
          {TABS.map((tab) => (
            <view
              key={tab.key}
              className={`TabItem ${activeTab === tab.key ? 'TabItem--active' : ''}`}
              bindtap={() => { setActiveTab(tab.key) }}
            >
              <text
                style={{
                  fontSize: '14px',
                  fontWeight: activeTab === tab.key ? '600' : '400',
                  color: activeTab === tab.key ? '#FF6B6B' : '#999',
                }}
              >
                {tab.label}
              </text>
            </view>
          ))}
        </view>
      </view>
    </AppProvider>
  )
}
```

- [ ] **Step 2: Write App.css**

```css
/* src/App.css */

:root {
  background-color: #fafafa;
  --color-text: #1a1a1a;
}

.AppContainer {
  display: flex;
  flex-direction: column;
  height: 100vh;
}

.TabBar {
  display: flex;
  flex-direction: row;
  background-color: #fff;
  border-top: 1px solid #f0f0f0;
  padding-bottom: env(safe-area-inset-bottom);
}

.TabItem {
  flex: 1;
  display: flex;
  justify-content: center;
  align-items: center;
  padding: 14px 0;
}
```

- [ ] **Step 3: Update index.tsx**

Replace `src/index.tsx` content:

```typescript
import '@lynx-js/preact-devtools'
import '@lynx-js/react/debug'
import { root } from '@lynx-js/react'

import { App } from './App.js'

root.render(<App />)

if (import.meta.webpackHot) {
  import.meta.webpackHot.accept()
}
```

(Content is identical to existing — no change needed.)

- [ ] **Step 4: Commit**

```bash
git add src/App.tsx src/App.css
git commit -m "feat: add App shell with tab navigation"
```

---

### Task 13: Tests & Cleanup

**Files:**
- Replace: `src/__tests__/index.test.jsx`
- Create: `src/__tests__/utils.test.ts`
- Remove: `src/useFlappy.ts`, `src/lib/flappy.ts`, `src/assets/arrow.png`, `src/assets/lynx-logo.png`, `src/assets/react-logo.png`

- [ ] **Step 1: Write component test**

```tsx
// src/__tests__/index.test.jsx
import '@testing-library/jest-dom'
import { expect, test } from 'vitest'
import { fireEvent, getQueriesForElement, render } from '@lynx-js/react/testing-library'

import { App } from '../App'

test('renders tab bar with three tabs', async () => {
  render(<App />)

  const { findByText } = getQueriesForElement(elementTree.root)

  const recordsTab = await findByText('流水')
  const statsTab = await findByText('统计')
  const settingsTab = await findByText('设置')

  expect(recordsTab).toBeInTheDocument()
  expect(statsTab).toBeInTheDocument()
  expect(settingsTab).toBeInTheDocument()
})

test('shows month header on records page', async () => {
  render(<App />)

  const { findByText } = getQueriesForElement(elementTree.root)

  // Should see current month
  const now = new Date()
  const monthText = `${now.getFullYear()}年${now.getMonth() + 1}月`
  const element = await findByText(monthText)
  expect(element).toBeInTheDocument()
})
```

- [ ] **Step 2: Write utility tests**

```typescript
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
```

- [ ] **Step 3: Run tests to verify**

```bash
npx vitest run
```

Expected: All tests pass.

- [ ] **Step 4: Clean up old demo files**

```bash
Remove-Item -LiteralPath "src/useFlappy.ts" -Force
Remove-Item -LiteralPath "src/lib" -Recurse -Force
Remove-Item -LiteralPath "src/assets/arrow.png" -Force
Remove-Item -LiteralPath "src/assets/lynx-logo.png" -Force
Remove-Item -LiteralPath "src/assets/react-logo.png" -Force
```

- [ ] **Step 5: Verify build compiles**

```bash
npx rspeedy build
```

Expected: Build succeeds without errors.

- [ ] **Step 6: Commit**

```bash
git add -A
git commit -m "feat: add tests, cleanup old demo files"
```

---

## Dependency Order

```
Task 1 (types + icons)
  └─ Task 2 (utils) ──┐
  └─ Task 3 (data) ───┤
                       ├── Task 4 (context)
                       │     └─ Task 5 (Icon components) ──┐
                       │     └─ Task 6 (RecordItem) ───────┤
                       │     └─ Task 7 (MonthBar) ─────────┤
                       │     └─ Task 8 (AddRecordModal) ───┤
                       │                                   ├── Task 9 (RecordsPage)
                       │                                   ├── Task 10 (StatsPage)
                       │                                   ├── Task 11 (SettingsPage)
                       │                                   │
                       └───────────────────────────────────┴── Task 12 (App.tsx)
                                                               └── Task 13 (tests)
```

Tasks 1-4 are sequential. Tasks 5-8 can run in parallel after Task 4. Tasks 9-11 can run in parallel after Tasks 5-8. Task 12 after 9-11. Task 13 last.
