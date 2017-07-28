#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	printf("%lu\n", sizeof(struct sockaddr_in));
	printf("%lu\n", sizeof(struct sockaddr_in6));
}
