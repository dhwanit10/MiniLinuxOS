import matplotlib.pyplot as plt

def read():
    with open("compare.txt") as f:
        lines = f.readlines()

    names = []
    internal = []
    external = []

    for i in range(6):   # 6 algorithms (Fixed + Variable)
        data = lines[i].split()
        names.append(data[0])
        internal.append(int(data[1]))
        external.append(int(data[2]))

    best = int(lines[6])   # best index

    return names, internal, external, best


def plot():
    names, internal, external, best = read()

    x = range(len(names))

    # colors for highlight
    int_colors = ["lightblue"] * len(names)
    ext_colors = ["orange"] * len(names)

    # BEST highlight (black border)
    int_colors[best] = "blue"
    ext_colors[best] = "red"

    width = 0.35

    # Bars
    plt.bar([i - width/2 for i in x], internal, width,
            label="Internal Fragmentation", color=int_colors)

    plt.bar([i + width/2 for i in x], external, width,
            label="External Fragmentation", color=ext_colors)

    # Values on bars
    for i in range(len(names)):
        plt.text(i - width/2, internal[i], str(internal[i]), ha='center')
        plt.text(i + width/2, external[i], str(external[i]), ha='center')

    plt.xticks(x, names, rotation=20)

    plt.title("Internal vs External Fragmentation Comparison")
    plt.xlabel("Algorithms")
    plt.ylabel("Fragmentation (KB)")

    plt.legend()
    plt.grid(axis='y')

    plt.tight_layout()
    plt.show()


plot()