/**
 * driver for the Steganographer object
 *
 */

/* includes */
#include "res/Steganographer.h"
#include <string>

//usings
using std::string;
using namespace std;

int main(){
    string inputFile = "test_orig2.bmp";
    string outputDir = "outputs";
    string strToHide = "hello there, world. aaaaaaaaaaabbbbbbbbbcccccccddddddddeeeeeeffffffffgggggggggggggggggghhhhhhhhiiiiiiigggggggggggjjjjjjjjjkkkkkkkklllllllmmmmmmmmnnnnnnnnnooooooooppppppppppppp!%##$^(&_+)(^$##@}{@#13";
    Steganographer sten;
    
    sten = Steganographer();
    
    sten.setup(inputFile, outputDir, strToHide);
    
    cout << sten.toString();

    if(sten.ready()){
        cout << "object is ready" << endl;
        bool worked = sten.doSteganography();
        if(worked){
            cout << "steganography worked" << endl;
        }else{
            cout << "steganography failed" << endl;
        }
        
        cout << "Hidden message from file: \"" << sten.getHiddenMessage() << "\"" << endl;
    }else{
        cout << "object is not ready" << endl;
    }
    
    
    
}//main()
