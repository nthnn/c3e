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

#include <c3e/net.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

void c3e_socket_init(c3e_socket* wsocket, const char* hostname, int port) {
    assert(wsocket != NULL);
    assert(hostname != NULL);

    wsocket->hostname = strdup(hostname);
    wsocket->port = port;
    wsocket->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    assert(wsocket->sockfd >= 0);

    wsocket->server_addr.sin_family = AF_INET;
    wsocket->server_addr.sin_port = htons(port);

    assert(inet_pton(AF_INET, hostname, &wsocket->server_addr.sin_addr) > 0);
    assert(connect(wsocket->sockfd, (struct sockaddr*) &wsocket->server_addr, sizeof(wsocket->server_addr)) >= 0);
}

void c3e_socket_close(c3e_socket* socket) {
    if(socket != NULL) {
        close(socket->sockfd);
        free(socket->hostname);
    }
}

bool c3e_socket_send_data(c3e_socket* socket, const void* data, size_t size) {
    assert(socket != NULL);
    assert(data != NULL);
    
    return send(socket->sockfd, data, size, 0) == size;
}

bool c3e_socket_receive_data(c3e_socket* socket, void* buffer, size_t size) {
    assert(socket != NULL);
    assert(buffer != NULL);

    return recv(socket->sockfd, buffer, size, 0) == size;
}

void c3e_socket_send_tensor(c3e_socket* socket, c3e_tensor* tensor) {
    assert(tensor != NULL);

    c3e_socket_send_data(socket, &tensor->dimensions, sizeof(tensor->dimensions));
    c3e_socket_send_data(socket, &tensor->dimension_size, sizeof(tensor->dimension_size));

    for(uint32_t i = 0; i < tensor->dimensions; ++i)
        c3e_socket_send_matrix(socket, tensor->matrices[i]);
    c3e_socket_send_vector(socket, tensor->data);
}

void c3e_socket_send_matrix(c3e_socket* socket, c3e_matrix* matrix) {
    assert(matrix != NULL);

    c3e_socket_send_data(socket, &matrix->rows, sizeof(matrix->rows));
    c3e_socket_send_data(socket, &matrix->cols, sizeof(matrix->cols));
    c3e_socket_send_data(socket, matrix->data, matrix->rows * matrix->cols * sizeof(c3e_number));
}

void c3e_socket_send_vector(c3e_socket* socket, c3e_vector* vector) {
    assert(vector != NULL);

    c3e_socket_send_data(socket, &vector->size, sizeof(vector->size));
    c3e_socket_send_data(socket, vector->data, vector->size * sizeof(c3e_number));
}

c3e_tensor* c3e_socket_tensor_read(c3e_socket* socket) {
    c3e_tensor* tensor = (c3e_tensor*) malloc(sizeof(c3e_tensor));

    c3e_socket_receive_data(socket, &tensor->dimensions, sizeof(tensor->dimensions));
    c3e_socket_receive_data(socket, &tensor->dimension_size, sizeof(tensor->dimension_size));
    tensor->matrices = (c3e_matrix**) malloc(tensor->dimensions * sizeof(c3e_matrix*));

    for(uint32_t i = 0; i < tensor->dimensions; ++i)
        tensor->matrices[i] = c3e_socket_matrix_read(socket);
    tensor->data = c3e_socket_vector_read(socket);

    return tensor;
}

c3e_matrix* c3e_socket_matrix_read(c3e_socket* socket) {
    c3e_matrix* matrix = (c3e_matrix*) malloc(sizeof(c3e_matrix));

    c3e_socket_receive_data(socket, &matrix->rows, sizeof(matrix->rows));
    c3e_socket_receive_data(socket, &matrix->cols, sizeof(matrix->cols));

    matrix->data = (c3e_number*) malloc(matrix->rows * matrix->cols * sizeof(c3e_number));
    c3e_socket_receive_data(socket, matrix->data, matrix->rows * matrix->cols * sizeof(c3e_number));

    return matrix;
}

c3e_vector* c3e_socket_vector_read(c3e_socket* socket) {
    c3e_vector* vector = (c3e_vector*)malloc(sizeof(c3e_vector));
    c3e_socket_receive_data(socket, &vector->size, sizeof(vector->size));

    vector->data = (c3e_number*)malloc(vector->size * sizeof(c3e_number));
    c3e_socket_receive_data(socket, vector->data, vector->size * sizeof(c3e_number));

    return vector;
}