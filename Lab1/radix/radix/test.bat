set PROGRAM="%~1"

rem Invalid arguments count
%PROGRAM% 16 10 > %TEMP%\out.txt
if %ERRORLEVEL% EQU 0 goto err
fc %TEMP%\out.txt reference\ref1.txt
if ERRORLEVEL 1 goto err

rem Invalid radix
%PROGRAM% 10 1 15 > %TEMP%\out.txt
if %ERRORLEVEL% EQU 0 goto err
fc %TEMP%\out.txt reference\ref2.txt
if ERRORLEVEL 1 goto err

rem Invalid character for this radix
%PROGRAM% 16 10 ZZ > %TEMP%\out.txt
if %ERRORLEVEL% EQU 0 goto err
fc %TEMP%\out.txt reference\ref3.txt
if ERRORLEVEL 1 goto err

rem value == 0
%PROGRAM% 3 10 -00000 > %TEMP%\out.txt
if %ERRORLEVEL% EQU 1 goto err
fc %TEMP%\out.txt reference\ref4.txt
if ERRORLEVEL 1 goto err

rem value == INT_MIN in 10 radix
%PROGRAM% 10 16 -2147483648 > %TEMP%\out.txt
if %ERRORLEVEL% EQU 1 goto err
fc %TEMP%\out.txt reference\ref5.txt
if ERRORLEVEL 1 goto err

rem value == INT_MIN in 36 radix
%PROGRAM% 36 10 -ZIK0ZK > %TEMP%\out.txt
if %ERRORLEVEL% EQU 1 goto err
fc %TEMP%\out.txt reference\ref6.txt
if ERRORLEVEL 1 goto err

rem overflow value < INT_MIN
%PROGRAM% 10 30 -2147483649 > %TEMP%\out.txt
if %ERRORLEVEL% EQU 0 goto err
fc %TEMP%\out.txt reference\ref7.txt
if ERRORLEVEL 1 goto err

rem value == INT_MAX in 12 radix
%PROGRAM% 12 10 4BB2308A7 > %TEMP%\out.txt
if %ERRORLEVEL% EQU 1 goto err
fc %TEMP%\out.txt reference\ref8.txt
if ERRORLEVEL 1 goto err

rem overflow value > INT_MAX in 10 radix 
%PROGRAM% 10 20 2147483648 > %TEMP%\out.txt
if %ERRORLEVEL% EQU 0 goto err
fc %TEMP%\out.txt reference\ref9.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1