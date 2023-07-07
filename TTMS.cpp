#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

namespace faculty_timetable {
    template <class T>
    class Schedule {
        public:
            virtual vector<T> getTimeTable() = 0;
    };

    template <class T>
    class Classroom : public Schedule<T> {
        private:
            vector<T> timeTable;
        public:
            vector<T> getTimeTable() override {
                return timeTable;
            }
            void setTimeTable(vector<T> timetable) {
                timeTable = timetable;
            }
    };

    class FileHandler {
        public:
            void writeToFile(string fileName, vector<Schedule<string>*> schedules) {
                ofstream file;
                file.open(fileName);
                for (int i = 0; i < schedules.size(); i++) {
                    file << "Classroom " << i+1 << ":\n";
                    vector<string> timetable = schedules[i]->getTimeTable();
                    for (int j = 0; j < timetable.size(); j++) {
                        file << timetable[j] << "\n";
                    }
                }
                file.close();
            }
            vector<Schedule<string>*> readFromFile(string fileName) {
                vector<Schedule<string>*> schedules;
                ifstream file;
                file.open(fileName);
                string line;
                Classroom<string>* classroom = nullptr;
                while (getline(file, line)) {
                    if (line.substr(0, 9) == "Classroom") {
                        classroom = new Classroom<string>();
                        schedules.push_back(classroom);
                    } else {
                        classroom->getTimeTable().push_back(line);
                    }
                }
                file.close();
                return schedules;
            }
    };

    template <class T>
    class TimeTable {
        private:
            vector<Schedule<T>*> schedules;
        public:
            ~TimeTable() {
                for (auto schedule : schedules) {
                    delete schedule;
                }
                schedules.clear();
            }
            vector<Schedule<T>*> getSchedules() {
                return schedules;
            }
            void addSchedule(Schedule<T>* schedule) {
                schedules.push_back(schedule);
            }
            void storeTimeTableToFile(string fileName) {
                FileHandler fileHandler;
                fileHandler.writeToFile(fileName, schedules);
            }
    };
    
		class TimeCalcException : public exception {
			public:
    		const char* what() const throw() {
    		return "Inputs not correct";
    }
};
    
		class UserInterface {
        private:
            TimeTable<string> timeTable;
            int numClasses;
            int classDuration;
        public:
            void setNumClasses() {
                cout << "Enter the number of classes: ";
                cin >> numClasses;
            }
            void setClassDuration() {
                cout << "Enter the duration of a class (in minutes): ";
                cin >> classDuration;
            }
            int getTotalTeachingTime() {
                return numClasses * classDuration;
            }
            
            int operator+(const UserInterface& other) const {
            	try {
                    numClasses * classDuration + other.numClasses * other.classDuration;
                }
                catch (TimeCalcException e) {
                    cerr << "Error: " << e.what() << endl;
                }
                return numClasses * classDuration + other.numClasses * other.classDuration;
            }
            void addSchedule() {
                Classroom<string>* classroom = new Classroom<string>();
                cout << "Enter time table information for classroom\n";
                cout << "How many classes do you want to add?\n";
                cin >> numClasses;
                vector<string> timetable(numClasses);
                for (int i = 0; i < numClasses; i++) {
                    cout << "Enter time table for period " << i+1 << ": ";
                    cin >> timetable[i];
                    
                }
                classroom->setTimeTable(timetable);
                timeTable.addSchedule(classroom);
                cout << "Classroom added!\n";
            }
            void readTimeTableFromFile() {//In the readTimeTableFromFile() method, I added the code to read the file and add the schedules to the TimeTable.
                string fileName;
                cout << "Enter file name: ";
                getline(cin, fileName);
                FileHandler fileHandler;
                vector<Schedule<string>*> schedules = fileHandler.readFromFile(fileName);
                for (auto schedule : schedules) {
                    timeTable.addSchedule(schedule);
                }
                cout << "Time table information read from file.\n";
            }
            void displayTimeTable() {//In the displayTimeTable() method, I added the code to display the time table information to the user.
                vector<Schedule<string>*> schedules = timeTable.getSchedules();
                if (schedules.empty()) {
                    cout << "No time table information available.\n";
                    return;
                }
                cout << "Time table information:\n";
                for (int i = 0; i < numClasses; i++) {
                    cout << "Classroom " << i+1 << ":\n";
                    vector<string> timetable = schedules[i]->getTimeTable();
                    for (int j = 0; j < numClasses ; j++) {
                        cout << "Period " << j+1 << ": " << timetable[j] << "\n";
                        
                    }
                    
                    cout << "\n";
                    break;
                }
            }
            void storeTimeTableToFile() {//In the storeTimeTableToFile() method, I added the code to store the time table information to a file.
                string fileName;
                cout << "Enter file name: ";
                getline(cin, fileName);
                FileHandler fileHandler;
                fileHandler.writeToFile(fileName, timeTable.getSchedules());
                cout << "Time table information stored to file.\n";
            }
};
}
int main() {
using namespace faculty_timetable;

UserInterface userInterface;

while (true) {
    cout << "Select an option:\n";
    cout << "1. Add schedule\n";
    cout << "2. Display time table\n";
    cout << "3. Store time table information to file\n";
    cout << "4. Read time table information from file\n";
    cout << "5. Set class duration\n";
    cout << "6. Get total teaching time\n";
    cout << "7. Exit\n";
    int option;
    cin >> option;
    cin.ignore();
    switch (option) {
        case 1:
            userInterface.addSchedule();
            break;
        case 2:
            userInterface.displayTimeTable();
            break;
        case 3:
            userInterface.storeTimeTableToFile();
            break;
        case 4:
            userInterface.readTimeTableFromFile();
            break;
        case 5:
            userInterface.setClassDuration();
            break;
        case 6:
            cout << "Total teaching time: " << userInterface.getTotalTeachingTime() << " minutes \n\n";
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
    };  
}
    return 0;
}