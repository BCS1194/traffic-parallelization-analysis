# Roads.jl
module Roads

  export Road, initRoads, nextRoad
 
  type Road
    startPosition::Int64
    destPosition::Int64
    travelCost::Int64
    carCount::Int64
    pathFull::Bool
  end

  function initRoads()
    println("Initializing Roads")
    test = [Road(1,2,0,0,false),  #Road 1  (1,2) Starting point
            Road(1,3,0,0,false),  #Road 2  (1,3) Starting point
            Road(2,4,0,0,false),  #Road 3  (2,4)
            Road(2,5,0,0,false),  #Road 4  (2,5)
            Road(3,5,0,0,false),  #Road 5  (3,5)
            Road(3,6,0,0,false),  #Road 6  (3,6)
            Road(2,7,0,0,false),  #Road 7  (2,7)
            Road(5,7,0,0,false),  #Road 8  (5,7)
            Road(5,8,0,0,false),  #Road 9  (5,8) Ending point
            Road(5,6,0,0,false),  #Road 10 (5,6)
            Road(6,8,0,0,false),  #Road 11 (6,8) Ending point
            Road(7,8,0,0,false)]  #Road 12 (7,8) Ending point
     
    return test
  end

  #function nextRoad(road)
  #  if 
end
