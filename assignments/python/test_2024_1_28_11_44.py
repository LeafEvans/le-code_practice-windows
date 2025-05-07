import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

plt.rc("font", family="Inter")
df = pd.read_excel("Problem_C_Data_Wordle.xlsx")
df["Date"] = pd.to_datetime(df["Date"]).dt.date

plt.plot(df.index, df["Number of reported results"], c="r")
plt.xlabel("Date", size=15, weight="bold")
plt.ylabel("Number of reported results", size=15, weight="bold")
plt.xticks(df.index[::50], df["Date"][::50])
plt.show()
