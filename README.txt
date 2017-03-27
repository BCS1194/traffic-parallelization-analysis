-------------------------  Julia Information  -------------------------

To use the Julia code, first download the most recent release of Julia 
at http://julialang.org/downloads/ 

For Windows 10: 
  Extract the files to a directory of your choosing. Save the Julia project
  files (Traffic.jl and Simulator.jl) in the main Julia directory, and then 
  run the executable. This will open the Julia REPL. On that command line, 
  enter the following command:

    include("Simulator.jl")

  This is the equivalent of main() and will run the program.

For Linux:
  Extract the files to a directory of your choosing. Next, use the following:

    sudo apt install julia

  On Linux, the REPL can be accessed from the command line. Do this by typing
  the following command:

    julia

  This will open the Julia REPL. On that command line, enter the following:

    include("Simulator.jl")

  Make sure that both Traffic.jl and Simulator.jl are in the same directory 
  that you call the REPL from.

----------------------------  C Information  ---------------------------

Use the provided Makefile to compile road_test.c.
Run the program with "./test".