import os
import json
def algo(inputfile,outputfile,function,algorithm,X,Y=0,**form):
    cmd = './lib/main -f{} -m{} -n{} -o{} -a{} -i{}'.format(function+1,X,Y,'./static/json/'+outputfile,algorithm+1,'./static/json/'+inputfile)
    return os.popen(cmd).read()
# def algo(inputfile,outputfile,function,algorithm,X,Y):


func = ['Max','Min','TopN','Nth','LastN','Median','Keyword','KeywordPercent','EliminateAbnormalData']
algorithm = ['shellSort','quickSort','heapSort','baseSort','mergeSort','BFPTR']

def validate(form):
    error = ''
    try:
        f = func.index(form['function'])
        a = algorithm.index(form['algorithm'])
        if '..' in form.get('inputfile'):
            error = 'Inputfile'
        elif (not 0<=f<=4 and not 0<=a<=5 ) or f>=8:
            print(f,a)
            error = 'Function or algorithm'
        elif form.get('inputfile') + form.get('outputfile')== '' or '..' in form.get('inputfile')+form.get('outputfile') or os.path.exists('../static/json/'+form.get('outputfile')):
            error = 'Input/output file path'

    except TypeError:
        error = 'Form'

    if error:
        return '',error
    else:
        msg = 'Using {algorithm} to find the {function}!INPUTFILE:{inputfile} OUTPUTFILE:{outputfile} X:{X}'+('Y:{Y}'if form.get('Y') else '')
        msg = msg.format(**form)
        form['function'] = f
        form['algorithm'] = a
        return msg,''
        # return ('Using {} to find the {}!INPUTFILE:{} OUTPUTFILE:{} X:{}'+'Y:{}'if form.get('Y') else '').format(form['algorithm'],form['function'],form['inputfile'],form)



def judgeCorrectness(fileName,y):
    # func = ['Max','Min','TopN','Nth','LastN']
    with open('./static/json/'+fileName) as f:
        obj = json.load(f)
    obj.sort(key = lambda x:x['monthTicket'],reverse=True)
    half = len(obj) // 2
    rst = {
        'Max':[obj[0]],
        'Min': [obj[-1]],
        'TopN': obj[:y],
        'Nth': [obj[y]],
        'LastN': obj[y:],
        'Keyword':[],
        'Median':[obj[half]]
    }
    return rst


