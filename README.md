# blink
Простейшая программа, написанная для в качестве примера для использования в обучающиъ статьях.

# Сборка
На данный момент, проект можно собрать двумя системами сборки: cmake и xmake. В процесс сборки представлен следующими шагами:
* git clone https://github.com/evgeniy1294/blink.git
* cd blink/
* git submodule init
* git submodule update
* Данный шаг зависит от предпочитаемой системы сборки. Для xmake:
    *  xmake f --toolchain=arm-none-eabi-gcc --arch=arm --plat=cross
    *  xmake build
* Cmake:
    *  cmake ./ -B ./build
    *  cmake --build ./out --target all
             
