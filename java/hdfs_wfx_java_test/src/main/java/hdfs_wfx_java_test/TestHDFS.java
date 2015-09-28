package hdfs_wfx_java_test;

import org.cgc.wfx.FSClientLauncher;
import org.cgc.wfx.WfxPair;

public class TestHDFS {

	public static void main(String[] args) {
		try {
			String path = System.getProperty("user.home");
			
			WfxPair pair = FSClientLauncher.getPairInstance(path + "/.config/doublecmd/plugins/hdfs_wfx/java/deps ");
			System.out.println("Init");
			pair.initFS();
			String[] content = pair.getFolderContent("/");
			for (String item : content) {
				System.out.println("\t" + item);
			}
			System.out.println("End");

		} catch (Throwable thr) {
			thr.printStackTrace();
		}
	}

}
