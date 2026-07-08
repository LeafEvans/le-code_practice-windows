import React from "react";
import { View, Text } from "react-native";
import Svg, { Path, G } from "react-native-svg";

interface PieSlice {
  label: string;
  value: number;
  color: string;
  icon: string;
}

interface PieChartProps {
  data: PieSlice[];
  size?: number;
}

const COLORS = [
  "#FF6384",
  "#36A2EB",
  "#FFCE56",
  "#4BC0C0",
  "#9966FF",
  "#FF9F40",
  "#C9CBCF",
  "#7BC67E",
];

function polarToCartesian(cx: number, cy: number, r: number, angleDeg: number) {
  const angleRad = ((angleDeg - 90) * Math.PI) / 180;
  return { x: cx + r * Math.cos(angleRad), y: cy + r * Math.sin(angleRad) };
}

function describeArc(
  cx: number,
  cy: number,
  r: number,
  startAngle: number,
  endAngle: number,
) {
  const start = polarToCartesian(cx, cy, r, endAngle);
  const end = polarToCartesian(cx, cy, r, startAngle);
  const largeArcFlag = endAngle - startAngle <= 180 ? "0" : "1";
  return `M ${cx} ${cy} L ${start.x} ${start.y} A ${r} ${r} 0 ${largeArcFlag} 0 ${end.x} ${end.y} Z`;
}

export default function PieChart({ data, size = 200 }: PieChartProps) {
  const total = data.reduce((sum, d) => sum + d.value, 0);
  if (total === 0) {
    return (
      <View
        style={{
          width: size,
          height: size,
          justifyContent: "center",
          alignItems: "center",
        }}
      >
        <Text style={{ color: "#999" }}>暂无数据</Text>
      </View>
    );
  }

  const radius = (size / 2) * 0.8;
  const cx = size / 2;
  const cy = size / 2;
  let currentAngle = 0;

  const filtered = data.filter((d) => d.value > 0);

  return (
    <View style={{ width: size, height: size }}>
      <Svg width={size} height={size}>
        <G>
          {filtered.map((slice, i) => {
            const sliceAngle = (slice.value / total) * 360;
            const startAngle = currentAngle;
            const endAngle = currentAngle + sliceAngle;
            currentAngle += sliceAngle;
            return (
              <Path
                key={i}
                d={describeArc(cx, cy, radius, startAngle, endAngle)}
                fill={slice.color || COLORS[i % COLORS.length]}
              />
            );
          })}
        </G>
      </Svg>
    </View>
  );
}
