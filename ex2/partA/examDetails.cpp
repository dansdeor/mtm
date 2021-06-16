#include "examDetails.h"
#include <iostream>
#include <string>
#include <utility>
#include <math.h>
#include <cfloat>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

bool mtm::ExamDetails::isTimeValid(double time)
{
	time *= 10;
	int discrete_time = static_cast<int>(time);
	return (discrete_time % 5 == 0) && (std::fabs(time - discrete_time) < DBL_EPSILON) && 0 <= time && time < 24;
}

std::string mtm::ExamDetails::timeToText(double time)
{
	string text;
	if (time < 10) {
		text += "0";
	}
	int discrete_time = static_cast<int>(time);
	text += std::to_string(discrete_time) + ":";
	text += std::to_string((time - discrete_time) * 60);
	return text;
}

mtm::ExamDetails::ExamDetails(int num_course, int month, int day, double time, double exam_length, const string& link)
		: num_course(num_course), month(month), day(day), time(time), exam_length(exam_length), link(link)
{
	if (month < 1 || NUMBER_OF_MONTHS < month || day < 1 || DAYS_IN_MONTH < day) {
		throw ExamDetails::InvalidDateException();
	}
	if (!isTimeValid(time)) {
		throw ExamDetails::InvalidTimeException();
	}
	if (num_course < 0 || exam_length < 0) {
		throw ExamDetails::InvalidArgsException();
	}
}


std::string mtm::ExamDetails::getLink()
{
	return link;
}

void mtm::ExamDetails::setLink(const string& new_link)
{
	link = new_link;
}


int mtm::ExamDetails::operator-(const mtm::ExamDetails& exam) const
{
	return (month - exam.month) * DAYS_IN_MONTH + (day - exam.day);
}

bool mtm::ExamDetails::operator<(const mtm::ExamDetails& exam)
{
	int days = *this - exam;
	return days < 0;
}

std::ostream& mtm::operator<<(std::ostream& os, const mtm::ExamDetails& exam)
{
	os << "Course Number: " << exam.num_course << endl;
	os << "Time: " << exam.day << "." << exam.month << " at " << exam.timeToText(exam.time) << endl;
	os << "Duration: " << exam.timeToText(exam.exam_length) << endl;
	os << "Zoom Link: " << exam.link << endl;
	return os;
}


mtm::ExamDetails mtm::ExamDetails::makeMatamExam(mtm::ExamDetails test)
{
	return mtm::ExamDetails(234124, 7, 28, 13, 3, "https://tinyurl.com/59hzps6m");
}
