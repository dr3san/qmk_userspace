#!/usr/bin/bash

FIRMWARE_KBD=$(qmk env QMK_FIRMWARE)/keyboards
USERSPACE_KBD=$(qmk config user.overlay_dir | cut -d'=' -f2)/keyboards

for keyboard_path in "$USERSPACE_KBD"/*; do
    if [ -d "$keyboard_path" ]; then
	keyboard=$(basename "$keyboard_path")
	echo "Syncing $keyboard"
        rsync -au --delete "$USERSPACE_KBD/$keyboard/" "$FIRMWARE_KBD/$keyboard/"
    fi
done
