#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <zlib.h>

#include "antlr4-runtime.h"
#include "JavaLexer.h"
#include "JavaParser.h"
#include "JavaParserBaseListener.h"

using namespace std;
using namespace antlr4;

uLong CRC32(const string &body) {
  return crc32(0L, (const Bytef*)body.c_str(), body.size());
}

class MyListener : public JavaParserBaseListener {
 public:

  MyListener(ostream *out) : out(out) {}

  void enterPackageDeclaration(JavaParser::PackageDeclarationContext *ctx) override {
    // Do something when entering the key rule.
    packageName = ctx->qualifiedName()->getText();
  }

  virtual void enterClassDeclaration(JavaParser::ClassDeclarationContext * ctx) override {
    className = ctx->IDENTIFIER()->getText();
    className = packageName + "." + className;
  }

  virtual void enterEnumDeclaration(JavaParser::EnumDeclarationContext * ctx) override {
    className.clear();
  }

  virtual void enterMethodDeclaration(JavaParser::MethodDeclarationContext * ctx) override {
    if (packageName.empty() || className.empty()) {
      return;
    }
    string methodSignature =
        ctx->typeTypeOrVoid()->getText() + "|" +
        ctx->IDENTIFIER()->getText() +
        ctx->formalParameters()->getText();

    string methodBody = ctx->methodBody()->getText();


    *out << className << ","
         << "METHOD" << ","
         << methodSignature << ","
         << CRC32(methodBody)
         << endl;
  }

  virtual void enterFieldDeclaration(JavaParser::FieldDeclarationContext * ctx) override {
    if (packageName.empty() || className.empty()) {
      return;
    }

    /* TODO: 暂时没见过一行写多个属性的，先不管那么多 */
    string fieldName = ctx->variableDeclarators()->getText();
    *out << className << ","
         << "FIELD,"
         << fieldName << ","
         << endl;
  }

 public:

  string packageName;
  string className;

  ostream *out;
};


int analyFile(const std::string &filename, std::ostream *out) {
  std::ifstream stream;
  stream.open(filename.c_str());
  ANTLRInputStream input(stream);
  JavaLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  JavaParser parser(&tokens);

  tree::ParseTree *tree = parser.compilationUnit();
  MyListener listener(out);
  tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
  return 0;
}
