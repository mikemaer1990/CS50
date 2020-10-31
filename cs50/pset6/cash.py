# import get_float function
from cs50 import get_float
# initialize change and coincount variable
change = 0
coinCount = 0

# receive input from user until it is a positive number
while change <= 0:
    change = get_float("Change: ")
    # convert to a full number
    cents = round(change * 100)
# loop until no change remains
while cents != 0:
    # if quarter
    if (cents - 25) >= 0:
        coinCount += 1
        cents -= 25
    # if dime
    elif (cents - 10) >= 0:
        coinCount +=1
        cents -= 10
    # if nickel
    elif (cents - 5) >= 0:
        coinCount +=1
        cents -= 5
    # if penny
    else:
        coinCount += 1
        cents -= 1
# print results!
print(f"Greedy Result: {coinCount}")