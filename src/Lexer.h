#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <istream>
//#include <vector>
#include <memory>
#include <unordered_map>
#include "Token.h"
#include "TokenTables.h"

namespace compiler {
    class Lexer {
    private:
        /*
         * �������� ������
         */
        std::string buffer;
        int position; //������� ������� � �������� ������

        int line;
        int last_position;

        static constexpr char ENDING_CHAR = '$'; // ������ ����� �����

        std::istream *fin;

        /*
         * ����� ����� � ��������� �������,
         * ������������ ��� �������� ������
         */
        static const std::unordered_map<std::string, Token> keyWordTokens;

        std::shared_ptr<Token> foundToken;

        void loadLine();

        inline bool isNumeric(char ch) {
            return ch >= '0' && ch <= '9';
        }

        inline bool isLetter(char ch) {
            return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
        }

        inline bool isWhitespace(char ch) {
            return ((std::string) "\r\n\t ").find(ch) != -1;
        }

        inline bool isOperator(char ch) {
            return ((std::string) "=+-*/^()[]{}<>").find(ch) != -1;
        }

    public:

        std::shared_ptr<TokenTables> tables;

        Token nextToken();

        Token lookForToken();

        int getPosition() const;
        int getLastTokenPosition() const;
        int getLine() const;
//    void scan(std::vector<std::shared_ptr<Token>>& vect);


        Lexer(const std::string &str, const std::shared_ptr<TokenTables>& tables);

        Lexer(std::istream &fin, const std::shared_ptr<TokenTables>& tables);

//    void initString(const std::string &str);
//    void initStream(std::istream &fin);
    };
}


#endif // COMPILER_LEXER_H
