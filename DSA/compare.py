import matplotlib.pyplot as plt

algorithms = ["FCFS","SSTF","SCAN","LOOK","C-SCAN","C-LOOK"]

def parse_file(filename):
    data = {}
    current = None

    with open(filename, "r") as f:
        for line in f:
            line = line.strip()

            # detect algorithm
            if line in algorithms:
                current = line

            # detect total seek time safely
            elif "Total Seek Time" in line and current:

                try:
                    val = float(line.split(":")[1].split()[0])
                    data[current] = val
                except:
                    continue

    return data


def show_table_and_best(data):

    if len(data) == 0:
        print("No data found!")
        return

    print("\n========== DISK SCHEDULING RESULT ==========\n")
    print("Algorithm\tTotal Seek Time (ms)")
    print("-------------------------------------------")

    best_algo = min(data, key=data.get)

    for algo, val in data.items():
        if algo == best_algo:
            print(f"{algo}\t\t{val}   <-- BEST")
        else:
            print(f"{algo}\t\t{val}")

    print("-------------------------------------------")
    print("BEST ALGORITHM :", best_algo)
    print("===========================================\n")


def plot(data):

    if len(data) == 0:
        return

    names = list(data.keys())
    values = list(data.values())

    plt.figure()
    bars = plt.bar(names, values)

    best_algo = min(data, key=data.get)

    for i, name in enumerate(names):
        if name == best_algo:
            bars[i].set_edgecolor('black')
            bars[i].set_linewidth(3)

    for i, v in enumerate(values):
        plt.text(i, v, str(v), ha='center')

    plt.xlabel("Algorithms")
    plt.ylabel("Seek Time (ms)")
    plt.title("Disk Scheduling Comparison")
    plt.grid()

    plt.show()


data = parse_file("disk_output.txt")

print("DEBUG:", data)

show_table_and_best(data)
plot(data)