# hdfs_wfx
=====

Description:
------------
Hadoop HDFS Double Commander / Tux Commander file system plugin


Version
-----------

0.1

Notes:
-----

The project is in early stages but is functional. Current version is built for Linux distribution and was tested with Xubuntu 15.04 x64 distribution   


Prerequires:
-----

	Linux
	Double Commander
	Java
	JAVA_HOME set to appropriate location
	Hadoop infrastructure
	Ant (optional used on install step)
	
	
	
Installation:
-----

1) Unzip the archive locate in hdfs_wfx/install/hdfs_wfx.zip on a local folder

2) 
Option 1:
	From unzip location run $> ant -f install.xml
Option 2
	Copy "plugins" folder from archive on $HOME/.config/doublecmd

	
3) In Double Commander menu go to Configuration -> Options -> Plugins -> File System Plugins (.wfx) -> Add -> OK

4) Done

Once installed the plugin should appear by accessing menu Commands -> Open VFS List or pressing its pair icon   

	