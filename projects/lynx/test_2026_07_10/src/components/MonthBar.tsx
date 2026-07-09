// src/components/MonthBar.tsx
import type { Category } from '../store/types.js';
import { formatAmount } from '../utils/format.js';
import { findCategory } from '../utils/stats.js';
import { CategoryIcon } from './CategoryIcon.js';

interface BarItem {
  categoryId: string;
  amount: number; // cents
  percentage: number; // 0-100
}

interface MonthBarProps {
  items: BarItem[];
  total: number; // cents
  categories: Category[];
}

export function MonthBar({ items, total: _total, categories }: MonthBarProps) {
  if (items.length === 0) {
    return (
      <view
        style={{
          display: 'flex',
          justifyContent: 'center',
          alignItems: 'center',
          padding: '40px 0',
        }}
      >
        <text style={{ fontSize: '14px', color: '#999' }}>暂无支出数据</text>
      </view>
    );
  }

  // Sort by amount descending
  const sorted = [...items].sort((a, b) => b.amount - a.amount);

  return (
    <view style={{ padding: '0 16px' }}>
      {sorted.slice(0, 8).map((item) => {
        const category = findCategory(categories, item.categoryId);
        if (!category) return null;

        return (
          <view
            key={item.categoryId}
            style={{
              display: 'flex',
              flexDirection: 'row',
              alignItems: 'center',
              marginBottom: '10px',
            }}
          >
            <CategoryIcon category={category} size={14} />

            <text
              style={{
                fontSize: '14px',
                color: '#666',
                marginLeft: '8px',
                width: '40px',
              }}
            >
              {category.name}
            </text>

            {/* Percentage bar */}
            <view style={{ flex: 1, marginLeft: '8px', marginRight: '8px' }}>
              <view
                style={{
                  height: '8px',
                  borderRadius: '4px',
                  backgroundColor: '#f0f0f0',
                  position: 'relative',
                }}
              >
                <view
                  style={{
                    height: '8px',
                    borderRadius: '4px',
                    backgroundColor: category.color,
                    width: `${Math.max(item.percentage, 2)}%`,
                  }}
                />
              </view>
            </view>

            <text
              style={{
                fontSize: '12px',
                color: '#999',
                width: '50px',
                textAlign: 'right',
              }}
            >
              {item.percentage.toFixed(0)}%
            </text>
            <text style={{ fontSize: '12px', color: '#999', width: '60px' }}>
              ¥{formatAmount(item.amount)}
            </text>
          </view>
        );
      })}
    </view>
  );
}
