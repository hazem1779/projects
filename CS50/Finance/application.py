import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application


app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)
# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")



@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    sums=[]
    s=[]
    count_share=[]
    symbols= db.execute("SELECT DISTINCT symbol FROM stocks")
    for symbol in symbols:
        s.append(symbol['symbol'])
        
        sumz= db.execute("SELECT SUM(shares_value) FROM stocks WHERE symbol =?",symbol['symbol'] )
        sums.append(sumz[0]['SUM(shares_value)'])
        
        count= db.execute("SELECT SUM(shares) FROM stocks WHERE symbol =?",symbol['symbol'])
        count_share.append(count[0]['SUM(shares)'])
        l=len(s)
    actual= db.execute("SELECT rest FROM stocks ORDER BY id DESC LIMIT 1")
    actual_cash=actual[0]['rest']
    return render_template("index.html",l=l , s=s,count_share=count_share, sums=sums, actual_cash=actual_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        username = session.get("username")
        lol= request.form.get("symbol")
        lmao=lookup(lol)

        if not lmao:
            return apology("EL lol", 400)
        if not request.form.get("shares"):
            return apology("EL lol", 400)

        shares=floa(request.form.get("shares"))
        
        if shares < 0 :
            return apology("EL lol positive", 400)
        
        shares_value= shares * int(lmao['price'])
        symbol=lmao['symbol']
        cash = db.execute("SELECT cash FROM users WHERE username = ?", username)
        rest=cash[0]['cash']-shares_value
        if rest < 0:
            return apology("you dont have enough cash", 400)
        else:
            rows = db.execute("INSERT INTO stocks (username, shares, shares_value, cash, symbol, rest) VALUES(?, ?, ?, ?, ?, ?)",username, shares, shares_value, cash[0]['cash'], symbol, rest)
            db.execute("UPDATE users SET cash= ? WHERE username = ?", rest, username)
            #stocks=db.execute("SELECT * FROM stocks ORDER BY id DESC LIMIT 1")
            #return redirect('/')
            return render_template("bought.html",symbol=symbol, price=float(lmao['price']), shares_value=shares_value)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    username = session.get("username")
    tables=db.execute("SELECT * FROM stocks WHERE username = ?", username)
    return render_template("history.html",tables=tables)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"]=request.form.get("username")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")




@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol= request.form.get("symbol")
        text=lookup(symbol)
        if not text:
            return apology("Symbol not found", 400)
        else:
            name=text['name']
            symbol=text['symbol']
            price=text['price']
            return render_template("post_quote.html",name=name,symbol=symbol,price=price)
            #@app.route("/post_quote")
            #def post_quote():
             #   return render_template("post_quote.html",text=Text)
            #return redirect("/post_quote")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Ensure username was submitted
        username=request.form.get("username")
        password=request.form.get("password")
        confirm_password=request.form.get("confirmation")
        
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)
        # Ensure password was confirmed
        elif not confirm_password:
            return apology("must confirm password", 400)


        elif confirm_password != password:
            return apology("password doesn't match", 400)


        check = db.execute("SELECT username FROM users WHERE username = ?", username)
        if check:
            ah=check[0]['username']
            if username == ah:
                return apology("username already exists!", 400)
        else:
            rows = db.execute("INSERT INTO users (username,hash) VALUES(?, ?)", username, generate_password_hash(password))
        return redirect ('/')
    # User reached route via GET (as by clicking a link or via redirect
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    username = session.get("username")
    if request.method == "POST":
        symbol= request.form.get("symbol")
        S=lookup(symbol)

        if not S:
            return apology("EL lol", 400)
        if not request.form.get("shares"):
            return apology("EL lol", 400)

        shares=int(request.form.get("shares"))
        if shares <= 0:
            return apology("EL lol positive", 400)

        shares_value= shares * int(S['price'])
        symbol=S['symbol']
        cash = db.execute("SELECT cash FROM users WHERE username = ?", username)
        rest=cash[0]['cash']+shares_value
        rows = db.execute("INSERT INTO stocks (username, shares, shares_value, cash, symbol, rest) VALUES(?, ?, ?, ?, ?, ?)",username, -1 * shares, -1 * shares_value, cash[0]['cash'], symbol, rest)
        db.execute("UPDATE users SET cash= ? WHERE username = ?", rest, username)
        return redirect("/")
    else:
        symbols=db.execute("SELECT DISTINCT symbol FROM stocks WHERE username = ?", username)
        return render_template("sell.html",symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
