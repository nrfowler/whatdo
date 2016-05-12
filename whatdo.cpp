#include <cassert>
#include <cstdlib>
using namespace std;
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "whatdo.h"
#include <vector>
#include <algorithm>
const int ROWS = 100;
const int COLS = 9;
const int BUFFSIZE = 500;
vector<Task> readTasks();
vector<Task> sortTasks(vector<Task> vec); 
void addTask(){}; 
void rmTask(){};
duration mins2duration(int mins){ //does cpp have tio
    duration temp(mins/60,mins%60);
    return temp;
    };
int main() {
    int hours, minutes;
    cout << "How many hours do you have?"<< endl;
    cin >>hours;
    cout << "How many minutes do you have?"<< endl;
    cin >> minutes;
    int min=hours*60+minutes;
    vector<Task> tasks = readTasks();
    tasks=sortTasks(tasks);
    vector<Task> todo;
    vector<Task>::iterator it = tasks.begin();
    while (min>=0 && it!=tasks.end()){
        if(it->min <= min) {
            todo.push_back(*it);
        min-=it->min;
        }
        it++;
    }
    cout << "How to fill " << hours << " hours and " << minutes << " minutes: " << endl;
    for (unsigned int i =0;i<todo.size();i++){
        cout <<(i+1)<<". "<< tasks[i].what << " for " << tasks[i].min <<" minutes"<< endl;
    }
}

vector<Task> sortTasks(vector<Task> vec){

    sort(vec.begin(), vec.end(), less_than_key());
    return vec;
}


vector<Task> readTasks(){
    vector<Task> tasks;
    string scoreline, temp;
    Task temptask;
    temptask.desc="0";
    temptask.utils=1;
    temptask.min=30;
    temptask.outside=1;
    temptask.sedentary=1;
    temptask.sleepfriendly=1;
    temptask.domain="NA";
  // The array must be big enough to fit the input data.
  int row, col;
  char buff[BUFFSIZE]; // a buffer to temporarily park the data
  ifstream infile("input.txt");
  stringstream ss;
  // Read input into the buffer a line at a time, until
  //  end of file is reached (newlines are automatically
  //  discarded).  The buffer must be big enough to fit
  //  an entire line from the file.
  // Notice that while reading from the file we check how
  //  many rows have been read, to avoid writing beyond
  //  the end of the array.
  row = 0;
  while( infile.getline( buff,  BUFFSIZE ) && row < ROWS ) {
	// copy the entire buffered line into the stringstream
	ss << buff;
	// Read from ss back into the buffer.  Now, ',' is
	//  specified as the delimiter so it reads only until
	//  it reaches a comma (which is automatically
	//  discarded) or reaches the 'eof', but of course
	//  this 'eof' is really just the end of a line of the
	//  original input.  The "10" means this will handle
	//  input numbers of 9 digits or less.
	//  While reading from the stringstream, we check
	//  how many columns have been read to avoid
	//  writing past the end of the array.
	col = 0;
    //cout << buff << endl;
	while( ss.getline( buff, 200, ',' ) && col < COLS ) {
	  // Next, use the stdlib atoi function to convert the
	  //  input value that was just read from ss to an int,
	  //  and copy it into the array.
      if(col==0) 
      {temptask.what=buff;}
      else if(col==1) 
      {temptask.desc=buff;}
      else if(col==2) 
      {temptask.utils=atoi(buff);}
      else if(col==3) 
      {temptask.min=atoi(buff);}
      else if(col==4) 
      {temptask.outside=atoi(buff);}
      else if(col==5) 
      {temptask.sedentary=atoi(buff);}
      else if(col==6) 
      {temptask.sleepfriendly=atoi(buff);}
      else if(col==7) 
      {temptask.domain=buff;}
      else if(col==8) 
      {temptask.indefinite=atoi(buff);}
      
      //cout << col<<": "<<buff << " ";
	  ++col;
	}
    tasks.push_back(temptask);
	// This copies an empty string into ss, erasing the
	//  previous contents.
	ss << "";
	// This clears the 'eof' flag.  Otherwise, even after
	//  writing new data to ss we wouldn't be able to
	//  read from it.
	ss.clear();
	++row;
  }
  // Now print the array to see the result
  //for( int _row = 0; _row < 10; ++_row ) {
	for( int _col = 0; _col < 10; ++_col ) {
	  //cout << tasks[_col].desc << " ";
	}
	cout << endl;
 // }
  infile.close();






return tasks;
}
