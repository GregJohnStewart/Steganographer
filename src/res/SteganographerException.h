/*
	Exception set up for the Steganographer object
	
	Sets up exceptions for the Steganographer
	
	Author: Greg Stewart
	Copyright: 2015
*/
#ifndef STEGANOGRAPHEREXCEPTION_H
#define STEGANOGRAPHEREXCEPTION_H
//includes
#include <string>//for strings
#include <stdexcept>//for runtime_error

//usings
using std::string;
using namespace std;

//Thrown when something went wrong
class SteganographerException : public runtime_error {
	public:
    
    //an exception without an error message
    SteganographerException() : runtime_error("Steganographer ran into an unspecified exception."){
        
    }//SteganographerException()
    
    
    //an exception with an error message
	SteganographerException(const string& exceptionIn) : runtime_error("Steganographer ran into an Exception. Error: " + exceptionIn){
        
	}//SteganographerException(string)
    
};//class SteganographerException
#endif