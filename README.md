# blink
Простейшая программа, написанная для в качестве примера для использования в обучающиъ статьях.

# Сборка
На данный момент, проект можно собрать двумя системами сборки: cmake и xmake. В процесс сборки представлен следующими шагами:
    1) git clone git@github.com:evgeniy1294/blink.git
    2) cd blink
    3) git submodule init
    4) git submodule update
    5) Данный шаг зависит от предпочитаемой системы сборки:
        5.1) xmake build
        5.2) cmake ./ -B ./build 
             cmake --build ./out --target all
             
