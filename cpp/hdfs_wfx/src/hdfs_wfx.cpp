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

int gPluginNumber;
tProgressProc gProgressProc;
tLogProc gLogProc;
tRequestProc gRequestProc;

int DCPCALL FsInit(int PluginNr, tProgressProc pProgressProc, tLogProc pLogProc, tRequestProc pRequestProc)
{
    gProgressProc = pProgressProc;
    gLogProc = pLogProc;
    gRequestProc = pRequestProc;
    gPluginNumber = PluginNr;

    return 0;
}

HANDLE DCPCALL FsFindFirst(char* Path, WIN32_FIND_DATAA *FindData)
{
    HANDLE handle = NULL;
    return handle;
}

BOOL DCPCALL FsFindNext(HANDLE Hdl, WIN32_FIND_DATAA *FindData)
{
    return 0;
}

int DCPCALL FsFindClose(HANDLE Hdl)
{
    return FS_FILE_OK;
}

BOOL DCPCALL FsMkDir(char* Path)
{
    return 0;
}

BOOL DCPCALL FsRemoveDir(char* RemoteName)
{
    return 0;
}

int DCPCALL FsRenMovFile(char* OldName, char* NewName, BOOL Move, BOOL OverWrite, RemoteInfoStruct* ri)
{
    return -1;
}

int DCPCALL FsGetFile(char* RemoteName, char* LocalName, int CopyFlags, RemoteInfoStruct* ri)
{
    return -1;
}

int DCPCALL FsPutFile(char* LocalName, char* RemoteName, int CopyFlags)
{
    return -1;
}

int DCPCALL FsExecuteFile(HWND MainWin, char* RemoteName, char* Verb)
{
    return -1;
}

BOOL DCPCALL FsDeleteFile(char* RemoteName)
{
    return 0;
}

BOOL DCPCALL FsSetTime(char* RemoteName, FILETIME *CreationTime, FILETIME *LastAccessTime, FILETIME *LastWriteTime)
{
    return 0;
}

BOOL DCPCALL FsDisconnect(char *DisconnectRoot)
{
    return 0;
}

void DCPCALL FsSetDefaultParams(FsDefaultParamStruct* dps)
{
}

void DCPCALL FsGetDefRootName(char* DefRootName, int maxlen)
{

}
