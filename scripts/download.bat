@echo off
if not exist "%1" (
  echo downloading "%1" from "%2" 
  curl.exe --silent "%2" --create-dirs --output "%1" 
)