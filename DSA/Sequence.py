import matplotlib.pyplot as plt

algorithms = ["FCFS","SSTF","SCAN","LOOK","C-SCAN","C-LOOK"]

def parse_file(filename):
    data = {}
    current_algo = None

    with open(filename, "r") as f:
        for line in f:
            line = line.strip()

            # detect algorithm
            if line in algorithms:
                current_algo = line

            # detect sequence safely
            elif "Seek Sequence" in line and current_algo:

                if ":" in line:
                    seq_str = line.split(":", 1)[1]

                    # fix "->" format issue
                    seq_str = seq_str.replace("->", " ")

                    parts = seq_str.split()

                    seq = []
                    for p in parts:
                        try:
                            seq.append(float(p))
                        except:
                            continue

                    if seq:   # only store if valid
                        data[current_algo] = seq

    return data


def plot_all(data):
    if not data:
        print("No valid data found!")
        return

    plt.figure()

    for algo, seq in data.items():
        if len(seq) == 0:
            continue

        x = list(range(len(seq)))
        plt.plot(x, seq, marker='o', linewidth=2, label=algo)

    plt.xlabel("Steps")
    plt.ylabel("Tracks")
    plt.title("Disk Scheduling Seek Sequence")
    plt.legend()
    plt.grid()

    plt.show()


data = parse_file("disk_output.txt")
print("DEBUG:", data)
plot_all(data)