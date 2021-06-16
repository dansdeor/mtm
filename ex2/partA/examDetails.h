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

		static const int DAYS_IN_MONTH = 30;
		static const int NUMBER_OF_MONTHS = 12;

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

		std::string getLink();

		void setLink(const std::string& new_link);

		int operator-(const mtm::ExamDetails& exam) const;

		bool operator<(const ExamDetails& exam);

		friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);

		static ExamDetails makeMatamExam(ExamDetails test);
	};

	class ExamDetails::InvalidDateException : public std::exception {
	};

	class ExamDetails::InvalidTimeException : public std::exception {
	};

	class ExamDetails::InvalidArgsException : public std::exception {
	};
}
#endif //EXAM_DETAILS_H
