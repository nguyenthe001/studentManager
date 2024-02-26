#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;
struct Student{
    int id;
    string name;
    int age;
    float grade;
};

vector<Student> readFile(vector<Student>& students){
	ifstream input;
    input.open("data.txt");
    string data;
    while (getline(input, data)) {
        Student student;
        string delimiter = ";";
        int posOfDelimiter = data.find(delimiter);
        student.id = stoi(data.substr(0, posOfDelimiter));
        data = data.substr(posOfDelimiter + 1, data.length() - 1);
        posOfDelimiter = data.find(delimiter);
        student.name = data.substr(0, posOfDelimiter);
        data = data.substr(posOfDelimiter + 1, data.length() - 1);
        posOfDelimiter = data.find(delimiter);
        student.age = stoi(data.substr(0, posOfDelimiter));
        data = data.substr(posOfDelimiter + 1, data.length() - 1);
        student.grade = stof(data);
        students.push_back(student);
    }
    input.close();
    return students;
}

void showStudentList(vector<Student> students){
    cout << "[1] Danh sach sinh vien \n";
    cout << "\t+---+----+---------------------------+----+----+\n";
    cout << "\t|STT|" << setw(4) << right << "MaSV|" 
        << setw(27) << left << "Ho va ten" 
        << setw(4) << right << "|Tuoi" << "|Diem|" << endl;
    cout << "\t+---+----+---------------------------+----+----+\n";
    for(int i = 0; i < students.size(); i++){
        cout << "\t|" << setw(3) << right << i + 1 << "|" 
            << setw(4) << right << students[i].id << "|"
            << setw(27) << left << students[i].name << "|" 
            << setw(4) << right << students[i].age << "|" 
            << setw(4) << right << students[i].grade << "|\n";
    }
    cout << "\t+---+----+---------------------------+----+----+\n";
}

void addStudent(vector<Student>& students){
    cout << "[2] Them sinh vien \n";
    int n;
    cout << "\t[?] Nhap so luong sinh vien can them: ";
    cin >> n;
    Student student[n];
    for (int i = 0; i < n; ++i){
        system("cls");
        cout << "Sinh vien " << i + 1 << endl;
        cout << "\t[?] Nhap ID: ";
        cin >> student[i].id;
        cout << "\t[?] Nhap ho ten sinh vien: ";
        cin.ignore();
        getline(cin, student[i].name);
        cout << "\t[?] Nhap tuoi cua sinh vien: ";
        cin >> student[i].age;
        cout << "\t[?] Nhap diem cua sinh vien: ";
        cin >> student[i].grade;
        students.push_back(student[i]);
    }

    ofstream output("data.txt", ios::app);
    if (output.is_open()) {
        for (int i = 0; i < n; ++i){
            output << student[i].id << ";" << student[i].name << ";" << student[i].age 
                << ";" << student[i].grade << ";\n";
        }
        output.close();
        cout << "\t\n---Thanh cong---! \n";
    } else {
        cout << "\t\n---Loi---! \n";
    }
    output.close();
}

void editStudentInfo(vector<Student>& students){
    cout << "[3] Sua thong tin sinh vien \n";
    showStudentList(students);

    int id;
    cout << "\t[?] Nhap ID sinh vien can sua: ";
    cin >> id;

    int count = 0;
    for (Student& student : students) {
        if (student.id != id) {
            ++count;
            if(count == students.size()){
                cout << "\t\t\n(!)Ma sinh vien khong ton tai!\n";
                break;
            }
            continue;
        }
        else{
            cout << "\t\t[?] Nhap ten moi: ";
            cin.ignore();
            getline(cin, student.name);
            cout << "\t\t[?] Nhap tuoi moi: ";
            cin >> student.age;
            cout << "\t\t[?] Nhap diem moi: ";
            cin >> student.grade;
            break;
        }
    }

    ofstream output("data.txt");
    for (const Student& student : students) {
        output << student.id << ";" << student.name << ";" << student.age << ";" << student.grade << ";\n";
    }
    output.close();
}

void deleteStudent(vector<Student>& students){
    cout << "[4] Xoa thong tin sinh vien \n";
    showStudentList(students);

    int id;
    cout << "\t[?] Nhap ID sinh vien can xoa: ";
    cin >> id;

    int count = 0;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id != id) {
            ++count;
            if(count == students.size()){
                cout << "\n\tMa sinh vien khong ton tai!\n";
                break;
            }
            continue;
        }
        else{
            students.erase(it);
            cout << "\n\tDa xoa sinh vien co ID: " << id << "\n";
            break;
        }
    }

    ofstream output("data.txt");
    for (const Student& student : students) {
        output << student.id << ";" << student.name << ";" << student.age << ";" << student.grade << ";\n";
    }
    output.close();
}

void searchStudent(vector<Student> students){
    cout << "[5] Tim kiem sinh vien \n";
    
    int subselection;
    cout << "\t1 - Tim kiem theo ID ";
    cout << "\n\t2 - Tim kiem theo ten ";
    cout << "\n\t[?] Nhap lua chon: ";
    cin >> subselection;
    if(subselection == 1){
        system("cls");
        cout << "[1] Tim kiem theo ID: ";
        int id;
        cout << "\n\t[?] Nhap ID sinh vien can tim: ";
        cin >> id;
    
        int count = 0;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id != id) {
                ++count;
                if(count == students.size()){
                    cout << "\n\tMa sinh vien khong ton tai!\n";
                    break;
                }
                continue;
            }
            else{
                cout << "\t+---+----+---------------------------+----+----+\n";
                cout << "\t|STT|" << setw(4) << right << "MaSV|" 
                    << setw(27) << left << "Ho va ten" 
                    << setw(4) << right << "|Tuoi" << "|Diem|" << endl;
                int i = 1;
                cout << "\t+---+----+---------------------------+----+----+\n";
                cout << "\t|" << setw(3) << right << i << "|" 
                    << setw(4) << right << it->id << "|"
                    << setw(27) << left << it->name << "|" 
                    << setw(4) << right << it->age << "|" 
                    << setw(4) << right << it->grade << "|\n";
                cout << "\t+---+----+---------------------------+----+----+\n";
                break;
            }
        }
    }
    else if(subselection == 2){
        system("cls");
        cout << "[2] Tim kiem theo ten ";
        string name;
        cout << "\n\t[?] Nhap ten sinh vien can tim: ";
        cin.ignore();
        getline(cin, name);
    
        int count = 0;
        cout << "\t+---+----+---------------------------+----+----+\n";
        cout << "\t|STT|" << setw(4) << right << "MaSV|" 
            << setw(27) << left << "Ho va ten" 
            << setw(4) << right << "|Tuoi" << "|Diem|" << endl;
        cout << "\t+---+----+---------------------------+----+----+\n";
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->name.find(name) == string::npos) {
                ++count;
                if(count == students.size()){
                    break;
                }
                continue;
            }
            else{
                cout << "\t|" << setw(3) << right << "1" << "|" 
                    << setw(4) << right << it->id << "|"
                    << setw(27) << left << it->name << "|" 
                    << setw(4) << right << it->age << "|" 
                    << setw(4) << right << it->grade << "|\n";
            }
        }
        cout << "\t+---+----+---------------------------+----+----+\n";
    }
}

bool sortByName(const Student& a, Student& b){
    return a.name < b.name;
}

bool sortByAge(const Student& a, Student& b){
    return a.age < b.age;
}

bool sortByGrade(const Student& a, Student& b){
    return a.grade < b.grade;
}

void sortStudentList(vector<Student> students){
    //sap xep theo ten(a-z)
    cout << "[6] Sap xep danh sach sinh vien \n";
    int subselection;
    cout << "\t1 - Sap xep theo ten ";
    cout << "\n\t2 - Sap xep theo theo tuoi ";
    cout << "\n\t3 - Sap xep theo diem";
    cout << "\n\t[?] Nhap lua chon: ";
    cin >> subselection;
    if(subselection == 1){
        sort(students.begin(), students.end(), sortByName);
        cout << "\t+---+----+---------------------------+----+----+\n";
        cout << "\t|STT|" << setw(4) << right << "MaSV|" 
            << setw(27) << left << "Ho va ten" 
            << setw(4) << right << "|Tuoi" << "|Diem|" << endl;
        cout << "\t+---+----+---------------------------+----+----+\n";
        for(int i = 0; i < students.size(); i++){
            cout << "\t|" << setw(3) << right << i + 1 << "|" 
                << setw(4) << right << students[i].id << "|"
                << setw(27) << left << students[i].name << "|" 
                << setw(4) << right << students[i].age << "|" 
                << setw(4) << right << students[i].grade << "|\n";
        }
        cout << "\t+---+----+---------------------------+----+----+\n";
    }
    //sap xep theo tuoi
    else if(subselection == 2){
        sort(students.begin(), students.end(), sortByAge);
        cout << "\t+---+----+---------------------------+----+----+\n";
        cout << "\t|STT|" << setw(4) << right << "MaSV|" 
            << setw(27) << left << "Ho va ten" 
            << setw(4) << right << "|Tuoi" << "|Diem|" << endl;
        cout << "\t+---+----+---------------------------+----+----+\n";
        for(int i = 0; i < students.size(); i++){
            cout << "\t|" << setw(3) << right << i + 1 << "|" 
                << setw(4) << right << students[i].id << "|"
                << setw(27) << left << students[i].name << "|" 
                << setw(4) << right << students[i].age << "|" 
                << setw(4) << right << students[i].grade << "|\n";
        }
        cout << "\t+---+----+---------------------------+----+----+\n";
    }
    //sap xep theo diem
    else if (subselection == 3){
        sort(students.begin(), students.end(), sortByGrade);
        cout << "\t+---+----+---------------------------+----+----+\n";
        cout << "\t|STT|" << setw(4) << right << "MaSV|" 
            << setw(27) << left << "Ho va ten" 
            << setw(4) << right << "|Tuoi" << "|Diem|" << endl;
        cout << "\t+---+----+---------------------------+----+----+\n";
        for(int i = 0; i < students.size(); i++){
            cout << "\t|" << setw(3) << right << i + 1 << "|" 
                << setw(4) << right << students[i].id << "|"
                << setw(27) << left << students[i].name << "|" 
                << setw(4) << right << students[i].age << "|" 
                << setw(4) << right << students[i].grade << "|\n";
        }
        cout << "\t+---+----+---------------------------+----+----+\n";
    }
}

void statistics(vector<Student> students){
    cout << "[7] Thong ke\n";
    //Thong ke diem trung binh cua ca lop
    int sum = 0;
    int quantity = 0;
    for (auto it = students.begin(); it != students.end(); ++it){
        sum += it->grade;
        quantity += 1;
        if (it == (students.end() - 1)){
            float AVG = static_cast<float>(sum)/quantity;
            cout << "\t(!) Diem trung binh ca lop: " << AVG << endl;
        }
    }
    //Ti le sinh vien gioi(grade >= 9.0)
    int excellent = 0;
    for (auto it = students.begin(); it != students.end(); ++it){
        if(it -> grade >= 9){
            excellent += 1;
        }
        if (it == (students.end() - 1)){
            float exPercent = static_cast<float>(excellent)/quantity * 100;
            cout << "\t(!) Ti le sinh vien gioi: " << exPercent << "%" << endl;
        }
    }
    //Ti le sinh vien kha(7.5 <= grade < 9.0)
    int good = 0;
    for (auto it = students.begin(); it != students.end(); ++it){
        if(it -> grade >= 7.5 && it -> grade < 9){
            good += 1;
        }
        if (it == (students.end() - 1)){
            float goodPercent = static_cast<float>(good)/quantity * 100;
            cout << "\t(!) Ti le sinh vien kha: " << goodPercent << "%" << endl;
        }
    }

    //Ti le sinh vien trung binh(5.0 <= grade < 7.5)
    int average = 0;
    for (auto it = students.begin(); it != students.end(); ++it){
        if(it -> grade >= 5 && it -> grade < 7.5){
            average += 1;
        }
        if (it == (students.end() - 1)){
            float avgPercent = static_cast<float>(average)/quantity * 100;
            cout << "\t(!) Ti le sinh vien trung binh: " << avgPercent << "%" << endl;
        }
    }
    
    //Ti le sinh vien kem(0 <= grade < 5.0)
    int poor = 0;
    for (auto it = students.begin(); it != students.end(); ++it){
        if(it -> grade >= 0 && it -> grade < 5){
            poor += 1;
        }
        if (it == (students.end() - 1)){
            float poorPercent = static_cast<float>(poor)/quantity * 100;
            cout << "\t(!) Ti le sinh vien kem: " << poorPercent << "%" << endl;
        }
    }

    //Sinh vien dat ket qua tot nhat
    int best = 0;
    for (auto it = students.begin(); it != students.end(); ++it){
        if(it -> grade > best){
            best = it -> grade;
        }
    }
    cout << "\t(!) Sinh vien co ket qua tot nhat: " << endl;
    cout << "\t+---+----+---------------------------+----+----+\n";
    cout << "\t|STT|" << setw(4) << right << "MaSV|" 
        << setw(27) << left << "Ho va ten" 
        << setw(4) << right << "|Tuoi" << "|Diem|" << endl;
    cout << "\t+---+----+---------------------------+----+----+\n";
    int number = 0;
    for (auto it = students.begin(); it != students.end(); ++it){
        if(it -> grade == best){
            number += 1;
            cout << "\t|" << setw(3) << right << number << "|" 
                << setw(4) << right << it -> id << "|"
                << setw(27) << left << it -> name << "|" 
                << setw(4) << right << it -> age << "|" 
                << setw(4) << right << it -> grade << "|\n";
        }
    }
    cout << "\t+---+----+---------------------------+----+----+\n";
    cout << endl;
}

void menu(vector<Student>& students){
    int selection;
    do{
        cout << "---Menu---";
        cout << "\n1 - In danh sach sinh vien";
        cout << "\n2 - Them";
        cout << "\n3 - Sua";
        cout << "\n4 - Xoa";
        cout << "\n5 - Tim kiem";
        cout << "\n6 - Sap xep";
        cout << "\n7 - Thong ke";
        cout << "\n0 - Thoat";
        cout << "\nNhap lenh: ";
        cin >> selection;
        cin.ignore();
        switch(selection){
            case 1:
				system("cls");
                showStudentList(students);
                system("pause");
                system("cls");
				break;
            case 2:
				system("cls");
                addStudent(students);
                system("pause");
                system("cls");
				break;
            case 3:
				system("cls");
                editStudentInfo(students);
                system("pause");
                system("cls");
				break;
            case 4:
				system("cls");
                deleteStudent(students);
                system("pause");
                system("cls");
				break;
            case 5:
				system("cls");
                searchStudent(students);
                system("pause");
                system("cls");
				break;
            case 6:
				system("cls");
                sortStudentList(students);
                system("pause");
                system("cls");
				break;
            case 7:
				system("cls");
                statistics(students);
                system("pause");
                system("cls");
				break;
            case 0:
				break;
        }
    }
    while(selection);
}

int main(){
    vector<Student> students;
    students = readFile(students);
    menu(students);
    return 0;
}
