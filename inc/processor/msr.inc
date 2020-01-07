%ifndef _MSR_INC_
%define _MSR_INC_

; syscall / sysret INTEL Init
%define MSR_IA32_SYSENTER_CS   0x174
%define MSR_IA32_SYSENTER_RSP  0x175
%define MSR_IA32_SYSENTER_RIP  0x176

%define MSR_IA32_BASE  0x80000001
%define MSR_IA32_EFER  0xC0000080
%define MSR_IA32_STAR  0xC0000081
%define MSR_IA32_LSTAR 0xC0000082
%define MSR_IA32_MASK  0xC0000084

; define for msr ==  0xC0000080

%define MSR_SCE 0x0
; 1-7 Reserved
%define MSR_LME   8  
%define MSR_LMA   10 
%define MSR_NXE   11 
%define MSR_SVME  12 
%define MSR_LMSLE 13 
%define MSR_FFXSR 14 
%define MSR_TCE   15 
; 16-63 Reserved

%endif