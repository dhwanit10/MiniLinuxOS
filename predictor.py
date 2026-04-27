import json
import sys
import os

FILE = "command_history.json"

def load_data():
    if not os.path.exists(FILE):
        return {}
    with open(FILE, "r") as f:
        return json.load(f)

def save_data(data):
    with open(FILE, "w") as f:
        json.dump(data, f, indent=2)

def update(prev_cmd, curr_cmd):
    data = load_data()

    if prev_cmd not in data:
        data[prev_cmd] = {}

    if curr_cmd not in data[prev_cmd]:
        data[prev_cmd][curr_cmd] = 0

    data[prev_cmd][curr_cmd] += 1

    save_data(data)

def suggest(prev_cmd):
    data = load_data()

    if prev_cmd not in data:
        print("No suggestions")
        return

    suggestions = data[prev_cmd]

    # sort by frequency
    sorted_cmds = sorted(suggestions.items(), key=lambda x: x[1], reverse=True)

    print("💡 Suggestions:")
    for cmd, count in sorted_cmds[:3]:
        print(f"{cmd} ({count})")

# CLI usage
if __name__ == "__main__":
    mode = sys.argv[1]

    if mode == "update":
        update(sys.argv[2], sys.argv[3])
    elif mode == "suggest":
        suggest(sys.argv[2])