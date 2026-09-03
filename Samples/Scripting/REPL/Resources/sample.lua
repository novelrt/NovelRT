speaker "narrator"
speaker "character" {
  pose = "happy",
  poses = {
    happy = { sprite = "happy.png" },
    angry = { sprite = "angry.png" },
    angry_left = { sprite = "angry.png", position = { -100, 0 } },
    sad = { sprite = "sad.png", scale = { 1, 1 } },
    sad_flip = { sprite = "sad.png", scale = { -1, 1 } }
  }
}

local shock = cue.sfx { sound = "shock.ogg" }
local awe = cue.sfx { sound = "awe.ogg" }
local shockAndAwe = cue.compound { shock, awe }

local makeSad = cue.compound{
  shockAndAwe,
  -- TODO: this doesn't actually validate anything yet. It probably should...
  cue.pose { character = "character", pose = "sad" }
}

while true do
  narrator
    "This is the first dialog piece."
    "This is the second."

  local chosen = choice "This is a choice" { "Option 1", "Option 2" }
  if chosen == 1 then
    awe()
    narrator "You chose the first option."
  else
    shock()
    narrator "You chose the second option."
    break
  end
end

character "Wowee!"
makeSad()
character "I'm sad now."
character "Why would you make me angry?!"
