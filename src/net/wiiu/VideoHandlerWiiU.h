//
// Created by rolando on 5/8/17.
//

#ifndef DRC_SIM_C_VIDEOHANDLER_WII_U_H
#define DRC_SIM_C_VIDEOHANDLER_WII_U_H


#include "../PacketHandler.h"
#include "packet/VideoPacketWiiU.h"

class VideoHandlerWiiU : PacketHandler {

public:
    VideoHandlerWiiU();

    bool is_idr_packet(const VideoPacketHeaderWiiU& header);

private:
    bool is_streaming;
    uint32_t frame_index;

    int h264_nal_encapsulate(bool is_idr, uint8_t *frame, size_t frame_size, uint8_t *nals);

    void update(unsigned char *packet, size_t packet_size, sockaddr_in *from_address,
                unsigned int *address_size) override;

    uint8_t *frame;
    int64_t frame_decode_num;
};


#endif //DRC_SIM_C_VIDEOHANDLER_WII_U_H
