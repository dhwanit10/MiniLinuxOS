import matplotlib
matplotlib.use('TkAgg')

import matplotlib.pyplot as plt
import matplotlib.animation as animation

states = {}

fig, ax = plt.subplots(figsize=(8,8))


def update(frame):
    ax.clear()

    try:
        with open('./SYNC/dining_log.txt', 'r') as f:
            lines = f.readlines()

        for line in lines:
            parts = line.strip().split()

            if len(parts) != 2:
                continue

            state = parts[0]
            pid = int(parts[1])

            states[pid] = state

    except:
        return

    n = max(states.keys()) + 1 if states else 5

    import math

    for i in range(n):
        angle = 2 * math.pi * i / n

        x = math.cos(angle)
        y = math.sin(angle)

        state = states.get(i, 'THINKING')

        color = 'green'

        if state == 'EATING':
            color = 'red'

        ax.scatter(x, y, s=4000, c=color)

        ax.text(x, y,
                f'P{i}\n{state}',
                ha='center',
                va='center',
                fontsize=12,
                color='white',
                fontweight='bold')

    ax.set_title('Dining Philosopher Visualization', fontsize=18)

    ax.axis('off')

ani = animation.FuncAnimation(
    fig,
    update,
    interval=500,
    cache_frame_data=False
)

plt.tight_layout()

plt.show()