#ifndef FSM_H
#define FSM_H

#include <QList>
#include "lexer.h"
// Les différents états possibles de la FSM
enum class State {
    Initial,
    FileName,
    FileType,
    FileExtension,
    MinFileSize,
    MaxFileSize,
    MinDate,
    MaxDate,
    MinDateXMaxDate,
    FileTypexFileExtension,
    MinSizexMaxSize,
    End,
    Error
};


#endif // FSM_H
