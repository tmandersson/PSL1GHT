#include <spu_intrinsics.h>
#include <spu_mfcio.h>

int main(uint64_t ea, uint64_t outptr, uint64_t arg3, uint64_t arg4)
{
#if 0
	/* memory-aligned buffer */
	volatile vec_uchar16 tmp;
	char *buf = (char *)&tmp;

	/* fetch the 16 bytes using dma */
	//mfc_get(buf, ea, 16, 0, 0, 0);

	/* wait for dma transfer to be finished */
	//mfc_write_tag_mask(1);
	//spu_mfcstat(MFC_TAG_UPDATE_ALL);

	/* fetch all 16 bytes into a character vector */
	vec_uchar16 v = tmp;

	/* compare all characters with the small 'a' caracter code */
	vec_uchar16 cmp = spu_cmpgt(v, spu_splats((unsigned char)'a'));

	/* for all small characters, we remove 0x20 to get the corresponding capital*/
	vec_uchar16 sub = spu_splats((unsigned char)0x20) & cmp;
	v = v - sub;

	/* write the updated vector to memory */
	*((vec_uchar16 *)buf) = v;

	/* send the updated vector to ppe */
	//mfc_put(buf, ea, 16, 0, 0, 0);

	/* wait for dma transfer to be finished */
	//mfc_write_tag_mask(1);
	//spu_mfcstat(MFC_TAG_UPDATE_ALL);

	/* send a message to inform the ppe program that the work is done */
	//uint32_t ok = 1;
	//mfc_put(&ok, outptr, 4, 0, 0, 0);

	/* wait for dma transfer to be finished */
	//mfc_write_tag_mask(1);
	//spu_mfcstat(MFC_TAG_UPDATE_ALL);
#endif

	return 0;
}
