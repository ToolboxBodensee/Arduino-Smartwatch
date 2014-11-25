while true; do
cp ~/Programmieren/Arduino/OS/Programm/Librarys/Programm/* -R ~/sketchbook/libraries/Programm/
cp ~/Programmieren/Arduino/OS/Programm/Librarys/Bitmap/* -R ~/sketchbook/libraries/Bitmap/
echo copied
arduino ~/Programmieren/Arduino/OS/Programm/main/main_ino/main_ino.ino
done
