package org.cgc.wfx;

public interface FileInformation {

	/**
	 * @return file attributes 
	 */
	int getFileAttributes();

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
	int getReserved0();

	/**
	 * @return fine name
	 */
	String getFileName();

}
