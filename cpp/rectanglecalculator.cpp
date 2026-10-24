#include <iostream>
#include <string>
using namespace std;
class rectangle{
    private:
        double width;
        double height;
    public:
    rectangle(double height,double width){
        this-> height = height;
        this-> width = width;
    }
    rectangle(){
        this->height = 0;
        this->width = 0;
    }
    void setheight(double h){
        this -> height = h;
    }
    void setwidth(double w){
        this -> width = w;
    }
    double area(){
        return height * width;
    }
    double perimeter(){
        return 2*(height+width);
    }
    void displaydata(){
        cout<<"The rectangle has height: "<< height <<endl;
        cout<<"The rectangle has width: "<< width <<endl;
        cout<<"The area of the rectangle is: "<<area()<<endl;
        cout<<"The perimeter of the rectangle is: "<<perimeter()<<endl;

    }

};

int main() {
    //the next line shows default construter
    rectangle r1;
    r1.displaydata();
    cout<<"---------------------------------"<<endl;
    //the next line shows argument based constructor
    rectangle r2(10,5);
    r2.displaydata();
}