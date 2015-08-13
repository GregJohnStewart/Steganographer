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
    string inputFile = "test_orig2.bmp";
    string outputDir = "outputs";
    string strToHide = "hello world";
    Stenographer sten;
    
    sten = Stenographer();
    
    sten.setup(inputFile, outputDir, strToHide);
    
    cout << sten.toString();

    if(sten.ready()){
        cout << "object is ready" << endl;
        bool worked = sten.doStenography();
        if(worked){
            cout << "stenography worked" << endl;
        }else{
            cout << "stenography failed" << endl;
        }
    }else{
        cout << "object is not ready" << endl;
    }
    
    
    
}//main()
