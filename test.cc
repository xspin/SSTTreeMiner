#include <iostream>
#include <fstream>
#include <string>

#include "xmlprocess.h"
#include "treeminer/treeminer.h"
#include "sstminer/sstminer.h"

using namespace std;
using namespace sst;

void check(string f1, string f2) {
    cout << "Checking ... "<< endl;
    cout << "  " << f1 << endl;
    cout << "  " << f2 << endl;
    string line1, line2;
    ifstream fh1(f1); 
    ifstream fh2(f2);
    bool passed = true;
    int i=0;
    while(getline(fh1, line1) and getline(fh2, line2)) {
            i++;
            if (line1 == "Summary") break;
            if (line1 != line2) {
                printf("  Not Match [line %d]:\n",i);
                cout << "    " << line1 << endl;
                cout << "    " << line2 << endl;
                passed = false;
            }
    }
    if (passed) printf("  Pass\n");
}

void xmltest_f5(double s, bool sst=false) {
    XMLPool xmlpool = XMLPool(false, sst);
    std::string f5t0 = "data/f5/t0.xml";
    std::string f5t1 = "data/f5/t1.xml";
    std::string f5t2 = "data/f5/t2.xml";
    xmlpool.process(f5t0);
    xmlpool.process(f5t1);
    xmlpool.process(f5t2);
    string idfile = "data/f5/id";
    if(sst) idfile += "sst";
    idfile += ".data";
    string datafile = "data/f5/encoding";
    if(sst) datafile += "sst";
    datafile += ".data";
    xmlpool.export_data(idfile, datafile);
    string outfile = "data/f5/out";
    if(sst) outfile += "sst";
    outfile += ".data";
    cout << "treeminer ... " << endl;
    treeminer(datafile, outfile, "-s", s);
}

void xmltest_f5leaf(double s, bool sst=false) {
    XMLPool xmlpool = XMLPool(true, sst);
    std::string f5t0 = "data/f5leaf/t0.xml";
    std::string f5t1 = "data/f5leaf/t1.xml";
    std::string f5t2 = "data/f5leaf/t2.xml";
    xmlpool.process(f5t0);
    xmlpool.process(f5t1);
    xmlpool.process(f5t2);
    string idfile = "data/f5leaf/id";
    if(sst) idfile += "sst";
    idfile += ".data";
    string datafile = "data/f5leaf/encoding";
    if(sst) datafile += "sst";
    datafile += ".data";
    xmlpool.export_data(idfile, datafile);
    string outfile = "data/f5leaf/out";
    if(sst) outfile += "sst";
    outfile += ".data";
    cout << "treeminer ... " << endl;
    treeminer(datafile, outfile, "-s", s);
}

void test_sst(double s, bool sst=false) {
    XMLPool xmlpool = XMLPool(false, sst);
    std::string xmlfn = "data/testsst/test_sst.xml";
    std::string xmlfn1 = "data/testsst/test_sst.1.xml";
    string idfile = "data/testsst/id";
    if(sst) idfile += "sst";
    idfile += ".data";
    string datafile = "data/testsst/encoding";
    if(sst) datafile += "sst";
    datafile += ".data";
    string outfile = "data/testsst/out";
    if(sst) outfile += "sst";
    outfile += ".data";

    xmlpool.process(xmlfn);
    xmlpool.process(xmlfn1);
    xmlpool.export_data(idfile, datafile);
    cout << "treeminer ... " << endl;
    treeminer(datafile, outfile, "-s", s);
}

void test_testF5(double s) {
    XMLPool xmlpool = XMLPool();
    std::string datafile = "data/test/F5.data";
    std::string sstdatafile = "data/test/F5_sst.data";
    std::string outfile = "data/test/F5_out.data";
    std::string sstoutfile = "data/test/F5_sst_out.data";
    xmlpool.process(datafile, false);
    xmlpool.export_sstdata(sstdatafile);
    cout << "sstminer... " << endl;
    sstminer(sstdatafile, sstoutfile, "-s", s);
    cout << "treeminer... " << endl;
    treeminer(datafile, outfile, "-s", s);
    check(sstoutfile, outfile);
}

void test_testD10(double s) {
    XMLPool xmlpool = XMLPool();
    std::string datafile = "data/test/D10.data";
    std::string sstdatafile = "data/test/D10_sst.data";
    std::string outfile = "data/test/D10_out.data";
    std::string sstoutfile = "data/test/D10_sst_out.data";
    xmlpool.process(datafile, false);
    xmlpool.export_sstdata(sstdatafile);
    cout << "sstminer... " << endl;
    sstminer(sstdatafile, sstoutfile, "-s", s);
    cout << "treeminer... " << endl;
    treeminer(datafile, outfile, "-s", s);
    check(sstoutfile, outfile);
}

int main() {
    // XMLPool xmlpool = XMLPool();
    // std::string testfile0 = "data/test.xml";
    // std::string testfile1 = "data/test1.xml";
    // std::string xmlfile1 = "tinyxml2/dream.xml";
    // std::string xmlfile2 = "data/ucd-sample-xml-files-appendix-g/NonSeller_ARM_121118.xml";
    double s = 0.5;
    // test_f5(s);
    // test_f5(s, true);

    // test_f5leaf(s);
    // test_f5leaf(s, true);

    // test_sst(s,true);
    // test_sst(s,false);

    test_testF5(0.1);
    test_testD10(0.1);
    return 0;
}