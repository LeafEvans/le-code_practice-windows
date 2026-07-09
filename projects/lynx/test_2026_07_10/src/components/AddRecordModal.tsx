// src/components/AddRecordModal.tsx
import { useCallback, useState } from '@lynx-js/react';
import { useAppContext } from '../store/AppContext.js';
import { todayStr } from '../utils/format.js';
import { CategoryIcon } from './CategoryIcon.js';

interface AddRecordModalProps {
  visible: boolean;
  onClose: () => void;
}

export function AddRecordModal({ visible, onClose }: AddRecordModalProps) {
  const { state, addRecord } = useAppContext();
  const [recordType, setRecordType] = useState<'expense' | 'income'>('expense');
  const [amountText, setAmountText] = useState('');
  const [selectedCategoryId, setSelectedCategoryId] = useState<string | null>(
    null,
  );
  const [note, setNote] = useState('');

  const filteredCategories = state.categories.filter(
    (c) => c.type === recordType,
  );

  const onSave = useCallback(() => {
    'background only';
    const amountYuan = parseFloat(amountText);
    if (Number.isNaN(amountYuan) || amountYuan <= 0 || !selectedCategoryId)
      return;

    addRecord({
      type: recordType,
      amount: Math.round(amountYuan * 100),
      categoryId: selectedCategoryId,
      date: todayStr(),
      note: note || undefined,
    });

    // Reset form
    setAmountText('');
    setSelectedCategoryId(null);
    setNote('');
    onClose();
  }, [amountText, selectedCategoryId, note, recordType, addRecord, onClose]);

  const canSave =
    amountText !== '' &&
    parseFloat(amountText) > 0 &&
    selectedCategoryId !== null;

  if (!visible) return null;

  return (
    <overlay visible={visible} style={{ position: 'fixed' }}>
      <view
        style={{
          width: '100%',
          height: '100%',
          backgroundColor: 'rgba(0, 0, 0, 0.4)',
          display: 'flex',
          justifyContent: 'flex-end',
        }}
        bindtap={onClose}
      >
        <view
          catchtap={() => {}}
          style={{
            width: '100%',
            backgroundColor: '#fff',
            borderTopLeftRadius: '20px',
            borderTopRightRadius: '20px',
            padding: '20px 16px',
            paddingBottom: '40px',
          }}
        >
          {/* Type toggle */}
          <view
            style={{
              display: 'flex',
              flexDirection: 'row',
              marginBottom: '20px',
            }}
          >
            <view
              bindtap={() => {
                setRecordType('expense');
              }}
              style={{
                flex: 1,
                padding: '10px',
                borderRadius: '10px',
                backgroundColor:
                  recordType === 'expense' ? '#FF6B6B' : '#f0f0f0',
                marginRight: '8px',
                display: 'flex',
                justifyContent: 'center',
              }}
            >
              <text
                style={{
                  color: recordType === 'expense' ? '#fff' : '#666',
                  fontWeight: '600',
                }}
              >
                支出
              </text>
            </view>
            <view
              bindtap={() => {
                setRecordType('income');
              }}
              style={{
                flex: 1,
                padding: '10px',
                borderRadius: '10px',
                backgroundColor:
                  recordType === 'income' ? '#00B894' : '#f0f0f0',
                display: 'flex',
                justifyContent: 'center',
              }}
            >
              <text
                style={{
                  color: recordType === 'income' ? '#fff' : '#666',
                  fontWeight: '600',
                }}
              >
                收入
              </text>
            </view>
          </view>

          {/* Amount input */}
          <view
            style={{
              display: 'flex',
              flexDirection: 'row',
              alignItems: 'center',
              marginBottom: '16px',
              border: '1px solid #e0e0e0',
              borderRadius: '12px',
              padding: '8px 12px',
            }}
          >
            <text
              style={{
                fontSize: '20px',
                color: recordType === 'expense' ? '#FF6B6B' : '#00B894',
                marginRight: '4px',
              }}
            >
              {recordType === 'expense' ? '-' : '+'}¥
            </text>
            <input
              type="digit"
              placeholder="0.00"
              style={{ flex: 1, fontSize: '20px', color: '#1a1a1a' }}
              bindinput={(e: { detail: { value: string } }) =>
                setAmountText(e.detail.value)
              }
            />
          </view>

          {/* Category picker */}
          <view style={{ marginBottom: '16px' }}>
            <text
              style={{ fontSize: '14px', color: '#999', marginBottom: '8px' }}
            >
              分类
            </text>
            <scroll-view scroll-x={true} style={{ height: '60px' }}>
              <view
                style={{
                  display: 'flex',
                  flexDirection: 'row',
                  padding: '4px 0',
                }}
              >
                {filteredCategories.map((cat) => (
                  <view
                    key={cat.id}
                    bindtap={() => {
                      setSelectedCategoryId(cat.id);
                    }}
                    style={{
                      marginRight: '12px',
                      display: 'flex',
                      flexDirection: 'column',
                      alignItems: 'center',
                      opacity: selectedCategoryId === cat.id ? 1 : 0.5,
                    }}
                  >
                    <CategoryIcon category={cat} size={22} />
                    <text
                      style={{
                        fontSize: '11px',
                        color: '#666',
                        marginTop: '4px',
                      }}
                    >
                      {cat.name}
                    </text>
                  </view>
                ))}
              </view>
            </scroll-view>
          </view>

          {/* Note input */}
          <view style={{ marginBottom: '20px' }}>
            <input
              type="text"
              placeholder="添加备注（选填）"
              style={{
                width: '100%',
                fontSize: '14px',
                color: '#1a1a1a',
                border: '1px solid #e0e0e0',
                borderRadius: '12px',
                padding: '10px 12px',
              }}
              bindinput={(e: { detail: { value: string } }) =>
                setNote(e.detail.value)
              }
            />
          </view>

          {/* Save button */}
          <view
            bindtap={canSave ? onSave : undefined}
            style={{
              backgroundColor: canSave
                ? recordType === 'expense'
                  ? '#FF6B6B'
                  : '#00B894'
                : '#e0e0e0',
              borderRadius: '12px',
              padding: '14px',
              display: 'flex',
              justifyContent: 'center',
            }}
          >
            <text
              style={{ color: '#fff', fontSize: '16px', fontWeight: '600' }}
            >
              保存
            </text>
          </view>
        </view>
      </view>
    </overlay>
  );
}
