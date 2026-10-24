while True:
    print("1:add | 2:subtract | 3:multiply | 4: divide | 0:exit")
    try:
        z = int(input())
    except ValueError:
        print("please enter a number")
        continue
    if z == 0:
        break
    print("enter the 2 numbers")
    x = float(input("first number: "))
    y = float(input("second number: "))
    if z == 1:
        print(f"the answer is {x+y}")
    elif z == 2:
        print(f"the answer is {x-y}")
    elif z == 3:
        print(f"the answer is {x*y}")
    elif z == 4:
        if y == 0:
            print("cant divide by zero")
        else:
            print(f"the anwer is {x/y}")
    else:
        print("Invalid choice")