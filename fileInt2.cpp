/* C++ Programming
   Final Individual Project
   Working with Dates, Times, and Files.
*/

//***Please make sure MAR23_ files are in local directory of cpp file before running***//

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <iomanip>

using namespace std;

//functions
void convertTime(unsigned long long t, ofstream &dateTime, string months[], 
                 class Time *eTime, ofstream &csv);
void initialFileRename();       //more info at function

//classes
class Time{
    public:
        double hours, minutes, seconds;
        int year, month, day;
};

int main(){
    
    int sensor1, sensor2, sensor3;
    unsigned long long time;   //holds time in milliseconds
    double temp;    
    string line;
    char ch;                    //separator for commas in files
    string months[12] = {"January", "February", "March", "April", "May", "June", "July", 
                            "August", "September", "October", "November", "December"};
   
    Time eTime;
    
    initialFileRename();
    
    ofstream write("Mar 23 2013.txt");  //file to be created with new daata and format
    ofstream csv("csvData.csv");        //created csv for excel graphs
    
    for(int x = 1; x <= 50; x++){
        
        stringstream ss;
	    ss << "MAR23_" << x;
	    
	    ifstream file(ss.str().c_str());

	    if(!file.is_open())
            cout << ss.str() << " could not be opened/found." << endl;
        else{  
            
            while(getline(file,line)){
                
                istringstream iss(line);
                
                iss >> time >> ch >> sensor1 >> ch >> temp >> ch >> 
                        sensor2 >> ch >> sensor3;    
                
                convertTime(time, write, months, &eTime, csv);
    
                write << "  Temperature:" << setw(6) << temp 
                      << "ºF  S1:" << setw(7) << sensor1 << "  S2:" << setw(3) 
                      << sensor2 << "  S3:" << setw(3) << sensor3 << endl;
                      
                csv << temp << "," << sensor1 << "," << sensor2 << "," << sensor3 << endl;
            }
            file.close();
        }  
    }
    write.close();
    csv.close();
    
    system("start csvData.csv");
    
    cout << "Press F11 on the Excel screen to continue.\n" << endl;
    
    system("pause");
    return 0;
}

void convertTime(unsigned long long t, ofstream &dateTime, string months[], Time *eTime,
                    ofstream &csv){
    //from jan 1 to mar 23  1364011200 seconds  1364011200000 milliseconds
    t += 1364011200000ULL;              //epoch of March 23 2013
    
    eTime->seconds = t % 60;
    t /= 60000;
    eTime->minutes = t % 60;
    t /= 60;
    eTime->hours = fmod(t, 24) - 4;    //-4 converts to EST
    t /= 24;
    
	if(eTime->hours < 0)                 //prevents hours from going into the negatives
        eTime->hours = 24 + eTime->hours;
    
    eTime->year = 2013;
    eTime->month = 3;
    eTime->day = 23;
    
    dateTime << months[eTime->month-1] << " " << eTime->day << ", " << eTime->year << "  "
             << setw(2) << eTime->hours << ":" << setw(2) << eTime->minutes << ":" 
             << setw(2) << eTime->seconds;
             
    csv << eTime->year << "/0" << eTime->month << "/" << eTime->day << ","
             << eTime->hours << ":" << eTime->minutes << ":" << eTime->seconds << ",";
}
//This function changes the initial file since it does not have the traditional file 
//name like the others
void initialFileRename(){
    string line;
    
    ifstream first("MAR23_");
    ofstream second("MAR23_1");
    
    if(!first.is_open())
        cout << "MAR23_ could not be opened/found." << endl;
    else
        while(getline(first,line))
            second << line << endl;
        
    first.close();
    second.close();
}
