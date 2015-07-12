/*
	Functions for the CollatzConjecture 
	
	Author: Greg Stewart
	Start:  4/16/14
*/

//includes
#include "Stenographer.h"//header file for the object
//all other includes in header file ^

//instance variables listed in Stenographer.h

//usings
using namespace std;

////////////////////////////
////	Public methods	////
////////////////////////////	
/*
	Constructors
*/

//Stenographer()
//  empty constructor, initializes everything to nulls
Stenographer(){
    stringToHide = "";
    origFilePath = "";
    outputDir = "";
}//Stenographer()

//Stenogrpher(string,string,string)
//  sets up the object using the setup() function
//
//@Param stringToHide
//      the string we are hiding
//@Param origFilePath
//      the filepath to the original image
//@Param outputDir
//      the output directory 
Stenographer(string stringToHide,string origFilePath,string outputDir){
    bool worked = setup(stringToHide,origFilePath,outputDir);//if things worked
    if(!worked){
        Stenographer();
        string output = "Failed to setup data, defaulted to nulls. Check to make sure file paths are valid, and are accessible and to this user's permissions.";
        throw StenographerException(output);
    }
}//Stenographer(string,string,string)

/*
    Setters
*/

/** sets up all the variables (stringToHideIn,origFilePathIn,outputDirIn)
tests input/output places to make sure they work
returns if it failed or not
*/
bool setup(string stringToHideIn,string origFilePathIn,string outputDirIn){
    bool worked = true;
    setNewStrToHide(stringToHideIn);
    
    worked = setInputImage(origFilePathIn);
    if(worked){
        worked = setInputImage(outputDirIn);
    }
    return worked;
}//setup(string,string,string)

//setNewStrToHide(string stringIn)
// sets the new string to hide	
//
//@Param stringIn
//  the string we are getting in
void setNewStrToHide(string stringIn){
    //TODO: checks?
    stringToHide = stringIn;
}//setStrToHide

/* sets the image to read from
tests the path for an image file
*/
bool setInputImage(string inputPath){
    bool worked = checkFilePath(inputPath);
    if(worked){
        origFilePath = inputPath;
    }
    return worked;
}//setInputImage(string)

/* sets the output directory
tests to make sure it exists
*/
bool setOutputDir(string outputPath){
    bool worked = checkFilePath(outputPath);
    if(worked){
        outputDir = outputPath;
    }
    return worked;
}//setOutputDir(string)

/*
    Getters
*/

//gets the input file path
string getInputPath(){
    return origFilePath();
}//getInputPath()

//gets the output file path
string getOutputPath(){
    return outputDir;
}//getOutputPath()

//gets the string that we are hiding
string getStringToHide(){
    return stringToHide;
}//getStringToHide

//gets what is currently hidden in the input file
string getInputHiddenMsg(){
    //open input file
    //
    //read in data & build string
    //output
}//getInputHiddenMsg()

//gets what is currently hidden in the output file (if any)
string getOutputHiddenMsg();
     
// returns if the object is ready to go or not
bool ready();
////////////////////////////////
////	Private Methods     ////
////////////////////////////////


//checks if the filepath given is valid
bool Stenographer::checkFilepath(string){
    
}//checkFilePath(string)
