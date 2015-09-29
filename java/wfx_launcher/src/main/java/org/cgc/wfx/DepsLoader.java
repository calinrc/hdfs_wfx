package org.cgc.wfx;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.List;

import org.cgc.wfx.exception.WfxHdfsException;

public class DepsLoader {

	private String folderPath;

	public DepsLoader(String folderPath) {
		this.folderPath = folderPath;
	}

	ClassLoader loadFolder() {
		try {
			File f = new File(folderPath);
			List<URL> urls = new ArrayList<URL>();

			if (f.exists() && f.isDirectory()) {
				File[] content = f.listFiles();
				for (File item : content) {
					if (!item.isDirectory()) {
						URL url = item.toURI().toURL();
						urls.add(item.toURI().toURL());
						System.out.println("Load file " + url);
					}
				}
			} else {
				urls.add(new File(folderPath).toURI().toURL());
			}
			URLClassLoader urlClassLoader = URLClassLoader
					.newInstance(urls.toArray(new URL[urls.size()]), getClass()
							.getClassLoader());

			return urlClassLoader;
		} catch (MalformedURLException ex) {
			ex.printStackTrace();
			throw new WfxHdfsException(ex);
		}
	}
}
