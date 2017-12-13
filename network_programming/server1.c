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
#include <signal.h>

#define SERVER1_PATH "/tmp/server1"
#define MAX_CLIENTS 10

void sig_handler(int sig) {
	if ( sig == SIGINT ) {
		signal(SIGPIPE, sig_handler);
	}
}

int main()
{
	int i = 0;
	int j = 0;
	fd_set rfds;
	int ret = 0;
	struct timeval tv = {0};
	int maxfd = -1;
	int svr = -1;
	struct sockaddr_un sa_un = {0};
	int nc = 0;
	int cln[MAX_CLIENTS] = {0};

	signal(SIGPIPE, sig_handler);

	svr = socket(AF_UNIX, SOCK_STREAM, PF_UNIX);
	if (svr < 0) {
		perror("failed to create socket");
		return -1;
	}

	ret = unlink(SERVER1_PATH);
	if (ret == -1 && errno != ENOENT) {
		perror("failed to remove existing ipc socket");
		return -1;
	}

	sa_un.sun_family = AF_UNIX;
	strcpy(sa_un.sun_path, SERVER1_PATH);
	ret = bind(svr, (struct sockaddr *)&sa_un, sizeof(sa_un));
	if (ret < 0) {
		perror("could not bind ipc socket");
		return -1;
	}

	ret = listen(svr, MAX_CLIENTS);
	if (ret < 0) {
		perror("could not listen on ipc socket");
		return -1;
	}

	while (1) {
		FD_ZERO(&rfds);
		FD_SET(svr, &rfds);
		if (svr > maxfd)
			maxfd = svr;

		for(i=0; i<nc; i++) {
			FD_SET(cln[i], &rfds);
			if(cln[i] > maxfd)
				maxfd = svr;
		}

		tv.tv_sec = 5;
		tv.tv_usec = 0;

		do {
			ret = select(maxfd+1, &rfds, NULL, NULL, &tv);
		} while ((ret == -1) && (errno == EINTR));

		if (ret == -1) {
			perror("select() failed");
			continue;
		}

		for(i=0; i<nc; i++) {
			/* clients are read only so if we get something on select() it
			 * means the client disconnected */
			if (FD_ISSET(cln[i], &rfds)) {
				int oldfd = cln[i];
				close(oldfd);
				for(j=i+1; j<nc; ++j)
					cln[j-1] = cln[j];
				i -= 1;
				nc -= 1;
				fprintf(stdout, "client disconnected (fd %d), %d clients still connected\n", oldfd, nc);
			}
		}

		if (FD_ISSET(svr, &rfds)) {
			int newfd;
			if(nc >= MAX_CLIENTS)
				fprintf(stderr, "too many ipc clients, ignoring\n");
			else {
				newfd = accept(svr, NULL, NULL);
				if (newfd < 0)
					perror("client accept failed");
				else {
					ret = fcntl(newfd, F_SETFL, O_NONBLOCK|O_CLOEXEC);
					if (ret < 0)
						perror("client fcntl failed");
					else {
						cln[nc] = newfd;
						nc += 1;
						fprintf(stdout, "client connected (fd %d), %d clients connected\n", newfd, nc);
					}
				}
			}
		}

		for(i = 0; i < nc; i++) {
			char buf[100] = {0};
			char *p = buf;
			int left = sizeof(buf);

			snprintf(buf, sizeof(buf), "This is server %d", (int)getpid());

			while (left) {
				ret = write(cln[i], p, left);
				if(ret < 0)
					break;
				left -= ret;
				p += ret;
			}
		}

	}

	return 0;
}
