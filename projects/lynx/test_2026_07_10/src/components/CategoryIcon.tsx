// src/components/CategoryIcon.tsx

import type { Category } from '../store/types.js';
import { Icon, type IconName } from './Icon.js';

interface CategoryIconProps {
  category: Category;
  size?: number;
}

const BG_COLORS: Record<string, string> = {
  '#FF6B6B': '#FF6B6B20',
  '#4ECDC4': '#4ECDC420',
  '#FFD93D': '#FFD93D20',
  '#6C5CE7': '#6C5CE720',
  '#A29BFE': '#A29BFE20',
  '#FD79A8': '#FD79A820',
  '#00B894': '#00B89420',
  '#E17055': '#E1705520',
  '#0984E3': '#0984E320',
  '#E84393': '#E8439320',
  '#FDCB6E': '#FDCB6E20',
};

export function CategoryIcon({ category, size = 20 }: CategoryIconProps) {
  const bgColor = BG_COLORS[category.color] ?? `${category.color}20`;

  return (
    <view
      style={{
        width: `${size + 12}px`,
        height: `${size + 12}px`,
        borderRadius: `${(size + 12) / 2}px`,
        backgroundColor: bgColor,
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
      }}
    >
      <Icon
        name={category.icon as IconName}
        size={size}
        color={category.color}
      />
    </view>
  );
}
