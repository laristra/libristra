hydro = {
  -- The case prefix and postfixes
  prefix = "mock_box_2d",
  postfix = "dat",
  -- The frequency of outputs
  output_freq = "7",
  -- The time stepping parameters
  final_time = 0.2,
  max_steps = 1e6,
  CFL = 1./2.,
  -- the mesh
  mesh = {
    type = "box",
    dimensions = {10, 10},
    xmin = {-0.5, -0.5},
    xmax = { 0.5,  0.5}
  },
  -- the equation of state
  eos = {
    type = "ideal_gas",
    gas_constant = 1.4,
    specific_heat = 1.0
  },
  -- the initial conditions
  -- return density, velocity, pressure
  ics = function (x,y,t)
    if x < 0 and y < 0 then
      return 0.125, {0,0}, 0.1
    else
      return 1.0, {0,0}, 1.0
    end
  end
}
