#!/usr/bin/python3

import urllib.request
import os
import sys
import time
import re
import csv
import curses

class StockCat:
    def __init__(self, stock_site, tickers):
        self.stock_site = stock_site
        self.tickers = tickers

        os.environ['TZ'] = 'Asia/Seoul'
        time.tzset()

        self.time = time.localtime()

    def fetch(self):
        results = []
        for ticker in self.tickers:
            item_page = urllib.request.urlopen(self.stock_site + ticker).read().decode()

            k = re.search('class="curPrice(.*?)">(.*?)<', item_page)
            r = re.search('class="rate (.*?)?>(.*?)<', item_page)

            price = k.group(2)
            rate = r.group(2)

            results.append((time.ctime(), price, rate))

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
            item_page = urllib.request.urlopen(self.stock_site + ticker).read().decode()
            print(item_page)
            k = re.search('class="curPrice(.*?)">(.*?)<', item_page)
            r = re.search('class="rate (.*?)?>(.*?)<', item_page)

if __name__ == "__main__":
    try:
        default_stock_site = "http://finance.daum.net/item/main.daum?code="
        default_tickers = [ "068270", "207940" ]

        screen = curses.initscr()

        sc = StockCat(default_stock_site, default_tickers)

        force_always = True

        while sc.is_stock_opened() or force_always:
            screen.clear()
            for result in sc.fetch():
                screen.addstr("%s, %s, %s\n" % result)
            screen.refresh()
            time.sleep(1)
    except:
        print("oops")

    curses.endwin()

