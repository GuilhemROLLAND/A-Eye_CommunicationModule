def decodeTM(str):
    code = str[0]
    str = str[1:]
    if code == 6:
        print(str)
    elif code == 5:
        file = open("temp.bmp", "w")
        file.write(str)
        file.close()
        print("Get New Image")
    else :
        print("OpCode not implemented in decodageTM")
    return
