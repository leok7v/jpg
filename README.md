# JPG

Simplified global variable free jpg encoder and decoder based on:
picojpeg - Public domain, Rich Geldreich <richgel99@gmail.com>
https://github.com/richgel999/picojpeg
and
jo_jpeg.cpp
public domain Simple, Minimalistic JPEG writer - http://jonolick.com
https://www.jonolick.com/uploads/7/9/2/1/7921194/jo_jpeg.cpp
https://github.com/dying153/jonolick.com


Assuming Microsoft Visual Studio 2022 Community Edition is installed from
  
https://visualstudio.microsoft.com/vs/community/

with SDK 10.0.222621 or better

from ``Developer Command Prompt 2022`` execute:

```
curl.exe "https://github.com/leok7v/quick/blob/main/quick.h"   --remote-name
curl.exe "https://github.com/leok7v/quick/blob/main/sample1.c" --remote-name
...
curl.exe "https://github.com/nothings/stb/blob/master/stb_image.h" --remote-name

user\quick>cl.exe sample1.c

user\quick>sample.exe
```

