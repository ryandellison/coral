#
# Makefile
#
# Makefile split into kbuild part and normal part to support backwards compatability
# with kernels that doesn't know of Kbuild files.
# The command line call of this Makefile invokes the normal part,
# while the make calls in this file invoke the kbuild part.
#
# Author: Ryan Ellison
#

ifneq ($(KERNELRELEASE),)
# KBUILD PART
# -----------

include Kbuild

else
# NORMAL PART OF MAKEFILE
# -----------------------

PWD := $(CURDIR)

# directory where kernel source is located, this is a symlink to
KDIR ?= /lib/modules/`uname -r`/build


all:
	make -C $(KDIR) M=$(PWD) modules   # 'M=' sets directory of external module to build

clean:
	make -C $(KDIR) M=$(PWD) clean

endif
