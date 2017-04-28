# Simulator.jl
include("Traffic.jl")
Pkg.add("PlotRecipes")

# Import the Traffic module
using Traffic
using PlotRecipes




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

# Display a visual representation of the map
    sups = Int64[]

    n = length(sups)
    nodes, source, destiny, weights = copy(sups), collect(1:n-1), collect(2:n), Int64[]

    function connect!(src, dest, wgt)
        push!(source, src)
        push!(destiny, dest)
        push!(weights, wgt)
    end

    push!(nodes, 1)
    push!(nodes, 2)
    push!(nodes, 3)
    push!(nodes, 4)
    push!(nodes, 5)
    push!(nodes, 6)

    connect!(1, 2, 4)
    connect!(1, 3, 3)
    connect!(1, 4, 2)
    connect!(1, 5, 3)
    connect!(1, 6, 4)

    push!(nodes, 7)
    connect!(2, 7, 2)

    connect!(3, 7, 3)
    connect!(3, 4, 2)

    push!(nodes, 8)
    connect!(4, 8, 3)
    connect!(5, 8, 2)
    connect!(6, 8, 3)

    push!(nodes, 9)
    connect!(7, 9, 3)

    push!(nodes, 10)
    connect!(3, 10, 5)
    connect!(10, 9, 2)

    push!(nodes, 11)
    connect!(8, 11, 3)

    push!(nodes, 12)
    connect!(8, 12, 4)
    connect!(11, 12, 3)

    push!(nodes, 13)
    connect!(7, 13, 4)
    connect!(10, 13, 3)

    push!(nodes, 14)
    connect!(9, 14, 3)
    connect!(13, 14, 2)

    push!(nodes, 15)
    connect!(10, 15, 3)
    connect!(11, 15, 3)
    connect!(14, 15, 2)

    push!(nodes, 16)
    connect!(10, 16, 5)
    connect!(8, 16, 4)
    connect!(12, 16, 2)
    connect!(16, 15, 2)

    push!(nodes, 17)
    connect!(12, 17, 3)
    connect!(17, 16, 3)

    push!(nodes, 18)
    connect!(13, 18, 6)
    connect!(14, 18, 3)
    connect!(15, 18, 2)
    connect!(16, 18, 4)
    connect!(17, 18, 5)



    names = map(string, nodes)


    graphplot(source, destiny, weights,
        names = names, #=method = :tree,=# root = :bottom,
        l = (weights[2], cgrad()),  # apply the default color gradient to the line (line_z values taken from edge weights)
        m = [node==Integer ? :orange : :steelblue for node in nodes]     # node colors
    )







