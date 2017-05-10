TMK Keyboard Firmware Collection
================================
This repository includes keyboard and converter firmware projects.

The latest source code is available here: <http://github.com/tmk/tmk_keyboard>


Start Your Own Project
-----------------------
1. Add `tmk_core` into your repository using `git submodule` or `git subtree`.
2. Copy files from `tmk_keybaord` or other project similar to yours
3. Edit those files to support your keyboard.

See these as examples.
- https://github.com/tmk/infinity_ergodox
- https://github.com/tmk/whitefox



Debugging
--------
Use PJRC's `hid_listen` to see debug messages. You can use xprintf() to display debug info, see `tmk_core/common/xprintf.h`.

- https://www.pjrc.com/teensy/hid_listen.html



Files and Directories
-------------------
### Top
* keyboard/     - keyboard projects
* converter/    - protocol converter projects
* tmk_core/     - core library
* tmk_core/doc/ - documents


Coding Style
-------------
- Doesn't use Tab to indent, use 4-spaces instead.



Other Keyboard Firmware Projects
------------------
You can learn a lot about keyboard firmware from these. See [Other Projects](https://github.com/tmk/tmk_keyboard/wiki/Other-Projects) other than TMK.
