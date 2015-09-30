package org.cgc.wfx.impl;

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
import org.cgc.wfx.Constants;
import org.cgc.wfx.FileInformation;
import org.cgc.wfx.WfxPair;
import org.cgc.wfx.exception.WfxHdfsException;

public class FileSystemProxy implements WfxPair {
	private static final Logger log = Logger.getLogger(FileSystemProxy.class);
	private FileSystem fileSystem;

	public FileSystemProxy() {
	}

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
						+ File.separatorChar + Constants.DEPENDENCIES_PATH
						+ File.separatorChar + file).toURI().toURL();
				if (url != null) {
					config.addResource(url);
				}

			}
			FileSystem fileSystem = FileSystem.get(config);
			this.fileSystem = fileSystem;
		} catch (Throwable ioEx) {
			log.info("Unable to create HDFS file system", ioEx);
			throw new WfxHdfsException(ioEx);
		} finally {
			log.debug("End Initialize FS");
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
				log.debug("Folder content is : "+contentList);
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
			return new FileInformationImpl(fstatus);
		} catch (IOException ioEx) {
			log.error("FAIL on getting file info for " + parentFolder + "/"
					+ fileName, ioEx);
			throw new WfxHdfsException(ioEx);
		}
	}

}
