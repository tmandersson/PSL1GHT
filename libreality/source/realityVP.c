#include "rsx/realityVP.h"
#include "string.h"

void *realityVertexProgramGetUCode(realityVertexProgram *vertexprogram)
{
	unsigned char *ptr=(unsigned char *)vertexprogram;

	return (void*)(ptr+vertexprogram->UCodeOffset);
}

unsigned int realityVertexProgramGetInputMask(realityVertexProgram *vertexprogram)
{
	return vertexprogram->InputMask;
}

unsigned int realityVertexProgramGetOutputMask(realityVertexProgram *vertexprogram)
{
	return vertexprogram->OutputMask;
}

realityVertexProgramAttribute *realityVertexProgramGetAttributes(realityVertexProgram *vertexprogram)
{
	return (realityVertexProgramAttribute*) (((unsigned char*)vertexprogram)+vertexprogram->AttributesOffset);
}

int realityVertexProgramGetInputAttribute(realityVertexProgram *vertexprogram,const char *name)
{
	int i;
	realityVertexProgramAttribute *attributes = realityVertexProgramGetAttributes(vertexprogram);
	for(i=0;i<vertexprogram->NumAttributes;++i)
	{
		char *namePtr;
		if(attributes[i].NameOffset==0)
			continue;
		namePtr=((char*)vertexprogram)+attributes[i].NameOffset;
		if(strcasecmp(name,namePtr)==0)
			return attributes[i].Index;
	}

	return -1;
}

realityVertexProgramConstant *realityVertexProgramGetConstants(realityVertexProgram *vertexprogram)
{
	return (realityVertexProgramConstant*) (((unsigned char*)vertexprogram)+vertexprogram->ConstantsOffset);
}

int realityVertexProgramGetConstant(realityVertexProgram *vertexprogram,const char *name)
{
	int i;
	realityVertexProgramConstant *constants = realityVertexProgramGetConstants(vertexprogram);
	for(i=0;i<vertexprogram->NumConstants;++i)
	{
		char *namePtr;
		if(constants[i].NameOffset==0)
			continue;
		namePtr=((char*)vertexprogram)+constants[i].NameOffset;
		if(strcasecmp(name,namePtr)==0)
			return constants[i].Index;
	}

	return -1;
}