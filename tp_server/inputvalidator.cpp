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
ValidationResult validateFileTypeAndExtension(const QString& fileType, const QString& fileExtension, State& currentState) {
    // Code de validation de type de fichier
    if (currentState > State::FileTypexFileExtension) {
        qDebug() << "State Error : FileTypexFileExtension";
        currentState = State::Error;
        return { false, currentState };
    }
    bool isValid = true;
    if (fileExtension != "all") {
        if (fileType == "exec") {
            isValid = fileExtension == "sh" || fileExtension == "jar" || fileExtension == "url"|| fileExtension == "lnk" || fileExtension == "exe";
        } else if (fileType == "text") {
            isValid = fileExtension == "txt" || fileExtension == "pdf" || fileExtension == "doc" || fileExtension == "docx" || fileExtension == "json" || fileExtension == "lock";
        } else if (fileType == "image") {
            isValid = fileExtension == "png" || fileExtension == "jpg" || fileExtension == "gif" || fileExtension == "bmp" || fileExtension == "tif" || fileExtension == "jpeg";
        } else if (fileType == "audio") {
            isValid = fileExtension == ".mp3";
        } else if (fileType == "video") {
            isValid = fileExtension == "mp4" || fileExtension == "avi" || fileExtension == "mov" || fileExtension == "wmv";
        } else if (fileType == "archive") {
            isValid = fileExtension == "zip" || fileExtension == "rar" || fileExtension == "7z" || fileExtension == "tar" || fileExtension == "gz";
        }
        if (!isValid) {
            currentState = State::Error;
            qDebug() << "State Error : FileTypeXFileExtension";
        } else {
            currentState = State::FileTypexFileExtension;
            qDebug() << "State : FileTypeXFileExtension";
        }
    } else {
        currentState = State::FileTypexFileExtension;
        qDebug() << "State : FileTypeXFileExtension";
    }
    return { isValid, currentState };
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
           fileExtension == "rar" || fileExtension == "7z" || fileExtension == "tar" || fileExtension == "gz" || fileExtension == "all"|| fileExtension == "json" || fileExtension == "lock";
}


bool validateDate(const QString& Date) {
    // Vérifie la validité des dates
    QDateTime DateTime = QDateTime::fromString(Date, "dd/MM/yyyy");
        return DateTime.isValid();
}

ValidationResult validateDateRange(const QString& minDate, const QString& maxDate, State& currentState) {
    if (currentState > State::MinDateXMaxDate) {
        qDebug() << "State Error : MinDateXMaxDate";
        currentState = State::Error;
        return { false, currentState };
    }
    qDebug() << "State : MinDateXMaxDate";
    currentState = State::MinDateXMaxDate;
    // Vérifie si la date minimale est inférieure ou égale à la date maximale
    bool isValid = minDate <= maxDate;
    if (!isValid) {
        currentState = State::Error;
    }
    return { isValid, currentState };
}

ValidationResult validateSizeRange(const QString& minFileSize, const QString& maxFileSize, State& currentState) {
    // Vérifie si la size minimale est inférieure ou égale à la size maximale
    if (currentState > State::MinSizexMaxSize) {
        qDebug() << "State Error : MinSizexMaxSize";
        currentState = State::Error;
        return { false, currentState };
    }
    bool isValid = minFileSize <= maxFileSize;
    if (!isValid) {
        currentState = State::Error;
        qDebug() << "State Error : MinSizexMaxSize";
    } else {
        currentState = State::MinSizexMaxSize;
        qDebug() << "State : MinSizexMaxSize";
    }
    return { isValid, currentState };
}
// Vérifie la validité de la taille minimale de fichier
bool validateMinFileSize(qint64 minFileSize) {
    // Code de validation de taille minimale de fichier
    return minFileSize >= 0;
}

bool validateCorrelation(const QString& fileType, const QString& fileExtension, const QString& minDate, const QString& maxDate, const QString& minFileSize, const QString& maxFileSize, State& currentState) {
    ValidationResult DateRange = validateDateRange(minDate, maxDate, currentState);
    if (DateRange.isValid) {
        ValidationResult TypeAndExtension = validateFileTypeAndExtension(fileType, fileExtension, DateRange.currentState);
        if (TypeAndExtension.isValid){
            ValidationResult SizeRange = validateSizeRange(minFileSize, maxFileSize, TypeAndExtension.currentState);
            if(SizeRange.isValid){
                if (SizeRange.currentState > State::End) {
                    qDebug() << "State Error : End";
                    currentState = State::Error;
                    return false;
                }
                qDebug() << "State : End";
                return true;
            }
        }
    } else {
        return false;
    qDebug() << "Date range is not valid";
    }
    return false;

}

// Vérifie la validité de la taille maximale de fichier
bool validateMaxFileSize(qint64 maxFileSize) {
    // Code de validation de taille maximale de fichier
    return maxFileSize > 0;
}

// Vérifie la validité de tous les champs
bool validateInput(const QList<Token>& tokens) {
    bool isValid = true;
    State currentState = State::Initial;
    qDebug() << "State : Initial";
    QString fileExtensionValue = "";
    QString fileTypeValue = "";// initialiser à une valeur par défaut
    QString MinDateValue = "";// initialiser à une valeur par défaut
    QString MaxDateValue = "";// initialiser à une valeur par défaut
    QString MinSizeValue = "";// initialiser à une valeur par défaut
    QString MaxSizeValue = "";// initialiser à une valeur par défaut
    for (const auto& token : tokens) {
        switch (token.type) {
            case TokenType::FileName:
                if (currentState > State::FileName) {
                               isValid = false;
                           }
                currentState = State::FileName;
                qDebug() << "State : FileName";
                isValid = isValid && validateFileName(token.value);
                if (!isValid) {
                    qDebug() << "State Error : FileName";
                    currentState = State::Error;
                    return false;
                }
                break;
            case TokenType::FileType:
                if (currentState > State::FileType) {
                                isValid = false;
                 }
                qDebug() << "State : FileType";
                currentState = State::FileType;
                fileTypeValue = token.value;
                isValid = isValid && validateFileType(token.value);
                if (!isValid) {
                    qDebug() << "State Error : FileType";
                    currentState = State::Error;
                    return false;
                }
                break;
            case TokenType::FileExtension:
            if (currentState > State::FileExtension) {
                               isValid = false;
                           }
                qDebug() << "State : FileExtension";
               currentState = State::FileExtension;
                fileExtensionValue = token.value; // mettre à jour la valeur de la variable
                isValid = isValid && validateFileExtension(token.value);
                if (!isValid) {
                    qDebug() << "State Error : FileExtension";
                     currentState = State::Error;
                     return false;
                }
                break;
        case TokenType::MinFileSize:
        if (currentState > State::MinFileSize) {
                            isValid = false;
                        }
                        currentState = State::MinFileSize;
            qDebug() << "State : MinFileSize";
            MinSizeValue = token.value;
            isValid = isValid && validateMinFileSize(token.value.toLongLong());
            if (!isValid) {
                qDebug() << "State Error : MinFileSize";
                currentState = State::Error;
                return false;
            }
            break;
        case TokenType::MaxFileSize:

            if (currentState > State::MaxFileSize) {
                               isValid = false;
                           }
            qDebug() << "State : MaxFileSize";
            currentState = State::MaxFileSize;
            MaxSizeValue  = token.value;
            isValid = isValid && validateMaxFileSize(token.value.toLongLong());
            if (!isValid) {
                qDebug() << "State Error : MaxFileSize";
                 currentState = State::Error;
                 return false;
            }
            break;
            case TokenType::MinDate:
            if (currentState > State::MinDate) {
                               isValid = false;
                           }
                           currentState = State::MinDate;
                qDebug() << "State : MinDate";
                MinDateValue = token.value;
                isValid = isValid && validateDate(token.value);
                if (!isValid) {
                    qDebug() << "State Error : MinDate";
                    currentState = State::Error;
                    return false;
                }
                break;
            case TokenType::MaxDate:
            if (currentState > State::MaxDate) {
                               isValid = false;
                           }
                qDebug() << "State : MaxDate";
                currentState = State::MaxDate;
                MaxDateValue = token.value;
                isValid = isValid && validateDate(token.value);
                if (!isValid) {
                    qDebug() << "State Error : MaxDate";
                    currentState = State::Error;
                    return false;
                }
                break;
            default:
            qDebug() << "State Error : Default";
             currentState = State::Error;
                // Token invalide
                break;
        }
    }
    isValid = isValid && validateCorrelation(fileTypeValue,fileExtensionValue, MinDateValue,MaxDateValue,MinSizeValue,MaxSizeValue,currentState);
    return isValid;
}
