multiple_of_3 = (x) -> x % 3 == 0
multiple_of_5 = (x) -> x % 5 == 0

for x in [1..100]
    output = ""

    if not multiple_of_3(x) and not multiple_of_5(x)
        output = x

    output += "Fizz" if multiple_of_3(x)
    output += "Buzz" if multiple_of_5(x)

    console.log output + "\n"