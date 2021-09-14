#include <iostream> 
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

struct Company
{
    string name, tax, address;
};

vector<Company> readCompanyList(string file_name){
    ifstream input(file_name);
    string a, name, tax, address;
    getline(input, a);
    
    Company com;
    vector<Company> companyList;
    
    while(!input.eof()){
        getline(input, a);
        stringstream ss(a);
        
        getline(ss, name, '|');
        getline(ss, tax, '|');
        getline(ss, address);

        com.name = name;
        com.tax = tax;
        com.address = address;

        companyList.push_back(com);
    }
    input.close();
    return companyList;
}

long long hashCalculate(int p, int i, int m){
    long long result = 1;
    for(int j=0; j < i; j++){
        result *= p;
        result = result % m;
    }
    return result;
}

long long hashString(string company_name){
    int length = company_name.size();
    if(length > 20){
        length = 20;
    }
    else{
        length = company_name.length();
    }

    int begin = company_name.length();

    if(begin > 20){
        begin = company_name.length() - 20;
    }
    else {
        begin = 0;
    }

    int m = pow(10, 9) + 9;
    long long hashVal = 0;

    for(int i = begin; i < (begin + length); i++){
        hashVal += int(company_name[i]) * hashCalculate(31, i - begin, m);
        hashVal = hashVal % m;
    }
    return hashVal;
}

Company* createHashTable(vector<Company> list_company) {
    Company* pCom = new Company[2000];
    for(int i = 0; i < 2000; i++) {
        pCom[i] = {"", "", ""};
    }

    for(int i = 0; i < list_company.size(); i++) {
        int hashVal = hashString(list_company[i].name);

        if(pCom[hashVal % 2000].name == "") {
            pCom[hashVal % 2000] = {list_company[i].name, list_company[i].tax, list_company[i].address};
        }
        else {
            int temp = hashString(list_company[i].name) % 2000 + 1;
            while(pCom[temp].name != "") {
                temp = (temp + 1) % 2000;
            }
            pCom[temp] = {list_company[i].name, list_company[i].tax, list_company[i].address};
        }
    }
    return pCom;
}

int main(){
    Company* pCom = createHashTable(readCompanyList("MST.txt"));
    for(int i = 0; i < 2000; i++){
        if(pCom[i].name != ""){
            cout << i << pCom[i].name << endl;
        }
    }
    delete[] pCom;
    return 0;
}


