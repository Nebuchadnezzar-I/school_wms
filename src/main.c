#include "main.h"

int main() {
    pthread_t threads[THREAD_COUNT];
    RouterArg args[THREAD_COUNT];

    // Networking
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("webserver (socket)");
        return EXIT_FAILURE;
    }

    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);

    if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
        perror("webserver (bind)");
        return EXIT_FAILURE;
    }

    if (listen(sockfd, SOMAXCONN) != 0) {
        perror("webserver (listen)");
        return EXIT_FAILURE;
    }

    for (int idx = 0; idx < THREAD_COUNT; idx++) {
        args[idx].index = idx;
        args[idx].sockfd = sockfd;
        args[idx].host_addr = host_addr;
        args[idx].host_addrlen = host_addrlen;
        args[idx].client_addr = client_addr;
        args[idx].client_addrlen = client_addrlen;
        pthread_create(&threads[idx], NULL, router, &args[idx]);
    }

    for (int idx = 0; idx < THREAD_COUNT; idx++) {
        pthread_join(threads[idx], NULL);
    }

    return EXIT_SUCCESS;
}
