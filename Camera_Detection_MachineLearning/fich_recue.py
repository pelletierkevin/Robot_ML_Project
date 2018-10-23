import serial
import socket
import time
import base64
import string
import os
import pygame
import pygame.camera
from PIL import Image


pygame.camera.init()
list = pygame.camera.list_cameras()
device = list[0]
print('Prise de vue')
cam = pygame.camera.Camera(device,(352,288))
cam.start()
img = cam.get_image()
path= "/home/pi/Documents/bon.jpg"
pygame.image.save(img,path)
cam.stop()

s = socket.socket()
host = '172.20.10.3' # adresse ip du pc traitement
port = 12374

s.connect((host,port))


fich = open('bon2.jpg','rb')
nb = os.path.getsize('bon2.jpg')/1024
data = ''
print('Envoi image au PC traitement...')

s.send(str(nb)) # on envoit la taille du fichier qu'on envoie

for i in range(nb):
    
    data = fich.read(1024)
    s.send(data)



fich.close()
s.close
