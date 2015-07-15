/**
 * driver for the Stenographer object
 *
 */

/* includes */
#include "res/Stenographer.h"
#include <string>

//usings
using std::string;
using namespace std;

int main(){
    string inputFile = "test_orig.jpg";
    string outputDir = "/";
    string strToHide = "hello world";
    Stenographer sten;
    
    sten = Stenographer();
    
    sten.setup(inputFile, outputDir, strToHide);
    
    cout << sten.toString();
}//main()
