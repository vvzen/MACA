import requests
import time
from bs4 import BeautifulSoup

url = "http://www.fortunecookiemessage.com/"

while True:
    document = requests.get(url).text
    soup = BeautifulSoup(document, "html.parser")
    for p in soup.select("div#message > div > a > p"):
        with open("fortune_cookies.txt", mode="a") as f:
            f.write("{}\n".format(p.text).encode("utf-8"))
    time.sleep(1.5)