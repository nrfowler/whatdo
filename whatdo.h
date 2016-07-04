#include <vector>
using namespace std;

class Task{
    public:
        string what; //present-tense description of action
        string desc; //more detailed description of action
        int utils; // value which determines priority of task. Higher is more important.
        int min; //minutes duration of task.
        float utilpermin; //utility divided by min. Used to calculate schedule.
        bool indoors; // 1 = indoors. Any timespan longer than 4 hours will require an outside task.
        bool sedentary; //1 means any sedentary activity. Too many hours of sedentary tasks will cause a non sedentary task to be added
        bool sleepfriendly; //1 means activity will not disrupt sleep if done 1-2 hours before sleep (reading, eating, etc)
        string domain; //The specific domain or ability that the utils is applied to, for instance career, meditation, walking.
        bool indefinite; //has no end time; the min is the minimum minutes to spend
        bool done; //This task is done for the day
        int repeat; //0=no; 1=daily; 2=ev 2 days, etc.
        int effort;
        string due;
        // void decrementMin(int completed){
            // min-=completed;
        // }
    };
     class less_than_key
    {
        public:
        inline bool operator() (const Task &struct1, const Task &struct2)
        {
            return (struct1.utilpermin > struct2.utilpermin);
        }
    };
 class duration{
 public:
    int hours;
    int minutes;
    int toMins();
    duration(int h,int m): hours(h), minutes(m){};
    };
class Schedule{
vector<Task> tasks;
duration length;
int numTasks;
int indoors;//schedules can be created for indoor tasks or outdoor tasks
};
vector<Task> readTasks();
vector<Task> sortTasks(vector<Task> vec);
void saveTasks(vector<Task> t);
void appendTask(Task& task,ofstream& outfile);
void printSched(vector<Task> vec, duration length);
void rmEmptyLines();
void printAllTasks(vector<Task> todo);
int addTask(vector<Task>& tasks);
void doneTask(vector<Task>& tasks);
void editTaskQueryName(vector<Task> &tasks);
void editTaskByID(int num, vector<Task> &tasks);
int addTask(vector<Task>& tasks,string name);
void doneTask(vector<Task>& tasks,string name);
void editTask(vector<Task> &tasks,string name);
int searchString(vector<string> query, vector<string> record);
vector<string> getStrings(vector<Task> tasks);
vector<string> parseQuery(string in);
