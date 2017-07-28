#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "def.h"


int make_socket()
{
	return socket(AF_INET, SOCK_DGRAM, 0);
}

struct sockaddr_in make_addr(const char * dst_ip, unsigned short dst_port)
{
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(dst_port);
	inet_aton(dst_ip, &addr.sin_addr);

	return addr;
}

void print_percentage(int try, int now)
{
	int base = TRY / 100;
	if ((now % base) == 0)
		printf("%d\n", now*100/TRY);
}

int main()
{
	FILE * fp = fopen("./tmpfs_space/hoge", "w");

	unsigned char buf[65536];
	int sd = make_socket();

	struct sockaddr_in own = make_addr("127.0.0.1", 50001);
	bind(sd, (struct sockaddr *)&own, sizeof(own));

	ssize_t recv_size;
	int i = 0;
	while (1) {
		recv_size = recv(sd, buf, 65536, 0);
		fwrite(fp, recv_size, 1, fp);
		i++;

		print_percentage(TRY, i);

		if (i == TRY)
			break;
	}
}
