import type { DailyForecast } from '../types/weather';
import { getWeatherIcon } from '../api/weather';

const WEEKDAY_NAMES = ['周日', '周一', '周二', '周三', '周四', '周五', '周六'];

function getWeekDay(dateStr: string, index: number): string {
  if (index === 0) return '今天';
  const date = new Date(dateStr);
  return WEEKDAY_NAMES[date.getDay()];
}

interface ForecastCardProps {
  data: DailyForecast;
  index: number;
}

export function ForecastCard({ data, index }: ForecastCardProps) {
  return (
    <view className={`forecast-card ${index === 0 ? 'forecast-card-today' : ''}`}>
      <text className="forecast-day">{getWeekDay(data.date, index)}</text>
      <text className="forecast-icon">{getWeatherIcon(data.weatherCode)}</text>
      <text className="forecast-temp-high">{data.maxTemp}°</text>
      <text className="forecast-temp-low">{data.minTemp}°</text>
    </view>
  );
}
