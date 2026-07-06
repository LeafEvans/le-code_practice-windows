import type {
  City,
  CurrentWeather,
  DailyForecast,
  WeatherData,
} from "../types/weather";

const GEOCODING_BASE = "https://geocoding-api.open-meteo.com/v1/search";
const WEATHER_BASE = "https://api.open-meteo.com/v1/forecast";

export async function searchCity(name: string): Promise<City[]> {
  const url = `${GEOCODING_BASE}?name=${encodeURIComponent(name)}&count=5&language=zh`;
  const res = await fetch(url);
  if (!res.ok) throw new Error(`Geocoding failed: ${res.status}`);
  const json = await res.json();
  if (!json.results) return [];
  return json.results.map(
    (r: {
      id: number;
      name: string;
      country: string;
      latitude: number;
      longitude: number;
    }) => ({
      id: r.id,
      name: r.name,
      country: r.country,
      latitude: r.latitude,
      longitude: r.longitude,
    }),
  );
}

export async function getWeather(
  lat: number,
  lon: number,
): Promise<WeatherData> {
  const params = new URLSearchParams({
    latitude: String(lat),
    longitude: String(lon),
    current:
      "temperature_2m,relative_humidity_2m,apparent_temperature,weather_code,wind_speed_10m,wind_direction_10m",
    daily: "weather_code,temperature_2m_max,temperature_2m_min",
    timezone: "Asia/Shanghai",
    forecast_days: "7",
  });
  const url = `${WEATHER_BASE}?${params.toString()}`;
  const res = await fetch(url);
  if (!res.ok) throw new Error(`Weather API failed: ${res.status}`);
  const json = await res.json();

  const current: CurrentWeather = {
    temperature: Math.round(json.current.temperature_2m),
    apparentTemperature: Math.round(json.current.apparent_temperature),
    humidity: json.current.relative_humidity_2m,
    weatherCode: json.current.weather_code,
    windSpeed: json.current.wind_speed_10m,
    windDirection: json.current.wind_direction_10m,
  };

  const daily: DailyForecast[] = json.daily.time.map(
    (date: string, i: number) => ({
      date,
      weatherCode: json.daily.weather_code[i],
      maxTemp: Math.round(json.daily.temperature_2m_max[i]),
      minTemp: Math.round(json.daily.temperature_2m_min[i]),
    }),
  );

  return { current, daily, cityName: "" };
}

// Map WMO weather codes to icons and descriptions
const WEATHER_MAP: Record<number, { icon: string; desc: string }> = {
  0: { icon: "☀️", desc: "晴" },
  1: { icon: "🌤", desc: "少云" },
  2: { icon: "⛅", desc: "多云" },
  3: { icon: "☁️", desc: "阴" },
  45: { icon: "🌫", desc: "雾" },
  48: { icon: "🌫", desc: "雾凇" },
  51: { icon: "🌦", desc: "小雨" },
  53: { icon: "🌦", desc: "中雨" },
  55: { icon: "🌦", desc: "大雨" },
  61: { icon: "🌧", desc: "小雨" },
  63: { icon: "🌧", desc: "中雨" },
  65: { icon: "🌧", desc: "大雨" },
  71: { icon: "❄️", desc: "小雪" },
  73: { icon: "❄️", desc: "中雪" },
  75: { icon: "❄️", desc: "大雪" },
  77: { icon: "❄️", desc: "雪粒" },
  80: { icon: "🌧", desc: "阵雨" },
  81: { icon: "🌧", desc: "中阵雨" },
  82: { icon: "🌧", desc: "大阵雨" },
  85: { icon: "❄️", desc: "小阵雪" },
  86: { icon: "❄️", desc: "大阵雪" },
  95: { icon: "⛈", desc: "雷暴" },
  96: { icon: "⛈", desc: "雷暴+冰雹" },
  99: { icon: "⛈", desc: "强雷暴+冰雹" },
};

export function getWeatherIcon(code: number): string {
  return WEATHER_MAP[code]?.icon ?? "❓";
}

export function getWeatherDescription(code: number): string {
  return WEATHER_MAP[code]?.desc ?? "未知";
}

const WIND_DIRECTIONS = [
  "北",
  "东北",
  "东",
  "东南",
  "南",
  "西南",
  "西",
  "西北",
];

export function getWindDirection(degrees: number): string {
  const index = Math.round(degrees / 45) % 8;
  return WIND_DIRECTIONS[index];
}
