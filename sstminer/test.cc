#include <string>
#include <cassert>
#include "sstminer.h"
using namespace std;

int main(int argc, char** argv) {
    assert(argc==5);
    //datafile, outfile, -sS, minsup
    sst::sstminer(argv[1], argv[2], argv[3], atof(argv[4]));
    return 0;
}