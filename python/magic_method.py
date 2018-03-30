
class MyInt(int):
    def __add__(self, other):
        return '{} + {} = {}'.format(self.real, other, self.real + other.real)

    def __str__(self):
        return 'oh {}'.format(self.real)

my_num = MyInt(5)

print(my_num + 5)
print(my_num)

class Food(object):
    def __init__(self, name, price):
        self.name = name
        self.price = price

    def __lt__(self, other):
        if self.price < other.price:
            return True
        else:
            return False

    def __add__(self, other):
        return self.price + other.price

food_1 = Food('icecream', 3000)
food_2 = Food('hamburger', 5000)
food_3 = Food('coke', 2000)

print(food_1 < food_2)
print(food_2 < food_3)

print(food_1 + food_3)
