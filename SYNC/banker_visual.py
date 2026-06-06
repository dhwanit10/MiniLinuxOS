import matplotlib
matplotlib.use('TkAgg')

import matplotlib.pyplot as plt
import matplotlib.animation as animation

sequence = []

fig, ax = plt.subplots(figsize=(10,4))


def update(frame):
    ax.clear()

    try:
        with open('./SYNC/banker_log.txt') as f:
            lines = f.readlines()

        sequence.clear()

        for line in lines:
            parts = line.split()

            if parts[0] == 'PROCESS':
                sequence.append(int(parts[1]))

    except:
        return

    for i, p in enumerate(sequence):

        rect = plt.Rectangle((i,0), 1,1,
                             color='lightgreen',
                             ec='black')

        ax.add_patch(rect)

        ax.text(i+0.5,
                0.5,
                f'P{p}',
                ha='center',
                va='center',
                fontsize=16,
                fontweight='bold')

    ax.set_xlim(0, max(5,len(sequence)+1))
    ax.set_ylim(0,2)

    ax.axis('off')

    ax.set_title('Banker Algorithm Safe Sequence', fontsize=18)

ani = animation.FuncAnimation(
    fig,
    update,
    interval=500,
    cache_frame_data=False
)

plt.tight_layout()

plt.show()