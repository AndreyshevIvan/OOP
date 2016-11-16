set PROGRAM="%~1"

rem Invalid arguments count
%PROGRAM% in1.txt %TEMP%\out.txt "searchingString"
fc.exe %TEMP%\out.txt reference\ref1.txt
if ERRORLEVEL 1 goto err

rem Failed to open input file
%PROGRAM% input\inF2.txt %TEMP%\out.txt "searchingString" "replaceString"
fc.exe %TEMP%\out.txt reference\ref2.txt
if ERRORLEVEL 1 goto err

rem Empty file
%PROGRAM% input\in3.txt %TEMP%\out.txt "searchingString" "replaceString"
fc.exe %TEMP%\out.txt reference\ref3.txt
if ERRORLEVEL 1 goto err

rem Failed to open output file
%PROGRAM% input\in4.txt %TEMP%\out.txt "searchingString" "replaceString"
fc.exe %TEMP%\out.txt reference\ref4.txt
if ERRORLEVEL 1 goto err

rem searchingString is empty
%PROGRAM% input\in5.txt %TEMP%\out.txt "" "replaceString"
fc.exe %TEMP%\out.txt reference\ref5.txt
if ERRORLEVEL 1 goto err

rem searchingString is empty
%PROGRAM% input\in6.txt %TEMP%\out.txt "carry" "CARRY"
fc.exe %TEMP%\out.txt reference\ref6.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1