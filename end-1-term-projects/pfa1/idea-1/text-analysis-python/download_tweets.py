#-*- coding: utf-8 -*-

# idea 1
# see the words most used by artists on twitter sto describe their generative artworks
# using https://twitter.com/search-advanced
# https://developer.twitter.com/en/docs/tweets/search/guides/standard-operators

import twitter
import os
import json
import pprint
import time

pp = pprint.PrettyPrinter(indent=4)

# load auth keys and authenticate app
with open("auth.json", mode="r") as f:
    auth = json.load(f)
api = twitter.Api(**auth)

target_hashtags = ["#generative", "#creativecoding"]

# 1. collect the most liked tweets about generative art and creative coding
# 2. see the most recurrent words inside those tweets

target_file_path = "popular_tweets.csv"

# save header of csv file
with open(target_file_path, mode="a") as fpt:
    fpt.write("tweet\tlikes\thashtags\n")

while True:

    print "asking twitter..."
    results = api.GetSearch(term=" ".join(target_hashtags), count=100)

    previous_text = ""

    for tweet in results:

        # skip duplicates
        if (previous_text != tweet.text):
        
            if tweet.favorite_count > 10:
                print "found a new popular one!"
                print "\tlikes: {}\n\t{}".format(tweet.favorite_count, tweet.text.encode("utf-8"))
                if len(tweet.hashtags) > 0:
                    print "\thashtags: {}".format([h.text for h in tweet.hashtags])
                with open(target_file_path, mode="a") as fpt:
                    file_text = "{}\t{}\t{}\n".format(tweet.text.encode("utf-8").replace("\n", ""), tweet.favorite_count, [str(h.text) for h in tweet.hashtags])
                    fpt.write(file_text)

        previous_text = tweet.text

    time.sleep(60 * 30) # seconds