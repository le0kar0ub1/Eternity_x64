#ifndef _CPU_DESCRIPTOR_H_
#define _CPU_DESCRIPTOR_H_

struct cpu_descriptor {
  uint8  thread;
  uint8  core;
  uint8  chip;
  uint32 domain;
};

#endif
