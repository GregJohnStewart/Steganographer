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
    string inputFile = "input_images/Kruse, Gerald.bmp";
    string outputDir = "outputs";
    string strToHide = "Hello there, Dr. Kruse! This is a message hidden INSIDE an image. Pretty nifty. Here's some special characters: \\`~!@#$%^&*()[]{}|/<>,.:;\"'*-+\nAnother line!";
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
