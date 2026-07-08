import React, { useState } from 'react';
import { View, Text, TextInput, TouchableOpacity, StyleSheet, ScrollView } from 'react-native';
import { router } from 'expo-router';
import { useRecords } from '../src/hooks/useRecords';
import CategoryPicker from '../src/components/CategoryPicker';
import { EXPENSE_CATEGORIES, INCOME_CATEGORIES } from '../src/constants/categories';
import { getToday } from '../src/utils/format';
import { ExpenseRecord } from '../src/types';

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

    const record: ExpenseRecord = {
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

      <Text style={styles.label}>分类</Text>
      <CategoryPicker categories={categories} selected={category} onSelect={setCategory} />

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

      <Text style={styles.label}>备注</Text>
      <TextInput
        style={styles.noteInput}
        value={note}
        onChangeText={setNote}
        placeholder="添加备注..."
        placeholderTextColor="#ccc"
      />

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
