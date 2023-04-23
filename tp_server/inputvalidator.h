#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QString>
#include <QList>
#include "lexer.h"

bool validateFileName(const QString& fileName);
bool validateFileType(const QString& fileType, const QString& fileExtension);
bool validateFileExtension(const QString& fileExtension);
bool validateDate(const QString& minDate, const QString& maxDate);
bool validateMinFileSize(qint64 minFileSize);
bool validateMaxFileSize(qint64 maxFileSize);
bool validateInput(const QList<Token>& tokens);

#endif // INPUTVALIDATOR_H

