import type { CurrentWeather as CurrentWeatherType } from '../types/weather';
import { getWeatherIcon, getWeatherDescription, getWindDirection } from '../api/weather';

interface CurrentWeatherProps {
  data: CurrentWeatherType;
  cityName: string;
}

export function CurrentWeather({ data, cityName }: CurrentWeatherProps) {
  return (
    <view className="current-weather">
      <text className="city-name">{cityName}</text>
      <text className="weather-icon-large">{getWeatherIcon(data.weatherCode)}</text>
      <text className="temperature">{data.temperature}°C</text>
      <text className="weather-desc">{getWeatherDescription(data.weatherCode)}</text>
      <text className="feels-like">体感 {data.apparentTemperature}°C</text>
      <view className="weather-details">
        <view className="detail-item">
          <text className="detail-icon">💧</text>
          <text className="detail-text">湿度 {data.humidity}%</text>
        </view>
        <view className="detail-item">
          <text className="detail-icon">🌬</text>
          <text className="detail-text">{getWindDirection(data.windDirection)}风 {data.windSpeed}km/h</text>
        </view>
      </view>
    </view>
  );
}
