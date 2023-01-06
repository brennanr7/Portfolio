* Program Purpose:

The purpose of this program is to interactively accept queries in the form of
an input command and the names of artists. It will then output a path to get
from the first artist to the second via musical collaberation.

* Compile/run:
To run the program simply type ./SixDegrees with a given artists txt file,
a command file, and an output file.

* Files:

               CollabGraph.cpp: The back end implementation of the graph. This
               file is able to create the create, access different artists,
               and access collaberations of artists.

               CollabGraph.h: The front end of the graph. This file holds
               different public and private functions of the graph.

               SixDegrees.cpp: This file reads in a data file and runs the
               program.

               SixDegrees.h: This file holds different private and public
               functions that run the SixDegrees program.

               main.cpp: The main file initially takes in commands from the
               command line and links together other files.
               
               
Data Structures: The data structure used to implement this program was a
                 graph. I used vectors also help me with the graph. Graph's
                 are useful in a number of ways. They can be used for social
                 networks like Facebook or Instagram as well as Google Maps.
                 Graphs are a non-linear data structure that hold edges and
                 vertices. Graphs can be weighted as well. Algorithms used
                 in this program consisted of a bfs and dfs. These runtime
                 complexities are the same being O(V+E) where V is the
                 number of vertices and E is the number of edges in the
                 graph.
