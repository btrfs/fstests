// SPDX-License-Identifier: GPL-2.0+
/*
 * Program to set a received UUID on a btrfs subvolume.
 */

#include <sys/ioctl.h>
#include <btrfs/ioctl.h>
#include <uuid/uuid.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	struct btrfs_ioctl_received_subvol_args args;
	uuid_t uuid;
	int ret;
	int fd;

	if (argc != 3) {
		fprintf(stderr, "Use: %s <uuid> <subvolume path>\n", argv[0]);
		return 1;
	}

	ret = uuid_parse(argv[1], uuid);
	if (ret == -1) {
		fprintf(stderr,
	"Invalid UUID. Example: 8c628557-6987-42b2-ba16-b7cc79ddfb43\n");
		return 2;
	}

	fd = open(argv[2], O_RDONLY | O_DIRECTORY, 0666);
	if (fd == -1) {
		perror("Failed to open fd");
		return 3;
	}

	memset(&args, 0, sizeof(args));
	memcpy(args.uuid, uuid, BTRFS_UUID_SIZE);

	ret = ioctl(fd, BTRFS_IOC_SET_RECEIVED_SUBVOL, &args);
	if (ret == -1) {
		perror("Failed to set received subvol");
		return 4;
	}

	return 0;
}
