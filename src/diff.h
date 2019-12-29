#ifndef DIFF_H
#define DIFF_H

#include <ftw.h>
#include <string>
#include <ostream>

class WorkspaceAnalyzer {
 public:
  WorkspaceAnalyzer() {}
  virtual ~WorkspaceAnalyzer() = default;

  void setOstream(std::ostream *out) { this->out = out; }

  void walk(const std::string &name);

  static int analy(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf);

 private:

  static std::ostream *out;

};

#endif /* DIFF_H */