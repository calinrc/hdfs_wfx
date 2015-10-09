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
#include "Utilities.h"
#include "Logger.h"
#include <assert.h>
#include <string>
#include <string.h>
#include <set>

HDFSAccessor* HDFSAccessor::s_instance = new HDFSAccessor();
jmethodID HDFSAccessor::s_WfxPairMetIdInitFS = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdGetFolderContent = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdGetFileInfo = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdMkDir = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdDelPath = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdRenPath = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdCopyPath = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdGetPath = NULL;
jmethodID HDFSAccessor::s_WfxPairMetIdPutPath = NULL;

jmethodID HDFSAccessor::s_FileInfoGetFileAttributes = NULL;
jmethodID HDFSAccessor::s_FileInfoGetFileCreationTime = NULL;
jmethodID HDFSAccessor::s_FileInfoGetFileLastAccessTime = NULL;
jmethodID HDFSAccessor::s_FileInfoGetFileSize = NULL;
jmethodID HDFSAccessor::s_FileInfoGetReserved0 = NULL;

HDFSAccessor::HDFSAccessor() :
        m_wfxPairObj(NULL), m_initialized(false)
{

}

HDFSAccessor::~HDFSAccessor()
{
    release();
}

int HDFSAccessor::initialize()
{
    if (!m_initialized)
    {
        char dependenciesPath[MAX_PATH];
        size_t pathSize = MAX_PATH;
        memset(dependenciesPath, 0, sizeof(dependenciesPath));
        bool isNewEnv = false;
        JNIEnv* env = JVMState::instance()->getEnv(&isNewEnv);
        Utilities::getJavaDependenciesPath(dependenciesPath, &pathSize);

        jclass wfxLauncherClass = static_cast<jclass>(env->FindClass("org/cgc/wfx/FSClientLauncher"));
        if (JVMState::instance()->exceptionExists(env) || wfxLauncherClass == NULL)
        {
            LOGGING("Unable to find Java launcher jar %s", JAVA_LAUNCHER_VAL)
            assert(false);
        }
        jstring depsPathStr = env->NewStringUTF(dependenciesPath);
        jmethodID getPairInstanceMethodId = env->GetStaticMethodID(wfxLauncherClass, "getPairInstance", "(Ljava/lang/String;)Lorg/cgc/wfx/WfxPair;");
        assert(getPairInstanceMethodId != NULL);

        jobject wfxPairObj = env->CallStaticObjectMethod(wfxLauncherClass, getPairInstanceMethodId, depsPathStr);

        if (!JVMState::instance()->exceptionExists(env) && wfxPairObj != NULL)
        {
            jclass wfxPairClass = env->GetObjectClass(wfxPairObj);

            s_WfxPairMetIdInitFS = env->GetMethodID(wfxPairClass, "initFS", "()V");
            assert(s_WfxPairMetIdInitFS != NULL);

            s_WfxPairMetIdGetFolderContent = env->GetMethodID(wfxPairClass, "getFolderContent", "(Ljava/lang/String;)[Ljava/lang/String;");
            assert(s_WfxPairMetIdGetFolderContent != NULL);

            s_WfxPairMetIdGetFileInfo = env->GetMethodID(wfxPairClass, "getFileInformation", "(Ljava/lang/String;Ljava/lang/String;)Lorg/cgc/wfx/FileInformation;");
            assert(s_WfxPairMetIdGetFileInfo != NULL);

            s_WfxPairMetIdMkDir = env->GetMethodID(wfxPairClass, "mkDir", "(Ljava/lang/String;)Z");
            assert(s_WfxPairMetIdMkDir != NULL);

            s_WfxPairMetIdDelPath = env->GetMethodID(wfxPairClass, "deletePath", "(Ljava/lang/String;)Z");
            assert(s_WfxPairMetIdDelPath != NULL);

            s_WfxPairMetIdRenPath = env->GetMethodID(wfxPairClass, "renamePath", "(Ljava/lang/String;Ljava/lang/String;)Z");
            assert(s_WfxPairMetIdRenPath != NULL);

            s_WfxPairMetIdCopyPath = env->GetMethodID(wfxPairClass, "copyPath", "(Ljava/lang/String;Ljava/lang/String;)Z");
            assert(s_WfxPairMetIdCopyPath != NULL);

            s_WfxPairMetIdGetPath = env->GetMethodID(wfxPairClass, "getFile", "(Ljava/lang/String;Ljava/lang/String;)V");
            assert(s_WfxPairMetIdGetPath != NULL);

            s_WfxPairMetIdPutPath = env->GetMethodID(wfxPairClass, "putFile", "(Ljava/lang/String;Ljava/lang/String;Z)V");
            assert(s_WfxPairMetIdPutPath != NULL);

            initFileEnumerator(env);

            if (!JVMState::instance()->exceptionExists(env))
            {
                m_wfxPairObj = env->NewGlobalRef(wfxPairObj);
                env->CallVoidMethod(m_wfxPairObj, s_WfxPairMetIdInitFS);
                if (JVMState::instance()->exceptionExists(env))
                {
                    assert(false);
                }
            } else
            {
                LOGGING("Fail on obtaining WfxPair instance. Please check the existence of hdfs_wfx.jar inside of ~/.config/doublecmd/plugins/hdfs_wfx/java/deps/ folder")
                assert(false);
            }
            env->DeleteLocalRef(depsPathStr);
            env->DeleteLocalRef(wfxPairObj);
            env->DeleteLocalRef(wfxPairClass);
            env->DeleteLocalRef(wfxLauncherClass);
            if (isNewEnv)
            {
                JVMState::instance()->releaseEnv();
            }
            m_initialized = true;
            return 0;
        } else
        {
            LOGGING("Unable to find Java launcher jar %s and its WfxPair class", JAVA_LAUNCHER_VAL)
            assert(false);
        }
        if (isNewEnv)
        {
            JVMState::instance()->releaseEnv();
        }
        return -1;
    } else
    {
        return 0;
    }
}

void HDFSAccessor::initFileEnumerator(JNIEnv* env)
{
    jclass wfxFileInformationClass = static_cast<jclass>(env->FindClass("org/cgc/wfx/FileInformation"));
    if (!JVMState::instance()->exceptionExists(env))
    {
        s_FileInfoGetFileAttributes = env->GetMethodID(wfxFileInformationClass, "getFileAttributes", "()J");
        assert(s_FileInfoGetFileAttributes != NULL);
        s_FileInfoGetFileCreationTime = env->GetMethodID(wfxFileInformationClass, "getFileCreationTime", "()J");
        assert(s_FileInfoGetFileCreationTime != NULL);
        s_FileInfoGetFileLastAccessTime = env->GetMethodID(wfxFileInformationClass, "getFileLastAccessTime", "()J");
        assert(s_FileInfoGetFileLastAccessTime != NULL);
        s_FileInfoGetFileSize = env->GetMethodID(wfxFileInformationClass, "getFileSize", "()J");
        assert(s_FileInfoGetFileSize != NULL);
        s_FileInfoGetReserved0 = env->GetMethodID(wfxFileInformationClass, "getReserved0", "()J");
        assert(s_FileInfoGetReserved0 != NULL);
    } else
    {
        assert(false);
    }
}

void HDFSAccessor::release()
{
    bool isNewEnv = false;
    JNIEnv* env = JVMState::instance()->getEnv(&isNewEnv);
    if (m_wfxPairObj != NULL)
    {
        env->DeleteGlobalRef(m_wfxPairObj);
        m_wfxPairObj = NULL;
    }
    if (isNewEnv)
    {
        JVMState::instance()->releaseEnv();
    }
    m_initialized = false;
}

FileEnumerator* HDFSAccessor::getFolderContent(char* path)
{
    bool isNewEnv = false;
    JNIEnv* env = JVMState::instance()->getEnv(&isNewEnv);
    if (m_wfxPairObj != NULL)
    {
        jstring pathStr = env->NewStringUTF(path);
        jobjectArray contentArray = static_cast<jobjectArray>(env->CallObjectMethod(m_wfxPairObj, s_WfxPairMetIdGetFolderContent, pathStr));
        if (!JVMState::instance()->exceptionExists(env))
        {
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
                if (isNewEnv)
                {
                    JVMState::instance()->releaseEnv();
                }
                jobject neObj = env->NewGlobalRef(m_wfxPairObj);
                if (isNewEnv)
                {
                    JVMState::instance()->releaseEnv();
                }
                return new FileEnumerator(neObj, pathStr, contentItems);
            }
        } else
        {
            env->DeleteLocalRef(pathStr);
        }
    }
    if (isNewEnv)
    {
        JVMState::instance()->releaseEnv();
    }

    return NULL;
}

bool HDFSAccessor::mkdir(char* path)
{
    bool isNewEnv = false;
    JNIEnv* env = JVMState::instance()->getEnv(&isNewEnv);
    if (m_wfxPairObj != NULL)
    {
        jstring pathStr = env->NewStringUTF(path);
        jboolean retVal = env->CallBooleanMethod(m_wfxPairObj, s_WfxPairMetIdMkDir, pathStr);
        if (!JVMState::instance()->exceptionExists(env))
        {
            env->DeleteLocalRef(pathStr);
            if (isNewEnv)
            {
                JVMState::instance()->releaseEnv();
            }
            return retVal;
        } else
        {
            env->DeleteLocalRef(pathStr);
        }
    }
    if (isNewEnv)
    {
        JVMState::instance()->releaseEnv();
    }
    return false;
}

bool HDFSAccessor::deletePath(char* path)
{
    bool isNewEnv = false;
    JNIEnv* env = JVMState::instance()->getEnv(&isNewEnv);
    if (m_wfxPairObj != NULL)
    {
        jstring pathStr = env->NewStringUTF(path);
        jboolean retVal = env->CallBooleanMethod(m_wfxPairObj, s_WfxPairMetIdDelPath, pathStr);
        if (!JVMState::instance()->exceptionExists(env))
        {
            env->DeleteLocalRef(pathStr);
            if (isNewEnv)
            {
                JVMState::instance()->releaseEnv();
            }
            return retVal;
        } else
        {
            env->DeleteLocalRef(pathStr);
        }
    }
    if (isNewEnv)
    {
        JVMState::instance()->releaseEnv();
    }
    return false;
}

bool HDFSAccessor::rename(char* oldPath, char* newPath)
{
    bool isNewEnv = false;
    JNIEnv* env = JVMState::instance()->getEnv(&isNewEnv);
    if (m_wfxPairObj != NULL)
    {
        jstring oldPathStr = env->NewStringUTF(oldPath);
        jstring newPathStr = env->NewStringUTF(newPath);
        jboolean retVal = env->CallBooleanMethod(m_wfxPairObj, s_WfxPairMetIdRenPath, oldPathStr, newPathStr);
        if (!JVMState::instance()->exceptionExists(env))
        {
            env->DeleteLocalRef(oldPathStr);
            env->DeleteLocalRef(newPathStr);
            if (isNewEnv)
            {
                JVMState::instance()->releaseEnv();
            }
            return retVal;
        } else
        {
            env->DeleteLocalRef(oldPathStr);
            env->DeleteLocalRef(newPathStr);
        }

    }
    if (isNewEnv)
    {
        JVMState::instance()->releaseEnv();
    }
    return false;
}


bool HDFSAccessor::copy(char* srcPath, char* destPath)
{
    bool isNewEnv = false;
    JNIEnv* env = JVMState::instance()->getEnv(&isNewEnv);
    if (m_wfxPairObj != NULL)
    {
        jstring srcPathStr = env->NewStringUTF(srcPath);
        jstring destPathStr = env->NewStringUTF(destPath);
        jboolean retVal = env->CallBooleanMethod(m_wfxPairObj, s_WfxPairMetIdCopyPath, srcPathStr, destPathStr);
        if (!JVMState::instance()->exceptionExists(env))
        {
            env->DeleteLocalRef(srcPathStr);
            env->DeleteLocalRef(destPathStr);
            if (isNewEnv)
            {
                JVMState::instance()->releaseEnv();
            }
            return retVal;
        } else
        {
            env->DeleteLocalRef(srcPathStr);
            env->DeleteLocalRef(destPathStr);
        }

    }
    if (isNewEnv)
    {
        JVMState::instance()->releaseEnv();
    }
    return false;
}


bool HDFSAccessor::getFile(char* remotePath, char* localPath)
{
    bool isNewEnv = false;
    JNIEnv* env = JVMState::instance()->getEnv(&isNewEnv);
    if (m_wfxPairObj != NULL)
    {
        jstring remotePathStr = env->NewStringUTF(remotePath);
        jstring localPathStr = env->NewStringUTF(localPath);

        env->CallVoidMethod(m_wfxPairObj, s_WfxPairMetIdGetPath, remotePathStr, localPathStr);
        if (!JVMState::instance()->exceptionExists(env))
        {
            env->DeleteLocalRef(localPathStr);
            env->DeleteLocalRef(remotePathStr);
            if (isNewEnv)
            {
                JVMState::instance()->releaseEnv();
            }
            return true;
        } else
        {
            env->DeleteLocalRef(localPathStr);
            env->DeleteLocalRef(remotePathStr);
        }

    }
    if (isNewEnv)
    {
        JVMState::instance()->releaseEnv();
    }
    return false;
}

bool HDFSAccessor::putFile(char* localPath, char* remotePath, bool overwrite)
{
    bool isNewEnv = false;
    JNIEnv* env = JVMState::instance()->getEnv(&isNewEnv);
    if (m_wfxPairObj != NULL)
    {
        jstring localPathStr = env->NewStringUTF(localPath);
        jstring remotePathStr = env->NewStringUTF(remotePath);
        jboolean joverwrite = overwrite;
        env->CallVoidMethod(m_wfxPairObj, s_WfxPairMetIdPutPath, localPathStr, remotePathStr, joverwrite);
        if (!JVMState::instance()->exceptionExists(env))
        {
            env->DeleteLocalRef(localPathStr);
            env->DeleteLocalRef(remotePathStr);
            if (isNewEnv)
            {
                JVMState::instance()->releaseEnv();
            }
            return true;
        } else
        {
            env->DeleteLocalRef(localPathStr);
            env->DeleteLocalRef(remotePathStr);
        }

    }
    if (isNewEnv)
    {
        JVMState::instance()->releaseEnv();
    }
    return false;
}
