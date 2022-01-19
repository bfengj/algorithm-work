import re
from flask import Flask,render_template,Blueprint,jsonify,request
from flask.scaffold import F
from lib.genrator import gen
from lib.algorithm import algo,validate,func,algorithm,judgeCorrectness
import json,os,time
import threading
from uuid import uuid1
app = Flask(__name__)

tasks = {}
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

if not os.path.exists('./static/json/'):
    os.mkdir('./static/json/')

'''
typedef struct Book{
    char bookId[8];
    char bookName[10];
    char author[5];
    int monthTicket;
}Book,*PBook;
'''




@app.route('/',methods=['POST','GET'])
def index():
    return render_template('index.html')



@app.route('/api/sorting',methods=['POST'])
def sorting():
# def algo(inputfile,outputfile,function,algorithm,X,Y):
    form = request.json
    name,error = validate(form)
    if error:
        return jsonify({
            'status':False,
            'error':error+' error!',
            'uuid':''
        })

    task = Task(name,algo,form['outputfile'],**form)
    task.start()
    tasks[task.uuid] = task
    return jsonify({
        'status':1,
        'uuid':task.uuid
    })

@app.route('/api/sortingAll',methods=['POST'])
def sortingAll():
    # algo(inputfile,outputfile,function,algorithm,X,Y=0,**form):
    form = dict(request.json)
    
    uuids = []
    for i,fun in enumerate(func):
        if i==8:continue
        if i<5:
            for alg in algorithm:   
                form['function'] = fun
                form['algorithm'] = alg
                form['outputfile'] = '{}-{}-{}'.format(fun,alg,form['inputfile'])
                print(form)
                name,error = validate(form)
                if error:
                    return jsonify({
                        'status':False,
                        'error':error+' error!',
                        'uuid':''
                    })

                # task = Task(name,algo,(*[form['inputfile'],form['outputfile'],form['function'],form['algorithm'],100]))
                task = Task(name,algo,form['outputfile'],**form)
                task.start()
                tasks[task.uuid] = task
                uuids.append(task.uuid)
        else:
            form['function'] = fun
            form['algorithm'] = 'BFPTR'
            form['outputfile'] = '{}-{}.json'.format(fun,form['inputfile'])
            name,error = validate(form)
            if error:
                return jsonify({
                    'status':False,
                    'error':error+' error!',
                    'uuid':''
                })

            task = Task(name,algo,form['outputfile'],**form)
            task.start()
            tasks[task.uuid] = task
            uuids.append(task.uuid)
    return jsonify({
        'status':True,
        'uuids':uuids
    })

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

@app.route('/api/deleteTask',methods=['GET'])
def deleteTask():
    try:
        del tasks[request.args.get('uuid')]
    except:
        pass
    return jsonify({
        'status':1
    })

@app.route('/api/tasks')
def taskStatus():
    return jsonify([v.list() for v in tasks.values()])



        #
@app.route('/api/listJson')
def listJson():

    return jsonify(os.listdir('./static/json/'))

@app.route('/api/test')
def test():
    file = request.args.get('filename')
    x = int(request.args.get('x'))
    print(file)
    if file and os.path.exists('./static/json/'+file):
        rst = judgeCorrectness(file,x)
        # print(rst)
        result ={}
        # try:

        # print(rst['Median'])
        for filename in os.listdir('./static/json'):
            if '-' in filename:
                func = filename.split('-')[0]
                result[filename] = 1
                with open('./static/json/'+filename,'r') as cur:
                    tmp = json.load(cur)
                    # try:
                    if len(tmp)!=len(rst[func]):
                        result[filename] = 0
                        continue
                    for i in range(len(tmp)):
                        if rst[func][i]['bookId'] != tmp[i]['bookId']:
                            print(rst[func][i]['bookId'],tmp[i]['bookId'])
                            result[filename] = 0
                    # except KeyError:
                    #     result[filename] = 0

        return jsonify({
            'statuc':True,
            'test':result
        })
        # except:
            # return jsonify({'statuc':False,'test':[]})
    else:
        return jsonify({'statuc':False,'test':[]})


if __name__=='__main__':
    app.run('0.0.0.0',8082,True)
    

    