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

// Fonction qui effectue l'analyse syntaxique d'une liste de jetons et renvoie vrai si l'entrée est valide
bool parseInput(const QList<Token>& tokens);

#endif // FSM_H
