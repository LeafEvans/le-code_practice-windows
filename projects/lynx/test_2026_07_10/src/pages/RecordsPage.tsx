// src/pages/RecordsPage.tsx
import { useCallback, useMemo, useState } from '@lynx-js/react';
import { AddRecordModal } from '../components/AddRecordModal.js';
import { Icon } from '../components/Icon.js';
import { RecordItem } from '../components/RecordItem.js';
import { useAppContext } from '../store/AppContext.js';
import { formatAmount } from '../utils/format.js';
import {
  filterRecordsByMonth,
  findCategory,
  getYearMonth,
  shiftMonth,
} from '../utils/stats.js';

export function RecordsPage() {
  const { state } = useAppContext();
  const [date, setDate] = useState(() => new Date());
  const [modalVisible, setModalVisible] = useState(false);

  const { year, month } = getYearMonth(date);

  const monthlyRecords = useMemo(
    () => filterRecordsByMonth(state.records, year, month),
    [state.records, year, month],
  );

  const summary = useMemo(() => {
    let income = 0;
    let expense = 0;
    for (const r of monthlyRecords) {
      if (r.type === 'income') income += r.amount;
      else expense += r.amount;
    }
    return { income, expense };
  }, [monthlyRecords]);

  const onPrevMonth = useCallback(() => {
    'background only';
    const shifted = shiftMonth(year, month, -1);
    setDate(new Date(shifted.year, shifted.month - 1));
  }, [year, month]);

  const onNextMonth = useCallback(() => {
    'background only';
    const shifted = shiftMonth(year, month, 1);
    setDate(new Date(shifted.year, shifted.month - 1));
  }, [year, month]);

  // Group by date
  const grouped = useMemo(() => {
    const map = new Map<string, typeof monthlyRecords>();
    for (const r of monthlyRecords) {
      const list = map.get(r.date) ?? [];
      list.push(r);
      map.set(r.date, list);
    }
    // Sort dates descending
    return Array.from(map.entries()).sort((a, b) => b[0].localeCompare(a[0]));
  }, [monthlyRecords]);

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
          <text
            style={{ fontSize: '16px', color: '#00B894', fontWeight: '600' }}
          >
            ¥{formatAmount(summary.income)}
          </text>
        </view>
        <view style={{ flex: 1 }}>
          <text style={{ fontSize: '12px', color: '#999' }}>支出</text>
          <text
            style={{ fontSize: '16px', color: '#FF6B6B', fontWeight: '600' }}
          >
            ¥{formatAmount(summary.expense)}
          </text>
        </view>
      </view>

      {/* Record list */}
      <scroll-view scroll-y={true} style={{ flex: 1 }}>
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
                <text
                  style={{ fontSize: '13px', color: '#999', fontWeight: '500' }}
                >
                  {dateStr.slice(5)} {getDayLabel(dateStr)}
                </text>
              </view>
              {/* Records */}
              <view style={{ backgroundColor: '#fff' }}>
                {records.map((record: (typeof monthlyRecords)[number]) => (
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
        bindtap={() => {
          setModalVisible(true);
        }}
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
        onClose={() => {
          setModalVisible(false);
        }}
      />
    </view>
  );
}

function getDayLabel(dateStr: string): string {
  const days = ['日', '一', '二', '三', '四', '五', '六'];
  const d = new Date(dateStr);
  return `周${days[d.getDay()] ?? '日'}`;
}
