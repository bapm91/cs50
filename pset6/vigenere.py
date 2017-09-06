import cs50
import sys

if len(sys.argv) != 2:
    print("Usage: python vigenere.py k")
    sys.exit(1)

key = sys.argv[1]
   
for i in range(len(key)):
    if not key[i].isalpha():
        print("Usage: python vigenere.py k")
        sys.exit(1)

key = key.upper()
print("plaintext: ",end = "")
p = cs50.get_string()
print("ciphertext: ",end = "")

index = 0
for i in range(len(p)):
   if index == len(key):
       index = 0
   if not p[i].isalpha():
       print("{}".format(p[i]),end = "")
       continue
   num = ord(key[index]) - 65
   if p[i].isupper():
       print("{}".format(chr(((ord(p[i]) - 65 + num) % 26) + 65)),end = "")
   else:
       print("{}".format(chr(((ord(p[i]) - 97 + num) % 26) + 97)),end = "")
   index += 1
print("")