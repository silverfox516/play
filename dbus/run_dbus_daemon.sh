#!/usr/bin/bash

if ! test -f /var/lib/dbus/machine-id; then
	sudo dbus-uuidgen --ensure=/var/lib/dbus/machine-id
fi

if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then
	## if not found, launch a new one
	eval `dbus-launch --sh-syntax`
	echo "D-Bus per-session daemon address is: $DBUS_SESSION_BUS_ADDRESS"
fi
