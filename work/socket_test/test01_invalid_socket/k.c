#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

struct ErrnoMsg {
	int no;
	char * msg;
} errno_msg[] = {
  {EACCES,        "EACCES"},
  {EAGAIN,        "EAGAIN"},
  {EWOULDBLOCK,   "EWOULDBLOCK"},
  {EAGAIN,        "EAGAIN"},
  {EBADF,         "EBADF"},
  {ECONNRESET,    "ECONNRESET"},
  {EDESTADDRREQ,  "EDESTADDRREQ"},
  {EFAULT  ,      "EFAULT  "},
  {EINTR,         "EINTR"},
  {EINVAL,        "EINVAL"},
  {EISCONN,       "EISCONN"},
  {EMSGSIZE,      "EMSGSIZE"},
  {ENOBUFS,       "ENOBUFS"},
  {ENOMEM  ,      "ENOMEM  "},
  {ENOTCONN,      "ENOTCONN"},
  {ENOTSOCK,      "ENOTSOCK"},
  {EOPNOTSUPP,    "EOPNOTSUPP"},
  {EPIPE,         "EPIPE"},
};

struct sockaddr_in make_addr(const char * dst_ip, unsigned short dst_port)
{
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(dst_port);
	inet_aton(dst_ip, &addr.sin_addr);

	return addr;
}

int make_socket()
{
	socket()
}

int main()
{
	unsigned char buf[2048];

	// EINVAL
	struct sockaddr_in dst_addr = make_addr("127.0.0.1", 13941);
	sendto(13878, buf, 1, 0, (struct sockaddr *)&dst_addr, sizeof(dst_addr));
	printf("Error: %s(%s)\n", errno_msg[errno].msg, strerror(errno));

	// EACCES
	struct sockaddr_in dst_addr = make_addr("255.255.255.255", 13941);
	sendto(13878, buf, 1, 0, (struct sockaddr *)&dst_addr, sizeof(dst_addr));
	printf("Error: %s(%s)\n", errno_msg[errno].msg, strerror(errno));
}

