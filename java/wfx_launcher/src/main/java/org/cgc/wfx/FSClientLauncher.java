package org.cgc.wfx;

import org.cgc.wfx.exception.WfxHdfsException;

public class FSClientLauncher {

	private static final String PAIR_CLASS = "org.cgc.wfx.impl.FileSystemProxy";

	public static WfxPair getPairInstance(String dependencyFolder) {
		try {
			System.out.println("Try getting WfxPair instance");
			DepsLoader loader = new DepsLoader(dependencyFolder);
			ClassLoader cl = loader.loadFolder();
			if (cl != null) {
				Thread.currentThread().setContextClassLoader(cl);
				Class<?> pairClasss = cl.loadClass(PAIR_CLASS);
				Object obj = pairClasss.newInstance();
				if (obj instanceof WfxPair) {
					System.out.println("WfxPair instance obtained");
					return (WfxPair) obj;
				}
			} else {
				System.err
						.println("Unable to initialize the new class loader with hdfs dependencies");

			}
		} catch (ClassNotFoundException cnfEx) {
			cnfEx.printStackTrace();
			System.err.println("Unable to find WfxPair class "
					+ cnfEx.getMessage());
			throw new WfxHdfsException(cnfEx);
		} catch (IllegalAccessException illAcEx) {
			illAcEx.printStackTrace();
			System.err
					.println("Fail on accessing WfxPair implementation with message"
							+ illAcEx.getMessage());
			throw new WfxHdfsException(illAcEx);
		} catch (InstantiationException instEx) {
			instEx.printStackTrace();
			System.err
					.println("Fail on instantiate WfxPair object with message"
							+ instEx.getMessage());
			throw new WfxHdfsException(instEx);
		} catch (Throwable thr) {
			thr.printStackTrace();
			System.err
					.println("Fail on initialization HDFS client with message"
							+ thr.getMessage());
			throw new WfxHdfsException(thr);
		}
		System.err.println("Fail on creating new instance of Wfx Pair");
		return null;
	}

}
