/*
 *    hdfs_wfx.cpp file written and maintained by Calin Cocan
 *    Created on: May 15, 2015
 *
 *    Double Commander
 *   -------------------------------------------------------------------------
 *   WFX plugin for working with HDFS
 *
 *   Based on:
 *     GVFS plugin for Tux Commander
 *     Copyright (C) 2008-2009 Tomas Bzatek <tbzatek@users.sourceforge.net>*
 *
 *     and
 *
 *     GVFS plugin for Double cOMMANDER
 *     Copyright (C) 2009-2010  Koblov Alexander (Alexx2000@mail.ru)
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include "wfxplugin.h"
#include <stddef.h>
#include <string.h>
#include "JVMState.h"
#include "gendef.h"
#include "Logger.h"

int gPluginNumber;
tProgressProc gProgressProc;
tLogProc gLogProc;
tRequestProc gRequestProc;

int FsInit(int PluginNr, tProgressProc pProgressProc, tLogProc pLogProc, tRequestProc pRequestProc)
{
    gProgressProc = pProgressProc;
    gLogProc = pLogProc;
    gRequestProc = pRequestProc;
    gPluginNumber = PluginNr;
    Logger::getInstance()->init(false, true);
    LOGGING("FSInit");
    JVMState::instance()->initialize(CLASS_PATH);

    return 0;
}

HANDLE FsFindFirst(char* Path, WIN32_FIND_DATAA *FindData)
{
    LOGGING("FsFindFirst");
    HANDLE handle = NULL;
    return handle;
}

BOOL FsFindNext(HANDLE Hdl, WIN32_FIND_DATAA *FindData)
{
    LOGGING("FsFindNext");
    return 0;
}

int FsFindClose(HANDLE Hdl)
{
    LOGGING("FsFindClose");
    if (Hdl != NULL)
    {
        //delete Hdl;
        Hdl = NULL;
    }

    return FS_FILE_OK;
}

BOOL FsMkDir(char* Path)
{
    LOGGING("FsMkDir");
    return 0;
}

BOOL FsRemoveDir(char* RemoteName)
{
    LOGGING("FsRemoveDir");
    return 0;
}

int FsRenMovFile(char* OldName, char* NewName, BOOL Move, BOOL OverWrite, RemoteInfoStruct* ri)
{
    LOGGING("FsRenMovFile");
    return -1;
}

int FsGetFile(char* RemoteName, char* LocalName, int CopyFlags, RemoteInfoStruct* ri)
{
    LOGGING("FsGetFile");
    return -1;
}

int FsPutFile(char* LocalName, char* RemoteName, int CopyFlags)
{
    LOGGING("FsPutFile");
    return -1;
}

int FsExecuteFile(HWND MainWin, char* RemoteName, char* Verb)
{
    LOGGING("FsExecuteFile");
    return -1;
}

BOOL FsDeleteFile(char* RemoteName)
{
    LOGGING("FsDeleteFile");
    return 0;
}

BOOL FsSetTime(char* RemoteName, FILETIME *CreationTime, FILETIME *LastAccessTime, FILETIME *LastWriteTime)
{
    LOGGING("FsSetTime");
    return 0;
}

BOOL FsDisconnect(char *DisconnectRoot)
{
    LOGGING("FsDisconnect");
    JVMState::instance()->detach();
    return 0;
}

void FsSetDefaultParams(FsDefaultParamStruct* dps)
{
    LOGGING("FsSetDefaultParams");
}

void FsGetDefRootName(char* DefRootName, int maxlen)
{
    Logger::getInstance()->init(false, true);
    LOGGING("FsGetDefRootName");
    strncpy(DefRootName, "HDFS", maxlen);
}
