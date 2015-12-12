/*
	Functions for the Steganographer
	
	Author: Greg Stewart
	Start:  4/16/14
*/

//includes
#include "Steganographer.h"//header file for the object
//all other includes & usings in header file ^

////////////////////////////
////	Public methods	////
////////////////////////////	
/*
	Constructors
*/

//Steganographer()
//  empty constructor, initializes everything to nulls
Steganographer::Steganographer(){
    stringToHide = "";
    origFilePath = "";
    outputDir = "";
}//Steganographer()

//Stenogrpher(string,string,string)
//  sets up the object using the setup() function
//
//@Param stringToHide
//      the string we are hiding
//@Param origFilePath
//      the filepath to the original image
//@Param outputDir
//      the output directory 
Steganographer::Steganographer(string origFilePath, string outputDir, string stringToHide){
    bool worked = setup(origFilePath, outputDir, stringToHide);//if things worked
    if(!worked){
        //Steganographer();
        string output = "Failed to setup data, defaulted to nulls. Check to make sure file paths are valid, and are accessible and to this user's permissions.";
        throw SteganographerException(output);
    }
}//Steganographer(string,string,string)

/*
    Setters
*/

/** sets up all the variables (stringToHideIn,origFilePathIn,outputDirIn)
tests input/output places to make sure they work
returns if it failed or not
*/
bool Steganographer::setup(string origFilePathIn,string outputDirIn, string stringToHideIn){
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
void Steganographer::setNewStrToHide(string stringIn){
    //TODO: checks?
    stringToHide = stringIn;
}//setStrToHide

/* sets the image to read from
tests the path for an image file
*/
bool Steganographer::setInputImage(string inputPath){
    bool worked = checkFilePath(inputPath,false);
    if(worked){
        origFilePath = inputPath;
    }else{
        throw SteganographerException("Failed setting the input image. Make sure the file path is correct and a corect filetype.");
    }
    return worked;
}//setInputImage(string)

/* sets the output directory
tests to make sure it exists
*/
bool Steganographer::setOutputDir(string outputPath){
    bool worked = checkFilePath(outputPath,true);
    if(worked){
        outputDir = outputPath;
    }else{
        throw SteganographerException("Failed setting the output directory. Make sure the file path is correct.");
    }
    return worked;
}//setOutputDir(string)


/* sets the output filename.
    NOTE: do not give it a file extension
*/
void setOutputName(string){
    
}//setOutputName()

/*
    Getters
*/

//gets the input file path
string Steganographer::getInputPath(){
    return origFilePath;
}//getInputPath()

//gets the output file path
string Steganographer::getOutputDir(){
    return outputDir;
}//getOutputPath()

string Steganographer::getOutputPath(){
    
    string outputFilePath = getOutputDir();
    //grab filename from outputFileName (cutting away rest of path & extension if there)
    
    //add output file path
    if((outputFilePath.find("/") + 1) != outputFilePath.length()){
        outputFilePath += "/"; 
    }

    outputFilePath += getOutputFileName();
    
    return outputFilePath;
}//getOutputPath()

//gets the optional output filename
string Steganographer::getOutputFileName(){
    string output = "";
    
    if(outputFileName == ""){
        //get name from input
        string inputFile = getInputPath();
        if(inputFile.find("/") == string::npos){
            output = inputFile;
        }else{
            output = inputFile.substr(inputFile.find_last_of("/") + 1);
        }
        
        if(inputFile.find(".") != string::npos){
            int posOfDot = output.find_last_of(".");
            output = output.substr(0,posOfDot);
        }
    }else{
        output = outputFileName;
    }
    //tack extension on
    output += "." + curExtension;
    //sendDebugMsg("output of getOutputFileName: " + output);
    return output;
}//getOutputFileName()

//gets the string that we are hiding
string Steganographer::getStringToHide(){
    return stringToHide;
}//getStringToHide

string Steganographer::toString(){
    return "Input File: \"" +
            getInputPath() + 
            "\" Output Dir: \"" + 
            getOutputDir() + 
            "\" String Hiding: \"" + 
            getStringToHide() +
            "\" Output File: \"" + 
            getOutputPath() +
            "\"\n";
}//toString()

// returns if the object is ready to go or not
bool Steganographer::ready(){
    bool ready = true;
    
    if(gotInputPath() && gotOutputDir() && gotStringToHide()){
        ready = true;
    }else{
        ready = false;
    }
    return ready;
}//ready()


//returns if got an input
bool Steganographer::gotInputPath(){
    if(origFilePath == ""){
        return false;
    }else{
        return true;
    }
}//gotInputPath()

//returns if got an output path
bool Steganographer::gotOutputDir(){
    if(outputDir == ""){
        return false;
    }else{
        return true;
    }
}//gotOutputPath()

//returns if got a string to hide
bool Steganographer::gotStringToHide(){
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
bool Steganographer::checkFilePath(string pathIn, bool dir){
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


bool Steganographer::checkFileType(string pathIn){
    bool worked = true;
    //get extension from path and normalize it by making it uppercase
    string extension = pathIn.substr(pathIn.find_last_of(".") + 1);
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    //check if a valid filetype
    if(isValidExtension(extension)){//TODO: add more extensions
        curExtension = extension;
        worked = true;
    }else{
        worked = false;
    }
    if(debugging & !worked){
        sendDebugMsg("checking file type \"" + extension + "\" failed.");
    }
    return worked;
}//checkFileType(string)

bool Steganographer::isValidExtension(string extensionIn){
    //TODO:: restructure to test using CImg (http://stackoverflow.com/questions/18634962/cimg-how-to-test-that-a-file-is-image)
    if(extensionIn == "jpg" || 
       extensionIn == "bmp" ||
       extensionIn == "gif" ||
       extensionIn == "png"
      ){
        return true;
    }else{
        return false;
    }
}//isValidExtension()

//couts a debug message
void Steganographer::sendDebugMsg(string message){
    if(debugging){
        cout << message << endl;
    }
}//sendDebugMsg





////////////////////////////////////////////////
////    File In/Out, steganography classes    ////
////////////////////////////////////////////////

//does the steganography

/**
 * Steps:
 * 
 *      1) zero out least significant bit of each byte in img data
 *      2) hide string (including null terminator), bit by bit, in image data, 1 bit/ byte of image data
 *      3) randomize rest of the least significant digits, to be less suspicious.
 * 
 * help from https://gist.github.com/utaal/1557933
 */
bool Steganographer::doSteganography(){
    // make sure we are ready to go
    bool worked = ready();
    
    if(worked){
        ByteCImg image(this->getInputPath().c_str());
        image &= 0xfe;
        string tempStringToHide = getStringToHide();
        //cout << "Size of string: " + sizeof(tempStringToHide.c_str()) << endl;
        ByteCImg::iterator it = image.begin();
        int i = 0;
        for (;;) {
            //+1 to length to ensure null terminator is placed.
            if (i == tempStringToHide.length() + 1) {
                break;
            }
            char cur = tempStringToHide.c_str()[i];
            //cout<< "cur: " + tempStringToHide[i] << endl;
            for (int b = 0; b < 8; ++b) {
                if (it == image.end()) {
                    break;
                }
                *it = *it | ((cur >> b) & 0x01);
                ++it;
            }
            i++;
        }
        if (it == image.end()) {
            //cerr << "Cannot fit the entire input in the image" << endl;
            worked = false;
        }else{
            //fill with random data, to hide the fact we hid a message
            srand (time(NULL));
            while(it != image.end()){
                *it = *it | (rand() & 0x01);
                ++it;
            }
        }
        if(worked){
            image.save(getOutputPath().c_str());
        }
    }//if obj ready
    
    return worked;
}//doSteganography

//gets the optional output file
/**
 * Pulls string data, bit by bit, from the image data. Stops on null terminator.
 * help from https://gist.github.com/utaal/1557933
 */
string Steganographer::getHiddenMessage(){
    bool worked = ready();
    string outputStr = "";
    
    if(worked){
        ByteCImg image(getOutputPath().c_str());
        
        int bit = 0;
        char chr = 0;
        int i = 0;
        for (ByteCImg::iterator it = image.begin(); it != image.end(); ++bit, ++it) {
            chr |= (*it & 0x01) << bit;
            if (bit == 7) {
                if(chr == '\0'){
                    break;
                }
                outputStr += chr;
                bit = -1;
                chr = 0;
            }
            i++;
        }
    }
    if(worked){
        return outputStr;
    }else{
        return "";
    }
}//getHiddenMessage()
