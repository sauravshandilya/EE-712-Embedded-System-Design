from PyQt4 import QtGui, QtCore
import sys
import os
import design
import serial
import glob

#global port_detect
#global port

class mygui(QtGui.QDialog, design.Ui_mainWindow):
	global port_detect
	global port
	global app


#**********************Communication/Serial Port Detection Starts*********************
	def serial_port_connection(port_detect):
		#global port

		print len(port_detect),"Ports detected" # print number of ports detected
	
		#------------- print all detectec ports - STARTS ---------#
		if (len(port_detect) != 0):				
			print "Port(s) detected is/are:"	
			
			for i in range (0,len(port_detect)):
				print port_detect[i]

		#self.cboxComport.addItems(port_detect)	
		#self.cboxComport.addItems(port_detect)	
		port = serial.Serial(port_detect[0],baudrate=9600)
		print "connected to: ", port_detect[0]					#-- change this as per input from comboxbox
		return
	#------------- print all detectec ports - END ---------#
	
#**********************Communication/Serial Port Detection Ends*********************
	#**********************Open Communication/Serial Port Starts*********************	
	def serial_open(self):
		#global port	
		port_detect = glob.glob("/dev/tty*") # stores all /dev/ttyACM* into a list port_detect
		
		try:
			if (len(port_detect) != 0):				
				print "Port(s) detected is/are:"	
				self.cboxComport.addItems(port_detect)

			#for i in range (0,len(port_detect)):
			#	print port_detect[i]

			port = serial.Serial(port_detect[0],baudrate=115200)
			print "connected to: ", port_detect[0]					#-- change this as per input from comboxbox		
		except:
			print "No USB port detected....check power and USB connection"
			sys.exit(0)
		port.close()

	def closeall(self):
		self.textStatus.append("Exiting")
		self.textStatus.append("---------------------------------")
		sys.exit(app.exec_())
		sys.exit(0)

	def set(self):
		self.textStatus.append("---------------------------------")
		text_cboxcomport = str(self.cboxComport.currentText())
		text_cboxfilterType = str(self.cboxFilterType.currentText())
		text_gaintext = str(self.textGain.text())
		#self.textStatus.setText("Hi")
		self.textStatus.append("Connected to: " + text_cboxcomport)
		self.textStatus.append("Filter Type: " + text_cboxfilterType)
		self.textStatus.append("Gain: " + text_gaintext)
		

		print self.cboxComport.currentText()
		print "set"	

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