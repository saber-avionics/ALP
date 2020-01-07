/** Simple LDR Reading Application
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2018
* Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include "drivers\readADC.h"

using namespace std;



int readAnalog(int number){
   stringstream ss;
   ss << LDR_PATH << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}
/*
int main(int argc, char* argv[]){
   cout << "Starting the readLDR program" << endl;
   int value = readAnalog(0);
   cout << "The LDR value was " << value << " out of 4095." << endl;
   return 0;
}
*/
