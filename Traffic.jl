# Traffic.jl
module Traffic

  export Road, Car, initRoads, initCar, nextRoad, traverse
 
  type Road
    roadNum      ::Int64
    startPosition::Int64  # At present, start/destPosition are for mapping purposes
    destPosition ::Int64
    travelCost   ::Int64
    carCount     ::Int64 # Irrelevent in current serial version
    pathFull     ::Bool  # See above ^
  end

  type Car
    carNum      ::Int64
    travelWeight::Int64
    currentRoad ::Road
  end

  # Initialize road array, this array will be shared memory in the parallel version
  function initRoads()
    println("Initializing Roads")
    roads = [Road(1,1,2,2,0,false),   # Road 1  (1,2) Starting point
             Road(2,1,3,3,0,false),   # Road 2  (1,3) Starting point
             Road(3,2,4,4,0,false),   # Road 3  (2,4)
             Road(4,2,7,7,0,false),   # Road 4  (2,7)
             Road(5,2,5,5,0,false),   # Road 5  (2,5)
             Road(6,3,5,3,0,false),   # Road 6  (3,5)
             Road(7,3,6,4,0,false),   # Road 7  (3,6)
             Road(8,4,7,4,0,false),   # Road 8  (4,7)
             Road(9,5,7,3,0,false),   # Road 9  (5,7) 
             Road(10,5,8,4,0,false),  # Road 10 (5,8) Ending point
             Road(11,6,8,6,0,false),  # Road 11 (6,8) Ending point
             Road(12,7,8,2,0,false)]  # Road 12 (7,8) Ending point     
    return roads
  end

  # Initialize the car, start it out on the road with less travel cost
  function initCar(roads)
    if roads[1].travelCost <= roads[2].travelCost
      start = roads[1]
    else
      start = roads[2]
    end

    car = Car(rand(1:100),2,start)
    start.travelCost += 2  
    println("Initializing Car $(car.carNum) on Road $(start.roadNum) with weight $(start.travelCost)\n")
    return car    
  end

  # Moves the car to the next road and updates old and new roads' travel cost
  function nextRoad(car, roads)
    println("Car $(car.carNum) leaving Road $(car.currentRoad.roadNum)")
    car.currentRoad.travelCost -= car.travelWeight
    println("Road $(car.currentRoad.roadNum) weight is back to $(car.currentRoad.travelCost)")

    if car.currentRoad.roadNum == 1
      car.currentRoad = getShortestRoad([roads[3],roads[4],roads[5]])
    elseif car.currentRoad.roadNum == 2
      car.currentRoad = getShortestRoad([roads[6],roads[7]])
    elseif car.currentRoad.roadNum == 3
      car.currentRoad = roads[8]
    elseif car.currentRoad.roadNum == 4
      car.currentRoad = roads[12]
    elseif car.currentRoad.roadNum == 5
      car.currentRoad = getShortestRoad([roads[9],roads[10]])
    elseif car.currentRoad.roadNum == 6
      car.currentRoad = getShortestRoad([roads[9],roads[10]])
    elseif car.currentRoad.roadNum == 7
      car.currentRoad = roads[11]
    elseif car.currentRoad.roadNum == 8
      car.currentRoad = roads[12]
    elseif car.currentRoad.roadNum == 9
      car.currentRoad = roads[12]
    end
    
    println("Car $(car.carNum) now on Road $(car.currentRoad.roadNum)") 
    car.currentRoad.travelCost += car.travelWeight
    println("Road $(car.currentRoad.roadNum) weight is now $(car.currentRoad.travelCost)\n")
    if car.currentRoad.roadNum == 10 || 
       car.currentRoad.roadNum == 11 ||
       car.currentRoad.roadNum == 12
      
      car.currentRoad.travelCost -= car.travelWeight
      print("Car $(car.carNum) has arrived at the destination! Road $(car.currentRoad.roadNum)")
      println(" now has a weight of $(car.currentRoad.travelCost).\n")
    end
  end

  # Return the shortest road of a given list
  function getShortestRoad(roads)
    lowest = roads[1].travelCost
    shortestRoad = roads[1] 
    for r in roads
      if r.travelCost < lowest
        lowest = r.travelCost
        shortestRoad = r
      end
    end
    return shortestRoad  
  end

  function traverse(roads)
    car = initCar(roads)
    while car.currentRoad.roadNum != 10 && 
          car.currentRoad.roadNum != 11 &&
          car.currentRoad.roadNum != 12
    nextRoad(car,roads)
    end
  end

    
end

