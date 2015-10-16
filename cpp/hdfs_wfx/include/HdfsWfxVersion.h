/*
 *    Version.h file written and maintained by Calin Cocan
 *    Created on: Oct 9, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_HDFSWFXVERSION_
#define INCLUDE_HDFSWFXVERSION_

#define VERSION "0.1"

class HdfsWfxVersion
{

    static const char* GetVersion()
    {
        return VERSION;
    }
};

#endif /* INCLUDE_HDFSWFXVERSION_ */
