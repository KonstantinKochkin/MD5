The program is designed to check the integrity of files by calculating the MD5 hash.\n\n\
MD5 [/H | /S STRING | /F FILE [/B] | /T | /W FILE | /C FILE1 FILE2 | /V FILE HASH]\n\
The calculated hashes are stored in 'Hashfile.txt'. Running without arguments \
displays all stored hashes.\n\n\
    /H - get help.\n\
    /S - calculate hash of string.\n\
    /F - calculate file hash and tries to verify it (/B - only calculate hash).\n\
    /T - turns on text input mode (сalculate the hash of the text. Signal to end input: ^Z).\n\
    /W - updates or writes new hash to the database.\n\
    /C - compares file hashes.\n\
    /V - verify a file by hash.\n
