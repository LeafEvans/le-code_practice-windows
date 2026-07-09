import { useCallback } from '@lynx-js/react'
import type { BookRecord } from '../types.js'

interface Props {
  records: BookRecord[]
  onDelete?: (id: string) => void
}

export function RecordsPage({ records, onDelete }: Props) {
  const sorted = [...records].sort((a, b) => b.date.localeCompare(a.date) || b.id.localeCompare(a.id))

  const thisMonth = new Date().toISOString().slice(0, 7)
  const monthRecords = records.filter((r) => r.date.startsWith(thisMonth))
  const monthIncome = monthRecords
    .filter((r) => r.type === 'income')
    .reduce((s, r) => s + r.amount, 0)
  const monthExpense = monthRecords
    .filter((r) => r.type === 'expense')
    .reduce((s, r) => s + r.amount, 0)

  return (
    <view style={containerStyle}>
      {/* 本月汇总 */}
      <view style={summaryStyle}>
        <text style={summaryTitleStyle}>本月</text>
        <view style={summaryRowStyle}>
          <view style={summaryItemStyle}>
            <text style={summaryLabelStyle}>收入</text>
            <text style={{ ...summaryAmountStyle, color: '#10B981' }}>
              ¥{monthIncome.toFixed(2)}
            </text>
          </view>
          <view style={summaryItemStyle}>
            <text style={summaryLabelStyle}>支出</text>
            <text style={{ ...summaryAmountStyle, color: '#F97316' }}>
              ¥{monthExpense.toFixed(2)}
            </text>
          </view>
          <view style={summaryItemStyle}>
            <text style={summaryLabelStyle}>结余</text>
            <text
              style={{
                ...summaryAmountStyle,
                color: monthIncome - monthExpense >= 0 ? '#6366F1' : '#EF4444',
              }}
            >
              ¥{(monthIncome - monthExpense).toFixed(2)}
            </text>
          </view>
        </view>
      </view>

      {/* 记录列表 */}
      <scroll-view
        scroll-y
        style={listStyle}
      >
        {sorted.length === 0 ? (
          <view style={emptyStyle}>
            <text style={emptyTextStyle}>还没有记录，快去记一笔吧</text>
          </view>
        ) : (
          sorted.map((record) => (
            <RecordItem key={record.id} record={record} onDelete={onDelete} />
          ))
        )}
      </scroll-view>
    </view>
  )
}

function RecordItem({
  record,
  onDelete,
}: {
  record: BookRecord
  onDelete?: (id: string) => void
}) {
  const isIncome = record.type === 'income'
  const color = isIncome ? '#10B981' : '#F97316'

  const handleDelete = useCallback(() => {
    'background only'
    onDelete?.(record.id)
  }, [record.id, onDelete])

  return (
    <view style={recordStyle}>
      <view style={{ ...dotStyle, backgroundColor: color }} />
      <view style={recordInfoStyle}>
        <text style={recordCategoryStyle}>{record.category}</text>
        {record.note ? (
          <text style={recordNoteStyle} text-maxline="1">
            {record.note}
          </text>
        ) : null}
      </view>
      <view style={recordRightStyle}>
        <text style={{ ...recordAmountStyle, color }}>
          {isIncome ? '+' : '-'}¥{record.amount.toFixed(2)}
        </text>
        <text style={recordDateStyle}>{record.date}</text>
      </view>
      {onDelete ? (
        <view style={deleteBtnStyle} bindtap={handleDelete}>
          <text style={deleteBtnTextStyle}>×</text>
        </view>
      ) : null}
    </view>
  )
}

const containerStyle = {
  flex: 1,
  width: '100%',
  display: 'flex' as const,
  flexDirection: 'column' as const,
  backgroundColor: '#F8FAFC',
}

const summaryStyle = {
  backgroundColor: '#FFFFFF',
  padding: '16px',
  marginLeft: '12px',
  marginRight: '12px',
  marginTop: '12px',
  borderRadius: '12px',
}

const summaryTitleStyle = {
  fontSize: '14px',
  fontWeight: '600' as const,
  color: '#64748B',
  marginBottom: '12px',
}

const summaryRowStyle = {
  display: 'flex' as const,
  flexDirection: 'row' as const,
}

const summaryItemStyle = {
  flex: 1,
  display: 'flex' as const,
  flexDirection: 'column' as const,
  alignItems: 'center' as const,
}

const summaryLabelStyle = {
  fontSize: '12px',
  color: '#94A3B8',
  marginBottom: '4px',
}

const summaryAmountStyle = {
  fontSize: '18px',
  fontWeight: '700' as const,
}

const listStyle = {
  flex: 1,
  width: '100%',
  marginTop: '12px',
  paddingLeft: '12px',
  paddingRight: '12px',
}

const emptyStyle = {
  display: 'flex' as const,
  alignItems: 'center' as const,
  justifyContent: 'center' as const,
  paddingTop: '60px',
  paddingBottom: '60px',
}

const emptyTextStyle = {
  fontSize: '14px',
  color: '#94A3B8',
}

const recordStyle = {
  width: '100%',
  display: 'flex' as const,
  flexDirection: 'row' as const,
  alignItems: 'center' as const,
  backgroundColor: '#FFFFFF',
  borderRadius: '10px',
  padding: '12px',
  marginBottom: '8px',
}

const dotStyle = {
  width: '8px',
  height: '8px',
  borderRadius: '4px',
  marginRight: '10px',
}

const recordInfoStyle = {
  flex: 1,
}

const recordCategoryStyle = {
  fontSize: '15px',
  fontWeight: '600' as const,
  color: '#1E293B',
}

const recordNoteStyle = {
  fontSize: '12px',
  color: '#94A3B8',
  marginTop: '2px',
}

const recordRightStyle = {
  display: 'flex' as const,
  flexDirection: 'column' as const,
  alignItems: 'flex-end' as const,
}

const recordAmountStyle = {
  fontSize: '16px',
  fontWeight: '700' as const,
}

const recordDateStyle = {
  fontSize: '11px',
  color: '#94A3B8',
  marginTop: '2px',
}

const deleteBtnStyle = {
  marginLeft: '8px',
  width: '24px',
  height: '24px',
  display: 'flex' as const,
  alignItems: 'center' as const,
  justifyContent: 'center' as const,
}

const deleteBtnTextStyle = {
  fontSize: '18px',
  color: '#CBD5E1',
}
