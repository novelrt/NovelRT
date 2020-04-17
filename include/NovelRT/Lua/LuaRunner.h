#include <string>
#include <novelrt.h>
namespace NovelRT::Lua {
  class LuaRunner {
  public:
    LuaRunner(std::string fileName);
    void init();
    void run();
  private:
    std::string _fileName;
    sol::state _state;
  };
}
