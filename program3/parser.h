#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <map>
using std::string;
using std::stoi;

#include "lexer.h"

extern void error(string file, int linenum, const string& message);
enum TypeForNode { INT_TYPE, STRING_TYPE, ERROR_TYPE, DECTFUNCT_TYPE, SETFUNCT_TYPE, PRINT_TYPE, ID_TYPE };

class ParseTree {
    int			linenumber;
    ParseTree	*left;
    ParseTree	*right;

public:
    ParseTree(int n, ParseTree *l = 0, ParseTree *r = 0) : linenumber(n), left(l), right(r){}
    virtual ~ParseTree() {}

    ParseTree* getLeft() const { return left; }
    ParseTree* getRight() const { return right; }
    int getLineNumber() const { return linenumber; }

    int traversalCount(int(ParseTree::*tree)()) {
        int count = 0;
        if (left){
            count += left ->traversalCount(tree);
        }
        if (right) {
            count += right -> traversalCount(tree);
        }
        return count + (this->*tree)();
    }

    int setCounte( std::map<string, int>&symbol) {
        int count = 0;
        if (left) {
            count += left -> setCounte(symbol);
        }
        if (right) {
            count =+ right -> setCounte(symbol);
        }

        return count + this -> checkBeforeSet(symbol);
    }

    int idCount(std::map<string, int> &id, string line) {
        id[line]++;
        return id.size();
    }

    virtual int checkBeforeSet(std::map<string, int>&symbol) {
        return 0;
    }
    virtual int isID() { return 0;}
    virtual int isSet() { return 0;}
    virtual int isPlus() { return 0;}
    virtual int Star() { return 0;}
    virtual TypeForNode GetType() const { return ERROR_TYPE; }
    virtual int GetIntValue() const { throw "no integer value"; }
    virtual string GetStringValue() const { throw "no string value"; }
};


class StatementList : public ParseTree {
public:
    StatementList(ParseTree *first, ParseTree *rest) : ParseTree(0, first, rest) {}

};

class DeclFunct : public ParseTree {
    string id;
public:
    DeclFunct(int line, Token& tok2, ParseTree * right) : ParseTree(line, right){
        id = tok2.GetLexeme();
    }

    TypeForNode GetType() const { return DECTFUNCT_TYPE; }
    int isID() { return 1;}
    string GetStringValue() const { return id;}
};


class SetFunct : public ParseTree {
    string id;
public:
    SetFunct(int line, Token& tok2, ParseTree *left, ParseTree *right) : ParseTree(line, left, right){
        id = tok2.GetLexeme();
    }


    //int isID() { return 1;}
    int isSet() { return 1;}
    string GetStringValue() const { return id;}
    TypeForNode GetType() const { return SETFUNCT_TYPE; }
    //string GetID() const { return id; }
};

class PrintFunct : public ParseTree {
    string id;
public:
    PrintFunct(int line, ParseTree *left, ParseTree *right) : ParseTree(line, left ,right) {
        //id =
    }

    //string GetStringValue() const { return id; }
    TypeForNode GetType() const { return PRINT_TYPE; }
};


class Addition : public ParseTree {
public:
    Addition(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {
    }

    int isPlus() { return 1;}
    // will need to fill in type and value;
    // remember type is a function of
};

class Subtraction : public ParseTree {
public:
    Subtraction(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

    // will need to fill in type and value;
    // remember type is a function of
};

class Multiplication : public ParseTree {
public:
    Multiplication(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

    int Star() { return 1;}
};

class Division :public ParseTree {
public:
    Division(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}
};

class IntegerConstant : public ParseTree {
    int	value;

public:
    IntegerConstant(const Token& tok) : ParseTree(tok.GetLinenum()) {
        value = stoi( tok.GetLexeme() );
    }

    TypeForNode GetType() const { return INT_TYPE; }
    int GetIntValue() const { return value; }
    //int isID() { return 1;}
};


class StringConstant : public ParseTree {
    string lexe;
public:
    StringConstant(const Token& tok) : ParseTree(tok.GetLinenum()){
        lexe = tok.GetLexeme();
    }

    TypeForNode GetType() const { return STRING_TYPE; }
    string GetStringValue() const { return lexe; }
};

class ID : public ParseTree {
    string id;
public:
    std::map<string, int> stuff;
    ID(const Token& tok) : ParseTree(tok.GetLinenum()){
        id = tok.GetLexeme();
        //stuff[id]++;
    }


    string GetStringValue() const { return id;}
    TypeForNode GetType() const { return ID_TYPE;}

    string GetID() const { return id; }
};

extern ParseTree *	Prog(istream* in, string fileName, std::map<string, int>&symbol);
extern ParseTree *	StmtList(istream* in);
extern ParseTree *	Stmt(istream* in);
extern ParseTree *	Decl(istream* in);
extern ParseTree *	Set(istream* in);
extern ParseTree *	Print(istream* in);
extern ParseTree *	Expr(istream* in);
extern ParseTree *	Term(istream* in);
extern ParseTree *	Primary(istream* in);
extern void  iderror(ParseTree *node);
extern bool thereIsAnError;

#endif /* PARSER_H_ */

