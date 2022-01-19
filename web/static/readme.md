# 算法综合实验大作业-作业九-xx小说网月票排行系统

## 角色分工
- 祝千禧 排序算法实现
- 李浩宇 (4)-(9)
- 洪汇智 实现图形用户交互接口

近年来，电商平台得到快速发展，特别是新冠疫情之下，网络直播为商家和消费者搭建了一个桥梁，扩大了传统行业的销售半径，许多传统行业以直播等为抓手，纷纷转战线上营销，有效降低了线下经营损失，甚至还出现了逆势增长。
## 那么
- 在一个直播平台或电商平台出现秒杀等高并发场景下如何快速找出TopN的刷榜榜单和热销商品呢？
- 在一个大型游戏平台每局游戏结束时如何快速统计某个用户的排名情况呢？
- 一个搜索引擎在检索出的上百万条记录中如何选出相关度最高的前N条结果呢？

这一系列问题都离不开**排序**。可是一旦数据量大起来，使用性能差的排序算法的话排序个几分钟都有可能，而对于用户来说，他们只希望点击之后就能立刻看到结果，因此算法的性能对于解决这样的问题来说十分的重要。
本次大作业针对的是起点中文网中类似月票榜这样的榜单的**TopN之类**的问题来设计算法，实现各种功能。


## 题目说明
1.创建用于存放待排名数据的数据结构（可以根据应用决定，如直播榜单、电商榜单、游戏榜单、影视/图书作品榜单等，不限）。
2.基本测试数据可以先使用随机数生成函数生成指定长度（1~1,000,000）的待排名序列，存放在相应的数据结构中。
3.自己实现希尔排序、快速排序、堆排序、基数排序和归并排序，对待排名序列进行排名，输出序列的第1名、倒数第1名、任意指定的第N个结果和前N个结果。
4.分别设计高效的算法，输出序列的第1名、倒数第1名、任意指定的前N个结果和后N个结果。
5.另外设计高效的算法，输出序列的中位数。
6.另外设计高效的算法，输出序列的各百分位数对应的关键字值，统计该区段数据所占的比例。
7.假设待统计序列中前后m%的数据为异常数据，设计算法剔除这些异常数据。
8.测试以上算法的正确性，对算法进行性能对比分析，逐个说明算法的优势。
9.设计统一的算法接口，将以上算法封装为库函数，方便调用；结合某个实际应用，寻找数据集或爬取数据，调用你的算法库进行统计分析。（数据量足够大，能够凸显算法效能）
10.良好的人机交互界面、合适的应用需求分析、合理的应用设计将获得加分。


## 程序实现
整个程序通过命令行参数作为输入，包括如下参数：
-f -m -n -o -a -i
f:功能
1：输出序列的第一位
2：输出序列的倒数第一位
3：前N个
4：第N个结果
5：后N个
6：中位数
7：百分位数对应的关键字值
8：统计任意给定的两个关键字区段间数据所占的比例
9：去除异常数据

m,n:输入的参数，除了功能7，其他的都只有一个输入，所以只需要输入m即可。

a:
实现的算法，部分功能需要区分算法。
1：希尔
2：快速
3：堆
4：基数
5：归并
6：BFPTR

o:
不同功能实现后的vector<Book> res，json之后写入的文件名。
i:
输入的JSON文件名。

输入之后根据-f和-a进行功能和算法的选择，调用相关的函数进行处理并将结果写入-o指定的json文件中或者打印出输出。
涉及到的所有函数如下：

```cpp
vector<Book> findMedian(vector<Book> &books);
int Partion(vector<Book> &a, int l, int r);
int Partion(vector<Book> &a, int l, int r, int pos);
void InsertSort(vector<Book> &a, int l, int r);
Book findMiddle(vector<Book> a, int l, int r);
void BFPTR(vector<Book> &a, int l, int r, int k);
vector<Book> topKPercent(vector<Book> &a,int k);
vector<Book> removeAbnormalData(vector<Book> &a, int m);
vector<Book> shellSort(vector<Book>& v);
vector<Book> heapSort(vector<Book> v);
void QuickSort(vector<Book> &a, int l, int r);
int oneSort(vector<Book> &v, int low, int high);
vector<Book> quickSort(vector<Book> &v);
vector<Book> baseSort(vector<Book> &v);
vector<Book> mergeSort(vector<Book> &v);
int search1(vector<Book>& nums, int target);
int search2(vector<Book>& nums, int target);
void findCountProportion(vector<Book> &a,int value1,int value2);

```
将在下面详细的说明。










