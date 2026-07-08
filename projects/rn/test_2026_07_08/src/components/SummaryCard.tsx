import React from "react";
import { View, Text, StyleSheet } from "react-native";
import { formatCurrency } from "../utils/format";

interface SummaryCardProps {
  label: string;
  amount: number;
  type: "income" | "expense" | "balance";
}

export default function SummaryCard({ label, amount, type }: SummaryCardProps) {
  const color =
    type === "income" ? "#4CAF50" : type === "expense" ? "#F44336" : "#2196F3";
  const prefix = type === "income" ? "+" : type === "expense" ? "-" : "";
  return (
    <View style={[styles.card, { borderTopColor: color }]}>
      <Text style={styles.label}>{label}</Text>
      <Text style={[styles.amount, { color }]}>
        {prefix}
        {formatCurrency(amount)}
      </Text>
    </View>
  );
}

const styles = StyleSheet.create({
  card: {
    flex: 1,
    backgroundColor: "#fff",
    borderRadius: 12,
    padding: 16,
    marginHorizontal: 4,
    borderTopWidth: 3,
    elevation: 2,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 1 },
    shadowOpacity: 0.1,
    shadowRadius: 4,
  },
  label: { fontSize: 13, color: "#888", marginBottom: 6 },
  amount: { fontSize: 20, fontWeight: "700" },
});
