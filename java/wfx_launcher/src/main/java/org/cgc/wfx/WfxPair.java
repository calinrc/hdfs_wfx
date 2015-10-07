/*
 *    WfxPair.java file written and maintained by Calin Cocan
 *    Created on: Oct 05, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

package org.cgc.wfx;

public interface WfxPair {

	void initFS();

	/**
	 * @param folderPath
	 * @return String[]
	 */
	String[] getFolderContent(String folderPath);

	/**
	 * @param parentFolder
	 * @param fileName
	 * @return FileInformation
	 */
	FileInformation getFileInformation(String parentFolder, String fileName);

	/**
	 * @param filePath
	 * @return boolean
	 */
	boolean mkDir(String filePath);

	/**
	 * @param filePath
	 * @return boolean
	 */
	boolean deletePath(String path);

	/**
	 * @param oldPath
	 * @param newPath
	 * @return boolean
	 */
	boolean renamePath(String oldPath, String newPath);

	/**
	 * @param remotePath
	 * @param localPath
	 * @return boolean
	 */
	void getFile(String remotePath, String localPath);

	/**
	 * @param localPath
	 * @param remotePath
	 * @return boolean
	 */
	void putFile(String localPath, String remotePath, boolean overwrite);

}
