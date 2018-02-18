#*- coding: utf-8 *-

import random
import pprint
import serial
import time

pp = pprint.PrettyPrinter(indent=4)

# 1. Read the input text
# 2. Classify what are the words the appear after n word (n-gram)

class Markov:
    def __init__(self, order=2):
        self.order = order
        self.group_size = self.order + 1
        self.text = None # the training text
        self.graph = {}  # the actual model

    # @arg: filename, the path to the file for the training
    def train(self, filename):
        with open(filename) as f:
            self.text = f.read().split() # split
        #print "text:"
        #pp.pprint(self.text)
        
        # take the beginning of the text and attach it to the end
        # so that for every word we can have a following word
        self.text = self.text + self.text[:self.order]

        # for every word
        for i in range(0, len(self.text) - self.group_size):
            # the key is the ngram
            key = tuple(self.text[i : i + self.order])
            # the value is the word after the ngram
            value = self.text[i + self.order]

            # add the key:value to our graph
            if key in self.graph:
                self.graph[key].append(value)
            else:
                self.graph[key] = [value]

        # print "-"*60
        # print "generated graph:"
        # print "-"*60
        # pp.pprint(self.graph)

    # @arg: length of the text to generate
    def generate(self, length):
        # start with a random ngram
        index = random.randint(0, len(self.text) - self.order)
        first_ngram = self.text[index : index + self.order]
        result = first_ngram[:]

        #print "-"*60
        #print "first ngram is {}".format(result)
        #print "-"*60

        for i in range(length):
            # that the last ngram from the result
            # this is our current state
            #state = tuple(result[len(result) - self.order])
            state = tuple(result[i:])
            
            #print "result[0] : {}, result[1]: {}".format(result[0], result[1])
            #print "state is : {}".format(state)
            #print "the next word could be: "
            
            # pick a random word to follow
            try:
                next_word = random.choice(self.graph[state])
                result.append(next_word)
            except KeyError:
                continue

        #first_ngram = " ".join(first_ngram)[0].upper() + " ".join(first_ngram)[1:]
        
        generated_words = " ".join(result[self.order : ])
        generated_words = generated_words.replace(". ", ".,\n")
        generated_words = generated_words.replace(",.", ",")
        generated_words = generated_words.replace(".,", ".")
        #generated_words = generated_words.replace(". ", ".\n")
        #generated_words = generated_words.replace(" ", ",")
        generated_words = generated_words[0].upper() + generated_words[1:]

        return "{words}.".format(words=generated_words)
    