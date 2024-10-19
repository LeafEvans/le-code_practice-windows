import pandas as pd

data = {"calories": [420, 380, 390], "duration": [50, 40, 45]}

df = pd.DataFrame(data, index=["day1", "day2", "day3"])
df["Salary"] = [50000, 60000, 70000]
print(df, "\n")
df.sort_values(by="duration", ascending=False, inplace=True)
print(df, "\n")
