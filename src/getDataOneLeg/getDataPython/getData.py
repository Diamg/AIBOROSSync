import telnetlib
import time

def tractarData(data):
	datos=[]
	# ectura hasta la marca
	while (data.find("555555")<0):
		data=data+te.read_some()
	# descarta la informacion de la bateria y divide la cadena
	if (data.find("Bat")<0):
		dataNow=data.split("555555")[0]
		data=data.split("555555")[1]
		dataArray=dataNow.split("\n")
		del dataArray[0]
		leg=0
		for i in range(len(dataArray)):
			if (dataArray[i].find("tag0")>0):
				leg=float(dataArray[i].split("]")[1])
		return leg, data 
	else:
		data=""
		return 0, data
		
# scritura en archivo
def writeData(f, text):
	f.write(text)
	
# incializacion cliente telnet
te=telnetlib.Telnet("192.168.0.125",54000)
time.sleep(1)
data=1
# eliminacion de la cabezera URBI
while data:
	data=te.read_eager()
	print data
# demanda del bucle de envio
te.write("motors on;\r\n")
te.write("motors.load=0;\r\n")
te.write("loop tag0 << legLF1.val, loop tag19 << 5*111111;")
# primera lectura y tratamiento de la cadena
dataArray, data=tractarData(data)
# abre el archivo de escritura
f = open("Data.txt", "w")
#bucle de tratamiento y escritura
while True:
	leg, data =tractarData(data)
	t= str(leg) + "\t"
	writeData(f,t)	
	sec = "{0:.15f}".format(time.time()) + "\n"
	writeData(f,sec)
	print sec
# cierra el archibo de escritura
f.close()
