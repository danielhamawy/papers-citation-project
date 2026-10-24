import random
number = random.randint(1,10)
tries = 0
guess = int(input("please enter a number between 1 and 10: "))
tries += 1
while guess != number :
    tries += 1
    if guess<number:
        guess=int(input("Your guess is lower than the number, enter another number: "))
    else:
        guess=int(input("Your guess is higher than the number, enter another number: "))
print(f"correct you guessed right, after {tries} tries")