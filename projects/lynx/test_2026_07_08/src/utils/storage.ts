import type { BookRecord } from '../types.js'

const KEY = 'ledger_records'

// Lynx has no localStorage. Use in-memory store as fallback.
const memoryStore: Record<string, string> = {}

function getStorage(): Storage | null {
  if (typeof localStorage !== 'undefined') {
    try {
      localStorage.getItem('__probe__')
      return localStorage
    } catch {
      // localStorage exists but inaccessible (e.g. security restrictions)
    }
  }
  return null
}

export function loadRecords(): BookRecord[] {
  try {
    const store = getStorage()
    const raw = store ? store.getItem(KEY) : memoryStore[KEY]
    return raw ? JSON.parse(raw) : []
  } catch {
    return []
  }
}

export function saveRecords(records: BookRecord[]): void {
  const data = JSON.stringify(records)
  const store = getStorage()
  if (store) {
    store.setItem(KEY, data)
  } else {
    memoryStore[KEY] = data
  }
}
