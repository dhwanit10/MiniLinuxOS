import psutil
import time
from datetime import datetime

import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt


# -------- Format Process Start Time --------
def format_time(t):
    return datetime.fromtimestamp(t).strftime("%Y-%m-%d %H:%M:%S")


# -------- List Running Processes --------
def list_processes():

    print("\n================ ACTIVE PROCESS LIST ================")
    print("{:<8} {:<25} {:<10} {:<10} {:<20}".format(
        "PID", "Name", "CPU%", "Memory%", "Start Time"))
    print("-------------------------------------------------------")

    for proc in psutil.process_iter(['pid','name','cpu_percent','memory_percent','create_time']):
        try:
            print("{:<8} {:<25} {:<10} {:<10} {:<20}".format(
                proc.info['pid'],
                proc.info['name'][:23],
                proc.info['cpu_percent'],
                round(proc.info['memory_percent'],2),
                format_time(proc.info['create_time'])
            ))
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            continue


# -------- Kill Process --------
def kill_process():

    while True:
        try:
            pid = int(input("\nEnter PID to terminate: "))

            if pid <= 0:
                print("Error: PID must be positive.")
                continue

            process = psutil.Process(pid)
            process.terminate()

            print(f"Process {pid} terminated successfully.")
            break

        except psutil.NoSuchProcess:
            print("Error: Process does not exist.")

        except ValueError:
            print("Error: Please enter a valid PID.")


# -------- Live CPU / Memory Monitor --------
def monitor():

    print("\nLive CPU & Memory Monitor (Press CTRL+C to stop)\n")

    try:
        while True:
            cpu = psutil.cpu_percent(interval=1)
            memory = psutil.virtual_memory().percent

            print(f"CPU Usage: {cpu}%   |   Memory Usage: {memory}%")

    except KeyboardInterrupt:
        print("\nMonitoring stopped.\n")


# -------- System Statistics Dashboard (ALL GRAPHS) --------
def system_dashboard():

    cpu_history = []
    mem_history = []
    time_points = []

    print("\nCollecting system statistics...\n")

    # collect usage data
    for i in range(10):
        cpu = psutil.cpu_percent(interval=1)
        mem = psutil.virtual_memory().percent

        cpu_history.append(cpu)
        mem_history.append(mem)
        time_points.append(i)


    # -------- Top CPU Processes --------
    proc_names = []
    proc_cpu = []

    for proc in psutil.process_iter():
        try:
            proc.cpu_percent(None)
        except:
            pass

    time.sleep(1)

    for proc in psutil.process_iter(['name']):
        try:
            cpu = proc.cpu_percent(None)

            if cpu > 0:
                proc_names.append(proc.info['name'])
                proc_cpu.append(cpu)

        except:
            pass

    proc_names = proc_names[:6]
    proc_cpu = proc_cpu[:6]


    # -------- Memory Distribution --------
    mem_labels = []
    mem_values = []

    for proc in psutil.process_iter(['name','memory_percent']):
        try:
            mem = proc.info['memory_percent']

            if mem > 0:
                mem_labels.append(proc.info['name'])
                mem_values.append(mem)

        except:
            pass

    mem_labels = mem_labels[:6]
    mem_values = mem_values[:6]


    # -------- Dashboard Layout --------
    fig, axs = plt.subplots(2,2, figsize=(14,8))


    # CPU Trend Line Graph
    axs[0,0].plot(time_points, cpu_history, marker='o')
    axs[0,0].set_title("CPU Usage Trend")
    axs[0,0].set_xlabel("Time (seconds)")
    axs[0,0].set_ylabel("CPU Usage (%)")


    # Memory Trend Area Graph
    axs[0,1].fill_between(time_points, mem_history)
    axs[0,1].set_title("Memory Usage Trend")
    axs[0,1].set_xlabel("Time (seconds)")
    axs[0,1].set_ylabel("Memory Usage (%)")


    # CPU Process Bar Chart
    axs[1,0].bar(proc_names, proc_cpu)
    axs[1,0].set_title("Top CPU Consuming Processes")
    axs[1,0].set_ylabel("CPU Usage (%)")
    axs[1,0].tick_params(axis='x', rotation=45)


    # Memory Distribution Pie Chart
    axs[1,1].pie(mem_values, labels=mem_labels, autopct='%1.1f%%')
    axs[1,1].set_title("Memory Usage Distribution")


    plt.suptitle("System Resource Statistics Dashboard", fontsize=16)

    plt.tight_layout()
    plt.show()



# -------- Menu --------
def menu():

    while True:

        print("\n================ PYTHON PROCESS MANAGER ================")
        print("1. List Running Processes")
        print("2. Kill a Process")
        print("3. Live CPU/Memory Monitor")
        print("4. System Statistics Dashboard (All Graphs)")
        print("5. Exit")

        choice = input("\nEnter choice: ")

        if choice == "1":
            list_processes()

        elif choice == "2":
            kill_process()

        elif choice == "3":
            monitor()

        elif choice == "4":
            system_dashboard()

        elif choice == "5":
            print("\nExiting Process Manager...\n")
            break

        else:
            print("Invalid option. Try again.")


# -------- Program Start --------
if __name__ == "__main__":
    menu()