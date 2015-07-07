/*
 *    HDFSAccess.h file written and maintained by Calin Cocan
 *    Created on: Jun 5, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_HDFSACCESSOR_H_
#define INCLUDE_HDFSACCESSOR_H_

#include "FileEnumerator.h"
#include <jni.h>

class HDFSAccessor
{

public:
    static HDFSAccessor* instance()
    {
        return s_instance;
    }

    int initialize();
    void release();

    FileEnumerator* getFolderContent(char* path);

private:
    HDFSAccessor();
    virtual ~HDFSAccessor();

    jclass m_wfxPairClass;
    jobject m_wfxPairObj;

    static HDFSAccessor* s_instance;
};

#endif /* INCLUDE_HDFSACCESSOR_H_ */
