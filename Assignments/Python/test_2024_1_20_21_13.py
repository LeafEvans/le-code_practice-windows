import matplotlib.pyplot as plt

plt.rc("font", family="inter")

x = range(2, 26, 2)
y = [15, 13, 14.5, 17, 20, 25, 26, 26, 24, 22, 18, 15]
fig = plt.figure(figsize=(20, 8), dpi=80)
plt.plot(x, y)
_xtick_labels = [i / 2 for i in range(4, 49)]
plt.xticks(range(25, 50))
plt.yticks(range(min(y), max(y) + 1))
plt.show()
