#pragma once

#include <stdint.h>
#include <netinet/in.h>

#define U8  uint8_t
#define U32 uint32_t
#define U64 uint64_t

typedef struct {
    U8  index;
    int sockfd;
    int host_addrlen;
    int client_addrlen;
    struct sockaddr_in host_addr;
    struct sockaddr_in client_addr;
} RouterArg;
