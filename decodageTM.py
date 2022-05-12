def decodeTM(str):
    code = str[0]
    size = str[1:5]
    str = str[5:]
    if code == 0x60:
        print(str)
    elif code == 0x50:
        file = open("temp.bmp", "wb")
        file.write(str)
        file.close()
        print("Get New Image")
    else :
        print("OpCode not implemented in decodageTM")
    return
