/*
 *    JVMState.cpp file written and maintained by Calin Cocan
 *    Created on: May 17, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include "JVMState.h"
#include <jni.h>
#include "Logger.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/stat.h>

typedef jint (*JNI_CreateJavaVM_func)(JavaVM **, void **, void *);

JVMState* JVMState::s_instance = new JVMState();

JVMState::JVMState() :
        m_initialized(false), m_handle(NULL), m_jvm(NULL)
{

}

JVMState::~JVMState()
{
}

JVMStateEnum JVMState::initialize(const char* javaclasspath)
{

    JVMStateEnum retVal = JVMLoadFail;
    if (!m_initialized)
    {
        LOGGING("Start creating JVM");

        JNIEnv *env; /* pointer to native method interface */
        JavaVMInitArgs vm_args; /* JDK/JRE 6 VM initialization arguments */
        JavaVMOption* options = new JavaVMOption[1];

        char classpath[2048];
        sprintf(classpath, "%s%s", JAVA_CLASSPATH_KEY, javaclasspath);
        options[0].optionString = classpath;
        vm_args.version = JNI_VERSION_1_6;
        vm_args.nOptions = 1;
        vm_args.options = options;
        vm_args.ignoreUnrecognized = false;
        /* load and initialize a Java VM, return a JNI interface
         * pointer in env */

        char* javaHomeFolder = getenv("JAVA_HOME");
        if (javaHomeFolder != NULL)
        {
            char path[MAX_PATH] = { 0 };

            sprintf(path, "%s/jre/lib/amd64/server/libjvm.so", javaHomeFolder);

            bool foundJvm = false;

            struct stat st = { 0 };

            if (stat(path, &st) == -1)
            {
                LOGGING("Unable to find jvm dynamic library in %s", path);
                sprintf(path, "%s/jre/lib/amd64/default/libjvm.so", javaHomeFolder);
                if (stat(path, &st) == -1)
                {
                    LOGGING("Unable to find jvm dynamic library in %s", path);
                } else
                {
                    foundJvm = true;
                }

            } else
            {
                //found in default Oracle, OpenJDK places
                foundJvm = true;
            }
            if (foundJvm)
            {
                m_handle = dlopen(path, RTLD_LAZY);

                if (m_handle != NULL)
                {

                    JNI_CreateJavaVM_func JNI_CreateJavaVM_loc;
                    JNI_CreateJavaVM_loc = (jint (*)(JavaVM **, void **, void *))dlsym(m_handle, "JNI_CreateJavaVM");

jint                    jvmCreateState = JNI_CreateJavaVM_loc(&m_jvm, (void**) &env, &vm_args);

                    if (jvmCreateState == JNI_OK)
                    {

                    }

                    LOGGING("Destroy created JVM");
                    retVal = JVMLoaded;
                }
            }

        } else
        {
            LOGGING("Unable to find JAVA_HOME variable");
        }

        delete options;

        /* invoke the Main.test method using the JNI */

        //jclass cls = env->FindClass("Main");
        //jmethodID mid = env->GetStaticMethodID(cls, "test", "(I)V");
        //env->CallStaticVoidMethod(cls, mid, 100);
        /* We are done. */
    }
    return retVal;

}

JVMStateEnum JVMState::detach()
{
    JVMStateEnum retVal = JVMDetached;
    if (m_jvm != NULL)
    {
        m_jvm->DestroyJavaVM();
        m_jvm = NULL;
    }
    if (m_handle != NULL)
    {
        dlclose(m_handle);
        m_handle = NULL;
    }
    m_initialized = false;
    return retVal;
}

JVMState* JVMState::instance()
{
    return s_instance;
}
