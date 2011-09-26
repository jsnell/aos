// -*- c-basic-offset: 4 -*-
//
// Copyright (C) 2011 by Juho Snellman. Standard MIT license:
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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

using std::string;

void write_string_to_file(string file, string content) {
    FILE* f = fopen(file.c_str(), "w");
    CHECK(f != NULL);
    fwrite(content.data(), 1, content.size(), f);
    fclose(f);
}

bool show_diff(string title, string a, string b) {
    if (a == b)
        return false;

    printf("%s\n", title.c_str());
    write_string_to_file("out/diff-a", a);
    write_string_to_file("out/diff-b", b);
    system("diff -u out/diff-a out/diff-b");

    return true;
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

int test(string test_pb_path) {
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

    if (show_diff("Options",
                  test.expected_options().DebugString(),
                  result_options.DebugString()))
        return true;

    if (!test.has_selected_action() &&
        !test.has_result())
        return false;

    dispatch(test.mutable_game(),
             &result_options,
             DISPATCH_ACT,
             test.game().order(test.game().current_order_index()),
             test.selected_action());

    if (show_diff("Result",
                  test.result().DebugString(),
                  test.game().DebugString()))
        return true;

    return false;
}

int main(int argc, char **argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging("test-aos");

    test(FLAGS_test_pb_paths);

    return 0;
}
