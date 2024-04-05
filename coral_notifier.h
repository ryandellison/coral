#ifndef CORAL_NOTIFIER_H
#define CORAL_NOTIFIER_H

#include <linux/notifier.h>      /* notifier_block struct */

/* length of keybuf */
#define BUFFER_LENGTH 512

extern char keybuf[];

extern int keybufpos;

extern struct notifier_block notif_block;

#endif
