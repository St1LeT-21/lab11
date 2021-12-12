#include <gtest/gtest.h>
#include <header.hpp>

#ifdef _JSON_DIR
#define JSON_DIR _JSON_DIR
#endif


TEST(ParseTest, TrueData) {
    EXPECT_TRUE(true);

    string JSON_path = JSON_DIR;
    JSON_path += "/students.json";
    string Tjson = ""
        "{\n"
        "  \"items\": [\n"
        "    {\n"
        "      \"name\": \"Ivanov Petr\",\n"
        "      \"group\": \"1\",\n"
        "      \"avg\": \"4.25\",\n"
        "      \"debt\": null\n"
        "    },\n"
        "    {\n"
        "      \"name\": \"Sidorov Ivan\",\n"
        "      \"group\": \"31\",\n"
        "      \"avg\": \"4\",\n"
        "      \"debt\": \"C++\"\n"
        "    },\n"
        "    {\n"
        "      \"name\": \"Pertov Nikita\",\n"
        "      \"group\": \"IU8-31\",\n"
        "      \"avg\": \"3.33\",\n"
        "      \"debt\": [\n"
        "        \"C++\",\n"
        "        \"Linux\",\n"
        "        \"Network\"\n"
        "      ]\n"
        "    }\n"
        "  ],\n"
        "  \"_meta\": {\n"
        "    \"count\": 3\n"
        "  }\n"
        "}";
    nlohmann::json TestFile = json::parse(Tjson);
    nlohmann::json File = Parse(JSON_path);
    EXPECT_EQ(TestFile, File);
}

TEST(ParseTest, try_file)
{
  string JSON_path = JSON_DIR;
  JSON_path += "/student.json";
  string er = "! The file cannot be found by this path:" + JSON_path;
  try {
    try_file(JSON_path);
    FAIL() << "! The file cannot be found by this path:" + JSON_path;
  }
  catch(std::runtime_error const & err) {
    EXPECT_EQ(err.what(),std::string(er));
  }
}
TEST(ParseTest, no_size)
{
  string JSON_path = JSON_DIR;
  JSON_path += "/test1.json";
  std::ifstream file{JSON_path};
  json data;
  file >> data;
  try {
    no_size(data);
    FAIL() << "! File is empty";
  }
  catch(std::runtime_error const & err) {
    EXPECT_EQ(err.what(),std::string("! File is empty"));
  }
}

TEST(ParseTest, Test3) {
  string JSON_path = JSON_DIR;
  JSON_path += "/test2.json";
  std::ifstream file{JSON_path};
  json data;
  file >> data;
  try {
    no_struct(data);
    FAIL() << "! The structure of the json file is broken";
  } catch (std::runtime_error const& err) {
    EXPECT_EQ(err.what(),
              std::string("! The structure of the json file is broken"));
  }
}

TEST(Print, Test1) {
  string Table = " |                name |          group |     avg |            dbt |\n"
      " -------------------------------------------------------------------\n"
      " |         Ivanov Petr |              1 |    4.25 |           null |\n"
      " -------------------------------------------------------------------\n"
      " |        Sidorov Ivan |             31 |       4 |            C++ |\n"
      " -------------------------------------------------------------------\n"
      " |       Pertov Nikita |         IU8-31 |    3.33 |        3 items |\n"
      " -------------------------------------------------------------------\n";

  std::stringstream StreamT;
  string JSON_path = JSON_DIR;
  JSON_path += "/students.json";
  json data = Parse(JSON_path);
  Print(StreamT, data);
  EXPECT_EQ(Table, StreamT.str());
}

