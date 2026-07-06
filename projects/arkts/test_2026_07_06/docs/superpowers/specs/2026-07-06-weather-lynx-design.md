# Weather App — Lynx + HarmonyOS Demo

## Overview

一个天气查询 Demo 应用，使用 ByteDance Lynx 跨平台框架，首发 HarmonyOS，后续扩展到 Android/iOS。目标是展示 Lynx 的核心能力（网络请求、列表渲染、条件样式、状态管理），同时产出可运行的 HAP。

## Tech Stack

| 层级 | 技术 |
|------|------|
| 前端框架 | Lynx (ReactLynx, TypeScript/TSX) |
| 样式 | Lynx CSS 子集 (Flexbox) |
| 构建工具 | Rspeedy (npm create rspeedy@latest) |
| 原生集成 | lynx-native-cli |
| 宿主平台 | HarmonyOS (DevEco Studio) |
| 天气 API | Open-Meteo (免费, 无需 key) |
| 地理编码 | Open-Meteo Geocoding API (城市名→经纬度) |

## Architecture

```
weather-lynx/
├── src/                         # Lynx 前端 (TypeScript/TSX, 跨平台共享)
│   ├── App.tsx                  # 根组件，组装子组件
│   ├── App.css                  # 全局样式
│   ├── index.tsx                # 入口文件
│   ├── api/
│   │   └── weather.ts           # Open-Meteo API 封装
│   ├── components/
│   │   ├── CitySearch.tsx       # 顶部城市搜索栏
│   │   ├── CurrentWeather.tsx   # 当前天气展示 (大图+温度+详情)
│   │   ├── ForecastCard.tsx     # 单日预报卡片
│   │   └── ForecastList.tsx     # 7 日预报横向滚动列表
│   ├── hooks/
│   │   └── useWeather.ts        # 天气数据获取与管理 hook
│   └── types/
│       └── weather.ts           # TypeScript 类型定义
├── harmony/                     # HarmonyOS 宿主项目 (lynx-native-cli 生成)
│   └── ...                      # ArkTS 壳, DevEco Studio 打开
├── lynx.config.ts               # Rspeedy 构建配置
└── package.json
```

## Data Flow

```
用户输入城市名
    │
    ▼
CitySearch ──→ useWeather hook
    │              │
    │    1. 调 Geocoding API → 获取经纬度
    │    2. 调用 Weather API  → 获取当前+7日预报
    │              │
    ▼              ▼
CurrentWeather  ForecastList (共享 hook 返回数据)
```

## Features

### 1. 城市搜索
- 顶部搜索栏，输入城市名
- 默认城市：北京，首次打开自动展示
- 调用 Open-Meteo Geocoding API 解析城市名→经纬度
- 预置几个常用城市快捷选择（北京、上海、深圳、成都、纽约、东京）

### 2. 当前天气
- 大号天气图标 (根据 weather code 映射)
- 当前温度 (摄氏度)
- 天气描述文本
- 湿度百分比
- 风速/风向
- 体感温度

### 3. 7 日预报
- 横向可滚动列表 (横向 scroll-view)
- 每天显示：星期、天气图标、最高/最低温
- 突出今天

### 4. 状态处理
- **Loading**: 骨架屏/加载动画
- **Empty**: 未搜索时的默认提示
- **Error**: 网络错误时的重试按钮 + 提示文字

## UI Layout

单页面纵向布局：

```
┌──────────────────────────────┐
│  🔍 搜索城市...   [快捷选择▼] │  CitySearch
├──────────────────────────────┤
│                              │
│          ☀️                  │
│         28°C                 │  CurrentWeather
│       晴  体感 30°           │
│       💧 湿度 45%            │
│       🌬 东北风 3级          │
│                              │
├──────────────────────────────┤
│  7 日预报                    │
│  ┌────┬────┬────┬────┬───┐  │
│  │今天│明天│周三│周四│...│  │  ForecastList
│  │ ☀️ │ ⛅ │ 🌧 │ ⛅ │   │  │  (横向滚动)
│  │28°│26°│22°│24°│   │  │
│  └────┴────┴────┴────┴───┘  │
└──────────────────────────────┘
```

## API Endpoints

### Geocoding (城市搜索)
```
GET https://geocoding-api.open-meteo.com/v1/search?name={city}&count=5&language=zh
```

### Weather (天气数据)
```
GET https://api.open-meteo.com/v1/forecast
    ?latitude={lat}&longitude={lon}
    &current=temperature_2m,relative_humidity_2m,apparent_temperature,weather_code,wind_speed_10m,wind_direction_10m
    &daily=weather_code,temperature_2m_max,temperature_2m_min
    &timezone=Asia/Shanghai
    &forecast_days=7
```

### Weather Code → 图标映射
| Code Range | 描述 | 图标 |
|-----------|------|------|
| 0 | 晴 | ☀️ |
| 1-3 | 多云 | ⛅ |
| 45-48 | 雾 | 🌫 |
| 51-67 | 小雨/中雨 | 🌧 |
| 71-86 | 雪 | ❄️ |
| 95-99 | 雷暴 | ⛈ |

## States

| 状态 | 处理方式 |
|------|---------|
| 首次加载 (默认城市) | Loading → 展示数据 |
| 搜索新城市 | Loading → 展示数据 |
| 搜索为空 | "未找到该城市" 提示 |
| 网络错误 | "加载失败" + 重试按钮 |
| API 返回空数据 | "暂无天气数据" |

## Cross-Platform Strategy

- `src/` 目录代码 100% 跨平台共享
- 通过 `lynx-native-cli` 分别添加各平台宿主：
  - `lynx add harmony` → DevEco Studio 编译 HAP
  - `lynx add android` → Android Studio 编译 APK
  - `lynx add ios` → Xcode 编译 IPA
- 如需平台特定样式，使用 Lynx 的条件编译

## Non-Goals (本次不做)

- 定位自动获取当前位置
- 天气地图/雷达图
- 推送通知
- 多城市收藏
- 国际化多语言
- 离线缓存
