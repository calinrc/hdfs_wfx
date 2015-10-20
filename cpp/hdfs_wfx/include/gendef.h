/*
 *    gendef.h file written and maintained by Calin Cocan
 *    Created on: May 17, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_GENDEF_H_
#define INCLUDE_GENDEF_H_

#include <HdfsWfxVersion.h>
#include <stddef.h>

#define PLUGINS_LOCATION ".config/doublecmd/plugins"

#define PLUGIN_LOCATION PLUGINS_LOCATION "/hdfs_wfx"
#define LOG_PATH PLUGIN_LOCATION "/logs"
#define JAVA_LAUNCHER_VAL PLUGIN_LOCATION "/java/wfx_launcher.jar"
#define LOGGER_LOCATION PLUGIN_LOCATION "/java/log4j.xml"
#define FULL_LOG_PATH PLUGIN_LOCATION "/logs/hdfs_wfx.log"
#define DEPENDENCIES_PATH PLUGIN_LOCATION "/java/deps"

#define PATH_SEPARATOR ":"
#define FILE_SEPARATOR "/"

#define MAX_PATH 260

enum JVMStateEnum
{
    JVMLoaded, JVMLoadFail, JVMDetached, JVMDetachFail
};

struct ProgressStructure
{
  char source[MAX_PATH];
  char target[MAX_PATH];
  void* ptr;
  int pluginNr;
};

#endif /* INCLUDE_GENDEF_H_ */
