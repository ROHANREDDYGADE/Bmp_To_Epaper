# BMP to ePaper or e-ink displays

#BMP command line 
.\bmp_to_epaper.exe <image_name.bmp> <profile_name>  you find the executables in bmp_to_epaper and bmp_to_epaper_linux




#image should be in bmp format


#when using gui there is no need to mention the profile but when using the cmd line the image should have the same height and width mentioned in the profile. All the profiles details are available in ModuleType.cpp file 


#If u want a profile which is not mentioned in the profiles you can add one in ModuleType.cpp file


#After making changes to the ModuleType.cpp you can execute it with g++ -o bmp_to_epaper.exe bmp_to_epaper.cpp ModuleType.cpp stdafx.cpp for windows

#g++ -o bmp_to_epaper.exe bmp_to_epaper.cpp ModuleType.cpp for linux.

#if the .exe files do not work execute them again as mentioned above 




