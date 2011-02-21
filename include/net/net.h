#pragma once

#include <psl1ght/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdlib.h>

#define net_errno *netErrnoLoc()
#define net_h_errno *netHErrnoLoc();

typedef u32 net_socklen_t;

typedef struct
{
	u32 memory;
	s32 memory_size;
	s32 flags;
} netInitialization;

typedef struct
{
	s32 s;
	s32 proto;
	s32 recv_queue_len;
	s32 send_queue_len;
	struct in_addr local_adr;
	s32 local_port;
	struct in_addr remote_adr;
	s32 remote_port;
	s32 state;
} netSocketInfo;

struct net_iovec
{
	u32			padding1;
	lv2_void	iov_base;
	u32			padding2;
	lv2_size_t	iov_len;
};

struct net_msghdr
{
	u32				padding1;
	lv2_void		msg_name;
	net_socklen_t	msg_namelen;
	u32				padding2;
	u32				padding3;
	lv2_void		msg_iov;
	s32				msg_iovlen;
	u32				padding4;
	u32				padding5;
	lv2_void		msg_control;
	net_socklen_t	msg_controllen;
	s32				msg_flags;
};

struct net_hostent {
	lv2_void h_name;
	lv2_void h_aliases;
	s32 h_addrtype;
	s32 h_length;
	lv2_void h_addr_list;
};

#define	NET_FD_SETSIZE	1024
//#define NBBY			8
#define	NET_NFDBITS		(sizeof(net_fd_mask) * NBBY)
typedef	s32 net_fd_mask;
typedef	struct {
	net_fd_mask	fds_bits[howmany(NET_FD_SETSIZE, NET_NFDBITS)];
} net_fd_set;

#define	NET_EPERM			1
#define	NET_ENOENT			2
#define	NET_ESRCH			3
#define	NET_EINTR			4
#define	NET_EIO				5
#define	NET_ENXIO			6
#define	NET_E2BIG			7
#define	NET_ENOEXEC			8
#define	NET_EBADF			9
#define	NET_ECHILD			10
#define	NET_EDEADLK			11
#define	NET_ENOMEM			12
#define	NET_EACCES			13
#define	NET_EFAULT			14
#define	NET_ENOTBLK			15
#define	NET_EBUSY			16
#define	NET_EEXIST			17
#define	NET_EXDEV			18
#define	NET_ENODEV			19
#define	NET_ENOTDIR			20
#define	NET_EISDIR			21
#define	NET_EINVAL			22
#define	NET_ENFILE			23
#define	NET_EMFILE			24
#define	NET_ENOTTY			25
#define	NET_ETXTBSY			26
#define	NET_EFBIG			27
#define	NET_ENOSPC			28
#define	NET_ESPIPE			29
#define	NET_EROFS			30
#define	NET_EMLINK			31
#define	NET_EPIPE			32
#define	NET_EDOM			33
#define	NET_ERANGE			34
#define	NET_EAGAIN			35
#define	NET_EWOULDBLOCK		NET_EAGAIN
#define	NET_EINPROGRESS		36
#define	NET_EALREADY		37
#define	NET_ENOTSOCK		38
#define	NET_EDESTADDRREQ	39
#define	NET_EMSGSIZE		40
#define	NET_EPROTOTYPE		41
#define	NET_ENOPROTOOPT		42
#define	NET_EPROTONOSUPPORT	43
#define	NET_ESOCKTNOSUPPORT	44
#define	NET_EOPNOTSUPP		45
#define	NET_EPFNOSUPPORT	46
#define	NET_EAFNOSUPPORT	47
#define	NET_EADDRINUSE		48
#define	NET_EADDRNOTAVAIL	49
#define	NET_ENETDOWN		50
#define	NET_ENETUNREACH		51
#define	NET_ENETRESET		52
#define	NET_ECONNABORTED	53
#define	NET_ECONNRESET		54
#define	NET_ENOBUFS			55
#define	NET_EISCONN			56
#define	NET_ENOTCONN		57
#define	NET_ESHUTDOWN		58
#define	NET_ETOOMANYREFS	59
#define	NET_ETIMEDOUT		60
#define	NET_ECONNREFUSED	61
#define	NET_ELOOP			62
#define	NET_ENAMETOOLONG	63
#define	NET_EHOSTDOWN		64
#define	NET_EHOSTUNREACH	65
#define	NET_ENOTEMPTY		66
#define	NET_EPROCLIM		67
#define	NET_EUSERS			68
#define	NET_EDQUOT			69
#define	NET_ESTALE			70
#define	NET_EREMOTE			71
#define	NET_EBADRPC			72
#define	NET_ERPCMISMATCH	73
#define	NET_EPROGUNAVAIL	74
#define	NET_EPROGMISMATCH	75
#define	NET_EPROCUNAVAIL	76
#define	NET_ENOLCK			77
#define	NET_ENOSYS			78
#define	NET_EFTYPE			79
#define	NET_EAUTH			80
#define	NET_ENEEDAUTH		81
#define	NET_EIDRM			82
#define	NET_ENOMSG			83
#define	NET_EOVERFLOW		84
#define	NET_EILSEQ			85
#define	NET_ENOTSUP			86
#define	NET_ECANCELED		87
#define	NET_EBADMSG			88
#define	NET_ENODATA			89
#define	NET_ENOSR			90
#define	NET_ENOSTR			91
#define	NET_ETIME			92
#define	NET_ELAST			92

EXTERN_BEGIN

s32 netInitialize();
s32 netDeinitialize();

s32* netErrnoLoc(void);
s32* netHErrnoLoc(void);

s32 netFinalizeNetwork();
#define netInitializeNetwork netInitialize
s32 netGetSockInfo(s32 socket, netSocketInfo* p, s32 n);
s32 netInitializeNetworkEx(netInitialization* param);
s32 netShowIfConfig();
s32 netShowNameserver();
s32 netShowRoute();

int netAccept(int socket, const struct sockaddr* address, net_socklen_t* address_len);
int netBind(int socket, const struct sockaddr* address, net_socklen_t address_len);
int netConnect(int socket, const struct sockaddr* address, net_socklen_t address_len);
int netGetPeerName(int socket, struct sockaddr* address, net_socklen_t* address_len);
int netGetSockName(int socket, struct sockaddr* address, net_socklen_t* address_len);
int netGetSockOpt(int socket, int level, int option_name, void* option_value, socklen_t* option_len);
int netListen(int socket, int backlog);
ssize_t netRecv(int socket, void* buffer, size_t length, int flags);
ssize_t netRecvFrom(int socket, void* buffer, size_t length, int flags, struct sockaddr* address, net_socklen_t* address_len);
ssize_t netRecvMsg(int socket, struct net_msghdr* message, int flags);
ssize_t netSend(int socket, const void* message, size_t length, int flags);
ssize_t netSendTo(int socket, const void* message, size_t length, int flags, const struct sockaddr* dest_addr, net_socklen_t dest_len);
ssize_t netSendMsg(int socket, const struct net_msghdr* message, int flags);
int netSetSockOpt(int socket, int level, int option_name, const void* option_value, socklen_t option_len);
int netShutdown(int socket, int how);
int netSelect(int nfds, fd_set* readfds, fd_set* writefds, fd_set* errorfds, struct timeval_32* timeout);
int netSocket(int domain, int type, int protocol);
int netSocketPair(int domain, int type, int protocol, int socket_vector[2]);
s32 netClose(int socket);
s32 netGetSockInfo(s32 socket, netSocketInfo* p, s32 n);
s32 netPoll(struct pollfd* fds, nfds_t nfds, int timeout);

struct net_hostent* netGetHostByAddr(const char* addr, net_socklen_t len, int type);
struct net_hostent* netGetHostByName(const char* name);

EXTERN_END
