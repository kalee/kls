// jumble.cpp
// Kenneth A. Lee
// $URL$
// $Author$
// $Date$
// $Id$
// 
// Revision History:
// 17 December 1998 - Coding
// 08 February 1999 - Added documentation for how to get values
// 18 September 2007 - Documented more examples to make it more clear how the 
//                     process works.
// 15 September 2008 - Documentation cleanup.  Set right margin at 80 chars.
//
// Prints off every permutation of entered string.
// This routine dynamically builds each unique answer.  There is actually no 
// limit on what it can do, except for amount of time to print the answer to the 
// screen.  This routine was set up so that there isn't a need to prebuild any 
// type of list. The function perm(), takes three parameters, the string, the 
// result, and an index.  The index can be any value from 0 to 
// strlen(string) - 1.  The perm function returns the unique permuation at the 
// specified index.  The perm algorithm has a predefined format for how any 
// permutation is stored and this is built into the algorithm.  A self imposed 
// limit of 12 characters has been included to keep size down.  Any character 
// including a space can be used.
//
// 4 Characters
// 4 Columns x 3(2)(1) Rows
//
//         0                  1                  2                  3
//  ----------------------------------------------------------------------------
// 0|s[0]s[1]s[2]s[3] | s[1]s[0]s[2]s[3] | s[1]s[2]s[0]s[3] | s[1]s[2]s[3]s[0] |
// 1|s[0]s[1]s[3]s[2] | s[1]s[0]s[3]s[2] | s[1]s[3]s[0]s[2] | s[1]s[3]s[2]s[0] |
// 2|s[0]s[2]s[1]s[3] | s[2]s[0]s[1]s[3] | s[2]s[1]s[0]s[3] | s[2]s[1]s[3]s[0] |
// 3|s[0]s[3]s[1]s[2] | s[3]s[0]s[1]s[2] | s[3]s[1]s[0]s[2] | s[3]s[1]s[2]s[0] |
// 4|s[0]s[2]s[3]s[1] | s[2]s[0]s[3]s[1] | s[2]s[3]s[0]s[1] | s[2]s[3]s[1]s[0] |
// 5|s[0]s[3]s[2]s[1] | s[3]s[0]s[2]s[1] | s[3]s[2]s[0]s[1] | s[3]s[2]s[1]s[0] |
//
//
//
// 3 Characters
// 3 Columns x 2(1) Rows
//           0                1                2
//  ----------------------------------------------------
// 0| s[0] s[1] s[2] | s[1] s[0] s[2] | s[1] s[2] s[0] |
// 1| s[0] s[2] s[1] | s[2] s[0] s[1] | s[2] s[1] s[0] |
//
//    abc              bac              bca
//    acb              cab              cba
//
// 3 Characters
// s[0] = a         Formulas used in Perm() for loop from # of Columns to 0
// s[1] = b         iOffSet = int((double)iIndex/bFactorial);
// s[2] = c         iIndex = iIndex % (int)bFactorial;  // Used in next iter
//
// ABC Find perm("abc",2) --> 2 is the initial iIndex
// Loop from (length -1) to 0 --> (3-1=2) to 0
// Loop=2
//   iIndex=2 
//   bFactorial=Loop!=2!=2 
//   iOffset=(int)iIndex/bFactorial=2/2=1 
//   iIndex=iIndex%bFactorial=2%2=0
// Loop=1
//   iIndex=0 
//   bFactorial=Loop!=1!=1 
//   iOffset=(int)iIndex/bFactorial=0/1=0 
//   iIndex=iIndex%bFactorial=0%1=0
// Loop=0
//   iIndex=0 
//   bFactorial=Loop!=0!=1 
//   iOffset=(int)iIndex/bFactorial=0/1=0 
// 
// Offset 1 ==> abc => Offset first letter 1 place      _ a _
// Offset 0 ==> abc => Offset next letter 0 places      b a _
// Offset 0 ==> abc => Offset next letter 0 places      b a c  ==> The last 
//   letter will always have an offset of 0 since there is no other place to go.
// The Offset value will be a value 1 less then the number of possible positions 
//   available.
// _ _ _ Offset 0 is the first position.  
//       Offset 1 is the second position.  
//       Offset 2 is the third position
// 
// _ _ a Offset 0 is the first position.  Offset 1 is the second position.
// _ a _ Offset 0 is the first position.  Offset 1 is the third position.
// a _ _ Offset 0 is the second position.  Offset 1 is the third position.
// 
// _ a b Only 1 position available. Offset 0 is the first position.
// a _ b Only 1 position available. Offset 0 is the second position.
// a b _ Only 1 position available. Offset 0 is the third position.
// 
// iOffSet = int((double)iIndex/bFactorial);  
// iIndex = iIndex % (int)bFactorial;// Used in next iteration
// perm("string",index)
//    ("abc",0)               ("abc",1)               ("abc",2)               
//    Offset      Index       Offset      Index       Offset      Index       
// 2  0 / 2! = 0  0 % 2! = 0  1 / 2! = 0  1 % 2! = 1  2 / 2! = 1  2 % 2! = 0  
// 1  0 / 1! = 0  0 % 1! = 0  1 / 1! = 1  1 % 1! = 0  0 / 1! = 0  0 % 2! = 0  
// 0  0 / 0! = 0              0 / 0! = 0              0 / 0! = 0              
//
//    ("abc",3)               ("abc",4)               ("abc",5)
//    Offset      Index       Offset      Index       Offset      Index
//    3 / 2! = 1  3 % 2! = 1  4 / 2! = 2  4 % 2! = 0  5 / 2! = 2  5 % 2! = 1
//    1 / 1! = 1  1 % 2! = 1  0 / 1! = 0  0 % 2! = 0  1 / 1! = 1  1 % 1! = 0
//    1 / 0! = 0              0 / 0! = 0              0 / 0! = 0  
// 
// 
//    0 @ OffSet 0   a _ _    0 @ OffSet 0   a _ _    0 @ OffSet 1   _ a _    
//    1 @ OffSet 0   a b _    1 @ OffSet 1   a _ b    1 @ OffSet 0   _ a _    
//    2 @ OffSet 0   a b c    2 @ OffSet 0   a c b    2 @ OffSet 0   b a c    
// 
//    0 @ OffSet 1   _ a _    0 @ OffSet 2   _ _ a    0 @ OffSet 2   _ _ a
//    1 @ OffSet 1   _ a b    1 @ OffSet 0   b _ a    1 @ OffSet 1   _ b a
//    2 @ OffSet 0   c a b    2 @ OffSet 0   b c a    2 @ OffSet 0   c b a
// 
// 
// 
// 
// 
// i = 2 bFactorial = 2 iOffSet = 0 iIndex = 0 pResult = a      
// i = 2 bFactorial = 2 iOffSet = 1 iIndex = 0 pResult =  a     
// i = 2 bFactorial = 2 iOffSet = 2 iIndex = 0 pResult =   a
// i = 1 bFactorial = 1 iOffSet = 0 iIndex = 0 pResult = ab     
// i = 1 bFactorial = 1 iOffSet = 0 iIndex = 0 pResult = ba     
// i = 1 bFactorial = 1 iOffSet = 0 iIndex = 0 pResult = b a
// i = 0 bFactorial = 1 iOffSet = 0 iIndex = 0 pResult = abc    
// i = 0 bFactorial = 1 iOffSet = 0 iIndex = 0 pResult = bac    
// i = 0 bFactorial = 1 iOffSet = 0 iIndex = 0 pResult = bca
//
// i = 2 bFactorial = 2 iOffSet = 0 iIndex = 1 pResult = a      
// i = 2 bFactorial = 2 iOffSet = 1 iIndex = 1 pResult =  a     
// i = 2 bFactorial = 2 iOffSet = 2 iIndex = 1 pResult =   a
// i = 1 bFactorial = 1 iOffSet = 1 iIndex = 0 pResult = a b    
// i = 1 bFactorial = 1 iOffSet = 1 iIndex = 0 pResult =  ab    
// i = 1 bFactorial = 1 iOffSet = 1 iIndex = 0 pResult =  ba
// i = 0 bFactorial = 1 iOffSet = 0 iIndex = 0 pResult = acb    
// i = 0 bFactorial = 1 iOffSet = 0 iIndex = 0 pResult = cab    
// i = 0 bFactorial = 1 iOffSet = 0 iIndex = 0 pResult = cba
// 
//                                                              
// Perm("abc","abc",0)                                          
// i | bFactorial | iOffSet | iIndex                            
// ---------------------------------                            
// 2 |      2     |    0    |   0                               
// 1 |      1     |    0    |   0                               
// 0 |      1     |    0    |                                   
//
// Perm("abc","abc",1)                                          
// i | bFactorial | iOffSet | iIndex                            
// ---------------------------------                            
// 2 |      2     |    0    |   1                               
// 1 |      1     |    1    |   1                               
// 0 |      1     |    0    |                                   
// 
// Perm("abc","abc",2)                      
// i | bFactorial | iOffSet | iIndex        
// ---------------------------------        
// 2 |      2     |    1    |   2           
// 1 |      1     |    0    |   0           
// 0 |      1     |    0    |              
// 
// Perm("abc","abc",3)                                          
// i | bFactorial | iOffSet | iIndex                            
// ---------------------------------                            
// 2 |      2     |    1    |   3                               
// 1 |      1     |    1    |   1                               
// 0 |      1     |    0    |                                   
//
// Perm("abc","abc",4)                                          
// i | bFactorial | iOffSet | iIndex                            
// ---------------------------------                            
// 2 |      2     |    2    |   4                               
// 1 |      1     |    0    |   0                               
// 0 |      1     |    0    |                                   
// 
// Perm("abc","abc",5)
// i | bFactorial | iOffSet | iIndex
// ---------------------------------
// 2 |      2     |    2    |   5
// 1 |      1     |    1    |   1
// 0 |      1     |    0    |   
//
//
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

// Function Prototypes
void perm(char* pString, char* pResult, int iIndex);
void printstring(char* pString);
double factorial(int iValue);
void getvalues(char* pString, const int iCount);
void fillvalue(char* pResult, int iIndex, char cCharacter);
void eatspaces(char* str);

int main(void) {
	const int MAX = 12;
	char cString[20];
	char cResult[20];
	int iStringLength = 0;

	getvalues(cString, MAX);

	iStringLength = strlen(cString);

	for (int i = 0; i < factorial(iStringLength); i++) {
		strcpy(cResult, cString);
		perm(cString, cResult, i);
		printstring(cResult);
	}

	cout << endl;
	return 0;
}


// Function void perm(char* pResult, int iIndex)
//
void perm(char* pString, char* pResult, int iIndex) {
	int iStringLength = strlen(pString);
	double bFactorial = 0.0;
	int iOffSet = 0;
	// char fileName[]="abc.txt";
	// ofstream fout(fileName, ios::app);  
	// Append to file, don't overwrite each time.

	// Replace contents of pResult with blanks
	for (int i = 0; i < iStringLength; i++) 
		pResult[i] = ' ';

	// Routine to set up which position should get filled in
	for (int i = iStringLength - 1; i >= 0; i--) {
		bFactorial = factorial(i);
		iOffSet = int((double)iIndex/bFactorial);
		// fout << " i = " << i << " bFactorial = " << bFactorial << " iOffSet = " 
		// << iOffSet << " iIndex = " << iIndex << endl;
		iIndex = iIndex%(int)bFactorial;
		// fout << " i = " << i << " bFactorial = " << bFactorial << " iOffSet = " 
		// << iOffSet << " iIndex = " << iIndex << " pResult = " << pResult 
		// << " pString = " << pString << " pString[iStringLength - i - 1] = " 
		// << pString[iStringLength - i - 1] << endl;
		fillvalue(pResult,iOffSet,pString[iStringLength - i - 1]);
    // fout << " i = " << i << " bFactorial = " << bFactorial << " iOffSet = " 
    // << iOffSet << " iIndex = " << iIndex << " pResult = " << pResult 
    // << " pString = " << pString << " pString[iStringLength - i - 1] = " 
    // << pString[iStringLength - i - 1] << endl;
	}
	// fout << endl;
	// fout.close();
}

void printstring(char* pString) {
	// Receive a string.  This routine will print output to the screen.  22 Rows
	// That fit on an 80 column width screen.
	static int row = 0;
	static int column = 0;
	const int MAXROW = 22;
	const int MAXCOL = 78;
	int iStringLength = strlen(pString) + 2;
	char buffer[80];

	if (column + iStringLength < MAXCOL) {
		cout << " " << pString << " ";
		column += iStringLength;
	} else {
		if (row == MAXROW) {
			cout << endl << "Press <ENTER> continue." << endl;
			cin.getline(buffer,80,'\n');
			row=0;
		}
		cout << endl << " " << pString << " ";
		column = iStringLength;
		row++;
	}
}


double factorial(int iValue) {
	// fact(n) = n * fact(n - 1)
	if (iValue == 1 || iValue == 0)
		return 1.0;

	return iValue * factorial(iValue - 1);
}


void getvalues(char* pString, const int iCount) {
	cout << endl;
	cout << "Enter a string of no more that 12 characters (Spaces are ignored): ";

	cin.getline(pString, iCount, '\n');

	if (strlen(pString) == 0) {
		cout << "Nothing entered, ending program and exiting to system." << endl;
		exit(1);
	}

	// Remove spaces from input string.
	eatspaces(pString);
}


// Recieves an array, some of the elements may contain spaces.
// find the indexed place, not counting spaces, and fill with cCharacter.
void fillvalue(char* pResult, int iIndex, char cCharacter) {
	int iCounter = 0;

	// Count from 0 to stringlength - 1
	for (int i = 0; (unsigned) i < strlen(pResult); i++) {
		if (pResult[i] == ' ') 		{
			if (iCounter == iIndex)
				pResult[i] = cCharacter;

			iCounter++;
		}
	}
}


// Function to eliminate blanks from a string
void eatspaces(char* str) {
   int i=0;         // 'Copy to' index to string
   int j=0;         // 'Copy from' index to string

   while ((*(str+i) = *(str+j++)) != '\0')   // Loop while character
                                            // copied is not \0
      if (*(str+i) != ' ')                   // Increment i as long as
         i++;                               // character is not a blank
   return;
}

// End of File
