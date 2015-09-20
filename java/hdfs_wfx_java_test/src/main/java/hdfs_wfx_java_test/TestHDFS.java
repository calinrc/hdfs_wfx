package hdfs_wfx_java_test;

import hdfs_wfx_java.WfxPair;

public class TestHDFS {

	public static void main(String[] args) {
		try {
			WfxPair pair = new WfxPair();
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
