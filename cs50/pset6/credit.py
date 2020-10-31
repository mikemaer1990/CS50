# training wheels
from cs50 import get_string

# variable declarations
# stripping any whitespace at the beginning or end
cc = get_string("Enter your credit card number: ").strip()
# variables for luhns algorithm
multSum = addSum = luhnsTotal = 0
# variables for length and first / first two digits of card for card type detection
length, first, firstTwo = len(cc), int(cc[0]), int(cc[0] + cc[1])

# initial for loop for the multiplication part of luhns
for i in range((len(cc) - 2), -1, -2):
    # multiple every other digit by 2 starting with second to last
    digit = (int(cc[i]) * 2)
    # check if the result is more than one digit long
    isMultiDigit = len(str(abs(digit)))
    # if more than one digit long -> add the two digits together -> add that to our multSum
    if(isMultiDigit == 2):
        digit = int(str(digit)[0]) + int(str(digit)[1])
        multSum += digit
    # otherwise just add the result to the sum
    else:
        multSum += digit

# simpler for loop to add up the non multiplied numbers
for j in range(len(cc) - 1, -1, -2):
        addSum += int(cc[j])

# add both totals together
luhnsTotal = multSum + addSum

# check which card type it is based on length and first one or two digits
if (luhnsTotal % 10) == 0:
    if (firstTwo == 34 or firstTwo == 37) and length == 15:
        print("AMEX")
    elif first == 4 and (length == 13 or length == 16):
        print("VISA")
    elif (firstTwo == 51 or firstTwo == 52 or firstTwo == 53 or firstTwo == 54 or firstTwo == 55) and length == 16:
        print("MASTERCARD")
    # if no digit / length combo matches print invalid
    else:
        print("INVALID")
# if fails luhns test print invalid
else:
    print("INVALID")
