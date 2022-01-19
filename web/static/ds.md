# 数据结构定义
# 数据结构
针对网络小说月票榜的小说的属性，设计的数据结构如下：
```cpp
typedef struct Book {
    char bookId[8];    //书号
    char bookName[10];  //书名
    char author[10];    //作者
    unsigned int monthTicket;  //月票数量
XPACK(O(bookId, bookName, author, monthTicket));
} Book, *PBook;
```

该数据结构描述了小说的书号（一串纯数字的ID）、书名、作者以及本月小说得到的月票数量，之后的各种排序算法也是针对月票数量来进行各种操作的。
其中的XPACK代码是用来标识JSON的。



