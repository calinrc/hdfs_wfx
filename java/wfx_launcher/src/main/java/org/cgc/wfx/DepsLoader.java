/*
 *    DeepsLoader.java file written and maintained by Calin Cocan
 *    Created on: Oct 05, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

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
