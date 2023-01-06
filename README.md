* This project handles a running train to accomodate passengers arriving/departing a metro. I Learned how to design and modularize code and work with documented libraries.

Compile/run:
     - Compile using
            make MetroSim
     - run executable with
            ./MetroSim stationsFile passFile [commands]

* Files:

main.cpp:
     Main.cpp is the base of the simulation. It allows the user to run the
     command line using a command file and an output file. Furthermore, main
     is connected to all the other files listed.

MetroSim.cpp:
     MetroSim.cpp allows the user to run the simulation. MetroSim stores
     passengers vectors of queues. MetroSim also stores stations in vectors
     of structs. MetroSim allows the user to enqueue a passenger at a specific
     train station with their destination. MetroSim also allows the user to
     move the train, enqueue passengers to the train, and dequeue passengers to
     their spcific destination which is printed to their outputed file.
     MetroSim also prints the state of the simulation to the screen. Lastly,
     MetroSim allows the user to run a command file .

MetroSim.h:
        MetroSim.h is the interface of MetroSim. MetroSim.h has a public and
        private class. Importance of the private class is the train is a
        vector of PassengerQueues and the staion data is a vector of structs.

stations.txt:
        an example file containing a list of stations.

test_commands.txt:
        sample list of commands that you could give to the simulator

the_metroSim:
        reference implementation for students to see how to run the program

Passenger.h:
        Passenger.h is the interface of the passenger.cpp file. This file
        constructs a passenger.

Passenger.cpp:
        Passenger.cpp includes a print function that allows creates the
        passenger in the format given in the spec.

PassengerQueue.h:
        PassengerQueue.h is the interface for PassengerQueue.cpp. This file
        Contains public functions that create a "Passenger queue". The private
        section of the file contatins a vector of passengers for the queue.

PassengerQueue.cpp:
        PassengerQueue.cpp holds functions that create a queue in a vector.
        PassengerQueue.cpp also contatins a print function that converses
        with the Passenger files in order to print the passengers on the
        queue.
Note:  the program should handle all cases.

Data Structures:
        -The Data Structures used to create the functionality of this homework
         were vectors and queues. Vectors were very useful in creating the
         functionality of this assignment because I was able to store
         passenger queues at different index's in the vector. Also, using a
         vector helped organize the contents of the queue's based on
         destination. Vector's are dynamic, so when creating a vector of
         queues, it was easy to access different elements in the vector and
         edit the size of the vector. Queue's were especially useful in this
         assignment because I needed to create a linear list of passengers in
         order of FIFO. This data structure allowed me to enqueue passengers
         to their specific destination, enqueue passengers to a specific
         station, and dequeue passengers as they either leave the train or
         leave a station. When we want to model people in a line, it useful
         to use this type of data structure. Overall, by using these two
         data structures together, we can easily access elements, add to the
         queue, and dequeue the queue.

* Testing:

Here describe the following: process of testing (unit tests), mention
of bugs you encountered while testing, mention of testing on inputs of
different sizes and edge cases, good description of base cases you
considered while testing. Demonstrate a methodical approach to
testing.  This section of your REAMDE should be very thorough for
homework assignments.

First, I needed to implement the queue in PassengerQueue.cpp. I individually
tested each function as I created it through unit_test. In unit_test, I needed
to create passengers by communicating with the Passenger.h file and then pass
them through my functions I created as arguments. I specifically did this type
of testing when enqueing, dequeuing and printing the queued passengers to
ensure their functionality. Furthermore, I asserted different sizes of the
PassengerQueue.cpp to ensure the functionality. Some bugs I ran into and fixed
in PassengerQueue.cpp was accessing the front of the queue (the problem was my
syntax was not correct). After I completed this first part of the assignment,
I then moved on to implementing main.cpp and MetroSim.cpp. To test both of
these files, I needed to a little bit of code and test it by either calling the
function and printing out the contents of an element to ensure functionality,
or run through cin in the command line. Starting with main.cpp, I need to
pass in files, so by testing that a file was successfully passed in, I needed
to implement a function in MetroSim that would open the file and read in the
data. To ensure that this worked and that I had successful conversations
between main.cpp and MetroSim.cpp, I printed out each element that was read
in in the function. This was then deleted. Next, now that I knew I had
successfully read in the data, I needed to create a print function that would
print the state of the simulation out to the terminal. Once I had completed
implementing my print function, I would call it in main.cpp in order to
ensure functionality then delete it. Since I knew these functions worked
correctly, I needed to implement and test my size function. To do this, I
printed out the size of the vector of stations after the data was read in then
later deleted it. Once I knew these functions were working correctly, I then
could implement the base of program which was to read in commands from the user.
I used the io-refrence to help me implement this function. This function was
called "runMetroSim". I first worked on query "p" which allowed the user to
enqueue a passenger to a specific station with an id and a departure station.
I created a function that would do this for me and I would call this function
in runMetroSim if the user imputed "p arrival departure". To test that I was
properly taking in commands in, the p query, I printed hello world then
deleted it after testing was finished. Now that I was successfully reading
in commands, I implemted my p query. To test that this was working successfully,
I could see that in the terminal, because runMetroSim calls my print function
that displays the state of simulation to the screen, the passenger that I
wanted to enqueue at a specific station was infact there. Some bugs that I ran
into when implementing this function was syntax errors. Now that this first
query was done, I could then implement the move metro query that would move
the train, enqueue passengers in order of departure, and dequeue passengers.
I first needed to declare a variable that would keep track of the train
and I initialized it to 0 in the constructor. In order to test that is was
initialized, I printed the value in my function, "query_mm". I then needed
to enqueue passengers from the station to the train. I ensured that this worked
through the print function that I implemented. A bug that I ran into was
syntax errors and the index's of the passengers on the train. I fixed this by
substracting 1 from the passengers index. I then needed to dequeue my
passengers from the train when they reached their departing station. This
was tested by printing in the print function. A bug that I ran into was
syntax errors. When passengers left the train, I also needed to make sure that
I was printing to the correct output file, so to test this I ran the program
and checked the contents of the file to ensure functionality. I then needed
to make sure if the train was at the last station, we would then go to the
first station. I tested this by enqueing a passenger at station 2 which
had departure 1, and used the "m m" command to ensure functionality. Now that
these two queries were implemented, I created my last query that would exit the
program (command "m f"). This was tested in the command line. I lastly needed
to implement a function that would take commands from a file. This was done
and tested by ensuring we were reading the contents of the file correctly, then
diffing against the program. To ensure the edge case of not being able to
open a file for all the functions that needed to read in a file, I had to
input a faulty file that would then print the proper error message.
