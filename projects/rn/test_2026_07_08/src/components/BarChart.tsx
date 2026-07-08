import React from "react";
import { View, Text } from "react-native";
import Svg, { Rect, Line, G, Text as SvgText } from "react-native-svg";

interface BarData {
  label: string;
  value: number;
}

interface BarChartProps {
  data: BarData[];
  width?: number;
  height?: number;
  color?: string;
  unit?: string;
}

export default function BarChart({
  data,
  width = 340,
  height = 200,
  color = "#4BC0C0",
  unit = "¥",
}: BarChartProps) {
  if (data.length === 0) {
    return (
      <View
        style={{
          width,
          height,
          justifyContent: "center",
          alignItems: "center",
        }}
      >
        <Text style={{ color: "#999" }}>暂无数据</Text>
      </View>
    );
  }

  const padding = { top: 20, right: 10, bottom: 40, left: 50 };
  const chartW = width - padding.left - padding.right;
  const chartH = height - padding.top - padding.bottom;
  const maxVal = Math.max(...data.map((d) => d.value), 1);
  const barW = Math.min(30, (chartW / data.length) * 0.7);
  const gap = chartW / data.length;

  return (
    <Svg width={width} height={height}>
      <G x={padding.left} y={padding.top}>
        <Line x1={0} y1={0} x2={0} y2={chartH} stroke="#ddd" strokeWidth={1} />
        <Line
          x1={0}
          y1={chartH}
          x2={chartW}
          y2={chartH}
          stroke="#ddd"
          strokeWidth={1}
        />
        {data.map((d, i) => {
          const barH = (d.value / maxVal) * chartH;
          const x = i * gap + (gap - barW) / 2;
          const y = chartH - barH;
          return (
            <G key={i}>
              <Rect
                x={x}
                y={y}
                width={barW}
                height={barH}
                fill={color}
                rx={4}
              />
              <SvgText
                x={x + barW / 2}
                y={chartH + 16}
                fontSize={10}
                fill="#666"
                textAnchor="middle"
              >
                {d.label}
              </SvgText>
              <SvgText
                x={x + barW / 2}
                y={y - 6}
                fontSize={10}
                fill="#333"
                textAnchor="middle"
              >
                {d.value > 0 ? `${unit}${d.value}` : ""}
              </SvgText>
            </G>
          );
        })}
      </G>
    </Svg>
  );
}
