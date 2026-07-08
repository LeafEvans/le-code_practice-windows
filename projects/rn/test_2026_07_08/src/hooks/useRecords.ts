import { useState, useEffect, useCallback } from "react";
import AsyncStorage from "@react-native-async-storage/async-storage";
import { ExpenseRecord } from "../types";

const STORAGE_KEY = "@expense_records";

export function useRecords() {
  const [records, setRecords] = useState<ExpenseRecord[]>([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    loadRecords();
  }, []);

  const loadRecords = async () => {
    try {
      const data = await AsyncStorage.getItem(STORAGE_KEY);
      setRecords(data ? JSON.parse(data) : []);
    } catch (e) {
      console.error("Failed to load records:", e);
    } finally {
      setLoading(false);
    }
  };

  const saveRecords = async (newRecords: ExpenseRecord[]) => {
    await AsyncStorage.setItem(STORAGE_KEY, JSON.stringify(newRecords));
    setRecords(newRecords);
  };

  const addRecord = useCallback(
    async (record: ExpenseRecord) => {
      const newRecords = [record, ...records];
      await saveRecords(newRecords);
    },
    [records],
  );

  const deleteRecord = useCallback(
    async (id: string) => {
      const newRecords = records.filter((r) => r.id !== id);
      await saveRecords(newRecords);
    },
    [records],
  );

  const getMonthlyTotal = useCallback(
    (monthKey: string, type: "income" | "expense") => {
      return records
        .filter((r) => r.type === type && r.date.startsWith(monthKey))
        .reduce((sum, r) => sum + r.amount, 0);
    },
    [records],
  );

  const getMonthlyRecords = useCallback(
    (monthKey: string) => {
      return records
        .filter((r) => r.date.startsWith(monthKey))
        .sort((a, b) => b.date.localeCompare(a.date));
    },
    [records],
  );

  const getCategoryBreakdown = useCallback(
    (monthKey: string, type: "income" | "expense") => {
      const breakdown: { [key: string]: number } = {};
      records
        .filter((r) => r.type === type && r.date.startsWith(monthKey))
        .forEach((r) => {
          breakdown[r.category] = (breakdown[r.category] || 0) + r.amount;
        });
      return breakdown;
    },
    [records],
  );

  const getAvailableMonths = useCallback(() => {
    const months = new Set(records.map((r) => r.date.slice(0, 7)));
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
