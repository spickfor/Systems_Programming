#!/bin/sh

if [ $# -ne 1 ]; then
    echo "Usage: $(basename $0) lockbox"
    exit 1
fi

LOCKBOX=$(readlink -f $1)

# TODO: Try all strings in $LOCKBOX as password
for password in $(strings $LOCKBOX); do
    # TODO: Exit with success if using password as argument to $LOCKBOX works
    $LOCKBOX $password && exit 0
done

echo "Unable to crack $LOCKBOX!"
exit 2