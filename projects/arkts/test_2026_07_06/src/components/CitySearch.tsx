import { useState, useCallback } from '@lynx-js/react';

const QUICK_CITIES = ['北京', '上海', '深圳', '成都', '纽约', '东京'];

interface CitySearchProps {
  onSearch: (cityName: string) => void;
}

export function CitySearch({ onSearch }: CitySearchProps) {
  const [inputValue, setInputValue] = useState('');
  const [showQuickCities, setShowQuickCities] = useState(false);

  const handleInput = useCallback((e: { detail: { value: string } }) => {
    setInputValue(e.detail.value);
  }, []);

  const handleSearch = useCallback(() => {
    const trimmed = inputValue.trim();
    if (!trimmed) return;
    setShowQuickCities(false);
    onSearch(trimmed);
  }, [inputValue, onSearch]);

  const handleQuickSelect = useCallback((cityName: string) => {
    setInputValue(cityName);
    setShowQuickCities(false);
    onSearch(cityName);
  }, [onSearch]);

  const toggleQuickCities = useCallback(() => {
    setShowQuickCities(prev => !prev);
  }, []);

  return (
    <view className="city-search">
      <view className="search-bar">
        <input
          className="search-input"
          placeholder="搜索城市..."
          bindinput={handleInput}
        />
        <view className="search-btn" bindtap={handleSearch}>
          <text className="search-btn-text">搜索</text>
        </view>
        <view className="quick-btn" bindtap={toggleQuickCities}>
          <text className="quick-btn-text">{showQuickCities ? '收起' : '快捷'}</text>
        </view>
      </view>
      {showQuickCities && (
        <view className="quick-cities">
          {QUICK_CITIES.map(city => (
            <view className="quick-city-item" key={city} bindtap={() => handleQuickSelect(city)}>
              <text className="quick-city-text">{city}</text>
            </view>
          ))}
        </view>
      )}
    </view>
  );
}
