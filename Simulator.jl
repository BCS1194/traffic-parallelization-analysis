# Simulator.jl
include("Traffic.jl")

using Traffic

# Parallel computing code -- working on this
#roads = @async initRoads()

#for w in workers()
#  remotecall(w, traverse, roads)
#end

#@parallel for w in workers()
#  traverse(roads)
#end

# Sets up the road array that the cars will traverse
roads = initRoads()

# Runs a singular instance of a car traversing the road array
traverse(roads)

