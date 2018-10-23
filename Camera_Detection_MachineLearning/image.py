from PIL import Image
from StringIO import StringIO
import os
import base64


#im = Image.open('im_bleu.jpg')
#im.show()
#http://codes-sources.commentcamarche.net/source/53419-transfert-de-fichier-par-socket


fe = open('im_bleu.jpg','rb')

fh = open('aza.jpg','wb')
fh.truncate()
nb = os.path.getsize('im_bleu.jpg')/1024
print(nb)
data = ''
for i in range(nb):
	#data = base64.b64encode(fe.read(1024))
	#fh.write(data.decode('base64'))
        data = fe.read(1024)
        fh.write(data)

fh.close()
fe.close()
