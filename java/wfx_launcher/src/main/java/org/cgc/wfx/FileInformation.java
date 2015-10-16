/*
 *    FileInformation.java file written and maintained by Calin Cocan
 *    Created on: Oct 05, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

package org.cgc.wfx;

public interface FileInformation {

	/**
	 * @return file attributes 
	 */
	long getFileAttributes();

	/**
	 * @return file creation time
	 */
	long getFileCreationTime();

	/**
	 * @return last file access time
	 */
	long getFileLastAccessTime();

	/**
	 * @return file size
	 */
	long getFileSize();

	/**
	 * @return reserved file flags
	 */
	long getReserved0();

	/**
	 * @return fine name
	 */
	String getFileName();

}
