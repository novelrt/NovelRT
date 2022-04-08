import os

class GenerateDeps():

    template = """#Dependencies required by NovelRT on Windows/macOS
set(DEPENDENCY_FILES
#DEP#
)

foreach(dependency ${DEPENDENCY_FILES})
  configure_file(${dependency} ${dependency} COPYONLY)
endforeach()

add_library(ThirdParty INTERFACE IMPORTED GLOBAL)
set_property(TARGET ThirdParty PROPERTY RESOURCE ${DEPENDENCY_FILES})
if(WIN32 OR APPLE)
  set(ext "")
  if(WIN32)
    set(ext "*.dll")
  else()
    set(ext "*.dylib")
  endif()
  install(FILES ${DEPENDENCY_FILES}
    DESTINATION bin
  )
endif()"""

    def CreateCMakeLists(self, depPath, cmakePath):
        files = os.scandir(depPath)
        safeExts = [".dll",".so",".a",".dylib"]
        strArray = ""
        for entry in files:
            for ext in safeExts:
                    if ext in entry.name:
                        st = """\t${CMAKE_BINARY_DIR}"""
                        st += f'/thirdparty/{entry.name}\n'
                        strArray += st
        template = self.template.replace('#DEP#',strArray)
        if not os.path.isdir(cmakePath):
            try:
                os.mkdir(cmakePath)
            except:
                print(f"Cannot create the directory when it does not exist!\nAttempted to create directory: {cmakePath}")
        with open(f'{cmakePath}/CMakeLists.txt', 'w') as f:
            for line in template:
                f.write(line)
            f.write('\n')
            f.close()
        print(f"Wrote Dependencies CMakeList to: {cmakePath}/CMakeLists.txt")
