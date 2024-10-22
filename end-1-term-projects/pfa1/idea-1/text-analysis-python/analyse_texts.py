#-*- coding: utf-8 -*-
import os
import re
import json
import csv
import pprint

pp = pprint.PrettyPrinter(indent=4)

# idea 1
# see the words most used by artists on their website, artwork descriptions and bio

# hash table with the frequency score for each word
words_frequency_score = {}
# sorted list of dictionaries
words_frequency_score_sorted = []

# paths
current_dir = os.path.dirname(os.path.realpath(__file__))
text_sources_dir = os.path.join(current_dir, "text-sources")
destination_dir = os.path.join(current_dir, "..", "generative_bot_stx_pfa1", "bin", "data")
# destination_dir = "your/path/here"

# list of english prepositions, used to filter words
with open(os.path.join(current_dir, "words-data", "prepositions.json"), mode="r") as fp:
    prepositions = json.load(fp)
    prepositions = [p.encode("utf-8") for p in prepositions["prepositions"]]

# other stopwords useful for filtering (conjuctions, etc..)
with open(os.path.join(current_dir, "words-data", "en_stopwords.json"), mode="r") as fp:
    stop_words = json.load(fp)
    stop_words = [p.encode("utf-8") for p in stop_words["stopWords"]]

print "-"*60
# loop through all text sources
for text in os.listdir(text_sources_dir):
    # skip everything not formatted in a precise way
    if re.search(r"\w+.txt", text):
        
        # read current text file
        with open(os.path.join(text_sources_dir, text), mode="r") as f:
            current_content = f.read()
        
        print "searching words in current text: {}".format(text)

        # print current_content[:100]

        # tokenize text into words
        # regex is used to get words without digits in them
        current_words = re.findall(r"[^\d\W]\w+", current_content)
        # lowerize all chars
        current_words = map(lambda w: w.lower(), current_words)

        # loop into words and keep track of scores
        for word in current_words:
            if word not in prepositions and word not in stop_words:
                if not words_frequency_score.has_key(word):
                    words_frequency_score[word] = 1
                else:
                    words_frequency_score[word] += 1
print "-"*60
print "{} words collected!".format(len(words_frequency_score.keys()))

# sort words by score
sorted_words = sorted(words_frequency_score, key=words_frequency_score.get, reverse=True)
most_frequent_word = sorted_words[0]
print "most frequent word: {}".format(most_frequent_word)
for w in sorted_words:
    #   print "\t{} : {}".format(w, words_frequency_score[w])
    words_frequency_score_sorted.append({
        "word" : w,
        "score" : words_frequency_score[w]
    })
print "TOP 20:"
print "\t{}".format("\n\t".join(sorted_words[:20]))

# save hash table
print "-"*60
print "saving data to {}".format(os.path.join(destination_dir, "words_frequency_score.json"))

# create destination path if doesn't exist
if not os.path.exists(destination_dir):
    os.makedirs(destination_dir, 0755)

with open(os.path.join(destination_dir, "words_frequency_score.json"), mode="w") as wf:
    json.dump(words_frequency_score_sorted, wf, encoding='utf-8')

print "-"*60