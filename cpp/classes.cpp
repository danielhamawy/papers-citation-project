#include<iostream>
using namespace std;
class Date{
    public:
        string day,month,year;
        Date(string d,string m,string y): day(d),month(m),year(y) {}
};
class student{
    public:
        string name;
        const string rollNumber;
        Date admissionDate;
        student(string n,string rn,Date ad):name(n),rollNumber(rn),admissionDate(ad){
        cout<<"student created"<<endl;
    }
    void setName(string name) {
        this->name = name;
    }
    void display()const{
        cout<<"name: "<<name<<endl;
        cout<<"roll number: "<<rollNumber<<endl;
        cout<<"admission date: "<<admissionDate.day<<"/"<<admissionDate.month<<"/"<<admissionDate.year<<endl;
    }
    friend void showthepriv(student s);
};
void showthepriv(student s){
    cout<<"private name is: "<<s.name<<endl;
}
int main() {
    Date d1("14", "March", "2026");
    student s1("Daniel", "A101", d1);
    s1.setName("Daniel Abu");
    s1.display();
    const student s2("Sarah", "B202", d1);
    s2.display();
    showthepriv(s1);
}