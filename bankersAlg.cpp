#include <iostream>
#include <vector>
#include <fstream>

int n = 0; //number of processes
int m = 0; //number of resource types

//declaration of state variables needed to implement Banker's Algorithm
//state data is initially stored in files
std::vector<int> available;
std::vector<std::vector<int>> max;
std::vector<std::vector<int>> allocation;
std::vector<std::vector<int>> need;

//vector that stores resulting successful sequence (if any)
std::vector<int> successfulSequence;

//name of file that stores the state data
const std::string FILENAME = "data.txt";

//forward declaration of function that initializes state variables from file
void initFromFile();

//forward declaration of function that examines if state is safe and populates the successfulSequence vector (if safe)
bool isSafeState();

int main() {
    //initialize state vectors from file 
    initFromFile();

    //call isSafeState(), if returns true print successful sequence
    if (isSafeState()){
        std::cout<< "■ The system is in a safe state since the sequence <";
        for (int i = 0; i < n; i++) {
            if (i > 0)
                std::cout << ", ";
            std::cout << "P" << successfulSequence[i];
        }
        std::cout << "> satisfies safety criteria" << std::endl;
    }
    else {
        std::cout << "system is not safe." << std::endl;
    }
}

void initFromFile() {
    //open file
    std::ifstream inputFile(FILENAME);

    //check for error
    if (!inputFile) {
        std::cerr << "error opening file";
        exit(1);
    }

    //number variable used to hold the int value from file (one at a time)
    int number;

    //due to my assumption that data file must contain header (comments) for each table, comment variable used to read and skip comment lines
    std::string comment;

    //read and skip comment line before reading values n (number of processes) and m (number of resource types)
    std::getline(inputFile, comment);
    inputFile >> n; //read number of processes from file
    inputFile >> m; //read numer of resource types from file

    max.resize(n,std::vector<int> (m));         //resize max matrix to accomodate m x n dimension
    allocation.resize(n,std::vector<int> (m));  //resize allocation matrix to accomodate m x n dimension
    need.resize(n,std::vector<int> (m));        //resize need matrix to accomodate m x n dimension

    //reading available vector (size m) from file 
    std::getline(inputFile, comment);   //read and skip comment line before reading data for available vector 
    std::getline(inputFile, comment);   //fixing current reading position
    for (int i = 0; i < m; i++) {
        inputFile >> number;
        available.push_back(number);
    } 


    //reading allocation matrix (n x m) from file
    std::getline(inputFile, comment); //read and skip comment line before reading data for allocation matrix
    std::getline(inputFile, comment); //fixing current reading position
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inputFile >> number;
            allocation[i][j] = number;
        }
    }

    //reading max matrix (n x m) from file
    std::getline(inputFile, comment); //read and skip comment line before reading data for need matrix
    std::getline(inputFile, comment); //fixing current reading position
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inputFile >> number;
            max[i][j] = number;
        }
    }

    //closing file
    inputFile.close();

    //calculating need matrix (n x m)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation [i][j];
        }
    }
}

bool isSafeState() {
    //declaring and initializing vectors for safe algorithm (work and finish)
    std::vector<int> work;      //size m (per resource type)
    std::vector<bool> finish;  //size n (per process)

    for (int i = 0; i < m; i++) 
        work.push_back(available[i]);

    for (int i = 0; i < n; i++)
        finish.push_back(false);

    //infinite loop while non-finished process in safe state is found
    while (true) {
        bool found = false; //initializing found false before looping through processes

        //loop through all prcesses
        for (int i = 0; i < n; i++) {
            if (!finish[i]) //skip if process already finished
            {
                //check if all resource types for given process are safe (work < need for each resource type)
                bool allResourcesSafe = true;   //assume that all resource types are safe
                for (int j = 0; j < m; j++) {   //loop through all resource types 
                   if (need[i][j] > work[j]){   //if at least one not safe resource type found, set allResourcesSafe to false; done with check
                       allResourcesSafe = false;
                       break;
                   }
                }

                //if all resource types for given process are safe: 
                if (allResourcesSafe) {
                    found = true; //indicate to while loop that safe process found 
                    //modify work vector according to algorithm 
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    
                    finish[i] = true; //indicate that given process is done
                    successfulSequence.push_back(i); //add the idx of this process to the successful sequence vector
                    break;
                }
            }  
        }

        //if nothing is found, exit the function returning true or false depending on finish vector
        if (!found)
        {
            //return false if at least one process is not finished 
            for (int i = 0; i < n; i++) {
                if (!finish[i])
                    return false;
            }
            //return true if all processes are finished
            return true;
        }
    }
}