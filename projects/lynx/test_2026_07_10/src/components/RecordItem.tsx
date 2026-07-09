// src/components/RecordItem.tsx
import { useCallback } from '@lynx-js/react';
import { useAppContext } from '../store/AppContext.js';
import type { Category, Record } from '../store/types.js';
import { formatSignedAmount } from '../utils/format.js';
import { CategoryIcon } from './CategoryIcon.js';

interface RecordItemProps {
  record: Record;
  category: Category | undefined;
}

export function RecordItem({ record, category }: RecordItemProps) {
  const { dispatch } = useAppContext();

  const onDelete = useCallback(() => {
    'background only';
    dispatch({ type: 'DELETE_RECORD', payload: record.id });
  }, [dispatch, record.id]);

  const isExpense = record.type === 'expense';

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
  );
}
