#pragma once
#pragma once
#include <cstdint>

#define BLOCK 4096
#define ALPHABET 256
#define MAGIC 0xDEADEAEF
#define MAX_CODE_SIZE (ALPHABET / 8)
#define MAX_TREE_SIZE (3 * ALPHABET - 1)

struct Header {
    uint32_t signature;
    uint16_t tree_size;
    uint64_t file_size;
};