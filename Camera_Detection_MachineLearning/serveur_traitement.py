#!/usr/bin/python           # This is server.py file
# -*- coding: cp1252 -*-

import socket               # Import socket module
import base64
from PIL import Image
from StringIO import StringIO
import matlab.engine

#vide l'image cible
fh = open('im.jpg','wb')
fh.truncate()
fh.close()

fh = open('im.jpg','wb')

s = socket.socket()         # Create a socket object
host = '' # Get local machine name
port = 12393        # Reserve a port for your service.
s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.


data = ''
c, addr = s.accept()     # Establish connection with client.
print ('Connecte a la Raspberry | ', addr)

#data = base64.b64encode(c.recv(1024))
#ch = data.decode('base64')

while True:
    

    

    data = c.recv(1024)
    size = int(data)
    print('Nb paquets 1024 octets:' + str(data))

    fh = open('im.jpg','wb')
    fh.truncate()
    fh.close()
    fh = open('im.jpg','wb')

    print('Attente de reception image...')
    print('Nb paquets 1024 octets:' + str(data))
    for i in range(size):
        data = c.recv(1024)
        fh.write(data)
       

    
    fh.close()

    print('Image reçue... Lancement script Matlab')


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
    elif(forme==6):
        print('Fond');




