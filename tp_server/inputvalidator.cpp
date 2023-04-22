#include "inputvalidator.h"

#include <QDateTime> // Added for QDateTime

// Vérifie la validité du nom de fichier
bool validateFileName(const QString& fileName) {
    // Code de validation de nom de fichier
    return !fileName.isEmpty();
}

// Vérifie la validité du type de fichier
bool validateFileType(const QString& fileType) {
    // Code de validation de type de fichier
    return fileType == "image" || fileType == "text" || fileType == "exec";
}

// Vérifie la validité de l'extension de fichier
bool validateFileExtension(const QString& fileExtension) {
    // Code de validation d'extension de fichier
    return fileExtension == ".sh" || fileExtension == ".txt" || fileExtension == ".png" || fileExtension == ".jpg";
}

// Vérifie la validité de la date
bool validateDate(const QString& date) {
    // Code de validation de date
    QDateTime dateTime = QDateTime::fromString(date, "yyyy-MM-dd");
    return dateTime.isValid();
}

// Vérifie la validité de la taille minimale de fichier
bool validateMinFileSize(qint64 minFileSize) {
    // Code de validation de taille minimale de fichier
    return minFileSize >= 0;
}

// Vérifie la validité de la taille maximale de fichier
bool validateMaxFileSize(qint64 maxFileSize) {
    // Code de validation de taille maximale de fichier
    return maxFileSize > 0;
}

// Vérifie la validité de tous les champs
bool validateInput(const QList<Token>& tokens) {
    bool isValid = true;
    for (const auto& token : tokens) {
        switch (token.type) {
            case TokenType::FileName:
                isValid = isValid && validateFileName(token.value);
                break;
            case TokenType::FileType:
                isValid = isValid && validateFileType(token.value);
                break;
            case TokenType::FileExtension:
                isValid = isValid && validateFileExtension(token.value);
                break;
            case TokenType::Date:
                isValid = isValid && validateDate(token.value);
                break;
            case TokenType::MinFileSize:
                isValid = isValid && validateMinFileSize(token.value.toLongLong());
                break;
            case TokenType::MaxFileSize:
                isValid = isValid && validateMaxFileSize(token.value.toLongLong());
                break;
            default:
                // Token invalide
                break;
        }
    }
    return isValid;
}
