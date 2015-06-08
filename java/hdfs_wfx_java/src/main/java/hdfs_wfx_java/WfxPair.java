package hdfs_wfx_java;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;

public class WfxPair {

	private FileSystem fileSystem;

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
			Configuration config = new Configuration();
			FileSystem fileSystem = FileSystem.get(config);
			if (fileSystem == null) {
				return WfxErrorCodes.InitializationError.ordinal();
			} else {
				this.fileSystem = fileSystem;
			}
			return WfxErrorCodes.OK.ordinal();
		} catch (Throwable thr) {
			return WfxErrorCodes.InitializationError.ordinal();
		}
	}

}
