//
// Created by rolando on 5/14/17.
//

#include <iostream>
#include <sstream>
#include <assert.h>
#include <cstring>
#include "VideoPacketWiiU.h"
#include "../../../util/logging/Logger.h"

using namespace std;

VideoPacketWiiU::VideoPacketWiiU(unsigned char *packet, size_t packet_size) : Packet(packet, packet_size) {
    // Parse
    //messy but straightforward
    header.magic       = packet[0] >> 4;
    header.packet_type = (packet[0] >> 2) & 3;
    header.seq_id      = ((packet[0] & 3) << 8) | (packet[1]);

    header.init          = !!(packet[2] & 0x80);
    header.frame_begin   = !!(packet[2] & 0x40);
    header.chunk_end     = !!(packet[2] & 0x20);
    header.frame_end     = !!(packet[2] & 0x10);
    header.has_timestamp = !!(packet[2] & 0x08);

    header.payload_size = ((packet[2] & 7) << 8) | packet[3];
    header.timestamp = (packet[4] << 24) | (packet[5] << 16) | (packet[6] << 8) | packet[7];
    memcpy(header.extended_header, packet + 8, sizeof(header.extended_header));

    payload = packet + 16;

    if (Logger::get_level() >= Logger::VERBOSE) {
        print_debug(packet, packet_size);
    }
    assert(header.payload_size <= packet_size - 16);
}

void VideoPacketWiiU::print_debug(unsigned char *packet, size_t packet_size) {
    stringstream hex_string;
    hex_string << hex;
    for (int byte = 0; byte < packet_size; byte++)
        hex_string << (int) packet[byte] << " ";
    hex_string << endl << dec;
    hex_string << "  magic = " << header.magic << endl;
    hex_string << "  packet_type = " << header.packet_type << endl;
    hex_string << "  seq_id = " << header.seq_id << endl;
    hex_string << "  init = " << header.init << endl;
    hex_string << "  frame_begin = " << header.frame_begin << endl;
    hex_string << "  chunk_end = " << header.chunk_end << endl;
    hex_string << "  frame_end = " << header.frame_end << endl;
    hex_string << "  has_timestamp = " << header.has_timestamp << endl;
    hex_string << "  payload_size = " << header.payload_size << endl;
    hex_string << "  timestamp = " << header.timestamp;
    Logger::verbose(Logger::DRC, "Video packet:\n  %s", hex_string.str().c_str());
}
