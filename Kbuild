#
# Kbuild
#
# This file is used by kernel versions that recognize it, or is included
# in the Makefile for versions that do not.
#
# Author: Ryan Ellison
#

# kbuild looks for this file "Kbuild" first, otherwise looks in our makefile

obj-m += coral_lkm.o

# used to build module from multiple sources
coral_lkm-y := coral.o coral_device.o coral_notifier.o

