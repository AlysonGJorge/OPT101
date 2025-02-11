#ifndef PRINT_H
#define PRINT_H

#include <Arduino.h>

#define DEBUG 0

// Macro para facilitar o print de informações
#if DEBUG
#define debugPrint(c) Serial.print((c))
#define debugPrintln(c) Serial.println((c))
#else
#define debugPrint(c)
#define debugPrintln(c)
#endif

#endif // PRINT_H
