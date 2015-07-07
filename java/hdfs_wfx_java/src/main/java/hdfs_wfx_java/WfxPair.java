package hdfs_wfx_java;



public class WfxPair {

	private FileSystemProxy fileSystem;

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
			fileSystem = new FileSystemProxy();
			fileSystem.init();
			return WfxErrorCodes.OK.ordinal();
		} catch (Throwable thr) {
			return WfxErrorCodes.InitializationError.ordinal();
		}
	}

}
