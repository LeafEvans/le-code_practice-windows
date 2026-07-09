import type { BookRecord } from '../types.js'

interface Props {
  records: BookRecord[]
}

export function StatsPage({ records }: Props) {
  const thisMonth = new Date().toISOString().slice(0, 7)
  const monthRecords = records.filter((r) => r.date.startsWith(thisMonth))

  const income = monthRecords.filter((r) => r.type === 'income')
  const expense = monthRecords.filter((r) => r.type === 'expense')

  const totalIncome = income.reduce((s, r) => s + r.amount, 0)
  const totalExpense = expense.reduce((s, r) => s + r.amount, 0)

  // 支出分类统计
  const expenseByCat: Record<string, number> = {}
  for (const r of expense) {
    expenseByCat[r.category] = (expenseByCat[r.category] || 0) + r.amount
  }
  const expenseSorted = Object.entries(expenseByCat).sort(
    (a, b) => b[1] - a[1],
  )
  const maxExpense = expenseSorted[0]?.[1] || 1

  // 收入分类统计
  const incomeByCat: Record<string, number> = {}
  for (const r of income) {
    incomeByCat[r.category] = (incomeByCat[r.category] || 0) + r.amount
  }
  const incomeSorted = Object.entries(incomeByCat).sort((a, b) => b[1] - a[1])
  const maxIncome = incomeSorted[0]?.[1] || 1

  return (
    <view style={containerStyle}>
      <scroll-view scroll-y style={scrollStyle}>
        {/* 本月概览 */}
        <view style={overviewStyle}>
          <view style={cardStyle}>
            <text style={cardTitleStyle}>本月支出</text>
            <text style={{ ...cardAmountStyle, color: '#F97316' }}>
              ¥{totalExpense.toFixed(2)}
            </text>
          </view>
          <view style={cardStyle}>
            <text style={cardTitleStyle}>本月收入</text>
            <text style={{ ...cardAmountStyle, color: '#10B981' }}>
              ¥{totalIncome.toFixed(2)}
            </text>
          </view>
        </view>

        {/* 支出分类 */}
        <text style={sectionTitleStyle}>
          {totalExpense > 0 ? '支出分类' : '支出分类（暂无数据）'}
        </text>
        {expenseSorted.length > 0 ? (
          <view style={barListStyle}>
            {expenseSorted.map(([cat, amount]) => (
              <BarItem
                key={cat}
                label={cat}
                amount={amount}
                max={maxExpense}
                color="#F97316"
              />
            ))}
          </view>
        ) : (
          <text style={emptyTextStyle}>本月暂无支出</text>
        )}

        {/* 收入分类 */}
        <text style={sectionTitleStyle}>
          {totalIncome > 0 ? '收入分类' : '收入分类（暂无数据）'}
        </text>
        {incomeSorted.length > 0 ? (
          <view style={barListStyle}>
            {incomeSorted.map(([cat, amount]) => (
              <BarItem
                key={cat}
                label={cat}
                amount={amount}
                max={maxIncome}
                color="#10B981"
              />
            ))}
          </view>
        ) : (
          <text style={emptyTextStyle}>本月暂无收入</text>
        )}

        {/* 总笔数 */}
        <view style={footerStyle}>
          <text style={footerTextStyle}>
            本月共 {monthRecords.length} 笔记录
          </text>
        </view>
      </scroll-view>
    </view>
  )
}

function BarItem({
  label,
  amount,
  max,
  color,
}: {
  label: string
  amount: number
  max: number
  color: string
}) {
  const pct = (amount / max) * 100
  return (
    <view style={barItemStyle}>
      <text style={barLabelStyle}>{label}</text>
      <view style={barTrackStyle}>
        <view
          style={{
            ...barFillStyle,
            width: `${pct}%`,
            backgroundColor: color,
          }}
        />
      </view>
      <text style={{ ...barAmountStyle, color }}>
        ¥{amount.toFixed(2)}
      </text>
    </view>
  )
}

const containerStyle = {
  flex: 1,
  width: '100%',
  backgroundColor: '#F8FAFC',
}

const scrollStyle = {
  flex: 1,
  width: '100%',
  paddingLeft: '16px',
  paddingRight: '16px',
  paddingTop: '16px',
}

const overviewStyle = {
  display: 'flex' as const,
  flexDirection: 'row' as const,
  marginBottom: '20px',
}

const cardStyle = {
  flex: 1,
  backgroundColor: '#FFFFFF',
  borderRadius: '12px',
  padding: '16px',
  display: 'flex' as const,
  flexDirection: 'column' as const,
  alignItems: 'center' as const,
  marginLeft: '6px',
  marginRight: '6px',
}

const cardTitleStyle = {
  fontSize: '13px',
  color: '#94A3B8',
  marginBottom: '8px',
}

const cardAmountStyle = {
  fontSize: '22px',
  fontWeight: '700' as const,
}

const sectionTitleStyle = {
  fontSize: '14px',
  fontWeight: '600' as const,
  color: '#64748B',
  marginBottom: '10px',
}

const barListStyle = {
  marginBottom: '20px',
}

const barItemStyle = {
  display: 'flex' as const,
  flexDirection: 'row' as const,
  alignItems: 'center' as const,
  marginBottom: '10px',
}

const barLabelStyle = {
  width: '50px',
  fontSize: '13px',
  color: '#475569',
}

const barTrackStyle = {
  flex: 1,
  height: '16px',
  backgroundColor: '#F1F5F9',
  borderRadius: '8px',
  marginLeft: '8px',
  marginRight: '8px',
  overflow: 'hidden',
}

const barFillStyle = {
  height: '100%',
  borderRadius: '8px',
}

const barAmountStyle = {
  width: '80px',
  fontSize: '13px',
  fontWeight: '600' as const,
  textAlign: 'right' as const,
}

const emptyTextStyle = {
  fontSize: '13px',
  color: '#94A3B8',
  marginBottom: '20px',
}

const footerStyle = {
  paddingTop: '20px',
  paddingBottom: '20px',
  display: 'flex' as const,
  alignItems: 'center' as const,
}

const footerTextStyle = {
  fontSize: '12px',
  color: '#94A3B8',
}
