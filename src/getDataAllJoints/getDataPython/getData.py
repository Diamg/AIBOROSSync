import telnetlib
import time

class Joints(object):
	_slots_=['val','tag']
def tractarData(data):
	
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
		Joint=Joints()
		Joint.val=[]
		Joint.tag=["legLF1", "legLF2", "legLF3", "legLH1", "legLH2","legLH3","legRF1","legRF2","legRF3","legRH1","legRH2","legRH3","neck","mouth","headPan","headTilt","tailTilt","tailPan"]
	
		#print dataArray
		for i in range(len(dataArray)):
			if (dataArray[i].find("tag0")>0):
				#print dataArray[i].split("]")[1]
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
				#print "______________________\n"
				#print Joint.val[0]
				
				
			
		return Joint, data 
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
global Joint
te.write("loop tag0 << legLF1.val, loop tag2 << legLF2.val,loop tag3 << legLF3.val, loop tag4 << legLH1.val, loop tag5 << legLH2.val, loop tag6 << legLH3.val, loop tag7 << legRF1.val, loop tag8 << legRF2.val, loop tag9 << legRF3.val, loop tag10 << legRH1.val, loop tag11 << legRH2.val, loop tag12 << legRH3.val, loop tag13 << mouth.val, loop tag14 << neck.val, loop tag15 << headPan.val, loop tag16 << headTilt.val, loop tag17 << tailTilt.val,loop tag18 << tailPan.val, loop tag19 << 5*111111;")
	
dataArray, data=tractarData(data)

f = open("Data.txt", "w")
while True:
	
	joint, data =tractarData(data)
	print "......................................................................."
	if (joint!=0) :
		for i in range(len(joint.val)):
			sec = "{0:.15f}".format(time.time()) + "\t"
			writeData(f,sec)
			print sec
			t= str(joint.tag[0]) + "\t"
			print t
			writeData(f,t)
			t= str(joint.val[0]) + "\n"
			print t
			writeData(f,t)	
			

f.close()
