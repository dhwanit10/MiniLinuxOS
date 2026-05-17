# MYOS — Mini Linux Terminal

```
███╗   ███╗██╗   ██╗ ██████╗ ███████╗
████╗ ████║╚██╗ ██╔╝██╔═══██╗██╔════╝
██╔████╔██║ ╚████╔╝ ██║   ██║███████╗
██║╚██╔╝██║  ╚██╔╝  ██║   ██║╚════██║
██║ ╚═╝ ██║   ██║   ╚██████╔╝███████║
╚═╝     ╚═╝   ╚═╝    ╚═════╝ ╚══════╝

═══════════════════════════════════════════════════════════════
						 MYOS TERMINAL - COMMAND CENTER
═══════════════════════════════════════════════════════════════
```

🚀 MYOS is a compact, educational Mini Linux terminal built in C that runs native Linux commands, provides simulators for OS topics (CPU scheduling, disk scheduling, page replacement, memory management), visualizations for threads/processes, synchronization demos, and integrated AI utilities for code generation, fixing and explanations.

**Highlights**
- **Native Shell**: Runs standard Linux commands like `ls`, `pwd`, `cd`, `cat`, `nano`, `git`, etc.
- **OS Simulators**: CPU scheduling (FCFS, SRTF, RR, Priority), Disk scheduling, Page Replacement, Memory Management.
- **Concurrency Visuals**: Thread vs Process visualizer, Process Manager, and classic sync problems (Dining, Producer/Consumer, Reader/Writer, Banker's algorithm).
- **AI Tools**: Natural-language-to-command (`ai`), code generation (`code`), code fixer (`fix`), code explainer (`explain`) and interactive GPT mode (`gpt`).
- **Extensible**: Autocomplete support and modular C + Python helpers.

**Files & Quick Links**
- **Compile command**: See the exact compile line in [scripts/compile.txt](scripts/compile.txt#L1).
- **Docker run & tips**: See [scripts/Docker-run.txt](scripts/Docker-run.txt#L1-L200).
- **Dockerfile**: The container build runs the same `gcc` compile command: [Dockerfile](Dockerfile#L13).

**Features (detailed)**
- **Basic Linux Commands**: `ls`, `pwd`, `cd`, `mkdir`, `rmdir`, `touch`, `cat`, `rm`, `nano`, `clear`, `git` and more.
- **CPU Scheduling Module**: `cpu fcfs`, `cpu srtf`, `cpu RR`, `cpu priority` — visualizers and runners.
- **Thread & Process Module**: `thread process` (visualization), `process manager` (interactive Python manager).
- **Memory & Storage**: `disk scheduling`, `page replacement`, `memory management` launch respective simulators.
- **Synchronization Module**: `sync menu`, `dining`, `producer`, `reader`, `banker`.
- **AI Utilities**:
	- `ai "natural language"` — convert NL into a shell command (asks for confirmation before executing).
	- `fix <file> --auto|--manual` — run AI-powered fixer.
	- `explain <file> [--short|--detailed]` — AI explanation of code.
	- `code` — interactive code generator that invokes the AI agent.
	- `gpt` — interactive GPT chat mode.
- **System Commands**: `help`, `myos` (reprint banner), `exit`.

**Custom Command Groups**
- **CPU**: `cpu <algorithm>` (fcfs|srtf|RR|priority)
- **Thread/process**: `thread process`, `process manager`
- **Disk / Page / Memory**: `disk scheduling`, `page replacement`, `memory management`
- **Sync**: `sync menu`, `dining`, `producer`, `reader`, `banker`
- **AI**: `ai`, `fix`, `explain`, `code`, `gpt`

**Install & Run — Linux (native)**
1. Install required system packages (example for Debian/Ubuntu):

```
sudo apt update
sudo apt install build-essential libreadline-dev -y
```

2. Compile the project (exact command in [scripts/compile.txt](scripts/compile.txt#L1)):

```
gcc src/myOS.c src/thread-process/thread.c src/scheduling/fcfs.c src/scheduling/srtf.c src/scheduling/roundrobin.c src/scheduling/priority.c -Iinclude -o myOS -lreadline -lm -pthread
```

3. (Optional) Create Python virtualenv and install Python dependencies used by AI tools:

```
python3 -m venv venv
source venv/bin/activate
pip install --upgrade pip
# Example packages used by scripts: python-dotenv and Google generative AI client
pip install python-dotenv google-genai
```

4. Run the terminal:

```
./myOS
```

**Install & Run — Windows (Docker)**
1. Build the Docker image (project includes a Dockerfile that compiles `myOS`):

```
docker build -t myos_image .
```

2. Run the container interactively:

```
docker run -it myos_image
```

3. (Alternative) Use the example in [scripts/Docker-run.txt](scripts/Docker-run.txt#L1-L200) to mount a Windows folder into Ubuntu for iterative development.

**Usage Examples**
- Autocomplete: press `TAB` to see command suggestions.
- Run FCFS scheduler: `cpu fcfs`
- Ask AI to generate a shell command: `ai "find the largest C file and compile it"`
- Start GPT chat: `gpt` then type prompts, `exit` to leave.

**Notes & Tips**
- The project uses `./venv/bin/python` paths in many C modules to invoke helpers — when running natively, create and activate the `venv` as shown above.
- If AI scripts need API keys, add them to a `.env` file (see `chat-gpt.py`, `ai-agent.py`, `explain_code.py`) with a key named `api_key`.
- For development, keep `venv/` in `.gitignore` (already ignored).

**Contributing**
- Improve algorithms inside `src/scheduling/`, visualizers in `MM/`, `PRA/`, `DSA/` directories, or enhance AI helpers in the Python scripts in the repo root.

**License**
- This project is provided as-is for learning and experimentation. Add an appropriate license if you plan to publish.

---

If you'd like, I can:
- Add a `requirements.txt` with the observed Python dependencies,
- Add a small `run.sh` wrapper for Linux or a `docker-compose.yml` for development.
