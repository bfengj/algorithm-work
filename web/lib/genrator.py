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



    fake.add_provider(MyProvider)
    rst = [fake.bookProfile() for i in tqdm(range(num))]
    with open('./static/json/{}books.json'.format(num),'w') as cur:
        json.dump(rst,cur)
    return str(rst[:1000])

def gen2():
    with open('bookname.txt','wb') as cur:
        s = b''
        for i in tqdm(range(2*10**4)):
                s+= '{}传\n'.format(fake.unique.name()).encode('utf-8')
        cur.write(s)





def judgeCorrectness(fileName,x):
    with open(fileName) as f:
        content = f.read()
    obj = json.loads(content)
    obj.sort(key = lambda x:x['monthTicket'],reverse=True)
    return obj[:x]