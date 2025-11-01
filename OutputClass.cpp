//--------------------------------------------------------------------------------------------------
//File Name:        OutputClass.cpp
//Associated File:  OutputClass.h
//Contains:
//  Print Methods:	(inline)			None
//					(defined in .cpp)	OutputDivider, OutputHeader, OutputCenteredMessage
//										OutputFileName
//--------------------------------------------------------------------------------------------------

#include "OutputClass.h"

//--------------------------------------------------------------------------------------------------
//OutputDivider - Outputs a specified number of symbols to the output file
//--------------------------------------------------------------------------------------------------
void OutputDivider(ofstream& fout, char symbol, int numberOfSymbols)
{
	fout << setfill(symbol) << setw(numberOfSymbols) << ' '
		<< setfill(' ') << endl;
}

/*****************************************************************************************/
/* OutputHeader - This function will print a heading to the stream that is sent to the function.
					It will be of a constant length and will include the college name, exercise number,
					and programmer name.
******************************************************************************************/
void OutputHeader(ofstream& fout)
{
	//print divider to output file with constant divider symbol and constant screen width
	OutputDivider(fout, '*', SCREEN_SIZE);

	//center align programmer's name
	fout << setw((SCREEN_SIZE + PROGRAMMER_NAME.length()) / 2) << PROGRAMMER_NAME << endl;

	//print divider to output file with constant divider symbol and constant screen width
	OutputDivider(fout, '*', SCREEN_SIZE);
}

//--------------------------------------------------------------------------------------------------
//OutputCenteredMessage - Print a centered message to the output stream based on the length of the 
//	message.
//--------------------------------------------------------------------------------------------------
void OutputCenteredMessage(ofstream& fout, string message)
{
	//print a centered message based on the length of the message
	fout << setw((SCREEN_SIZE + message.length()) / 2) << message << endl;
}

//--------------------------------------------------------------------------------------------------
//OutputFileName - Print a message to the output stream based on the string that is passed in.
// Print specific message based on the input or output flag that is passed in to the function as
// to where the input/output file can be found. 
//--------------------------------------------------------------------------------------------------
void OutputFileName(ofstream& fout, string fileName, bool printInputFileFlag)
{
	//if the function is printing where the input file can be found...
	if (printInputFileFlag)
	{
		//print where the input file can be found
		fout << setw((SCREEN_SIZE + fileName.length() - 40) / 2) << "The input file(s) can be found in: "
			<< fileName << endl;
	}
	//if the function is not printing where the input file can be found, print where the output file
	//	can be found
	else
	{
		//print where the output file can be found
		fout << setw((SCREEN_SIZE + fileName.length() - 37) / 2) << "The output file(s) can be found in: "
			<< fileName << endl;
	}
}