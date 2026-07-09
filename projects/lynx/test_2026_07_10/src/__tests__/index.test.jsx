// src/__tests__/index.test.jsx
import '@testing-library/jest-dom'
import { expect, test } from 'vitest'
import { getQueriesForElement, render } from '@lynx-js/react/testing-library'

import { App } from '../App'

test('renders tab bar with three tabs', async () => {
  render(<App />)

  const { findByText } = getQueriesForElement(elementTree.root)

  const recordsTab = await findByText('流水')
  const statsTab = await findByText('统计')
  const settingsTab = await findByText('设置')

  expect(recordsTab).toBeInTheDocument()
  expect(statsTab).toBeInTheDocument()
  expect(settingsTab).toBeInTheDocument()
})

test('shows month header on records page', async () => {
  const { container } = render(<App />)

  const now = new Date()
  const monthText = `${now.getFullYear()}年${now.getMonth() + 1}月`

  await new Promise(resolve => setTimeout(resolve, 0))
  expect(container.textContent).toContain(monthText)
})
