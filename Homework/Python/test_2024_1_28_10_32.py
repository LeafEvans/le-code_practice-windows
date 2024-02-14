import pandas as pd

# 创建 DataFrame
data = {
    "Salesperson": ["Alice", "Bob", "Charlie", "Alice", "Bob", "Charlie"],
    "SaleAmount": [100, 200, 150, 50, 250, 300],
    "SaleDate": [
        "2020-01-01",
        "2020-01-02",
        "2020-01-03",
        "2020-02-01",
        "2020-02-02",
        "2020-02-03",
    ],
}
df = pd.DataFrame(data)

# 将 SaleDate 列转换为日期类型，并提取月份
df["SaleMonth"] = pd.to_datetime(df["SaleDate"]).dt.month

# 使用 pivot_table 方法生成透视表
pivot_table = df.pivot_table(
    index="Salesperson", columns="SaleMonth", values="SaleAmount", aggfunc="sum"
)

print(pivot_table)
