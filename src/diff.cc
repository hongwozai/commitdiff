#include <string>
#include <iostream>
#include <ftw.h>

#include "diff.h"
#include "analy.h"

using namespace std;

std::ostream* WorkspaceAnalyzer::out;

int WorkspaceAnalyzer::analy(const char *fpath, const struct stat *sb,
                             int tflag, struct FTW *ftwbuf)
{
  if (tflag != FTW_F) {
    return 0;
  }

  string path = fpath;
  string filename = path.substr(ftwbuf->base);

  if (filename.size() < sizeof(".java") ||
      filename.substr(filename.size() - 5) != ".java") {
    return 0;
  }

  try {
    analyFile(path, out);
  } catch (...) {
  }

  return 0;
}


void WorkspaceAnalyzer::walk(const std::string &name)
{
  if (-1 == nftw(name.c_str(), analy, 20, 0)) {
    perror("nftw");
  }
}