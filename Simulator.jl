# Simulator.jl
include("Traffic.jl")

# Import the Traffic module
using Traffic

function simulate(cars)
  # These are shared arrays for the travel costs and visit count of each road
  costs    = SharedArray(Int32, 35)
  visits   = SharedArray(Int32, 35)
  travels  = SharedArray(Int8, (cars * 9))
  index    = SharedArray(Int64, 1)

  # Initialize shared arrays with their starting values
  initSharedMemory(costs, visits, index) 

  # Sets up the road array that the cars will traverse
  roads = initRoads()

  # Signal to user that the sim has started
  println("                                        --- Starting Simulation ---\n")

  # Use parallel framework to run multiple cars at once through a shared road 
  @sync @parallel for w in workers()
    for i in 1:cars/(nprocs()-1)
      remotecall(traverse, w, roads, costs, visits, travels, index)
    end  
  end

  # Rudimentary waiting functionality to ensure that workers are finished
  sleep(1)

  # Output route statistics to the user
  generateTravelStats(travels, cars)
end

# Print the information message to the user
printInfoMsg() 







