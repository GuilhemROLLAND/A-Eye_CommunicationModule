#!/usr/bin/env python3

""" client.py - Echo client for sending/receiving C-like structs via socket
References:
- Ctypes: https://docs.python.org/3/library/ctypes.html
- Sockets: https://docs.python.org/3/library/socket.html
"""

import argparse
from ast import Try
from asyncio.windows_events import NULL
from hashlib import new
from multiprocessing.connection import Client, wait
import socket
import sys
import random
from ctypes import *
from threading import Thread
from time import sleep
import encodageTC

class client:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    @staticmethod
    def client_init(ip, port):
        # Connection parameters
        server_addr = (ip, port)
        try:
            client.s.connect(server_addr)
            print("Connected to {:s}".format(repr(server_addr)))
        except AttributeError as ae:
            print("Error creating the socket: {}".format(ae))
        except socket.error as se:
            print("Exception on socket: {}".format(se))
        return client.s

    """
    Create an instance of a tcp client connecting to zybo addr and port 64000
    If the tcp server is active on zybo, this function will connect to the tcp server 
    and send the specified message
    """
    @staticmethod
    def tcp_client_send():
        msg = encodageTC.encode_tc()
        if(client.s == NULL):
            print("Socket not init.")
            return
        # Connected and send msg, wait for ack
        for tc in msg:
            # print("send " + tc)
            client.s.send(tc.encode())
        # Close connection after ack

    @staticmethod
    def tcp_client_receive():
        print("In tcp_client_receive")
        while(1):
            buff = client.s.recv(1024)
            print(buff.decode())


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--ip", type=str,required=True, help="take IpV4 format addr")
    parser.add_argument("-p", "--port", type=int, required=True, help="port of the server")
    args = parser.parse_args()
    client.client_init(args.ip, args.port)
    receiver = Thread(target=client.tcp_client_receive)
    receiver.start()
    while(1):
        sender = Thread(target=client.tcp_client_send)
        sender.start()
        sleep(1)
        