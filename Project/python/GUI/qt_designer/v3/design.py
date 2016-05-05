# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'uidesign.ui'
#
# Created: Mon May  2 07:16:06 2016
#      by: PyQt4 UI code generator 4.10.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(687, 559)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.gridLayout = QtGui.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.gridLayout_5 = QtGui.QGridLayout()
        self.gridLayout_5.setObjectName(_fromUtf8("gridLayout_5"))

        # Connect Button
        self.btnSet = QtGui.QPushButton(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(12)
        self.btnSet.setFont(font)
        self.btnSet.setObjectName(_fromUtf8("btnSet"))
        self.gridLayout_5.addWidget(self.btnSet, 4, 3, 1, 1)

        #com port dropdown
        self.cboxComport = QtGui.QComboBox(self.centralwidget)
        self.cboxComport.setObjectName(_fromUtf8("cboxComport"))
        self.gridLayout_5.addWidget(self.cboxComport, 1, 3, 1, 1)

        #Console window
        self.textStatus = QtGui.QTextBrowser(self.centralwidget)
        self.textStatus.setMouseTracking(False)
        self.textStatus.setObjectName(_fromUtf8("textStatus"))
        self.gridLayout_5.addWidget(self.textStatus, 8, 0, 4, 4)

        #label - comport
        self.labelcom = QtGui.QLabel(self.centralwidget)
        self.labelcom.setEnabled(True)
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.labelcom.setFont(font)
        self.labelcom.setTextFormat(QtCore.Qt.RichText)
        self.labelcom.setObjectName(_fromUtf8("labelcom"))
        self.gridLayout_5.addWidget(self.labelcom, 0, 3, 1, 1)

        # dial - fc
        self.fc = QtGui.QDial(self.centralwidget)
        self.fc.setMaximum(20)
        self.fc.setWrapping(False)
        self.fc.setNotchesVisible(True)
        self.fc.setObjectName(_fromUtf8("fc"))
        self.gridLayout_5.addWidget(self.fc, 1, 0, 3, 3)

        # Refresh Button
        self.btnRefresh = QtGui.QPushButton(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setBold(False)
        font.setWeight(50)
        self.btnRefresh.setFont(font)
        self.btnRefresh.setObjectName(_fromUtf8("btnRefresh"))
        self.gridLayout_5.addWidget(self.btnRefresh, 3, 3, 1, 1)

        #Label Console
        self.labelStatus = QtGui.QLabel(self.centralwidget)
        self.labelStatus.setEnabled(True)
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.labelStatus.setFont(font)
        self.labelStatus.setObjectName(_fromUtf8("labelStatus"))
        self.gridLayout_5.addWidget(self.labelStatus, 7, 0, 1, 4)

        # Exit button
        self.btnExit = QtGui.QPushButton(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(12)
        self.btnExit.setFont(font)
        self.btnExit.setObjectName(_fromUtf8("btnExit"))
        self.gridLayout_5.addWidget(self.btnExit, 5, 3, 1, 1)

        #label fc
        self.labelfc = QtGui.QLabel(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.labelfc.setFont(font)
        self.labelfc.setObjectName(_fromUtf8("labelfc"))
        self.gridLayout_5.addWidget(self.labelfc, 0, 0, 1, 3)

        #gropbox
        self.groupBox = QtGui.QGroupBox(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.groupBox.setFont(font)
        self.groupBox.setFlat(True)
        self.groupBox.setCheckable(False)
        self.groupBox.setObjectName(_fromUtf8("groupBox"))
        self.radio_lp1 = QtGui.QRadioButton(self.groupBox)
        self.radio_lp1.setGeometry(QtCore.QRect(130, 0, 110, 26))
        self.radio_lp1.setObjectName(_fromUtf8("radio_lp1"))
        self.radio_lp2 = QtGui.QRadioButton(self.groupBox)
        self.radio_lp2.setGeometry(QtCore.QRect(130, 30, 110, 26))
        self.radio_lp2.setObjectName(_fromUtf8("radio_lp2"))
        self.radio_lp3 = QtGui.QRadioButton(self.groupBox)
        self.radio_lp3.setGeometry(QtCore.QRect(130, 60, 131, 26))
        self.radio_lp3.setObjectName(_fromUtf8("radio_lp3"))
        self.radio_lp3.setChecked(True)
        self.gridLayout_5.addWidget(self.groupBox, 5, 0, 3, 2)

        #label - min
        self.labelmin_value = QtGui.QLabel(self.centralwidget)
        self.labelmin_value.setObjectName(_fromUtf8("labelmin_value"))
        self.gridLayout_5.addWidget(self.labelmin_value, 3, 1, 1, 1)

        #label - max
        self.labelmax_value = QtGui.QLabel(self.centralwidget)
        self.labelmax_value.setObjectName(_fromUtf8("labelmax_value"))
        self.gridLayout_5.addWidget(self.labelmax_value, 3, 2, 1, 1)

        self.gridLayout.addLayout(self.gridLayout_5, 0, 0, 2, 3)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "Programmable Noise Generator", None))
        self.btnSet.setText(_translate("MainWindow", "Connect", None))
        self.labelcom.setText(_translate("MainWindow", "COM", None))
        self.btnRefresh.setText(_translate("MainWindow", "Refresh", None))
        self.labelStatus.setText(_translate("MainWindow", "Console", None))
        self.btnExit.setText(_translate("MainWindow", "Exit", None))
        self.labelfc.setText(_translate("MainWindow", "Cut Off Frequency", None))
        self.groupBox.setTitle(_translate("MainWindow", "Lowpass Filter", None))
        self.radio_lp1.setText(_translate("MainWindow", "LP-30 KHz", None))
        self.radio_lp2.setText(_translate("MainWindow", "LP-65 KHz", None))
        self.radio_lp3.setText(_translate("MainWindow", "LP-100 KHz", None))
        self.labelmin_value.setText(_translate("MainWindow", "Min.", None))
        self.labelmax_value.setText(_translate("MainWindow", "Max.", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    MainWindow = QtGui.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

