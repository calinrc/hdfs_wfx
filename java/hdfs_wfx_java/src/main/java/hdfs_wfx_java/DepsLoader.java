package hdfs_wfx_java;

import hdfs_wfx_java.exception.WfxHdfsException;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;

public class DepsLoader {

	private String folderPath;

	public DepsLoader(String folderPath) {
	}

	ClassLoader loadFolder() {
		try {
			URLClassLoader urlClassLoader = URLClassLoader
					.newInstance(new URL[] { new File(folderPath).toURI()
							.toURL() });

			return urlClassLoader;
		} catch (MalformedURLException ex) {
			ex.printStackTrace();
			throw new WfxHdfsException(ex);
		}
	}
}
