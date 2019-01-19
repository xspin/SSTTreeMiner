#ifndef __sstminer_H
#define __sstminer_H

#include <cassert>
#include <vector>
#include <string>
#include <functional>

namespace sst{

//enums
enum sort_vals {nosort, incr, decr};
enum alg_vals {alltreeminer, maxtreeminer};
enum prune_vals {noprune, prune};
  
//externs
extern double MINSUP_PER;
extern int MINSUPPORT;
extern int DBASE_MAXITEM;
extern int DBASE_NUM_TRANS;

extern bool output;
extern bool output_idlist;

extern sort_vals sort_type;  
extern alg_vals alg_type;
extern prune_vals prune_type;

void sstminer(const std::string& datafile, const std::string& outfile, const std::string& t, double minsup);


}//namespace sstminer
#endif
