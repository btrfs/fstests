# SPDX-License-Identifier: GPL-2.0
# Copyright (c) 2003-2005 Silicon Graphics, Inc.  All Rights Reserved.
#

TOPDIR = ..
include $(TOPDIR)/include/builddefs

TARGETS = doio fsstress fsx iogen
SCRIPTS = rwtest.sh
CFILES = $(TARGETS:=.c)
HFILES = doio.h
LDIRT = $(TARGETS)
LCFLAGS = -DXFS
LCFLAGS += -I$(TOPDIR)/src #Used for including $(TOPDIR)/src/global.h

ifeq ($(HAVE_AIO), true)
TARGETS += aio-stress
LCFLAGS += -DAIO
LLDLIBS += -laio -lpthread
endif

ifeq ($(HAVE_URING), true)
LCFLAGS += -DURING
LLDLIBS += -luring
endif

ifeq ($(HAVE_LIBBTRFSUTIL), true)
LLDLIBS += -lbtrfsutil
endif

ifeq ($(HAVE_FALLOCATE), true)
LCFLAGS += -DFALLOCATE
endif

ifeq ($(HAVE_COPY_FILE_RANGE),yes)
LCFLAGS += -DHAVE_COPY_FILE_RANGE
endif

ifeq ($(NEED_INTERNAL_XFS_IOC_EXCHANGE_RANGE),yes)
LCFLAGS += -DNEED_INTERNAL_XFS_IOC_EXCHANGE_RANGE
endif

default: depend $(TARGETS)

depend: .dep

include $(BUILDRULES)

$(TARGETS): $(LIBTEST)
	@echo "    [CC]    $@"
	$(Q)$(LTLINK) $@.c -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(LIBTEST)

install: default
	$(INSTALL) -m 755 -d $(PKG_LIB_DIR)/ltp
	$(LTINSTALL) -m 755 $(TARGETS) $(PKG_LIB_DIR)/ltp
	$(INSTALL) -m 755 $(SCRIPTS) $(PKG_LIB_DIR)/ltp

-include .dep
