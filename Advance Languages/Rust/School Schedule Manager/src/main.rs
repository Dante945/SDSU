use std::{
    fs::{self, File},
    io::Write,
};

pub struct StudentGrades {
    name: String,
    grades: Vec<f64>,
}

impl StudentGrades {
    fn average(&self) -> f64 {
        self.grades.iter().sum::<f64>() / self.grades.len() as f64
    }

    fn grade(&self) -> char {
        let avg: f64 = self.average();
        match avg {
            x if x >= 90.0 => 'A',
            x if x >= 80.0 => 'B',
            x if x >= 70.0 => 'C',
            x if x >= 60.0 => 'D',
            _ => 'F',
        }
    }
}

pub struct CourseGrades {
    students: Vec<StudentGrades>,
}

impl CourseGrades {
    fn average(&self, N: i64) -> Option<f64> {
        let mut average: f64 = 0.0;
        for student in &self.students {
            //If N is out of range of the student grades, return None
            match N {
                N if N > student.grades.len() as i64 => return None,
                _ => average += student.grades[(N - 1) as usize],
            }
        }
        return Some(average / self.students.len() as f64);
    }

    fn student(&self, name: String) -> Option<&StudentGrades> {
        for student in &self.students {
            if student.name == name {
                return Some(student);
            }
        }
        return None;
    }

    fn from_file(file_path: String) -> Self {
        let file_content: String =
            fs::read_to_string(file_path).expect("Should have been able to read the file");
        let student_vec: Vec<&str> = file_content.split("\n").collect::<Vec<&str>>();

        // Vector of StudentGrades to be stored and returned in Self
        let mut students: Vec<StudentGrades> = vec![];

        for student_info in student_vec.iter() {
            let mut new_name: String = String::new();
            let mut new_grade: Vec<f64> = vec![];
            for (index, val) in student_info.split(",").enumerate() {
                // First index is always the name of the student and everything after is the grades
                match index {
                    0 => new_name = String::from(val),
                    _ => new_grade.push(val.trim().parse().unwrap()),
                }
            }
            let new_student: StudentGrades = StudentGrades {
                name: String::from(new_name),
                grades: new_grade,
            };
            students.push(new_student);
        }
        Self { students }
    }
}

pub struct CourseSchedule {
    courses: Vec<Course>,
}

impl CourseSchedule {
    fn from_file(file_path: String) -> Self {
        let file_content: String =
            fs::read_to_string(file_path).expect("Should have been able to read the file");
        let mut courses_vec: Vec<&str> = file_content.split("\n").collect::<Vec<&str>>();

        // Remove the first two rows, as they dont represent any courses
        courses_vec.drain(0..2);

        // Vector of Courses to be stored and returned in Self
        let mut courses: Vec<Course> = vec![];

        for course in courses_vec.iter() {
            let mut catalog_number: String = String::new();
            let mut course_number: String = String::new();
            let mut title: String = String::new();
            let mut instructor: String = String::new();
            let mut time: String = String::new();
            let mut days: String = String::new();

            // Store fields depending on index which represents a header
            for (index, val) in course.split("\t").enumerate() {
                match index {
                    2 => course_number = String::from(val),
                    4 => catalog_number = String::from(val),
                    5 => title = String::from(val),
                    22 => time = String::from(val),
                    24 => days = String::from(val),
                    25 => instructor = String::from(val),
                    _ => continue,
                }
            }
            let course: Course = Course {
                catalog_number,
                course_number,
                title,
                instructor,
                time,
                days,
            };
            courses.push(course);
        }
        Self { courses }
    }

    fn courses_at(&self, time: &str, days: &str) -> Vec<&Course> {
        let mut courses_at: Vec<&Course> = vec![];
        for course in &self.courses {
            if course.time == time && course.days == days {
                courses_at.push(course);
            }
        }
        courses_at
    }
}

pub struct Course {
    catalog_number: String,
    course_number: String,
    title: String,
    instructor: String,
    time: String,
    days: String,
}

fn main() {}

fn create_test_file(file_name: String) {
    let mut file = File::create(file_name).expect("Error encountered while creating file!");
    file.write_all(
        b"Dante,90.0, 80.0, 70.0\nroger,100.0,80.0,80\npete,70.0,75.5,73.0\nNewdy, 60.0,80.0,100.0",
    )
    .expect("Error while writing to file");
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::{fs::File, io::Write};
    #[test]
    fn testing_StudentGrades_grade() {
        let student: StudentGrades = StudentGrades {
            name: String::from("Dante"),
            grades: vec![10.0, 10.0, 20.0],
        };
        assert_eq!(student.grade(), 'F');
    }
    #[test]
    fn testing_StudentGrades_average() {
        let student: StudentGrades = StudentGrades {
            name: String::from("John"),
            grades: vec![100.0, 90.0, 80.0],
        };
        assert_eq!(student.average(), 90.0);
    }
    #[test]
    fn testing_CourseGrades_from_file() {
        create_test_file(String::from("test.txt"));
        let course_grades = CourseGrades::from_file(String::from("test.txt"));
        assert_eq!(course_grades.students.len(), 4);
        assert_eq!(course_grades.students[0].name, "Dante");
        assert_eq!(course_grades.students[1].name, "roger");
        assert_eq!(course_grades.students[2].grades, [70.0, 75.5, 73.0]);
    }
    #[test]
    fn testing_CourseGrades_student() {
        create_test_file(String::from("test.txt"));
        let course_grades = CourseGrades::from_file(String::from("test.txt"));
        let student_present: Option<&StudentGrades> = course_grades.student(String::from("Newdy"));

        assert!(!student_present.is_none());
        assert_eq!(student_present.unwrap().grades, vec![60.0, 80.0, 100.0]);
        assert_eq!(student_present.unwrap().name, "Newdy");
        assert_eq!(student_present.unwrap().average(), 80.0);
        assert_eq!(student_present.unwrap().grade(), 'B');

        let student_absent: Option<&StudentGrades> =
            course_grades.student(String::from("NOT HERE"));
        assert!(student_absent.is_none());
    }
    #[test]
    fn testing_CourseGrades_average() {
        create_test_file(String::from("test.txt"));
        let course_grades = CourseGrades::from_file(String::from("test.txt"));
        assert_eq!(course_grades.average(1), Some(80.0));
        assert_eq!(course_grades.average(1000), None);
    }
    #[test]
    fn testing_CourseSchedule_from_file() {
        let course_schedule: CourseSchedule = CourseSchedule::from_file(String::from("search.xls"));
        assert_eq!(course_schedule.courses.len(), 125);
        assert_eq!(
            course_schedule.courses[0].catalog_number,
            String::from("null")
        );
        assert_eq!(
            course_schedule.courses[100].title,
            String::from("WIRELESS NETWORKS")
        );
        assert_eq!(
            course_schedule.courses[100].course_number,
            String::from("578")
        );
        assert_eq!(course_schedule.courses[50].time, String::from("1400"));
        assert_eq!(course_schedule.courses[45].days, String::from("MW"));
        assert_eq!(
            course_schedule.courses[33].instructor,
            String::from("A. MEWADA")
        );
    }

    #[test]
    fn testing_CourseSchedule_courses_at() {
        let course_schedule: CourseSchedule = CourseSchedule::from_file(String::from("search.xls"));
        assert_eq!(course_schedule.courses_at("1100", "TTH").len(), 3);
        assert_eq!(course_schedule.courses_at("1100", "MW").len(), 1);
        assert_eq!(course_schedule.courses_at("1500", "MWF").len(), 0);
    }
}
