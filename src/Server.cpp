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

//needed for mkv
const uint8_t avcconfig[] = {
  // sps
  0x00, 0x00, 0x00, 0x01, 0x67, 0x64, 0x00, 0x20, 0xac, 0x2b, 0x40, 0x6c, 0x1e, 0xf3, 0x68,
  // pps
  0x00, 0x00, 0x00, 0x01, 0x68, 0xee, 0x06, 0x0c, 0xe8
};

void Server::run() {
  AVOutputFormat* of = av_guess_format("matroska", NULL, NULL);
  if (!of) abort(); //todo real error handling

  avf = avformat_alloc_context();
  if (!avf) abort();

  avf->oformat = of;

  AVStream* vst = avformat_new_stream(avf, NULL);
  if (!vst) abort();

  AVCodecParameters* vstcp = vst->codecpar;
  vstcp->codec_id = AV_CODEC_ID_H264;
  vstcp->codec_type = AVMEDIA_TYPE_VIDEO;
  vstcp->width = 854;
  vstcp->height = 480;

  const size_t exdatasize = sizeof(avcconfig) + AV_INPUT_BUFFER_PADDING_SIZE;
  vstcp->extradata = (uint8_t*)av_malloc(exdatasize);
  memset(vstcp->extradata, 0, exdatasize);
  memcpy(vstcp->extradata, avcconfig, sizeof(avcconfig));
  vstcp->extradata_size = sizeof(avcconfig);

  AVStream* ast = avformat_new_stream(avf, NULL);
  if (!ast) abort();

  AVCodecParameters* astcp = ast->codecpar;
  astcp->codec_id = AV_CODEC_ID_PCM_S16LE;
  astcp->codec_type = AVMEDIA_TYPE_AUDIO;
  astcp->channels = 2;
  astcp->sample_rate = 48000;

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

void Server::broadcast_audio(AVPacket* pkt, AVRational time_base) {
  pkt->stream_index = 1;
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

void Server::broadcast_command(uint16_t command_id) {

}

void Server::broadcast_media(unsigned char *data, size_t size, const int type) {
  //write(fifo, data, size);
}

void Server::broadcast_command(unsigned char *packet, size_t packet_size) {

}
