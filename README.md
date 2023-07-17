# CPP Fractals
Progam made to visualise Julia Set. Its made completely in cpp with SDL2 library. It has user-friendly (at least I hope so) and it supports multithread rendering (SDL natively does not support GPU computing - color shaders).


## UI Preview
![ui preview](https://github.com/Zer0AlmostNull/CPP-Fractals/blob/main/assets/images/ui_preview.png?raw=true)

How to use ui:
| Object | Function |
| --------------- | --------------- |
| a (slider)   | Controls one of Julia Set's constant value (check out wiki page) (range -1.0f -> 1.0f)  |
| b (slider)  | Controls other of Julia Set's constant value  (range -1.0f -> 1.0f) |
| iteration (slider)   | Controls number of max iteration for each pixel (range 2 - 300) |
| zoom (slider)   | Controls zoom of rendering |
| dx (slider)  | Sets displacement in x axis (range -.5f -> .5f of screen width) |
| dy (slider)   | Sets displacement in y axis (range -.5f -> .5f of screen height)|
| gradient (checkbox)   | Toggles renderer to use color gradinent (blue - green - red - orange - red)|
| save (button)   | Saves current screen image (without UI) to ./img.bmp) |
| toggle UI (butotn)   | SToggles UI to hide |

## Generated fractals preview
| Images|
|-------|
| ![img](https://github.com/Zer0AlmostNull/CPP-Fractals/blob/main/assets/images/img1.bmp?raw=true) |
| ![img](https://github.com/Zer0AlmostNull/CPP-Fractals/blob/main/assets/images/img2.bmp?raw=true) |
| ![img](https://github.com/Zer0AlmostNull/CPP-Fractals/blob/main/assets/images/img4.bmp?raw=true) |
| ![img](https://github.com/Zer0AlmostNull/CPP-Fractals/blob/main/assets/images/img3.bmp?raw=true) |
| ![img](https://github.com/Zer0AlmostNull/CPP-Fractals/blob/main/assets/images/img.bmp?raw=true) |