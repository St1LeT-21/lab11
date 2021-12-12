#include <header.hpp>
#include <iostream>

int main() {
  string jsonPath = "..\\Students\\students.json";
  json data = Parse(jsonPath);
  Print(cout, data);
  return  0;
}
