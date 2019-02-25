#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include "xmlprocess.h"
#include "treeminer/treeminer.h"
#include "sstminer/sstminer.h"

void usage(){
    std::string doc = 
    "\nUsage: miner [OPTION] ... [FILE] ...\n\n"
    "  -h               print this help\n"
    "  -p [PATH]        path of XML files\n"
    "  -d [FILE]        encoding data file\n"
    "  -i [FILE]        ID file of XML tags\n"
    "  -m [MINER]       mining method: treeminer(default) or sstminer\n"
    "  -o [FILE]        output file\n"
    "  -s [MINSUP]      proportional minimum support\n"
    "  -S [MINSUP]      absolute minimum support (default 0)\n\n"
    "Process XML file:\n"
    "  miner -p [XML_file_path] -d [encoding_file] -i [ID_file]\n\n"
    "Call treeminer or sstminer:\n"
    "  miner -m [treeminer/sstminer] -d [encoding_file] -o [output_file] -s[S] [minsup]\n\n"
    "Process XML file and call treeminer/sstminer:\n"
    "  miner -p [XML_file_path] -m [treeminer/sstminer] ...\n";
    std::cout << doc << std::endl;
}

int main(int argc, char** argv){
    int ch;
    std::string xmlpath, datafile, idfile("temp/temp_id.txt"), method("treeminer"), outfile("temp/temp_out.txt");
    std::string minsup_tag = "-S";
    double minsup = 0;
    while((ch=getopt(argc, argv, "p:d:i:m:o:s:S:h")) != -1) {
        switch(ch) {
            case 'p':
                xmlpath = optarg;
                break;
            case 'd':
                datafile = optarg;
                break;
            case 'i':
                idfile = optarg;
                break;
            case 'm':
                method = optarg;
                break;
            case 'o':
                outfile = optarg;
                break;
            case 's':
                minsup_tag = "-s";
                minsup = atof(optarg);
                break;
            case 'S':
                minsup_tag = "-S";
                minsup = atof(optarg);
                break;
            case 'h':
                usage();
                break;
            default:
                // std::cerr << "invalid argument: " << (char)ch << std::endl;
                usage();
                exit(1);
        }
    }
    // std::cout << "XML: " << xmlpath << std::endl
    // << "encoding: " << datafile << std::endl
    // << "id: " << idfile << std::endl 
    // << "out: " << outfile << std::endl
    // << "method: " << method << std::endl
    // << "minsup: " << minsup << std::endl;
    if(xmlpath=="" and datafile=="") {
        std::cerr << "invalid option! One of '-p' and '-d' must be set\n";
        usage();
        exit(1);
    } else if(datafile=="") {
        datafile = "temp/temp_encoding.txt";
    }
    if(method!="treeminer" and method!="sstminer") {
        std::cerr << "invalid argument! '-m' must be followed by 'treeminer' or 'sstminer'\n";
        usage();
        exit(1);
    }
#ifdef WIN
    mkdir("temp");
#else
    mkdir("temp", S_IRWXU);
#endif
    std::string sstdatafile = "temp/temp_sst_encoding.txt";
    XMLPool pool;
    if(xmlpath != "") {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(xmlpath.c_str())) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL) {
                // printf ("%s\n", ent->d_name);
                int len = strlen(ent->d_name);
                if(len<4) continue;
                std::string suffix = ent->d_name + (len-4);
                if(suffix != ".xml") continue;
                std::string xmlfile = xmlpath + "/" + ent->d_name;
                pool.process(xmlfile);
            }
            closedir (dir);
        } else {
            perror ("");
            exit(1);
        }
        pool.export_data(idfile, datafile);
        return 0;
    } 
    if(method=="sstminer") {
        pool.process_sst(datafile);
        pool.export_sstdata(sstdatafile);
        std::cout << "sstminer ..." << std::endl;
        sst::sstminer(sstdatafile, outfile, minsup_tag, minsup);
    } else {
        std::cout << "treeminer ..." << std::endl;
        treeminer(datafile, outfile, minsup_tag, minsup);
    }

    return 0;
}