local runner = novelrt.NovelRunner:new(0, "NovelRT Lua");
local transformVec = novelrt.GeoVector2f:new(1920 / 2, 1080 / 2);
local scaleVec = novelrt.GeoVector2f:new(762, 811);
local transform = novelrt.Transform:new(transformVec, 10, scaleVec);
local rgbaConfig = novelrt.RGBAConfig:new(225, 0, 225, 225);

local renderer = runner.renderer;

local imageRect = renderer:createImageRect(transform, 3, "C:\\Users\\sirbr\\Documents\\coding\\projects\\Cpp\\NovelRT\\build\\samples\\LuaSamples\\Resources\\Images\\novel-chan.png", rgbaConfig);


runner:sceneConstructionRequested(function()
    imageRect:executeObjectBehaviour();
end);

runner:update(function()
    imageRect.transform.rotation = imageRect.transform.rotation + 1;
    print(imageRect.transform.rotation);
end);

runner:runNovel();