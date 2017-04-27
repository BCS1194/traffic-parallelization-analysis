# Traffic.jl
@everywhere module Traffic

  # "export" allows Simulator.jl to use these types and functions
  export Road, initRoads, initSharedMemory, traverse,
         generateTravelStats, printInfoMsg
 
  type Road
    roadNum      ::Int8
    origin       ::Int8  # 1 indicates the starting paths
    destination  ::Int8  # 6 indicates the ending paths  
  end

  type Car
    carNum        ::Int64 # Useful for tracking individual cars
    travelWeight  ::Int16 # Cars have a weight of 2, but this can be changed by the user
    currentRoad   ::Road
    roadCount     ::Int8  # This is used to count how many roads the car has been on

    # There are 9 roads because that is the longest potential path through the sim
    # These variables will represent the journey of each car
    road1         ::Int8
    road2         ::Int8
    road3         ::Int8
    road4         ::Int8
    road5         ::Int8
    road6         ::Int8
    road7         ::Int8
    road8         ::Int8
    road9         ::Int8
  end

# ------------------------------- Function Start --------------------------------- #
  # Initialize the road array, building the map on which cars will travel
  function initRoads()
    println("                                       --- Initializing Road Map ---\n")
    roads = [Road(1,1,2),   # Road 1  (1,2) Starting point
             Road(2,1,2),   # Road 2  (1,2) Starting point
             Road(3,1,2),   # Road 3  (1,2) Starting point
             Road(4,1,2),   # Road 4  (1,2) Starting point
             Road(5,1,2),   # Road 5  (1,2) Starting point
             Road(6,2,3),   # Road 6  (2,3)
             Road(7,2,3),   # Road 7  (2,3)
             Road(8,2,4),   # Road 8  (2,4)
             Road(9,2,2),   # Road 9  (2,2)
             Road(10,2,3),  # Road 10 (2,3)
             Road(11,2,3),  # Road 11 (2,3)
             Road(12,2,3),  # Road 12 (2,3)
             Road(13,3,5),  # Road 13 (3,5)
             Road(14,3,4),  # Road 14 (3,4)
             Road(15,3,4),  # Road 15 (3,4)
             Road(16,3,5),  # Road 16 (3,5)
             Road(17,3,4),  # Road 17 (3,4)
             Road(18,4,5),  # Road 18 (4,5)
             Road(19,4,4),  # Road 19 (4,4)
             Road(20,4,5),  # Road 20 (4,5)
             Road(21,4,5),  # Road 21 (4,5)
             Road(22,4,5),  # Road 22 (4,5)
             Road(23,4,5),  # Road 23 (4,5)
             Road(24,4,4),  # Road 24 (4,4)
             Road(25,4,5),  # Road 25 (4,5)
             Road(26,4,5),  # Road 26 (4,5)
             Road(27,5,6),  # Road 27 (5,6) Ending point
             Road(28,5,5),  # Road 28 (5,5)
             Road(29,5,6),  # Road 29 (5,6) Ending point
             Road(30,5,5),  # Road 30 (5,5)
             Road(31,5,6),  # Road 31 (5,6) Ending point
             Road(32,5,5),  # Road 32 (5,5)
             Road(33,5,6),  # Road 33 (5,6) Ending point
             Road(34,5,5),  # Road 34 (5,5)
             Road(35,5,6)]  # Road 35 (5,6) Ending point
    return roads
  end # End of initRoads

# ------------------------------- Function Start --------------------------------- #
  # Initialize the car, start it out on the road with less travel cost
  function initCar(roads, costs, visits)
    # Pick the starting road
    start = getCheapestRoad([roads[1],roads[2],roads[3],roads[4],roads[5]], costs)
    
    # Initialize a new Car object
    car = Car(rand(-10000000:10000000),2,start,1,start.roadNum,0,0,0,0,0,0,0,0)

    # Update shared memory
    costs[start.roadNum] += 2
    visits[start.roadNum] += 1  

    return car    
  end # End of initCar

# ------------------------------- Function Start --------------------------------- #
  # Initialize costs, visits, and the index
  function initSharedMemory(costs, visits, index)
    # costs[] contains the travel cost for each road, while visits[] tracks how
    # many times a given road has been travelled on
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

    # index[] is used to later on to generate travel statistics
    index[1] = 1
  end # End of initSharedMemory

# ------------------------------- Function Start --------------------------------- #
  # Moves the car to the next road and updates relevant shared memory
  function nextRoad(car, roads, costs, visits, travels, index)

    # Decrement the travel cost of the current road as the car is about to switch roads
    costs[car.currentRoad.roadNum] -= car.travelWeight

    # To understand what is happening in this next block, we have included in our 
    # deliverable a map for reference. Basically, the car will pick its next road
    # based on which road it is currently on and which of its next options (if there 
    # is more than one) has the lowest travel cost. 
 
    # Julia would greatly benefit from adding a C style switch statement
    if car.currentRoad.roadNum     == 1
      car.currentRoad = roads[6]
    elseif car.currentRoad.roadNum == 2
      car.currentRoad = getCheapestRoad([roads[7],roads[8],roads[9]], costs)
    elseif car.currentRoad.roadNum == 3
      car.currentRoad = roads[10]
    elseif car.currentRoad.roadNum == 4
      car.currentRoad = roads[11]
    elseif car.currentRoad.roadNum == 5
      car.currentRoad = roads[12]
    elseif car.currentRoad.roadNum == 6
      car.currentRoad = getCheapestRoad([roads[13],roads[14]], costs)
    elseif car.currentRoad.roadNum == 7
      car.currentRoad = getCheapestRoad([roads[13],roads[14]], costs)
    elseif car.currentRoad.roadNum == 8
      car.currentRoad = getCheapestRoad([roads[19],roads[20],roads[21],roads[22]], costs)
    elseif car.currentRoad.roadNum == 9
      car.currentRoad = roads[10]
    elseif car.currentRoad.roadNum == 10
      car.currentRoad = getCheapestRoad([roads[15],roads[16],roads[17]], costs)
    elseif car.currentRoad.roadNum == 11
      car.currentRoad = getCheapestRoad([roads[15],roads[16],roads[17]], costs)
    elseif car.currentRoad.roadNum == 12
      car.currentRoad = getCheapestRoad([roads[15],roads[16],roads[17]], costs)
    elseif car.currentRoad.roadNum == 13
      car.currentRoad = getCheapestRoad([roads[27],roads[28]], costs)
    elseif car.currentRoad.roadNum == 14
      car.currentRoad = roads[18]
    elseif car.currentRoad.roadNum == 15
      car.currentRoad = getCheapestRoad([roads[23],roads[24]], costs)
    elseif car.currentRoad.roadNum == 16
      car.currentRoad = getCheapestRoad([roads[32],roads[33]], costs)
    elseif car.currentRoad.roadNum == 17
      car.currentRoad = getCheapestRoad([roads[25],roads[26]], costs)
    elseif car.currentRoad.roadNum == 18
      car.currentRoad = getCheapestRoad([roads[29],roads[30]], costs)
    elseif car.currentRoad.roadNum == 19
      car.currentRoad = roads[18]
    elseif car.currentRoad.roadNum == 20
      car.currentRoad = getCheapestRoad([roads[27],roads[28]], costs)
    elseif car.currentRoad.roadNum == 21
      car.currentRoad = roads[31]
    elseif car.currentRoad.roadNum == 22
      car.currentRoad = getCheapestRoad([roads[32],roads[33]], costs)
    elseif car.currentRoad.roadNum == 23
      car.currentRoad = roads[31]
    elseif car.currentRoad.roadNum == 24
      car.currentRoad = getCheapestRoad([roads[25],roads[26]], costs)
    elseif car.currentRoad.roadNum == 25
      car.currentRoad = getCheapestRoad([roads[32],roads[33]], costs)
    elseif car.currentRoad.roadNum == 26
      car.currentRoad = getCheapestRoad([roads[34],roads[35]], costs)
    elseif car.currentRoad.roadNum == 28
      car.currentRoad = getCheapestRoad([roads[29],roads[30]], costs)
    elseif car.currentRoad.roadNum == 30
      car.currentRoad = roads[31]
    elseif car.currentRoad.roadNum == 32
      car.currentRoad = roads[31]
    elseif car.currentRoad.roadNum == 34
      car.currentRoad = getCheapestRoad([roads[32],roads[33]], costs)
    end
 
    # Increment the cars road count and update its journey variables
    car.roadCount += 1
    updateTravels(car)

    # Update shared memory to account for the road chosen
    costs[car.currentRoad.roadNum]  += car.travelWeight
    visits[car.currentRoad.roadNum] += 1
 
    # This will be triggered when the car is on its final road
    if car.currentRoad.destination == 6 
      # Decrement the last road and log the journey in shared memory     
      costs[car.currentRoad.roadNum] -= car.travelWeight
      logJourney(travels, index, car)
    end
  end # End of nextRoad

# ------------------------------- Function Start --------------------------------- #
  # Return the cheapest road of a given list
  function getCheapestRoad(roads, costs)

    lowest = costs[roads[1].roadNum]
    cheapestRoad = roads[1] 

    # Standard sorting algorithm that returns the lowest integer
    for r in roads
      if costs[r.roadNum] < lowest
        lowest = costs[r.roadNum]
        cheapestRoad = r
      end
    end
    return cheapestRoad  
  end # End of getCheapestRoad

# ------------------------------- Function Start --------------------------------- #
  # Helper function for tracking the journey of each car
  function updateTravels(car)
    # Update the car's relevant journey variables with the current road
    if car.roadCount == 2
      car.road2 = car.currentRoad.roadNum
    elseif car.roadCount == 3
      car.road3 = car.currentRoad.roadNum
    elseif car.roadCount == 4
      car.road4 = car.currentRoad.roadNum
    elseif car.roadCount == 5
      car.road5 = car.currentRoad.roadNum
    elseif car.roadCount == 6
      car.road6 = car.currentRoad.roadNum
    elseif car.roadCount == 7
      car.road7 = car.currentRoad.roadNum
    elseif car.roadCount == 8
      car.road8 = car.currentRoad.roadNum
    elseif car.roadCount == 9
      car.road9 = car.currentRoad.roadNum
    end
  end # End of updateTravels

# ------------------------------- Function Start --------------------------------- #
  # Document a car's journey
  function logJourney(travels, index, car)
    # Add the path of the car to the shared travel array
    travels[index[1]]     = car.road1
    travels[index[1] + 1] = car.road2
    travels[index[1] + 2] = car.road3
    travels[index[1] + 3] = car.road4
    travels[index[1] + 4] = car.road5
    travels[index[1] + 5] = car.road6
    travels[index[1] + 6] = car.road7
    travels[index[1] + 7] = car.road8
    travels[index[1] + 8] = car.road9

    # Increment the index by 9 for the next car
    index[1] += 9
  end # End of logJourney

# ------------------------------- Function Start --------------------------------- #
  # Generate a car and run it through the road map
  function traverse(roads, costs, visits, travels, index)
    # Generate a car
    car = initCar(roads, costs, visits)

    # nextRoad is called until the car is on its last road
    while car.currentRoad.destination != 6
      nextRoad(car, roads, costs, visits, travels, index)
    end
  end # End of traverse

# ------------------------------- Function Start --------------------------------- #
  # Calculates the most popular paths taken during the simulation
  function generateTravelStats(travels,cars)
    println("                                        --- Simulation Complete ---\n")
    
    # Routes will store every route taken, as well as how many times it was taken
    routes = zeros(Int64, (100,11))
    index = 1

    # For every car, add its path to routes
    for c in 1:cars
      # Initialize an array that contains each car's journey variable
      path = [travels[index],
              travels[index + 1],
              travels[index + 2],
              travels[index + 3],
              travels[index + 4],
              travels[index + 5],
              travels[index + 6],
              travels[index + 7],
              travels[index + 8]]
      addRoute(path, routes)
      index += 9
    end   

    # Print out the statistics
    println("                                --- Top 10 (Or Less) Most Popular Routes ---\n")
    printStats(routes, cars)
    
  end # End of generateTravelStatistics

# ------------------------------- Function Start --------------------------------- #
  function addRoute(path, routes)
    # Catch bad runs, which result from a rarely occurring bug
    if path[1] == 0
      return 0
    end

    # Iterate through the current log
    for row in 1:100
      # If the row is all 0's, it can be overwritten with the current path
      if routes[row, 1] == 0
        routes[row, 1], routes[row, 2], routes[row, 3] = path[1], path[2], path[3]
        routes[row, 4], routes[row, 5], routes[row, 6] = path[4], path[5], path[6]
        routes[row, 7], routes[row, 8], routes[row, 9] = path[7], path[8], path[9]

        # Increment counter for the first time and generate special tag
        routes[row, 10] += 1
        routes[row, 11] = rand(-9223372036854775808:9223372036854775807)
        break

      # If the row has the same information as the path, increment its 10th element, the counter  
      elseif routes[row, 1] == path[1] && routes[row, 2] == path[2] && routes[row, 3] == path[3] &&
             routes[row, 4] == path[4] && routes[row, 5] == path[5] && routes[row, 6] == path[6] &&
             routes[row, 7] == path[7] && routes[row, 8] == path[8] && routes[row, 9] == path[9]
        routes[row, 10] += 1
        break
      end 
    end
    
  end # End of new route

# ------------------------------- Function Start --------------------------------- #
  function printStats(routes, cars)
    visited = zeros(Int64, (100,2))

    # Get each visit count 
    for i in 1:100
      visited[i, 1] = routes[i, 10] # Counter
      visited[i, 2] = routes[i, 11] # Randomized tag
    end

    # Sort the list in reverse, getting the most popular routes at the top
    visited = sortrows(visited, by=x->(x[1]), rev=true)

    # Sorry Dr. Lam for this heinous for loop, basically it prints the most popular
    # routes as well as the percentage of cars that took them
    for i in 1:10
      if routes[i, 1] == 0
        continue
      end
      print(" #$(i) Path: ")
      for j in 1:100
        if visited[i, 2] == routes[j, 11]
          print("Road $(routes[j,1]) ")
          for k in 2:9
            if routes[j, k] != 0
              print("--> Road $(routes[j, k]) ")
            end
          end
          print("\n This route was taken by $(routes[j, 10]) of $(cars) ")
          println("cars. ($(100 * (convert(Float32, routes[j, 10]) / convert(Float32, cars)))%)")
          if i != 10
            print("--------------------------------------------------------")
            println("-------------------------------------------------------")
          end   
        end
      end
    end # End of for loop  
   
  end # End of printStats

# ------------------------------- Function Start --------------------------------- #
  # Prints out information about using the traffic simulator
  function printInfoMsg()
    println("\n   Welcome to our Julia Multi-Processing Traffic Simulation!\n")
    println("   This program runs cars through a map of 35 interconnected roads, demonstrating")
    println("   how parallel computing can be harnessed to model real-world congestion.\n")
    println("   Our implementation uses a function called simulate, which takes an integer as its parameter.")
    println("   Example, to run 100000 cars, type the following:    simulate(100000)")
    println("   To see this information again, input the following: printInfoMsg()")
  end # End of printInfoMsg

end # End of Traffic module!

