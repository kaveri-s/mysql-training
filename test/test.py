from subprocess import PIPE, Popen
import re
import random
import string

"""
CONFIGURATION
"""
PATH_TO_CLIENT = '/home/kaveri/Desktop/mysql-training/src/client/client'
PROMPT = 'Lorem >>'
END_OF_OUTPUT = '\n\n'
STATUS_LINES_BEFORE_PROMPT = 0
ACC_NO_REGEX = re.compile(r'Account number is ([\d]+)')
get_acc_no = lambda s : int(ACC_NO_REGEX.search(s).group(1))
AMOUNT_REGEX = re.compile(r'Account balance is \$(([0-9]*\.)?[0-9]+)')
get_amount = lambda s : float(AMOUNT_REGEX.search(s).group(1))
"""
END OF CONFIGURATION
"""

process = Popen(PATH_TO_CLIENT, stdin=PIPE, stdout=PIPE, stderr=PIPE, bufsize=1)
cin,cout,cerr = process.stdin, process.stdout, process.stderr

out=''
for i in range(STATUS_LINES_BEFORE_PROMPT):
    out = cout.readline()


def randomString(stringLength=10):
    """Generate a random string of fixed length """
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))


def send_command(input_string):
    input_string+='\n'
    cin.write(input_string.encode('utf-8')) 
    cin.flush() 
    out=''
    output_string=''
    end_bytes = END_OF_OUTPUT.encode('utf-8')
    while out != end_bytes:
        out = cout.readline()
        output_string += out.decode('utf-8')
    return output_string.lstrip(PROMPT).replace(END_OF_OUTPUT,'')

def open_account():
    s = send_command("open account {} {}".format(randomString(),randomString()))
    return get_acc_no(s)
    
# for i in range(10000):
#     open_account()
#     s = send_command("show all accounts")
#     print(s)

for i in range(100):
    print(i)
    balance = 0.0
    acc_no = open_account()
    for j in range(1000):
        print("{}:{}".format(i,j))
        send_command("show account balance {}".format(acc_no))

        amount = round(random.uniform(500,1000),0)
        s = send_command("deposit {} {}".format(acc_no, amount))
        balance += amount
        assert(get_amount(s)==balance)

        send_command("show account balance {}".format(acc_no))

        amount = amount - 1.0
        s = send_command("withdraw {} {}".format(acc_no, amount))
        balance -= amount
        assert(get_amount(s)==balance)

        send_command("show account balance {}".format(acc_no))

    send_command("show mini statement {}".format(acc_no))
    send_command("show bank balance")    
    send_command("show all accounts")