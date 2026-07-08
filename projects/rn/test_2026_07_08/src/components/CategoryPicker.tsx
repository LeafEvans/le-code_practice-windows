import React from "react";
import { View, Text, TouchableOpacity, StyleSheet } from "react-native";
import { Category } from "../types";

interface CategoryPickerProps {
  categories: Category[];
  selected: string;
  onSelect: (key: string) => void;
}

export default function CategoryPicker({
  categories,
  selected,
  onSelect,
}: CategoryPickerProps) {
  return (
    <View style={styles.grid}>
      {categories.map((cat) => (
        <TouchableOpacity
          key={cat.key}
          style={[styles.item, selected === cat.key && styles.itemSelected]}
          onPress={() => onSelect(cat.key)}
        >
          <Text style={styles.icon}>{cat.icon}</Text>
          <Text
            style={[
              styles.itemLabel,
              selected === cat.key && styles.itemLabelSelected,
            ]}
          >
            {cat.label}
          </Text>
        </TouchableOpacity>
      ))}
    </View>
  );
}

const styles = StyleSheet.create({
  grid: { flexDirection: "row", flexWrap: "wrap", gap: 8, paddingVertical: 8 },
  item: {
    width: "22%",
    aspectRatio: 1,
    backgroundColor: "#f5f5f5",
    borderRadius: 12,
    alignItems: "center",
    justifyContent: "center",
    padding: 4,
  },
  itemSelected: {
    backgroundColor: "#e3f2fd",
    borderWidth: 2,
    borderColor: "#2196F3",
  },
  icon: { fontSize: 24, marginBottom: 2 },
  itemLabel: { fontSize: 11, color: "#666" },
  itemLabelSelected: { color: "#2196F3", fontWeight: "600" },
});
