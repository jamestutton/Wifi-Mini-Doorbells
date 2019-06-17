/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include <time.h>       /* time_t, time, ctime */

#define PORT "39090"  // the port users will be connecting to
#define BUFSIZE 4096
#define BACKLOG 10	 // how many pending connections queue will hold
FILE* pFile;
FILE* VisitorImg;

void sigchld_handler(int s)
{
	// waitpid() might overwrite errno, so we save and restore it:
	int saved_errno = errno;

	while(waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	char buffer[BUFSIZE];
	char imgBuffer[BUFSIZE];
	size_t n;
	//size_t size2;
	size_t imgbufsize;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (p == NULL)  {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	printf("server: waiting for connections...\n");

	while(1) {  // main accept() loop
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *)&their_addr),
			s, sizeof s);


			char imgfilename[40];
			struct tm *timenow;

			time_t now = time(NULL);
			timenow = gmtime(&now);

			strftime(imgfilename, sizeof(imgfilename), "/tmp/vistor_%Y%m%dT%H%M%S.jpg", timenow);

			pFile = fopen("/tmp/stream.raw","wb");
			VisitorImg = fopen(imgfilename,"wb");

			fprintf(stdout, "New Visitor at Door!!!!\n");
			//WE NEED TO DROP THE FIRST 38 BITS of data
			int ImageOffset = 37;

memset(buffer,0,BUFSIZE);
         while ((n = recv(new_fd,buffer,BUFSIZE-1,0)) > 0){
					 /*
            //buffer[n] = '\0';
            //printf("%s", buffer);
						printf("Recieved %zu bytes of data to file\n",n);
						size2 = n;
						if (pFile ){
					 		 fwrite(buffer,1,size2,pFile);
							 printf("Writing %zu bytes of data to file\n",size2);
					  }    else {
							   printf("Can't open file");
						}
						*/
						if (VisitorImg) {
							 imgbufsize = n -  ImageOffset;
							 memcpy ( &imgBuffer[0], &buffer[ImageOffset], imgbufsize * sizeof buffer[0]);

					 		 fwrite(imgBuffer,1,imgbufsize,VisitorImg);
							 //Only need to drap data from first packet
							 ImageOffset = 0;
							 printf("Writing %zu bytes of data to %s\n",imgbufsize,imgfilename);
					  }    else {
							   printf("Can't open file");
						}
						//Clear the buffer not sure if it needed
						memset(buffer,0,BUFSIZE);
         }



		if (!fork()) { // this is the child process
			close(sockfd); // child doesn't need the listener
			if (send(new_fd, "", 0, 0) == -1)
				perror("send");
			close(new_fd);
			exit(0);
		}

		close(new_fd);  // parent doesn't need this
		fclose(VisitorImg);
		printf("Visitor Recorded as %s\n\n",imgfilename);

	}

	return 0;
}
