The program is designed to check the integrity of files by calculating the MD5 hash.

MD5 [/H | /S STRING | /F FILE [/B] | /T | /W FILE | /C FILE1 FILE2 | /V FILE HASH]
The calculated hashes are stored in 'Hashfile.txt'. Running without arguments
displays all stored hashes.

    /H - get help.
    /S - calculate hash of string.
    /F - calculate file hash and tries to verify it (/B - only calculate hash).
    /T - turns on text input mode (сalculate the hash of the text. Signal to end input: ^Z).
    /W - updates or writes new hash to the database.
    /C - compares file hashes.
    /V - verify a file by hash.
