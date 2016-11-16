set PROGRAM="%~1"


rem Invalid arguments count
%PROGRAM% input\in1.txt output\out1.txt searchingString > %TEMP%\output.txt
fc %TEMP%\output.txt reference\ref1.txt
if ERRORLEVEL 1 goto err

rem Failed to open input file
%PROGRAM% input\inF2.txt output\out2.txt searchingString replaceString > %TEMP%\output.txt
fc %TEMP%\output.txt reference\ref2.txt
if ERRORLEVEL 1 goto err

rem Empty file
%PROGRAM% input\in3.txt output\out3.txt searchingString replaceString > %TEMP%\output.txt
fc %TEMP%\output.txt reference\ref3.txt
if ERRORLEVEL 1 goto err

rem Failed to open output file
%PROGRAM% input\in4.txt output\out4.txt searchingString replaceString > %TEMP%\output.txt
fc %TEMP%\output.txt reference\ref4.txt
if ERRORLEVEL 1 goto err

rem searchingString is empty
%PROGRAM% input\in5.txt output\out5.txt "" replaceString > %TEMP%\output.txt
fc %TEMP%\output.txt reference\ref5.txt
if ERRORLEVEL 1 goto err

rem searchingString is empty
%PROGRAM% input\in6.txt output\out6.txt carry CARRY
fc output\out6.txt reference\ref6.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1