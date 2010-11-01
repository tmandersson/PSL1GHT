#include <psl1ght/lv2.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include <sysutil/video.h>
#include <rsx/gcm.h>

#include <psl1ght/lv2.h>

int context;

int main(int argc, const char* argv[])
{
	int ret;
	void *host_addr = memalign(1024*1024, 1024*1024); // Allocate a 1Mb buffer, alligned to a 1mb boundary.
	assert(host_addr != 0);

	printf("Allocated 1Mb buffer @ 0x%x\n", (long) host_addr);

	ret = gcmInitBody(&context, 0x10000, 1024*1024, host_addr);
       /* For some reason this returns 0x80010002 instead of working.
	* I've traced the problem to a lv1_gpu_context_iomap in lv2 
        * (@ 0x8000000000113C98 in 3.41). It's claiming that it failed to map
        * the io address I gave it (host_addr).  
	*/
	printf("gcmInitBody(), ret=0x%x, context=0x%x\n", ret, context);
	assert(ret == 0);

	return 0;
}

