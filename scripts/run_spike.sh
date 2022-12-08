#!/bin/bash


BASE_DIR=../
MMIO_PLUGIN=$BASE_DIR/mmio_plugin/pcie_rc_plugin.so
DTS=$BASE_DIR/device_tree/cs262a.dtb

spike  -m16384 --dtb=$DTS \
  --extlib=$MMIO_PLUGIN \
  --device=pcie_rc_plugin,0x40000000,hi  \
  /scratch/joonho.whangbo/coding/accel_integration_chipyard/software/firemarshal/images/br-driver-bin
