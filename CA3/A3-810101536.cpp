#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

const int NUMBER_OF_DAYS = 5;
const int NUMBER_OF_SHIFTS_PER_DAY = 3;
const int CLASS_NUMBER_1 = 1;
const int CLASS_NUMBER_2 = 2;



typedef struct TIME {
	int hours;
	int minutes;
}Time;

typedef struct CLASS_TIME
{
    string day;
    string time;
}ClassTime;

typedef struct TEACHER
{
    string name;
    vector<string> freeDays;
    vector<string> courses;
    vector<ClassTime> classTime;
}Teacher;

typedef struct COURSE
{
    string name;
    vector<string> days;
    vector<Time> times; 
    vector<string> times_str;
}Course;

typedef struct OUTPUT_COURSE
{
    Course course;
    vector<Teacher> teachers;
    vector<string> startTime;
    vector<string> endTime;
    bool check;
}OutputCourse;



Time create_time(string time_str) 
{
	Time result;
	result.hours = atoi(time_str.substr(0, 2).c_str());
	result.minutes = atoi(time_str.substr(3).c_str());
	return result;
}

vector<Teacher> get_teachers()
{
    int numOfFreeDays = 0 , numOfCourses = 0 , n = 0;
    vector<Teacher> teachers;
    string day , course ;
    Teacher temp;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        temp.freeDays.clear();
        temp.courses.clear();
        cin >> temp.name;
        cin >> numOfFreeDays;
        for (int j = 0; j < numOfFreeDays; j++)
        {
            cin >> day;
            temp.freeDays.push_back(day);
        }
        cin >> numOfCourses;
        for (int j = 0; j < numOfCourses; j++)
        {
            cin >> course;
            temp.courses.push_back(course);
        }
        teachers.push_back(temp);
    }
    return teachers;
}

vector<Course> get_courses()
{
    vector<Course> courses;
    string day , time_str;
    Course temp;
    int k = 0;
    Time time;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        temp.days.clear();
        temp.times.clear();
        temp.times_str.clear();
        cin >> temp.name;
        for (int j = 0; j < 2; j++)
        {
            cin >> day;
            temp.days.push_back(day);
        }
        for (int j = 0; j < 2; j++)
        {
            cin >> time_str;
            temp.times_str.push_back(time_str);
            time = create_time(time_str);
            temp.times.push_back(time);
        }
        courses.push_back(temp);
    }
    return courses;
}



int time_to_minute(Time time)
{
    int minutes = (60*(time.hours)) + time.minutes;
    return minutes;
}

vector<Course> find_course_for_this_day(vector<Course> &courses , string day)
{
    vector<Course> foundCourses;
    for (int i = 0; i < courses.size() ; i++)
    {
        if (courses[i].days[0] == day || courses[i].days[1] == day)
        {
            foundCourses.push_back(courses[i]);
        }
    }
    return foundCourses;    
}

vector<Course> find_course_for_this_time(vector<Course> &courses , Time startTime)
{
    vector<Course> foundCourses; 
    Time endTime; 
    endTime.hours = startTime.hours + 2;
    endTime.minutes = 0;
    for (int i = 0; i < courses.size() ; i++)
    {
        if (time_to_minute(courses[i].times[0]) <= time_to_minute(startTime) 
        &&  time_to_minute(courses[i].times[1]) >= time_to_minute(endTime) )
        {
            foundCourses.push_back(courses[i]);
        }
    }
    return foundCourses;    
}

vector<Course> not_duplicated_course(vector<Course> &courses , vector<OutputCourse> &schedule)
{
    vector<Course> foundCourses;
    int flag = 0;
    for (int i = 0; i < courses.size() ; i++)
    {
        flag = 0;
        for (int j = 0; j < schedule.size() ; j++)
        {
            if (courses[i].name == schedule[j].course.name)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            foundCourses.push_back(courses[i]);
    }
    return foundCourses;    
}

vector<Course> find_courses(vector<OutputCourse> &schedule , vector<Course> &courses , string day , Time time)
{
    vector<Course> foundCourses;
    foundCourses = find_course_for_this_day(courses,day);
    foundCourses = find_course_for_this_time(foundCourses,time);
    foundCourses = not_duplicated_course(foundCourses,schedule);
    return foundCourses;
}

Course find_less_course(vector<Course> &courses)
{
    string min = courses[0].name;
    Course found = courses[0];
    for (int i = 0; i < courses.size() ; i++)
    {
        if (courses[i].name <= min)
        {
            min = courses[i].name;
            found = courses[i];
        }
    }
    return found;
}

vector<ClassTime> find_shifts_class(vector<OutputCourse> schedule , int classNum)
{
    vector<ClassTime> shifts;
    ClassTime temp;
    for (int i = 0; i < schedule.size() ; i++)
    {
        if (schedule[i].check || classNum == CLASS_NUMBER_1)
        {
            for (int j = 0; j < 2 ; j++)
            {
                
                temp.day = schedule[i].course.days[j];
                temp.time = schedule[i].startTime[classNum-1];
                shifts.push_back(temp);
            }       
        }
    }
    return shifts;
}

bool busy_shift(vector<ClassTime> shifts , string day , string time)
{
    for (int i = 0; i < shifts.size() ; i++)
    {
        if (day == shifts[i].day && time == shifts[i].time)
            return true;
    }
    return false;
}

bool shift_is_busy(vector<ClassTime> shifts , Course course , string time) 
{
    for (int k = 0; k < 2 ; k++)
    {
        if (busy_shift(shifts,course.days[k],time))
            return true;
    }
    return false;
}



vector<Teacher> find_teacher_for_this_course(vector<Teacher> &teachers , Course course)
{
    vector<Teacher> foundTeachers;
    int flag = 0;
    for (int i = 0; i < teachers.size() ; i++)
    {
        flag = 0;
        for (int j = 0; j < teachers[i].courses.size() ; j++)
        {
            if (teachers[i].courses[j] == course.name)
            {
                flag = 1;
                break;
            }  
        }
        if (flag == 1)
            foundTeachers.push_back(teachers[i]);
    }
    return foundTeachers;    
}

vector<Teacher> find_teacher_for_this_day(vector<Teacher> &teachers , Course course)
{
   vector<Teacher> foundTeachers;
    int flag = 0;
    for (int i = 0; i < teachers.size() ; i++)
    {
        flag = 0;
        for (int j = 0; j < teachers[i].freeDays.size() ; j++)
        {
            if (teachers[i].freeDays[j] == course.days[0] || teachers[i].freeDays[j] == course.days[1])
            {
                flag++;
            }  
        }
        if (flag == 2)
            foundTeachers.push_back(teachers[i]);
    }
    return foundTeachers;    
}

vector<Teacher> find_less_days(vector<Teacher> &teachers)
{
    vector<Teacher> foundTeachers;
    int minDays = 7;
    for (int i = 0; i < teachers.size() ; i++)
    {
        if (teachers[i].freeDays.size() <= minDays)
            minDays = teachers[i].freeDays.size();
    }
    for (int i = 0; i < teachers.size() ; i++)
    {
        if (teachers[i].freeDays.size() == minDays)
            foundTeachers.push_back(teachers[i]);
    }
    return foundTeachers;
}

vector<Teacher> not_duplicated_teacher(vector<Teacher> &teachers , Course course , string time)
{
    vector<Teacher> foundTeacher;
    int flag = 0;
    for (int i = 0; i < teachers.size() ; i++)
    {
        flag = 0;
        for (int j = 0; j < teachers[i].classTime.size() ; j++)
        {
            if (time == teachers[i].classTime[j].time && 
               (course.days[0] == teachers[i].classTime[j].day ||
                course.days[1] == teachers[i].classTime[j].day ))
            {
                flag = 1;
                break;
            }    
        }
        if (flag == 0)
        {
           foundTeacher.push_back(teachers[i]);
        } 
    }
    return foundTeacher;
}

vector<Teacher> find_teachers(vector<Teacher> &teachers , Course course , int classNum , string time)
{
    vector<Teacher> foundTeachers;
    foundTeachers = find_teacher_for_this_course(teachers,course);
    foundTeachers = find_teacher_for_this_day(foundTeachers,course);
    if (classNum == CLASS_NUMBER_2)
        foundTeachers = not_duplicated_teacher(foundTeachers,course,time);
    foundTeachers = find_less_days(foundTeachers);
    return foundTeachers;
}

Teacher find_less_teacher(vector<Teacher> &teachers)
{
    string min = teachers[0].name;
    Teacher found = teachers[0];
    for (int i = 0; i < teachers.size() ; i++)
    {
        if (teachers[i].name <= min)
        {
            min = teachers[i].name;
            found = teachers[i];
        }
    }
    return found;
}

vector<Teacher> find_teachers_class_time(vector<Teacher> &teachers , Teacher chosenTeacher , string day , string time)
{
    ClassTime temp;
    temp.day = day;
    temp.time = time;
    for (int i = 0; i < teachers.size() ; i++)
    {
        if (teachers[i].name == chosenTeacher.name)
        {
            teachers[i].classTime.push_back(temp);
            break;
        }
    }
    return teachers;
}



OutputCourse build_outputCourse(Course chosenCourse , Teacher chosenTeacher , string startTime , string endTime)
{
    OutputCourse tempOutput;
    tempOutput.course = chosenCourse;
    tempOutput.teachers.push_back(chosenTeacher);
    tempOutput.startTime.push_back(startTime);
    tempOutput.endTime.push_back(endTime);
    tempOutput.check = false;
    return tempOutput;
}

vector<OutputCourse> update_schedule(vector<OutputCourse> &schedule , int index , Teacher chosenTeacher , string startTime , string endTime)
{
    schedule[index].teachers.push_back(chosenTeacher);
    schedule[index].startTime.push_back(startTime);
    schedule[index].endTime.push_back(endTime);
    schedule[index].check = true;
    return schedule;
}

vector<OutputCourse> find_schedule_class1(vector<Teacher> &teachers , vector<Course> &courses)
{
    vector<string> weekDays = {"Saturday","Sunday","Monday","Tuesday","Wednesday"};
    vector<vector<string> > classTime = {{"07:30","09:00"},{"09:30","11:00"},{"11:30","13:00"}};
    vector<OutputCourse> schedule;
    vector<Teacher> foundTechers;
    vector<Course> foundCourses;
    vector<ClassTime> shifts;
    Teacher chosenTeacher;
    Course chosenCourse;
    Time startTime;
    startTime.minutes = 30;

    for (int i = 0; i < NUMBER_OF_DAYS ; i++)
    {
        startTime.hours = 5;
        for (int j = 0; j < NUMBER_OF_SHIFTS_PER_DAY ; j++)
        {
            startTime.hours += 2;
            foundCourses = find_courses(schedule,courses,weekDays[i],startTime);
            if (foundCourses.size() == 0)
                continue;
            chosenCourse = find_less_course(foundCourses);
            if (shift_is_busy(shifts,chosenCourse,classTime[j][0])) 
                continue;
            foundTechers = find_teachers(teachers,chosenCourse,CLASS_NUMBER_1,classTime[j][0]);
            if (foundTechers.size() == 0)
                continue;
            chosenTeacher = find_less_teacher(foundTechers);
            teachers = find_teachers_class_time(teachers,chosenTeacher,weekDays[i],classTime[j][0]);
            schedule.push_back(build_outputCourse(chosenCourse,chosenTeacher,classTime[j][0],classTime[j][1]));
            shifts = find_shifts_class(schedule,CLASS_NUMBER_1);
        }
    }
    return schedule;
}

vector<OutputCourse> find_schedule_class2(vector<OutputCourse> &schedule , vector<Teacher> &teachers)
{
    vector<vector<string> > classTime = {{"07:30","09:00"},{"09:30","11:00"},{"11:30","13:00"}};
    vector<Course> foundCourses;
    vector<Teacher> foundTechers;
    vector<ClassTime> shifts;
    Teacher chosenTeacher;
    Time startTime;
    startTime.minutes = 30;

    for (int i = 0; i < schedule.size() ; i++)
    {
        foundCourses.clear();
        foundCourses.push_back(schedule[i].course); 
        startTime.hours = 5;
        for (int j = 0; j < NUMBER_OF_SHIFTS_PER_DAY ; j++)
        {
            startTime.hours += 2;
            foundCourses = find_course_for_this_time(foundCourses,startTime);
            if (shift_is_busy(shifts,schedule[i].course,classTime[j][0]) || foundCourses.size() == 0) 
                continue;
            foundTechers = find_teachers(teachers,schedule[i].course,CLASS_NUMBER_2,classTime[j][0]);
            if (foundTechers.size() == 0)
                continue;
            chosenTeacher = find_less_teacher(foundTechers);
            schedule = update_schedule(schedule,i,chosenTeacher,classTime[j][0],classTime[j][1]);
            shifts = find_shifts_class(schedule,CLASS_NUMBER_2);
        }
    }
    return schedule;
}

vector<Course> not_found_time(vector<OutputCourse> &schedule , vector<Course> &courses)
{
    vector<Course> notFoundTime;
    int flag = 0;
    for (int i = 0; i < courses.size() ; i++)
    {
        int flag = 0;
        for (int j = 0; j < schedule.size() ; j++)
        {
            if (courses[i].name == schedule[j].course.name)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            notFoundTime.push_back(courses[i]);
        }
    }
    return notFoundTime;
}

vector<OutputCourse> sort_schedule(vector<OutputCourse> schedule)
{
    OutputCourse temp;
    for (int i = 0; i < schedule.size() ; i++)
    {
        for (int j = i+1 ; j < schedule.size() ; j++)
        {
            if (schedule[i].course.name < schedule[j].course.name)
            {
                temp = schedule[i];
                schedule[i] = schedule[j];
                schedule[j] = temp;
            } 
        }
    }
    return schedule;
}

void print_schedule(vector<OutputCourse> &schedule , vector<Course> &courses)
{
    vector<Course> notFoundTime = not_found_time(schedule,courses);
    schedule = sort_schedule(schedule);
    for (int i = 0; i < schedule.size() ; i++)
    {
        cout << schedule[i].course.name << endl;
        cout << schedule[i].teachers[0].name << ": ";
        cout << schedule[i].startTime[0] << " " << schedule[i].endTime[0] << endl;
        if (schedule[i].check)
        {
            cout << schedule[i].teachers[1].name << ": ";
            cout << schedule[i].startTime[1] << " " << schedule[i].endTime[1] << endl;
        }
        else
        {
            cout << "Not Found" << endl;
        }   
    }
    for (int i = 0; i < notFoundTime.size() ; i++)
    {
        cout << notFoundTime[i].name << endl;
        cout << "Not Found" << endl << "Not Found" << endl;
    }
}



int main()
{
    vector<Teacher> teachers = get_teachers();
    vector<Course> courses = get_courses();
    vector<OutputCourse> schedule = find_schedule_class1(teachers,courses);
    schedule = find_schedule_class2(schedule,teachers);
    print_schedule(schedule,courses);

    return 0;
}


