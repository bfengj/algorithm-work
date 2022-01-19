//#include <bits/stdc++.h>
#include "xpack/json.h"
#include <unistd.h>
#include <vector>
#include <time.h>
#include <iostream>
#include<algorithm>
#include <stdio.h>
#include "algorithm.h"
using namespace std;


int main(int argc,char* argv[]) {
    if(argc<=2){
        cout<<"-f -m -n -o -a -i\nf:功能\n1：输出序列的第一位\n2：输出序列的倒数第一位\n3：前N个\n4：第N个\n5：后N个\n6：中位数\n7：百分位数\n8：比例\n9：去除异常数据\n\nm,n:输入的参数，除了功能7，其他的都只有一个输入，所以只需要输入m即可。\n\na:\n实现的算法，部分功能需要区分算法。\n1：希尔\n2：快速\n3：堆\n4：基数\n5：归并\n6：BFPTR\n\no:\n不同功能实现后的vector<Book> res，json之后写入的文件名。\ni:\n输入的JSON文件名"<<endl;
        return 0;
    }
    char ch;
    int value1,value2;
    int function;
    int alg;
    string outputFileName,inputFileName;
    opterr = 0;         //不显示参数错误信息
    while ((ch = getopt(argc,argv,"f:m:n:a:o:i:")) != -1) {

        switch (ch) {
            case 'f':
                function = atoi(optarg);
                //printf("f:%d\n",function);
                break;
            case 'm':
                value1 = atoi(optarg);
                //printf("m:%d\n",value1);
                break;
            case 'n':
                value2 = atoi(optarg);
                //printf("n:%d\n",value2);
                break;
            case 'a':
                alg = atoi(optarg);
                //printf("a:%d\n",alg);
                break;
            case 'o':
                outputFileName = optarg;
                //printf("%s\n",fileName.c_str());
                break;
            case 'i':
                inputFileName= optarg;
                //printf("%s\n",fileName.c_str());
                break;
        }
    }

    vector<Book> books;
    std::ifstream f(inputFileName);
    std::string str((std::istreambuf_iterator<char>(f)),
                    std::istreambuf_iterator<char>());

    xpack::json::decode(str, books);
    vector<Book> res;
    clock_t startTime, endTime;
    int n = books.size();
    cout<<"待排序数组长:"<<n<<endl;
    startTime = clock();
    switch (function) {
        case 1:{
            switch (alg) {
                case 1:{
                    books = shellSort(books);
                    break;
                }
                case 2:{
                    books = quickSort(books);
                    break;
                }
                case 3:{
                    books = heapSort(books);
                    break;
                }
                case 4:{
                    books = baseSort(books);
                    break;
                }
                case 5:{
                    //printf("ok");
                    books = mergeSort(books);
                    break;
                }
                case 6:{
                    BFPTR(books,0,n-1,1);
                    break;
                }
            }
            res.push_back(books[0]);
            break;
        }
        case 2:{
            switch (alg) {
                case 1:{
                    books = shellSort(books);
                    break;
                }
                case 2:{
                    books = quickSort(books);
                    break;
                }
                case 3:{
                    books = heapSort(books);
                    break;
                }
                case 4:{
                    books = baseSort(books);
                    break;
                }
                case 5:{
                    books = mergeSort(books);
                    break;
                }
                case 6:{
                    BFPTR(books,0,n-1,n);
                    break;
                }
            }
            res.push_back(books[n-1]);
            break;
        }
        case 3:{
            switch (alg) {
                case 1:{
                    books = shellSort(books);
                    break;
                }
                case 2:{
                    books = quickSort(books);
                    break;
                }
                case 3:{
                    books = heapSort(books);
                    break;
                }
                case 4:{
                    books = baseSort(books);
                    break;
                }
                case 5:{
                    books = mergeSort(books);
                    break;
                }
                case 6:{
                    BFPTR(books,0,n-1,value1);
                    QuickSort(books,0,value1-1);
                    break;
                }
            }
            for (int i = 0; i < value1; ++i) {
                res.push_back(books[i]);
            }
            break;
        }
        case 4:{
            switch (alg) {
                case 1:{
                    books = shellSort(books);
                    break;
                }
                case 2:{
                    books = quickSort(books);
                    break;
                }
                case 3:{
                    books = heapSort(books);
                    break;
                }
                case 4:{
                    books = baseSort(books);
                    break;
                }
                case 5:{
                    books = mergeSort(books);
                    break;
                }
                case 6:{
                    BFPTR(books,0,n-1,value1);
                    //QuickSort(books,0,value1-1);
                    break;
                }
            }
            res.push_back(books[value1-1]);
            break;
        }
        case 5:{
            switch (alg) {
                case 1:{
                    books = shellSort(books);
                    break;
                }
                case 2:{
                    books = quickSort(books);
                    break;
                }
                case 3:{
                    books = heapSort(books);
                    break;
                }
                case 4:{
                    books = baseSort(books);
                    break;
                }
                case 5:{
                    books = mergeSort(books);
                    break;
                }
                case 6:{
                    BFPTR(books,0,n-1,n-value1);
                    QuickSort(books,value1-1,n-1);
                    break;
                }
            }
            for (int i = n-value1; i < n; ++i) {
                res.push_back(books[i]);
            }
            break;
        }
        case 6:{
            res = findMedian(books);
            break;
        }
        case 7: {
            res = topKPercent(books,value1);
            break;
        }
        case 8:{
            findCountProportion(books,value1,value2);
            break;
        }
        case 9:{
            res = removeAbnormalData(books,value1);
            break;
        }
    }
    endTime=clock();
    if (res.size()!=0){
        string json = xpack::json::encode(res);
        ofstream OsWrite(outputFileName, ofstream::app);
        OsWrite << json;
        OsWrite << std::endl;
        OsWrite.close();
    }
    cout<<"主循环执行了"<<cnt<<"次"<<endl;
    printf("总时间：%0.8fs", (double)(endTime - startTime)/CLOCKS_PER_SEC );


/*
-f -m -n -o -a
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
 */
}
