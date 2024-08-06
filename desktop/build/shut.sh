#!/bin/sh

echo -e "[killing exe]"
ps | grep "duos-pad/exe" | awk '{print $1}' | head -n1 | xargs kill

echo -e "[unloading gt9xx.ko]"
rmmod /mnt/system/ko/3rd/gt9xx.ko

echo -e "[unloading cvi_fb.ko]"
rmmod /mnt/system/ko/cvi_fb.ko