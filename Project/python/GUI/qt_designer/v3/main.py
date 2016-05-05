from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import sys
import os
import design
import serial
import glob

global port_detect
global port
data = []
global connect_status

class mygui(QtGui.QMainWindow, design.Ui_MainWindow):
	global port_detect
	global port
	global app


#**********************Communication/Serial Port Detection Starts*********************
	def serial_port_connection(self):
		global port_detect
		global port
		global connect_status

		#global port_detect
		
		#print len(port_detect),"Ports detected" # print number of ports detected
	
		#------------- print all detectec ports - STARTS ---------#
		#if (len(port_detect) != 0):				
		#	print "Port(s) detected is/are:"	
			
			#for i in range (0,len(port_detect)):
			#	print port_detect[i]
		#port_detect = self.cboxComport.currentText()
		
		port = serial.Serial(str(self.cboxComport.currentText()),baudrate=9600)
		print "connected to: ", self.cboxComport.currentText()					#-- change this as per input from comboxbox

		if port.isOpen() == True: #(len(port_detect) != 0):				
				connect_status = 1
				print "connect_status is " + str(connect_status)
				self.textStatus.append("Connected to: " + self.cboxComport.currentText())
				self.btnSet.setText("Connected")
				self.btnSet.setEnabled(False)
		else:
			connect_status = 1
			print "Error connecting to port"

	#------------- print all detectec ports - END ---------#
	
#**********************Communication/Serial Port Detection Ends*********************
	#**********************Open Communication/Serial Port Starts*********************	
	def serial_open(self):
		global port
		port_detect = []
		port_detect = glob.glob("/dev/tty*") # stores all /dev/ttyACM* into a list port_detect
		#print len(port_detect),"Ports detected" # print number of ports detected
		
		self.cboxComport.addItems(port_detect)
		self.btnSet.setEnabled(True)
		self.btnSet.setText("Connect")

		'''
		try:
			self.serial_port_connection(port_detect)
				
			if port.isOpen() == True: #(len(port_detect) != 0):				
				print "port is open"	
				self.cboxComport.addItems(port_detect)
			else: 
				self.serial_port_connection(port_detect)

		except:
			print "No USB port detected....check connection"
			sys.exit(0)
		'''

		#port.close()

	def closeall(self):
		global port
		connect_status = 0
		print "connect_status is " + str(connect_status)	
		self.textStatus.append("Exiting")
		self.textStatus.append("---------------------------------")
		port.close()
		if port.isOpen() == False:
			print "Port Closed"
		else:
			print "Port Not Closed properly.."
		sys.exit(app.exec_())
		#sys.exit(0)

	def set(self):
		global port
		# store data from textbox in variable
		data = []
		#filtertype = "Allpass"
		text_cboxcomport = str(self.cboxComport.currentText())

		# send data to controller
		#data.append(text_cboxfilterType)
		#data.append(text_gaintext)

		for i in range(0,len(data)):
			port.write(str(data[i]))
			print str(data[i])

		# print in status box
		self.textStatus.append("---------------------------------")

		#self.textStatus.setText("Hi")
		self.textStatus.append("Connected to: " + text_cboxcomport)

	def fcvalue(self,value):
		global port
		global connect_status

		fc_value = self.fc.value()
		#try:
		if connect_status == 1:
			#print fc_value
			data = fc_value
			port.write(chr(data))
			print "port write "+ (str(data))
			self.textStatus.append("Value for Cutoff Frequency is: " + str(data))		

		#except:
			#self.textStatus.append("Device not connected .. Press Connect Button")

	def ampvalue(self,value):
		global port 
		global connect_status

		amp_value = self.amp.value()
		try:
			if connect_status == 1:
				#print fc_value
				data = amp_value+20
				port.write(str(data))
				print "port write "+ (str(data))

		except:
			self.textStatus.append("Device not connected .. Press Connect Button")		

	def lpfiltervalue_none(self,value):
		global port 
		global connect_status
		if self.radio_none.isChecked():
			print "button-none clicked"
		#radio_value = self.amp.value()
		try:
			if connect_status == 1:
				#print fc_value
				data = amp_value+20
				port.write(str(data))
				print "port write "+ (str(data))

		except:
			self.textStatus.append("Device not connected .. Press Connect Button")

	def lpfiltervalue_lp1(self,value):
		global port 
		global connect_status
		#if self.radio_lp1.isChecked():
			#print "button-none clicked"
		#radio_value = self.amp.value()
		try:
			if connect_status == 1 and self.radio_lp1.isChecked():
				#print fc_value
				data = 21
				port.write(chr(data))
				print "port write "+ (str(data))
				self.textStatus.append("Value for Lowpass-1 is: " + str(data))
		except:
			self.textStatus.append("Device not connected .. Press Connect Button")			

	def lpfiltervalue_lp2(self,value):
		global port 
		global connect_status
		#if self.radio_lp1.isChecked():
			#print "button-none clicked"
		#radio_value = self.amp.value()
		try:
			if connect_status == 1 and self.radio_lp2.isChecked():
				#print fc_value
				data = 22
				port.write(chr(data))
				print "port write "+ (str(data))
				self.textStatus.append("Value for Lowpass-2 is: " + str(data))
		except:
			self.textStatus.append("Device not connected .. Press Connect Button")

	def lpfiltervalue_lp3(self,value):
		global port 
		global connect_status
		#if self.radio_lp1.isChecked():
			#print "button-none clicked"
		#radio_value = self.amp.value()
		try:
			if connect_status == 1 and self.radio_lp3.isChecked():
				#print fc_value
				data = 23
				port.write(chr(data))
				print "port write "+ (str(data))
				self.textStatus.append("Value for Lowpass-3 is: " + str(data))
		except:
			self.textStatus.append("Device not connected .. Press Connect Button")


	def __init__(self, parent=None):
        #super(ExampleApp, self).__init__(parent)
		super(self.__class__, self).__init__()
		self.setupUi(self)
		dialog = QtGui.QDialog()
		dialog.setWindowFlags(dialog.windowFlags() | QtCore.Qt.WindowMinimizeButtonHint | QtCore.Qt.WindowSystemMenuHint)
    	
		self.btnRefresh.clicked.connect(self.serial_open)
		self.btnSet.clicked.connect(self.serial_port_connection)
		self.btnExit.clicked.connect(self.closeall)
		self.connect(self.fc, SIGNAL("valueChanged(int)"),self.fcvalue)
		#self.connect(self.amp, SIGNAL("valueChanged(int)"),self.ampvalue)
		#self.radio_none.toggled.connect(self.lpfiltervalue_none)
		self.radio_lp1.toggled.connect(self.lpfiltervalue_lp1)
		self.radio_lp2.toggled.connect(self.lpfiltervalue_lp2)
		self.radio_lp3.toggled.connect(self.lpfiltervalue_lp3)

		'''
		check = self.radio_none.isChecked()
		print check

		if self.radio_none.isChecked():
			print "lp4 checked"
		else:
			print "nnn"
		'''	



def main():
	global app
	app = QtGui.QApplication(sys.argv)
	form = mygui()
	print "start"
	form.show()
	form.serial_open()

	sys.exit(app.exec_())

if __name__ == '__main__':
	main()