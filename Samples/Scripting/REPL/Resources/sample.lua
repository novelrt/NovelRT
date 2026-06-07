speaker "narrator"
speaker "character" {
  pose = "happy",
  poses = {
    happy = { sprite = "happy.png" },
    angry = { sprite = "angry.png" },
    sad = { sprite = "sad.png" }
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
