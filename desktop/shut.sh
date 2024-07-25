#!/bin/sh

echo -e "[killing exe]"
ps | grep "duos-pad/exe" | awk '{print $1}' | head -n1 | xargs kill
