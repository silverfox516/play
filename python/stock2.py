#!/usr/bin/python3

import requests
import lxml.html as lh
from lxml import etree
#import pandas as pd

if __name__ == "__main__":
    default_stock_site = "http://finance.daum.net/item/quote.daum?code="
    default_tickers = [ "068270" ]

    for ticker in default_tickers:
        page = requests.get(default_stock_site + ticker)
        doc = lh.fromstring(page.content)

        element = doc.xpath("//div[@id='price5StepBody']/parent::*")
        print(element.text)
