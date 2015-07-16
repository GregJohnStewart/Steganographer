/*
	Functions for the CollatzConjecture 
	
	Author: Greg Stewart
	Start:  4/16/14
*/

//includes
#include "Stenographer.h"//header file for the object
//all other includes & usings in header file ^

////////////////////////////
////	Public methods	////
////////////////////////////	
/*
	Constructors
*/

//Stenographer()
//  empty constructor, initializes everything to nulls
Stenographer::Stenographer(){
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
Stenographer::Stenographer(string origFilePath, string outputDir, string stringToHide){
    bool worked = setup(origFilePath, outputDir, stringToHide);//if things worked
    if(!worked){
        //Stenographer();
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
bool Stenographer::setup(string origFilePathIn,string outputDirIn, string stringToHideIn){
    bool worked = true;
    setNewStrToHide(stringToHideIn);
    
    worked = setInputImage(origFilePathIn);
    if(worked){
        worked = setOutputDir(outputDirIn);
    }
    
    return worked;
}//setup(string,string,string)

//setNewStrToHide(string stringIn)
// sets the new string to hide	
//
//@Param stringIn
//  the string we are getting in
void Stenographer::setNewStrToHide(string stringIn){
    //TODO: checks?
    stringToHide = stringIn;
}//setStrToHide

/* sets the image to read from
tests the path for an image file
*/
bool Stenographer::setInputImage(string inputPath){
    bool worked = checkFilePath(inputPath,false);
    if(worked){
        origFilePath = inputPath;
    }else{
        throw StenographerException("Failed setting the input image. Make sure the file path is correct and a corect filetype.");
    }
    return worked;
}//setInputImage(string)

/* sets the output directory
tests to make sure it exists
*/
bool Stenographer::setOutputDir(string outputPath){
    bool worked = checkFilePath(outputPath,true);
    if(worked){
        outputDir = outputPath;
    }else{
        throw StenographerException("Failed setting the output directory. Make sure the file path is correct.");
    }
    return worked;
}//setOutputDir(string)

/*
    Getters
*/

//gets the input file path
string Stenographer::getInputPath(){
    return origFilePath;
}//getInputPath()

//gets the output file path
string Stenographer::getOutputPath(){
    return outputDir;
}//getOutputPath()

//gets the string that we are hiding
string Stenographer::getStringToHide(){
    return stringToHide;
}//getStringToHide

//gets the string hidden in the input file
string getHiddenMessage(){
    
}//getHiddenMessage()
     
string Stenographer::toString(){
    return "Input File: \"" +
            getInputPath() + 
            "\" Output Dir: \"" + 
            getOutputPath() + 
            "\" String Hiding: \"" + 
            getStringToHide() +
            "\"\n"; 
}//toString()

// returns if the object is ready to go or not
bool Stenographer::ready(){
    bool ready = true;
    
    if(gotInputPath() && gotOutputPath() && gotStringToHide()){
        ready = true;
    }else{
        ready = false;
    }
    
    return ready;
}//ready()


//returns if got an input
bool Stenographer::gotInputPath(){
    if(origFilePath == ""){
        return false;
    }else{
        return true;
    }
}//gotInputPath()

//returns if got an output path
bool Stenographer::gotOutputPath(){
    if(outputDir == ""){
        return false;
    }else{
        return true;
    }
}//gotOutputPath()

//returns if got a string to hide
bool Stenographer::gotStringToHide(){
    if(stringToHide == ""){
        return false;
    }else{
        return true;
    }
}//gotStringToHide()


////////////////////////////////
////	Private Methods     ////
////////////////////////////////


//checks if the filepath given is valid
bool Stenographer::checkFilePath(string pathIn, bool dir){
    //sendDebugMsg("Path Given: " + pathIn);
    bool worked = false;//if things worked
    struct stat pathStat;//buffer for the stat
    //check if valid 
    if(worked = (lstat(pathIn.c_str(), &pathStat) == 0)){
        //sendDebugMsg("path is present");
        //check if a file or directory
        if((S_ISDIR(pathStat.st_mode)) && dir){
            //sendDebugMsg("path is dir");
            worked = true;
        }else if((pathStat.st_mode && S_IFREG) && !dir){
            //sendDebugMsg("path is file");
            //check if valid filetype
            worked = checkFileType(pathIn);
        }else{
            //sendDebugMsg("path is not recognized");
            worked = false;
        }
    }else{//if valid path
        //sendDebugMsg("path is invalid");
        worked = false;
    }
    /*
    if(debugging & !worked){
        sendDebugMsg("checking file path \"" + pathIn + "\" failed.");
    }else if(debugging){
        sendDebugMsg("path given is valid");
    }
    */
    
    return worked;
}//checkFilePath(string)


bool Stenographer::checkFileType(string pathIn){
    bool worked = true;
    //get extension from path and normalize it by making it uppercase
    string extension = pathIn.substr(pathIn.find_last_of(".") + 1);
    transform(extension.begin(), extension.end(), extension.begin(), ::toupper);
    //check if a valid filetype
    if(extension == "JPG"){//TODO: add more extensions
        worked = true;
    }else{
        worked = false;
    }
    if(debugging & !worked){
        sendDebugMsg("checking file type \"" + extension + "\" failed.");
    }
    return worked;
}//checkFileType(string)


//couts a debug message
void Stenographer::sendDebugMsg(string message){
    if(debugging){
        cout << message << endl;
    }
}//sendDebugMsg





////////////////////////////////////////////////
////    File In/Out, stenography classes    ////
////////////////////////////////////////////////

//does the stenography
bool Stenographer::doStenography(){
    
}//doStenography

//gets the optional output file
string Stenographer::getHiddenMessage(){
    
}




















