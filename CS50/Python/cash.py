from cs50 import get_float
while True:
    dollars= get_float("Change owned:")
    if dollars > 0:
        break
    
n= round(dollars*100)
i= 0
while n>=25:
    n=n-25
    i=i+1
while n>=10:
    
    n=n-10
    i=i+1
while n>=5:
    
    n=n-5
    i=i+1
    
while n>=1:
    
    n=n-1
    i=i+1
    
print(i)
        