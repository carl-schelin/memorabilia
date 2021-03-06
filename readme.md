### Overview

This repo contains all the source code for games and utilities I created between apparently 1979 and 1997 or so. I thought I'd share them both for the Memorabilia per the repo name, and to show that I did some coding back in the day :) 


### CXL/TCXL

I was looking for a DOS based Windowing library and after a few failed attempts, I found Mike Smedley's CXL library. I used it and purchased it simply because I could get it to work :) Several of the programs in the repository use the CXL library to create windowed applications. You can tell by seeing cxlxxxx in the include lines.

Later a company called Tesseract that had been creating TSR (Terminate and Stay Resident) programs bought the rights to CXL and called it TCXL. Chips intention was to convert it into a multi-platform library. You can see where I started using it by seeing tcxlxxxx in the include lines. One thing to note was due to the multi-platform goal, a lot of the C internals had wrappers. For example, int became IntT. You'll see that a lot in my code.

Of course neither of these libraries are available (although I think I might still have the diskette I got from Mike). And without the TurboC or Borland C++ compilers, it's unlikely they'll be compilable any time soon.


### 3Com Networks

In the Networking directories may be some utilities I created for 3Com's 3+Share local area networking environments. As such they're certainly not useful nowadays :) Still, interesting ideas I had there to help manage my networks.


### Dungeons & Dragons

This directory structure contains my Computerized Dungeon Master. I wrote it to help me run my games. I'd have a laptop (a small Toshiba 1100+) and could enter character information. I gradually improved it and even converted it to C in order to learn how to program in C.


### Games

This one contains my very first program that I created for a purpose, CARWARS.BAS. A program that helped you create vehicles for Steve Jackson's Car Wars game. In the ORIGINAL directory contains the same program but converted to C.

It also contains my BlokBust/Dot2Dot program I created. It is the old draw a grid, then one person draws a line between two points. If they complete a box, they get an extra turn. At the end, the person with the most boxes wins. I'd played it in the past using paper and pencil and at a 3Com Conference, I played it with the guy sitting next to me (boring presentation). Then when I got home, I created the version 1 in Basic. Then converted it at Version 2 to C. And then Version 3 where I was trying to use NetBIOS sockets so others can play the game with you across the network. I think that one didn't work but Version 1 and Version 2 certainly did.

Third is my 3D StarTrek program. It was based on the Super StarTrek from the Unix days but I added graphics and a console to it. Once I even got a writeup in one of the gaming magazines that talked about Star Trek games.


### Internet Tools

This is just my Metal DOS based Newsreader. It was something I created while working at Johns Hopkins Applied Physics Lab. I was a 3Com LAN admin and trainer but it was pretty idle so the boss wanted me to create a DOS based news reader. It was quite enlightening and I think the main reason I got hired a few years later as a Unix admin.


### Network Programs 

These utilities are larger more involved tools. They're also ones I created vs just using a library call so they were Shareware. I actually did get a couple of bucks for some of these tools so someone thought they were worth it.

### Network Utilities

These utilities are smaller things that were likely just library calls I compiled and maybe inhanced a little.


### Utilities

Most of these were used to add functionality to my batch files. Things that were missing in DOS. Upon review, several seem to mimic some Unix/Linux type utilities so there's some commonality there. Many have a DOC file.

