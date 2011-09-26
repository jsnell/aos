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

#include "aos.pb.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include <google/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/text_format.h>

DEFINE_string(test_pb_path, "", "");
DEFINE_bool(rewrite_inline, false, "");

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
    CHECK(f != NULL) << "Could not open '" << file << "'";

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

    if (FLAGS_rewrite_inline) {
        write_string_to_file(FLAGS_test_pb_path + ".tmp",
                             test.DebugString().c_str());
        rename((FLAGS_test_pb_path + ".tmp").c_str(),
               FLAGS_test_pb_path.c_str());
    } else {
        printf("%s", test.DebugString().c_str());
    }
}

int main(int argc, char **argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging("test-aos");

    CHECK(!FLAGS_test_pb_path.empty());

    render_test(FLAGS_test_pb_path);

    return 0;
}
