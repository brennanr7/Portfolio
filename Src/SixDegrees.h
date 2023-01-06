/*
 * SixDegrees.h
 *
 * COMP 15 Project 2: Six Degrees of Collaboration front end public and
 *                    private functions to run the program
 *
 * by [Brennan Rivera], [4/15/21]
 */

#ifndef SIX_DEGREES_H
#define SIX_DEGREES_H

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Artist.h"
#include "CollabGraph.h"

using namespace std;

class SixDegrees
{

public:
  //populate graph
  SixDegrees();
  ~SixDegrees();
  void populate(string filename);

  void runSixDegrees(istream &data, ostream &output);
  //bfs
  void bfs(string p1, string p2, ostream &output);
  //bfs algorithm
  void do_bfs(Artist a1, Artist a2, ostream &output);
  //dfs
  void dfs(string s1, string s2, ostream &output);
  //dfs algorithm
  void do_dfs(Artist a1, Artist a2, ostream &output);
  //print path
  void print_path(stack<Artist> path, Artist a1, Artist a2, ostream &output);
  //not
  void not_command(istream &data, ostream &output);
  //verification
  bool verify_vertex(vector<Artist> v, Artist a1, Artist a2, ostream &output);
  //command file
  void commandFile(string file, ostream &output);

private:
  CollabGraph graph;
  struct Art {
    Artist person;
    vector<string> collaboration;
    bool seen;
  };
  vector<Art> r;

  vector<Artist> name;//vector of excluded artists
};

#endif
