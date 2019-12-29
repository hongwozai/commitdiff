#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "analy.h"
#include "diff.h"

using namespace std;

int mapfiles (const std::string &prefix, const std::string &name) {
  ifstream file(name);

  if (!file.is_open()) {
    perror("file open failed: ");
    return -1;
  }

  string line;
  while (getline(file, line)) {
    /* cout << line << endl; */
    if (line.size() < sizeof(".java") ||
        line.substr(line.size() - 5) != ".java") {
      return 0;
    }

    /* cout << prefix + line << endl; */
    if (!prefix.empty()) {
      analyFile(prefix + line, &cout);
    } else {
      analyFile(line, &cout);
    }
  }
}

int main(int argc, char *argv[])
{
  ios::sync_with_stdio(false);

  if (argc < 3) {
    cout << "error argument" << endl;
    exit(-1);
  }

  if (strcmp(argv[1], "-workspace") == 0) {
    WorkspaceAnalyzer *wa = new WorkspaceAnalyzer;
    wa->setOstream(&cout);
    wa->walk(argv[2]);
    return 0;
  }

  if (strcmp(argv[1], "-files") == 0) {
    if (argc == 4) {
      mapfiles(argv[3], argv[2]);
    } else {
      mapfiles("", argv[2]);
    }
    return 0;
  }
  cout << "error argument 2" << endl;
  return 0;
}
