/*
 *    Utilities.h file written and maintained by Calin Cocan
 *    Created on: May 18, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_UTILITIES_H_
#define INCLUDE_UTILITIES_H_

#include <stddef.h>
#include <stdlib.h>
#ifdef LINUX
#include <pwd.h>
#include <unistd.h>
#endif
#include "gendef.h"
#include <sys/stat.h>
#include <string.h>

class Utilities
{
public:
    static const char* getUserHomeDir()
    {
        const char *homedir=NULL;
#ifdef LINUX
        if ((homedir = getenv("HOME")) == NULL)
        {
            homedir = getpwuid(getuid())->pw_dir;
        }
#endif
        return homedir;

    }

    static void mkDirectory(const char* path)
    {
        struct stat st = { 0 };

        if (stat(path, &st) == -1)
        {
#ifdef LINUX
            mkdir(path, 0700);
#endif
        }
    }

    static char* getPluginsDir(char* retPath, size_t* size)
    {
        return getAbsolutePath(PLUGINS_LOCATION, retPath, size);
    }

    static char* getPluginDir(char* retPath, size_t* size)
    {
        return getAbsolutePath(PLUGIN_LOCATION, retPath, size);
    }

    static char* getLogDir(char* retPath, size_t* size)
    {
        return getAbsolutePath(LOG_PATH, retPath, size);
    }

    static char* getLogFilePath(char* retPath, size_t* size)
    {
        return getAbsolutePath(FULL_LOG_PATH, retPath, size);
    }

    static char* getJavaLoggerFileLocation(char* retPath, size_t* size)
    {
        return getAbsolutePath(LOGGER_LOCATION, retPath, size);
    }

    static char* getJavaLauncherPath(char* retPath, size_t* size)
    {
        return getAbsolutePath(JAVA_LAUNCHER_VAL, retPath, size);
    }

    static char* getJavaDependenciesPath(char* retPath, size_t* size)
    {
        return getAbsolutePath(DEPENDENCIES_PATH, retPath, size);
    }

private:
    Utilities();
    virtual ~Utilities();

    static char* getAbsolutePath(const char* relativePath, char* retPath, size_t* size)
    {
        char path[MAX_PATH];
        sprintf(path, "%s/%s", getUserHomeDir(), relativePath);
        size_t length = strlen(path);

        if (length < *size - 1)
        {
            *size = length;
            strcpy(retPath, path);
            return retPath;
        } else
        {
            *size = length;
            return NULL;
        }
    }
};

#endif /* INCLUDE_UTILITIES_H_ */
