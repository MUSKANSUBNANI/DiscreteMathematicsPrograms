import sys

def transpose(a): # for symmetric closure function
    m=a.copy()
    for i in range(len(m)):
        for j in range(len(m[0])):
            m[i][j]=m[j][i]
    return m

def reflexive(a):
    for i in range (len(a)):
        for j in range(len(a[0])):
            if ((a[i][j]==1) or (i==j)):
                 a[i][j]=1
            else:
                a[i][j]=0
    return a
    
def symmetric(a):
    ans=a.copy() 
    r=a.copy()
    rinverse=transpose(r)
    for i in range (len(a)):
        for j in range(len(a[0])):
            if (a[i][j]==1 or rinverse[i][j]==1):
                 ans[i][j]=1
            else:
                ans[i][j]=0
    return ans

def transitive(a):
    #Warshall's Algorithm
    n = len(a)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                a[i][j] = a[i][j] or (a[i][k] and a[k][j])
    return a

def main():
    aLineWeRead=None
    with open(sys.argv[1],'r') as f: 
        aLineWeRead = f.readline()
        aLineWeRead = f.readline()#to read the second line
        aLineWeRead= eval(aLineWeRead.replace("{","[").replace("}","]"))
        aLineWeRead=reflexive(aLineWeRead)
        aLineWeRead=symmetric(aLineWeRead)
        aLineWeRead=transitive(aLineWeRead)
        stringmatrix=str(aLineWeRead)
        stringmatrix=stringmatrix.replace("[","{").replace("]","}")#converting back to string to match output
        print(stringmatrix)

if __name__ == "__main__":
    main()



