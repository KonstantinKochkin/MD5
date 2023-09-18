# Console hasher with MD5
```
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
```
## Example 1
```
\MD5\test>MD5.exe /S test_string
3474851a3410906697ec77337df7aae4
\MD5\test>MD5.exe /S md5
1bc29b36f623ba82aaf6724fd3b16718
```
## Example 2
```
\MD5\test>MD5.exe /F test1_md5.txt
Result - TRUE. File has NOT been modified!
File name:        test1_md5.txt
Full path:        D:\Tools\MVS_Projects\Repos\MD5\test\test1_md5.txt
New hash:         1bc29b36f623ba82aaf6724fd3b16718
Hash in hashfile: 1bc29b36f623ba82aaf6724fd3b16718
```
