import json
from pathlib import Path
from collections import defaultdict

# ── Config ─────────────────────────────────────────────────────────────────
TRANSITIONS_FILE = Path(__file__).parent / "data" / "transitions.json"
PRETRAINED_SCALE = 1.0
TOP_N = 3

# ── Model ──────────────────────────────────────────────────────────────────
class CommandPredictor:
    def __init__(self):
        self._pretrained = json.loads(TRANSITIONS_FILE.read_text())
        self._user = defaultdict(lambda: defaultdict(int))
        self._history = []

    def add(self, cmd):
        self._history.append(cmd)
        if len(self._history) > 1:
            self._user[self._history[-2]][cmd] += 1

    def suggest(self, cmd):
        scores = {}
        for c, w in self._pretrained.get(cmd, {}).items():
            scores[c] = scores.get(c, 0.0) + w * PRETRAINED_SCALE
        for c, n in self._user.get(cmd, {}).items():
            scores[c] = scores.get(c, 0.0) + n

        def tag(c):
            a = c in self._pretrained.get(cmd, {})
            b = c in self._user.get(cmd, {})
            return "hybrid" if a and b else "learned" if b else "pretrained"

        return [
            {"command": c, "score": s, "source": tag(c)}
            for c, s in sorted(scores.items(), key=lambda x: x[1], reverse=True)[:TOP_N]
        ]

    def stats(self):
        return {
            "commands_entered": len(self._history),
            "pretrained_pairs": sum(len(v) for v in self._pretrained.values()),
            "user_learned_pairs": sum(len(v) for v in self._user.values()),
        }

# ── CLI ────────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    predictor = CommandPredictor()
    print("AI Command Predictor  |  'stats' · 'exit'\n")

    while True:
        cmd = input("MiniLinuxOS> ").strip()
        if not cmd:        continue
        if cmd == "exit":  break
        if cmd == "stats":
            [print(f"  {k}: {v}") for k, v in predictor.stats().items()]
            print(); continue

        predictor.add(cmd)
        suggestions = predictor.suggest(cmd)
        if suggestions:
            for i, s in enumerate(suggestions, 1):
                print(f"  {i}. {s['command']:<28} [{s['source']}]")
        else:
            print("  No suggestions yet.")
        print()