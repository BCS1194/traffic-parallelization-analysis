-------------------------  Julia Information  -------------------------

To use the Julia code, first download the most recent release of Julia 
at http://julialang.org/downloads/ 

For Windows 10: 
  Extract the files to a directory of your choosing. Save the Julia project
  files (Traffic.jl and Simulator.jl) in the main Julia directory, and then 
  run the executable. This will open the Julia REPL. On that command line, 
  enter the following command:
  
    addprocs(1)
    include("Simulator.jl")

  This is the equivalent of main() and will run the program.

For Linux:
  Extract the files to a directory of your choosing. Next, use the following:

    sudo apt install julia

  On Linux, the REPL can be accessed from the command line. Do this by typing
  the following command:

    julia -p 2

  This will open the Julia REPL with two processes. To add more processes, simply
  change the number. IMPORTANT: Due to parallel commands used, "-p" must be at least 2!
  Inside the REPL, enter the following:

    include("Simulator.jl")

  This will print out an information message about the program. To run the program,
  enter the following command in the REPL: simulate(X) 
  with X being the number of cars that you want to have run through the simulator. 
  A good starting point is 100,000. At orders of magnitude in the >=10,000,000 range,
  the program will usually become unresponsive. 
  
  Make sure that both Traffic.jl and Simulator.jl are in the same directory 
  that you call the REPL from.
  
  ---
  
  To run the Julia version with visuals, enter the following instead of include("Simulator.jl"):
  
    include("Simulator_Visual.jl")
    
  This version requires a package that will be downloaded when running for the first
  time. This requires some additional disk space.

----------------------------  C Information  ---------------------------

Use the provided Makefile to compile road_test.c.
Run the program with "./test".
