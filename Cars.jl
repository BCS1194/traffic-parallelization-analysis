# Cars.jl
module Cars

  export Car, initCar
 
  type Car
    startPosition::Int64
    destPosition::Int64
    travelWeight::Int64
  end

  function initCar()
    println("Initializing car")
    test = Car(1,2,4)
  end
end

