import random
import string

def randomString(stringLength=10):
    letters = string.ascii_uppercase
    return ''.join(random.choice(letters) for i in range(stringLength))

#Use for concurrency check
print("OPEN ACCOUNT ", randomString())
print("OPEN ACCOUNT ", randomString())
print("OPEN ACCOUNT ", randomString())

#Use for closing only along with one of the above
print("OPEN ACCOUNT ", randomString())
print("OPEN ACCOUNT ", randomString())

for i in range(0, 1000):
    j = random.randint(1, 10)
    if(j == 1):
        print("OPEN ACCOUNT", randomString())
    elif(j == 2):
        print("WITHDRAW", random.randint(100,104), random.randint(100, 100000)/100)
    elif(j == 3):
        print("DEPOSIT", random.randint(100,104), random.randint(100, 100000)/100)
    elif(j == 4):
        print("SHOW ACCOUNT BALANCE", random.randint(100, 104))
    elif(j == 5):
        print("SHOW MINI STATEMENT", random.randint(100, 104))
    elif(j == 6):
        print("SHOW ALL ACCOUNTS")
    elif(j == 7):
        print("SHOW BANK BALANCE")
    elif(j == 8):
        print("SHOW ACTIVE CONNECTIONS")
    elif(j == 9):
        print("CLOSE ACCOUNT", random.randint(103, 106))
    else:
        res = "Not good"

print("SHUTDOWN")