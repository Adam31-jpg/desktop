#ifndef LEXER_H
#define LEXER_H

#include <QString>
#include <QVector>
#include <QDebug>

// The different possible token types
enum class TokenType {
    Invalid, // Invalid token
    FileName, // File name
    FileType, // File type (image, text, executable)
    FileExtension, // File extension (.txt, .sh, etc.)
    MinDate,
    MaxDate,
    MinFileSize, // Minimum file size
    MaxFileSize // Maximum file size
};

// A token consists of a type and a value
struct Token {
    TokenType type;
    QString value;

    Token(TokenType t, const QString& v) : type(t), value(v) {}
};


// A class that performs lexical analysis of an input string and returns the list of corresponding tokens
class Lexer {
public:
    explicit Lexer(const QString& input);
    QVector<Token> tokenize();
private:
    QString input;
};

#endif // LEXER_H
