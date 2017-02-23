from sklearn.tree import DecisionTreeClassifier
import numpy as np
from sklearn import tree
import os
os.chdir("Insert the working directory")

 
#Choose what file to test on

fileName = 'DTDataAll'
biton = ' main wo tower'
f = open(fileName+biton+'.txt', 'r')
#f = open('DTData'+'.txt', 'r')
#f = open('DTDataAll'+'.txt', 'r')
 
#Process file
nextLine = f.readline()
fuzz = nextLine[0:len(nextLine)-1].split(",")[1:len(nextLine[0:len(nextLine)-1].split(","))]
for i in range(len(fuzz)):
    tempLabel = ''
    for c in fuzz[i]:
        if not c.islower():
            tempLabel = tempLabel + c
    fuzz[i] = tempLabel
#print(fuzz)
nextLine = f.readline()
mainData = np.matrix(nextLine[0:len(nextLine)-1].split(","))
#print(mainData)
nextLine = f.readline()
while nextLine != "\n" and nextLine != "":
    #print(nextLine, np.matrix(nextLine.split(",")))
    mainData = np.append(mainData,np.matrix(nextLine[0:len(nextLine)-1].split(",")), axis=0)
    nextLine = f.readline()
f.close()

#print(mainData)
y = mainData[:,0]
x = np.delete(mainData,0,1)
#print(x,y)


#bob = DecisionTreeClassifier()
bob = DecisionTreeClassifier(max_depth = 5, min_samples_split= 2)
bob = bob.fit(x, y)

'''
f = open('DTData'+"Test"+'.txt', 'r')
f.close()
'''
 
#Process test set file
f = open(fileName+"Test"+biton+'.txt', 'r')
#f = open('DTData'+"Test"+'.txt', 'r')
#f = open('DTDataAll'+"Test"+'.txt', 'r')
f.readline()
nextLine = f.readline()
mainDataTest = np.matrix(nextLine[0:len(nextLine)-1].split(","))
nextLine = f.readline()
while nextLine != "\n" and nextLine != "":
    mainDataTest = np.append(mainDataTest,np.matrix(nextLine[0:len(nextLine)-1].split(",")), axis=0)
    nextLine = f.readline()
f.close()
print(mainDataTest.shape, mainData.shape)

yTest = mainDataTest[:,0]
xTest = np.delete(mainDataTest,0,1)
'''
yTest = mainData[:,0]
xTest = np.delete(mainData,0,1)
'''

 
#predict and output summary
ySaid = bob.predict(xTest)

countRight = 0.0
for i in range(len(yTest)):
    if yTest[i] == ySaid[i]:
        countRight = countRight + 1
percent = countRight/float(len(yTest))
print(percent)

TruePositive = 0
TrueNegative = 0
FalsePositive = 0
FalseNegative = 0
for i in range(len(yTest)):
    if yTest[i] == "True" and ySaid[i] == "True":
        TruePositive = TruePositive + 1
    elif yTest[i] == "False" and ySaid[i] == "False":
        TrueNegative = TrueNegative + 1
    elif yTest[i] == "False" and ySaid[i] == "True":
        FalsePositive = FalsePositive + 1
    elif yTest[i] == "True" and ySaid[i] == "False":
        FalseNegative = FalseNegative + 1
TruePositive = TruePositive/float(len(yTest))
TrueNegative = TrueNegative/float(len(yTest))
FalsePositive = FalsePositive/float(len(yTest))
FalseNegative = FalseNegative/float(len(yTest))
print("TruePositive: " + str(TruePositive))
print("TrueNegative: " + str(TrueNegative))
print("FalsePositive: " + str(FalsePositive))
print("FalseNegative: " + str(FalseNegative))
#print(type(ySaid[2]),ySaid[2], "True" == ySaid[2])
 
#Exports a file that can be turned into an image with graphviz
#Their is a way to do it in code, but graphviz has trouble when it installs on windows
#So here it must be done manually



#import pydotplus 
dot_data = tree.export_graphviz(bob, out_file="tree.dot", feature_names = fuzz,class_names=[str(False),str(True)],filled=True, rounded=True, rotate = True) 
#print(dot_data)
'''
f = open("tree.dot", 'r')
dot_dat = f.read()
f.close()
print(dot_dat)
graph = pydotplus.graphviz.graph_from_dot_file("tree.dot")#dot_data) 
graph.write_pdf("tree.pdf") 
'''




