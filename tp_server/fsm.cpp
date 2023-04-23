#include "fsm.h"
#include <QList>
#include <qDebug>

bool parseInput(const QList<Token>& tokens)
{
    State state = State::Initial;
    for (const Token& token : tokens) {
        switch (state) {
        case State::Initial:
            if (token.type == TokenType::FileName) {
                state = State::FileName;
                qDebug() << "filename";
            } else {
                state = State::Error;
                qDebug() << "error";
            }
            break;
        case State::FileName:
            if (token.type == TokenType::FileExtension) {
                state = State::FileExtension;
            } else if (token.type == TokenType::FileType) {
                state = State::FileType;
            } else if (token.type == TokenType::MinDate) {
                state = State::MinDate;
            } else if (token.type == TokenType::MinFileSize) {
                state = State::MinFileSize;
            } else {
                state = State::Error;
            }
            break;
        case State::FileType:
            if (token.type == TokenType::FileExtension) {
                state = State::FileExtension;
            } else if (token.type == TokenType::MaxDate) {
                state = State::MaxDate;
            } else if (token.type == TokenType::MaxFileSize) {
                state = State::MaxFileSize;
            } else {
                state = State::Error;
            }
            break;
        case State::FileExtension:
            if (token.type == TokenType::MinDate) {
                state = State::MinDate;
            } else if (token.type == TokenType::MinFileSize) {
                state = State::MinFileSize;
            } else if (token.type == TokenType::MaxDate) {
                state = State::MaxDate;
            } else if (token.type == TokenType::MaxFileSize) {
                state = State::MaxFileSize;
            } else {
                state = State::Error;
            }
            break;
        case State::MinDate:
            if (token.type == TokenType::MaxDate) {
                state = State::MaxDate;
            } else {
                state = State::Error;
            }
            break;
        case State::MaxDate:
            if (token.type == TokenType::MinFileSize) {
                state = State::MinFileSize;
            } else if (token.type == TokenType::MaxFileSize) {
                state = State::MaxFileSize;
            } else {
                state = State::Error;
            }
            break;
        case State::MinFileSize:
            if (token.type == TokenType::MaxFileSize) {
                state = State::MaxFileSize;
            } else {
                state = State::Error;
            }
            break;
        case State::MaxFileSize:
            state = State::Error;
            break;
        case State::Error:
            return false;
        }
    }
    return state != State::Error;
}
