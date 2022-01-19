# 随机数据生成

## 实现方式
我们小组编写了一个基于python第三方库`faker`的书本信息生成程序，将这些信息转化为`JSON`结构后写入一个`JSON`文件中。

```python
import random

from faker import Faker
from tqdm import tqdm
import json


def gen(num):
    fake = Faker('')
    from faker.providers import BaseProvider

    class MyProvider(BaseProvider):
        def bookProfile(self):
            return {
                'bookName': random.choice(['Biography of {}\n'.format(fake.name()), '{} travels'.format(fake.city())]),
                'bookId': fake.unique.ean8(),
                'author': fake.name(),
                'monthTicket': random.randint(1,1000000),
                }

```

并且实现了远程调用该函数的接口。
```python
@app.route('/api/genrator',methods=['GET'])
def genrate():
    num = int(request.args.get('num'))%1000001
    if num:
        task = Task('Genration of {} fake books\' profile'.format(num),gen,'{}books.json'.format(num),num)
        task.start()
        tasks[task.uuid] = task
        return jsonify({
            'status':True,
            'uuid':task.uuid
        })
    else:
        return jsonify({
            'status':False,
            'uuid':''
        })
```