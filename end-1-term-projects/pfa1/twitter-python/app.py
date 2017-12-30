import twitter
import os
import json
import pprint

pp = pprint.PrettyPrinter(indent=4)

with open("auth.json", mode="r") as f:
    auth = json.load(f)

api = twitter.Api(**auth)

results = api.GetSearch(term="generative art", count=100)

for tweet in results:
    print tweet.text