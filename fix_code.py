from google import genai
from dotenv import load_dotenv
import shutil
import sys
import os

load_dotenv()
gemini_api_key = os.getenv("api_key")

def agent():
    if len(sys.argv) < 3:
        print("Usage: fix_code.py <filename> <--auto | --manual>")
        return

    filename = sys.argv[1]
    mode = sys.argv[2]

    if not os.path.exists(filename):
        print("File not found")
        return

    with open(filename, "r") as f:
        code = f.read()

    # limit size (important)
    code = code[:8000]

    client = genai.Client(api_key=gemini_api_key)

    if mode == "--auto":
        system_prompt = f"""
You are an expert programmer.

Fix the following code.

Rules:
- Return ONLY the corrected code
- NO explanation
- NO markdown
- Keep original logic intact
- Ensure code is runnable and error-free

CODE:
{code}
"""
    else:  # --manual
        system_prompt = f"""
You are an expert programmer.

Analyze the following code.

Return in EXACT format:

PROBLEM:
<what is wrong>

FIX:
<how to fix it>

FIXED CODE:
<corrected code>

Rules:
- Keep explanation simple
- No markdown
- Be clear and structured

CODE:
{code}
"""

    response = client.models.generate_content(
        model="gemini-2.5-flash-lite",
        contents=system_prompt,
    )

    output = response.text.strip()

    if mode == "--auto":
        shutil.copy(filename, filename + ".bak")

    # AUTO MODE → overwrite file
    if mode == "--auto":
        with open(filename, "w") as f:
            f.write(output)

        print(f"Code fixed and saved to {filename}")

    else:
        print(output)


agent()