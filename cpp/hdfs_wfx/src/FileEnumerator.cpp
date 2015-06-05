/*
 *    FileEnumerator.cpp file written and maintained by Calin Cocan
 *    Created on: May 31, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include <FileEnumerator.h>

FileEnumerator::FileEnumerator()
{
}

FileEnumerator::~FileEnumerator()
{
}

bool FileEnumerator::getFirst(WIN32_FIND_DATAA *FindData)
{
    return false;
}

bool FileEnumerator::getNext(WIN32_FIND_DATAA *FindData)
{
    return false;
}
void FileEnumerator::close()
{

}

bool getJavaFolderContent(char* Path){
    return false;
}

