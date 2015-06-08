/*
 *    HDFSAccess.cpp file written and maintained by Calin Cocan
 *    Created on: Jun 5, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include <HDFSAccessor.h>
#include "gendef.h"

HDFSAccessor* HDFSAccessor::s_instance = new HDFSAccessor();

HDFSAccessor::HDFSAccessor()
{

}

HDFSAccessor::~HDFSAccessor()
{
}

FileEnumerator* HDFSAccessor::getFolderContent(char* path)
{
    return NULL;
}
