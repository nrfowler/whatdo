#include <vector>
class Task{
    public:
        string what; //present-tense description of action
        string desc; //more detailed description of action
        int utils; // value which determines priority of task. Higher is more important.
        int min; //minutes duration of task.
        bool indoors; // 1 = indoors. Any timespan longer than 4 hours will require an outside task.
        bool sedentary; //1 means any sedentary activity. Too many hours of sedentary tasks will cause a non sedentary task to be added
        bool sleepfriendly; //1 means activity will not disrupt sleep if done 1-2 hours before sleep (reading, eating, etc)
        string domain; //The specific domain or ability that the utils is applied to, for instance career, meditation, walking.
        bool indefinite; //has no end time; the min is the minimum minutes to spend
        bool done; //This task is done for the day
        // void decrementMin(int completed){
            // min-=completed;
        // }
    };
     class less_than_key
    {
        public:
        inline bool operator() (const Task &struct1, const Task &struct2)
        {
            return (struct1.utils > struct2.utils);
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

