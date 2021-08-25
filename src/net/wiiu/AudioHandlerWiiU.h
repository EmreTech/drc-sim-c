//
// Created by rolando on 5/17/17.
//

#ifndef DRC_SIM_C_AUDIOHANDLER_WII_U_H
#define DRC_SIM_C_AUDIOHANDLER_WII_U_H


#include "../PacketHandler.h"

class AudioHandlerWiiU : PacketHandler {
    void update(unsigned char *packet, size_t packet_size, sockaddr_in *from_address,
                unsigned int *address_size) override;

public:
    AudioHandlerWiiU();

    void send_mic_blow();

    unsigned char *rand_audio;

    uint32_t initial_ts;
    uint32_t last_uts;
    int64_t last_ts;
    int64_t ts_wrap_ref;
};


#endif //DRC_SIM_C_AUDIOHANDLER_WII_U_H
