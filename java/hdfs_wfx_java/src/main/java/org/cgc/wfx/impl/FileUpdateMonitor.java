package org.cgc.wfx.impl;

import org.cgc.wfx.Progress;

public class FileUpdateMonitor {

	Progress progress;
	int lastProgress = 0;
	long totalFileSize = 0;
	long exchangedBites = 0;

	/**
	 * @param progress
	 * @param totalFileSize
	 */
	public FileUpdateMonitor(Progress progress, long totalFileSize) {
		this.progress = progress;
	}

	/**
	 * @param updateBitesNo
	 */
	public void updateMovedBytes(long updateBitesNo) {
		if (this.progress != null) {
			exchangedBites += updateBitesNo;
			int actualProgress = (int) (exchangedBites * 100 / totalFileSize);
			if (actualProgress > lastProgress) {
				lastProgress = actualProgress;
				progress.notifyProgress(lastProgress);
			}
		}
	}

}
