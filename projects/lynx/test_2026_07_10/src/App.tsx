// src/App.tsx
import { useState } from '@lynx-js/react'
import './App.css'
import { AppProvider } from './store/AppContext.js'
import { RecordsPage } from './pages/RecordsPage.js'
import { StatsPage } from './pages/StatsPage.js'
import { SettingsPage } from './pages/SettingsPage.js'

type Tab = 'records' | 'stats' | 'settings'

const TABS: { key: Tab; label: string }[] = [
  { key: 'records', label: '流水' },
  { key: 'stats', label: '统计' },
  { key: 'settings', label: '设置' },
]

export function App() {
  const [activeTab, setActiveTab] = useState<Tab>('records')

  return (
    <AppProvider>
      <view className="AppContainer">
        {/* Page content */}
        <view style={{ flex: 1 }}>
          {activeTab === 'records' && <RecordsPage />}
          {activeTab === 'stats' && <StatsPage />}
          {activeTab === 'settings' && <SettingsPage />}
        </view>

        {/* Bottom tab bar */}
        <view className="TabBar">
          {TABS.map((tab) => (
            <view
              key={tab.key}
              className={`TabItem ${activeTab === tab.key ? 'TabItem--active' : ''}`}
              bindtap={() => { setActiveTab(tab.key) }}
            >
              <text
                style={{
                  fontSize: '14px',
                  fontWeight: activeTab === tab.key ? '600' : '400',
                  color: activeTab === tab.key ? '#FF6B6B' : '#999',
                }}
              >
                {tab.label}
              </text>
            </view>
          ))}
        </view>
      </view>
    </AppProvider>
  )
}
