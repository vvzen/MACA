import os
import json
import csv

with open(os.path.join(".", "encouraging_words.json"), "r") as fr:
    json_file = json.load(fr)

print "json description: {}".format(json_file["description"])

encouraging_words = json_file["encouraging_words"]
print "encouraging words: {}\n".format(",".join(encouraging_words))

with open("encouraging_words.csv", "w") as fw:
    words_csv = csv.writer(fw, delimiter=",")
    for i, word in enumerate(encouraging_words):
        words_csv.writerow([i, word])