//
// Created by rolando on 5/14/17.
//

#ifndef DRC_SIM_C_VIDEO_WII_U_H
#define DRC_SIM_C_VIDEO_WII_U_H
#include "../../Packet.h"

typedef struct {
    unsigned magic;
    unsigned packet_type;
    unsigned seq_id;
    bool init;
    bool frame_begin;
    bool chunk_end;
    bool frame_end;
    bool has_timestamp;
    unsigned payload_size;
    unsigned int timestamp;
    unsigned char extended_header[8]; // Extended header
} VideoPacketHeaderWiiU;

class VideoPacketWiiU : Packet {

public:
    VideoPacketWiiU(unsigned char *packet, size_t packet_size);

    VideoPacketHeaderWiiU header;
    unsigned char* payload;

private:
    void print_debug(unsigned char *packet, size_t packet_size);
};


#endif //DRC_SIM_C_VIDEO_WII_U_H
