// src/pages/StatsPage.tsx
import { useCallback, useMemo, useState } from "@lynx-js/react";
import { Icon } from "../components/Icon.js";
import { MonthBar } from "../components/MonthBar.js";
import { useAppContext } from "../store/AppContext.js";
import { formatAmount } from "../utils/format.js";
import {
  computeMonthlyStats,
  filterRecordsByMonth,
  getYearMonth,
  shiftMonth,
} from "../utils/stats.js";

export function StatsPage() {
  const { state } = useAppContext();
  const [date, setDate] = useState(() => new Date());

  const { year, month } = getYearMonth(date);

  const onPrevMonth = useCallback(() => {
    "background only";
    const shifted = shiftMonth(year, month, -1);
    setDate(new Date(shifted.year, shifted.month - 1));
  }, [year, month]);

  const onNextMonth = useCallback(() => {
    "background only";
    const shifted = shiftMonth(year, month, 1);
    setDate(new Date(shifted.year, shifted.month - 1));
  }, [year, month]);

  const monthlyRecords = useMemo(
    () => filterRecordsByMonth(state.records, year, month),
    [state.records, year, month],
  );

  const stats = useMemo(
    () => computeMonthlyStats(monthlyRecords),
    [monthlyRecords],
  );

  const barItems = useMemo(() => {
    const total = stats.totalExpense;
    if (total === 0) return [];

    return Array.from(stats.expenseByCategory.entries()).map(
      ([categoryId, amount]) => ({
        categoryId,
        amount,
        percentage: (amount / total) * 100,
      }),
    );
  }, [stats]);

  return (
    <view style={{ flex: 1, backgroundColor: "#fafafa" }}>
      {/* Month header */}
      <view
        style={{
          display: "flex",
          flexDirection: "row",
          justifyContent: "space-between",
          alignItems: "center",
          padding: "16px",
          backgroundColor: "#fff",
        }}
      >
        <view bindtap={onPrevMonth} style={{ padding: "4px" }}>
          <Icon name="chevron-left" size={20} color="#666" />
        </view>
        <text style={{ fontSize: "18px", fontWeight: "700", color: "#1a1a1a" }}>
          {month}月统计
        </text>
        <view bindtap={onNextMonth} style={{ padding: "4px" }}>
          <Icon name="chevron-right" size={20} color="#666" />
        </view>
      </view>

      {/* Summary cards */}
      <view
        style={{
          display: "flex",
          flexDirection: "row",
          padding: "16px",
          backgroundColor: "#fff",
        }}
      >
        <view
          style={{
            flex: 1,
            marginRight: "8px",
            padding: "16px",
            borderRadius: "12px",
            backgroundColor: "#f0fdf4",
          }}
        >
          <text style={{ fontSize: "12px", color: "#00B894" }}>总收入</text>
          <text
            style={{ fontSize: "20px", fontWeight: "700", color: "#00B894" }}
          >
            ¥{formatAmount(stats.totalIncome)}
          </text>
        </view>
        <view
          style={{
            flex: 1,
            marginLeft: "8px",
            marginRight: "8px",
            padding: "16px",
            borderRadius: "12px",
            backgroundColor: "#fff5f5",
          }}
        >
          <text style={{ fontSize: "12px", color: "#FF6B6B" }}>总支出</text>
          <text
            style={{ fontSize: "20px", fontWeight: "700", color: "#FF6B6B" }}
          >
            ¥{formatAmount(stats.totalExpense)}
          </text>
        </view>
        <view
          style={{
            flex: 1,
            marginLeft: "8px",
            padding: "16px",
            borderRadius: "12px",
            backgroundColor: "#f0f9ff",
          }}
        >
          <text style={{ fontSize: "12px", color: "#0984E3" }}>结余</text>
          <text
            style={{
              fontSize: "20px",
              fontWeight: "700",
              color: stats.balance >= 0 ? "#0984E3" : "#FF6B6B",
            }}
          >
            ¥{formatAmount(Math.abs(stats.balance))}
          </text>
        </view>
      </view>

      {/* Expense breakdown */}
      <view
        style={{ padding: "16px", backgroundColor: "#fff", marginTop: "8px" }}
      >
        <text
          style={{
            fontSize: "16px",
            fontWeight: "600",
            color: "#1a1a1a",
            marginBottom: "16px",
          }}
        >
          支出分类
        </text>
        <MonthBar
          items={barItems}
          total={stats.totalExpense}
          categories={state.categories}
        />
      </view>
    </view>
  );
}
