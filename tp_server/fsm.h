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
    MinDate,
    MaxDate,
    MinFileSize,
    MaxFileSize,
    Error
};

// Les différents types de jetons possibles
//enum class TokenType {
//    Invalid,        // Jeton invalide
//    FileName,       // Nom de fichier
//    FileType,       // Type de fichier (image, texte, exécutable)
//    FileExtension,  // Extension de fichier (.txt, .sh, etc.)
//    MinDate,        // Date de création du fichier
//    MaxDate,
//    MinFileSize,    // Taille minimale du fichier
//    MaxFileSize     // Taille maximale du fichier
//};

// Un jeton est composé d'un type et d'une valeur
//struct Token {
//    TokenType type;
//    QString value;
//};

// Fonction qui effectue l'analyse syntaxique d'une liste de jetons et renvoie vrai si l'entrée est valide
bool parseInput(const QList<Token>& tokens);

#endif // FSM_H
