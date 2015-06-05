/*
 *    hdfs_wfx.cpp file written and maintained by Calin Cocan
 *    Created on: May 15, 2015
 *
 *    Double Commander
 *   -------------------------------------------------------------------------
 *   WFX plugin for working with HDFS
 *
 *   Based on:
 *     GVFS plugin for Double Commander
 *     Copyright (C) 2009-2010  Koblov Alexander (Alexx2000@mail.ru)
 *
 *     and
 *
 *     GVFS plugin for Tux Commander
 *     Copyright (C) 2008-2009 Tomas Bzatek <tbzatek@users.sourceforge.net>*
 *
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
#include "Utilities.h"
#include "FileEnumerator.h"
#include "HDFSAccessor.h"

tProgressProc gProgressProc;
tRequestProc gRequestProc;

char logPath[MAX_PATH];
size_t pathSize = MAX_PATH;

int FsInit(int PluginNr, tProgressProc pProgressProc, tLogProc pLogProc, tRequestProc pRequestProc)
{
    gProgressProc = pProgressProc;
    gRequestProc = pRequestProc;
    Logger::getInstance()->init(false, true, pLogProc, PluginNr);
    LOGGING("FSInit");

    char logPath[MAX_PATH];
    size_t pathSize = MAX_PATH;
//    if (pRequestProc != NULL)
//    {
//        char returnedText[100];
//        strcpy(returnedText, "ReturnedTText");
//        BOOL rv = pRequestProc(PluginNr, 3, "CustomTitle", "CustomText", returnedText, 100);
//        LOGGING("requestProc val %d, message %s", rv, returnedText);
//    }
    JVMState::instance()->initialize(Utilities::getJavaClasspathDir(logPath, &pathSize));

    return 0;
}

HANDLE FsFindFirst(char* Path, WIN32_FIND_DATAA *FindData)
{
    LOGGING("FsFindFirst on path %s", Path);
    memset(FindData, 0, sizeof(WIN32_FIND_DATAA));
    FileEnumerator* fEnum = HDFSAccessor::instance()->getFolderContent(Path);
    HANDLE handle = NULL;
    if (fEnum->getFirst(FindData))
    {
        handle = fEnum;
    } else
    {
        delete fEnum;
    }

    return handle;
}

BOOL FsFindNext(HANDLE Hdl, WIN32_FIND_DATAA *FindData)
{
    LOGGING("FsFindNext");
    memset(FindData, 0, sizeof(WIN32_FIND_DATAA));
    FileEnumerator* fEnum = (FileEnumerator*) Hdl;
    bool retVal = fEnum->getNext(FindData);
    return retVal;
}

int FsFindClose(HANDLE Hdl)
{
    LOGGING("FsFindClose");
    if (Hdl != NULL)
    {
        FileEnumerator* fEnum = (FileEnumerator*) Hdl;
        delete fEnum;
        Hdl = NULL;
    }

    return FS_FILE_OK;
}

BOOL FsMkDir(char* Path)
{
    LOGGING("FsMkDir %s", Path);
    return 0;
}

BOOL FsRemoveDir(char* RemoteName)
{
    LOGGING("FsRemoveDir %s", RemoteName);
    return 0;
}

int FsRenMovFile(char* OldName, char* NewName, BOOL Move, BOOL OverWrite, RemoteInfoStruct* ri)
{
    LOGGING("FsRenMovFile oldName %s -> newName %s - Move: %d - Overwrite: %d", OldName, NewName, Move, OverWrite);
    return -1;
}

int FsGetFile(char* RemoteName, char* LocalName, int CopyFlags, RemoteInfoStruct* ri)
{
    LOGGING("FsGetFile");
    return -1;
}

int FsPutFile(char* LocalName, char* RemoteName, int CopyFlags)
{
    LOGGING("FsPutFile Local path %s in HDFS path %s with flags %d", LocalName, RemoteName, CopyFlags);
    return -1;
}

int FsExecuteFile(HWND MainWin, char* RemoteName, char* Verb)
{
    LOGGING("FsExecuteFile %s verb %s", RemoteName, Verb);
    return -1;
}

BOOL FsDeleteFile(char* RemoteName)
{
    LOGGING("FsDeleteFile %s", RemoteName);
    return 0;
}

BOOL FsSetTime(char* RemoteName, FILETIME *CreationTime, FILETIME *LastAccessTime, FILETIME *LastWriteTime)
{
    LOGGING("FsSetTime %s", RemoteName);
    return 0;
}

BOOL FsDisconnect(char *DisconnectRoot)
{
    LOGGING("FsDisconnect root %s", DisconnectRoot);
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
