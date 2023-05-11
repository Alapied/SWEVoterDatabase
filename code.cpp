#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string canddir = "candiates.txt";
string voterdir = "voters.txt";
vector<vector<string>> candidatedatabase(0, vector<string>(5));
vector<vector<string>> voterdatabase(0, vector<string>(5));
bool menu = true;

void printdata() {
            cout << "Printing : " << candidatedatabase.size() << " records" << endl;
            for (int i = 0; i < candidatedatabase.size(); i++){
                
                for (int j = 0; j < 5; j++)
                {
                    cout << candidatedatabase[i][j]<< "\t";
                    //cout << "test";
                }
                cout << endl;
            }
            cout << "Printing : " << voterdatabase.size() << " records" << endl;
            for (int i = 0; i < voterdatabase.size(); i++){
                
                for (int j = 0; j < 5; j++)
                {
                    cout << voterdatabase[i][j]<< "\t";
                    //cout << "test";
                }
                cout << endl;
            
        }
}

void writedatabase(){
    fstream file(canddir, ios::out | ios::trunc);
    if (file.is_open()){
        cout << "File Opened" << endl;
        if (file.good())
        {   
            cout << "database size to write: " << candidatedatabase.size() << endl;
           for (int i = 1; i < candidatedatabase.size(); i++)
           {
            cout << "Writing entry: " << i << endl;
            cout << "Record: ";
            for (int j = 0; j < 5; j++)
            {
                 cout <<  j;
                if (j == 4){
                    file << candidatedatabase[i][j] << '\n';
                } else {
                    file << candidatedatabase[i][j] << ',';
                }
                
            }
            cout << endl;
            }
            cout << "Ended Write"; 
            file.close();
        }
    }
    fstream file2(voterdir, ios::out | ios::trunc);
    if (file2.is_open()){
        cout << "File Opened" << endl;
        if (file2.good())
        {   
            cout << "database size to write: " << voterdatabase.size() << endl;
           for (int i = 1; i < voterdatabase.size(); i++)
           {
            cout << "Writing entry: " << i << endl;
            cout << "Record: ";
            for (int j = 0; j < 5; j++)
            {
                 cout <<  j;
                if (j == 4){
                    file2 << voterdatabase[i][j] << '\n';
                } else {
                    file2 << voterdatabase[i][j] << ',';
                }
                
            }
            cout << endl;
            }
            cout << "Ended Write"; 
            file2.close();
        }
    }
}
void readindata(){
    vector<string> headerRec = {"Symbol", "Name", "Age", "Suburb", "Votes"};
    candidatedatabase.push_back(headerRec);
    fstream file(canddir);
    if (file.is_open()){
        cout << "File Opened" << endl;
        while (file.good())
        {
           cout << "Started readin entry" << endl;
           vector<string> entry;
           
           if (file.eof()){
            cout << "end of file, breaking" << endl;
           }
           for (int i = 0; i < 5; i++)
           {
            string element;
            if (i == 4){
                getline(file, element, '\n');
            } else {
                getline(file, element, ',');
            }
            
            cout << element << endl;
            entry.push_back(element);
             if (file.peek() == '\n'){
            file.ignore(); // ignore /n
            cout << "Ignored N";
            }
            
           }
           candidatedatabase.push_back(entry);
            cout << "entered entry"<< endl;
        }
        cout << "Ended Read"; 
        file.close();
        
    }
    vector<string> headerRec2 = {"VoterID", "Name", "PIN",  "Age", "Suburb", "Status", "IsAdmin"};
    voterdatabase.push_back(headerRec2);
    fstream file2(voterdir);
    if (file2.is_open()){
        cout << "File Opened" << endl;
        while (file2.good())
        {
           cout << "Started readin entry" << endl;
           vector<string> entry;
           
           if (file2.eof()){
            cout << "end of file, breaking" << endl;
           }
           for (int i = 0; i < 7; i++)
           {
            string element;
            if (i == 6){
                getline(file2, element, '\n');
            } else {
                getline(file2, element, ',');
            }
            
            cout << element << endl;
            entry.push_back(element);
             if (file2.peek() == '\n'){
            file2.ignore(); // ignore /n
            cout << "Ignored N";
            }
            
           }
           voterdatabase.push_back(entry);
            cout << "entered entry"<< endl;
        }
        cout << "Ended Read"; 
        file2.close();
        
    }
}

void add_to_database(string record[5]){
    vector<string> vecRecord(record, record + 5);
    candidatedatabase.push_back(vecRecord);
    voterdatabase.push_back(vecRecord);
    writedatabase();
}

void newentry(){
    string record[5]; 
    string clearbuffer;
    cin.clear();   
    cout << "Enter ID: ";
    getline(cin, clearbuffer);
    getline(cin, record[0]);
    cout << "Enter Name: ";
    getline(cin, record[1]);
    cout << "Enter Age";
    getline(cin, record[2]);
    cout << "Enter Suburb";
    getline(cin, record[3]);
    cout << "Enter Status";
    getline(cin, record[4]);
    cout << "Enter a Count";
    getline(cin, record[4]);
    add_to_database(record);
}

void menuoptionsvoter(){
    int menuoption;
    // Menuoptions for Voters
    while (menu){
        cout << "Enter Menu Option: " << endl;
        cin >> menuoption;
        switch (menuoption)
        {
        case 1:
            newentry();
            break;
        case 2:
            newentry();
            break;
        case 3:
            printdata();
            break;
        case 4:
            printdata();
            break;
        default:
            cout << "Invalid Menu option" << endl;
            break;
        }
    }
    
}

void menuoptionsadmin(){
    int menuoption;
    // Menuoptions for admins
    while (menu){
        cout << "Enter Menu Option: " << endl;
        cin >> menuoption;
        switch (menuoption)
        {
        case 1:
            newentry();
            break;
        case 2:
            newentry();
            break;
        case 3:
            printdata();
            break;
        case 4:
            printdata();
            break;
        default:
            cout << "Invalid Menu option" << endl;
            break;
        }
    }
    
}


int main(){
    readindata();
    //cout << "printing data";
    //printdata();
    menuoptionsvoter();
    return 0;
}