local narrator = speaker "narrator" { }
local novelchan = speaker "Novel-chan" {
  pose = 'default',
  poses = {
    default = {
      sprite = "Images/novel-chan.png",
      position = { 0, 0 },
      scale = { 1, 1 }
    },
    startled = {
      sprite = "Images/novel-chan.png",
      position = { -0.5, 0 },
      scale = { 1, 1 }
    }
  }
}

local milk = speaker "Milk" {
  pose = 'default',
  poses = {
    default = {
      sprite = "Images/Milk.png",
      position = { 0.5, 0 },
      scale = { 2, 2 }
    }
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

novelchan "Hi! I'm Novel-chan!"
milk "Moooooo...."
novelchan:pose 'startled'
novelchan "Goodness! I didn't know high quality artwork could speak!"
