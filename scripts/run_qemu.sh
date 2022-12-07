#!/bin/bash

echo $RISCV
QEMU=$RISCV/bin/qemu-system-riscv64
MEM=16384
CHIPYARD=/scratch/joonho.whangbo/coding/accel_integration_chipyard
FIREMARSHAL="$CHIPYARD/software/firemarshal"
KERNEL="$FIREMARSHAL/images/br-base-bin"
IMAGE="$FIREMARSHAL/images/br-base.img"
DTB=../device_tree/qemu.dtb


$QEMU -s -S -nographic -bios none \
  -smp 4 -machine virt -m $MEM \
  -kernel $KERNEL \
  -object rng-random,filename=/dev/urandom,id=rng0 \
  -device virtio-rng-device,rng=rng0 \
  -device virtio-net-device,netdev=usernet \
  -netdev user,id=usernet,hostfwd=tcp::52819-:22 \
  -device virtio-blk-device,drive=hd0 \
  -drive file=$IMAGE,format=raw,id=hd0 \
  -dtb $DTB
