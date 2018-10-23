import serial
import time
import string
import pygame
import pygame.camera
from PIL import Image

ser = serial.Serial('/dev/ttyAMA0', 19200)

pygame.camera.init()
list = pygame.camera.list_cameras()
device = list[0]
print('Prise de vue')
cam = pygame.camera.Camera(device,(352,288))

index_photos = 1
duree_intervalle = 1 
nb_photos = 5

photo_determine = False
photo_continu = False



#while(cmd != 's'):
while True:

    cmd = ser.readline()
    
    
    if(cmd.startswith('PPH ')==True):
        print(cmd)
        mode=cmd[4]
        if(mode == 'O'):
            print('Photographie...')
            cam.start()
            img = cam.get_image()
            path= "/home/pi/Documents/aprisevue_unique.jpg"
            pygame.image.save(img,path)
            cam.stop()

        if(mode == 'S'):
            print('Multiple photos')
            duree_intervalle = (ord(cmd[8])-48)*10 + ord(cmd[9])-48
            if(len(cmd) > 16):
                nb_photos = (ord(cmd[13])-48)*100 + (ord(cmd[14])-48)*10 + ord(cmd[15])-48
            else:
                nb_photos = (ord(cmd[13])-48)*10 + (ord(cmd[14])-48)
            photo_determine = True
            photo_continu = False
            index_photos = 1
            start = 0 # prend une photo direct, pas besoin d attendre l'intervalle de tps

        if(mode == 'C'):
            print('Photos en continu')
            duree_intervalle = (ord(cmd[8])-48)*10 + ord(cmd[9])-48
            photo_continu = True
            photo_determine = False
            index_photos = 1
            start = 0 # prend une photo direct, pas besoin d attendre l'intervalle de tps

    if(cmd.startswith('SPH')==True): #arret de prise de photographies
        print(cmd)
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

    
    

