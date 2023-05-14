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

bool DEBUGMODE = false;

void writedatabase();
void readindata();
int searchDB(string Searchstring, vector<vector<string>> database, int Searchposition);
void add_to_database(string record[5]);
void newentry();
void menuOptionsVoter(int number);
void menuoptionsadmin(int);
int login();
void menu(bool Admin, int number);
void printCandidates(string suburb);
void castVote(int index);
void minVoteCandidate();
void maxVoteCandidate();
void displayAllCandidates();
void addMultiVote(string);


int main(){
    readindata();
    int index = login();
    bool isAdmin = false;
    if (index == -1) {
        cout << "Login failed";
    } else {
        if (voterdatabase[index][6] == "true") {
            isAdmin = true;
        }
        menu(isAdmin, index);
    }
    return 0;
}

void writedatabase() {
    cout << "Saving Changes" << endl;
    fstream file(canddir, ios::out | ios::trunc);
    if (file.is_open()) {
        if (DEBUGMODE)
        {
           cout << "File Opened" << endl;
        }
        if (file.good())
        {
            if (DEBUGMODE)
            {
                cout << "database size to write: " << candidatedatabase.size() << endl;
            }
            for (int i = 0; i < candidatedatabase.size(); i++)
            {
                if (DEBUGMODE){
                    cout << "Writing entry: " << i << endl;
                    cout << "Record: ";
                }
                for (int j = 0; j < 6; j++)
                {
                    if (DEBUGMODE){
                        cout << j;
                    }
                    if (j == 5) {
                        file << candidatedatabase[i][j] << '\n';
                    }
                    else {
                        file << candidatedatabase[i][j] << ',';
                    }
                }
                if (DEBUGMODE){
                    cout << endl;
                }
                
            }
            if (DEBUGMODE){
                cout << "Ended Write" << endl;
            }
            file.close();
        }
    }
    fstream file2(voterdir, ios::out | ios::trunc);
    if (file2.is_open()) {
        if (DEBUGMODE){
           cout << "File Opened" << endl;
        }
        if (file2.good()){
            if (DEBUGMODE){
                cout << "database size to write: " << candidatedatabase.size() << endl;
            }
            for (int i = 0; i < voterdatabase.size(); i++){
                if (DEBUGMODE){
                    cout << "Writing entry: " << i << endl;
                    cout << "Record: ";
                }
                for (int j = 0; j < 7; j++)
                {
                    if (DEBUGMODE){
                        cout << j;
                    }
                    if (j == 6) {
                        file2 << voterdatabase[i][j] << '\n';
                    }
                    else {
                        file2 << voterdatabase[i][j] << ',';
                    }

                }
                if (DEBUGMODE){
                    cout << endl;
                }
            }
            if (DEBUGMODE){
                cout << "Ended Write" << endl;
            }
            file2.close();
            cout << "Database Saved" << endl;
        }
    }
}

void readindata() {
    //vector<string> headerRec = { "CandidateID","Symbol", "Name", "Age", "Suburb", "Votes" };
    fstream file(canddir);
    if (file.is_open()) {
        if (DEBUGMODE)
        {
           cout << "File Opened" << endl;
        }
        while (file.good())
        {
            if (DEBUGMODE){
                cout << "Started record copy" << endl;
            }
            vector<string> entry;

            if (file.eof()) {
                //cout << "end of file, breaking" << endl;
                //break;
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


    //vector<string> headerRec2 = { "VoterID", "Name", "PIN",  "Age", "Suburb", "Status", "IsAdmin" };
    fstream file2(voterdir);
    if (file2.is_open()) {
        while (file2.good())
        {
            vector<string> entry;
            if (file2.eof()) {
                //cout << "end of file, breaking" << endl;
                //break;
            }
            for (int i = 0; i < 7; i++)
            {
                string element;
                if (i == 6) {
                    getline(file2, element, '\n');
                }
                else {
                    getline(file2, element, ',');
                }
                entry.push_back(element);
                if (file2.peek() == '\n') {
                    file2.ignore(); // ignore /n
                }

            }
            voterdatabase.push_back(entry);
        }
        file2.close();
    }
}

int searchDB(string Searchstring,vector<vector<string>> database , int Searchposition){
    int i;
    for (i = 0; i < database.size(); i++){
        if (database[i][Searchposition] == Searchstring){
            return i;
        }
    }
    return i = -1;
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
        case 'P':
            displayAllCandidates();
            break;
        case 'A':
            if (voterdatabase[index][5] == "true")
            {
                cout << endl << "You have already casted your vote!" << endl;
            }
            else
            {
                castVote(index);
                writedatabase();
            }
            break;
        case 'S':
            minVoteCandidate();
            break;
        case 'L':
            maxVoteCandidate();
            break;
        case 'Q':
            exit(0);
            break;
        default:
            cout << "Invalid Menu option" << endl;
            break;
        }
    }
}

void menuoptionsadmin(int index){
    char menuoption;
    string inputID;
    while (true) {
        cout << "\nP - Print total votes for candidates" << endl;
        cout << "V - Cast personal vote for a candidate" << endl;
        cout << "A - Count Extra Votes - Add Votes to candidate" << endl;
        cout << "S - Display least voted candidate" << endl;
        cout << "L - Display most voted candidate" << endl;
        cout << "Q - Quit\n" << endl;
        cout << "Enter Menu Option: " << endl;
        cin >> menuoption;
        menuoption = toupper(menuoption);
        cin.ignore();
        switch (menuoption)
        {
        case 'P':
            displayAllCandidates();
            break;
        case 'V':
            if (voterdatabase[index][5] == "true")
            {
                cout << endl << "You have already casted your vote!" << endl;
            }
            else
            {
                castVote(index);
                writedatabase();
            }
            break;
        case 'S':
            minVoteCandidate();
            break;
        case 'L':
            maxVoteCandidate();
            break;
        case 'A':
            cout << "Please input the candidate id to add votes: ";
            getline(cin, inputID);
            addMultiVote(inputID);
            //writedatabase();
            break;
        case 'Q':
            exit(0);
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
    } else {
        return -1;
    }
}

void menu(bool Admin, int index) {
    if (Admin) {
        menuoptionsadmin(index);
    }
    else {
        menuOptionsVoter(index);
    }
}

void displayAllCandidates(){
    int number;
    cout << "-----------------------------------------------" << endl;
    cout << "List of Candidates" << endl;
    cout << setw(16) << left << "Number" << setw(16) << "Symbol" << setw(16) << left << "Name" << endl;
    for (int i = 1; i < candidatedatabase.size(); i++) {
            cout << left << setw(10) << candidatedatabase[i][0];
            cout << left << setw(16) << candidatedatabase[i][1];
            cout << left << setw(16) << candidatedatabase[i][2];
            cout << endl;
    }

    cout << "-----------------------------------------------" << endl;
    cout << endl;
    cout << "Enter the Candidate Number to view the vote count: " << endl;
    cin >> number;
    cin.ignore();
    for (int i = 1; i < candidatedatabase.size(); i++) {
        if (number == stoi(candidatedatabase[i][0]))
        {   
            cout << "----------------------------------------------------------" << endl;
            cout << setw(16) << left << "Number" << setw(16) << "Symbol" << setw(16) << left << "Name" << setw(16) << "Vote Count" << endl;
            cout << left << setw(16) << candidatedatabase[i][0];
            cout << left << setw(16) << candidatedatabase[i][1];
            cout << left << setw(16) << candidatedatabase[i][2];
            cout << left << setw(10) << candidatedatabase[i][5];
            cout << endl;
            cout << "----------------------------------------------------------" << endl;
        }
    }
}

void printCandidates(string suburb)
{
    cout << "-----------------------------------------------" << endl;
    cout << setw(16) << left << "Symbol" << setw(16) << "Name" << setw(16) << left << "Number" << endl;
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
    while (toupper(confirm) != 'Y')
    {
        cout << "Please confirm your vote (Y/N): ";
        cin >> confirm;
        confirm = toupper(confirm);
        if (toupper(confirm) == 'N') //TO_UPPER
        {
            cout << "Enter candidate number: ";
            cin >> vote;
            cin.ignore();
        }
        else
        {
            cout << "Invalid input" << endl;
        }
    }
    if (toupper(confirm) == 'Y')
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
        cout << "-----------------------------------------------" << endl;
        cout << "Vote confirmed" << endl;
        cout << "-----------------------------------------------" << endl;
    }
}

void addMultiVote(string CandID){
    int count;
    string buffer;
    int CandIndex = searchDB(CandID, candidatedatabase, 0);
    if (CandIndex == -1){
        cout << "Invalid Candidate ID" << endl;
        return;
    }
    char confirm = 'N';
    cout << "Please input the amount of votes to count for this candidate: ";
    cin >> count;
    for (int i = 0; i < count; i++)
    {
        string voteID;
        cout << "Please input the VoterID: ";
        getline(cin , buffer);
        getline(cin , voteID);
        int index = searchDB(voteID, voterdatabase, 0);
        if (index != -1){
            if (voterdatabase[index][5]== "true"){
                cout << endl << "This user have already cast their vote!" << endl;
            } else {
                cout << "Please confirm the vote for "<< voteID << " (Y/N): ";
                cin >> confirm;
                confirm = toupper(confirm);
                if (toupper(confirm) == 'N') //TO_UPPER
                {
                    continue;
                } else if (toupper(confirm) == 'Y'){
                    voterdatabase[index][5] = "true";
                    int CandCount = stoi(candidatedatabase[CandIndex][5]) + 1;
                    candidatedatabase[CandIndex][5] = to_string(CandCount);                   
                    cout << "-----------------------------------------------" << endl;
                    cout << "Vote confirmed" << endl;
                    cout << "-----------------------------------------------" << endl;
                } else {
                    cout << "Invalid Option chosen" << endl;
                }
            }
        } else {
            char conf = 'N';
            cout << "Error - Invalid VoterID" << endl;
            cout << "Would you like to redo the last input? (Y/N): ";
            cin >> conf;
            conf = toupper(conf);
            if (conf == 'Y'){
                i--;
            } else {
                break;
            }
        }
    }
    char save = 'N';
    cout << "Would you like to save your changes? (Y/N): ";
    cin >> save;
    save = toupper(save);
    if (save == 'Y'){
        writedatabase();
    } else {
        cout << "Not saving" << endl;
    }
}

void minVoteCandidate(){
    int count = 0;
    int minimum = stoi(candidatedatabase[1][5]);
    for (int i = 1; i < candidatedatabase.size(); i++) {
        if (stoi(candidatedatabase[i][5]) == 0){
            count++;
        }
        if (minimum > stoi(candidatedatabase[i][5]))
        {
            minimum = stoi(candidatedatabase[i][5]);
        }
    }
    cout << "-----------------------------------------------" << endl;
    if (count == candidatedatabase.size()-1){
        cout << "None of the candidates has been voted yet" << endl;
    }
    else{
        cout << "Candidate(s) with the least number of votes: \n" << endl;
        cout << setw(16) << left << "Symbol" << setw(16) << "Name" << setw(16) << left << "Number of Votes" << endl;
        for (int i = 1; i < candidatedatabase.size(); i++) {
            if (minimum == stoi(candidatedatabase[i][5]))
            {
                cout << left << setw(16) << candidatedatabase[i][1];
                cout << left << setw(16) << candidatedatabase[i][2];
                cout << left << setw(16) << candidatedatabase[i][5] << endl;
            }
        }
    }
    cout << "-----------------------------------------------" << endl;
    cout << endl;
}

void maxVoteCandidate(){
    int count = 0;
    int maximum = stoi(candidatedatabase[1][5]);
    for (int i = 1; i < candidatedatabase.size(); i++) {
        if (stoi(candidatedatabase[i][5]) == 0){
            count++;
        }
        if (maximum < stoi(candidatedatabase[i][5]))
        {
            maximum = stoi(candidatedatabase[i][5]);
        }
    }
    cout << "-----------------------------------------------" << endl;
    if (count == candidatedatabase.size()-1){
        cout << "None of the candidates has been voted yet" << endl;
    }
    else{
        cout << "Candidate(s) with the least number of votes: \n" << endl;
        cout << setw(16) << left << "Symbol" << setw(16) << "Name" << setw(16) << left << "Number of Votes" << endl;
        for (int i = 1; i < candidatedatabase.size(); i++) {
            if (maximum == stoi(candidatedatabase[i][5]))
            {
                cout << left << setw(16) << candidatedatabase[i][1];
                cout << left << setw(16) << candidatedatabase[i][2];
                cout << left << setw(16) << candidatedatabase[i][5] << endl;
            }
        }
    }
    cout << "-----------------------------------------------" << endl;
    cout << endl;
}
