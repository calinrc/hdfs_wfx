/*
 *    IOUtils.java file written and maintained by Calin Cocan
 *    Created on: Oct 16, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

package org.cgc.wfx.impl;

import java.io.Closeable;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class IOUtils {

	private IOUtils() {
	}

	public static void deplate(InputStream is, OutputStream os, FileUpdateMonitor monitor) throws IOException {
		try {
			byte[] buff = new byte[2 * 1024 * 1024];
			int readBytes = 0;

			while ((readBytes = is.read(buff)) > -1) {
				os.write(buff, 0, readBytes);
				monitor.updateMovedBytes(readBytes);
			}
		} finally {
			close(is, os);
		}

	}

	public static void close(Closeable... cls) {
		for (Closeable item : cls) {
			try {
				item.close();
			} catch (Exception ex) {

			}
		}
	}

}
