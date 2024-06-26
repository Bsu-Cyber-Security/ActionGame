# Основные ошибки и рекомендации

# Общее

## Структура кода

### Switch

Многие забывают обрабатывать случай по умолчанию (`default`). Важно всегда понимать, может ли проверяемое значение не попасть ни в один `case`, и если да, добавлять блок `default` (а даже если не может, то все равно добавить блок и бросить там исключение).

Но если вы проверяете значение перечисления (`enum class`), то `default`, наоборот, оставлять опасно, потому что при добавлении нового поля в enum оно попадёт в эту ветку без предупреждения компилятора о том, что не все варианты рассмотрены.

Здесь есть более общая рекомендация. Компилируемые языки, такие как C++, помогают отлавливать многие ошибки во время компиляции. Это лучше, чем обнаружить их в процессе исполнения кода. И этим стоит уметь пользоваться! Например, если компилятор помогает найти все места, где проверяются значения enum — не мешайте ему в этом. Если хотите чтобы метод не изменял значения полей класса — сделайте его `const`, пусть компилятор за этим проследит.

_Clang-Tidy_: [`bugprone-switch-missing-default-case`](https://clang.llvm.org/extra/clang-tidy/checks/bugprone/switch-missing-default-case.html)

### Конструкция if … else { весь код функции }

Избегайте чего-то такого:

```cpp
int find(std::vector<int>& array, int x) {
    if (array.empty()) {
        return 0;
    } else {
        int l = -1;
        int r = array.size();
        ...
        while (...) {
            ...
        }
        return r;
    }
}
```

Здесь получается, что весь код основной логики функции сдвинут на один отступ вправо. Это пустая трата места, особенно если внутри у вас есть длинные имена или выражения, которые из-за этого перестанут влезать в строку. Такой `else` можно опустить и писать код после `if () {}`, внутри которого делаете `return` или `throw`.

_Clang-Tidy_: [`readability-else-after-return`](https://clang.llvm.org/extra/clang-tidy/checks/readability/else-after-return.html)

## Другое

### Многофайловость

Если объявление находится в хедере `a.h`, то определение должно быть в `a.cpp`. Складывать все сигнатуры в один хедер и разносить реализации по нескольким cpp файлам не очень хорошо. Если хотите разнести что-то, разносите вплоть до интерфейса.

### Аккуратность

Когда написали код, посмотрите на него и подумайте, нельзя ли его упростить. Если есть ощущение, что в стандартной библиотеке должна быть функция, которая поможет писать меньше кода, стоит попробовать её найти. Если в библиотеке такой функции не нашлось, подумайте, как она должна была бы выглядеть, если бы существовала, и реализуйте её именно в таком переиспользуемом виде вместо того, чтобы делать функцию, которая имеет смысл только в рамках вашей задачи.

В том числе не забывайте, как "засунуть слона в холодильник". Такой подход переиспользования готовых блоков и написания функций "сверху вниз" очень сильно улучшает читаемость кода, а это станет очень важно, когда вы начнете работать в команде.

### Особенности языка

Старайтесь не использовать экзотические вещи, про которые вам не рассказывали на лекциях. Например, альтернативные операторы — `and`, `not` и т.п.
Также обходите стороной оператор `,` — от него одни проблемы.

_Clang-Tidy_: [`readability-operators-representation`](https://clang.llvm.org/extra/clang-tidy/checks/readability/operators-representation.html)

### Namespace aliases

В будущем желательно не использовать `using namespace std`. Обычно это запрещено стайлгайдами. Если правда нужно сэкономить место, можно использовать отдельные алиасы: `using std::cin;` и т.д. Но даже его не стоит делать в заголовочных файлах. В них старайтесь сохранять интерфейс максимально чистым.

_Clang-Tidy_: [`google-build-using-namespace`](https://clang.llvm.org/extra/clang-tidy/checks/google/build-using-namespace.html)

### Ввод/вывод

Если выводите какие-то строки в поток, хорошим стилем считается завершить вывод переносом строки (`\n`).

Также лучше использовать `'\n'` вместо `std::endl`. `std::endl` — довольно странная вещь, которая делает две вещи:

- выводит `'\n'`;
- сбрасывает буффер вывода (вызывает `flush`).

В тех редких случаях, когда это правда нужно, стайлгайды рекомендуют явно делать `std::cout.flush()` вместо этого.

_Clang-Tidy_: [`performance-avoid-endl`](https://clang.llvm.org/extra/clang-tidy/checks/performance/avoid-endl.html)

### Объявления переменных

- Не объявляйте несколько переменных в одной строке, это только ухудшает читаемость.
- По возможности инициализируйте переменную сразу при объявлении. Например, это будет важно для констант (`const`).

_Плохо:_
```cpp
int a = 0, b;
b = 1;
```

_Хорошо:_
```cpp
int a = 0;
const int b = 1;
```

_Clang-Tidy_:
- [`readability-isolate-declaration`](https://clang.llvm.org/extra/clang-tidy/checks/readability/isolate-declaration.html)
- [`cppcoreguidelines-init-variables`](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines/init-variables.html)

### “Магические” константы

В коде не должно быть чисел, про которые может быть не очевидно, что они означают. Такие числа стоит складывать в константу с понятным именем. Преимуществ сразу несколько:

- Имя позволяет понимать, что в этом месте кода вообще происходит (не `while (n < 130000)`, а `while (n < MAX_SEARCH_DEPTH)`);
- Для изменения значения достаточно поменять всего одно место в коде;
- Позволяет избежать коллизий, то есть придать разный смысл числам `2` в коде.

_Примеры:_

- `ch - 48` — не надо знать эти коды наизусть и ожидать, что кто-то другой их знает. Для перевода char в int делайте так: `ch - '0'`.
- Ещё хуже: `ch + 32`. Для перевода в lower case аналогично: `ch - 'A' + 'a'`.
- `for (int i = 0; i < 16; ++i)` — замените на переменную `MAX_DECIMAL_LENGTH`, а лучше используйте `while (n > 0)`.

_Clang-Tidy_: [`readability-magic-numbers`](https://clang.llvm.org/extra/clang-tidy/checks/readability/magic-numbers.html)

<details>
<summary>

### Исключения (будет позже)
</summary>

Для простоты вам показывали, как бросать числа в качестве исключений. Теперь вы знакомы с классами, поэтому больше никогда так не делайте. Есть стандартные типы исключений в хедере `[<stdexcept>](https://en.cppreference.com/w/cpp/header/stdexcept)`. В большинстве случаев выброс исключения выглядит как-то так:

```cpp
try {
    ...
    throw std::runtime_error("Your message");
    ...
} catch (const std::runtime_error& ex) {
    std::cerr << "Runtime error: " << ex.what();
    return 1;
}
```

Еще можно обрабатывать исключения используя наследование.
</details>

## Дробные типы

### Сравнение дробных чисел

Как только вы начинаете работать с числами типа `double`, нельзя делать проверки `x == y`, `x < y` и т.п. Например, на самом деле `0.1 * 3 > 0.3`, а иногда `0 != -0`. Как сравнивать дробные числа, если это всё таки нужно, разобрано [здесь](https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss).

### Преобразования типов и округления

Нежелательно использовать синтаксис `(int)x` или `int(x)` для преобразований. Вместо этого используйте `static_cast<int>(x)`. Первый вариант (C-style cast) может использовать разные виды преобразований в зависимости от контекста, поэтому может сделать не то, что вы хотели.
В частности, есть задачи, где вам вообще не нужен целочисленный результат, поэтому нужно было использовать функции округления — `std::floor` и `std::ceil`.

_Clang-Tidy_: [`cppcoreguidelines-pro-type-cstyle-cast`](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines/pro-type-cstyle-cast.html)

Неявные преобразования — тоже плохо. Старайтесь проверять, какой тип принимает функция, и если это необходимо, преобразовывать аргументы явно. А также не использовать конструкцию `if (x)`, если `x` — не типа `bool`. Лучше читается явное `x != 0`, `!x.empty()`, `x != ""` и т.п.

_Clang-Tidy_: [`readability-implicit-bool-conversion`](https://clang.llvm.org/extra/clang-tidy/checks/readability/implicit-bool-conversion.html)

### C-style функции

Не нужно использовать `fabs`, `abs`, `fmax`, `sqrtf` и т.п. Это наследие из C, которое работает в C++ исключительно по историческим причинам. Если их использовать, могут случиться неожиданные преобразования типов.
Вместо этого используйте `std::abs`, `std::max`.

### `std::pow`

Есть такой метод стандартной библиотеки для возведения x в степень y. Но важно понимать, что он работает с дробными числами и вычисляет `exp(y * log(x))`. Поэтому использовать его **с целыми числами запрещено**! Ответ никогда не получится целым числом до округления. На некоторых платформах есть даже [примеры](https://stackoverflow.com/questions/15851636/why-is-my-integer-math-with-stdpow-giving-the-wrong-answer), когда округление даёт неправильный ответ.

Поэтому для возведения в квадрат всегда делайте просто `x * x`, а если `x` — это какое-то выражение, то лучше напишите свою функцию `sqr(x)`.

[_What Every Computer Scientist Should Know About Floating-Point Arithmetic_](https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html)

### Парсинг чисел из строки

Функция `std::stoi` парсит число типа `int`. Если вам нужно дробное число, используйте [`std::stod`](https://en.cppreference.com/w/cpp/string/basic_string/stof). Если `long long` — `std::stoll`. А вообще, по возможности, стоит сразу читать число из потока ввода и не пользоваться такой конвертацией.

</details>

<details>
<summary>

## Для продвинутых
</summary>

Принимать компаратор как указатель на функцию не всегда корректно. Например, лямбда-выражения с непустым списком захвата не умеют преобразовываться к указателю на функцию. Для хранения всего, что может использоваться как функция, подходит `std::function`.
Однако, даже это не идеальное решение. Дело в том, что преобразование лямбда выражений к `std::function` занимает какое-то время. Чтобы выжать максимум производительности из кода, можно принимать замыкание напрямую. Но тип замыкания известен только компилятору (вы не можете описать его в коде). Решение заключается в том, чтобы сделать тип принимаемой функции шаблонным. Тогда, что бы вы ни передавали в качестве компаратора — функцию, функтор или замыкание, компилятор выведет точный тип, и они не будут преобразовываться для передачи в функцию.

```cpp
template <class T, class Comp>
void sort(std::vector<T>& array, const Comp& comparator);
```
</details>
