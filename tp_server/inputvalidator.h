#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QString>
#include <QList>
#include "Token.h"

class InputValidator
{
public:
    InputValidator();

    // Vérifie la validité du nom de fichier
    static bool validateFileName(const QString& fileName);

    // Vérifie la validité du type de fichier
    static bool validateFileType(const QString& fileType);

    // Vérifie la validité de l'extension de fichier
    static bool validateFileExtension(const QString& fileExtension);

    // Vérifie la validité de la date
    static bool validateDate(const QString& date);

    // Vérifie la validité de la taille minimale de fichier
    static bool validateMinFileSize(qint64 minFileSize);

    // Vérifie la validité de la taille maximale de fichier
    static bool validateMaxFileSize(qint64 maxFileSize);

    // Vérifie la validité de tous les champs
    static bool validateInput(const QList<Token>& tokens);
};

#endif // INPUTVALIDATOR_H
