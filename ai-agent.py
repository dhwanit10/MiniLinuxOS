from google import genai
import sys

# genai.configure(api_key="AIzaSyBOKlLxXZroXjJO43SNf1-1hYFOtN_wm9Q")

def agent():

    client = genai.Client(api_key="AIzaSyBOKlLxXZroXjJO43SNf1-1hYFOtN_wm9Q")

    prompt = sys.argv[1]

# model = genai.GenerativeModel("gemini-1.5-flash")

# response = model.generate_content(
#     "Generate only code without explanation:\n" + prompt
# )

    response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents="Generate only code without explanation:\n" + prompt,
    )

    print(response.text)

agent()