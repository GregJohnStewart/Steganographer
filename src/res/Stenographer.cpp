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


/* sets the output filename.
    NOTE: do not give it a file extension
*/
void setOutputName(string){
    
}//setOutputName()

/*
    Getters
*/

//gets the input file path
string Stenographer::getInputPath(){
    return origFilePath;
}//getInputPath()

//gets the output file path
string Stenographer::getOutputDir(){
    return outputDir;
}//getOutputPath()

string Stenographer::getOutputPath(){
    
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
string Stenographer::getOutputFileName(){
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
string Stenographer::getStringToHide(){
    return stringToHide;
}//getStringToHide

string Stenographer::toString(){
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
bool Stenographer::ready(){
    bool ready = true;
    
    if(gotInputPath() && gotOutputDir() && gotStringToHide()){
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
bool Stenographer::gotOutputDir(){
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

bool Stenographer::isValidExtension(string extensionIn){
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
void Stenographer::sendDebugMsg(string message){
    if(debugging){
        cout << message << endl;
    }
}//sendDebugMsg





////////////////////////////////////////////////
////    File In/Out, stenography classes    ////
////////////////////////////////////////////////

//does the stenography

/**
 * Does the stenography by:
 *
 * 1) pulling the data into an input queue
 *
 * 2) hide the stringToHide in the data, moving thr data from the input queue to the output queue
 *      - skip over the header, just move it over
 * 
 * 3) move the stuff to the new file
 *      - 
 */
bool Stenographer::doStenography(){
    // make sure we are ready to go
    bool worked = ready();
    
    
    if(worked){
        ByteCImg image(getInputPath().c_str());
        image &= 0xfe;
        string tempStringToHide = getStringToHide() + (char)EOF;
        
        ByteCImg::iterator it = image.begin();
        int i = 0;
        for (;;) {
            if (i == tempStringToHide.length()) {
                break;
            }
            char cur = tempStringToHide[i];
            
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
            cerr << "Cannot fit the entire input in the image" << endl;
        }
        
        image.save(getOutputPath().c_str());
    }//if obj ready
    
    return worked;
}//doStenography

//gets the optional output file
string Stenographer::getHiddenMessage(){
    bool worked = ready();
    string outputStr = "";
    
    if(worked){
        ByteCImg image(getOutputPath().c_str());
    
        char * buffer = (char*) malloc(sizeof(char) * image.size());
        int bufferpos = 0;
      
        int bit = 0;
        char chr = 0;
        for (ByteCImg::iterator it = image.begin(); it != image.end(); ++bit, ++it) {
            chr |= (*it & 0x01) << bit;
            if (bit == 7) {
                buffer[bufferpos++] = chr;
                bit = -1;
                chr = 0;
            }
        }
        
        //cout << "bufferpos b4: " << (int) bufferpos << endl << "EOF: " << EOF;
        
        for (; buffer[bufferpos] != EOF; --bufferpos);
        
        //cout << "bufferpos af: " << (int) bufferpos << endl;
        
        for (int i = 0; i < bufferpos; ++i) {
            //cout << "\tBuffer: " << (int)buffer[i] << endl;
            outputStr += (int) buffer[i];
        }
    }
    
    if(worked){
        return outputStr;
    }else{
        return "";
    }
}//getHiddenMessage()

//function to get data from image
bool Stenographer::getImageData(queue<unsigned char> *inputQ){
    bool worked = true;
    
    fstream inputFileStream;
    inputFileStream.open(origFilePath.c_str(), ios::in|ios::binary);
    
    if(!inputFileStream){
        worked = false;
    }else{
        inputFileStream.seekg(0, ios::beg);
        char tempByte;
        while(!inputFileStream.eof()){
            //inputQ->push(inputFileStream.read(tempByte, 1));
            inputFileStream.read(&tempByte, sizeof tempByte);
            inputQ->push(tempByte);
            //sendDebugMsg("getting another bit of info");
        }
    }
    inputFileStream.close();
    
    return worked;
}//getImageData()

//function to process the data in the que
bool Stenographer::processImageData(queue<unsigned char> *inputQ, queue<unsigned char> *outputQ, unsigned short int headerSize){
    sendDebugMsg("Begin processing image data");
    bool worked = true;
    unsigned char curByte;
    //move header over
    for(unsigned short int i = 1; i <= headerSize && !inputQ->empty(); i++){
        outputQ->push(inputQ->front());
        inputQ->pop();
        //sendDebugMsg("moving a byte of the header");
    }
    
    //process string
    bool processWorked = true;
    for(int i = 0;i < stringToHide.length() && !inputQ->empty();i++){
        processWorked = putCharInImgData(inputQ, outputQ, stringToHide.at(i));
        if(!processWorked){
            throw StenographerException("Failed processing image data. Failed putting char data into image data.");
        }
    }

    //dump rest over
    while(!inputQ->empty()){
        curByte = inputQ->front();
        inputQ->pop();
        outputQ->push(curByte);
    }
    return worked;
}//processImageData()

//function to put the data into the new file
bool Stenographer::putImageData(queue<unsigned char> *outputQ){
    bool worked = true;
    //determine new filename
    string outputFilePath = getOutputPath();
    sendDebugMsg("output file path: " + outputFilePath + "\n");    
    //open new file @ outputFilePath
    fstream outputFileStream;
    outputFileStream.open(outputFilePath.c_str(), fstream::out|fstream::binary|fstream::trunc);
    
    if(!outputFileStream){
        worked = false;
    }else{
        sendDebugMsg("setup output file");  
        outputFileStream.seekg(0, ios::beg);
        
        sendDebugMsg("putting info into file: ");
        
        do{
            outputFileStream.put(outputQ->front());
            //sendDebugMsg("info");
            outputQ->pop();
            //sendDebugMsg("");
        }while(!outputQ->empty());
    }
    outputFileStream.close();
    
    return worked;
}//putImageData()

//function to get the header size in number of bytes
unsigned short int Stenographer::getHeaderSize(){
    //based on: http://stackoverflow.com/questions/10423942/what-is-the-header-size-of-png-jpg-jpeg-bmp-gif-and-other-common-graphics-for
    unsigned short int multiplier = 3;
    sendDebugMsg("getHeaderSize() - extension: " + curExtension);
    if(curExtension == "jpg"){
        //TODO: do more to be more accurate. see source above
        return 2 * multiplier;
    }else if(curExtension == "bmp" || curExtension == "gif"){
        return 14 * multiplier;
    }else if(curExtension == "png"){
        return 8 * multiplier;
    }else{
        throw StenographerException("Failed determining image header file size. Invalid extension given.");
    }
}//get HeaderSize

// gets a character from the image data
char Stenographer::getCharDataFromImgData(queue<unsigned char> *inputQ){
    unsigned char charBuilding = 0;
    
    return charBuilding;
}// getCharDataFromImgData(queue<unsigned char>*)
        
// puts a character into the queue data
bool Stenographer::putCharInImgData(queue<unsigned char> *inputQ, queue<unsigned char> *outputQ, unsigned char inputChar){
    bool worked = true;
    bool finished = false;
    //cout<<"Current Char: " << inputChar << endl;
    //cout<<"sizeof unsigned Char: " << sizeof(inputChar) << endl;
    unsigned char curData;
    unsigned short int tempBitLoc = 0;
    bool tempBit = 0;
    bool tempInBit = 0;
    unsigned short int bitSize = sizeof(unsigned char) * 8;
    //cout<<"bitSize: " << bitSize << endl;                 
    for(int i = 0;(i < bitSize) && !inputQ->empty();i++){
        //update temp bit to the one we are on
        tempBitLoc = pow(2,i);

        curData = inputQ->front();
        inputQ->pop();
        
        //move data through
        tempBit = inputChar & tempBitLoc;
        tempInBit = curData & 1;
        //cout<<tempBit<<endl;//debugging
        
        //cout<<"curData defore: "<< (int)curData;
        
        if(tempBit){
            if(!tempInBit){ 
                curData++;
            }
        }else{
            if(tempInBit){
                curData--;
            }
        }
        //cout << " curData after: " << (int)curData << endl;
        outputQ->push(curData);
        
        if(inputQ->empty()){
            finished = true;
        }
    }    
    if(finished){
        worked = false;
    }
    
    return worked;
}// putCharInImgData(queue<unsigned char>*, unsigned char)