#!/bin/sh

echo -e "[killing exe]"
ps | grep "setup/exe" | awk '{print $1}' | head -n1 | xargs kill
cat /dev/zero > /dev/fb0
