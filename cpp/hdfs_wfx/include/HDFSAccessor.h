/*
 *    HDFSAccess.h file written and maintained by Calin Cocan
 *    Created on: Jun 5, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_HDFSACCESSOR_H_
#define INCLUDE_HDFSACCESSOR_H_

#include "FileEnumerator.h"
#include <jni.h>

class ProgressInfo;

class HDFSAccessor
{

public:
    static HDFSAccessor* instance()
    {
        return s_instance;
    }

    int initialize();
    void release();

    FileEnumerator* getFolderContent(char* path);

    bool mkdir(char* path);

    bool deletePath(char* path);

    bool rename(char* oldPath, char* newPath);

    bool copy(char* srcPath, char* destPath);

    bool getFile(char* remotePath, char* localPath, ProgressInfo* progressInfo);

    bool putFile(char* localPath, char* remotePath, bool overwrite, ProgressInfo* progressInfo);


private:
    HDFSAccessor();
    virtual ~HDFSAccessor();
    void initFileEnumerator(JNIEnv* env);
    void initProgressInfo(JNIEnv* env);

    jobject m_wfxPairObj;
    jclass m_nativeProgressClass;
    bool m_initialized;

    static HDFSAccessor* s_instance;

public:
    static jmethodID s_WfxPairMetIdInitFS;
    static jmethodID s_WfxPairMetIdGetFolderContent;
    static jmethodID s_WfxPairMetIdGetFileInfo;
    static jmethodID s_WfxPairMetIdMkDir;
    static jmethodID s_WfxPairMetIdDelPath;
    static jmethodID s_WfxPairMetIdRenPath;
    static jmethodID s_WfxPairMetIdCopyPath;
    static jmethodID s_WfxPairMetIdGetPath;
    static jmethodID s_WfxPairMetIdPutPath;

    static jmethodID s_NativeProgressConstructor;

    static jmethodID s_FileInfoGetFileAttributes;
    static jmethodID s_FileInfoGetFileCreationTime;
    static jmethodID s_FileInfoGetFileLastAccessTime;
    static jmethodID s_FileInfoGetFileSize;
    static jmethodID s_FileInfoGetReserved0;
};

#endif /* INCLUDE_HDFSACCESSOR_H_ */
