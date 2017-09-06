from cs50 import get_int

value = -1
while value < 0 or value > 23 :
    print("Height: ", end='')
    value = get_int()

index = 1
for temp in range(value):
    print((" " * (value - index)) + ("#" * index) + "  " + ("#" * index))
    index += 1