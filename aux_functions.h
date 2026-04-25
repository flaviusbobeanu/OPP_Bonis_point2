#pragma once
#include <fstream>
#include <filesystem>
#include <system_error>

#include "node.h"

void buildHistogram(std::ifstream& in, uint64_t hist[ALPHABET]);
uint16_t countUniqueSymbols(uint64_t hist[ALPHABET]);
void dumpTree(Node* root, std::ofstream& out);
uint64_t getFileSize(const std::string& Filename);
void array_dumptree(std::ifstream& in,uint16_t tree_size,uint8_t tree_dump[]);
