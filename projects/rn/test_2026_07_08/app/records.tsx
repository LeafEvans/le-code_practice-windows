import React, { useState, useMemo } from 'react';
import { View, Text, StyleSheet, FlatList, TouchableOpacity, Alert } from 'react-native';
import { useRecords } from '../src/hooks/useRecords';
import { getMonthKey, formatDate } from '../src/utils/format';
import { getCategoryIcon, getCategoryLabel } from '../src/constants/categories';
import { ExpenseRecord } from '../src/types';

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

  const renderItem = ({ item }: { item: ExpenseRecord }) => (
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

  return (
    <View style={styles.container}>
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

      <View style={styles.summaryRow}>
        <Text style={styles.summaryIncome}>收入 ¥{income.toFixed(2)}</Text>
        <Text style={styles.summaryExpense}>支出 ¥{expense.toFixed(2)}</Text>
        <Text style={styles.summaryBalance}>结余 ¥{(income - expense).toFixed(2)}</Text>
      </View>

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
