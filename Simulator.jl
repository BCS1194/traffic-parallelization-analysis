# Simulator.jl
include("Traffic.jl")

using Traffic

function run()
  # These are shared arrays for the travel costs and visit count of each road
  costs  = SharedArray(Int32, 35)
  visits = SharedArray(Int32, 35)
  #paths  = SharedArray(Int32, )

  # Initialize shared arrays with starting values, these will change frequently
  # constantly during execution 
  costs[1],  visits[1]  = 4, 0
  costs[2],  visits[2]  = 3, 0
  costs[3],  visits[3]  = 2, 0
  costs[4],  visits[4]  = 3, 0
  costs[5],  visits[5]  = 4, 0
  costs[6],  visits[6]  = 2, 0
  costs[7],  visits[7]  = 3, 0
  costs[8],  visits[8]  = 5, 0
  costs[9],  visits[9]  = 2, 0
  costs[10], visits[10] = 3, 0
  costs[11], visits[11] = 2, 0
  costs[12], visits[12] = 3, 0
  costs[13], visits[13] = 4, 0
  costs[14], visits[14] = 3, 0
  costs[15], visits[15] = 3, 0
  costs[16], visits[16] = 4, 0
  costs[17], visits[17] = 3, 0
  costs[18], visits[18] = 3, 0
  costs[19], visits[19] = 2, 0
  costs[20], visits[20] = 5, 0
  costs[21], visits[21] = 3, 0
  costs[22], visits[22] = 5, 0
  costs[23], visits[23] = 4, 0
  costs[24], visits[24] = 2, 0
  costs[25], visits[25] = 3, 0
  costs[26], visits[26] = 3, 0
  costs[27], visits[27] = 6, 0
  costs[28], visits[28] = 2, 0
  costs[29], visits[29] = 3, 0
  costs[30], visits[30] = 2, 0
  costs[31], visits[31] = 2, 0
  costs[32], visits[32] = 3, 0
  costs[33], visits[33] = 4, 0
  costs[34], visits[34] = 2, 0
  costs[35], visits[35] = 5, 0

  # Sets up the road array that the cars will traverse
  roads = initRoads()

  # Use parallel framework to run multiple cars at once through a shared road 
  @sync @parallel for w in workers()
    for i in 1:10000/(nprocs()-1)
      remotecall(traverse, w, roads, costs, visits)
    end  
  end

  # Rudimentary waiting functionality to ensure that workers are finished
  sleep(1)

  # Print out visit counts by Path Order
  @sync for i in 1:35
    println("    Visits to Road $(i): $(visits[i])")
  end
end

run()











