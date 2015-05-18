/*
 *    Utilities.h file written and maintained by Calin Cocan
 *    Created on: May 18, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_UTILITIES_H_
#define INCLUDE_UTILITIES_H_

#include <stddef.h>
#include "gendef.h"
#include <sys/stat.h>
#include <string.h>

class Utilities
{
public:
    static const char* getUserHomeDir()
    {
        const char *homedir;

        if ((homedir = getenv("HOME")) == NULL)
        {
            homedir = getpwuid(getuid())->pw_dir;
        }
        return homedir;

    }

    static void mkDirectory(const char* path)
    {
        struct stat st = { 0 };

        if (stat(path, &st) == -1)
        {
            mkdir(path, 0700);
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

    static char* getLoggerDir(char* retPath, size_t* size)
    {
        return getAbsolutePath(LOG_PATH, retPath, size);
    }

    static char* getLoggerFilePath(char* retPath, size_t* size)
    {
        return getAbsolutePath(FULL_LOG_PATH, retPath, size);
    }

private:
    Utilities();
    virtual ~Utilities();

    static char* getAbsolutePath(const char* part, char* retPath, size_t* size)
    {
        char path[MAX_PATH];
        sprintf(path, "%s/%s", getUserHomeDir(), part);
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
