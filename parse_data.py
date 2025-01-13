import json
import sys
import statistics

txt_content = ""
with open('idealParameters.json') as f:
    line = f.readline()
    while line:
        txt_content += line
        line = f.readline()
        
def getMetricRange(data, idx):
    min_val = sys.maxsize
    max_val = -min_val
    for run in data:
        for config in run:
            if (config['input'][idx] < min_val):
                min_val = config['input'][idx]
            if (config['input'][idx] > max_val):
                max_val = config['input'][idx]
    return min_val, max_val

def getMetricAvertages(data, idx):
    total = 0
    occurence = 0
    for run in data:
        for config in run:
            total += config['input'][idx]
            occurence += 1
    return total/occurence

def getMetricMedieum(data, idx):
    total = 0
    occurence = 0
    tempHold = []
    for run in data:
        for config in run:
            tempHold.append(config['input'][idx])
    tempHold.sort()
    return statistics.median(tempHold)

maximums = []
minimums = []
fileData = json.loads(txt_content)['data']
for testingRun in fileData:
    localMin = None
    localMax = None
    for outcome in testingRun:
        if localMin == None:
            localMin = outcome
        elif outcome[0]['sum'] < localMin[0]['sum']:
            localMin = outcome
            
        if localMax == None:
            localMax = outcome
        elif outcome[0]['sum'] > localMax[0]['sum']:
            localMax = outcome
    minimums.append(localMin)
    maximums.append(localMax)
    
print("Range (min)")
for x in range(4):
    minTurnaroundInput,maxTurnaroundInput = getMetricRange(minimums, x)
    print(minTurnaroundInput, maxTurnaroundInput)
print("Average (min)")
for x in range(4):
    print(int(getMetricAvertages(minimums, x)))
print("Medium (min)")
for x in range(4):
    print(int(getMetricMedieum(minimums, x)))

    
print("Range (max)")
for x in range(4):
    minTurnaroundInput,maxTurnaroundInput = getMetricRange(maximums, x)
    print(minTurnaroundInput, maxTurnaroundInput)
print("Average (max)")
for x in range(4):
    print(int(getMetricAvertages(maximums, x)))
print("Medium (max)")
for x in range(4):
    print(int(getMetricMedieum(maximums, x)))

workloadData = """0,3,0 
3,50,0 
7,2,0 
10,6,0 
10,12,0 
10,4,0 
23,6,0 
27,11,0 
33,3,0 
36,2,0 
42,4,0 
50,6,0 
50,5,0 
50,6,0 
50,1,0 
66,41,0 
71,3,0 
74,2,0 
77,6,0"""
workloadData = workloadData.split('\n')
for idx in range(0,len(workloadData)):
    workloadData[idx] = workloadData[idx].split(",")
    for innerIdx in range(0, len(workloadData[idx])):
        data = workloadData[idx][innerIdx]
        workloadData[idx][innerIdx] = int(data)

occurence = 0
for entry in workloadData:
    if entry[1] <= 6:
        occurence += 1
print(f'Occurence: {occurence} {occurence/len(workloadData)}')
