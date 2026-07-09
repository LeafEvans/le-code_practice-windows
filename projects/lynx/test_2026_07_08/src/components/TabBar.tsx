import { useCallback } from '@lynx-js/react'
import type { TabKey } from '../types.js'

interface Props {
  activeTab: TabKey
  onTabChange: (tab: TabKey) => void
}

const TABS: { key: TabKey; label: string; icon: string }[] = [
  { key: 'records', label: '流水', icon: '☰' },
  { key: 'add', label: '记账', icon: '+' },
  { key: 'stats', label: '统计', icon: '◈' },
]

export function TabBar({ activeTab, onTabChange }: Props) {
  return (
    <view style={containerStyle}>
      {TABS.map((tab) => {
        const active = activeTab === tab.key
        return (
          <view
            key={tab.key}
            style={{
              ...tabStyle,
              ...(active ? activeTabStyle : {}),
            }}
            bindtap={() => {
              'background only'
              onTabChange(tab.key)
            }}
          >
            <text
              style={{
                ...iconStyle,
                ...(active ? activeIconStyle : {}),
              }}
            >
              {tab.icon}
            </text>
            <text
              style={{
                ...labelStyle,
                ...(active ? activeLabelStyle : {}),
              }}
            >
              {tab.label}
            </text>
          </view>
        )
      })}
    </view>
  )
}

const containerStyle = {
  width: '100%',
  display: 'flex' as const,
  flexDirection: 'row' as const,
  height: '64px',
  backgroundColor: '#FFFFFF',
  borderTop: '1px solid #E2E8F0',
  paddingBottom: '8px',
}

const tabStyle = {
  flex: 1,
  display: 'flex' as const,
  flexDirection: 'column' as const,
  alignItems: 'center' as const,
  justifyContent: 'center' as const,
}

const activeTabStyle = {
  backgroundColor: '#F8FAFC',
}

const iconStyle = {
  fontSize: '20px',
  lineHeight: '28px',
  color: '#94A3B8',
}

const activeIconStyle = {
  color: '#6366F1',
}

const labelStyle = {
  fontSize: '11px',
  lineHeight: '14px',
  color: '#94A3B8',
  marginTop: '2px',
}

const activeLabelStyle = {
  color: '#6366F1',
  fontWeight: '700' as const,
}
