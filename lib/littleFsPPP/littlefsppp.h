
// CRIADO POR AUGUSTO CESAR DE LIMA
//  01/02/2022
//      
// PARA USO COM ESP32
//
//
//
// INSTALAÇÃO PLATFORMIO:
// 
// lib_deps = https://github.com/lorol/LITTLEFS.git

// LITTLEFS BEGIN:

/* void Setup(){

    if(!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
        Serial.println("LITTLEFS Mount Failed");
        return;
    }

} */


#ifndef LITTLEFSPPP_H
#define LITTLEFSPPP_H

#pragma once
#include <FS.h>
#include <LittleFS.h>   
#include <definicoes.h>
#define FORMAT_LITTLEFS_IF_FAILED true

void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

void createDir(fs::FS &fs, const char * path);

void removeDir(fs::FS &fs, const char * path);

void readFile(fs::FS &fs, const char * path);

void writeFile(fs::FS &fs, const char * path, const char * message);

void appendFile(fs::FS &fs, const char * path, const char * message);

void renameFile(fs::FS &fs, const char * path1, const char * path2);

void deleteFile(fs::FS &fs, const char * path);

void writeFile2(fs::FS &fs, const char * path, const char * message);

void deleteFile2(fs::FS &fs, const char * path);

void testFileIO(fs::FS &fs, const char * path);


        //********** EXEMPLOS DE CHAMADAS DAS FUNÇÕES ********** //

    //writeFile2(LITTLEFS, "/new1/new2/new3/hello3.txt", "Hello3");
    //listDir(LITTLEFS, "/", 3);
    //deleteFile2(LITTLEFS, "/new1/new2/new3/hello3.txt");
    //listDir(LITTLEFS, "/", 3);
	//createDir(LITTLEFS, "/mydir");
	//writeFile(LITTLEFS, "/pppconfig.txt", "Hello augusto cesar!");
	//listDir(LITTLEFS, "/", 1);
	//deleteFile(LITTLEFS, "/mydir/hello2.txt");
	//removeDir(LITTLEFS, "/mydir");
    //listDir(LITTLEFS, "/", 1);
    //writeFile(LITTLEFS, "/hello.txt", "Hello ");
    //appendFile(LITTLEFS, "/hello.txt", "World!\r\n");
    //readFile(LITTLEFS, "/hello.txt");
    //renameFile(LITTLEFS, "/hello.txt", "/foo.txt");
    //readFile(LITTLEFS, "/foo.txt");
    //deleteFile(LITTLEFS, "/foo.txt");
    //testFileIO(LITTLEFS, "/test.txt");
    //deleteFile(LITTLEFS, "/test.txt");




#endif