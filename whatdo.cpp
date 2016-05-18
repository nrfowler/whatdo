#include <cassert>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "whatdo.h"
using namespace std;
//Summary: mark as done, edit task completed. added "effort" field. Main command prompt now letter based.
//Details:
//updated COLS const
//added repeat field to import and save to file
//[ ] search by task name
    //[ ] search function for Task vector
//[tested] save tasks vector to file - works
// [x] save file after editing task
//[x] add edit for every field
//[x] allow edit to take spaces in string by using getline
//[ ] update tasks every day using ctime, see http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c

const int ROWS = 100;//max. # of tasks in input file
const int COLS = 12;//number of task fields
const int BUFFSIZE = 900;//maximum size of a task line in input file
vector<Task> readTasks();
vector<Task> sortTasks(vector<Task> vec); 
void saveTasks(vector<Task> t);
void appendTask(Task& task,ofstream& outfile);
void printSched(vector<Task> vec, duration length);
void rmEmptyLines();
void printAllTasks(vector<Task> todo);
duration mins2duration(int mins){ //does cpp have tio
    duration temp(mins/60,mins%60);
    return temp;
    };
int main() {
    int hours, minutes;
    string foo;
    duration length(0,0);
            vector<Task> todo;
            vector<Task> tasks = readTasks();
while (foo!="q"){
    cout << endl << "What would you like to do?" << endl << "s: Make a schedule" << endl << "d: Mark Tasks as Done" << endl << "a: Add Tasks" << endl << "e: Edit Tasks"<<endl << "k: Delete Tasks" << endl << "q. Quit" << endl;
    cin >> foo;
    if(foo=="s"){
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
            if((it->min <= min) && (it->done!=1)) {
                todo.push_back(*it);
                //cout << it->min << endl;
            min-=it->min;
            }
            it++;
        }
        printSched(todo,length);
    }
    else if(foo=="d"){
        int remove,perm;
        printAllTasks(tasks);
        cout<< "What would you like to mark as done?" <<endl;
        cin >> remove;
        cout <<"This task has been marked done"<<endl;
        perm=0; //implement repeat task test here
        if(perm){
            tasks.erase(tasks.begin()+remove-1);
        }
        else {
            tasks[remove-1].done=1;
        }
            
        }
    else if(foo=="a"){
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
        cout << "Enter effort" << endl;
        cin >> tt.effort;
        tasks.push_back(tt);



        }
        
        
    else if(foo=="e"){
        Task tt;
        int num,field;
        string newval;
        printAllTasks(tasks);
        cout<< "Which task would you like to edit?" <<endl;
        cin >> num;
        cout<< "Which field would you like to edit?" <<endl;
        cout<<"n. Name of task \n 2. Description \n u. Utility \n m. Minutes duration \n i. Indoors? \n 6. Sedentary \n 7. Sleep friendly \n 8. Domain \n 9. Indefinite \n 10. Done \n 11. Repeat \n 12. Effort"<<endl;
        cin>>field;
        cout<<"Enter the new value"<<endl;
        cin.ignore();
        getline (cin,newval);
        char *cstr = new char[newval.length() + 1];
        strcpy(cstr, newval.c_str());
        switch (field){
        case 1:
            tasks[num-1].what=newval;
            break;
        case 2:
            tasks[num-1].desc=newval;
            break;
        case 3:
            tasks[num-1].utils=atoi(cstr);
            break;
        case 4:
            tasks[num-1].min=atoi(cstr);
            break;
         case 5:
            tasks[num-1].indoors=atoi(cstr);
            break;
        case 6:
            tasks[num-1].sedentary=atoi(cstr);
            break;
        case 7:
            tasks[num-1].sleepfriendly=atoi(cstr);
            break;
        case 8:
            tasks[num-1].domain=newval;
            break;
        case 9:
            tasks[num-1].indefinite=atoi(cstr);
            break;
        case 10:
            tasks[num-1].done=atoi(cstr);
            break;
        case 11:
            tasks[num-1].repeat=atoi(cstr);
            break;
        case 12:
            tasks[num-1].effort=atoi(cstr);
            break;
        default:
            break;
        }
        //BUG: displays 5 command prompts after this
    }
    else if(foo=="k"){
        Task tt;
        int num;
        string newval;
        printAllTasks(tasks);
        cout<< "Which task would you like to delete?" <<endl;
        cin >> num;
        tasks.erase(tasks.begin()+num-1);
    }
    else if(foo=="q"){
    cout << "Goodbye"<<endl;
    saveTasks(tasks);
    return 0;
    }
}
}

void printSched(vector<Task> todo, duration length){
    cout <<endl<< "How to fill " << length.hours << " hours and " << length.minutes << " minutes: \n \n";
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
        cout <<(i+1)<<". "<< todo[i].what << " for " << todo[i].min <<" minutes";
        if(todo[i].done==1){
            cout<<" DONE"<<endl;
        }
        else
        {
            cout<<endl;
            }
    }
}

vector<Task> sortTasks(vector<Task> vec){

    sort(vec.begin(), vec.end(), less_than_key());
    return vec;
}
void appendTask(Task& task,ofstream& outfile){
                cout << task.what <<" "<< task.done<< endl;

  outfile <<task.what<<","<<task.desc<<","<<task.utils<<","<<task.min<<","<<task.indoors<<","<<task.sedentary<<","<<task.sleepfriendly<<","<<task.domain<<","<<task.indefinite<<","<<task.done<<","<<task.repeat<<","<<task.effort<<endl;
  return;
}
void saveTasks(vector<Task> tasks){
    vector<Task>::iterator it = tasks.begin();
    ofstream outfile("input.txt");
    while (it!=tasks.end()){
            
                appendTask(*it,outfile);
                //cout << it->what << endl;
            
            it++;
        }
    outfile.close();
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
    temptask.done=0;
    temptask.repeat=0;
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
      else if(col==9) 
      {temptask.done=atoi(buff);}
      else if(col==10) 
      {temptask.repeat=atoi(buff);}
      else if(col==11) 
      {temptask.effort=atoi(buff);}
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
