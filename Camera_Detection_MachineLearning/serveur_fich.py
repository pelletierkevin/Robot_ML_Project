#!/usr/bin/python           # This is server.py file

import socket               # Import socket module
import base64
from PIL import Image
from StringIO import StringIO
import matlab.engine

#vide l'image cible
fh = open('client_serial.py','wb')
fh.truncate()
fh.close()

fh = open('client_serial.py','wb')

s = socket.socket()         # Create a socket object
host = '' # Get local machine name
port = 12376                # Reserve a port for your service.
s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.


data = ''
c, addr = s.accept()     # Establish connection with client.
print ('Got connection from', addr)

#data = base64.b64encode(c.recv(1024))
#ch = data.decode('base64')

data = c.recv(1024)
size = int(data)

for i in range(size):
    data = c.recv(1024)
    fh.write(data)
    print(i)
   

c.close()                # Close the connection
fh.close()

# lance script matlab detection img
eng= matlab.engine.start_matlab()
couleur = 0
forme =0
(couleur,forme) = eng.detect_final(nargout=2) #detect_final est ma fonction matlab
print(couleur,forme)

if(couleur==1):
    print('Orange');
elif(couleur==2):
    print('Jaune');
elif (couleur==3) :   
    print('Vert');
elif (couleur==4):
    print('Bleu');
elif(couleur==5):
    print('Violet');
elif(couleur==6):
    print('Rose');


if(forme==1):
    print('Carre');
elif(forme==2):
    print('Coeur');
elif (forme==3) :
    print('Croix');
elif (forme==4):    
    print('Rond');
elif(forme==5):
    print('Triangle');
elif(forme==5):
    print('Fond');



c.close()
s.close()
