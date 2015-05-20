/*
 *    gendef.h file written and maintained by Calin Cocan
 *    Created on: May 17, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_GENDEF_H_
#define INCLUDE_GENDEF_H_

#define PLUGINS_LOCATION ".config/doublecmd/plugins"

#define PLUGIN_LOCATION PLUGINS_LOCATION "/hdfs_wfx"
#define LOG_PATH PLUGIN_LOCATION "/logs"
#define LOG_FILE_NAME "/hdfs_wfx.log"

#define JAVA_CLASSPATH_KEY "-Djava.class.path="
#define JAVA_CLASSPATH_VAL "~/work/workspace-cpp/hdfs_wfx_java/target/classes"


#define FULL_LOG_PATH LOG_PATH LOG_FILE_NAME
#define MAX_PATH 260


enum JVMStateEnum {

    JVMLoaded,
    JVMLoadFail,
    JVMDetached,
    JVMDetachFail
};

#endif /* INCLUDE_GENDEF_H_ */
