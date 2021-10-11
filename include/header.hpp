// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <string>

using nlohmann::json;
using std::cout;
using std::string;
using std::endl;
using std::to_string;


bool try_file(string jsonPath);
bool no_size(json data);
bool no_struct(json data);
json Parse(string jsonPath);
void Print(std::ostream& stream, json data);
#endif // INCLUDE_HEADER_HPP_
