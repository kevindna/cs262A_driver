# Scripts for building linux device drivers for RISC-V


## Directories
- `device_tree` : Some example device trees. Can generate device tree blobs (dtb) by running `create_dtb.sh`
- `mmio_plugin` : A mmio plugin example for `Spike`. It can be used to emulate a MMIO device in Spike
- `pcie_cs262a_controller` : Some example driver implementations & files to include in linux source

## Using Marshal
- `./marshal build <path to img config.json>`
  - e.g., `./marshal build ./boards/chipyard/base-workloads/br-base.json`
  - This command will rebuild linux & place the new kernel inside the generated image
- We can run this command in the CY conda env


## Building the RISC-V toolchain
- We need to build the riscv-toolchain that is independent with the CY conda env
  - Why ...?
- This will build gdb, gcc, qemu, and all sorts of necessary tools

```bash
git clone --recursive  https://github.com/riscv-collab/riscv-gnu-toolchain.git
cd riscv-gnu-toolchain
./configure --prefix=$PWD
make -j$(nproc) all
cd bin
ln -s ../qemu/build/qemu-system-riscv64 .
cd ..
export RISCV=$PWD
```

## Setting up QEMU
- Can start by using the `scripts/run_qemu.sh` script
- the `-S` option tells qemu to wait for another process to initiate it (in our case, it will be gdb)
- It uses the image that is made by Marshal above



## Attaching gdb to QEMU
- Can start by using the `scripts/run_gdb.sh` script
  - `br-base-bin-dwarf` basically has the debug flags for the image
- Inside gdb, `c` will trigger QEMU to boot
```
target remote localhost:1234
c
```

## Setting up termdebug
- Although the above steps are sufficient for development, there is some additional steps
to make life easier

- Add `let g:termdebugger=/path/to/your/gdb/binary` in your `vimrc`
  - For us, the gdb binary would be something like `$RISCV/bin/riscv64-unknown-linux-gnu-gdb`

- Then do something like this
```
vi .

// inside vim
:Termdebug

// inside the debug command prompt
file br-base-bin-dwarf
target remote localhost:1234
c
```



## Miscellaneous tips
- Export variable MARSHAL_BOARD_DIR to point to FireMarshal/board/chipyard directory
- Use spike 1.1.1-dev
