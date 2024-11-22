# OSProject2GGurariy

The submission contains three files: bankersAlg.cpp that contains c++ source code that implements the Banker's Algorithm using data from the data.txt file, and the data.txt file that must be located in the execution directory. Data file must have the name data.txt. There is also a README file. 

data.txt must contain 4 tables in this order:
DIMENSION TABLE, AVAILABILITY TABLE, ALLOCATION TABLE, MAX TABLE.
There are no empty lines between tables.
Each table must contain one line of a string header (arbitrary description of the table).
Each table's data are organized as rows (seperate lines) and columns where values in each row are integers seperated by spaces.

DIMENSION TABLE contains one row with two columns and defines numbers of processes (n -- first number) and number of resource types (m -- seccond mumber).
AVAILABILITY TABLE contains one row with m columns and defines the data for the availability vector needed for Banker's Algorithm
ALLOCATION TABLE contains n rows with m columns and defines the data for the allocation matrix needed for Banker's Algorithm
MAX TABLE contains n rows with m columns and defines the data for the max matrix needed for Banker's Algorithm


SOURCE CODE EXPLANATION FOR bankersAlg.cpp
1. Reads the system's initial state from data.txt file.
2. Calculate the "Need" matrix
3. isSafeState() implements the Banker's Algorithm to determine if the system is in a safe state
4. Outputs a successful sequence of processes if the system is safe. Otherwise, we output that the system is unsafe.
(Please refer to the source code comments for more details)

In order to compile use:
g++ bankersAlg.cpp -pthread -lrt -o bankersAlg

To run use:
./bankersAlg