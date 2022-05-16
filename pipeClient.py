def writeInPipe(msg):
    with open(r'\\.\pipe\\'+'CSServer', 'w') as f:
        f.write(msg)
