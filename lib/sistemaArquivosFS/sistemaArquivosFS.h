#ifndef SISTEMAARQUIVOS_H
#define SISTEMAARQUIVOS_H
#pragma once
#include "FS.h"
#include <LITTLEFS.h>
#include <ArduinoJson.h>  


#include <definicoes.h>


void saveConfig(char *saveEmail, char *savePassword);
void readConfig(char *retornoEmail, char *retornoPassword);






















#endif