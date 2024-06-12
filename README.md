Собрать проект:
```
mkdir build
cd build
cmake ..
make
```

Для запуска программы нужно создать карту с файлом карты map.txt
файл карты должен лежать в папке, откуда запускается программа
Пример карты
```
-3 0 3 wall
-3 1 2 exit
-3 2 1 free
-3 3 0 wall
-2 -1 3 free
-2 0 2 exit
-2 1 1 wall
-2 2 0 free
-2 3 -1 exit
-1 -2 3 wall
-1 -1 2 free
-1 0 1 exit
-1 1 0 wall
-1 2 -1 free
-1 3 -2 exit
0 -3 3 wall
0 -2 2 exit
0 -1 1 wall
0 0 0 free
0 1 -1 exit
0 2 -2 free
0 3 -3 wall
1 -3 2 exit
1 -2 1 free
1 -1 0 free
1 0 -1 exit
1 1 -2 free
1 2 -3 wall
2 -3 1 exit
2 -2 0 wall
2 -1 -1 wall
2 0 -2 exit
2 1 -3 free
3 -3 0 free
3 -2 -1 exit
3 -1 -2 free
3 0 -3 wall
```

Реалзиовано:
- объявление переменных ```digit|logic varName[[size1, size2, ..., sizeN]]=CONST;```
- узнать размер переменной ```size(varName);```
- изменить размер переменной ```resize(varname, [size1, size2, ..., sizeN]);```
- вывод переменной ```print(varname[[ind1,ind2,...,indN]]);``` - поддерживает обращение по индексу

Пример скрипта:
```
digit abc=1;
logic q=true;
digit var1[3,3]=7;
logic switch[7] = false;

size(var1);
resize(var1, [4,4]);

print(var1);
print(var1[2,3]); # обращение по индексу начинается с 1
```

Результат работы примера (ОБЪЯВЛЕНИЕ И ВЫВОД):
```
>>> digit abc=1;
    Вы ввели: digit abc=1;
    Variable name: abc
    Dimensions: 1 
    Default value: 1 
    Type: digit
>>> logic q=true;
    Вы ввели: logic q=true;
    Variable name: q
    Dimensions: 1 
    Default value: 1 
    Type: logic
>>> digit var1[3,3]=7;
    Вы ввели: digit var1[3,3]=7;
    Variable name: var1
    Dimensions: 3 3 
    Default value: 7 7 7 7 7 7 7 7 7 
    Type: digit
>>> logic switch[7] = false;
    Вы ввели: logic switch[7] = false;
    Variable name: switch
    Dimensions: 7 
    Default value: 0 0 0 0 0 0 0 
    Type: logic
>>> size(var1);
    Вы ввели: size(var1);
    Найдена переменная: var1
    [3, 3]
>>> resize(var1, [4,4]);
    Вы ввели: resize(var1, [4,4]);
    Найдена переменная: var1
    [3, 3]
>>> print(var1);
    Вы ввели: print(var1);
    Значения переменной var1:
    [[7, 7, 7], [7, 7, 7], [7, 7, 7]]
>>> print(var1[2,3]);
    Вы ввели: print(var1[2,3]);
    Значения переменной var1:
    7
>>> 
```

ПРИСВАИВАНИЕ:
```
digit lol=6;digit kek=5;digit amogus=0;
amogus = lol + kek * gt(6) && eq(!(!(6))) + 72 / 3 * 4;
```
В результате переменная amogus будет равна 102

Операторы сравнения с нулем (используются в арифметических выражениях):
```
eq(varname)
lt(varname)
gt(varname)
lte(varname)
gte(varname)
```

Оператор НЕ (используется в арифметических выражениях)
```
!(varname)
```

Логическое И (используется в арифметических выражениях)
```
varname && varname
```

Оператор most (используется в ариф выр) - возвращает true, если большинство элементов ненулевые, иначе false
```
most(varname)
```

Оператор цикла for

Синтаксис
```
for начальное_значение_счетчика stop конечное_значение_счетчика step шаг_изменения счетчика {оператор;};
```

Цикл на 10 итераций
```
digit lol=0;
for 0 stop 10 step 1 {operator;}; 
```
Результат цикла lol = 10;

Оператор цикла с многомерными счетчиками
(Итерации выполняются, пока все счетчики не достигнут конечного значения.
То есть, пока первый счетчик не накопит конечное значение, другие счетчики не начнут накапливаться)
```
digit lol=0;
for [0,1,2] stop [10,-1,4] step [1,-1,1] {lol=lol+1;}; 
```
Результат цикла lol = 14;

Условный оператор

Синтаксис:
```
check условие then {оператор;};
check условие then {оператор;} otherwise {оператор;};
```

Объявление функций

Синтаксис:
```
тип routing имя_функции(параметр1, параметр2){оператор;return что-нибудь;};
```

Пример:
```
digit routing sum(a,b){digit result=0;result=a+b;return result;};
```

Вызов функции:
```
perform sum(1,6);
```

Ожидается, что функция всегда что-то возвращает и используется в арифметическом выражении
Пример:
```
digit tmp=0;
digit routing sum(a,b){digit result=0;result=a+b;return result;};
tmp=perform sum(7,5);
```
Результат работы программы: tmp=12;

Операторы управления роботом:
Движение робота (параметром передается насколько клеток сделать шаг в текущем направлении)
```
move(varname);
```

Поворот робота (только на угол кратный 60 градусам)
```
rotate(varname);
```

Узнать, что робот видит
```
surrundings();
```

У робота есть рассудок, если робот долго не может найти выход, он расстраивается и самоуничтожается

Чтобы повысить рассудок, робот должен увидеть выход в результате работы команды surrundings
Или периодически проявлять вежливость командами
```
please;
thank you;
```
От излишней вежливости робот также сходит с ума
Если робот переместится в стену, он самоуничтожится