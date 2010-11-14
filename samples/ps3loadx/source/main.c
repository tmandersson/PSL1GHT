#include <lv2/process.h>
#include <psl1ght/lv2/thread.h>
#include <sysmodule/sysmodule.h>
#include <sysutil/video.h>
#include <sysutil/events.h>
#include <rsx/gcm.h>
#include <rsx/reality.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <zlib.h>

#include "font.h"
void s_printf( char *format, ...);


#include <jpgdec/loadjpg.h>
#include "psl1ght_jpg.bin.h" // jpg in memory

JpgDatas jpg1;

void release_all();

#define VERSION "v0.2"
#define PORT 4299
#define MAX_ARG_COUNT 0x100

#define ERROR(a, msg) { \
	if (a < 0) { \
		color=0xFF3F00; \
		s_printf("PS3Load: " msg "\n"); \
		release_all();\
		sleep(2); \
		return 1; \
	} \
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SELF_PATH "/dev_hdd0/tmp/ps3load.self"

#include <io/pad.h>
gcmContextData *context; // Context to keep track of the RSX buffer.

VideoResolution res; // Screen Resolution

int currentBuffer = 0;
s32 *buffer[2]; // The buffer we will be drawing into.

void waitFlip() { // Block the PPU thread untill the previous flip operation has finished.
	while(gcmGetFlipStatus() != 0) 
		usleep(200);
	gcmResetFlipStatus();
}

void flip(s32 buffer) {
	assert(gcmSetFlip(context, buffer) == 0);
	realityFlushBuffer(context);
	gcmSetWaitFlip(context); // Prevent the RSX from continuing until the flip has finished.
}

u8 aspect;

// Initilize everything. You can probally skip over this function.
void init_screen() {
	// Allocate a 1Mb buffer, alligned to a 1Mb boundary to be our shared IO memory with the RSX.
	void *host_addr = memalign(1024*1024, 1024*1024);
	assert(host_addr != NULL);

	// Initilise Reality, which sets up the command buffer and shared IO memory
	context = realityInit(0x10000, 1024*1024, host_addr); 
	assert(context != NULL);

	VideoState state;
	assert(videoGetState(0, 0, &state) == 0); // Get the state of the display
	assert(state.state == 0); // Make sure display is enabled

	// Get the current resolution
	assert(videoGetResolution(state.displayMode.resolution, &res) == 0);
	
	// Configure the buffer format to xRGB
	VideoConfiguration vconfig;
	memset(&vconfig, 0, sizeof(VideoConfiguration));
	vconfig.resolution = state.displayMode.resolution;
	vconfig.format = VIDEO_BUFFER_FORMAT_XRGB;
	vconfig.pitch = res.width * 4;
	aspect=vconfig.aspect=state.displayMode.aspect;

	assert(videoConfigure(0, &vconfig, NULL, 0) == 0);
	assert(videoGetState(0, 0, &state) == 0); 

	s32 buffer_size = 4 * res.width * res.height; // each pixel is 4 bytes
	printf("buffers will be 0x%x bytes\n", buffer_size);
	
	gcmSetFlipMode(GCM_FLIP_VSYNC); // Wait for VSYNC to flip

	// Allocate two buffers for the RSX to draw to the screen (double buffering)
	buffer[0] = rsxMemAlign(16, buffer_size);
	buffer[1] = rsxMemAlign(16, buffer_size);
	assert(buffer[0] != NULL && buffer[1] != NULL);

	u32 offset[2];
	assert(realityAddressToOffset(buffer[0], &offset[0]) == 0);
	assert(realityAddressToOffset(buffer[1], &offset[1]) == 0);
	// Setup the display buffers
	assert(gcmSetDisplayBuffer(0, offset[0], res.width * 4, res.width, res.height) == 0);
	assert(gcmSetDisplayBuffer(1, offset[1], res.width * 4, res.width, res.height) == 0);

	gcmResetFlipStatus();
	flip(currentBuffer);
}


// virtual screen

u32 *virtual_scr= NULL;

#define VIRTUAL_WIDTH  768
#define VIRTUAL_HEIGHT 512

void rescaler(u32 *scr, int wscr, int hscr, u32 *buf, int wbuf, int hbuf) {

	int n,m;

	int w, h, cws, chs, cwb, chb, ws, wb;

	// screen correction offset
	if(wscr> res.width) wscr =res.width; else  scr+=(res.width-wscr)/2;
	if(hscr> res.height) hscr =res.height; else  scr+= res.width*(res.height-hscr)/2;


	h= hscr; if(h<hbuf) h= hbuf;

	w= wscr; if(w<wbuf) w= wbuf;

	chs=chb=0;

	for(n=0; n<h; n++)
	{
	
	cws=cwb=ws=wb=0;

		for(m=0; m<w; m++) {

			scr[ws]= buf[wb]; 
		 
			cws+= wscr; if(cws>=w) {cws-=w; ws++;}
			cwb+= wbuf; if(cwb>=w) {cwb-=w; wb++;}
		}
    
	chs+= hscr; if(chs>=h) {chs-=h; scr+=res.width;}
	chb+= hbuf; if(chb>=h) {chb-=h; buf+=wbuf;}

	}

}

// thread

PadInfo padinfo;
PadData paddata;

int running = 1;

volatile int my_socket=-1;
volatile int flag_exit=0;

static void thread_start(u64 arg)
{
	
	int i;
	
	while(running ){
		ioPadGetInfo(&padinfo);
		for(i=0; i<MAX_PADS; i++){
			if(padinfo.status[i]){
				ioPadGetData(i, &paddata);
				
				if(paddata.BTN_CROSS && my_socket!=-1){
					
					flag_exit=1;
						
					close(my_socket);
					my_socket=-1;
	
				}
			}
		}
		

		sys_ppu_thread_yield();
		
		waitFlip();

		// re-scale and draw virtual screen to real screen

		// 480P / 576P
		if(res.width<1280) {

			rescaler((u32 *) buffer[currentBuffer], res.width-80 , res.height-32, virtual_scr, VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
		
		} else if(res.width==1280) {
        // 720P
			rescaler((u32 *) buffer[currentBuffer], res.width-120 , res.height-32, virtual_scr, VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
		
		} else {
		// 1080i
			rescaler((u32 *) buffer[currentBuffer], res.width-160 , res.height-112, virtual_scr, VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
		
		}
		
		flip(currentBuffer);
		sysCheckCallback();
		currentBuffer^=1;
		
	}
	//you must call this, kthx
	sys_ppu_thread_exit(0);
}




// console

#include <stdarg.h> 

static int PX=0, PY=0;
static u32 color=0xffffffff;

void PutChar(int x, int y, u8 c, unsigned e_color) {

	int n, m, k;

	u32 r=255, g=255, b=255, a;
	u32 r2, g2, b2;

	b= e_color & 0xff;
	g= (e_color>>8) & 0xff;
	r= (e_color>>16) & 0xff;

	if(x < 0 || y < 0 || x > (VIRTUAL_WIDTH-16) || y > (VIRTUAL_HEIGHT-32)) return;

	if(c < 32) return;

	c-=32;
	
	u32 * scr= (u32 *) virtual_scr;
	
	scr+= x + y * VIRTUAL_WIDTH;

	k= c * 16 * 32;

	// chars 16 x 32  2 bits intensity (ANSI charset from 32 to 255)

	for(n=0; n<32; n++) {
		for(m=0; m<16; m++) {

			a=((font[k>>2]>>((k & 3)<<1)) & 3)*85;

			if(a!=0) {
				r2= (r * a)>>8;
				g2= (g * a)>>8;
				b2= (b * a)>>8;
				
				e_color= (r2<<16) | (g2<<8) | (b2) | 0xff000000;

				scr[m]= e_color;

			}
		k++;
		}

	scr+= VIRTUAL_WIDTH;
	}	
}

void cls()
{
	//memset((void *) virtual_scr, 0, VIRTUAL_WIDTH*VIRTUAL_HEIGHT*4);

// fill screen

	s32 i, j;
	for(i = 0; i < VIRTUAL_HEIGHT; i++) {
		s32 color2 = (int)((i / (VIRTUAL_HEIGHT * 1.0) * 256)) & 255;
		// This should make a nice black to green graident
		color2 |= 0x30<<16;
		for(j = 0; j < VIRTUAL_WIDTH; j++)
			virtual_scr[i* VIRTUAL_WIDTH + j] = color2;
		}

	PX= 0; PY= 0;

	// display logo

	if(jpg1.bmp_out) {
		
			int x=0,y=0;

			u32 *scr=  (u32 *) virtual_scr;
			u32 *jpg= (u32 *) jpg1.bmp_out;
			int n, m, l, addx;
			
			// calculate coordinates for JPG

			x=(VIRTUAL_WIDTH-16)+8- jpg1.width*48/64; addx=48;
			y= 0+8;

			scr+= y* VIRTUAL_WIDTH + x;

			// draw JPG
		
			for(n=0;n<jpg1.height;n++) {

				if((y+n)>=res.height) break;
				l=0;	
				for(m=0;m<jpg1.width;m++) {
				
					scr[l>>6]=jpg[m];

				l+= addx;

				}
			
			jpg+=jpg1.wpitch>>2;
			scr+= VIRTUAL_WIDTH;

			}
		
		}
}

void s_printf( char *format, ...) {
	va_list	opt;
	static  u8 buff[2048];

	memset(buff, 0, 2048);
	va_start(opt, format);
	vsprintf( (void *) buff, format, opt);
	va_end(opt);

	u8 *buf = (u8 *) buff;
	while(*buf) {

		if(*buf == '\n') {PX= 0; PY+= 32;}
		else if(*buf == 9) PX+=16;
		else if(*buf >= 32) {
			PutChar(PX, PY, *buf, color);
			PX+=16;
		}

	buf++;

	if(PX < 0) PX= 0;
	if(PX > (VIRTUAL_WIDTH-16)) {PX= 0; PY+= 32;}
	if(PY < 0) PY= 0;
	if(PY > (VIRTUAL_HEIGHT-32)) {cls();}
	
	}

/*
// square test
PutChar(0, 0, '*', 0x00ff00);
PutChar((VIRTUAL_WIDTH-16), 0, '*', 0x00ff00);
PutChar(0, (VIRTUAL_HEIGHT-32), '*', 0x00ff00);
PutChar((VIRTUAL_WIDTH-16), (VIRTUAL_HEIGHT-32), '*', 0x00ff00);
*/
return;
}

static void sys_callback(uint64_t status, uint64_t param, void* userdata) {

     switch (status) {
		case EVENT_REQUEST_EXITAPP:
			if(my_socket!=-1) {
				flag_exit=1;
				close(my_socket);
				my_socket=-1;
			}
			release_all();
			sysProcessExit(1);
			break;
      
       default:
		   break;
         
	}
}

sys_ppu_thread_t thread1_id;

void release_all() {

	u64 retval;

	sysUnregisterCallback(EVENT_SLOT0);
	running= 0;
	sys_ppu_thread_join(thread1_id, &retval);
	SysUnloadModule(SYSMODULE_JPGDEC);

}

int main(int argc, const char* argv[], const char* envp[])
{
	
	SysLoadModule(SYSMODULE_JPGDEC);

	init_screen();
	ioPadInit(7);

	// alloc memory for virtual screen

	virtual_scr = malloc (VIRTUAL_WIDTH*VIRTUAL_HEIGHT*4);
	
	u64 thread_arg = 0x1337;
	u64 priority = 1500;
	size_t stack_size = 0x1000;
	char *thread_name = "Control Thread ps3load";

    sys_ppu_thread_create( &thread1_id, thread_start, thread_arg, priority, stack_size, THREAD_JOINABLE, thread_name);

	// register exit callback
	sysRegisterCallback(EVENT_SLOT0, sys_callback, NULL);

	jpg1.jpg_in= (void *) psl1ght_jpg_bin;
	jpg1.jpg_size= sizeof(psl1ght_jpg_bin);

	LoadJPG(&jpg1, NULL);
	
	cls();

	color=0xFFFF00;
	s_printf("PS3Load " VERSION " - PSL1GHT\n\n");

	color=0xFFFFFF;

	s_printf("Creating socket..\n\n");

	my_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	ERROR(my_socket, "Error creating socket()");

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);

	s_printf("Binding socket..\n\n");

	ERROR(bind(my_socket, (struct sockaddr*)&server, sizeof(server)), "Error bind()ing socket");


	ERROR(listen(my_socket, 10), "Error calling listen()");

#define continueloop() { close(c); goto reloop; }

reloop:

	cls();

	color=0xFFFF00;
	s_printf("PS3Load " VERSION " - PSL1GHT\n\n");

	color=0xFFFFFF;

	s_printf("Press 'X' to exit\n\n");

	while (1) {
		
		if(flag_exit) break;

		color=0xFFFFFF;
		s_printf("Waiting for connection...\n\n");
		color=0x00FF00;
		
		int c = accept(my_socket, NULL, NULL);

		if(flag_exit) break;

		ERROR(c, "Error calling accept()");

		u32 magic = 0;
		if (read(c, &magic, sizeof(magic)) < 0)
			continueloop();
		if (strncmp((char*)&magic, "HAXX", 4)) {
			s_printf("Wrong HAXX magic.\n");
			continueloop();
		}
		if (read(c, &magic, sizeof(magic)) < 0)
			continueloop();
		u16 argslen = magic & 0xFFFF;
		
		u32 filesize = 0;
		if (read(c, &filesize, sizeof(filesize)) < 0)
			continueloop();

		u32 uncompressed = 0;
		if (read(c, &uncompressed, sizeof(uncompressed)) < 0)
			continueloop();

		s_printf("Receiving data... (0x%08x/0x%08x)\n", filesize, uncompressed);

		u8* data = (u8*)malloc(filesize);
		u32 pos = 0;
		u32 count;
		while (pos < filesize) {
			u32 count = MIN(0x1000, filesize - pos);
			int ret = read(c, data + pos, count);
			if (ret < 0)
				continueloop();
			pos += ret;
		}

		s_printf("Receiving arguments... 0x%08x\n", argslen);

		u8* args = NULL;
		if (argslen) {
			args = (u8*)malloc(argslen);
			if (read(c, args, argslen) < 0)
				continueloop();
		}

		close(c);

		s_printf("Decompressing...\n");

		if (filesize != uncompressed) {
			u8* compressed = data;
			uLongf final = uncompressed;
			data = (u8*)malloc(final);
			int ret = uncompress(data, &final, compressed, filesize);
			if (ret != Z_OK)
				continue;
			free(compressed);
			if (uncompressed != final)
				continue;
			uncompressed = final;
		}

		s_printf("Launching...\n");

		int fd = open(SELF_PATH, O_CREAT | O_TRUNC | O_WRONLY);
		ERROR(fd, "Error opening temporary file.");

		pos = 0;
		while (pos < uncompressed) {
			count = MIN(0x1000, uncompressed - pos);
			write(fd, data + pos, count);
			pos += count;
		}

		close(fd);

		char* launchenvp[2];
		char* launchargv[MAX_ARG_COUNT];
		memset(launchenvp, 0, sizeof(launchenvp));
		memset(launchargv, 0, sizeof(launchargv));

		launchenvp[0] = (char*)malloc(0x440);
		snprintf(launchenvp[0], 0x440, "ps3load=%s", argv[0]);

		pos = 0;
		int i = 0;
		while (pos < argslen) {
			int len = strlen((char*)args + pos);
			if (!len)
				break;
			launchargv[i] = (char*)malloc(len + 1);
			strcpy(launchargv[i], (char*)args + pos);
			pos += len + 1;
			i++;
		}

		release_all();
		sleep(1);
		sysProcessExitSpawn2(SELF_PATH, (const char**)launchargv, (const char**)launchenvp, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
	}
	s_printf("Exiting...\n");
	
	release_all();

	sleep(2);
	return 0;
}
