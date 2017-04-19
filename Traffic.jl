# Traffic.jl
@everywhere module Traffic

  export Road, Car, initRoads, initCar, nextRoad, traverse
 
  type Road
    roadNum      ::Int8
    origin       ::Int8  # 1 indicates the starting paths
    destination  ::Int8  # 6 indicates the ending paths
  
    carCount     ::Int64
    pathFull     ::Bool  #
  end

  type Car
    carNum      ::Int64
    travelWeight::Int16
    currentRoad ::Road
  end

  # Initialize the road array, building the map on which cars will travel
  function initRoads()
    println("Initializing Roads")
    roads = [Road(1,1,2,0,false),   # Road 1  (1,2) Starting point
             Road(2,1,2,0,false),   # Road 2  (1,2) Starting point
             Road(3,1,2,0,false),   # Road 3  (1,2) Starting point
             Road(4,1,2,0,false),   # Road 4  (1,2) Starting point
             Road(5,1,2,0,false),   # Road 5  (1,2) Starting point
             Road(6,2,3,0,false),   # Road 6  (2,3) 
             Road(7,2,3,0,false),   # Road 7  (2,3)
             Road(8,2,4,0,false),   # Road 8  (2,4)
             Road(9,2,2,0,false),   # Road 9  (2,2)
             Road(10,2,3,0,false),  # Road 10 (2,3)
             Road(11,2,3,0,false),  # Road 11 (2,3)
             Road(12,2,3,0,false),  # Road 12 (2,3)
             Road(13,3,5,0,false),  # Road 13 (3,5)
             Road(14,3,4,0,false),  # Road 14 (3,4)
             Road(15,3,4,0,false),  # Road 15 (3,4)
             Road(16,3,5,0,false),  # Road 16 (3,5)
             Road(17,3,4,0,false),  # Road 17 (3,4)
             Road(18,4,5,0,false),  # Road 18 (4,5)
             Road(19,4,4,0,false),  # Road 19 (4,4)
             Road(20,4,5,0,false),  # Road 20 (4,5)
             Road(21,4,5,0,false),  # Road 21 (4,5)
             Road(22,4,5,0,false),  # Road 22 (4,5)
             Road(23,4,5,0,false),  # Road 23 (4,5)
             Road(24,4,4,0,false),  # Road 24 (4,4)
             Road(25,4,5,0,false),  # Road 25 (4,5)
             Road(26,4,5,0,false),  # Road 26 (4,5)
             Road(27,5,6,0,false),  # Road 27 (5,6) Ending point
             Road(28,5,5,0,false),  # Road 28 (5,5)
             Road(29,5,6,0,false),  # Road 29 (5,6) Ending point
             Road(30,5,5,0,false),  # Road 30 (5,5)
             Road(31,5,6,0,false),  # Road 31 (5,6) Ending point
             Road(32,5,5,0,false),  # Road 32 (5,5)
             Road(33,5,6,0,false),  # Road 33 (5,6) Ending point
             Road(34,5,5,0,false),  # Road 34 (5,5)
             Road(35,5,6,0,false)]  # Road 35 (5,6) Ending point
    return roads
  end

  # Initialize the car, start it out on the road with less travel cost
  function initCar(roads, costs, visits)
    start = getShortestRoad([roads[1],roads[2],roads[3],roads[4],roads[5]], costs)

    car = Car(rand(1:1000),2,start)
    costs[start.roadNum] += 2
    visits[start.roadNum] += 1  
    #println("Initializing Car $(car.carNum) on Road $(start.roadNum) with weight $(costs[start.roadNum])\n")
    return car    
  end

  # Moves the car to the next road and updates old and new roads' travel cost
  function nextRoad(car, roads, costs, visits)
    costs[car.currentRoad.roadNum] -= car.travelWeight

    # Julia would greatly benefit from adding switch statement functionality
    if car.currentRoad.roadNum     == 1
      car.currentRoad = roads[6]
    elseif car.currentRoad.roadNum == 2
      car.currentRoad = getShortestRoad([roads[7],roads[8],roads[9]], costs)
    elseif car.currentRoad.roadNum == 3
      car.currentRoad = roads[10]
    elseif car.currentRoad.roadNum == 4
      car.currentRoad = roads[11]
    elseif car.currentRoad.roadNum == 5
      car.currentRoad = roads[12]
    elseif car.currentRoad.roadNum == 6
      car.currentRoad = getShortestRoad([roads[13],roads[14]], costs)
    elseif car.currentRoad.roadNum == 7
      car.currentRoad = getShortestRoad([roads[13],roads[14]], costs)
    elseif car.currentRoad.roadNum == 8
      car.currentRoad = getShortestRoad([roads[19],roads[20],roads[21],roads[22]], costs)
    elseif car.currentRoad.roadNum == 9
      car.currentRoad = roads[10]
    elseif car.currentRoad.roadNum == 10
      car.currentRoad = getShortestRoad([roads[15],roads[16],roads[17]], costs)
    elseif car.currentRoad.roadNum == 11
      car.currentRoad = getShortestRoad([roads[15],roads[16],roads[17]], costs)
    elseif car.currentRoad.roadNum == 12
      car.currentRoad = getShortestRoad([roads[15],roads[16],roads[17]], costs)
    elseif car.currentRoad.roadNum == 13
      car.currentRoad = getShortestRoad([roads[27],roads[28]], costs)
    elseif car.currentRoad.roadNum == 14
      car.currentRoad = roads[18]
    elseif car.currentRoad.roadNum == 15
      car.currentRoad = getShortestRoad([roads[23],roads[24]], costs)
    elseif car.currentRoad.roadNum == 16
      car.currentRoad = getShortestRoad([roads[32],roads[33]], costs)
    elseif car.currentRoad.roadNum == 17
      car.currentRoad = getShortestRoad([roads[25],roads[26]], costs)
    elseif car.currentRoad.roadNum == 18
      car.currentRoad = getShortestRoad([roads[29],roads[30]], costs)
    elseif car.currentRoad.roadNum == 19
      car.currentRoad = roads[18]
    elseif car.currentRoad.roadNum == 20
      car.currentRoad = getShortestRoad([roads[27],roads[28]], costs)
    elseif car.currentRoad.roadNum == 21
      car.currentRoad = roads[31]
    elseif car.currentRoad.roadNum == 22
      car.currentRoad = getShortestRoad([roads[32],roads[33]], costs)
    elseif car.currentRoad.roadNum == 23
      car.currentRoad = roads[31]
    elseif car.currentRoad.roadNum == 24
      car.currentRoad = getShortestRoad([roads[26],roads[26]], costs)
    elseif car.currentRoad.roadNum == 25
      car.currentRoad = getShortestRoad([roads[32],roads[33]], costs)
    elseif car.currentRoad.roadNum == 26
      car.currentRoad = getShortestRoad([roads[34],roads[35]], costs)
    elseif car.currentRoad.roadNum == 28
      car.currentRoad = getShortestRoad([roads[29],roads[30]], costs)
    elseif car.currentRoad.roadNum == 30
      car.currentRoad = roads[31]
    elseif car.currentRoad.roadNum == 32
      car.currentRoad = roads[31]
    elseif car.currentRoad.roadNum == 34
      car.currentRoad = getShortestRoad([roads[32],roads[33]], costs)
    end
 
    costs[car.currentRoad.roadNum]  += car.travelWeight
    visits[car.currentRoad.roadNum] += 1
 
    if car.currentRoad.destination == 6      
      costs[car.currentRoad.roadNum] -= car.travelWeight
      #println("Car $(car.carNum) has arrived at the destination! Road $(car.currentRoad.roadNum) now has a weight of $(costs[car.currentRoad.roadNum]).\n")
    end
  end

  # Return the shortest road of a given list
  function getShortestRoad(roads, costs)
    lowest = costs[roads[1].roadNum]
    shortestRoad = roads[1] 
    for r in roads
      if costs[r.roadNum] < lowest
        lowest = costs[r.roadNum]
        shortestRoad = r
      end
    end
    return shortestRoad  
  end

  function traverse(roads, costs, visits)
    car = initCar(roads, costs, visits)
    while car.currentRoad.destination != 6
      nextRoad(car, roads, costs, visits)
    end
  end

    
end

