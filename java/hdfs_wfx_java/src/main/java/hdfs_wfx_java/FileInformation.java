package hdfs_wfx_java;

import org.apache.hadoop.fs.FileStatus;

public class FileInformation {
	private static final long FILE_ATTRIBUTE_UNIX_MODE = 0x80000000;
	private static final long FILE_ATTRIBUTE_DIRECTORY = 16;

	private int fileAttributes;
	private long fileCreationTime;
	private long fileLastAccessTime;
	private long fileLastWriteTime;
	private long fileSize;
	private int reserverd0;
	private int reserverd1;
	private String fileName;

	public FileInformation(FileStatus fstatus) {
		boolean isDir = fstatus.isDirectory();

		this.fileAttributes |= FILE_ATTRIBUTE_UNIX_MODE;
		if (isDir){
			this.fileAttributes |= FILE_ATTRIBUTE_DIRECTORY;
		}

		this.fileCreationTime = fstatus.getModificationTime();
		this.fileLastAccessTime = fstatus.getAccessTime();
		this.fileLastWriteTime = fstatus.getModificationTime();
		if (isDir == false) {
			this.fileSize = fstatus.getLen();
		} else {
			this.fileSize = 0;
		}
		// this.reserverd0 = 0; 
		
		//TODO continue here
		this.reserverd1 = 0;
		this.fileName = fstatus.getPath().getName();

	}

	public int getFileAttributes() {
		return fileAttributes;
	}

	public long getFileCreationTime() {
		return fileCreationTime;
	}

	public long getFileLastAccessTime() {
		return fileLastAccessTime;
	}

	public long getFileLastWriteTime() {
		return fileLastWriteTime;
	}

	public long getFileSize() {
		return fileSize;
	}

	public long getReserverd0() {
		return reserverd0;
	}

	public long getReserverd1() {
		return reserverd1;
	}

	public String getFileName() {
		return fileName;
	}

}
