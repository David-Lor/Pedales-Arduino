# Pedales-Arduino
Proyecto con Arduino que utiliza unos pedales de un volante USB para añadir dos teclas extra al ordenador controladas con los pies. La idea de este proyecto es, por ejemplo, añadir dos funcionalidades extra a los juegos de PC que se pueden controlar por los pies, como por ejemplo correr o agacharse.

El proyecto cuenta de dos partes: la parte que se ejecuta en Arduino y la parte que se ejecuta en el ordenador. En la parte de Arduino, el elemento principal son los pedales, que formaban parte de un volante USB sencillo. Estos pedales utilizan dos cables, que en su interior conectan en serie dos potenciómetros (uno por pedal). Pulsar un pedal u otro varia esta resistencia. Utilizando un divisor de tensión compuesto por una resistencia fija (utilicé 1K) y la propia resistencia variable de los pedales, se consigue una tensión que varía según los pedales que se hayan pulsado. Sin embargo más adelante quitaré este cable y añadire un sistema con mas cables (cuatro, dos para cada pedal).

Según el valor de tensión que llega a un input analogico en Arduino se interpreta qué pedal ha sido pulsado. Esta informacion se le envia al ordenador por serial, y un script (en Python) interpreta esta informacion y utiliza la libreria para python "keyboard" para ejecutar las acciones pertinentes (pulsar una tecla). La tecla se mantiene pulsada hasta que se deja de pulsar el pedal. Quizás seria interesante que el Arduino enviase directamente un valor analogico y el script en Python fuese quien se encargue de interpretarlo (para esto se podria usar directamente Firmata en el Arduino).
