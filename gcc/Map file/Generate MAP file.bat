REM For ITI: This batch file creates helpful troubleshooting details. For the time-being, we'll refer to this as the MAP file.

set OUTPUT_PATH=..\exe

REM Set directory to the present working directory. Not needed if this batch file is run directly, but necessary when this batch file is run from VBA or Eclipse.
cd /d "%~dp0"

REM Print the project size
"arm-none-eabi-size.exe" "%OUTPUT_PATH%\output.axf" > "temp"
echo . >> "temp"

REM Print the location of every function and variable
"arm-none-eabi-nm.exe" "%OUTPUT_PATH%\output.axf" >> "temp0"
sort "temp0" >> "temp"
del "temp0"
echo . >> "temp"

REM Replace the .map file with the updated version
REM SAVE FOR WHEN WE HAVE AN ACTUAL MAP FILE: type "%OUTPUT_PATH%\output.map" >> "%OUTPUT_PATH%\temp"
copy /y "temp" "output.map"
del "temp"

timeout /t 3
REM pause