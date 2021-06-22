from gradesCalc import *


# Testing your implemented functions, feel free to add more tests below
def main():
    # Testing the `final_grade` function
    input_path = 'tests/input'
    output_path = 'tests/out'
    course_avg = final_grade(input_path=input_path, output_path=output_path)
    assert course_avg == 70

    # Testing the `check_strings` function
    s1 = 'naanb'
    s2 = 'baNaNa'
    result = check_strings(s1=s1, s2=s2)
    assert result


if __name__ == "__main__":
    main()
