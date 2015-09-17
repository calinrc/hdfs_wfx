/*
 *    HDFSAccess.cpp file written and maintained by Calin Cocan
 *    Created on: Jun 5, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include <HDFSAccessor.h>
#include "gendef.h"
#include "JVMState.h"
#include <assert.h>
#include <string>
#include <set>

HDFSAccessor* HDFSAccessor::s_instance = new HDFSAccessor();
jmethodID HDFSAccessor::s_WfxPairMetIdConstructor = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdInitFS = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdGetFolderContent = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdGetFileInfo = NULL;

jmethodID HDFSAccessor::s_FileInfoGetFileAttributes = NULL;
jmethodID HDFSAccessor::s_FileInfoGetFileCreationTime = NULL;
jmethodID HDFSAccessor::s_FileInfoGetFileLastAccessTime = NULL;
jmethodID HDFSAccessor::s_FileInfoGetFileSize = NULL;
jmethodID HDFSAccessor::s_FileInfoGetReserved0 = NULL;

HDFSAccessor::HDFSAccessor() :
        m_wfxPairObj(NULL)
{

}

HDFSAccessor::~HDFSAccessor()
{
    release();
}

int HDFSAccessor::initialize()
{
    JNIEnv* env = JVMState::instance()->getEnv();
    jclass wfxPairClass = static_cast<jclass>(env->FindClass("hdfs_wfx_java/WfxPair"));
    if (!JVMState::instance()->exceptionExists(env))
    {
        s_WfxPairMetIdConstructor = env->GetMethodID(wfxPairClass, "<init>", "()V");
        assert(s_WfxPairMetIdConstructor != NULL);

        s_WfxPairMetIdInitFS = env->GetMethodID(wfxPairClass, "initFS", "()I");
        assert(s_WfxPairMetIdInitFS != NULL);

        s_WfxPairMetIdGetFolderContent = env->GetMethodID(wfxPairClass, "getFolderContent", "(Ljava/lang/String;)[Ljava/lang/String;");
        assert(s_WfxPairMetIdGetFolderContent != NULL);

        s_WfxPairMetIdGetFileInfo = env->GetMethodID(wfxPairClass, "getFileInformation",
                                                     "(Ljava/lang/String;Ljava/lang/String;)Lhdfs_wfx_java/FileInformation;");
        assert(s_WfxPairMetIdGetFileInfo != NULL);

        jobject wfxPairObj = env->NewObject(wfxPairClass, s_WfxPairMetIdConstructor);
        assert(wfxPairObj != NULL);
        m_wfxPairObj = env->NewGlobalRef(wfxPairObj);
        jint result = env->CallIntMethod(m_wfxPairObj, s_WfxPairMetIdInitFS);
        assert(result != 0);
        initFileEnumerator(env);

        env->DeleteLocalRef(wfxPairObj);
        env->DeleteLocalRef(wfxPairClass);
        return 0;
    } else
    {
        assert(false);
    }
    return -1;
}

void HDFSAccessor::initFileEnumerator(JNIEnv* env)
{
    jclass wfxFileInformationClass = static_cast<jclass>(env->FindClass("hdfs_wfx_java/FileInformation"));
    assert(wfxFileInformationClass != NULL);
    s_FileInfoGetFileAttributes = env->GetMethodID(wfxFileInformationClass, "getFileAttributes", "()I");
    assert(s_FileInfoGetFileAttributes != NULL);
    s_FileInfoGetFileCreationTime = env->GetMethodID(wfxFileInformationClass, "getFileCreationTime", "()J");
    assert(s_FileInfoGetFileCreationTime != NULL);
    s_FileInfoGetFileLastAccessTime = env->GetMethodID(wfxFileInformationClass, "getFileLastAccessTime", "()J");
    assert(s_FileInfoGetFileLastAccessTime != NULL);
    s_FileInfoGetFileSize = env->GetMethodID(wfxFileInformationClass, "getFileSize", "()J");
    assert(s_FileInfoGetFileSize != NULL);
    s_FileInfoGetReserved0 = env->GetMethodID(wfxFileInformationClass, "getReserved0", "()I");
    assert(s_FileInfoGetReserved0 != NULL);
}

void HDFSAccessor::release()
{
    JNIEnv* env = JVMState::instance()->getEnv();
    if (m_wfxPairObj != NULL)
    {
        env->DeleteGlobalRef(m_wfxPairObj);
        m_wfxPairObj = NULL;
    }

}

FileEnumerator* HDFSAccessor::getFolderContent(char* path)
{
    JNIEnv* env = JVMState::instance()->getEnv();
    if (m_wfxPairObj != NULL)
    {
        jstring pathStr = env->NewStringUTF(path);
        jobjectArray contentArray = static_cast<jobjectArray>(env->CallObjectMethod(m_wfxPairObj, s_WfxPairMetIdGetFolderContent, pathStr));
        env->DeleteLocalRef(pathStr);
        if (contentArray != NULL)
        {
            set<string> contentItems;
            jsize len = env->GetArrayLength(contentArray);
            for (jsize i = 0; i < len; i++)
            {
                jstring elem = static_cast<jstring>(env->GetObjectArrayElement(contentArray, i));
                if (elem != NULL)
                {
                    const char *str = env->GetStringUTFChars(elem, NULL);
                    string item(str);
                    contentItems.insert(item);
                    env->ReleaseStringUTFChars(elem, str);
                }
            }
            string pathStr(path);
            return new FileEnumerator(env, m_wfxPairObj, pathStr, contentItems);
        }
    }
    return NULL;
}
