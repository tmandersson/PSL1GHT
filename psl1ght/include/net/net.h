#pragma once

#include <psl1ght/types.h>
#include <sys/types.h>
#include <stdlib.h>

typedef struct sys_net_initialize_parameter {
	void *memory;
	int memory_size;
	int flags;
} sys_net_initialize_parameter_t;

//#define sys_net_errno (*_sys_net_errno_loc())

#define libnet_errno *_sys_net_errno_loc()

EXTERN_BEGIN

#define sys_net_initialize_network() ({ \
	static char __libnet_memory[128 * 1024]; \
	sys_net_initialize_parameter_t __libnet_param; \
	__libnet_param.memory = __libnet_memory; \
	__libnet_param.memory_size = sizeof(__libnet_memory); \
	__libnet_param.flags = 0; \
	sys_net_initialize_network_ex(&__libnet_param); \
})

int sys_net_initialize_network_ex(sys_net_initialize_parameter_t *param);

s32* _sys_net_errno_loc(void);

EXTERN_END
