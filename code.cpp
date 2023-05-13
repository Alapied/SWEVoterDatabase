#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

string canddir = "candidates.txt";
string voterdir = "voters.txt";
vector<vector<string>> candidatedatabase(0, vector<string>(5));
vector<vector<string>> voterdatabase(0, vector<string>(7));


void printdata();
void writedatabase();
void readindata();
int searchDB(string Searchstring, vector<vector<string>> database, int Searchposition);
void add_to_database(string record[5]);
void newentry();
void menuOptionsVoter(int number);
void menuoptionsadmin();
int login();
void menu(bool Admin, int number);
void printCandidates(string suburb);
void castVote(int index);

int main(){
     readindata();
    int index = login();
    

    bool isAdmin = false;

    if (index == -1) {
        cout << "Login failed";
        //return 0;
    }
    if (voterdatabase[index][6] == "true") {
        isAdmin = true;
    }
    menu(isAdmin, index);
  

    //cout << "printing data";
    //printdata();

    //menuoptionsvoter();
    return 0;
}

void printdata() {
            cout << "Printing : " << candidatedatabase.size() << " records" << endl;
    for (int i = 0; i < candidatedatabase.size(); i++) {

        for (int j = 0; j < 6; j++)
        {
            cout << candidatedatabase[i][j] << "\t";
            //cout << "test";
        }
        cout << endl;
    }
    cout << "Printing : " << voterdatabase.size() << " records" << endl;
    for (int i = 0; i < voterdatabase.size(); i++) {

        for (int j = 0; j < 7; j++)
        {
            cout << voterdatabase[i][j] << "\t";
            //cout << "test";
        }
        cout << endl;

    }
}

void writedatabase() {
    fstream file(canddir, ios::out | ios::trunc);
    if (file.is_open()) {
        cout << "File Opened" << endl;
        if (file.good())
        {
            cout << "database size to write: " << candidatedatabase.size() << endl;
            for (int i = 1; i < candidatedatabase.size(); i++)
            {
                cout << "Writing entry: " << i << endl;
                cout << "Record: ";
                for (int j = 0; j < 6; j++)
                {
                    cout << j;
                    if (j == 5) {
                        file << candidatedatabase[i][j] << '\n';
                    }
                    else {
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
    if (file2.is_open()) {
        cout << "File Opened" << endl;
        if (file2.good())
        {
            cout << "database size to write: " << voterdatabase.size() << endl;
            for (int i = 1; i < voterdatabase.size(); i++)
            {
                cout << "Writing entry: " << i << endl;
                cout << "Record: ";
                for (int j = 0; j < 7; j++)
                {
                    cout << j;
                    if (j == 6) {
                        file2 << voterdatabase[i][j] << '\n';
                    }
                    else {
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

void readindata() {
    vector<string> headerRec = { "CandidateID","Symbol", "Name", "Age", "Suburb", "Votes" };
    //candidatedatabase.push_back(headerRec);
    fstream file(canddir);
    if (file.is_open()) {
        cout << "File Opened" << endl;
        while (file.good())
        {
            //cout << "Started readin entry" << endl;
            vector<string> entry;

            if (file.eof()) {
                //cout << "end of file, breaking" << endl;
            }
            for (int i = 0; i < 6; i++)
            {
                string element;
                if (i == 5) {
                    getline(file, element, '\n');
                }
                else {
                    getline(file, element, ',');
                }

                //cout << element << endl;
                entry.push_back(element);
                if (file.peek() == '\n') {
                    file.ignore(); // ignore /n
                    //cout << "Ignored N";
                }

            }
            candidatedatabase.push_back(entry);
            //cout << "entered entry" << endl;
        }
        //cout << "Ended Read";
        file.close();

    }
}
	
	
int searchDB(string Searchstring,vector<vector<string>> database , int Searchposition){
    int i;
    for (i = 0; i < database.size(); i++)
    {
        if (database[i][Searchposition] == Searchstring){
            return i;
        }
    }
    
    return i = -1;
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

void menuOptionsVoter(int index) {
    char menuoption;
    while (true) {
        cout << "\nP - Print total votes for candidates" << endl;
        cout << "A - Vote for a candidate" << endl;
        cout << "S - Display least voted candidate" << endl;
        cout << "L - Display most voted candidate" << endl;
        cout << "Q - Quit\n" << endl;
        cout << "Enter Menu Option: " << endl;
        cin >> menuoption;
        menuoption = toupper(menuoption);
        cin.ignore();
        switch (menuoption)
        {
        case 1:
            //newentry();
            break;
        case 'A':
            if (voterdatabase[index][5] == "true")
            {
                cout << endl << "You have already casted your vote!" << endl;
            }
            else
            {
                castVote(index);
            }
            break;
        case 3:
           //printdata();
            break;
        case 4:
            //printdata();
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
    while (true){
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

int login(){
    string IDstring;
    int index = -1;
    int attempts = 0;
    bool loggedin = false;
    while (loggedin == false){
        if (attempts > 3){
            return -1;
        }
        cout << "Please Enter ID: ";
        getline(cin, IDstring);
        index = searchDB(IDstring,voterdatabase , 0);
        if (index != -1){
            string PIN;
            cout << "Please enter PIN: ";
            getline(cin , PIN);
            if (voterdatabase[index][2] == PIN){
                loggedin = true;
                break;
            } else {
                cout << "Incorrect Password, try again" << endl;
                attempts++;
            }
        } else {
            cout << "That VoterID does not exist, try again" << endl;
            attempts++;
        }
    }
    if (loggedin == true){
        return index;
    }
    
    
}

void menu(bool Admin, int index) {
    if (Admin) {
        menuoptionsadmin();
    }
    else {
        menuOptionsVoter(index);
    }
}

void printCandidates(string suburb)
{
    cout << "-----------------------------------------------" << endl;
    cout << setw(20) << left << "Symbol" << setw(10) << "Name" << setw(10) << left << "Number" << endl;
    for (int i = 1; i < candidatedatabase.size(); i++) {
        
        if (suburb == candidatedatabase[i][4])
        {
            cout << left << setw(16) << candidatedatabase[i][1];
            cout << left << setw(16) << candidatedatabase[i][2];
            cout << left << setw(10) << candidatedatabase[i][0];
            cout << endl;
        }
      
    }
    cout << "-----------------------------------------------" << endl;
    cout << endl;
}

void castVote(int index)
{
    string vote;
    char confirm = 'N';
    cout <<endl<< "Suburb: " << voterdatabase[index][4] << endl;
    printCandidates(voterdatabase[index][4]);

    cout << "Enter candidate number: ";
    cin >> vote;
    cin.ignore();

    while (confirm != 'Y') //TO_UPPER
    {
        cout << "Please confirm your vote (Y/N): ";
        cin >> confirm;

        if (confirm == 'N') //TO_UPPER
        {
            cout << "Enter candidate number: ";
            cin >> vote;
            cin.ignore();
        }
    }
    if (confirm == 'Y')
    {

        voterdatabase[index][5] = "true";

        for (int i = 1; i < candidatedatabase.size(); i++) {

            if (vote == candidatedatabase[i][0])
            {
                int count = stoi(candidatedatabase[i][5]) + 1;
                candidatedatabase[i][5] = to_string(count);
                //cout << "VOTE COUNT: " << candidatedatabase[i][5] << endl;
                break;
            }

        }
    }
    
}