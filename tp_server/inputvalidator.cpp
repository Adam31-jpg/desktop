#include "inputvalidator.h"
#include <QList> // ajouté pour inclure QList
#include <QDateTime> // Added for QDateTime

// Vérifie la validité du nom de fichier
bool validateFileName(const QString& fileName) {
    // Code de validation de nom de fichier
    return !fileName.isEmpty();
}
// Vérifie la validité du type de fichier
bool validateFileType(const QString& fileType) {
    // Code de validation de type de fichier
    return fileType == "exec" || fileType == "text" || fileType == "image" || fileType == "audio" ||fileType == "video" || fileType == "archive";
}

// Vérifie la validité du type de fichier et l'extension qui lui correspond
bool validateFileTypeAndExtension(const QString& fileType, const QString& fileExtension) {
    // Code de validation de type de fichier
    if (fileType == "exec") {
        return fileExtension == "sh" || fileExtension == "jar";
    } else if (fileType == "text") {
        return fileExtension == "txt" || fileExtension == "pdf" || fileExtension == "doc" || fileExtension == "docx";
    } else if (fileType == "image") {
        return fileExtension == "png" || fileExtension == "jpg" || fileExtension == "gif" || fileExtension == "bmp" || fileExtension == "tif";
    } else if (fileType == "audio") {
        return fileExtension == ".mp3";
    } else if (fileType == "video") {
        return fileExtension == "mp4" || fileExtension == "avi" || fileExtension == "mov" || fileExtension == "wmv";
    } else if (fileType == "archive") {
        return fileExtension == "zip" || fileExtension == "rar" || fileExtension == "7z" || fileExtension == "tar" || fileExtension == "gz";
    } else {
        return true;
    }
}

// Vérifie la validité de l'extension de fichier
bool validateFileExtension(const QString& fileExtension) {
    // Code de validation d'extension de fichier
    return fileExtension == "sh" || fileExtension == "jar" || fileExtension == "txt" ||
           fileExtension == "png" || fileExtension == "jpg" || fileExtension == "pdf" ||
           fileExtension == "doc" || fileExtension == "docx" || fileExtension == "xls" ||
           fileExtension == "xlsx" || fileExtension == "ppt" || fileExtension == "pptx" ||
           fileExtension == "mp3" || fileExtension == "mp4" || fileExtension == "avi" ||
           fileExtension == "mov" || fileExtension == "wmv" || fileExtension == "gif" ||
           fileExtension == "bmp" || fileExtension == "tif" || fileExtension == "zip" ||
           fileExtension == "rar" || fileExtension == "7z" || fileExtension == "tar" || fileExtension == "gz";
}


bool validateDate(const QString& Date) {
    // Vérifie la validité des dates
    QDateTime DateTime = QDateTime::fromString(Date, "dd/MM/yyyy");
        return DateTime.isValid();
}

//bool validateDateRange(const QString& minDate, const QString& maxDate) {
//    // Vérifie si la date minimale est inférieure ou égale à la date maximale
//    return minDateTime <= maxDateTime;
//}


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
    QString fileExtensionValue = "";
    QString fileTypeValue = "";// initialiser à une valeur par défaut
    QString MinDateValue = "";// initialiser à une valeur par défaut
    QString MaxDateValue = "";
    QString MinSizeValue = "";
    QString MaxSizeValue = "";// initialiser à une valeur par défaut
    for (const auto& token : tokens) {
        switch (token.type) {
            case TokenType::FileName:
                isValid = isValid && validateFileName(token.value);
                qDebug() << "FileName input:" << isValid;
                break;
            case TokenType::FileType:
                fileTypeValue = token.value;
                isValid = isValid && validateFileType(token.value);
                qDebug() << "token.value" << token.value;
                qDebug() << "FileType input:" << isValid;
                break;
            case TokenType::FileExtension:
                fileExtensionValue = token.value; // mettre à jour la valeur de la variable
                isValid = isValid && validateFileExtension(token.value);
                qDebug() << "FileExtension input:" << isValid;
                break;
            case TokenType::MinDate:
                MinDateValue = token.value;
                isValid = isValid && validateDate(token.value);
                qDebug() << "MinDate input:" << isValid;
                break;
            case TokenType::MaxDate:
                MaxDateValue = token.value;
                isValid = isValid && validateDate(token.value);
                qDebug() << "MaxDate input:" << isValid;
                break;
            case TokenType::MinFileSize:
                MinSizeValue = token.value;
                isValid = isValid && validateMinFileSize(token.value.toLongLong());
                qDebug() << "MinFileSize input:" << isValid;
                break;
            case TokenType::MaxFileSize:
                MaxSizeValue  = token.value;
                isValid = isValid && validateMaxFileSize(token.value.toLongLong());
                qDebug() << "MaxFileSize input:" << isValid;
                break;
            default:
                // Token invalide
                break;
        }
    }
    return isValid;
}
