package hdfs_wfx_java;

import hdfs_wfx_java.exception.WfxHdfsException;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.log4j.Logger;

public class FileSystemProxy {
	private FileSystem fileSystem;
	private static final Logger log = Logger.getLogger(FileSystemProxy.class);

	public void init() {
		try {
			Configuration config = new Configuration();
			FileSystem fileSystem = FileSystem.get(config);
			this.fileSystem = fileSystem;
		} catch (IOException ioEx) {
			log.info("Unable to create HDFS file system", ioEx);
			throw new WfxHdfsException(ioEx);
		}
	}

}
