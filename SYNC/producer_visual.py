import matplotlib
matplotlib.use('TkAgg')

import matplotlib.pyplot as plt
import matplotlib.animation as animation

buffer_count = 0
last_action = ''

fig, ax = plt.subplots(figsize=(10,5))


def update(frame):
    global buffer_count
    global last_action

    ax.clear()

    try:
        with open('./SYNC/producer_log.txt') as f:
            lines = f.readlines()

        if lines:
            parts = lines[-1].split()

            last_action = ' '.join(parts[:3])
            buffer_count = int(parts[3])

    except:
        return

    for i in range(10):

        color = 'lightgray'

        if i < buffer_count:
            color = 'skyblue'

        rect = plt.Rectangle((i,0), 1,1,
                             color=color,
                             ec='black')

        ax.add_patch(rect)

    ax.text(5, 1.5,
            f'Buffer Usage: {buffer_count}',
            ha='center',
            fontsize=16,
            fontweight='bold')

    ax.text(5, -0.5,
            f'Last Action: {last_action}',
            ha='center',
            fontsize=14)

    ax.set_xlim(0,10)
    ax.set_ylim(-1,3)

    ax.axis('off')

    ax.set_title('Producer Consumer Visualization',
                 fontsize=18)

ani = animation.FuncAnimation(
    fig,
    update,
    interval=500,
    cache_frame_data=False
)

plt.tight_layout()

plt.show()