# coral

Coral is a kernel space linux keylogger that logs keys by registering a keyboard notifier with
the kernel.

## Building

To build coral, ensure that the "kmod" and "build-essential" packages are installed (or the
appropriate equivalent for your distribution) as well as the linux-headers for your kernel version.

For Ubuntu/Debian, installing the linux-headers can be done using:
```
# apt install linux-headers-`uname -r`
```

After installing the necessary packages, coral can be easily built using:
```
# make
```

## Installing

Once built, coral can be installed by inserting the module into the kernel:
```
# insmod coral-lkm.ko
```

This will register the character-device driver, create the character device used to interact
with coral in `/dev`, and register the keyboard notifier.

## Usage

After installing, the keys that are logged can be viewed by running:
```
# cat /dev/coral-dev
```

## Removing

To remove coral, use the following command:
```
# rmmod coral-lkm
```

Removing coral will destroy the character device, unregister the character device driver,
and unregister the keyboard notifier.
