#include "lexer.h"
#include <QDebug>
#include <QRegularExpression>


Lexer::Lexer(const QString& input) : input(input) {}

QVector<Token> Lexer::tokenize() {
    QVector<Token> tokens;

    // Regular expressions to extract each type of token
    QRegularExpression fileNameRegex("\"([^\"]+)\"");
    QRegularExpression fileTypeRegex("type:(\\S+)");
    QRegularExpression fileExtensionRegex("extension:(\\S+)");
    QRegularExpression dateRegex("date:(\\S+)");
    QRegularExpression minFileSizeRegex("minsize:(\\d+)");
    QRegularExpression maxFileSizeRegex("maxsize:(\\d+)");

    // Traverse the input string to extract the tokens
    int pos = 0;
    while (pos < input.size()) {
        // Try to extract each type of token in the following order:
        // file name, file type, file extension, date,
        // minimum file size, maximum file size
        bool found = false;
        for (const auto& regex : {fileNameRegex, fileTypeRegex, fileExtensionRegex,
                                  dateRegex, minFileSizeRegex, maxFileSizeRegex}) {
            QRegularExpressionMatch match = regex.match(input, pos);
            if (!match.hasMatch()) {
                qDebug() << "Invalid input at position" << pos;
                return {};
            }
            int matchPos = match.capturedStart();

            if (matchPos != -1) {
                TokenType type;
                if (&regex == &fileNameRegex) {
                    type = TokenType::FileName;
                } else if (&regex == &fileTypeRegex) {
                    type = TokenType::FileType;
                } else if (&regex == &fileExtensionRegex) {
                    type = TokenType::FileExtension;
                } else if (&regex == &dateRegex) {
                    type = TokenType::Date;
                } else if (&regex == &minFileSizeRegex) {
                    type = TokenType::MinFileSize;
                } else if (&regex == &maxFileSizeRegex) {
                    type = TokenType::MaxFileSize;
                } else {
                    type = TokenType::Invalid;
                }
                tokens.append(Token(type, match.capturedTexts()[1]));
                pos = matchPos + match.capturedLength();
                found = true;
                break;
            }
        }
        if (!found) {
            qDebug() << "Invalid input at position" << pos;
            return {};
        }
    }

    return tokens;
}


