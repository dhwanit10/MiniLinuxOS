import matplotlib.pyplot as plt

def read_data():
    with open("compare.txt","r") as f:
        lines = f.readlines()

    # clean lines
    lines = [l.strip() for l in lines if l.strip()]

    if len(lines) < 4:
        print("compare.txt incomplete!")
        print(lines)
        exit()

    names=[]
    faults=[]
    hits=[]
    ratios=[]

    for i in range(3):
        data = lines[i].split()

        if len(data) != 4:
            print("Format error in line:", lines[i])
            exit()

        names.append(data[0])
        faults.append(int(data[1]))
        hits.append(int(data[2]))
        ratios.append(float(data[3]))

    best = int(lines[3])

    return names,faults,hits,ratios,best


def plot():
    names,faults,hits,ratios,best = read_data()

    x = range(len(names))

    colors = ["gray"]*3
    colors[best] = "green"

    plt.figure(figsize=(8,5))

    # Bars
    bars_fault = plt.bar(x, faults, alpha=0.6, color=colors, label="Faults")
    bars_hit = plt.bar(x, hits, alpha=0.4, color="blue", label="Hits")

    # Ratio line
    plt.plot(x, ratios, marker='o', color='red', label="Ratio")

    # BLACK highlight (BEST)
    bars_fault[best].set_edgecolor('black')
    bars_fault[best].set_linewidth(3)

    # circle on best ratio point
    plt.plot(best, ratios[best],
             marker='o',
             markersize=12,
             markeredgecolor='black',
             markerfacecolor='none',
             linewidth=3)

    # SHOW VALUES
    for i in x:
        plt.text(i, faults[i] + 0.2, str(faults[i]), ha='center')
        plt.text(i, hits[i] + 0.2, str(hits[i]), ha='center')
        plt.text(i, ratios[i] + 0.02, f"{ratios[i]:.2f}", ha='center', color='red')

    plt.xticks(x, names)
    plt.title("Comparison (Best Highlighted)")
    plt.legend()
    plt.grid()

    plt.show()


plot()