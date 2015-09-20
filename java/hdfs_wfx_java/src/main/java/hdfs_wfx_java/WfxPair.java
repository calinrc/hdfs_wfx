package hdfs_wfx_java;

import hdfs_wfx_java.exception.WfxHdfsException;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.log4j.Logger;

public class WfxPair {

	private static final Logger log = Logger.getLogger(WfxPair.class);
	private FileSystem fileSystem;

	public WfxPair() {

	}

	private long nativePtr = 0;

	void setNativePair(long nativePtr) {
		this.nativePtr = nativePtr;

	}

	public void notifyProgress() {
		if (checkInitted()) {
			notifyProgress(this.nativePtr);
		}

	}

	private boolean checkInitted() {
		return nativePtr != 0;
	}

	private native void notifyProgress(long nativePtr);

	/**
	 * @return int value translation of WfxErrorCodes
	 */
	public void initFS() {
		log.debug("Initialize FS");
		try {
			Configuration config = new Configuration();

			for (String file : new String[] { "core-site.xml",
					"mapred-site.xml", "hdfs-site.xml", "yarn-site.xml" }) {
				URL url = new File(System.getProperty("user.home")
						+ File.separatorChar
						+ ".config/doublecmd/plugins/hdfs_wfx/java/" + file)
						.toURI().toURL();
				if (url != null) {
					config.addResource(url);
				}

			}

			FileSystem fileSystem = FileSystem.get(config);
			this.fileSystem = fileSystem;
		} catch (IOException ioEx) {
			log.info("Unable to create HDFS file system", ioEx);
			throw new WfxHdfsException(ioEx);
		}
	}

	/**
	 * @param folderPath
	 * @return String[]
	 */
	public String[] getFolderContent(String folderPath) {
		try {
			log.debug("Try getting folder content for " + folderPath);
			Path fPath = new Path(folderPath);
			if (this.fileSystem.isDirectory(fPath)) {
				List<String> contentList = new ArrayList<String>();
				FileStatus[] fstatuses = this.fileSystem.listStatus(fPath);
				for (FileStatus status : fstatuses) {
					contentList.add(status.getPath().getName());
				}
				return contentList.toArray(new String[contentList.size()]);
			} else {
				return new String[0];
			}

		} catch (IOException ioEx) {
			log.error("FAIL on getting folder content for " + folderPath, ioEx);
			throw new WfxHdfsException(ioEx);
		}
	}

	public FileInformation getFileInformation(String parentFolder,
			String fileName) {
		log.debug("Try getting file informations for " + parentFolder + "/"
				+ fileName);
		try {
			FileStatus fstatus = this.fileSystem.getFileStatus(new Path(
					parentFolder + "/" + fileName));
			return new FileInformation(fstatus);
		} catch (IOException ioEx) {
			log.error("FAIL on getting file info for " + parentFolder + "/"
					+ fileName, ioEx);
			throw new WfxHdfsException(ioEx);
		}
	}

}
