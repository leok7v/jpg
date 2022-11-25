@echo off
pushd ..
call scripts\download.bat stb_image.h https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
call scripts\download.bat quick.h     https://raw.githubusercontent.com/leok7v/quick.h/main/quick.h
call scripts\version.bat > src/version.h 2>nul
popd
exit /b 0