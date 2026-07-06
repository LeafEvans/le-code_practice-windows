import { useState, useCallback } from '@lynx-js/react';
import { searchCity as apiSearchCity, getWeather as apiGetWeather } from '../api/weather';
import type { City, WeatherData } from '../types/weather';

export function useWeather() {
  const [weatherData, setWeatherData] = useState<WeatherData | null>(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const fetchWeatherForCity = useCallback(async (city: City) => {
    setLoading(true);
    setError(null);
    try {
      const data = await apiGetWeather(city.latitude, city.longitude);
      setWeatherData({ ...data, cityName: city.name });
    } catch {
      setError('获取天气数据失败，请检查网络后重试');
    } finally {
      setLoading(false);
    }
  }, []);

  const searchCity = useCallback(async (name: string) => {
    setLoading(true);
    setError(null);
    try {
      const cities = await apiSearchCity(name);
      if (cities.length === 0) {
        setError('未找到该城市，请尝试其他名称');
        setLoading(false);
        return;
      }
      await fetchWeatherForCity(cities[0]);
    } catch {
      setError('网络请求失败，请检查网络后重试');
      setLoading(false);
    }
  }, [fetchWeatherForCity]);

  const loadDefaultCity = useCallback(async () => {
    await searchCity('北京');
  }, [searchCity]);

  return { weatherData, loading, error, searchCity, loadDefaultCity };
}
