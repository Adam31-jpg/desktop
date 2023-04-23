#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QString>
#include <QList>
#include "lexer.h"

bool validateFileName(const QString& fileName);
bool validateFileType(const QString& fileType);
bool validateFileTypeAndExtension(const QString& fileType, const QString& fileExtension);
bool validateFileExtension(const QString& fileExtension);
bool validateDate(const QString& Date);
bool validateDateRange(const QString& minDate, const QString& maxDate);
bool validateSizeRange(const qint64& minFileSize, const qint64& maxFileSize);
bool validateCorrelation(const QString& fileType, const QString& fileExtension, const QString& minDate, const QString& maxDate,const qint64& minFileSize, const qint64& maxFileSize);
bool validateInput(const QList<Token>& tokens);

#endif // INPUTVALIDATOR_H
