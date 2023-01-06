/*
 * SixDegrees.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration that holds the programs
 *                    commands and traversals. The data structure used to
 *                    implement this program was a graph.
 *
 * by [Brennan Rivera], [4/15/21]
 */

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <exception>
#include <fstream>


#include "Artist.h"
#include "CollabGraph.h"
#include "SixDegrees.h"

using namespace std;

/* default constructor
  *
  *
*/
SixDegrees::SixDegrees()
{

}

/* deconstructor
  *
  *
*/
SixDegrees::~SixDegrees()
{

}

/* populate
  *
  * Purpose: to populate the graph from a data file
  * Parameters: the filename passed in
  * Returns: none
*/
void SixDegrees::populate(string filename)
{
    ifstream input;
    string line;
    input.open(filename);
    if (input.fail()){
      cerr << "Error: could not open file " << filename << endl;
      exit(EXIT_FAILURE); //error statement if could not open file
    }

    while (getline(input, line)) {
      Art my_artist;
      my_artist.person.set_name(line);//set artist
      getline(input, line);
      while (line != "*") {
        my_artist.person.add_song(line);
        my_artist.collaboration.push_back(line);
        getline(input, line);//get song
      }
        r.push_back(my_artist);
        //insert vertex in the graph
        graph.insert_vertex(my_artist.person);
    }
    //iterate through vector
    for (int i = 0; i < (int)r.size(); i++) {
        for (int j = 0; j < (int)r.size(); j++) {
          if (r.at(i).person == r.at(j).person) {
            continue;
          }

          string song = r.at(i).person.get_collaboration(r.at(j).person);
          if (song == "") {
            continue;
          }
          graph.insert_edge(r.at(i).person, r.at(j).person, song);
        }
    }
    input.close();
}

/* runSixDegrees
  *
  * Purpose: to run the SixDegrees program by taking in commands from
  *          cin or a command file
  * Parameters: the istream data
  * Returns: none
*/
void SixDegrees::runSixDegrees(istream &data, ostream &output)
{
    string command;
    string s1;
    string s2;


    while(getline(data, command) and command != "q") {
      //query loop that takes in commands from the command line
      if (command == "bfs") {
        getline(data, s1);
        getline(data, s2);
        bfs(s1, s2, output);
      }
      else if (command == "dfs") {
        getline(data, s1);
        getline(data, s2);
        dfs(s1, s2, output);
      }
      else if (command == "not") {
        not_command(data, output);
      }
      else if (command == "quit") {
        exit(EXIT_SUCCESS);
      }
      else {
            output << command << " is not a command. Please try again.";
            output << endl;
          }
    }
}

/* bfs
  *
  * Purpose: The purpose of this function is to initially take in the
  *          artists and check if they are valid
  * Parameters: The two artists and the output stream
  * Returns: none
*/
void SixDegrees::bfs(string p1, string p2, ostream &output)
{
    Artist a1;//create artists to check if valid
    Artist a2;
    a1.set_name(p1);
    a2.set_name(p2);
    //check if artists were valid
    if (not graph.is_vertex(a1)) {
      if (not graph.is_vertex(a2)) {
        output << '"' << a1.get_name() << '"' <<
        " was not found in the dataset :(" << endl;
        output << '"' << a2.get_name() << '"' <<
        " was not found in the dataset :(" << endl;
        return;
      }
      output << '"' << a1.get_name() << '"' << " was not found in the dataset :("
      << endl;
      return;
    }
    if (not graph.is_vertex(a2)) {
      output << '"' << a2.get_name() << '"' << " was not found in the dataset :("
      << endl;
      return;
    }

    do_bfs(a1, a2, output);//perform bfs

}

/*do_bfs
  *
  * Purpose: To perform the bfs algorithm
  * Parameters: The two artists and the output stream
  * Returns: none
*/
void SixDegrees::do_bfs(Artist a1, Artist a2, ostream &output)
{
    //create queue for the artst vertex
    queue<Artist> q;
    q.push(a1);

    while (not q.empty()) {
      Artist next = q.front();
      q.pop();
      graph.mark_vertex(next);
      //set the predecessor of the path
      vector<Artist> r = graph.get_vertex_neighbors(next);
      //iterate through neighbor vector
      for(int i = 0; i < (int)r.size(); i++) {
        if(graph.is_marked(r.at(i))) {
          continue;
        }
        graph.mark_vertex(r.at(i));
        graph.set_predecessor(r.at(i), next);
        q.push(r.at(i));
      }
    }
    stack<Artist> a = graph.report_path(a1, a2);//report path, print, clear
    print_path(a, a1, a2, output);
    graph.clear_metadata();
}

/* dfs
  *
  * Purpose: to breadth first search the graph and find two connecting
  *          artists
  * Parameters: two strings as the names of artists
  * Returns: none
*/
void SixDegrees::dfs(string s1, string s2, ostream &output)
{
    Artist a1;//create artists to check if valid
    Artist a2;
    a1.set_name(s1);
    a2.set_name(s2);
    //ensure valid artists
    if (not graph.is_vertex(a1)) {
      if (not graph.is_vertex(a2)) {
        output << '"' << a1.get_name() << '"' <<
        " was not found in the dataset :(" << endl;
        output << '"' << a2.get_name() << '"' <<
        " was not found in the dataset :(" << endl;
        return;
      }
      output << '"' << a1.get_name() << '"' << " was not found in the dataset :("
      << endl;
      return;
    }
    if (not graph.is_vertex(a2)) {
      output << '"' << a2.get_name() << '"' << " was not found in the dataset :("
      << endl;
      return;
    }
    do_dfs(a1, a2, output);//perform dfs recursively
    stack<Artist> a = graph.report_path(a1, a2);
    print_path(a, a1, a2, output);
    graph.clear_metadata();
}

/* do_dfs
  *
  * Purpose: To perfrom the dfs algorithm
  * Parameters: The two artists and the output stream
  * Returns: none
*/
void SixDegrees::do_dfs(Artist a1, Artist a2, ostream &output)
{
    stack<Artist> s;//use stack
    s.push(a1);

    while (not s.empty()) {
      Artist next = s.top();
      s.pop();
      graph.mark_vertex(next);
      vector<Artist> r = graph.get_vertex_neighbors(next);
      //iterate through neighbor vector
      for(int i = 0; i < (int)r.size(); i++) {
        if(!graph.is_marked(r.at(i))) {
          graph.set_predecessor(r.at(i), next);
          do_dfs(r.at(i), a2, output);
        }
        if(graph.is_marked(r.at(i))) {//if seen continue
          continue;
        }
      }
    }
}

/* not
  *
  * Purpose: to perform an exclusive search on artists that a list of
  *          of artists
  * Parameters: the istream data and output stream
  * Returns: none
*/
void SixDegrees::not_command(istream &data, ostream &output)
{
    string p1;
    getline(data, p1);//get both artists from command line
    string p2;
    getline(data, p2);

    Artist a1;//set artists
    Artist a2;
    a1.set_name(p1);
    a2.set_name(p2);
    //get list of excluded artists
    string command;
    while(getline(data, command) and command != "*") {
      Artist a;
      a.set_name(command);
      name.push_back(a);
    }
    //verify and mark as seen all excluded artists
    if(!verify_vertex(name, a1, a2, output)) {
      name.clear();
      return;
    }
    name.clear();//clear excluded artist vector
    do_bfs(a1, a2, output);
}

/* verify_vertex
  *
  * Purpose: To verify if a given artist is in the graph for not command
  * Parameters: the vector of artists, two source and destination artists,
  *             the ostream output
  * Returns: a boolean true if artists are valid, false if not
*/
bool SixDegrees::verify_vertex(vector<Artist> v, Artist a1, Artist a2, ostream
                               &output)
{
  bool verify = true;
  //check initial artists
  if (not graph.is_vertex(a1)) {
    output << '"' << a1.get_name() << '"' << " was not found in the dataset :("
    << endl;
    verify = false;
  }
  if (not graph.is_vertex(a2)) {
    output << '"' << a2.get_name() << '"' << " was not found in the dataset :("
    << endl;
    verify = false;
  }
  //iterate through excluded list
  for(int i = 0; i < (int)v.size(); i++) {
    if(not graph.is_vertex(v.at(i))) {
      output << '"' << v.at(i).get_name() << '"' <<
      " was not found in the dataset :(" << endl;
      verify = false;
      continue;
    }
    graph.mark_vertex(v.at(i));//mark vertex as seen
  }
  v.clear();
  return verify;
}

/* print_path
  *
  * Purpose: to print the path of an artist
  * Parameters: a stack of artists representing the path of one artist to
  *             another
  * Returns: none
*/
void SixDegrees::print_path(stack<Artist> path, Artist a1, Artist a2, ostream
                            &output)
{
    if(path.empty()) {//no path exists if stack is empty
      output << "A path does not exist between " << '"';
      output << a1.get_name() << '"' << " and " << '"' << a2.get_name();
      output << '"' << "." << endl;
      return;
    }
    while (path.size() != 1)//go through stack and print artists
    {
        a1 = path.top();
        output << '"' << a1.get_name() << '"' << " collaborated with ";
        path.pop();
        a2 = path.top();
        string song = a1.get_collaboration(a2);
        output << '"' << a2.get_name() << '"' << " in " << '"' << song << '"';
        output << ".";
        output << endl;
    }
    output << "***" << endl;
}
/* commandFile
  *
  * Purpose: To open a command file given
  * Parameters: the file and output file
  * Returns: none
*/
void SixDegrees::commandFile(string file, ostream &output)
{
    ifstream filename;

    filename.open(file);//open file

    if(not filename.is_open()) {//if file not valid
      cerr << file << " cannot be opened." << endl;
      exit(EXIT_FAILURE);
    }
    runSixDegrees(filename, output);//pass the file to runSixDegrees
    filename.close();
}
