//============================================================================
// Name        : hdfs_wfx_test.cpp
// Author      : Calin Cocan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "wfxplugin.h"
#include <dlfcn.h>

using namespace std;

int main() {
	cout << "Begin" << endl; // prints !!!Hello World!!!
	char name[100];

	FsGetDefRootName(name, 100);
	cout <<"Plugin Name: "<< name<<endl;

	FsInit(1, NULL, NULL,NULL);

	cout << "After FSInit";

	return 0;
}
