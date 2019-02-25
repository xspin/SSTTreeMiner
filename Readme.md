## 使用说明

### 编译
编译 Linux 可执行程序 (g++) miner
``` 
$ make deepclean
$ make
```
编译 Windows 可执行程序 (Mingw-w64) miner.exe
```
$ make deepclean 
$ make platform=win
```
**注意**：若运行windows程序，下面的 miner 需改为 miner.exe

### XML文件处理
```
$ bin/miner -p XMLfile_path -o datafile -i idfile
```
其中 XMLfile_path 为XML文件所在目录，可包含多个XML文件；datafile为处理后数据的储存文件路径；idfile为XML文件中标签对应的编号；数据输出格式见后面。

### 调用 TreeMiner/SSTMiner 
```
$ bin/miner -m treeminer/sstminer -d datafile -o outfile -s[S] minsup
```
其中 `-m` 参数指明使用treeminer或sstminer； `-d` 指明数据文件；`-o` 指定数据输出路径；`-S` 指明minsup大小，`-s` 则以比例形式表示，例如若数据大小为100则`-s 0.5`跟`-S 50`是一样的。


### 例子

XML处理
```
$ bin/miner -p data/xmlsample -d data/xmlsample/data.txt -i data/xmlsample/id.txt
```

调用 TreeMiner/SSTMiner 算法

```
$ bin/miner -m treeminer -d data/xmlsample/data.txt -o data/xmlsample/out_treeminer.txt -s 0
$ bin/miner -m sstminer -d data/xmlsample/data.txt -o data/xmlsample/out_sstminer.txt -S 1
```

cslogs
``` 
$ bin/miner -m treeminer -d data/cslogs/cslogs_processed.txt -o data/cslogs/out_treeminer.txt -s 0.02
$ bin/miner -m sstminer -d data/cslogs/cslogs_processed.txt -o data/cslogs/out_sstminer.txt -s 0.02
```

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
注意与文献[^zaki2005treeminer]中编码的区别：前面没有编号和长度数据且后面多加了一个-1

### outfile：使用TreeMiner或SSTMiner后的输出数据
```
DBASE_NUM_TRANS:         （树的总个数）
DBASE_MAXITEM:           （标签总数/最大编号+1）
MINSUPPORT:              （support参数，括号中的小数是占总数的比例）
FORMAT:                  （频繁子树输出格式）
    prefix: x x x x x x  （下面各子树的公共前缀）
    #(-1) x - #subtree1  （-1的个数） （最后节点编号） - （该子树出现频率）
    #(-1) x - #subtree2

prefix: 0 2
0 1 - 5         (表示子树 0 2 1 有5个)
1 2 - 2         (表示子树 0 2 -1 2 有2个)
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

## 文件结构说明
- bin 
  - miner 或 miner.exe 所在目录
- treeminer
  - treeminer 源代码所在目录
- sstminer
  - sstminer 源代码所在目录
- tinyxml2
  - 处理xml的程序代码，参考 https://github.com/eethomason/tinyxml2
- data
  - 测试数据所在目录
- doc
  - 相关文献pdf [^zaki2005treeminer] [^fu2007sstminer]
- temp
  - 临时文件输出目录

## 数据集说明
- cslogs
  - 文献[^zaki2005treeminer]中使用的一个数据集
  - http://www.cs.rpi.edu/~zaki/www-new/pmwiki.php/Software/Software#toc41
- TreeGen
  - 文献[^zaki2005treeminer]中提供的能随机生成数据的程序
- test
  - [wulangbu](https://github.com/wulangbnu/TreeMiner) 中的一些测试数据
- xmlsample
  - xml测试数据


## 参考文献
[^zaki2005treeminer]:  Zaki, Mohammed J. "TREEMinER: An Efficient Algorithm for Mining Embedded Ordered Frequent Trees." Advanced Methods for Knowledge Discovery from Complex Data. Springer, London, 2005. 123-151.

[^fu2007sstminer]: 傅珊珊. 基于聚类的 XML 文档集成管理方法研究 [D]. 华桥大学, 2007.

