
class DecoratorClass:
    def __init__(self, original_function):
        self.original_function = original_function

    def __call__(self, *args, **kwargs):
        print "C before ", self.original_function.__name__
        return self.original_function(*args, **kwargs)

def decorator_function(original_function):
    def wrapper_function(*args, **kwargs):
        print "F before ", original_function.__name__
        return original_function(*args, **kwargs)

    return wrapper_function

@DecoratorClass
def display1():
    print "display1()"

@DecoratorClass
def display2(name, age):
    print "display2({}, {})".format(name, age)

#deco_display1 = decorator_function(display1)
#deco_display2 = decorator_function(display2)

display1()
display2("song", 38)

print '-' * 80

import datetime
import time
import sys
from functools import wraps

def my_logger(original_function):
    import logging
    logging.basicConfig(stream=sys.stdout, level=logging.INFO)

    @wraps(original_function)
    def wrapper(*args, **kwargs):
        print "my_logger.wrapper() ", original_function.__name__
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
        logging.info('[{}] result args - {}, kwargs {}'.format(timestamp, args, kwargs))
        return original_function(*args, **kwargs)

    return wrapper

def my_timer(original_function):
    import logging
    logging.basicConfig(stream=sys.stdout, level=logging.INFO)

    @wraps(original_function)
    def wrapper(*args, **kwargs):
        print "my_timer.wrapper() ", original_function.__name__
        t1 = time.time()
        result = original_function(*args, **kwargs)
        t2 = time.time() - t1
        logging.info('time {}'.format(t2))
        return result

    return wrapper

@my_logger
@my_timer
def display_info(name, age):
    time.sleep(1)
    print 'display_info({}, {})'.format(name, age)

display_info("lee", 36)

