package hdfs_wfx_java;

public class WfxPair {

	private long nativePtr = 0;

	void setNativePair(long nativePtr) {
		this.nativePtr = nativePtr;

	}

	public void notifyProgress() {
		if (checkInitted()){
			notifyProgress(this.nativePtr);
		} 

	}

	private boolean checkInitted() {
		return nativePtr != 0;
	}

	private native void notifyProgress(long nativePtr);

}
