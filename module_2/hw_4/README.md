Задача 4. Использование АВЛ-дерева (5 баллов)  
Обязательная задача  
Требование для всех вариантов Задачи 4  
Решение должно поддерживать передачу функции сравнения снаружи.  

4_2. Порядковые статистики. Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики задается числом k.  
Требования: скорость выполнения запроса - O(log n).   
Пример  
Ввод  
```5```  
```40 0```  
```10 1```  
```4 1```   
```-10 0```  
```50 2```  
вывод  
```40```  
```40```  
```10```  
```4```  
```50```  
