from random import randrange
import subprocess
import os
import sys
import threading
import json
    
def runProgram(dataInput):
    process = subprocess.run(["./testGenerator.sh", dataInput], capture_output=True, check=False)
    contents = process.stdout.decode()
    output = contents.split("\n")[1].split(',')
    for idx in range(0, len(output)):
        output[idx] = float(output[idx])
    return output

def generate_params(existing, increment, config):
    params = {}
    
    while (len(params) < pow(int(config/increment), 4)):
        temp = [randrange(100)+1, randrange(100)+1, randrange(100)+1, randrange(100)+1]
        key = f"{temp[0]} {temp[1]} {temp[2]} {temp[3]}"
        if (key not in params):
            if (key not in existing):
                params[key] = [f"{temp[0]} {temp[1]} {temp[2]} {temp[3]}", temp]
                print(key)
            else:
                print("stop")
    return params

known_params = {}
thread_progress = {}
out_list = []
mutex = threading.Lock()

def search_blocks(input_data):
    allEntitys = {}
    counter = 0
    totalLen = len(input_data)
    for param in input_data:
        data = runProgram(param[0])
        if (data is not None):
            sumData = 0
            for idx in range(0, len(data)-1):
                sumData += data[idx]
            entry = {"output": data, "input": param[1], 'sum': sumData}
            keySumData = str(sumData)
            if (keySumData not in allEntitys):
                allEntitys[keySumData] = [entry]
            else:
                allEntitys[keySumData].append(entry)
        counter += 1
        
        mutex.acquire()
        thread_progress[f'{threading.current_thread().ident}'] = {'progress':counter/totalLen , 'workload':param[1]}
        mutex.release()
    
    mutex.acquire()
    out_list.extend(list(allEntitys.values()))
    mutex.release()
    sys.exit()

#enforce non-zero time quantums
#Complier testing intergration
lowestItems = []
for _ in range(20):
    out_list = []
    threads = []
    
    param_disc = generate_params(known_params, 10, 100)
    params = list(param_disc.values())
    
    num_threads = 40
    for _ in range(num_threads):
        local_params = []
        for idx in range(int(len(params)/num_threads)):
            local_params.append(params.pop())
        thread = threading.Thread(target=search_blocks, args=(list(local_params),))
        threads.append(thread) 
        thread.start()
        
    while True:
        breakOff = True
        
        mutex.acquire()
        iterationItems = list(thread_progress.items())
        mutex.release()
        
        output = 0
        for threadId,value in iterationItems:
            if (value['progress'] < 1):
                output += value["progress"]
            if (value['progress'] != 1):
                breakOff = False
        if breakOff:
            break
        os.system("clear")
        print(f'PROGRESS: {output/len(iterationItems)}')
        
    for thread in threads:
        thread.join()
    lowestItems.append(out_list)
    
    for key, value in param_disc.items():
        known_params[key] = value
    
with open("idealParameters.json", "w") as text_file:
    text_file.write(json.dumps({'data':lowestItems}))
    





