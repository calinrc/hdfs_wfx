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
