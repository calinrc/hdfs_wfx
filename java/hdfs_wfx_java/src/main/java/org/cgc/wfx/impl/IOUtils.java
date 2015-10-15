package org.cgc.wfx.impl;

import java.io.Closeable;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import org.apache.log4j.Logger;

public class IOUtils {
	private static final Logger log = Logger.getLogger(IOUtils.class);

	private IOUtils() {
	}

	public static void deplate(InputStream is, OutputStream os)
			throws IOException {
		try {
			byte[] buff = new byte[2 * 1024 * 1024];
			int readBytes = 0;

			while ((readBytes = is.read(buff)) > -1) {
				os.write(buff, 0, readBytes);
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
