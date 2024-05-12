Собрать проект:
```
mkdir build
cd build
cmake ..
make
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

Результат работы примера:
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