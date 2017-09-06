from cs50 import get_float

print("O hai!", end='')
value = -1
monets = 25, 10, 5, 1

while value < 0 :
    print("How much change is owed?");
    value = round(get_float() * 100);

result = 0
for temp in monets :
    result += value//temp
    value %= temp
    
print(result)