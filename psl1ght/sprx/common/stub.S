#include "config.h"

.align 2
.section ".rodata.sceFNID","a"
.global LIBRARY_SYMBOL
LIBRARY_SYMBOL:

#define EXPORT(name, fnid) \
.align 2; \
.section ".sceStub.text","ax"; \
	.global __##name; \
	__##name: \
		mflr %r0; \
		std %r0, 0x18(%r1); \
		std %r2, 0x28(%r1); \
		li %r2, name##_stub@l; \
		oris %r2, %r2, name##_stub@ha; \
		lwz %r2, 0x00(%r2); \
		lwz %r0, 0x00(%r2); \
		lwz %r2, 0x04(%r2); \
		mtctr %r0; \
		bctrl; \
		ld %r2, 0x28(%r1); \
		ld %r0, 0x18(%r1); \
		mtlr %r0; \
		blr; \
.align 3; \
.section ".opd","aw"; \
	.global name; \
	name: \
		.quad __##name, .TOC.@tocbase, 0

#include "exports.h"
