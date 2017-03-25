# Simulator.jl
include("Traffic.jl")

using Traffic

roads = initRoads()
car = initCar(roads)

println("The car starts on Road $(car.currentRoad.roadNum) with weight $(car.currentRoad.travelCost)\n")

while car.currentRoad.roadNum != 10 && 
      car.currentRoad.roadNum != 11 &&
      car.currentRoad.roadNum != 12
  nextRoad(car,roads)
end

println("")
