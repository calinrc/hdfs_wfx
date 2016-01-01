/*
 *    hdfs_wfx_test.cpp file written and maintained by Calin Cocan
 *    Created on: Oct 05, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#include <iostream>
#include "wfxplugin.h"
#include <string.h>
#ifdef LINUX
#include <dlfcn.h>
#endif
#include <stdio.h>

using namespace std;

typedef void (*FsGetDefRootName_func)(char* DefRootName, int maxlen);
typedef int (*FsInit_func)(int PluginNr, tProgressProc pProgressProc, tLogProc pLogProc, tRequestProc pRequestProc);
typedef void (*FsSetDefaultParams_func)(FsDefaultParamStruct* dps);
typedef HANDLE (*FsFindFirst_func)(char* Path, WIN32_FIND_DATAA *FindData);
typedef BOOL (*FsFindNext_func)(HANDLE Hdl, WIN32_FIND_DATAA *FindData);
typedef int (*FsFindClose_func)(HANDLE Hdl);

HANDLE INVALID_HANDLE = (HANDLE) -1;

void printFileInfo(char* path, WIN32_FIND_DATAA* data)
{
    printf("Informations about path %s:\n", path);
    printf("\t FileName: %s\n\t dwFileAttributes: %d\n\t dwReserved0: %d\n", data->cFileName, data->dwFileAttributes, data->dwReserved0);
}

int main()
{
    cout << "Begin" << endl; // prints !!!Hello World!!!
    char name[100];

#ifdef LINUX
    void* handle = dlopen("../hdfs_wfx/Debug/hdfs_wfx.wfx", RTLD_LAZY);

    FsGetDefRootName_func FsGetDefRootName = (FsGetDefRootName_func) dlsym(handle, "FsGetDefRootName");
    FsInit_func FsInit = (FsInit_func) dlsym(handle, "FsInit");
    FsSetDefaultParams_func FsSetDefaultParams = (FsSetDefaultParams_func) dlsym(handle, "FsSetDefaultParams");
    FsFindFirst_func FsFindFirst = (FsFindFirst_func) dlsym(handle, "FsFindFirst");
    FsFindNext_func FsFindNext = (FsFindNext_func) dlsym(handle, "FsFindNext");
    FsFindClose_func FsFindClose = (FsFindClose_func) dlsym(handle, "FsFindClose");
#else
	FsGetDefRootName_func FsGetDefRootName = NULL;
	FsInit_func FsInit = NULL;
	FsSetDefaultParams_func FsSetDefaultParams = NULL;
	FsFindFirst_func FsFindFirst = NULL;
	FsFindNext_func FsFindNext = NULL;
	FsFindClose_func FsFindClose = NULL;
#endif 
    FsGetDefRootName(name, 100);

    cout << "Plugin Name: " << name << endl;

    FsInit(1, NULL, NULL, NULL);
    cout << "After FSInit";

    FsDefaultParamStruct dps;
    strcpy(dps.DefaultIniName, "Name1");
    dps.PluginInterfaceVersionHi = 3;
    dps.PluginInterfaceVersionLow = 2;
    dps.size = 5;

    FsSetDefaultParams(&dps);

    WIN32_FIND_DATAA FindData;
    memset(&FindData, 0, sizeof(WIN32_FIND_DATAA));

    char path[256] = { '/', '\0' };

    HANDLE h = FsFindFirst(path, &FindData);
    BOOL hasNext = true;
    if (h != NULL && h != INVALID_HANDLE)
    {
        while (hasNext)
        {
            printFileInfo(path, &FindData);
            hasNext = FsFindNext(h, &FindData);
        }
    }

    int closeResult = FsFindClose(h);
    printf("FsFindClose result %d", closeResult);

    return 0;
}
