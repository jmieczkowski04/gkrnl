CC:=gcc
AS:=gcc
AR:=ar
LD:=ld
MAKE:=make

export CC AS AR LD MAKE

abs_srctree := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
abs_objtree := $(abs_srctree)

export abs_srctree abs_objtree


CFLAGS := -I$(abs_srctree)/include -std=gnu11 -fno-common -m32 -O2 -fno-pie -fno-builtin -fomit-frame-pointer -fno-stack-protector -c 
ASFLAGS := -I$(abs_srctree)/include -m32 -O2 -fno-pie -fno-builtin -fomit-frame-pointer -c -DASM_FILE
ARFLAGS := cDPrT # P?
MAKEFLAGS += --no-print-directory --rR



export CFLAGS ASFLAGS ARFLAGS MAKEFLAGS 

Q:=@
ifeq ("$(origin V)", "command line")
Q:=
endif
export Q

all: 
ifeq ($(abs_objtree), $(abs_srctree))
srctree := .
endif
objtree := .
	
export srctree objtree


BUILD_MAKEFILE := $(srctree)/scripts/Makefile.build
build := -f $(srctree)/scripts/Makefile.build obj
export BUILD_MAKEFILE build

all: gkrnl launch
	@:

launch: gkrnl
	$(Q)qemu-system-i386 -kernel gkrnl

gkrnl: build gkrnl.lds
	$(Q)echo "LD\t gkrnl"
	$(Q)$(LD) -T gkrnl.lds built-in.a -o gkrnl
	$(Q)grub-file --is-x86-multiboot gkrnl

clean:
	$(Q)$(MAKE) $(build)=. clean
	$(Q)rm -f gkrnl

prepare:
	$(Q)mkdir -p $(OBJTREE)

build:
	$(Q)$(MAKE) $(build)=.

.PHONY: all clean prepare build
