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
		li %r12, 0; \
		oris %r12, %r12, name##_stub@ha; \
		lwz %r12, name##_stub@l(%r12); \
		std %r2, 40(%r1); \
		lwz %r0, 0(%r12); \
		lwz %r2, 4(%r12); \
		mtctr %r0; \
		bctr; \
.align 3; \
.section ".opd","aw"; \
	.global name; \
	name: \
		.quad __##name, .TOC.@tocbase, 0

#include "exports.c"
