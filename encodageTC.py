from asyncio.windows_events import NULL
import json
import argparse
import string
from deepdiff import DeepDiff
import socket

"""
Create an instance of a tcp client connecting to zybo addr and port 64000
If the tcp server is active on zybo, this function will connect to the tcp server 
and send the specified message
"""
def tcp_client_send(msg, ip, port):

    # Connection parameters
    server_addr = (ip, port)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Connected and send msg, wait for ack
    try:
        s.connect(server_addr)
        print("Connected to {:s}".format(repr(server_addr)))
        nsent = s.send(msg.encode())
        buff = s.recv(1024)
        print(buff.decode())
    except AttributeError as ae:
        print("Error creating the socket: {}".format(ae))
    except socket.error as se:
        print("Exception on socket: {}".format(se))
    # Close connection after ack
    finally:
        print("Closing socket")
        s.close()


def decode_send_tc(ip, port) : 
    # Loading json config file
    f1 = open('config.json')
    f2 = open('last_config.json')
    new_config = json.load(f1)
    last_config = json.load(f2)

    # Search for differences in config files
    diff = DeepDiff(last_config,new_config, ignore_string_case = True)
    diff = diff.to_dict()
    tc = []

    # TC decoding

    # TC modeSelector 
    if 'values_changed' in diff :
        if "root['Config']['ModeSelector']" in diff['values_changed']:
            mode = diff['values_changed']["root['Config']['ModeSelector']"]['new_value']
            tc.append("1{}".format(mode))  
        if "root['Config']['StartStop']" in diff['values_changed']:
            mode = diff['values_changed']["root['Config']['StartStop']"]['new_value']
            if mode == 'True' :
                tc.append("31")
            else :
                tc.append("30")
        # TC weights         
        if "root['Weights']['Valid']"  in diff['values_changed']:
            mode = diff['values_changed']["root['Weights']['Valid']"]['new_value']
            if mode == 'True' :
                tc.append("41")
            else :
                tc.append("40")
        # TC takePicture 
        if "root['TakePicture']['Valid']" in diff['values_changed']:
            mode = diff['values_changed']["root['TakePicture']['Valid']"]['new_value']
            if mode == 'True' :
                tc.append("21")
            else :
                tc.append("20")
    print(tc)
    for i in range(len(tc)) :
        tcp_client_send(tc[i], ip, port)
    with open('./last_config.json', 'w', encoding='utf-8') as f :
        json.dump(new_config, f, ensure_ascii=False, indent = 4)




parser = argparse.ArgumentParser()
parser.add_argument("-i", "--ip", type=str,required=True, help="take IpV4 format addr")
parser.add_argument("-p", "--port", type=int, required=True, help="port of the server")
args = parser.parse_args()
decode_send_tc(args.ip, args.port)