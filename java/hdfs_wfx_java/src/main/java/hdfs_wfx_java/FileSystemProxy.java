package hdfs_wfx_java;

import hdfs_wfx_java.exception.WfxHdfsException;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.log4j.Logger;

public class FileSystemProxy {
	private FileSystem fileSystem;
	private static final Logger log = Logger.getLogger(FileSystemProxy.class);

	/**
	 * 
	 */
	public void init() {
		try {
			Configuration config = new Configuration();
			FileSystem fileSystem = FileSystem.newInstance(config);
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
			Path fPath = new Path(folderPath);
			if (this.fileSystem.isDirectory(fPath)) {
				List<String> contentList = new ArrayList<String>();
				FileStatus[] fstatuses = this.fileSystem.listStatus(fPath);
				for (FileStatus status : fstatuses) {
					contentList.add(status.getPath().toString());
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
}
