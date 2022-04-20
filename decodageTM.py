import pipeClient

def decodeTM(str):
    code = str[0]
    size = str[1:5]
    str = str[5:]
    if code == 0x60:
        # String to print
        pipeClient.writeInPipe("content of TM : " + str)
    elif code == 0x50:
        # Image
        file = open("temp.bmp", "wb")
        file.write(str)
        file.close()
        pipeClient.writeInPipe("Get New Image")
    else:
        # Other
        pipeClient.writeInPipe("OpCode not implemented in decodageTM")
    return
