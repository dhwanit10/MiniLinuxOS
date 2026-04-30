from google import genai
from dotenv import load_dotenv
import sys
import os

load_dotenv()
gemini_api_key = os.getenv("api_key")

def agent():
    client = genai.Client(api_key=gemini_api_key)

    prompt = sys.argv[1]

    system_prompt = f"""
You are a Linux command generator.

Your task is to convert natural language into a valid Linux shell command.
generate commands on user input, your understanding, and user context. 

STRICT RULES (MUST FOLLOW):
- Output ONLY the command
- NO explanations, NO extra text, NO markdown
- Do NOT output partial words
- Do NOT output English sentences
- ALWAYS return a COMPLETE and executable command
- If unsure, return: echo "Command not found"

INTERPRETATION RULES:
- "list files", "show files", "list all files" → ls
- "list all files including hidden" → ls -a
- "current directory" → pwd
- "show all processes" → ps aux
- "kill process <pid>" → kill <pid>
- "make directory test" → mkdir test
- "delete file test.txt" → rm test.txt
- "delete all txt files" → rm *.txt
- "git status" → git status
- "what is my git status" → git status
- "add all files to git" → git add .
- "commit changes" → git commit -m "message"
- "push code" → git push
- "compile c file main.c" → gcc main.c
- "run program" → ./a.out

SAFETY:
- DO NOT generate dangerous system-wide destructive commands like:
  rm -rf /
- For delete operations, restrict to user-level scope (e.g., rm *.txt)

EXAMPLES:

Input: list all files  
Output: ls  

Input: what is my git status  
Output: git status  

Input: show all processes  
Output: ps aux  

Input: delete all txt files  
Output: rm *.txt  

Input: create folder test  
Output: mkdir test  

Input: compile main.c  
Output: gcc main.c  

Input: run program  
Output: ./a.out  

Now convert this input into a command:

Input: {prompt}
"""

    response = client.models.generate_content(
        model="gemini-2.5-flash-lite",
        contents=system_prompt,
    )

    print(response.text.strip())

agent()