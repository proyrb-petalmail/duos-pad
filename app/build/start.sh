#!/bin/sh

echo -e "[loading cvi_fb.ko]"
insmod /mnt/system/ko/cvi_fb.ko vxres=800 vyres=1280

echo -e "[loading gt9xx.ko]"
insmod /mnt/system/ko/3rd/gt9xx.ko

echo -e "[launching exe]"
nice -n -20 /root/duos-pad/app/setup/exe
