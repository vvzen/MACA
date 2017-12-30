import os
import re
import csv
import pprint

pp = pprint.PrettyPrinter(indent=4)

# idea 1
# see the words most used by artists on their website, artwork descriptions and bio

# hash table with the frequency score for each word
words_frequency_score = {}

current_dir = os.path.dirname(os.path.realpath(__file__))
text_sources_dir = os.path.join(current_dir, "text-sources")

# loop through all text sources
for text in os.listdir(text_sources_dir):
    # skip everything not formatted in a precise way
    if re.search(r"\w+.txt", text):
        # read file
        with open(os.path.join(text_sources_dir, text, mode="r")) as f:
            current_content = f.read()
        # tokenize text into words
        current_words = re.findall(r"\w+.txt", current_content)
        # lowerize all chars
        current_words = map(lambda w: w.lower(), current_words)

''' for word in current_words:
    
    if not words_frequency_score.has_key(word):
        words_frequency_score[word] = 1
    else:
        words_frequency_score[word] += 1
        
pp.pprint(words_frequency_score) '''