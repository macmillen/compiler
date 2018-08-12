#pragma once
#include <cstdint>

namespace puck {
    uint32_t getUInt32BigEndian(uint8_t const* data);

    void storeUInt32BigEndian(uint8_t* dst, uint32_t value);

    int32_t getInt32BigEndian(uint8_t const* data);

    void storeInt32BigEndian(uint8_t* dst, int32_t value);

    uint16_t getUInt16BigEndian(uint8_t const* data);
}
