import matplotlib.pyplot as plt

def read():
    with open("alloc.txt") as f:
        lines = f.readlines()

    name = lines[0].strip()
    b, p = map(int, lines[1].split())
    blocks = list(map(int, lines[2].split()))
    processes = list(map(int, lines[3].split()))
    alloc = list(map(int, lines[4].split()))

    return name,b,p,blocks,processes,alloc


def plot():
    name,b,p,blocks,processes,alloc = read()

    fig, ax = plt.subplots(figsize=(10,5))

    for i in range(b):

        text = ""

        for j in range(p):
            if alloc[j] == i:
                text += f"P{j+1}\n{processes[j]}KB\n"

        if text == "":
            text = "Free"

        rect = plt.Rectangle((i,0),0.8,1,
                             edgecolor='black',
                             facecolor='lightblue')

        ax.add_patch(rect)

        ax.text(i+0.4,0.5,text,
                ha='center',va='center')

    # BLOCK NAMES BELOW
    plt.xticks([i+0.4 for i in range(b)],
           [f"B{i+1}\n{blocks[i]}KB" for i in range(b)])

    plt.yticks([])
    plt.title(name + " Memory Allocation")

    plt.xlim(0,b)
    plt.ylim(0,1)

    plt.show()


plot()