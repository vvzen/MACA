# set working directory
setwd("/Users/valerioviperino/Documents/MACA/end-1-term-projects/pfa1/idea-1/twitter-python")

# Load qdap
# install.packages("qdap") if is not installed
library(qdap)

tweets <- read.csv("popular_tweets.csv", sep="\t", stringsAsFactors=FALSE)
# Print new_text to the console

print(tweets$tweet)

# Find the 10 most frequent terms: term_count
tweets_term_count = freq_terms(tweets$tweet, 4)
hashtags_term_count = freq_terms(tweets$hashtags, 4)

# Plot term_count
plot(tweets_term_count)

# STEP 2
"
Your next step is to convert this vector containing the text data to a corpus.
As you\'ve learned in the video, a corpus is a collection of documents,
but it\'s also important to know that in the tm domain, R recognizes it as a data type.
There are two kinds of the corpus data type, the permanent corpus, PCorpus, and the volatile corpus, VCorpus.
In essence, the difference between the two has to do with how the collection of documents is stored in your computer.
# In this course, we will use the volatile corpus, which is held in your computer\'s RAM rather than saved to disk, just to be more memory efficient.
To make a volatile corpus, R needs to interpret each element in our vector of text, coffee_tweets, as a document.
And the tm package provides what are called Source functions to do just that!
In this exercise, we\'ll use a Source function called VectorSource() because our text data is contained in a vector.
The output of this function is called a Source object. Give it a shot!
"

# Load tm
install.packages("tm")
library("tm")

# Make a vector source: coffee_source
tweets_source <- VectorSource(tweets$tweet)

"Now that we\'ve converted our vector to a Source object, we pass it to another tm function, VCorpus(), to create our volatile corpus.
The VCorpus object is a nested list, or list of lists. At each index of the VCorpus object,
there is a PlainTextDocument object, which is essentially a list that contains the actual text data (content),
as well as some corresponding metadata (meta). It can help to visualize a VCorpus object to conceptualize the whole thing
"

# Make a volatile corpus: tweets_corpus
tweets_corpus <- VCorpus(tweets_source)

# Print data on the 4th tweet in tweets_corpus
print(tweets_corpus[4])

# Print the content of the 5 tweet in tweets_corpus
print(tweets_corpus[[4]]$content)