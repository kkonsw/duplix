# Duplix

CLI приложение, которое позволяет выбрать папки, анализирует их, находит в этих папках идентичные (бинарно) файлы и выводит список дубликатов.

Использовал:

- C++17 (для `std::filesystem`)
- `Catch2` (для тестов)

Приложение было протестировано только на Linux!

## Сборка

Требуется `OpenSSl` (используется для вычисления хеша файлов).

```sh
mkdir build
cd build
cmake ..
make
```

## Алгоритм

1. Рекурсивно обходим указанные папки и сохраняем имена всех обычных непустых файлов.
2. Вычисляем md5 хеш каждого файла.
3. Выбираем файлы с одинаковым хэшем.

## Пример

```sh
duplix/release -> bin/duplix
duplix - CLI tool to find duplicate files in directories
Usage: ./duplix first_dir second_dir

duplix/release -> bin/duplix ./bin ./
Duplicate files:
./src/CMakeFiles/duplix.dir/flags.make
./src/duplix/CMakeFiles/duplix-lib.dir/flags.make
        md5 hash: 06d04f341af58a93926bc37da3ecc85b

./bin/tests
./bin/tests
        md5 hash: 9fc57c0360cf325760da131ad7e526b0

./bin/duplix
./bin/duplix
        md5 hash: b1b954e85f75487235c8c3672e4fefac

./src/CMakeFiles/CMakeDirectoryInformation.cmake
./src/duplix/CMakeFiles/CMakeDirectoryInformation.cmake
./tests/CMakeFiles/CMakeDirectoryInformation.cmake
./CMakeFiles/CMakeDirectoryInformation.cmake
        md5 hash: c49e6a4150d1c46b24880332e8656b39
```
