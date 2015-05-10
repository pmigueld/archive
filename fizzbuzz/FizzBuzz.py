multiple_of_3 = lambda n: n % 3 == 0
multiple_of_5 = lambda n: n % 5 == 0

for i in xrange(1, 100 + 1):
    output = ""

    if not multiple_of_3(i) and not multiple_of_5(i):
        output = i

    if multiple_of_3(i): output += "Fizz"
    if multiple_of_5(i): output += "Buzz"

    print output