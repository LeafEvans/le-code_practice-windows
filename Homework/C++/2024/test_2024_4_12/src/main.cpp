#include <iostream>
#include <string>

using namespace std;

class Person {
 protected:
  string _name;
  string _sex;
  unsigned int _age;

 public:
  Person(const string &name, const string &sex, const unsigned int age)
      : _name(name), _sex(sex), _age(age) {}
  virtual ~Person() {}

  virtual void show() const {
    cout << "name: " << _name << endl;
    cout << "sex: " << _sex << endl;
    cout << "age: " << _age << endl;
  }
};

class Teacher : virtual public Person {
 protected:
  string _title;

 public:
  Teacher(const string &name, const string &sex, const unsigned int age,
          const string &title)
      : Person(name, sex, age), _title(title) {}
  virtual ~Teacher() {}
  virtual void show() const {
    cout << "Teacher" << endl;
    Person::show();
    cout << "title: " << _title << endl;
  }
};

class Cadre : virtual public Person {
 protected:
  string _post;

 public:
  Cadre(const string &name, const string &sex, const unsigned int age,
        const string &post)
      : Person(name, sex, age), _post(post) {}
  virtual ~Cadre() {}
  virtual void show() const {
    cout << "Cadre" << endl;
    Person::show();
    cout << "post: " << _post << endl;
  }
};

class TeacherCadre : public Teacher, public Cadre {
 protected:
  float _wages;

 public:
  TeacherCadre(const string &name, const string &sex, const unsigned int age,
               const string &title, const string &post, const float wages)
      : Person(name, sex, age),
        Teacher(name, sex, age, title),
        Cadre(name, sex, age, post),
        _wages(wages) {}

  virtual void show() const {
    cout << "TeacherCadre" << endl;
    Person::show();
    cout << "title: " << _title << endl;
    cout << "post: " << _post << endl;
    cout << "wages: " << _wages << endl;
  }
};

void showInfo(const Person &person) {
  person.show();
  cout << endl;
}

int main(int argc, char **argv) {
  Person person("Judy", "female", 15);
  Teacher teacher("Alice", "female", 20, "math teacher");
  Cadre cadre("Cathy", "male", 23, "principal");
  TeacherCadre teacher_cadre("Evans", "male", 20, "english teacher", "director",
                             2000.3);

  showInfo(person);
  showInfo(teacher);
  showInfo(cadre);
  showInfo(teacher_cadre);

  return 0;
}
