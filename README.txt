libqtavi GNU GPL v. 3.0
------------------------
AUTHOR: Ion Vasilief
------------------------
FEATURES: libqtavi enables Qt based applications to easily create and record video files in the AVI container format. 
————————————————————————————————————————————————————————————————————————————————————————————————————----------
DEPENDENCIES: In order to build libqtavi you need to install first the Qt framework (http://www.qt.io) and 
			  the libgwavi library (https://github.com/Rolinh/libgwavi) on your system.
————————————————————————————————————————————————————————————————————————————————————————————————————----------
LICENSE: GNU GPL v. 3.0 for open source applications. Otherwise you need a commercial license from IONDEV SRL (http://iondev.ro).
————————————————————————————————————————————————————————————————————————————————————————————————————----------
COMPILING: libqtavi uses qmake for the building process. 
	qmake is part of a Qt distribution: 
	qmake reads project files, that contain the options and rules how to build a certain project. 
	A project file ends with the suffix "*.pro". Please read the qmake documentation for more details.

After installing Qt and libgwavi on your system, type the following command lines: 
	$ cd libqtavi
	$ qmake
	$ make
————————————————————————————————————————————————————————————————————————————————————————————————————----------
USE: demo applications are provided in the “demos” folder of the source archive.
————————————————————————————————————————————————————————————————————————————————————————————————————----------
