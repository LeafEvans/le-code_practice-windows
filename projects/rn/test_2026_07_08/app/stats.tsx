import React, { useMemo } from 'react';
import { View, Text, StyleSheet, ScrollView } from 'react-native';
import BarChart from '../src/components/BarChart';
import { useRecords } from '../src/hooks/useRecords';
import { getCategoryLabel, getCategoryIcon } from '../src/constants/categories';

export default function Stats() {
  const { getMonthlyTotal, getCategoryBreakdown, getAvailableMonths } = useRecords();
  const months = useMemo(() => {
    const m = getAvailableMonths();
    return m.length > 0 ? m : [new Date().toISOString().slice(0, 7)];
  }, [getAvailableMonths]);

  const barData = useMemo(() => {
    return months.slice().reverse().slice(-6).map(m => {
      const expense = getMonthlyTotal(m, 'expense');
      return { label: `${parseInt(m.slice(5, 7))}月`, value: expense };
    });
  }, [months, getMonthlyTotal]);

  const allTimeExpenseBreakdown = useMemo(() => {
    const breakdown: { [key: string]: number } = {};
    months.forEach(m => {
      const monthBreakdown = getCategoryBreakdown(m, 'expense');
      Object.entries(monthBreakdown).forEach(([k, v]) => {
        breakdown[k] = (breakdown[k] || 0) + (v as number);
      });
    });
    const sorted = Object.entries(breakdown).sort((a, b) => b[1] - a[1]);
    const total = sorted.reduce((sum, [, v]) => sum + v, 0);
    return sorted.map(([key, value]) => ({ key, value, percent: total > 0 ? (value / total * 100).toFixed(1) : '0' }));
  }, [months, getCategoryBreakdown]);

  const totalExpense = allTimeExpenseBreakdown.reduce((s, i) => s + i.value, 0);

  return (
    <ScrollView style={styles.container}>
      <View style={styles.section}>
        <Text style={styles.sectionTitle}>月度支出趋势</Text>
        <BarChart data={barData} width={340} height={200} color="#FF6384" />
      </View>

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
