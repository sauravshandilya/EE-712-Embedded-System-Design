# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'uidesign.ui'
#
# Created: Sat Apr 23 15:08:46 2016
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
        MainWindow.resize(563, 257)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.gridLayout = QtGui.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.gridLayout.addLayout(self.horizontalLayout_2, 0, 0, 1, 1)
        self.labelcom = QtGui.QLabel(self.centralwidget)
        self.labelcom.setEnabled(True)
        self.labelcom.setTextFormat(QtCore.Qt.RichText)
        self.labelcom.setObjectName(_fromUtf8("labelcom"))
        self.gridLayout.addWidget(self.labelcom, 1, 1, 1, 1)
        self.cboxComport = QtGui.QComboBox(self.centralwidget)
        self.cboxComport.setObjectName(_fromUtf8("cboxComport"))
        self.gridLayout.addWidget(self.cboxComport, 1, 2, 1, 1)
        self.btnRefresh = QtGui.QPushButton(self.centralwidget)
        self.btnRefresh.setObjectName(_fromUtf8("btnRefresh"))
        self.gridLayout.addWidget(self.btnRefresh, 1, 3, 1, 1)
        self.labelFilterType = QtGui.QLabel(self.centralwidget)
        self.labelFilterType.setTextFormat(QtCore.Qt.RichText)
        self.labelFilterType.setObjectName(_fromUtf8("labelFilterType"))
        self.gridLayout.addWidget(self.labelFilterType, 2, 1, 1, 1)
        self.cboxFilterType = QtGui.QComboBox(self.centralwidget)
        self.cboxFilterType.setObjectName(_fromUtf8("cboxFilterType"))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.addItem(_fromUtf8(""))
        self.cboxFilterType.setItemText(11, _fromUtf8(""))
        self.gridLayout.addWidget(self.cboxFilterType, 2, 2, 1, 1)
        self.btnSet = QtGui.QPushButton(self.centralwidget)
        self.btnSet.setObjectName(_fromUtf8("btnSet"))
        self.gridLayout.addWidget(self.btnSet, 2, 3, 1, 1)
        self.labelGain = QtGui.QLabel(self.centralwidget)
        self.labelGain.setTextFormat(QtCore.Qt.RichText)
        self.labelGain.setObjectName(_fromUtf8("labelGain"))
        self.gridLayout.addWidget(self.labelGain, 3, 1, 1, 1)
        self.textGain = QtGui.QLineEdit(self.centralwidget)
        self.textGain.setObjectName(_fromUtf8("textGain"))
        self.gridLayout.addWidget(self.textGain, 3, 2, 1, 1)
        self.btnExit = QtGui.QPushButton(self.centralwidget)
        self.btnExit.setObjectName(_fromUtf8("btnExit"))
        self.gridLayout.addWidget(self.btnExit, 3, 3, 1, 1)
        spacerItem = QtGui.QSpacerItem(367, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem, 4, 2, 1, 1)
        self.labelStatus = QtGui.QLabel(self.centralwidget)
        self.labelStatus.setObjectName(_fromUtf8("labelStatus"))
        self.gridLayout.addWidget(self.labelStatus, 5, 1, 1, 1)
        self.textStatus = QtGui.QTextBrowser(self.centralwidget)
        self.textStatus.setObjectName(_fromUtf8("textStatus"))
        self.gridLayout.addWidget(self.textStatus, 5, 2, 1, 1)
        self.layoutWidget_2 = QtGui.QWidget(self.centralwidget)
        self.layoutWidget_2.setGeometry(QtCore.QRect(0, 0, 2, 2))
        self.layoutWidget_2.setObjectName(_fromUtf8("layoutWidget_2"))
        self.horizontalLayout_3 = QtGui.QHBoxLayout(self.layoutWidget_2)
        self.horizontalLayout_3.setMargin(0)
        self.horizontalLayout_3.setObjectName(_fromUtf8("horizontalLayout_3"))
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "Pseudo Random Noise Generator", None))
        self.labelcom.setText(_translate("MainWindow", "COM", None))
        self.btnRefresh.setText(_translate("MainWindow", "Refresh", None))
        self.labelFilterType.setText(_translate("MainWindow", "Filter Type", None))
        self.cboxFilterType.setItemText(0, _translate("MainWindow", "Allpass", None))
        self.cboxFilterType.setItemText(1, _translate("MainWindow", "Bandpass -  (1-101KHz)", None))
        self.cboxFilterType.setItemText(2, _translate("MainWindow", "Bandpass -  (101-201KHz)", None))
        self.cboxFilterType.setItemText(3, _translate("MainWindow", "Bandpass -  (201-301KHz)", None))
        self.cboxFilterType.setItemText(4, _translate("MainWindow", "Bandpass -  (301-401KHz)", None))
        self.cboxFilterType.setItemText(5, _translate("MainWindow", "Bandpass -  (401-501KHz)", None))
        self.cboxFilterType.setItemText(6, _translate("MainWindow", "Bandpass -  (501-601KHz)", None))
        self.cboxFilterType.setItemText(7, _translate("MainWindow", "Bandpass -  (601-701KHz)", None))
        self.cboxFilterType.setItemText(8, _translate("MainWindow", "Bandpass -  (701-801KHz)", None))
        self.cboxFilterType.setItemText(9, _translate("MainWindow", "Bandpass -  (801-901KHz)", None))
        #self.cboxFilterType.setItemText(10, _translate("MainWindow", "Bandpass -  (451-501KHz)", None))
        self.btnSet.setText(_translate("MainWindow", "Set", None))
        self.labelGain.setText(_translate("MainWindow", "Gain", None))
        self.btnExit.setText(_translate("MainWindow", "Exit", None))
        self.labelStatus.setText(_translate("MainWindow", "Status", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    MainWindow = QtGui.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

