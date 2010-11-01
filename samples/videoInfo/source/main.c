#include <psl1ght/lv2.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <sysutil/video.h>

int main(int argc, const char* argv[])
{
	printf("Video Test\n\n");

	videoState state;
	videoGetState(0, 0, &state);

	printf("state: %i\ncolourSpace: %i\n", state.state, state.colorSpace);

	return 0;
}
