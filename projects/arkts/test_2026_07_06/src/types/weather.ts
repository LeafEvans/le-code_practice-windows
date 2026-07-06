export interface City {
  id: number;
  name: string;
  country: string;
  latitude: number;
  longitude: number;
}

export interface CurrentWeather {
  temperature: number;
  apparentTemperature: number;
  humidity: number;
  weatherCode: number;
  windSpeed: number;
  windDirection: number;
}

export interface DailyForecast {
  date: string;
  weatherCode: number;
  maxTemp: number;
  minTemp: number;
}

export interface WeatherData {
  current: CurrentWeather;
  daily: DailyForecast[];
  cityName: string;
}
