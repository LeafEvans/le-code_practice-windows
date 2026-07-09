# Bookkeeping App — Design Spec

**Date:** 2026-07-10  
**Platform:** ReactLynx (cross-platform Android/iOS)  
**Scope:** Personal daily bookkeeping — standard edition

---

## 1. Overview

A personal finance tracking app built with ReactLynx. Core features: income/expense recording, category management, and monthly statistics.

### Non-goals (for this version)
- Cloud sync / multi-device
- Budget management
- Multiple accounts (cash, bank card)
- Data export

---

## 2. Architecture

### 2.1 Module Structure

```
src/
├── App.tsx                  # Entry, tab routing
├── index.tsx                # Mount point
├── pages/
│   ├── RecordsPage.tsx      # Tab 1 — record list + add
│   ├── StatsPage.tsx        # Tab 2 — monthly charts
│   └── SettingsPage.tsx     # Tab 3 — category management
├── components/
│   ├── AddRecordModal.tsx   # Add/edit record panel
│   ├── RecordItem.tsx       # Single record row
│   ├── CategoryIcon.tsx     # Category icon (SVG)
│   ├── MonthBar.tsx         # Monthly percentage bar
│   └── Icon.tsx             # Generic SVG icon component
├── store/
│   ├── AppContext.tsx        # Context Provider + Reducer
│   └── types.ts              # State type definitions
├── data/
│   ├── storage.ts           # AsyncStorage read/write
│   ├── categories.ts        # Default categories
│   └── icons.ts             # SVG path data for Lucide icons
├── utils/
│   ├── format.ts            # Amount/date formatting
│   └── stats.ts             # Statistics computation
```

### 2.2 Data Flow

```
App mount
  └→ storage.load() → LOAD_DATA
       └→ Context initialized with persisted state

User action (add/delete/update)
  └→ dispatch(action)
       ├→ reducer updates state
       ├→ React re-renders affected components
       └→ storage.save(state) — auto-persist
```

**Principles:**
- Unidirectional data flow: pages never mutate state directly
- `data/` layer encapsulates all I/O; pages interact only through Context
- Each page is independently maintainable

---

## 3. Data Model

### 3.1 Types

```typescript
type Record = {
  id: string              // UUID
  type: 'income' | 'expense'
  amount: number          // In cents (avoids floating point issues)
  categoryId: string
  date: string            // 'YYYY-MM-DD'
  note?: string
  createdAt: number       // Timestamp for stable ordering
}

type Category = {
  id: string
  name: string            // '餐饮', '交通', etc.
  type: 'income' | 'expense'
  icon: string            // Icon key referencing icons.ts
  isDefault: boolean      // System default — cannot be deleted
}

type AppState = {
  records: Record[]
  categories: Category[]
}
```

### 3.2 Actions

```typescript
type Action =
  | { type: 'ADD_RECORD'; payload: Record }
  | { type: 'DELETE_RECORD'; payload: string }
  | { type: 'UPDATE_RECORD'; payload: Record }
  | { type: 'ADD_CATEGORY'; payload: Category }
  | { type: 'DELETE_CATEGORY'; payload: string }
  | { type: 'LOAD_DATA'; payload: AppState }
```

### 3.3 Persistence

- **Key:** `lynx_bookkeeping_data`
- **Format:** JSON-serialized `AppState`
- **Trigger:** After every reducer dispatch
- **Load:** On app mount (`LOAD_DATA` action)

---

## 4. Pages

### 4.1 RecordsPage (Tab 1)

- **Top bar:** Current month with `< >` navigation, month income/expense summary
- **List:** Records grouped by date, sorted newest-first
- **Each row (`RecordItem`):** Category icon (SVG), category name, amount (red for expense, green for income), optional note
- **FAB:** Floating "+" button, bottom-right, opens `AddRecordModal`

### 4.2 StatsPage (Tab 2)

- **Header:** Month selector
- **Chart (`MonthBar`):** Expense category breakdown — horizontal colored percentage bars
- **Summary:** Total income, total expense, balance (income - expense)

### 4.3 SettingsPage (Tab 3)

- **Expense categories list:** Each with icon, name, delete button (hidden for defaults)
- **Income categories list:** Same layout
- **Add category:** Button to create custom category

### 4.4 AddRecordModal (overlay)

Uses Lynx native `<overlay>` element with `visible` prop to toggle.

- **Type toggle:** Income / Expense tab
- **Amount input:** Lynx `<input type="number">` with placeholder "0.00"
- **Category picker:** Horizontal scroll of category icons
- **Date:** Defaults to today, displayed as text (simple date; full picker deferred)
- **Note input:** `<input type="text">` optional field
- **Save button:** Validates amount > 0 before dispatching `ADD_RECORD`

---

## 5. Icons

### 5.1 Approach

Use Lynx native `<svg>` element with Lucide icon path data. Each icon is a string of SVG path data rendered via a generic `Icon` component.

```tsx
<Icon name="utensils" size={24} color="#FF6B6B" />
```

### 5.2 Required Icons (~18)

**Categories (12):**
- Expense: `utensils` (餐饮), `bus` (交通), `shopping-bag` (购物), `gamepad-2` (娱乐), `home` (居住), `smartphone` (通讯), `pill` (医疗), `spray-can` (日用)
- Income: `banknote` (工资), `briefcase` (兼职), `red-envelope` — use `gift`, `trending-up` (理财)

**UI Chrome (6):**
- `plus-circle` (add record FAB)
- `chevron-left` / `chevron-right` (month navigation)
- `x` (close modal)
- `trash-2` (delete)
- `check` (save)

### 5.3 Default Categories (12)

| Name | Icon key | Type |
|------|----------|------|
| 餐饮 | utensils | expense |
| 交通 | bus | expense |
| 购物 | shopping-bag | expense |
| 娱乐 | gamepad-2 | expense |
| 居住 | home | expense |
| 通讯 | smartphone | expense |
| 医疗 | pill | expense |
| 日用 | spray-can | expense |
| 工资 | banknote | income |
| 兼职 | briefcase | income |
| 红包 | gift | income |
| 理财 | trending-up | income |

### 5.4 Color Palette (Categories)

| Icon | Color |
|------|-------|
| utensils | #FF6B6B |
| bus | #4ECDC4 |
| shopping-bag | #FFD93D |
| gamepad-2 | #6C5CE7 |
| home | #A29BFE |
| smartphone | #FD79A8 |
| pill | #00B894 |
| spray-can | #E17055 |
| banknote | #00B894 |
| briefcase | #0984E3 |
| gift | #E84393 |
| trending-up | #FDCB6E |

---

## 6. Seed Data

Four demo records pre-loaded for first-time experience:

```
🍔 餐饮  -¥35.00  午餐
🚌 交通  -¥12.50  地铁通勤
💰 工资  +¥3,500  7月工资
🛒 购物  -¥128.00 超市采购
```

Generated iff storage is empty on first load.

---

## 7. State Management

React Context + `useReducer`. Single `AppContext` provides:

```typescript
const { state, dispatch } = useAppContext()
```

- **Provider** wraps entire app in `App.tsx`
- **Reducer** is a pure function handling 6 action types
- **Persistence** hook inside Provider: `useEffect` calls `storage.save(state)` on state change
- **Initial load** hook: on mount, calls `storage.load()` and dispatches `LOAD_DATA`

---

## 8. Technical Constraints

- **UI components:** Lynx primitives only — `<view>`, `<text>`, `<image>`, `<svg>`, `<scroll-view>`, `<input>`, `<overlay>`
- **No DOM APIs:** No `document`, no `window`, no CSS pseudo-elements
- **Styling:** Lynx CSS subset (flexbox, transforms, animations; also `linear` layout mode)
- **Navigation:** Manual tab switching via state, no router library
- **Storage:** Abstracted behind `data/storage.ts`. Initial implementation uses in-memory module state (data persists within session). Interface designed to swap in native persistence layer later.
- **Icon rendering:** Lynx `<svg>` element with `content` attribute (Lynx 3.7+)
- **Modal:** Lynx `<overlay>` element with `visible` prop (Lynx 3.5+)
- **Text input:** Lynx `<input>` element with `type="number"`/`type="text"` (Lynx 3.4+)

---

## 9. File Changes Summary

| Action | File |
|--------|------|
| **Replace** | `src/App.tsx` — Rewrite as tab container |
| **Replace** | `src/App.css` — Replace demo styles with app styles |
| **Replace** | `src/index.tsx` — Keep mount, may need minor tweaks |
| **Create** | `src/pages/RecordsPage.tsx` |
| **Create** | `src/pages/StatsPage.tsx` |
| **Create** | `src/pages/SettingsPage.tsx` |
| **Create** | `src/components/AddRecordModal.tsx` |
| **Create** | `src/components/RecordItem.tsx` |
| **Create** | `src/components/CategoryIcon.tsx` |
| **Create** | `src/components/MonthBar.tsx` |
| **Create** | `src/components/Icon.tsx` |
| **Create** | `src/store/AppContext.tsx` |
| **Create** | `src/store/types.ts` |
| **Create** | `src/data/storage.ts` |
| **Create** | `src/data/categories.ts` |
| **Create** | `src/data/icons.ts` |
| **Create** | `src/data/seed.ts` |
| **Create** | `src/utils/format.ts` |
| **Create** | `src/utils/stats.ts` |
| **Update** | `src/__tests__/` — Add unit tests |
