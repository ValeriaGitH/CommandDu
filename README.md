# Aналог команды du (как в Linux) на C/C++
 Пример:
 /usr/bin/du -s /private/var/mobile/
 Вывод: (разделитель между размером и путем: \t, каждый путь на отдельной строке: \n)
 4400 /private/var/mobile/
 - по умолчанию занимаемое место выводить в 512-байтных блоках (округлять вверх по каждому файлу);
 - параметр -b выводит точный размер в байтах;
 - параметр -a выводит данные и для каждого файла;
 - параметр -c выводит в конце общий размер;
 - параметр -s выводит только общий размер;
 - размер занимаемого места самой папки (даже пустой) считать в блоках - 1 блок, в байтах - 0 байт.
 Вывод размеров писать в консоль в реальном времени обработки каталогов, как в настоящем du, а не накапливать список и выводить в конце.
 Обрабатывать ошибки, такие как отсутствие доступа к файлу или каталогу. Сообщения об ошибках выводить в err и продолжать обработку остального.
 Дополнение, которое не поддерживает оригинальный du, но должно быть реализовано: в параметрах можно задавать сразу несколько каталогов списком или браться из файла, если указан параметр типа --files-from=/tmp/oxytmp внутри файла список путей, по одному в каждой строке.
