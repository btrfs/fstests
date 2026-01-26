// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2026 Christoph Hellwig.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (truncate(argv[1], 0) < 0) {
		perror("truncate");
		exit(1);
	}

	fprintf(stderr, "truncate succeeded\n");
}
