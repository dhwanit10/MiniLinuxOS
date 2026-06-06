from google import genai
from dotenv import load_dotenv
import sys
import os
import subprocess

load_dotenv()
gemini_api_key = os.getenv("api_key")

def get_extension(lang):
    lang = lang.lower()
    if "c++" in lang or "cpp" in lang:
        return "cpp"
    elif "c#" in lang or "csharp" in lang or "cs" in lang:
        return "cs"
    elif lang == "c":
        return "c"
    elif "go" in lang:
        return "go"
    elif "java" in lang:
        return "java"
    elif "python" in lang:
        return "py"
    elif "javascript" in lang:
        return "js"
    else:
        return "txt"

def agent():
    client = genai.Client(api_key=gemini_api_key)

    prompt = sys.argv[1]

    system_prompt = f"""
You are a coding assistant.

Return output in EXACT format:

LANGUAGE: <language>
CODE:
<only code here>

Rules:
- No explanation
- No markdown
- Detect correct programming language

User request:
{prompt}
"""

    response = client.models.generate_content(
        model="gemini-2.5-flash",
        contents=system_prompt,
    )

    output = response.text.strip()

    # Parse response
    lines = output.splitlines()
    language = "txt"
    code = []
    is_code = False

    for line in lines:
        if line.startswith("LANGUAGE:"):
            language = line.replace("LANGUAGE:", "").strip()
        elif line.startswith("CODE:"):
            is_code = True
            continue
        elif is_code:
            code.append(line)

    code_str = "\n".join(code)

    # Decide filename
    ext = get_extension(language)
    filename = f"generated.{ext}"

    # Save file
    with open(filename, "w") as f:
        f.write(code_str)

    # Copy to clipboard (Ubuntu)
    try:
        subprocess.run(["xclip", "-selection", "clipboard"], input=code_str.encode())
        clipboard_status = "Copied to clipboard"
    except Exception:
        clipboard_status = "Clipboard failed (install xclip)"

    print(f"Saved as: {filename}")
    print(clipboard_status)

agent()