/* VideoInfo:
 * This example querys the PS3 for its current reslution and prints it to tty.
 * You will need something that redirects tty to see the output.
 */

#include <audio/audio.h>
#include <math.h>
#include <assert.h>


#define PI 3.14159265f

void fillBuffer(float *buf)
{
	static float pos=0;

	for (unsigned int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
	{
		buf[i*2+0] = sin(pos);
		buf[i*2+1] = sin(pos*2);
		pos+=0.01f;
		if(pos>M_PI)
			pos-=2*M_PI;
	}
}

u32 playOneBlock(AudioPortConfig config)
{
	u32 current_block = *config.readIndex;
	static u32 audio_block_index=1;


	if(audio_block_index == current_block)
	{
		return 0;
	}
	//                                   
	float *buf = config.audioDataStart + 2 /*channelcount*/ * AUDIO_BLOCK_SAMPLES * audio_block_index;
	fillBuffer(buf);

	audio_block_index = (audio_block_index + 1) % AUDIO_BLOCK_8;

	return 1;
}

int main(int argc, const char* argv[])
{
	AudioPortParam params;
	AudioPortConfig config;
	u32 portNum;

	audioInit();

	params.numChannels = AUDIO_PORT_2CH;
	params.numBlocks = AUDIO_BLOCK_8;
	params.attr = 0;
	params.level = 1;

	assert(audioPortOpen(&params, &portNum)==0);

	audioGetPortConfig(portNum, &config);

	audioPortStart(portNum);


	int i=0;
	while(i<1000)
	{
		if(playOneBlock(config))
			i++;
	}

	return i;

}
