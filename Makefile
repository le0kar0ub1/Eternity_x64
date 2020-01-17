arch := x86_64
kernel := build/eternity-$(arch).bin
iso := build/eternity-$(arch).iso

linker_script := src/link.ld
grub_cfg := src/grub.cfg

rootSourceDir	:= src/$(arch)/

includeDir := $(addprefix -Iinc/,			\
                         	descriptors		\
                         	boot			\
                         	interrupt		\
                         	def				\
                         	drivers			\
                         	memory			\
                         	lib				\
                         	system			\
                         	tty				\
                         	processor		\
                         	threads       	\
                            abstractor      \
                         	/				\
    					 	)
sourceDir := 	/					\
				boot				\
				assemblyToolChain	\
                descriptors        	\
 				drivers			    \
  				lib				    \
   				interrupts   	    \
                interrupts/syscall  \
    			memory			    \
	 		    processor		    \
	  			network			    \
	   			system			    \
	    		tty				    \
		 		abstractor		    \
				userspace			\
				threads


ld := ld
ldflags := -n						\
	   	   -nostdlib				\
	   	   -entry=_start			\
		   -z max-page-size=0x1000	\
		   -g						\
	   	  #$(ldflags_debug)

ldflags_debug := --cref			\
	   	 		--print-map		\
	   	 		--relocatable	\

nasm := nasm
asflags :=  -felf64         \
            $(includeDir)   \
            -w+all          \
            -Werror

qemuarch := qemu-system-x86_64
qemu_networking :=   -net nic,vlan=0,model=rtl8139 -net user,vlan=0 #-net nic,model=rtl8139 -net user #-netdev user,id=n1 -device rtl8139,netdev=n1
		     #-netdev tap,id=hostnet0,script=/etc/qemu-ifup  \
		     -device rtl8139,netdev=hostnet0,id=rtl1,mac=54:52:1b:36:1a:01 #-device rtl8139
qemu_basic_device := -usb		\
		     -device usb-mouse  \
		     -device usb-tablet \
		     -soundhw pcspk

qemuflags := -cdrom $(iso)        \
	         -enable-kvm          \
			 -m 4G                \
		     #-boot menu=on        \
		     #$(qemu_basic_device)
	     	 #-full-screen

gcc := ~/Personnal/OSdev/cross-gcc/x86_64-elf-4.9.1-target/bin/x86_64-elf-gcc-4.9.1
CFLAGS := -nostdlib		 			 		\
	  	  -fno-builtin           	 		\
	  	  -fno-stack-protector   	 		\
	  	  -W 			 			 		\
	  	  -Wall 		 			 		\
	  	  -Wextra					 		\
	  	  -Wnested-externs 	 		 		\
	  	  -Winline 		 			 		\
          -Wpragmas                  		\
	  	  --std=gnu11 		 		 		\
	  	  $(includeDir) 	         		\
	  	  -Wuninitialized        	 		\
          -Wno-missing-braces    	 		\
	      -ffreestanding         	 		\
	  	  -Wcast-align           	 		\
          -Wwrite-strings        	 		\
          -fno-omit-frame-pointer	 		\
	  	  -mno-red-zone				 		\
	  	  -g3						 		\
	  	  -mcmodel=kernel 			 		\
		  -nostartfiles          	 		\
		  -static					 		\
		  -msse4.1				     		\
		  -Wparentheses						\
		  -Wunreachable-code				\
		  -Wunused							\
		  -Wmissing-field-initializers		\
 		  -Wswitch-enum						\
 		  -Wshadow							\
 		  -Wuninitialized					\
	  	  #-Wpadded						\

CFLAGS_RESTRICT :=	-Wmissing-declarations			\
 		  			-Wmissing-prototypes			\
 		  			-Wstrict-prototypes				\
  		  			-Werror

asm_src :=	$(wildcard $(addsuffix /*.asm, $(addprefix $(rootSourceDir), $(sourceDir))))

c_src	:=	$(wildcard $(addsuffix /*.c, $(addprefix $(rootSourceDir), $(sourceDir))))

objects := 	$(patsubst src/$(arch)/%.asm, build/arch/$(arch)/%.o, $(asm_src)) 		\
			$(patsubst src/$(arch)/%.c, build/arch/$(arch)/%.o, $(c_src))

.PHONY: all clean fclean run debug info gdbdebug disassemble symbols

all: $(kernel) $(iso)

re:	fclean all

clean:	fclean

fclean:
	@-printf "\e[1;31m"
	@-echo -e "\033[91mcleaning build\033[0m"
	@rm -rf build
	@-printf "\e[0m"

run:
	@-echo -e "\033[36mrunning...\033[0m"
	@$(qemuarch) $(qemuflags) -serial stdio #run with KVM module (set in BIOS)

info:
	@$(qemuarch) $(qemuflags)           \
            -d int,cpu_reset            \
            --no-reboot                 \
            -monitor stdio

gdbdebug:
	@$(qemuarch) $(qemuflags) -monitor stdio -no-reboot -gdb tcp::9090 -S

debug:
	@-echo -e "\033[36mrunning in debug mode...\033[0m"
	@$(qemuarch) $(qemuflags) -monitor stdio -no-reboot -s -S

disassemble: $(kernel)
	@objdump --no-show-raw-insn -d -Mintel $(kernel) | source-highlight -s asm -f esc256 | less -eRiMX

symbols: $(kernel)
	@readelf $(kernel) -s | less

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles
	@-echo -e "\033[37m     GRUB   $@\033[0m"

$(kernel): $(objects) $(linker_script)
	@$(ld) $(ldflags) -T $(linker_script) -o $(kernel) $(objects)
	@-echo -e "\033[37m   LINKED   $@\033[0m"

build/arch/$(arch)/%.o: src/$(arch)/%.asm
	@mkdir -p $(shell dirname $@)
	@mkdir -p $(addprefix build/arch/$(arch)/, $(sourceDir))
	@$(nasm) $(asflags) $< -o $@
	@-echo -e "\033[34m     NASM   $@\e[0m"

build/arch/%.o: src/%.c
	@$(gcc) $(CFLAGS) -c $< -o $@
	@-echo -e "\e[34m      GCC   $@\e[0m"
