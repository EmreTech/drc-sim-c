//
// Created by rolando on 5/16/17.
//

#include <cstring>
#include <zconf.h>
#include "Server.h"
#include "util/logging/Logger.h"
#include "data/Constants.h"
#include "Gamepad.h"
#include "net/server/packet/CommandPacketServer.h"
#include <fcntl.h>

extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
}

using namespace std;

AVFormatContext* avf;

Server::Server() {

}

void Server::run() {
  AVOutputFormat* of = av_guess_format("mpegts", NULL, NULL);
  if (!of) abort(); //todo real error handling

  avf = avformat_alloc_context();
  if (!avf) abort();

  avf->oformat = of;

  AVStream* st = avformat_new_stream(avf, NULL);
  if (!st) abort();

  AVCodecParameters* stcp = st->codecpar;
  stcp->codec_id = AV_CODEC_ID_H264;
  stcp->codec_type = AVMEDIA_TYPE_VIDEO;
  stcp->width = 854;
  stcp->height = 480;

  int ret = avio_open(&avf->pb, "video", AVIO_FLAG_WRITE);
  if (ret < 0) abort();

  ret = avformat_write_header(avf, NULL);
  if (ret < 0) abort();
  printf("a %d\n", ret);
}

void Server::cleanup() {
  av_write_trailer(avf);
  avio_close(avf->pb);

  avformat_free_context(avf);
}

void Server::check_socket_time() {

}

void Server::update_sockets() {

}

void Server::print_init() {

}

void Server::init_sockets() {

}

void Server::broadcast_video(AVPacket* pkt, AVRational time_base) {
  pkt->stream_index = 0;
  av_packet_rescale_ts(pkt, time_base, avf->streams[pkt->stream_index]->time_base);
  av_interleaved_write_frame(avf, pkt);
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
  //write(fifo, data, size);
}

void Server::broadcast_command(unsigned char *packet, size_t packet_size) {

}
