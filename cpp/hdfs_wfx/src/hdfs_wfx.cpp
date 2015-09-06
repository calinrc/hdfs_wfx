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
    HDFSAccessor::instance()->initialize();


    return 0;
}

/*
static void GFileInfoToWin32FindData (GFile *reference_file, GFileInfo *info, WIN32_FIND_DATAA *FindData)
{
  GFileInfo *symlink_info = NULL;
  GError *error = NULL;

  g_assert (info != NULL);
  g_assert (FindData != NULL);

  g_strlcpy(FindData->cFileName, g_file_info_get_name (info), MAX_PATH);
  // File size
  goffset filesize = g_file_info_get_size (info);
  FindData->nFileSizeLow = (DWORD)filesize;
  FindData->nFileSizeHigh = filesize >> 32;
  // File attributes
  FindData->dwFileAttributes |= FILE_ATTRIBUTE_UNIX_MODE;
  FindData->dwReserved0 = g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_MODE);
  // File date/time
  if (!UnixTimeToFileTime(g_file_info_get_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_MODIFIED), &FindData->ftLastWriteTime))
    {
          FindData->ftLastWriteTime.dwHighDateTime = 0xFFFFFFFF;
          FindData->ftLastWriteTime.dwLowDateTime = 0xFFFFFFFE;
    }
  if (!UnixTimeToFileTime(g_file_info_get_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_ACCESS), &FindData->ftLastAccessTime))
    {
          FindData->ftLastAccessTime.dwHighDateTime = 0xFFFFFFFF;
          FindData->ftLastAccessTime.dwLowDateTime = 0xFFFFFFFE;
    }
  if (!UnixTimeToFileTime(g_file_info_get_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_CREATED), &FindData->ftCreationTime))
    {
          FindData->ftCreationTime.dwHighDateTime = 0xFFFFFFFF;
          FindData->ftCreationTime.dwLowDateTime = 0xFFFFFFFE;
    }

//  g_print ("(II) GFileInfoToWin32FindData: type = %d\n", g_file_info_get_file_type (info));
//  g_print ("(II) GFileInfoToWin32FindData: UNIX_MODE = %d\n", FindData->dwReserved0);

  switch (g_file_info_get_file_type (info)) {
      case G_FILE_TYPE_DIRECTORY:
      case G_FILE_TYPE_SHORTCUT:   //  Used in network:///
      case G_FILE_TYPE_MOUNTABLE:
        FindData->dwFileAttributes |= FILE_ATTRIBUTE_DIRECTORY;
        break;
      case G_FILE_TYPE_SYMBOLIC_LINK:
        FindData->dwReserved0 |= S_IFLNK;

        // Check: file is symlink to directory
        symlink_info = g_file_query_info (reference_file, G_FILE_ATTRIBUTE_UNIX_MODE,
                                          G_FILE_QUERY_INFO_NONE, NULL, &error);

        if (error) {
          g_print ("(EE) GFileInfoToWin32FindData: g_file_query_info() error: %s\n", error->message);
          g_error_free (error);
        }

        if (symlink_info)
    {
          if (g_file_info_get_file_type (symlink_info) == G_FILE_TYPE_DIRECTORY)
      {
        FindData->dwFileAttributes |= FILE_ATTRIBUTE_REPARSE_POINT;
      }
      g_object_unref (symlink_info);
    }
        break;
      case G_FILE_TYPE_UNKNOWN:
      case G_FILE_TYPE_REGULAR:
      case G_FILE_TYPE_SPECIAL:
    break;
    }

    //fallback to default file mode if read fails
  if (FindData->dwReserved0 == 0) {
    if ((FindData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
      FindData->dwReserved0 = S_IFDIR + S_IRWXU + S_IRGRP + S_IXGRP + S_IROTH + S_IXOTH;
    else
      FindData->dwReserved0 = S_IRUSR + S_IWUSR + S_IRGRP + S_IROTH;
  }
}
*/

HANDLE FsFindFirst(char* Path, WIN32_FIND_DATAA *FindData)
{
    LOGGING("FsFindFirst on path %s", Path);
    memset(FindData, 0, sizeof(WIN32_FIND_DATAA));
    FileEnumerator* fEnum = HDFSAccessor::instance()->getFolderContent(Path);
    HANDLE handle = (HANDLE)(-1);
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
