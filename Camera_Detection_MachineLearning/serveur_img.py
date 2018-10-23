#!/usr/bin/python           # This is server.py file

import socket               # Import socket module
import base64
from PIL import Image
from StringIO import StringIO


fh = open('rez.jpg','wb')

s = socket.socket()         # Create a socket object
host = '' # Get local machine name
port = 12354                # Reserve a port for your service.
s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.


data = ''
c, addr = s.accept()     # Establish connection with client.
print ('Got connection from', addr)
i=0
while(True):
   data = base64.b64encode(c.recv(1024))
   fh.write(data.decode('base64'))
   print('Iteration')
   print(i)
   i=i+1
   
   

c.close()                # Close the connection
