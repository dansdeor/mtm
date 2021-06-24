#### PART 1 ####
# final_grade: Calculates the final grade for each student, and writes the output (while eliminating illegal
# rows from the input file) into the file in `output_path`. Returns the average of the grades.
#   input_path: Path to the file that contains the input
#   output_path: Path to the file that will contain the output
def final_grade(input_path: str, output_path: str) -> int:
    students = {}
    input_file = open(input_path, 'r')
    for line in input_file:
        # Splitting the string to list of characters and joining back with spaces to remove multiple spaces
        # We need to replace every occurrence of ',' with ' , ' to ensure that any , will no longer be part of member
        student_id, student_name, semester, homework_average = ' '.join(line.replace(',', ' , ').split()).split(' , ')
        if student_id[0] == '0' or len(student_id) != 8:
            continue
        if not student_name.replace(' ', '').isalpha():
            continue
        if int(semester) < 1:
            continue
        if int(homework_average) <= 50 or 100 < int(homework_average):
            continue
        grade = str((int(homework_average) + int(student_id[-2:])) // 2)
        students[student_id] = (student_id, homework_average, grade)
    input_file.close()

    if 0 < len(students):
        output_file = open(output_path, 'w')
        for _, details in sorted(students.items()):
            output_file.write(', '.join(details) + '\n')
        output_file.close()

    return sum([int(details[-1]) for details in students.values()]) // len(students)


#### PART 2 ####
# check_strings: Checks if `s1` can be constructed from `s2`'s characters.
#   s1: The string that we want to check if it can be constructed
#   s2: The string that we want to construct s1 from
def check_strings(s1: str, s2: str) -> bool:
    s2_letters = [letter for letter in s2.lower()]
    for s1_letter in s1.lower():
        if s1_letter not in s2_letters:
            return False
        # Remove the instance only once
        s2_letters.remove(s1_letter)
    return True
