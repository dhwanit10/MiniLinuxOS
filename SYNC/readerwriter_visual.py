import matplotlib
matplotlib.use('TkAgg')

import matplotlib.pyplot as plt
import matplotlib.animation as animation

fig, ax = plt.subplots(figsize=(8,6))


def update(frame):
    ax.clear()

    readers = []
    writers = []

    try:
        with open('./SYNC/readerwriter_log.txt') as f:
            lines = f.readlines()

        for line in lines[-10:]:
            parts = line.split()

            if parts[0] == 'READER':
                readers.append(parts[1])

            elif parts[0] == 'WRITER':
                writers.append(parts[1])

    except:
        return

    ax.text(0.2, 0.8,
            f'Active Readers: {", ".join(readers)}',
            fontsize=16,
            bbox=dict(facecolor='lightblue'))

    ax.text(0.2, 0.5,
            f'Active Writers: {", ".join(writers)}',
            fontsize=16,
            bbox=dict(facecolor='salmon'))

    ax.set_title('Reader Writer Visualization', fontsize=18)

    ax.axis('off')

ani = animation.FuncAnimation(
    fig,
    update,
    interval=500,
    cache_frame_data=False
)

plt.tight_layout()

plt.show()