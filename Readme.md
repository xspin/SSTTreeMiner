TODO:
- implement SSTMiner algorithm
- implement decoding algorithm


## 使用说明

### 编译
``` 
$ make
```

### XML文件处理
```
$ miner -p XMLfile_path -o datafile -i idfile
```
其中 XMLfile_path 为XML文件所在目录，可包含多个XML文件；datafile为处理后数据的储存文件路径；idfile为XML文件中标签对应的编号；数据输出格式见后面。

### 调用 TreeMiner/SSTMiner 
```
$ miner -m treeminer/sstminer -d datafile -o outfile -s[S] minsup
```
其中 `-m` 参数指明使用treeminer或sstminer； `-d` 指明数据文件；`-o` 指定数据输出路径；`-S` 指明minsup大小，`-s` 则以比例形式表示，例如若数据大小为100则`-s 0.5`跟`-S 50`是一样的。

## 文件格式说明

### idfile：记录标签的编号，其中编号对应于datafile中的相应数据
```
0 <标签0>
1 <标签1>
2 <标签2>
.
.
.
```

### datafile：储存编码后的树
```
第1个XML文件对应的树的编码
第2个XML文件对应的树的编码
.
.
.
```
比如
```
0 1 -1 2 3 -1 -1 -1
1 0 1 -1 3 -1 -1 1 -1 2 -1 -1
0 2 1 -1 -1 4 0 1 -1 2 3 -1 -1 -1 -1 -1
```

### outfile：使用TreeMiner或SSTMiner后的输出数据
```
DBASE_NUM_TRANS:         （树的总个数）
DBASE_MAXITEM:           （标签总数/最大编号+1）
MINSUPPORT:              （support参数，括号中的小数是占总数的比例）
FORMAT:                  （频繁子树输出格式）
    prefix: x x x x x x  （下面各子树的公共前缀）
    #(-1) x - #subtree1  （-1的个数） （最后节点编号） - （该子树出现频率）
    #(-1) x - #subtree2

.
.
.

Summary         （Fk的大小统计）
F1 - a1 b1      （a为满足minsup的等价类个数，b为遍历到的等价类个数）
F2 - a2 b2
.
.
.

TIME = ... （总耗时）

```