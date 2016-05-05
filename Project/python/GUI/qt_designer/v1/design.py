# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'test_v1-Widgetwindow.ui'
#
# Created: Sat Apr 23 15:07:03 2016
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

class Ui_mainWindow(object):
    def setupUi(self, mainWindow):
        mainWindow.setObjectName(_fromUtf8("mainWindow"))
        mainWindow.resize(563, 257)
        self.gridLayout = QtGui.QGridLayout(mainWindow)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.btnRefresh = QtGui.QPushButton(mainWindow)
        self.btnRefresh.setObjectName(_fromUtf8("btnRefresh"))
        self.gridLayout.addWidget(self.btnRefresh, 0, 6, 1, 1)
        self.textStatus = QtGui.QTextBrowser(mainWindow)
        self.textStatus.setObjectName(_fromUtf8("textStatus"))
        self.gridLayout.addWidget(self.textStatus, 9, 2, 1, 1)
        self.labelFilterType = QtGui.QLabel(mainWindow)
        self.labelFilterType.setTextFormat(QtCore.Qt.RichText)
        self.labelFilterType.setObjectName(_fromUtf8("labelFilterType"))
        self.gridLayout.addWidget(self.labelFilterType, 1, 0, 1, 2)
        self.textGain = QtGui.QLineEdit(mainWindow)
        self.textGain.setObjectName(_fromUtf8("textGain"))
        self.gridLayout.addWidget(self.textGain, 4, 2, 1, 1)
        self.cboxComport = QtGui.QComboBox(mainWindow)
        self.cboxComport.setObjectName(_fromUtf8("cboxComport"))
        self.gridLayout.addWidget(self.cboxComport, 0, 2, 1, 1)
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem, 6, 2, 1, 1)
        self.labelGain = QtGui.QLabel(mainWindow)
        self.labelGain.setTextFormat(QtCore.Qt.RichText)
        self.labelGain.setObjectName(_fromUtf8("labelGain"))
        self.gridLayout.addWidget(self.labelGain, 4, 1, 1, 1)
        self.btnSet = QtGui.QPushButton(mainWindow)
        self.btnSet.setObjectName(_fromUtf8("btnSet"))
        self.gridLayout.addWidget(self.btnSet, 1, 6, 1, 1)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.gridLayout.addLayout(self.horizontalLayout, 4, 4, 1, 1)
        self.labelStatus = QtGui.QLabel(mainWindow)
        self.labelStatus.setObjectName(_fromUtf8("labelStatus"))
        self.gridLayout.addWidget(self.labelStatus, 9, 1, 1, 1)
        self.cboxFilterType = QtGui.QComboBox(mainWindow)
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
        self.gridLayout.addWidget(self.cboxFilterType, 1, 2, 1, 1)
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.gridLayout.addLayout(self.horizontalLayout_2, 2, 6, 1, 1)
        self.btnExit = QtGui.QPushButton(mainWindow)
        self.btnExit.setObjectName(_fromUtf8("btnExit"))
        self.gridLayout.addWidget(self.btnExit, 4, 6, 1, 1)
        self.labelcom = QtGui.QLabel(mainWindow)
        self.labelcom.setEnabled(True)
        self.labelcom.setTextFormat(QtCore.Qt.RichText)
        self.labelcom.setObjectName(_fromUtf8("labelcom"))
        self.gridLayout.addWidget(self.labelcom, 0, 1, 1, 1)

        self.retranslateUi(mainWindow)
        QtCore.QMetaObject.connectSlotsByName(mainWindow)

    def retranslateUi(self, mainWindow):
        mainWindow.setWindowTitle(_translate("mainWindow", "Pseudo Random Noise Generator", None))
        self.btnRefresh.setText(_translate("mainWindow", "Refresh", None))
        self.labelFilterType.setText(_translate("mainWindow", "Filter Type", None))
        self.labelGain.setText(_translate("mainWindow", "Gain", None))
        self.btnSet.setText(_translate("mainWindow", "Set", None))
        self.labelStatus.setText(_translate("mainWindow", "Status", None))
        self.cboxFilterType.setItemText(0, _translate("mainWindow", "Allpass", None))
        self.cboxFilterType.setItemText(1, _translate("mainWindow", "Bandpass -  (1-51KHz)", None))
        self.cboxFilterType.setItemText(2, _translate("mainWindow", "Bandpass -  (51-101KHz)", None))
        self.cboxFilterType.setItemText(3, _translate("mainWindow", "Bandpass -  (101-151KHz)", None))
        self.cboxFilterType.setItemText(4, _translate("mainWindow", "Bandpass -  (151-201KHz)", None))
        self.cboxFilterType.setItemText(5, _translate("mainWindow", "Bandpass -  (201-251KHz)", None))
        self.cboxFilterType.setItemText(6, _translate("mainWindow", "Bandpass -  (251-301KHz)", None))
        self.cboxFilterType.setItemText(7, _translate("mainWindow", "Bandpass -  (301-351KHz)", None))
        self.cboxFilterType.setItemText(8, _translate("mainWindow", "Bandpass -  (351-401KHz)", None))
        self.cboxFilterType.setItemText(9, _translate("mainWindow", "Bandpass -  (401-451KHz)", None))
        self.cboxFilterType.setItemText(10, _translate("mainWindow", "Bandpass -  (451-501KHz)", None))
        self.btnExit.setText(_translate("mainWindow", "Exit", None))
        self.labelcom.setText(_translate("mainWindow", "COM", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    mainWindow = QtGui.QDialog()
    ui = Ui_mainWindow()
    ui.setupUi(mainWindow)
    mainWindow.show()
    sys.exit(app.exec_())

