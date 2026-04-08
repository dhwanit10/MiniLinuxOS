from google import genai
from dotenv import load_dotenv
import sys
import os

# Load the .env file
load_dotenv()

# Fetch the API key
gemini_api_key = os.getenv("api_key")

def agent():

    client = genai.Client(api_key=gemini_api_key)

    prompt = sys.argv[1]

# model = genai.GenerativeModel("gemini-1.5-flash")

# response = model.generate_content(
#     "Generate only code without explanation:\n" + prompt
# )

    response = client.models.generate_content(
        model="gemini-3.1-flash-lite-preview",
        contents="Generate only code without explanation:\n" + prompt,
    )

    print(response.text)

agent()

