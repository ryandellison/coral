/*
 * coral_device.c
 *
 * The purpose of this file is to perform the main actions for the character
 * device driver.
 *
 * Author: Ryan Ellison
 *
 */

#include <linux/fs.h>            /* file_operations struct, simple_read_from_buffer() */

#include "coral_device.h"        
#include "coral_notifier.h"      /* keybuf */

/*
 * device_read()
 *
 * @filp:   file from file system point of view
 * @buffer: buffer to write to provided by user
 * @length: num of bytes to put in buffer (num of bytes being read by caller)
 *
 * Return:  number of characters read
 *
 */

static ssize_t device_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
  return simple_read_from_buffer(buffer, length, offset, keybuf, BUFFER_LENGTH);
}


/* the file_operations struct for registering the device */
struct file_operations fops = {
  .read = device_read,
};
