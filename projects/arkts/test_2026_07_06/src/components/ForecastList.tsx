import type { DailyForecast } from '../types/weather';
import { ForecastCard } from './ForecastCard';

interface ForecastListProps {
  daily: DailyForecast[];
}

export function ForecastList({ daily }: ForecastListProps) {
  return (
    <view className="forecast-section">
      <text className="forecast-title">7 日预报</text>
      <scroll-view className="forecast-scroll" scroll-orientation="horizontal">
        {daily.map((day, index) => (
          <ForecastCard key={day.date} data={day} index={index} />
        ))}
      </scroll-view>
    </view>
  );
}
