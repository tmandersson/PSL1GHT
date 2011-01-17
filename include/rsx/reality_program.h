#ifndef __REALITY_PROGRAM_H__
#define __REALITY_PROGRAM_H__

#include <psl1ght/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reality_vp
{
	u16 magic;
	u16 num_attrib;
	u32 attrib_off;

	u32 input_mask;
	u32 output_mask;

	u16 const_start;
	u16 num_const;
	u32 const_off;

	u16 start_insn;
	u16 num_insn;
	u32 ucode_off;
} realityVertexProgram;

typedef struct reality_fp
{
	u16 magic;
	u16 num_attrib;
	u32 attrib_off;

	u32 num_regs;
	u32 fp_control;

	u16 _pad0;

	u16 num_const;
	u32 const_off;

	u16 num_insn;
	u32 ucode_off;
} realityFragmentProgram;

typedef struct reality_const
{
	u32 name_off;
	u32 index;
	u8 type;
	u8 is_internal;
	u8 count;

	u8 _pad0;
	
	union {
		u32 u;
		f32 f;
	} values[4];

} realityProgramConst;

typedef struct reality_attrib
{
	u32 name_off;
	u32 index;
} realityProgramAttrib;

#ifdef __cplusplus
	}
#endif

#endif
