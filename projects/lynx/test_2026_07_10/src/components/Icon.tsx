// src/components/Icon.tsx
import { ICONS } from '../data/icons.js'
import type { IconName } from '../data/icons.js'

export type { IconName }

interface IconProps {
  name: IconName
  size?: number
  color?: string
}

export function Icon({ name, size = 24, color = 'currentColor' }: IconProps) {
  const def = ICONS[name]
  if (!def) return null

  const paths = def.paths
    .map((d) => `<path d="${d}" fill="none" stroke="${color}" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>`)
    .join('')

  const svgContent = `<svg viewBox="${def.viewBox}" xmlns="http://www.w3.org/2000/svg">${paths}</svg>`

  return (
    <svg
      content={svgContent}
      style={{ width: `${size}px`, height: `${size}px` }}
    />
  )
}
