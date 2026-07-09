import { useCallback, useState } from '@lynx-js/react'
import type { BookRecord, RecordType } from '../types.js'
import { EXPENSE_CATEGORIES, INCOME_CATEGORIES } from '../types.js'

interface Props {
  onSave: (record: BookRecord) => void
}

export function AddRecordPage({ onSave }: Props) {
  const [type, setType] = useState<RecordType>('expense')
  const [amount, setAmount] = useState('')
  const [category, setCategory] = useState('')
  const [note, setNote] = useState('')

  const categories = type === 'expense' ? EXPENSE_CATEGORIES : INCOME_CATEGORIES

  const handleTypeChange = useCallback((newType: RecordType) => {
    'background only'
    setType(newType)
    setCategory('')
  }, [])

  const handleAmountInput = useCallback((e: { detail: { value: string } }) => {
    'background only'
    const val = e.detail.value
    if (/^\d*\.?\d{0,2}$/.test(val) || val === '') {
      setAmount(val)
    }
  }, [])

  const handleCategorySelect = useCallback((cat: string) => {
    'background only'
    setCategory(cat)
  }, [])

  const handleNoteInput = useCallback((e: { detail: { value: string } }) => {
    'background only'
    setNote(e.detail.value)
  }, [])

  const handleSave = useCallback(() => {
    'background only'
    const num = parseFloat(amount)
    if (isNaN(num) || num <= 0) {
      return
    }
    if (!category) {
      return
    }
    onSave({
      id: Date.now().toString() + Math.random().toString(36).slice(2, 8),
      type,
      amount: num,
      category,
      note,
      date: new Date().toISOString().slice(0, 10),
    })
    setAmount('')
    setCategory('')
    setNote('')
  }, [amount, category, note, type, onSave])

  const canSave = parseFloat(amount) > 0 && category !== ''

  return (
    <view style={containerStyle}>
      <scroll-view scroll-y style={scrollStyle}>
        {/* 收入/支出切换 */}
        <view style={typeSwitchStyle}>
          {(['expense', 'income'] as RecordType[]).map((t) => {
            const active = type === t
            const expenseColor = '#F97316'
            const incomeColor = '#10B981'
            return (
              <view
                key={t}
                style={{
                  ...typeBtnStyle,
                  backgroundColor: active
                    ? t === 'expense'
                      ? expenseColor
                      : incomeColor
                    : '#F1F5F9',
                }}
                bindtap={() => handleTypeChange(t)}
              >
                <text
                  style={{
                    ...typeBtnTextStyle,
                    color: active ? '#FFFFFF' : '#64748B',
                    fontWeight: active ? '700' : '400',
                  }}
                >
                  {t === 'expense' ? '支出' : '收入'}
                </text>
              </view>
            )
          })}
        </view>

        {/* 金额输入 */}
        <view style={amountSectionStyle}>
          <text style={currencyStyle}>¥</text>
          <input
            style={amountInputStyle}
            placeholder='0.00'
            {...({ value: amount } as any)}
            bindinput={handleAmountInput}
            type='number'
          />
        </view>

        {/* 分类 */}
        <text style={sectionTitleStyle}>分类</text>
        <view style={categoryGridStyle}>
          {categories.map((cat) => {
            const active = category === cat
            const borderColor = type === 'expense' ? '#F97316' : '#10B981'
            const bgColor = type === 'expense' ? '#FFF7ED' : '#ECFDF5'
            return (
              <view
                key={cat}
                style={{
                  ...categoryItemStyle,
                  ...(active
                    ? {
                        borderColor,
                        backgroundColor: bgColor,
                      }
                    : {}),
                }}
                bindtap={() => handleCategorySelect(cat)}
              >
                <text
                  style={{
                    ...categoryTextStyle,
                    ...(active
                      ? {
                          color: borderColor,
                          fontWeight: '600',
                        }
                      : {}),
                  }}
                >
                  {cat}
                </text>
              </view>
            )
          })}
        </view>

        {/* 备注 */}
        <text style={sectionTitleStyle}>备注</text>
        <input
          style={noteInputStyle}
          placeholder='可选'
          {...({ value: note } as any)}
          bindinput={handleNoteInput}
        />

        {/* 保存按钮 */}
        <view
          style={{
            ...saveBtnStyle,
            backgroundColor: canSave ? '#6366F1' : '#E2E8F0',
          }}
          bindtap={handleSave}
        >
          <text
            style={{
              ...saveBtnTextStyle,
              color: canSave ? '#FFFFFF' : '#94A3B8',
            }}
          >
            保存
          </text>
        </view>
      </scroll-view>
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

const typeSwitchStyle = {
  display: 'flex' as const,
  flexDirection: 'row' as const,
  backgroundColor: '#F1F5F9',
  borderRadius: '10px',
  padding: '3px',
}

const typeBtnStyle = {
  flex: 1,
  paddingTop: '10px',
  paddingBottom: '10px',
  borderRadius: '8px',
  display: 'flex' as const,
  alignItems: 'center' as const,
  justifyContent: 'center' as const,
}

const typeBtnTextStyle = {
  fontSize: '15px',
}

const amountSectionStyle = {
  display: 'flex' as const,
  flexDirection: 'row' as const,
  alignItems: 'center' as const,
  justifyContent: 'center' as const,
  marginTop: '24px',
  marginBottom: '24px',
}

const currencyStyle = {
  fontSize: '32px',
  fontWeight: '700' as const,
  color: '#1E293B',
  marginRight: '4px',
}

const amountInputStyle = {
  fontSize: '36px',
  fontWeight: '700' as const,
  color: '#1E293B',
  borderWidth: '0',
  outline: 'none',
  textAlign: 'center' as const,
  width: '200px',
  height: '50px',
}

const sectionTitleStyle = {
  fontSize: '14px',
  fontWeight: '600' as const,
  color: '#64748B',
  marginBottom: '10px',
}

const categoryGridStyle = {
  display: 'flex' as const,
  flexDirection: 'row' as const,
  flexWrap: 'wrap' as const,
  marginBottom: '20px',
}

const categoryItemStyle = {
  paddingLeft: '16px',
  paddingRight: '16px',
  paddingTop: '10px',
  paddingBottom: '10px',
  borderRadius: '8px',
  borderWidth: '1.5px',
  borderColor: '#E2E8F0',
  backgroundColor: '#FFFFFF',
  marginBottom: '8px',
  marginRight: '8px',
}

const categoryTextStyle = {
  fontSize: '14px',
  color: '#475569',
}

const noteInputStyle = {
  width: '100%',
  boxSizing: 'border-box' as const,
  height: '44px',
  backgroundColor: '#FFFFFF',
  borderRadius: '8px',
  borderWidth: '1px',
  borderColor: '#E2E8F0',
  paddingLeft: '12px',
  paddingRight: '12px',
  fontSize: '14px',
  color: '#1E293B',
  marginBottom: '24px',
}

const saveBtnStyle = {
  width: '100%',
  boxSizing: 'border-box' as const,
  paddingTop: '14px',
  paddingBottom: '14px',
  borderRadius: '10px',
  display: 'flex' as const,
  alignItems: 'center' as const,
  justifyContent: 'center' as const,
  marginBottom: '24px',
}

const saveBtnTextStyle = {
  fontSize: '16px',
  fontWeight: '700' as const,
}
