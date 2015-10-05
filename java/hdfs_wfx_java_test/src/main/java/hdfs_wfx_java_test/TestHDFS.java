/*
 *    TestHDFS.java file written and maintained by Calin Cocan
 *    Created on: Oct 05, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

package hdfs_wfx_java_test;

import java.io.File;

import org.cgc.wfx.Constants;
import org.cgc.wfx.FSClientLauncher;
import org.cgc.wfx.FileInformation;
import org.cgc.wfx.WfxPair;

public class TestHDFS {

	public static void main(String[] args) {
		try {
			String path = System.getProperty("user.home");

			WfxPair pair = FSClientLauncher.getPairInstance(path
					+ File.separatorChar + Constants.DEPENDENCIES_PATH);
			System.out.println("Init");
			pair.initFS();
			String[] content = pair.getFolderContent("/");
			for (String item : content) {
				System.out.println("\t" + item);
				FileInformation fi = pair.getFileInformation("/", item);
				System.out.println("File " + fi);
			}
			System.out.println("End");

		} catch (Throwable thr) {
			thr.printStackTrace();
		}
	}

}
