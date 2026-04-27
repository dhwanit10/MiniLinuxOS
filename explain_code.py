from google import genai
from dotenv import load_dotenv
import sys
import os

load_dotenv()
gemini_api_key = os.getenv("api_key")

def agent():
    if len(sys.argv) < 2:
        print("Usage: explain <filename> [--short | --detailed]")
        return

    filename = sys.argv[1]
    mode = "short"  # default

    if len(sys.argv) >= 3:
        if sys.argv[2] == "--short":
            mode = "short"
        elif sys.argv[2] == "--detailed":
            mode = "detailed"

    if not os.path.exists(filename):
        print("File not found")
        return

    with open(filename, "r") as f:
        code = f.read()

    # Prevent very large input
    code = code[:8000]

    client = genai.Client(api_key=gemini_api_key)

    # Different prompts based on mode
    if mode == "short":
        prompt = f"""
Explain the following code briefly.

Rules:
- Keep it very short (4-5 lines max)
- Focus on what the code does overall
- No deep technical explanation

CODE:
{code}
"""
    else:
        prompt = f"""
Explain the following code in detail.

Rules:
- Beginner-friendly explanation
- Step-by-step breakdown
- Explain logic clearly
- Mention overall purpose

CODE:
{code}
"""

    response = client.models.generate_content(
        model="gemini-2.5-flash-lite",
        contents=prompt,
    )

    print(response.text.strip())

agent()