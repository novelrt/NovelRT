local env = { }

function env.speaker(name)
  env[name] = function(msg)
    coroutine.yield({
      type = "text",
      speaker = name,
      text = msg
    })

    return env[name]
  end
end

function env.choice(prompt)
  return function(options)
    return coroutine.yield({
      type = "branch",
      prompt = prompt,
      options = options
    })
  end
end

local manager = { }

function manager:load(loc)
    local f = assert(loadfile(loc, "bt", env))
    local tree = { }

    local resume do
      resume = function(c, ...)
        local _, r = assert(coroutine.resume(c, ...))

        if not r then
          --coroutine.close(c)
          return
        end

        if r.type == "text" then
          function r:continue()
            return resume(c)
          end
        elseif r.type == "branch" then
          function r:continue(choice)
            return resume(c, choice)
          end
        end

        return r
      end
    end

    function tree:begin()
        local c = coroutine.create(f)
        return resume(c)
    end

    return tree
end

local tree = manager:load("prototype_script.lua")
local state = tree:begin()
while true do
  if not state then break end
  if state.type == "text" then
    io.write(state.speaker, ": ", state.text)
    io.read()
    state = state:continue()
  elseif state.type == "branch" then
    io.write(state.prompt, ":\n")
    for i = 1, #state.options do
      io.write(i, ". ", state.options[i], "\n")
    end
    io.write("Choice: ")
    local choice = io.read("*n", "*l")
    state = state:continue(choice)
  end
end
