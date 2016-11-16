set PROGRAM="%~1" 

rem Invalid arguments count
%PROGRAM% input\in1.txt output\out1.txt "hello" > output\out1.txt
if %ERRORLEVEL% EQU 0 goto err
fc output\out1.txt reference\ref1.txt
if ERRORLEVEL 1 goto err
	
rem Input file not open
%PROGRAM% input\in22.txt output\out2.txt "hello" "hell" > %TEMP%\out.txt
if %ERRORLEVEL% EQU 0 goto err
fc %TEMP%\out.txt reference\ref2.txt
if ERRORLEVEL 1 goto err

rem Input file is empty
%PROGRAM% input\in3.txt output\out3.txt "Empty" "Empty file" > %TEMP%\out.txt
if %ERRORLEVEL% EQU 0 goto err
fc %TEMP%\out.txt reference\ref3.txt
if ERRORLEVEL 1 goto err

rem Output not open
%PROGRAM% input\in4.txt %TEMP%\out.txt "2" "123"
if %ERRORLEVEL% EQU 1 goto err
fc %TEMP%\out.txt reference\ref4.txt
if ERRORLEVEL 1 goto err

rem Search string is empty
%PROGRAM% input\in5.txt output\out5.txt "" "not empty string" > %TEMP%\out.txt
if %ERRORLEVEL% EQU 0 goto err
fc %TEMP%\out.txt reference\ref5.txt
if ERRORLEVEL 1 goto err

rem Normal replace
%PROGRAM% input\in6.txt output\out6.txt "<replace me>" "CARRY"
if NOT %ERRORLEVEL% EQU 0 goto err
fc output\out6.txt reference\ref6.txt
if ERRORLEVEL 1 goto err

rem Test from sample
%PROGRAM% input\in7.txt output\out7.txt "1231234" "<new string>"
if NOT %ERRORLEVEL% EQU 0 goto err
fc output\out7.txt reference\ref7.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
