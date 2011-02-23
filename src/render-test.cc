#include "dispatch.h"
#include "render.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include <google/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/text_format.h>

DEFINE_string(test_pb_paths, "", "");

DEFINE_string(options_outfile, "", "");
DEFINE_string(result_outfile, "", "");

using std::string;

void write_string_to_file(string file, string content) {
  FILE* f = fopen(file.c_str(), "w");
  CHECK(f != NULL);
  fwrite(content.data(), 1, content.size(), f);
  fclose(f);
}

string slurp(string file) {
  string res;
  char data[4096];
  int len;

  FILE* f = fopen(file.c_str(), "r");
  CHECK(f != NULL) << file;

  while ((len = fread(data, 1, sizeof(data), f)))
    res.append(data, len);

  return res;
}

void render_test(string test_pb_path) {
  Test test;
  string test_pb = slurp(test_pb_path);

  if (!google::protobuf::TextFormat::ParseFromString(test_pb, &test))
    LOG(FATAL) << "Error parsing Test pb:\n"
               << test_pb_path;

  Options result_options;
  dispatch(test.mutable_game(),
           &result_options,
           DISPATCH_OPT,
           test.game().order(test.game().current_order_index()),
           0);

  if (!FLAGS_options_outfile.empty()) {
    write_string_to_file(FLAGS_options_outfile,
                         render_game(test.game(), result_options));
  }

  if (!FLAGS_result_outfile.empty()) {
    CHECK(test.has_selected_action());

    dispatch(test.mutable_game(),
             &result_options,
             DISPATCH_ACT,
             test.game().order(test.game().current_order_index()),
             test.selected_action());

    write_string_to_file(FLAGS_result_outfile,
                         render_game(test.game(), Options()));
  }
}

int main(int argc, char **argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging("test-aos");  

  render_test(FLAGS_test_pb_paths);

  return 0;
}
