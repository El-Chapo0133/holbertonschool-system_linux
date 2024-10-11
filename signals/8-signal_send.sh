#!/bin/sh
# Send SIGQUIT to given pid
# If no pid givend
if [ "$#" -ne 1 ]; then
	echo "Usage: $0 <pid>"
	exit 1
fi

kill -QUIT "$1"
