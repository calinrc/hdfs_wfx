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

JVMState* JVMState::s_instance = new JVMState();

JVMState::JVMState() :
        m_initialized(false)
{

}

JVMState::~JVMState()
{
}

void JVMState::initialize(const char* javaclasspath)
{

    if (!m_initialized)
    {
        LOGGING("Start creating JVM");

        JavaVM *jvm; /* denotes a Java VM */
        JNIEnv *env; /* pointer to native method interface */
        JavaVMInitArgs vm_args; /* JDK/JRE 6 VM initialization arguments */
        JavaVMOption* options = new JavaVMOption[1];
        options[0].optionString = "-Djava.class.path=/usr/lib/java";
        vm_args.version = JNI_VERSION_1_6;
        vm_args.nOptions = 1;
        vm_args.options = options;
        vm_args.ignoreUnrecognized = false;
        /* load and initialize a Java VM, return a JNI interface
         * pointer in env */
        JNI_CreateJavaVM(&jvm, (void**) &env, &vm_args);
        delete options;
        /* invoke the Main.test method using the JNI */

        //jclass cls = env->FindClass("Main");
        //jmethodID mid = env->GetStaticMethodID(cls, "test", "(I)V");
        //env->CallStaticVoidMethod(cls, mid, 100);
        /* We are done. */
        LOGGING("Destroy created JVM");
        jvm->DestroyJavaVM();
    }

}

void JVMState::detach()
{

}

JVMState* JVMState::instance()
{
    return s_instance;
}
