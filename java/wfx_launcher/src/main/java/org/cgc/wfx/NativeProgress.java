package org.cgc.wfx;

import java.io.File;

public class NativeProgress implements Progress {

	private long ptr;

	public NativeProgress(long prgStructPntr) {
		this.ptr = prgStructPntr;
	}

	public void notifyProgress(int progressVal) {
		if (this.ptr != 0 && this.ptr != -1) {
			try {
				notifyProgress(ptr, progressVal);
			} catch (UnsatisfiedLinkError linkError) {
				System.err
						.println("Fail on calling native method. Try loading native library");
				linkError.printStackTrace();
				tryLoadingWfxLinbrary();
				try {
					notifyProgress(ptr, progressVal);
				} catch (Throwable thr) {
					System.err
							.println("Final fail on sending progress notification");
				}
			}
		}
	}

	private static void tryLoadingWfxLinbrary() {
		File nativeLibPath = new File(System.getProperty("user.home")
				+ File.separatorChar + Constants.HDFS_WFX_NATIVE_LIBRARY);
		try {
			System.load(nativeLibPath.getAbsolutePath());
		} catch (Throwable thr) {
			System.err
					.println("Fail on loading hdfs_wfx.wfx library from path "
							+ nativeLibPath.getAbsolutePath());
			thr.printStackTrace();
			throw thr;
		}
		System.out.println("Success on loading hdfs_wfx.wfx");

	}

	native void notifyProgress(long pointer, int progressVal);

}
