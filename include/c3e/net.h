/*
 * Copyright 2024 Nathanne Isip
 * 
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 */

#ifndef C3E_NET_H
#define C3E_NET_H

#ifndef __linux__
#   error "Incompatible target architecture using <c3e/net.h>"
#endif

#include <arpa/inet.h>
#include <c3e/commons.h>

typedef struct {
    char* hostname;
    int port;
    int sockfd;
    struct sockaddr_in server_addr;
} c3e_socket;

void c3e_socket_init(c3e_socket* socket, const char* hostname, int port);
void c3e_socket_close(c3e_socket* socket);

bool c3e_socket_send_data(c3e_socket* socket, const void* data, size_t size);
bool c3e_socket_receive_data(c3e_socket* socket, void* buffer, size_t size);

void c3e_socket_send_tensor(c3e_socket* socket, c3e_tensor* tensor);
void c3e_socket_send_matrix(c3e_socket* socket, c3e_matrix* matrix);
void c3e_socket_send_vector(c3e_socket* socket, c3e_vector* vector);

c3e_tensor* c3e_socket_tensor_read(c3e_socket* socket);
c3e_matrix* c3e_socket_matrix_read(c3e_socket* socket);
c3e_vector* c3e_socket_vector_read(c3e_socket* socket);

#endif