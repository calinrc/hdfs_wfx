package org.cgc.wfx;

public class FSClientLauncher {

	private static final String PAIR_CLASS = "org.cgc.wfx.impl.FileSystemProxy";

	public static WfxPair getPairInstance(String dependencyFolder) {
		try {
			DepsLoader loader = new DepsLoader(dependencyFolder);
			ClassLoader cl = loader.loadFolder();
			Class<?> pairClasss = cl.loadClass(PAIR_CLASS);
			Object obj = pairClasss.newInstance();
			if (obj instanceof WfxPair) {
				return (WfxPair) obj;
			}
		} catch (ClassNotFoundException cnfEx) {
			cnfEx.printStackTrace();
			System.err.println("Unable to find WfxPair class "
					+ cnfEx.getMessage());
		} catch (IllegalAccessException illAcEx) {
			illAcEx.printStackTrace();
			System.err
					.println("Fail on accessing WfxPair implementation with message"
							+ illAcEx.getMessage());
		} catch (InstantiationException instEx) {
			instEx.printStackTrace();
			System.err
					.println("Fail on instantiate WfxPair object with message"
							+ instEx.getMessage());
		} catch (Throwable thr) {
			thr.printStackTrace();
			System.err
					.println("Fail on initialization HDFS client with message"
							+ thr.getMessage());
		}
		System.err.println("Fail on creating new instance of Wfx Pair");
		return null;
	}

}
