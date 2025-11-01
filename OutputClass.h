//--------------------------------------------------------------------------------------------------
//File Name:        OutputClass.h
//Associated File:  OutputClass.cpp, Standards.h
//Contains:
//  Print Methods:	(inline)			None
//					(defined in .cpp)	OutputDivider, OutputHeader, OutputCenteredMessage
//										OutputFileName
//--------------------------------------------------------------------------------------------------

#pragma once
#include "Standards.h"

//output divider: take in output stream, symbol, and length of divider
void OutputDivider(ofstream& fout, char symbol, int numberOfSymbols);
//output header with programmer name
void OutputHeader(ofstream& fout);
//output centered message
void OutputCenteredMessage(ofstream& fout, string message);
//output the file name
void OutputFileName(ofstream& fout, string fileName, bool printInputFileFlag);

