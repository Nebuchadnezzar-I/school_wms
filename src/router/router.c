#include "router.h"

#define B_SIZE 1024

void* router(void* a) {
    char buffer[B_SIZE];

    RouterArg arg = *(RouterArg*)a;
    Arena* arena = arena_new(4096);
    if (arena == NULL) {
        perror("Arena wasnt created");
        return NULL;
    }

    char body[128];
    int blen = snprintf(body, sizeof(body),
                        "<html>hello, world from: %u</html>\r\n", arg.index);
    char hdr[256];
    int hlen = snprintf(hdr, sizeof(hdr),
                        "HTTP/1.1 200 OK\r\n"
                        "Server: webserver-c\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: %d\r\n"
                        "Connection: close\r\n"
                        "\r\n", blen);

    char resp[512];
    int rlen = 0;
    memcpy(resp + rlen, hdr, (size_t)hlen); rlen += hlen;
    memcpy(resp + rlen, body, (size_t)blen); rlen += blen;

    for (;;) {
        int newsockfd = accept(arg.sockfd, (struct sockaddr *)&arg.host_addr,
                               (socklen_t *)&arg.host_addrlen);
        if (newsockfd < 0) {
            perror("webserver (accept)");
            continue;
        }

        int sockn = getsockname(newsockfd, (struct sockaddr *)&arg.client_addr,
                                (socklen_t *)&arg.client_addrlen);
        if (sockn < 0) {
            perror("webserver (getsockname)");
            continue;
        }

        int valread = read(newsockfd, buffer, B_SIZE);
        if (valread < 0) {
            perror("webserver (read)");
            continue;
        }

        char method[B_SIZE], uri[B_SIZE], version[B_SIZE];
        // sscanf(buffer, "%s %s %s", method, uri, version);
        // printf("[%s:%u] %s %s %s\n", inet_ntoa(arg.client_addr.sin_addr),
        //        ntohs(arg.client_addr.sin_port), method, version, uri);

        int valwrite = write(newsockfd, resp, strlen(resp));
        if (valwrite < 0) {
            perror("webserver (write)");
            continue;
        }

        close(newsockfd);
    }

    printf("Thread: %d, Socket: %d\n", arg.index, arg.sockfd);

    return NULL;
}
