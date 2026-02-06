import pandas as pd
import matplotlib.pyplot as plt

merge = pd.read_csv("merge.csv")
quick = pd.read_csv("quick.csv")


merge["Time"] *= 1_000_000
quick["Time"] *= 1_000_000

plt.figure(figsize=(8, 5))

plt.plot(
    merge["Count"], merge["Time"],
    marker="o", markersize=8, linewidth=2,
    label="Merge Sort"
)

plt.plot(
    quick["Count"], quick["Time"],
    marker="o", markersize=5, linewidth=2,
    label="Quick Sort"
)

plt.xlabel("Number of Elements")
plt.ylabel("Time (microseconds)")
plt.title("Merge Sort vs Quick Sort Performance")
plt.legend()
plt.grid(True)

plt.show()
