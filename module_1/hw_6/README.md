Дано множество целых чисел из [0..109] размера n.  
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:  
10% перцентиль  
медиана  
90% перцентиль  
Требования:  

К дополнительной памяти: O(n).  
Среднее время работы: O(n)  
Должна быть отдельно выделенная функция partition.  
Рекурсия запрещена.  
Решение должно поддерживать передачу функции сравнения снаружи.  
Формат ввода  
Сначала вводится кол-во элементов массива n. После сам массив.  

Формат вывода  
Параметры множества в порядке:  

10% перцентиль  
медиана  
90% перцентиль  
6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”.  
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.  
Пример  
Ввод  
```10```  
```1 2 3 4 5 6 7 8 9 10 ```  
вывод  
```2```  
```6```  
```10```  

