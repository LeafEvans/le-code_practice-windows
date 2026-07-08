# Expense Tracker Implementation Plan

> **For agentic workers:** Use superpowers:subagent-driven-development or superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Build a local-first expense tracking React Native app in `projects/rn/test_07_08/` with Expo SDK 55 + pnpm, ready for HarmonyOS via expo-harmony-toolkit.

**Architecture:** Expo Router file-based routing, AsyncStorage persistence, SVG charts, Reanimated animations. Four screens (dashboard, records, stats, add modal).

**Tech Stack:** Expo SDK 55, React Native 0.82, Expo Router, react-native-svg, react-native-reanimated, @react-native-async-storage/async-storage, pnpm.

---

## Task 1: Scaffold Expo Project

**Files:** All project scaffolding

- [ ] **Step 1: Create project with create-expo-app**

```bash
cd projects/rn
npx create-expo-app@latest test_07_08 --template blank-typescript -- --pnpm
```

- [ ] **Step 2: Install runtime dependencies**

```bash
cd projects/rn/test_07_08
pnpm add expo-router react-native-svg react-native-reanimated @react-native-async-storage/async-storage react-native-gesture-handler react-native-safe-area-context expo-system-ui expo-status-bar expo-linking expo-constants
```

- [ ] **Step 3: Install dev dependencies**

```bash
pnpm add -D expo-harmony-toolkit
```

- [ ] **Step 4: Create .npmrc for RN compatibility**

```text
# projects/rn/test_07_08/.npmrc
shamefully-hoist=true
strict-peer-dependencies=false
```

- [ ] **Step 5: Commit**

---

## Task 2: Foundation Files (types, constants, utils, hooks)

**Files:**
- Create: `projects/rn/test_07_08/src/types/index.ts`
- Create: `projects/rn/test_07_08/src/constants/categories.ts`
- Create: `projects/rn/test_07_08/src/utils/format.ts`
- Create: `projects/rn/test_07_08/src/hooks/useRecords.ts`

### `src/types/index.ts`

```ts
export interface Record {
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
```

### `src/constants/categories.ts`

```ts
import { Category } from '../types';

export const EXPENSE_CATEGORIES: Category[] = [
  { key: 'food', label: '餐饮', icon: '🍔' },
  { key: 'transport', label: '交通', icon: '🚗' },
  { key: 'shopping', label: '购物', icon: '🛒' },
  { key: 'housing', label: '住房', icon: '🏠' },
  { key: 'entertainment', label: '娱乐', icon: '🎮' },
  { key: 'medical', label: '医疗', icon: '🏥' },
  { key: 'education', label: '教育', icon: '📚' },
  { key: 'other', label: '其他', icon: '💡' },
];

export const INCOME_CATEGORIES: Category[] = [
  { key: 'salary', label: '工资', icon: '💰' },
  { key: 'freelance', label: '兼职', icon: '🔧' },
  { key: 'investment', label: '理财', icon: '📈' },
  { key: 'redpacket', label: '红包', icon: '🎁' },
  { key: 'other', label: '其他', icon: '💡' },
];

export function getCategoryLabel(type: 'income' | 'expense', key: string): string {
  const cats = type === 'income' ? INCOME_CATEGORIES : EXPENSE_CATEGORIES;
  return cats.find(c => c.key === key)?.label ?? key;
}

export function getCategoryIcon(type: 'income' | 'expense', key: string): string {
  const cats = type === 'income' ? INCOME_CATEGORIES : EXPENSE_CATEGORIES;
  return cats.find(c => c.key === key)?.icon ?? '💡';
}
```

### `src/utils/format.ts`

```ts
export function formatCurrency(amount: number): string {
  return `¥${amount.toFixed(2)}`;
}

export function formatDate(dateStr: string): string {
  const d = new Date(dateStr);
  return `${d.getMonth() + 1}月${d.getDate()}日`;
}

export function getMonthKey(dateStr: string): string {
  return dateStr.slice(0, 7); // YYYY-MM
}

export function getCurrentMonth(): string {
  return new Date().toISOString().slice(0, 7);
}

export function getToday(): string {
  return new Date().toISOString().slice(0, 10);
}
```

### `src/hooks/useRecords.ts`

```ts
import { useState, useEffect, useCallback } from 'react';
import AsyncStorage from '@react-native-async-storage/async-storage';
import { Record } from '../types';

const STORAGE_KEY = '@expense_records';

export function useRecords() {
  const [records, setRecords] = useState<Record[]>([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    loadRecords();
  }, []);

  const loadRecords = async () => {
    try {
      const data = await AsyncStorage.getItem(STORAGE_KEY);
      setRecords(data ? JSON.parse(data) : []);
    } catch (e) {
      console.error('Failed to load records:', e);
    } finally {
      setLoading(false);
    }
  };

  const saveRecords = async (newRecords: Record[]) => {
    await AsyncStorage.setItem(STORAGE_KEY, JSON.stringify(newRecords));
    setRecords(newRecords);
  };

  const addRecord = useCallback(async (record: Record) => {
    const newRecords = [record, ...records];
    await saveRecords(newRecords);
  }, [records]);

  const deleteRecord = useCallback(async (id: string) => {
    const newRecords = records.filter(r => r.id !== id);
    await saveRecords(newRecords);
  }, [records]);

  const getMonthlyTotal = useCallback((monthKey: string, type: 'income' | 'expense') => {
    return records
      .filter(r => r.type === type && r.date.startsWith(monthKey))
      .reduce((sum, r) => sum + r.amount, 0);
  }, [records]);

  const getMonthlyRecords = useCallback((monthKey: string) => {
    return records
      .filter(r => r.date.startsWith(monthKey))
      .sort((a, b) => b.date.localeCompare(a.date));
  }, [records]);

  const getCategoryBreakdown = useCallback((monthKey: string, type: 'income' | 'expense') => {
    const breakdown: Record<string, number> = {};
    records
      .filter(r => r.type === type && r.date.startsWith(monthKey))
      .forEach(r => {
        breakdown[r.category] = (breakdown[r.category] || 0) + r.amount;
      });
    return breakdown;
  }, [records]);

  const getAvailableMonths = useCallback(() => {
    const months = new Set(records.map(r => r.date.slice(0, 7)));
    return Array.from(months).sort().reverse();
  }, [records]);

  return {
    records,
    loading,
    addRecord,
    deleteRecord,
    getMonthlyTotal,
    getMonthlyRecords,
    getCategoryBreakdown,
    getAvailableMonths,
  };
}
```

- [ ] **Step 1: Create all four files with content above**

- [ ] **Step 2: Commit**

---

## Task 3: Components (PieChart, BarChart, SummaryCard, CategoryPicker)

**Files:**
- Create: `projects/rn/test_07_08/src/components/PieChart.tsx`
- Create: `projects/rn/test_07_08/src/components/BarChart.tsx`
- Create: `projects/rn/test_07_08/src/components/SummaryCard.tsx`
- Create: `projects/rn/test_07_08/src/components/CategoryPicker.tsx`

### `src/components/PieChart.tsx`

```tsx
import React from 'react';
import { View, Text } from 'react-native';
import Svg, { Path, G } from 'react-native-svg';

interface PieSlice {
  label: string;
  value: number;
  color: string;
  icon: string;
}

interface PieChartProps {
  data: PieSlice[];
  size?: number;
}

const COLORS = ['#FF6384', '#36A2EB', '#FFCE56', '#4BC0C0', '#9966FF', '#FF9F40', '#C9CBCF', '#7BC67E'];

function polarToCartesian(cx: number, cy: number, r: number, angleDeg: number) {
  const angleRad = ((angleDeg - 90) * Math.PI) / 180;
  return { x: cx + r * Math.cos(angleRad), y: cy + r * Math.sin(angleRad) };
}

function describeArc(cx: number, cy: number, r: number, startAngle: number, endAngle: number) {
  const start = polarToCartesian(cx, cy, r, endAngle);
  const end = polarToCartesian(cx, cy, r, startAngle);
  const largeArcFlag = endAngle - startAngle <= 180 ? '0' : '1';
  return `M ${cx} ${cy} L ${start.x} ${start.y} A ${r} ${r} 0 ${largeArcFlag} 0 ${end.x} ${end.y} Z`;
}

export default function PieChart({ data, size = 200 }: PieChartProps) {
  const total = data.reduce((sum, d) => sum + d.value, 0);
  if (total === 0) {
    return (
      <View style={{ width: size, height: size, justifyContent: 'center', alignItems: 'center' }}>
        <Text style={{ color: '#999' }}>暂无数据</Text>
      </View>
    );
  }

  const radius = size / 2 * 0.8;
  const cx = size / 2;
  const cy = size / 2;
  let currentAngle = 0;

  const filtered = data.filter(d => d.value > 0);

  return (
    <View style={{ width: size, height: size }}>
      <Svg width={size} height={size}>
        <G>
          {filtered.map((slice, i) => {
            const sliceAngle = (slice.value / total) * 360;
            const startAngle = currentAngle;
            const endAngle = currentAngle + sliceAngle;
            currentAngle += sliceAngle;
            return (
              <Path
                key={i}
                d={describeArc(cx, cy, radius, startAngle, endAngle)}
                fill={slice.color || COLORS[i % COLORS.length]}
              />
            );
          })}
        </G>
      </Svg>
    </View>
  );
}
```

### `src/components/BarChart.tsx`

```tsx
import React from 'react';
import { View, Text } from 'react-native';
import Svg, { Rect, Line, G, Text as SvgText } from 'react-native-svg';

interface BarData {
  label: string;
  value: number;
}

interface BarChartProps {
  data: BarData[];
  width?: number;
  height?: number;
  color?: string;
  unit?: string;
}

export default function BarChart({ data, width = 340, height = 200, color = '#4BC0C0', unit = '¥' }: BarChartProps) {
  if (data.length === 0) {
    return (
      <View style={{ width, height, justifyContent: 'center', alignItems: 'center' }}>
        <Text style={{ color: '#999' }}>暂无数据</Text>
      </View>
    );
  }

  const padding = { top: 20, right: 10, bottom: 40, left: 50 };
  const chartW = width - padding.left - padding.right;
  const chartH = height - padding.top - padding.bottom;
  const maxVal = Math.max(...data.map(d => d.value), 1);
  const barW = Math.min(30, (chartW / data.length) * 0.7);
  const gap = chartW / data.length;

  return (
    <Svg width={width} height={height}>
      <G x={padding.left} y={padding.top}>
        {/* Y axis */}
        <Line x1={0} y1={0} x2={0} y2={chartH} stroke="#ddd" strokeWidth={1} />
        {/* X axis */}
        <Line x1={0} y1={chartH} x2={chartW} y2={chartH} stroke="#ddd" strokeWidth={1} />
        {/* Bars */}
        {data.map((d, i) => {
          const barH = (d.value / maxVal) * chartH;
          const x = i * gap + (gap - barW) / 2;
          const y = chartH - barH;
          return (
            <G key={i}>
              <Rect x={x} y={y} width={barW} height={barH} fill={color} rx={4} />
              <SvgText x={x + barW / 2} y={chartH + 16} fontSize={10} fill="#666" textAnchor="middle">
                {d.label}
              </SvgText>
              <SvgText x={x + barW / 2} y={y - 6} fontSize={10} fill="#333" textAnchor="middle">
                {d.value > 0 ? `${unit}${d.value}` : ''}
              </SvgText>
            </G>
          );
        })}
      </G>
    </Svg>
  );
}
```

### `src/components/SummaryCard.tsx`

```tsx
import React from 'react';
import { View, Text, StyleSheet } from 'react-native';
import { formatCurrency } from '../utils/format';

interface SummaryCardProps {
  label: string;
  amount: number;
  type: 'income' | 'expense' | 'balance';
}

export default function SummaryCard({ label, amount, type }: SummaryCardProps) {
  const color = type === 'income' ? '#4CAF50' : type === 'expense' ? '#F44336' : '#2196F3';
  const prefix = type === 'income' ? '+' : type === 'expense' ? '-' : '';
  return (
    <View style={[styles.card, { borderTopColor: color }]}>
      <Text style={styles.label}>{label}</Text>
      <Text style={[styles.amount, { color }]}>{prefix}{formatCurrency(amount)}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  card: {
    flex: 1,
    backgroundColor: '#fff',
    borderRadius: 12,
    padding: 16,
    marginHorizontal: 4,
    borderTopWidth: 3,
    elevation: 2,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 1 },
    shadowOpacity: 0.1,
    shadowRadius: 4,
  },
  label: { fontSize: 13, color: '#888', marginBottom: 6 },
  amount: { fontSize: 20, fontWeight: '700' },
});
```

### `src/components/CategoryPicker.tsx`

```tsx
import React from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';
import { Category } from '../types';

interface CategoryPickerProps {
  categories: Category[];
  selected: string;
  onSelect: (key: string) => void;
}

export default function CategoryPicker({ categories, selected, onSelect }: CategoryPickerProps) {
  return (
    <View style={styles.grid}>
      {categories.map(cat => (
        <TouchableOpacity
          key={cat.key}
          style={[styles.item, selected === cat.key && styles.itemSelected]}
          onPress={() => onSelect(cat.key)}
        >
          <Text style={styles.icon}>{cat.icon}</Text>
          <Text style={[styles.itemLabel, selected === cat.key && styles.itemLabelSelected]}>{cat.label}</Text>
        </TouchableOpacity>
      ))}
    </View>
  );
}

const styles = StyleSheet.create({
  grid: { flexDirection: 'row', flexWrap: 'wrap', gap: 8, paddingVertical: 8 },
  item: {
    width: '22%',
    aspectRatio: 1,
    backgroundColor: '#f5f5f5',
    borderRadius: 12,
    alignItems: 'center',
    justifyContent: 'center',
    padding: 4,
  },
  itemSelected: { backgroundColor: '#e3f2fd', borderWidth: 2, borderColor: '#2196F3' },
  icon: { fontSize: 24, marginBottom: 2 },
  itemLabel: { fontSize: 11, color: '#666' },
  itemLabelSelected: { color: '#2196F3', fontWeight: '600' },
});
```

- [ ] **Step 1: Create all four components**

- [ ] **Step 2: Commit**

---

## Task 4: Pages (app directory)

**Files:**
- Create: `projects/rn/test_07_08/app/_layout.tsx`
- Create: `projects/rn/test_07_08/app/index.tsx`
- Create: `projects/rn/test_07_08/app/records.tsx`
- Create: `projects/rn/test_07_08/app/stats.tsx`
- Create: `projects/rn/test_07_08/app/add.tsx`

### `app/_layout.tsx`

```tsx
import React from 'react';
import { Stack } from 'expo-router';
import { StatusBar } from 'expo-status-bar';

export default function RootLayout() {
  return (
    <>
      <StatusBar style="dark" />
      <Stack>
        <Stack.Screen name="index" options={{ title: '记账', headerTitleAlign: 'center' }} />
        <Stack.Screen name="records" options={{ title: '账单', headerTitleAlign: 'center' }} />
        <Stack.Screen name="stats" options={{ title: '统计', headerTitleAlign: 'center' }} />
        <Stack.Screen
          name="add"
          options={{
            presentation: 'modal',
            title: '记一笔',
            headerTitleAlign: 'center',
          }}
        />
      </Stack>
    </>
  );
}
```

### `app/index.tsx` (Dashboard)

```tsx
import React from 'react';
import { View, Text, StyleSheet, ScrollView, TouchableOpacity } from 'react-native';
import { router } from 'expo-router';
import SummaryCard from '../src/components/SummaryCard';
import PieChart from '../src/components/PieChart';
import { useRecords } from '../src/hooks/useRecords';
import { getCurrentMonth } from '../src/utils/format';
import { EXPENSE_CATEGORIES, getCategoryIcon } from '../src/constants/categories';
import { Record } from '../src/types';

const CHART_COLORS = ['#FF6384', '#36A2EB', '#FFCE56', '#4BC0C0', '#9966FF', '#FF9F40', '#C9CBCF', '#7BC67E'];

export default function Dashboard() {
  const { getMonthlyTotal, getCategoryBreakdown, loading } = useRecords();
  const month = getCurrentMonth();

  const income = getMonthlyTotal(month, 'income');
  const expense = getMonthlyTotal(month, 'expense');
  const balance = income - expense;

  const expenseBreakdown = getCategoryBreakdown(month, 'expense');
  const pieData = Object.entries(expenseBreakdown).map(([key, value], i) => ({
    label: key,
    value,
    color: CHART_COLORS[i % CHART_COLORS.length],
    icon: getCategoryIcon('expense', key),
  }));

  return (
    <ScrollView style={styles.container}>
      {/* Summary Cards */}
      <View style={styles.summaryRow}>
        <SummaryCard label="本月收入" amount={income} type="income" />
        <SummaryCard label="本月支出" amount={expense} type="expense" />
        <SummaryCard label="本月结余" amount={balance} type="balance" />
      </View>

      {/* Pie Chart */}
      <View style={styles.section}>
        <Text style={styles.sectionTitle}>支出分类</Text>
        <View style={styles.chartContainer}>
          <PieChart data={pieData} size={200} />
          {/* Legend */}
          <View style={styles.legend}>
            {pieData.map((d, i) => (
              <View key={i} style={styles.legendItem}>
                <View style={[styles.legendDot, { backgroundColor: d.color }]} />
                <Text style={styles.legendLabel}>{d.icon} {EXPENSE_CATEGORIES.find(c => c.key === d.label)?.label || d.label}</Text>
                <Text style={styles.legendValue}>¥{d.value.toFixed(0)}</Text>
              </View>
            ))}
          </View>
        </View>
      </View>

      {/* Nav Buttons */}
      <View style={styles.navRow}>
        <TouchableOpacity style={styles.navBtn} onPress={() => router.push('/records')}>
          <Text style={styles.navBtnText}>📋 全部账单</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.navBtn} onPress={() => router.push('/stats')}>
          <Text style={styles.navBtnText}>📊 统计分析</Text>
        </TouchableOpacity>
      </View>

      {/* FAB */}
      <TouchableOpacity style={styles.fab} onPress={() => router.push('/add')}>
        <Text style={styles.fabText}>+</Text>
      </TouchableOpacity>
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, backgroundColor: '#f0f2f5', paddingHorizontal: 16 },
  summaryRow: { flexDirection: 'row', marginTop: 16, marginBottom: 8 },
  section: { backgroundColor: '#fff', borderRadius: 12, padding: 16, marginTop: 8, elevation: 2 },
  sectionTitle: { fontSize: 16, fontWeight: '600', marginBottom: 12 },
  chartContainer: { alignItems: 'center' },
  legend: { marginTop: 12, width: '100%' },
  legendItem: { flexDirection: 'row', alignItems: 'center', marginBottom: 6 },
  legendDot: { width: 10, height: 10, borderRadius: 5, marginRight: 8 },
  legendLabel: { flex: 1, fontSize: 13, color: '#555' },
  legendValue: { fontSize: 13, color: '#333', fontWeight: '500' },
  navRow: { flexDirection: 'row', gap: 12, marginTop: 12, marginBottom: 80 },
  navBtn: { flex: 1, backgroundColor: '#fff', borderRadius: 12, padding: 16, alignItems: 'center', elevation: 2 },
  navBtnText: { fontSize: 15, color: '#333', fontWeight: '500' },
  fab: {
    position: 'absolute', bottom: 24, right: 24,
    width: 56, height: 56, borderRadius: 28,
    backgroundColor: '#2196F3', elevation: 6,
    alignItems: 'center', justifyContent: 'center',
  },
  fabText: { fontSize: 28, color: '#fff', lineHeight: 30 },
});
```

### `app/records.tsx`

```tsx
import React, { useState, useMemo } from 'react';
import { View, Text, StyleSheet, FlatList, TouchableOpacity, Alert } from 'react-native';
import { useRecords } from '../src/hooks/useRecords';
import { getMonthKey, formatDate } from '../src/utils/format';
import { getCategoryIcon, getCategoryLabel, EXPENSE_CATEGORIES, INCOME_CATEGORIES } from '../src/constants/categories';
import { Record } from '../src/types';

export default function Records() {
  const { getMonthlyRecords, getAvailableMonths, deleteRecord } = useRecords();
  const months = getAvailableMonths();
  const [selectedMonth, setSelectedMonth] = useState(months[0] || getMonthKey(new Date().toISOString().slice(0, 10)));

  const records = useMemo(() => getMonthlyRecords(selectedMonth), [getMonthlyRecords, selectedMonth]);

  const income = records.filter(r => r.type === 'income').reduce((s, r) => s + r.amount, 0);
  const expense = records.filter(r => r.type === 'expense').reduce((s, r) => s + r.amount, 0);

  const handleDelete = (id: string) => {
    Alert.alert('确认删除', '确定要删除这条记录吗？', [
      { text: '取消', style: 'cancel' },
      { text: '删除', style: 'destructive', onPress: () => deleteRecord(id) },
    ]);
  };

  const renderItem = ({ item }: { item: Record }) => (
    <View style={styles.recordItem}>
      <Text style={styles.recordIcon}>{getCategoryIcon(item.type, item.category)}</Text>
      <View style={styles.recordInfo}>
        <Text style={styles.recordCategory}>{getCategoryLabel(item.type, item.category)}</Text>
        <Text style={styles.recordDate}>{formatDate(item.date)}{item.note ? ` · ${item.note}` : ''}</Text>
      </View>
      <Text style={[styles.recordAmount, item.type === 'income' ? styles.income : styles.expense]}>
        {item.type === 'income' ? '+' : '-'}¥{item.amount.toFixed(2)}
      </Text>
      <TouchableOpacity onPress={() => handleDelete(item.id)} style={styles.deleteBtn}>
        <Text style={styles.deleteText}>删除</Text>
      </TouchableOpacity>
    </View>
  );

  const currentMonthLabel = `${selectedMonth.slice(5, 7)}月`;

  return (
    <View style={styles.container}>
      {/* Month Selector */}
      <View style={styles.monthSelector}>
        {months.length > 0 ? months.map(m => (
          <TouchableOpacity
            key={m}
            style={[styles.monthTab, m === selectedMonth && styles.monthTabActive]}
            onPress={() => setSelectedMonth(m)}
          >
            <Text style={[styles.monthTabText, m === selectedMonth && styles.monthTabTextActive]}>
              {m.slice(5, 7)}月
            </Text>
          </TouchableOpacity>
        )) : (
          <Text style={styles.emptyText}>暂无账单记录</Text>
        )}
      </View>

      {/* Summary */}
      <View style={styles.summaryRow}>
        <Text style={styles.summaryIncome}>收入 ¥{income.toFixed(2)}</Text>
        <Text style={styles.summaryExpense}>支出 ¥{expense.toFixed(2)}</Text>
        <Text style={styles.summaryBalance}>结余 ¥{(income - expense).toFixed(2)}</Text>
      </View>

      {/* List */}
      <FlatList
        data={records}
        keyExtractor={item => item.id}
        renderItem={renderItem}
        ListEmptyComponent={<Text style={styles.emptyText}>本月暂无记录</Text>}
      />
    </View>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, backgroundColor: '#f0f2f5' },
  monthSelector: { flexDirection: 'row', padding: 12, gap: 8, flexWrap: 'wrap' },
  monthTab: { paddingHorizontal: 14, paddingVertical: 6, borderRadius: 16, backgroundColor: '#fff' },
  monthTabActive: { backgroundColor: '#2196F3' },
  monthTabText: { fontSize: 13, color: '#666' },
  monthTabTextActive: { color: '#fff', fontWeight: '600' },
  summaryRow: { flexDirection: 'row', paddingHorizontal: 16, paddingBottom: 8, gap: 12 },
  summaryIncome: { fontSize: 13, color: '#4CAF50', fontWeight: '600' },
  summaryExpense: { fontSize: 13, color: '#F44336', fontWeight: '600' },
  summaryBalance: { fontSize: 13, color: '#2196F3', fontWeight: '600' },
  recordItem: {
    flexDirection: 'row', alignItems: 'center',
    backgroundColor: '#fff', marginHorizontal: 16, marginVertical: 3,
    borderRadius: 10, padding: 14, elevation: 1,
  },
  recordIcon: { fontSize: 28, marginRight: 12 },
  recordInfo: { flex: 1 },
  recordCategory: { fontSize: 15, fontWeight: '500', color: '#333' },
  recordDate: { fontSize: 12, color: '#999', marginTop: 2 },
  recordAmount: { fontSize: 16, fontWeight: '600', marginRight: 8 },
  income: { color: '#4CAF50' },
  expense: { color: '#F44336' },
  deleteBtn: { padding: 4 },
  deleteText: { fontSize: 12, color: '#ccc' },
  emptyText: { textAlign: 'center', color: '#999', marginTop: 40, fontSize: 14 },
});
```

### `app/stats.tsx`

```tsx
import React, { useMemo } from 'react';
import { View, Text, StyleSheet, ScrollView } from 'react-native';
import BarChart from '../src/components/BarChart';
import { useRecords } from '../src/hooks/useRecords';
import { getCategoryLabel, getCategoryIcon, EXPENSE_CATEGORIES } from '../src/constants/categories';

export default function Stats() {
  const { getMonthlyTotal, getCategoryBreakdown, getAvailableMonths } = useRecords();
  const months = useMemo(() => {
    const m = getAvailableMonths();
    return m.length > 0 ? m : [new Date().toISOString().slice(0, 7)];
  }, [getAvailableMonths]);

  const barData = useMemo(() => {
    return months.slice().reverse().slice(-6).map(m => {
      const income = getMonthlyTotal(m, 'income');
      const expense = getMonthlyTotal(m, 'expense');
      return { label: `${parseInt(m.slice(5, 7))}月`, value: expense };
    });
  }, [months, getMonthlyTotal]);

  const allTimeExpenseBreakdown = useMemo(() => {
    const breakdown: Record<string, number> = {};
    months.forEach(m => {
      const monthBreakdown = getCategoryBreakdown(m, 'expense');
      Object.entries(monthBreakdown).forEach(([k, v]) => {
        breakdown[k] = (breakdown[k] || 0) + v;
      });
    });
    const sorted = Object.entries(breakdown).sort((a, b) => b[1] - a[1]);
    const total = sorted.reduce((sum, [, v]) => sum + v, 0);
    return sorted.map(([key, value]) => ({ key, value, percent: total > 0 ? (value / total * 100).toFixed(1) : '0' }));
  }, [months, getCategoryBreakdown]);

  const totalExpense = allTimeExpenseBreakdown.reduce((s, i) => s + i.value, 0);

  return (
    <ScrollView style={styles.container}>
      {/* Monthly Trend */}
      <View style={styles.section}>
        <Text style={styles.sectionTitle}>月度支出趋势</Text>
        <BarChart data={barData} width={340} height={200} color="#FF6384" />
      </View>

      {/* Category Ranking */}
      <View style={styles.section}>
        <Text style={styles.sectionTitle}>累计支出排行</Text>
        {allTimeExpenseBreakdown.length === 0 ? (
          <Text style={styles.emptyText}>暂无数据</Text>
        ) : (
          allTimeExpenseBreakdown.map((item, i) => {
            const barWidth = totalExpense > 0 ? (item.value / allTimeExpenseBreakdown[0].value) * 100 : 0;
            return (
              <View key={item.key} style={styles.rankItem}>
                <Text style={styles.rankNum}>{i + 1}</Text>
                <Text style={styles.rankIcon}>{getCategoryIcon('expense', item.key)}</Text>
                <Text style={styles.rankLabel}>{getCategoryLabel('expense', item.key)}</Text>
                <View style={styles.rankBarBg}>
                  <View style={[styles.rankBar, { width: `${barWidth}%` }]} />
                </View>
                <Text style={styles.rankValue}>¥{item.value.toFixed(0)}</Text>
                <Text style={styles.rankPercent}>{item.percent}%</Text>
              </View>
            );
          })
        )}
      </View>
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, backgroundColor: '#f0f2f5', padding: 16 },
  section: { backgroundColor: '#fff', borderRadius: 12, padding: 16, marginBottom: 12, elevation: 2 },
  sectionTitle: { fontSize: 16, fontWeight: '600', marginBottom: 12 },
  emptyText: { textAlign: 'center', color: '#999', marginTop: 20, fontSize: 14 },
  rankItem: { flexDirection: 'row', alignItems: 'center', marginBottom: 10 },
  rankNum: { width: 22, fontSize: 14, fontWeight: '700', color: '#999' },
  rankIcon: { fontSize: 18, marginRight: 8 },
  rankLabel: { width: 50, fontSize: 13, color: '#555' },
  rankBarBg: { flex: 1, height: 8, backgroundColor: '#f0f0f0', borderRadius: 4, marginHorizontal: 8, overflow: 'hidden' },
  rankBar: { height: 8, backgroundColor: '#FF6384', borderRadius: 4 },
  rankValue: { width: 60, fontSize: 13, color: '#333', textAlign: 'right' },
  rankPercent: { width: 44, fontSize: 12, color: '#999', textAlign: 'right' },
});
```

### `app/add.tsx`

```tsx
import React, { useState } from 'react';
import { View, Text, TextInput, TouchableOpacity, StyleSheet, ScrollView, Platform } from 'react-native';
import { router } from 'expo-router';
import { useRecords } from '../src/hooks/useRecords';
import CategoryPicker from '../src/components/CategoryPicker';
import { EXPENSE_CATEGORIES, INCOME_CATEGORIES } from '../src/constants/categories';
import { getToday } from '../src/utils/format';
import { Record } from '../src/types';

export default function AddRecord() {
  const { addRecord } = useRecords();
  const [type, setType] = useState<'income' | 'expense'>('expense');
  const [amount, setAmount] = useState('');
  const [category, setCategory] = useState('food');
  const [date, setDate] = useState(getToday());
  const [note, setNote] = useState('');

  const categories = type === 'income' ? INCOME_CATEGORIES : EXPENSE_CATEGORIES;

  const handleSave = () => {
    const numAmount = parseFloat(amount);
    if (!numAmount || numAmount <= 0) return;

    const record: Record = {
      id: Date.now().toString(),
      type,
      amount: numAmount,
      category,
      date,
      note,
    };

    addRecord(record);
    router.back();
  };

  const adjustDate = (days: number) => {
    const d = new Date(date);
    d.setDate(d.getDate() + days);
    setDate(d.toISOString().slice(0, 10));
  };

  return (
    <ScrollView style={styles.container} keyboardShouldPersistTaps="handled">
      {/* Type Toggle */}
      <View style={styles.typeRow}>
        <TouchableOpacity
          style={[styles.typeBtn, type === 'expense' && styles.typeBtnExpense]}
          onPress={() => { setType('expense'); setCategory('food'); }}
        >
          <Text style={[styles.typeBtnText, type === 'expense' && styles.typeBtnTextActive]}>支出</Text>
        </TouchableOpacity>
        <TouchableOpacity
          style={[styles.typeBtn, type === 'income' && styles.typeBtnIncome]}
          onPress={() => { setType('income'); setCategory('salary'); }}
        >
          <Text style={[styles.typeBtnText, type === 'income' && styles.typeBtnTextActive]}>收入</Text>
        </TouchableOpacity>
      </View>

      {/* Amount */}
      <View style={styles.amountRow}>
        <Text style={styles.currency}>¥</Text>
        <TextInput
          style={styles.amountInput}
          value={amount}
          onChangeText={setAmount}
          placeholder="0.00"
          placeholderTextColor="#ccc"
          keyboardType="decimal-pad"
          autoFocus
        />
      </View>

      {/* Category */}
      <Text style={styles.label}>分类</Text>
      <CategoryPicker categories={categories} selected={category} onSelect={setCategory} />

      {/* Date */}
      <Text style={styles.label}>日期</Text>
      <View style={styles.dateRow}>
        <TouchableOpacity onPress={() => adjustDate(-1)}>
          <Text style={styles.dateArrow}>◀</Text>
        </TouchableOpacity>
        <Text style={styles.dateText}>{date}</Text>
        <TouchableOpacity onPress={() => adjustDate(1)}>
          <Text style={styles.dateArrow}>▶</Text>
        </TouchableOpacity>
      </View>

      {/* Note */}
      <Text style={styles.label}>备注</Text>
      <TextInput
        style={styles.noteInput}
        value={note}
        onChangeText={setNote}
        placeholder="添加备注..."
        placeholderTextColor="#ccc"
      />

      {/* Save */}
      <TouchableOpacity
        style={[styles.saveBtn, (!amount || parseFloat(amount) <= 0) && styles.saveBtnDisabled]}
        onPress={handleSave}
        disabled={!amount || parseFloat(amount) <= 0}
      >
        <Text style={styles.saveBtnText}>✓ 保存</Text>
      </TouchableOpacity>
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, backgroundColor: '#f0f2f5', padding: 16 },
  typeRow: { flexDirection: 'row', gap: 12, marginBottom: 20 },
  typeBtn: { flex: 1, paddingVertical: 10, borderRadius: 10, backgroundColor: '#fff', alignItems: 'center' },
  typeBtnExpense: { backgroundColor: '#FFEBEE', borderWidth: 2, borderColor: '#F44336' },
  typeBtnIncome: { backgroundColor: '#E8F5E9', borderWidth: 2, borderColor: '#4CAF50' },
  typeBtnText: { fontSize: 16, color: '#666', fontWeight: '500' },
  typeBtnTextActive: { color: '#333', fontWeight: '700' },
  amountRow: { flexDirection: 'row', alignItems: 'baseline', justifyContent: 'center', marginBottom: 20 },
  currency: { fontSize: 28, color: '#333', fontWeight: '300', marginRight: 4 },
  amountInput: {
    fontSize: 40, fontWeight: '700', color: '#333',
    minWidth: 120, textAlign: 'center',
    borderBottomWidth: 2, borderBottomColor: '#ddd', paddingBottom: 4,
  },
  label: { fontSize: 14, color: '#888', marginBottom: 8, marginTop: 8 },
  dateRow: { flexDirection: 'row', alignItems: 'center', justifyContent: 'center', gap: 20, marginBottom: 16 },
  dateArrow: { fontSize: 18, color: '#2196F3', padding: 8 },
  dateText: { fontSize: 16, color: '#333', fontWeight: '500' },
  noteInput: {
    backgroundColor: '#fff', borderRadius: 10, padding: 12,
    fontSize: 15, color: '#333', marginBottom: 24,
  },
  saveBtn: { backgroundColor: '#2196F3', borderRadius: 12, padding: 16, alignItems: 'center' },
  saveBtnDisabled: { backgroundColor: '#ccc' },
  saveBtnText: { fontSize: 17, color: '#fff', fontWeight: '600' },
});
```

- [ ] **Step 1: Create all five page files**

- [ ] **Step 2: Commit**

---

## Task 5: Configuration Files

**Files:**
- Modify: `projects/rn/test_07_08/metro.config.js`
- Modify: `projects/rn/test_07_08/app.json`
- Create: `projects/rn/test_07_08/.npmrc`

### `metro.config.js`

Replace with:

```js
const { getDefaultConfig } = require('expo/metro-config');

const config = getDefaultConfig(__dirname);

config.watchFolders = [__dirname];

module.exports = config;
```

### `app.json`

Replace with:

```json
{
  "expo": {
    "name": "记账 · Expense Tracker",
    "slug": "expense-tracker",
    "version": "1.0.0",
    "orientation": "portrait",
    "scheme": "expense-tracker",
    "userInterfaceStyle": "light",
    "newArchEnabled": true,
    "ios": { "supportsTablet": false },
    "android": {
      "package": "com.example.expensetracker"
    },
    "plugins": ["expo-router"]
  }
}
```

### `.npmrc`

```text
shamefully-hoist=true
strict-peer-dependencies=false
```

- [ ] **Step 1: Update/create all three config files**

- [ ] **Step 2: Commit**

---

## Task 6: Clean up scaffolding defaults

**Files:**
- Delete: `projects/rn/test_07_08/App.tsx` (not needed with expo-router)
- Remove initial content in `app/index.tsx` if any (already handled in Task 4)

- [ ] **Step 1: Remove App.tsx or convert it**

- [ ] **Step 2: Commit**

---

## Task 7: Verify

- [ ] **Step 1: Install deps again to make sure**

```bash
cd projects/rn/test_07_08
pnpm install
```

- [ ] **Step 2: Check TypeScript**

```bash
cd projects/rn/test_07_08
npx tsc --noEmit 2>&1 | head -20
```

- [ ] **Step 3: Expo doctor check**

```bash
cd projects/rn/test_07_08
npx expo-doctor
```

- [ ] **Step 4: Try export (build check)**

```bash
cd projects/rn/test_07_08
npx expo export --dump-sourcemap
```
