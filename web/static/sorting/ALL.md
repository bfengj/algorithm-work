# 异步并发执行

## 实现原理
服务器端提供了基于flask的异步工作模型，使用异步工作的原因是考虑到排序程序需要花大量时间来进行I/O操作，异步任务可以提高工作效率，减少CPU空闲时间。另外还实现了批量添加任务的操作，更加高效地利用异步提高工作效率。

## 具体代码
Task类继承了python中的并发库threading.Thread类，并实现了自定义的函数功能。
同时定义了用于返回线程信息的函数。
```python
class Task(threading.Thread):
    def __init__(self,name,target,output,*args,**argv):
        threading.Thread.__init__(self)
        self.uuid = str(uuid1())
        self.name = name
        self.target = target
        self.outputfile=output
        self.args = args
        self.argv = argv
    def run(self):
        self.start_time = time.time()
        # print(self.argv)
        self.result = self.target(*self.args,**self.argv)[:200]+'...'
        self.end_time = time.time()

    def list(self):
        return {
            'uuid':self.uuid,
            'name':self.name,
            'is_alive':self.is_alive(),
            'start_time':self.start_time,
            'end_time':0 if self.is_alive() else self.end_time,
            'result':'' if self.is_alive() else self.result,
            'outputfile':self.outputfile
        }
```