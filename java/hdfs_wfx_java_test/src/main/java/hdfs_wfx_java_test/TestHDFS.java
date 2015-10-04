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
