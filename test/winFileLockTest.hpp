/*
 * Copyright 2020 © Centre Interdisciplinaire de développement en Cartographie des Océans (CIDCO), Tous droits réservés
 */

/* 
 * File:   winFileLockTest.hpp
 * Author: Jordan McManus
 */

#ifndef WINFILELOCKTEST_HPP
#define WINFILELOCKTEST_HPP

#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include <string>

TEST_CASE("Test file lock with monitor, windows version") {
    
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
    
    if(CreateProcess("build\\test\\bin\\winlocker.exe",       // Application name
                 " test\\data\\lockTest\\s4.xtf",                 // Additional application arguments
                 NULL,
                 NULL,
                 FALSE,
                 CREATE_DEFAULT_ERROR_MODE,
                 NULL,
                 NULL,
                 &si,
                 &pi) == FALSE) {
        
        std::cout << "Couldn't create process" << std::endl;
        REQUIRE(false);
    }
    
    REQUIRE(true);
    
}

#endif /* WINFILELOCKTEST_HPP */

