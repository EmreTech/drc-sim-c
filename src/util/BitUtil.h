//
// Created by rolando on 5/14/17.
//

#ifndef DRC_SIM_C_BITUTIL_H
#define DRC_SIM_C_BITUTIL_H


class BitUtil {

public:
    static unsigned int reverse(unsigned number, int bits) {
        unsigned reversed = 0;
        for(int i = 0; i < bits; i++)
            reversed |= ((number >> i) & 1) << (bits - 1 - i);
        return reversed;
    }
};


#endif //DRC_SIM_C_BITUTIL_H
