#ifndef EXAM_DETAILS_H
#define EXAM_DETAILS_H

#include <string>
#include <exception>

namespace mtm {
	class ExamDetails {
	private:
		int num_course;
		int month;
		int day;
		double time;
		double exam_length;
		std::string link;

		constexpr static const double EPSILON = 10e-6;
		constexpr static const double HALF_HOUR = 0.5;
		static const int HOURS_IN_DAY = 24;
		static const int DAYS_IN_MONTH = 30;
		static const int MONTHS_IN_YEAR = 12;

		static const int MTM_COURSE_NUMBER = 234124;
		static const int MTM_COURSE_MONTH = 7;
		static const int MTM_COURSE_DAY = 28;
		constexpr static const double MTM_COURSE_TIME = 13.0;
		constexpr static const double MTM_EXAM_LENGTH = 3.0;
		constexpr static const char* MTM_COURSE_LINK = "https://tinyurl.com/59hzps6m";

		static bool isTimeValid(double time);

		static std::string timeToText(double time);

	public:
		class InvalidDateException;

		class InvalidTimeException;

		class InvalidArgsException;

		ExamDetails(int num_course, int month, int day, double time, double exam_length, const std::string& link = "");

		~ExamDetails() = default;

		ExamDetails(const ExamDetails& exam) = default;

		ExamDetails& operator=(const ExamDetails& exam) = default;

		std::string getLink() const;

		void setLink(const std::string& new_link);

		int operator-(const mtm::ExamDetails& exam) const;

		bool operator<(const ExamDetails& exam) const;

		friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);

		static ExamDetails makeMatamExam();
	};

	class ExamDetails::InvalidDateException : public std::exception {
	};

	class ExamDetails::InvalidTimeException : public std::exception {
	};

	class ExamDetails::InvalidArgsException : public std::exception {
	};


	std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);
}
#endif //EXAM_DETAILS_H
