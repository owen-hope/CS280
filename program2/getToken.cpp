//
// Created by Owen on 10/21/2017.
//
#include "lexer.h"
#include <map>


using namespace std;
map<TokenType, string> tokenMap;

ostream& operator<<(ostream& out, const Token& tok){

    tokenMap[T_INT] = "T_INT";
    tokenMap[T_STRING] = "T_STRING";
    tokenMap[T_SET] = "T_SET";
    tokenMap[T_PRINT] = "T_PRINT";
    tokenMap[T_PRINTLN] = "T_PRINTLN";
    tokenMap[T_ID] = "T_ID";
    tokenMap[T_ICONST] = "T_ICONST";
    tokenMap[T_SCONST] = "T_SCONST";
    tokenMap[T_PLUS] = "T_PLUS";
    tokenMap[T_MINUS] = "T_MINUS";
    tokenMap[T_STAR] = "T_STAR";
    tokenMap[T_SLASH] = "T_SLASH";
    tokenMap[T_LPAREN] = "T_LPAREN";
    tokenMap[T_RPAREN] = "T_RPAREN";
    tokenMap[T_SC] = "T_SC";
    tokenMap[T_ERROR] = "T_ERROR";
    tokenMap[T_DONE] = "T_DONE";

    if (tokenMap[tok.GetTokenType()] == "T_ID" || tokenMap[tok.GetTokenType()] == "T_ICONST" ||
        tokenMap[tok.GetTokenType()] == "T_SCONST" || tokenMap[tok.GetTokenType()] == "T_ERROR") {
        out << tokenMap[tok.GetTokenType()] << "(" << tok.GetLexeme() << ")";
    } else {
        out << tokenMap[tok.GetTokenType()];
    }
    return out;
}

Token getToken(istream* br) {


    //int lineNumber = 0;
    char c = br -> peek();
    string nextChar, lexeme, keyWord, error;
    //cout << c << endl;

    while (c != EOF) {
        c = br -> get();
        //KeyWord check
        //cout << "top of while loop get token" << endl;
        //cout << c << endl;
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            lexeme += c;

            //while loop for keyWords
            while ((br->peek() >= 'a' && br->peek() <= 'z')) {
                lexeme += br->peek();
                c = br->get();

            }
            if (lexeme == "set") {
                return Token(T_SET);
            } else if (lexeme == "int") {
                return Token(T_INT);
            } else if (lexeme == "string") {
                return Token(T_STRING);
            } else if (lexeme == "print") {
                return Token(T_PRINT);
            } else if (lexeme == "println") {
                return Token(T_PRINTLN);
            }

            //while loop for ID
            while (((br->peek() >= 'a' && br->peek() <= 'z') || (br->peek() >= 'A' && br->peek() <= 'Z') ||
                    (br->peek() >= '0' && br->peek() <= '9'))) {
                lexeme += br -> peek();
                c = br->get();

            }
            return Token(T_ID, lexeme);

        } else if ((c >= '0' && c <= '9')) {
            lexeme += c;
            while ((br->peek() >= '0' && br->peek() <= '9')) {
                c = br->get();
                lexeme += c;
            }
            //cout << c << endl;
            if(br->peek() == ' ') {
                return Token(T_ICONST, lexeme);
            } else if (!(br->peek() >= '0' && br -> peek() <= '9')) {
                if (br-> peek() == '+') {
                    return Token(T_PLUS);
                } else if (br -> peek() == ';') {
                    return Token(T_SC);
                } else {
                    error += br->peek();
                    return Token(T_ERROR, error);
                }
            }

        } else if ((c == '"')) {
            lexeme += c;
            //cout << "in string const\n";
            while ((br -> peek() != '"')) {
                lexeme += br -> peek();
                //cout << br -> peek();
                //cout << lexeme <<endl;
                c = br->get();
                //cout << lexeme << endl;
                if (br -> peek() == '\n'){
                    lexeme += br -> peek();
                    return Token(T_ERROR, lexeme);
                }
            }
            if (br ->peek() == '"') {
                lexeme += br -> get();
                return Token(T_SCONST, lexeme);
            }
        } else if ((c == '/')) {
            if (br -> peek() != '/') {
                return Token(T_SLASH);
            } else if (br -> peek() == '/') {
                c = br ->get();
                while (br -> get() != '\n' || br ->get() == EOF) {
                    if (br ->get() == EOF) {
                        return Token(T_DONE);
                    }else {
                        c = br -> get();
                    }
                }
            }
        } else if ((c == '(')) {
            return Token(T_LPAREN);
        } else if ((c == ')')) {
            return Token(T_RPAREN);
        } else if ((c == '+')) {
            return Token(T_PLUS);
        } else if ((c == '-')) {
            return Token(T_MINUS);
        } else if ((c == '*')) {
            return Token(T_STAR);
        } else if ((c == ';')) {
            return Token(T_SC);
        }

    }


    if (c == EOF) {
        return Token(T_DONE);
    }

    return Token(T_DONE);
}

