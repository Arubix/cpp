/*
  Team 2 Program 2
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "stdlib.h"

#define NUMBER_OF_MOVIES 3
#define NUMBER_OF_FILES 4

using namespace std;

int tokenize(string line);

class Matrix{
    public:
        int personID;
        int movieRate[NUMBER_OF_MOVIES];
    Matrix(int x){
        personID = x;
    }
};

int main(){
    
    int counter = 0;
    int lineCount = 0;
    int personNum;
    char movie;
    int rating;
    string line;
    vector<Matrix> PersonList;
    
    for(int x = 0; x < NUMBER_OF_FILES - 1; x++){
        stringstream ss;
	    ss << "file" << x << ".txt";
	         
	    ifstream file(ss.str().c_str());

	    if(!file.is_open())
            cout << ss.str() << " could not be opened/found." << endl;
        else{   
            
            string holdLastLine ;
            
            while(getline(file, line))
            {
                ++lineCount;
                //cout << "line=" << line << endl ;
                holdLastLine = line ;
            }
            
	        personNum = tokenize( holdLastLine );
	        cout << ss.str() << " opened successfully." << endl;
	        
	        PersonList.push_back(Matrix(personNum));
	           
	        for(int j = 0; j < NUMBER_OF_MOVIES; j++)
                PersonList.at(counter).movieRate[j] = 0;
                 
            file.clear();
            file.seekg(0);
            
            while(lineCount){
                file >> personNum >> movie >> rating;
                PersonList.at(counter).movieRate[(int)(movie-65)] = rating;
                lineCount--;
            }
            counter++;
        }  
    }
    cout << "\n\n";
    
    ofstream newFile("file.txt");
    
    for(int a = 0; a < PersonList.size(); a++){
        for(int b = 0; b < NUMBER_OF_MOVIES; b++){
            cout << "Person: " << PersonList.at(a).personID << "  Movie " << char(b+65) 
                << ": " << PersonList.at(a).movieRate[b] << endl;
            newFile << PersonList.at(a).personID << ' ' << char(b+65) << ' '
                << PersonList.at(a).movieRate[b] << endl;
        }
        cout << endl;
    }
    
    newFile.close();
    
    return 0;
}

int tokenize(string line){
    string myText(line);
    istringstream iss(myText);
    string token;
    
    getline(iss, token, ' ');
    
    int strInt = atoi(token.c_str());
    
    return strInt;
}
