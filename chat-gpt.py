from google import genai
import sys


def agent():

    client = genai.Client(api_key="api-key")

    prompt = sys.argv[1]

# model = genai.GenerativeModel("gemini-1.5-flash")

# response = model.generate_content(
#     "Generate only code without explanation:\n" + prompt
# )

    response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents="Give answer in 1-2 line\n" + prompt,
    )

    print(response.text)

agent()

