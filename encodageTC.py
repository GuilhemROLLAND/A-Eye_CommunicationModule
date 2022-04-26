from asyncio.windows_events import NULL
import json
from deepdiff import DeepDiff
import socket

def tcp_client_send(msg):
    server_addr = ('192.168.1.21', 64000)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

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
    finally:
        print("Closing socket")
        s.close()



f1 = open('config.json')
f2 = open('last_config.json')
new_config = json.load(f1)
last_config = json.load(f2)

diff = DeepDiff(new_config,last_config, ignore_string_case = True)
diff_dict = diff.to_dict()
print(diff_dict)
tc = []
if "root['config']['modeSelector']" in diff_dict['values_changed']:
    print('difference dans config')
    mode = diff_dict['values_changed']["root['config']['modeSelector']"]['new_value']
    tc.append("1{}".format(mode))  
if "root['config']['startStop']" in diff_dict['values_changed']:
    print('difference dans config')
    mode = diff_dict['values_changed']["root['config']['startStop']"]['new_value']
    if mode == 'true' :
        tc.append("31")
    else :
        tc.append("30")
if "root['weights']['valid']"  in diff_dict['values_changed']:
    print('difference dans weights')
    mode = diff_dict['values_changed']["root['weights']['valid']"]['new_value']
    if mode == 'true' :
        tc.append("41")
    else :
        tc.append("40")

if "root['takePicture']['valid']" in diff_dict['values_changed']:
    print('difference dans takePicture')
    mode = diff_dict['values_changed']["root['takePicture']['valid']"]['new_value']
    if mode == 'true' :
        tc.append("21")
    else :
        tc.append("20")
print(tc)
for i in range(len(tc)) :
    tcp_client_send(tc[i])