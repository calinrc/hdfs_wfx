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
#include <assert.h>

JVMState* JVMState::s_instance = new JVMState();

JVMState::JVMState() :
        m_initialized(false), m_handle(NULL), m_jvm(NULL)
{

}

JVMState::~JVMState()
{
}

JVMStateEnum JVMState::initialize(const char* javaLauncherJar)
{

    JVMStateEnum retVal = JVMLoadFail;
    if (!m_initialized)
    {

        LOGGING("Start creating JVM");
        JavaVMInitArgs vm_args; /* JDK/JRE 6 VM initialization arguments */
        JavaVMOption* options = new JavaVMOption[2];

        char classpathParam[MAX_PATH + 100];
        char log4j[MAX_PATH + 100];
        char log4jParam[MAX_PATH + 100];

        size_t pathSize = MAX_PATH;

        memset(classpathParam, 0, sizeof(classpathParam));
        memset(log4j, 0, sizeof(log4j));
        memset(log4jParam, 0, sizeof(log4jParam));

        sprintf(classpathParam, "-Djava.class.path=%s", javaLauncherJar);

        Utilities::getJavaLoggerFileLocation(log4j, &pathSize);
        sprintf(log4jParam, "-Dlog4j.configuration=file://%s", log4j);

        LOGGING("Using classpath param:  \"%s\" ", classpathParam);

        LOGGING("Using log4j.configuration param \"%s\"", log4jParam);

        options[0].optionString = classpathParam;
        options[0].extraInfo = 0;
        //(char*) "-Djava.class.path=/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-mapreduce-client-common-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jersey-json-1.9.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-net-3.1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jaxb-impl-2.2.3-1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-el-1.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jline-0.9.94.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-lang-2.6.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-mapreduce-client-core-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-beanutils-1.7.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/java-xmlbuilder-0.4.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jetty-6.1.26.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/log4j-1.2.17.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-common-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/zookeeper-3.4.6.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jets3t-0.9.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/avro-1.7.4.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/activation-1.1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/snappy-java-1.0.4.1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hdfs_wfx.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jsch-0.1.42.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/slf4j-api-1.7.5.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/asm-3.2.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/guava-11.0.2.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/aopalliance-1.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-mapreduce-client-jobclient-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/paranamer-2.3.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-cli-1.2.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/gson-2.2.4.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/xml-apis-1.3.04.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-yarn-api-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-httpclient-3.1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/apacheds-i18n-2.0.0-M15.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hdfs-site.xml:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jersey-guice-1.9.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-daemon-1.0.13.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/api-asn1-api-1.0.0-M20.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jetty-util-6.1.26.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/xmlenc-0.52.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jackson-core-asl-1.9.13.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jasper-runtime-5.5.23.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/curator-client-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jackson-jaxrs-1.9.13.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/guice-3.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/mapred-site.xml:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-yarn-server-common-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-math3-3.1.1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/httpcore-4.2.5.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/leveldbjni-all-1.8.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-configuration-1.6.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jersey-client-1.9.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jersey-core-1.9.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/htrace-core-3.0.4.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/apacheds-kerberos-codec-2.0.0-M15.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/cglib-2.2.1-v20090111.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-mapreduce-client-app-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/xercesImpl-2.9.1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/servlet-api-2.5.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-yarn-client-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-beanutils-core-1.8.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jackson-mapper-asl-1.9.13.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jaxb-api-2.2.2.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-hdfs-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/xz-1.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-codec-1.4.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-client-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-mapreduce-client-shuffle-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-io-2.4.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-auth-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/curator-recipes-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/yarn-site.xml:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-logging-1.1.3.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jsp-api-2.1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jackson-xc-1.9.13.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-annotations-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jettison-1.1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jersey-server-1.9.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jsr305-1.3.9.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/httpclient-4.2.5.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/slf4j-log4j12-1.7.5.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/stax-api-1.0-2.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/core-site.xml:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/hadoop-yarn-common-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/api-util-1.0.0-M20.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-digester-1.8.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/netty-3.6.2.Final.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-compress-1.4.1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/javax.inject-1.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/protobuf-java-2.5.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/jasper-compiler-5.5.23.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/curator-framework-2.6.0.jar:/home/ae/.config/doublecmd/plugins/hdfs_wfx/java/commons-collections-3.2.1.jar";
        options[1].optionString = log4jParam; //(char*) "-Dlog4j.configuration=file:///home/ae/.config/doublecmd/plugins/hdfs_wfx/log4j.xml";
        options[1].extraInfo = 0;
        vm_args.version = JNI_VERSION_1_6;
        vm_args.nOptions = 1;
        vm_args.options = options;
        vm_args.ignoreUnrecognized = false;
        /*
         JNIEnv* env;
         jint jvmCreateState = JNI_CreateJavaVM(&m_jvm, (void**) &env, &vm_args);

         if (jvmCreateState == JNI_OK)
         {
         LOGGING("JVM create OK");
         m_initialized = true;
         retVal = JVMLoaded;
         }else{
         LOGGING("Fail to create JVM. Exit with code %d", jvmCreateState)
         }

         LOGGING("End JVM creation");
         */
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
                } else
                {
                    LOGGING("JVM loading error %s", dlerror());
                    assert(false);
                }
            }

        } else
        {
            LOGGING("Unable to find JAVA_HOME variable");
            assert(false);
        }

        delete[] options;

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

JVMState* JVMState::instance()
{
    return s_instance;
}
