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
    return fileType == "exec" || fileType == "text" || fileType == "image" || fileType == "audio" ||fileType == "video" || fileType == "archive" || fileType == "unknown" || fileType == "all";
}

// Vérifie la validité du type de fichier et l'extension qui lui correspond
bool validateFileTypeAndExtension(const QString& fileType, const QString& fileExtension) {
    // Code de validation de type de fichier
    if (fileExtension != "all") {
        if (fileType == "exec") {
            return fileExtension == "sh" || fileExtension == "jar" || fileExtension == "url"|| fileExtension == "lnk" || fileExtension == "exe";
        } else if (fileType == "text") {
            return fileExtension == "txt" || fileExtension == "pdf" || fileExtension == "doc" || fileExtension == "docx" || fileExtension == "json" || fileExtension == "lock";
        } else if (fileType == "image") {
            return fileExtension == "png" || fileExtension == "jpg" || fileExtension == "gif" || fileExtension == "bmp" || fileExtension == "tif" || fileExtension == "jpeg";
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
    return true;
}

// Vérifie la validité de l'extension de fichier
bool validateFileExtension(const QString& fileExtension) {
    // Code de validation d'extension de fichier
    return fileExtension == "url"|| fileExtension == "lnk"|| fileExtension == "sh" || fileExtension == "jar" || fileExtension == "txt" ||
           fileExtension == "png" || fileExtension == "jpg" || fileExtension == "pdf" ||
           fileExtension == "doc" || fileExtension == "docx" || fileExtension == "xls" ||
           fileExtension == "xlsx" || fileExtension == "ppt" || fileExtension == "pptx" ||
           fileExtension == "mp3" || fileExtension == "mp4" || fileExtension == "avi" ||
           fileExtension == "mov" || fileExtension == "wmv" || fileExtension == "gif" ||
           fileExtension == "bmp" || fileExtension == "tif" || fileExtension == "zip" ||
           fileExtension == "rar" || fileExtension == "7z" || fileExtension == "tar" || fileExtension == "gz" || fileExtension == "all";
}


bool validateDate(const QString& Date) {
    // Vérifie la validité des dates
    QDateTime DateTime = QDateTime::fromString(Date, "dd/MM/yyyy");
        return DateTime.isValid();
}

bool validateDateRange(const QString& minDate, const QString& maxDate) {
    // Vérifie si la date minimale est inférieure ou égale à la date maximale
    return minDate <= maxDate;
}

bool validateSizeRange(const QString& minFileSize, const QString& maxFileSize) {
    // Vérifie si la size minimale est inférieure ou égale à la size maximale
    return minFileSize <= maxFileSize;
}
// Vérifie la validité de la taille minimale de fichier
bool validateMinFileSize(qint64 minFileSize) {
    // Code de validation de taille minimale de fichier
    return minFileSize >= 0;
}

bool validateCorrelation(const QString& fileType, const QString& fileExtension, const QString& minDate, const QString& maxDate,const QString& minFileSize, const QString& maxFileSize) {
    return validateDateRange(minDate,maxDate) && validateFileTypeAndExtension(fileType,fileExtension) && validateSizeRange(minFileSize, maxFileSize);
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
    QString MaxDateValue = "";// initialiser à une valeur par défaut
    QString MinSizeValue = "";// initialiser à une valeur par défaut
    QString MaxSizeValue = "";// initialiser à une valeur par défaut
    for (const auto& token : tokens) {
        switch (token.type) {
            case TokenType::FileName:
                isValid = isValid && validateFileName(token.value);
                break;
            case TokenType::FileType:
                fileTypeValue = token.value;
                isValid = isValid && validateFileType(token.value);
                break;
            case TokenType::FileExtension:
                fileExtensionValue = token.value; // mettre à jour la valeur de la variable
                isValid = isValid && validateFileExtension(token.value);
                break;
            case TokenType::MinDate:
                MinDateValue = token.value;
                isValid = isValid && validateDate(token.value);
                break;
            case TokenType::MaxDate:
                MaxDateValue = token.value;
                isValid = isValid && validateDate(token.value);
                break;
            case TokenType::MinFileSize:
                MinSizeValue = token.value;
                isValid = isValid && validateMinFileSize(token.value.toLongLong());
                break;
            case TokenType::MaxFileSize:
                MaxSizeValue  = token.value;
                isValid = isValid && validateMaxFileSize(token.value.toLongLong());
                break;
            default:
                // Token invalide
                break;
        }
    }
    isValid = isValid && validateCorrelation(fileExtensionValue,fileTypeValue, MinDateValue,MaxDateValue,MinSizeValue,MaxSizeValue);
    return isValid;
}
