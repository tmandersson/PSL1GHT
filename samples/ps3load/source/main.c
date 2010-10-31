#include <lv2/process.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <zlib.h>

#define VERSION "v0.1"
#define PORT 4299
#define MAX_ARG_COUNT 0x100

#define ERROR(a, msg) { \
	if (a < 0) { \
		fprintf(stderr, "PS3Load: " msg "\n"); \
		return 1; \
	} \
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SELF_PATH "/dev_hdd0/tmp/ps3load.self"

int main(int argc, const char* argv[], const char* envp[])
{
	printf("PS3Load " VERSION "\n");

	int s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	ERROR(s, "Error creating socket()");

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);

	ERROR(bind(s, (struct sockaddr*)&server, sizeof(server)), "Error bind()ing socket");

	ERROR(listen(s, 10), "Error calling listen()");

#define continueloop() { close(c); goto reloop; }
reloop:
	while (1) {
		printf("Waiting for connection...\n");
		int c = accept(s, NULL, NULL);
		ERROR(c, "Error calling accept()");

		u32 magic = 0;
		if (read(c, &magic, sizeof(magic)) < 0)
			continueloop();
		if (strncmp((char*)&magic, "HAXX", 4)) {
			fprintf(stderr, "Wrong HAXX magic.\n");
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

		printf("Receiving data... (0x%08x/0x%08x)\n", filesize, uncompressed);

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

		printf("Receiving arguments... 0x%08x\n", argslen);

		u8* args = NULL;
		if (argslen) {
			args = (u8*)malloc(argslen);
			if (read(c, args, argslen) < 0)
				continueloop();
		}

		close(c);

		printf("Decompressing...\n");

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

		printf("Launching...\n");

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

		sysProcessExitSpawn2(SELF_PATH, (const char**)launchargv, (const char**)launchenvp, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
	}

	return 0;
}
