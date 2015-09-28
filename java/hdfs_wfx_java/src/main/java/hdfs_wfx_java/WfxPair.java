package hdfs_wfx_java;


public class WfxPair {

	private FileSystemProxy fileSystemProxy = null;

	public WfxPair() {

	}

	private long nativePtr = 0;

	void setNativePair(long nativePtr) {
		this.nativePtr = nativePtr;

	}

	public void notifyProgress() {
		if (checkInitted()) {
		}

	}

	private boolean checkInitted() {
		return nativePtr != 0;
	}

	/**
	 * @return int value translation of WfxErrorCodes
	 */
	public void initFS(String dependencyFolder) {
		DepsLoader ld = new DepsLoader(dependencyFolder);
		ClassLoader cl = ld.loadFolder();
		fileSystemProxy = new FileSystemProxy();
		fileSystemProxy.initFS();
	}

	/**
	 * @param folderPath
	 * @return String[]
	 */
	public String[] getFolderContent(String folderPath) {
		return fileSystemProxy.getFolderContent(folderPath);
	}

	public FileInformation getFileInformation(String parentFolder,
			String fileName) {
		return fileSystemProxy.getFileInformation(parentFolder, fileName);
	}

}
