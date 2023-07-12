#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
using namespace std;

inline int ynchoice();
void collegeportal();
void teacherportal();
void studentportal();
void teacher_controlpanel();
int checkif_test_exists(string testname);
void exitprogram();
void fileopenerror();
void check_admin_pass();
void keyproceed();

class Student
{
    char username[50];
    char pass[50];
    int enroll;

    int checkenrol(int enrol)
    {
        
        ifstream studentnin("studentname.txt");
        if(studentnin.is_open())
        {
            int *fileenrol = new int;
            char *temp = new char[50];
            while(studentnin.eof() == 0)
            {
                studentnin >> *fileenrol >> temp >>  temp;
                if(*fileenrol == enrol)
                {
                    delete[] temp;
                    delete fileenrol;
                    studentnin.close();
                    return 0;
                }
            }
            delete[] temp;
            delete fileenrol;
            studentnin.close();
            return 1;
        }
        else
            fileopenerror();
    }

    int checkuser(char username[])
    {
        ifstream studentnin("studentname.txt");
        if(studentnin.is_open())
        {
            char *filename = new char[50];
            char *temp = new char[50];
            while(studentnin.eof() == 0)
            {
                studentnin >> temp >> filename >> temp;
                if(strcmp(username,filename) == 0)
                {
                    studentnin.close();
                    delete[] temp; 
                    delete[] filename;
                    return 0;
                }
            }
            studentnin.close();
            delete[] temp; 
            delete[] filename;
            return 1;
        }
        else
            fileopenerror();
    }

    void reguser(char username[],char pass[],int enrol)
    {
        ofstream studentnout("studentname.txt",ios::app);
        if(studentnout.is_open())
        {
            studentnout << "\n"<<enrol << " " << username << " "<<pass ;
            studentnout.close();
        }
        else
            fileopenerror();
    }

    int credcheck(int enrol,char username[], char pass[])
    {
        ifstream studentnin("studentname.txt");
        if(studentnin.is_open())
        {
            char *filename = new char[50]; 
            char *filepass = new char [50];
            int *fileenrol = new int;
            while(studentnin.eof() == 0)
            {
                studentnin >> *fileenrol >> filename >> filepass;
                if(strcmp(username,filename) == 0)
                {
                    if(enrol == *fileenrol)
                    { 
                        if(strcmp(filepass,pass) == 0)
                        {
                            delete[] filename;
                            delete[] filepass;
                            delete[] fileenrol;
                            studentnin.close();
                            return 1;           //Successfull login
                        }
                    }
                }
            }
            delete[] filename;
            delete[] filepass;
            delete[] fileenrol;
            studentnin.close();
            return 0;
        }
        else
            fileopenerror();
    }

    void print_student_marks(string testname, int enrol)
    {
            ifstream getenrol(testname);
            int fileenrol;
            int marks;
            int filemarks;
            string temp;
            while(getenrol >> temp >> fileenrol >> filemarks)
            {
                if(fileenrol == enrol)
                {
                    marks =filemarks;
                    cout << "Marks : " << marks << " / 100" << endl;
                    return;
                }
            }
            cout << "Entry not found" << endl;
            keyproceed();
    }

    friend void student_controlpanel(Student &s);
    
public:

        Student()
        {
            strcpy(username," ");
            strcpy(pass," ");
            enroll = 0;
        }
        void reggetdata()
        {
            system("cls");
            cout << "< STUDENT REGISTRATION >" << endl << endl;
            cout << "Enter enrollment number: ";
            cin >> enroll;
            if(checkenrol(enroll)!=1)
            {
                cout << "User with that enrollment no. already exists." << endl;
                if(ynchoice())
                    studentportal();
                else
                    exitprogram();
            }

            cout << "Enter username: ";
            cin >> username;
            if(checkuser(username)!=1)
            {
                cout << "Username already exists." << endl << endl;
                if(ynchoice())
                    studentportal();
                else
                    exitprogram();
            }
            
            cout << "Enter password: ";
            cin >> pass;
            strcat(pass,username);
            
            reguser(username,pass,enroll);

            cout << "Registered successfully" << endl;
            cout << "Do you want to login ?" << endl;
            if(ynchoice())
                loggetdata();
            else 
                exitprogram();
        }

        void loggetdata()
        {
            char rl_choice;
            cout << endl << "< LOGIN >" << endl;   

            cout << "Enter username : ";
            cin >> username;

            cout << "Enter password : "; 
            cin >> pass;

            cout << "Enter enrollment number : ";
            cin >> enroll;

            strcat(pass,username);

            if (credcheck(enroll,username,pass))
                cout << endl << "Login successfull!" << endl;
            else
            {
                cout << "Invalid credentials" << endl;
                cout << "Do you want to retry ? " << endl;
                if(ynchoice())
                    loggetdata();
                else
                    exitprogram();
            }
        }
        
        void get_test_marks()
        {
            Student s;
            int choice;
            string testname;
            cout << "Enter test name: ";
            cin >> testname;
            testname += ".txt";
            if(checkif_test_exists(testname)!=1)
            {
                print_student_marks(testname,enroll);
                if(ynchoice())
                {
                    system("cls");
                    student_controlpanel(s);
                }
                else
                    exit(1);
            }
            else
                cout << "Test not found" << endl;
            keyproceed();
            student_controlpanel(s);
        }
};

class Teacher : public Student
{
    char username[50];
    char pass[50];

    int checkenrol(int enrol)
    {
        int fileenrol;
        char *temp = new char[50];
        ifstream studentnin("studentname.txt");
        while(studentnin.eof() == 0)
        {
             studentnin >> fileenrol >> temp >>  temp;
             if(fileenrol == enrol)
             {
                return 1;
             }
        }
        return 0;
        delete[] temp;
    }

    void print_test_details(string testname)
    {
        int *enrol = new int;
        int *marks = new int;
        char *name = new char[50];
        ifstream printtest(testname);
        cout << endl << left << setw(25) << "ENROLLMENT NO.";
        cout << left << setw(25) << "NAME";
        cout << left << setw(15) << "MARKS" << endl <<endl;

        while(printtest >> name >> *enrol >> *marks)
        {
            cout << left << setw(25) << *enrol;
            cout << left << setw(25) << name;
            cout << right  << *marks << " / 100"<< endl;
        }
        keyproceed();
        delete enrol;
        delete marks;
        delete []name;
    }

    void add_test_marks(string testname)
    {
        int enrol,marks;
        char *name =  new char[50];
        string temp;
        int enrolcheck;
        ifstream studentinfo("studentname.txt");
        ifstream check_if_marks_entered(testname);

        check_if_marks_entered >> temp >> enrolcheck;
        studentinfo >> enrol;
        if(enrolcheck == enrol)
        {
            cout << "Marks for has already been recorded" << endl;
            cout << "Do you want to overwrite ?" << endl;
            if(ynchoice() == 0)
                return;
            cout << "Enter marks out of 100 : "<< endl;
        }

        ofstream testadd(testname);
        studentinfo.seekg(0,ios::beg);
        cout << left << setw(25) << "ENROLLMENT NO.";
        cout << left << setw(25) << "NAME";
        cout << left << setw(15) << "MARKS" << endl <<endl;
        while(studentinfo.eof() == 0)
        {
            studentinfo >> enrol >> name >> temp;
            testadd << name <<" " << enrol << " ";
            cout << left << setw(25) << enrol;
            cout << left << setw(25) << name;
            cout << left << setw(15);
            cin >> marks;
            testadd << marks << endl;  
        }
        keyproceed();
        get_test_details();
    }

    void edit_test_marks(string testname)
    {
        int enrol;
        int fileenrol;
        char filename[50];
        int marks;
        int filemarks,enrolcheck=0;
        ofstream temp("temp.txt",ios::trunc);
        ifstream getenrol(testname);
        cout << "Enter enrollment no. of student of whom you want to edit marks: ";
        cin >> enrol;
        cout << "Enter new marks: ";
        cin >> marks;
        while(getenrol >> filename >> fileenrol >> filemarks)
        {
            if(fileenrol == enrol)
            {
                temp << filename << " " << fileenrol << " "<< marks << endl;
                enrolcheck= 1;
            }
            else
            {
                temp<< filename << " " << fileenrol << " " << filemarks  << endl;
            } 
        }
        if(enrolcheck== 1)
        {
            string line;
            ifstream tempcpy("temp.txt");
            ofstream editmarks(testname,ios::trunc);
            while (getline(tempcpy, line)) 
            {
                editmarks << line << "\n";
            }
        }
        else
        {
            if(checkenrol(enrol))
            {
                string line;
                ifstream tempcpy("temp.txt");
                ofstream editmarks(testname,ios::trunc);
                while (getline(tempcpy, line)) 
                    editmarks << line << "\n";

                int fileenrol;
                char name2[50];
                char *temp1 = new char[50];
                ifstream studentnin("studentname.txt");
                while(studentnin.eof() == 0)
                {
                    studentnin >> fileenrol >> name2 >>  temp1;
                    if(fileenrol == enrol)
                    {
                        editmarks << name2 <<  " " << enrol << " " << marks << "\n";
                        cout << "Marks added successfully!" << endl;
                        return;
                    }
                }
            }
            else
            {
                cout << "Enrollment number not found";
                keyproceed();
                teacher_controlpanel();
            }
            cout << "Error adding marks" << endl;
        }
    }

    void addtest(string testname)
    {
        if(checkif_test_exists(testname))
        {
            ofstream testfileadd(testname);
            if(testfileadd.is_open())
            {
                cout << "Test successfully added" << endl;
                testfileadd.close();
                cout << "Do you want to enter marks? ";
                if(ynchoice())
                    add_test_marks(testname);
                else
                    teacher_controlpanel();
            } 
            else
            {    
                cout << "Error! Test not added" << endl;
                keyproceed();
                teacher_controlpanel();
            }
        }
        else
        {
                cout << "This test name already exists" << endl;
                if(ynchoice())
                    get_test_details();
                else
                    teacher_controlpanel();
        }
    }

    void studentdetail()
    {
        char name[50];
        int enrol;
        char *temp = new char[50];
        ifstream studentin("studentname.txt");

        cout << left << setw(15) << "NAME";
        cout << left << setw(20) << "ENROLLMENT NO." << endl <<endl;

        while(studentin.eof() == 0)
        {
            studentin >> enrol >> name >> temp;
            cout << left << setw(15) << name;
            cout << left << setw(20) << enrol << endl; 
        }
        delete[] temp;
    }
 
    void checkuser(char username[])
    {
        //Check if username exists or not
        char filename[50];
        char *temp = new char[50];
        ifstream teacherin("teachername.txt");
        while(teacherin.eof() == 0)
        {
             teacherin >> filename >> temp;
             if(strcmp(username,filename) == 0)
             {
                cout << "User already exists" << endl;
                teacherportal();
             }
        }
        delete[] temp;
    }

    void reguser(char username[],char pass[])
    {
        ofstream teachernout("teachername.txt",ios::app);
        teachernout <<username << " " << pass << "\n";
    }

    int credcheck(char username[], char pass[])
    {
        char filename[50],filepass[50];
        ifstream teacherin("teachername.txt");

        //username check
        while(teacherin.eof() == 0)
        {
            teacherin >> filename;
            teacherin >> filepass;
            if(strcmp(username,filename) == 0)
            {
                //pass check
                if(strcmp(pass,filepass) == 0)
                {
                    //Successfull login
                    return 1;
                }
            }
        }
        return 0;
    }
    
public:
        Teacher()
        {
            strcpy(username," ");
            strcpy(pass," ");
        }

        void reggetdata()
        {
            system("cls");
            cout << "< TEACHER REGISTRATION >" << endl << endl;
            cout << "Enter username: ";
            cin >> username;
            checkuser(username);
            cout << "Enter password: ";
            cin >> pass;
            strcat(pass,username);
            reguser(username,pass);
            cout << "Registered successfully" << endl;
        }
        
        void loggetdata()
        {
            system("cls");
            char rl_choice;
            cout << "< TEACHER LOGIN >" << endl << endl;
            cout << "Enter username : ";
            cin >> username;
            cout << "Enter password : "; 
            cin >> pass;
            cin.ignore();   
            strcat(pass,username);
            if (credcheck(username,pass))
            {
                cout << "Login successfull" << endl << endl;
                cout << "Enter a key to proceed";
                getchar();
            } 
            else
            {
                cout << "Invalid credentials" << endl;
                exit (1);
            }
        }

        void getstudentdetail()
        {
            studentdetail();
            if(ynchoice())
                teacher_controlpanel();
            else
                exitprogram();
        }

        void get_test_details()
        {
            system("cls");
            cout << "==============================================" <<endl;
            cout << " TEST OPERATIONS" << endl;
            cout << "==============================================" <<endl << endl;
            int choice;
            string testname;
  
            cout << "Enter operation" << endl;
            cout << "1 - Create new test" << endl;
            cout << "2 - Add marks of all students to a test" << endl;
            cout << "3 - Edit marks of a student" << endl;
            cout << "4 - Print test details" << endl;
            cout << "5 - Go to Teacher control panel" << endl;
            cin >> choice;
            if(choice == 5)
                teacher_controlpanel();
            else if(choice >5)
            {   cout << "Invalid option" << endl;
                keyproceed();
                get_test_details();
            }
            cout << "Enter test name: ";
            cin >> testname;
            testname += ".txt";

            switch (choice)
            {
            case 1:
                addtest(testname);
                break;
            case 2:
                if(checkif_test_exists(testname)!=1)
                    add_test_marks(testname);
                else
                    cout << "Test not found" << endl;
                keyproceed();
                teacher_controlpanel();
                break;
            case 3: 
                if(checkif_test_exists(testname)!=1)
                    edit_test_marks(testname);
                else
                    cout << "Test not found" << endl;
                keyproceed();
                teacher_controlpanel();
                break;
            case 4:
                if(checkif_test_exists(testname)!=1)
                    print_test_details(testname);
                else
                    cout << "Test not found" << endl;
                keyproceed();
                teacher_controlpanel();
                break;
            default:
                cout << "Invalid option" << endl;
                cin.ignore();
                keyproceed();
                get_test_details();
                break;
            }
        }
};


int main()
{
    collegeportal();
    return 0;
}

inline int ynchoice()
{  
    char choice;
    cout << "Enter Y to continue : ";
    cin >> choice;
    choice = toupper(choice);
    if(choice == 'Y')
        return 1;
    else
        return 0;
}

void collegeportal()
{
    system("cls");
    int st_choice;
    cout << "==============================================" <<endl;
    cout << " WELCOME TO COLLEGE PORTAL" << endl;
    cout << "==============================================" <<endl << endl;
    cout << "[ 1 ] TEACHER" << endl << "[ 2 ] STUDENT" << endl << "[ 3 ] Exit Program"<< endl << endl;
    cout << "Choice : ";
    cin >> st_choice;
    switch (st_choice)
    {
    case 1:
        teacherportal();
        break;
    case 2: 
        studentportal();
        break;
    case 3:
        exitprogram();
        break;
    default:
        cout << "Invalid option!" << endl;
        keyproceed();
        collegeportal();
        break;
    }
}

void teacherportal()
{
    system("cls");
    Teacher t;
    int rl_choice,op_choice;
    cout << "==============================================" <<endl;
    cout << " TEACHER PORTAL" << endl;
    cout << "==============================================" <<endl << endl;
    cout << "[ 1 ] Register" << endl << "[ 2 ] Login" << endl <<"[ 3 ] Go Back"<< endl << endl;
    cout << "Choice: ";
    cin >> rl_choice;
        switch (rl_choice)
        {
        case 1:
            check_admin_pass();
            t.reggetdata();
            cout << "Do you want to login ?" << endl;
            if(ynchoice())
                t.loggetdata();
            else
                exit (1);
            break;
        case 2:
            t.loggetdata();
            break;
        case 3:
            collegeportal();
            break;
        default:
            cout << "Invalid option";
            keyproceed();
            teacherportal();
            break;
        }
        teacher_controlpanel();
}

void teacher_controlpanel()
{
    system("cls");
    Teacher t;
    int op_choice;
    cout << "==============================================" <<endl;
    cout << " TEACHER CONTROL PANEL" << endl;
    cout << "==============================================" <<endl << endl;
    cout << "Enter operation: " << endl;
    cout << "[ 1 ] Student details" << endl;
    cout << "[ 2 ] Test operations" << endl;
    cout << "[ 3 ] Exit program" << endl;
    cout << endl << "Choice : ";
    cin >> op_choice;
    switch (op_choice)
    {
        case 1:
        
            t.getstudentdetail();
            break;
        case 2:
            t.get_test_details();
            break;
        case 3:
            cout << "THANK YOU" << endl;
            exitprogram();
            break;
        default:
            cout << "Invalid option" << endl;
            teacher_controlpanel();
            break;
    }
}
void studentportal()
{
    system("cls");
    Student s;
    int rl_choice;
    cout << "--------------------------------------------" <<endl;
    cout << " STUDENT PORTAL" << endl;
    cout <<"--------------------------------------------" <<endl << endl;
    cout << "[ 1 ] Register" << endl << "[ 2 ] Login" << endl << endl;
    cout << "Choice : ";
    cin >> rl_choice;
        switch (rl_choice)
        {
        case 1:
            check_admin_pass();
            s.reggetdata();
            break;
        case 2:
            s.loggetdata();
            break;
        case 3:
            exitprogram();
            break;
        default:
            cout << "Invalid option" << endl;
            exitprogram();
            break;
        }
    student_controlpanel(s);
}

void student_controlpanel(Student &s)
{   
    system("cls");
    Student s1;
    cout << "==============================================" <<endl;
    cout << " STUDENT CONTROL PANEL" << endl;
    cout << "==============================================" <<endl << endl;
    int op_choice;
    cout << "Enter operation: " << endl;
    cout << "[ 1 ] View marks of a test" << endl;
    cout << "[ 2 ] Exit Program" << endl;
    cout << endl << "Choice : ";
    cin >> op_choice;
    switch (op_choice)
    {
        case 1:
            s.get_test_marks();
            break;
        case 2:
            cout << "Thank You" << endl;
            exitprogram();
            break;
        default:
            cout << "Invalid option" << endl;
            student_controlpanel(s1);
            break;
    }
}

int checkif_test_exists(string testname)
{
    string temp;
        ifstream testcheck(testname);
        if(testcheck)
            return 0;
        else
            return 1;
}

void exitprogram()
{
    cout << "Exiting program..." << endl;
    system("cls");
    exit(1);
}

void fileopenerror()
{
    cout << "Error while opening the file" << endl;
    exit(1);
}

void check_admin_pass()
{
    char *pass = new char[50];
    cout << "Enter admin password : ";
    cin >> pass;
    if(strcmp(pass,"admin") == 0)
        return;
    else
    {
        cout << "Incorrect password" << endl;
        exit(1);
    }
}

void keyproceed()
{
    cout << endl << "Enter a key to proceed";
    cin.ignore();
    getchar();
}



