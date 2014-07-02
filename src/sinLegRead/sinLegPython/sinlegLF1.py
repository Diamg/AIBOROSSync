import sys
import telnetlib
import time
import math
import threading

global Joint
angle=0

#funcion de envio
def move():
	global te1
	global angle
	global f2
	A=50
	offsetl=85
	paso=15
	legLF1=A*math.sin(math.radians(angle)) + offsetl
	te1.write("legLF1.val= %1.6f time: 500,\r\n" % legLF1)
	angle+=paso
	sec = "{0:.15f}".format(time.time()) + "\t"
	writeData(f2,sec)
	t2= str(legLF1) + "\n"
	writeData(f2,t2)
	threading.Timer(0.2,move).start()
#define la clase joints
class Joints(object):
	_slots_=['val','tag']

#funcion de tratamiento de la cadena
def tractarData(data):
	while (data.find("555555")<0):
		
		data=data+te.read_some()
	if (data.find("Bat")<0):
		dataNow=data.split("555555")[0]
		data=data.split("555555")[1]
		dataArray=dataNow.split("\n")
		del dataArray[0]
		Joint=Joints()
		Joint.val=[]
		Joint.tag=["legLF1", "legLF2", "legLF3", "legLH1", "legLH2","legLH3","legRF1","legRF2","legRF3","legRH1","legRH2","legRH3","neck","mouth","headPan","headTilt","tailTilt","tailPan"]
		for i in range(len(dataArray)):
			if (dataArray[i].find("tag0")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag2")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag3")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag4")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag5")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag6")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag7")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag8")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag9")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag10")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag11")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag12")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag13")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag14")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag15")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag16")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag17")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))
			if (dataArray[i].find("tag18")>0):
				Joint.val.append(float(dataArray[i].split("]")[1]))	
				
		return Joint, data 
	else:
		data=""
		return 0, data
		
#escribe en el archivo
def writeData(f, text):
	
	f.write(text) 

#inicia cliente telnet de envio
te1=telnetlib.Telnet("192.168.0.124",54000)
te1.write("motors on;\r\n")
#selecciona modo de resolver conflictos
te1.write("legLF1.val->blend = cancel;\r\n")
#inicia cliente telnet de recepcion
te=telnetlib.Telnet("192.168.0.124",54000)
te.write("motors on;\r\n")
time.sleep(3)
data=1
#elimina la cabecera de URBI de la cadena
while data:
	data=te.read_eager()
	print data
#demanda del bucle de envio de datos
te.write("loop tag0 << legLF1.val, loop tag2 << legLF2.val,loop tag3 << legLF3.val, loop tag4 << legLH1.val, loop tag5 << legLH2.val, loop tag6 << legLH3.val, loop tag7 << legRF1.val, loop tag8 << legRF2.val, loop tag9 << legRF3.val, loop tag10 << legRH1.val, loop tag11 << legRH2.val, loop tag12 << legRH3.val, loop tag13 << mouth.val, loop tag14 << neck.val, loop tag15 << headPan.val, loop tag16 << headTilt.val, loop tag17 << tailTilt.val,loop tag18 << tailPan.val, loop tag19 << 5*111111;")
#primera cadena leida y tratada
dataArray, data=tractarData(data)
#abre los archivos de escritura
f = open("Data.txt", "w")
f2 = open("DataIn.txt", "w")
#llama a la funcion de movimiento a los 200ms
threading.Timer(0.2,move).start()
#bucle de lectura
while True:
	joint, data =tractarData(data)
	if (joint!=0) :
		sec = "{0:.15f}".format(time.time()) + "\t"
		writeData(f,sec)
		t= str(joint.tag[0]) + "\t"
		writeData(f,t)
		t= str(joint.val[0]) + "\n"
		writeData(f,t)	
#cierra archivos
f.close()
f2.close()
