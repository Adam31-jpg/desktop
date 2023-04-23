#include "lexer.h"
#include <QDebug>
#include <QRegularExpression>
#include "inputvalidator.h"


Lexer::Lexer(const QString& input) : input(input) {}

QVector<Token> Lexer::tokenize() {
    QVector<Token> tokens;

    // Regular expression to extract the information from the input string
    QRegularExpression regex("([^;]+);([^;]+);([^;]+);(\\d+);(\\d+);(\\d{2}/\\d{2}/\\d{4});(\\d{2}/\\d{2}/\\d{4})");
    QRegularExpressionMatch match = regex.match(input);
    if (!match.hasMatch()) {
        qDebug() << "Invalid input:" << input;
        return tokens;
    }

    QString FileName = match.captured(1);
    QString FileType = match.captured(2);
    QString FileExtension = match.captured(3);
    qint64 MinFileSize = match.captured(4).toLongLong();
    qint64 MaxFileSize = match.captured(5).toLongLong();
    QString MinDate = match.captured(6);
    QString MaxDate = match.captured(7);

    // Create a token for each information extracted from the input string
    tokens.append(Token(TokenType::FileName, FileName));
    tokens.append(Token(TokenType::FileType, FileType));
    tokens.append(Token(TokenType::FileExtension, FileExtension));
    tokens.append(Token(TokenType::MinFileSize, QString::number(MinFileSize)));
    tokens.append(Token(TokenType::MaxFileSize, QString::number(MaxFileSize)));
    tokens.append(Token(TokenType::MinDate, MinDate));
    tokens.append(Token(TokenType::MaxDate, MaxDate));
    if (!validateInput(tokens)) {
           qDebug() << "Probleme input:" << input;
           return QVector<Token>();
       }

    return tokens;
}
