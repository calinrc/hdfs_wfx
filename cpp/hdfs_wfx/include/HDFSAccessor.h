/*
 *    HDFSAccess.h file written and maintained by Calin Cocan
 *    Created on: Jun 5, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_HDFSACCESSOR_H_
#define INCLUDE_HDFSACCESSOR_H_

#include "FileEnumerator.h"

class HDFSAccessor
{

public:
    static HDFSAccessor* instance()
    {
        return s_instance;
    }

    FileEnumerator* getFolderContent(char* path);

private:
    HDFSAccessor();
    virtual ~HDFSAccessor();

    static HDFSAccessor* s_instance;
};

#endif /* INCLUDE_HDFSACCESSOR_H_ */
