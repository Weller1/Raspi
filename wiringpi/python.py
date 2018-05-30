from bs4 import BeautifulSoup
import requests
import time

while True:
    page_3 = requests.get("https://aikataulut.tampere.fi/?lang=&mobile=1&stop=3731&direction=1&showLines=3A%2C3B%2C3R")
    soup_3 = BeautifulSoup(page_3.content, 'html.parser')
    page_4 = requests.get("https://aikataulut.tampere.fi/?stop=3575&direction=1&showLines=4%2C4Y&lang=&key=&mobile=1")
    soup_4 = BeautifulSoup(page_4.content, 'html.parser')
    page_6 = requests.get("https://aikataulut.tampere.fi/?lang=&mobile=1&stop=3731&direction=1&showLines=6")
    soup_6 = BeautifulSoup(page_6.content, 'html.parser')

    with open('timetables3k.txt', 'a') as the_3_file:
        for i in range(3):
            the_3_file.write(soup_3.find_all('td', class_='timeColumn')[i].get_text() + " ")
    with open('timetables4k.txt', 'a') as the_4_file:
        for i in range(3):
            the_4_file.write(soup_4.find_all('td', class_='timeColumn')[i].get_text() + " ")
    with open('timetables6k.txt', 'a') as the_6_file:
        for i in range(3):
            the_6_file.write(soup_6.find_all('td', class_='timeColumn')[i].get_text() + " ")
    time.sleep(60)
    clear_3 = open('timetables3k.txt', 'w')
    clear_3.close()
    clear_4 = open('timetables4k.txt', 'w')
    clear_4.close()
    clear_6 = open('timetables6k.txt', 'w')
    clear_6.close()
