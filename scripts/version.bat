@echo off
setlocal EnableDelayedExpansion
rem github builds in UTC timezone. To keep local builds
rem in monotonic sync with github version use UTC too.
for /f "tokens=* usebackq" %%i in (`tzutil /g`) do (
  set q="%%i"
)
set "tzrestore=tzutil /s %q%"
tzutil /s UTC
for /f "usebackq tokens=1,2 delims=,=- " %%i in (`wmic path win32_utctime get Year /value`) do @if %%i==Year (
     set year=%%j
)
for /f "usebackq tokens=1,2 delims=,=- " %%i in (`wmic path win32_utctime get Month /value`) do @if %%i==Month (
     set mm=%%j
)
for /f "usebackq tokens=1,2 delims=,=- " %%i in (`wmic path win32_utctime get Day /value`) do @if %%i==Day (
     set dd=%%j
)
set yy=%year:~2,2%
set hh=%time:~0,2%
set mm10=%mm%
set dd10=%dd%
set hh10=%hh%
rem mitigate for 08 and 09 are illegal octal constants in C
if "%mm10%" equ "08" ( set "mm10=8" )
if "%mm10%" equ "09" ( set "mm10=9" )
if "%dd10%" equ "08" ( set "dd10=8" )
if "%dd10%" equ "09" ( set "dd10=9" )
if "%hh10%" equ "08" ( set "hh10=8" )
if "%hh10%" equ "09" ( set "hh10=9" )
rem replace spaces with zeros:
set hh=%hh: =0%
set hash=10ca1c0de
set tag=10ca1c0de
git status >nul 2>nul
if %errorlevel% equ 0 (
  for /f "usebackq delims=" %%a in (`git rev-parse --short HEAD`) do (
    set hash=%%a
  )
  for /f "usebackq delims=" %%a in (`git describe --tags HEAD`) do (
    set tag=%%a
  )
)
echo #define version_hash "%hash%"
echo #define version_tag "%tag%"
echo #define version_yy (%yy%)
echo #define version_mm (%mm10%)
echo #define version_dd (%dd10%)
echo #define version_hh (%hh10%)
echo #define version_str "%yy%.%mm%.%dd%.%hh%UTC %hash%"
echo #define version_int32 (0x%yy%%mm%%dd%%hh%)
rem `git rev-parse --short HEAD` spits out 28 bit hash tail now
rem but there is no guarantee that someone decide to make it longer
echo #define version_hash_int64 (0x%hash%ULL)
%tzrestore%
