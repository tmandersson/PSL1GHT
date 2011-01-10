#include <spu_intrinsics.h>
#include <spu_mfcio.h>

int main(uint64_t ea, uint64_t outptr, uint64_t arg3, uint64_t arg4)
{
	/* memory-aligned buffer (vectors always are properly aligned) */
	volatile vec_uchar16 v;

	/* fetch the 16 bytes using dma */
	mfc_get(&v, ea, 16, 0, 0, 0);

	/* wait for dma transfer to be finished */
	mfc_write_tag_mask(1);
	spu_mfcstat(MFC_TAG_UPDATE_ALL);

	/* compare all characters with the small 'a' character code */
	vec_uchar16 cmp = spu_cmpgt(v, spu_splats((unsigned char)'a'-1));

	/* for all small characters, we remove 0x20 to get the corresponding capital*/
	vec_uchar16 sub = spu_splats((unsigned char)0x20) & cmp;
	v = v - sub;

	/* send the updated vector to ppe */
	mfc_put(&v, ea, 16, 0, 0, 0);

	/* wait for dma transfer to be finished */
	mfc_write_tag_mask(1);
	spu_mfcstat(MFC_TAG_UPDATE_ALL);

	/* send a message to inform the ppe program that the work is done */
	uint32_t ok = 1;
	mfc_put(&ok, outptr, 4, 0, 0, 0);

	/* wait for dma transfer to be finished */
	mfc_write_tag_mask(1);
	spu_mfcstat(MFC_TAG_UPDATE_ALL);

	return 0;
}
