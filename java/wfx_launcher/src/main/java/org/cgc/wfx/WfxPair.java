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
