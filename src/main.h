#pragma once

#include "arena/arena.h"
#include "router/router.h"

#include <pthread.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT            8080
#define BUFFER_SIZE     4096
#define THREAD_COUNT    12
