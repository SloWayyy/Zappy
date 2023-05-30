/*
** EPITECH PROJECT, 2023
** server
** File description:
** util.c
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

struct sockaddr *generate_address(int port, char *address)
{
    struct sockaddr_in *addr = malloc(sizeof(struct sockaddr_in));

    if (addr == NULL) {
        return NULL;
    }
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = address == NULL ? INADDR_ANY : inet_addr(address);
    return (struct sockaddr *) addr;
}
