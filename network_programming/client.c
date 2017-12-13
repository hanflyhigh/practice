#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <error.h>
#include <sys/un.h>
#include <fcntl.h>

#define SERVER1_PATH "/tmp/server1"
#define MAX_CLIENTS 10

int main()
{
	struct sockaddr_un addr;
	int cli = -1;
	char rcvbuf[100] = {0};
	int rcvLen = 0;
	int ret = 0;

reinit:

	sleep(1);

	cli = socket(PF_LOCAL, SOCK_STREAM, 0);
	if(cli < 0) {
		perror("failed to create socket");
		goto reinit;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = PF_LOCAL;
	strncpy(addr.sun_path, SERVER1_PATH, sizeof(SERVER1_PATH));

	ret = connect(cli, (struct sockaddr*)(&addr), sizeof(addr));
	if(ret < 0) {
		perror("could not connect to " SERVER1_PATH);
		goto reinit;
	}

	while(1) {
		memset(rcvbuf, 0, sizeof(rcvbuf));
		rcvLen = recv(cli, rcvbuf, sizeof(rcvbuf), MSG_WAITALL);
		if(rcvLen <= 0) {
			perror("failed to receive msg");
			goto reinit;
		} else {
			fprintf(stdout, "msg from client %d: %s\n", (int)getpid(), rcvbuf);
		}
	}

	return 0;
}
