#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QDir>
#include "lexer.h"

void SqlConnexion(); // Declaration of the SqlConnexion function
QList<QString>  ReturnSqlData(const QList<Token>& tokens); // Declaration of the SqlConnexion function

#endif // SQLDATABASE_H
