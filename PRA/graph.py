import matplotlib.pyplot as plt
import numpy as np

def read_file():
    with open("output.txt", "r") as f:
        lines = f.readlines()

    # ALGO NAME
    algo = lines[0].strip()

    # REFERENCE
    reference = list(map(int, lines[1].split()))

    # SAFE FRAME COUNT
    try:
        frame_count = int(lines[2].strip())
        start = 3
    except:
        frame_count = len(lines[2].split())
        start = 2

    # STEPS
    steps = []
    for line in lines[start:]:
        steps.append(list(map(int, line.split())))

    return algo, reference, frame_count, steps


def plot(algo, reference, frame_count, steps):

    data = np.array(steps)

    plt.figure(figsize=(10, 6))

    plt.imshow(data, cmap="Blues", aspect="auto")

    # DYNAMIC TITLE
    plt.title(f"{algo} Page Replacement Visualization")

    plt.xlabel("Frames")
    plt.ylabel("Steps")

    plt.xticks(range(frame_count), [f"F{i+1}" for i in range(frame_count)])
    plt.yticks(range(len(reference)), reference)

    # MULTI COLORS (AUTO)
    colors = ["#ff9999", "#99ff99", "#9999ff", "#ffcc99", "#cc99ff", "#66cccc"]

    for i in range(len(steps)):
        for j in range(frame_count):

            val = steps[i][j]
            text = "-" if val == -1 else str(val)

            plt.text(
                j, i, text,
                ha="center",
                va="center",
                bbox=dict(
                    facecolor=colors[j % len(colors)],
                    alpha=0.4,
                    edgecolor="none"
                )
            )

    plt.tight_layout()
    plt.show()


algo, ref, f, steps = read_file()
plot(algo, ref, f, steps)