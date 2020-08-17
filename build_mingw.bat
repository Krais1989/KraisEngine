"%CMAKE%" -S . -B project_builds/cmake/vs2019 -G "MinGW Makefiles"
"%CMAKE%" --build project_builds/cmake/vs2019
pause