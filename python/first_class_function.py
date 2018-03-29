def square(x):
    return x * x

def cube(x):
    return x * x * x

def quad(x):
    return x * x * x * x

def my_map(func, arg_list):
    results = []

    for arg in arg_list:
        results.append(func(arg))

    return results

num_list = [ 1, 2, 3, 4, 5 ]

squares = my_map(square, num_list)
qubes = my_map(cube, num_list)
quads = my_map(quad, num_list)

print squares
print qubes
print quads

print '-' * 80

def logger(msg):

    def log_message():
        print 'Log: ', msg

    return log_message

log_hi = logger('Hi')
log_hi()

del logger

try:
    print logger
except NameError:
    print 'NameError: logger is not exist'

log_hi()

print '-' * 80

def simple_html_tag(tag, msg):
    print '<{0}>{1}<{0}>'.format(tag, msg)

simple_html_tag('h1', 'simple html tag')

print '-' * 80

def html_tag(tag):

    def wrap_text(msg):
        print '<{0}>{1}<{0}>'.format(tag, msg)

    return wrap_text

print_h1 = html_tag('h1')
print_h2 = html_tag('h2')
print_h3 = html_tag('h3')

print_h1("hello")
print_h2("my name is")
print_h3("simpson")

