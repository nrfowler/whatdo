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
void saveSchedule(){};
void printSched(vector<Task> vec, duration length);
void rmEmptyLines(){};
duration mins2duration(int mins){ //does cpp have tio
    duration temp(mins/60,mins%60);
    return temp;
    };
int main() {
    int hours, minutes, foo;
    duration length(0,0);
            vector<Task> todo;
while (foo!=4){
    cout << endl << "What would you like to do?" << endl << "1: Make a schedule" << endl << "2: Mark Tasks as Done" << endl << "3: Add Tasks" << endl << "4. Quit" << endl;
    cin >> foo;
    if(foo==1){
        cout << "How many hours do you have?"<< endl;
        cin >>hours;
        cout << "How many minutes do you have?"<< endl;
        cin >> minutes;
        length.hours=hours;
        length.minutes=minutes;
        todo.clear();
        int min=hours*60+minutes;g
        vector<Task> tasks = readTasks();
        tasks=sortTasks(tasks);
        vector<Task>::iterator it = tasks.begin();
        while (min>=0 && it!=tasks.end()){
            if(it->min <= min) {
                todo.push_back(*it);
                //cout << it->min << endl;
            min-=it->min;
            }
            it++;
        }
        printSched(todo,length);
    }
    else if(foo==2){
        int remove,perm;
        cout << "Here is your schedule: " << endl;
            printSched(todo,length);
            cout<< "What would you like to mark as done?" <<endl;
            cin >> remove;
            cout <<"Do you want to remove it permanently (0), or just mark it done for the day? (1)"<<endl;
            cin >> perm;
            //remove task from todo and recompile schedule
            if(perm){
                //find line of file
                //delete line
            }
            else {
                //mark task as done in file
            }
            
        }
    else if(foo==3){
        Task tt;
        cout << "Enter the name of task: " << endl;
        cin >> tt.what;
        cout << "Enter the description of task: " << endl;
        cout << "Enter the utility of task: " << endl;
        cout << "Enter the duration of task, in format hours:minutes " << endl;
        cout << "Enter 1 if the task is indoors" << endl;
        cout << "Enter 1 if the task is sedentary" << endl;
        cout << "Enter 1 if the task is sleep friendly" << endl;
        cout << "Enter the domain" << endl;
        cout << "Enter 1 if the task is indefinite" << endl;



        }
    }
}

void printSched(vector<Task> todo, duration length){
    cout << "How to fill " << length.hours << " hours and " << length.minutes << " minutes: " << endl;
        for (unsigned int i =0;i<todo.size();i++){
            cout <<(i+1)<<". "<< todo[i].what << " for " << todo[i].min <<" minutes"<< endl;
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
    temptask.indoors=1;
    temptask.sedentary=1;
    temptask.sleepfriendly=1;
    temptask.domain="NA";
  int row, col;
  char buff[BUFFSIZE]; 
  ifstream infile("input.txt");
  stringstream ss;

  row = 0;
  while( infile.getline( buff,  BUFFSIZE ) && row < ROWS ) {
	ss << buff;

	col = 0;
	while( ss.getline( buff, 200, ',' ) && col < COLS ) {

      if(col==0) 
      {temptask.what=buff;}
      else if(col==1) 
      {temptask.desc=buff;}
      else if(col==2) 
      {temptask.utils=atoi(buff);}
      else if(col==3) 
      {temptask.min=atoi(buff);}
      else if(col==4) 
      {temptask.indoors=atoi(buff);}
      else if(col==5) 
      {temptask.sedentary=atoi(buff);}
      else if(col==6) 
      {temptask.sleepfriendly=atoi(buff);}
      else if(col==7) 
      {temptask.domain=buff;}
      else if(col==8) 
      {temptask.indefinite=atoi(buff);}
      
	  ++col;
	}
    tasks.push_back(temptask);

	ss << "";

	ss.clear();
	++row;
  }

	// for( int _col = 0; _col < 10; ++_col ) {
	// }
	// cout << endl;
  infile.close();






return tasks;
}
