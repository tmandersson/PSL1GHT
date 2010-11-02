#include "rsx/reality.h"
#include "rsx/gcm.h"

void realityFlushBuffer(gcmContextData *context) {
	gcmControlRegister *control = gcmGetControlRegister(context);
	__asm __volatile__("sync"); // Sync, to make sure the command was written;
	uint32_t offset;
	gcmAddressToOffset(context->current, &offset);
	control->put = offset;
}

/* Maps the memory at ioAddress into the RSX's memory space so the userspace thread
 * and the RSX can comunicate.
 * This shared memory must be 1mb aligned, and at least 1mb long.
 * Also Initilizes a RSX command buffer of cmdSize inside the shared memory. 
 * 
 * Returns a context structure.
 */
gcmContextData *realityInit(const uint32_t cmdSize, const uint32_t ioSize, const void* ioAddress) {
	uint32_t contextPointer;
	int ret = gcmInitBody(&contextPointer, cmdSize, ioSize, ioAddress);
	if (ret == 0) {
		// Double cast fixes warning about diffrent pointer sizes.
		gcmContextData *context = (gcmContextData *) (uint64_t) contextPointer;
		return context;
	}
	return NULL;
}

int realityAddressToOffset(void* ptr, uint32_t *offset) {
	// Double cast for warnings.
	return gcmAddressToOffset((uint32_t) (uint64_t) ptr, offset);
}
