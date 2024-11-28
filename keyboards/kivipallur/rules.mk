SRC += swapper.c
SRC += oneshot.c
SPLIT_KEYBOARD = yes

# Optical sensor driver for trackball.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360

CAPS_WORD_ENABLE = yes
UNICODEMAP_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
MOUSEKEY_ENABLE = yes
