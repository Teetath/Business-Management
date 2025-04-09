
class Person {
    protected:      //เดะเอาไปใช้ใน Employee (inheri)
        string name;
        int age;
    public:
        Person (string name, int age) : name(name), age(age) {}
        virtual void display(){
            cout << "Name: " << name << "Age " << age <<endl;
        }
};