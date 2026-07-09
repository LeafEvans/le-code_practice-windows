// src/pages/SettingsPage.tsx
import { useCallback } from "@lynx-js/react";
import { CategoryIcon } from "../components/CategoryIcon.js";
import { useAppContext } from "../store/AppContext.js";
import type { Category } from "../store/types.js";

export function SettingsPage() {
  const { state, dispatch } = useAppContext();

  const expenseCategories = state.categories.filter(
    (c) => c.type === "expense",
  );
  const incomeCategories = state.categories.filter((c) => c.type === "income");

  const onDeleteCategory = useCallback(
    (id: string) => {
      "background only";
      dispatch({ type: "DELETE_CATEGORY", payload: id });
    },
    [dispatch],
  );

  return (
    <scroll-view
      scroll-y={true}
      style={{ flex: 1, backgroundColor: "#fafafa" }}
    >
      {/* Expense categories */}
      <view style={{ backgroundColor: "#fff", marginTop: "8px" }}>
        <text
          style={{
            fontSize: "14px",
            fontWeight: "600",
            color: "#666",
            padding: "16px 16px 8px",
          }}
        >
          支出分类
        </text>
        {expenseCategories.map((cat) => (
          <CategoryRow
            key={cat.id}
            category={cat}
            onDelete={
              cat.isDefault ? undefined : () => onDeleteCategory(cat.id)
            }
          />
        ))}
      </view>

      {/* Income categories */}
      <view style={{ backgroundColor: "#fff", marginTop: "8px" }}>
        <text
          style={{
            fontSize: "14px",
            fontWeight: "600",
            color: "#666",
            padding: "16px 16px 8px",
          }}
        >
          收入分类
        </text>
        {incomeCategories.map((cat) => (
          <CategoryRow
            key={cat.id}
            category={cat}
            onDelete={
              cat.isDefault ? undefined : () => onDeleteCategory(cat.id)
            }
          />
        ))}
      </view>

      {/* Footer */}
      <view
        style={{
          padding: "24px 16px",
          display: "flex",
          justifyContent: "center",
        }}
      >
        <text style={{ fontSize: "12px", color: "#ccc" }}>
          Bookkeeping v1.0
        </text>
      </view>
    </scroll-view>
  );
}

function CategoryRow({
  category,
  onDelete,
}: {
  category: Category;
  onDelete?: () => void;
}) {
  return (
    <view
      style={{
        display: "flex",
        flexDirection: "row",
        alignItems: "center",
        padding: "12px 16px",
        borderBottom: "1px solid #f5f5f5",
      }}
    >
      <CategoryIcon category={category} size={18} />
      <text
        style={{
          fontSize: "16px",
          color: "#1a1a1a",
          marginLeft: "12px",
          flex: 1,
        }}
      >
        {category.name}
      </text>
      {onDelete ? (
        <view
          bindtap={onDelete}
          style={{
            padding: "6px 12px",
            borderRadius: "6px",
            backgroundColor: "#fff5f5",
          }}
        >
          <text style={{ fontSize: "13px", color: "#FF6B6B" }}>删除</text>
        </view>
      ) : (
        <text style={{ fontSize: "12px", color: "#ccc" }}>默认</text>
      )}
    </view>
  );
}
