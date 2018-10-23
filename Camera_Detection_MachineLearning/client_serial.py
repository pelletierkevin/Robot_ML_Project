import serial
import time
import string
import pygame
import pygame.camera
from PIL import Image
import socket
import os

ser = serial.Serial('/dev/ttyAMA0', 19200)

pygame.camera.init()
list = pygame.camera.list_cameras()
device = list[0]
print('Prise de vue')
cam = pygame.camera.Camera(device,(336,600))

index_photos = 1
duree_intervalle = 1 
nb_photos = 5

photo_determine = False
photo_continu = False

s = socket.socket()
host = '172.20.10.3' # adresse ip du pc traitement
port = 12370
s.connect((host,port))


#while(cmd != 's'):
while True:

    cmd = ser.readline()
    
    
    if(cmd.startswith('PPH ')==True):
        print('\n'+cmd)
        mode=cmd[4]
        if(mode == 'O'):
            print('Photographie...')
            cam.start()
            img = cam.get_image()
            path= "/home/pi/Documents/aprisevue_unique.jpg"
            pygame.image.save(img,path)
            cam.stop()
            time.sleep(0.5)
            fich = open('aprisevue_unique.jpg','rb')
            nb = os.path.getsize('aprisevue_unique.jpg')/1024 +1
            data = ''
            print('Envoi image au PC traitement...')
            print('Size:' +str(nb))

            s.send(str(nb)) # on envoit la taille du fichier qu'on envoie

            for i in range(nb):
                data = fich.read(1024)
                print(len(data))
                s.send(data)
                print(i)

            fich.close()
            
            

        if(mode == 'S'):
            print('Multiple photos')

            if(cmd[6]=='E' and cmd[7]==':'):
                if(  (ord(cmd[8])-48) <= 9 and (ord(cmd[8])-48) >= 0 and (ord(cmd[9])-48) <= 9 and (ord(cmd[9])-48) >= 0):#on verifie que les caracteres soient des chiffres
                    duree_intervalle = (ord(cmd[8])-48)*10 + ord(cmd[9])-48

            if(cmd[11]=='N' and cmd[12]==':'):
                if(  (ord(cmd[13])-48) <= 9 and (ord(cmd[13])-48) >= 0):
                    if(  (ord(cmd[14])-48) <= 9 and (ord(cmd[14])-48) >= 0): #si le deuxieme caractere est aussi un chiffre
                        if(  (ord(cmd[15])-48) <= 9 and (ord(cmd[15])-48) >= 0):
                            nb_photos = (ord(cmd[13])-48)*100 + (ord(cmd[14])-48)*10 + ord(cmd[15])-48 #3 chiffres
                        else:
                            nb_photos = (ord(cmd[13])-48)*10 + (ord(cmd[14])-48)  #2 chiffres      
                        
                    else:
                        nb_photos = (ord(cmd[13])-48) #juste un chiffre

            print('Duree intervalle :' + str(duree_intervalle))
            print('Nb photos :' + str(nb_photos))
            photo_determine = True
            photo_continu = False
            index_photos = 1
            start = 0 # prend une photo direct, pas besoin d attendre l'intervalle de tps

        if(mode == 'C'):
            print('Photos en continu')

            if(cmd[6]=='E' and cmd[7]==':'): #fixe la duree de l'intervalle entre chaque photo
                if(  (ord(cmd[8])-48) <= 9 and (ord(cmd[8])-48) >= 0 and (ord(cmd[9])-48) <= 9 and (ord(cmd[9])-48) >= 0): # on verifie que les caracteres soient des chiffres
                    duree_intervalle = (ord(cmd[8])-48)*10 + ord(cmd[9])-48
            
            print('Duree intervalle :' + str(duree_intervalle))
            photo_continu = True
            photo_determine = False
            index_photos = 1
            start = 0 # prend une photo direct, pas besoin d attendre l'intervalle de tps

    if(cmd.startswith('SPH')==True): #arret de prise de photographies
        print('\n'+cmd)
        photo_continu = False
        photo_determine = False
            
        

    if(photo_determine == True):
        if(index_photos <= nb_photos and (time.time() - start)*10 > duree_intervalle ):    
            cam.start()
            img = cam.get_image()
            path= "/home/pi/Documents/prisevue{}.jpg".format(index_photos)
            pygame.image.save(img,path)   
            cam.stop()
            index_photos = index_photos+1
            start = time.time()

        if(index_photos > nb_photos):
            photo_determine = False # on arrete

    if(photo_continu == True):
        if( (time.time() - start)*10 > duree_intervalle ):    
            cam.start()
            img = cam.get_image()
            path= "/home/pi/Documents/prisevue{}.jpg".format(index_photos)
            pygame.image.save(img,path)   
            cam.stop()
            index_photos = index_photos+1
            start = time.time()

    
    
s.close    

