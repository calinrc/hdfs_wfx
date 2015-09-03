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

HDFSAccessor::HDFSAccessor() :
        m_wfxPairClass(NULL), m_wfxPairObj(NULL)
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
    if (m_wfxPairClass != NULL)
    {
        m_wfxPairClass = static_cast<jclass>(env->NewGlobalRef(wfxPairClass));
        env->DeleteLocalRef(wfxPairClass);
        jmethodID constructorMetId = env->GetMethodID(m_wfxPairClass, "<init>", "()V");
        jobject wfxPaitrObj = env->NewObject(m_wfxPairClass, constructorMetId);
        assert(wfxPaitrObj != NULL);
        m_wfxPairObj = env->NewGlobalRef(wfxPaitrObj);
        jmethodID initFS = env->GetMethodID(m_wfxPairClass, "initFS", "()I");
        jint result = env->CallIntMethod(m_wfxPairObj, initFS);
        assert(result != 0);

        env->DeleteLocalRef(m_wfxPairObj);
        return 0;
    }
    return -1;

}

void HDFSAccessor::release()
{
    JNIEnv* env = JVMState::instance()->getEnv();
    if (m_wfxPairClass != NULL)
    {
        env->DeleteGlobalRef(m_wfxPairClass);
        m_wfxPairClass = NULL;
    }
    if (m_wfxPairObj != NULL)
    {
        env->DeleteGlobalRef(m_wfxPairObj);
        m_wfxPairObj = NULL;
    }

}

FileEnumerator* HDFSAccessor::getFolderContent(char* path)
{
    JNIEnv* env = JVMState::instance()->getEnv();
    if (m_wfxPairClass != NULL && m_wfxPairObj != NULL)
    {
        jmethodID getFolderContentMetId = env->GetMethodID(m_wfxPairClass, "getFolderContent", "(Ljava/lang/String;)[Ljava/lang/String;");
        jstring pathStr = env->NewStringUTF(path);
        jobjectArray contentArray = static_cast<jobjectArray>(env->CallObjectMethod(m_wfxPairObj, getFolderContentMetId, pathStr));
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
            return new FileEnumerator(pathStr, contentItems);
        }
    }
    return NULL;
}

