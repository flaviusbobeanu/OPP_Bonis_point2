#pragma once
#include <fstream>
#include <iostream>
#include "aux_functions.h"
#include "code.h"
#include "defines.h"
#include "huffman.h"
#include "node.h"
#include "writebit.h"
void Huffman_decoding(const std::string& inFile,std::ostream& out);

