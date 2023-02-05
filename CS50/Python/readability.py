from cs50 import get_string


def main():
    text = get_string("Text: ") 
    letters= count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    grade = calculate_grade(letters, words, sentences)   
    
    if grade <= 0:
        print("Before Grade 1")  
    
    elif grade < 16:
    
        print(f"Grade {grade}")
    
    else:
    
        print("Grade 16+")

def count_letters(word):
    n=len(word)
    B=0
    for i in range(n):
        if (word[i] >= 'A' and word[i] <='Z') or (word[i] >= 'a' and word[i] <= 'z'):
            B=B+1
    print(B)
    return B 

def count_words(word):
    c= 0
    n=len(word)
    for i in range(n):
        if word[i]==' ' or word[i]=='\0':
            c=c+1
    
    print(c+1)  
    return c+1 

def count_sentences(word):
    d= 0
    n=len(word)
    for i in range(n):
        if word[i]=='.' or word[i]=='!' or word[i]=='?':
            d=d+1
    print(d)
    return d 
    
def calculate_grade(l,w,s):

    letters= (l*100) /float(w) 
    sentences= (s*100) /float(w) 
    index= 0.0588 *  letters - 0.296 * sentences - 15.8 
    I=round(index)

    return I 

if __name__ == "__main__":
    main()



