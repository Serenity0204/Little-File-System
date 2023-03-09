
# Little File System
A little file system that built with C++ SFML that simulates common operations on windows file system,
the user can select the terminal by clicking the terminal, and type in different commands to achieve 
desired behaviours, the custom part of command is quoted {}, and the command is in "", the user can type:

* "lfs touch {filename}.txt" to create a file
* "lfs mkdir {foldername}" to create a folder
* "lfs cd {foldername}" to switch into the directory
* "lfs back" to go back to the parent directory
* "lfs ls" to list all of the folders and files under the current directory
* "lfs rm {foldername} to remove the folder
* "lfs open {filename}.txt" to open the file, and click the file to start entering text
* "lfs save" to save the most recent opened file
* "lfs del {filename}.txt" to delete the file

## Demo
use this to generate image link: https://postimages.org/

* directory tree
[![directory-tree.png](https://i.postimg.cc/3R5mB8XT/directory-tree.png)](https://postimg.cc/Mc5nZ83P) 

* touch
[![touch.png](https://i.postimg.cc/3NNJW8xn/touch.png)](https://postimg.cc/p5Nt6t8F)
* mkdir
[![mkdir.png](https://i.postimg.cc/bvfJLfmw/mkdir.png)](https://postimg.cc/NKbBfSh3)

* cd
[![cd.png](https://i.postimg.cc/8PW9V81v/cd.png)](https://postimg.cc/564nwRQ9)
* back
[![back.png](https://i.postimg.cc/PxxQfDYc/back.png)](https://postimg.cc/sBkhwvn9)

* ls
[![ls.png](https://i.postimg.cc/qv3q8vXF/ls.png)](https://postimg.cc/HrTTmHN0)

* del
[![del.png](https://i.postimg.cc/15T4nq66/del.png)](https://postimg.cc/ykm72WLY)
* rm
[![rm.png](https://i.postimg.cc/jj6jF31Q/rm.png)](https://postimg.cc/KKzFKfxR)

* open
[![open.png](https://i.postimg.cc/1t9zhchx/open.png)](https://postimg.cc/rdPT54wg)
* after open
[![after-open.png](https://i.postimg.cc/h42Xnwt2/after-open.png)](https://postimg.cc/QVW8kf57)

* save
[![save.png](https://i.postimg.cc/3RnxK4Yk/save.png)](https://postimg.cc/47HgP3KG)

* after save
[![after-save.png](https://i.postimg.cc/VL5dkRSm/after-save.png)](https://postimg.cc/F759P0gB)



## Design
Can be found in https://github.com/Serenity0204/Little_File_System/blob/master/design.txt


## Features
- has a directory tree that shows the files and folders in tree like format
- has persistent storage that the files and folders will all be saved after closing the program, the data will remain when restart the program
- supports complex file and folder operations like create, read, update, and delete
- allows the user to switch between directories
- includes an easy to use and interactive commandline that allows the user to get instant feedbacks
- a file and folder terminal that will show the files and folders store



## System Setup

To run this project, please follow the system requirements below.


`Windows: `
  - compiler: g++ 7.3.0 
  - cmake: 3.20.0

`SFML setup: `
  - windows: https://docs.google.com/document/d/13Tn2sq9-CtAMuUenALlj1l4f8xL-BzeI8-DKRjhdPu0/edit?usp=sharing
  - mac https://docs.google.com/document/d/1ujZWMMvwwIH_dAd-X4JvcVdtn7B71-joOjbOo-vVXLY/edit?usp=sharing
