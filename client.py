#!/usr/bin/env python3

""" client.py - Echo client for sending/receiving C-like structs via socket
References:
- Ctypes: https://docs.python.org/3/library/ctypes.html
- Sockets: https://docs.python.org/3/library/socket.html
"""

import socket
import sys
import random
from ctypes import *


""" This class defines a C-like struct """
class Payload(Structure):
    _fields_ = [("id", c_uint32),
                ("counter", c_uint32),
                ("temp", c_float)]


def tcp_client_send():
    server_addr = ('192.168.1.21', 64000)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect(server_addr)
        print("Connected to {:s}".format(repr(server_addr)))
    except AttributeError as ae:
        print("Error creating the socket: {}".format(ae))
    except socket.error as se:
        print("Exception on socket: {}".format(se))
    while(1):
        msg = input("Message to send : ")
        nsent = s.send(msg.encode())
        buff = s.recv(1024)
        print(buff.decode())
        if (buff == "STOP") :
            s.close()
   



if __name__ == "__main__":
        tcp_client_send()
    
    