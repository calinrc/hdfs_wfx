/*
 *    FileEnumerator.h file written and maintained by Calin Cocan
 *    Created on: May 31, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_FILEENUMERATOR_H_
#define INCLUDE_FILEENUMERATOR_H_

#include "wfxplugin.h"
#include <set>
#include <string>

struct FileInfo
{

    long fileAttr;
    long long fileCreationTime;
    long long fileLastAccessTime;
    long long fileLastWriteTime;
    long long fileSize;
    char fileName[MAX_PATH];
};

using namespace std;

class FileEnumerator
{
public:
    FileEnumerator(string& parentPath, set<string>& content);
    bool getFirst(WIN32_FIND_DATAA *FindData);
    bool getNext(WIN32_FIND_DATAA *FindData);
    void close();
    virtual ~FileEnumerator();
private:

    string m_parent;
    set<string> m_content;




};

#endif /* INCLUDE_FILEENUMERATOR_H_ */
