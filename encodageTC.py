from asyncio.windows_events import NULL
import json
from deepdiff import DeepDiff
import socket

"""
Create an instance of a tcp client connecting to zybo addr and port 64000
If the tcp server is active on zybo, this function will connect to the tcp server 
and send the specified message
"""
def tcp_client_send(msg):

    # Connection parameters
    server_addr = ('192.168.1.21', 64000)
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


def decode_send_tc() : 
    # Loading json config file
    f1 = open('config.json')
    f2 = open('last_config.json')
    new_config = json.load(f1)
    last_config = json.load(f2)

    # Search for differences in config files
    diff = DeepDiff(new_config,last_config, ignore_string_case = True)
    diff = diff.to_dict()
    tc = []

    # TC decoding

    # TC modeSelector 
    if "root['config']['modeSelector']" in diff['values_changed']:
        mode = diff['values_changed']["root['config']['modeSelector']"]['new_value']
        tc.append("1{}".format(mode))  
    if "root['config']['startStop']" in diff['values_changed']:
        mode = diff['values_changed']["root['config']['startStop']"]['new_value']
        if mode == 'true' :
            tc.append("31")
        else :
            tc.append("30")
    # TC weights         
    if "root['weights']['valid']"  in diff['values_changed']:
        mode = diff['values_changed']["root['weights']['valid']"]['new_value']
        if mode == 'true' :
            tc.append("41")
        else :
            tc.append("40")
    # TC takePicture 
    if "root['takePicture']['valid']" in diff['values_changed']:
        mode = diff['values_changed']["root['takePicture']['valid']"]['new_value']
        if mode == 'true' :
            tc.append("21")
        else :
            tc.append("20")
    print(tc)
    for i in range(len(tc)) :
        tcp_client_send(tc[i])
    with open('./config.json', 'w', encoding='utf-8') as f :
        json.dump(new_config, f, ensure_ascii=False, indent = 4)