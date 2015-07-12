/*
	Exception set up for the Stenographer object
	
	Sets up exceptions for the Stenographer
	
	Author: Greg Stewart
	Copyright: 2015
*/
#ifndef STENOGRAPHEREXCEPTION_H
#define STENOGRAPHEREXCEPTION_H
//includes
#include <stdexcept>//for runtime_error

//usings
using namespace std;

//Thrown when something went wrong
class StenographerException : public runtime_error {
	public:
    //an exception with an error message
	StenographerException(string exeptionIn) : runtime_error("Stenographer ran into an Exception. Error: " + exceptionIn){
        
	}//StenographerException(string)

    //an exception without an error message
    StenographerException() : runtime_error("Stenographer ran into an unspecified exception."){
        
    }//StenographerException()

};//class StenographerException
#endif
