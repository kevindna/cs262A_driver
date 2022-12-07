
function create_dtb() {
  dtc -O dtb -o $1.dtb $1.dts
}

create_dtb qemu
create_dtb cs262a

