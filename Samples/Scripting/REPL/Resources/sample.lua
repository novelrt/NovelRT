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

while true do
  narrator
    "This is the first dialog piece."
    "This is the second."

  local chosen = choice "This is a choice" { "Option 1", "Option 2" }
  if chosen == 1 then
    narrator "You chose the first option."
  else
    narrator "You chose the second option."
    break
  end
end

character "Wowee!"
character:pose "sad"
character "I'm sad now."
character:pose "angry"
character "Why would you make me angry?!"
