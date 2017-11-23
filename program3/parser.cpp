//
// Created by Owen on 10/30/2017.
//
#include <string>
#include <vector>

using std::string;

#include "parser.h"

std::map<string, bool> idmapint;
class ParserToken {
private:
    Token	tok;
    bool	pushedBack;

public:
    ParserToken() : pushedBack(false) {}

    Token getToken(istream *in) {
        if( pushedBack ) {
            pushedBack = false;
            return tok;
        }

        return ::getToken(in);
    }
    void pushbackToken(const Token& t) {
        if( pushedBack ) {
            // error
        }
        tok = t;
        pushedBack = true;
    }
} ParserToken;

string file;

void error(const string& msg)
{
    return;
}

// Prog ::= StmtList
ParseTree *Prog(istream* in, string fileName, std::map<string,int>&symbol)
{

    file = fileName;
    return StmtList(in);
}

// StmtList ::= {Stmt T_SC} {StmtList}
ParseTree * StmtList(istream* in) {

    ParseTree *stmt = Stmt(in);
    Token tok = ParserToken.getToken(in);

    if (stmt == 0) {
        return 0;
    }

    if (tok == T_SC) {
        return new StatementList(stmt, StmtList(in));
    }else {
        error(file, tok.GetLinenum(), "Syntax error semicolon required");
        ParserToken.pushbackToken(tok);
        return 0;
    }

    return 0;


}

// Stmt ::= Decl | Set | Print
ParseTree *	Stmt(istream* in) {

    ParseTree *set = Set(in);
    ParseTree *print = Print(in);
    ParseTree *decl = Decl(in);

    if (decl != 0) {
        return decl;
    }else if (set != 0) {
        return set;
    }else if (print != 0) {
        return print;
    }

    return 0;
}

// Decl ::= T_INT T_ID | T_STRING T_ID
ParseTree *	Decl(istream* in) {
    Token tok1 = ParserToken.getToken(in);
    //std::cout << tok1 << "\n";
    if (tok1 == T_INT) {
        Token tok2 = ParserToken.getToken(in);
        //std::cout << tok2 << "\n";

        if (tok2 == T_ID) {
            return new DeclFunct(tok2.GetLinenum(), tok2, 0);
        }else {
            ParserToken.pushbackToken(tok2);
            error(file, tok2.GetLinenum(), "Expecting an ID\n");
        }
    } else {
        ParserToken.pushbackToken(tok1);
    }

    tok1 = ParserToken.getToken(in);
    if (tok1 == T_STRING) {
        Token tok2 = ParserToken.getToken(in);
        //std::cout << tok2 << "\n";
        if (tok2 == T_ID) {
            //idmapint[tok2.GetLexeme()];
            //variableCheck[tok2.GetLexeme()];
            //ParseTree *id = new ID(tok2);
            return new DeclFunct(tok2.GetLinenum(), tok2, 0);
        } else {
            ParserToken.pushbackToken(tok2);
            error(file, tok2.GetLinenum(), "need id\n");
        }
    } else {
        ParserToken.pushbackToken(tok1);
    }

    return 0;
}

// Set ::= T_SET T_ID Expr
ParseTree *	Set(istream* in) {
    //check if token is T_SET
    //check if token is T_ID
    //check if Expr is returned


    Token tok1 = ParserToken.getToken(in);
     //std:: cout << tok1 << "\n";
    if (tok1 == T_SET) {
        Token tok2 = ParserToken.getToken(in);
        //std:: cout << tok2 << "\n";
        if (tok2 == T_ID) {

            //idmapint[tok2.GetLexeme()];
            ParseTree *expr = Expr(in);
            if ( expr == 0) {
               error(file, tok2.GetLinenum(), "Syntax error expression required\n");
            }else {
                //std::cout<<tok2.GetLexeme()<< std::endl;
                return new SetFunct(tok2.GetLinenum(), tok2, expr, 0);
            }
            //std::cout << "were here \n";


        } else {
            ParserToken.pushbackToken(tok2);
            error(file, tok2.GetLinenum(), "expected id after set\n");
        }
    } else {
        ParserToken.pushbackToken(tok1);
    }

    return 0;
}

// Print ::= T_PRINT Expr | T_Println Expr

ParseTree *	Print(istream* in) {

    Token tok = ParserToken.getToken(in);

    /*
    if(tok != T_PRINT && tok != T_PRINTLN) {
        ParserToken.pushbackToken(tok);
        return 0;
    }
    */

    if (tok == T_PRINT) {
        ParseTree *expr = Expr(in);
        if (expr == 0) {
            error(file, tok.GetLinenum(), "Syntax error expression required");
            return 0;
        }  else {
            return new PrintFunct(tok.GetLinenum(), expr, 0);
        }
    }else if (tok == T_PRINTLN) {
        ParseTree *expr = Expr(in);
        if (expr == 0) {
            error(file, tok.GetLinenum(), "Syntax error expression required");
            return 0;
        } else {
            return new PrintFunct(tok.GetLinenum(), expr, 0);
        }
    } else {
        ParserToken.pushbackToken(tok);
        return 0;
    }

    return 0;
}

// Expr ::= Term{(T_PLUS | T_MINUS) Expr}
ParseTree *Expr(istream* in) {
    ParseTree *t1 = Term(in);
    if( t1 == 0 ) {
        return 0;
    }


    for(;;) {
        Token op = ParserToken.getToken(in);
        if( op != T_PLUS && op != T_MINUS ) {
            //std::cout << "in Expr return t1 \n";
            ParserToken.pushbackToken(op);
            return t1;
        }

        ParseTree *t2 = Expr(in);
        if( t2 == 0) {
            error(file, op.GetLinenum(), "expression required after + or - operator\n");
            return 0;
        }

        // combine t1 and t2 together
        if( op == T_PLUS )
            t1 = new Addition(op.GetLinenum(), t1, t2);
        else
            t1 = new Subtraction(op.GetLinenum(), t1, t2);
    }

    // should never get here...
    return 0;
}

// Term ::= Primary {(T_STAR | T_SLASH) Term}
ParseTree *	Term(istream* in) {

    //std::cout << "in Term \n";

    ParseTree *prim = Primary(in);
    //std::cout << prim << "\n";
    if (prim == 0) {
        return 0;
    }

    for (;;) {
        Token op = ParserToken.getToken(in);
        if (op != T_STAR && op != T_SLASH) {
            ParserToken.pushbackToken(op);
            return prim;
        }

        ParseTree *t1 = Term(in);
        if (t1 == 0) {
            error(file, op.GetLinenum(), "term required after * or / opperaor\n");
        }

        //do * or /
        if (op == T_STAR) {
            prim = new Multiplication(op.GetLinenum(), prim, t1);
        }else {
            prim = new Division(op.GetLinenum(), prim, t1);
        }
    }


    return 0;

}

// Primary ::= T_ICONST | T_SCONST | T_ID | T_LPAREN Expr T_RPAREN
ParseTree *	Primary(istream* in) {

    Token tok = getToken(in);
    //std::cout<< tok << "\n";

    if (tok == T_ICONST) {
        return new IntegerConstant(tok);
    } else if(tok == T_SCONST) {
        return new StringConstant(tok);
    } else if (tok == T_ID) {
        return new ID(tok);
    }else if (tok == T_LPAREN){
        ParseTree *expr = Expr(in);
        Token rparen = ParserToken.getToken(in);
        if (rparen != T_RPAREN) {
            error(file, tok.GetLinenum(), "Syntax error right paren expected\n");
            ParserToken.pushbackToken(rparen);
            return 0;
        } else {
            return expr;
        }
    }else {
        error(file, tok.GetLinenum(), "Syntax error primary expected\n");
        return 0;}

    return 0;
}

bool thereIsAnError = false;
//int idErrorCount = 0;
void iderror(ParseTree *Node) {

    if (Node != 0) {
        //std::cout<< "not 0";
        iderror(Node->getLeft());
        iderror(Node->getRight());

        if (Node->GetType() == DECTFUNCT_TYPE) {
            //std::cout << "in int\n";
            //std::cout << Node->GetStringValue() << std::endl;

            if (idmapint.find(Node->GetStringValue()) == idmapint.end() ) {
                string val = Node->GetStringValue();
                idmapint[Node->GetStringValue()] = true;
                //std::cout<<"added to map\n";
            } else {
                thereIsAnError = true;
                error(file, Node->getLineNumber(), "variable " + Node->GetStringValue() +
                                                   " was already declared");
            }
        } else if (Node->GetType() == SETFUNCT_TYPE) {
            //std::cout << "in set\n";
            //std::cout << Node->GetStringValue() << std::endl;
            if (idmapint.find(Node->GetStringValue()) == idmapint.end() ) {
                thereIsAnError = true;
                error(file, Node->getLineNumber(), "variable " + Node->GetStringValue() +
                        " is used before being declared");
            }

        } else if (Node->GetType() == ID_TYPE ){
            //std::cout << "in id type\n";

            //std::cout << Node->GetStringValue() << std::endl;

            if (idmapint.find(Node->GetStringValue()) == idmapint.end()) {
                //error it is used before it is declared
                //idErrorCount++;
                thereIsAnError = true;
                error(file, Node->getLineNumber(),
                      "variable " + Node->GetStringValue() + " is used before being declared");
                //std::cout<< "in id type\n";
            }
        }

    }
}