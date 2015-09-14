package hdfs_wfx_java;

public class WfxPair {

	public WfxPair() {

	}

	private FileSystemProxy fSystemProxy;

	private long nativePtr = 0;

	void setNativePair(long nativePtr) {
		this.nativePtr = nativePtr;

	}

	public void notifyProgress() {
		if (checkInitted()) {
			notifyProgress(this.nativePtr);
		}

	}

	private boolean checkInitted() {
		return nativePtr != 0;
	}

	private native void notifyProgress(long nativePtr);

	/**
	 * @return int value translation of WfxErrorCodes
	 */
	public int initFS() {
		try {
			fSystemProxy = new FileSystemProxy();
			fSystemProxy.init();
			return WfxErrorCodes.OK.ordinal();
		} catch (Throwable thr) {
			return WfxErrorCodes.InitializationError.ordinal();
		}
	}

	/**
	 * @param folderPath
	 * @return String[]
	 */
	public String[] getFolderContent(String folderPath) {
		try {
			return fSystemProxy.getFolderContent(folderPath);
		} catch (Throwable thr) {
			return null;
		}
	}
	
	public FileInformation getFileInformation(String parentFolder, String fileName){
		try {
			return fSystemProxy.getFileInformation(parentFolder, fileName);
		} catch (Throwable thr) {
			return null;
		}
	}

}
