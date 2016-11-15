set PROGRAM="%~1"

%PROGRAM% "10" "10" "12"
if ERRORLEVEL 1 goto err   

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1