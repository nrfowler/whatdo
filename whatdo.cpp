#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "whatdo.h"
using namespace std;

const int ROWS = 100;//max. # of tasks in input file
const int COLS = 14;//number of task fields
const int BUFFSIZE = 900;//maximum size of a task line in input file
//convert @mins to duration object; not currently in use
duration mins2duration(int mins){
    duration temp(mins/60,mins%60);
    return temp;
};
int main(int argc, char** argv) {
    int hours, minutes;
    string foo;
    duration length(0,0);
    vector<Task> todo;
    //backups input.txt by creating input{timestamp}.txt
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    stringstream ss;
    ss << (now->tm_year + 1900) << '-'
    << (now->tm_mon + 1) << '-'
    <<  now->tm_mday;
    string backup="backup/input_"+ss.str()+".txt";
    ifstream  src("input.txt", std::ios::binary);
    ofstream  dst(backup.c_str(),   std::ios::binary);
    dst << src.rdbuf();
    vector<Task> tasks = readTasks();
    if(argc==1){
        while (foo!="q"){
            cout << endl << "What would you like to do?" << endl << "s: Make a schedule" << endl << "d: Mark Tasks as Done" << endl << "a: Add Tasks" << endl << "e: Edit Tasks"<<endl << "k: Delete Tasks" << endl << "p: Print All Tasks"<<endl << "q. Quit" << endl;
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
                tasks=sortTasks(tasks);
                vector<Task>::iterator it = tasks.begin();
                while (min>=0 && it!=tasks.end()){
                    if((it->min <= min) && (it->done!=1)) {
                        todo.push_back(*it);
                    min-=it->min;
                    cout<<it->what<<endl;
                    }
                    it++;
                }
                printSched(todo,length);
            }
            else if(foo=="d"){
                    doneTask(tasks);
                }
            else if(foo=="p"){
                    printAllTasks(tasks);
                }
            else if(foo=="a"){
              addTask(tasks);
                }
            else if(foo=="e"){
                    editTaskQueryName(tasks);
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
    else if (argc==2){
        if(argv[1][1]=='-'){
            if(strcmp(argv[1],"--add")==0){
                addTask(tasks);
            }
            else if(strcmp(argv[1],"--done")==0){
                doneTask(tasks);
            }
        }
        else if(argv[1][0]=='-'){
            if(strcmp(argv[1],"-a")==0){
                addTask(tasks);
            }
            else if(strcmp(argv[1],"-d")==0){
            cout<<"task doned";
                doneTask(tasks);
            }
        }
        else cout<<"Error"<<endl;
    saveTasks(tasks);
    }
    else if (argc>2){
        string args;
        for (int i =2;i<argc;i++){
            args+=string(argv[i])+" ";
            }
        if(argv[1][1]=='-'){
            if(strcmp(argv[1],"--add")==0){
                addTask(tasks,args);
            }
            else if(strcmp(argv[1],"--done")==0){
                doneTask(tasks,args);
            }
            else if(strcmp(argv[1],"--edit")==0){
                editTask(tasks,args);
            }
        }
        else {
            if(strcmp(argv[1],"-a")==0){
                addTask(tasks,args);
            }
            else if(strcmp(argv[1],"-d")==0){
                doneTask(tasks,args);
            }
            else if(strcmp(argv[1],"-e")==0){
                editTask(tasks,args);
            }
        }
    saveTasks(tasks);
    }
    else std::cout << "error" << std::endl ;
}
//query user for task to be edited, and edit the task
void editTaskQueryName(vector<Task> &tasks){
    if(tasks.size()==0){
        cout<<"No tasks found"<<endl;
           return;
    }
    Task tt;
    int num,field;
    string newval;
    printAllTasks(tasks);
    cout<< "Which task would you like to edit?" <<endl;
    cin >> num;
    editTaskByID(num,tasks);
    return;
}
void editTaskByID(int num, vector<Task> &tasks){
    string newval;
    int field;
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
        tasks[num-1].utilpermin=atof(cstr);
        break;
     case 6:
        tasks[num-1].indoors=atoi(cstr);
        break;
    case 7:
        tasks[num-1].sedentary=atoi(cstr);
        break;
    case 8:
        tasks[num-1].sleepfriendly=atoi(cstr);
        break;
    case 9:
        tasks[num-1].domain=newval;
        break;
    case 10:
        tasks[num-1].indefinite=atoi(cstr);
        break;
    case 11:
        tasks[num-1].done=atoi(cstr);
        break;
    case 12:
        tasks[num-1].repeat=atoi(cstr);
        break;
    case 13:
        tasks[num-1].effort=atoi(cstr);
        break;
    default:
        break;
    }
}
//search tasks for best match of name; edit the selected task
void editTask(vector<Task> &tasks, string name){
    if(tasks.size()==0){
        cout<<"No tasks found"<<endl;
       return;
    }
    Task tt;
    int num,field;
    string newval;
    //search for task name
    vector<string> query=parseQuery(name);
    vector<string> taskstrings=getStrings(tasks);
    editTaskByID(searchString(query,taskstrings),tasks);
    return;
}
//queries user for task name and deletes task
void doneTask(vector<Task> &tasks){
    int remove,perm;
    if(tasks.size()==0){
        cout<<"No tasks found"<<endl;
        return;
    }
    printAllTasks(tasks);
    cout<< "What would you like to mark as done?" <<endl;
    cin >> remove;
    cout <<"This task has been marked done"<<endl;
    perm=0; //implement repeat task test here
    if(perm){
        tasks.erase(tasks.begin()+remove-1);
    }
    else {
        tasks[remove-1].done=~tasks[remove-1].done;
    }
}
//searches tasks by name and deletes the task that matches name best
void doneTask(vector<Task> &tasks, string name){
    int remove,perm;
    vector<string> query (15);
    vector<string> taskstrings (tasks.size());
    if(tasks.size()==0){
        cout<<"No tasks found"<<endl;
        return;
    }
    //printAllTasks(tasks);
    query=parseQuery(name);
    cout<<query.size()<<endl;
    //remove "the"
    taskstrings=getStrings(tasks);
    cout<<query[0]<<endl;
    remove=searchString(query,taskstrings);
    perm=0; //implement repeat task test here
    if(perm){
        tasks.erase(tasks.begin()+remove);
    }
    else {
        tasks[remove].done=1;
    }
    cout <<"This task has been marked done"<<endl;
    return;
}
//returns vector of strings of what field from tasks vector
vector<string> getStrings(vector<Task> tasks){
    vector<string> names (tasks.size());
    for (int i =0;i<tasks.size();i++){
        names[i]=tasks[i].what;
    }
    return names;
}
//parses a string by spaces
vector<string> parseQuery(string in){
    istringstream ss(in);
    string buff;
    int i=0;
    vector<string> out(15);
    while (getline( ss,buff, ' ' )){
        out[i]=buff;
        i++;
    }
    out.resize(i);
    return out;
}
    //record needs to be converted into 2d array, or searchString has to parse record
// searches the query vector for the highest number of matches of strings in record.
// returns index of string in query with the most matches
int searchString(vector<string> query, vector<string> record){
    int score,rid=1,maxscore=0;
    for (int i =0;i<record.size();i++){
        score =0;
        for (int j =0;j<query.size();j++){
            if(query[j].compare(record[i])==0){
                score+=3;
            }
            //else if(_stricmp(query[j],record[j])==0)score+=2;
            //string compare case insensitive din description score+=1
        }
        if(score>maxscore){
            maxscore=score;
            rid=i;
        }
    }
    return rid;
}
//print a vector of tasks that represent a schedule
void printSched(vector<Task> todo, duration length){
    if(todo.size()==0){
        cout<<"No tasks found"<<endl;
        return;
    }
    cout <<endl<< "How to fill " <<length.hours << " hours and " << length.minutes << " minutes: \n \n";
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
//print all tasks to console
void printAllTasks(vector<Task> todo){
    cout <<endl<< "All your tasks: " << endl;
    for (unsigned int i =0;i<todo.size();i++){
        cout <<(i+1)<<". "<< todo[i].what << " for " << todo[i].min <<" minutes ("<<todo[i].utilpermin<<" utils)";
        if(todo[i].done==1){
            cout<<" DONE"<<endl;
        }
        else{
            cout<<endl;
        }
    }
}
//add a task with the title of @name to a tasks vector.
int addTask(vector<Task>& tasks, string name){
    Task tt;
    string newval,newvaldesc;
    tt.what=name;
    tt.desc="test";
    cout << "The new task description is: " <<tt.desc<< endl;
    cout << "Enter the utility of task: " << endl;
    cin >> tt.utils;
    cin.ignore();
    cout << "Enter the duration of task, in total minutes " << endl;
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
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    stringstream ss;
    ss << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;
    tt.due=ss.str();
     tasks.push_back(tt);
    return 1;
}
//add a task and query for the name in console
int addTask(vector<Task>& tasks){
    Task tt;
    string newval,newvaldesc;
    cout << "Enter the name of task: " << endl;
    cin.ignore();
    getline (cin,newval);
    tt.what=newval;
    cout << "The new task name is: " <<tt.what<< endl;
    cout << "Enter the description of task: " << endl;
    getline (cin,newvaldesc);
    tt.desc=newvaldesc;
    cout << "The new task description is: " <<tt.desc<< endl;
    cout << "Enter the utility of task: " << endl;
    cin >> tt.utils;
    cout << "Enter the duration of task, in total minutes " << endl;
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
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    stringstream ss;
    ss << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;
    tt.due=ss.str();
     tasks.push_back(tt);
    return 1;
        }
//sorts tasks based on utility
vector<Task> sortTasks(vector<Task> vec){
    sort(vec.begin(), vec.end(), less_than_key());
    printAllTasks(vec);
    return vec;
}
//writes a single task to file
void appendTask(Task& task,ofstream& outfile){
  outfile <<task.what<<","<<task.desc<<","<<task.utils<<","<<task.min<<","
  <<task.utilpermin<<","<<task.indoors<<","<<task.sedentary<<","<<task.sleepfriendly
  <<","<<task.domain<<","<<task.indefinite<<","<<task.done<<","<<task.repeat<<","
  <<task.effort<<","<<task.due<<endl;
  return;
}
//saves tasks to file
void saveTasks(vector<Task> tasks){
    vector<Task>::iterator it = tasks.begin();
    ofstream outfile("input.txt");
    while (it!=tasks.end()){
        appendTask(*it,outfile);
        it++;
    }
    outfile.close();
}
//read tasks from file and return a vector<Task> containing them
vector<Task> readTasks(){
    vector<Task> tasks;
    string scoreline, temp;
    Task temptask;
    temptask.what="test";
    temptask.desc="0";
    temptask.utils=1;
    temptask.min=30;
    temptask.utilpermin=.001;
    temptask.indoors=1;
    temptask.sedentary=1;
    temptask.sleepfriendly=1;
    temptask.domain="NA";
    temptask.done=0;
    temptask.repeat=0;
    temptask.due="2016-5-19";
    int row, col;
    char buff[BUFFSIZE];
    ifstream infile("input.txt");
    stringstream ss;
    row = 0;
    while( infile.getline( buff,  BUFFSIZE ) && row < ROWS) {
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
            {
                if(temptask.min!=0){
                temptask.utilpermin=(float)temptask.utils/(float)temptask.min;
                }
                else{
                temptask.utilpermin=.001;
                }
            }
            else if(col==5)
            {temptask.indoors=atoi(buff);}
            else if(col==6)
            {temptask.sedentary=atoi(buff);}
            else if(col==7)
            {temptask.sleepfriendly=atoi(buff);}
            else if(col==8)
            {temptask.domain=buff;}
            else if(col==9)
            {temptask.indefinite=atoi(buff);}
            else if(col==10)
            {temptask.done=atoi(buff);}
            else if(col==11)
            {temptask.repeat=atoi(buff);}
            else if(col==12)
            {temptask.effort=atoi(buff);}
            else if(col==13)
            {temptask.due=buff;}
            ++col;
        }
        if(col==COLS){ //make sure task had enough fields
            tasks.push_back(temptask);
        }
        ss << "";
        ss.clear();
        ++row;
    }
    if(tasks.size()==0){
        tasks.push_back(temptask);
    }
    infile.close();
    return tasks;
}
