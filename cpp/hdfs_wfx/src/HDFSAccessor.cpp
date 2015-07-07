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

HDFSAccessor* HDFSAccessor::s_instance = new HDFSAccessor();

HDFSAccessor::HDFSAccessor()
{

}

HDFSAccessor::~HDFSAccessor()
{
}

int HDFSAccessor::initialize()
{
    JNIEnv* env = JVMState::instance()->getEnv();
    jclass wfxPairClass = static_cast<jclass>(env->FindClass("hdfs_wfx_java/WfxPair"));
    if (m_wfxPairClass != NULL)
    {
        m_wfxPairClass = static_cast<jclass>(env->NewGlobalRef(wfxPairClass));
        env->DeleteLocalRef(wfxPairClass);
        jmethodID constructorMetId = env->GetMethodID(m_wfxPairClass, CONSTRUCTOR_NAME, "()V");
        jobject wfxPaitrObj = env->NewObject(m_wfxPairClass, constructorMetId);
        m_wfxPairObj = static_cast<jclass>(env->NewGlobalRef(wfxPaitrObj));
        env->DeleteLocalRef(m_wfxPairObj);
        return 0;
    }
    return -1;

}

void HDFSAccessor::release()
{
    JNIEnv* env = JVMState::instance()->getEnv();
    if (m_wfxPairClass != NULL){
        env->DeleteGlobalRef(m_wfxPairClass);
        m_wfxPairClass = NULL;
    }
    if (m_wfxPairObj != NULL){
        env->DeleteGlobalRef(m_wfxPairObj);
        m_wfxPairObj = NULL;
    }


}

FileEnumerator* HDFSAccessor::getFolderContent(char* path)
{
    return NULL;
}
