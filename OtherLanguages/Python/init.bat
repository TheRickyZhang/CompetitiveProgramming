@echo off
set "prefix=%~1"
for %%f in (A B C D E F) do (
    copy /y Template.py "%prefix%%%f.py"
)
