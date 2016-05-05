from PyQt4 import QtGui, QtCore
import sys
import os
import design
import serial
import glob

global port_detect
global port

class mygui(QtGui.QMainWindow, design.Ui_MainWindow):
	global port_detect
	global port
	global app


#**********************Communication/Serial Port Detection Starts*********************
	def serial_port_connection(self,port_detect):
		global port
		#global port_detect
		
		print len(port_detect),"Ports detected" # print number of ports detected
	
		#------------- print all detectec ports - STARTS ---------#
		if (len(port_detect) != 0):				
			print "Port(s) detected is/are:"	
			
			for i in range (0,len(port_detect)):
				print port_detect[i]

		#------------- connect to PORT if only one port is detected - STARTS ---------#
		#self.cboxComport.addItems(port_detect)	
		#self.cboxComport.addItems(port_detect)	
		port = serial.Serial(port_detect[0],baudrate=9600)
		print "connected to: ", port_detect[0]					#-- change this as per input from comboxbox

		return
	#------------- print all detectec ports - END ---------#
	
#**********************Communication/Serial Port Detection Ends*********************
	#**********************Open Communication/Serial Port Starts*********************	
	def serial_open(self):
		global port
		#global port_detect

		port_detect = glob.glob("/dev/ttyACM*") # stores all /dev/ttyACM* into a list port_detect
		#print len(port_detect),"Ports detected" # print number of ports detected

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

		#port.close()

	def closeall(self):
		self.textStatus.append("Exiting")
		self.textStatus.append("---------------------------------")
		port.close()
		sys.exit(app.exec_())
		#sys.exit(0)

	def set(self):
		global port
		# store data from textbox in variable
		data = []
		#filtertype = "Allpass"
		text_cboxcomport = str(self.cboxComport.currentText())
		text_cboxfilterType = str(self.cboxFilterType.currentText())
		text_gaintext = str(self.textGain.text())

		# send data to controller
		if text_cboxfilterType == "Allpass":
			print "filter Type:" + text_cboxfilterType
			data = [0]

		if text_cboxfilterType == "Bandpass -  (101-201KHz)":
			print "filter Type:" + text_cboxfilterType
			data = [1]

		if text_cboxfilterType == "Bandpass -  (301-401KHz)":
			print "filter Type:" + text_cboxfilterType
			data = [2]

		#data.append(text_cboxfilterType)
		#data.append(text_gaintext)

		for i in range(0,len(data)):
			port.write(str(data[i]))
			print str(data[i])

		# print in status box
		self.textStatus.append("---------------------------------")

		#self.textStatus.setText("Hi")
		self.textStatus.append("Connected to: " + text_cboxcomport)
		self.textStatus.append("Filter Type: " + text_cboxfilterType)
		self.textStatus.append("Gain: " + text_gaintext)	

	def __init__(self, parent=None):
        #super(ExampleApp, self).__init__(parent)
		super(self.__class__, self).__init__()
		self.setupUi(self)
		dialog = QtGui.QDialog()
		dialog.setWindowFlags(dialog.windowFlags() | QtCore.Qt.WindowMinimizeButtonHint | QtCore.Qt.WindowSystemMenuHint)
    	
		self.btnRefresh.clicked.connect(self.serial_open)
		self.btnSet.clicked.connect(self.set)
		self.btnExit.clicked.connect(self.closeall)
		#self.cboxComport.addItem("bye")
    	#self.btnConnect.clicked.connect



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