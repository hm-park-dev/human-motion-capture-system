import socket
import time
from datetime import datetime
import sys
sys.path.append("/home/blepi01/BlueSTSDK_Python")
from blue_st_examples.test_tcp_ble_2 import MSG

HOST = '192.168.0.11' 
PORT = 8080
MSG       

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

server_socket.bind((HOST, PORT))

server_socket.listen()

client_socket, addr = server_socket.accept()

print('Connected by', addr)

k = 0

while True:
    
    client_socket.sendall(MSG.encode())
    print('send 완료 '+ str(k) )
    k += 1
    #time.sleep(2)
    
    '''
    무한 루프를 돌면서 2초에 한번씩 데이터를 송신함.
    만약 종료 조건을 넣고 싶다면 여기에 넣으면 됨
    '''

client_socket.close()
server_socket.close()