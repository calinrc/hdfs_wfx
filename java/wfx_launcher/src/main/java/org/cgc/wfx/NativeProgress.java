package org.cgc.wfx;

public class NativeProgress implements Progress {

	private long ptr;

	public NativeProgress(long prgStructPntr) {
		this.ptr = prgStructPntr;
	}

	public void notifyProgress(int progressVal) {
		if (this.ptr != 0 && this.ptr != -1) {
			notifyProgress(ptr, progressVal);
		}
	}

	native void notifyProgress(long pointer, int progressVal);

}
