
def square_numbers(nums):
    for i in nums:
        yield i * i

my_nums = square_numbers([1, 2, 3, 4, 5])

print next(my_nums)
print next(my_nums)
print next(my_nums)

print '_' * 80

for num in my_nums:
    print num

print '_' * 80

my_nums = [x * x for x in [1, 2, 3, 4, 5]]
print my_nums
for num in my_nums:
    print num

print '_' * 80

my_nums = (x * x for x in [1, 2, 3, 4, 5])
print my_nums
for num in my_nums:
    print num

print '_' * 80

my_nums = (x * x for x in [1, 2, 3, 4, 5])
print list(my_nums)

print '_' * 80

import os
import psutil
import random
import time
import psutil

names = [ 'yhchoi', 'gjji', 'yyjin', 'shkim', 'shoh', 'mwkim' ]
majors = [ 'computer', 'korean', 'english', 'math', 'politics' ]

process = psutil.Process(os.getpid())
mem_before = process.memory_info().rss / 1024 / 1024

def people_list(num_people):
    result = []
    for i in xrange(num_people):
        person = {
                'id' : i,
                'name' : random.choice(names),
                'major' : random.choice(majors)
                }
        result.append(person)
    return result

def people_generator(num_people):
    for i in xrange(num_people):
        person = {
                'id' : i,
                'name' : random.choice(names),
                'major' : random.choice(majors)
                }
        yield person

t1 = time.clock()
people = people_list(1000000)
t2 = time.clock()
mem_after = process.memory_info().rss / 1024 / 1024
total_time = t2 - t1

print 'before {} MB'.format(mem_before)
print 'after {} MB'.format(mem_after)
print 'total {:.6f} sec'.format(total_time)

t1 = time.clock()
people = people_generator(1000000)
t2 = time.clock()
mem_after = process.memory_info().rss / 1024 / 1024
total_time = t2 - t1

print 'before {} MB'.format(mem_before)
print 'after {} MB'.format(mem_after)
print 'total {:.6f} sec'.format(total_time)

