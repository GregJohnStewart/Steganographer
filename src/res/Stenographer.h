/*  
	Header file for the Stenographer object
	
	Author: Greg Stewart
	Started: 5/29/15
*/
#ifndef STENOGRAPHER_H
#define STENOGRAPHER_H

//includes
#include "StenographerException.h"//exceptions for the object

#include <stdlib.h>  //for calloc() calloc, exit, free
#include <string>    //for strings
#include <algorithm> //for checking file extentions
//#include <sstream> //string stream
#include <iostream>  //for outputs
#include <iomanip>   //manipulate outputs
#include <sys/stat.h>//for checking filepaths
#include <queue>     //for qeueing the data
#include <cstddef>   //for size_t
#include <fstream>   //for file io
#include <cmath>     //for pow() for bit locations

//usings
using std::string;
using namespace std;

class Stenographer{
	/*
		Private variables and methods
	*/
	private:
		//instance variables
		string stringToHide; // the string we are hiding in the image
        string origFilePath; // the image we are grabbing from
        string outputDir;    // the directory we are putting the finished images in
        string curExtension; // the current file extension of the input file
        string outputFileName;   // the name of the file to output to (optional), without extension.
        const static bool debugging = true;//if we are debugging (outputs debug messages)

        /*
            Private functions
        */

        //checks if the filepath given is valid
        bool checkFilePath(string,bool);
        //checks if the extension of the filepath is valid
        bool checkFileType(string);
        //check if valid extension
        bool isValidExtension(string);
        //couts a debug message
        void sendDebugMsg(string);

        //
        //functions to do the stenography
        //
        
        //function to get data from image
        bool getImageData(queue<unsigned char>*);

        //function to process the data in the que
        bool processImageData(queue<unsigned char>*, queue<unsigned char>*, unsigned short int);

        //function to put the data into the new file
        bool putImageData(queue<unsigned char>*);
        
        //function to get the header size
        unsigned short int getHeaderSize();
        
        //function to generate a new image filename
        string getOutputFilePath();
        
        //function to grab a filename from a path w/o exception
        string getOutputFileName(string);

        //gets the current file extension
        //string getFileExtension();
        
        // gets a character from the image data
        char getCharDataFromImgData(queue<unsigned char>*);
        
        // puts a character into the queue data
        bool putCharInImgData(queue<unsigned char>*, queue<unsigned char>*, unsigned char);
        
	public:
		/*
			Constructors
		*/
		//empty constructor, inistalizes everything to nulls
		Stenographer();
        
        //sets up the object using the setup() functionws
        Stenographer(string,string,string);//origFilePath,outputDir, stringToHide
	    
		/*
			Setters
		*/
        
        /** sets up all the variables (stringToHide,origFilePath,outputDir)
            tests input/output places to make sure they work
            returns if it failed or not
        */
        bool setup(string,string,string);//origFilePath,outputDir, stringToHide
        
		// sets the new string to hide	
		void setNewStrToHide(string);

	    /* sets the image to read from
           tests the path for an image file
        */
        bool setInputImage(string);
        
        /* sets the output directory
            tests to make sure it exists
        */
        bool setOutputDir(string);

        /* sets the output filename.
            NOTE: do not give it a file extension
        */
        void setOutputName(string);
		
		/*
			Getters
		*/
        
        //gets the input file path
        string getInputPath();

        //gets the output file directory
        string getOutputDir();

        //gets the output file directory
        string getOutputPath();

        //gets the output file name
        string getOutputFileName();
        
        //gets the string that we are hiding
        string getStringToHide();

        //gets the optional output file
        string getHiddenMessage();
        
        //toString
        string toString();
        
        // returns if the object is ready to go or not
		bool ready();

        //returns if got an input
        bool gotInputPath();

        //returns if got an output path
        bool gotOutputDir();

        //returns if got a string to hide
        bool gotStringToHide();

        //does the stenography
        bool doStenography();
	
};//class Stenographer
#endif
