#!/usr/bin/python3

import urllib.request
import os
import sys
import time
import re
import csv
import curses
from bs4 import BeautifulSoup

class DaumStockCat:
    def __init__(self, tickers):
        self.stock_main_site = 'http://finance.daum.net/quote/index.daum?nil_profile=stockgnb&nil_menu=sise_top'
        self.stock_item_site = "http://finance.daum.net/item/main.daum?code="
        self.tickers = tickers

        os.environ['TZ'] = 'Asia/Seoul'
        time.tzset()

        self.time = time.localtime()

    def point_fetch(self):
        results = []

        main_page = urllib.request.urlopen(self.stock_main_site).read().decode()
        main_soup = BeautifulSoup(main_page, 'html.parser')
        point_info = main_soup.find('div', class_='pointInfoBox')

        kospi_info = point_info.find('dl', class_='pointInfo kospi')
        kospi_point_sign = '-' if kospi_info.find('dd', class_='cDn') else '+'
        results.append('%s, KOSPI, %s, %s%s' % (time.ctime(),
            kospi_info.find('dd', class_='point').string,
            kospi_point_sign, kospi_info.find('span', class_='num').string))

        kosdaq_info = point_info.find('dl', class_='pointInfo kosdaq')
        kosdaq_point_sign = '-' if kosdaq_info.find('dd', class_='cDn') else '+'
        results.append('%s, KOSDAQ, %s, %s%s' % (time.ctime(),
            kosdaq_info.find('dd', class_='point').string,
            kosdaq_point_sign, kosdaq_info.find('span', class_='num').string))

        return results

    def tickers_fetch(self):
        results = []

        for ticker in self.tickers:
            item_page = urllib.request.urlopen(self.stock_item_site + ticker).read().decode()

            soup = BeautifulSoup(item_page, 'html.parser')
            info = soup.find('ul', class_='list_stockrate')

            price = info.find('em', class_='curPrice').string
            rate = info.find('span', class_='rate').string

            results.append('%s, %s, %s, %s' % (time.ctime(), ticker, price, rate))

        return results

    def is_stock_opened(self):
        if self.time.tm_hour < 9:
            return False

        if self.time.tm_hour < 15:
            return True
        elif self.time.tm_hour == 15: 
            if self.time.tm_min < 30:
                return True

        return False

    def debug(self):
        for ticker in self.tickers:
            item_page = urllib.request.urlopen(self.stock_item_site + ticker).read().decode()
            print(item_page)
            k = re.search('class="curPrice(.*?)">(.*?)<', item_page)
            r = re.search('class="rate (.*?)?>(.*?)<', item_page)

if __name__ == "__main__":
    try:
        default_tickers = [ "068270", "207940" ]

        screen = curses.initscr()

        sc = DaumStockCat(default_tickers)

        force_always = False

        while sc.is_stock_opened() or force_always:
            screen.clear()

            for result in sc.point_fetch():
                screen.addstr('%s\n' % result)

            for result in sc.tickers_fetch():
                screen.addstr('%s\n' % result)

            screen.refresh()
            time.sleep(1)
    except:
        print('oop')

    curses.endwin()

