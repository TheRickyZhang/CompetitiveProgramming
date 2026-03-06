#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  string jury = upperCase(ans.readToken());
  string part = upperCase(ouf.readToken());

  if(part != "WIN" && part != "LOSE")
    quitf(_pe, "Expected WIN or LOSE, got '%s'", part.c_str());

  if(part == jury)
    quitf(_ok, "%s", part.c_str());
  else
    quitf(_wa, "Expected %s, got %s", jury.c_str(), part.c_str());
}
