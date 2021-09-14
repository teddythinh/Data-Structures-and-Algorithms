#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;
int main(){
    ifstream file("input.txt");
    string a, name, toan, ly, hoa;
    float total, average;
    while(!file.eof()){
        getline(file, a);
        stringstream ss(a);
        getline(ss, name, ',');
        getline(ss, toan, ',');
        if(toan == ""){
            toan = "0";
        }
        getline(ss, ly, ',');
        if(ly == ""){
            ly = "0";
        }
        getline(ss, hoa, ',');
        if(hoa == ""){
            hoa = "0";
        }
        total = stof(toan) + stof(ly) + stof(hoa);
        average = total / 3;
        cout << "Name: " << name << endl;
        cout << "Total: " << total << endl;
        cout << "Average: " << average << endl;
        cout << endl;
    }
}