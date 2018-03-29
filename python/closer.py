
def outer_func(tag):
    tag = tag

    def inner_func(txt):
        print '<{0}>{1}<{0}>'.format(tag, txt)

    return inner_func

my_func = outer_func('my')

print my_func
print
print dir(my_func)
print
print type(my_func.__closure__)
print
print my_func.__closure__
print
print my_func.__closure__[0]
print
print dir(my_func.__closure__[0])
print
print my_func.__closure__[0].cell_contents
print

print '-' * 80

h1_func = outer_func('h1')
p_func = outer_func('p')

h1_func('hello')
p_func('world')
