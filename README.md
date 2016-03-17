# tkd53: かな漢字変換システム

## セットアップ
```
$ git submodule update --init
```

## テストの実行
tkd53はテストフレームワークに[googletest](https://github.com/google/googletest)を使用しています。

### googletestをインストール
```
$ cd src/third_party/googletest/googletest/build-aux
$ cmake ../
$ make
$ mkdir -p ../../../../../tests/bin/gtest
$ cp libgtest.a libgtest_main.a ../../../../../tests/bin/gtest
```

### テストを実行
例えば、bigram_converterのテスト (bigram_converter_test) は次にようにして実行します。

```
$ cd src/converter
$ make test
$ cd ../../tests/bin/converter/
$ ./bigram_converter_test
```
