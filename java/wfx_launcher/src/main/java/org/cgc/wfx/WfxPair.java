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

	void initFS() ;

	/**
	 * @param folderPath
	 * @return String[]
	 */
	String[] getFolderContent(String folderPath) ;

	FileInformation getFileInformation(String parentFolder,
			String fileName) ;

}
