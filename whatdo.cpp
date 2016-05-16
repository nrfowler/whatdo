#include <cassert>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "whatdo.h"
using namespace std;
//TODO: 
//[X] don't print "-" when no description - boolean null string
//[ ] search by task name
    //[ ] search function for Task vector
//[x] mark task done 
//[ ] delete task
    //[ ] delete a vector element
//[test] edit task function
    //[ ] Programmatic selection of class member variable
//[test] save tasks vector to file
//[test] add task to task vector
//[ ] update tasks every day
    //[ ] see if chron or native function can return current date

const int ROWS = 100;
const int COLS = 9;
const int BUFFSIZE = 500;
vector<Task> readTasks();
vector<Task> sortTasks(vector<Task> vec); 
void addTask(){}; 
void rmTask(){};
void saveSchedule(){};
void appendTask();
void printSched(vector<Task> vec, duration length);
void rmEmptyLines();
void printAllTasks(vector<Task> todo);
duration mins2duration(int mins){ //does cpp have tio
    duration temp(mins/60,mins%60);
    return temp;
    };
int main() {
    int hours, minutes, foo;
    duration length(0,0);
            vector<Task> todo;
            vector<Task> tasks = readTasks();
while (foo!=4){
    cout << endl << "What would you like to do?" << endl << "1: Make a schedule" << endl << "2: Mark Tasks as Done" << endl << "3: Add Tasks" << endl << "4: Edit Tasks"<<endl << "5: Delete Tasks" << endl << "6. Quit" << endl;
    cin >> foo;
    if(foo==1){
        cout << "How many hours do you have?"<< endl;
        cin >>hours;
        cout << "How many minutes do you have?"<< endl;
        cin >> minutes;
        length.hours=hours;
        length.minutes=minutes;
        todo.clear();
        int min=hours*60+minutes;
        tasks = readTasks();
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
        printAllTasks(tasks);
        cout<< "What would you like to mark as done?" <<endl;
        cin >> remove;
        cout <<"Do you want to remove it permanently (0), or just mark it done for the day? (1)"<<endl;
        cin >> perm;
        //remove task from tasks
        printAllTasks(tasks);
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
        cin >> tt.desc;
        cout << "Enter the utility of task: " << endl;
        cin >> tt.utils;
        cout << "Enter the duration of task, in format hours:minutes " << endl;
        cin >> tt.min;
        cout << "Enter 1 if the task is indoors" << endl;
        cin >> tt.indoors;
        cout << "Enter 1 if the task is sedentary" << endl;
        cin >> tt.sedentary;
        cout << "Enter 1 if the task is sleep friendly" << endl;
        cin >> tt.sleepfriendly;
        cout << "Enter the domain" << endl;
        cin >> tt.domain;
        cout << "Enter 1 if the task is indefinite" << endl;
        cin >> tt.indefinite;
        cout << "Enter repeat" << endl;
        cin >> tt.repeat;
        tasks.push_back(tt);



        }
        
        
    else if(foo==4){
        Task tt;
        int num,field;
        string newval;
        printAllTasks(tasks);
        cout<< "Which task would you like to edit?" <<endl;
        cin >> num;
        cout<< "Which field would you like to edit?" <<endl;
        cout<<"1. Name of task \n 2. Description \n 3. Utility \n 4. Minutes duration \n 5. Indoors? \n 6. Sedentary \n 7. Sleep friendly \n 8. Domain \n 9. Indefinite \n 10. Done \n 10. Repeat"<<endl;
        cin>>field;
        cout<<"Enter the new value"<<endl;
        cin>>newval;
        //tasks[num-1].field??=newval;
    }
    else if(foo==4){
        Task tt;
        int num,field;
        string newval;
        printAllTasks(tasks);
        cout<< "Which task would you like to delete?" <<endl;
        cin >> num;
        //delete tasks[num-1];
    }
}
}

void printSched(vector<Task> todo, duration length){
    cout <<endl<< "How to fill " << length.hours << " hours and " << length.minutes << " minutes: " << endl;
    if(todo[0].indefinite){ //most important task is of undefined maximum duration
        if(todo[0].desc!=""){
        cout << todo[0].what <<" - "<<todo[0].desc<< endl;
        }
        else{
        cout << todo[0].what << endl;

        }
        return;
        }
        for (unsigned int i =0;i<todo.size();i++){
            if(todo[i].desc.length()!=0){
                cout <<(i+1)<<". "<< todo[i].what <<" - "<<todo[i].desc<< " -  for " << todo[i].min <<" minutes"<< endl;
            }
            else{
                cout <<(i+1)<<". "<< todo[i].what << " for " << todo[i].min <<" minutes"<< endl;
            }
        }
}

void printAllTasks(vector<Task> todo){
    cout <<endl<< "All your tasks: " << endl;
    for (unsigned int i =0;i<todo.size();i++){
        cout <<(i+1)<<". "<< todo[i].what << " for " << todo[i].min <<" minutes"<< endl;
    }
}

vector<Task> sortTasks(vector<Task> vec){

    sort(vec.begin(), vec.end(), less_than_key());
    return vec;
}
void appendTask(Task task){
    ofstream outfile("input.txt");
  stringstream ss;
  ss <<task.what<<","<<task.desc<<","<<task.utils<<","<<task.min<<","<<task.indoors<<","<<task.sedentary<<","<<task.sleepfriendly<<","<<task.domain<<","<<task.indefinite<<","<<task.done<<endl;
  outfile.close();
  return;
}
void saveTasks(vector<Task> tasks){
    vector<Task>::iterator it = tasks.begin();
    while (it!=tasks.end()){
            
                appendTask(*it);
                //cout << it->min << endl;
            
            it++;
        }

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
