/* VideoInfo:
 * This example querys the PS3 for its current reslution and prints it to tty.
 * You will need something that redirects tty to see the output.
 */

#include <psl1ght/lv2.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <sysutil/video.h>

// For pretty printfs
const char *scanMode[] = {"Interlaced", "Progressive"};
const char *conversion[] = {"None", "WXGA", "SXGA", "WUXGA", "1080", "Remote Play"};
const char *aspect[] = {"auto", "4:3", "16:9"};
const char *colorSpace[] = {"?", "RGB", "YUV", "??", "XVYCC"};
const char *videoStatus[] = {"Enabled", "Disabled", "Busy"};

int main(int argc, const char* argv[])
{
	printf("\nCurrent Video Settings:\n");

	VideoState state;
	videoGetState(0, 0, &state);

	printf("State: \t\t%s\nColor Space: \t%s\n", 
		videoStatus[state.state], 
		colorSpace[state.colorSpace]);

	// Query actual Resolution from Resolution ID
	VideoResolution res;
	videoGetResolution(state.displayMode.resolution, &res);

	printf("resolution: \t%ix%i\nscanMode: \t%s\nconversion: \t%s\naspect: \t%s\nrefreshRates: \t0x%x\n",
		res.width, res.height,
		scanMode[state.displayMode.scanMode],
		conversion[state.displayMode.conversion],
		aspect[state.displayMode.aspect],
		state.displayMode.refreshRates);

	return 0;
}
