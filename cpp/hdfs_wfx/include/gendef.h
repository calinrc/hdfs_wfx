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

#include <stddef.h>

#define PLUGINS_LOCATION ".config/doublecmd/plugins"

#define PLUGIN_LOCATION PLUGINS_LOCATION "/hdfs_wfx"
#define LOG_PATH PLUGIN_LOCATION "/logs"
#define LOGGER_LOCATION PLUGIN_LOCATION "/log4j.xml"
#define JAVA_CLASSPATH_VAL PLUGIN_LOCATION "/java"
#define FULL_LOG_PATH LOG_PATH "/hdfs_wfx.log"

#define PATH_SEPARATOR ":"
#define FILE_SEPARATOR "/"

#define MAX_PATH 260


enum JVMStateEnum {

    JVMLoaded,
    JVMLoadFail,
    JVMDetached,
    JVMDetachFail
};


#endif /* INCLUDE_GENDEF_H_ */
