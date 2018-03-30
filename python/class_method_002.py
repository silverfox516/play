
class Person(object):
    def __init__(self, year, month, day, sex):
        self.year = year
        self.month = month
        self.day = day
        self.sex = sex

    def __str__(self):
        return 'I was born {} {} {} and {}'.format(self.year, self.month, self.day, self.sex)

    @classmethod
    def ssn_constructor(cls, ssn):
        front, back = ssn.split('-')
        sex = back[0]

        if sex == '1' or sex == '2':
            year = '19' + front[:2]
        else:
            year = '20' + front[:2]

        if (int(sex) % 2) == 0:
            sex = 'female'
        else:
            sex = 'male'

        month = front[2:4]
        day = front[4:6]

        return cls(year, month, day, sex)

    @staticmethod
    def is_work_day(day):
        if day.weekday() == 5 or day.weekday == 6:
            return False
        return True

def ssn_parser(ssn):
    front, back = ssn.split('-')
    sex = back[0]

    if sex == '1' or sex == '2':
        year = '19' + front[:2]
    else:
        year = '20' + front[:2]

    if (int(sex) % 2) == 0:
        sex = 'female'
    else:
        sex = 'male'

    month = front[2:4]
    day = front[4:6]

    return year, month, day, sex

ssn_1 = '900829-1034356'
ssn_2 = '051224-4061569'


print('{} {} {} {}'.format(*ssn_parser(ssn_1)))

person_1 = Person(*ssn_parser(ssn_1))
print(person_1)

person_2 = Person(*ssn_parser(ssn_2))
print(person_2)

person_3 = Person.ssn_constructor(ssn_1)
print(person_3)

person_4 = Person.ssn_constructor(ssn_2)
print(person_4)

import datetime

my_date = datetime.date(2018, 3, 31)

print(Person.is_work_day(my_date))
print(person_1.is_work_day(my_date))
