import sys
import telnetlib
import time
import math

te=telnetlib.Telnet("192.168.0.125",54000)

te.write("motors on;\r\n")
te.write("legLF1.val->blend = cancel;\r\n")


A=50
offsetl=85
angle=0
paso=15
while True:
	legLF1=A*math.sin(math.radians(angle)) + offsetl
	print "telnet send"
	te.write("legLF1.val= %1.6f time: 80,\r\n" % legLF1)
	print "legLF1.val= %1.6f,\r\n" % legLF1
	angle+=paso
	time.sleep(0.08)
