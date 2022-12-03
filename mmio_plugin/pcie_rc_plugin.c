#include <riscv/mmio_plugin.h>
#include <stdio.h>
#include <stdlib.h>
// #include <asm-generic/io.h>

#define RC_BASE 0x40000000

void* pcie_rc_plugin_alloc(const char* args)
{
    printf("ALLOC -- ARGS=%s\n", args);
    //return (void *)0x123456789ABCEDF;
		uint32_t * config_space = (uint32_t  *)malloc(4096);

		config_space[0] = 0x00C5262A;
		config_space[1] = 0x00000000;
		config_space[2] = 0x06000005; //class code: 0x06(bridge), subclass code:0x0 (host bridge), Prog IF: 0x0 (Normal Decode)
		config_space[3] = 0x00010000;	 // Not BIST capable, don't start BIST, single function PCI-to-PCIBridge header type, latency timer = 0, cache line size = 0
		config_space[4] = 0x00000000; // BAR0
		config_space[5] = 0x00000000; // BAR1
		config_space[6] = 0x00000000; // Secondary Latency timer = 0, subordinate, primary and secondary bsese = 0
		config_space[7] = 0x00000000;
		config_space[8] = 0x00000000;
		config_space[9] = 0x00000000;
		config_space[10] = 0x00000000;
		config_space[11] = 0x00000000;
		config_space[12] = 0x00000000;
		config_space[13] = 0x00000000;
		config_space[14] = 0x00000000;
		config_space[15] = 0x00000000;

		return (void *) config_space;
}

bool pcie_rc_plugin_load(void* self, reg_t addr, size_t len, uint8_t* bytes)
{
    printf("LOAD -- SELF=%p ADDR=0x%lx LEN=%lu BYTES=%p\n", self, addr, len, (void*)bytes);
		printf("Read config space: %d", *((uint32_t *) self));
//    int val;

    // if outside range fail
    if (addr < RC_BASE && addr >= RC_BASE+64) {
        return false;
    }

/*
    for(int of = 0; of < len; of++) {
        //val = ioread32((void *)(addr + of));   // read config space
        val = 0xDEADBEEF;   // read config space

        bytes[4*of + 0] = (0x000000FF & val);
        bytes[4*of + 1] = (0x0000FF00 & val) >> 8;
        bytes[4*of + 2] = (0x00FF0000 & val) >> 16;
        bytes[4*of + 3] = (0xFF000000 & val) >> 24;

    }
*/
    return true;
}

bool pcie_rc_plugin_store(void* self, reg_t addr, size_t len, const uint8_t* bytes)
{
    //int val;

		printf("PCIe: Attempting store\n");

    // if outside range fail
    if (addr < RC_BASE && addr >= RC_BASE+64) {
        return false;
    }


    for(int of = 0; of < len; of+=4) {
        // iowrite32(bytes[4*of] || (bytes[4*of + 1] << 8) || (bytes[4*of + 2] << 16) || (bytes[4*of + 3] << 24), (void *)addr);
        printf("iowrite32 not available\n");
    }

    return true;
}

void pcie_rc_plugin_dealloc(void* self)
{
    printf("DEALLOC -- SELF=%p\n", self);
    //free(self);
}

__attribute__((constructor)) static void on_load()
{
  static mmio_plugin_t pcie_rc_plugin = {
      pcie_rc_plugin_alloc,
      pcie_rc_plugin_load,
      pcie_rc_plugin_store,
      pcie_rc_plugin_dealloc
  };

  register_mmio_plugin("pcie_rc_plugin", &pcie_rc_plugin);
}
