
import sys

class Employee(object):

    raise_amount = 1.1

    def __init__(self, first, last, pay):
        self.first = first
        self.last = last
        self.pay = pay
        self.email = first.lower() + '.' + last.lower() + '@schoolweb.net'

    def apply_raise(self):
        self.pay = int(self.pay * self.raise_amount)

    def full_name(self):
        return '{} {}'.format(self.first, self.last)

    def get_pay(self):
        return '{} : {} '.format(self.full_name(), self.pay)

    @classmethod
    def change_raise_amount(cls, amount):
        while amount < 1:
            print('amount cannot less than 1')
            amount = input('input raise mount\n=>')
            amount = float(amount)
            cls.raise_amount = amount
            print('applied raise amount {}'.format(amount))

emp_1 = Employee('Sanghee', 'Lee', 50000)
emp_2 = Employee('Minjung', 'Kim', 60000)

print(emp_1.get_pay())
print(emp_2.get_pay())

Employee.change_raise_amount(0.9)

emp_1.apply_raise()
emp_2.apply_raise()

print(emp_1.get_pay())
print(emp_2.get_pay())

