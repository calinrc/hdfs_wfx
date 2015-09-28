package org.cgc.wfx.exception;

public class WfxHdfsException extends RuntimeException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 5392264330417971129L;

	public WfxHdfsException() {
	}

	public WfxHdfsException(String message) {
		super(message);
	}

	public WfxHdfsException(Throwable cause) {
		super(cause);
	}

	public WfxHdfsException(String message, Throwable cause) {
		super(message, cause);
	}

	public WfxHdfsException(String message, Throwable cause,
			boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

}
