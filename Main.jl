# Main.jl
include("Roads.jl")
include("Cars.jl")

using Roads, Cars

roads = initRoads()
car = initCar()
println("$(car.travelWeight) is the travel weight and Road 12 ends at $(roads[12].destPosition)")
