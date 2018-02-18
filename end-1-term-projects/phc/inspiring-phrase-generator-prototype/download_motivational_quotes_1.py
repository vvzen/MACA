import requests
from bs4 import BeautifulSoup

url = "https://www.brainyquote.com/topics/motivational"

document = requests.get(url).text
soup = BeautifulSoup(document, "html.parser")

#for w in soup.find(id="quotesList").contents:
for w in soup.find_all("a"):
    
    try:
        #print w["class"]
        if "b-qt" in w["class"]:
            for content in w.contents:
                print content
    except KeyError:
        continue