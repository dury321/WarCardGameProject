//--------------------------------------------------------------------------------------------------
//File Name:        Standards.h
//Associated File:  None
//Contains:
//  Preprocessor directives for I/0, String, Formatting, and Constants.
//--------------------------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <cstdlib>
#include <ctime>

using namespace std;

//set basic constants
static const string PROGRAMMER_NAME = "Christian Dury";
//set divider fill character as constant 
static const char DEFAULT_CHAR = '-';
//set screen size constant
static const int SCREEN_SIZE = 65;
static const int TAB = 10;

//enumerated type for card suits
enum suits { heart = 3, diamond, club, spade };
//constant for the size of a deck
static const int DECK_SIZE = 52;
//constant for the maximum number of rounds allowed
static const int MAX_ROUNDS = 10000;
//game title
static const string GAME_TITLE = R"(

      ___           ___           ___     
     /__/\         /  /\         /  /\    
    _\_ \:\       /  /::\       /  /::\   
   /__/\ \:\     /  /:/\:\     /  /:/\:\  
  _\_ \:\ \:\   /  /:/~/::\   /  /:/~/:/  
 /__/\ \:\ \:\ /__/:/ /:/\:\ /__/:/ /:/___
 \  \:\ \:\/:/ \  \:\/:/__\/ \  \:\/:::::/
  \  \:\ \::/   \  \::/       \  \::/~~~~ 
   \  \:\/:/     \  \:\        \  \:\     
    \  \::/       \  \:\        \  \:\    
     \__\/         \__\/         \__\/    
)";
