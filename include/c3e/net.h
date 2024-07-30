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

/**
 * @file net.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief Network communication utilities for the C3E library.
 *
 * This file provides functionalities for network communication within the C3E library. It includes
 * definitions and functions for socket management, as well as sending and receiving data structures
 * such as vectors, matrices, and tensors over a network.
 */
#ifndef C3E_NET_H
#define C3E_NET_H

#include <c3e/commons.h>

#include <arpa/inet.h>

/**
 * @struct c3e_socket
 * @brief Represents a network socket for communication.
 *
 * This structure encapsulates the details of a network socket, including:
 * - `hostname`: The hostname or IP address of the server.
 * - `port`: The port number on which the server is listening.
 * - `sockfd`: The file descriptor for the socket.
 * - `server_addr`: The server's address, including the hostname and port number.
 */
typedef struct {
    char* hostname; ///< The hostname or IP address of the server.
    int port;       ///< The port number on which the server is listening.
    int sockfd;     ///< The file descriptor for the socket.
    struct sockaddr_in server_addr; ///< The server's address structure.
} c3e_socket;

/**
 * @brief Initializes a socket with the specified hostname and port.
 *
 * This function sets up a network socket for communication with a server. It configures the socket's
 * address and port, and prepares it for use in sending and receiving data.
 *
 * @param socket A pointer to a `c3e_socket` structure to be initialized.
 * @param hostname The hostname or IP address of the server.
 * @param port The port number on which the server is listening.
 */
void c3e_socket_init(c3e_socket* socket, const char* hostname, int port);

/**
 * @brief Closes the network socket.
 *
 * This function releases the resources associated with the socket and closes the connection.
 *
 * @param socket A pointer to the `c3e_socket` structure to be closed.
 */
void c3e_socket_close(c3e_socket* socket);

/**
 * @brief Sends data through the socket.
 *
 * This function transmits data over the network through the specified socket.
 *
 * @param socket A pointer to the `c3e_socket` structure used for sending data.
 * @param data A pointer to the data to be sent.
 * @param size The size of the data to be sent.
 * @return `true` if the data was successfully sent, `false` otherwise.
 */
bool c3e_socket_send_data(c3e_socket* socket, const void* data, size_t size);

/**
 * @brief Receives data from the socket.
 *
 * This function reads data from the network through the specified socket and stores it in the provided buffer.
 *
 * @param socket A pointer to the `c3e_socket` structure used for receiving data.
 * @param buffer A pointer to the buffer where received data will be stored.
 * @param size The size of the buffer.
 * @return `true` if the data was successfully received, `false` otherwise.
 */
bool c3e_socket_receive_data(c3e_socket* socket, void* buffer, size_t size);

/**
 * @brief Sends a tensor object through the socket.
 *
 * This function serializes and transmits a `c3e_tensor` object over the network.
 *
 * @param socket A pointer to the `c3e_socket` structure used for sending the tensor.
 * @param tensor A pointer to the `c3e_tensor` object to be sent.
 */
void c3e_socket_send_tensor(c3e_socket* socket, c3e_tensor* tensor);

/**
 * @brief Sends a matrix object through the socket.
 *
 * This function serializes and transmits a `c3e_matrix` object over the network.
 *
 * @param socket A pointer to the `c3e_socket` structure used for sending the matrix.
 * @param matrix A pointer to the `c3e_matrix` object to be sent.
 */
void c3e_socket_send_matrix(c3e_socket* socket, c3e_matrix* matrix);

/**
 * @brief Sends a vector object through the socket.
 *
 * This function serializes and transmits a `c3e_vector` object over the network.
 *
 * @param socket A pointer to the `c3e_socket` structure used for sending the vector.
 * @param vector A pointer to the `c3e_vector` object to be sent.
 */
void c3e_socket_send_vector(c3e_socket* socket, c3e_vector* vector);


/**
 * @brief Sends a numerical value over a socket connection.
 *
 * This function sends a `c3e_number` type value through the specified socket. It uses the
 * `c3e_socket_send_data` function to transmit the binary representation of the number.
 *
 * @param socket A pointer to a `c3e_socket` structure representing the socket
 *               connection through which the data will be sent.
 * @param number The numerical value of type `c3e_number` to be sent. This value
 *               is sent as a binary stream, which means the receiving end should
 *               be aware of the data format to correctly interpret it.
 */
void c3e_socket_send_number(c3e_socket* socket, c3e_number number);

/**
 * @brief Receives and deserializes a tensor object from the socket.
 *
 * This function reads and reconstructs a `c3e_tensor` object from the data received through the network.
 *
 * @param socket A pointer to the `c3e_socket` structure used for receiving the tensor.
 * @return A pointer to the deserialized `c3e_tensor` object. NULL if the operation fails.
 */
c3e_tensor* c3e_socket_tensor_read(c3e_socket* socket);

/**
 * @brief Receives and deserializes a matrix object from the socket.
 *
 * This function reads and reconstructs a `c3e_matrix` object from the data received through the network.
 *
 * @param socket A pointer to the `c3e_socket` structure used for receiving the matrix.
 * @return A pointer to the deserialized `c3e_matrix` object. NULL if the operation fails.
 */
c3e_matrix* c3e_socket_matrix_read(c3e_socket* socket);

/**
 * @brief Receives and deserializes a vector object from the socket.
 *
 * This function reads and reconstructs a `c3e_vector` object from the data received through the network.
 *
 * @param socket A pointer to the `c3e_socket` structure used for receiving the vector.
 * @return A pointer to the deserialized `c3e_vector` object. NULL if the operation fails.
 */
c3e_vector* c3e_socket_vector_read(c3e_socket* socket);

/**
 * @brief Receives a numerical value from a socket connection.
 *
 * This function reads a `c3e_number` type value from the specified socket.
 *
 * @param socket A pointer to a `c3e_socket` structure representing the socket
 *               connection from which the data will be received.
 * @return The numerical value of type `c3e_number` that was received from the socket.
 */
c3e_number c3e_socket_number_read(c3e_socket* socket);

#endif /* C3E_NET_H */