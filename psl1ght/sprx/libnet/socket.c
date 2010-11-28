#include <psl1ght/lv2/net.h>

#include <psl1ght/lv2/errno.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>

int h_errno = 0;

#define FD(socket) (socket & ~SOCKET_FD_MASK)

void* __netMemory = NULL;
#define LIBNET_INITIALIZED (__netMemory)

int netErrno(int ret)
{
	if (!LIBNET_INITIALIZED)
		return lv2Errno(ret);

	if (ret >= 0)
		return ret;

	errno = net_errno;
	return -1;
}

int accept(int socket, struct sockaddr* address, socklen_t* address_len)
{
	s32 ret;
	net_socklen_t len;
	net_socklen_t* lenp = (address && address_len) ? &len : NULL;
	if (LIBNET_INITIALIZED)
		ret = netAccept(FD(socket), address, lenp);
	else
		ret = lv2NetAccept(FD(socket), address, lenp);

	if (ret < 0)
		return netErrno(ret);

	if (lenp)
		*address_len = len;

	return ret | SOCKET_FD_MASK;
}

int bind(int socket, const struct sockaddr* address, socklen_t address_len)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netBind(FD(socket), address, (net_socklen_t)address_len);
	else
		ret = lv2NetBind(FD(socket), address, (net_socklen_t)address_len);
	return netErrno(ret);
}

int connect(int socket, const struct sockaddr* address, socklen_t address_len)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netConnect(FD(socket), address, (net_socklen_t)address_len);
	else
		ret = lv2NetConnect(FD(socket), address, (net_socklen_t)address_len);
	return netErrno(ret);
}

int listen(int socket, int backlog)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netListen(FD(socket), backlog);
	else
		ret = lv2NetListen(FD(socket), backlog);
	return netErrno(ret);
}

int socket(int domain, int type, int protocol)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netSocket(domain, type, protocol);
	else
		ret = lv2NetSocket(domain, type, protocol);

	if (ret < 0)
		return netErrno(ret);
	
	return ret | SOCKET_FD_MASK;
}

ssize_t send(int socket, const void* message, size_t length, int flags)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netSend(FD(socket), message, length, flags);
	else
		return sendto(socket, message, length, flags, NULL, 0);
	return netErrno(ret);
}

ssize_t sendto(int socket, const void* message, size_t length, int flags, const struct sockaddr* dest_addr, socklen_t dest_len)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netSendTo(FD(socket), message, length, flags, dest_addr, (net_socklen_t)dest_len);
	else
		ret = lv2NetSendTo(FD(socket), message, length, flags, dest_addr, (net_socklen_t)dest_len);
	return netErrno(ret);
}

ssize_t recv(int s, void *buf, size_t len, int flags)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netRecv(FD(s),buf,len,flags);
	else
		return recvfrom(s, buf, len, flags, NULL, NULL);
	return netErrno(ret);
}

ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr* from, socklen_t* fromlen)
{
	s32 ret;
	net_socklen_t socklen;
	net_socklen_t* socklenp = (from && fromlen) ? &socklen : NULL;
	if (LIBNET_INITIALIZED)
		ret = netRecvFrom(FD(s), buf, len, flags, from, socklenp);
	else
		ret = lv2NetRecvFrom(FD(s), buf, len, flags, from, socklenp);
	
	if (ret < 0)
		return netErrno(ret);

	if (socklenp)
		*fromlen = socklen;

	return ret;
}

int shutdown(int socket, int how)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netShutdown(FD(socket), how);
	else
		ret = lv2NetShutdown(FD(socket), how);
	return netErrno(ret);
}

int closesocket(int socket)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netClose(FD(socket));
	else
		ret = lv2NetClose(FD(socket));
	return netErrno(ret);
}

int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* errorfds, struct timeval* timeout)
{
	net_fd_set* net_readfds = NULL;
	net_fd_set* net_writefds = NULL;
	net_fd_set* net_errorfds = NULL;

	size_t fdsize = sizeof(fd_set) * nfds;

#define COPY_NFDS(dest, src, num) { \
	for (size_t i = 0; i < num; i++) { \
		for (size_t j = 0; j < (sizeof(src[i].fds_bits) / sizeof(src[i].fds_bits[0])); j++) \
			dest[i].fds_bits[j] = src[i].fds_bits[j]; \
	} \
}

	if (readfds) {
		net_readfds = (net_fd_set*)malloc(fdsize);
		COPY_NFDS(net_readfds, readfds, nfds);
	}
	if (writefds) {
		net_writefds = (net_fd_set*)malloc(fdsize);
		COPY_NFDS(net_writefds, writefds, nfds);
	}
	if (errorfds) {
		net_errorfds = (net_fd_set*)malloc(fdsize);
		COPY_NFDS(net_errorfds, errorfds, nfds);
	}

	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netSelect(nfds, net_readfds, net_writefds, net_errorfds, timeout);
	else
		ret = lv2NetSelect(nfds, net_readfds, net_writefds, net_errorfds, timeout);

	if (net_readfds) {
		if (ret >= 0)
			COPY_NFDS(readfds, net_readfds, nfds);
		free(net_readfds);
	}
	if (net_writefds) {
		if (ret >= 0)
			COPY_NFDS(writefds, net_writefds, nfds);
		free(net_writefds);
	}
	if (net_errorfds) {
		if (ret >= 0)
			COPY_NFDS(errorfds, net_errorfds, nfds);
		free(net_errorfds);
	}

	return netErrno(ret);
}

int getsockname(int socket, struct sockaddr* address, socklen_t* address_len)
{
	s32 ret;
	net_socklen_t len;
	net_socklen_t* lenp = (address && address_len) ? &len : NULL;
	if (LIBNET_INITIALIZED)
		ret = netGetSockName(FD(socket), address, lenp);
	else
		ret = lv2NetGetSockName(FD(socket), address, lenp);

	if (ret < 0)
		return netErrno(ret);

	if (lenp)
		*address_len = len;

	return ret;
}

int getpeername(int socket, struct sockaddr* address, socklen_t* address_len)
{
	s32 ret;
	net_socklen_t len;
	net_socklen_t* lenp = (address && address_len) ? &len : NULL;
	if (LIBNET_INITIALIZED)
		ret = netGetPeerName(FD(socket), address, lenp);
	else
		ret = lv2NetGetPeerName(FD(socket), address, lenp);

	if (ret < 0)
		return netErrno(ret);

	if (lenp)
		*address_len = len;

	return ret;
}


