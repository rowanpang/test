*** Settings ***
# N.B. @{arguments} must be defined before importing this resource file
Library     ./myLibrary.py  @{arguments}

*** Keywords ***
Show files
    ${files} =  myLibrary.getFiles
    log to console  the files are ${files}