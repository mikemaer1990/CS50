from cs50 import get_int
# initialize height variable
height = 0
# receive input from user until its a number between 1-8
while height <= 0 or height > 8:
    height = get_int("Height: ")
    # printing function
for i in range(height):
    print(" " * (height - (i+1)), end = "")
    print("#" * (i + 1))
