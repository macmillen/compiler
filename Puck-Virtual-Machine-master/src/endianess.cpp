#include "endianess.h"
#include <boost/detail/endian.hpp>

//TODO: There are intrinsics that flip the byte order. We should use them here

uint32_t puck::getUInt32BigEndian(uint8_t const* data) {
    #ifdef BOOST_BIG_ENDIAN
    return *reinterpret_cast<uint32_t*>(data);
    #else
    return
            static_cast<uint32_t>(data[0]) << 24 |
            static_cast<uint32_t>(data[1]) << 16 |
            static_cast<uint32_t>(data[2]) << 8 |
            static_cast<uint32_t>(data[3]);
    #endif
}

void puck::storeUInt32BigEndian(uint8_t* dst, uint32_t value) {
    #ifdef BOOST_BIG_ENDIAN
    *reinterpret_cast<uint32_t*>(dst) = value;
    #else
    const auto data = reinterpret_cast<uint8_t*>(&value);
    dst[0] = static_cast<uint8_t>(data[3]);
    dst[1] = static_cast<uint8_t>(data[2]);
    dst[2] = static_cast<uint8_t>(data[1]);
    dst[3] = static_cast<uint8_t>(data[0]);
    #endif
}

int32_t puck::getInt32BigEndian(uint8_t const* data) {
    #ifdef BOOST_BIG_ENDIAN
    return *reinterpret_cast<uint32_t*>(data);
    #else
    return
            static_cast<int32_t>(data[0]) << 24 |
            static_cast<int32_t>(data[1]) << 16 |
            static_cast<int32_t>(data[2]) << 8 |
            static_cast<int32_t>(data[3]);
    #endif
}

void puck::storeInt32BigEndian(uint8_t* dst, int32_t value) {
    #ifdef BOOST_BIG_ENDIAN
    *reinterpret_cast<int32_t*>(dst) = value;
    #else
    const auto data = reinterpret_cast<uint8_t*>(&value);
    dst[0] = static_cast<uint8_t>(data[3]);
    dst[1] = static_cast<uint8_t>(data[2]);
    dst[2] = static_cast<uint8_t>(data[1]);
    dst[3] = static_cast<uint8_t>(data[0]);
    #endif
}

uint16_t puck::getUInt16BigEndian(uint8_t const* data) {
    #ifdef BOOST_BIG_ENDIAN
    return *reinterpret_cast<uint16_t*>(data);
    #else
    return
            static_cast<uint16_t>(data[0]) << 8 |
            static_cast<uint16_t>(data[1]);
    #endif
}
