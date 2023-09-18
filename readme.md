# Console hasher with MD5
```
The program is designed to check the integrity of files by calculating the MD5 hash.

MD5 [/H | /S STRING | /F FILE [/B] | /T | /W FILE | /C FILE1 FILE2 | /V FILE HASH]
The calculated hashes are stored in 'Hashfile.txt'. Running without arguments
displays all stored hashes.

    /H - get help.
    /S - calculate hash of string.
    /F - calculate file hash and tries to verify it (/B - only calculate hash).
    /T - turns on text input mode (calculate the hash of the text. Signal to end input: ^Z).
    /W - updates or writes new hash to the database.
    /C - compares file hashes.
    /V - verify a file by hash.
```
## Example 0
```
\MD5>MD5.exe
Filename                                                 md5 hash
D:\Tools\MVS_Projects\Repos\MD5\test\test1_md5.txt       1bc29b36f623ba82aaf6724fd3b16718
D:\Tools\MVS_Projects\Repos\MD5\test\test3.txt           d4c40ac9a474601fedfd41b02f2c88da
D:\Tools\MVS_Projects\Repos\MD5\test\test4_as_test3.txt  d4c40ac9a474601fedfd41b02f2c88da
D:\Tools\MVS_Projects\Repos\MD5\test\Autoruns.exe        a217a4233d83cfa84055ccd285a508d0
```
## Example 1
```
\MD5>MD5.exe /S test_string
3474851a3410906697ec77337df7aae4
\MD5\test>MD5.exe /S md5
1bc29b36f623ba82aaf6724fd3b16718
```
## Example 2
```
\MD5>MD5.exe /F test\test1_md5.txt
Result - TRUE. File has NOT been modified!
File name:        test1_md5.txt
Full path:        D:\Tools\MVS_Projects\Repos\MD5\test\test1_md5.txt
New hash:         1bc29b36f623ba82aaf6724fd3b16718
Hash in hashfile: 1bc29b36f623ba82aaf6724fd3b16718
```
## Example 3
```
\MD5.exe /F test\test2_empty.txt
There are no such file in the database!
File name:        test\test2_empty.txt
Full path:        D:\Tools\MVS_Projects\Repos\MD5\test\test2_empty.txt
New hash:         d41d8cd98f00b204e9800998ecf8427e
```
## Example 4
```
\MD5.exe /W test\test2_empty.txt
File name:        test\test2_empty.txt
Full path:        D:\Tools\MVS_Projects\Repos\MD5\test\test2_empty.txt
New hash:         d41d8cd98f00b204e9800998ecf8427e
\MD5.exe
Filename                                                 md5 hash
D:\Tools\MVS_Projects\Repos\MD5\test\test1_md5.txt       1bc29b36f623ba82aaf6724fd3b16718
D:\Tools\MVS_Projects\Repos\MD5\test\test3.txt           d4c40ac9a474601fedfd41b02f2c88da
D:\Tools\MVS_Projects\Repos\MD5\test\test4_as_test3.txt  d4c40ac9a474601fedfd41b02f2c88da
D:\Tools\MVS_Projects\Repos\MD5\test\Autoruns.exe        a217a4233d83cfa84055ccd285a508d0
D:\Tools\MVS_Projects\Repos\MD5\test\test2_empty.txt     d41d8cd98f00b204e9800998ecf8427e
```
## Example 5
```
\MD5.exe /T
multiline
text
^Z
4cf874dd8e467805ca4ba66744251d31
\MD5.exe /T
^Z
d41d8cd98f00b204e9800998ecf8427e
```
## Example 6
```
\MD5.exe /C test\test1_md5.txt test\test3.txt
File 1: test\test1_md5.txt               Hash: 1bc29b36f623ba82aaf6724fd3b16718
File 2: test\test3.txt                   Hash: d4c40ac9a474601fedfd41b02f2c88da
Files are DIFFERENT!
\MD5.exe /C test\test3.txt test\test4_as_test3.txt
File 1: test\test3.txt                   Hash: d4c40ac9a474601fedfd41b02f2c88da
File 2: test\test4_as_test3.txt          Hash: d4c40ac9a474601fedfd41b02f2c88da
Files are IDENTICAL!
```
## Example 7
```
\MD5.exe /V test\test1_md5.txt 1bc29b36f623ba82aaf6724fd3b16718
Calculated hash:   1bc29b36f623ba82aaf6724fd3b16718
Verification hash: 1bc29b36f623ba82aaf6724fd3b16718
Verification was SUCCESSFUL!
```
