from collections import defaultdict

class CommandPredictor:

    def __init__(self):
        # stores transitions
        self.model = defaultdict(lambda: defaultdict(int))
        self.history = []

    def add_command(self, command):

        # store command in history
        self.history.append(command)

        # if at least 2 commands exist, build bigram
        if len(self.history) > 1:
            prev = self.history[-2]
            curr = self.history[-1]

            self.model[prev][curr] += 1


    def suggest(self, command, top_n=3):

        if command not in self.model:
            return []

        next_commands = self.model[command]

        # sort by frequency
        sorted_cmds = sorted(next_commands.items(), key=lambda x: x[1], reverse=True)

        return [cmd for cmd, freq in sorted_cmds[:top_n]]


def main():

    predictor = CommandPredictor()

    print("AI Command Predictor")
    print("Type 'exit' to stop\n")

    while True:

        cmd = input("MiniLinuxOS> ")

        if cmd == "exit":
            break

        predictor.add_command(cmd)

        suggestions = predictor.suggest(cmd)

        if suggestions:
            print("Suggested commands:")
            for s in suggestions:
                print(" -", s)

        print()


if __name__ == "__main__":
    main()