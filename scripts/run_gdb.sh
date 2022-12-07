#!/bin/bash


GDB=$RISCV/bin/riscv64-unknown-elf-gdb

CHIPYARD=/scratch/joonho.whangbo/coding/accel_integration_chipyard
FIREMARSHAL="$CHIPYARD/software/firemarshal"
IMAGE="$FIREMARSHAL/images/br-base-bin-dwarf"

$GDB $IMAGE
