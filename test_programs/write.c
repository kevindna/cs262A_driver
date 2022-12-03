//#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
//#include <asm/mmio.h>
//#include <asm-generic/io.h>
//#include <io.h>
//#include <types.h>


//static inline void __raw_writel(u_int32_t val, volatile void __iomem *addr) {
//	asm volatile("sw %0, 0(%1)" : : "r" (val), "r" (addr));
//}


int main()  {

	printf("Write test program\n");
	//asm volatile("sw %0, 0(%1)" : : "r" (0xDEAF), "r" (0x10000000));
//	__raw_writel(0xDEAF, 0x23424);

  int val;
	int addr = 0x40000000;
  asm volatile("lw %0, 0(%1)" : "=r" (val) : "r" (addr));





	return 0;
}


