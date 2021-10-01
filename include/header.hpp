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


bool try_file(string jsonPath){
  bool nofile = false;
  std::ifstream file{jsonPath};
  if (!file) {
    nofile = true;
    throw std::runtime_error{
        "! The file cannot be found by this path:" + jsonPath};
  }
  return nofile;
}

bool no_size(json data){
  bool nosize = false;
  if (data["items"].size() == 0){
    nosize = true;
    throw std::runtime_error{"! File is empty"};
  }
  return nosize;
}

bool no_struct(json data){
  bool nostruct = false;
  if (data["_meta"]["count"] != data["items"].size()){
    nostruct = true;
    throw std::runtime_error{"! The structure of the json file is broken"};
  }
  return nostruct;
}

json Parse(string jsonPath){
  std::ifstream file{jsonPath};
  bool nofile = try_file(jsonPath);
  if (nofile)
    return 0;
  json data;
  file >> data;
  bool nosize = no_size(data);
  if (nosize)
    return 0;
  bool nostruct = no_struct(data);
  if (nostruct)
    return 0;
  return data;
}

void Print(std::ostream& stream, json data){
  string dbt;
  string avg;
  string name;
  string group;
  stream<<" |"<<std::setw( 20 ) << std::right << "name"
         <<" |"<<std::setw( 15 ) << std::right << "group"
         <<" |"<<std::setw( 8 ) << std::right << "avg"
         <<" |"<<std::setw( 15 ) << std::right << "dbt" << " |" << endl;
  stream<<" -------------------------------------------------------------------"
         <<endl;
  int t = data["items"].size();
  for (int i = 0; i < t; i++) {
    if (data["items"][i]["debt"] == "null")
      stream<<to_string(data["items"][i]["debt"]);
    if (int(data["items"][i]["debt"].size()) > 1)
      dbt = to_string(data["items"][i]["debt"].size()) + " items";
    else if(data["items"][i].at("debt").is_null())
      dbt = "null";
    else
      dbt = data["items"][i].at("debt").get<string>();
    name = data["items"][i].at("name").get<string>();
    group = data["items"][i].at("group").get<string>();
    avg = data["items"][i].at("avg").get<string>();
    stream<<" |"<<std::setw( 20 ) << std::right << name
           <<" |"<<std::setw( 15 ) << std::right << group
           <<" |"<<std::setw( 8 ) << std::right << avg
           <<" |"<<std::setw( 15 ) << std::right << dbt << " |" << endl;
    stream<<" --------------------------------"
              "-----------------------------------"<<endl;
  }
}
#endif // INCLUDE_HEADER_HPP_
