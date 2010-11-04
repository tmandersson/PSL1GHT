#include <psl1ght/lv2.h>
#include <psl1ght/lv2/filesystem.h>
#include <lv2/spu.h>

LV2_SYSCALL lv2SpuInitialize(u32 spus, u32 rawspus) { return Lv2Syscall2(169, spus, rawspus); }

LV2_SYSCALL lv2SpuRawCreate(u32* spu, u32* attributes) { return Lv2Syscall2(160, (u64)id, (u64)attributes); }
LV2_SYSCALL lv2SpuRawDestroy(u32 spu, u32 attributes) { return Lv2Syscall2(161, spu, attributes); }
LV2_SYSCALL lv2SpuRawCreateInterruptTag(u32 spu, u32 classid, u32 hardwarethread, u32* tag) { return Lv2Syscall4(150, spu, classid, hardwarethread, (u64)tag); }
LV2_SYSCALL lv2SpuRawSetIntMask(u32 spu, u32 classid, u64 mask) { return Lv2Syscall3(151, id, classid, mask); }
LV2_SYSCALL lv2SpuRawGetIntMask(u32 spu, u32 classid, u64* mask) { return Lv2Syscall3(152, id, classid, (u64)mask); }
LV2_SYSCALL lv2SpuRawSetIntStat(u32 spu, u32 classid, u64 stat) { return Lv2Syscall3(153, id, classid, stat); }
LV2_SYSCALL lv2SpuRawGetIntStat(u32 spu, u32 classid, u64* stat) { return Lv2Syscall3(154, id, classid, (u64)stat); }
LV2_SYSCALL lv2SpuRawReadPuintMb(u32 spu, u32* value) { return Lv2Syscall2(163, spu, (u64)value); }
LV2_SYSCALL lv2SpuRawSetCfg(u32 spu, u32 value) { return Lv2Syscall2(196, spu, value); }
LV2_SYSCALL lv2SpuRawGetCfg(u32 spu, u32* value) { return Lv2Syscall2(197, spu, (u64)value); }
LV2_SYSCALL lv2SpuRawRecoverPageFault(u32 spu) { return Lv2Syscall1(199, spu); }

LV2_SYSCALL lv2SpuImageOpen(sysSpuImage* image, const char* path) { return Lv2Syscall2(156, (u64)image, (u64)path); }
LV2_SYSCALL lv2SpuImageOpenFd(sysSpuImage* image, Lv2FsFile fd, u64 offset) { return Lv2Syscall3(260, (u64)image, fd, offset); }

LV2_SYSCALL lv2SpuThreadInitialize(u32* thread, u32* group, u32 spu, sysSpuImage* image, Lv2SpuThreadAttribute* attributes, Lv2SpuThreadArgument* arguments) { return Lv2Syscall(172, (u64)thread, (u64)group, spu, (u64)image, (u64)attributes, (u64)arguments); }
LV2_SYSCALL lv2SpuThreadSetArgument(u32 thread, Lv2SpuThreadArgument* arguments) { return Lv2Syscall(166, thread, (u64)arguments); }
