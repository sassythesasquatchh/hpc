import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import ScalarFormatter
from fractions import Fraction
import matplotlib.ticker as ticker


def fractions(x, pos):
    if x >= 1:
        # x is an integer, so just return that
        return "{:.0f}".format(x)
    else:
        # this returns a formatted fraction
        return str(Fraction(x))


pfp_7h12 = 41.6
pfp_7763 = 39.2
bw_7h12 = 15
bw_7763 = 25
ridge_7h12 = pfp_7h12 / bw_7h12
ridge_7763 = pfp_7763 / bw_7763
x_plot = np.array([0.25, 0.5, 1, 2, 4, 8, 16])
x = np.append(x_plot, [ridge_7763, ridge_7h12])
x.sort()
y_7h12 = np.minimum(pfp_7h12, bw_7h12 * x)
y_7763 = np.minimum(pfp_7763, bw_7763 * x)

fig, ax = plt.subplots()

ax.plot(x, y_7h12, label="7H12")
ax.plot(x, y_7763, label="7763")
ax.set_xscale("log", base=2)
ax.set_yscale("log", base=2)

ax.axvline(
    x=ridge_7h12,
    color="#6CBED2",
    linestyle="--",
    ymax=np.log2(pfp_7h12) / 6,
)
ax.axvline(
    x=ridge_7763,
    color="#FFCCCC",
    linestyle="--",
    ymax=np.log2(pfp_7763) / 6,
)

# Set ticks and tick labels for the x-axis
ax.set_xticks(x_plot)
ax.set_xlim(min(x), max(x))
ax.xaxis.set_major_formatter(ticker.FuncFormatter(fractions))

# Set ticks and tick labels for the y-axis
y_ticks = [
    2**i for i in range(0, int(np.ceil(np.log2(max(y_7h12.max(), y_7763.max())))) + 1)
]
ax.set_yticks(y_ticks)
ax.get_yaxis().set_major_formatter(ScalarFormatter())

ax.grid(True, which="both", linestyle="--", linewidth=0.5)

ax.set_xlabel("Operational Intensity (Flops/Byte)")
ax.set_ylabel("Attainable GFlop/s")
ax.legend(title="CPU")
ax.set_title("Roofline for Euler VII")

plt.savefig("roofline.svg")

print(f"Ridge 7H12: {ridge_7h12}")
print(f"Ridge 7763: {ridge_7763}")
