#include<iostream>
#include<string>
using namespace std;
class Person{
    Person(string name, size_t age)
    :_name(name), _age(age)
    {}

    void Print(){
        cout << _name << " " << _age << endl;
    }

protected:
    string _name;
    size_t _age;
};

class Student : public Person{
    Student(string name, size_t age, int score = 0)
    :Person(name, age), _score(score)
    {}

protected:
    int _score;
};

int main(){
    Student s("xiaotang", 19, 100);
    s.Print();
    return 0;
}