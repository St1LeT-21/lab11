#include <header.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using nlohmann::json;
using namespace std;

int main() {
  string dbt;
  string jsonPath = "D:/MyPrograms/C++ programs/Students/students.json";
  std::ifstream file{jsonPath};
  if (!file) {
    throw std::runtime_error{"! The file cannot be found by this path:" + jsonPath};
  }
  json data;
  file >> data;
  if (data["items"].size() == 0){
    throw std::runtime_error{"! File is empty"};
  }
  if (data["meta"]["count"] != data["items"].size()){
    throw std::runtime_error{"! The structure of the json file is broken"};
  }
  cout<<" |"<<std::setw( 20 ) << std::right << "name"
       <<" |"<<std::setw( 15 ) << std::right << "group"
       <<" |"<<std::setw( 8 ) << std::right << "avg"
       <<" |"<<std::setw( 15 ) << std::right << "dbt" << " |" << endl;
  cout<<" -------------------------------------------------------------------"<<endl;
  int t = data["items"].size();
  for (int i = 0; i < t; i++) {
    if (data["items"][i]["debt"] == "null")
      cout<<data["items"][i]["debt"];
    if (int(data["items"][i]["debt"].size()) > 1)
      dbt = to_string(data["items"][i]["debt"].size()) + " items";
    else
      dbt = to_string(data["items"][i]["debt"]);
    string name = data["items"][i]["name"];
    string group = data["items"][i]["group"];
    string avg = data["items"][i]["avg"];
    cout<<" |"<<std::setw( 20 ) << std::right << name
         <<" |"<<std::setw( 15 ) << std::right << group
         <<" |"<<std::setw( 8 ) << std::right << avg
         <<" |"<<std::setw( 15 ) << std::right << dbt << " |" << endl;
    cout<<" -------------------------------------------------------------------"<<endl;
  }
  return  0;

}