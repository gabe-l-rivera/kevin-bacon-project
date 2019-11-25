/*
* Gabe Rivera
* Edit: 11/24/2019
* Kevin Bacon Project
* University of Kentucky
* CS216
*/
#include <iostream>    //need for a lot
#include <sstream>    //need for splitFirst
#include <fstream>    //need for reading data
#include <string>    //need for a lot
#include <vector>    //need for vectors
#include "Graph.h"    //need for cpp file
#include "Matrix.h"    //need for cpp file
#include <stdio.h> //need for atoi
#include <stdlib.h> //need for atoi
using namespace std; //makes it easier to code

int splitFirst(string aline, string & first, string & rest) {
    first = rest = "";                // init results to empty string
    if (aline == "") return 0;        // if nothing to split, we're done
    string next;                    // next word in aline
    istringstream iss(aline);        // converts aline into a input string stream
    iss >> first;                   // extract the first word, if any
    iss >> rest;                    // extract the second word, if any
    if (rest == "") return 1;       // if the second word is empty, only 1 word in aline
    iss >> next;                    // extract the third word, if any
    while (iss && next != "") {     // while there are more words in the stream
        rest = rest + " " + next;   //       stick it on the end of rest
        iss >> next;                //       get the next word, if any
    }
    return 2;                       // aline was split into two parts.
} // splitFirst()

int main(int argc, char** argv) {
    //DECLARATIONS
    vector<int> actorID;    //stores the ID of the actor from an actors file
    vector<int> movieID;    //stores the ID of the movie from the movies file
    vector<int> relationMovieID;    //stores the ID of the movie in parallel with actor ID from relation text file
    vector<int> relationActorID;    //stores the ID of the actor in parallel with movie ID from relation text file
    vector<string> actorName;    //stores a name as a string in parallel with the actors ID from an actors file.
    vector<string> movieTitle;    //stores a name as a string in parallel with the movies ID from a movies file.
    //int i = 0; //debugging variable
    string aline, first, second; //for splitFirst function
    int iFirst, iSecond;    //integer values of what is stored from the string after calling getline.
    //READ FILES
    const int ARG = 4;    //amount of arguments the user should enter if they want to read their own files
    const char * fileA = "actorsTest.txt";        //initially set the file to be a default file
    const char * fileB = "moviesTest.txt";        //initially set the file to be a default file
    const char * fileC = "movie-actorTest.txt";    //initially set the file to be a default file
    if (argc != ARG) {                            //if the arguments are not equal to the const int ARG, then
        cout << "Usage: " << argv[0] << " <filename> x 3" << endl;    //show that they did not use correct usage
        cout << "Using default files" << endl;                        //state that default files are being used
        cout << "KEVIN BACON PROGRAM" << endl;
        cout << "Loading default files..." << endl;
    }
    else {
        fileA = argv[1];    //set the fileA to be the first text file the user entered
        fileB = argv[2];    //set the fileB to be the second text file the user entered
        fileC = argv[3];    //set the fileC to be the third text file the uesr entered
        cout << "KEVIN BACON PROGRAM" << endl;
        cout << "Please be patient." << endl;
        cout << "Loading files..." << endl;
    }
    ifstream aTest;    //make an object for ifstream to open
    aTest.open(fileA);    //open fileA
    while (getline(aTest, aline)) {     //used for splitFirst, extracts a line out of text file
        splitFirst(aline, first, second);    //code I used from CS215 project 3
        iFirst = atoi(first.c_str());    //converts to integer
        actorID.push_back(iFirst);    //add data to vector
        actorName.push_back(second);    //add data to vector
        //cout << "Actor ID: " << actorID[i] << ", is " << actorName[i] << endl; //debugging to check stored data
        //i++;
    }
    //i = 0; debugger to check data
    aTest.close();    //Close file 1
    //cout << endl;    //debugging formatter
    ifstream movTest;    //make an object for ifstream to open
    movTest.open(fileB);    //open fileB
    while (getline(movTest, aline)) {
        splitFirst(aline, first, second);    //code I used from CS215 project 3
        iFirst = atoi(first.c_str());    //converts to integer
        movieID.push_back(iFirst);    //add data to vector
        movieTitle.push_back(second);    //add data to vector
        //cout << "Movie ID: " << movieID[i] << ", is " << movieTitle[i] << endl; //debugging to check stored data
        //i++;
    }
    //i = 0; debugger to check data
    movTest.close(); //Close file 2
    //cout << endl;    //debugging formatter
    ifstream mat;    //make an object for ifstream to open
    mat.open(fileC);    //open fileC
    while (getline(mat, aline)) {
        splitFirst(aline, first, second);    //code I used from CS215 project 3
        iFirst = atoi(first.c_str());    //converts to integer
        iSecond = atoi(second.c_str());    //converts to integer
        relationMovieID.push_back(iFirst);    //add data to vector
        relationActorID.push_back(iSecond);    //add data to vector
        //cout << "Movie ID: " << relationMovieID[i] << ", has actor: " << relationActorID[i] << endl; //debugging to check stored data
        //i++;
    }
    //i = 0; debugger to check data
    mat.close();    //close file 3
    //Making the graph
    Graph Fullgraph(actorID.size());    //Graph is as big as how many actors there are.
    //cout << actorID.size(); //debugging statement
    int a1, a2;    //temporary values used to store information for addEdge.
    for (int i = 0; i < relationActorID.size(); i++) {    //nested for loop to make comparison checks
        for (int j = i+1; j < relationActorID.size(); j++) {    //...j only needs to start below i each time and prevents double cases.
            if (relationMovieID[i] == relationMovieID[j]) {    //if two lines are the same movie...
                if (relationActorID[i] != relationActorID[j]){    //and if two actors are not the same person
                    for (int k = 0; k < actorID.size(); k++) {    //find the actors index
                        if (relationActorID[i] == actorID[k])
                            a1 = k;    //stores index in temporary variable
                    }
                    for (int l = 0; l < actorID.size(); l++) {    //find the 2nd actors index
                        if (relationActorID[j] == actorID[l]) {
                            a2 = l;    //stores index in temporary variable
                        }
                    }
                    if (Fullgraph.hasEdge(a1, a2) == false) {    //check to see if there is already an edge
                        Fullgraph.addEdge(a1, a2, relationMovieID[i]);    //add edge between two actors.
                    }
                }
            }
        }
    }
    /*debugging code That shows all the edges relations
    cout << endl << endl;
    for (int i = 0; i < actorID.size(); i++) {
        for (int j = i; j < actorID.size(); j++) {
            if (i != j) {
                if (Fullgraph.hasEdge(i,j) == true) {
                    cout << "Connection of " << i << ", " << j << ": " << Fullgraph.getEdge(i,j) << endl;
                }
            }
        }
    }
    */
    //PROGRAM
    //declare variables
    bool found_name = false;    //sentinal value
    int baconsource, inputNumber, tempGetEdgeVal, intMovName, savedj;
    string checkinput, inputName;
    for (int m = 0; m < actorName.size(); m++) {    //Find Kevin Bacon and store the baconsource as his index.
        if (actorName[m] == "Kevin Bacon") {
            baconsource = m;    //stores "Kevin Bacon"'s index number as variable "baconsource"
        }
    }
    vector<int> distance(actorID.size(), -1);    //declare distance vector
    vector<int> go_through(actorID.size(), -1);    //declare go_through vector
    Fullgraph.BFS(baconsource, distance, go_through);    //perform Breadth-First-Search on given baconsource with our distance and go through vectors
    
    //This code block is meant to find all of the actors with the highest distance away from baconsource
    //declare variables
    int biggest = 0;
    int biggestID;
    int amtOfPeoplewithFarthest = 0;
    vector<string> people;
    //for loop to find the biggest distance away from baconsource
    for (int i = 0; i < actorID.size(); i++) {
        if (biggest < distance[i]) {
            biggest = distance[i];
            biggestID = i;
        }
    }
    //using the biggest distance found, compare if actor has that distance and store their name in to an array.
    for (int i = 0; i < actorID.size(); i++) {
        if (distance[i] == biggest) {
            people.push_back(actorName[i]);
            amtOfPeoplewithFarthest++;
        }
    }
    //display the actors if there are actors to display.
    if (people.size() != 0) {
        cout << "Consider searching these people!" << endl;
        for (int i = 0; i < amtOfPeoplewithFarthest; i++) {
            cout << "Highest distance away(" << biggest << "): " << people[i] << endl;
        }
        cout << "------------------------------------------------------------------------------------" << endl;
    }

    //Cout statements
    cout << "************************************************************************************" << endl;
    cout << "The Bacon number of an actor is the number of degrees of separation he/she has from Bacon." <<endl << "Those actors who have worked directly with Kevin Bacon in a movie have a Bacon number of 1." << endl;
    cout << "This application helps you find the Bacon number of an actor." << endl << "Enter \"exit\" to quit the program." << endl;
    cout << "Please enter an actor's name (case-sensitive): ";
    getline(cin, checkinput);
    cout << endl;
    cout << "************************************************************************************" << endl;
    cout << endl;

    while (true) {    //always ask for actor names until a break command give from "exit" or "Exit"
        for (int i = 0; i < actorName.size(); i++) {    //Check to see if input given is equivalent to name on actorID list
            if (checkinput == actorName[i]) {
                inputName = actorName[i];
                inputNumber = i;
                found_name = true;
            }
        }
        if (found_name == false) {    //if the name is not found, then possible that user wants to leave program or typed invalid name.
            if (checkinput == "exit" || checkinput == "Exit")    //checks to see if user wants to leave
                break;
            else {                                                //otherwise they entered wrong name.
                cout << "Invalid input, please try again..." << endl << endl;
            }
        }
        else if (distance[inputNumber] == -1) {
            cout << actorName[inputNumber] << " does not have a relationship to " << actorName[baconsource] << endl << endl;
        }
        else {
            if (baconsource != inputNumber) {  //prevents displaying the -1 distance from the source to itself
                cout << "The Kevin Bacon number of " << actorName[inputNumber] << " is: " << distance[inputNumber] << "." << endl;    //formatting the cout
                if (distance[inputNumber] != 1) {
                    savedj = inputNumber;
                    for (int j = inputNumber ; go_through[j] != baconsource; j = go_through[j]) { //the for loop sets the variable to whatever the result of the go_through[j] is in order to loop for any amount of length the path is.
                        tempGetEdgeVal = Fullgraph.getEdge(j, go_through[j]);    //for finding the name of the movie
                        for (int p = 0; p < movieID.size(); p++) {    //the associated movie
                            if (movieID[p] == tempGetEdgeVal) {    //comparing ID found from getEdge to movieID
                                intMovName = p;    //stores index in temporary variable
                            }
                        }
                        cout << actorName[j] << " appeared in " << movieTitle[intMovName] << " with " << actorName[go_through[j]] << endl;    //cout statement <actor> apeared in <movie> with <actor>
                        savedj = j;
                    }
                    tempGetEdgeVal = Fullgraph.getEdge(go_through[savedj], go_through[go_through[savedj]]);
                    for (int p = 0; p < movieID.size(); p++) {    //the associated movie
                        if (movieID[p] == tempGetEdgeVal) {
                            intMovName = p;    //stores index in temporary variable
                        }
                    }
                    //last connection is always actorID[baconsource]
                    cout << actorName[go_through[savedj]] << " appeared in " << movieTitle[intMovName] << " with " << actorName[baconsource] << endl << endl;    //cout statement <actor> apeared in <movie> with <actor>
                }
                else {        //otherwise the path of 1 is:
                        tempGetEdgeVal = Fullgraph.getEdge(inputNumber, baconsource);
                        for (int p = 0; p < movieID.size(); p++) {    //the associated movie
                            if (movieID[p] == tempGetEdgeVal) {
                                intMovName = p;    //stores index in temporary variable
                            }
                        }
                        cout << actorName[inputNumber] << " appeared in ";
                        cout << movieTitle[intMovName] << " with " << actorName[baconsource] << endl;
                        cout << endl;
                }
            }
            else {
                cout << actorName[baconsource] << " has a distance of 0 from themself" << endl << endl;
            }
        }
        //repeat: ask for actor name from user.
        cout << "************************************************************************************" << endl;
        cout << "The Bacon number of an actor is the number of degrees of separation he/she has from Bacon." <<endl << "Those actors who have worked directly with Kevin Bacon in a movie have a Bacon number of 1." << endl;
        cout << "This application helps you find the Bacon number of an actor." << endl << "Enter \"exit\" to quit the program." << endl;
        cout << "Please enter an actor's name (case-sensitive): ";
        getline(cin, checkinput);
        cout << endl;
        cout << "************************************************************************************" << endl;
        cout << endl;
        found_name = false;
    }
    return 0;
}

