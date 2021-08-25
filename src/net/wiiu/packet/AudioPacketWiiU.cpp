//
// Created by rolando on 5/26/17.
//

#include <assert.h>
#include <netinet/in.h>
#include "AudioPacketWiiU.h"
#include "../../../util/BitUtil.h"

AudioPacketWiiU::AudioPacketWiiU(unsigned char *packet, size_t packet_size) : Packet(packet, packet_size) {
    header.format = packet[0] >> 5;

    header.mono    = !!(packet[0] & 0x10);
    header.vibrate = !!(packet[0] & 0x08);
    header.type    = !!(packet[0] & 0x04);

    header.seq_id = ((packet[0] & 3) << 8) | packet[1];

    header.payload_size = (packet[2] << 8) | packet[3];

    header.timestamp = (packet[7] << 24) | (packet[6] << 16) | (packet[5] << 8) | packet[4];

    payload = packet + 8;
    assert(header.payload_size <= packet_size - 8);

    if (header.type == TYPE_VIDEO) {
        header_video_format.timestamp = (payload[0] << 24) | (payload[1] << 16) | (payload[2] << 8) | payload[3];
        header_video_format.video_format = (payload[0xc] << 24) | (payload[0xd] << 16) | (payload[0xe] << 8) | payload[0xf];
    }
}
