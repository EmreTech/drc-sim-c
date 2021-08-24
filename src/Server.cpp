//
// Created by rolando on 5/16/17.
//

#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <zconf.h>
#include "Server.h"
#include "util/logging/Logger.h"
#include "data/Constants.h"
#include "Gamepad.h"
#include "net/server/packet/CommandPacketServer.h"
#include <fcntl.h>

using namespace std;

int fifo;

Server::Server() {

}

void Server::run() {
  fifo = open("video", O_RDWR, O_NONBLOCK);
}

void Server::check_socket_time() {

}

void Server::update_sockets() {

}

void Server::print_init() {

}

void Server::init_sockets() {

}

void Server::broadcast_video(uint8_t *frame, size_t size) {
    broadcast_media(frame, size, VIDEO);
}

void Server::handle_packet(int fd, PacketHandler *handler) {

}

void Server::register_client_socket(in_port_t port, in_addr_t addr, const int type) {

}

void Server::remove_client_socket(ClientSocket *client_socket) {

}

void Server::update_socket_time(in_port_t port, in_addr_t addr) {

}

void Server::register_client_socket(int fd, const int type) {

}

void Server::broadcast_audio(unsigned char *data, size_t size) {
    //broadcast_media(data, size, AUDIO);
}

void Server::broadcast_command(uint16_t command_id) {

}

void Server::broadcast_media(unsigned char *data, size_t size, const int type) {
  write(fifo, data, size);
}

void Server::broadcast_command(unsigned char *packet, size_t packet_size) {

}
