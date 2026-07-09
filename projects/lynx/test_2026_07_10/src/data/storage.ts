// src/data/storage.ts
import type { AppState } from '../store/types.js'
import { defaultCategories } from './categories.js'
import { seedRecords } from './seed.js'

let appState: AppState | null = null

/** Load state. Returns defaults + seed if never saved. */
export function loadState(): AppState {
  if (appState) return appState

  // First run: seed with defaults
  appState = {
    records: seedRecords,
    categories: [...defaultCategories],
  }
  return appState
}

/** Save state to memory. */
export function saveState(state: AppState): void {
  appState = state
}

/** Reset to empty state (for testing or data clear). */
export function clearState(): void {
  appState = null
}
