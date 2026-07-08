import React from 'react';
import { View, Text, StyleSheet, ScrollView, TouchableOpacity } from 'react-native';
import { router } from 'expo-router';
import SummaryCard from '../src/components/SummaryCard';
import PieChart from '../src/components/PieChart';
import { useRecords } from '../src/hooks/useRecords';
import { getCurrentMonth } from '../src/utils/format';
import { EXPENSE_CATEGORIES, getCategoryIcon } from '../src/constants/categories';

const CHART_COLORS = ['#FF6384', '#36A2EB', '#FFCE56', '#4BC0C0', '#9966FF', '#FF9F40', '#C9CBCF', '#7BC67E'];

export default function Dashboard() {
  const { getMonthlyTotal, getCategoryBreakdown } = useRecords();
  const month = getCurrentMonth();

  const income = getMonthlyTotal(month, 'income');
  const expense = getMonthlyTotal(month, 'expense');
  const balance = income - expense;

  const expenseBreakdown = getCategoryBreakdown(month, 'expense');
  const pieData = Object.entries(expenseBreakdown).map(([key, value], i) => ({
    label: key,
    value: value as number,
    color: CHART_COLORS[i % CHART_COLORS.length],
    icon: getCategoryIcon('expense', key),
  } as { label: string; value: number; color: string; icon: string }));

  return (
    <View style={{ flex: 1 }}>
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
            <View style={styles.legend}>
              {pieData.map((d, i) => (
                <View key={i} style={styles.legendItem}>
                  <View style={[styles.legendDot, { backgroundColor: d.color }]} />
                  <Text style={styles.legendLabel}>
                    {d.icon} {EXPENSE_CATEGORIES.find(c => c.key === d.label)?.label || d.label}
                  </Text>
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
      </ScrollView>

      {/* FAB */}
      <TouchableOpacity style={styles.fab} onPress={() => router.push('/add')}>
        <Text style={styles.fabText}>+</Text>
      </TouchableOpacity>
    </View>
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
