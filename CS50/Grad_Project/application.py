from flask import Flask , render_template, request, redirect 
import numpy as np

app = Flask(__name__)
@app.route("/")
def index():
       return render_template("index.html")
       
@app.route("/roots")
def roots():
        return render_template("roots.html") 
@app.route("/answer", methods=["POST"])
def answer():
        coeff=[]
        counter=int(request.form.get("XX"))
        if not counter:
                return render_template("roots.html") 
        for i in range(counter+1):
                if not (request.form.get(str(i))) :
                        return render_template("roots.html") 
                coeff.append(int(request.form.get(str(i))))
        poly=np.poly1d(coeff)
        x=poly.roots
       
        return render_template("answer.html",x=x,leng=len(x))

