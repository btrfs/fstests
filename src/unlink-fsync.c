// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2025 SUSE Linux Products GmbH.  All Rights Reserved.
 */

/*
 * Utility to open an existing file or directory, unlink or rmdir it while
 * holding an open fd on it and then fsync it before closing the fd.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	struct stat path_stat;
	int fd;
	int ret;

	if (argc != 2) {
		fprintf(stderr, "Use: %s <file or dir path>\n", argv[0]);
		return 1;
	}

	ret = stat(argv[1], &path_stat);
	if (ret == -1) {
		perror("stat failed");
		exit(1);
	}

	if (S_ISDIR(path_stat.st_mode))
		fd = open(argv[1], O_RDONLY | O_DIRECTORY);
	else
		fd = open(argv[1], O_WRONLY, 0666);

	if (fd == -1) {
		perror("failed to open file/dir");
		exit(1);
	}

	if (S_ISDIR(path_stat.st_mode)) {
		ret = rmdir(argv[1]);
		if (ret == -1) {
			perror("rmdir failed");
			exit(2);
		}
	} else {
		ret = unlink(argv[1]);
		if (ret == -1) {
			perror("unlink failed");
			exit(2);
		}
	}

	ret = fsync(fd);
	if (ret == -1) {
		perror("fsync failed");
		exit(3);
	}

	return 0;
}
