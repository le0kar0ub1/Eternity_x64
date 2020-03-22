arch 		:= 	x86_64
BUILD_DIR	:=	build
kernel 		:= 	$(BUILD_DIR)/eternity-$(arch).bin
iso 		:= 	$(BUILD_DIR)/eternity-$(arch).iso

LINKER_SCRIPT 	:= src/link.ld
GRUB_CFG 		:= src/grub.cfg

ROOT_SOURCE_DIR	:= src/$(arch)/

INCLUDE_DIR	 := $(addprefix -Iinc/,			\
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
							threads		 	\
							abstractor		\
							/				\
							)
SOURCE_DIR := 	/					\
				boot				\
				assemblyTools		\
				descriptors			\
				drivers				\
				lib					\
				interrupts			\
				interrupts/syscall	\
				memory				\
				processor			\
				network				\
				system				\
				tty					\
				abstractor			\
				userspace			\
				threads


ld := ld
LDFLAGS := -n						\
			-nostdlib				\
			-entry=_start			\
			-z max-page-size=0x1000	\
			-g						\
			#$(LDFALGS_DEBUG)

LDFALGS_DEBUG := --cref			\
				--print-map		\
				--relocatable	\

nasm := nasm
asflags :=  -felf64         \
			$(INCLUDE_DIR)   \
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

qemuflags := -cdrom $(iso)        	\
	         -enable-kvm          	\
			 -m 4G					\
		     #-boot menu=on			\
		     #$(qemu_basic_device)
	     	 #-full-screen

gcc := gcc

CFLAGS := -nostdlib		 			 		\
	  	  -fno-builtin           	 		\
	  	  -fno-stack-protector   	 		\
	  	  -W 			 			 		\
	  	  -Wall 		 			 		\
	  	  -Wextra					 		\
	  	  -Wnested-externs 	 		 		\
	  	  -Winline 		 			 		\
          -Wpragmas				  			\
	  	  --std=gnu11 		 		 		\
	  	  $(INCLUDE_DIR) 	         		\
	  	  -Wuninitialized        	 		\
          -Wno-missing-braces    	 		\
	      -ffreestanding         	 		\
	  	  -Wcast-align           	 		\
          -Wwrite-strings        	 		\
          -fno-omit-frame-pointer	 		\
	  	  -mno-red-zone				 		\
	  	  -g3						 		\
	  	  -mcmodel=large 			 		\
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
		  -Wno-logical-not-parentheses		\
	  	  #-Wpadded						\

CFLAGS_RESTRICT :=	-Wmissing-declarations			\
					-Wmissing-prototypes			\
					-Wstrict-prototypes				\
					-Werror

ASM_SRC :=	$(wildcard $(addsuffix /*.asm, $(addprefix $(ROOT_SOURCE_DIR), $(SOURCE_DIR))))

C_SRC	:=	$(wildcard $(addsuffix /*.c, $(addprefix $(ROOT_SOURCE_DIR), $(SOURCE_DIR))))

OBJECTS := 	$(patsubst src/$(arch)/%.asm, $(BUILD_DIR)/arch/$(arch)/%.o, $(ASM_SRC)) 		\
			$(patsubst src/$(arch)/%.c, $(BUILD_DIR)/arch/$(arch)/%.o, $(C_SRC))

.PHONY: all clean fclean run debug info gdbdebug disassemble symbols

all: $(kernel) $(iso)

re:	fclean all

clean:	fclean

fclean:
	@-printf "\e[1;31m"
	@-echo -e "\033[91mcleaning $(BUILD_DIR)\033[0m"
	@rm -rf $(BUILD_DIR)
	@-printf "\e[0m"

run:
	@-echo -e "\033[36mrunning...\033[0m"
	@$(qemuarch) $(qemuflags) -serial stdio

info:
	@$(qemuarch) $(qemuflags)           \
            -d int,cpu_reset            \
            --no-reboot				 \
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

$(iso): $(kernel) $(GRUB_CFG)
	@mkdir -p $(BUILD_DIR)/isofiles/boot/grub
	@cp $(kernel) $(BUILD_DIR)/isofiles/boot/kernel.bin
	@cp $(GRUB_CFG) $(BUILD_DIR)/isofiles/boot/grub
	@grub-mkrescue -o $(iso) $(BUILD_DIR)/isofiles 2> /dev/null
	@rm -r $(BUILD_DIR)/isofiles
	@-echo -e "\033[37m     GRUB   $@\033[0m"

$(kernel): $(OBJECTS) $(LINKER_SCRIPT)
	@$(ld) $(LDFLAGS) -T $(LINKER_SCRIPT) -o $(kernel) $(OBJECTS)
	@-echo -e "\033[37m   LINKED   $@\033[0m"

$(BUILD_DIR)/arch/$(arch)/%.o: src/$(arch)/%.asm
	@mkdir -p $(shell dirname $@)
	@mkdir -p $(addprefix $(BUILD_DIR)/arch/$(arch)/, $(SOURCE_DIR))
	@$(nasm) $(asflags) $< -o $@
	@-echo -e "\033[34m     NASM   $@\e[0m"

$(BUILD_DIR)/arch/%.o: src/%.c
	@$(gcc) $(CFLAGS) -c $< -o $@
	@-echo -e "\e[34m      GCC   $@\e[0m"
