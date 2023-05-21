import Levenshtein
import sys
from fuzzywuzzy import fuzz

correct_answer = sys.argv[1]
user_answer = sys.argv[2]

similarity_ratio = fuzz.ratio(correct_answer.lower(), user_answer.lower())
if similarity_ratio <= 35:
    print(f"Remarks: Very poor ({similarity_ratio}%)")
elif similarity_ratio >= 36 and similarity_ratio <= 50:
    print(f"Remarks: Ok ({similarity_ratio}%)")
elif similarity_ratio >= 50:
    print(f"Remarks: Great ({similarity_ratio}%)")
# {"role": "user", "content": f"correct answer: {sys.argv[1]}\nmy answer: {sys.argv[2]}\n give me a short response whether my answer matches the correct one or not."}
