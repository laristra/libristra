foo = 4

bar = {1, 2, 3}

function sum(a, b)
    return a+b
end

function split(a, b)
    return a,b
end

mytable = {}
mytable[3] = "hi"
mytable["there"] = 4.5
function mytable.func()
    return 6;
end

function ics(x,y,z,t)
  print(x,y,z,t)
  if z < 0 then
    return 1.0, {0,0,0}, 1.0
  else
    return 0.125, {0,0,0}, 0.1
  end
end
