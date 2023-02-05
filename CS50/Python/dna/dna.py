import csv
import sys

def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py file.csv file.txt")

    csvfile= sys.argv[1]
    textfile= sys.argv[2]

    t = open(textfile, 'r')
    reader1= t.read()


    # matching
    lentxt= len(reader1)
    counter=0
   
    MAXES=[]

    
    indic1=0
    indic2=0
    STR=[]
    with open(csvfile) as f:
        reader2= csv.reader(f)
        for row in reader2:
            for i in range(len(row)-1):
                STR.append(row[i+1])
                indic2+=1
            if indic2 > 0:
                break
       
        for j in range(len(STR)):
            maxarray=[]
            position=0
            x=len(STR[j])
            y=round(lentxt/x)
            
            #while position < (lentxt-x+1):
            for position in [0,1,2,3,4,5,6]:    
                for k in range(y):
                    if STR[j] != reader1[position+x*k:position+x+x*k]:
                        counter=0
                        continue
                    else:
                        counter+=1
                        maxarray.append(counter)
            #print(maxarray)
            
            if len(maxarray)==0:
                maxarray.append(0)
            MAXES.append(max(maxarray))
        #print(MAXES)
        c=[]
        p=0
        for row in reader2:
            counteez=0
            for k in range(len(MAXES)):
                if MAXES[k] != int(row[k+1]):
                    break
                else:
                    counteez+=1
                    c.append(counteez)
            if counteez == len(MAXES):
                print(row[0])
        if c==[]:
            c.append(p)
        
        if max(c) < len(MAXES): 
            print("No match")
            
    
       
                
if __name__ == "__main__":
    main()
    