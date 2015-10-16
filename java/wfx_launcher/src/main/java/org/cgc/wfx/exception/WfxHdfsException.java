/*
 *    WfxHdfsException.java file written and maintained by Calin Cocan
 *    Created on: Oct 05, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

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
