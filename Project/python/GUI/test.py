import sys
from PyQt4.QtGui import *

def window(): 
	# Create an PyQT4 application object.
	app = QApplication(sys.argv)       
	 
	# The QWidget widget is the base class of all user interface objects in PyQt4. creates top level window. Add QLabel object in it.
	window1 = QWidget()
	 
	# Set window size. 
	# window1.resize(320, 240)
	window1.setGeometry (100,100,500,200)		#x_posiiton of window, y_position, Windowsize_x, Windowsize_y

	# Set window title  
	window1.setWindowTitle("Window Title") 
	 
	# create Label in window1
	label1 = QLabel(window1)
	#set Label Title
	label1.setText("Label Text")
	#set coordinate of Label
	label1.move(10,20)

	# Show window
	window1.show() 
	 
	sys.exit(app.exec_())
	
if __name__ == '__main__':
	window()
