from bs4 import BeautifulSoup
import requests
import time

while True:
    page = requests.get("https://aikataulut.tampere.fi/?stop=3575&direction=1&showLines=4%2C4Y&lang=&key=&mobile=1")
    soup = BeautifulSoup(page.content, 'html.parser')
    with open('timetables.txt', 'a') as the_file:
        for i in range(3):
            the_file.write(soup.find_all('td', class_='timeColumn')[i].get_text() + "\n")
            print(soup.find_all('td', class_='timeColumn')[i].get_text())
    time.sleep(60)
    f = open('timetables.txt', 'w')
    f.close()
