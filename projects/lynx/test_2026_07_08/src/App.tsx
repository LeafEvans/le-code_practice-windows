import { useCallback, useEffect, useState } from '@lynx-js/react'

import './App.css'
import type { BookRecord, TabKey } from './types.js'
import { loadRecords, saveRecords } from './utils/storage.js'
import { AddRecordPage } from './components/AddRecordPage.js'
import { RecordsPage } from './components/RecordsPage.js'
import { StatsPage } from './components/StatsPage.js'
import { TabBar } from './components/TabBar.js'

export function App() {
  const [activeTab, setActiveTab] = useState<TabKey>('records')
  const [records, setRecords] = useState<BookRecord[]>(loadRecords)

  // 持久化
  useEffect(() => {
    saveRecords(records)
  }, [records])

  const handleSave = useCallback((record: BookRecord) => {
    'background only'
    setRecords((prev) => [record, ...prev])
    setActiveTab('records')
  }, [])

  const handleDelete = useCallback((id: string) => {
    'background only'
    setRecords((prev) => prev.filter((r) => r.id !== id))
  }, [])

  return (
    <view className='App'>
      <view className='App-main'>
        {activeTab === 'records' && (
          <RecordsPage records={records} onDelete={handleDelete} />
        )}
        {activeTab === 'add' && <AddRecordPage onSave={handleSave} />}
        {activeTab === 'stats' && <StatsPage records={records} />}
      </view>
      <TabBar activeTab={activeTab} onTabChange={setActiveTab} />
    </view>
  )
}
