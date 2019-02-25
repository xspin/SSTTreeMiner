#ifndef _xmlprocess_h
#define _xmlprocess_h

#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <unordered_map>
#include <set>
#include "tinyxml2/tinyxml2.h"

// #define DEBUG

using namespace tinyxml2;
using namespace std;

bool is_file_exist(const string &fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

bool diff(vector<vector<int>>& childtrees, vector<int>&tree) {
    for(auto& t : childtrees) {
        if(t.size()!=tree.size()) continue;
        int i;
        for(i=0; i<t.size(); i++) {
            if(t[i] != tree[i]) break;
        }
        if(i>=t.size()) return false;
    }
    return true;
}

std::vector<int> sst_process(const std::vector<int>& encoding, int i=0, int j=-1, bool nosibling=false) {
    if(j<0) j = encoding.size()-1;
    std::vector<int> new_encoding;
    if(!nosibling or encoding[i]!=encoding[i-1]) {
        new_encoding.push_back(encoding[i]);
    }
    std::vector<std::vector<int>> childtrees;
    int s = i+1;
    int cnt_sibling = 0;
    bool flag = false;
    while(s<j){// find childtrees
        int k = s+1;
        int cnt = 1;
        while(cnt>0) {
            assert(k<j);
            cnt += encoding[k]<0? -1 : 1;
            k++;
        }
        flag = flag | (k==j);
        std::vector<int> subtree = sst_process(encoding, s, k-1, flag);
        s = k;
        if(diff(childtrees, subtree)) {
            childtrees.push_back(subtree);
            for(auto id : subtree) new_encoding.push_back(id);
        }
    }
    if(!nosibling or encoding[i]!=encoding[i-1]) {
        new_encoding.push_back(encoding[j]);
    }
    return new_encoding;
}


class XMLPool{
    public:
    XMLPool(bool count_leaf=false, bool sst=false) {
        _count_text_leaf = count_leaf;
        _sst = false;
    }
    ~XMLPool() {
    }

    void process_sst(string& file) {
        return process(file, false);
    }

    void process(string& file, bool isxml=true) {
        cout << "Processing: " << file << endl;
        assert(is_file_exist(file));
        if(isxml) {
            XMLPrinter printer;
            XMLDocument doc;
            doc.LoadFile(file.c_str());
            XMLNode* root = doc.FirstChildElement();
            vector<int> encoding;
            dfs(encoding, root);
            tree_.push_back(encoding);
            vector<int> sst_encoding = sst_process(encoding);
            ssttree_.push_back(sst_encoding);
#ifdef DEBUG
            encoding = sst_encoding;
            cout << "  SST Reduced: " << encoding.size()-sst_encoding.size() << endl;
            int cnt = 0;
            int i;
            for(i=0; i<encoding.size() &&i<30; i++) {
                cout<< (encoding[i]<0? "-1" : nodeName_[encoding[i]]) << " " ;
                cnt += encoding[i]<0? -1 : 1;
            }
            if(i<encoding.size()) cout << "...";
            cout << endl;
            if(cnt!=0) cout << "Error XML\n";
            assert(cnt==0);
#endif //DEBUG
        } else {
            ifstream datafile(file);
            vector<int> encoding;
            int v;
            int cnt = 0;
            int row = 0;
            while(datafile >> v) {
                if(nodeId_.find(to_string(v)) == nodeId_.end()) {
                    nodeId_[to_string(v)] = v;
                }
                encoding.push_back(v);
                cnt += v<0? -1 : 1;
                if(cnt==0) {
                    row++;
                    tree_.push_back(encoding);
                    vector<int> sst_encoding = sst_process(encoding);
                    int d = encoding.size()-sst_encoding.size();
                    ssttree_.push_back(sst_encoding);

#ifdef DEBUG
                    if (d>0) {
                        cout << "  SST Reduced: " << d << "  Row: " << row << endl;

                        int i;
                        cout << "        ";
                        for(i=0; i<encoding.size() &&i<40; i++) {
                            cout<< encoding[i]<< " " ;
                        }
                        if(i<encoding.size()) cout << "...";
                        cout << endl;

                        int t = 0;
                        cout <<  "    SST ";
                        for(i=0; i<sst_encoding.size() ; i++) {
                            if(i<40) cout<< sst_encoding[i]<< " " ;
                            t += sst_encoding[i]<0? -1 : 1;
                        }
                        if(sst_encoding.size()>40) cout << "...";
                        cout << endl;
                        if(t!=0) cout << "Error Tree [t=" << t << "]\n";
                        assert(t==0);
                    }
#endif //DEBUG
                    encoding.clear();
                }
            }
        }
        
    }


    void export_data(const string& idfile, const string& datafile){
        cout << "Exporting...\n";
        cout << "  Data file: " << datafile << endl;
        cout << "  ID file: " << idfile << endl;
        ofstream idfd(idfile);
        ofstream datafd(datafile);
        cout << "  #Nodes: " << nodeName_.size() << endl;
        for(auto i=0; i<nodeName_.size(); i++) {
            idfd << i << " " << nodeName_[i] << "\n";
        }
        for(auto i=0; i<tree_.size(); i++) {
            cout << "  Len tree#" << i << ": " << tree_[i].size() << endl;
            int k;
            for(k=0; k<tree_[i].size()-1; k++) {
                datafd << tree_[i][k] << " ";
            }
            datafd << tree_[i][k] << "\n";
        }
        datafd.close();
        idfd.close();
    }
    void export_sstdata(const string& datafile){
        cout << "Exporting...\n";
        cout << "  SST Data file: " << datafile << endl;
        ofstream sstdatafd(datafile);
        cout << "  #Nodes: " << nodeId_.size() << endl;
        for(auto i=0; i<tree_.size(); i++) {
            // cout << "Len ssttree#" << i << ": " << ssttree_[i].size() << endl;
            int k;
            for(k=0; k<ssttree_[i].size()-1; k++) {
                sstdatafd << ssttree_[i][k] << " ";
            }
            sstdatafd << ssttree_[i][k] << "\n";
        }
        sstdatafd.close();
    }

    private:
    void dfs(vector<int>& encoding, XMLNode* root, int depth=0) {
        int spaces = 2;
        if(!root) return;
        if(!_count_text_leaf and root->NoChildren()) {
            // ignore text leaf nodes
            // if(root->ToElement()->GetText()!=nullptr) {
            //     string buf = root->ToElement()->GetText();
            //     cout << "Find data: " << buf << endl;
            // }
            return;
        }
        string v = root->Value();

        if(_sst) { // reduce multiplicative node
            XMLNode* child_node = root->FirstChild();
            if(child_node != nullptr) {
                string child_v = child_node->Value();
                if(child_node->NextSibling()==nullptr and child_v==v) {
                    return dfs(encoding, child_node, depth);
                }
            }
        }

        v = "<"+v+">";
        if(nodeId_.find(v)==nodeId_.end()) {
            nodeId_[v] = nodeName_.size();
            nodeName_.push_back(v);
            // cout << v << ": " << nodeId_[v] << endl;
        }


        encoding.push_back(nodeId_[v]);

        vector<vector<int>> childtrees;
        for(XMLNode* child=root->FirstChild(); child; child=child->NextSibling()) {
            vector<int> temptree;
            dfs(temptree, child, depth+1);
            if(!_sst or diff(childtrees, temptree)) { // reduce repeat paths
                if(_sst) childtrees.push_back(temptree);
                for(auto i : temptree) {
                    encoding.push_back(i);
                }
            }
        }
        encoding.push_back(-1);
    }


    private:
    vector<vector<int>> tree_; // one-node tree: 0 -1, two-node tree: 0 1 -1 -1
    vector<vector<int>> ssttree_; // one-node tree: 0 -1, two-node tree: 0 1 -1 -1
    vector<string> nodeName_;
    unordered_map<string, int> nodeId_;
    bool _count_text_leaf;
    bool _sst;
};

#endif //_xmlprocess_h