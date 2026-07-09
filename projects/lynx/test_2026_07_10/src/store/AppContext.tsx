// src/store/AppContext.tsx
import {
  createContext,
  useCallback,
  useContext,
  useEffect,
  useReducer,
  type Dispatch,
} from '@lynx-js/react'
import type { Action, AppState, Record } from './types.js'
import { loadState, saveState } from '../data/storage.js'
import { generateId } from '../utils/format.js'

function reducer(state: AppState, action: Action): AppState {
  switch (action.type) {
    case 'LOAD_DATA':
      return action.payload

    case 'ADD_RECORD':
      return {
        ...state,
        records: [action.payload, ...state.records],
      }

    case 'DELETE_RECORD':
      return {
        ...state,
        records: state.records.filter((r) => r.id !== action.payload),
      }

    case 'UPDATE_RECORD':
      return {
        ...state,
        records: state.records.map((r) =>
          r.id === action.payload.id ? action.payload : r,
        ),
      }

    case 'ADD_CATEGORY':
      return {
        ...state,
        categories: [...state.categories, action.payload],
      }

    case 'DELETE_CATEGORY': {
      const categoryId = action.payload
      return {
        ...state,
        categories: state.categories.filter((c) => c.id !== categoryId),
        records: state.records.filter((r) => r.categoryId !== categoryId),
      }
    }

    default:
      return state
  }
}

interface AppContextValue {
  state: AppState
  dispatch: Dispatch<Action>
  addRecord: (record: Omit<Record, 'id' | 'createdAt'>) => void
}

const AppContext = createContext<AppContextValue | null>(null)

export function AppProvider({ children }: { children: React.ReactNode }) {
  const [state, dispatch] = useReducer(reducer, null, () => loadState())

  // Auto-persist on state change
  useEffect(() => {
    saveState(state)
  }, [state])

  const addRecord = useCallback(
    (data: Omit<Record, 'id' | 'createdAt'>) => {
      'background only'
      const record: Record = {
        ...data,
        id: generateId(),
        createdAt: Date.now(),
      }
      dispatch({ type: 'ADD_RECORD', payload: record })
    },
    [dispatch],
  )

  return (
    <AppContext.Provider value={{ state, dispatch, addRecord }}>
      {children}
    </AppContext.Provider>
  )
}

export function useAppContext(): AppContextValue {
  const ctx = useContext(AppContext)
  if (!ctx) throw new Error('useAppContext must be used within AppProvider')
  return ctx
}
