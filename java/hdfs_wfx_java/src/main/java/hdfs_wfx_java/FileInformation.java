package hdfs_wfx_java;

import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.permission.FsAction;
import org.apache.hadoop.fs.permission.FsPermission;

public class FileInformation {
	private static final long FILE_ATTRIBUTE_UNIX_MODE = 0x80000000;
	private static final long FILE_ATTRIBUTE_DIRECTORY = 16;

	private static int S_IFDIR = 0040000;
	private static int S_IFLNK = 0120000;

	private static int S_IRUSR = 0400; /* Read by owner. */
	private static int S_IWUSR = 0200; /* Write by owner. */
	private static int S_IXUSR = 0100; /* Execute by owner. */

	// private static int S_IRGRP = (S_IRUSR >> 3); /* Read by group. */
	// private static int S_IWGRP = (S_IWUSR >> 3); /* Write by group. */
	// private static int S_IXGRP = (S_IXUSR >> 3); /* Execute by group. */
	//
	// private static int S_IROTH = (S_IRGRP >> 3); /* Read by others. */
	// private static int S_IWOTH = (S_IWGRP >> 3); /* Write by others. */
	// private static int S_IXOTH = (S_IXGRP >> 3); /* Execute by others. */

	private int fileAttributes;
	private long fileCreationTime;
	private long fileLastAccessTime;
	private long fileSize;
	private int reserved0;
	private String fileName;

	public FileInformation(FileStatus fstatus) {
		boolean isDir = fstatus.isDirectory();

		this.fileAttributes |= FILE_ATTRIBUTE_UNIX_MODE;
		if (isDir) {
			this.fileAttributes |= FILE_ATTRIBUTE_DIRECTORY;
		}

		this.fileCreationTime = javaTimeToFileTime(fstatus
				.getModificationTime());
		this.fileLastAccessTime = javaTimeToFileTime(fstatus.getAccessTime());
		if (isDir == false) {
			this.fileSize = fstatus.getLen();
		} else {
			this.fileSize = 0;
		}
		this.reserved0 = 0;

		if ((this.fileAttributes &= FILE_ATTRIBUTE_DIRECTORY) != 0) {
			this.reserved0 |= S_IFDIR;
		}
		if (fstatus.isSymlink()) {
			this.reserved0 |= S_IFLNK;
		}
		FsPermission fperm = fstatus.getPermission();
		this.reserved0 |= fsActionToUnixVal(fperm.getUserAction());
		this.reserved0 |= (fsActionToUnixVal(fperm.getGroupAction()) >> 3);
		this.reserved0 |= (fsActionToUnixVal(fperm.getOtherAction()) >> 6);

		this.fileName = fstatus.getPath().getName();

	}

	/**
	 * @param javaTime - in milliseconds since January 1, 1970 UTC.
	 * @return fileTime -  number of 100-nanosecond intervals since January 1, 1601.
	 */
	private static long javaTimeToFileTime(long javaTime) {
		long retVal = (javaTime*10000)+ 116444736000000000L;
		return retVal;
	}

	private static int fsActionToUnixVal(FsAction action) {
		int retVal = 0;
		if (action.implies(FsAction.READ)) {
			retVal |= S_IRUSR;
		}
		if (action.implies(FsAction.WRITE)) {
			retVal |= S_IWUSR;
		}
		if (action.implies(FsAction.EXECUTE)) {
			retVal |= S_IXUSR;
		}
		return retVal;
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

	public long getFileSize() {
		return fileSize;
	}

	public int getReserved0() {
		return reserved0;
	}

	public String getFileName() {
		return fileName;
	}

}
