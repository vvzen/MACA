import requests
from bs4 import BeautifulSoup

url = "https://motivationping.com/quotes-perseverance-never-giving-up/"
document = requests.get(url).text
soup = BeautifulSoup(document, "html.parser")

for p in soup.find_all("p")[10:100]:
    print p.text.encode("utf-8")