#!/usr/bin/python

import random

class Machine:
    def insertCoin(self, c):
        print('Machine: inserted coin %d' %(c))
        self.c = c
        self.pay = 0

    def stoppedItem(self):
        return random.randint(0, 7)

    def run(self):
        items = [self.stoppedItem(), self.stoppedItem(), self.stoppedItem()]

        print('Machine: hit %d, %d, %d' % tuple(items))
        for i in items:
            if items.count(i) == 3:
                if i == 7:
                    self.pay = self.c * 10
                else:
                    self.pay = self.c * 5
                print('Machin: 3 numbers match, break')
                break
            elif items.count(i) == 2:
                if i == 7:
                    self.pay = self.c * 2
                else:
                    self.pay = self.c
                print('Machin: 2 numbers match, break')
                break
            else:
                self.pay = 0

    def payCoin(self):
        print('Machine: pay %d' % (self.pay))
        p = self.pay
        self.pay = 0
        self.coin = 0
        return p


class Player:
    def __init__(self, init_coin = 1000):
        print('Player: new with coin %d' % (init_coin))
        self.coin = init_coin

    def setCoin(self, c):
        print('Player: set coin %d' % (c))
        self.coin = c

    def pushCoin(self, c):
        print('Player: push coin %d' % (c))
        self.coin = self.coin + c

    def popCoin(self, c):
        if c < self.coin:
            self.coin = self.coin - c
            print('Player: pop coin %d remains %d' % (c, self.coin))
            return c

        c = self.coin
        self.coin = 0
        print('Player: pop coin %d remains %d' % (c, self.coin))
        return c

    def coinHas(self):
        return self.coin


if __name__ == '__main__':
    machine = Machine()
    player = Player(1000)

    while True:
        i = input('input coin to bet:')
        if i == 0:
            break

        if player.coinHas() <= 0:
            print('no coin, re?')
            r = input()
            if r == 'r':
                player.setCoin(1000)
                continue

        c = int(i)
        machine.insertCoin(player.popCoin(c))
        machine.run()
        player.pushCoin(machine.payCoin())
        print('player has coin %s' % (player.coinHas()))
