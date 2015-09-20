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
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "Utilities.h"

JVMState* JVMState::s_instance = new JVMState();

JVMState::JVMState() :
        m_initialized(false), m_handle(NULL), m_jvm(NULL)
{

}

JVMState::~JVMState()
{
}

JVMStateEnum JVMState::initialize(const char* javaclasspathDir)
{

    JVMStateEnum retVal = JVMLoadFail;
    if (!m_initialized)
    {

        LOGGING("Start creating JVM");
        JavaVMInitArgs vm_args; /* JDK/JRE 6 VM initialization arguments */
        JavaVMOption* options = new JavaVMOption[2];

        char classpathParam[206800];
        char classpath[204800];
        char log4j[MAX_PATH];
        char log4jParam[MAX_PATH+100];

        size_t pathSize = MAX_PATH;


        memset(classpathParam, 0, sizeof(classpathParam));
        memset(classpath, 0, sizeof(classpath));
        memset(log4j, 0, sizeof(log4j));

        buildClassPath(javaclasspathDir, classpath, sizeof(classpath));
        LOGGING("Using classpath: %s", classpath);
        sprintf(classpathParam, "-Djava.class.path=%s", classpath);

        Utilities::getJavaLoggerFileLocation(log4j, &pathSize);
        sprintf(log4jParam, "-Dlog4j.configuration=file://%s", log4j);



        options[0].optionString = classpathParam;
        options[1].optionString = log4jParam;
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
                LOGGING("Try loading JVM dynamic library...");
                m_handle = dlopen(path, RTLD_LAZY);

                if (m_handle != NULL)
                {

                    LOGGING("Try creating JVM");
                    JNI_CreateJavaVM_func JNI_CreateJavaVM_loc;
                    JNI_CreateJavaVM_loc = (JNI_CreateJavaVM_func) dlsym(m_handle, "JNI_CreateJavaVM");

                    JNIEnv* env;
                    jint jvmCreateState = JNI_CreateJavaVM_loc(&m_jvm, (void**) &env, &vm_args);

                    if (jvmCreateState == JNI_OK)
                    {
                        LOGGING("JVM create OK");
                        m_initialized = true;
                    }

                    LOGGING("End JVM creation");
                    retVal = JVMLoaded;
                }
            }

        } else
        {
            LOGGING("Unable to find JAVA_HOME variable");
        }

        delete options;

    }
    return retVal;

}

JNIEnv* JVMState::getEnv()
{

    JNIEnv* env = NULL;
    if (m_jvm != NULL)
    {
        if (JNI_OK != m_jvm->GetEnv((void **) &env, JNI_VERSION_1_2))
        {
            m_jvm->AttachCurrentThread((void **) &env, NULL);
            LOGGING("Create a new JNIEnv for a new thread. Make sure we are detaching it when not used anymore");
        }

    }
    return env;
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

bool JVMState::exceptionExists(JNIEnv* env)
{
    jboolean exceptionExists = env->ExceptionCheck();
    if (exceptionExists)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    return exceptionExists;
}

void JVMState::buildClassPath(const char* cJarsDir, char* classpath, size_t classpathsize)
{
    dirent* dp = NULL;
    bool isFirst = true;
    size_t totalSizeWritten = 0;
    size_t cpFOlderSize = strlen(cJarsDir);

    DIR* dirp = opendir(cJarsDir);
    while ((dp = readdir(dirp)) != NULL)
    {
        size_t itemSize = strlen(dp->d_name);
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0
                && (totalSizeWritten + sizeof(PATH_SEPARATOR) + cpFOlderSize + sizeof(FILE_SEPARATOR) + itemSize + 1) < classpathsize)
        {
            if (!isFirst)
            {
                strcat(classpath, PATH_SEPARATOR);
                itemSize += sizeof(PATH_SEPARATOR);
            }
            isFirst = false;
            strcat(classpath, cJarsDir);
            strcat(classpath, FILE_SEPARATOR);
            strcat(classpath, dp->d_name);
            totalSizeWritten += cpFOlderSize + sizeof(FILE_SEPARATOR) + itemSize;
        }
    }
    (void) closedir(dirp);
}

JVMState* JVMState::instance()
{
    return s_instance;
}
