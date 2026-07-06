import { useCallback, useEffect } from '@lynx-js/react';
import './App.css';
import { CitySearch } from './components/CitySearch';
import { CurrentWeather } from './components/CurrentWeather';
import { ForecastList } from './components/ForecastList';
import { useWeather } from './hooks/useWeather';

export function App() {
  const { weatherData, loading, error, searchCity, loadDefaultCity } = useWeather();

  useEffect(() => {
    loadDefaultCity();
  }, []);

  const handleSearch = useCallback((cityName: string) => {
    searchCity(cityName);
  }, [searchCity]);

  return (
    <view className="app">
      <CitySearch onSearch={handleSearch} />
      <view className="content">
        {loading && (
          <view className="status-message">
            <text className="status-text">加载中...</text>
          </view>
        )}

        {error && !loading && (
          <view className="status-message status-error">
            <text className="status-text">{error}</text>
            <view className="retry-btn" bindtap={loadDefaultCity}>
              <text className="retry-btn-text">重试</text>
            </view>
          </view>
        )}

        {!loading && !error && !weatherData && (
          <view className="status-message">
            <text className="status-text">正在获取默认城市天气...</text>
          </view>
        )}

        {weatherData && !loading && (
          <>
            <CurrentWeather data={weatherData.current} cityName={weatherData.cityName} />
            <ForecastList daily={weatherData.daily} />
          </>
        )}
      </view>
    </view>
  );
}
