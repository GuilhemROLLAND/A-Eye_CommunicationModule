DEBUG = False

def writeInPipe(msg):
    if DEBUG:
        print(msg)
    else:
        with open(r'\\.\pipe\\'+'CSServer', 'w') as f:
            f.write(msg + "\n")
    return
