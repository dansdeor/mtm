#include "examDetails.h"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

class ExamDetails {
	int num_course, month, day, time, exam_length;
	string link;
	char* test;

public:
	ExamDetails(int num_course, int month, int day, int time, int exam_length, string link );
	~ExamDetails();
	ExamDetails(const int &num_course,const int &month,const int &day,const int &time, const int &exam_length,const string &link);
	ExamDetails operator=(const int &a);
	ExamDetails operator-();
	ExamDetails operator<(char const test);
	string getLink(const string &link){};
	string setLink(const string &newlink){};
	void printDate(){};
	static ExamDetails makeMatamExam(ExamDetails test){};
	double distance(const ExamDetails& p) const;
};

ExamDetails::ExamDetails(int num_course, int month, int day, int time, int exam_length, string link) {
}

int main() {
	return 0;
}
