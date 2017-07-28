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

#define SIZE 1480

int main()
{
	FILE * fp = fopen("hoge", "w");

	unsigned char buf[SIZE];
	int i;
	int sd = make_socket();

	struct sockaddr_in own = make_addr("127.0.0.1", 50000);
	struct sockaddr_in dst = make_addr("127.0.0.1", 50001);
	bind(sd, (struct sockaddr *)&own, sizeof(own));
	connect(sd, (struct sockaddr *)&dst, sizeof(dst));

	for (i = 0; i < SIZE; i++) {
		buf[i] = 'a';
	}

	for (i = 0; i < TRY; i++) {
		send(sd, buf, SIZE, 0);
	}
	printf("finish\n");
	int c = getchar();
}

