#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// commandline -> argv
// argc, argc ... booot::programoptions

class student {
public:
    student(std::string name)
        : m_name(std::move(name))    
    {
    }
    virtual ~student() {}

    double average() const
    {
        return std::accumulate(m_grades.cbegin(), m_grades.cend(), 0)
                / (double) m_grades.size();
    }

    void add_grade(int grade)
    {
        m_grades.push_back(grade);
    }

    virtual std::string name() const
    {
        return m_name;
    }

private:
    std::string m_name;
    std::vector<int> m_grades;
};

class master_student: public student {
public:
    master_student(std::string name, std::string thesis, std::string mentor)
        : student(std::move(name))
        , m_thesis(std::move(thesis))
        , m_mentor(std::move(mentor))
    {
    }

    std::string name() const override
    {
        return student::name() + " MASTER";
    }

private:
    std::string m_thesis;
    std::string m_mentor;
};

int main()
{
    student s1("Petar Petrovic");

    s1.add_grade(8);
    s1.add_grade(9);
    s1.add_grade(8);
    s1.add_grade(9);

    master_student s2("Janka Jankovic", "Alat za vizuelizaciju hiperbolicke geometrija", "Mirko Mirkovic");

    s2.add_grade(9);
    s2.add_grade(10);
    s2.add_grade(9);

    student s2_sliced = s2;

    student& s3(s2);

    std::cout << s1.name() << std::endl;
    std::cout << s2.name() << std::endl;
    std::cout << s2_sliced.name() << std::endl;
    std::cout << s3.name() << std::endl;

    std::cout << s1.average() << std::endl;
    std::cout << s2.average() << std::endl;
    std::cout << s2_sliced.average() << std::endl;
    std::cout << s3.average() << std::endl;

    // Slicno se moze (sto je i preporuceno) postici
    // koriscenjem shared_ptr klase.
    student* ms = new master_student("Pera Peric", "Funcionalno programiranje u jeziku Fotrtan", "Ne Hvala");
    std::cout << ms->name() << std::endl;
    delete ms;

    return 0;
}
