#!/usr/bin/python3

import urllib.request
import os
import sys
import time
import re
import csv
import curses
from bs4 import BeautifulSoup
import pandas as pd


class DaumStockCat:
    def __init__(self, tickers):
        self.stock_main_site = 'http://finance.daum.net/quote/index.daum?nil_profile=stockgnb&nil_menu=sise_top'
        self.stock_item_site = "http://finance.daum.net/item/main.daum?code="
        self.tickers = tickers

        os.environ['TZ'] = 'Asia/Seoul'
        time.tzset()

        self.time = time.localtime()

    def point_fetch(self):
        results = {}

        main_page = urllib.request.urlopen(self.stock_main_site).read().decode()
        main_soup = BeautifulSoup(main_page, 'html.parser')
        point_info = main_soup.find('div', class_='pointInfoBox')

        kospi_info = point_info.find('dl', class_='pointInfo kospi')
        kospi_point_sign = '-' if kospi_info.find('dd', class_='cDn') else '+'

        results['KOSPI'] = [ time.strftime('%X'),
                kospi_info.find('dd', class_='point').string,
                kospi_point_sign + kospi_info.find('span', class_='num').string ]

        kosdaq_info = point_info.find('dl', class_='pointInfo kosdaq')
        kosdaq_point_sign = '-' if kosdaq_info.find('dd', class_='cDn') else '+'

        results['KOSDAQ'] = [ time.strftime('%X'),
                kosdaq_info.find('dd', class_='point').string,
                kosdaq_point_sign + kosdaq_info.find('span', class_='num').string ]

        return results

    def tickers_fetch(self):
        results = {}

        for ticker in self.tickers:
            item_page = urllib.request.urlopen(self.stock_item_site + ticker).read().decode()

            soup = BeautifulSoup(item_page, 'html.parser')
            info = soup.find('ul', class_='list_stockrate')

#            item = soup.find('ul', class_='list_stockinfo').find('em', class_='screen_out').string
            item = ticker
            price = info.find('em', class_='curPrice').string
            rate = info.find('span', class_='rate').string

            results[item] = [ time.strftime('%X'), price, rate ]

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
        print('do debug')

def apply_color(val):
    color = 'black'

    try:
        if int(val) < 0:
            color = 'blue'
        elif int(val) > 0:
            color = 'red'
    except:
        print('Failed to eval %s', val)

    return 'color: %s' % color
    

if __name__ == '__main__':
    pd.set_option('display.width', pd.util.terminal.get_terminal_size()[0])
    try:
        default_tickers = [ '068270', '207940' ]
        force_always = True
        fetch_results = {}

        screen = curses.initscr()

        sc = DaumStockCat(default_tickers)

        while sc.is_stock_opened() or force_always:
            screen.clear()

            fetch_results.update(sc.point_fetch())
            fetch_results.update(sc.tickers_fetch())
            df = pd.DataFrame(data = fetch_results, index = [ 'time', 'price', 'rate' ])

            screen.addstr('%s\n' % df.T.to_string(header=False))

            screen.refresh()
            time.sleep(2)
    except:
        print('oop')

    curses.endwin()

