all: pcie-cs262a-driver.o

CHIPYARD=/scratch/joonho.whangbo/coding/accel_integration_chipyard
MARSHAL=$(CHIPYARD)/software/firemarshal

LINUX=$(MARSHAL)/boards/chipyard/linux
LINUXINCLUDES=$(LINUX)/include

ARCH=$(LINUX)/arch/riscv
ARCHINCLUDES=$(ARCH)/include

INCLUDEDIRS = -I$(LINUXINCLUDES) -I$(ARCHINCLUDES)


pcie-cs262a-driver.o :
	gcc pcie-cs262a-driver.c $(INCLUDEDIRS)  -o pcie-cs262a-driver.o


obj-$(CONFIG_MY_DRIVER) += pcie-cs262a-driver.o
