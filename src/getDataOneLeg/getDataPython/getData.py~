import telnetlib
import time
def tractarData(data):
	datos=[]
	while (data.find("555555")<0):
		data=data+te.read_some()
	if (data.find("Bat")<0):
		#print "dataNow"
		dataNow=data.split("555555")[0]
		#print dataNow
		#print "sobras"
		data=data.split("555555")[1]
		#print data
		dataArray=dataNow.split("\n")
		del dataArray[0]
		#print "dataArray"
		#print dataArray
		leg=0
		for i in range(len(dataArray)):
			if (dataArray[i].find("tag0")>0):
				#print dataArray[i].split("]")[1]
				leg=float(dataArray[i].split("]")[1])
				print "______________________\n"
				print leg
				
			
		return leg, data 
	else:
		#print "nfweonfoiwen"
		data=""
		return 0, data
def writeData(f, text):
	
	f.write(text) # Write a string to a file


te=telnetlib.Telnet("192.168.0.125",54000)
time.sleep(1)
data=1
while data:
	data=te.read_eager()
	print data
te.write("motors on;\r\n")
te.write("motors.load=0;\r\n")

print "........................."

te.write("loop tag0 << legLF1.val, loop tag19 << 5*111111;")

dataArray, data=tractarData(data)

f = open("Data.txt", "w")
while True:
	
	leg, data =tractarData(data)
	t= str(leg) + "\t"
	writeData(f,t)	
	sec = "{0:.15f}".format(time.time()) + "\n"
	writeData(f,sec)
	print sec
	
f.close()
